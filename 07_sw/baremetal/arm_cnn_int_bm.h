/* arm_cnn_int_bm.h — integer-scalar ARM CNN reference (no floats, no
 * VFP, no SIMD). Same Conv+Pool+flatten+requant pipeline as the float
 * path, but every MAC is an INT32 += INT32 × INT16 scalar operation —
 * exactly what naive integer-pipelined code on a Cortex-A9 looks like.
 *
 * This is the apples-to-apples baseline for the thesis abstract's
 * "8-12 FPS ARM-only" claim: no VFP, no NEON, plain scalar code.
 *
 * Output: 400 INT32 activations matching the act400 format consumed by
 * the CGRA FC1 pipeline (sweep_act400-compatible). The caller still
 * runs FC1+FC2 on the CGRA so the Conv+Pool half is the only variable.
 */
#ifndef ARM_CNN_INT_BM_H
#define ARM_CNN_INT_BM_H

#include <stdint.h>

#define ARM_INT_CNN_INPUT_N   784
#define ARM_INT_CNN_ACT400_N  400

int arm_cnn_int_run(const uint8_t input_uint8[ARM_INT_CNN_INPUT_N],
                    int32_t       act400_out[ARM_INT_CNN_ACT400_N]);

#endif /* ARM_CNN_INT_BM_H */
