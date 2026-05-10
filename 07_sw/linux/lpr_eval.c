/* =============================================================================
 * lpr_eval.c — Linux user-space accuracy eval for the VN LPR golden model.
 *
 * Phase L2 baseline: float Conv1+Pool1+Conv2+Pool2+FC on ARM Cortex-A9.
 * Iterates the held-out 4500-image VN-char test set and reports top-1 accuracy
 * + per-class breakdown. No CGRA touch — this locks the algorithm baseline
 * before we offload the FC layer (Phase L2 next step).
 *
 * Inputs:
 *   golden_weights.bin           — 24798 float32 weights (Conv1/2 + FC)
 *   demo_lpr_test_images.bin     — 4500 × 28×28 int32 pixels [0..255]
 *   demo_lpr_test_images.h       — embedded ground-truth char[4500]
 *
 * Build:    make -C 07_sw/linux eval
 * Deploy:   scp build/lpr_eval haoyue:/home/root/cgra/
 *           scp ../lprnet_eval/golden_weights.bin haoyue:/home/root/cgra/
 *           # demo_lpr_test_images.bin is already on board
 * Run:      /home/root/cgra/lpr_eval [weights.bin] [images.bin]
 * ============================================================================= */
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#ifdef USE_CGRA_INFER
#include "cgra_baremetal_shim.h"   /* must come before lpr_golden.h on -DUSE_CGRA_INFER */
#endif

#include "lpr_golden.h"
#include "../baremetal/demo_lpr_test_images.h"   /* lpr_test_chars[4500] */

#define IMG_PIXELS  784
#define N_IMAGES    LPR_TEST_NUM_IMAGES

static double now_s(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (double)t.tv_sec + (double)t.tv_nsec * 1e-9;
}

static int load_blob(const char *path, void *buf, size_t bytes)
{
    FILE *f = fopen(path, "rb");
    if (!f) { perror(path); return -1; }
    size_t n = fread(buf, 1, bytes, f);
    fclose(f);
    if (n != bytes) {
        fprintf(stderr, "%s: short read %zu/%zu\n", path, n, bytes);
        return -1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);   /* unbuffered so progress shows live over SSH */
    /* Optional first arg "-c" enables CGRA-FC mode (Conv on ARM, FC on CGRA).
     * Without it, we run pure-ARM golden_infer. */
    int use_cgra = 0;
    int argi = 1;
    if (argc > argi && !strcmp(argv[argi], "-c")) { use_cgra = 1; argi++; }
    const char *wpath  = (argc > argi) ? argv[argi++] : "golden_weights.bin";
    const char *impath = (argc > argi) ? argv[argi++] : "demo_lpr_test_images.bin";

#ifndef USE_CGRA_INFER
    if (use_cgra) {
        fprintf(stderr, "lpr_eval was built without -DUSE_CGRA_INFER; rebuild with `make eval_cgra`\n");
        return 1;
    }
#endif

#ifdef USE_CGRA_INFER
    /* CGRA-FC mode setup: mmap MAP_FIXED uncached scratch + open CGRA. */
    cgra_dev_t cgra_dev = {0};
    int memfd = -1;
    void *pool2_va = NULL, *staging_va = NULL;
    void *int16_blob = NULL;
    if (use_cgra) {
        if (cgra_init(&cgra_dev, NULL) < 0) { perror("cgra_init"); return 1; }
        cgra_shim_attach(&cgra_dev);
        memfd = open("/dev/mem", O_RDWR | O_SYNC);
        if (memfd < 0) { perror("/dev/mem"); return 1; }
        pool2_va   = mmap((void *)(uintptr_t)LPR_CGRA_POOL2_Q_DDR, 0x1000,
                          PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED,
                          memfd, LPR_CGRA_POOL2_Q_DDR);
        staging_va = mmap((void *)(uintptr_t)LPR_CGRA_STAGING_DDR, 0x1000,
                          PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED,
                          memfd, LPR_CGRA_STAGING_DDR);
        if (pool2_va   == MAP_FAILED || (uintptr_t)pool2_va   != LPR_CGRA_POOL2_Q_DDR ||
            staging_va == MAP_FAILED || (uintptr_t)staging_va != LPR_CGRA_STAGING_DDR) {
            fprintf(stderr, "MAP_FIXED scratch alloc failed\n"); return 1;
        }
        memset(pool2_va,   0, 0x1000);
        memset(staging_va, 0, 0x1000);

        /* Load int16 weight blob into a regular RAM buffer (CPU-side only). */
        const char *int16_path = "golden_weights_int16.bin";
        FILE *f = fopen(int16_path, "rb");
        if (!f) { perror(int16_path); return 1; }
        fseek(f, 0, SEEK_END);
        long sz = ftell(f);
        fseek(f, 0, SEEK_SET);
        int16_blob = malloc(sz);
        if (fread(int16_blob, 1, sz, f) != (size_t)sz) { fprintf(stderr, "int16 short read\n"); return 1; }
        fclose(f);
        fprintf(stderr, "[eval] CGRA mode: scratch @ 0x%08lx (pool2) + 0x%08lx (staging), int16 blob %ld B\n",
                LPR_CGRA_POOL2_Q_DDR, LPR_CGRA_STAGING_DDR, sz);
    }
#endif

    /* ── Load weights ──────────────────────────────────────────── */
    GoldenWeights *w = calloc(1, sizeof(*w));
    if (!w) { perror("calloc weights"); return 1; }
    if (golden_weights_load(w, wpath) != 0) {
        fprintf(stderr, "failed to load %s\n", wpath);
        return 1;
    }
    printf("[eval] loaded weights from %s\n", wpath);

    /* ── Load test images (4500 × 784 × int32) ─────────────────── */
    size_t img_bytes = (size_t)N_IMAGES * IMG_PIXELS * sizeof(int32_t);
    int32_t *images = malloc(img_bytes);
    if (!images) { perror("malloc images"); return 1; }
    if (load_blob(impath, images, img_bytes) != 0) return 1;
    printf("[eval] loaded %d images (%zu bytes) from %s\n",
           N_IMAGES, img_bytes, impath);

    /* ── Inference context ─────────────────────────────────────── */
    GoldenContext *ctx = calloc(1, sizeof(*ctx));
    if (!ctx) { perror("calloc ctx"); return 1; }

    /* ── Sweep ─────────────────────────────────────────────────── */
    int correct = 0;
    int per_correct[VN_NUM_CLASSES] = {0};
    int per_total  [VN_NUM_CLASSES] = {0};
    double t0 = now_s();

    for (int i = 0; i < N_IMAGES; i++) {
        int   pred_cls = -1;
        char  pred_ch  = '?';
        const int32_t *img = images + (size_t)i * IMG_PIXELS;

#ifdef USE_CGRA_INFER
        int rc = use_cgra
               ? golden_infer_cgra(img, w, ctx, int16_blob, &pred_cls, &pred_ch)
               : golden_infer     (img, w, ctx,             &pred_cls, &pred_ch);
#else
        int rc = golden_infer(img, w, ctx, &pred_cls, &pred_ch);
#endif
        if (rc != 0) {
            fprintf(stderr, "infer failed @ image %d\n", i);
            return 1;
        }

        char gt_ch  = lpr_test_chars[i];
        int  gt_cls = -1;
        for (int c = 0; c < VN_NUM_CLASSES; c++)
            if (VN_CHAR_MAP[c] == gt_ch) { gt_cls = c; break; }
        if (gt_cls < 0) {
            fprintf(stderr, "unknown gt char '%c' @ image %d\n", gt_ch, i);
            return 1;
        }

        per_total[gt_cls]++;
        if (pred_cls == gt_cls) {
            correct++;
            per_correct[gt_cls]++;
        }

        /* Print at 5/50 first, then every 100 images, so we get fast feedback
         * in CGRA mode (which is ~10× slower than ARM). */
        if (i == 4 || i == 49 || ((i + 1) % 100 == 0))
            printf("  ... %4d/%d  acc=%.2f%%\n",
                   i + 1, N_IMAGES, 100.0 * correct / (i + 1));
    }

    double dt = now_s() - t0;

    /* ── Report ────────────────────────────────────────────────── */
    printf("\n==== LPR Linux %s eval ====\n", use_cgra ? "ARM-Conv + CGRA-FC" : "ARM-only");
    printf("  images       : %d\n", N_IMAGES);
    printf("  correct      : %d\n", correct);
    printf("  top-1 accuracy: %.2f%%\n", 100.0 * correct / N_IMAGES);
    printf("  wall time    : %.2f s  (%.2f ms/img)\n",
           dt, 1000.0 * dt / N_IMAGES);

    printf("\n  Per-class:\n  Char  Correct/Total   Acc\n");
    for (int c = 0; c < VN_NUM_CLASSES; c++) {
        if (per_total[c] == 0) continue;
        printf("  %c     %6d/%-6d  %6.2f%%\n",
               VN_CHAR_MAP[c], per_correct[c], per_total[c],
               100.0 * per_correct[c] / per_total[c]);
    }

    free(images);
    free(ctx);
    free(w);
    return (correct == N_IMAGES) ? 0 : (correct >= N_IMAGES * 89 / 100 ? 0 : 2);
}
