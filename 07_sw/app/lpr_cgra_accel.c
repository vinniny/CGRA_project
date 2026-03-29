/* ===================================================================
 *  lpr_cgra_accel.c – CGRA-Accelerated LPR Character Classifier
 *
 *  Offloads the FC layer (784→30, heaviest per-character layer) to the
 *  CGRA 4×4 PE array.  Conv/Pool layers run on ARM using the golden
 *  model's verified int32 implementations.
 *
 *  Quantization scheme
 *  -------------------
 *    Activations : float → INT16  (Q8.8 fixed-point, scale = 256)
 *    Weights     : float → INT8   ([-128, +127])
 *    CGRA MAC    : 32-bit operands, 40-bit saturating accumulator
 *    Dequantize  : result >> 8 to compensate for Q8.8 scaling
 *
 *  Execution flow (per character image)
 *  ------------------------------------
 *    ARM : Conv1 → Pool1 → Conv2 → Pool2     (golden model, int32)
 *    ARM : Quantize FC input vector to INT16
 *    CGRA: FC matmul in groups of 4 outputs
 *          ┌─────────────────────────────────────────────────┐
 *          │  For each group of 4 output classes:            │
 *          │    1. ACC_CLR: DMA clr-config, run ctx 0 once  │
 *          │    2. For each 13-element input chunk:          │
 *          │       a. Build config (correct per-chunk IMMs)  │
 *          │       b. DMA config to PE config RAM            │
 *          │       c. DMA input chunk to tile memory banks   │
 *          │       d. Start CU → 16 context cycles           │
 *          │    3. Read 4 results from east-edge registers   │
 *          └─────────────────────────────────────────────────┘
 *    ARM : Add bias, dequantize, argmax → predicted character
 *    ARM : Top-K sorting kept on CPU (per design spec)
 *
 *  PE config per run (16 contexts)
 *  ───────────────────────────────
 *    PE[r][0] col 0 : ctx 0..12 = MAC(WEST, IMM=weight), ctx 13-15 = NOP
 *    PE[r][1] col 1 : ctx 0..12 = NOP,   ctx 13-15 = PASS0(WEST)
 *    PE[r][2] col 2 : ctx 0..12 = NOP,   ctx 13-15 = PASS0(WEST)
 *    PE[r][3] col 3 : ctx 0..12 = NOP,   ctx 13-15 = PASS0(WEST)
 *
 *  The 3 drain contexts pipeline the accumulated result from col 0's
 *  registered data_out through cols 1-3, so the east-edge result
 *  registers capture col 0's accumulator when cu_done fires.
 * =================================================================== */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

#include "../driver/cgra_driver.h"
#include "../lib/cgra_tiler.h"
#include "../lib/lpr_golden.h"

/* ── CGRA Architecture Constants ─────────────────────────────────── */

#define CGRA_ROWS           4
#define CGRA_COLS           4
#define CGRA_NUM_PES        (CGRA_ROWS * CGRA_COLS)
#define CONTEXT_DEPTH       16
#define DRAIN_CYCLES        3       /* col0→col3 pipeline latency    */
#define MAC_PER_RUN         (CONTEXT_DEPTH - DRAIN_CYCLES)  /* = 13  */

/* DMA address space prefixes — use driver defines:
 *   DMA_PREFIX_AXI    (0x0) → external DDR
 *   DMA_PREFIX_TILE   (0x1) → tile memory
 *   DMA_PREFIX_CONFIG (0x2) → PE config RAM
 *   TILE_BANK(b)      → tile bank b base address
 */
#define TILE_BASE           DMA_PREFIX_TILE
#define CONFIG_BASE         DMA_PREFIX_CONFIG


/* ── PE ISA Opcodes (matches cgra_pe.sv / tb_defs.svh) ──────────── */

#define OP_NOP              0
#define OP_MAC              4
#define OP_ACC_CLR          15      /* clear PE accumulator (tb_defs: 6'd15)  */
#define OP_PASS0            16

/* Operand source select */
#define SRC_WEST            4
#define SRC_IMM             6

/* Route mask bits (config [21:18]) */
#define ROUTE_EAST          0x4u

/* ── PE 64-bit Config Word Builder ───────────────────────────────── */
/*
 * Layout (cgra_pe.sv):
 *   [5:0]   opcode
 *   [9:6]   src0_sel
 *   [13:10] src1_sel
 *   [17:14] dst_sel
 *   [21:18] route_mask
 *   [23:22] pred_en, pred_inv
 *   [39:24] immediate (16-bit, sign-extended to 32-bit inside PE)
 *   [63:40] extended (dest coords, multicast — unused here)
 */
static inline uint64_t pe_config(uint8_t op, uint8_t src0, uint8_t src1,
                                 uint8_t dst, uint8_t route, int16_t imm)
{
    uint64_t w = 0;
    w |= (uint64_t)(op    & 0x3F);
    w |= (uint64_t)(src0  & 0x0F) << 6;
    w |= (uint64_t)(src1  & 0x0F) << 10;
    w |= (uint64_t)(dst   & 0x0F) << 14;
    w |= (uint64_t)(route & 0x0F) << 18;
    w |= (uint64_t)((uint16_t)imm) << 24;
    return w;
}

/* ── Quantization ────────────────────────────────────────────────── */

#define QUANT_SCALE         256     /* 2^8 for Q8.8 activation scaling */
#define QUANT_SHIFT         8       /* Right-shift after MAC to dequant */
#define NUM_TEST_CHARS      10      /* Synthetic test images to process */

/* Float activation → INT16 (Q8.8), returned widened to int32 */
static inline int32_t quantize_act(float x)
{
    int32_t q = (int32_t)roundf(x * QUANT_SCALE);
    if (q >  32767) q =  32767;
    if (q < -32768) q = -32768;
    return q;
}

/* Float weight → INT8, returned widened to int32 */
static inline int32_t quantize_wt(float x)
{
    int32_t q = (int32_t)roundf(x);
    if (q >  127) q =  127;
    if (q < -128) q = -128;
    return q;
}

/* Bulk quantization helpers */
static void quantize_activations(const int32_t *golden_i32, int32_t *out, int n)
{
    for (int i = 0; i < n; i++)
        out[i] = quantize_act((float)golden_i32[i]);
}

static void quantize_weight_matrix(const int32_t *golden_i32, int32_t *out, int n)
{
    for (int i = 0; i < n; i++)
        out[i] = quantize_wt((float)golden_i32[i]);
}

/* ── Timing helper ───────────────────────────────────────────────── */

static inline double time_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

/* ── Config Bitstream Builder ────────────────────────────────────── */
/*
 * Build the double-pumped config DMA buffer for one CGRA FC run.
 *
 * Each 64-bit config word is split into two 32-bit DMA beats:
 *   Beat 0 (addr bit[2]=1): high word  → latched in config_high_reg
 *   Beat 1 (addr bit[2]=0): low word   → commits full 64-bit
 *
 * The DMA engine writes to increasing addresses starting at CONFIG_BASE.
 * Address layout: PE=[11:8], slot=[6:3], hi/lo=[2].
 *
 * Because consecutive addresses alternate lo/hi within a slot, we
 * organise the buffer so the DMA stream matches the double-pump
 * protocol: for each PE, for each slot, write [hi, lo].  The DMA
 * target base is set to CONFIG_BASE+4 (start on a high-word address)
 * so the first beat latches the high word, the second commits.
 *
 * Buffer layout (uint32_t words):
 *   [PE0 slot0 hi] [PE0 slot0 lo] [PE0 slot1 hi] [PE0 slot1 lo] ...
 *   ... [PE15 slot15 hi] [PE15 slot15 lo]
 *
 * Total: 16 PEs × 16 slots × 2 = 512 uint32_t words = 2048 bytes.
 */

#define CFG_BUF_WORDS   (CGRA_NUM_PES * CONTEXT_DEPTH * 2)
#define CFG_BUF_BYTES   (CFG_BUF_WORDS * sizeof(uint32_t))

static void build_fc_config(uint32_t *buf,
                            const int32_t wt[4][MAC_PER_RUN],
                            int mac_count)
{
    memset(buf, 0, CFG_BUF_BYTES);

    for (int pe = 0; pe < CGRA_NUM_PES; pe++) {
        int row = pe / CGRA_COLS;
        int col = pe % CGRA_COLS;

        for (int ctx = 0; ctx < CONTEXT_DEPTH; ctx++) {
            uint64_t cw;

            if (col == 0) {
                /* Column 0: MAC engine during compute, NOP during drain */
                if (ctx < mac_count)
                    cw = pe_config(OP_MAC, SRC_WEST, SRC_IMM, 0,
                                   ROUTE_EAST, (int16_t)wt[row][ctx]);
                else
                    cw = pe_config(OP_NOP, 0, 0, 0, ROUTE_EAST, 0);
            } else {
                /* Columns 1-3: NOP during compute, PASS0 during drain */
                if (ctx >= mac_count)
                    cw = pe_config(OP_PASS0, SRC_WEST, 0, 0, ROUTE_EAST, 0);
                else
                    cw = pe_config(OP_NOP, 0, 0, 0, ROUTE_EAST, 0);
            }

            int idx = (pe * CONTEXT_DEPTH + ctx) * 2;
            buf[idx + 0] = (uint32_t)(cw >> 32);         /* high word */
            buf[idx + 1] = (uint32_t)(cw & 0xFFFFFFFFu); /* low word  */
        }
    }
}

/*
 * build_acc_clr_config - Config where ctx 0 is ACC_CLR on every PE and
 * all other contexts are NOP.  Used to clear PE accumulators between
 * output groups without a full CU soft-reset.
 */
static void build_acc_clr_config(uint32_t *buf)
{
    memset(buf, 0, CFG_BUF_BYTES);
    for (int pe = 0; pe < CGRA_NUM_PES; pe++) {
        uint64_t cw  = pe_config(OP_ACC_CLR, 0, 0, 0, 0, 0);
        int      idx = (pe * CONTEXT_DEPTH + 0) * 2;
        buf[idx + 0] = (uint32_t)(cw >> 32);
        buf[idx + 1] = (uint32_t)(cw & 0xFFFFFFFFu);
        /* ctx 1-15: NOP (zero — already set by memset) */
    }
}

/* ── CGRA FC Layer ───────────────────────────────────────────────── */
/*
 * Compute:  output[j] = (Σ_i input_q[i] × weight_q[i][j]) >> SHIFT + bias[j]
 *
 * Optimisation applied:
 *
 *  ACC_CLR — Replaces cgra_soft_reset() with a single-context ACC_CLR
 *             instruction run at the start of each output group.  Only
 *             the PE accumulators are cleared; no full CU reset.
 *
 * Why HW loop count>0 is NOT used here (FC correctness constraint):
 *
 *  The HW loop repeats the same CONTEXT_DEPTH config words from config
 *  RAM.  Correct FC matmul requires different weight immediates for each
 *  input chunk (13 weights per run × 61 chunks = 784 features).  The
 *  scratchpad (SPM) cannot substitute because:
 *
 *    a) spm_addr = operand1[7:0] — driven by the config immediate and
 *       NOT auto-incremented by the hardware loop counter (cgra_pe.sv:567).
 *    b) SRC_SPM (4'd5) reads spm_rdata, whose address for the next cycle
 *       is set to spm_rdata[7:0] — pointer chasing, not sequential access.
 *    c) SPM depth = 256 words < 784 features; a single preload does not fit.
 *    d) Tile memory address = context_pc, always restarting at 0 on each
 *       cgra_run() call — pre-loading the full vector does not help for
 *       sequential per-chunk calls without HW loop.
 *
 *  HW loop count>0 IS correct for workloads where the same config weights
 *  apply across all loop iterations, e.g. KNN with a short reference vector
 *  (≤ MAC_PER_RUN = 13 features) pre-loaded as config immediates.
 *
 * Weight matrix layout: [in_features][out_features] row-major.
 */
static int cgra_fc_layer(cgra_dev_t *dev,
                         const int32_t *input_q,   /* [in_feat]              */
                         const int32_t *weight_q,   /* [in_feat * out_feat]   */
                         const int32_t *bias,       /* [out_feat]             */
                         int32_t *output,            /* [out_feat]             */
                         int in_feat, int out_feat,
                         cgra_cma_buf_t *cma_cfg,
                         cgra_cma_buf_t *cma_tile)
{
    int n_groups = (out_feat + CGRA_ROWS - 1) / CGRA_ROWS;
    int n_chunks = (in_feat  + MAC_PER_RUN - 1) / MAC_PER_RUN;

    uint32_t *cfg_buf  = (uint32_t *)cma_cfg->virt;
    int32_t  *tile_buf = (int32_t  *)cma_tile->virt;

    for (int g = 0; g < n_groups; g++) {

        /* ── 1. ACC_CLR: clear all PE accumulators ──────────────── */
        build_acc_clr_config(cfg_buf);
        if (cgra_dma_read(dev, cma_cfg->phys,
                          CONFIG_BASE, CFG_BUF_BYTES) < 0) {
            fprintf(stderr, "[CGRA] ACC_CLR DMA failed (g=%d)\n", g);
            return -1;
        }
        cgra_set_loop(dev, 0, 0, 0);   /* run ctx 0 (ACC_CLR) once */
        if (cgra_run(dev) < 0) {
            fprintf(stderr, "[CGRA] ACC_CLR run failed (g=%d)\n", g);
            return -1;
        }

        for (int k = 0; k < n_chunks; k++) {
            int base  = k * MAC_PER_RUN;
            int count = (base + MAC_PER_RUN <= in_feat)
                      ? MAC_PER_RUN : in_feat - base;

            /* ── 2. Build per-PE config with correct weight IMMs ── */
            int32_t chunk_wt[CGRA_ROWS][MAC_PER_RUN];
            memset(chunk_wt, 0, sizeof(chunk_wt));
            for (int r = 0; r < CGRA_ROWS; r++) {
                int oidx = g * CGRA_ROWS + r;
                if (oidx >= out_feat) continue;
                for (int c = 0; c < count; c++)
                    chunk_wt[r][c] = weight_q[(base + c) * out_feat + oidx];
            }
            build_fc_config(cfg_buf, chunk_wt, count);

            if (cgra_dma_read(dev, cma_cfg->phys,
                              CONFIG_BASE, CFG_BUF_BYTES) < 0) {
                fprintf(stderr, "[CGRA] Config DMA failed (g=%d k=%d)\n", g, k);
                return -1;
            }

            /* ── 3. Load input chunk to all 4 tile-memory banks ── */
            for (int r = 0; r < CGRA_ROWS; r++) {
                for (int c = 0; c < CONTEXT_DEPTH; c++) {
                    int si = base + c;
                    tile_buf[r * CONTEXT_DEPTH + c] =
                        (c < count && si < in_feat) ? input_q[si] : 0;
                }
                uint32_t src_off = cma_tile->phys
                                 + (uint32_t)(r * CONTEXT_DEPTH) * sizeof(int32_t);
                if (cgra_dma_read(dev, src_off, TILE_BANK(r),
                                  CONTEXT_DEPTH * sizeof(int32_t)) < 0) {
                    fprintf(stderr, "[CGRA] Tile DMA failed (g=%d k=%d r=%d)\n",
                            g, k, r);
                    return -1;
                }
            }

            /* ── 4. Execute 16 contexts (13 MAC + 3 drain) ──────── */
            cgra_set_loop(dev, 0, 15, 0);   /* count=0: run once */
            int cycles = cgra_run(dev);
            if (cycles < 0) {
                fprintf(stderr, "[CGRA] CU timeout (g=%d k=%d)\n", g, k);
                return -1;
            }
        }

        /* ── 5. Read accumulated results from east-edge regs ─────── */
        uint32_t results[4];
        cgra_get_results(dev, results);
        for (int r = 0; r < CGRA_ROWS; r++) {
            int oidx = g * CGRA_ROWS + r;
            if (oidx >= out_feat) continue;
            int32_t raw = (int32_t)results[r];
            output[oidx] = (raw >> QUANT_SHIFT)
                         + (bias ? bias[oidx] : 0);
        }
    }

    return 0;
}

/* ── Software FC reference (quantized, for comparison) ───────────── */

static void sw_fc_quantized(const int32_t *input_q,
                            const int32_t *weight_q,
                            const int32_t *bias,
                            int32_t *output,
                            int in_feat, int out_feat)
{
    for (int j = 0; j < out_feat; j++) {
        int32_t acc = 0;
        for (int i = 0; i < in_feat; i++)
            acc += input_q[i] * weight_q[i * out_feat + j];
        output[j] = (acc >> QUANT_SHIFT) + (bias ? bias[j] : 0);
    }
}

/* ── Test image generator (deterministic pseudo-random) ──────────── */

static void gen_test_image(int32_t *img, int idx)
{
    uint32_t rng = (uint32_t)(idx * 2654435761u + 1);
    int n = GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C;
    for (int i = 0; i < n; i++) {
        rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
        img[i] = (int32_t)(rng & 0xFF);   /* 0-255 grayscale */
    }
}

/* ── Main ────────────────────────────────────────────────────────── */

int main(int argc, char *argv[])
{
    printf("========================================\n");
    printf("  CGRA 4x4 LPR Accelerator\n");
    printf("  INT16 act / INT8 wt  Quantization\n");
    printf("  FC Layer Offload + Golden Model\n");
    printf("========================================\n\n");

    int use_hw = !(argc > 1 && strcmp(argv[1], "--sw-only") == 0);

    /* ── Golden model weights ────────────────────────────────────── */

    GoldenWeights *gw   = (GoldenWeights *)malloc(sizeof(GoldenWeights));
    GoldenContext *gctx  = (GoldenContext *)calloc(1, sizeof(GoldenContext));
    if (!gw || !gctx) { fprintf(stderr, "malloc failed\n"); return 1; }

    golden_weights_init_synthetic(gw, 0xCAFEBABE);
    golden_context_init(gctx, NULL, NULL);

    /* ── Quantize FC weights (int32 → INT8, stored as int32) ───── */

    const int fc_in  = GOLDEN_FC_IN;    /* 784  */
    const int fc_out = GOLDEN_FC_OUT;   /* 30   */

    int32_t *fc_w_q     = (int32_t *)malloc(fc_in * fc_out * sizeof(int32_t));
    int32_t *fc_input_q = (int32_t *)calloc(fc_in, sizeof(int32_t));
    int32_t *fc_out_hw  = (int32_t *)calloc(fc_out, sizeof(int32_t));
    int32_t *fc_out_sw  = (int32_t *)calloc(fc_out, sizeof(int32_t));
    int32_t *input_img  = (int32_t *)calloc(GOLDEN_IN_H * GOLDEN_IN_W, sizeof(int32_t));

    if (!fc_w_q || !fc_input_q || !fc_out_hw || !fc_out_sw || !input_img) {
        fprintf(stderr, "malloc failed\n"); return 1;
    }

    quantize_weight_matrix(gw->fc_w, fc_w_q, fc_in * fc_out);

    printf("[QUANT] FC weights quantized: %dx%d INT8 (range [-4,+3])\n",
           fc_in, fc_out);
    printf("[QUANT] Activations: INT16 Q8.8 (scale=%d)\n", QUANT_SCALE);
    printf("[ARCH]  MAC per run: %d  |  Drain cycles: %d  |  Groups: %d\n",
           MAC_PER_RUN, DRAIN_CYCLES,
           (fc_out + CGRA_ROWS - 1) / CGRA_ROWS);
    printf("[ARCH]  Chunks per group: %d  |  Total CGRA runs: %d\n",
           (fc_in + MAC_PER_RUN - 1) / MAC_PER_RUN,
           ((fc_out + CGRA_ROWS - 1) / CGRA_ROWS) *
           ((fc_in  + MAC_PER_RUN - 1) / MAC_PER_RUN));

    /* ── Initialize CGRA hardware ────────────────────────────────── */

    cgra_dev_t      dev;
    cgra_cma_buf_t  cma_cfg  = {0};
    cgra_cma_buf_t  cma_tile = {0};

    if (use_hw) {
        printf("\n[HW] Initializing CGRA via /dev/uio0 ...\n");
        if (cgra_init(&dev, "/dev/uio0") < 0) {
            fprintf(stderr, "[HW] CGRA init failed -- falling back to SW\n");
            use_hw = 0;
        } else {
            /* Per-chunk tile: CGRA_ROWS banks × CONTEXT_DEPTH words each */
            size_t tile_sz = CGRA_ROWS * CONTEXT_DEPTH * sizeof(int32_t);

            if (cgra_cma_alloc(&cma_cfg, CFG_BUF_BYTES) < 0 ||
                cgra_cma_alloc(&cma_tile, tile_sz) < 0) {
                fprintf(stderr, "[HW] CMA alloc failed -- falling back to SW\n");
                use_hw = 0;
            } else {
                cgra_irq_enable(&dev, IRQ_DONE);
                printf("[HW] CGRA ready  cfg=%zu B  tile=%zu B\n",
                       (size_t)CFG_BUF_BYTES, tile_sz);
            }
        }
    }

    /* ── Process test characters ─────────────────────────────────── */

    double total_hw_ms = 0, total_sw_ms = 0;
    int    match_count = 0;

    printf("\n--- Processing %d characters ---\n", NUM_TEST_CHARS);
    printf("    Conv1 -> Pool1 -> Conv2 -> Pool2 : ARM CPU (golden model)\n");
    printf("    FC (784->30)                     : %s\n\n",
           use_hw ? "CGRA 4x4" : "ARM CPU (SW fallback)");

    for (int ch = 0; ch < NUM_TEST_CHARS; ch++) {

        /* ── ARM: generate input image ───────────────────────────── */
        gen_test_image(input_img, ch);

        /* ── ARM: Conv1 → Pool1 → Conv2 → Pool2 (golden model) ── */
        golden_conv2d_relu(input_img, gctx->conv1_out,
                           gw->conv1_w, gw->conv1_b,
                           GOLDEN_IN_H, GOLDEN_IN_W,
                           GOLDEN_IN_C, GOLDEN_CONV1_OUT_CH,
                           GOLDEN_CONV1_KH, GOLDEN_CONV1_KW,
                           GOLDEN_CONV1_PAD, GOLDEN_CONV1_STRIDE);

        golden_maxpool_2x2(gctx->conv1_out, gctx->pool1_out,
                           GOLDEN_IN_H, GOLDEN_IN_W,
                           GOLDEN_CONV1_OUT_CH);

        golden_conv2d_relu(gctx->pool1_out, gctx->conv2_out,
                           gw->conv2_w, gw->conv2_b,
                           GOLDEN_POOL1_H, GOLDEN_POOL1_W,
                           GOLDEN_CONV2_IN_CH, GOLDEN_CONV2_OUT_CH,
                           GOLDEN_CONV2_KH, GOLDEN_CONV2_KW,
                           GOLDEN_CONV2_PAD, GOLDEN_CONV2_STRIDE);

        golden_maxpool_2x2(gctx->conv2_out, gctx->pool2_out,
                           GOLDEN_POOL1_H, GOLDEN_POOL1_W,
                           GOLDEN_CONV2_OUT_CH);

        /* ── ARM: Quantize FC input (Pool2 output) to INT16 ─────── */
        quantize_activations(gctx->pool2_out, fc_input_q, fc_in);

        /* ── CGRA: FC layer (hardware) ───────────────────────────── */
        int class_hw = -1;
        if (use_hw) {
            double t0 = time_ms();

            if (cgra_fc_layer(&dev, fc_input_q, fc_w_q, gw->fc_b,
                              fc_out_hw, fc_in, fc_out,
                              &cma_cfg, &cma_tile) == 0)
                class_hw = golden_argmax(fc_out_hw, fc_out);

            total_hw_ms += time_ms() - t0;

            printf("[CHAR %2d] HW: '%c' (%2d)",
                   ch,
                   (class_hw >= 0 && class_hw < VN_NUM_CLASSES)
                       ? VN_CHAR_MAP[class_hw] : '?',
                   class_hw);
        }

        /* ── ARM: FC layer (software reference) ──────────────────── */
        double t0_sw = time_ms();

        sw_fc_quantized(fc_input_q, fc_w_q, gw->fc_b,
                        fc_out_sw, fc_in, fc_out);
        int class_sw = golden_argmax(fc_out_sw, fc_out);

        total_sw_ms += time_ms() - t0_sw;

        if (use_hw) {
            int ok = (class_hw == class_sw);
            if (ok) match_count++;
            printf("  |  SW: '%c' (%2d)  %s\n",
                   VN_CHAR_MAP[class_sw], class_sw,
                   ok ? "[MATCH]" : "[MISMATCH]");
        } else {
            printf("[CHAR %2d] SW: '%c' (class %2d)  %.3f ms\n",
                   ch, VN_CHAR_MAP[class_sw], class_sw,
                   time_ms() - t0_sw);
        }
    }

    /* ── Summary ─────────────────────────────────────────────────── */

    printf("\n========================================\n");
    printf("  Results (%d characters)\n", NUM_TEST_CHARS);
    printf("========================================\n");
    printf("  Quantization : INT16 activations / INT8 weights\n");
    printf("  FC layer     : %d -> %d  (%d MACs/char)\n",
           fc_in, fc_out, fc_in * fc_out);

    if (use_hw) {
        printf("  HW avg       : %.3f ms/char\n", total_hw_ms / NUM_TEST_CHARS);
        printf("  SW avg       : %.3f ms/char\n", total_sw_ms / NUM_TEST_CHARS);
        if (total_hw_ms > 0)
            printf("  Speedup      : %.2fx\n", total_sw_ms / total_hw_ms);
        printf("  HW/SW match  : %d / %d\n", match_count, NUM_TEST_CHARS);
    } else {
        printf("  SW avg       : %.3f ms/char\n", total_sw_ms / NUM_TEST_CHARS);
    }

    /* ── Cleanup ─────────────────────────────────────────────────── */

    if (use_hw) {
        cgra_cma_free(&cma_cfg);
        cgra_cma_free(&cma_tile);
        cgra_close(&dev);
    }

    free(gw);        free(gctx);
    free(fc_w_q);    free(fc_input_q);
    free(fc_out_hw); free(fc_out_sw);
    free(input_img);

    printf("\nDone.\n");
    return 0;
}
