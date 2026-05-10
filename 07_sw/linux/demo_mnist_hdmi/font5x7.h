/* font5x7.h — minimal 5x7 ASCII bitmap font.
 *
 * Source: extracted verbatim from 07_sw/linux/lpr_hdmi_demo.c (lines 49-94).
 * Coverage: space, '-', ':', '/', '0'-'9', 'A'-'Z'. Sufficient for labels
 * like "ARM PRED: 7  GT: 7  CGRA SPEEDUP: 21X".
 *
 * Each glyph is 7 bytes (one per row, top-to-bottom). Bits [4:0] of each
 * byte select pixels left-to-right (bit 4 = leftmost). All other bits are 0.
 * Lookup: font5x7_glyph(c) returns NULL for out-of-range, otherwise a
 * pointer to a 7-byte glyph.
 */
#ifndef FONT5X7_H
#define FONT5X7_H

#include <stdint.h>

#define FONT5X7_WIDTH   5
#define FONT5X7_HEIGHT  7
#define FONT5X7_FIRST   ' '   /* ASCII 0x20 */
#define FONT5X7_LAST    'Z'   /* ASCII 0x5A */

/* Returns a pointer to the 7-byte glyph for ASCII `c`, or NULL if out of
 * range (caller should render a space or skip). */
const uint8_t *font5x7_glyph(char c);

#endif /* FONT5X7_H */
