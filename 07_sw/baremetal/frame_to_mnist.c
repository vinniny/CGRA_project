/* =============================================================================
 * frame_to_mnist.c — see header for full description.
 *
 * Bare-metal: no malloc, no FP, no stdlib. Pure integer math.
 * ============================================================================= */
#include "frame_to_mnist.h"
#include "hdmi_in_bm.h"
#include <stddef.h>

void downsample_roi_to_mnist(const uint8_t *fb,
                              hdmi_roi_t      roi,
                              uint8_t         out784[28*28])
{
    /* Block size (in source pixels) per output cell. */
    const uint32_t bw = roi.w / 28u;
    const uint32_t bh = roi.h / 28u;

    /* Avoid divide-by-zero on bad ROI. */
    const uint32_t block_pix = (bw == 0u || bh == 0u) ? 1u : (bw * bh);

    for (uint32_t oy = 0; oy < 28u; oy++) {
        for (uint32_t ox = 0; ox < 28u; ox++) {
            /* Top-left of the source block (clamped to frame). */
            const uint32_t sx0 = roi.x + ox * bw;
            const uint32_t sy0 = roi.y + oy * bh;

            uint32_t sum_b = 0, sum_g = 0, sum_r = 0;

            for (uint32_t dy = 0; dy < bh; dy++) {
                const uint32_t y = sy0 + dy;
                if (y >= HDMI_IN_H) break;
                const uint8_t *row = fb + (size_t)y * HDMI_IN_ROW_STRIDE;
                for (uint32_t dx = 0; dx < bw; dx++) {
                    const uint32_t x = sx0 + dx;
                    if (x >= HDMI_IN_W) break;
                    const uint8_t *p = row + x * HDMI_IN_BPP;
                    sum_b += p[0];
                    sum_g += p[1];
                    sum_r += p[2];
                }
            }

            const uint32_t avg_b = sum_b / block_pix;
            const uint32_t avg_g = sum_g / block_pix;
            const uint32_t avg_r = sum_r / block_pix;

            /* Full-range BT.601 luma: Y = (77R + 150G + 29B + 128) >> 8.
             * Coefficients sum to 256 so white (255,255,255) → 255, black → 0.
             * The narrower 66/129/25 set is limited-range BT.601 (sums to
             * 220, maps to Y∈[16..235]); using it here would clamp every
             * Paint background pixel to 36 after inversion. */
            const uint32_t y_lin = (77u * avg_r + 150u * avg_g + 29u * avg_b + 128u) >> 8;

            /* Invert: Paint black-ink on white-canvas → MNIST white-on-black.
             * Result lies in [0..255] — same format as sweep_input28[]. */
            const uint32_t y_inv = 255u - (y_lin > 255u ? 255u : y_lin);

            /* Pass through the grayscale value -- DO NOT threshold to
             * binary. Silicon test 2026-05-27: thresholding produced a
             * 28x28 image with stark 0/255 edges that pushed conv2
             * outputs into INT16 saturation (act400 had 0x7FFF entries).
             * The saturated act400 then triggered CGRA-vs-ARM-INT
             * divergence at the 40-bit accumulator boundary (CGRA saw
             * cgra=5, ARM saw int=3 on the same array). Bypassing the
             * threshold (sending grayscale 0..255 like sweep_input28)
             * keeps activations balanced and all three FC paths agree.
             *
             * The original justification for the threshold ("CGRA-INT
             * needs bimodal histogram to predict correctly") was wrong:
             * the silicon-validated mnist_sweep_fixture uses normal
             * grayscale values directly, and forcing sweep_input28[0]
             * into the live pipeline gave 7/7/7 ALL-AGREE. */
            out784[oy * 28u + ox] = (uint8_t)y_inv;
        }
    }
}
