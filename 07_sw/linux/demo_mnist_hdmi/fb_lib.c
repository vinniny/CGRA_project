/* fb_lib.c — see fb_lib.h for API and design rationale. */

#include "fb_lib.h"
#include "font5x7.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/mman.h>

/* AXI VDMA MM2S register offsets — verified from bitstreams/cgra_pynq_base/
 * base.hwh against the actual instance (Xilinx PG020 r6.3). Note: this
 * VDMA does NOT expose a separate FRMSTORE register; the ring size is
 * fixed at synthesis via C_NUM_FSTORES=4. Software writes to 0x18 are
 * unmapped no-ops.
 *
 * PARK_PTR_REG (0x28) layout (corrected from PG020 errata):
 *   bits  [4:0]  RdFrmPtrRef  RW  MM2S park frame index (the swap reg)
 *   bits  [12:8] WrFrmPtrRef  RW  S2MM park frame index (unused here)
 *   bits [20:16] RdFrmStore   RO  Current MM2S frame indicator
 *   bits [28:24] WrFrmStore   RO  Current S2MM frame indicator
 */
#define VDMA_MM2S_CR         0x00
#define VDMA_MM2S_SR         0x04
#define VDMA_MM2S_PARK_PTR   0x28
#define VDMA_MM2S_VSIZE      0x50
#define VDMA_MM2S_HSIZE      0x54
#define VDMA_MM2S_STRIDE     0x58
#define VDMA_MM2S_FRAME0     0x5C
#define VDMA_MM2S_FRAME1     0x60
#define VDMA_REG_SPAN        0x100

/* ARM dcache-clean syscall: pushes dirty cache lines out to the point of
 * coherency (which on Zynq-7000 is L2/DDR, visible to HP1 AXI master that
 * VDMA reads through). Glibc/musl don't provide a wrapper. */
#ifndef __ARM_NR_cacheflush
#define __ARM_NR_cacheflush  (0x0f0000 + 2)
#endif
static inline void arm_dcache_clean(void *start, void *end) {
    syscall(__ARM_NR_cacheflush, start, end, 0);
}

int fb_open(fb_t *fb, unsigned long phys) {
    memset(fb, 0, sizeof(*fb));
    fb->fd = -1;

    long ps = sysconf(_SC_PAGESIZE);
    fb->page_off = (size_t)(phys & (unsigned long)(ps - 1));
    unsigned long page_base = phys - fb->page_off;
    fb->map_len = (fb->page_off + FB_BYTES + (size_t)ps - 1) & ~(size_t)(ps - 1);

    /* Open /dev/mem WITHOUT O_SYNC: the FB region is normal DDR, cacheable
     * mapping gives ~10x write throughput vs uncached. Per-frame visibility
     * to VDMA is achieved by dcache-clean before swap (fb_swap in DB mode).
     * Single-buffer mode tolerates the lack of explicit flush because of the
     * 100 ms dwell which lets natural cache eviction catch up. */
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

int fb_open_db(fb_t *fb, unsigned long phys_a, unsigned long phys_b,
               unsigned long vdma_phys)
{
    memset(fb, 0, sizeof(*fb));
    fb->fd = -1;

    long ps = sysconf(_SC_PAGESIZE);
    size_t pmask = (size_t)(ps - 1);

    /* Both FBs share the same page-offset since they're both at addresses
     * that are page-aligned by design (0x1F000000, 0x1F0F0000). */
    fb->page_off  = (size_t)(phys_a & (unsigned long)pmask);
    fb->map_len   = (fb->page_off + FB_BYTES + pmask) & ~pmask;
    fb->map_len_b = (((size_t)(phys_b & pmask)) + FB_BYTES + pmask) & ~pmask;
    fb->vdma_len  = (VDMA_REG_SPAN + pmask) & ~pmask;

    /* FB fd: cacheable mapping (no O_SYNC). */
    fb->fd = open("/dev/mem", O_RDWR);
    if (fb->fd < 0) { perror("fb_lib: open /dev/mem (FB)"); return -1; }

    fb->map = mmap(NULL, fb->map_len, PROT_READ | PROT_WRITE,
                   MAP_SHARED, fb->fd, (off_t)(phys_a - fb->page_off));
    if (fb->map == MAP_FAILED) {
        perror("fb_lib: mmap FB_A"); fb_close(fb); return -1;
    }
    fb->map_b = mmap(NULL, fb->map_len_b, PROT_READ | PROT_WRITE,
                     MAP_SHARED, fb->fd,
                     (off_t)(phys_b & ~(unsigned long)pmask));
    if (fb->map_b == MAP_FAILED) {
        perror("fb_lib: mmap FB_B"); fb_close(fb); return -1;
    }

    /* VDMA register window: open a SEPARATE fd with O_SYNC so the kernel
     * gives us an uncached mapping (peripheral writes must bypass cache). */
    int vdma_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (vdma_fd < 0) { perror("fb_lib: open /dev/mem (VDMA)"); fb_close(fb); return -1; }
    void *vdma_map = mmap(NULL, fb->vdma_len, PROT_READ | PROT_WRITE,
                          MAP_SHARED, vdma_fd, (off_t)vdma_phys);
    /* The vdma_fd can be closed immediately — the mapping persists. */
    close(vdma_fd);
    if (vdma_map == MAP_FAILED) {
        perror("fb_lib: mmap VDMA"); fb_close(fb); return -1;
    }
    fb->vdma = (volatile uint32_t *)vdma_map;

    /* Start with back buffer at FB_B; VDMA parks on FB_A. */
    fb->front_idx     = 0;
    fb->pixels        = fb->map_b + (size_t)(phys_b & pmask);
    fb->double_buffer = 1;

    /* Clear both buffers so neither shows garbage during the first swap. */
    fb_clear(fb, FB_BLACK);          /* clears current back (FB_B) */
    uint8_t *save_pixels = fb->pixels;
    fb->pixels = fb->map + fb->page_off;
    fb_clear(fb, FB_BLACK);          /* now clear FB_A */
    fb->pixels = save_pixels;

    /* Add FRAME1 to the running VDMA ring WITHOUT resetting.
     *
     * The earlier "reset + full reconfigure" approach broke the downstream
     * AXIS handshake (v_axi4s_vid_out_0 lost lock, monitor went to
     * no-signal) and didn't recover until hdmi_first_light.sh was re-run.
     * Instead we rely on hdmi_first_light having already brought the chain
     * up cleanly in single-frame mode (FRAME0=phys_a, PARK_PTR=0, CR.RS=1).
     * We just register the second frame buffer and ensure PARK_PTR is 0
     * to start; the C_NUM_FSTORES=4 ring already has slots 1..3 allocated.
     * Subsequent fb_swap() writes flip RdFrmPtrRef between 0 and 1. */

    /* Sanity-check that VDMA is already running. If not, bail — caller
     * should have run hdmi_first_light.sh first. */
    uint32_t cr = fb->vdma[VDMA_MM2S_CR / 4];
    uint32_t sr = fb->vdma[VDMA_MM2S_SR / 4];
    if (!(cr & 0x1) || (sr & 0x1) /* halted bit */) {
        fprintf(stderr, "fb_lib: VDMA not running (CR=0x%08X SR=0x%08X). "
                        "Run hdmi_first_light.sh + hdmi_paint.sh first.\n", cr, sr);
        fb_close(fb);
        return -1;
    }

    /* Verify FRAME0 already matches phys_a (it should, since hdmi_first_light
     * wrote it). Warn but proceed if it differs. */
    uint32_t cur_frame0 = fb->vdma[VDMA_MM2S_FRAME0 / 4];
    if (cur_frame0 != (uint32_t)phys_a) {
        fprintf(stderr, "fb_lib: WARN — FRAME0=0x%08X, expected 0x%08lX; "
                        "demo will still work but is not synced with bring-up\n",
                cur_frame0, phys_a);
    }

    /* Register FRAME1 and ensure park is on FRAME0 to start. PARK_PTR is
     * the only register we routinely touch from here on — fb_swap writes
     * its RdFrmPtrRef field every frame. */
    fb->vdma[VDMA_MM2S_FRAME1   / 4] = (uint32_t)phys_b;
    fb->vdma[VDMA_MM2S_PARK_PTR / 4] = 0x00000000u;

    fprintf(stderr, "fb_lib: DB mode — FB_A=0x%08lX FB_B=0x%08lX VDMA=0x%08lX\n",
            phys_a, phys_b, vdma_phys);
    fprintf(stderr, "fb_lib:   MM2S CR=0x%08X SR=0x%08X PARK_PTR=0x%08X "
                    "FRAME0=0x%08X FRAME1=0x%08X\n",
            fb->vdma[VDMA_MM2S_CR / 4],
            fb->vdma[VDMA_MM2S_SR / 4],
            fb->vdma[VDMA_MM2S_PARK_PTR / 4],
            fb->vdma[VDMA_MM2S_FRAME0 / 4],
            fb->vdma[VDMA_MM2S_FRAME1 / 4]);
    return 0;
}

void fb_swap(fb_t *fb) {
    if (!fb->double_buffer) return;
    /* Flush pending pixel writes from L1/L2 dcache out to DDR so the next
     * VDMA read sees fresh content. ~1 MB clean takes ~200 us on Cortex-A9
     * — negligible vs the 16.6 ms vsync interval. */
    arm_dcache_clean(fb->pixels, fb->pixels + FB_BYTES);

    /* The frame we just rendered becomes the new front. Old front becomes
     * the new back. front_idx tracks what VDMA is reading. */
    fb->front_idx ^= 1;
    fb->pixels = ((fb->front_idx == 0) ? fb->map_b : fb->map)
               + fb->page_off;

    /* Hand the new front to VDMA. PARK_PTR_REG.RdFrmPtrRef (bits[4:0]) =
     * MM2S park frame index; VDMA samples it at the next vsync
     * (C_USE_FSYNC=1 in the bitstream), giving us a tear-free buffer swap.
     * (bits[20:16] are the read-only RdFrmStore status indicator — writing
     * there is what the v1 of this code did, with no effect; corrected.) */
    fb->vdma[VDMA_MM2S_PARK_PTR / 4] = (uint32_t)fb->front_idx & 0x1Fu;
}

void fb_close(fb_t *fb) {
    if (fb->map && fb->map != MAP_FAILED) {
        munmap(fb->map, fb->map_len);
        fb->map = NULL;
    }
    if (fb->map_b && fb->map_b != MAP_FAILED) {
        munmap(fb->map_b, fb->map_len_b);
        fb->map_b = NULL;
    }
    if (fb->vdma && fb->vdma != MAP_FAILED) {
        munmap((void *)fb->vdma, fb->vdma_len);
        fb->vdma = NULL;
    }
    fb->pixels = NULL;
    if (fb->fd >= 0) {
        close(fb->fd);
        fb->fd = -1;
    }
    fb->double_buffer = 0;
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
