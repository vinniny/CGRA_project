/* =============================================================================
 * demo_hdmi_in_capture.c — minimal sanity ELF for the HDMI-input bring-up.
 *
 * Boots, initializes the dvi2rgb → v_tc_1 → v_vid_in_axi4s →
 * axis_subset_converter_in → axi_vdma_1 capture chain, then loops forever
 * reporting:
 *
 *   - the v_tc_1 detector "locked" flag
 *   - the VDMA "busy/not-halted" status
 *   - the first 4 bytes of the current frame buffer (proves SOMETHING got
 *     written to DDR)
 *
 * Once the laptop is plugged into J10 and the dump shows non-zero pixel
 * bytes, scale up to demo_mnist_hdmi_bm.elf with LIVE_INPUT=1.
 * =============================================================================
 */
#include <stdint.h>
#include "uart.h"
#include "hdmi_in_bm.h"

static void delay_ms(int ms)
{
    /* PS7 CGRA clock is 50 MHz. A trivial busy loop here is roughly
     * 4 instructions per iteration → ~12 Mcyc/ms. Order-of-magnitude. */
    for (volatile int i = 0; i < ms * 12000; i++) ;
}

int main(void)
{
    uart_init();
    uart_puts("\n========================================\n");
    uart_puts("  HDMI-IN capture sanity v1\n");
    uart_puts("  (no-HDMI mode: capture pipeline tested\n");
    uart_puts("   via XSDB-injected DDR pixels)\n");
    uart_puts("========================================\n");

    uart_puts("Initialising HDMI-in chain (VTC skipped)...\n");
    hdmi_in_init();
    uart_puts("  done.\n");

    uart_puts("Loop will report frame state every 500 ms.\n");
    uart_puts("To inject fake pixels via XSDB:\n");
    uart_puts("  mwr 0x11000000 0x55555555 230400\n");
    uart_puts("  then dump:\n");
    uart_puts("  mrd -bin -file /tmp/fb.bin 0x11000000 921600\n\n");

    uint32_t frame_n = 0;
    while (1) {
        const int ready  = hdmi_in_frame_ready();
        const uint8_t *fb = hdmi_in_current_frame();

        uart_puts("[capture] frame=");
        uart_putdec(frame_n++);
        uart_puts("  ready=");
        uart_putdec(ready);
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
