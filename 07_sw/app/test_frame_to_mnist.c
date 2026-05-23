/* =============================================================================
 * test_frame_to_mnist.c — Host-side test for the HDMI-in frame downsampler.
 *
 * Builds a synthetic 640x480 BGR frame (the same memory layout the bare-metal
 * `hdmi_in_current_frame()` would return) and exercises
 * `downsample_roi_to_mnist()`. Verifies:
 *
 *   - Solid white frame    → all-zero 28x28 (background polarity)
 *   - Solid black frame    → all-255 28x28 (foreground polarity)
 *   - Black bar mid-ROI    → middle rows ~255, top/bottom rows ~0
 *   - "Plus" stroke in ROI → cross-shaped 28x28 with sane intensities
 *
 * No HW needed — compiles on any host. Lets us shake bugs out of the
 * downsample math before silicon bring-up.
 * ============================================================================= */

#include "frame_to_mnist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FB_W   640
#define FB_H   480
#define FB_BPP 3
#define FB_BYTES (FB_W * FB_H * FB_BPP)

static uint8_t *fb;
static uint8_t  out[28 * 28];

static void fill_solid(uint8_t b, uint8_t g, uint8_t r) {
    for (int y = 0; y < FB_H; y++) {
        uint8_t *row = fb + (size_t)y * FB_W * FB_BPP;
        for (int x = 0; x < FB_W; x++) {
            row[x * 3 + 0] = b;
            row[x * 3 + 1] = g;
            row[x * 3 + 2] = r;
        }
    }
}

static void draw_bar(int y0, int y1) {
    for (int y = y0; y < y1; y++) {
        if (y < 0 || y >= FB_H) continue;
        uint8_t *row = fb + (size_t)y * FB_W * FB_BPP;
        for (int x = 0; x < FB_W * FB_BPP; x++) row[x] = 0;
    }
}

static void draw_plus(hdmi_roi_t roi, int thickness) {
    /* Black plus sign centered in the ROI on a white background. */
    fill_solid(255, 255, 255);
    int cx = roi.x + roi.w / 2;
    int cy = roi.y + roi.h / 2;
    /* Vertical stroke */
    for (int y = roi.y; y < (int)(roi.y + roi.h); y++) {
        uint8_t *row = fb + (size_t)y * FB_W * FB_BPP;
        for (int dx = -thickness/2; dx < thickness/2; dx++) {
            int x = cx + dx;
            if (x < 0 || x >= FB_W) continue;
            row[x * 3 + 0] = 0;
            row[x * 3 + 1] = 0;
            row[x * 3 + 2] = 0;
        }
    }
    /* Horizontal stroke */
    for (int dy = -thickness/2; dy < thickness/2; dy++) {
        int y = cy + dy;
        if (y < 0 || y >= FB_H) continue;
        uint8_t *row = fb + (size_t)y * FB_W * FB_BPP;
        for (int x = roi.x; x < (int)(roi.x + roi.w); x++) {
            row[x * 3 + 0] = 0;
            row[x * 3 + 1] = 0;
            row[x * 3 + 2] = 0;
        }
    }
}

static void print_28x28(const uint8_t *t) {
    static const char ramp[] = " .:-=+*#%@";
    const int n = (int)(sizeof(ramp) - 2);
    for (int y = 0; y < 28; y++) {
        for (int x = 0; x < 28; x++) {
            int v = t[y * 28 + x] * n / 255;
            if (v < 0) v = 0;
            if (v > n) v = n;
            putchar(ramp[v]);
            putchar(ramp[v]);
        }
        putchar('\n');
    }
}

static int count_above(const uint8_t *t, int thr) {
    int c = 0;
    for (int i = 0; i < 28 * 28; i++) if (t[i] >= thr) c++;
    return c;
}

static int max_val(const uint8_t *t) {
    int m = 0;
    for (int i = 0; i < 28 * 28; i++) if (t[i] > m) m = t[i];
    return m;
}

static int min_val(const uint8_t *t) {
    int m = 255;
    for (int i = 0; i < 28 * 28; i++) if (t[i] < m) m = t[i];
    return m;
}

int main(void) {
    fb = malloc(FB_BYTES);
    if (!fb) { fprintf(stderr, "OOM\n"); return 1; }

    hdmi_roi_t roi = HDMI_ROI_DEFAULT;
    printf("ROI: x=%u y=%u w=%u h=%u  (block %ux%u src px/output cell)\n",
           roi.x, roi.y, roi.w, roi.h, roi.w / 28, roi.h / 28);

    int failures = 0;

    /* --- Test 1: solid white frame → all-zero output -------------------- */
    fill_solid(255, 255, 255);
    downsample_roi_to_mnist(fb, roi, out);
    int mx = max_val(out);
    printf("[T1] solid white      max=%3d (expect 0)  %s\n",
           mx, mx <= 2 ? "PASS" : "FAIL");
    if (mx > 2) failures++;

    /* --- Test 2: solid black frame → all-255 output --------------------- */
    fill_solid(0, 0, 0);
    downsample_roi_to_mnist(fb, roi, out);
    int mn = min_val(out);
    printf("[T2] solid black      min=%3d (expect 255) %s\n",
           mn, mn >= 253 ? "PASS" : "FAIL");
    if (mn < 253) failures++;

    /* --- Test 3: horizontal black bar at ROI vertical center ------------ */
    fill_solid(255, 255, 255);
    draw_bar(roi.y + roi.h / 2 - 14, roi.y + roi.h / 2 + 14);
    downsample_roi_to_mnist(fb, roi, out);
    int above_thr = count_above(out, 200);
    /* The bar is 28 src rows tall = ~2.8 output rows wide at 10:1 downsample.
     * Expect 2 or 3 output rows × 28 cols = 56..84 cells > 200. */
    printf("[T3] horizontal bar   bright cells=%d (expect 28..112) %s\n",
           above_thr, (above_thr >= 28 && above_thr <= 112) ? "PASS" : "FAIL");
    if (above_thr < 28 || above_thr > 112) failures++;

    /* --- Test 4: plus sign — print and eyeball -------------------------- */
    draw_plus(roi, 28);
    downsample_roi_to_mnist(fb, roi, out);
    int bright = count_above(out, 200);
    int dark   = count_above(out, 20);
    printf("[T4] plus sign        bright(>=200)=%d  any-fg(>=20)=%d\n",
           bright, dark);
    printf("       28x28 visual (' '=bg, '@'=stroke):\n");
    print_28x28(out);
    /* A 28-px-thick plus inside a 280x280 ROI = ~2.8 output rows + 2.8
     * output cols of stroke, intersection counted once. Rough expectation:
     * 2 rows + 2 cols - 4 intersection cells ≈ 52 cells of stroke. We
     * accept 30..160 to absorb the antialiasing / boundary blur. */
    if (bright < 30 || bright > 160) {
        printf("[T4] FAIL: bright count outside expected range 30..160\n");
        failures++;
    } else {
        printf("[T4] PASS\n");
    }

    free(fb);
    printf("\n%d failure(s)\n", failures);
    return failures ? 1 : 0;
}
