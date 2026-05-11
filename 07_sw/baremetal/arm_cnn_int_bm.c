/* arm_cnn_int_bm.c — see header. Pure integer Conv+Pool+quantize on ARM,
 * matching cnn_conv_bm.c's INT pipeline but without any CGRA calls. */

#include "arm_cnn_int_bm.h"
#include <stdint.h>
#include <stddef.h>

extern const uint8_t cnn_conv_start[];

#define INPUT_SCALE       256
#define INPUT_SCALE_LOG2  8
#define CONV1_INV_SCALE_W 32885   /* 1 / MNIST_CONV1_SCALE_W_F */

#define C1_OUT_C   8
#define C1_KH      3
#define C1_KW      3
#define C1_IN_H    28
#define C1_IN_W    28
#define C1_OUT_H   26
#define C1_OUT_W   26

#define P1_OUT_H   13
#define P1_OUT_W   13

#define C2_OUT_C   16
#define C2_IN_C    8
#define C2_KH      3
#define C2_KW      3
#define C2_IN_H    13
#define C2_IN_W    13
#define C2_OUT_H   11
#define C2_OUT_W   11

#define P2_OUT_H   5
#define P2_OUT_W   5
#define P2_OUT_N   (P2_OUT_H * P2_OUT_W * C2_OUT_C)

/* Distinct .bss buffers from arm_cnn_bm (which uses floats). */
static int32_t int_buf_input  [C1_IN_H * C1_IN_W];
static int32_t int_buf_conv1  [C1_OUT_H * C1_OUT_W * C1_OUT_C];
static int32_t int_buf_pool1  [P1_OUT_H * P1_OUT_W * C1_OUT_C];
static int32_t int_buf_conv2  [C2_OUT_H * C2_OUT_W * C2_OUT_C];
static int32_t int_buf_pool2  [P2_OUT_N];

static inline int16_t c1_w(int oc, int kh, int kw) {
    const int16_t *w = (const int16_t *)cnn_conv_start;
    return w[oc * 9 + kh * 3 + kw];
}
static inline int32_t c1_b(int oc) {
    const int32_t *b = (const int32_t *)(cnn_conv_start + 144);
    return b[oc];
}
static inline int16_t c2_w(int oc, int kh, int kw, int ic) {
    const int16_t *w = (const int16_t *)(cnn_conv_start + 176);
    return w[oc * 72 + kh * 24 + kw * 8 + ic];
}
static inline int32_t c2_b(int oc) {
    const int32_t *b = (const int32_t *)(cnn_conv_start + 2480);
    return b[oc];
}

static int32_t normalize_pixel_int(uint8_t v)
{
    int32_t scaled = (int32_t)v * (INPUT_SCALE * 65536) / 255;
    scaled -= 21884;       /* (int32_t)(0.1307f * 256 * 65536) */
    int32_t out = scaled / 20194;  /* (int32_t)(0.3081f * 65536) */
    return out;
}

static int cnn_requant_int16(int32_t *buf, int n)
{
    int32_t max_abs = 0;
    for (int i = 0; i < n; ++i) {
        int32_t a = buf[i]; if (a < 0) a = -a;
        if (a > max_abs) max_abs = a;
    }
    int shift = 0;
    while ((max_abs >> shift) > 32767 && shift < 31) shift++;
    if (shift > 0) for (int i = 0; i < n; ++i) buf[i] >>= shift;
    return shift;
}

int arm_cnn_int_run(const uint8_t input_uint8[ARM_INT_CNN_INPUT_N],
                    int32_t       act400_out[ARM_INT_CNN_ACT400_N])
{
    /* 1. Normalize. */
    for (int i = 0; i < C1_IN_H * C1_IN_W; ++i)
        int_buf_input[i] = normalize_pixel_int(input_uint8[i]);

    /* 2. Conv1 + bias + ReLU. */
    for (int oc = 0; oc < C1_OUT_C; ++oc) {
        int32_t bias_q = c1_b(oc);
        for (int oh = 0; oh < C1_OUT_H; ++oh) {
            for (int ow = 0; ow < C1_OUT_W; ++ow) {
                int32_t acc = 0;
                for (int kh = 0; kh < 3; ++kh) {
                    for (int kw = 0; kw < 3; ++kw) {
                        int32_t v = int_buf_input[(oh + kh) * C1_IN_W + (ow + kw)];
                        acc += v * (int32_t)c1_w(oc, kh, kw);
                    }
                }
                int32_t out = acc + (bias_q << INPUT_SCALE_LOG2);
                if (out < 0) out = 0;
                int_buf_conv1[(oh * C1_OUT_W + ow) * C1_OUT_C + oc] = out;
            }
        }
    }

    /* 3. Pool1 (2x2 stride 2, max). */
    for (int oh = 0; oh < P1_OUT_H; ++oh) {
        for (int ow = 0; ow < P1_OUT_W; ++ow) {
            for (int c = 0; c < C1_OUT_C; ++c) {
                int32_t a = int_buf_conv1[((oh*2  ) * C1_OUT_W + ow*2  ) * C1_OUT_C + c];
                int32_t b = int_buf_conv1[((oh*2  ) * C1_OUT_W + ow*2+1) * C1_OUT_C + c];
                int32_t cc = int_buf_conv1[((oh*2+1) * C1_OUT_W + ow*2  ) * C1_OUT_C + c];
                int32_t d = int_buf_conv1[((oh*2+1) * C1_OUT_W + ow*2+1) * C1_OUT_C + c];
                int32_t m = a;
                if (b  > m) m = b;
                if (cc > m) m = cc;
                if (d  > m) m = d;
                int_buf_pool1[(oh * P1_OUT_W + ow) * C1_OUT_C + c] = m;
            }
        }
    }

    int shift1 = cnn_requant_int16(int_buf_pool1, P1_OUT_H * P1_OUT_W * C1_OUT_C);

    /* 4. Conv2 + bias + ReLU, accumulating across 8 input channels. */
    for (int i = 0; i < C2_OUT_H * C2_OUT_W * C2_OUT_C; ++i) int_buf_conv2[i] = 0;
    for (int oc = 0; oc < C2_OUT_C; ++oc) {
        for (int oh = 0; oh < C2_OUT_H; ++oh) {
            for (int ow = 0; ow < C2_OUT_W; ++ow) {
                int32_t acc = 0;
                for (int kh = 0; kh < 3; ++kh) {
                    for (int kw = 0; kw < 3; ++kw) {
                        for (int ic = 0; ic < C2_IN_C; ++ic) {
                            int32_t v = int_buf_pool1[
                                ((oh + kh) * C2_IN_W + (ow + kw)) * C2_IN_C + ic];
                            acc += v * (int32_t)c2_w(oc, kh, kw, ic);
                        }
                    }
                }
                int32_t bias_q = c2_b(oc);
                int32_t bias_term = 0;
                if (shift1 >= 7) {
                    int64_t b64 = (int64_t)bias_q
                                * (int64_t)INPUT_SCALE
                                * (int64_t)CONV1_INV_SCALE_W;
                    b64 >>= shift1;
                    if (b64 >  (int64_t)2147483647LL) b64 =  2147483647LL;
                    if (b64 < -(int64_t)2147483648LL) b64 = -2147483648LL;
                    bias_term = (int32_t)b64;
                }
                int32_t out = acc + bias_term;
                if (out < 0) out = 0;
                int_buf_conv2[(oh * C2_OUT_W + ow) * C2_OUT_C + oc] = out;
            }
        }
    }

    /* 5. Pool2. */
    for (int oh = 0; oh < P2_OUT_H; ++oh) {
        for (int ow = 0; ow < P2_OUT_W; ++ow) {
            for (int c = 0; c < C2_OUT_C; ++c) {
                int32_t a = int_buf_conv2[((oh*2  ) * C2_OUT_W + ow*2  ) * C2_OUT_C + c];
                int32_t b = int_buf_conv2[((oh*2  ) * C2_OUT_W + ow*2+1) * C2_OUT_C + c];
                int32_t cc = int_buf_conv2[((oh*2+1) * C2_OUT_W + ow*2  ) * C2_OUT_C + c];
                int32_t d = int_buf_conv2[((oh*2+1) * C2_OUT_W + ow*2+1) * C2_OUT_C + c];
                int32_t m = a;
                if (b  > m) m = b;
                if (cc > m) m = cc;
                if (d  > m) m = d;
                int_buf_pool2[(oh * P2_OUT_W + ow) * C2_OUT_C + c] = m;
            }
        }
    }

    /* 6. Per-image requant + HWC→CHW. */
    (void)cnn_requant_int16(int_buf_pool2, P2_OUT_N);
    for (int c = 0; c < C2_OUT_C; ++c) {
        for (int h = 0; h < P2_OUT_H; ++h) {
            for (int w = 0; w < P2_OUT_W; ++w) {
                int hwc = (h * P2_OUT_W + w) * C2_OUT_C + c;
                int chw = (c * P2_OUT_H + h) * P2_OUT_W + w;
                act400_out[chw] = int_buf_pool2[hwc];
            }
        }
    }
    return 0;
}
