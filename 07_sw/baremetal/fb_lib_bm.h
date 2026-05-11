/* fb_lib_bm.h — bare-metal text + image blit on top of hdmi_bm's FB.
 *
 * Adapts the Linux demo's fb_lib (pixel/rect/text/image28) to direct MMIO
 * pointers — same API surface, same font5x7 glyph table reused via
 * 07_sw/linux/demo_mnist_hdmi/font5x7.{h,c} (added to baremetal Makefile
 * sources list).
 */
#ifndef FB_LIB_BM_H
#define FB_LIB_BM_H

#include <stdint.h>
#include "hdmi_bm.h"

/* Color macros — RGB 0xRRGGBB; stored BGR per byte in DDR. */
#define FBM_BLACK   0x000000u
#define FBM_WHITE   0xFFFFFFu
#define FBM_RED     0xFF0000u
#define FBM_GREEN   0x00FF00u
#define FBM_BLUE    0x0000FFu
#define FBM_YELLOW  0xFFFF00u
#define FBM_CYAN    0x00FFFFu
#define FBM_GRAY    0x808080u
#define FBM_DARKBG  0x001020u

/* Render one ASCII glyph at (x,y), pixel size = scale * 5w x scale * 7h. */
void fbm_draw_char(int x, int y, char c, uint32_t fg, int scale);

/* Render a null-terminated string. 6*scale advance per char (1-px gap). */
void fbm_draw_text(int x, int y, const char *s, uint32_t fg, int scale);

/* Render a 28x28 uint8 grayscale image at (x0,y0), each input pixel
 * replicated to `scale x scale`. */
void fbm_draw_image28(int x0, int y0, const uint8_t *img784, int scale);

#endif /* FB_LIB_BM_H */
