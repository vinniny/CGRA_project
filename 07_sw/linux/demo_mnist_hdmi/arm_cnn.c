/* arm_cnn.c — see arm_cnn.h. Cortex-A9 VFPv3 float implementation. */

#include "arm_cnn.h"
#include "arm_fc.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

/* Conv weight blob is linked via demo_mnist_conv_weights.S into the
 * `.cnn_conv_spm` section, exposed as cnn_conv_start..cnn_conv_end. */
extern const uint8_t cnn_conv_start[];
extern const uint8_t cnn_conv_end[];

/* Per-tensor scale factors from mnist_weights_scale.h.
 * We embed them as constants here so arm_cnn doesn't depend on the
 * Python-generated header (keeps the C demo self-contained). */
#define ARM_CNN_CONV1_SCALE_W   0.00003041f
#define ARM_CNN_CONV2_SCALE_W   0.00004060f

/* Tensor dimensions (no padding, stride 1 conv; stride 2 pool). */
#define C1_OUT_C   8
#define C1_IN_C    1
#define C1_KH      3
#define C1_KW      3
#define C1_IN_H    28
#define C1_IN_W    28
#define C1_OUT_H   (C1_IN_H - C1_KH + 1)   /* 26 */
#define C1_OUT_W   (C1_IN_W - C1_KW + 1)   /* 26 */

#define P1_OUT_H   (C1_OUT_H / 2)          /* 13 */
#define P1_OUT_W   (C1_OUT_W / 2)          /* 13 */

#define C2_OUT_C   16
#define C2_IN_C    C1_OUT_C
#define C2_KH      3
#define C2_KW      3
#define C2_IN_H    P1_OUT_H                /* 13 */
#define C2_IN_W    P1_OUT_W
#define C2_OUT_H   (C2_IN_H - C2_KH + 1)   /* 11 */
#define C2_OUT_W   (C2_IN_W - C2_KW + 1)

#define P2_OUT_H   (C2_OUT_H / 2)          /* 5 */
#define P2_OUT_W   (C2_OUT_W / 2)
#define P2_OUT_N   (P2_OUT_H * P2_OUT_W * C2_OUT_C)   /* 400 */

/* Static intermediate buffers — sized to peak usage. ~50 KB total bss. */
static float buf_normalized[C1_IN_H * C1_IN_W * C1_IN_C];     /* 28*28*1 = 784 */
static float buf_conv1_out [C1_OUT_H * C1_OUT_W * C1_OUT_C];  /* 26*26*8 = 5408 */
static float buf_pool1_out [P1_OUT_H * P1_OUT_W * C1_OUT_C];  /* 13*13*8 = 1352 */
static float buf_conv2_out [C2_OUT_H * C2_OUT_W * C2_OUT_C];  /* 11*11*16 = 1936 */
static float buf_pool2_out [P2_OUT_N];                         /* 5*5*16 = 400 */

/* Dequantized weights, computed lazily on first call. */
static float c1_w_f[C1_OUT_C * C1_KH * C1_KW * C1_IN_C];   /* 72 */
static float c1_b_f[C1_OUT_C];                              /* 8 */
static float c2_w_f[C2_OUT_C * C2_KH * C2_KW * C2_IN_C];   /* 1152 */
static float c2_b_f[C2_OUT_C];                              /* 16 */
static int   weights_loaded = 0;

/* Layout of cnn_conv_start blob (OKHWI for weights):
 *   conv1_w_i16[0 .. 71]   (144 B)  C1_OUT_C × C1_KH × C1_KW × C1_IN_C
 *   conv1_b_i32[0 ..  7]   ( 32 B)
 *   conv2_w_i16[0 .. 1151] (2304 B) C2_OUT_C × C2_KH × C2_KW × C2_IN_C
 *   conv2_b_i32[0 .. 15]   ( 64 B)
 * Bias is in INT32 accumulator units; multiply by scale_w to dequantize. */
static void load_weights(void)
{
    if (weights_loaded) return;

    const int16_t *c1_w_i16 = (const int16_t *)cnn_conv_start;
    const int32_t *c1_b_i32 = (const int32_t *)(cnn_conv_start + 144);
    const int16_t *c2_w_i16 = (const int16_t *)(cnn_conv_start + 176);
    const int32_t *c2_b_i32 = (const int32_t *)(cnn_conv_start + 2480);

    for (size_t i = 0; i < sizeof(c1_w_f) / sizeof(c1_w_f[0]); ++i) {
        c1_w_f[i] = (float)c1_w_i16[i] * ARM_CNN_CONV1_SCALE_W;
    }
    for (int i = 0; i < C1_OUT_C; ++i) {
        c1_b_f[i] = (float)c1_b_i32[i] * ARM_CNN_CONV1_SCALE_W;
    }
    for (size_t i = 0; i < sizeof(c2_w_f) / sizeof(c2_w_f[0]); ++i) {
        c2_w_f[i] = (float)c2_w_i16[i] * ARM_CNN_CONV2_SCALE_W;
    }
    for (int i = 0; i < C2_OUT_C; ++i) {
        c2_b_f[i] = (float)c2_b_i32[i] * ARM_CNN_CONV2_SCALE_W;
    }
    weights_loaded = 1;
}

/* Input normalization: matches torchvision.transforms.Normalize(0.1307, 0.3081)
 * after ToTensor (val/255). */
static void normalize_input(const uint8_t *src, float *dst)
{
    const float inv255 = 1.0f / 255.0f;
    const float mean   = 0.1307f;
    const float stdinv = 1.0f / 0.3081f;
    for (int i = 0; i < ARM_CNN_INPUT_N; ++i) {
        dst[i] = ((float)src[i] * inv255 - mean) * stdinv;
    }
}

/* Conv2D, stride 1, no padding. Layout:
 *   weights: [out_c][kH][kW][in_c]  (OKHWI, the format in cnn_conv_start)
 *   input:   [H][W][in_c]            (HWC)
 *   output:  [out_H][out_W][out_c]   (HWC)
 * Bias is per output channel. */
static void conv2d(const float *input, const float *weights, const float *bias,
                   float *output,
                   int H_in, int W_in, int C_in,
                   int H_out, int W_out, int C_out,
                   int KH, int KW)
{
    const size_t wstride_oc = (size_t)KH * KW * C_in;   /* per output channel */
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
                        for (int ic = 0; ic < C_in; ++ic) {
                            acc += in_pos[ic] * w_pos[ic];
                        }
                    }
                }
                output[((size_t)oh * W_out + ow) * C_out + oc] = acc;
            }
        }
    }
}

/* In-place ReLU on N float values. */
static void relu_inplace(float *buf, int n)
{
    for (int i = 0; i < n; ++i) if (buf[i] < 0.0f) buf[i] = 0.0f;
}

/* 2x2 max-pool, stride 2, no padding. Input HWC, output HWC.
 * Output dims = floor(input / 2). */
static void maxpool_2x2(const float *input, float *output,
                        int H_in, int W_in, int C)
{
    int H_out = H_in / 2;
    int W_out = W_in / 2;
    for (int oh = 0; oh < H_out; ++oh) {
        for (int ow = 0; ow < W_out; ++ow) {
            for (int c = 0; c < C; ++c) {
                const int ih = oh * 2;
                const int iw = ow * 2;
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

/* Per-image symmetric quantization to INT16 range, returned as INT32
 * (matches emit_sweep_fixture's act_scale = max(abs(act)) / 32767 path).
 * Returns the scale factor (caller needs it for downstream dequantization
 * arithmetic). */
static float quantize_to_int32(const float *buf, int32_t *out, int n)
{
    float max_abs = 0.0f;
    for (int i = 0; i < n; ++i) {
        float a = buf[i];
        if (a < 0.0f) a = -a;
        if (a > max_abs) max_abs = a;
    }
    if (max_abs <= 0.0f) {
        for (int i = 0; i < n; ++i) out[i] = 0;
        return 1.0f;
    }
    float scale = max_abs / 32767.0f;
    float inv_scale = 1.0f / scale;
    for (int i = 0; i < n; ++i) {
        float q = buf[i] * inv_scale;
        /* Round to nearest, ties away from zero — matches np.round default. */
        int32_t qi = (int32_t)(q >= 0.0f ? q + 0.5f : q - 0.5f);
        if (qi >  32767) qi =  32767;
        if (qi < -32768) qi = -32768;
        out[i] = qi;
    }
    return scale;
}

/* mnist_weights_scale.h provides fc1/fc2 bias arrays + FC scale factors. */
#include "../../cnn_eval/mnist_weights_scale.h"

/* FC1 dequantize + bias + ReLU + per-image requantize. Matches
 * emit_sweep_fixture.py lines 107-112:
 *   fc1_float = fc1_acc * (act400_scale * sf1) + bias_q * sf1
 *   fc1_relu  = max(0, fc1_float)
 *   act64_scale = max(abs(fc1_relu)) / 32767
 *   act64_i32   = round(fc1_relu / act64_scale) as int16-range int32
 * Returns act64_scale (caller forwards to FC2 dequant). */
static float fc1_post_process(const int32_t fc1_acc[ARM_FC1_N_OUT],
                              float act400_scale,
                              int32_t act64[ARM_FC2_N_IN])
{
    float fc1_relu[ARM_FC1_N_OUT];
    const float sf1   = MNIST_FC1_SCALE_W_F;
    const float scale = act400_scale * sf1;
    for (int n = 0; n < ARM_FC1_N_OUT; ++n) {
        float fc1_float = (float)fc1_acc[n] * scale
                        + (float)mnist_fc1_bias_q[n] * sf1;
        fc1_relu[n] = (fc1_float > 0.0f) ? fc1_float : 0.0f;
    }
    return quantize_to_int32(fc1_relu, act64, ARM_FC1_N_OUT);
}

/* FC2 dequantize + bias (no ReLU). Argmax is scale-invariant so the
 * caller can argmax directly on the returned floats. */
static int fc2_post_argmax(const int32_t fc2_acc[ARM_FC2_N_OUT],
                           float act64_scale)
{
    float fc2_float[ARM_FC2_N_OUT];
    const float sf2   = MNIST_FC2_SCALE_W_F;
    const float scale = act64_scale * sf2;
    for (int n = 0; n < ARM_FC2_N_OUT; ++n) {
        fc2_float[n] = (float)fc2_acc[n] * scale
                     + (float)mnist_fc2_bias_q[n] * sf2;
    }
    int best = 0;
    for (int i = 1; i < ARM_FC2_N_OUT; ++i)
        if (fc2_float[i] > fc2_float[best]) best = i;
    return best;
}

int arm_cnn_run(const uint8_t input_uint8[ARM_CNN_INPUT_N],
                const uint32_t fc1_w[ARM_FC1_N_OUT * ARM_FC1_N_IN],
                const uint32_t fc2_w[ARM_FC2_N_OUT * ARM_FC2_N_IN],
                int32_t out_act400[ARM_FC1_N_IN])
{
    load_weights();

    normalize_input(input_uint8, buf_normalized);

    conv2d(buf_normalized, c1_w_f, c1_b_f, buf_conv1_out,
           C1_IN_H, C1_IN_W, C1_IN_C, C1_OUT_H, C1_OUT_W, C1_OUT_C,
           C1_KH, C1_KW);
    relu_inplace(buf_conv1_out, C1_OUT_H * C1_OUT_W * C1_OUT_C);
    maxpool_2x2(buf_conv1_out, buf_pool1_out, C1_OUT_H, C1_OUT_W, C1_OUT_C);

    conv2d(buf_pool1_out, c2_w_f, c2_b_f, buf_conv2_out,
           C2_IN_H, C2_IN_W, C2_IN_C, C2_OUT_H, C2_OUT_W, C2_OUT_C,
           C2_KH, C2_KW);
    relu_inplace(buf_conv2_out, C2_OUT_H * C2_OUT_W * C2_OUT_C);
    maxpool_2x2(buf_conv2_out, buf_pool2_out, C2_OUT_H, C2_OUT_W, C2_OUT_C);

    /* Transpose pool2 output from HWC to CHW before flattening — PyTorch's
     * F.max_pool2d returns [N, C, H, W] and .reshape(-1) flattens in CHW
     * order. The FC1 weights were trained against THAT order. Without
     * this transpose, the 400 inputs to FC1 are permuted and the dot
     * products are nonsense (caught by image-0 debug: act400[0] matched
     * but act400[1..] diverged, see emit_sweep_fixture comparison). */
    float buf_pool2_chw[P2_OUT_N];
    for (int c = 0; c < C2_OUT_C; ++c) {
        for (int h = 0; h < P2_OUT_H; ++h) {
            for (int w = 0; w < P2_OUT_W; ++w) {
                int hwc = ((size_t)h * P2_OUT_W + w) * C2_OUT_C + c;
                int chw = ((size_t)c * P2_OUT_H + h) * P2_OUT_W + w;
                buf_pool2_chw[chw] = buf_pool2_out[hwc];
            }
        }
    }

    /* Quantize 400-element float feature map to int32 (sweep_act400 format).
     * Track act400_scale — FC1 post-processing needs it for the dequant. */
    int32_t act400[ARM_FC1_N_IN];
    float act400_scale = quantize_to_int32(buf_pool2_chw, act400, ARM_FC1_N_IN);
    if (out_act400) memcpy(out_act400, act400, sizeof(act400));

    /* FC1 int MAC + dequant/bias/ReLU/requant. */
    int32_t fc1_acc[ARM_FC1_N_OUT];
    arm_fc1_64x400(act400, fc1_w, fc1_acc);
    int32_t act64[ARM_FC2_N_IN];
    float act64_scale = fc1_post_process(fc1_acc, act400_scale, act64);

    /* FC2 int MAC + dequant/bias + argmax (no ReLU on logits). */
    int32_t fc2_acc[ARM_FC2_N_OUT];
    arm_fc2_10x64(act64, fc2_w, fc2_acc);
    return fc2_post_argmax(fc2_acc, act64_scale);
}
