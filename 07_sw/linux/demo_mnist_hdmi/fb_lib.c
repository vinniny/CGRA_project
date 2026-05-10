/* fb_lib.c — see fb_lib.h for API and design rationale. */

#include "fb_lib.h"
#include "font5x7.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int fb_open(fb_t *fb, unsigned long phys) {
    long ps = sysconf(_SC_PAGESIZE);
    fb->page_off = (size_t)(phys & (unsigned long)(ps - 1));
    unsigned long page_base = phys - fb->page_off;
    fb->map_len = (fb->page_off + FB_BYTES + (size_t)ps - 1) & ~(size_t)(ps - 1);

    /* Open /dev/mem WITHOUT O_SYNC. O_SYNC forces uncached mappings, which
     * makes per-pixel writes pay a round-trip to DDR. The reserved framebuffer
     * region is normal DDR; cacheable mapping is correct. We msync() before
     * VDMA reads if we ever need explicit ordering; for the demo's per-frame
     * cadence the natural cache eviction is enough. */
    fb->fd = open("/dev/mem", O_RDWR);
    if (fb->fd < 0) {
        perror("fb_lib: open /dev/mem");
        return -1;
    }

    fb->map = mmap(NULL, fb->map_len, PROT_READ | PROT_WRITE,
                   MAP_SHARED, fb->fd, (off_t)page_base);
    if (fb->map == MAP_FAILED) {
        perror("fb_lib: mmap /dev/mem");
        close(fb->fd);
        fb->fd = -1;
        return -1;
    }
    fb->pixels = fb->map + fb->page_off;
    return 0;
}

void fb_close(fb_t *fb) {
    if (fb->map && fb->map != MAP_FAILED) {
        munmap(fb->map, fb->map_len);
        fb->map = NULL;
        fb->pixels = NULL;
    }
    if (fb->fd >= 0) {
        close(fb->fd);
        fb->fd = -1;
    }
}

/* Clip the requested rect against the FB. Updates *x,*y,*w,*h in place.
 * Returns 1 if there's anything left to draw, 0 if fully clipped out. */
static int clip_rect(int *x, int *y, int *w, int *h) {
    if (*w <= 0 || *h <= 0) return 0;
    if (*x < 0)             { *w += *x; *x = 0; }
    if (*y < 0)             { *h += *y; *y = 0; }
    if (*x + *w > FB_WIDTH)  *w = FB_WIDTH  - *x;
    if (*y + *h > FB_HEIGHT) *h = FB_HEIGHT - *y;
    return (*w > 0 && *h > 0);
}

void fb_rect(fb_t *fb, int x, int y, int w, int h, uint32_t rgb) {
    if (!clip_rect(&x, &y, &w, &h)) return;

    /* Build one scanline of pixels (3*w bytes), then memcpy it onto each row.
     * Faster than per-pixel writes for w >= ~8 because of memcpy's SIMD path. */
    uint8_t bgr[3] = {
        (uint8_t)(rgb         & 0xFFu),
        (uint8_t)((rgb >>  8) & 0xFFu),
        (uint8_t)((rgb >> 16) & 0xFFu),
    };

    if (bgr[0] == bgr[1] && bgr[1] == bgr[2]) {
        /* Solid grayscale: memset is fastest. */
        for (int row = 0; row < h; ++row) {
            uint8_t *p = fb->pixels + (size_t)(y + row) * FB_STRIDE + (size_t)x * FB_BPP;
            memset(p, bgr[0], (size_t)w * FB_BPP);
        }
        return;
    }

    /* Build a w-pixel scanline once, replicate. */
    /* For tiny widths just per-pixel — avoids a stack alloc. */
    if (w <= 16) {
        for (int row = 0; row < h; ++row) {
            uint8_t *p = fb->pixels + (size_t)(y + row) * FB_STRIDE + (size_t)x * FB_BPP;
            for (int col = 0; col < w; ++col) {
                p[col*3 + 0] = bgr[0];
                p[col*3 + 1] = bgr[1];
                p[col*3 + 2] = bgr[2];
            }
        }
        return;
    }

    /* Larger rect: build scanline once, memcpy per row. */
    uint8_t scanline[FB_WIDTH * FB_BPP];
    for (int col = 0; col < w; ++col) {
        scanline[col*3 + 0] = bgr[0];
        scanline[col*3 + 1] = bgr[1];
        scanline[col*3 + 2] = bgr[2];
    }
    for (int row = 0; row < h; ++row) {
        uint8_t *p = fb->pixels + (size_t)(y + row) * FB_STRIDE + (size_t)x * FB_BPP;
        memcpy(p, scanline, (size_t)w * FB_BPP);
    }
}

void fb_clear(fb_t *fb, uint32_t rgb) {
    fb_rect(fb, 0, 0, FB_WIDTH, FB_HEIGHT, rgb);
}

void fb_draw_char(fb_t *fb, int x, int y, char c, uint32_t fg, int scale) {
    if (scale <= 0) return;
    const uint8_t *g = font5x7_glyph(c);
    if (!g) return; /* unsupported char → blank */
    for (int row = 0; row < FONT5X7_HEIGHT; ++row) {
        uint8_t bits = g[row];
        for (int col = 0; col < FONT5X7_WIDTH; ++col) {
            /* bit (FONT5X7_WIDTH-1 - col) is leftmost (matches table layout). */
            if (bits & (1u << (FONT5X7_WIDTH - 1 - col))) {
                fb_rect(fb, x + col * scale, y + row * scale, scale, scale, fg);
            }
        }
    }
}

void fb_draw_text(fb_t *fb, int x, int y, const char *s, uint32_t fg, int scale) {
    if (!s || scale <= 0) return;
    int adv = (FONT5X7_WIDTH + 1) * scale; /* 1-px gap between glyphs */
    int cur = x;
    for (int i = 0; s[i]; ++i) {
        if (cur >= FB_WIDTH) break;
        fb_draw_char(fb, cur, y, s[i], fg, scale);
        cur += adv;
    }
}

void fb_draw_image28(fb_t *fb, int x0, int y0, const uint8_t *img784, int scale) {
    if (!img784 || scale <= 0) return;
    /* Per-pixel: read uint8, replicate to BGR, fill scale x scale block. */
    for (int j = 0; j < 28; ++j) {
        for (int i = 0; i < 28; ++i) {
            uint8_t v = img784[j * 28 + i];
            uint32_t rgb = ((uint32_t)v << 16) | ((uint32_t)v << 8) | (uint32_t)v;
            fb_rect(fb, x0 + i * scale, y0 + j * scale, scale, scale, rgb);
        }
    }
}
