/* =========================================================================
 * cgra_kernels_cnn.h — CGRA FC kernels for MNIST CNN inference
 *
 * Two FC layers:
 *   FC1: 400 inputs → 64 outputs  (LOOP_COUNT=24, 25×16=400 MACs/neuron)
 *   FC2:  64 inputs → 10 outputs  (LOOP_COUNT= 3,  4×16= 64 MACs/neuron)
 *
 * Uses SPM-backed MAC v2 infrastructure (identical structure to LPR FC v2):
 *   - One INT16 weight per 32-bit SPM word (lower 16 bits, upper = 0)
 *   - SPM auto-inc: spm_iter_cnt += 16 per loop wrap
 *   - Tile auto-inc: tile bank address advances by 16 per loop wrap
 *   - CGRA runs 4 neurons per group (one per row, col=0 PEs)
 *   - col=1,2,3 PEs: east-chain PASS0 (set once by build_chains)
 *   - SG-DMA chains pre-built in DDR by cnn_fc{1,2}_build_chains()
 *
 * Weight binary layout (mnist_weights_spm.bin, from quantize_cgra.py):
 *   FC1: [64 neurons × 400 words × 4 bytes] = 102400 bytes
 *   FC2: [10 neurons ×  64 words × 4 bytes] =   2560 bytes
 *   Total: 104960 bytes
 *
 * Call sequence per inference:
 *   cnn_fc1_build_chains(fc1_w_ddr);        // once per boot
 *   cnn_fc2_build_chains(fc2_w_ddr);        // once per boot
 *   ...
 *   cnn_fc1_tile_preload(act400_ddr);        // load 400 int32 activations
 *   for (g = 0; g < CNN_FC1_N_GROUPS; g++)
 *       cnn_fc1_run_group(g, &acc[g*4]);     // 16 groups
 *   // ARM: bias + ReLU → quantize → store 64 int32 acts at act64_ddr
 *   cnn_fc2_tile_preload(act64_ddr);
 *   for (g = 0; g < CNN_FC2_N_GROUPS; g++)
 *       cnn_fc2_run_group(g, &acc[g*4]);     // 3 groups (acc[8..11] unused)
 * ========================================================================= */

#ifndef CGRA_KERNELS_CNN_H
#define CGRA_KERNELS_CNN_H

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

/* ---- FC1 (400→64) constants -------------------------------------------- */
#define CNN_FC1_N_INPUTS    400u
#define CNN_FC1_N_OUTPUTS    64u
#define CNN_FC1_N_GROUPS     16u   /* ceil(64/4) */
#define CNN_FC1_LOOP_COUNT   24u   /* ceil(400/16) - 1  (25 passes × 16 = 400) */
#define CNN_FC1_SPM_BPN     (CNN_FC1_N_INPUTS * 4u)   /* bytes per neuron */
#define CNN_FC1_CHAINS_DDR   0x00114000UL  /* 0x720 bytes used */

/* ---- FC2 (64→10) constants --------------------------------------------- */
#define CNN_FC2_N_INPUTS     64u
#define CNN_FC2_N_OUTPUTS    10u
#define CNN_FC2_N_GROUPS      3u   /* ceil(10/4) — last group has 2 valid neurons */
#define CNN_FC2_LOOP_COUNT    3u   /* ceil(64/16) - 1  (4 passes × 16 = 64) */
#define CNN_FC2_SPM_BPN     (CNN_FC2_N_INPUTS * 4u)
#define CNN_FC2_CHAINS_DDR   0x00115000UL  /* 0x3E0 bytes used */

/* col=0 PE IDs for the 4 rows */
static const uint8_t cnn_fc_col0_ids[4] = {0u, 4u, 8u, 12u};

/* =========================================================================
 * Internal helpers
 * ========================================================================= */

/* Build an 8-descriptor SG-DMA chain that writes one 64-bit config word
 * (hi_src / lo_src) to slot 0 of each col=0 PE (rows 0-3).               */
static inline void cnn_fc_build_col0_chain(
        volatile cgra_sg_dma_descriptor_t *desc,
        uint32_t hi_src, uint32_t lo_src)
{
    int r;
    for (r = 0; r < 4; r++) {
        uint32_t cfg_base = CGRA_PFX_CONFIG
                          | (((uint32_t)cnn_fc_col0_ids[r] & 0xFu) << 7);
        desc[r*2  ].src      = hi_src;
        desc[r*2  ].dst      = cfg_base;
        desc[r*2  ].size     = 4u;
        desc[r*2  ].next_ptr = (uint32_t)(uintptr_t)(&desc[r*2+1]);
        desc[r*2+1].src      = lo_src;
        desc[r*2+1].dst      = cfg_base | 4u;  /* bit[2]=1 → commit + broadcaster */
        desc[r*2+1].size     = 4u;
        desc[r*2+1].next_ptr = (r < 3) ? (uint32_t)(uintptr_t)(&desc[r*2+2]) : 0u;
    }
    asm volatile("dsb" ::: "memory");
}

/* Build all SG-DMA descriptor tables for one FC layer into chains_ddr.
 * chains_ddr must be 16-byte aligned; n_outputs must be a multiple of 4
 * or the final group will have fewer than 4 active neurons (handled).    */
static inline int cnn_fc_build_chains(
        uint32_t chains_ddr,
        uint32_t fc_w_spm_ddr,
        uint32_t n_outputs,
        uint32_t n_groups,
        uint32_t spm_bytes_per_neuron)
{
    /* Opword area at chains_ddr+0x00 (8 words × 4B = 32B) */
    volatile uint32_t *op = (volatile uint32_t *)chains_ddr;
    uint64_t acc_clr_w = CFGW(OP_ACC_CLR, 0,       0,       0, 0,       0);
    uint64_t mac_w     = CFGW(OP_MAC,     SRC_W,   SRC_SPM, 0, 0,       0);
    uint64_t p0_rf_w   = CFGW(OP_PASS0,   SRC_RF,  0,       0, ROUTE_E, 0);
    uint64_t p0_we_w   = CFGW(OP_PASS0,   SRC_W,   0,       0, ROUTE_E, 0);
    op[0] = (uint32_t)(acc_clr_w >> 32); op[1] = (uint32_t)(acc_clr_w & 0xFFFFFFFFuL);
    op[2] = (uint32_t)(mac_w     >> 32); op[3] = (uint32_t)(mac_w     & 0xFFFFFFFFuL);
    op[4] = (uint32_t)(p0_rf_w   >> 32); op[5] = (uint32_t)(p0_rf_w   & 0xFFFFFFFFuL);
    op[6] = (uint32_t)(p0_we_w   >> 32); op[7] = (uint32_t)(p0_we_w   & 0xFFFFFFFFuL);

    uint32_t base   = chains_ddr;
    uint32_t hi_acc = base + 0u,  lo_acc = base + 4u;
    uint32_t hi_mac = base + 8u,  lo_mac = base + 12u;
    uint32_t hi_p0r = base + 16u, lo_p0r = base + 20u;
    uint32_t hi_p0w = base + 24u, lo_p0w = base + 28u;

    /* acc_clr chain at +0x20 (8 descs) */
    volatile cgra_sg_dma_descriptor_t *d_acc =
        (volatile cgra_sg_dma_descriptor_t *)(base + 0x20u);
    cnn_fc_build_col0_chain(d_acc, hi_acc, lo_acc);

    /* mac_restore chain at +0xA0 (8 descs) */
    volatile cgra_sg_dma_descriptor_t *d_mac =
        (volatile cgra_sg_dma_descriptor_t *)(base + 0xA0u);
    cnn_fc_build_col0_chain(d_mac, hi_mac, lo_mac);

    /* readout chain at +0x120 (8 descs) */
    volatile cgra_sg_dma_descriptor_t *d_ro =
        (volatile cgra_sg_dma_descriptor_t *)(base + 0x120u);
    cnn_fc_build_col0_chain(d_ro, hi_p0r, lo_p0r);

    /* init_chain at +0x1A0 (24 descs: col=1,2,3 × 4 rows × 2 HI/LO) */
    volatile cgra_sg_dma_descriptor_t *d_ic =
        (volatile cgra_sg_dma_descriptor_t *)(base + 0x1A0u);
    {
        int i = 0, r, c;
        for (r = 0; r < 4; r++) {
            for (c = 1; c < 4; c++) {
                uint32_t pe      = (uint32_t)r * 4u + (uint32_t)c;
                uint32_t cfg_base = CGRA_PFX_CONFIG | ((pe & 0xFu) << 7);
                int last = (r == 3 && c == 3);
                d_ic[i  ].src = hi_p0w; d_ic[i  ].dst = cfg_base;
                d_ic[i  ].size = 4u;
                d_ic[i  ].next_ptr = (uint32_t)(uintptr_t)(&d_ic[i+1]);
                d_ic[i+1].src = lo_p0w; d_ic[i+1].dst = cfg_base | 4u;
                d_ic[i+1].size = 4u;
                d_ic[i+1].next_ptr = last ? 0u : (uint32_t)(uintptr_t)(&d_ic[i+2]);
                i += 2;
            }
        }
        asm volatile("dsb" ::: "memory");
    }

    /* SPM preload chains at +0x320 (n_groups groups × 4 descs each) */
    volatile cgra_sg_dma_descriptor_t *d_spm =
        (volatile cgra_sg_dma_descriptor_t *)(base + 0x320u);
    {
        uint32_t g, r;
        for (g = 0; g < n_groups; g++) {
            volatile cgra_sg_dma_descriptor_t *dc = &d_spm[g * 4];
            for (r = 0; r < 4; r++) {
                uint32_t neuron = g * 4u + r;
                if (neuron >= n_outputs) break;
                uint32_t src = fc_w_spm_ddr + neuron * spm_bytes_per_neuron;
                uint32_t dst = CGRA_PFX_SPM
                             | (((uint32_t)cnn_fc_col0_ids[r] & 0xFu) << 12);
                int last = (r == 3u || neuron == n_outputs - 1u);
                dc[r].src      = src;
                dc[r].dst      = dst;
                dc[r].size     = spm_bytes_per_neuron;
                dc[r].next_ptr = last ? 0u : (uint32_t)(uintptr_t)(&dc[r+1]);
            }
        }
        asm volatile("dsb" ::: "memory");
    }

    /* One-time east-chain init (col=1,2,3 → PASS0) */
    cgra_sg_dma_start(base + 0x1A0u);
    if (cgra_sg_dma_wait(5000000u)) return -1;

    /* Broadcast MAC to all 16 PEs (col=0 only to avoid overwriting PASS0) */
    cgra_sg_dma_start(base + 0xA0u);
    return cgra_sg_dma_wait(5000000u);
}

/* Run one 4-neuron group (MAC loop + readout).
 * Assumes tile has been preloaded and build_chains was called once.
 * result[r] = int32 dot-product for neuron g*4+r.                       */
static inline int cnn_fc_run_group(
        uint32_t chains_ddr,
        int g,
        uint32_t loop_count,
        uint32_t n_outputs,
        int32_t result[4])
{
    uint32_t base = chains_ddr;

    /* Step 1: SPM preload for this group */
    cgra_sg_dma_start(base + 0x320u + (uint32_t)g * 4u * 16u);
    if (cgra_sg_dma_wait(5000000u)) return -1;

    /* Step 2: clear accumulators */
    cgra_sg_dma_start(base + 0x20u);
    if (cgra_sg_dma_wait(5000000u)) return -1;
    cgra_wr(CGRA_CU_PC_END, 2u);
    cgra_cu_start();
    if (cgra_cu_wait(1000000u)) return -1;

    /* Step 3: restore MAC to col=0 PEs */
    cgra_sg_dma_start(base + 0xA0u);
    if (cgra_sg_dma_wait(5000000u)) return -1;

    /* Step 4: MAC loop */
    cgra_wr(CGRA_LOOP_START,    0u);
    cgra_wr(CGRA_LOOP_END,      15u);
    cgra_wr(CGRA_LOOP_COUNT,    loop_count);
    cgra_wr(CGRA_CU_PC_END,     15u);
    cgra_wr(CGRA_TILE_AUTO_INC, 1u);
    cgra_wr(CGRA_SPM_AUTO_INC,  1u);
    cgra_cu_start();
    if (cgra_cu_wait(5000000u)) return -1;
    cgra_wr(CGRA_TILE_AUTO_INC, 0u);
    cgra_wr(CGRA_SPM_AUTO_INC,  0u);

    /* Step 5: readout (east chain → RESULT_ROW0-3) */
    cgra_sg_dma_start(base + 0x120u);
    if (cgra_sg_dma_wait(5000000u)) return -1;
    cgra_wr(CGRA_CU_PC_END, 15u);
    cgra_cu_start();
    if (cgra_cu_wait(1000000u)) return -1;

    uint32_t active = 4u;
    if ((uint32_t)(g * 4) + 4u > n_outputs)
        active = n_outputs - (uint32_t)(g * 4);
    result[0] = (active > 0u) ? (int32_t)cgra_rd(CGRA_RESULT_ROW0) : 0;
    result[1] = (active > 1u) ? (int32_t)cgra_rd(CGRA_RESULT_ROW1) : 0;
    result[2] = (active > 2u) ? (int32_t)cgra_rd(CGRA_RESULT_ROW2) : 0;
    result[3] = (active > 3u) ? (int32_t)cgra_rd(CGRA_RESULT_ROW3) : 0;
    return 0;
}

/* =========================================================================
 * Public API — FC1 (400→64)
 * ========================================================================= */

static inline int cnn_fc1_build_chains(uint32_t fc1_w_spm_ddr)
{
    return cnn_fc_build_chains(CNN_FC1_CHAINS_DDR, fc1_w_spm_ddr,
                               CNN_FC1_N_OUTPUTS, CNN_FC1_N_GROUPS,
                               CNN_FC1_SPM_BPN);
}

static inline int cnn_fc1_run_group(int g, int32_t result[4])
{
    return cnn_fc_run_group(CNN_FC1_CHAINS_DDR, g,
                            CNN_FC1_LOOP_COUNT, CNN_FC1_N_OUTPUTS, result);
}

/* Load 400 int32 activations into all 4 tile banks (broadcast). */
static inline int cnn_fc1_tile_preload(uint32_t act_ddr)
{
    return cgra_dma(act_ddr, CGRA_TILE_BCAST, CNN_FC1_N_INPUTS * 4u);
}

/* =========================================================================
 * Public API — FC2 (64→10)
 * ========================================================================= */

static inline int cnn_fc2_build_chains(uint32_t fc2_w_spm_ddr)
{
    return cnn_fc_build_chains(CNN_FC2_CHAINS_DDR, fc2_w_spm_ddr,
                               CNN_FC2_N_OUTPUTS, CNN_FC2_N_GROUPS,
                               CNN_FC2_SPM_BPN);
}

static inline int cnn_fc2_run_group(int g, int32_t result[4])
{
    return cnn_fc_run_group(CNN_FC2_CHAINS_DDR, g,
                            CNN_FC2_LOOP_COUNT, CNN_FC2_N_OUTPUTS, result);
}

/* Load 64 int32 activations into all 4 tile banks (broadcast). */
static inline int cnn_fc2_tile_preload(uint32_t act_ddr)
{
    return cgra_dma(act_ddr, CGRA_TILE_BCAST, CNN_FC2_N_INPUTS * 4u);
}

/* =========================================================================
 * Conv3×3 9-tap kernel (single output pixel)
 * =========================================================================
 * Computes one output pixel = sum_{i=0..8} input[i] * weight[i].
 *
 * Layout (proven by tb_suite_cnn_kernel.svh CK23..CK25):
 *   - SPM[2..10] = 9 weights (SPM[0,1, 11..15] = 0)
 *   - tile bank 0, words 2..10 = 9 input pixels (rest = 0)
 *   - PE0 runs MAC kernel with SPM_AUTO_INC=1, TILE_AUTO_INC=1, LOOP_COUNT=0
 *   - Slots {3..11} commit per the empirical slot model (others are zero-pad)
 *   - alu_result on PE0 = the convolution output
 *
 * Caller must place 9-element weight + input arrays in DDR, then provide the
 * staging address for the SPM load. Returns 0 on success, -1 on timeout.
 * ========================================================================= */
static inline int cnn_conv3x3_pixel(
        uint32_t staging_ddr,    /* scratch 4-byte aligned region (>=8 bytes) */
        uint32_t weights_ddr,    /* 16 int32 words: zeros except [2..10] */
        uint32_t inputs_ddr,     /* 16 int32 words: zeros except [2..10] */
        int32_t *result_out)
{
    uint32_t i;

    /* 1. Load weights into SPM (PE0) */
    if (cgra_dma(weights_ddr, CGRA_SPM_PE_ADDR(0, 0), 64u)) return -1;

    /* 2. Load inputs into tile bank 0 (broadcast to all 4 PE rows; PE0 reads
     *    bank 0 since row 0 is wired to bank 0).                             */
    if (cgra_dma(inputs_ddr, CGRA_TILE_BCAST, 64u)) return -1;

    /* 3. Configure PE0: MAC with SRC_W × SRC_SPM, all 16 slots */
    for (i = 0; i < 16u; i++) {
        if (cgra_config_pe_slot(0u, i, staging_ddr,
                OP_MAC, SRC_W, SRC_SPM, 0u, 0u, 0u)) return -1;
    }

    /* 4. Soft-reset → zeroes the PE accumulator via pe_reset_n */
    cgra_wr(CGRA_CU_CTRL, 2u);
    cgra_wr(CGRA_CU_CTRL, 0u);

    /* 5. Run the MAC loop */
    cgra_wr(CGRA_LOOP_START,    0u);
    cgra_wr(CGRA_LOOP_END,      15u);
    cgra_wr(CGRA_LOOP_COUNT,    0u);
    cgra_wr(CGRA_CU_PC_END,     15u);
    cgra_wr(CGRA_TILE_AUTO_INC, 1u);
    cgra_wr(CGRA_SPM_AUTO_INC,  1u);
    cgra_cu_start();
    if (cgra_cu_wait(1000000u)) return -1;
    cgra_wr(CGRA_TILE_AUTO_INC, 0u);
    cgra_wr(CGRA_SPM_AUTO_INC,  0u);

    /* 6. Read result from RESULT_DATA (FIFO front from PE(3,3) east port).
     * Note: bare-metal callers requiring exact alu_result of PE0 must
     * follow up with a PASS0(SRC_RF) east-chain readout (see
     * tb_suite_cnn_kernel.svh CK14). */
    *result_out = (int32_t)cgra_rd(CGRA_RESULT_DATA);
    return 0;
}

/* =========================================================================
 * ReLU activation kernel (single value via PE0)
 * =========================================================================
 * Applies max(0, x) to one tile-driven value. Mirrors tb_suite_cnn_kernel.svh
 * CK21/CK26 sequence. Caller stages a 1-word tile broadcast.
 * ========================================================================= */
static inline int cnn_relu_apply(uint32_t staging_ddr,
                                 uint32_t input_ddr, int32_t *result_out)
{
    if (cgra_dma(input_ddr, CGRA_TILE_BCAST, 4u)) return -1;
    if (cgra_config_pe_slot(0u, 0u, staging_ddr,
            OP_RELU, SRC_W, SRC_W, 0u, 0u, 0u)) return -1;
    cgra_wr(CGRA_CU_PC_END, 5u);
    cgra_cu_start();
    if (cgra_cu_wait(1000000u)) return -1;
    *result_out = (int32_t)cgra_rd(CGRA_RESULT_DATA);
    return 0;
}

/* =========================================================================
 * 2×2 max-pool stage: 2-PE chain that reduces (in0, in1) → max
 * =========================================================================
 * For full 2×2 max-pool, callers chain two of these per row. Mirrors
 * tb_suite_cnn_kernel.svh CK27 setup (PE0 PASS0 east-broadcast, PE1 MAX).
 * Caller stages in0 in a tile broadcast and provides in1 as a 16-bit immediate.
 * ========================================================================= */
static inline int cnn_max_of_two(uint32_t staging_ddr,
                                 uint32_t in0_tile_ddr, int16_t in1_imm,
                                 int32_t *result_out)
{
    if (cgra_dma(in0_tile_ddr, CGRA_TILE_BCAST, 4u)) return -1;
    if (cgra_config_pe_slot(0u, 0u, staging_ddr,
            OP_PASS0, SRC_W, SRC_W, 0u, ROUTE_E, 0u)) return -1;
    if (cgra_config_pe_slot(1u, 0u, staging_ddr,
            OP_MAX, SRC_W, SRC_IMM, 0u, 0u, (uint16_t)in1_imm)) return -1;
    cgra_wr(CGRA_CU_PC_END, 8u);
    cgra_cu_start();
    if (cgra_cu_wait(1000000u)) return -1;
    /* PE1's alu_result is the maximum. For RESULT_ROW0 readout, follow up
     * with a PASS0(SRC_RF) east-chain pass. */
    *result_out = (int32_t)cgra_rd(CGRA_RESULT_DATA);
    return 0;
}

#endif /* CGRA_KERNELS_CNN_H */
