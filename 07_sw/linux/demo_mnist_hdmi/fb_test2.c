/* fb_test2.c — M2 smoke test for fb_lib + font5x7 + image-blit primitives.
 *
 * Renders the first MNIST test image (sweep_input28[0], expected label 7)
 * upscaled 8x to 224x224 in the upper-center of the screen, plus several
 * text labels to verify the font and layout primitives.
 *
 * Build via Makefile:  make fb_test2
 * Deploy + run:        sudo /tmp/fb_test2
 *
 * Pass: monitor shows a recognizable digit "7" plus the label text.
 */
#include <stdio.h>
#include <stdlib.h>
#include "fb_lib.h"

/* SWEEP_RODATA expands to __attribute__((section(".cnn_sweep"))) in the
 * fixture by default — fine for bare-metal linking, harmless in Linux ELF
 * (section name just becomes a custom section in the binary). We override
 * it to empty in the Makefile to avoid the custom section. */
#include "mnist_sweep_fixture.h"

int main(void) {
    fb_t fb;
    if (fb_open(&fb, FB_DEFAULT_PHYS) < 0) return 1;

    fb_clear(&fb, FB_DARKBG);

    /* Top banner */
    fb_draw_text(&fb, 200, 16, "MNIST DEMO", FB_WHITE, 4);

    /* Render image[0] at center-top, 8x scale → 224x224 */
    int img_x = (FB_WIDTH - 224) / 2;     /* = 208 */
    int img_y = 64;
    fb_draw_image28(&fb, img_x, img_y, sweep_input28[0], 8);

    /* Bordering rect to make the tile visible */
    fb_rect(&fb, img_x - 2, img_y - 2, 228, 1,   FB_GRAY); /* top */
    fb_rect(&fb, img_x - 2, img_y + 224, 228, 1, FB_GRAY); /* bottom */
    fb_rect(&fb, img_x - 2, img_y - 2, 1, 228,   FB_GRAY); /* left */
    fb_rect(&fb, img_x + 224, img_y - 2, 1, 228, FB_GRAY); /* right */

    /* Label below the tile */
    char buf[64];
    snprintf(buf, sizeof(buf), "GROUND TRUTH: %d", (int)sweep_labels[0]);
    fb_draw_text(&fb, 200, 310, buf, FB_GREEN, 4);

    /* Sample of all the chars we have so far on the bottom line */
    fb_draw_text(&fb, 16, 380, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", FB_CYAN, 2);
    fb_draw_text(&fb, 16, 410, "0123456789  ARM CGRA SPEEDUP MS",  FB_YELLOW, 2);
    fb_draw_text(&fb, 16, 440, "PRED: 7  GT: 7  21X  1.8 MS",  FB_WHITE, 2);

    fb_close(&fb);

    printf("fb_test2: rendered MNIST image[0] (label=%d) + text labels\n",
           (int)sweep_labels[0]);
    return 0;
}
