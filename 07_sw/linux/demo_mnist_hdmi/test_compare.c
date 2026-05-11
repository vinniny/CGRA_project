/* test_compare.c — M4 side-by-side ARM vs CGRA: timing + accuracy.
 *
 * For each of N fixture images:
 *   1. Run ARM FC1(act400) + FC2(act64), time with clock_gettime.
 *   2. Run CGRA FC1(act400) + FC2(act64) via cgra_user_run_inference,
 *      time with clock_gettime, also accumulate pure CU_CYCLES.
 *   3. Verify both argmax match each other AND match sweep_labels[i].
 *
 * Prints per-image timings + final aggregate (ARM ms total, CGRA ms total,
 * speedup, CGRA pure-cycles).
 *
 * Both paths mirror demo_mnist_sweep.c: FC1 output discarded, FC2 fed the
 * fixture's pre-computed act64. This isolates the comparison to "do FC1
 * MAC math + FC2 MAC math on the same inputs."
 *
 * Build: make test_compare
 * Run:   sudo /tmp/test_compare [-n N]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "cgra_user.h"
#include "arm_fc.h"
#include "mnist_sweep_fixture.h"

extern const uint32_t cnn_spm_start[];

#define FC1_BYTES  (ARM_FC1_N_OUT * ARM_FC1_N_IN * 4)   /* 102400 */

/* CGRA group counts (mirror cgra_kernels_cnn.h, kept local to avoid
 * pulling in the bare-metal CGRA header in this TU). */
#define CGRA_FC1_GROUPS  16
#define CGRA_FC2_GROUPS   3

static double ms_since(struct timespec *t0) {
    struct timespec t1;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double dt = (double)(t1.tv_sec - t0->tv_sec) * 1000.0
              + (double)(t1.tv_nsec - t0->tv_nsec) * 1e-6;
    return dt;
}

int main(int argc, char **argv)
{
    int n_test = 10;
    int verbose = 0;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-n") && i + 1 < argc) {
            n_test = atoi(argv[++i]);
            if (n_test < 1) n_test = 1;
            if (n_test > SWEEP_N_IMAGES) n_test = SWEEP_N_IMAGES;
        } else if (!strcmp(argv[i], "-v")) {
            verbose = 1;
        }
    }

    cgra_user_t u;
    if (cgra_user_init(&u) < 0) {
        fprintf(stderr, "FAIL: cgra_user_init\n");
        return 1;
    }

    /* FC1/FC2 weights live in the same blob the CGRA uses, in DDR via
     * cnn_spm_start[]. ARM accesses them through the linked symbol. */
    const uint32_t *fc1_w = cnn_spm_start;
    const uint32_t *fc2_w = cnn_spm_start + (FC1_BYTES / 4);

    int arm_correct = 0, cgra_correct = 0, arm_eq_cgra = 0, errors = 0;
    double arm_ms_total = 0.0, cgra_ms_total = 0.0;
    uint64_t cgra_cycles_total = 0;
    int32_t fc1_acc[ARM_FC1_N_OUT];
    int32_t arm_fc2[ARM_FC2_N_OUT];
    int32_t cgra_fc2[ARM_FC2_N_OUT];

    printf("=== ARM vs CGRA MNIST inference (%d images) ===\n", n_test);
    if (verbose) printf("  idx | arm | cgra | label | arm_ms | cgra_ms | speedup\n");

    for (int i = 0; i < n_test; ++i) {
        struct timespec t0;

        /* --- ARM path: FC1 (output discarded) + FC2 --- */
        clock_gettime(CLOCK_MONOTONIC, &t0);
        arm_fc1_64x400(sweep_act400[i], fc1_w, fc1_acc);
        arm_fc2_10x64(sweep_act64[i],   fc2_w, arm_fc2);
        int arm_pred = arm_argmax(arm_fc2, 10);
        double arm_ms = ms_since(&t0);

        /* --- CGRA path: same call signature, same workload --- */
        uint32_t cyc_before = cgra_read(&u.dev, CGRA_CU_CYCLES);
        clock_gettime(CLOCK_MONOTONIC, &t0);
        if (cgra_user_run_inference(&u, sweep_act400[i], sweep_act64[i],
                                    cgra_fc2) < 0) {
            printf("  [%2d] CGRA timeout\n", i);
            errors++;
            continue;
        }
        double cgra_ms = ms_since(&t0);
        uint32_t cyc_after = cgra_read(&u.dev, CGRA_CU_CYCLES);
        int cgra_pred = arm_argmax(cgra_fc2, 10);

        /* CGRA_CU_CYCLES counts the CU's busy cycles for ONE run_group;
         * the register doesn't accumulate across run_groups, so the
         * "before/after" delta is just the last group's cycles. We
         * approximate by counting all groups' cycles roughly equal —
         * cnn_fc_run_group sets PC_END=15 each time. Use post-read as
         * the per-group cycle count and multiply by N_GROUPS to estimate
         * pure compute cycles for the whole inference. */
        uint32_t per_group_cycles = cyc_after;  /* last run_group's CU_CYCLES */
        uint64_t inference_cycles = (uint64_t)per_group_cycles *
                                    (CGRA_FC1_GROUPS + CGRA_FC2_GROUPS);
        (void)cyc_before;
        cgra_cycles_total += inference_cycles;

        int label = (int)sweep_labels[i];
        if (arm_pred  == label) arm_correct++;
        if (cgra_pred == label) cgra_correct++;
        if (arm_pred  == cgra_pred) arm_eq_cgra++;

        arm_ms_total  += arm_ms;
        cgra_ms_total += cgra_ms;

        if (verbose) {
            double speedup = (cgra_ms > 0.0) ? (arm_ms / cgra_ms) : 0.0;
            printf("  [%2d] arm=%d cgra=%d lbl=%d  arm=%6.2f ms  cgra=%6.2f ms  %.1fx\n",
                   i, arm_pred, cgra_pred, label, arm_ms, cgra_ms, speedup);
        }
    }

    printf("\n=== aggregate ===\n");
    printf("  Accuracy   ARM vs label : %d/%d (%.0f%%)\n",
           arm_correct, n_test, 100.0 * arm_correct / n_test);
    printf("  Accuracy   CGRA vs label: %d/%d (%.0f%%)\n",
           cgra_correct, n_test, 100.0 * cgra_correct / n_test);
    printf("  Agreement  ARM == CGRA  : %d/%d (%.0f%%)\n",
           arm_eq_cgra, n_test, 100.0 * arm_eq_cgra / n_test);
    printf("  CGRA errors             : %d\n", errors);
    printf("\n");
    printf("  ARM wall-clock total : %.2f ms  (avg %.3f ms/img)\n",
           arm_ms_total,  arm_ms_total / n_test);
    printf("  CGRA wall-clock total: %.2f ms  (avg %.3f ms/img)\n",
           cgra_ms_total, cgra_ms_total / n_test);
    if (cgra_ms_total > 0.0) {
        printf("  Speedup (wall-clock) : %.2fx\n",
               arm_ms_total / cgra_ms_total);
    }
    /* Pure-CGRA-compute speedup uses CU_CYCLES (50 MHz → 20 ns/cycle).
     * This excludes Linux syscall + AXI setup overhead. */
    double cgra_pure_ms = (double)cgra_cycles_total * 20e-6;  /* 20 ns/cycle */
    printf("  CGRA pure cycles tot : %llu (%.2f ms @ 50 MHz)\n",
           (unsigned long long)cgra_cycles_total, cgra_pure_ms);
    if (cgra_pure_ms > 0.0) {
        printf("  Speedup (pure cycles): %.2fx\n",
               arm_ms_total / cgra_pure_ms);
    }

    cgra_user_close(&u);
    return (errors == 0) ? 0 : 2;
}
