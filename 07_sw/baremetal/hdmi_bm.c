/* hdmi_bm.c — see hdmi_bm.h. */

#include "hdmi_bm.h"

#include <stdint.h>

/* MMIO base addresses (matches scripts/hdmi_first_light.sh + base.hwh). */
#define SLCR_BASE       0xF8000000UL
#define VDMA_BASE       0x43000000UL
#define DYNCLK_BASE     0x43C10000UL
#define VTC_BASE        0x43C20000UL
#define CC_OUT_BASE     0x43C60000UL  /* hdmi_out/color_convert */
#define PU_OUT_BASE     0x43C70000UL  /* hdmi_out/pixel_unpack */

/* Forward decl for cycle-counter delay. */
static void delay_us(uint32_t us);

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

/* ------------------ color_convert identity + pixel_unpack V_24 --------- */
static void hls_configure(void)
{
    /* color_convert: identity 3x3 matrix in ap_fixed<10,2> (1.0 = 0x100). */
    mmio_w(CC_OUT_BASE + 0x10, 0x100u); /* c1_c1 */
    mmio_w(CC_OUT_BASE + 0x18, 0x000u); /* c1_c2 */
    mmio_w(CC_OUT_BASE + 0x20, 0x000u); /* c1_c3 */
    mmio_w(CC_OUT_BASE + 0x28, 0x000u); /* c2_c1 */
    mmio_w(CC_OUT_BASE + 0x30, 0x100u); /* c2_c2 */
    mmio_w(CC_OUT_BASE + 0x38, 0x000u); /* c2_c3 */
    mmio_w(CC_OUT_BASE + 0x40, 0x000u); /* c3_c1 */
    mmio_w(CC_OUT_BASE + 0x48, 0x000u); /* c3_c2 */
    mmio_w(CC_OUT_BASE + 0x50, 0x100u); /* c3_c3 */
    mmio_w(CC_OUT_BASE + 0x58, 0x000u); /* bias_c1 */
    mmio_w(CC_OUT_BASE + 0x60, 0x000u); /* bias_c2 */
    mmio_w(CC_OUT_BASE + 0x68, 0x000u); /* bias_c3 */

    /* pixel_unpack: mode = 0 (V_24 = 3 bytes/pixel packed in DDR). */
    mmio_w(PU_OUT_BASE + 0x10, 0x0u);
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
    /* In bare-metal we control SLCR directly. ps7_init.tcl set FCLK0 to
     * some value; we override to 100 MHz here so dynclk's MMCM sees the
     * reference it was synthesised for. */
    mmio_w(SLCR_BASE + 0x008, 0x0000DF0Du); /* SLCR_UNLOCK */
    mmio_w(SLCR_BASE + 0x170, 0x00100A00u); /* FPGA0_CLK_CTRL: DIV0=10,DIV1=1,IO_PLL */
    mmio_w(SLCR_BASE + 0x004, 0x0000767Bu); /* SLCR_LOCK */

    /* Quench any leftover state from a previous ELF run. Without this,
     * ELF reloads via XSDB cause HDMI tearing/misalignment until SRST. */
    hdmi_force_idle();

    if (dynclk_program_25_175MHz() < 0) return -1;
    hls_configure();
    vtc_program_640x480();
    vdma_program_mm2s(HDMI_FB_PHYS);
    return 0;
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
