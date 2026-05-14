/* demo_mnist_per_stage.c — per-stage cycle accounting for Table 5.6.
 *
 * Runs the full MNIST pipeline (Conv1+ReLU+Pool1, Conv2+ReLU+Pool2,
 * quantize, FC1, FC2, argmax) over the 100-image sweep with PMCCNTR
 * boundaries around each stage. FC1/FC2 are timed twice per image:
 *
 *   SW-only path  : arm_fc_int_bm.c (INT64 acc scalar)
 *   HW-accel path : cnn_fc{1,2}_run_group() on the 4×4 CGRA mesh
 *
 * The convolutional front-end is identical in both paths (ARM-VFP); we
 * report it once.  Averages are printed as hex cycle counts at the end;
 * convert to ms with cycles / 666_000 at 666 MHz. */

#include "uart.h"
#include "cgra.h"
#include "cgra_kernels_cnn.h"
#include "mnist_sweep_fixture.h"
#include "../cnn_eval/mnist_weights_scale.h"
#include "arm_fc_bm.h"
#include "arm_cnn_int_bm.h"

#include <stdint.h>
#include <stddef.h>

extern const uint32_t cnn_spm_start[];
extern const uint8_t  cnn_conv_start[];

#define N_TEST           100

#define ACT400_DDR       0x00220000UL
#define ACT64_DDR        0x00221000UL

#define CONV1_SCALE_W    0.00003041f
#define CONV2_SCALE_W    0.00004060f

#define C1_OUT_C   8
#define C1_IN_C    1
#define C1_KH      3
#define C1_KW      3
#define C1_IN_H    28
#define C1_IN_W    28
#define C1_OUT_H   (C1_IN_H - C1_KH + 1)   /* 26 */
#define C1_OUT_W   (C1_IN_W - C1_KW + 1)
#define P1_OUT_H   (C1_OUT_H / 2)          /* 13 */
#define P1_OUT_W   (C1_OUT_W / 2)

#define C2_OUT_C   16
#define C2_IN_C    C1_OUT_C
#define C2_KH      3
#define C2_KW      3
#define C2_IN_H    P1_OUT_H
#define C2_IN_W    P1_OUT_W
#define C2_OUT_H   (C2_IN_H - C2_KH + 1)   /* 11 */
#define C2_OUT_W   (C2_IN_W - C2_KW + 1)
#define P2_OUT_H   (C2_OUT_H / 2)          /* 5 */
#define P2_OUT_W   (C2_OUT_W / 2)
#define P2_OUT_N   (P2_OUT_H * P2_OUT_W * C2_OUT_C)  /* 400 */

#define FC1_N_IN   400
#define FC1_N_OUT   64
#define FC2_N_IN    64
#define FC2_N_OUT   10
#define FC1_W_WORDS (FC1_N_OUT * FC1_N_IN)

static float buf_normalized[C1_IN_H * C1_IN_W];
static float buf_conv1_out [C1_OUT_H * C1_OUT_W * C1_OUT_C];
static float buf_pool1_out [P1_OUT_H * P1_OUT_W * C1_OUT_C];
static float buf_conv2_out [C2_OUT_H * C2_OUT_W * C2_OUT_C];
static float buf_pool2_out [P2_OUT_N];
static float buf_pool2_chw [P2_OUT_N];

static float c1_w_f[C1_OUT_C * C1_KH * C1_KW * C1_IN_C];
static float c1_b_f[C1_OUT_C];
static float c2_w_f[C2_OUT_C * C2_KH * C2_KW * C2_IN_C];
static float c2_b_f[C2_OUT_C];

static void load_weights(void)
{
    const int16_t *c1_w_i16 = (const int16_t *)cnn_conv_start;
    const int32_t *c1_b_i32 = (const int32_t *)(cnn_conv_start + 144);
    const int16_t *c2_w_i16 = (const int16_t *)(cnn_conv_start + 176);
    const int32_t *c2_b_i32 = (const int32_t *)(cnn_conv_start + 2480);
    for (size_t i = 0; i < sizeof(c1_w_f) / sizeof(c1_w_f[0]); ++i)
        c1_w_f[i] = (float)c1_w_i16[i] * CONV1_SCALE_W;
    for (int i = 0; i < C1_OUT_C; ++i)
        c1_b_f[i] = (float)c1_b_i32[i] * CONV1_SCALE_W;
    for (size_t i = 0; i < sizeof(c2_w_f) / sizeof(c2_w_f[0]); ++i)
        c2_w_f[i] = (float)c2_w_i16[i] * CONV2_SCALE_W;
    for (int i = 0; i < C2_OUT_C; ++i)
        c2_b_f[i] = (float)c2_b_i32[i] * CONV2_SCALE_W;
}

static void normalize_input(const uint8_t *src, float *dst)
{
    const float inv255 = 1.0f / 255.0f;
    const float mean   = 0.1307f;
    const float stdinv = 1.0f / 0.3081f;
    for (int i = 0; i < C1_IN_H * C1_IN_W; ++i)
        dst[i] = ((float)src[i] * inv255 - mean) * stdinv;
}

static void conv2d(const float *input, const float *weights,
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

static void relu_inplace(float *buf, int n)
{
    for (int i = 0; i < n; ++i) if (buf[i] < 0.0f) buf[i] = 0.0f;
}

static void maxpool_2x2(const float *input, float *output,
                        int H_in, int W_in, int C)
{
    int H_out = H_in / 2, W_out = W_in / 2;
    for (int oh = 0; oh < H_out; ++oh) {
        for (int ow = 0; ow < W_out; ++ow) {
            for (int c = 0; c < C; ++c) {
                int ih = oh * 2, iw = ow * 2;
                float a  = input[((size_t)(ih    ) * W_in + iw    ) * C + c];
                float b  = input[((size_t)(ih    ) * W_in + iw + 1) * C + c];
                float cc = input[((size_t)(ih + 1) * W_in + iw    ) * C + c];
                float d  = input[((size_t)(ih + 1) * W_in + iw + 1) * C + c];
                float m = a;
                if (b  > m) m = b;
                if (cc > m) m = cc;
                if (d  > m) m = d;
                output[((size_t)oh * W_out + ow) * C + c] = m;
            }
        }
    }
}

static void chw_quantize(const float *buf_hwc, int32_t *out)
{
    for (int c = 0; c < C2_OUT_C; ++c)
        for (int h = 0; h < P2_OUT_H; ++h)
            for (int w = 0; w < P2_OUT_W; ++w) {
                int hwc = ((size_t)h * P2_OUT_W + w) * C2_OUT_C + c;
                int chw = ((size_t)c * P2_OUT_H + h) * P2_OUT_W + w;
                buf_pool2_chw[chw] = buf_hwc[hwc];
            }
    float max_abs = 0.0f;
    for (int i = 0; i < P2_OUT_N; ++i) {
        float a = buf_pool2_chw[i];
        if (a < 0.0f) a = -a;
        if (a > max_abs) max_abs = a;
    }
    if (max_abs <= 0.0f) {
        for (int i = 0; i < P2_OUT_N; ++i) out[i] = 0;
        return;
    }
    float inv_scale = 32767.0f / max_abs;
    for (int i = 0; i < P2_OUT_N; ++i) {
        float q = buf_pool2_chw[i] * inv_scale;
        int32_t qi = (int32_t)(q >= 0.0f ? q + 0.5f : q - 0.5f);
        if (qi >  32767) qi =  32767;
        if (qi < -32768) qi = -32768;
        out[i] = qi;
    }
}

/* ── ARM-INT FC implementations (split into FC1 / FC2 / argmax stages) ── */
static inline int32_t spm_int16(uint32_t word)
{
    return (int32_t)(int16_t)(word & 0xFFFFu);
}
static inline int32_t sat_i32(int64_t v)
{
    if (v >  (int64_t)0x7FFFFFFFLL) return  (int32_t)0x7FFFFFFF;
    if (v < -(int64_t)0x80000000LL) return (int32_t)0x80000000;
    return (int32_t)v;
}

static void arm_int_fc1(const int32_t act400[FC1_N_IN], int32_t fc1_acc[FC1_N_OUT])
{
    const uint32_t *fc1_w = cnn_spm_start;
    for (int n = 0; n < FC1_N_OUT; ++n) {
        const uint32_t *w_row = fc1_w + (size_t)n * FC1_N_IN;
        int64_t acc = 0;
        for (int i = 0; i < FC1_N_IN; ++i)
            acc += (int64_t)act400[i] * (int64_t)spm_int16(w_row[i]);
        fc1_acc[n] = sat_i32(acc);
    }
}

static void fc1_post_process(const int32_t fc1_acc[FC1_N_OUT], int32_t act64[FC1_N_OUT])
{
    int32_t tmp[FC1_N_OUT];
    int32_t max_abs = 0;
    for (int n = 0; n < FC1_N_OUT; ++n) {
        int64_t s = (int64_t)fc1_acc[n] + (int64_t)mnist_fc1_bias_q[n];
        if (s < 0) s = 0;
        if (s > 0x7FFFFFFFLL) s = 0x7FFFFFFFLL;
        tmp[n] = (int32_t)s;
        if (tmp[n] > max_abs) max_abs = tmp[n];
    }
    int shift = 0;
    while ((max_abs >> shift) > 32767 && shift < 31) shift++;
    for (int n = 0; n < FC1_N_OUT; ++n) act64[n] = tmp[n] >> shift;
}

static void arm_int_fc2(const int32_t act64[FC2_N_IN], int32_t fc2_acc[FC2_N_OUT])
{
    const uint32_t *fc2_w = cnn_spm_start + FC1_W_WORDS;
    for (int n = 0; n < FC2_N_OUT; ++n) {
        const uint32_t *w_row = fc2_w + (size_t)n * FC2_N_IN;
        int64_t acc = 0;
        for (int i = 0; i < FC2_N_IN; ++i)
            acc += (int64_t)act64[i] * (int64_t)spm_int16(w_row[i]);
        fc2_acc[n] = sat_i32(acc);
    }
}

static int argmax_with_bias(const int32_t fc2_acc[FC2_N_OUT])
{
    int32_t v[FC2_N_OUT];
    for (int i = 0; i < FC2_N_OUT; ++i)
        v[i] = fc2_acc[i] + mnist_fc2_bias_q[i];
    int best = 0;
    for (int i = 1; i < FC2_N_OUT; ++i) if (v[i] > v[best]) best = i;
    return best;
}

static void put_hex_field(const char *lbl, uint64_t cyc_sum)
{
    uint32_t avg = (uint32_t)(cyc_sum / (uint64_t)N_TEST);
    uart_puts(lbl); uart_puts(" 0x"); uart_puthex(avg); uart_putchar('\n');
}

int main(void)
{
    uart_init();
    uart_puts("\n=== Table 5.6 per-stage measurement (N=");
    uart_putdec((uint32_t)N_TEST);
    uart_puts(" images) ===\n");

    arm_pmu_enable();
    arm_ccnt_reset();

    load_weights();

    uint32_t fc1_w_ddr = (uint32_t)(uintptr_t)cnn_spm_start;
    uint32_t fc2_w_ddr = fc1_w_ddr + CNN_FC1_N_OUTPUTS * CNN_FC1_SPM_BPN;
    if (cnn_fc1_build_chains(fc1_w_ddr) || cnn_fc2_build_chains(fc2_w_ddr)) {
        uart_puts("FAIL: FC chain build\n"); for(;;);
    }

    uint64_t s_c1 = 0, s_p1 = 0, s_c2 = 0, s_p2 = 0, s_qz = 0;
    uint64_t s_cnn_int = 0;   /* ARM-INT scalar full Conv+Pool (per arm_cnn_int_run) */
    uint64_t s_fc1_int = 0, s_fc1pp_int = 0, s_fc2_int = 0, s_arg_int = 0;
    uint64_t s_fc1_cgra = 0, s_fc1pp_cgra = 0, s_fc2_cgra = 0, s_arg_cgra = 0;

    int correct_int = 0, correct_cgra = 0;

    for (int i = 0; i < N_TEST; ++i) {
        int label = (int)sweep_labels[i];
        uint32_t t0, t1;

        /* ----- Conv1+ReLU on ARM-VFP ----- */
        normalize_input(sweep_input28[i], buf_normalized);
        t0 = arm_ccnt_read();
        conv2d(buf_normalized, c1_w_f, c1_b_f, buf_conv1_out,
               C1_IN_H, C1_IN_W, C1_IN_C, C1_OUT_H, C1_OUT_W, C1_OUT_C,
               C1_KH, C1_KW);
        relu_inplace(buf_conv1_out, C1_OUT_H * C1_OUT_W * C1_OUT_C);
        t1 = arm_ccnt_read();
        s_c1 += (uint64_t)(t1 - t0);

        /* ----- Pool1 ----- */
        t0 = arm_ccnt_read();
        maxpool_2x2(buf_conv1_out, buf_pool1_out, C1_OUT_H, C1_OUT_W, C1_OUT_C);
        t1 = arm_ccnt_read();
        s_p1 += (uint64_t)(t1 - t0);

        /* ----- Conv2+ReLU ----- */
        t0 = arm_ccnt_read();
        conv2d(buf_pool1_out, c2_w_f, c2_b_f, buf_conv2_out,
               C2_IN_H, C2_IN_W, C2_IN_C, C2_OUT_H, C2_OUT_W, C2_OUT_C,
               C2_KH, C2_KW);
        relu_inplace(buf_conv2_out, C2_OUT_H * C2_OUT_W * C2_OUT_C);
        t1 = arm_ccnt_read();
        s_c2 += (uint64_t)(t1 - t0);

        /* ----- Pool2 ----- */
        t0 = arm_ccnt_read();
        maxpool_2x2(buf_conv2_out, buf_pool2_out, C2_OUT_H, C2_OUT_W, C2_OUT_C);
        t1 = arm_ccnt_read();
        s_p2 += (uint64_t)(t1 - t0);

        /* ----- HWC→CHW + INT16 quantize ----- */
        int32_t act400[FC1_N_IN];
        t0 = arm_ccnt_read();
        chw_quantize(buf_pool2_out, act400);
        t1 = arm_ccnt_read();
        s_qz += (uint64_t)(t1 - t0);

        /* ----- ARM-INT scalar full Conv+Pool (thesis-baseline ARM) ----- */
        int32_t act400_int[FC1_N_IN];
        t0 = arm_ccnt_read();
        (void)arm_cnn_int_run(sweep_input28[i], act400_int);
        t1 = arm_ccnt_read();
        s_cnn_int += (uint64_t)(t1 - t0);

        /* ===== SW-only: ARM-INT FC pipeline ===== */
        int32_t fc1_acc_i[FC1_N_OUT], act64_i[FC1_N_OUT], fc2_acc_i[FC2_N_OUT];

        t0 = arm_ccnt_read();
        arm_int_fc1(act400, fc1_acc_i);
        t1 = arm_ccnt_read();
        s_fc1_int += (uint64_t)(t1 - t0);

        t0 = arm_ccnt_read();
        fc1_post_process(fc1_acc_i, act64_i);
        t1 = arm_ccnt_read();
        s_fc1pp_int += (uint64_t)(t1 - t0);

        t0 = arm_ccnt_read();
        arm_int_fc2(act64_i, fc2_acc_i);
        t1 = arm_ccnt_read();
        s_fc2_int += (uint64_t)(t1 - t0);

        t0 = arm_ccnt_read();
        int pred_int = argmax_with_bias(fc2_acc_i);
        t1 = arm_ccnt_read();
        s_arg_int += (uint64_t)(t1 - t0);
        if (pred_int == label) correct_int++;

        /* ===== HW-accel: CGRA FC pipeline ===== */
        volatile int32_t *act400_ddr = (volatile int32_t *)ACT400_DDR;
        for (int j = 0; j < FC1_N_IN; ++j) act400_ddr[j] = act400[j];
        asm volatile("dsb" ::: "memory");

        int32_t fc1_acc_c[FC1_N_OUT], act64_c[FC1_N_OUT], fc2_acc_c[12];

        t0 = arm_ccnt_read();
        if (cnn_fc1_tile_preload(ACT400_DDR)) { uart_puts("FC1 preload fail\n"); for(;;); }
        for (int g = 0; g < (int)CNN_FC1_N_GROUPS; ++g) {
            int32_t grp[4];
            if (cnn_fc1_run_group(g, grp)) { uart_puts("FC1 group fail\n"); for(;;); }
            for (int r = 0; r < 4; ++r) fc1_acc_c[g*4 + r] = grp[r];
        }
        t1 = arm_ccnt_read();
        s_fc1_cgra += (uint64_t)(t1 - t0);

        t0 = arm_ccnt_read();
        fc1_post_process(fc1_acc_c, act64_c);
        t1 = arm_ccnt_read();
        s_fc1pp_cgra += (uint64_t)(t1 - t0);

        volatile int32_t *act64_ddr = (volatile int32_t *)ACT64_DDR;
        for (int j = 0; j < FC1_N_OUT; ++j) act64_ddr[j] = act64_c[j];
        asm volatile("dsb" ::: "memory");

        t0 = arm_ccnt_read();
        if (cnn_fc2_tile_preload(ACT64_DDR)) { uart_puts("FC2 preload fail\n"); for(;;); }
        for (int g = 0; g < (int)CNN_FC2_N_GROUPS; ++g) {
            int32_t grp[4];
            if (cnn_fc2_run_group(g, grp)) { uart_puts("FC2 group fail\n"); for(;;); }
            for (int r = 0; r < 4 && g*4+r < FC2_N_OUT; ++r) fc2_acc_c[g*4+r] = grp[r];
        }
        t1 = arm_ccnt_read();
        s_fc2_cgra += (uint64_t)(t1 - t0);

        t0 = arm_ccnt_read();
        int pred_cgra = argmax_with_bias(fc2_acc_c);
        t1 = arm_ccnt_read();
        s_arg_cgra += (uint64_t)(t1 - t0);
        if (pred_cgra == label) correct_cgra++;

        if ((i & 0xF) == 0) { uart_puts("img "); uart_putdec((uint32_t)i); uart_putchar('\n'); }
    }

    uart_puts("\n=== averages over ");
    uart_putdec((uint32_t)N_TEST);
    uart_puts(" frames (hex cycles @ 666 MHz) ===\n");

    put_hex_field("Conv1+ReLU (VFP)  :", s_c1);
    put_hex_field("Pool1      (VFP)  :", s_p1);
    put_hex_field("Conv2+ReLU (VFP)  :", s_c2);
    put_hex_field("Pool2      (VFP)  :", s_p2);
    put_hex_field("Quantize HWC->CHW :", s_qz);
    put_hex_field("CNN-INT Conv+Pool :", s_cnn_int);   /* ARM scalar INT, no VFP */
    uart_putchar('\n');
    put_hex_field("ARM-INT FC1       :", s_fc1_int);
    put_hex_field("ARM-INT FC1-post  :", s_fc1pp_int);
    put_hex_field("ARM-INT FC2       :", s_fc2_int);
    put_hex_field("ARM-INT argmax    :", s_arg_int);
    uart_putchar('\n');
    put_hex_field("CGRA   FC1        :", s_fc1_cgra);
    put_hex_field("CGRA   FC1-post   :", s_fc1pp_cgra);
    put_hex_field("CGRA   FC2        :", s_fc2_cgra);
    put_hex_field("CGRA   argmax     :", s_arg_cgra);
    uart_putchar('\n');

    /* Composite rows (for direct table fill). */
    put_hex_field("ROW Conv1+ReLU+Pool1:", s_c1 + s_p1);
    put_hex_field("ROW Conv2+ReLU+Pool2:", s_c2 + s_p2);
    put_hex_field("ROW FC1 ARM-INT     :", s_fc1_int + s_fc1pp_int);
    put_hex_field("ROW FC1 CGRA        :", s_fc1_cgra + s_fc1pp_cgra);
    put_hex_field("ROW FC2 ARM-INT     :", s_fc2_int);
    put_hex_field("ROW FC2 CGRA        :", s_fc2_cgra);
    put_hex_field("ROW argmax+post (both):", s_arg_int);
    put_hex_field("ROW FC total ARM-INT:", s_fc1_int + s_fc1pp_int + s_fc2_int + s_arg_int);
    put_hex_field("ROW FC total CGRA   :", s_fc1_cgra + s_fc1pp_cgra + s_fc2_cgra + s_arg_cgra);
    uint64_t full_sw_vfp = s_c1 + s_p1 + s_c2 + s_p2 + s_qz
                         + s_fc1_int + s_fc1pp_int + s_fc2_int + s_arg_int;
    uint64_t full_hw_vfp = s_c1 + s_p1 + s_c2 + s_p2 + s_qz
                         + s_fc1_cgra + s_fc1pp_cgra + s_fc2_cgra + s_arg_cgra;
    uint64_t full_sw_int = s_cnn_int
                         + s_fc1_int + s_fc1pp_int + s_fc2_int + s_arg_int;
    put_hex_field("ROW Full SW VFP+INT:", full_sw_vfp);
    put_hex_field("ROW Full HW VFP+CGRA:", full_hw_vfp);
    put_hex_field("ROW Full SW INT-only:", full_sw_int);  /* thesis-baseline ARM */

    uart_puts("Accuracy ARM-INT: ");  uart_putdec((uint32_t)correct_int);
    uart_putchar('/'); uart_putdec((uint32_t)N_TEST); uart_putchar('\n');
    uart_puts("Accuracy CGRA   : "); uart_putdec((uint32_t)correct_cgra);
    uart_putchar('/'); uart_putdec((uint32_t)N_TEST); uart_putchar('\n');
    uart_puts("[ARM] Demo complete\n");
    uart_puts("=== DONE ===\n");
    uart_drain();

    for (;;);
    return 0;
}
