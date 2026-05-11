/* demo_hdmi_text.c — B3 bare-metal HDMI text + image rendering smoke.
 *
 * Brings up HDMI, then renders:
 *   - Banner "BARE METAL HDMI" at top
 *   - sweep_input28[0] (a "7") upscaled 8x to 224x224 centered
 *   - "GROUND TRUTH: 7" label
 *   - Alphabet + digit row at bottom
 *
 * Pass: monitor shows a recognizable "7" + readable text.
 */
#include "uart.h"
#include "hdmi_bm.h"
#include "fb_lib_bm.h"
#include "mnist_sweep_fixture.h"

int main(void)
{
    uart_init();
    uart_puts("\n=== B3 bare-metal HDMI text + image ===\n");
    if (hdmi_init() != 0) { uart_puts("FAIL: hdmi_init\n"); for(;;); }
    uart_puts("hdmi_init OK\n");

    hdmi_clear(FBM_DARKBG);

    /* Banner */
    fbm_draw_text(160, 16, "BARE METAL HDMI", FBM_WHITE, 4);

    /* MNIST "7" centered, 8x upscale */
    int img_x = (HDMI_FB_W - 224) / 2;   /* 208 */
    int img_y = 80;
    fbm_draw_image28(img_x, img_y, sweep_input28[0], 8);

    /* Border around image */
    hdmi_rect(img_x - 2, img_y - 2, 228, 1,   FBM_GRAY);
    hdmi_rect(img_x - 2, img_y + 224, 228, 1, FBM_GRAY);
    hdmi_rect(img_x - 2, img_y - 2, 1,   228, FBM_GRAY);
    hdmi_rect(img_x + 224, img_y - 2, 1, 228, FBM_GRAY);

    /* Label below the tile */
    char buf[64];
    /* Tiny snprintf-free formatter for the label. */
    int lbl = (int)sweep_labels[0];
    buf[0] = 'G'; buf[1] = 'R'; buf[2] = 'O'; buf[3] = 'U';
    buf[4] = 'N'; buf[5] = 'D'; buf[6] = ' '; buf[7] = 'T';
    buf[8] = 'R'; buf[9] = 'U'; buf[10] = 'T'; buf[11] = 'H';
    buf[12] = ':'; buf[13] = ' '; buf[14] = (char)('0' + lbl);
    buf[15] = 0;
    fbm_draw_text(208, 320, buf, FBM_GREEN, 4);

    /* Alphabet + digits sample at bottom */
    fbm_draw_text(16, 410, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", FBM_CYAN, 2);
    fbm_draw_text(16, 440, "0123456789  HELLO BARE METAL!", FBM_YELLOW, 2);

    hdmi_flush_fb();

    uart_puts("Done. Monitor should show '7' + text labels.\n");
    uart_drain();
    for (;;);
    return 0;
}
