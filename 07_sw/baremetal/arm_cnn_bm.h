/* arm_cnn_bm.h — bare-metal ARM float CNN reference (VFPv3 build).
 *
 * Does Conv1+ReLU+Pool1+Conv2+ReLU+Pool2+flatten+per-image quantize and
 * emits a 400-element INT32 activation vector ready for FC1 on the CGRA.
 * FC1/FC2 themselves run on the CGRA in all demo paths, so this is the
 * Conv-half of the ARM comparator.
 *
 * Compiled with -mfpu=vfpv3 -mfloat-abi=hard -DARM_CNN_VARIANT=1 into
 * arm_cnn_bm_vfp.o. A no-VFP/no-NEON scalar baseline (matching the
 * thesis abstract's implicit "8-12 FPS ARM-only" claim) lives in a
 * separate file (arm_cnn_int_bm.{h,c}) because mixed-ABI soft-float in
 * one ELF is rejected by arm-none-eabi-ld. */
#ifndef ARM_CNN_BM_H
#define ARM_CNN_BM_H

#include <stdint.h>

#define ARM_CNN_INPUT_N    784    /* 28×28 */
#define ARM_CNN_ACT400_N   400    /* 5×5×16 flattened CHW */

#ifdef __cplusplus
extern "C" {
#endif

/* VFP variant (hardware floats). Returns 0 on success. */
int arm_cnn_vfp_run(const uint8_t  input_uint8[ARM_CNN_INPUT_N],
                    int32_t        act400_out[ARM_CNN_ACT400_N]);

#ifdef __cplusplus
}
#endif

#endif /* ARM_CNN_BM_H */
