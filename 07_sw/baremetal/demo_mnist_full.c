/* demo_mnist_full.c — B4 end-to-end MNIST on CGRA (Conv1+Pool1+Conv2+Pool2+FC1+FC2).
 *
 * Validates the FULL CNN inference path running on the CGRA in bare-metal:
 *   - Conv1+Conv2 use pixel-by-pixel cnn_conv3x3_pixel calls.
 *   - Pool/ReLU/quantize are on ARM (small data, no CGRA benefit).
 *   - FC1+FC2 reuse the existing silicon-validated cnn_fc{1,2}_* path.
 *
 * Goals:
 *   1. Argmax matches sweep_labels for >= 70% of images (pixel-by-pixel
 *      will accumulate some scale-drift; FC reuses the same INT-MAC math
 *      as the fixture so its part is bit-exact).
 *   2. Print per-image cycle breakdown:
 *      total = conv_pool_cycles + fc_cycles + arm_overhead
 *
 * NOTE: This is the simple pixel-by-pixel kernel. It will be SLOW
 * (~590 ms/image estimated). Optimisation to TILE_AUTO_INC sliding
 * window is the next step (B4 phase 2).
 */
#include "uart.h"
#include "cgra.h"
#include "cgra_kernels_cnn.h"
#include "cnn_conv_bm.h"
#include "mnist_sweep_fixture.h"
#include "../cnn_eval/mnist_weights_scale.h"

extern const uint32_t cnn_spm_start[];

#define N_TEST  5   /* small initial sweep — bump to 100 once validated */

#define ACT400_DDR  0x00220000UL
#define ACT64_DDR   0x00221000UL

/* FC1 post-processing: int32 MAC + bias + ReLU + right-shift to INT16 range.
 * Uses mnist_fc1_bias_q[] from the cnn_eval header. */
static void fc1_post_process(const int32_t fc1_acc[64],
                             int32_t act64_out[64])
{
    int32_t tmp[64];
    int32_t max_abs = 0;
    for (int n = 0; n < 64; ++n) {
        int64_t s = (int64_t)fc1_acc[n] + (int64_t)mnist_fc1_bias_q[n];
        if (s < 0) s = 0;                          /* ReLU */
        if (s > 0x7FFFFFFFLL) s = 0x7FFFFFFFLL;
        tmp[n] = (int32_t)s;
        if (tmp[n] > max_abs) max_abs = tmp[n];
    }
    int shift = 0;
    while ((max_abs >> shift) > 32767 && shift < 31) shift++;
    for (int n = 0; n < 64; ++n) act64_out[n] = tmp[n] >> shift;
}

static int argmax_with_bias_10(const int32_t fc2_acc[10])
{
    int32_t v[10];
    for (int i = 0; i < 10; ++i)
        v[i] = fc2_acc[i] + mnist_fc2_bias_q[i];
    int best = 0;
    for (int i = 1; i < 10; ++i) if (v[i] > v[best]) best = i;
    return best;
}

int main(void)
{
    uart_init();
    uart_puts("\n=== B4 bare-metal full CNN on CGRA (");
    uart_putdec((uint32_t)N_TEST);
    uart_puts(" images) ===\n");

    arm_pmu_enable();
    arm_ccnt_reset();

    /* Set up FC1+FC2 chains (one-time). */
    uint32_t fc1_w_ddr = (uint32_t)(uintptr_t)cnn_spm_start;
    uint32_t fc2_w_ddr = fc1_w_ddr + CNN_FC1_N_OUTPUTS * CNN_FC1_SPM_BPN;
    uart_puts("Building FC1+FC2 chains...\n");
    if (cnn_fc1_build_chains(fc1_w_ddr) || cnn_fc2_build_chains(fc2_w_ddr)) {
        uart_puts("FAIL: chain build\n"); for (;;);
    }

    int correct = 0;
    uint32_t total_conv_cycles = 0;
    uint32_t total_fc_cycles   = 0;

    for (int i = 0; i < N_TEST; ++i) {
        int32_t act400[400];
        int32_t fc1_acc[64];
        int32_t act64[64];
        int32_t fc2_acc[12];   /* 3 groups × 4 = 12 slots, last 2 unused */

        /* ---- Conv1+Pool1+Conv2+Pool2 on CGRA + ARM ---- */
        uint32_t t0 = arm_ccnt_read();
        if (cnn_full_inference(sweep_input28[i], act400) < 0) {
            uart_puts("FAIL: cnn_full_inference\n"); for(;;);
        }
        uint32_t t1 = arm_ccnt_read();
        total_conv_cycles += (t1 - t0);

        /* ---- FC1 + post + FC2 on CGRA ---- */
        volatile int32_t *act400_ddr = (volatile int32_t *)ACT400_DDR;
        for (int j = 0; j < 400; ++j) act400_ddr[j] = act400[j];
        asm volatile("dsb" ::: "memory");

        t0 = arm_ccnt_read();
        if (cnn_fc1_tile_preload(ACT400_DDR)) { uart_puts("FC1 preload fail\n"); for(;;); }
        for (int g = 0; g < (int)CNN_FC1_N_GROUPS; ++g) {
            int32_t grp[4];
            if (cnn_fc1_run_group(g, grp)) { uart_puts("FC1 group fail\n"); for(;;); }
            for (int r = 0; r < 4; ++r) fc1_acc[g*4 + r] = grp[r];
        }
        fc1_post_process(fc1_acc, act64);

        volatile int32_t *act64_ddr = (volatile int32_t *)ACT64_DDR;
        for (int j = 0; j < 64; ++j) act64_ddr[j] = act64[j];
        asm volatile("dsb" ::: "memory");

        if (cnn_fc2_tile_preload(ACT64_DDR)) { uart_puts("FC2 preload fail\n"); for(;;); }
        for (int g = 0; g < (int)CNN_FC2_N_GROUPS; ++g) {
            int32_t grp[4];
            if (cnn_fc2_run_group(g, grp)) { uart_puts("FC2 group fail\n"); for(;;); }
            for (int r = 0; r < 4 && g*4+r < 10; ++r) fc2_acc[g*4+r] = grp[r];
        }
        t1 = arm_ccnt_read();
        total_fc_cycles += (t1 - t0);

        int pred = argmax_with_bias_10(fc2_acc);
        int label = (int)sweep_labels[i];
        if (pred == label) correct++;

        uart_puts(" img ");
        uart_putdec((uint32_t)i);
        uart_puts(": pred=");
        uart_putdec((uint32_t)pred);
        uart_puts(" lbl=");
        uart_putdec((uint32_t)label);
        if (pred == label) uart_puts(" OK\n"); else uart_puts(" MISS\n");
    }

    uart_puts("\n=== results ===\n");
    uart_puts("Accuracy (CGRA full CNN) : ");
    uart_putdec((uint32_t)correct); uart_putchar('/'); uart_putdec((uint32_t)N_TEST);
    uart_putchar('\n');
    uart_puts("Total Conv+Pool cycles   : 0x"); uart_puthex(total_conv_cycles); uart_putchar('\n');
    uart_puts("Total FC1+FC2 cycles     : 0x"); uart_puthex(total_fc_cycles);   uart_putchar('\n');
    uart_puts("Per-img Conv avg cycles  : 0x"); uart_puthex(total_conv_cycles / (uint32_t)N_TEST); uart_putchar('\n');
    uart_puts("Per-img FC avg cycles    : 0x"); uart_puthex(total_fc_cycles   / (uint32_t)N_TEST); uart_putchar('\n');
    uart_drain();
    for (;;);
    return 0;
}
