/* =============================================================================
 * demo_hdmi_live.c — Capture a LIVE HDMI source through the AXIS chain.
 *
 * Pipeline:
 *   Laptop ──HDMI── splitter ──┬──> J10 (PYNQ-Z2) ──> dvi2rgb ──> frontend
 *                              └──> external monitor (passive mirror, user
 *                                   sees what the laptop sends)
 *
 *   frontend.video_out ──> axis_switch_in.S00 ──> color_convert (YCbCr->RGB,
 *                                                  BT.709 for HD laptop)
 *                                              ──> pixel_pack (V_24 RGB)
 *                                              ──> axi_vdma (S2MM)
 *                                              ──> DDR @ 0x1100_0000
 *
 * Requires:
 *   bitstream: bitstreams/cgra_vtpg_ila.bit (has axis_switch + ILA), or
 *              cgra_vtpg_test.bit (axis_switch but no ILA). The original
 *              cgra_top.bit has no axis_switch -- run demo_hdmi_in_capture.elf
 *              against that one instead.
 *   HDMI cable plugged into J10 with a *live* source on the other end.
 *   The board's HDMI-out (J11) is independent of this demo.
 *
 * Output:
 *   UART telemetry every 500 ms with VTC lock bit, frame counter, first 4
 *   bytes of FB0.
 *
 * To dump the frame from a host XSDB shell:
 *   stop
 *   mrd -bin -file /tmp/fb.bin 0x11000000 230400
 *   con
 *
 * Then render: python3 scripts/hdmi_in_dump_to_bmp.py /tmp/fb.bin \
 *                      -o /tmp/fb.bmp -w 640 --height 480 --rgb-order RGB
 * ============================================================================= */
#include <stdint.h>
#include "uart.h"
#include "hdmi_in_bm.h"
#include "vtpg.h"

static void delay_ms(int ms)
{
    /* CGRA clock ~50 MHz; tight 4-insn loop ~12 Mcyc/ms. Coarse busy wait. */
    for (volatile int i = 0; i < ms * 12000; i++) ;
}

int main(void)
{
    uart_init();
    uart_puts("\n=================================================\n");
    uart_puts("  HDMI LIVE capture  (axis_switch.S00 = dvi2rgb)\n");
    uart_puts("  bitstream: cgra_vtpg_ila.bit or cgra_vtpg_test.bit\n");
    uart_puts("=================================================\n");

    /* 0. ASSERT HPD FIRST — laptop won't transmit until it sees a "monitor"
     *    on this output. Some HDMI splitters also gate downstream
     *    forwarding on HPD. Drive HPD high, then give the source ~1 sec
     *    to renegotiate and start streaming.
     *
     * Note: kept in this v_tpg demo's main() (not in hdmi_in_init) because
     * the production demo_mnist_hdmi_bm runs hdmi_in_init AFTER hdmi_init
     * (HDMI-OUT) and a shared VDMA reset disturbs HDMI-OUT timing. Each
     * demo decides when to assert HPD. */
    uart_puts("[init ] HDMI-in HPD = 1 (request source to transmit)\n");
    hdmi_in_assert_hpd();
    delay_ms(1000);

    /* 1. Bring up VDMA + color_convert + pixel_pack (CIRCULAR_PARK in DMACR
     *    so FrameStore cycles through the 3-frame ring). */
    uart_puts("[init ] VDMA + color_convert + pixel_pack...");
    hdmi_in_init();
    hdmi_in_color_convert_identity();
    uart_puts(" done\n");

    /* 2. Program color_convert with IDENTITY -- Windows / typical HDMI
     *    sources send RGB-full on the wire, and dvi2rgb passes RGB through
     *    v_vid_in_axi4s as 24-bit RGB AXIS. A YCbCr->RGB matrix on RGB
     *    input would scramble it into noise. Use BT.709 / BT.601 ONLY
     *    when the source is known to send YCbCr-444 (e.g. v_tpg pattern). */
    uart_puts("[init ] color_convert: identity (RGB->RGB passthrough)\n");
    hdmi_in_color_convert_identity();

    /* 3. Route axis_switch to S00 = dvi2rgb. If we just came from
     *    demo_vtpg.elf, MUX0 is currently 0x01 (S01 = v_tpg) -- this flips
     *    it back. Safe to call even if axis_switch isn't in the bitstream
     *    (the write hits unmapped AXI space and returns SLVERR which the
     *    AXI bus absorbs without halting the CPU; but you'll see no
     *    capture). */
    uart_puts("[init ] axis_switch_in: route S00 (dvi2rgb) -> M00\n");
    vtpg_axis_switch_route(AXIS_SWITCH_SRC_HDMI);

    /* 4. VTC detector enable is INTENTIONALLY SKIPPED in this demo.
     *    VTC's AXI-Lite slave is clocked by dvi2rgb's recovered PixelClk;
     *    if dvi2rgb hasn't locked (wrong resolution, no cable, signal
     *    integrity issue), the VTC write stalls the AXI bus -> external
     *    abort + CPU hang. VDMA capture itself does not require VTC --
     *    it just needs TVALID on the AXIS chain. So we skip VTC, capture
     *    frames blind, and report FB state. If frames are non-zero ->
     *    dvi2rgb DID lock. If FB stays at the previous bitstream's
     *    leftover -> dvi2rgb didn't lock; check resolution / cable.
     *
     *    Once silicon confirms dvi2rgb locks at the source's resolution,
     *    we can re-enable VTC in a separate demo via:
     *      hdmi_in_enable_vtc(); */
    uart_puts("[init ] VTC enable SKIPPED (avoid AXI hang if dvi2rgb unlocked)\n");

    /* Let dvi2rgb lock + a couple frames flow before we start reporting. */
    delay_ms(200);

    uart_puts("[init ] loop reporting every 500 ms.\n");
    uart_puts("        Host dump:  mrd -bin -file /tmp/fb.bin 0x11000000 230400\n\n");

    uint32_t loop_n = 0;
    while (1) {
        const int ready  = hdmi_in_frame_ready();
        const uint8_t *fb = hdmi_in_current_frame();
        /* hdmi_in_locked() is gated by VTC AXI-Lite -- would hang if
         * PixelClk is dead. Skipped along with the VTC enable above. */

        uart_puts("[stat ] n=");      uart_putdec(loop_n++);
        uart_puts("  frame_ready=");  uart_putdec(ready);
        uart_puts("  FB0[0..15]=");
        for (int b = 0; b < 16; b++) uart_puthex(fb[b]);
        uart_puts("\n");

        delay_ms(500);
    }
    return 0;
}
