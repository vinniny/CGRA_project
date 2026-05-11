/* arm_cnn_bm.c — float CNN reference (Conv1+Pool1+Conv2+Pool2+flatten+quant)
 * Compiled twice into the demo ELF:
 *   1. -mfpu=vfpv3 -mfloat-abi=hard -DARM_CNN_VARIANT=1  → arm_cnn_vfp_run
 *   2. -mfloat-abi=soft             -DARM_CNN_VARIANT=2  → arm_cnn_scalar_run
 *
 * The VFP build maps each `float` op to a VFPv3 instruction (~1-3 cyc on
 * Cortex-A9). The scalar build emits libgcc soft-float helpers
 * (__aeabi_fadd / __aeabi_fmul / etc.), which average ~30-80 cycles per
 * op — matching the thesis abstract's "8-12 FPS ARM baseline".          */

#include "arm_cnn_bm.h"

#include <stdint.h>
#include <stddef.h>

#ifndef ARM_CNN_VARIANT
# error "Define ARM_CNN_VARIANT=1 (VFP) or 2 (scalar) when compiling arm_cnn_bm.c"
#endif

#if ARM_CNN_VARIANT == 1
# define ARM_CNN_RUN_NAME arm_cnn_vfp_run
#elif ARM_CNN_VARIANT == 2
# define ARM_CNN_RUN_NAME arm_cnn_scalar_run
#else
# error "ARM_CNN_VARIANT must be 1 or 2"
#endif

extern const uint8_t cnn_conv_start[];

#define CONV1_SCALE_W   0.00003041f
#define CONV2_SCALE_W   0.00004060f

#define C1_OUT_C   8
#define C1_IN_C    1
#define C1_KH      3
#define C1_KW      3
#define C1_IN_H    28
#define C1_IN_W    28
#define C1_OUT_H   (C1_IN_H - C1_KH + 1)
#define C1_OUT_W   (C1_IN_W - C1_KW + 1)

#define P1_OUT_H   (C1_OUT_H / 2)
#define P1_OUT_W   (C1_OUT_W / 2)

#define C2_OUT_C   16
#define C2_IN_C    C1_OUT_C
#define C2_KH      3
#define C2_KW      3
#define C2_IN_H    P1_OUT_H
#define C2_IN_W    P1_OUT_W
#define C2_OUT_H   (C2_IN_H - C2_KH + 1)
#define C2_OUT_W   (C2_IN_W - C2_KW + 1)

#define P2_OUT_H   (C2_OUT_H / 2)
#define P2_OUT_W   (C2_OUT_W / 2)
#define P2_OUT_N   (P2_OUT_H * P2_OUT_W * C2_OUT_C)

/* Each variant gets its own .bss buffers to avoid linker name clashes
 * when both objects are linked together. */
#if ARM_CNN_VARIANT == 1
# define VAR(name) name ## _vfp
#else
# define VAR(name) name ## _scalar
#endif

static float VAR(buf_normalized)[C1_IN_H * C1_IN_W];
static float VAR(buf_conv1_out) [C1_OUT_H * C1_OUT_W * C1_OUT_C];
static float VAR(buf_pool1_out) [P1_OUT_H * P1_OUT_W * C1_OUT_C];
static float VAR(buf_conv2_out) [C2_OUT_H * C2_OUT_W * C2_OUT_C];
static float VAR(buf_pool2_out) [P2_OUT_N];
static float VAR(buf_pool2_chw) [P2_OUT_N];

static float VAR(c1_w_f)[C1_OUT_C * C1_KH * C1_KW * C1_IN_C];
static float VAR(c1_b_f)[C1_OUT_C];
static float VAR(c2_w_f)[C2_OUT_C * C2_KH * C2_KW * C2_IN_C];
static float VAR(c2_b_f)[C2_OUT_C];
static int   VAR(weights_loaded) = 0;

static void VAR(load_weights)(void)
{
    if (VAR(weights_loaded)) return;
    const int16_t *c1_w_i16 = (const int16_t *)cnn_conv_start;
    const int32_t *c1_b_i32 = (const int32_t *)(cnn_conv_start + 144);
    const int16_t *c2_w_i16 = (const int16_t *)(cnn_conv_start + 176);
    const int32_t *c2_b_i32 = (const int32_t *)(cnn_conv_start + 2480);

    for (size_t i = 0; i < sizeof(VAR(c1_w_f)) / sizeof(VAR(c1_w_f)[0]); ++i)
        VAR(c1_w_f)[i] = (float)c1_w_i16[i] * CONV1_SCALE_W;
    for (int i = 0; i < C1_OUT_C; ++i)
        VAR(c1_b_f)[i] = (float)c1_b_i32[i] * CONV1_SCALE_W;
    for (size_t i = 0; i < sizeof(VAR(c2_w_f)) / sizeof(VAR(c2_w_f)[0]); ++i)
        VAR(c2_w_f)[i] = (float)c2_w_i16[i] * CONV2_SCALE_W;
    for (int i = 0; i < C2_OUT_C; ++i)
        VAR(c2_b_f)[i] = (float)c2_b_i32[i] * CONV2_SCALE_W;

    VAR(weights_loaded) = 1;
}

static void VAR(normalize_input)(const uint8_t *src, float *dst)
{
    const float inv255 = 1.0f / 255.0f;
    const float mean   = 0.1307f;
    const float stdinv = 1.0f / 0.3081f;
    for (int i = 0; i < ARM_CNN_INPUT_N; ++i)
        dst[i] = ((float)src[i] * inv255 - mean) * stdinv;
}

static void VAR(conv2d)(const float *input, const float *weights,
                        const float *bias, float *output,
                        int H_in, int W_in, int C_in,
                        int H_out, int W_out, int C_out,
                        int KH, int KW)
{
    const size_t wstride_oc = (size_t)KH * KW * C_in;
    for (int oh = 0; oh < H_out; ++oh) {
        for (int ow = 0; ow < W_out; ++ow) {
            for (int oc = 0; oc < C_out; ++oc) {
                float acc = bias[oc];
                const float *w_oc = weights + (size_t)oc * wstride_oc;
                for (int kh = 0; kh < KH; ++kh) {
                    for (int kw = 0; kw < KW; ++kw) {
                        int ih = oh + kh;
                        int iw = ow + kw;
                        const float *in_pos =
                            input + ((size_t)ih * W_in + iw) * C_in;
                        const float *w_pos =
                            w_oc + ((size_t)kh * KW + kw) * C_in;
                        for (int ic = 0; ic < C_in; ++ic)
                            acc += in_pos[ic] * w_pos[ic];
                    }
                }
                output[((size_t)oh * W_out + ow) * C_out + oc] = acc;
            }
        }
    }
}

static void VAR(relu_inplace)(float *buf, int n)
{
    for (int i = 0; i < n; ++i) if (buf[i] < 0.0f) buf[i] = 0.0f;
}

static void VAR(maxpool_2x2)(const float *input, float *output,
                             int H_in, int W_in, int C)
{
    int H_out = H_in / 2, W_out = W_in / 2;
    for (int oh = 0; oh < H_out; ++oh) {
        for (int ow = 0; ow < W_out; ++ow) {
            for (int c = 0; c < C; ++c) {
                int ih = oh * 2, iw = ow * 2;
                float a = input[((size_t)(ih    ) * W_in + iw    ) * C + c];
                float b = input[((size_t)(ih    ) * W_in + iw + 1) * C + c];
                float cc = input[((size_t)(ih + 1) * W_in + iw    ) * C + c];
                float d = input[((size_t)(ih + 1) * W_in + iw + 1) * C + c];
                float m = a;
                if (b  > m) m = b;
                if (cc > m) m = cc;
                if (d  > m) m = d;
                output[((size_t)oh * W_out + ow) * C + c] = m;
            }
        }
    }
}

static void VAR(quantize_to_int32)(const float *buf, int32_t *out, int n)
{
    float max_abs = 0.0f;
    for (int i = 0; i < n; ++i) {
        float a = buf[i];
        if (a < 0.0f) a = -a;
        if (a > max_abs) max_abs = a;
    }
    if (max_abs <= 0.0f) {
        for (int i = 0; i < n; ++i) out[i] = 0;
        return;
    }
    float inv_scale = 32767.0f / max_abs;
    for (int i = 0; i < n; ++i) {
        float q = buf[i] * inv_scale;
        int32_t qi = (int32_t)(q >= 0.0f ? q + 0.5f : q - 0.5f);
        if (qi >  32767) qi =  32767;
        if (qi < -32768) qi = -32768;
        out[i] = qi;
    }
}

int ARM_CNN_RUN_NAME(const uint8_t input_uint8[ARM_CNN_INPUT_N],
                     int32_t       act400_out[ARM_CNN_ACT400_N])
{
    VAR(load_weights)();
    VAR(normalize_input)(input_uint8, VAR(buf_normalized));

    VAR(conv2d)(VAR(buf_normalized), VAR(c1_w_f), VAR(c1_b_f),
                VAR(buf_conv1_out),
                C1_IN_H, C1_IN_W, C1_IN_C,
                C1_OUT_H, C1_OUT_W, C1_OUT_C,
                C1_KH, C1_KW);
    VAR(relu_inplace)(VAR(buf_conv1_out), C1_OUT_H * C1_OUT_W * C1_OUT_C);
    VAR(maxpool_2x2)(VAR(buf_conv1_out), VAR(buf_pool1_out),
                     C1_OUT_H, C1_OUT_W, C1_OUT_C);

    VAR(conv2d)(VAR(buf_pool1_out), VAR(c2_w_f), VAR(c2_b_f),
                VAR(buf_conv2_out),
                C2_IN_H, C2_IN_W, C2_IN_C,
                C2_OUT_H, C2_OUT_W, C2_OUT_C,
                C2_KH, C2_KW);
    VAR(relu_inplace)(VAR(buf_conv2_out), C2_OUT_H * C2_OUT_W * C2_OUT_C);
    VAR(maxpool_2x2)(VAR(buf_conv2_out), VAR(buf_pool2_out),
                     C2_OUT_H, C2_OUT_W, C2_OUT_C);

    /* HWC → CHW transpose: PyTorch reshape order. */
    for (int c = 0; c < C2_OUT_C; ++c) {
        for (int h = 0; h < P2_OUT_H; ++h) {
            for (int w = 0; w < P2_OUT_W; ++w) {
                int hwc = ((size_t)h * P2_OUT_W + w) * C2_OUT_C + c;
                int chw = ((size_t)c * P2_OUT_H + h) * P2_OUT_W + w;
                VAR(buf_pool2_chw)[chw] = VAR(buf_pool2_out)[hwc];
            }
        }
    }

    VAR(quantize_to_int32)(VAR(buf_pool2_chw), act400_out, P2_OUT_N);
    return 0;
}
