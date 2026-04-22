/* ===================================================================
 *  lpr_golden.c – Pure-C Golden Model for Vietnamese License Plate
 *                 Character Recognition
 *
 *  Weights and activations use IEEE 754 single-precision float.
 *  sizeof(float)==sizeof(int32_t)==4, so the GoldenWeights binary
 *  format is 99,192 bytes regardless of the element type.
 * =================================================================== */

#include "lpr_golden.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Pseudo-random generator (xorshift32) ───────────────────────── */

static uint32_t xorshift32(uint32_t *state)
{
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return x;
}

/* ── Weight initialization ──────────────────────────────────────── */

void golden_weights_init_synthetic(GoldenWeights *w, uint32_t seed)
{
    if (!w) return;
    memset(w, 0, sizeof(*w));

    uint32_t rng = seed ? seed : 0xCAFEBABE;

    float *all = (float *)w;
    size_t total = sizeof(*w) / sizeof(float);
    for (size_t i = 0; i < total; i++) {
        all[i] = (float)((int32_t)(xorshift32(&rng) % 8) - 4);
    }
}

int golden_weights_load(GoldenWeights *w, const char *path)
{
    if (!w || !path) return -1;
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    size_t n = fread(w, sizeof(*w), 1, f);
    fclose(f);
    return (n == 1) ? 0 : -1;
}

int golden_weights_save(const GoldenWeights *w, const char *path)
{
    if (!w || !path) return -1;
    FILE *f = fopen(path, "wb");
    if (!f) return -1;
    size_t n = fwrite(w, sizeof(*w), 1, f);
    fclose(f);
    return (n == 1) ? 0 : -1;
}

/* ── Context init ───────────────────────────────────────────────── */

void golden_context_init(GoldenContext *ctx,
                         golden_layer_dump_fn dump_fn,
                         void *dump_user_data)
{
    if (!ctx) return;
    memset(ctx, 0, sizeof(*ctx));
    ctx->dump_fn = dump_fn;
    ctx->dump_user_data = dump_user_data;
}

/* ── Conv2D + ReLU (multi-channel in, multi-channel out) ────────── */

void golden_conv2d_relu(const float *input, float *output,
                        const float *weights, const float *bias,
                        int H, int W, int C_in, int C_out,
                        int KH, int KW, int pad, int stride)
{
    /*
     * Input layout:   [H][W][C_in]   (HWC)
     * Output layout:  [out_H][out_W][C_out]  (HWC)
     * Weight layout:  [C_out][KH][KW][C_in]
     */
    int out_h = (H + 2 * pad - KH) / stride + 1;
    int out_w = (W + 2 * pad - KW) / stride + 1;

    for (int oc = 0; oc < C_out; oc++) {
        const float *kern = weights + oc * (KH * KW * C_in);
        float b = bias ? bias[oc] : 0.0f;

        for (int oh = 0; oh < out_h; oh++) {
            for (int ow = 0; ow < out_w; ow++) {
                float acc = b;

                for (int kh = 0; kh < KH; kh++) {
                    int ih = oh * stride - pad + kh;
                    if (ih < 0 || ih >= H) continue;

                    for (int kw = 0; kw < KW; kw++) {
                        int iw = ow * stride - pad + kw;
                        if (iw < 0 || iw >= W) continue;

                        for (int ic = 0; ic < C_in; ic++) {
                            acc += input[(ih * W + iw) * C_in + ic]
                                 * kern[(kh * KW + kw) * C_in + ic];
                        }
                    }
                }

                output[(oh * out_w + ow) * C_out + oc] = acc > 0.0f ? acc : 0.0f;
            }
        }
    }
}

/* ── MaxPool 2×2 (multi-channel) ────────────────────────────────── */

void golden_maxpool_2x2(const float *input, float *output,
                        int H, int W, int C)
{
    /*
     * Input layout:  [H][W][C]  (HWC)
     * Output layout: [H/2][W/2][C]  (HWC)
     */
    int out_h = H / 2;
    int out_w = W / 2;

    for (int oh = 0; oh < out_h; oh++) {
        for (int ow = 0; ow < out_w; ow++) {
            int ih = oh * 2;
            int iw = ow * 2;

            for (int c = 0; c < C; c++) {
                float v00 = input[(ih * W + iw) * C + c];
                float v01 = input[(ih * W + iw + 1) * C + c];
                float v10 = input[((ih + 1) * W + iw) * C + c];
                float v11 = input[((ih + 1) * W + iw + 1) * C + c];

                float mx = v00;
                if (v01 > mx) mx = v01;
                if (v10 > mx) mx = v10;
                if (v11 > mx) mx = v11;

                output[(oh * out_w + ow) * C + c] = mx;
            }
        }
    }
}

/* ── Fully Connected ────────────────────────────────────────────── */

void golden_fc(const float *input, float *output,
               const float *weights, const float *bias,
               int in_features, int out_features)
{
    /*
     * weights layout: [in_features][out_features] row-major
     * output[j] = sum_i(input[i] * weights[i * out_features + j]) + bias[j]
     */
    for (int j = 0; j < out_features; j++) {
        float acc = bias ? bias[j] : 0.0f;
        for (int i = 0; i < in_features; i++) {
            acc += input[i] * weights[i * out_features + j];
        }
        output[j] = acc;
    }
}

/* ── Argmax ─────────────────────────────────────────────────────── */

int golden_argmax(const float *vec, int len)
{
    int best = 0;
    for (int i = 1; i < len; i++) {
        if (vec[i] > vec[best])
            best = i;
    }
    return best;
}

/* ── Full inference pipeline ────────────────────────────────────── */

int golden_infer(const int32_t *input,
                 const GoldenWeights *w,
                 GoldenContext *ctx,
                 int *out_class,
                 char *out_char)
{
    if (!input || !w || !ctx) return -1;

    /* Convert int32 pixel input [0-255] to float */
    float input_f[GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C];
    for (int i = 0; i < GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C; i++)
        input_f[i] = (float)input[i];

    /* ── Conv1: [28][28][1] → [28][28][8] + ReLU ──────────────── */
    golden_conv2d_relu(input_f, ctx->conv1_out,
                       w->conv1_w, w->conv1_b,
                       GOLDEN_IN_H, GOLDEN_IN_W,
                       GOLDEN_IN_C, GOLDEN_CONV1_OUT_CH,
                       GOLDEN_CONV1_KH, GOLDEN_CONV1_KW,
                       GOLDEN_CONV1_PAD, GOLDEN_CONV1_STRIDE);

    if (ctx->dump_fn)
        ctx->dump_fn("conv1", ctx->conv1_out,
                     GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_CONV1_OUT_CH,
                     ctx->dump_user_data);

    /* ── Pool1: [28][28][8] → [14][14][8] ─────────────────────── */
    golden_maxpool_2x2(ctx->conv1_out, ctx->pool1_out,
                       GOLDEN_IN_H, GOLDEN_IN_W,
                       GOLDEN_CONV1_OUT_CH);

    if (ctx->dump_fn)
        ctx->dump_fn("pool1", ctx->pool1_out,
                     GOLDEN_POOL1_H * GOLDEN_POOL1_W * GOLDEN_CONV1_OUT_CH,
                     ctx->dump_user_data);

    /* ── Conv2: [14][14][8] → [14][14][16] + ReLU ─────────────── */
    golden_conv2d_relu(ctx->pool1_out, ctx->conv2_out,
                       w->conv2_w, w->conv2_b,
                       GOLDEN_POOL1_H, GOLDEN_POOL1_W,
                       GOLDEN_CONV2_IN_CH, GOLDEN_CONV2_OUT_CH,
                       GOLDEN_CONV2_KH, GOLDEN_CONV2_KW,
                       GOLDEN_CONV2_PAD, GOLDEN_CONV2_STRIDE);

    if (ctx->dump_fn)
        ctx->dump_fn("conv2", ctx->conv2_out,
                     GOLDEN_POOL1_H * GOLDEN_POOL1_W * GOLDEN_CONV2_OUT_CH,
                     ctx->dump_user_data);

    /* ── Pool2: [14][14][16] → [7][7][16] ─────────────────────── */
    golden_maxpool_2x2(ctx->conv2_out, ctx->pool2_out,
                       GOLDEN_POOL1_H, GOLDEN_POOL1_W,
                       GOLDEN_CONV2_OUT_CH);

    if (ctx->dump_fn)
        ctx->dump_fn("pool2", ctx->pool2_out,
                     GOLDEN_POOL2_H * GOLDEN_POOL2_W * GOLDEN_CONV2_OUT_CH,
                     ctx->dump_user_data);

    /* ── Flatten + FC: [784] → [30] ───────────────────────────── */
    golden_fc(ctx->pool2_out, ctx->fc_out,
              w->fc_w, w->fc_b,
              GOLDEN_FC_IN, GOLDEN_FC_OUT);

    if (ctx->dump_fn)
        ctx->dump_fn("fc", ctx->fc_out,
                     GOLDEN_FC_OUT,
                     ctx->dump_user_data);

    /* ── Argmax → class ───────────────────────────────────────── */
    int cls = golden_argmax(ctx->fc_out, GOLDEN_FC_OUT);

    if (out_class) *out_class = cls;
    if (out_char)  *out_char  = VN_CHAR_MAP[cls];

    return 0;
}

/* ── Accessor ───────────────────────────────────────────────────── */

const float *golden_get_fc_output(const GoldenContext *ctx)
{
    return ctx ? ctx->fc_out : NULL;
}

/* =========================================================================
 * CGRA-accelerated FC layer (M2: 784→30, weight-stationary INT16)
 *
 * Compiled only when -DUSE_CGRA_INFER is passed (baremetal demo_lpr_cgra).
 * Includes cgra.h and cgra_kernels_lpr.h from the baremetal directory
 * (reachable via -I. which is set in LPR_CFLAGS).
 * ========================================================================= */
#ifdef USE_CGRA_INFER

#include "cgra.h"
#include "cgra_kernels_lpr.h"

/* DDR addresses used by the CGRA FC path — above the existing DDR_STAGE. */
#define LPR_CGRA_POOL2_Q_DDR  0x00110000UL   /* pool2 quantised: 784 × 4B = 3136 B */
#define LPR_CGRA_STAGING_DDR  0x00112000UL   /* PE-config DMA scratch:  128 B       */

/* Pool2 activations are scaled by this integer before passing to the CGRA.
 * Pool2 float values after ReLU are in [0, ~3.5]; ×8 → [0, ~28] → fits int16.
 * Max accumulator = 784 × 28 × 32767 ≈ 0.72B  <  INT32_MAX (2.15B).  No saturation. */
#define LPR_POOL2_ACT_SCALE   8

/* Byte offsets in golden_weights_int16.bin:
 * Layout (int16): conv1_w(72)+conv1_b(8)+conv2_w(1152)+conv2_b(16)+fc_w(23520)+fc_b(30) */
#define LPR_INT16_FC_W_BOFF  ((72u+8u+1152u+16u)*2u)             /* 2496 B */
#define LPR_INT16_FC_B_BOFF  ((72u+8u+1152u+16u+23520u)*2u)      /* 49536 B */

/* ── golden_fc_cgra ────────────────────────────────────────────────────
 * Run the FC layer (784→30) on the CGRA.
 * pool2_q_ddr: DDR address holding 784 int32 quantised activations.
 * logits_raw:  output array [30] receiving raw INT32 accumulators.
 * fc_w_q:      [784][30] INT16 weights row-major (from int16 blob).
 * staging_ddr: 128 B DDR scratch for PE-config DMA.
 */
static void golden_fc_cgra(uint32_t pool2_q_ddr,
                            int32_t logits_raw[LPR_FC_N_CLASSES],
                            const int16_t *fc_w_q,
                            uint32_t staging_ddr)
{
    /* One-time: wire col=1,2,3 of every row as east-chain forwarders. */
    lpr_fc_init_chain(staging_ddr);

    for (int g = 0; g < LPR_FC_N_GROUPS; g++) {
        /* Clear the 40-bit accumulator in col=0 of all 4 rows. */
        lpr_fc_acc_clr(staging_ddr);

        /* 49 chunks of 16 inputs each (784 = 49 × 16). */
        for (int c = 0; c < LPR_FC_N_CHUNKS; c++) {
            uint32_t src = pool2_q_ddr + (uint32_t)(c * 16) * 4u;

            /* Bake weights for this (chunk, group) into col=0 MAC slots. */
            lpr_fc_program_chunk(fc_w_q, c, g, staging_ddr);

            /* Same 16 inputs broadcast to all 4 tile banks (one per row). */
            cgra_dma(src, CGRA_PFX_TILE + 0x0000u, 64u);  /* bank 0 → row 0 */
            cgra_dma(src, CGRA_PFX_TILE + 0x1000u, 64u);  /* bank 1 → row 1 */
            cgra_dma(src, CGRA_PFX_TILE + 0x2000u, 64u);  /* bank 2 → row 2 */
            cgra_dma(src, CGRA_PFX_TILE + 0x3000u, 64u);  /* bank 3 → row 3 */

            cgra_cu_start();
            cgra_cu_wait(1000000u);
        }

        /* Route accumulated RF[0] east → RESULT_ROW capture. */
        int32_t result[4];
        lpr_fc_readout(staging_ddr, result);

        for (int r = 0; r < 4; r++) {
            int n = g * 4 + r;
            if (n < LPR_FC_N_CLASSES)
                logits_raw[n] = result[r];
        }
    }
}

/* ── golden_infer_cgra ─────────────────────────────────────────────────── */
int golden_infer_cgra(const int32_t *input,
                      const GoldenWeights *w_f,
                      GoldenContext *ctx,
                      const void *w_int16_base,
                      int *out_class,
                      char *out_char)
{
    if (!input || !w_f || !ctx || !w_int16_base) return -1;

    /* ── ARM float: Conv1 + Pool1 + Conv2 + Pool2 ───────────────────────── */
    float input_f[GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C];
    for (int i = 0; i < GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C; i++)
        input_f[i] = (float)input[i];

    golden_conv2d_relu(input_f, ctx->conv1_out,
                       w_f->conv1_w, w_f->conv1_b,
                       GOLDEN_IN_H, GOLDEN_IN_W,
                       GOLDEN_IN_C, GOLDEN_CONV1_OUT_CH,
                       GOLDEN_CONV1_KH, GOLDEN_CONV1_KW,
                       GOLDEN_CONV1_PAD, GOLDEN_CONV1_STRIDE);

    golden_maxpool_2x2(ctx->conv1_out, ctx->pool1_out,
                       GOLDEN_IN_H, GOLDEN_IN_W, GOLDEN_CONV1_OUT_CH);

    golden_conv2d_relu(ctx->pool1_out, ctx->conv2_out,
                       w_f->conv2_w, w_f->conv2_b,
                       GOLDEN_POOL1_H, GOLDEN_POOL1_W,
                       GOLDEN_CONV2_IN_CH, GOLDEN_CONV2_OUT_CH,
                       GOLDEN_CONV2_KH, GOLDEN_CONV2_KW,
                       GOLDEN_CONV2_PAD, GOLDEN_CONV2_STRIDE);

    golden_maxpool_2x2(ctx->conv2_out, ctx->pool2_out,
                       GOLDEN_POOL1_H, GOLDEN_POOL1_W, GOLDEN_CONV2_OUT_CH);

    /* ── Quantise pool2_out to int32 and write to DDR for CGRA DMA ──────── */
    volatile int32_t *pool2_q = (volatile int32_t *)LPR_CGRA_POOL2_Q_DDR;
    for (int i = 0; i < GOLDEN_FC_IN; i++)
        pool2_q[i] = (int32_t)(ctx->pool2_out[i] * (float)LPR_POOL2_ACT_SCALE);

    /* ── CGRA FC ──────────────────────────────────────────────────────────── */
    const int16_t *fc_w_q = (const int16_t *)((const uint8_t *)w_int16_base
                                              + LPR_INT16_FC_W_BOFF);
    const int16_t *fc_b_q = (const int16_t *)((const uint8_t *)w_int16_base
                                              + LPR_INT16_FC_B_BOFF);

    int32_t logits_raw[LPR_FC_N_CLASSES];
    golden_fc_cgra(LPR_CGRA_POOL2_Q_DDR, logits_raw, fc_w_q, LPR_CGRA_STAGING_DDR);

    /* ── Argmax: add bias (in accumulator units) then find best class ────── */
    int best = 0;
    int32_t best_val = logits_raw[0] + (int32_t)fc_b_q[0];
    for (int j = 1; j < LPR_FC_N_CLASSES; j++) {
        int32_t val = logits_raw[j] + (int32_t)fc_b_q[j];
        if (val > best_val) { best_val = val; best = j; }
    }

    if (out_class) *out_class = best;
    if (out_char)  *out_char  = VN_CHAR_MAP[best];
    return 0;
}

#endif /* USE_CGRA_INFER */
