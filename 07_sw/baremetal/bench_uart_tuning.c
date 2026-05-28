/* bench_uart_tuning.c — minimal UART-only ELF.
 *
 * Does NOTHING but print a fixed pattern over UART repeatedly so the
 * host can scan baud rates against live output. No CGRA, no DMA, no
 * smoke logic — guaranteed to reach the continuous-print loop.
 *
 * Pattern uses 'U' (0x55, perfectly alternating bits — easiest to
 * recognize at any baud) and '=' (a banner character) plus a known
 * marker string "TUNE" that the host scanner can match.
 */
#include <stdint.h>
#include "uart.h"

extern void Xil_DCacheDisable(void);
extern void Xil_ICacheDisable(void);
__attribute__((weak)) void Xil_DCacheDisable(void) { }
__attribute__((weak)) void Xil_ICacheDisable(void) { }

int main(void)
{
    Xil_DCacheDisable();
    Xil_ICacheDisable();
    uart_init();

    /* Quick startup banner so we can detect the first frame */
    uart_puts("\nTUNE=========================UART=TUNING=ELF=================\n");
    uart_puts("If you can read this, the UART baud matches the host setting.\n");
    uart_puts("Continuous pattern follows...\n");

    /* Infinite loop emitting a recognizable pattern every ~10 ms */
    uint32_t i = 0;
    while (1) {
        for (volatile uint32_t d = 0; d < 100000u; d++) ;   /* delay */
        uart_puts("TUNE=UUUU=== iter ");
        uart_putdec(i++);
        uart_puts(" ===UUUU=\n");
    }
    return 0;
}
