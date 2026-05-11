/* arm_fc_int_bm.c — ARM integer FC1+FC2 reference. Mirrors CGRA's
 * integer pipeline: INT16 weights × INT32 activations into INT64 acc,
 * then bias + ReLU + requant + FC2 + argmax-with-bias. */

#include "arm_fc_bm.h"
#include "../cnn_eval/mnist_weights_scale.h"

#include <stdint.h>
#include <stddef.h>

#define FC1_N_IN   400
#define FC1_N_OUT   64
#define FC2_N_IN    64
#define FC2_N_OUT   10

#define FC1_W_WORDS  (FC1_N_OUT * FC1_N_IN)        /* 25600 */
#define FC2_W_WORDS  (FC2_N_OUT * FC2_N_IN)        /*   640 */

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

static void fc1_post_process(const int32_t fc1_acc[FC1_N_OUT],
                             int32_t act64_out[FC1_N_OUT])
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
    for (int n = 0; n < FC1_N_OUT; ++n) act64_out[n] = tmp[n] >> shift;
}

int arm_fc_int_run(const int32_t  act400[FC1_N_IN],
                   const uint32_t spm_blob[26240])
{
    const uint32_t *fc1_w = spm_blob;
    const uint32_t *fc2_w = spm_blob + FC1_W_WORDS;

    int32_t fc1_acc[FC1_N_OUT];
    for (int n = 0; n < FC1_N_OUT; ++n) {
        const uint32_t *w_row = fc1_w + (size_t)n * FC1_N_IN;
        int64_t acc = 0;
        for (int i = 0; i < FC1_N_IN; ++i) {
            acc += (int64_t)act400[i] * (int64_t)spm_int16(w_row[i]);
        }
        fc1_acc[n] = sat_i32(acc);
    }

    int32_t act64[FC1_N_OUT];
    fc1_post_process(fc1_acc, act64);

    int32_t fc2_acc[FC2_N_OUT];
    for (int n = 0; n < FC2_N_OUT; ++n) {
        const uint32_t *w_row = fc2_w + (size_t)n * FC2_N_IN;
        int64_t acc = 0;
        for (int i = 0; i < FC2_N_IN; ++i) {
            acc += (int64_t)act64[i] * (int64_t)spm_int16(w_row[i]);
        }
        fc2_acc[n] = sat_i32(acc);
    }

    int32_t v[FC2_N_OUT];
    for (int i = 0; i < FC2_N_OUT; ++i)
        v[i] = fc2_acc[i] + mnist_fc2_bias_q[i];
    int best = 0;
    for (int i = 1; i < FC2_N_OUT; ++i) if (v[i] > v[best]) best = i;
    return best;
}
