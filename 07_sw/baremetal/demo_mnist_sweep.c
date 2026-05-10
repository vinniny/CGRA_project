/* demo_mnist_sweep.c — N-image MNIST sweep on CGRA FC1+FC2.
 *
 * For each image: load act400 → run HW FC1, load act64 → run HW FC2,
 * argmax → compare against (label, golden_pred).
 * Report HW-vs-label, golden-vs-label, HW-vs-golden agreement.
 */

#include "uart.h"
#include "cgra.h"
#include "cgra_kernels_cnn.h"
#include "mnist_sweep_fixture.h"

extern const uint32_t cnn_spm_start[];

#define ACT400_DDR 0x00220000UL
#define ACT64_DDR  0x00221000UL

static int run_image(int idx, int32_t fc2_out[10])
{
    volatile int32_t *act400 = (volatile int32_t *)ACT400_DDR;
    volatile int32_t *act64  = (volatile int32_t *)ACT64_DDR;

    for (int i = 0; i < 400; i++) act400[i] = sweep_act400[idx][i];
    for (int i = 0; i <  64; i++) act64[i]  = sweep_act64[idx][i];
    asm volatile("dsb" ::: "memory");

    if (cnn_fc1_tile_preload(ACT400_DDR)) return -1;
    int32_t fc1_dummy[4];
    for (int g = 0; g < (int)CNN_FC1_N_GROUPS; g++)
        if (cnn_fc1_run_group(g, fc1_dummy)) return -1;

    if (cnn_fc2_tile_preload(ACT64_DDR)) return -1;
    int32_t buf[12];
    for (int g = 0; g < (int)CNN_FC2_N_GROUPS; g++) {
        int32_t grp[4];
        if (cnn_fc2_run_group(g, grp)) return -1;
        for (int r = 0; r < 4 && g * 4 + r < (int)CNN_FC2_N_OUTPUTS; r++)
            buf[g * 4 + r] = grp[r];
    }
    for (int i = 0; i < 10; i++) fc2_out[i] = buf[i];
    return 0;
}

int main(void)
{
    uart_init();
    uart_puts("\n=== MNIST sweep (");
    uart_putdec((uint32_t)SWEEP_N_IMAGES);
    uart_puts(" images) ===\n");

    arm_pmu_enable();

    uint32_t fc1_w_ddr = (uint32_t)(uintptr_t)cnn_spm_start;
    uint32_t fc2_w_ddr = fc1_w_ddr + CNN_FC1_N_OUTPUTS * CNN_FC1_SPM_BPN;
    if (cnn_fc1_build_chains(fc1_w_ddr) || cnn_fc2_build_chains(fc2_w_ddr)) {
        uart_puts("FAIL: chain build\n"); for (;;);
    }

    int hw_correct = 0, gold_correct = 0, hw_eq_gold = 0, errors = 0;

    arm_ccnt_reset();
    uint32_t t0 = arm_ccnt_read();

    for (int i = 0; i < SWEEP_N_IMAGES; i++) {
        int32_t fc2[10];
        if (run_image(i, fc2)) { errors++; continue; }

        int hw_pred = 0;
        for (int j = 1; j < 10; j++)
            if (fc2[j] > fc2[hw_pred]) hw_pred = j;

        int label = sweep_labels[i];
        int gold  = sweep_golden[i];
        if (hw_pred == label) hw_correct++;
        if (gold    == label) gold_correct++;
        if (hw_pred == gold)  hw_eq_gold++;

        if ((i & 0xF) == 0) {
            uart_puts(" [");
            uart_putdec((uint32_t)i);
            uart_puts("] hw=");
            uart_putdec((uint32_t)hw_pred);
            uart_puts(" gold=");
            uart_putdec((uint32_t)gold);
            uart_puts(" lbl=");
            uart_putdec((uint32_t)label);
            uart_putchar('\n');
        }
    }
    uint32_t t1 = arm_ccnt_read();

    uart_puts("\n=== Sweep results ===\n");
    uart_puts("HW vs label    : ");
    uart_putdec((uint32_t)hw_correct);
    uart_putchar('/');
    uart_putdec((uint32_t)SWEEP_N_IMAGES);
    uart_putchar('\n');
    uart_puts("Golden vs label: ");
    uart_putdec((uint32_t)gold_correct);
    uart_putchar('/');
    uart_putdec((uint32_t)SWEEP_N_IMAGES);
    uart_putchar('\n');
    uart_puts("HW vs golden   : ");
    uart_putdec((uint32_t)hw_eq_gold);
    uart_putchar('/');
    uart_putdec((uint32_t)SWEEP_N_IMAGES);
    uart_putchar('\n');
    uart_puts("Errors         : ");
    uart_putdec((uint32_t)errors);
    uart_putchar('\n');
    uart_puts("Total cycles   : 0x");
    uart_puthex(t1 - t0);
    uart_puts(" (CCNT delta)\n");
    uart_drain();
    for (;;);
    return 0;
}
