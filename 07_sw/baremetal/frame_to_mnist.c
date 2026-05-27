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
    /* Simple block-average + invert. Bbox-centering preprocessing was
     * tested 2026-05-27 but produced worse live-input accuracy than
     * the straight pass-through (likely because it locked onto noise
     * artifacts when the captured frame had partial-frame transitions).
     * Reverted to direct grayscale downsample. */
    const uint32_t bw = roi.w / 28u;
    const uint32_t bh = roi.h / 28u;
    const uint32_t block_pix = (bw == 0u || bh == 0u) ? 1u : (bw * bh);

    for (uint32_t oy = 0; oy < 28u; oy++) {
        for (uint32_t ox = 0; ox < 28u; ox++) {
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
                    sum_b += p[0]; sum_g += p[1]; sum_r += p[2];
                }
            }
            const uint32_t avg_b = sum_b / block_pix;
            const uint32_t avg_g = sum_g / block_pix;
            const uint32_t avg_r = sum_r / block_pix;
            const uint32_t y_lin = (77u * avg_r + 150u * avg_g + 29u * avg_b + 128u) >> 8;
            const uint32_t y_inv = 255u - (y_lin > 255u ? 255u : y_lin);
            out784[oy * 28u + ox] = (uint8_t)y_inv;
        }
    }
}
