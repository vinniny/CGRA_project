/* arm_fc_vfp_bm.c — ARM float FC1+FC2 reference. Same algorithmic
 * structure as arm_fc_int_bm.c but with float MAC inside the dot
 * products. Compiled with -mfpu=vfpv3 -mfloat-abi=hard so every MAC is
 * a VFP `vmla.f32`.
 *
 * Floats give the "honest modern compile" asterisk for the FC speedup
 * panel: VFP can hit ~1 cycle per MAC on Cortex-A9, where the INT path
 * has higher per-op cost from sign-extension + 64-bit add. */

#include "arm_fc_bm.h"
#include "../cnn_eval/mnist_weights_scale.h"

#include <stdint.h>
#include <stddef.h>

#define FC1_N_IN   400
#define FC1_N_OUT   64
#define FC2_N_IN    64
#define FC2_N_OUT   10

#define FC1_W_WORDS  (FC1_N_OUT * FC1_N_IN)
#define FC2_W_WORDS  (FC2_N_OUT * FC2_N_IN)

/* Big float weight buffers (102 KB + 2.5 KB) — too large for OCM .bss.
 * Pin to a custom DDR section so the linker places them in DDR_DATA. */
#define CNN_RUNTIME __attribute__((section(".cnn_runtime")))
static CNN_RUNTIME float vfp_fc1_w[FC1_N_OUT * FC1_N_IN];
static CNN_RUNTIME float vfp_fc2_w[FC2_N_OUT * FC2_N_IN];
static int vfp_weights_loaded = 0;

static inline int32_t spm_int16(uint32_t word)
{
    return (int32_t)(int16_t)(word & 0xFFFFu);
}

static void vfp_load_weights(const uint32_t *spm_blob)
{
    if (vfp_weights_loaded) return;
    const uint32_t *fc1_w = spm_blob;
    const uint32_t *fc2_w = spm_blob + FC1_W_WORDS;

    for (int i = 0; i < FC1_N_OUT * FC1_N_IN; ++i)
        vfp_fc1_w[i] = (float)spm_int16(fc1_w[i]);
    for (int i = 0; i < FC2_N_OUT * FC2_N_IN; ++i)
        vfp_fc2_w[i] = (float)spm_int16(fc2_w[i]);
    vfp_weights_loaded = 1;
}

int arm_fc_vfp_run(const int32_t  act400[FC1_N_IN],
                   const uint32_t spm_blob[26240])
{
    vfp_load_weights(spm_blob);

    /* FC1 — float MAC, then add bias, ReLU, find max. */
    float fc1_out[FC1_N_OUT];
    float max_abs = 0.0f;
    for (int n = 0; n < FC1_N_OUT; ++n) {
        const float *w_row = vfp_fc1_w + (size_t)n * FC1_N_IN;
        float acc = 0.0f;
        for (int i = 0; i < FC1_N_IN; ++i)
            acc += (float)act400[i] * w_row[i];
        acc += (float)mnist_fc1_bias_q[n];
        if (acc < 0.0f) acc = 0.0f;
        fc1_out[n] = acc;
        if (acc > max_abs) max_abs = acc;
    }

    /* Requantize to roughly INT16 to match FC2's scale (we want the
     * same numerical ballpark FC2's weights expect). */
    float scale = (max_abs > 0.0f) ? (32767.0f / max_abs) : 1.0f;
    float act64_f[FC1_N_OUT];
    for (int n = 0; n < FC1_N_OUT; ++n) act64_f[n] = fc1_out[n] * scale;

    /* FC2 — float MAC + bias. */
    float fc2_v[FC2_N_OUT];
    for (int n = 0; n < FC2_N_OUT; ++n) {
        const float *w_row = vfp_fc2_w + (size_t)n * FC2_N_IN;
        float acc = 0.0f;
        for (int i = 0; i < FC2_N_IN; ++i)
            acc += act64_f[i] * w_row[i];
        acc += (float)mnist_fc2_bias_q[n];
        fc2_v[n] = acc;
    }

    int best = 0;
    for (int i = 1; i < FC2_N_OUT; ++i)
        if (fc2_v[i] > fc2_v[best]) best = i;
    return best;
}
