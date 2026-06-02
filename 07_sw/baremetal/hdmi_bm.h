/* hdmi_bm.h — bare-metal HDMI bring-up for PYNQ-base + CGRA bitstream.
 *
 * Mirrors scripts/hdmi_first_light.sh + scripts/hdmi_paint.sh, ported from
 * sh/devmem to C using direct volatile pointer access (MMU identity-mapped
 * for these MMIO ranges in our bare-metal linker.ld). Same exact register
 * sequence as the proven Linux scripts.
 *
 * Pipeline (output side):
 *   dynclk(0x43C10000) -> rgb2dvi  pixel clock = 25.175 MHz
 *   vtc_out(0x43C20000)            generator 640x480@60
 *   color_convert(0x43C60000)      identity 3x3 matrix
 *   pixel_unpack(0x43C70000)       V_24 (3 bytes/pixel BGR packed)
 *   vdma(0x43000000)               MM2S, reads FB at FB_PHYS
 *
 * FB at 0x1F000000 in DDR (in the PetaLinux-reserved gap so it coexists
 * with the PetaLinux DT; in bare-metal we can use any DDR address).
 * 640*480*3 = 921,600 bytes per frame.
 *
 * Call hdmi_init() once at startup. Then draw to fb_pixels[].
 * Call hdmi_flush_fb() after a batch of writes if cache is enabled.
 */
#ifndef HDMI_BM_H
#define HDMI_BM_H

#include <stdint.h>

#define HDMI_FB_PHYS    0x10000000UL  /* mid-DDR; 0x1F000000 hit VDMA DMADecErr
                                       * at the HP0 high-DDR edge on the clean BD */
#define HDMI_FB_W       640
#define HDMI_FB_H       480
#define HDMI_FB_BPP     3
#define HDMI_FB_STRIDE  (HDMI_FB_W * HDMI_FB_BPP)
#define HDMI_FB_BYTES   (HDMI_FB_STRIDE * HDMI_FB_H)

/* Bring up the full HDMI output chain. Returns 0 on success, -1 if dynclk
 * MMCM fails to lock (the only step that can fail at runtime). */
int hdmi_init(void);

/* Convenience pixel access. (0,0) is top-left. RGB color = 0xRRGGBB
 * (stored BGR per byte in memory to match pixel_unpack V_24 / rgb2dvi). */
static inline volatile uint8_t *hdmi_fb_pixels(void)
{
    return (volatile uint8_t *)HDMI_FB_PHYS;
}

static inline void hdmi_pixel(int x, int y, uint32_t rgb)
{
    volatile uint8_t *p = hdmi_fb_pixels()
                        + (uintptr_t)y * HDMI_FB_STRIDE
                        + (uintptr_t)x * HDMI_FB_BPP;
    /* Clean dual-HDMI BD pipeline maps framebuffer byte0->G, byte1->B, byte2->R
     * (silicon-confirmed 2026-06-02: intended FBM_YELLOW 0xFFFF00 displayed as
     * purple 0xFF00FF until G/B were swapped here).  Write G,B,R accordingly. */
    p[0] = (uint8_t)((rgb >>  8) & 0xFFu); /* G -> byte0 */
    p[1] = (uint8_t)(rgb         & 0xFFu); /* B -> byte1 */
    p[2] = (uint8_t)((rgb >> 16) & 0xFFu); /* R -> byte2 */
}

/* Clear / rect helpers (no clipping — caller must keep within FB bounds). */
void hdmi_clear(uint32_t rgb);
void hdmi_rect(int x, int y, int w, int h, uint32_t rgb);

/* Live HDMI-OUT VDMA MM2S status register (DMASR) for runtime diagnostics. */
uint32_t hdmi_out_dmasr(void);

/* Flush dcache so VDMA sees writes. Safe to call after a batch of pixel
 * writes; a no-op if caches are not enabled. */
void hdmi_flush_fb(void);

#endif /* HDMI_BM_H */
