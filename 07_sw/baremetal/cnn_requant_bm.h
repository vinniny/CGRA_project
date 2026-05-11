/* cnn_requant_bm.h — per-layer max-abs requantization for the bare-metal
 * MNIST CNN forward pass.
 *
 * Why requantization matters here. The integer pipeline accumulates scale
 * across layers: after Conv1 the magnitudes are roughly
 *   v_int ≈ v_float * INPUT_SCALE * (1/s_w1)   ≈ v_float * 8.42M
 * which after Conv2 would blow up by another factor of (1/s_w2) ≈ 24631,
 * pegging the INT32 accumulator everywhere. The fix is to shift each
 * post-pool buffer right just enough to fit back into INT16 range, and
 * carry the shift amount forward for bias scaling.
 *
 * The same pattern is in 07_sw/cnn_eval/emit_sweep_fixture.py — Python
 * uses max(abs(buf)) / 32767 as the float-scale; we use the equivalent
 * integer right-shift here.
 */
#ifndef CNN_REQUANT_BM_H
#define CNN_REQUANT_BM_H

#include <stdint.h>

/* Right-shift `buf` in-place so max(|buf[i]|) <= INT16_MAX. */
static inline int cnn_requant_to_int16(int32_t *buf, int n)
{
    int32_t max_abs = 0;
    for (int i = 0; i < n; ++i) {
        int32_t a = buf[i];
        if (a < 0) a = -a;
        if (a > max_abs) max_abs = a;
    }
    int shift = 0;
    while ((max_abs >> shift) > 32767 && shift < 31) shift++;
    if (shift > 0) {
        for (int i = 0; i < n; ++i) buf[i] >>= shift;
    }
    return shift;
}

/* Right-shift in-place so max(|buf[i]|) <= `target_max`. Use this when a
 * downstream MAC needs more headroom than INT16. For Conv2 inputs we
 * limit pool1 to ~7281 so that 9 spatial-MAC × INT15 weights stay under
 * INT32_MAX inside the CGRA's saturating accumulator. */
static inline int cnn_requant_to_max(int32_t *buf, int n, int32_t target_max)
{
    int32_t max_abs = 0;
    for (int i = 0; i < n; ++i) {
        int32_t a = buf[i];
        if (a < 0) a = -a;
        if (a > max_abs) max_abs = a;
    }
    int shift = 0;
    while ((max_abs >> shift) > target_max && shift < 31) shift++;
    if (shift > 0) {
        for (int i = 0; i < n; ++i) buf[i] >>= shift;
    }
    return shift;
}

/* Conv1 bias correction. Conv1's MAC accumulates at scale
 *   (INPUT_SCALE × 1/s_w1) ≈ 8.42M per float unit.
 * The stored bias_q is at scale (1/s_w1), so we left-shift by
 * INPUT_SCALE_LOG2 (=log2(INPUT_SCALE)) to convert it into accumulator
 * units. */
static inline int32_t conv1_apply_bias(int32_t acc,
                                       int32_t bias_q,
                                       int input_scale_log2)
{
    return acc + (bias_q << input_scale_log2);
}

/* Conv2 bias correction.
 *
 *   Conv2 input scale (after Conv1 + bias + ReLU + Pool1 + shift1):
 *     s_in2 = INPUT_SCALE * (1/s_w1) / 2^shift1
 *   Conv2 MAC accumulator scale:
 *     s_acc2 = s_in2 * (1/s_w2)
 *   bias_q is stored at scale (1/s_w2). To convert it to s_acc2 units we
 *   multiply by s_in2 = INPUT_SCALE * (1/s_w1) / 2^shift1.
 *
 * Using INT64 because (INPUT_SCALE × 1/s_w1) is ~8.4M and bias_q can be
 * ~50k — their product exceeds INT32. The final >>shift1 brings it back
 * into INT32 range when shift1 ≥ ~7. Real MNIST images yield shift1 of
 * 10-11 so the typical case is comfortable.
 *
 * Edge case: if shift1 is small enough that the scaled bias would
 * dominate the accumulator (effectively turning the channel into a
 * constant), we skip the bias rather than emit a saturated value. This
 * matches the original code's behavior for pathological / near-blank
 * inputs and avoids INT32 saturation chaining through later stages.   */
#define CONV2_BIAS_MIN_SHIFT1  7

static inline int32_t conv2_apply_bias(int32_t acc,
                                       int32_t bias_q,
                                       int input_scale,
                                       int32_t inv_s_w1,
                                       int shift1)
{
    if (shift1 < CONV2_BIAS_MIN_SHIFT1) {
        /* Bias would scale-saturate; skip rather than corrupt the channel. */
        return acc;
    }
    int64_t bias64 = (int64_t)bias_q
                   * (int64_t)input_scale
                   * (int64_t)inv_s_w1;
    bias64 >>= shift1;
    if (bias64 >  (int64_t)2147483647LL) bias64 =  2147483647LL;
    if (bias64 < -(int64_t)2147483648LL) bias64 = -2147483648LL;
    return acc + (int32_t)bias64;
}

#endif /* CNN_REQUANT_BM_H */
