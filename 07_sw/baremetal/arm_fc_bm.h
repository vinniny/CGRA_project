/* arm_fc_bm.h — bare-metal ARM FC1+FC2 reference implementations.
 *
 * Both variants take the same `act400` input (produced by ARM-VFP Conv)
 * and produce the predicted class (0-9). They internally run FC1 → bias
 * + ReLU + requant → FC2 → argmax (with FC2 bias).
 *
 *   arm_fc_int_run  — INT64 accumulator, INT16 weights from the SPM blob.
 *                     Mirrors the CGRA's integer pipeline exactly.
 *   arm_fc_vfp_run  — float MAC (compiled with -mfpu=vfpv3 -mfloat-abi=hard).
 *                     Lazy-loads dequantized weights on first call.
 *   arm_fc_neon_run — INT16 NEON MAC (vmlal_s16, 4-accumulator interleave;
 *                     compiled at -O3 -funroll-loops -mfpu=neon-vfpv3 per
 *                     senior-review §30 "give the CPU every advantage").
 */
#ifndef ARM_FC_BM_H
#define ARM_FC_BM_H

#include <stdint.h>

#define ARM_FC_INPUT_N   400
#define ARM_FC_OUTPUT_N   10

#ifdef __cplusplus
extern "C" {
#endif

int arm_fc_int_run(const int32_t  act400[ARM_FC_INPUT_N],
                   const uint32_t spm_blob[26240]);

int arm_fc_vfp_run(const int32_t  act400[ARM_FC_INPUT_N],
                   const uint32_t spm_blob[26240]);

int arm_fc_neon_run(const int32_t  act400[ARM_FC_INPUT_N],
                    const uint32_t spm_blob[26240]);

#ifdef __cplusplus
}
#endif

#endif /* ARM_FC_BM_H */
