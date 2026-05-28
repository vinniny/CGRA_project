/* bench_neon_fc.c — Pillar 5 silicon ELF.
 *
 * Times arm_fc_neon_run() and arm_fc_int_run() (and arm_fc_vfp_run() for
 * completeness) over N=1000 iterations on a fixed input. The NEON build
 * is compiled with -O3 -funroll-loops -mfpu=neon-vfpv3 to give the CPU
 * the fair-baseline treatment senior review §30 requires.
 *
 * Expected order of magnitude (Gemini + Codex band):
 *   arm_fc_neon_run :  15-40 µs  ← target NEON line
 *   arm_fc_int_run  : 200-400 µs (scalar INT64, no SIMD)
 *   arm_fc_vfp_run  : 100-200 µs (float VFP, no SIMD)
 *
 * The neon number is what we plot on the Roofline as the FC ceiling
 * achievable on Cortex-A9 when properly hand-tuned.
 */

#include <stdint.h>
#include "cgra.h"
#include "uart.h"
#include "arm_fc_bm.h"

/* SPM blob linked from demo_mnist_weights.S — same symbol the
 * existing CGRA path uses (demo_mnist_sweep.c:31). 26240 uint32_t
 * words = FC1 (25600) + FC2 (640), INT16 packed in lower 16. */
extern const uint32_t cnn_spm_start[];

/* Synthetic act400 — same shape as what conv2-pool-quant produces, but
 * we don't need actual conv output for timing. Use a deterministic
 * pattern so the NEON kernel can't shortcut. */
static int32_t synth_act400[400];

static void init_synth_act400(void)
{
    /* Mid-range INT16 values to exercise both halves of the MAC range */
    for (int i = 0; i < 400; ++i)
        synth_act400[i] = (int32_t)((i * 137 + 41) & 0x7FFFu) - 16384;
}

static void run_one(const char *label,
                    int (*fc_fn)(const int32_t*, const uint32_t*),
                    int n_iter,
                    const uint32_t *spm_blob)
{
    /* Warmup: first call triggers lazy weight unpack in NEON/VFP paths */
    volatile int sink = fc_fn(synth_act400, spm_blob);
    (void)sink;

    arm_ccnt_reset();
    uint32_t t0 = arm_ccnt_read();
    for (int i = 0; i < n_iter; ++i) {
        sink = fc_fn(synth_act400, spm_blob);
        (void)sink;
    }
    uint32_t cyc_total = arm_ccnt_read() - t0;

    uint32_t cyc_per   = cyc_total / (uint32_t)n_iter;
    /* @ 666.67 MHz, 1 cyc = 1.5 ns → us_per = cyc_per * 3 / 2000 */
    uint32_t us_x10    = (cyc_per * 15u) / 1000u;   /* µs × 10 */

    uart_puts(label);
    uart_puts(": ");
    uart_putdec(cyc_per);
    uart_puts(" cyc/inf = ");
    uart_putdec(us_x10 / 10u);
    uart_putchar('.');
    uart_putdec(us_x10 % 10u);
    uart_puts(" us  (pred=");
    uart_putdec((uint32_t)sink);
    uart_puts(")\n");
}

int main(void)
{
    uart_init();
    arm_pmu_enable();
    arm_ccnt_reset();

    uart_puts("\n=========================================================\n");
    uart_puts("  bench_neon_fc — Pillar 5: FC NEON baseline timing\n");
    uart_puts("  ARM Cortex-A9 @ 666.67 MHz, INT16 weights, 25,600 + 640 MACs\n");
    uart_puts("=========================================================\n");

    init_synth_act400();
    const uint32_t *spm = cnn_spm_start;

    const int N_ITER = 1000;
    uart_puts("Iterations per kernel: 1000\n\n");

    run_one("arm_fc_neon_run", arm_fc_neon_run, N_ITER, spm);
    run_one("arm_fc_int_run ", arm_fc_int_run,  N_ITER, spm);
    run_one("arm_fc_vfp_run ", arm_fc_vfp_run,  N_ITER, spm);

    uart_puts("\n=== Pillar 5 complete ===\n");
    while (1) ;
    return 0;
}
