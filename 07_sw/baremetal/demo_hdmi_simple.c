/* =============================================================================
 * demo_hdmi_simple.c — minimal HDMI-in capture without axis_switch.
 *
 * Pairs with bitstreams/cgra_top.bit (the production silicon-validated
 * bitstream that has dvi2rgb -> color_convert -> pixel_pack -> VDMA
 * WITHOUT the axis_switch from Procedures B/D). This removes the switch
 * as a variable when debugging "VDMA halts on SOFEarlyErr" against a
 * live HDMI source.
 *
 * The diff from demo_hdmi_live.c: no vtpg.h include, no axis_switch
 * route call. Everything else is identical (HPD assert + identity matrix
 * + VTC skipped + loop reporting).
 * ============================================================================= */
#include <stdint.h>
#include "uart.h"
#include "hdmi_in_bm.h"

static void delay_ms(int ms)
{
    for (volatile int i = 0; i < ms * 12000; i++) ;
}

int main(void)
{
    uart_init();
    uart_puts("\n=================================================\n");
    uart_puts("  HDMI SIMPLE capture (no axis_switch)\n");
    uart_puts("  bitstream: cgra_top.bit (production)\n");
    uart_puts("=================================================\n");

    uart_puts("[init ] HDMI-in HPD = 1 (request source to transmit)\n");
    hdmi_in_assert_hpd();
    delay_ms(2000);            /* extra time for source to renegotiate */

    uart_puts("[init ] VDMA + color_convert + pixel_pack...");
    hdmi_in_init();
    uart_puts(" done\n");

    /* Identity matrix — laptop sends RGB-full over HDMI; dvi2rgb passes
     * RGB through; color_convert with identity = clean RGB output. */
    uart_puts("[init ] color_convert: identity (RGB->RGB)\n");
    hdmi_in_color_convert_identity();

    uart_puts("[init ] VTC enable SKIPPED (avoid AXI hang if dvi2rgb unlocked)\n");

    delay_ms(500);
    uart_puts("[init ] reporting every 500 ms.\n\n");

    uint32_t loop_n = 0;
    while (1) {
        const int ready  = hdmi_in_frame_ready();
        const uint8_t *fb = hdmi_in_current_frame();

        uart_puts("[stat ] n=");      uart_putdec(loop_n++);
        uart_puts("  frame_ready=");  uart_putdec(ready);
        uart_puts("  FB0[0..15]=");
        for (int b = 0; b < 16; b++) uart_puthex(fb[b]);
        uart_puts("\n");

        delay_ms(500);
    }
    return 0;
}
