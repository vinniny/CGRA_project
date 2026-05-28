/* bench_mac_micro.c — Pillar 1 silicon microbenchmark.
 *
 * Pure-compute MAC microkernel that pins both operands in PE immediate
 * fields (SRC_IMM, SRC_IMM) — no SPM read, no DMA, no readout overhead.
 * This isolates the architectural-peak MAC/cycle of a single PE, which
 * is the compute-roof of the Roofline plot.
 *
 * Mirrors the simulation Suite MTP (01_bench/include/tb_suite_mac_throughput.svh)
 * with three LOOP_COUNT settings to expose the startup/drain cost vs
 * steady-state efficiency. The senior review §28 requires this as the
 * bottom-of-stack measurement before any layer or end-to-end timing.
 *
 * Expected silicon (matches simulation, contribs = 16·N − 3 model):
 *   MTP01  LOOP_COUNT=0   1 pass    contribs=~13   cycles=~16    ~80% slot eff
 *   MTP02  LOOP_COUNT=9   10 passes contribs=~157  cycles=~160   ~98%
 *   MTP03  LOOP_COUNT=63  64 passes contribs=~1021 cycles=~1024  ~99.7%
 *
 * Headline number for the thesis: MTP03's cycle_eff is the architectural
 * peak MAC/cyc per PE on PYNQ-Z2 silicon. Multiply by 16 PEs × 50 MHz
 * to get peak GOPS.
 */

#include <stdint.h>
#include "cgra.h"
#include "uart.h"

/* Vitis BSP enables D-cache at boot. cgra_config_pe_slot writes config
 * words to DDR via volatile pointers without flushing — works with
 * caches off (Makefile build) but fails when caches are on (Vitis
 * build). Declare the BSP helper here rather than pull in xil_cache.h
 * so this ELF stays portable between Makefile and Vitis builds. */
extern void Xil_DCacheDisable(void);
extern void Xil_ICacheDisable(void);

/* CU_STATUS_DONE defined in cgra.h (bit 1 = done) */
#define DDR_STAGE       0x00100000u
#define PE_TEST         3u   /* PE[0,3] east edge — direct RESULT_ROW0 readout */

static void cgra_clear_irqs(void) { cgra_wr(CGRA_IRQ_STATUS, 0x7u); }

static int cu_run_wait(void)
{
    cgra_wr(CGRA_CU_CTRL, 1u);
    for (uint32_t t = 0; t < 1000000u; t++) {
        if (cgra_rd(CGRA_CU_STATUS) & CU_STATUS_DONE) return 0;
    }
    return -1;
}

/* NOP-fill all 16 PEs — required before any kernel, otherwise stale
 * config slots from prior runs can stall the CU. Mirrors
 * bench_cgra.c:cfg_all_nop(). */
static void cfg_all_nop(void)
{
    for (uint32_t pe = 0; pe < 16; pe++)
        cgra_config_pe(pe, DDR_STAGE, OP_NOP, 0, 0, 0, 0, 0);
}

static void bench_setup(void)
{
    cgra_cu_reset();
    cgra_clear_irqs();
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   15);
    cgra_wr(CGRA_LOOP_COUNT,  0);
    cgra_wr(CGRA_LOOP2_START, 0);
    cgra_wr(CGRA_LOOP2_END,   0);
    cgra_wr(CGRA_LOOP2_COUNT, 0);
    cgra_wr(CGRA_TILE_AUTO_INC, 0);
    cgra_wr(CGRA_TILE_BANK_SEL, 0);
    cgra_wr(CGRA_CU_PC_END,   15);
    cfg_all_nop();
}

/* Configure PE[0,3] with slot 0 = ACC_CLR, slots 1..15 = MAC(IMM=1, IMM=1).
 * Acc accumulates +1 per effective MAC; the readout value = contribs. */
static void cfg_mac_kernel(void)
{
    cgra_config_pe_slot(PE_TEST, 0, DDR_STAGE,
                        OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
    for (uint32_t s = 1; s < 16; s++) {
        cgra_config_pe_slot(PE_TEST, s, DDR_STAGE,
                            OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E, 1);
    }
}

static void run_one(const char *label, uint32_t loop_count)
{
    bench_setup();
    cfg_mac_kernel();
    cgra_wr(CGRA_LOOP_COUNT, loop_count);

    int tmo = cu_run_wait();
    uint32_t cycles   = cgra_rd(CGRA_CU_CYCLES);
    uint32_t contribs = cgra_rd(CGRA_RESULT_ROW0);
    uint32_t status   = cgra_rd(CGRA_CU_STATUS);
    if (tmo != 0) {
        uart_puts(label);
        uart_puts(": TIMEOUT  CU_STATUS=0x");  uart_puthex(status);
        uart_puts(" CU_CYCLES="); uart_putdec(cycles);
        uart_puts(" ROW0=");      uart_putdec(contribs);
        uart_putchar('\n');
        return;
    }
    uint32_t passes   = loop_count + 1u;
    uint32_t expected = 16u * passes - 3u;  /* closed-form for SRC_IMM */

    /* Efficiencies in tenths-of-percent (e.g. 997 → "99.7%") */
    uint32_t slot_eff_x10  = (passes > 0)
        ? (contribs * 1000u) / (16u * passes) : 0u;
    uint32_t cycle_eff_x10 = (cycles > 0)
        ? (contribs * 1000u) / cycles : 0u;

    uart_puts(label);
    uart_puts(" passes=");  uart_putdec(passes);
    uart_puts(" contribs=");uart_putdec(contribs);
    uart_puts(" (exp=");    uart_putdec(expected);
    uart_puts(") cycles="); uart_putdec(cycles);
    uart_puts(" slot_eff=");
        uart_putdec(slot_eff_x10/10u); uart_putchar('.');
        uart_putdec(slot_eff_x10%10u);  uart_putchar('%');
    uart_puts(" cycle_eff=");
        uart_putdec(cycle_eff_x10/10u); uart_putchar('.');
        uart_putdec(cycle_eff_x10%10u); uart_putchar('%');
    uart_putchar('\n');
}

int main(void)
{
    /* Match the Makefile-build behavior — caches OFF — so that
     * cgra_config_pe_slot's volatile DDR writes are immediately visible
     * to the CGRA DMA engine. */
    Xil_DCacheDisable();
    Xil_ICacheDisable();

    uart_init();
    arm_pmu_enable();
    arm_ccnt_reset();

    uart_puts("\n=========================================================\n");
    uart_puts("  bench_mac_micro — Pillar 1: architectural-peak MAC/cyc\n");
    uart_puts("  PE[0,3] OP_MAC(SRC_IMM=1, SRC_IMM=1) — pure compute, no SPM/DMA\n");
    uart_puts("  16 slots × N passes  (contribs = 16·N − 3 closed form)\n");
    uart_puts("=========================================================\n");

    /* Cold-reset CGRA to recover from any prior state (mirrors
     * bench_compare.c:386-391). Without this, residual PL state from a
     * failed prior run can hang the first DMA inside cgra_config_pe. */
    cgra_cu_reset();
    cgra_clear_irqs();
    cgra_wr(CGRA_DMA_CTRL, 0u);
    for (volatile uint32_t k = 0; k < 1000u; k++) ;
    uart_puts("[CGRA cold-reset complete]\n\n");

    run_one("MTP01", 0u);   /*  1 pass    — 1-pass slot efficiency  */
    run_one("MTP02", 9u);   /* 10 passes  — steady-state efficiency */
    run_one("MTP03", 63u);  /* 64 passes  — asymptotic peak         */

    /* Headline summary — the Roofline compute-roof number */
    uart_puts("\nROOFLINE COMPUTE ROOF (per PE):\n");
    uart_puts("  MTP03 cycle_eff IS the architectural peak MAC/cyc/PE.\n");
    uart_puts("  Peak GOPS = MTP03_eff × 16 PE × 50 MHz × 2 ops/MAC\n");
    uart_puts("            ≈ 1.6 GOPS theoretical (1 MAC = 2 ops).\n");

    uart_puts("\n=== Pillar 1 complete ===\n");
    while (1) ;
    return 0;
}
