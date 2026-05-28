/* arm_fc_neon_bm.c — ARM-NEON INT16 FC1+FC2 kernel for the
 * heterogeneous-pipeline baseline. Matches the signature of
 * arm_fc_int_run() and arm_fc_vfp_run() so it drops into the existing
 * demo wiring (demo_mnist_hdmi_bm.c:519, demo_mnist_per_stage.c).
 *
 * Compiled with -O3 -funroll-loops -mfpu=neon-vfpv3 per senior review
 * §30: "give the CPU every possible advantage" so the eventual
 * head-to-head with the CGRA-FC path can't be attacked as a strawman.
 *
 * Kernel structure:
 *  1. Lazy weight unpack on first call — spm_blob has INT16 packed in
 *     lower-16 of uint32_t; NEON wants tightly-packed int16_t. One-time
 *     unpack into static buffer; amortized across all subsequent calls.
 *  2. Activation pack — int32_t act400 (post-quantize) → int16_t for
 *     NEON. Trivial cost (400 ops per inference).
 *  3. FC1 MAC: vmlal_s16 with 4-accumulator interleave (Gemini's recipe)
 *     to hide the 3-cycle accumulator latency on the Cortex-A9 NEON
 *     pipeline.
 *  4. Post-process: bias + ReLU + requant (matches arm_fc_int_bm.c).
 *  5. FC2 MAC: same NEON pattern, smaller.
 *  6. Argmax with FC2 bias.
 *
 * Bit-exact match with arm_fc_int_run() is NOT guaranteed because the
 * MAC reduction order differs (NEON does pairwise tree-add of 4 lanes).
 * For INT16 × INT16 with sum below INT32 saturation this is fine — the
 * predicted class matches.
 */

#include "arm_fc_bm.h"
#include "../cnn_eval/mnist_weights_scale.h"

#include <stdint.h>
#include <stddef.h>
#include <arm_neon.h>

#define FC1_N_IN   400
#define FC1_N_OUT   64
#define FC2_N_IN    64
#define FC2_N_OUT   10

#define FC1_W_WORDS  (FC1_N_OUT * FC1_N_IN)        /* 25600 */
#define FC2_W_WORDS  (FC2_N_OUT * FC2_N_IN)        /*   640 */

/* Pre-unpacked, NEON-friendly weight buffers. 16-byte aligned per
 * Gemini §1 (VLD1 is faster on 128-bit boundaries). */
#define ALIGN16 __attribute__((aligned(16)))
#define CNN_RUNTIME __attribute__((section(".cnn_runtime")))

static ALIGN16 CNN_RUNTIME int16_t neon_fc1_w[FC1_W_WORDS];
static ALIGN16 CNN_RUNTIME int16_t neon_fc2_w[FC2_W_WORDS];
static int neon_weights_loaded = 0;

static void neon_load_weights(const uint32_t *spm_blob)
{
    if (neon_weights_loaded) return;
    const uint32_t *fc1_w = spm_blob;
    const uint32_t *fc2_w = spm_blob + FC1_W_WORDS;
    for (int i = 0; i < FC1_W_WORDS; ++i)
        neon_fc1_w[i] = (int16_t)(fc1_w[i] & 0xFFFFu);
    for (int i = 0; i < FC2_W_WORDS; ++i)
        neon_fc2_w[i] = (int16_t)(fc2_w[i] & 0xFFFFu);
    neon_weights_loaded = 1;
}

static inline int32_t sat_i32(int64_t v)
{
    if (v >  (int64_t)0x7FFFFFFFLL) return  (int32_t)0x7FFFFFFF;
    if (v < -(int64_t)0x80000000LL) return (int32_t)0x80000000;
    return (int32_t)v;
}

/* NEON dot-product of n INT16 pairs with 4-accumulator interleave.
 * n must be a multiple of 16 (FC1=400=16×25, FC2=64=16×4 — both fit). */
static inline int32_t neon_dot_int16(const int16_t *a, const int16_t *w, int n)
{
    int32x4_t acc0 = vmovq_n_s32(0);
    int32x4_t acc1 = vmovq_n_s32(0);
    int32x4_t acc2 = vmovq_n_s32(0);
    int32x4_t acc3 = vmovq_n_s32(0);

    int i = 0;
    for (; i + 16 <= n; i += 16) {
        int16x4_t a0 = vld1_s16(a + i +  0);
        int16x4_t a1 = vld1_s16(a + i +  4);
        int16x4_t a2 = vld1_s16(a + i +  8);
        int16x4_t a3 = vld1_s16(a + i + 12);
        int16x4_t w0 = vld1_s16(w + i +  0);
        int16x4_t w1 = vld1_s16(w + i +  4);
        int16x4_t w2 = vld1_s16(w + i +  8);
        int16x4_t w3 = vld1_s16(w + i + 12);
        acc0 = vmlal_s16(acc0, a0, w0);
        acc1 = vmlal_s16(acc1, a1, w1);
        acc2 = vmlal_s16(acc2, a2, w2);
        acc3 = vmlal_s16(acc3, a3, w3);
    }
    /* Tail (only if n is not 16-aligned — for FC1/FC2 it always is) */
    for (; i + 4 <= n; i += 4) {
        int16x4_t a0 = vld1_s16(a + i);
        int16x4_t w0 = vld1_s16(w + i);
        acc0 = vmlal_s16(acc0, a0, w0);
    }

    /* Tree reduction: combine 4 accumulators, then horizontal-add lanes */
    int32x4_t sum01 = vaddq_s32(acc0, acc1);
    int32x4_t sum23 = vaddq_s32(acc2, acc3);
    int32x4_t total = vaddq_s32(sum01, sum23);
    return vgetq_lane_s32(total, 0) + vgetq_lane_s32(total, 1) +
           vgetq_lane_s32(total, 2) + vgetq_lane_s32(total, 3);
}

static void fc1_post_process(const int32_t fc1_acc[FC1_N_OUT],
                             int16_t       act64_out[FC1_N_OUT])
{
    /* Match arm_fc_int_bm.c::fc1_post_process exactly: bias + ReLU +
     * shift-requant by the smallest amount that fits max into INT16. */
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
    for (int n = 0; n < FC1_N_OUT; ++n)
        act64_out[n] = (int16_t)(tmp[n] >> shift);
}

int arm_fc_neon_run(const int32_t  act400[FC1_N_IN],
                    const uint32_t spm_blob[26240])
{
    neon_load_weights(spm_blob);

    /* Pack int32_t activations → int16_t for NEON. Acts are already
     * quantized to INT16 range upstream; this just truncates the wider
     * carry-precision representation. */
    int16_t a16[FC1_N_IN] ALIGN16;
    for (int i = 0; i < FC1_N_IN; ++i) a16[i] = (int16_t)act400[i];

    int32_t fc1_acc[FC1_N_OUT];
    for (int n = 0; n < FC1_N_OUT; ++n) {
        const int16_t *w_row = &neon_fc1_w[(size_t)n * FC1_N_IN];
        fc1_acc[n] = neon_dot_int16(a16, w_row, FC1_N_IN);
    }

    int16_t act64[FC1_N_OUT] ALIGN16;
    fc1_post_process(fc1_acc, act64);

    int32_t fc2_acc[FC2_N_OUT];
    for (int n = 0; n < FC2_N_OUT; ++n) {
        const int16_t *w_row = &neon_fc2_w[(size_t)n * FC2_N_IN];
        fc2_acc[n] = neon_dot_int16(act64, w_row, FC2_N_IN);
    }

    int32_t v[FC2_N_OUT];
    for (int i = 0; i < FC2_N_OUT; ++i)
        v[i] = fc2_acc[i] + mnist_fc2_bias_q[i];
    int best = 0;
    for (int i = 1; i < FC2_N_OUT; ++i) if (v[i] > v[best]) best = i;
    return best;
}
