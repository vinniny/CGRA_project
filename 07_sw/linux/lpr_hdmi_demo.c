/* =============================================================================
 * lpr_hdmi_demo.c — HDMI live demo: display test characters + CGRA predictions.
 *
 * Reads the same demo_lpr_test_images.bin (4500 × 28×28 int32) and
 * golden_weights*.bin used by lpr_eval, picks images sequentially, and:
 *   1. Renders the 28×28 image as a 280×280 tile (10× nearest-neighbor) at
 *      top-left of /dev/fb0.
 *   2. Renders a label box: "CGRA-FC: <char>   ground truth: <char>".
 *   3. Sleeps 200 ms, advances to the next image.
 *
 * Build (CGRA-FC mode by default):
 *   make -C 07_sw/linux hdmi_demo
 * Deploy:
 *   scp build/lpr_hdmi_demo haoyue:/home/root/cgra/
 * Run (after fpgautil + fclk2_enable + cgra_smoke):
 *   /home/root/cgra/lpr_hdmi_demo
 *   /home/root/cgra/lpr_hdmi_demo --arm     # ARM-only mode for compare
 *   /home/root/cgra/lpr_hdmi_demo --delay 100  # ms between images
 *
 * Font: tiny built-in 5×7 pixel font sufficient for label rendering.
 * ============================================================================= */
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <time.h>

#ifdef USE_CGRA_INFER
#include "cgra_baremetal_shim.h"
#endif

#include "lpr_golden.h"
#include "../baremetal/demo_lpr_test_images.h"

#define IMG_W 28
#define IMG_H 28
#define ZOOM  10
#define TILE_W (IMG_W * ZOOM)
#define TILE_H (IMG_H * ZOOM)
#define MARGIN 40

/* ── Tiny 5×7 ASCII font (digits 0-9, A-Z, space). One bit per pixel.
 * Each glyph is 7 bytes; bit 4..0 of each byte = pixel row left-to-right.
 * Just enough for "CGRA-FC: X  GT: Y  ARM: Z" labels. */
static const uint8_t font5x7[][7] = {
    /* '!' through '0' partial — we only encode digits + uppercase + space + ':' + '-' */
    [' ' - ' '] = {0,0,0,0,0,0,0},
    ['-' - ' '] = {0,0,0x1F,0,0,0,0},
    [':' - ' '] = {0,0x06,0x06,0,0x06,0x06,0},
    ['/' - ' '] = {0x01,0x02,0x04,0x08,0x10,0,0},
    ['0' - ' '] = {0x0E,0x11,0x13,0x15,0x19,0x11,0x0E},
    ['1' - ' '] = {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E},
    ['2' - ' '] = {0x0E,0x11,0x01,0x06,0x08,0x10,0x1F},
    ['3' - ' '] = {0x0E,0x11,0x01,0x06,0x01,0x11,0x0E},
    ['4' - ' '] = {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02},
    ['5' - ' '] = {0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E},
    ['6' - ' '] = {0x06,0x08,0x10,0x1E,0x11,0x11,0x0E},
    ['7' - ' '] = {0x1F,0x01,0x02,0x04,0x08,0x08,0x08},
    ['8' - ' '] = {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E},
    ['9' - ' '] = {0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C},
    ['A' - ' '] = {0x0E,0x11,0x11,0x1F,0x11,0x11,0x11},
    ['B' - ' '] = {0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E},
    ['C' - ' '] = {0x0E,0x11,0x10,0x10,0x10,0x11,0x0E},
    ['D' - ' '] = {0x1E,0x11,0x11,0x11,0x11,0x11,0x1E},
    ['E' - ' '] = {0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F},
    ['F' - ' '] = {0x1F,0x10,0x10,0x1E,0x10,0x10,0x10},
    ['G' - ' '] = {0x0E,0x11,0x10,0x17,0x11,0x11,0x0F},
    ['H' - ' '] = {0x11,0x11,0x11,0x1F,0x11,0x11,0x11},
    ['I' - ' '] = {0x0E,0x04,0x04,0x04,0x04,0x04,0x0E},
    ['J' - ' '] = {0x07,0x02,0x02,0x02,0x02,0x12,0x0C},
    ['K' - ' '] = {0x11,0x12,0x14,0x18,0x14,0x12,0x11},
    ['L' - ' '] = {0x10,0x10,0x10,0x10,0x10,0x10,0x1F},
    ['M' - ' '] = {0x11,0x1B,0x15,0x15,0x11,0x11,0x11},
    ['N' - ' '] = {0x11,0x11,0x19,0x15,0x13,0x11,0x11},
    ['O' - ' '] = {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E},
    ['P' - ' '] = {0x1E,0x11,0x11,0x1E,0x10,0x10,0x10},
    ['Q' - ' '] = {0x0E,0x11,0x11,0x11,0x15,0x12,0x0D},
    ['R' - ' '] = {0x1E,0x11,0x11,0x1E,0x14,0x12,0x11},
    ['S' - ' '] = {0x0E,0x11,0x10,0x0E,0x01,0x11,0x0E},
    ['T' - ' '] = {0x1F,0x04,0x04,0x04,0x04,0x04,0x04},
    ['U' - ' '] = {0x11,0x11,0x11,0x11,0x11,0x11,0x0E},
    ['V' - ' '] = {0x11,0x11,0x11,0x11,0x11,0x0A,0x04},
    ['W' - ' '] = {0x11,0x11,0x11,0x15,0x15,0x15,0x0A},
    ['X' - ' '] = {0x11,0x11,0x0A,0x04,0x0A,0x11,0x11},
    ['Y' - ' '] = {0x11,0x11,0x11,0x0A,0x04,0x04,0x04},
    ['Z' - ' '] = {0x1F,0x01,0x02,0x04,0x08,0x10,0x1F},
};
#define FONT_LAST (sizeof(font5x7) / 7)
#define FONT_SCALE 4   /* pixels per font cell side */

typedef struct {
    int      fd;
    uint8_t *map;
    int      w, h, bpp, stride;
    size_t   size;
} fb_t;

static int fb_open(fb_t *fb)
{
    fb->fd = open("/dev/fb0", O_RDWR);
    if (fb->fd < 0) { perror("open /dev/fb0"); return -1; }
    struct fb_var_screeninfo v;
    struct fb_fix_screeninfo f;
    if (ioctl(fb->fd, FBIOGET_VSCREENINFO, &v) < 0) { perror("vinfo"); return -1; }
    if (ioctl(fb->fd, FBIOGET_FSCREENINFO, &f) < 0) { perror("finfo"); return -1; }
    fb->w = v.xres; fb->h = v.yres;
    fb->bpp = v.bits_per_pixel; fb->stride = f.line_length;
    fb->size = f.smem_len;
    fb->map = mmap(NULL, fb->size, PROT_READ|PROT_WRITE, MAP_SHARED, fb->fd, 0);
    if (fb->map == MAP_FAILED) { perror("mmap fb"); return -1; }
    fprintf(stderr, "[fb] %dx%d %dbpp stride=%d\n", fb->w, fb->h, fb->bpp, fb->stride);
    return 0;
}

static inline void fb_pixel(fb_t *fb, int x, int y, uint32_t bgr)
{
    if (x < 0 || y < 0 || x >= fb->w || y >= fb->h) return;
    uint8_t *p = fb->map + y * fb->stride + x * (fb->bpp / 8);
    if (fb->bpp == 24) {
        p[0] = bgr & 0xFF;          /* B */
        p[1] = (bgr >> 8) & 0xFF;   /* G */
        p[2] = (bgr >> 16) & 0xFF;  /* R */
    } else if (fb->bpp == 32) {
        ((uint32_t *)p)[0] = bgr;
    }
}

static void fb_rect(fb_t *fb, int x0, int y0, int w, int h, uint32_t bgr)
{
    for (int dy = 0; dy < h; dy++)
        for (int dx = 0; dx < w; dx++)
            fb_pixel(fb, x0 + dx, y0 + dy, bgr);
}

static void fb_draw_char(fb_t *fb, int x, int y, char c, uint32_t fg)
{
    if (c < ' ' || c >= ' ' + (int)FONT_LAST) c = ' ';
    const uint8_t *g = font5x7[c - ' '];
    for (int row = 0; row < 7; row++) {
        uint8_t bits = g[row];
        for (int col = 0; col < 5; col++) {
            if (bits & (1 << (4 - col)))
                fb_rect(fb, x + col * FONT_SCALE, y + row * FONT_SCALE, FONT_SCALE, FONT_SCALE, fg);
        }
    }
}

static void fb_draw_text(fb_t *fb, int x, int y, const char *s, uint32_t fg)
{
    for (int i = 0; s[i]; i++)
        fb_draw_char(fb, x + i * 6 * FONT_SCALE, y, s[i], fg);
}

/* Render 28×28 grayscale (int32 [0..255]) as a TILE_W × TILE_H tile at (x0,y0). */
static void fb_draw_image28(fb_t *fb, int x0, int y0, const int32_t *img)
{
    for (int j = 0; j < IMG_H; j++)
        for (int i = 0; i < IMG_W; i++) {
            int v = img[j * IMG_W + i];
            if (v < 0) v = 0; if (v > 255) v = 255;
            uint32_t c = ((uint32_t)v << 16) | ((uint32_t)v << 8) | (uint32_t)v;
            fb_rect(fb, x0 + i * ZOOM, y0 + j * ZOOM, ZOOM, ZOOM, c);
        }
}

static double now_s(void)
{
    struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t);
    return (double)t.tv_sec + (double)t.tv_nsec * 1e-9;
}

int main(int argc, char **argv)
{
    int use_cgra = 1;
    int delay_ms = 200;
    for (int i = 1; i < argc; i++) {
        if      (!strcmp(argv[i], "--arm"))    use_cgra = 0;
        else if (!strcmp(argv[i], "--cgra"))   use_cgra = 1;
        else if (!strcmp(argv[i], "--delay") && i + 1 < argc) delay_ms = atoi(argv[++i]);
    }
#ifndef USE_CGRA_INFER
    if (use_cgra) { fprintf(stderr, "rebuild with -DUSE_CGRA_INFER for --cgra\n"); return 1; }
#endif

    /* ── Load weights + images ─────────────────────────────────── */
    GoldenWeights *w = calloc(1, sizeof(*w));
    if (golden_weights_load(w, "golden_weights.bin") != 0) return 1;
    size_t img_bytes = (size_t)LPR_TEST_NUM_IMAGES * IMG_W * IMG_H * sizeof(int32_t);
    int32_t *images = malloc(img_bytes);
    FILE *f = fopen("demo_lpr_test_images.bin", "rb");
    if (!f) { perror("demo_lpr_test_images.bin"); return 1; }
    fread(images, 1, img_bytes, f); fclose(f);
    GoldenContext *ctx = calloc(1, sizeof(*ctx));

#ifdef USE_CGRA_INFER
    cgra_dev_t cgra_dev = {0};
    int memfd = -1; void *int16_blob = NULL;
    if (use_cgra) {
        if (cgra_init(&cgra_dev, NULL) < 0) return 1;
        cgra_shim_attach(&cgra_dev);
        memfd = open("/dev/mem", O_RDWR | O_SYNC);
        if (mmap((void *)(uintptr_t)LPR_CGRA_POOL2_Q_DDR,   0x1000, PROT_READ|PROT_WRITE,
                 MAP_SHARED|MAP_FIXED, memfd, LPR_CGRA_POOL2_Q_DDR) == MAP_FAILED) return 1;
        if (mmap((void *)(uintptr_t)LPR_CGRA_STAGING_DDR, 0x1000, PROT_READ|PROT_WRITE,
                 MAP_SHARED|MAP_FIXED, memfd, LPR_CGRA_STAGING_DDR) == MAP_FAILED) return 1;
        FILE *wf = fopen("golden_weights_int16.bin", "rb");
        if (!wf) { perror("golden_weights_int16.bin"); return 1; }
        fseek(wf, 0, SEEK_END); long sz = ftell(wf); fseek(wf, 0, SEEK_SET);
        int16_blob = malloc(sz); fread(int16_blob, 1, sz, wf); fclose(wf);
    }
#endif

    fb_t fb = {0};
    if (fb_open(&fb) != 0) return 1;

    /* Clear screen to dark blue */
    fb_rect(&fb, 0, 0, fb.w, fb.h, 0x001020);
    /* Banner */
    fb_draw_text(&fb, MARGIN, MARGIN, use_cgra ? "CGRA-FC LPR DEMO" : "ARM-ONLY LPR DEMO", 0xFFFFFF);

    int correct = 0;
    int seen = 0;
    double t0 = now_s();

    for (int i = 0;; i = (i + 1) % LPR_TEST_NUM_IMAGES) {
        const int32_t *img = images + (size_t)i * IMG_W * IMG_H;
        char gt = lpr_test_chars[i];
        int   pred_cls = -1;
        char  pred_ch  = '?';

        double t1 = now_s();
#ifdef USE_CGRA_INFER
        int rc = use_cgra
               ? golden_infer_cgra(img, w, ctx, int16_blob, &pred_cls, &pred_ch)
               : golden_infer     (img, w, ctx,             &pred_cls, &pred_ch);
#else
        int rc = golden_infer(img, w, ctx, &pred_cls, &pred_ch);
#endif
        double dt_ms = (now_s() - t1) * 1000.0;
        if (rc != 0) continue;

        seen++;
        if (pred_ch == gt) correct++;

        /* Image tile */
        fb_draw_image28(&fb, MARGIN, MARGIN + 80, img);
        /* Labels */
        fb_rect(&fb, MARGIN + TILE_W + MARGIN, MARGIN + 80, 600, TILE_H, 0x001020);

        char line[64];
        int ly = MARGIN + 80;
        snprintf(line, sizeof line, "PREDICTION: %c", pred_ch);
        fb_draw_text(&fb, MARGIN + TILE_W + MARGIN, ly, line, pred_ch == gt ? 0x00FF40 : 0xFF4040);
        ly += 8 * FONT_SCALE;
        snprintf(line, sizeof line, "GROUND TRUTH: %c", gt);
        fb_draw_text(&fb, MARGIN + TILE_W + MARGIN, ly, line, 0xFFFFFF);
        ly += 8 * FONT_SCALE;
        snprintf(line, sizeof line, "INFER MS: %3d", (int)dt_ms);
        fb_draw_text(&fb, MARGIN + TILE_W + MARGIN, ly, line, 0xFFFF80);
        ly += 8 * FONT_SCALE;
        snprintf(line, sizeof line, "ACC: %d/%d %d PCT", correct, seen, (int)(100.0 * correct / seen));
        fb_draw_text(&fb, MARGIN + TILE_W + MARGIN, ly, line, 0xFFFFFF);
        ly += 12 * FONT_SCALE;
        snprintf(line, sizeof line, "MODE: %s", use_cgra ? "CGRA-FC" : "ARM-ONLY");
        fb_draw_text(&fb, MARGIN + TILE_W + MARGIN, ly, line, 0x40A0FF);

        if (delay_ms > 0) usleep(delay_ms * 1000);

        /* Print to console too */
        if (seen % 50 == 0) {
            double dur = now_s() - t0;
            fprintf(stderr, "[demo] seen=%d acc=%.2f%% chars/s=%.1f\n",
                    seen, 100.0 * correct / seen, seen / dur);
        }
    }
    return 0;
}
