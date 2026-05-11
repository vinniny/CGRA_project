/* fb_lib.h — minimal HDMI framebuffer renderer for the PYNQ-base + CGRA
 * bitstream. Writes directly to a physical-address-mapped DDR framebuffer
 * via mmap("/dev/mem"), bypassing the absent /dev/fb0.
 *
 * Pixel format: 24-bit BGR packed (3 bytes/pixel, low byte = B). Matches the
 * pixel_unpack V_24 mode + color_convert identity matrix configured by
 * scripts/hdmi_paint.sh. RGB input to the API (0xRRGGBB) is stored as B,G,R.
 *
 * Resolution: 640x480 @ 60 Hz. Stride = 1920 bytes/line. Frame = 921600 bytes.
 * Default phys = 0x1F000000 (PYNQ-Z2 reserved-memory framebuffer region).
 *
 * The kernel's CONFIG_STRICT_DEVMEM=y blocks read()/write() to /dev/mem but
 * permits mmap() of reserved-memory regions, which is the path we use.
 */
#ifndef FB_LIB_H
#define FB_LIB_H

#include <stdint.h>
#include <stddef.h>

#define FB_WIDTH        640
#define FB_HEIGHT       480
#define FB_BPP          3                       /* bytes per pixel */
#define FB_STRIDE       (FB_WIDTH * FB_BPP)     /* 1920 */
#define FB_BYTES        (FB_STRIDE * FB_HEIGHT) /* 921600 */
#define FB_DEFAULT_PHYS 0x1F000000UL

typedef struct {
    int       fd;
    uint8_t  *map;      /* page-aligned mmap base of FB_A (and only FB in single mode) */
    uint8_t  *map_b;    /* FB_B mmap base in double-buffer mode, NULL in single mode */
    uint8_t  *pixels;   /* current back-buffer write target (= map_X + page_off) */
    size_t    map_len;
    size_t    map_len_b;
    size_t    page_off;
    /* Double-buffer state — unused when double_buffer == 0. */
    volatile uint32_t *vdma;    /* mmap'd VDMA register window (MM2S) */
    size_t    vdma_len;
    int       front_idx;        /* frame VDMA reads: 0 = FB_A, 1 = FB_B */
    int       double_buffer;    /* 1 if opened via fb_open_db; 0 = single */
} fb_t;

/* Open /dev/mem and mmap FB_BYTES at the given physical address (single-
 * buffer mode). `phys` may be FB_DEFAULT_PHYS or another reserved-memory
 * base. Returns 0 on success; -1 on error (errno set). */
int  fb_open(fb_t *fb, unsigned long phys);

/* Open the framebuffer in double-buffer mode:
 *   - mmaps FB_A at phys_a and FB_B at phys_b (each FB_BYTES, page-aligned).
 *   - mmaps the AXI VDMA register window at vdma_phys (one page).
 *   - Configures VDMA MM2S for 2-frame park mode: FRMSTORE=2,
 *     FRAME0=phys_a, FRAME1=phys_b, PARK_PTR=0 (display FB_A first).
 *   - Clears both buffers to FB_BLACK so neither shows garbage during the
 *     first swap.
 *   - Initialises fb->pixels at FB_B (caller draws to it first).
 *
 * Subsequent fb_pixel/rect/clear/draw_* calls write to the BACK buffer.
 * Call fb_swap(&fb) at end of each frame to hand the back to VDMA and
 * receive the (now displayed) old front as the new back.
 *
 * Returns 0 on success; -1 on error. */
int  fb_open_db(fb_t *fb, unsigned long phys_a, unsigned long phys_b,
                unsigned long vdma_phys);

/* Swap front/back buffers. Writes VDMA's MM2S_PARK_PTR to point at what
 * was just rendered; VDMA picks it up at the next vsync (tear-free, since
 * the bitstream's VDMA has C_USE_FSYNC=1). After the call, fb->pixels
 * points at the new back buffer. No-op for single-buffer fb. */
void fb_swap(fb_t *fb);

void fb_close(fb_t *fb);

/* Color macros: API takes 0xRRGGBB (top byte ignored). The library converts
 * to BGR-in-memory. Use these for readability. */
#define FB_BLACK   0x000000u
#define FB_WHITE   0xFFFFFFu
#define FB_RED     0xFF0000u
#define FB_GREEN   0x00FF00u
#define FB_BLUE    0x0000FFu
#define FB_YELLOW  0xFFFF00u
#define FB_CYAN    0x00FFFFu
#define FB_MAGENTA 0xFF00FFu
#define FB_GRAY    0x808080u
#define FB_DARKBG  0x001020u  /* dark navy, matches lpr_hdmi_demo aesthetic */

/* Single-pixel write. Inlined for tight inner loops in fb_rect/blit code.
 * Caller must clip; out-of-bounds is undefined. */
static inline void fb_pixel(fb_t *fb, int x, int y, uint32_t rgb) {
    uint8_t *p = fb->pixels + (size_t)y * FB_STRIDE + (size_t)x * FB_BPP;
    p[0] = (uint8_t)(rgb         & 0xFFu); /* B */
    p[1] = (uint8_t)((rgb >>  8) & 0xFFu); /* G */
    p[2] = (uint8_t)((rgb >> 16) & 0xFFu); /* R */
}

/* Fill a rectangle. Bounds-clipped against the FB. w/h <= 0 is a no-op. */
void fb_rect(fb_t *fb, int x, int y, int w, int h, uint32_t rgb);

/* Fill the entire FB with one color. */
void fb_clear(fb_t *fb, uint32_t rgb);

/* Render one ASCII character using the 5x7 bitmap font (font5x7.h).
 * Each font pixel becomes a `scale x scale` solid block. Final glyph
 * size is (5*scale) wide x (7*scale) tall. Out-of-range characters
 * render as blank. Bounds-clipped. */
void fb_draw_char(fb_t *fb, int x, int y, char c, uint32_t fg, int scale);

/* Render a null-terminated string at (x,y). Inter-character spacing is
 * 6*scale (5 glyph + 1 gap). No wrapping; clipped at FB right edge. */
void fb_draw_text(fb_t *fb, int x, int y, const char *s, uint32_t fg, int scale);

/* Render a 28x28 grayscale image at (x0,y0), each pixel scaled to
 * `scale x scale`. Input is 784 bytes (uint8 grayscale 0..255). Final
 * tile size is (28*scale) x (28*scale). Bounds-clipped. */
void fb_draw_image28(fb_t *fb, int x0, int y0, const uint8_t *img784, int scale);

#endif /* FB_LIB_H */
