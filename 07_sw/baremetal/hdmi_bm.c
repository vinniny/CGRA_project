/* hdmi_bm.c — see hdmi_bm.h. */

#include "hdmi_bm.h"
#include "uart.h"

#include <stdint.h>

/* MMIO base addresses (matches scripts/hdmi_first_light.sh + base.hwh). */
#define SLCR_BASE       0xF8000000UL
/* Address map for the CLEAN dual-HDMI BD (cgra_hdmi_dual.xsa), confirmed
 * from design_1.hwh 2026-06-01.  NOTE: this differs from the old CGRA_PYNQ
 * base — dynclk moved to 0x43C00000 (0x43C10000 is now the CGRA), and the
 * clean OUT pipeline has NO color_convert / pixel_unpack (vdma RGB ->
 * v_axi4s_vid_out -> rgb2dvi), so hls_configure() is not used. */
#define VDMA_BASE       0x43000000UL  /* axi_vdma_0  (HDMI-OUT MM2S)   */
#define DYNCLK_BASE     0x43C00000UL  /* axi_dynclk_0                  */
#define VTC_BASE        0x43C20000UL  /* v_tc_0      (HDMI-OUT)        */

/* Forward decl for cycle-counter delay. */
static void delay_us(uint32_t us);
uint32_t hdmi_measure_frame_cycles(void);

static inline void mmio_w(uint32_t addr, uint32_t val)
{
    *(volatile uint32_t *)(uintptr_t)addr = val;
    /* Memory barrier so writes hit MMIO in order. */
    asm volatile("dsb" ::: "memory");
}

static inline uint32_t mmio_r(uint32_t addr)
{
    return *(volatile uint32_t *)(uintptr_t)addr;
}

/* ARM Cortex-A9 cycle counter (PMU) — used for delay_us. uart.h's setup
 * doesn't enable it; we do it here on first call. */
static int ccnt_inited = 0;
static inline uint32_t ccnt_read(void)
{
    uint32_t v;
    asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(v));
    return v;
}
static void ccnt_init(void)
{
    /* Enable user-mode access to PMU (USEREN). */
    asm volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"(1));
    /* Enable all counters, reset cycle counter, reset event counters. */
    asm volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(7));
    /* Enable cycle counter (PMCNTENSET bit 31). */
    asm volatile("mcr p15, 0, %0, c9, c12, 1" :: "r"(0x80000000));
    ccnt_inited = 1;
}

static void delay_us(uint32_t us)
{
    if (!ccnt_inited) ccnt_init();
    /* 666 MHz CPU -> 666 cycles per us. */
    uint32_t target = ccnt_read() + us * 666u;
    while ((int32_t)(ccnt_read() - target) < 0) { /* spin */ }
}

/* ------------------ dynclk MMCM (Digilent axi_dynclk) ------------------ */
static int dynclk_program_25_175MHz(void)
{
    /* Values from scripts/hdmi_first_light.sh step 3.
     * REF=100 MHz, target=25.175 MHz; fbmult=34, clkdiv=9, maindiv=3. */
    mmio_w(DYNCLK_BASE       , 0x00000000u); /* CTRL: stop */
    mmio_w(DYNCLK_BASE + 0x08, 0x00800105u); /* CLK_O_REG */
    mmio_w(DYNCLK_BASE + 0x0C, 0x00000451u); /* CLK_FB_REG */
    mmio_w(DYNCLK_BASE + 0x10, 0x00000000u); /* CLK_FRAC */
    mmio_w(DYNCLK_BASE + 0x14, 0x00002042u); /* CLK_DIV */
    mmio_w(DYNCLK_BASE + 0x18, 0xD2CFA401u); /* CLK_LOCK */
    mmio_w(DYNCLK_BASE + 0x1C, 0x006300FFu); /* CLK_FLTR */
    mmio_w(DYNCLK_BASE       , 0x00000001u); /* CTRL: start */

    /* Poll STATUS bit 0 = lock, up to ~2 seconds. */
    for (int i = 0; i < 10; ++i) {
        if (mmio_r(DYNCLK_BASE + 0x04) & 1u) return 0;
        delay_us(200000);
    }
    return -1;
}

/* ------------------ VTC 640x480 timing generator ----------------------- */
static void vtc_program_640x480(void)
{
    /* Values from scripts/hdmi_first_light.sh step 5. */
    mmio_w(VTC_BASE + 0x60, 0x01E00280u); /* GASIZE  (480<<16)|640 */
    mmio_w(VTC_BASE + 0x68, 0x00000040u); /* GFENC PROG */
    mmio_w(VTC_BASE + 0x6C, 0x00000010u); /* GPOL AVP only */
    mmio_w(VTC_BASE + 0x70, 0x00000320u); /* GHSIZE 800 */
    mmio_w(VTC_BASE + 0x74, 0x0000020Du); /* GVSIZE 525 */
    mmio_w(VTC_BASE + 0x78, 0x02F00290u); /* GHSYNC pack(656,752) */
    mmio_w(VTC_BASE + 0x7C, 0x031F0280u); /* GVBHOFF pack(640,799) */
    mmio_w(VTC_BASE + 0x80, 0x01EC01EAu); /* GVSYNC pack(490,492) */
    mmio_w(VTC_BASE + 0x84, 0x02F00290u); /* GVSHOFF pack(656,752) */
    mmio_w(VTC_BASE + 0x140, 0x00000000u); /* GGD */
    mmio_w(VTC_BASE       , 0x0007FF03u);  /* CTL: ALLGENSRC|RU|SW */
    mmio_w(VTC_BASE       , 0x0007FF07u);  /* CTL: + GE (enable generator) */
}

/* ------------------ VDMA MM2S single-buffer (proven baseline) ---------- */
static void vdma_program_mm2s(uint32_t fb_phys)
{
    mmio_w(VDMA_BASE       , 0x00000004u); /* CR: RESET */
    delay_us(5000);
    mmio_w(VDMA_BASE + 0x18, 0x00000001u); /* FRMSTORE = 1 */
    mmio_w(VDMA_BASE + 0x28, 0x00000000u); /* PARK_PTR = 0 */
    mmio_w(VDMA_BASE       , 0x00000001u); /* CR: RUNSTOP */
    mmio_w(VDMA_BASE + 0x5C, fb_phys);     /* START_ADDR */
    mmio_w(VDMA_BASE + 0x58, 0x00000780u); /* STRD_FRMDLY = 1920 */
    mmio_w(VDMA_BASE + 0x54, 0x00000780u); /* HSIZE = 1920 */
    mmio_w(VDMA_BASE + 0x50, 0x000001E0u); /* VSIZE = 480 (write LAST) */
}

/* Force every HDMI IP into a known idle state before reconfiguration.
 * Needed because XSDB-driven ELF reloads don't power-cycle the PL — when
 * the previous ELF left VDMA/VTC running, the new hdmi_init() would
 * write the regs while a frame transfer was in flight, producing torn
 * or shifted output until the next board reset. */
static void hdmi_force_idle(void)
{
    /* VDMA MM2S: stop (RUNSTOP=0), then soft-reset (bit 2), wait. */
    mmio_w(VDMA_BASE, 0u);
    delay_us(1000);
    mmio_w(VDMA_BASE, 0x4u);        /* RESET */
    delay_us(5000);
    /* VTC generator: disable (CTL=0). Stops AXI-Stream output. */
    mmio_w(VTC_BASE, 0u);
    delay_us(1000);
    /* dynclk: stop the MMCM so the next program sequence sees a clean
     * de-asserted state. */
    mmio_w(DYNCLK_BASE, 0u);
    delay_us(1000);
}

int hdmi_init(void)
{
    /* NO FCLK0 override here.  The clean dual-HDMI BD clocks the whole
     * AXI-lite fabric (v_tc/vdma/dynclk/CGRA) from FCLK0=50 MHz and feeds
     * dynclk's MMCM reference from FCLK1=100 MHz — both already set
     * correctly by the Vivado-generated ps7_init.  The old SLCR 0x170
     * override (DIV0=10 off IO_PLL) assumed IO_PLL=1000 (crystal=33.333);
     * with the corrected crystal=50 it pushed FCLK0 to 160 MHz and wedged
     * the video-IP AXI bus.  Removed. */

    /* Quench any leftover state from a previous ELF run. */
    uart_puts("  hdmi: force_idle\n"); uart_drain();
    hdmi_force_idle();

    uart_puts("  hdmi: dynclk @0x43C00000\n"); uart_drain();
    int lk = dynclk_program_25_175MHz();
    uart_puts("    dynclk STATUS="); uart_puthex(mmio_r(DYNCLK_BASE + 0x04));
    uart_puts(" CTRL="); uart_puthex(mmio_r(DYNCLK_BASE)); uart_putchar('\n'); uart_drain();
    if (lk < 0) { uart_puts("  hdmi: dynclk NO LOCK\n"); uart_drain(); return -1; }
    uart_puts("  hdmi: vtc 640x480\n"); uart_drain();
    vtc_program_640x480();
    uart_puts("    vtc CTL="); uart_puthex(mmio_r(VTC_BASE));
    uart_puts(" STAT="); uart_puthex(mmio_r(VTC_BASE + 0x04)); uart_putchar('\n'); uart_drain();
    uart_puts("  hdmi: vdma mm2s\n"); uart_drain();
    vdma_program_mm2s(HDMI_FB_PHYS);
    uart_puts("    vdma DMASR="); uart_puthex(mmio_r(VDMA_BASE + 0x04));
    uart_puts(" DMACR="); uart_puthex(mmio_r(VDMA_BASE)); uart_putchar('\n'); uart_drain();
    uart_puts("  hdmi: measuring frame rate...\n"); uart_drain();
    uint32_t fc = hdmi_measure_frame_cycles();
    uart_puts("    frame_cyc="); uart_puthex(fc);
    uart_puts("  (60fps@666MHz ~= 0x00A98AC0)\n"); uart_drain();
    uart_puts("  hdmi: out path up\n"); uart_drain();
    return 0;
}

/* Live HDMI-OUT VDMA MM2S status (DMASR @ +0x04) for runtime diagnostics. */
uint32_t hdmi_out_dmasr(void) { return mmio_r(VDMA_BASE + 0x04); }

/* Measure CPU cycles per displayed frame by timing VDMA MM2S FrmCntIrq edges.
 * In genlock/parked mode the VDMA completes one frame per downstream vsync, so
 * the edge rate == display frame rate == pixel-clock-determined.  Returns avg
 * CPU cycles between frame completions over N frames, or 0 on timeout (frames
 * never completing -> downstream not consuming).  Compare to APU_HZ/60. */
uint32_t hdmi_measure_frame_cycles(void)
{
    if (!ccnt_inited) ccnt_init();
    /* DMACR: keep RS(bit0), set FrmCntIrqEn(bit12) + IRQFrameCount=1(bits15:8). */
    uint32_t cr = mmio_r(VDMA_BASE);
    mmio_w(VDMA_BASE, (cr & ~0x0000FF00u) | (1u << 12) | (1u << 8));
    const uint32_t TO = 200000000u;            /* ~0.3 s @ 666 MHz watchdog */
    mmio_w(VDMA_BASE + 0x04, 0x00001000u);     /* W1C FrmCntIrq */
    uint32_t g = ccnt_read();
    while (!(mmio_r(VDMA_BASE + 0x04) & 0x1000u)) if (ccnt_read() - g > TO) return 0;
    mmio_w(VDMA_BASE + 0x04, 0x00001000u);
    uint32_t t0 = ccnt_read();
    const int N = 10;
    for (int i = 0; i < N; ++i) {
        uint32_t s = ccnt_read();
        while (!(mmio_r(VDMA_BASE + 0x04) & 0x1000u)) if (ccnt_read() - s > TO) return 0;
        mmio_w(VDMA_BASE + 0x04, 0x00001000u);
    }
    return (ccnt_read() - t0) / (uint32_t)N;
}

/* ----- pixel ops ------------------------------------------------------- */
void hdmi_rect(int x, int y, int w, int h, uint32_t rgb)
{
    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            hdmi_pixel(x + col, y + row, rgb);
        }
    }
}

void hdmi_clear(uint32_t rgb)
{
    hdmi_rect(0, 0, HDMI_FB_W, HDMI_FB_H, rgb);
}

/* Without the Vitis BSP linked in, we don't have Xil_DCacheFlushRange.
 * The bare-metal start.s leaves caches OFF after reset, so writes through
 * volatile pointers go straight to DDR. If caches are later enabled in
 * the project, replace this with a real flush call. */
void hdmi_flush_fb(void)
{
    asm volatile("dsb" ::: "memory");
}
