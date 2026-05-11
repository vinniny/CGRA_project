/* demo_hdmi_test.c — B2 bare-metal HDMI bring-up smoke test.
 *
 * After load via XSDB:
 *   1. uart_init (so we see progress)
 *   2. hdmi_init (SLCR FCLK0=100MHz, dynclk lock, VTC, VDMA, color_convert,
 *                 pixel_unpack — mirrors hdmi_first_light.sh + hdmi_paint.sh)
 *   3. Fill FB with 4-band test pattern: red | green | blue | white
 *   4. Print final pipeline state, sit in idle.
 *
 * Pass: monitor shows 4 vertical bands (R, G, B, white).
 */
#include "uart.h"
#include "hdmi_bm.h"

int main(void)
{
    uart_init();
    uart_puts("\n=== bare-metal HDMI smoke test ===\n");

    uart_puts("[1/3] hdmi_init...\n");
    int rc = hdmi_init();
    if (rc != 0) {
        uart_puts("FAIL: hdmi_init returned ");
        uart_putdec((uint32_t)(int32_t)rc);
        uart_putchar('\n');
        for (;;);
    }
    uart_puts("  hdmi_init OK\n");

    uart_puts("[2/3] Fill FB with 4-band test pattern (R|G|B|W)...\n");
    int band_w = HDMI_FB_W / 4;
    for (int row = 0; row < HDMI_FB_H; ++row) {
        for (int col = 0; col < HDMI_FB_W; ++col) {
            uint32_t color;
            int b = col / band_w;
            switch (b) {
                case 0:  color = 0xFF0000u; break; /* red */
                case 1:  color = 0x00FF00u; break; /* green */
                case 2:  color = 0x0000FFu; break; /* blue */
                default: color = 0xFFFFFFu; break; /* white */
            }
            hdmi_pixel(col, row, color);
        }
    }
    hdmi_flush_fb();

    uart_puts("[3/3] State:\n");
    uart_puts("  dynclk STATUS = 0x"); uart_puthex(*(volatile uint32_t *)0x43C10004u); uart_putchar('\n');
    uart_puts("  VTC STATUS    = 0x"); uart_puthex(*(volatile uint32_t *)0x43C20004u); uart_putchar('\n');
    uart_puts("  VDMA SR       = 0x"); uart_puthex(*(volatile uint32_t *)0x43000004u); uart_putchar('\n');
    uart_puts("\nDone. If a monitor is attached you should see 4 vertical bands.\n");
    uart_drain();
    for (;;);
    return 0;
}
