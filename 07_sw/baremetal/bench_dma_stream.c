/* bench_dma_stream.c — Pillar 2 silicon microbenchmark.
 *
 * Pure-streaming DMA microbench per senior review §16: NOT the workload's
 * BW (that would make the Roofline circular), but a synthetic stream
 * that saturates the HP port with max-burst-length DDR→tile copies.
 * The headline number is the largest sustained MB/s, which becomes the
 * "Empirical Roof" on the Roofline plot (typically 60-80% of theoretical
 * 1.2 GB/s per HP port on Zynq-7000).
 *
 * Sweeps DMA sizes {1KB, 4KB, 16KB, 64KB} to show the BW-vs-size curve:
 *   - small DMAs are dominated by setup overhead (~120 cyc per cgra_dma)
 *   - large DMAs converge to the HP-port sustained ceiling
 *
 * Also measures sustained back-to-back 64KB chunks (16× = 1 MB total)
 * to show whether the engine can keep HP fully busy across multiple
 * issues, which is the more relevant number for any real workload.
 */

#include <stdint.h>
#include "cgra.h"
#include "uart.h"

/* Caches OFF — DDR writes must be immediately visible to CGRA DMA. */
static inline void cache_disable_cp15(void)
{
    uint32_t sctlr;
    __asm__ volatile("mrc p15, 0, %0, c1, c0, 0" : "=r"(sctlr));
    sctlr &= ~((1u << 2) | (1u << 12));
    __asm__ volatile("mcr p15, 0, %0, c1, c0, 0" : : "r"(sctlr));
    __asm__ volatile("isb");
}

#define DDR_SRC_BASE   0x00100000u  /* 1 MB scratch region in DDR */
#define DDR_SRC_BYTES  (1u << 20)   /* 1 MB */

/* CPU clock for cycle→MB/s conversion. 666.666667 MHz @ Zynq-7020. */
#define CPU_HZ         666666667u

static void fill_ddr_pattern(uint32_t *p, uint32_t nwords)
{
    /* Non-zero, non-trivial pattern so DMA engine can't compress away */
    for (uint32_t i = 0; i < nwords; ++i)
        p[i] = (i * 0x9E3779B1u) ^ 0xCAFEBABEu;
}

static void measure_one(const char *label, uint32_t nbytes, int n_iter)
{
    uint32_t cyc_total;

    /* Pre-warm: one untimed DMA so address translation / TLB are hot */
    cgra_dma(DDR_SRC_BASE, CGRA_TILE_BCAST, nbytes);

    arm_ccnt_reset();
    uint32_t t0 = arm_ccnt_read();
    for (int i = 0; i < n_iter; ++i)
        cgra_dma(DDR_SRC_BASE, CGRA_TILE_BCAST, nbytes);
    cyc_total = arm_ccnt_read() - t0;

    uint32_t cyc_per   = cyc_total / (uint32_t)n_iter;
    /* MB/s = bytes / (cycles / cpu_hz) / 1e6  = bytes × cpu_hz / cycles / 1e6 */
    uint32_t mbs = (uint32_t)(((uint64_t)nbytes * CPU_HZ) / cyc_per / 1000000u);

    uart_puts(label);
    uart_puts(" size=");
    if (nbytes >= 1024u) { uart_putdec(nbytes / 1024u); uart_puts(" KB"); }
    else                 { uart_putdec(nbytes);          uart_puts(" B "); }
    uart_puts(" cyc/dma="); uart_putdec(cyc_per);
    uart_puts(" iters=");   uart_putdec((uint32_t)n_iter);
    uart_puts(" BW=");      uart_putdec(mbs); uart_puts(" MB/s\n");
}

int main(void)
{
    cache_disable_cp15();
    uart_init();
    arm_pmu_enable();
    arm_ccnt_reset();

    uart_puts("\n=========================================================\n");
    uart_puts("  bench_dma_stream — Pillar 2: empirical HP-port BW\n");
    uart_puts("  DDR (0x00100000) → CGRA_TILE_BCAST (broadcast to 4 banks)\n");
    uart_puts("  ARM CCNT @ 666.67 MHz brackets each cgra_dma()\n");
    uart_puts("=========================================================\n\n");

    /* Cold-reset CGRA / clear stale DMA state — must happen BEFORE the
     * first DMA call. Same pattern as bench_compare.c:386-391. */
    cgra_cu_reset();
    cgra_wr(CGRA_DMA_CTRL, 0u);
    cgra_wr(CGRA_IRQ_STATUS, 0x7u);
    for (volatile uint32_t k = 0; k < 1000u; k++) ;

    /* Fill 1 MB of DDR with a non-trivial pattern */
    fill_ddr_pattern((uint32_t *)DDR_SRC_BASE, DDR_SRC_BYTES / 4u);
    asm volatile("dsb" ::: "memory");

    uart_puts("Single-shot per-size sweep (100 iter avg):\n");
    measure_one("S01", 1024u,         100);   /*  1 KB */
    measure_one("S02", 4u  * 1024u,   100);   /*  4 KB */
    measure_one("S03", 16u * 1024u,   100);   /* 16 KB */
    measure_one("S04", 64u * 1024u,   100);   /* 64 KB — max single tile  */

    uart_puts("\nSustained back-to-back (1 MB = 16× 64 KB):\n");
    /* 16 iterations of 64 KB = 1 MB total, no idle between issues.
     * Best estimate of "what a real workload sees" from the HP port. */
    measure_one("S_SUST", 64u * 1024u, 16);

    uart_puts("\nROOFLINE EMPIRICAL ROOF:\n");
    uart_puts("  S04 BW is the per-DMA HP-port sustained ceiling.\n");
    uart_puts("  S_SUST BW is the realistic memory-roof for the Roofline.\n");
    uart_puts("  Theoretical Zynq-7000 HP per port = ~1200 MB/s; expect 60-80%.\n");

    uart_puts("\n=== Pillar 2 complete ===\n");
    while (1) ;
    return 0;
}
