/* =========================================================================
 * uart.h — Minimal Zynq PS UART0 driver (bare-metal, no OS)
 *
 * UART0 base: 0xE0000000
 * MIO pins: MIO[14]=RX, MIO[15]=TX (configured by ps7_init)
 *
 * ps7_init configures MIO[14]/[15] and sets baud divisors:
 *   BAUD_RATE_GEN (CD)   = 124  (0x7C)
 *   BAUD_RATE_DIV (BDIV) = 6
 *   Actual baud = 100MHz / 124 / 7 = 115,384 (~0.16% error @ 115200)
 *
 * uart_init() resets FIFOs, reapplies mode and baud, then enables TX/RX.
 * Do NOT configure MIO here — ps7_init already does it correctly.
 * ========================================================================= */
#ifndef UART_H
#define UART_H

#include <stdint.h>

#define UART0_BASE      0xE0000000UL

/* Register offsets (Zynq UG585 Table 19-2) */
#define UART_CR         0x00    /* Control Register */
#define UART_MR         0x04    /* Mode Register */
#define UART_SR         0x2C    /* Channel Status Register */
#define UART_FIFO       0x30    /* Tx/Rx FIFO */
#define UART_BAUD_GEN   0x18    /* Baud Rate Generator (CD) */
#define UART_BAUD_DIV   0x34    /* Baud Rate Divider (BDIV) */

/* CR bits */
#define UART_CR_RXRST   (1u << 0)
#define UART_CR_TXRST   (1u << 1)
#define UART_CR_RX_EN   (1u << 2)
#define UART_CR_RX_DIS  (1u << 3)
#define UART_CR_TX_EN   (1u << 4)
#define UART_CR_TX_DIS  (1u << 5)

/* SR bits */
#define UART_SR_TXFULL  (1u << 4)
#define UART_SR_TXEMPTY (1u << 3)

static inline void uart_init(void)
{
    volatile uint32_t *cr = (volatile uint32_t *)(UART0_BASE + UART_CR);

    /* Disable TX/RX and reset FIFOs */
    *cr = UART_CR_TX_DIS | UART_CR_RX_DIS;
    *cr = UART_CR_TXRST  | UART_CR_RXRST;
    for (volatile int i = 0; i < 200; i++) ;

    /* 8N1, uart_ref_clk (matches ps7_init MR=0x20) */
    *(volatile uint32_t *)(UART0_BASE + UART_MR) = 0x20u;

    /* Baud: CD=124, BDIV=6 → 115200 @ 100 MHz ref (matches ps7_init) */
    *(volatile uint32_t *)(UART0_BASE + UART_BAUD_GEN) = 124u;
    *(volatile uint32_t *)(UART0_BASE + UART_BAUD_DIV) = 6u;

    /* Enable TX and RX */
    *cr = UART_CR_TX_EN | UART_CR_RX_EN;
    for (volatile int i = 0; i < 200; i++) ;
}

static inline void uart_putchar(char c)
{
    volatile uint32_t *sr   = (volatile uint32_t *)(UART0_BASE + UART_SR);
    volatile uint32_t *fifo = (volatile uint32_t *)(UART0_BASE + UART_FIFO);
    while (*sr & UART_SR_TXFULL)
        ;
    *fifo = (uint32_t)c;
}

static inline void uart_drain(void)
{
    volatile uint32_t *sr = (volatile uint32_t *)(UART0_BASE + UART_SR);
    while (!(*sr & UART_SR_TXEMPTY))
        ;
}

static inline void uart_puts(const char *s)
{
    while (*s) {
        if (*s == '\n') {
            uart_putchar('\r');
            uart_putchar('\n');
            /* Drain TX FIFO at end of each line — gives the USB-serial host
             * time to absorb the burst and prevents dropped lines on long
             * back-to-back prints. ~5.5 ms per line, but only on \n. */
            uart_drain();
            for (volatile int i = 0; i < 5000; i++) ;
            s++;
            continue;
        }
        uart_putchar(*s++);
    }
}

static inline void uart_puthex(uint32_t v)
{
    const char hex[] = "0123456789ABCDEF";
    uart_puts("0x");
    for (int i = 28; i >= 0; i -= 4)
        uart_putchar(hex[(v >> i) & 0xF]);
}

static inline void uart_puthex64(uint64_t v)
{
    uart_puthex((uint32_t)(v >> 32));
    uart_putchar('_');
    uart_puthex((uint32_t)(v & 0xFFFFFFFF));
}

static inline void uart_putdec(uint32_t v)
{
    char buf[12];
    int i = 11;
    buf[i] = '\0';
    if (v == 0) { uart_putchar('0'); return; }
    while (v && i > 0) { buf[--i] = '0' + (v % 10); v /= 10; }
    uart_puts(&buf[i]);
}

#endif /* UART_H */
