/* fb_test.c — M1 smoke test for fb_lib. Replaces the 4-band test pattern
 * with 4 colored corners + a centered white rect. If the monitor shows that,
 * fb_lib is working.
 *
 * Build via Makefile (cross-compiled, static-musl ARM):
 *     make fb_test
 * Deploy + run:
 *     scp fb_test petalinux@<board>:/tmp/
 *     ssh petalinux@<board> 'sudo /tmp/fb_test'
 */
#include <stdio.h>
#include <stdlib.h>
#include "fb_lib.h"

int main(int argc, char **argv) {
    unsigned long phys = (argc > 1) ? strtoul(argv[1], NULL, 0) : FB_DEFAULT_PHYS;

    fb_t fb;
    if (fb_open(&fb, phys) < 0) return 1;

    fb_clear(&fb, FB_DARKBG);

    /* Four corners — 100x100 each */
    fb_rect(&fb,           10,            10, 100, 100, FB_RED);     /* top-left */
    fb_rect(&fb, FB_WIDTH-110,            10, 100, 100, FB_GREEN);   /* top-right */
    fb_rect(&fb,           10, FB_HEIGHT-110, 100, 100, FB_BLUE);    /* bottom-left */
    fb_rect(&fb, FB_WIDTH-110, FB_HEIGHT-110, 100, 100, FB_YELLOW);  /* bottom-right */

    /* Centered white rect */
    int cx = FB_WIDTH / 2, cy = FB_HEIGHT / 2;
    fb_rect(&fb, cx - 80, cy - 60, 160, 120, FB_WHITE);

    /* Thin gray border around the centered rect to verify pixel-perfect placement */
    fb_rect(&fb, cx - 80,           cy - 60, 160, 1,     FB_GRAY);  /* top edge */
    fb_rect(&fb, cx - 80,           cy + 59, 160, 1,     FB_GRAY);  /* bottom edge */
    fb_rect(&fb, cx - 80,           cy - 60, 1,   120,   FB_GRAY);  /* left edge */
    fb_rect(&fb, cx + 79,           cy - 60, 1,   120,   FB_GRAY);  /* right edge */

    fb_close(&fb);

    printf("fb_test: drew 4 corners + centered white rect at phys 0x%lX\n", phys);
    return 0;
}
