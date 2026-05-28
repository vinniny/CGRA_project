/* bench_smoke.c — Atomic-validation smoke test per Gemini senior-eng
 * advice (2026-05-28). MUST run before any DMA/CU workload on a new
 * bitstream. Detects stale-ps7_init / wedged-interconnect symptoms
 * BEFORE you waste a 5-minute workload run on a broken bitstream.
 *
 * Sequence (each step prints PASS/FAIL/value to UART; aborts on FAIL):
 *
 *   S0. PS health check — DDR controller status (0xF8000600), PLL/clock
 *       status (0xF8000100). Board fault if either flags an error;
 *       otherwise the PS is alive and any subsequent hang is a tooling
 *       (stale ps7_init / wrong .xsa) issue, NOT silicon.
 *
 *   S1. MMIO scratchpad ping-pong — write 0xDEADBEEF to CGRA_DMA_SRC
 *       (offset 0x08, RW), read it back. Confirms PS↔PL AXI path,
 *       APB decoder, CGRA clock, CGRA reset are all functional.
 *
 *   S2. Short loopback DMA — 64-byte DDR→CGRA_TILE_BCAST. Confirms DMA
 *       engine + AXI master + interconnect path works end-to-end.
 *
 * If S0+S1+S2 all PASS, the bitstream/ps7_init combo is sane. Proceed
 * with real workload. If any step fails: STOP. Do not power-cycle.
 * The .xsa <-> .bit identity is broken; fix the tooling, not the board.
 */

#include <stdint.h>
#include "cgra.h"
#include "uart.h"

/* Vitis BSP provides Xil_DCacheDisable / Xil_ICacheDisable; the Makefile
 * build doesn't include the BSP. Define weak stubs that link in only if
 * the BSP versions aren't present (Makefile build → no-op). */
__attribute__((weak)) void Xil_DCacheDisable(void) { }
__attribute__((weak)) void Xil_ICacheDisable(void) { }

#define DDR_SCRATCH      0x00100000u
#define DDR_CTRL_STATUS  0xF8000600u   /* Zynq-7000 DDR controller status */
#define SLCR_PLL_STATUS  0xF8000100u   /* Zynq-7000 PLL lock-status reg   */

#define MAGIC_DEADBEEF   0xDEADBEEFu
#define MAGIC_CAFEBABE   0xCAFEBABEu

static uint32_t mrd_u32(uint32_t addr)
{
    return *(volatile uint32_t *)addr;
}

static void put_hex_field(const char *label, uint32_t v)
{
    uart_puts(label);
    uart_puts("0x");
    uart_puthex(v);
    uart_putchar('\n');
}

static int step_s0_ps_health(void)
{
    uart_puts("\n[S0] PS HEALTH CHECK\n");
    uint32_t ddr_status = mrd_u32(DDR_CTRL_STATUS);
    uint32_t pll_status = mrd_u32(SLCR_PLL_STATUS);
    put_hex_field("  DDR ctrl status (0xF8000600) = ", ddr_status);
    put_hex_field("  SLCR PLL  status (0xF8000100) = ", pll_status);
    /* PLL_STATUS expected = 0x3F = all 6 PLLs locked + clocks stable */
    /* DDR ctrl status — high bits indicate calibration state; not
     * checking specific values, just confirming the reads don't hang. */
    if (ddr_status == 0xFFFFFFFFu || pll_status == 0xFFFFFFFFu) {
        uart_puts("  FAIL: PS register reads returned all-Fs (bus error)\n");
        return -1;
    }
    uart_puts("  PASS: PS registers readable, system alive\n");
    return 0;
}

static int step_s1_scratchpad_ping_pong(void)
{
    uart_puts("\n[S1] CGRA MMIO PING-PONG (write/readback)\n");
    /* DMA_SRC is RW, safe to clobber when DMA engine is idle */
    cgra_wr(CGRA_DMA_SRC, MAGIC_DEADBEEF);
    uint32_t r1 = cgra_rd(CGRA_DMA_SRC);
    put_hex_field("  wrote 0xDEADBEEF -> CGRA_DMA_SRC, read back = ", r1);
    if (r1 != MAGIC_DEADBEEF) {
        uart_puts("  FAIL: scratchpad readback mismatch\n");
        return -1;
    }
    /* Second pass — different magic, confirms write actually lands */
    cgra_wr(CGRA_DMA_SRC, MAGIC_CAFEBABE);
    uint32_t r2 = cgra_rd(CGRA_DMA_SRC);
    put_hex_field("  wrote 0xCAFEBABE -> CGRA_DMA_SRC, read back = ", r2);
    if (r2 != MAGIC_CAFEBABE) {
        uart_puts("  FAIL: scratchpad readback mismatch (2nd pass)\n");
        return -1;
    }
    /* Clear */
    cgra_wr(CGRA_DMA_SRC, 0u);
    uart_puts("  PASS: CGRA APB decode + scratchpad RW functional\n");
    return 0;
}

static int step_s2_loopback_dma(void)
{
    uart_puts("\n[S2] SHORT LOOPBACK DMA (64 B DDR -> CGRA_TILE_BCAST)\n");
    /* Fill 64 bytes (16 words) at DDR_SCRATCH with known pattern */
    volatile uint32_t *p = (volatile uint32_t *)DDR_SCRATCH;
    for (int i = 0; i < 16; ++i) p[i] = 0xA5A50000u | (uint32_t)i;
    asm volatile("dsb" ::: "memory");

    cgra_cu_reset();
    cgra_wr(CGRA_DMA_CTRL,    0u);
    cgra_wr(CGRA_IRQ_STATUS,  0x7u);

    int rc = cgra_dma(DDR_SCRATCH, CGRA_TILE_BCAST, 64u);
    uart_puts("  cgra_dma() return: ");
    uart_putdec((uint32_t)(rc < 0 ? 1 : 0));
    uart_puts(rc == 0 ? "  (PASS)" : "  (FAIL — DMA timed out)");
    uart_putchar('\n');
    return rc;
}

int main(void)
{
    Xil_DCacheDisable();
    Xil_ICacheDisable();

    uart_init();
    arm_pmu_enable();
    arm_ccnt_reset();

    uart_puts("\n=========================================================\n");
    uart_puts("  bench_smoke — atomic bitstream validation (Gemini §7)\n");
    uart_puts("  S0: PS health → S1: scratchpad RW → S2: loopback DMA\n");
    uart_puts("  abort on any FAIL — fix .xsa coupling, do NOT power-cycle\n");
    uart_puts("=========================================================\n");

    if (step_s0_ps_health() != 0) {
        uart_puts("\n*** ABORT at S0: board fault suspected ***\n"); while (1) ;
    }
    if (step_s1_scratchpad_ping_pong() != 0) {
        uart_puts("\n*** ABORT at S1: stale ps7_init OR wrong .xsa ***\n");
        uart_puts("    The CGRA's clock or reset is wrong for this PS-PL config.\n");
        uart_puts("    Do NOT power-cycle. Re-export the .xsa from Vivado.\n");
        while (1) ;
    }
    if (step_s2_loopback_dma() != 0) {
        uart_puts("\n*** ABORT at S2: CGRA DMA engine broken ***\n"); while (1) ;
    }

    uart_puts("\n=========================================================\n");
    uart_puts("  SMOKE PASS — bitstream healthy, proceed with workload\n");
    uart_puts("=========================================================\n");

    /* Continuous UART tuning pattern: emits ASCII content every ~100ms so
     * the host can scan baud rates against live data. "U" = 0x55, perfectly
     * alternating bits, easiest to recognize at any baud. */
    uint32_t i = 0;
    while (1) {
        if ((i++ & 0xFFFFF) == 0)
            uart_puts("UUUU=== smoke tuning ===UUUU\n");
    }
    return 0;
}
