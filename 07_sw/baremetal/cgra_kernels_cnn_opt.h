/* =========================================================================
 * cgra_kernels_cnn_opt.h — Tier-1 optimised CGRA FC kernels for MNIST.
 *
 * Same 4-PE silicon-validated path as cgra_kernels_cnn.h (col=0 MAC,
 * col=1..3 PASS0 east-chain readout) — accuracy is bit-identical because
 * the math hasn't changed. The wins come from removing redundant work:
 *
 *   1. ACC_CLR pass eliminated. cgra_cu_reset() (CU_CTRL=2 then 0)
 *      zeroes all 16 PE accumulators in ~150 cycles and leaves the PE
 *      config RAM untouched. Saves the ACC_CLR SG-DMA chain (8 descs)
 *      AND a one-slot CU pass per group.
 *
 *   2. CU control registers hoisted out of the per-group loop. The
 *      MAC loop's LOOP_START/END/COUNT/CU_PC_END/SPM_AUTO_INC/
 *      TILE_AUTO_INC are identical for all groups of a layer — set
 *      them once before iterating.
 *
 *   3. Readout CU pass shortened from 16 slots to ~6 (4 east-chain
 *      hops × 3-stage PE pipeline ≈ 5-6 cycles to drain).
 *
 * Per-group flow (Tier 1):
 *   Step 1: SPM preload SG-DMA (unchanged)
 *   Step 2: cgra_cu_reset()           ← replaces ACC_CLR DMA+CU pass
 *   Step 3: MAC restore SG-DMA        ← undoes prev group's readout overwrite
 *   Step 4: MAC loop CU run           (~408 cyc compute)
 *   Step 5: readout SG-DMA + CU run   (CU_PC_END=5, was 15)
 *
 * Estimated savings per group (CGRA cycles):
 *   ACC_CLR SG-DMA    ~800 cyc   -> eliminated
 *   ACC_CLR CU run    ~10  cyc   -> eliminated
 *   Soft reset        ~150 cyc   <- added
 *   Readout CU run    ~25 -> ~10 cyc
 *   Net               ~675 cyc/group saved
 *
 * Per-FC1 (16 groups):  ~10.8K CGRA cycles saved
 * Per-FC2  (3 groups):   ~2.0K CGRA cycles saved
 * Per inference        ~12.8K CGRA cycles = ~170K ARM cycles
 *                      Expected ARM measurement: ~10% drop on the
 *                      CGRA-FC path (1.70 M -> ~1.53 M @ 666 MHz).
 *
 * Activation function:
 *   The SG-DMA descriptor tables built by cnn_fc_opt_build_chains() are
 *   identical layout to cgra_kernels_cnn.h's tables (same offsets and
 *   sizes), so the existing CNN_FCx_CHAINS_DDR addresses are reused.
 *   Calling cnn_fcx_build_chains() (v1) once then cnn_fcx_opt_run_group()
 *   (this header) per group is fully supported.
 * ========================================================================= */

#ifndef CGRA_KERNELS_CNN_OPT_H
#define CGRA_KERNELS_CNN_OPT_H

#include "cgra.h"
#include "cgra_kernels_cnn.h"   /* re-use build_chains + constants */

/* =========================================================================
 * One-time per-layer CU register setup.
 * Call AFTER build_chains and BEFORE the first run_group of a layer.
 *
 * The same register set persists across all groups of one layer because
 * every group runs the same 16-slot LOOP_COUNT MAC kernel.
 * ========================================================================= */
static inline void cnn_fc_opt_layer_setup(uint32_t loop_count)
{
    cgra_wr(CGRA_LOOP_START,    0u);
    cgra_wr(CGRA_LOOP_END,      15u);
    cgra_wr(CGRA_LOOP_COUNT,    loop_count);
    cgra_wr(CGRA_TILE_AUTO_INC, 1u);
    cgra_wr(CGRA_SPM_AUTO_INC,  1u);
}

/* =========================================================================
 * Optimised per-group execution.
 * ========================================================================= */
static inline int cnn_fc_opt_run_group(
        uint32_t chains_ddr,
        int g,
        uint32_t n_outputs,
        int32_t result[4])
{
    uint32_t base = chains_ddr;

    /* Step 1: SPM weight preload for this group (4× ~1600 B DMAs).
     * Unchanged from v1 — same chain offset, same layout. */
    cgra_sg_dma_start(base + 0x320u + (uint32_t)g * 4u * 16u);
    if (cgra_sg_dma_wait(5000000u)) return -1;

    /* Step 2: Soft-reset CU — zeroes ALL 16 PE accumulators in ~150
     * cycles without touching config RAM. Replaces the v1 ACC_CLR
     * SG-DMA chain + 3-slot CU run (~810 cyc total). */
    cgra_cu_reset();

    /* Step 3: MAC restore — undo the readout-chain overwrite of col=0
     * slot 0 from the PREVIOUS group's readout. (At boot, build_chains
     * leaves slot 0 = MAC already, so this is a no-op for the very
     * first group of the very first inference — but harmless.) */
    cgra_sg_dma_start(base + 0xA0u);
    if (cgra_sg_dma_wait(5000000u)) return -1;

    /* Step 4: MAC loop. CU registers were set by cnn_fc_opt_layer_setup. */
    cgra_wr(CGRA_CU_PC_END, 15u);
    cgra_cu_start();
    if (cgra_cu_wait(5000000u)) return -1;

    /* Step 5: Readout — swap col=0 slot 0 to PASS0(SRC_RF) and run the
     * east chain. PC_END=5 is enough to drain RF[0] through 4 east hops
     * with the 3-stage pipeline (col=0 decode @0, _r @1, _r2 @2 →
     * col=1 captures @3, col=2 @4, col=3 @5). v1 used 15 — wasted ~10
     * idle cycles. */
    cgra_sg_dma_start(base + 0x120u);
    if (cgra_sg_dma_wait(5000000u)) return -1;
    cgra_wr(CGRA_CU_PC_END, 5u);
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
 * Public Tier-1 API — FC1 (400→64)
 * ========================================================================= */
static inline int cnn_fc1_opt_run_group(int g, int32_t result[4])
{
    return cnn_fc_opt_run_group(CNN_FC1_CHAINS_DDR, g,
                                CNN_FC1_N_OUTPUTS, result);
}

/* =========================================================================
 * Public Tier-1 API — FC2 (64→10)
 * ========================================================================= */
static inline int cnn_fc2_opt_run_group(int g, int32_t result[4])
{
    return cnn_fc_opt_run_group(CNN_FC2_CHAINS_DDR, g,
                                CNN_FC2_N_OUTPUTS, result);
}

#endif /* CGRA_KERNELS_CNN_OPT_H */
