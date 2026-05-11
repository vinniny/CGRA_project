/* arm_fc.h — ARM scalar reference path for FC1+FC2 MNIST inference.
 *
 * Mirrors the CGRA's integer math so ARM and CGRA produce comparable
 * results on the same inputs: INT16 weight × INT32 activation accumulated
 * into INT64, then clamped to INT32 (matching the CGRA's 40-bit
 * saturating MAC truncated to 32-bit). No SIMD intrinsics — the point is
 * an honest scalar baseline for the speedup comparison.
 *
 * Weights are read from the same blob the CGRA uses (cnn_spm_start[]):
 * one INT16 in the low 16 bits of each 32-bit word, neuron-major layout
 * (FC1: 64 neurons × 400 inputs; FC2: 10 neurons × 64 inputs).
 */
#ifndef ARM_FC_H
#define ARM_FC_H

#include <stdint.h>

#define ARM_FC1_N_IN   400
#define ARM_FC1_N_OUT   64
#define ARM_FC2_N_IN    64
#define ARM_FC2_N_OUT   10

/* Compute fc1_acc[n] = clamp_i32( sum_i act400[i] * sign_extend_i16(w[n*N_IN + i]) ).
 * `weights` is the FC1 portion of the cnn_spm blob (uint32_t[64*400]).
 * fc1_acc[64] is filled with INT32 dot-products.                          */
void arm_fc1_64x400(const int32_t  act400[ARM_FC1_N_IN],
                    const uint32_t weights[ARM_FC1_N_OUT * ARM_FC1_N_IN],
                    int32_t fc1_acc[ARM_FC1_N_OUT]);

/* Same shape as FC1 but 10×64. `weights` is the FC2 portion of cnn_spm. */
void arm_fc2_10x64(const int32_t  act64[ARM_FC2_N_IN],
                   const uint32_t weights[ARM_FC2_N_OUT * ARM_FC2_N_IN],
                   int32_t fc2_acc[ARM_FC2_N_OUT]);

/* Argmax helper. */
int  arm_argmax(const int32_t *v, int n);

#endif /* ARM_FC_H */
