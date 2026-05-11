/* cnn_conv_bm.c — see cnn_conv_bm.h. */

#include "cnn_conv_bm.h"
#include "cgra.h"
#include "cgra_kernels_cnn.h"
#include "cnn_requant_bm.h"

#include <stdint.h>
#include <stddef.h>

/* Conv weight blob (from demo_mnist_conv_weights.S). Layout:
 *   conv1 OKHWI [8,3,3,1] INT16  (144 B)
 *   conv1 biases INT32 [8]       ( 32 B)
 *   conv2 OKHWI [16,3,3,8] INT16 (2304 B)
 *   conv2 biases INT32 [16]      ( 64 B)
 */
extern const uint8_t cnn_conv_start[];

/* Input scaling for INT MAC compatibility. INPUT_SCALE = 256 lifts the
 * mean-subtracted normalized pixel into integer range while keeping
 * Conv1 MAC sums well above bias_q magnitudes. */
#define INPUT_SCALE       256
#define INPUT_SCALE_LOG2  8

/* 1 / MNIST_CONV1_SCALE_W_F (= 1 / 0.00003041). Used to scale Conv2 bias
 * into the Conv2 accumulator's post-requant units. */
#define CONV1_INV_SCALE_W 32885

/* Input normalization in integer fixed point. */
static inline int32_t normalize_pixel(uint8_t v)
{
    /* ((v/255 - 0.1307) / 0.3081) * INPUT_SCALE */
    int32_t scaled = (int32_t)v * (INPUT_SCALE * 65536) / 255;
    scaled -= (int32_t)(0.1307f * INPUT_SCALE * 65536.0f);
    int32_t out = scaled / (int32_t)(0.3081f * 65536.0f);
    return out;
}

/* INT16 weight extraction from the OKHWI blob. */
static inline int16_t c1_weight(int oc, int kh, int kw) {
    const int16_t *w = (const int16_t *)cnn_conv_start;
    return w[oc * 9 + kh * 3 + kw];
}
static inline int32_t c1_bias(int oc) {
    const int32_t *b = (const int32_t *)(cnn_conv_start + 144);
    return b[oc];
}
static inline int16_t c2_weight(int oc, int kh, int kw, int ic) {
    const int16_t *w = (const int16_t *)(cnn_conv_start + 176);
    return w[oc * 72 + kh * 24 + kw * 8 + ic];
}
static inline int32_t c2_bias(int oc) {
    const int32_t *b = (const int32_t *)(cnn_conv_start + 2480);
    return b[oc];
}

/* Pack a 16-word weight buffer for cnn_conv3x3_pixel: zeros at [0,1,11..15],
 * 9 INT16 weights sign-extended to INT32 at [2..10]. */
static void pack_weights_c1(int oc, volatile uint32_t *w_buf)
{
    for (int i = 0; i < 16; ++i) w_buf[i] = 0;
    int idx = 2;
    for (int kh = 0; kh < 3; ++kh)
        for (int kw = 0; kw < 3; ++kw)
            w_buf[idx++] = (uint32_t)(int32_t)c1_weight(oc, kh, kw);
}
static void pack_weights_c2(int oc, int ic, volatile uint32_t *w_buf)
{
    for (int i = 0; i < 16; ++i) w_buf[i] = 0;
    int idx = 2;
    for (int kh = 0; kh < 3; ++kh)
        for (int kw = 0; kw < 3; ++kw)
            w_buf[idx++] = (uint32_t)(int32_t)c2_weight(oc, kh, kw, ic);
}

/* Pack a 3x3 input patch from a HWC INT32 buffer at (oh, ow). */
static void pack_inputs(int32_t *src, int H, int W, int C, int ic,
                        int oh, int ow,
                        volatile uint32_t *in_buf)
{
    (void)H;
    for (int i = 0; i < 16; ++i) in_buf[i] = 0;
    int idx = 2;
    for (int kh = 0; kh < 3; ++kh)
        for (int kw = 0; kw < 3; ++kw) {
            int32_t v = src[((oh + kh) * W + (ow + kw)) * C + ic];
            in_buf[idx++] = (uint32_t)v;
        }
}

/* Pack inputs from a 28x28 single-channel HW-only buffer. */
static void pack_inputs_1ch(int32_t *src, int W,
                            int oh, int ow,
                            volatile uint32_t *in_buf)
{
    for (int i = 0; i < 16; ++i) in_buf[i] = 0;
    int idx = 2;
    for (int kh = 0; kh < 3; ++kh)
        for (int kw = 0; kw < 3; ++kw) {
            int32_t v = src[(oh + kh) * W + (ow + kw)];
            in_buf[idx++] = (uint32_t)v;
        }
}

/* Conv1: 28x28x1 input -> 26x26x8 output. Adds bias (correctly scaled) and
 * fused ReLU. Output is in integer accumulator units at scale
 * INPUT_SCALE * (1/s_w1) ≈ 8.42M per float unit.
 *
 * Amortized: PE0 configured once at the top, weights re-DMAed only when
 * the output channel changes. Per-pixel cost is just input-DMA + CU +
 * read — ~3500 cyc instead of cnn_conv3x3_pixel's ~7000.                */
static int conv1_run(int32_t *input_hw, int32_t *output_hwc)
{
    volatile uint32_t *wbuf  = (volatile uint32_t *)CONV_WBUF_DDR;
    volatile uint32_t *inbuf = (volatile uint32_t *)CONV_INBUF_DDR;

    if (cnn_conv3x3_kernel_setup(CONV_STAGING_DDR) < 0) return -1;

    for (int oc = 0; oc < CONV1_OUT_C; ++oc) {
        pack_weights_c1(oc, wbuf);
        if (cnn_conv3x3_load_weights(CONV_WBUF_DDR) < 0) return -1;
        int32_t bias_q = c1_bias(oc);
        for (int oh = 0; oh < CONV1_OUT_H; ++oh) {
            for (int ow = 0; ow < CONV1_OUT_W; ++ow) {
                pack_inputs_1ch(input_hw, CONV1_IN_W, oh, ow, inbuf);
                int32_t acc = 0;
                if (cnn_conv3x3_run_pixel(CONV_INBUF_DDR, &acc) < 0)
                    return -1;
                int32_t out = conv1_apply_bias(acc, bias_q, INPUT_SCALE_LOG2);
                if (out < 0) out = 0;
                output_hwc[(oh * CONV1_OUT_W + ow) * CONV1_OUT_C + oc] = out;
            }
        }
    }
    return 0;
}

/* Conv2: 13x13x8 input -> 11x11x16 output with fused ReLU and bias.
 *
 * Inputs are pool1_out *after* shift1 right-shift, so they fit in INT16.
 * MAC across 8 input channels stays well inside INT32. Bias is converted
 * from (1/s_w2) units into the Conv2-accumulator scale using shift1.    */
/* Conv2: 13x13x8 input -> 11x11x16 output with fused ReLU and bias.
 * Amortized: weights are re-DMAed only when (oc, ic) advances; the
 * inner loop over (oh, ow) shares PE config and SPM weight content. */
static int conv2_run(int32_t *input_hwc, int32_t *output_hwc, int shift1)
{
    volatile uint32_t *wbuf  = (volatile uint32_t *)CONV_WBUF_DDR;
    volatile uint32_t *inbuf = (volatile uint32_t *)CONV_INBUF_DDR;

    if (cnn_conv3x3_kernel_setup(CONV_STAGING_DDR) < 0) return -1;

    /* Zero the channel-sum buffer before accumulating across ic. */
    for (int i = 0; i < CONV2_OUT_H * CONV2_OUT_W * CONV2_OUT_C; ++i)
        output_hwc[i] = 0;

    for (int oc = 0; oc < CONV2_OUT_C; ++oc) {
        for (int ic = 0; ic < CONV2_IN_C; ++ic) {
            pack_weights_c2(oc, ic, wbuf);
            if (cnn_conv3x3_load_weights(CONV_WBUF_DDR) < 0) return -1;
            for (int oh = 0; oh < CONV2_OUT_H; ++oh) {
                for (int ow = 0; ow < CONV2_OUT_W; ++ow) {
                    pack_inputs(input_hwc, CONV2_IN_H, CONV2_IN_W,
                                CONV2_IN_C, ic, oh, ow, inbuf);
                    int32_t acc = 0;
                    if (cnn_conv3x3_run_pixel(CONV_INBUF_DDR, &acc) < 0)
                        return -1;
                    output_hwc[(oh * CONV2_OUT_W + ow) * CONV2_OUT_C + oc]
                        += acc;
                }
            }
        }
        /* After all 8 ic accumulated, add bias + ReLU for this oc. */
        int32_t bias_q = c2_bias(oc);
        for (int oh = 0; oh < CONV2_OUT_H; ++oh) {
            for (int ow = 0; ow < CONV2_OUT_W; ++ow) {
                int idx = (oh * CONV2_OUT_W + ow) * CONV2_OUT_C + oc;
                int32_t v = conv2_apply_bias(output_hwc[idx], bias_q,
                                             INPUT_SCALE,
                                             CONV1_INV_SCALE_W,
                                             shift1);
                if (v < 0) v = 0;
                output_hwc[idx] = v;
            }
        }
    }
    return 0;
}

/* 2x2 max-pool stride 2, HWC layout, INT32. */
static void maxpool_2x2(int32_t *input, int H_in, int W_in, int C,
                        int32_t *output)
{
    int H_out = H_in / 2, W_out = W_in / 2;
    for (int oh = 0; oh < H_out; ++oh) {
        for (int ow = 0; ow < W_out; ++ow) {
            for (int c = 0; c < C; ++c) {
                int32_t a = input[((oh*2  ) * W_in + ow*2  ) * C + c];
                int32_t b = input[((oh*2  ) * W_in + ow*2+1) * C + c];
                int32_t cc = input[((oh*2+1) * W_in + ow*2  ) * C + c];
                int32_t d = input[((oh*2+1) * W_in + ow*2+1) * C + c];
                int32_t m = a;
                if (b  > m) m = b;
                if (cc > m) m = cc;
                if (d  > m) m = d;
                output[(oh * W_out + ow) * C + c] = m;
            }
        }
    }
}

/* Transpose HWC -> CHW. Output [16][5][5] flattened to 400. */
static void chw_transpose(const int32_t *pool2_hwc, int32_t *act400_out)
{
    for (int c = 0; c < CONV2_OUT_C; ++c) {
        for (int h = 0; h < POOL2_OUT_H; ++h) {
            for (int w = 0; w < POOL2_OUT_W; ++w) {
                int hwc = ((size_t)h * POOL2_OUT_W + w) * CONV2_OUT_C + c;
                int chw = ((size_t)c * POOL2_OUT_H + h) * POOL2_OUT_W + w;
                act400_out[chw] = pool2_hwc[hwc];
            }
        }
    }
}

int cnn_full_inference(const uint8_t input_uint8[CONV1_IN_H * CONV1_IN_W],
                       int32_t       act400_out[POOL2_OUT_N])
{
    int32_t *input_buf  = (int32_t *)CONV_INPUT_DDR;
    int32_t *conv1_out  = (int32_t *)CONV1_OUT_DDR;
    int32_t *pool1_out  = (int32_t *)POOL1_OUT_DDR;
    int32_t *conv2_out  = (int32_t *)CONV2_OUT_DDR;
    int32_t *pool2_out  = (int32_t *)POOL2_OUT_DDR;

    for (int i = 0; i < CONV1_IN_H * CONV1_IN_W; ++i)
        input_buf[i] = normalize_pixel(input_uint8[i]);
    asm volatile("dsb" ::: "memory");

    if (conv1_run(input_buf, conv1_out) < 0) return -1;
    maxpool_2x2(conv1_out, CONV1_OUT_H, CONV1_OUT_W, CONV1_OUT_C, pool1_out);

    /* Per-layer requant after pool1 — clamps inputs to Conv2 into INT16. */
    int shift1 = cnn_requant_to_int16(pool1_out,
                                      POOL1_OUT_H * POOL1_OUT_W * CONV1_OUT_C);

    if (conv2_run(pool1_out, conv2_out, shift1) < 0) return -1;
    maxpool_2x2(conv2_out, CONV2_OUT_H, CONV2_OUT_W, CONV2_OUT_C, pool2_out);

    /* Per-image requant before flattening to FC1 input. */
    (void)cnn_requant_to_int16(pool2_out, POOL2_OUT_N);
    chw_transpose(pool2_out, act400_out);
    return 0;
}
