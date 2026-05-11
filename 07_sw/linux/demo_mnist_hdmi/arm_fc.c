/* arm_fc.c — see arm_fc.h. */

#include "arm_fc.h"

#include <stdint.h>
#include <stddef.h>

/* Inline INT16 extraction + sign-extension from the low 16 bits of a
 * 32-bit SPM word. */
static inline int32_t spm_int16(uint32_t word) {
    return (int32_t)(int16_t)(word & 0xFFFFu);
}

/* Saturating cast int64 → int32. CGRA's 40-bit MAC saturates at the
 * 40-bit boundary then exposes 32-bit; in practice for FC outputs the
 * dynamic range stays well within INT32. We still clamp defensively. */
static inline int32_t sat_i32(int64_t v) {
    if (v >  (int64_t)INT32_MAX) return INT32_MAX;
    if (v < -(int64_t)INT32_MAX - 1) return INT32_MIN;
    return (int32_t)v;
}

void arm_fc1_64x400(const int32_t  act400[ARM_FC1_N_IN],
                    const uint32_t weights[ARM_FC1_N_OUT * ARM_FC1_N_IN],
                    int32_t fc1_acc[ARM_FC1_N_OUT])
{
    for (int n = 0; n < ARM_FC1_N_OUT; ++n) {
        const uint32_t *w_row = weights + (size_t)n * ARM_FC1_N_IN;
        int64_t acc = 0;
        for (int i = 0; i < ARM_FC1_N_IN; ++i) {
            acc += (int64_t)act400[i] * (int64_t)spm_int16(w_row[i]);
        }
        fc1_acc[n] = sat_i32(acc);
    }
}

void arm_fc2_10x64(const int32_t  act64[ARM_FC2_N_IN],
                   const uint32_t weights[ARM_FC2_N_OUT * ARM_FC2_N_IN],
                   int32_t fc2_acc[ARM_FC2_N_OUT])
{
    for (int n = 0; n < ARM_FC2_N_OUT; ++n) {
        const uint32_t *w_row = weights + (size_t)n * ARM_FC2_N_IN;
        int64_t acc = 0;
        for (int i = 0; i < ARM_FC2_N_IN; ++i) {
            acc += (int64_t)act64[i] * (int64_t)spm_int16(w_row[i]);
        }
        fc2_acc[n] = sat_i32(acc);
    }
}

int arm_argmax(const int32_t *v, int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) if (v[i] > v[best]) best = i;
    return best;
}
