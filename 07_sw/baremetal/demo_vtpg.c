/* =============================================================================
 * demo_vtpg.c — Silicon-validate the AXIS→VDMA→DDR capture path using the
 *               PL-internal v_tpg test pattern generator (Procedure B bitstream).
 *
 * Path:    v_tpg (640×480 RGB colour bars)
 *      ──► axis_switch_in.S01 ──► M00
 *      ──► color_convert ──► pixel_pack ──► axi_vdma (S2MM) ──► DDR @ 0x1100_0000
 *
 * No HDMI cable needed. No VTC enable needed (v_tpg generates its own
 * timing). This is the bare-metal equivalent of "is the capture chain
 * functional?" — proves end-to-end at the silicon level without the
 * external-source dependency.
 *
 * Expected UART output after the banner:
 *   [vtpg ] tpg.AP_CTRL=0x84  switch.MUX0=0x00000001
 *   [vdma ] frame=N ready=R FB0[0..3]=<24-bit colour-bar pixel>
 *
 * After a few seconds the operator can dump DDR via XSDB:
 *   mrd -bin -file /tmp/fb.bin 0x11000000 921600
 * Then render to BMP with scripts/hdmi_in_dump_to_bmp.py — the result
 * MUST show recognisable vertical colour bars.
 * ============================================================================= */
#include <stdint.h>
#include "uart.h"
#include "hdmi_in_bm.h"
#include "vtpg.h"

static void delay_ms(int ms)
{
    /* CGRA clock is 50 MHz; loop is ~4 insns ⇒ ~12 Mcyc/ms. */
    for (volatile int i = 0; i < ms * 12000; i++) ;
}

int main(void)
{
    uart_init();
    uart_puts("\n=================================================\n");
    uart_puts("  v_tpg AXIS capture silicon test  (Procedure B)\n");
    uart_puts("  bitstream: cgra_vtpg_test.bit\n");
    uart_puts("=================================================\n");

    /* 1. Bring up VDMA + color_convert + pixel_pack (same as HDMI-in
     *    flow). VTC stays gated — v_tpg drives its own timing. */
    uart_puts("[init ] VDMA + color_convert + pixel_pack...");
    hdmi_in_init();
    uart_puts(" done\n");

    /* 1b. v_tpg outputs YCbCr-444 (silicon-validated 2026-05-24:
     *     SOLID_BLACK → bytes (0, 128, 128), SOLID_RED → (76, 85, 255),
     *     i.e. byte order (Y, Cb, Cr) with BT.601 full-range coding).
     *     Program color_convert with the YCbCr→RGB BT.601 matrix so
     *     the FB ends up as a viewable RGB image. */
    uart_puts("[init ] color_convert: YCbCr-444 -> RGB (BT.601)\n");
    hdmi_in_color_convert_ycbcr2rgb();

    /* 2. Route the AXIS switch to the v_tpg source (S01 → M00). */
    uart_puts("[init ] axis_switch_in: route S01 (v_tpg) -> M00\n");
    vtpg_axis_switch_route(AXIS_SWITCH_SRC_VTPG);

    /* 3. Start v_tpg in free-run mode (colour bars, 640×480 RGB). */
    uart_puts("[init ] v_tpg: 640x480 RGB colour bars, auto-restart\n");
    vtpg_start(640, 480, VTPG_PATTERN_COLOR_BARS);

    /* Brief settle period — the HLS pipeline drains a few hundred cycles
     * before the first frame appears at color_convert. */
    delay_ms(50);

    uart_puts("[init ] free-running. Reporting every 500 ms.\n");
    uart_puts("        XSDB:  mrd -bin -file /tmp/fb.bin 0x11000000 921600\n\n");

    uint32_t loop_n = 0;
    while (1) {
        const int ready  = hdmi_in_frame_ready();
        const uint8_t *fb = hdmi_in_current_frame();
        uint32_t tpg_ctrl   = vtpg_mmio_r(VTPG_BASE + VTPG_AP_CTRL);
        uint32_t switch_mux = vtpg_mmio_r(AXIS_SWITCH_BASE +
                                          AXIS_SWITCH_MI_MUX0);

        uart_puts("[stat ] n=");          uart_putdec(loop_n++);
        uart_puts("  ready=");            uart_putdec(ready);
        uart_puts("  tpg.AP=");           uart_puthex(tpg_ctrl);
        uart_puts("  switch.MUX0=");      uart_puthex(switch_mux);
        uart_puts("  FB0[0..3]=");
        uart_puthex(((uint32_t)fb[0] << 0)  |
                    ((uint32_t)fb[1] << 8)  |
                    ((uint32_t)fb[2] << 16) |
                    ((uint32_t)fb[3] << 24));
        uart_puts("\n");

        delay_ms(500);
    }
    return 0;
}
