/* test_arm_cnn.c — P1 validation: full ARM CNN reference accuracy + speed.
 *
 * For each fixture image, runs the full pipeline:
 *   sweep_input28[i] (uint8) -> normalize -> Conv1 -> ReLU -> Pool1 ->
 *     Conv2 -> ReLU -> Pool2 -> quantize -> FC1+ReLU+requantize ->
 *     FC2 -> argmax
 *
 * Compares predicted digit to sweep_labels[i]. Reports accuracy + average
 * wall-clock ms/image + derived FPS.
 *
 * Pass criteria:
 *   - Accuracy >= 95/100 (golden_sim achieves 100/100 in pure Python;
 *     we use the same float arithmetic so should match).
 *   - Wall-clock per image plausible (Cortex-A9 @ 666 MHz with ~190K MACs
 *     of float Conv expects single-digit ms).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "arm_cnn.h"
#include "arm_fc.h"
#include "mnist_sweep_fixture.h"

/* The FC1+FC2 INT16 weight blob (same one CGRA uses, demo_mnist_weights.S). */
extern const uint32_t cnn_spm_start[];
#define FC1_BYTES  (ARM_FC1_N_OUT * ARM_FC1_N_IN * 4)

static double ms_since(const struct timespec *t0) {
    struct timespec t1;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    return (double)(t1.tv_sec  - t0->tv_sec)  * 1000.0
         + (double)(t1.tv_nsec - t0->tv_nsec) * 1e-6;
}

/* Debug-dump first 9 weights of conv1 channel 0, first 9 act400 values,
 * and the raw fc2 logits for image 0. Hook to verify our blob layout
 * matches Python golden — call via -d flag. */
extern const uint8_t cnn_conv_start[];

static void debug_dump(void)
{
    const int16_t *c1_w_i16 = (const int16_t *)cnn_conv_start;
    printf("=== conv1 weights[0][:,:,0] first 9 (should match Python) ===\n");
    for (int i = 0; i < 9; ++i) {
        printf("  c1_w_i16[%d] = %d (= %.8f)\n",
               i, (int)c1_w_i16[i], (double)c1_w_i16[i] * 0.00003041);
    }
    const int32_t *c1_b_i32 = (const int32_t *)(cnn_conv_start + 144);
    printf("=== conv1 biases (8 values) ===\n");
    for (int i = 0; i < 8; ++i) {
        printf("  b[%d] = %d (= %.6f)\n",
               i, (int)c1_b_i32[i], (double)c1_b_i32[i] * 0.00003041);
    }
    int32_t act400[400];
    int pred = arm_cnn_run(sweep_input28[0], cnn_spm_start,
                           cnn_spm_start + (FC1_BYTES / 4), act400);
    printf("=== arm_cnn act400[0..15] (image 0) ===\n");
    for (int i = 0; i < 16; ++i) printf("  act400[%d] = %d  (golden=%d)\n",
        i, act400[i], sweep_act400[0][i]);
    printf("=== arm_cnn predicted = %d  (label=%d  golden=%d) ===\n",
        pred, (int)sweep_labels[0], (int)sweep_golden[0]);
}

int main(int argc, char **argv)
{
    int n_test = 100;
    int verbose = 0;
    int debug = 0;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-n") && i + 1 < argc) {
            n_test = atoi(argv[++i]);
            if (n_test < 1) n_test = 1;
            if (n_test > SWEEP_N_IMAGES) n_test = SWEEP_N_IMAGES;
        } else if (!strcmp(argv[i], "-v")) {
            verbose = 1;
        } else if (!strcmp(argv[i], "-d")) {
            debug = 1;
        }
    }
    if (debug) { debug_dump(); return 0; }

    const uint32_t *fc1_w = cnn_spm_start;
    const uint32_t *fc2_w = cnn_spm_start + (FC1_BYTES / 4);

    int correct_vs_label = 0;
    int correct_vs_golden = 0;
    int wrong_first[5] = {-1,-1,-1,-1,-1};
    int wrong_count = 0;

    double total_ms = 0.0;
    struct timespec t0;

    printf("=== arm_cnn full pipeline test (%d images) ===\n", n_test);
    if (verbose) printf("  idx | pred | label | golden | ms\n");

    for (int i = 0; i < n_test; ++i) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        int pred = arm_cnn_run(sweep_input28[i], fc1_w, fc2_w, NULL);
        double dt = ms_since(&t0);
        total_ms += dt;

        int label  = (int)sweep_labels[i];
        int golden = (int)sweep_golden[i];
        if (pred == label)  correct_vs_label++;
        if (pred == golden) correct_vs_golden++;

        if (verbose) {
            printf("  [%2d] %d  %d  %d  %.2f ms %s\n",
                   i, pred, label, golden, dt,
                   pred == label ? "" : "***");
        }
        if (pred != label && wrong_count < 5) {
            wrong_first[wrong_count++] = i;
        }
    }

    double avg_ms = total_ms / n_test;
    double fps    = (avg_ms > 0.0) ? 1000.0 / avg_ms : 0.0;

    printf("\n=== results ===\n");
    printf("  Accuracy   vs label   : %d/%d (%.0f%%)\n",
           correct_vs_label, n_test, 100.0 * correct_vs_label / n_test);
    printf("  Accuracy   vs golden  : %d/%d (%.0f%%)\n",
           correct_vs_golden, n_test, 100.0 * correct_vs_golden / n_test);
    printf("  Wall-clock total      : %.2f ms\n", total_ms);
    printf("  Wall-clock per image  : %.3f ms\n", avg_ms);
    printf("  FPS (1/ms_per_image)  : %.0f\n", fps);
    if (wrong_count > 0) {
        printf("  First %d mismatches    : ", wrong_count);
        for (int k = 0; k < wrong_count; ++k) printf("%d ", wrong_first[k]);
        printf("\n");
    }
    return (correct_vs_label >= n_test * 95 / 100) ? 0 : 2;
}
