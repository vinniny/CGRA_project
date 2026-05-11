/* test_inference.c — M3 smoke test: run CGRA inference on the first few
 * sweep fixture images and verify argmax matches sweep_labels[i].
 *
 * Pass criteria:
 *   - cgra_user_init succeeds (CGRA APB up, staging region mmap'd, weight
 *     blob staged, FC1+FC2 chains built).
 *   - For each of N test images, cgra_user_run_inference returns 0 and
 *     argmax(fc2_out) matches sweep_labels[i].
 *
 * Run on board:  sudo /tmp/test_inference [-n N]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "cgra_user.h"
#include "mnist_sweep_fixture.h"

int main(int argc, char **argv)
{
    int n_test = 10;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-n") && i + 1 < argc) {
            n_test = atoi(argv[++i]);
            if (n_test < 1) n_test = 1;
            if (n_test > SWEEP_N_IMAGES) n_test = SWEEP_N_IMAGES;
        }
    }

    cgra_user_t u;
    if (cgra_user_init(&u) < 0) {
        fprintf(stderr, "FAIL: cgra_user_init\n");
        return 1;
    }
    printf("cgra_user_init OK — staging at %p, FC1+FC2 chains built\n",
           u.staging_va);

    int hw_correct = 0, errors = 0;
    int32_t fc2[10];

    for (int i = 0; i < n_test; ++i) {
        if (cgra_user_run_inference(&u,
                                    sweep_act400[i],
                                    sweep_act64[i],
                                    fc2) < 0) {
            printf("  [%2d] ERROR: run_inference timeout\n", i);
            errors++;
            continue;
        }
        int hw_pred = cgra_user_argmax(fc2, 10);
        int label   = (int)sweep_labels[i];
        int gold    = (int)sweep_golden[i];
        const char *flag = (hw_pred == label) ? "OK " : "*** ";
        printf("  %s[%2d] hw=%d gold=%d label=%d  fc2={%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}\n",
               flag, i, hw_pred, gold, label,
               fc2[0], fc2[1], fc2[2], fc2[3], fc2[4],
               fc2[5], fc2[6], fc2[7], fc2[8], fc2[9]);
        if (hw_pred == label) hw_correct++;
    }

    printf("\nHW vs label: %d/%d  errors=%d\n", hw_correct, n_test, errors);

    cgra_user_close(&u);
    return (hw_correct == n_test && errors == 0) ? 0 : 2;
}
