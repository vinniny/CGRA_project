/* =========================================================================
 * cgra_kernels_cnn_v2.h — All-16-PE CGRA FC kernels for MNIST CNN (v2)
 *
 * Upgrade from v1 (cgra_kernels_cnn.h): all 16 PEs compute MAC in parallel
 * using dual-port SPM (Port A = activation via SRC_SPM, Port B = weight via
 * SRC_SPM2). Activations broadcast to all PE SPMs once per inference;
 * weights preloaded per-group per-PE via SG-DMA chains.
 *
 * FC1 (400→64): 4 groups  (vs 16 in v1), 16 neurons/group, ~4× speedup.
 * FC2 ( 64→10): 1 group   (vs  3 in v1), neurons 10-15 padded to 0.
 *
 * SPM layout per PE (identical for all 16 PEs):
 *   spm[0 .. N_INPUTS-1]          — activations  (Port A, broadcast-loaded)
 *   spm[CNN_V2_WGT_OFFSET ..
 *       CNN_V2_WGT_OFFSET+N_INPUTS-1] — weights (Port B, per-PE per-group)
 *
 * MAC instruction: OP_MAC(src0=SRC_SPM, src1=SRC_SPM2, imm=CNN_V2_WGT_OFFSET)
 *   Port A addr = spm_iter_cnt + context_pc          (base = 0)
 *   Port B addr = CNN_V2_WGT_OFFSET + spm_iter_cnt + context_pc
 *
 * PE-to-neuron mapping within group g:
 *   PE[row=r][col=c]  →  neuron  g*16 + r*4 + c
 *
 * Result order from cnn_fc_v2_run_group(g, result[16]):
 *   result[r*4+c] = dot-product for neuron g*16 + r*4 + c
 *   (column c is read from RESULT_ROW_r during the col=c readout pass)
 *
 * Per-inference call sequence:
 *   cnn_fc1_v2_build_chains(fc1_w_ddr);   // once per boot
 *   cnn_fc2_v2_build_chains(fc2_w_ddr);   // once per boot
 *   ...
 *   cnn_fc1_v2_act_preload(act400_ddr);    // once per inference
 *   for (g = 0; g < CNN_FC1_V2_N_GROUPS; g++)
 *       cnn_fc1_v2_run_group(g, &acc[g*16]);  // 4 groups
 *   // ARM: bias + ReLU → quantize → 64 int32 activations at act64_ddr
 *   cnn_fc2_v2_act_preload(act64_ddr);
 *   for (g = 0; g < CNN_FC2_V2_N_GROUPS; g++)
 *       cnn_fc2_v2_run_group(g, &acc[g*16]);  // 1 group (acc[10..15] unused)
 * ========================================================================= */

#ifndef CGRA_KERNELS_CNN_V2_H
#define CGRA_KERNELS_CNN_V2_H

#include "cgra.h"

#ifndef CFGW
#define CFGW(op, s0, s1, dst, route, imm) \
    (  ((uint64_t)(op)     & 0x3F)         \
     | (((uint64_t)(s0)    & 0xF) <<  6)   \
     | (((uint64_t)(s1)    & 0xF) << 10)   \
     | (((uint64_t)(dst)   & 0xF) << 14)   \
     | (((uint64_t)(route) & 0xF) << 18)   \
     | ((uint64_t)(imm)           << 24))
#endif

/* ---- Shared v2 weight SPM base offset ---------------------------------- */
#define CNN_V2_WGT_OFFSET    512u   /* weights at spm[512..511+N_INPUTS] */

/* ---- FC1 (400→64) v2 constants ----------------------------------------- */
#define CNN_FC1_V2_N_INPUTS    400u
#define CNN_FC1_V2_N_OUTPUTS    64u
#define CNN_FC1_V2_N_GROUPS      4u   /* ceil(64/16) */
#define CNN_FC1_V2_LOOP_COUNT   24u   /* ceil(400/16)-1 : 25×16=400 MACs/PE */
#define CNN_FC1_V2_SPM_BPN     (CNN_FC1_V2_N_INPUTS * 4u)  /* bytes/neuron */
#define CNN_FC1_V2_CHAINS_DDR   0x00116000UL   /* ~0xC40 bytes used */

/* ---- FC2 (64→10) v2 constants ------------------------------------------ */
#define CNN_FC2_V2_N_INPUTS     64u
#define CNN_FC2_V2_N_OUTPUTS    10u
#define CNN_FC2_V2_N_GROUPS      1u   /* ceil(10/16) = 1; neurons 10-15 unused */
#define CNN_FC2_V2_LOOP_COUNT    3u   /* ceil(64/16)-1 : 4×16=64 MACs/PE */
#define CNN_FC2_V2_SPM_BPN     (CNN_FC2_V2_N_INPUTS * 4u)
#define CNN_FC2_V2_CHAINS_DDR   0x00117000UL   /* ~0x940 bytes used */

/* ---- SG-DMA descriptor table offsets (relative to chains_ddr) ---------- */
#define CNN_V2_OFF_OPWORDS   0x000u   /* 8 × 8B  = 0x40 */
#define CNN_V2_OFF_ACC_CLR   0x040u   /* 32 descs = 0x200 */
#define CNN_V2_OFF_MAC       0x240u   /* 32 descs = 0x200 */
#define CNN_V2_OFF_RELAY     0x440u   /* 32 descs = 0x200 (all PEs → PASS0(SRC_W,E)) */
#define CNN_V2_OFF_RO0       0x640u   /* 8 descs  = 0x080 (col=0 PEs → PASS0(SRC_RF,E)) */
#define CNN_V2_OFF_RO1       0x6C0u   /* 8 descs */
#define CNN_V2_OFF_RO2       0x740u   /* 8 descs */
#define CNN_V2_OFF_RO3       0x7C0u   /* 8 descs */
#define CNN_V2_OFF_SPM_WGT   0x840u   /* 16 descs × 0x100 per group */

/* =========================================================================
 * Internal helpers
 * ========================================================================= */

/* Write one 64-bit opword to slot 0 of all 16 PEs (32 HI+LO descriptors).
 * Slot-0 broadcaster in cgra_top auto-fills slots 1-15 with the same word. */
static inline void cnn_fc_v2_build_all16_chain(
        volatile cgra_sg_dma_descriptor_t *desc,
        uint32_t hi_src, uint32_t lo_src)
{
    int pe;
    for (pe = 0; pe < 16; pe++) {
        uint32_t cfg_base = CGRA_PFX_CONFIG | ((uint32_t)(pe & 0xF) << 7);
        desc[pe*2  ].src      = hi_src;
        desc[pe*2  ].dst      = cfg_base;
        desc[pe*2  ].size     = 4u;
        desc[pe*2  ].next_ptr = (uint32_t)(uintptr_t)(&desc[pe*2+1]);
        desc[pe*2+1].src      = lo_src;
        desc[pe*2+1].dst      = cfg_base | 4u;
        desc[pe*2+1].size     = 4u;
        desc[pe*2+1].next_ptr = (pe < 15) ? (uint32_t)(uintptr_t)(&desc[pe*2+2]) : 0u;
    }
    asm volatile("dsb" ::: "memory");
}

/* Write one 64-bit opword to slot 0 of the 4 PEs in column `col` (8 descs).
 * col=c: PE IDs are c, c+4, c+8, c+12. */
static inline void cnn_fc_v2_build_col_chain(
        volatile cgra_sg_dma_descriptor_t *desc,
        int col, uint32_t hi_src, uint32_t lo_src)
{
    int r;
    for (r = 0; r < 4; r++) {
        int pe = r * 4 + col;
        uint32_t cfg_base = CGRA_PFX_CONFIG | ((uint32_t)(pe & 0xF) << 7);
        desc[r*2  ].src      = hi_src;
        desc[r*2  ].dst      = cfg_base;
        desc[r*2  ].size     = 4u;
        desc[r*2  ].next_ptr = (uint32_t)(uintptr_t)(&desc[r*2+1]);
        desc[r*2+1].src      = lo_src;
        desc[r*2+1].dst      = cfg_base | 4u;
        desc[r*2+1].size     = 4u;
        desc[r*2+1].next_ptr = (r < 3) ? (uint32_t)(uintptr_t)(&desc[r*2+2]) : 0u;
    }
    asm volatile("dsb" ::: "memory");
}

/* Build all SG-DMA descriptor tables for one v2 FC layer.
 * chains_ddr must be at least 16-byte aligned.                             */
static inline int cnn_fc_v2_build_chains(
        uint32_t chains_ddr,
        uint32_t fc_w_spm_ddr,
        uint32_t n_outputs,
        uint32_t n_groups,
        uint32_t spm_bytes_per_neuron)
{
    int c, g, pe;

    /* ---- Opword storage area at chains_ddr+CNN_V2_OFF_OPWORDS ---------- */
    volatile uint32_t *op = (volatile uint32_t *)(chains_ddr + CNN_V2_OFF_OPWORDS);

    uint64_t acc_clr_w = CFGW(OP_ACC_CLR, 0,       0,       0, 0,       0);
    uint64_t mac_v2_w  = CFGW(OP_MAC,     SRC_SPM, SRC_SPM2, 0, 0,      CNN_V2_WGT_OFFSET);
    uint64_t p0_rf_w   = CFGW(OP_PASS0,   SRC_RF,  0,       0, ROUTE_E, 0);
    uint64_t p0_we_w   = CFGW(OP_PASS0,   SRC_W,   0,       0, ROUTE_E, 0);

    op[0] = (uint32_t)(acc_clr_w >> 32); op[1] = (uint32_t)(acc_clr_w & 0xFFFFFFFFuL);
    op[2] = (uint32_t)(mac_v2_w  >> 32); op[3] = (uint32_t)(mac_v2_w  & 0xFFFFFFFFuL);
    op[4] = (uint32_t)(p0_rf_w   >> 32); op[5] = (uint32_t)(p0_rf_w   & 0xFFFFFFFFuL);
    op[6] = (uint32_t)(p0_we_w   >> 32); op[7] = (uint32_t)(p0_we_w   & 0xFFFFFFFFuL);

    uint32_t base   = chains_ddr;
    uint32_t hi_acc = base + CNN_V2_OFF_OPWORDS + 0u;
    uint32_t lo_acc = base + CNN_V2_OFF_OPWORDS + 4u;
    uint32_t hi_mac = base + CNN_V2_OFF_OPWORDS + 8u;
    uint32_t lo_mac = base + CNN_V2_OFF_OPWORDS + 12u;
    uint32_t hi_p0r = base + CNN_V2_OFF_OPWORDS + 16u;
    uint32_t lo_p0r = base + CNN_V2_OFF_OPWORDS + 20u;
    uint32_t hi_p0w = base + CNN_V2_OFF_OPWORDS + 24u;
    uint32_t lo_p0w = base + CNN_V2_OFF_OPWORDS + 28u;

    /* ---- ACC_CLR chain: all 16 PEs (32 descs) -------------------------- */
    volatile cgra_sg_dma_descriptor_t *d_acc =
        (volatile cgra_sg_dma_descriptor_t *)(base + CNN_V2_OFF_ACC_CLR);
    cnn_fc_v2_build_all16_chain(d_acc, hi_acc, lo_acc);

    /* ---- MAC_V2 restore chain: all 16 PEs (32 descs) ------------------- */
    volatile cgra_sg_dma_descriptor_t *d_mac =
        (volatile cgra_sg_dma_descriptor_t *)(base + CNN_V2_OFF_MAC);
    cnn_fc_v2_build_all16_chain(d_mac, hi_mac, lo_mac);

    /* ---- Relay init chain: all 16 PEs → PASS0(SRC_W,E) (32 descs) ----- */
    volatile cgra_sg_dma_descriptor_t *d_rel =
        (volatile cgra_sg_dma_descriptor_t *)(base + CNN_V2_OFF_RELAY);
    cnn_fc_v2_build_all16_chain(d_rel, hi_p0w, lo_p0w);

    /* ---- Per-column readout chains (4 × 8 descs) ----------------------- */
    for (c = 0; c < 4; c++) {
        uint32_t ro_off = CNN_V2_OFF_RO0 + (uint32_t)c * 0x80u;
        volatile cgra_sg_dma_descriptor_t *d_ro =
            (volatile cgra_sg_dma_descriptor_t *)(base + ro_off);
        cnn_fc_v2_build_col_chain(d_ro, c, hi_p0r, lo_p0r);
    }

    /* ---- Per-group SPM weight load chains (16 descs/group) ------------- */
    volatile cgra_sg_dma_descriptor_t *d_wt =
        (volatile cgra_sg_dma_descriptor_t *)(base + CNN_V2_OFF_SPM_WGT);
    for (g = 0; g < (int)n_groups; g++) {
        volatile cgra_sg_dma_descriptor_t *dc = &d_wt[g * 16];
        int last_valid = -1;
        for (pe = 0; pe < 16; pe++) {
            uint32_t neuron = (uint32_t)g * 16u + (uint32_t)pe;
            if (neuron < n_outputs) last_valid = pe;
        }
        for (pe = 0; pe < 16; pe++) {
            uint32_t neuron = (uint32_t)g * 16u + (uint32_t)pe;
            if (neuron >= n_outputs) break;
            uint32_t src = fc_w_spm_ddr + neuron * spm_bytes_per_neuron;
            uint32_t dst = CGRA_SPM_PE_ADDR((uint32_t)pe, CNN_V2_WGT_OFFSET);
            int last = (pe == last_valid);
            dc[pe].src      = src;
            dc[pe].dst      = dst;
            dc[pe].size     = spm_bytes_per_neuron;
            dc[pe].next_ptr = last ? 0u : (uint32_t)(uintptr_t)(&dc[pe+1]);
        }
    }
    asm volatile("dsb" ::: "memory");

    /* ---- Init: set all 16 PEs to relay state (PASS0(SRC_W,E)) --------- */
    cgra_sg_dma_start(base + CNN_V2_OFF_RELAY);
    return cgra_sg_dma_wait(5000000u);
}

/* Run one 16-neuron group (weight load → ACC_CLR → MAC → readout).
 * result[r*4+c] = int32 dot-product for neuron g*16 + r*4 + c.
 * Activations must be pre-loaded into SPM[0..N_INPUTS-1] of all PEs
 * (via cnn_fc*_v2_act_preload before the first group of each inference). */
static inline int cnn_fc_v2_run_group(
        uint32_t chains_ddr,
        int g,
        uint32_t loop_count,
        uint32_t n_outputs,
        int32_t result[16])
{
    uint32_t base = chains_ddr;
    int c, r;

    /* Step 1: preload weights for this group (16 PEs, sequential DMA) */
    cgra_sg_dma_start(base + CNN_V2_OFF_SPM_WGT + (uint32_t)g * 16u * 16u);
    if (cgra_sg_dma_wait(10000000u)) return -1;

    /* Step 2: ACC_CLR all 16 PEs, run 1 slot */
    cgra_sg_dma_start(base + CNN_V2_OFF_ACC_CLR);
    if (cgra_sg_dma_wait(5000000u)) return -1;
    cgra_wr(CGRA_CU_PC_END, 0u);
    cgra_cu_start();
    if (cgra_cu_wait(1000000u)) return -1;

    /* Step 3: restore MAC_V2 to all 16 PEs */
    cgra_sg_dma_start(base + CNN_V2_OFF_MAC);
    if (cgra_sg_dma_wait(5000000u)) return -1;

    /* Step 4: MAC loop — all 16 PEs accumulate in parallel */
    cgra_wr(CGRA_LOOP_START,   0u);
    cgra_wr(CGRA_LOOP_END,     15u);
    cgra_wr(CGRA_LOOP_COUNT,   loop_count);
    cgra_wr(CGRA_CU_PC_END,    15u);
    cgra_wr(CGRA_SPM_AUTO_INC, 1u);
    cgra_cu_start();
    if (cgra_cu_wait(5000000u)) return -1;
    cgra_wr(CGRA_SPM_AUTO_INC, 0u);

    /* Step 5: init relay state — all 16 PEs → PASS0(SRC_W, ROUTE_E) */
    cgra_sg_dma_start(base + CNN_V2_OFF_RELAY);
    if (cgra_sg_dma_wait(5000000u)) return -1;

    /* Step 6: 4-column readout — one CU run per column */
    for (c = 0; c < 4; c++) {
        uint32_t ro_off = CNN_V2_OFF_RO0 + (uint32_t)c * 0x80u;

        /* Switch col=c PEs to PASS0(SRC_RF, ROUTE_E) */
        cgra_sg_dma_start(base + ro_off);
        if (cgra_sg_dma_wait(5000000u)) return -1;

        cgra_wr(CGRA_CU_PC_END, 15u);
        cgra_cu_start();
        if (cgra_cu_wait(1000000u)) return -1;

        /* Capture row results for this column */
        for (r = 0; r < 4; r++) {
            uint32_t neuron = (uint32_t)g * 16u + (uint32_t)r * 4u + (uint32_t)c;
            uint32_t row_reg;
            switch (r) {
                case 0: row_reg = CGRA_RESULT_ROW0; break;
                case 1: row_reg = CGRA_RESULT_ROW1; break;
                case 2: row_reg = CGRA_RESULT_ROW2; break;
                default: row_reg = CGRA_RESULT_ROW3; break;
            }
            result[r * 4 + c] = (neuron < n_outputs) ? (int32_t)cgra_rd(row_reg) : 0;
        }
    }
    return 0;
}

/* =========================================================================
 * Public API — FC1 (400→64) v2
 * ========================================================================= */

/* Build SG-DMA chains once at boot. fc1_w_ddr points to the weight blob
 * (64 neurons × 400 words × 4B = 102400B, same layout as v1).             */
static inline int cnn_fc1_v2_build_chains(uint32_t fc1_w_ddr)
{
    return cnn_fc_v2_build_chains(
        CNN_FC1_V2_CHAINS_DDR, fc1_w_ddr,
        CNN_FC1_V2_N_OUTPUTS, CNN_FC1_V2_N_GROUPS,
        CNN_FC1_V2_SPM_BPN);
}

/* Broadcast 400 int32 activations to all 16 PEs' spm[0..399].
 * Call once per inference before the first FC1 group.                      */
static inline int cnn_fc1_v2_act_preload(uint32_t act_ddr)
{
    return cgra_dma(act_ddr, CGRA_SPM_BCAST_ADDR(0u), CNN_FC1_V2_N_INPUTS * 4u);
}

static inline int cnn_fc1_v2_run_group(int g, int32_t result[16])
{
    return cnn_fc_v2_run_group(CNN_FC1_V2_CHAINS_DDR, g,
                               CNN_FC1_V2_LOOP_COUNT,
                               CNN_FC1_V2_N_OUTPUTS, result);
}

/* =========================================================================
 * Public API — FC2 (64→10) v2
 * ========================================================================= */

static inline int cnn_fc2_v2_build_chains(uint32_t fc2_w_ddr)
{
    return cnn_fc_v2_build_chains(
        CNN_FC2_V2_CHAINS_DDR, fc2_w_ddr,
        CNN_FC2_V2_N_OUTPUTS, CNN_FC2_V2_N_GROUPS,
        CNN_FC2_V2_SPM_BPN);
}

/* Broadcast 64 int32 activations to all 16 PEs' spm[0..63].
 * Call once per inference before FC2 (after FC1 + bias/ReLU/quant).       */
static inline int cnn_fc2_v2_act_preload(uint32_t act_ddr)
{
    return cgra_dma(act_ddr, CGRA_SPM_BCAST_ADDR(0u), CNN_FC2_V2_N_INPUTS * 4u);
}

static inline int cnn_fc2_v2_run_group(int g, int32_t result[16])
{
    return cnn_fc_v2_run_group(CNN_FC2_V2_CHAINS_DDR, g,
                               CNN_FC2_V2_LOOP_COUNT,
                               CNN_FC2_V2_N_OUTPUTS, result);
}

#endif /* CGRA_KERNELS_CNN_V2_H */
