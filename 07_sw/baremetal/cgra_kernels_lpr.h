/* =========================================================================
 * cgra_kernels_lpr.h — CGRA kernel descriptors for LPR inference
 *
 * Defines cgra_pe_prog_t / cgra_kernel_t configurations for the three
 * operations in the golden CNN:
 *
 *   KERN_POOL_2x2   — 2×2 max-pool via OP_MAX east-chain (CGRA-ready)
 *   KERN_CONV_3x3   — 3×3 convolution template (needs int32-quantized weights)
 *   KERN_FC_TILE    — FC dot-product tile template (needs int32-quantized weights)
 *
 * Phase 3 demo uses ARM float inference (golden_infer from lpr_golden.c)
 * for correctness.  These descriptors document the intended CGRA mapping
 * and serve as the starting point for future integer-quantized acceleration.
 *
 * Hardware notes (from CLAUDE.md / bench_cgra verification):
 *   - PE pipeline is 3 stages (decode→_r→_r2): insert ≥2 NOP slots between
 *     a write and the dependent read in the same PE.
 *   - RF address: only RF[0] is readable (src0_sel/src1_sel=SRC_RF reads RF[0]).
 *     dst_sel selects the write address (0-15), but writeback to RF[1..15]
 *     is invisible to subsequent SRC_RF reads.
 *   - OP_MAX: result = (src0 > src1) ? src0 : src1  (int32 signed compare)
 *   - OP_MAC: acc += src0 * src1  (40-bit saturating accumulator)
 *   - Tile memory: 4 banks, each 4096 × 32 bits.  The DMA writes row data
 *     into the bank; the PE reads its bank value via the W (west) port.
 * ========================================================================= */

#ifndef CGRA_KERNELS_LPR_H
#define CGRA_KERNELS_LPR_H

#include "cgra.h"

/* ── Helper: build config word inline ────────────────────────────────── */
#define CFGW(op, s0, s1, dst, route, imm) \
    (  ((uint64_t)(op)    & 0x3F)          \
     | (((uint64_t)(s0)   & 0xF) << 6)    \
     | (((uint64_t)(s1)   & 0xF) << 10)   \
     | (((uint64_t)(dst)  & 0xF) << 14)   \
     | (((uint64_t)(route)& 0xF) << 18)   \
     | ((uint64_t)(imm)          << 24))

/* =========================================================================
 * KERN_POOL_2x2 — 2×2 max-pool, one output channel per PE row
 *
 * Data layout in tile banks before CU run (one output pixel per call):
 *   Bank 0: [top-left  pixel] × 16 (one per slot — only slot 0 is used)
 *   Bank 1: [top-right pixel] × 16
 *   Bank 2: [bot-left  pixel] × 16
 *   Bank 3: [bot-right pixel] × 16
 *
 * PE program (4 active slots per PE, NOP elsewhere):
 *   Slot 0: col0 PASS0 W→East  (latch top-left, send to col1)
 *   Slot 1: col1 MAX   W,E     (max(top-left, top-right) stored RF[0]→East)
 *           col2 PASS0 W→East  (latch bot-left, send to col3)
 *   Slot 2: NOP (pipeline bubble — 2 slots after slot 1 write before RF read)
 *   Slot 3: col3 MAX   W, E    (max(bot-left, bot-right) RF[0])
 *           [col1 result still routing East toward RESULT_ROW via col2/3 chain]
 *
 * Limitation: two-stage max needs 2 CU passes (or careful re-routing).
 * Simplified version: two 2-input max passes.
 *
 * For full max-pool acceleration: stage the 2×2 window into 4 banks,
 * run KERN_POOL_2x2_STAGE1 (col01 max), read result back, re-stage,
 * run KERN_POOL_2x2_STAGE2 (vertical max).
 * ========================================================================= */

/* Stage 1: max(bank0, bank1) per row → result in RESULT_ROWr */
static const cgra_pe_prog_t lpr_pool_s1_pes[8] = {
    /* Row 0 */
    { .pe_id = 0, .n_slots = 4, .words = {
        CFGW(OP_PASS0, SRC_W, 0,     0, ROUTE_E, 0),  /* col0: pass tile→East */
        CFGW(OP_NOP,   0,     0,     0, 0,        0),  /* pipeline gap */
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
    }},
    { .pe_id = 1, .n_slots = 4, .words = {
        CFGW(OP_NOP,   0,     0,     0, 0,        0),  /* wait for col0 result */
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_MAX,   SRC_W, SRC_W, 0, ROUTE_E,  0),  /* max(bank0,bank1)→E */
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
    }},
    { .pe_id = 2, .n_slots = 4, .words = {
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_PASS1, 0,     SRC_W, 0, ROUTE_E,  0),  /* forward to col3 */
    }},
    { .pe_id = 3, .n_slots = 4, .words = {
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_PASS1, 0,     SRC_W, 0, ROUTE_E,  0),  /* to RESULT_ROW0 */
    }},
    /* Row 1 — identical pattern, pe_ids 4-7 */
    { .pe_id = 4, .n_slots = 4, .words = {
        CFGW(OP_PASS0, SRC_W, 0,     0, ROUTE_E, 0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
    }},
    { .pe_id = 5, .n_slots = 4, .words = {
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_MAX,   SRC_W, SRC_W, 0, ROUTE_E,  0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
    }},
    { .pe_id = 6, .n_slots = 4, .words = {
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_PASS1, 0,     SRC_W, 0, ROUTE_E,  0),
    }},
    { .pe_id = 7, .n_slots = 4, .words = {
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_NOP,   0,     0,     0, 0,        0),
        CFGW(OP_PASS1, 0,     SRC_W, 0, ROUTE_E,  0),
    }},
};

static const cgra_kernel_t KERN_POOL_2x2_STAGE1 = {
    .pes     = lpr_pool_s1_pes,
    .n_pes   = 8,
    .last_pc = 3,
};

/* =========================================================================
 * KERN_CONV_3x3 — 3×3 convolution template
 *
 * Intended mapping (one output channel per PE row, one output pixel per call):
 *   - Pre-load 9-pixel neighbourhood into SPM[0..8] via STORE_SPM pass
 *   - 9-slot MAC program: acc += SPM[k] * int32_weight[k]  for k in 0..8
 *   - Read acc via RESULT_ROW
 *
 * Weights (16-bit immediates after ×256 scaling of float weights) must be
 * filled at runtime by cgra_program_kernel() before the first CU run.
 * The descriptor below is a NOP placeholder — replace .words with the
 * correct per-output-channel MAC sequence.
 *
 * Float→int16 mapping: w_int = round(w_float * CONV_SCALE)
 * Recommended CONV_SCALE = 256 (weights typically in [-1, +1] → [-256, 256])
 * Accumulator bias: add (int32)(bias_float * CONV_SCALE * CONV_SCALE)
 * ========================================================================= */
#define CONV_SCALE   256

/* Placeholder — 9 NOP slots (substitute with 9 MAC instructions at runtime) */
static const cgra_pe_prog_t lpr_conv_pes_placeholder[1] = {
    { .pe_id = 0, .n_slots = 9, .words = {
        CFGW(OP_NOP, 0, 0, 0, 0, 0),  /* slot 0: replace with MAC */
        CFGW(OP_NOP, 0, 0, 0, 0, 0),  /* slot 1: replace with MAC */
        CFGW(OP_NOP, 0, 0, 0, 0, 0),  /* slot 2: replace with MAC */
        CFGW(OP_NOP, 0, 0, 0, 0, 0),  /* slot 3: replace with MAC */
        CFGW(OP_NOP, 0, 0, 0, 0, 0),  /* slot 4: replace with MAC */
        CFGW(OP_NOP, 0, 0, 0, 0, 0),  /* slot 5: replace with MAC */
        CFGW(OP_NOP, 0, 0, 0, 0, 0),  /* slot 6: replace with MAC */
        CFGW(OP_NOP, 0, 0, 0, 0, 0),  /* slot 7: replace with MAC */
        CFGW(OP_NOP, 0, 0, 0, 0, 0),  /* slot 8: PASS0 East for RESULT */
    }},
};

static const cgra_kernel_t KERN_CONV_3x3_TEMPLATE = {
    .pes     = lpr_conv_pes_placeholder,
    .n_pes   = 1,
    .last_pc = 8,
};

/* =========================================================================
 * KERN_FC_TILE — FC dot-product tile
 *
 * Intended mapping (784→30 FC, tiled 16 inputs × 4 outputs per tile):
 *   - 16 MACs per CU pass (one per PE slot), 4 PE rows = 4 output neurons
 *   - Inner loop (LOOP_COUNT=48) steps through 16 × 49 = 784 inputs
 *   - After loop: 4 RESULT_ROWs hold partial sums for 4 output neurons
 *
 * The 16-bit IMM field holds the int32-quantized weight for that input index.
 * Each slot MAC: acc += tile_value * IMM16
 * Tile memory: input[0..15] pre-loaded per tile; auto-inc advances by 16.
 *
 * Output scale: logit_approx = acc / (INPUT_SCALE × WEIGHT_SCALE)
 * For argmax, the scale factors cancel and raw acc comparison is valid.
 * ========================================================================= */

/* FC tile placeholder — 16 NOP slots (replace each with MAC SRC_W, SRC_IMM) */
static const cgra_pe_prog_t lpr_fc_pes_placeholder[4] = {
    { .pe_id =  3, .n_slots = 16, .words = {
        CFGW(OP_NOP, 0, 0, 0, 0, 0),  /* replace: MAC SRC_W SRC_IMM for neuron 0 */
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0),
    }},
    { .pe_id =  7, .n_slots = 16, .words = {
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
    }},
    { .pe_id = 11, .n_slots = 16, .words = {
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
    }},
    { .pe_id = 15, .n_slots = 16, .words = {
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
        CFGW(OP_NOP, 0, 0, 0, 0, 0), CFGW(OP_NOP, 0, 0, 0, 0, 0),
    }},
};

static const cgra_kernel_t KERN_FC_TILE_TEMPLATE = {
    .pes     = lpr_fc_pes_placeholder,
    .n_pes   = 4,
    .last_pc = 15,
};

/* =========================================================================
 * FC layer CGRA kernels (M2: 784→30 INT16 weight-stationary dot product)
 *
 * Mapping: 4 PE rows in col=0 accumulate one group of 4 output neurons.
 * 8 groups × 49 chunks of 16 inputs = 784 MACs per neuron.
 * Readout: col0 PASS0(SRC_RF)→col1→col2→col3 east chain, read RESULT_ROW.
 *
 * FC layer constants:
 * ========================================================================= */
#define LPR_FC_N_INPUTS   784
#define LPR_FC_N_CLASSES   30
#define LPR_FC_N_GROUPS     8   /* ceil(30/4) */
#define LPR_FC_N_CHUNKS    49   /* ceil(784/16) */

/* PE IDs for col=0 of each row (the MAC accumulator PEs) */
static const uint8_t lpr_fc_col0_ids[4] = {0, 4, 8, 12};

/* ── lpr_fc_init_chain ────────────────────────────────────────────────
 * Program col=1,2,3 of all 4 rows with PASS0(SRC_W, ROUTE_E) for all
 * slots.  This east-chain forwards col0's output to RESULT_ROW at readout.
 * Call once before any group processing. */
static inline int lpr_fc_init_chain(uint32_t staging_ddr)
{
    for (int r = 0; r < 4; r++) {
        for (int c = 1; c < 4; c++) {
            uint32_t pe = (uint32_t)r * 4u + (uint32_t)c;
            if (cgra_config_pe(pe, staging_ddr,
                               OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0)) return -1;
        }
    }
    return 0;
}

/* ── lpr_fc_acc_clr ──────────────────────────────────────────────────
 * Clear the 40-bit accumulator in col=0 of all 4 rows, then run the CU.
 * PC_END=2 (3 slots): the 3-stage PE pipeline needs exactly 3 cycles with
 * global_stall_r=0 before the accumulator write lands.  PC_END=0 fires
 * array_done on cycle 0, global_stall_r goes high on cycle 1, freezing
 * stages 2+3 — the accumulator is never cleared.  With PC_END=2,
 * array_done fires on cycle 2, global_stall_r goes high on cycle 3, so
 * stages 1/2/3 all execute while global_stall_r=0.
 * Call once per 4-neuron group. */
static inline int lpr_fc_acc_clr(uint32_t staging_ddr)
{
    for (int r = 0; r < 4; r++) {
        if (cgra_config_pe(lpr_fc_col0_ids[r], staging_ddr,
                           OP_ACC_CLR, 0, 0, 0, 0, 0)) return -1;
    }
    cgra_wr(CGRA_CU_PC_END, 2u);  /* 3 cycles to drain the 3-stage pipeline */
    cgra_cu_start();
    return cgra_cu_wait(1000000u);
}

/* ── lpr_fc_program_chunk ────────────────────────────────────────────
 * Build and load a 16-MAC kernel for col=0 of 4 rows.
 * fc_w_q: INT16 weight array [LPR_FC_N_INPUTS][LPR_FC_N_CLASSES] row-major.
 * chunk:  0..LPR_FC_N_CHUNKS-1  (selects which 16 inputs to bind to IMM).
 * group:  0..LPR_FC_N_GROUPS-1  (selects 4-neuron block; rows 0-3 → neurons).
 * Does NOT start the CU — caller must DMA tile banks then cu_start/wait. */
static inline int lpr_fc_program_chunk(const int16_t *fc_w_q,
                                        int chunk, int group,
                                        uint32_t staging_ddr)
{
    int base_input  = chunk * 16;
    int base_neuron = group * 4;

    for (int r = 0; r < 4; r++) {
        int neuron = base_neuron + r;
        uint64_t words[16];
        for (int j = 0; j < 16; j++) {
            int input_idx = base_input + j;
            /* Clamp out-of-range accesses (last chunk may reference past end) */
            uint16_t w = 0u;
            if (neuron < LPR_FC_N_CLASSES && input_idx < LPR_FC_N_INPUTS)
                w = (uint16_t)fc_w_q[input_idx * LPR_FC_N_CLASSES + neuron];
            words[j] = CFGW(OP_MAC, SRC_W, SRC_IMM, 0, 0, w);
        }
        if (cgra_config_pe_bulk(lpr_fc_col0_ids[r], words, staging_ddr)) return -1;
    }
    cgra_wr(CGRA_CU_PC_END, 15u);
    return 0;
}

/* ── lpr_fc_readout ──────────────────────────────────────────────────
 * Route the final accumulated dot product from RF[0] (col=0) east through
 * col=1→2→3 and capture in RESULT_ROW.  Runs a single 16-slot CU pass.
 * result[4] receives the signed 32-bit accumulator for each row. */
static inline int lpr_fc_readout(uint32_t staging_ddr, int32_t result[4])
{
    for (int r = 0; r < 4; r++) {
        if (cgra_config_pe(lpr_fc_col0_ids[r], staging_ddr,
                           OP_PASS0, SRC_RF, 0, 0, ROUTE_E, 0)) return -1;
    }
    cgra_wr(CGRA_CU_PC_END, 15u);
    cgra_cu_start();
    if (cgra_cu_wait(1000000u)) return -1;

    result[0] = (int32_t)cgra_rd(CGRA_RESULT_ROW0);
    result[1] = (int32_t)cgra_rd(CGRA_RESULT_ROW1);
    result[2] = (int32_t)cgra_rd(CGRA_RESULT_ROW2);
    result[3] = (int32_t)cgra_rd(CGRA_RESULT_ROW3);
    return 0;
}

/* =========================================================================
 * FC v2 — SPM-based MAC kernel (R1/R2/R3 features required)
 *
 * Weight layout:  fc_w_spm[N_CLASSES][N_INPUTS] as int32  (92,160 bytes)
 *   neuron n occupies byte range [n*784*4 .. (n+1)*784*4).
 *   Generated by: quantize_int16.py --out_spm golden_weights_spm.bin
 *
 * Performance design:
 *   - SPM preload: direct DDR→SPM DMA (no CPU staging copy)
 *   - Config writes: SG-DMA chains (ARM submits head pointer, waits once)
 *   - ACC_CLR writes slot 0 of col=0 PEs only (per-PE broadcaster fills
 *     all 16 slots); col=1,2,3 untouched (PASS0 from one-time init_chain)
 *   - MAC restore writes slot 0 of col=0 PEs only (same broadcaster path)
 *   - No per-group lpr_build_fc_kernel_v2 / lpr_fc_init_chain calls
 *
 * Pre-built SG-DMA chains (built once by lpr_fc_build_chains_v2):
 *   chains_ddr+0x00: 8B opword storage (acc_clr HI/LO at +0, mac HI/LO at +8,
 *                     pass0_rf HI/LO at +16, pass0_we HI/LO at +24)
 *   chains_ddr+0x20: acc_clr chain (8 descs × 16B: HI/LO × 4 col=0 PEs)
 *   chains_ddr+0xA0: mac_restore chain (8 descs)
 *   chains_ddr+0x120: readout chain (8 descs)
 *   chains_ddr+0x1A0: init_chain (24 descs: HI/LO × 12 col=1,2,3 PEs)
 *   chains_ddr+0x320: spm_preload chains (LPR_FC_N_GROUPS groups × 4 descs)
 * Total: ≤ 0x520 = 1312 bytes.
 * ========================================================================= */

#define LPR_FC_SPM_BYTES_PER_NEURON  (LPR_FC_N_INPUTS * 4u)

/* DDR area for pre-built SG-DMA descriptors (1312 B, 16-byte aligned). */
#define LPR_FC_V2_CHAINS_DDR  0x00113000UL

/* ── Internal helper: build an 8-descriptor chain that double-pumps one
 * 64-bit config word to slot 0 of each col=0 PE (4 PEs × HI+LO = 8 descs).
 * desc[] must point to an 8-element cgra_sg_dma_descriptor_t array in DDR.
 * hi_src/lo_src: DDR addresses of the 4-byte HI and LO words to send.    */
static inline void lpr_fc_build_col0_chain(
        volatile cgra_sg_dma_descriptor_t *desc,
        uint32_t hi_src, uint32_t lo_src)
{
    int r;
    for (r = 0; r < 4; r++) {
        uint32_t cfg_base = CGRA_PFX_CONFIG
                          | (((uint32_t)lpr_fc_col0_ids[r] & 0xFu) << 7);
        desc[r*2  ].src      = hi_src;
        desc[r*2  ].dst      = cfg_base;
        desc[r*2  ].size     = 4u;
        desc[r*2  ].next_ptr = (uint32_t)(uintptr_t)(&desc[r*2+1]);
        desc[r*2+1].src      = lo_src;
        desc[r*2+1].dst      = cfg_base | 4u;   /* bit[2]=1 → commit + broadcaster */
        desc[r*2+1].size     = 4u;
        desc[r*2+1].next_ptr = (r < 3) ? (uint32_t)(uintptr_t)(&desc[r*2+2]) : 0u;
    }
    asm volatile("dsb" ::: "memory");
}

/* ── lpr_fc_build_chains_v2 ──────────────────────────────────────────
 * One-time setup call.  Writes all SG-DMA descriptor tables to DDR and
 * pre-builds the col=1,2,3 init_chain and per-group SPM preload chains.
 * Also sets up col=1,2,3 with PASS0 (init_chain, blocking).
 * fc_w_spm_ddr: DDR address of golden_weights_spm.bin (LPR_CGRA_SPM_STAGE
 *               is not used — DMA reads directly from this address).     */
static inline int lpr_fc_build_chains_v2(uint32_t fc_w_spm_ddr,
                                          uint32_t staging_ddr)
{
    volatile uint32_t *op = (volatile uint32_t *)LPR_FC_V2_CHAINS_DDR;
    /* Opword area: [0,1]=acc_clr HI/LO, [2,3]=mac HI/LO,
     *              [4,5]=pass0_rf HI/LO, [6,7]=pass0_we HI/LO */
    uint64_t acc_clr_w = CFGW(OP_ACC_CLR, 0, 0, 0, 0, 0);
    uint64_t mac_w     = CFGW(OP_MAC,     SRC_W, SRC_SPM, 0, 0, 0);
    uint64_t p0_rf_w   = CFGW(OP_PASS0,   SRC_RF, 0, 0, ROUTE_E, 0);
    uint64_t p0_we_w   = CFGW(OP_PASS0,   SRC_W,  0, 0, ROUTE_E, 0);
    op[0] = (uint32_t)(acc_clr_w >> 32);  op[1] = (uint32_t)(acc_clr_w & 0xFFFFFFFFuL);
    op[2] = (uint32_t)(mac_w     >> 32);  op[3] = (uint32_t)(mac_w     & 0xFFFFFFFFuL);
    op[4] = (uint32_t)(p0_rf_w   >> 32);  op[5] = (uint32_t)(p0_rf_w   & 0xFFFFFFFFuL);
    op[6] = (uint32_t)(p0_we_w   >> 32);  op[7] = (uint32_t)(p0_we_w   & 0xFFFFFFFFuL);

    uint32_t base = LPR_FC_V2_CHAINS_DDR;
    uint32_t hi_acc = base + 0u,  lo_acc = base + 4u;
    uint32_t hi_mac = base + 8u,  lo_mac = base + 12u;
    uint32_t hi_p0r = base + 16u, lo_p0r = base + 20u;
    uint32_t hi_p0w = base + 24u, lo_p0w = base + 28u;

    /* acc_clr chain: +0x20 */
    volatile cgra_sg_dma_descriptor_t *d_acc =
        (volatile cgra_sg_dma_descriptor_t *)(base + 0x20u);
    lpr_fc_build_col0_chain(d_acc, hi_acc, lo_acc);

    /* mac_restore chain: +0xA0 */
    volatile cgra_sg_dma_descriptor_t *d_mac =
        (volatile cgra_sg_dma_descriptor_t *)(base + 0xA0u);
    lpr_fc_build_col0_chain(d_mac, hi_mac, lo_mac);

    /* readout chain: +0x120 */
    volatile cgra_sg_dma_descriptor_t *d_ro =
        (volatile cgra_sg_dma_descriptor_t *)(base + 0x120u);
    lpr_fc_build_col0_chain(d_ro, hi_p0r, lo_p0r);

    /* init_chain: +0x1A0 (24 descs: col=1,2,3, all 4 rows) */
    volatile cgra_sg_dma_descriptor_t *d_ic =
        (volatile cgra_sg_dma_descriptor_t *)(base + 0x1A0u);
    {
        int i = 0, r, c;
        for (r = 0; r < 4; r++) {
            for (c = 1; c < 4; c++) {
                uint32_t pe = (uint32_t)r * 4u + (uint32_t)c;
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

    /* SPM preload chains: +0x320, one chain per group (4 descs each) */
    volatile cgra_sg_dma_descriptor_t *d_spm =
        (volatile cgra_sg_dma_descriptor_t *)(base + 0x320u);
    {
        int g, r;
        for (g = 0; g < LPR_FC_N_GROUPS; g++) {
            volatile cgra_sg_dma_descriptor_t *dc = &d_spm[g * 4];
            int n_pe = 0;
            for (r = 0; r < 4; r++) {
                int neuron = g * 4 + r;
                if (neuron >= LPR_FC_N_CLASSES) break;
                n_pe++;
                uint32_t src = fc_w_spm_ddr + (uint32_t)neuron * LPR_FC_SPM_BYTES_PER_NEURON;
                uint32_t dst = CGRA_PFX_SPM | (((uint32_t)lpr_fc_col0_ids[r] & 0xFu) << 12);
                int last = (r == 3 || neuron == LPR_FC_N_CLASSES - 1);
                dc[r].src      = src;
                dc[r].dst      = dst;
                dc[r].size     = LPR_FC_SPM_BYTES_PER_NEURON;
                dc[r].next_ptr = last ? 0u : (uint32_t)(uintptr_t)(&dc[r+1]);
            }
            (void)n_pe;
        }
        asm volatile("dsb" ::: "memory");
    }

    /* Initial east chain setup (blocking, once per char) */
    cgra_sg_dma_start(base + 0x1A0u);
    if (cgra_sg_dma_wait(5000000u)) return -1;

    /* Broadcast MAC to all 16 PEs using multi-PE bcast flag (col=0 config for
     * MAC; col=1,2,3 already PASS0 from init_chain above, so we unicast MAC
     * only to col=0 PEs to avoid overwriting col=1,2,3).                     */
    cgra_sg_dma_start(base + 0xA0u);
    return cgra_sg_dma_wait(5000000u);
}

/* ── lpr_fc_run_group_v2 ──────────────────────────────────────────────
 * Run one 4-neuron group using SPM-backed MAC (SG-DMA chains, no CPU copy).
 * lpr_fc_build_chains_v2 must be called once before the first group.
 * Fills result[r] with int32 dot product for neuron g*4+r.           */
/* ── Debug counters (group-0 per-step timing, written when LPR_CGRA_V2_DBG) */
#ifdef LPR_CGRA_V2_DBG
extern volatile uint32_t g_v2_dbg_spm_cyc;   /* SPM preload DMA wait cycles */
extern volatile uint32_t g_v2_dbg_mac_cyc;   /* MAC loop CU wait cycles     */
extern volatile uint32_t g_v2_dbg_timeout;   /* bitmask: bit0=spm, bit1=mac */
#endif

static inline int lpr_fc_run_group_v2(int g,
                                       const int32_t *fc_w_spm,
                                       uint32_t staging_ddr,
                                       int32_t result[4])
{
    uint32_t base = LPR_FC_V2_CHAINS_DDR;
    (void)fc_w_spm;   /* weights DMA'd directly from fc_w_spm_ddr in chains */
    (void)staging_ddr;

    /* Step 1: preload SPM via pre-built chain (direct DDR→SPM, no CPU copy) */
#ifdef LPR_CGRA_V2_DBG
    uint32_t _dbg_t0 = (g == 0) ? arm_ccnt_read() : 0u;
#endif
    cgra_sg_dma_start(base + 0x320u + (uint32_t)g * 4u * 16u);
    int _r_spm = cgra_sg_dma_wait(5000000u);
#ifdef LPR_CGRA_V2_DBG
    if (g == 0) { g_v2_dbg_spm_cyc = arm_ccnt_read() - _dbg_t0;
                  if (_r_spm) g_v2_dbg_timeout |= 1u; }
#endif
    if (_r_spm) return -1;

    /* Step 2: clear accumulators — chain writes ACC_CLR to col=0 PEs slot 0.
     * Per-PE broadcaster fills all 16 slots.  col=1,2,3 untouched (PASS0). */
    cgra_sg_dma_start(base + 0x20u);
    if (cgra_sg_dma_wait(5000000u)) return -1;
    cgra_wr(CGRA_CU_PC_END, 2u);
    cgra_cu_start();
    if (cgra_cu_wait(1000000u)) return -1;

    /* Step 3: restore MAC to col=0 PEs — chain writes MAC to slot 0.
     * Per-PE broadcaster fills all 16 slots.  col=1,2,3 still PASS0. */
    cgra_sg_dma_start(base + 0xA0u);
    if (cgra_sg_dma_wait(5000000u)) return -1;

    /* Step 4: MAC loop — 784 MACs via 49 passes × 16 slots */
    cgra_wr(CGRA_LOOP_START,    0u);
    cgra_wr(CGRA_LOOP_END,      15u);
    cgra_wr(CGRA_LOOP_COUNT,    48u);
    cgra_wr(CGRA_CU_PC_END,     15u);
    cgra_wr(CGRA_TILE_AUTO_INC, 1u);
    cgra_wr(CGRA_SPM_AUTO_INC,  1u);
#ifdef LPR_CGRA_V2_DBG
    uint32_t _dbg_t4 = (g == 0) ? arm_ccnt_read() : 0u;
#endif
    cgra_cu_start();
    int _r_mac = cgra_cu_wait(5000000u);
#ifdef LPR_CGRA_V2_DBG
    if (g == 0) { g_v2_dbg_mac_cyc = arm_ccnt_read() - _dbg_t4;
                  if (_r_mac) g_v2_dbg_timeout |= 2u; }
#endif
    if (_r_mac) return -1;
    cgra_wr(CGRA_TILE_AUTO_INC, 0u);
    cgra_wr(CGRA_SPM_AUTO_INC,  0u);

    /* Step 5: readout — chain writes PASS0(SRC_RF, ROUTE_E) to col=0.
     * col=1,2,3 already PASS0 → full east chain for RESULT_ROW capture. */
    cgra_sg_dma_start(base + 0x120u);
    if (cgra_sg_dma_wait(5000000u)) return -1;
    cgra_wr(CGRA_CU_PC_END, 15u);
    cgra_cu_start();
    if (cgra_cu_wait(1000000u)) return -1;

    result[0] = (int32_t)cgra_rd(CGRA_RESULT_ROW0);
    result[1] = (int32_t)cgra_rd(CGRA_RESULT_ROW1);
    result[2] = (int32_t)cgra_rd(CGRA_RESULT_ROW2);
    result[3] = (int32_t)cgra_rd(CGRA_RESULT_ROW3);
    return 0;
}

/* ── lpr_fc_tile_preload_v2 ───────────────────────────────────────────
 * DMA 784 int32 activations from DDR to all 4 tile banks simultaneously.
 * pool2_q_ddr: DDR address of quantised pool2 output (no CPU staging copy). */
static inline int lpr_fc_tile_preload_v2(uint32_t pool2_q_ddr)
{
    return cgra_dma(pool2_q_ddr, CGRA_TILE_BCAST, LPR_FC_N_INPUTS * 4u);
}

#endif /* CGRA_KERNELS_LPR_H */
