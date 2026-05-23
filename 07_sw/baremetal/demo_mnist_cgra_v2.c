/* demo_mnist_cgra_v2.c — MNIST inference using all-16-PE FC kernels (v2).
 *
 * Runs both v1 (4-PE) and v2 (16-PE) FC kernels on the sweep fixture and
 * reports: accuracy, timing comparison, and per-group cycle breakdown.
 *
 * Build: see Makefile target mnist_cgra_v2.
 */

#include "uart.h"
#include "cgra.h"
#include "cgra_kernels_cnn.h"
#include "cgra_kernels_cnn_v2.h"
#include "mnist_sweep_fixture.h"

extern const uint32_t cnn_spm_start[];

#define ACT400_DDR   0x00220000UL
#define ACT64_DDR    0x00221000UL

/* -------------------------------------------------------------------------
 * Helpers: collect 64-element FC1 output and 10-element FC2 output.
 * For v2, result[r*4+c] = neuron g*16 + r*4 + c.
 * --------------------------------------------------------------------- */

static int run_image_v1(int idx, int32_t fc2_out[10])
{
    volatile int32_t *act400 = (volatile int32_t *)ACT400_DDR;
    volatile int32_t *act64  = (volatile int32_t *)ACT64_DDR;
    int g, r;
    int32_t fc1_out[64] = {0}, grp[4];

    for (int i = 0; i < 400; i++) act400[i] = sweep_act400[idx][i];
    for (int i = 0; i <  64; i++) act64[i]  = sweep_act64[idx][i];
    asm volatile("dsb" ::: "memory");

    if (cnn_fc1_tile_preload(ACT400_DDR)) return -1;
    for (g = 0; g < (int)CNN_FC1_N_GROUPS; g++) {
        if (cnn_fc1_run_group(g, grp)) return -1;
        for (r = 0; r < 4; r++) fc1_out[g * 4 + r] = grp[r];
    }

    if (cnn_fc2_tile_preload(ACT64_DDR)) return -1;
    for (g = 0; g < (int)CNN_FC2_N_GROUPS; g++) {
        if (cnn_fc2_run_group(g, grp)) return -1;
        for (r = 0; r < 4 && g * 4 + r < (int)CNN_FC2_N_OUTPUTS; r++)
            fc2_out[g * 4 + r] = grp[r];
    }
    return 0;
}

static int run_image_v2(int idx, int32_t fc2_out[10])
{
    volatile int32_t *act400 = (volatile int32_t *)ACT400_DDR;
    volatile int32_t *act64  = (volatile int32_t *)ACT64_DDR;
    int g, pe;
    int32_t fc1_grp[16], fc2_grp[16];

    for (int i = 0; i < 400; i++) act400[i] = sweep_act400[idx][i];
    for (int i = 0; i <  64; i++) act64[i]  = sweep_act64[idx][i];
    asm volatile("dsb" ::: "memory");

    /* FC1: broadcast activations once, then 4 groups */
    if (cnn_fc1_v2_act_preload(ACT400_DDR)) return -1;
    for (g = 0; g < (int)CNN_FC1_V2_N_GROUPS; g++) {
        if (cnn_fc1_v2_run_group(g, fc1_grp)) return -1;
        /* fc1_grp[pe] = neuron g*16+pe; discard — only argmax matters */
    }

    /* FC2: broadcast activations once, then 1 group */
    if (cnn_fc2_v2_act_preload(ACT64_DDR)) return -1;
    for (g = 0; g < (int)CNN_FC2_V2_N_GROUPS; g++) {
        if (cnn_fc2_v2_run_group(g, fc2_grp)) return -1;
        for (pe = 0; pe < 16 && g * 16 + pe < (int)CNN_FC2_V2_N_OUTPUTS; pe++)
            fc2_out[g * 16 + pe] = fc2_grp[pe];
    }
    return 0;
}

static int argmax10(const int32_t v[10])
{
    int best = 0, i;
    for (i = 1; i < 10; i++)
        if (v[i] > v[best]) best = i;
    return best;
}

int main(void)
{
    uart_init();
    uart_puts("\n=== MNIST 16-PE v2 vs 4-PE v1 (");
    uart_putdec((uint32_t)SWEEP_N_IMAGES);
    uart_puts(" images) ===\n");

    arm_pmu_enable();

    uint32_t fc1_w_ddr = (uint32_t)(uintptr_t)cnn_spm_start;
    uint32_t fc2_w_ddr = fc1_w_ddr + CNN_FC1_N_OUTPUTS * CNN_FC1_SPM_BPN;

    /* Build v1 chains */
    uart_puts("Building v1 chains...\n");
    if (cnn_fc1_build_chains(fc1_w_ddr) || cnn_fc2_build_chains(fc2_w_ddr)) {
        uart_puts("FAIL: v1 chain build\n"); for (;;);
    }

    /* Build v2 chains (same weight blob, different chain tables) */
    uart_puts("Building v2 chains...\n");
    if (cnn_fc1_v2_build_chains(fc1_w_ddr) || cnn_fc2_v2_build_chains(fc2_w_ddr)) {
        uart_puts("FAIL: v2 chain build\n"); for (;;);
    }

    uart_puts("Chains ready. Running sweep...\n");

    int v1_correct = 0, v2_correct = 0, agree = 0, errors = 0;

    /* --- v1 timing pass --- */
    arm_ccnt_reset();
    uint32_t v1_t0 = arm_ccnt_read();
    for (int i = 0; i < (int)SWEEP_N_IMAGES; i++) {
        int32_t fc2[10] = {0};
        if (run_image_v1(i, fc2)) { errors++; continue; }
        if (argmax10(fc2) == sweep_labels[i]) v1_correct++;
    }
    uint32_t v1_cyc = arm_ccnt_read() - v1_t0;

    /* --- v2 timing pass --- */
    errors = 0;
    arm_ccnt_reset();
    uint32_t v2_t0 = arm_ccnt_read();
    for (int i = 0; i < (int)SWEEP_N_IMAGES; i++) {
        int32_t fc2[10] = {0};
        if (run_image_v2(i, fc2)) { errors++; continue; }
        int pred = argmax10(fc2);
        if (pred == sweep_labels[i]) v2_correct++;
        {
            /* Compare v2 vs golden */
            if (pred == sweep_golden[i]) agree++;
        }
    }
    uint32_t v2_cyc = arm_ccnt_read() - v2_t0;

    /* --- Report --- */
    uart_puts("\n=== Results ===\n");
    uart_puts("v1 acc : "); uart_putdec((uint32_t)v1_correct);
    uart_putchar('/'); uart_putdec((uint32_t)SWEEP_N_IMAGES);
    uart_puts("\nv2 acc : "); uart_putdec((uint32_t)v2_correct);
    uart_putchar('/'); uart_putdec((uint32_t)SWEEP_N_IMAGES);
    uart_puts("\nv2 agree w/ golden: "); uart_putdec((uint32_t)agree);
    uart_putchar('/'); uart_putdec((uint32_t)SWEEP_N_IMAGES);
    uart_puts("\nErrors : "); uart_putdec((uint32_t)errors);
    uart_puts("\n\n=== Timing (CCNT cycles, "); uart_putdec((uint32_t)SWEEP_N_IMAGES);
    uart_puts(" images) ===\n");
    uart_puts("v1 total: 0x"); uart_puthex(v1_cyc); uart_putchar('\n');
    uart_puts("v2 total: 0x"); uart_puthex(v2_cyc); uart_putchar('\n');

    /* Approximate speedup (integer division) */
    uart_puts("speedup : ~");
    if (v2_cyc > 0) uart_putdec(v1_cyc / v2_cyc);
    else uart_putchar('?');
    uart_puts("x (expect ~2-4x on MAC phase)\n");

    uart_drain();
    for (;;);
    return 0;
}
