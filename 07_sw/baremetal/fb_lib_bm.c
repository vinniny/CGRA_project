/* fb_lib_bm.c — see fb_lib_bm.h. */

#include "fb_lib_bm.h"
#include "../linux/demo_mnist_hdmi/font5x7.h"

void fbm_draw_char(int x, int y, char c, uint32_t fg, int scale)
{
    if (scale <= 0) return;
    const uint8_t *g = font5x7_glyph(c);
    if (!g) return;
    for (int row = 0; row < FONT5X7_HEIGHT; ++row) {
        uint8_t bits = g[row];
        for (int col = 0; col < FONT5X7_WIDTH; ++col) {
            if (bits & (1u << (FONT5X7_WIDTH - 1 - col))) {
                hdmi_rect(x + col * scale, y + row * scale, scale, scale, fg);
            }
        }
    }
}

void fbm_draw_text(int x, int y, const char *s, uint32_t fg, int scale)
{
    if (!s || scale <= 0) return;
    int adv = (FONT5X7_WIDTH + 1) * scale;
    int cur = x;
    for (int i = 0; s[i]; ++i) {
        if (cur >= HDMI_FB_W) break;
        fbm_draw_char(cur, y, s[i], fg, scale);
        cur += adv;
    }
}

void fbm_draw_image28(int x0, int y0, const uint8_t *img784, int scale)
{
    if (!img784 || scale <= 0) return;
    for (int j = 0; j < 28; ++j) {
        for (int i = 0; i < 28; ++i) {
            uint8_t v = img784[j * 28 + i];
            uint32_t rgb = ((uint32_t)v << 16) | ((uint32_t)v << 8) | (uint32_t)v;
            hdmi_rect(x0 + i * scale, y0 + j * scale, scale, scale, rgb);
        }
    }
}
