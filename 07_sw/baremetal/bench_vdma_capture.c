/* =============================================================================
 * bench_vdma_capture.c — measure VDMA capture throughput driven by v_tpg.
 *
 * Loop:
 *   1. snapshot the cycle counter (PMCCNTR)
 *   2. spin until N frames have been captured (FrameStore advances)
 *   3. snapshot again
 *   4. compute frames/sec and bytes/sec, print over UART
 *
 * Pairs with bitstreams/cgra_vtpg_ila.bit OR cgra_vtpg_test.bit. Useful
 * to quantify the cost of the capture chain and how close it comes to
 * the theoretical 142.857 MHz × 24 bits = 428.6 MB/s peak.
 *
 * Expected results on PYNQ-Z2 with the Procedure-D bitstream:
 *   640 × 480 × 3 B per frame = 921 600 B
 *   At 60 Hz output rate → 55.3 MB/s sustained
 *   v_tpg + axis_switch generates a sample every clk_142M tick, so the
 *   sustained framerate is bounded by VDMA + HP0 + DDR bandwidth (~110
 *   MB/s peak on HP0 / 32-bit @ 100 MHz interconnect side).
 * =============================================================================
 */
#include <stdint.h>
#include "uart.h"
#include "hdmi_in_bm.h"
#include "vtpg.h"

#define FRAMES_PER_TRIAL  60   /* about 1 s at 60 Hz */
#define NUM_TRIALS        4

static inline uint32_t pmccntr_read(void)
{
    uint32_t c;
    __asm__ volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(c));
    return c;
}
static inline void pmu_enable(void)
{
    /* Enable PMCCNTR -- divide by 64 (DIVEN), then enable counter 31. */
    __asm__ volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(1u));   /* PMCR.E = 1 */
    __asm__ volatile("mcr p15, 0, %0, c9, c12, 1" :: "r"(1u<<31));/* PMCNTENSET */
}

/* VDMA S2MM_DMASR FrameStore field [28:24] indexes the current frame
 * being filled. We poll for transitions to count captured frames. */
#define VDMA_DMASR_ADDR    (0x43000000UL + 0x34u)
#define DMASR_FRAMESTORE   ((uint32_t)0x1F << 24)

static inline uint32_t vdma_frame_idx(void)
{
    uint32_t sr = *(volatile uint32_t *)VDMA_DMASR_ADDR;
    return (sr & DMASR_FRAMESTORE) >> 24;
}

static void uart_putu32(uint32_t v) { uart_putdec(v); }

/* Timeout: at 60 Hz a frame is ~16.7 ms = 5.5 Mcyc @ 333 MHz. Bail out
 * if FrameStore hasn't advanced after 10× that. Saves the bench from
 * hanging forever when CIRCULAR_PARK is misconfigured or VDMA stalls. */
#define BENCH_TIMEOUT_CYC   (55u * 1000u * 1000u)

static void bench_one_trial(uint32_t trial_n)
{
    uint32_t prev = vdma_frame_idx();
    uint32_t captured = 0;
    uint32_t t0       = pmccntr_read();
    uint32_t last_t   = t0;

    while (captured < FRAMES_PER_TRIAL) {
        uint32_t cur = vdma_frame_idx();
        if (cur != prev) {
            captured++;
            prev    = cur;
            last_t  = pmccntr_read();
        } else if ((pmccntr_read() - last_t) > BENCH_TIMEOUT_CYC) {
            /* FrameStore hasn't ticked in too long — abort this trial. */
            uart_puts("[bench] trial="); uart_putu32(trial_n);
            uart_puts("  ABORT: FrameStore stalled  prev=");
            uart_puthex(prev);
            uart_puts("  DMASR=");
            uart_puthex(*(volatile uint32_t *)VDMA_DMASR_ADDR);
            uart_puts("  captured=");
            uart_putu32(captured);
            uart_puts("\n");
            return;
        }
    }
    uint32_t t1 = pmccntr_read();

    /* PMCCNTR ticks at half the CPU clock (666 MHz / 2 = 333 MHz) when
     * DIVEN=0; we left it at default so ticks = 333 Mcyc/s. */
    uint32_t elapsed = t1 - t0;
    uint32_t ms      = (uint32_t)((uint64_t)elapsed / 333000u);
    uint32_t fps_x100 = ms ? (FRAMES_PER_TRIAL * 100000u) / ms : 0;
    uint32_t bytes   = FRAMES_PER_TRIAL * 921600u;
    uint32_t kbps    = ms ? (bytes / ms) : 0;     /* ≈ KB/s */

    uart_puts("[bench] trial="); uart_putu32(trial_n);
    uart_puts("  frames=");     uart_putu32(FRAMES_PER_TRIAL);
    uart_puts("  elapsed_ms="); uart_putu32(ms);
    uart_puts("  FPS*100=");    uart_putu32(fps_x100);
    uart_puts("  KBps=");       uart_putu32(kbps);
    uart_puts("\n");
}

int main(void)
{
    uart_init();
    uart_puts("\n========================================\n");
    uart_puts("  VDMA capture-path benchmark (v_tpg)\n");
    uart_puts("========================================\n");

    pmu_enable();

    uart_puts("[init] VDMA + color_convert + pixel_pack...\n");
    hdmi_in_init();
    hdmi_in_color_convert_ycbcr2rgb();
    vtpg_axis_switch_route(AXIS_SWITCH_SRC_VTPG);
    vtpg_start(640, 480, VTPG_PATTERN_COLOR_BARS);

    /* Allow a couple of frames to land before we start counting. */
    for (volatile int i = 0; i < 50 * 12000; i++) ;

    uart_puts("[bench] warm-up done; starting trials.\n");
    for (uint32_t i = 0; i < NUM_TRIALS; i++) bench_one_trial(i);

    uart_puts("[done ] bench complete. PMCCNTR @333 MHz; KBps ≈ KiB/s.\n");
    while (1) ;
}
