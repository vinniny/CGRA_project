/* cnn_conv_bm.c — see cnn_conv_bm.h. */

#include "cnn_conv_bm.h"
#include "cgra.h"
#include "cgra_kernels_cnn.h"

#include <stdint.h>
#include <stddef.h>

/* Conv weight blob (from demo_mnist_conv_weights.S). Layout:
 *   conv1 OKHWI [8,3,3,1] INT16  (144 B)
 *   conv1 biases INT32 [8]       ( 32 B)
 *   conv2 OKHWI [16,3,3,8] INT16 (2304 B)
 *   conv2 biases INT32 [16]      ( 64 B)
 */
extern const uint8_t cnn_conv_start[];

/* Input scaling: torchvision Normalize((0.1307,), (0.3081,)) applied to
 * pixel/255.  We approximate in INT32 to avoid float in the hot path:
 *   val_int = (val_uint8 * 32768 / 255 - 13107 * 32768 / 10000) * 10000 / 30810
 *          ~ ((val * 128) - 1671) * 207 / 64   (close enough for argmax)
 * For simplicity and minimal drift, we scale by 32 so the range
 * [-0.42..+2.82] maps to roughly [-13..+90] INT range — fits easily in INT8
 * and keeps subsequent MAC accumulators within INT32. */
static inline int32_t normalize_pixel(uint8_t v)
{
    /* (v/255 - 0.1307) / 0.3081  * 32   — derived once, hard-coded. */
    int32_t scaled = (int32_t)v * 8388608 / 255;       /* v/255 * 32 << 18 */
    scaled -= (int32_t)(0.1307f * 32 * 262144);        /* -mean * 32 << 18 */
    int32_t out = scaled / (int32_t)(0.3081f * 262144);
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
    /* OKHWI: w[oc][kh][kw][ic] = w[oc*72 + kh*24 + kw*8 + ic]. */
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

/* Conv1: 28x28x1 input -> 26x26x8 output. ReLU done here too (cheap). */
static int conv1_run(int32_t *input_hw, int32_t *output_hwc)
{
    volatile uint32_t *wbuf  = (volatile uint32_t *)CONV_WBUF_DDR;
    volatile uint32_t *inbuf = (volatile uint32_t *)CONV_INBUF_DDR;

    for (int oc = 0; oc < CONV1_OUT_C; ++oc) {
        pack_weights_c1(oc, wbuf);
        int32_t bias = c1_bias(oc);
        for (int oh = 0; oh < CONV1_OUT_H; ++oh) {
            for (int ow = 0; ow < CONV1_OUT_W; ++ow) {
                pack_inputs_1ch(input_hw, CONV1_IN_W, oh, ow, inbuf);
                int32_t acc = 0;
                if (cnn_conv3x3_pixel(CONV_STAGING_DDR,
                                      CONV_WBUF_DDR, CONV_INBUF_DDR,
                                      &acc) < 0) return -1;
                int32_t out = acc + bias;
                if (out < 0) out = 0; /* fused ReLU */
                output_hwc[(oh * CONV1_OUT_W + ow) * CONV1_OUT_C + oc] = out;
            }
        }
    }
    return 0;
}

/* Conv2: 13x13x8 input -> 11x11x16 output (with fused ReLU). */
static int conv2_run(int32_t *input_hwc, int32_t *output_hwc)
{
    volatile uint32_t *wbuf  = (volatile uint32_t *)CONV_WBUF_DDR;
    volatile uint32_t *inbuf = (volatile uint32_t *)CONV_INBUF_DDR;

    for (int oc = 0; oc < CONV2_OUT_C; ++oc) {
        int32_t bias = c2_bias(oc);
        for (int oh = 0; oh < CONV2_OUT_H; ++oh) {
            for (int ow = 0; ow < CONV2_OUT_W; ++ow) {
                int32_t acc_sum = bias;
                /* Sum over input channels by re-running cnn_conv3x3_pixel
                 * per ic — each pass accumulates one channel slice. */
                for (int ic = 0; ic < CONV2_IN_C; ++ic) {
                    pack_weights_c2(oc, ic, wbuf);
                    pack_inputs(input_hwc, CONV2_IN_H, CONV2_IN_W,
                                CONV2_IN_C, ic, oh, ow, inbuf);
                    int32_t acc = 0;
                    if (cnn_conv3x3_pixel(CONV_STAGING_DDR,
                                          CONV_WBUF_DDR, CONV_INBUF_DDR,
                                          &acc) < 0) return -1;
                    acc_sum += acc;
                }
                if (acc_sum < 0) acc_sum = 0; /* fused ReLU */
                output_hwc[(oh * CONV2_OUT_W + ow) * CONV2_OUT_C + oc] = acc_sum;
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

/* CHW-flatten + per-image right-shift to fit into INT16-range INT32.
 * pool2_out is HWC [5][5][16]. Output is [16][5][5] flattened to 400. */
static void chw_quantize(int32_t *pool2_hwc, int32_t *act400_out)
{
    /* Find max abs to decide a shift amount. */
    int32_t max_abs = 0;
    for (int i = 0; i < POOL2_OUT_N; ++i) {
        int32_t a = pool2_hwc[i]; if (a < 0) a = -a;
        if (a > max_abs) max_abs = a;
    }
    int shift = 0;
    while ((max_abs >> shift) > 32767 && shift < 31) shift++;

    /* Transpose HWC -> CHW + shift. */
    for (int c = 0; c < CONV2_OUT_C; ++c) {
        for (int h = 0; h < POOL2_OUT_H; ++h) {
            for (int w = 0; w < POOL2_OUT_W; ++w) {
                int hwc = ((size_t)h * POOL2_OUT_W + w) * CONV2_OUT_C + c;
                int chw = ((size_t)c * POOL2_OUT_H + h) * POOL2_OUT_W + w;
                act400_out[chw] = pool2_hwc[hwc] >> shift;
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
    if (conv2_run(pool1_out, conv2_out) < 0) return -1;
    maxpool_2x2(conv2_out, CONV2_OUT_H, CONV2_OUT_W, CONV2_OUT_C, pool2_out);
    chw_quantize(pool2_out, act400_out);
    return 0;
}

