/* ===================================================================
 *  lpr_golden_test.c – Standalone test for the golden model
 *
 *  Runs inference on synthetic 28×28 character images, dumps per-layer
 *  outputs to binary files for comparison against CGRA results.
 *
 *  No hardware dependency — builds and runs on any Linux (x86 or ARM).
 *
 *  Usage:
 *    ./lpr_golden_test                       # synthetic weights + images
 *    ./lpr_golden_test weights.bin           # load trained weights
 *    ./lpr_golden_test weights.bin image.bin # load weights + one image
 * =================================================================== */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "../lib/lpr_golden.h"

/* ── Test image generation ──────────────────────────────────────── */

static void generate_test_image(int32_t *img, int index)
{
    uint32_t rng = (uint32_t)(index * 2654435761u + 1);
    for (int i = 0; i < GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C; i++) {
        rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
        img[i] = (int32_t)(rng & 0xFF);
    }
}

static int load_image_file(const char *path, int32_t *img)
{
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    size_t n = fread(img, sizeof(int32_t),
                     GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C, f);
    fclose(f);
    return (n == (size_t)(GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C)) ? 0 : -1;
}

/* ── Layer dump callback ────────────────────────────────────────── */

typedef struct {
    const char *out_dir;
    int image_index;
} DumpCtx;

static void dump_layer(const char *layer_name, const float *data,
                       int size, void *user_data)
{
    DumpCtx *dctx = (DumpCtx *)user_data;
    char path[512];

    snprintf(path, sizeof(path), "%s/img%02d_%s.bin",
             dctx->out_dir, dctx->image_index, layer_name);

    FILE *f = fopen(path, "wb");
    if (f) {
        fwrite(data, sizeof(float), (size_t)size, f);
        fclose(f);
        printf("  [dump] %s (%d values)\n", path, size);
    } else {
        fprintf(stderr, "  [dump] FAILED to write %s\n", path);
    }
}

/* ── Timing ─────────────────────────────────────────────────────── */

static double time_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

/* ── Main ───────────────────────────────────────────────────────── */

#define NUM_TEST_IMAGES 10
#define DUMP_DIR        "golden_dump"

int main(int argc, char *argv[])
{
    const char *weights_path = NULL;
    const char *image_path   = NULL;

    if (argc > 1) weights_path = argv[1];
    if (argc > 2) image_path   = argv[2];

    printf("========================================\n");
    printf("  Golden Model – VN License Plate OCR\n");
    printf("  28x28 → Conv1→Pool1→Conv2→Pool2→FC\n");
    printf("  %d classes (Vietnamese plate charset)\n", VN_NUM_CLASSES);
    printf("========================================\n\n");

    /* ── Print network summary ──────────────────────────────────── */
    printf("Network architecture:\n");
    printf("  Input:  %dx%dx%d\n", GOLDEN_IN_H, GOLDEN_IN_W, GOLDEN_IN_C);
    printf("  Conv1:  %dx%d, %d→%d ch, pad=%d → %dx%dx%d + ReLU\n",
           GOLDEN_CONV1_KH, GOLDEN_CONV1_KW,
           GOLDEN_IN_C, GOLDEN_CONV1_OUT_CH, GOLDEN_CONV1_PAD,
           GOLDEN_IN_H, GOLDEN_IN_W, GOLDEN_CONV1_OUT_CH);
    printf("  Pool1:  2x2 max → %dx%dx%d\n",
           GOLDEN_POOL1_H, GOLDEN_POOL1_W, GOLDEN_CONV1_OUT_CH);
    printf("  Conv2:  %dx%d, %d→%d ch, pad=%d → %dx%dx%d + ReLU\n",
           GOLDEN_CONV2_KH, GOLDEN_CONV2_KW,
           GOLDEN_CONV2_IN_CH, GOLDEN_CONV2_OUT_CH, GOLDEN_CONV2_PAD,
           GOLDEN_POOL1_H, GOLDEN_POOL1_W, GOLDEN_CONV2_OUT_CH);
    printf("  Pool2:  2x2 max → %dx%dx%d\n",
           GOLDEN_POOL2_H, GOLDEN_POOL2_W, GOLDEN_CONV2_OUT_CH);
    printf("  FC:     %d → %d\n", GOLDEN_FC_IN, GOLDEN_FC_OUT);
    printf("  Total weights: %zu float values (%zu bytes)\n",
           sizeof(GoldenWeights) / sizeof(float),
           sizeof(GoldenWeights));
    printf("\n");

    /* ── Load or generate weights ───────────────────────────────── */
    GoldenWeights *weights = (GoldenWeights *)malloc(sizeof(GoldenWeights));
    if (!weights) {
        fprintf(stderr, "Failed to allocate weights\n");
        return 1;
    }

    if (weights_path) {
        printf("Loading weights from: %s\n", weights_path);
        if (golden_weights_load(weights, weights_path) != 0) {
            fprintf(stderr, "Failed to load weights, using synthetic\n");
            golden_weights_init_synthetic(weights, 42);
        }
    } else {
        printf("Using synthetic weights (seed=42)\n");
        golden_weights_init_synthetic(weights, 42);

        /* Save synthetic weights so CGRA test can load the same ones */
        if (golden_weights_save(weights, "golden_weights.bin") == 0)
            printf("Saved synthetic weights → golden_weights.bin\n");
    }

    /* ── Create dump directory ──────────────────────────────────── */
    {
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "mkdir -p %s", DUMP_DIR);
        if (system(cmd) != 0)
            fprintf(stderr, "Warning: could not create %s\n", DUMP_DIR);
    }

    /* ── Set up inference context with layer dumping ─────────────── */
    GoldenContext ctx;
    DumpCtx dctx = { .out_dir = DUMP_DIR, .image_index = 0 };
    golden_context_init(&ctx, dump_layer, &dctx);

    /* ── Run inference ──────────────────────────────────────────── */
    int32_t *img = (int32_t *)malloc(GOLDEN_IN_H * GOLDEN_IN_W *
                                     GOLDEN_IN_C * sizeof(int32_t));
    if (!img) {
        fprintf(stderr, "Failed to allocate image buffer\n");
        free(weights);
        return 1;
    }

    int num_images = image_path ? 1 : NUM_TEST_IMAGES;
    double total_ms = 0;

    printf("\n--- Running %d inference(s) ---\n\n", num_images);

    for (int i = 0; i < num_images; i++) {
        dctx.image_index = i;

        if (image_path) {
            printf("[IMG %2d] Loading: %s\n", i, image_path);
            if (load_image_file(image_path, img) != 0) {
                fprintf(stderr, "  Failed to load image\n");
                continue;
            }
        } else {
            generate_test_image(img, i);
        }

        double t0 = time_ms();

        int cls;
        char ch;
        int rc = golden_infer(img, weights, &ctx, &cls, &ch);

        double t1 = time_ms();
        double ms = t1 - t0;
        total_ms += ms;

        if (rc == 0) {
            printf("[IMG %2d] class=%2d char='%c'  %.3f ms\n",
                   i, cls, ch, ms);

            /* Print top-3 logits for debugging */
            const float *logits = golden_get_fc_output(&ctx);
            int top[3] = {0, 0, 0};
            for (int j = 0; j < GOLDEN_FC_OUT; j++) {
                if (logits[j] > logits[top[0]]) {
                    top[2] = top[1]; top[1] = top[0]; top[0] = j;
                } else if (logits[j] > logits[top[1]]) {
                    top[2] = top[1]; top[1] = j;
                } else if (logits[j] > logits[top[2]]) {
                    top[2] = j;
                }
            }
            printf("         top3: '%c'(%.2f) '%c'(%.2f) '%c'(%.2f)\n",
                   VN_CHAR_MAP[top[0]], logits[top[0]],
                   VN_CHAR_MAP[top[1]], logits[top[1]],
                   VN_CHAR_MAP[top[2]], logits[top[2]]);
        } else {
            printf("[IMG %2d] inference FAILED (rc=%d)\n", i, rc);
        }

        printf("\n");
    }

    /* ── Summary ────────────────────────────────────────────────── */
    printf("========================================\n");
    printf("  Summary (%d images)\n", num_images);
    printf("========================================\n");
    printf("  Total time: %.3f ms\n", total_ms);
    printf("  Avg time:   %.3f ms/image\n", total_ms / num_images);
    printf("  Throughput: %.1f images/sec\n",
           total_ms > 0 ? num_images / (total_ms / 1000.0) : 0);
    printf("  Dump dir:   %s/\n", DUMP_DIR);
    printf("\n");
    printf("Layer dump files per image:\n");
    printf("  imgNN_conv1.bin  – %d values (%dx%dx%d)\n",
           GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_CONV1_OUT_CH,
           GOLDEN_IN_H, GOLDEN_IN_W, GOLDEN_CONV1_OUT_CH);
    printf("  imgNN_pool1.bin  – %d values (%dx%dx%d)\n",
           GOLDEN_POOL1_H * GOLDEN_POOL1_W * GOLDEN_CONV1_OUT_CH,
           GOLDEN_POOL1_H, GOLDEN_POOL1_W, GOLDEN_CONV1_OUT_CH);
    printf("  imgNN_conv2.bin  – %d values (%dx%dx%d)\n",
           GOLDEN_POOL1_H * GOLDEN_POOL1_W * GOLDEN_CONV2_OUT_CH,
           GOLDEN_POOL1_H, GOLDEN_POOL1_W, GOLDEN_CONV2_OUT_CH);
    printf("  imgNN_pool2.bin  – %d values (%dx%dx%d)\n",
           GOLDEN_POOL2_H * GOLDEN_POOL2_W * GOLDEN_CONV2_OUT_CH,
           GOLDEN_POOL2_H, GOLDEN_POOL2_W, GOLDEN_CONV2_OUT_CH);
    printf("  imgNN_fc.bin     – %d values (logits)\n", GOLDEN_FC_OUT);
    printf("\n");
    printf("To compare against CGRA:\n");
    printf("  1. Load golden_weights.bin on target\n");
    printf("  2. Feed same images through CGRA pipeline\n");
    printf("  3. Compare layer outputs: diff golden_dump/ cgra_dump/\n");

    free(img);
    free(weights);

    printf("\nDone.\n");
    return 0;
}
