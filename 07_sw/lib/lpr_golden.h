/* ===================================================================
 *  lpr_golden.h – Pure-C Golden Model for Vietnamese License Plate
 *                 Character Recognition (Cortex-A9 reference)
 *
 *  Network:  28×28 grayscale → Conv1 → Pool1 → Conv2 → Pool2
 *            → Flatten → FC → 30-class output
 *
 *  Vietnamese plate character set (30 classes):
 *    Digits: 0 1 2 3 4 5 6 7 8 9
 *    Letters: A B C D E F G H K L M N P S T U V X Y Z
 *    (I, O, Q excluded — confused with 1, 0, 9)
 *
 *  All arithmetic is int32 fixed-point to match CGRA execution.
 * =================================================================== */

#ifndef LPR_GOLDEN_H
#define LPR_GOLDEN_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Vietnamese plate character set ─────────────────────────────── */

#define VN_NUM_CLASSES      30

/* Class index → character (matches c_alpr/src/char_map.c) */
static const char VN_CHAR_MAP[VN_NUM_CLASSES] = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9',      /* 0-8  */
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'K',      /* 9-17 */
    'L', 'M', 'N', 'P', 'S', 'T', 'U', 'V', 'X',      /* 18-26 */
    'Y', 'Z', '0'                                        /* 27-29 */
};

/* ── Network architecture constants ─────────────────────────────── */

/* Input */
#define GOLDEN_IN_H         28
#define GOLDEN_IN_W         28
#define GOLDEN_IN_C         1       /* Grayscale */

/* Conv1: 1 → 8 channels, 3×3, pad=1, stride=1 → 28×28×8 */
#define GOLDEN_CONV1_OUT_CH 8
#define GOLDEN_CONV1_KH     3
#define GOLDEN_CONV1_KW     3
#define GOLDEN_CONV1_PAD    1
#define GOLDEN_CONV1_STRIDE 1

/* Pool1: 2×2 max-pool → 14×14×8 */
#define GOLDEN_POOL1_H      14
#define GOLDEN_POOL1_W      14

/* Conv2: 8 → 16 channels, 3×3, pad=1, stride=1 → 14×14×16 */
#define GOLDEN_CONV2_IN_CH  8
#define GOLDEN_CONV2_OUT_CH 16
#define GOLDEN_CONV2_KH     3
#define GOLDEN_CONV2_KW     3
#define GOLDEN_CONV2_PAD    1
#define GOLDEN_CONV2_STRIDE 1

/* Pool2: 2×2 max-pool → 7×7×16 */
#define GOLDEN_POOL2_H      7
#define GOLDEN_POOL2_W      7

/* Flatten: 7 × 7 × 16 = 784 features */
#define GOLDEN_FC_IN        (GOLDEN_POOL2_H * GOLDEN_POOL2_W * GOLDEN_CONV2_OUT_CH)

/* FC: 784 → 30 */
#define GOLDEN_FC_OUT       VN_NUM_CLASSES

/* ── Weight sizes (for allocation) ──────────────────────────────── */

/*  Conv1: OUT_CH kernels of KH × KW × IN_C */
#define GOLDEN_CONV1_WEIGHT_SIZE  (GOLDEN_CONV1_OUT_CH * GOLDEN_CONV1_KH * GOLDEN_CONV1_KW * GOLDEN_IN_C)
#define GOLDEN_CONV1_BIAS_SIZE    GOLDEN_CONV1_OUT_CH

/*  Conv2: OUT_CH kernels of KH × KW × IN_CH */
#define GOLDEN_CONV2_WEIGHT_SIZE  (GOLDEN_CONV2_OUT_CH * GOLDEN_CONV2_KH * GOLDEN_CONV2_KW * GOLDEN_CONV2_IN_CH)
#define GOLDEN_CONV2_BIAS_SIZE    GOLDEN_CONV2_OUT_CH

/*  FC: FC_IN × FC_OUT weights + FC_OUT biases */
#define GOLDEN_FC_WEIGHT_SIZE     (GOLDEN_FC_IN * GOLDEN_FC_OUT)
#define GOLDEN_FC_BIAS_SIZE       GOLDEN_FC_OUT

/* ── Model weights container ────────────────────────────────────── */
/* Fields use float (IEEE 754 single) stored as raw bytes.
 * sizeof(float)==sizeof(int32_t)==4, so total size is unchanged (99192 B).
 * The ARM Cortex-A9 VFP unit handles float arithmetic natively.       */

typedef struct {
    float conv1_w[GOLDEN_CONV1_WEIGHT_SIZE];  /* [OUT_CH][KH][KW][IN_C] */
    float conv1_b[GOLDEN_CONV1_BIAS_SIZE];
    float conv2_w[GOLDEN_CONV2_WEIGHT_SIZE];  /* [OUT_CH][KH][KW][IN_CH] */
    float conv2_b[GOLDEN_CONV2_BIAS_SIZE];
    float fc_w[GOLDEN_FC_WEIGHT_SIZE];        /* [FC_IN][FC_OUT] row-major */
    float fc_b[GOLDEN_FC_BIAS_SIZE];
} GoldenWeights;

/* ── Per-layer dump callback (for comparison against CGRA) ──────── */

typedef void (*golden_layer_dump_fn)(
    const char *layer_name,   /* e.g. "conv1", "pool1", "fc" */
    const float *data,        /* layer output buffer */
    int size,                 /* number of float elements */
    void *user_data           /* caller context */
);

/* ── Inference context ──────────────────────────────────────────── */

typedef struct {
    /* Intermediate buffers (pre-allocated) */
    float conv1_out[GOLDEN_CONV1_OUT_CH * GOLDEN_IN_H * GOLDEN_IN_W];
    float pool1_out[GOLDEN_CONV1_OUT_CH * GOLDEN_POOL1_H * GOLDEN_POOL1_W];
    float conv2_out[GOLDEN_CONV2_OUT_CH * GOLDEN_POOL1_H * GOLDEN_POOL1_W];
    float pool2_out[GOLDEN_CONV2_OUT_CH * GOLDEN_POOL2_H * GOLDEN_POOL2_W];
    float fc_out[GOLDEN_FC_OUT];

    /* Optional dump hook */
    golden_layer_dump_fn dump_fn;
    void *dump_user_data;
} GoldenContext;

/* ── API ────────────────────────────────────────────────────────── */

/**
 * golden_weights_init_synthetic - Fill weights with deterministic
 * pseudo-random values for testing (no trained model needed).
 */
void golden_weights_init_synthetic(GoldenWeights *w, uint32_t seed);

/**
 * golden_weights_load - Load weights from a binary file.
 * File format: raw int32 dump in struct order.
 * Returns 0 on success, -1 on error.
 */
int golden_weights_load(GoldenWeights *w, const char *path);

/**
 * golden_weights_save - Save weights to a binary file.
 * Returns 0 on success, -1 on error.
 */
int golden_weights_save(const GoldenWeights *w, const char *path);

/**
 * golden_context_init - Zero-initialize inference context.
 * Optionally set dump_fn for per-layer output capture.
 */
void golden_context_init(GoldenContext *ctx,
                         golden_layer_dump_fn dump_fn,
                         void *dump_user_data);

/**
 * golden_infer - Run full inference pipeline.
 * @input:  28×28 grayscale image, int32 pixel values [0-255].
 * @w:      Model weights.
 * @ctx:    Inference context (holds intermediate buffers).
 * @out_class: Output: predicted class index [0-29].
 * @out_char:  Output: predicted character.
 * Returns 0 on success.
 */
int golden_infer(const int32_t *input,
                 const GoldenWeights *w,
                 GoldenContext *ctx,
                 int *out_class,
                 char *out_char);

/**
 * golden_get_fc_output - Get raw FC logits after inference.
 * Useful for detailed comparison against CGRA output.
 */
const float *golden_get_fc_output(const GoldenContext *ctx);

/* ── Layer-level functions (exposed for individual testing) ──────── */

void golden_conv2d_relu(const float *input, float *output,
                        const float *weights, const float *bias,
                        int H, int W, int C_in, int C_out,
                        int KH, int KW, int pad, int stride);

void golden_maxpool_2x2(const float *input, float *output,
                        int H, int W, int C);

void golden_fc(const float *input, float *output,
               const float *weights, const float *bias,
               int in_features, int out_features);

int golden_argmax(const float *vec, int len);

#ifdef __cplusplus
}
#endif

#endif /* LPR_GOLDEN_H */
