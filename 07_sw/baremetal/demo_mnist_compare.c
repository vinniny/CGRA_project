/* demo_mnist_compare.c — UART head-to-head for the MNIST CNN:
 *   CGRA path        — cnn_full_inference   (Conv+Pool on CGRA + FC)
 *   ARM-VFP path     — arm_cnn_vfp_run      (Cortex-A9 VFPv3 floats)
 *   ARM-INT path     — arm_cnn_int_run      (scalar INT16 MAC, no FP/SIMD)
 *
 * The INT path is the apples-to-apples baseline for the thesis abstract's
 * "8-12 FPS ARM-only" claim: zero VFP, zero NEON, plain integer scalar.
 * The VFP path is the honest "modern default compiler" asterisk. All
 * three feed the SAME CGRA FC1/FC2 chains for the final argmax so only
 * the Conv+Pool half varies between paths. */

#include "uart.h"
#include "cgra.h"
#include "cgra_kernels_cnn.h"
#include "cnn_conv_bm.h"
#include "arm_cnn_bm.h"
#include "arm_cnn_int_bm.h"
#include "mnist_sweep_fixture.h"
#include "../cnn_eval/mnist_weights_scale.h"

extern const uint32_t cnn_spm_start[];

#ifndef N_TEST
#define N_TEST  5
#endif

#define ACT400_DDR  0x00220000UL
#define ACT64_DDR   0x00221000UL

static void fc1_post_process(const int32_t fc1_acc[64],
                             int32_t act64_out[64])
{
    int32_t tmp[64];
    int32_t max_abs = 0;
    for (int n = 0; n < 64; ++n) {
        int64_t s = (int64_t)fc1_acc[n] + (int64_t)mnist_fc1_bias_q[n];
        if (s < 0) s = 0;
        if (s > 0x7FFFFFFFLL) s = 0x7FFFFFFFLL;
        tmp[n] = (int32_t)s;
        if (tmp[n] > max_abs) max_abs = tmp[n];
    }
    int shift = 0;
    while ((max_abs >> shift) > 32767 && shift < 31) shift++;
    for (int n = 0; n < 64; ++n) act64_out[n] = tmp[n] >> shift;
}

static int argmax_with_bias(const int32_t fc2_acc[10])
{
    int32_t v[10];
    for (int i = 0; i < 10; ++i)
        v[i] = fc2_acc[i] + mnist_fc2_bias_q[i];
    int best = 0;
    for (int i = 1; i < 10; ++i) if (v[i] > v[best]) best = i;
    return best;
}

/* Run FC1 + FC1-post + FC2 + argmax on the CGRA given the act400 input.
 * Returns the predicted class (0-9) or -1 on CGRA error. */
static int run_fc_path(const int32_t act400[400])
{
    volatile int32_t *act400_ddr = (volatile int32_t *)ACT400_DDR;
    for (int j = 0; j < 400; ++j) act400_ddr[j] = act400[j];
    asm volatile("dsb" ::: "memory");

    if (cnn_fc1_tile_preload(ACT400_DDR)) return -1;
    int32_t fc1_acc[64];
    for (int g = 0; g < (int)CNN_FC1_N_GROUPS; ++g) {
        int32_t grp[4];
        if (cnn_fc1_run_group(g, grp)) return -1;
        for (int r = 0; r < 4; ++r) fc1_acc[g*4 + r] = grp[r];
    }
    int32_t act64[64];
    fc1_post_process(fc1_acc, act64);

    volatile int32_t *act64_ddr = (volatile int32_t *)ACT64_DDR;
    for (int j = 0; j < 64; ++j) act64_ddr[j] = act64[j];
    asm volatile("dsb" ::: "memory");

    if (cnn_fc2_tile_preload(ACT64_DDR)) return -1;
    int32_t fc2_acc[12];
    for (int g = 0; g < (int)CNN_FC2_N_GROUPS; ++g) {
        int32_t grp[4];
        if (cnn_fc2_run_group(g, grp)) return -1;
        for (int r = 0; r < 4 && g*4+r < 10; ++r) fc2_acc[g*4+r] = grp[r];
    }
    return argmax_with_bias(fc2_acc);
}

int main(void)
{
    uart_init();
    uart_puts("\n=== MNIST 3-way compare (CGRA / ARM-VFP / ARM-scalar) ===\n");
    uart_puts("Images: "); uart_putdec((uint32_t)N_TEST); uart_putchar('\n');

    arm_pmu_enable();
    arm_ccnt_reset();

    /* Build FC1+FC2 chains once. */
    uint32_t fc1_w_ddr = (uint32_t)(uintptr_t)cnn_spm_start;
    uint32_t fc2_w_ddr = fc1_w_ddr + CNN_FC1_N_OUTPUTS * CNN_FC1_SPM_BPN;
    if (cnn_fc1_build_chains(fc1_w_ddr) || cnn_fc2_build_chains(fc2_w_ddr)) {
        uart_puts("FAIL: FC chain build\n"); for(;;);
    }

    int correct_cgra = 0, correct_vfp = 0, correct_int = 0;
    uint32_t total_cgra = 0, total_vfp = 0, total_int = 0;

    for (int i = 0; i < N_TEST; ++i) {
        int32_t act400[400];
        uint32_t t0, t1;
        int pred_cgra, pred_vfp, pred_int;
        int label = (int)sweep_labels[i];

        /* ---- CGRA path ---- */
        t0 = arm_ccnt_read();
        if (cnn_full_inference(sweep_input28[i], act400) < 0) {
            uart_puts("FAIL: CGRA Conv\n"); for(;;);
        }
        pred_cgra = run_fc_path(act400);
        t1 = arm_ccnt_read();
        total_cgra += (t1 - t0);
        if (pred_cgra == label) correct_cgra++;

        /* ---- ARM-VFP path ---- */
        t0 = arm_ccnt_read();
        arm_cnn_vfp_run(sweep_input28[i], act400);
        pred_vfp = run_fc_path(act400);
        t1 = arm_ccnt_read();
        total_vfp += (t1 - t0);
        if (pred_vfp == label) correct_vfp++;

        /* ---- ARM-INT scalar path (no VFP, no NEON) ---- */
        t0 = arm_ccnt_read();
        arm_cnn_int_run(sweep_input28[i], act400);
        pred_int = run_fc_path(act400);
        t1 = arm_ccnt_read();
        total_int += (t1 - t0);
        if (pred_int == label) correct_int++;

        uart_puts(" img ");
        uart_putdec((uint32_t)i);
        uart_puts(" lbl=");
        uart_putdec((uint32_t)label);
        uart_puts("  cgra=");
        uart_putdec((uint32_t)pred_cgra);
        uart_puts(" vfp=");
        uart_putdec((uint32_t)pred_vfp);
        uart_puts(" int=");
        uart_putdec((uint32_t)pred_int);
        uart_putchar('\n');
    }

    uart_puts("\n=== Summary ===\n");
    uart_puts("Accuracy  CGRA:    "); uart_putdec((uint32_t)correct_cgra);
    uart_putchar('/'); uart_putdec((uint32_t)N_TEST); uart_putchar('\n');
    uart_puts("Accuracy  ARMVFP:  "); uart_putdec((uint32_t)correct_vfp);
    uart_putchar('/'); uart_putdec((uint32_t)N_TEST); uart_putchar('\n');
    uart_puts("Accuracy  ARMINT:  "); uart_putdec((uint32_t)correct_int);
    uart_putchar('/'); uart_putdec((uint32_t)N_TEST); uart_putchar('\n');

    uart_puts("Cycles/img CGRA:   0x"); uart_puthex(total_cgra / (uint32_t)N_TEST); uart_putchar('\n');
    uart_puts("Cycles/img ARMVFP: 0x"); uart_puthex(total_vfp  / (uint32_t)N_TEST); uart_putchar('\n');
    uart_puts("Cycles/img ARMINT: 0x"); uart_puthex(total_int  / (uint32_t)N_TEST); uart_putchar('\n');
    uart_drain();
    for(;;);
    return 0;
}
