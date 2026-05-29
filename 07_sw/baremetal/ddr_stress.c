/* ddr_stress.c — harsh bare-metal DDR memory test on the Zynq PS.
 *
 * Runs from OCM, exercises a 64 MB DDR region (0x00100000..0x04100000) with
 * classic RAM-test patterns. Caches OFF so we hit real DDR (not the L1/L2).
 *
 * Tests:
 *   T1 address-in-address  — write each word's own address as data, verify
 *                            all. Catches address aliasing / decode faults
 *                            (the exact failure seen with the bad DDR config).
 *   T2 walking 1s / 0s      — per-bit data-bus integrity at sample addresses.
 *   T3 pattern march        — 0x00000000 / 0xFFFFFFFF / 0xAAAAAAAA /
 *                            0x55555555 fill+verify over the whole region.
 *   T4 incrementing fill    — value = index, full-region verify.
 *
 * Reports error counts + first failing address per test. PASS = 0 errors.
 */
#include <stdint.h>
#include "uart.h"

#define DDR_BASE   0x00100000UL
#define DDR_WORDS  (16u * 1024u * 1024u)   /* 64 MB / 4 = 16M words */

static inline void cache_disable_cp15(void)
{
    uint32_t sctlr;
    __asm__ volatile("mrc p15, 0, %0, c1, c0, 0" : "=r"(sctlr));
    sctlr &= ~((1u << 2) | (1u << 12));   /* C + I */
    __asm__ volatile("mcr p15, 0, %0, c1, c0, 0" : : "r"(sctlr));
    __asm__ volatile("isb");
}

static volatile uint32_t *const DDR = (volatile uint32_t *)DDR_BASE;

static void report(const char *name, uint32_t errs, uint32_t first_idx,
                   uint32_t exp, uint32_t got)
{
    uart_puts(name);
    if (errs == 0) { uart_puts(": PASS (0 errors)\n"); return; }
    uart_puts(": FAIL errs="); uart_puthex(errs);
    uart_puts(" @addr=");      uart_puthex(DDR_BASE + first_idx * 4u);
    uart_puts(" exp=");        uart_puthex(exp);
    uart_puts(" got=");        uart_puthex(got);
    uart_putchar('\n');
}

/* T1: write addr-as-data, then verify — aliasing detector */
static uint32_t test_addr_in_addr(void)
{
    for (uint32_t i = 0; i < DDR_WORDS; i++) DDR[i] = DDR_BASE + i * 4u;
    uint32_t errs = 0, fi = 0, fe = 0, fg = 0;
    for (uint32_t i = 0; i < DDR_WORDS; i++) {
        uint32_t exp = DDR_BASE + i * 4u, got = DDR[i];
        if (got != exp) { if (!errs) { fi = i; fe = exp; fg = got; } errs++; }
    }
    report("T1 addr-in-addr", errs, fi, fe, fg);
    return errs;
}

/* T2: walking 1s and 0s on the data bus at a handful of addresses */
static uint32_t test_walking_bits(void)
{
    uint32_t errs = 0, fi = 0, fe = 0, fg = 0;
    const uint32_t addrs[4] = {0u, DDR_WORDS / 4u, DDR_WORDS / 2u, DDR_WORDS - 1u};
    for (int a = 0; a < 4; a++) {
        uint32_t idx = addrs[a];
        for (int b = 0; b < 32; b++) {
            uint32_t w = 1u << b;
            DDR[idx] = w;  if (DDR[idx] != w)  { if (!errs){fi=idx;fe=w;fg=DDR[idx];} errs++; }
            uint32_t nw = ~w;
            DDR[idx] = nw; if (DDR[idx] != nw) { if (!errs){fi=idx;fe=nw;fg=DDR[idx];} errs++; }
        }
    }
    report("T2 walking-bits", errs, fi, fe, fg);
    return errs;
}

/* T3: one pattern fill + verify over the whole region */
static uint32_t test_pattern(const char *lbl, uint32_t pat)
{
    for (uint32_t i = 0; i < DDR_WORDS; i++) DDR[i] = pat;
    uint32_t errs = 0, fi = 0, fg = 0;
    for (uint32_t i = 0; i < DDR_WORDS; i++)
        if (DDR[i] != pat) { if (!errs){fi=i;fg=DDR[i];} errs++; }
    report(lbl, errs, fi, pat, fg);
    return errs;
}

/* T4: value = index */
static uint32_t test_incrementing(void)
{
    for (uint32_t i = 0; i < DDR_WORDS; i++) DDR[i] = i;
    uint32_t errs = 0, fi = 0, fg = 0;
    for (uint32_t i = 0; i < DDR_WORDS; i++)
        if (DDR[i] != i) { if (!errs){fi=i;fg=DDR[i];} errs++; }
    report("T4 incrementing", errs, fi, fi, fg);
    return errs;
}

int main(void)
{
    cache_disable_cp15();
    uart_init();
    uart_puts("\n=========================================================\n");
    uart_puts("  ddr_stress \xe2\x80\x94 harsh DDR test, 64 MB @ 0x00100000\n");
    uart_puts("  caches OFF (raw DDR). PASS = every test 0 errors.\n");
    uart_puts("=========================================================\n");

    uint32_t total = 0;
    total += test_addr_in_addr();
    total += test_walking_bits();
    total += test_pattern("T3a pattern 0x00000000", 0x00000000u);
    total += test_pattern("T3b pattern 0xFFFFFFFF", 0xFFFFFFFFu);
    total += test_pattern("T3c pattern 0xAAAAAAAA", 0xAAAAAAAAu);
    total += test_pattern("T3d pattern 0x55555555", 0x55555555u);
    total += test_incrementing();

    uart_puts("\n=== DDR STRESS RESULT: ");
    uart_puts(total == 0 ? "*** ALL PASS — DDR CLEAN ***" : "*** FAILURES PRESENT ***");
    uart_puts(" total_errs="); uart_puthex(total); uart_putchar('\n');
    uart_puts("=== ddr_stress complete ===\n");
    for (;;) { }
    return 0;
}
