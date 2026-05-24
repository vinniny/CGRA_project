/* =============================================================================
 * hdmi_in_bm.c — Bare-metal HDMI input driver implementation.
 *
 * See hdmi_in_bm.h for the API contract and signal-flow overview.
 *
 * Register layout matches the AXI VDMA Lite product guide (PG020) plus the
 * sub-IPs added by scripts/add_hdmi_in_pynqz2.tcl:
 *   axi_vdma_1   @ VDMA_IN_BASE   — S2MM mode, 3-frame ring at 0x1F[8AC]0_0000
 *   v_tc_1       @ VTC_IN_BASE    — detector mode, no generator
 *   color_convert_1 @ CCONV_IN_BASE — identity RGB→RGB pass-through
 *   pixel_pack_0 @ PIXPACK_IN_BASE — mode 0 = V_24 (24-bit packed)
 *   dvi2rgb_0    — purely passive, no AXI-Lite; auto-locks on TMDS arrival
 * ============================================================================= */
#include "hdmi_in_bm.h"

/* ── MMIO helpers (matches hdmi_bm.c style) ───────────────────────────── */
static inline void mmio_w(uint32_t addr, uint32_t val)
{
    *(volatile uint32_t *)(uintptr_t)addr = val;
    asm volatile("dsb" ::: "memory");
}

static inline uint32_t mmio_r(uint32_t addr)
{
    return *(volatile uint32_t *)(uintptr_t)addr;
}

/* ── PMU-cycle delay (mirrored from hdmi_bm.c so we don't have to expose
 *    delay_us from there). 50 MHz fabric => 50 cycles per us is a coarse
 *    over-estimate for an ARM Cortex-A9 running at 666 MHz, so we use the
 *    CPU cycle counter (PMCCNTR) for accuracy. ─────────────────────────── */
static uint32_t pmu_cycles_per_us = 333u;  /* 666 MHz / 2 (PMCCNTR divides by 2) */

static inline uint32_t pmccntr_read(void)
{
    uint32_t c;
    asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(c));
    return c;
}

static void delay_us(uint32_t us)
{
    const uint32_t target = us * pmu_cycles_per_us;
    const uint32_t start  = pmccntr_read();
    while ((pmccntr_read() - start) < target) { /* spin */ }
}

/* ── VDMA S2MM register offsets (PG020 §6) ───────────────────────────── */
#define S2MM_DMACR              0x30u
#define S2MM_DMASR              0x34u
#define S2MM_REG_INDEX          0x38u
#define S2MM_VSIZE              0xA0u
#define S2MM_HSIZE              0xA4u
#define S2MM_FRMDLY_STRIDE      0xA8u
#define S2MM_START_ADDR_1       0xACu
#define S2MM_START_ADDR_2       0xB0u
#define S2MM_START_ADDR_3       0xB4u
#define S2MM_PARK_PTR           0x28u

#define DMACR_RS_BIT            (1u << 0)
#define DMACR_RESET_BIT         (1u << 2)
#define DMACR_GENLOCK_SRC_BIT   (1u << 7)   /* 1 = source — internal */
#define DMACR_FRMCNT_EN_BIT     (1u << 4)   /* 0 = free-run (we want this) */

#define DMASR_HALTED_BIT        (1u << 0)
#define DMASR_FRMSTORE_MASK     (0x1Fu << 24)
#define DMASR_FRMSTORE_SHIFT    24

/* ── VTC detector register offsets (Xilinx v_tc PG016) ───────────────── */
#define VTC_CTL                 0x00u
#define VTC_STAT                0x04u
#define VTC_ERROR               0x08u

#define VTC_CTL_DET_EN          (1u << 0)
#define VTC_CTL_REG_UPDATE      (1u << 1)
#define VTC_STAT_LOCK_BIT       (1u << 8)

/* ── Color-convert (HLS) — identity 3x3 matrix offsets (PG284) ──────── */
#define CC_C1_C1                0x10u
#define CC_C1_C2                0x18u
#define CC_C1_C3                0x20u
#define CC_C2_C1                0x28u
#define CC_C2_C2                0x30u
#define CC_C2_C3                0x38u
#define CC_C3_C1                0x40u
#define CC_C3_C2                0x48u
#define CC_C3_C3                0x50u
/* Coefficient format: ap_fixed<10,2,AP_RND,AP_SAT>. 1.0 = 0x100, 0.0 = 0x000. */
#define CC_COEFF_ONE            0x100u
#define CC_COEFF_ZERO           0x000u

/* ── Pixel-pack: mode register ───────────────────────────────────────── */
#define PIXPACK_MODE            0x10u
#define PIXPACK_MODE_V24        0u  /* 3-byte BGR */

/* ── Driver state ────────────────────────────────────────────────────── */
static volatile uint8_t *g_fb[3];
static int               g_initialised;

/* ============================================================ */
/* Public API                                                   */
/* ============================================================ */

void hdmi_in_init(void)
{
    /* 1. Hard-stop and reset the S2MM channel of axi_vdma_1. */
    mmio_w(VDMA_IN_BASE + S2MM_DMACR, 0u);                /* halt   */
    mmio_w(VDMA_IN_BASE + S2MM_DMACR, DMACR_RESET_BIT);   /* reset  */
    /* Spin until the reset bit self-clears (max 100 us). */
    for (int t = 0; t < 100; t++) {
        if ((mmio_r(VDMA_IN_BASE + S2MM_DMACR) & DMACR_RESET_BIT) == 0u) break;
        delay_us(1);
    }

    /* 2. Color-convert and pixel-pack IPs were removed from the BD in the
     *    final scripts/add_hdmi_in_pynqz2.tcl — replaced with
     *    axis_subset_converter_in (config-time-only, no AXI-Lite slave;
     *    24->32 byte-pad is fixed at synth). The previous writes to
     *    CCONV_IN_BASE / PIXPACK_IN_BASE targeted non-existent AXI-Lite
     *    slaves and would have stalled on AXI decode timeout. Removed. */

    /* 3. VTC detector: enable. The IP measures hsync/vsync from the
     *    recovered pixel clock. dvi2rgb has no AXI-Lite — it locks
     *    automatically the moment a valid TMDS signal arrives at J10. */
    mmio_w(VTC_IN_BASE + VTC_CTL, VTC_CTL_DET_EN | VTC_CTL_REG_UPDATE);

    /* 4. Configure the S2MM channel.
     *    a) primary register bank (REG_INDEX = 0)
     *    b) three frame-store base addresses
     *    c) PARK_PTR = 0 to round-robin all three
     *    d) start running
     *    e) program HSIZE / STRIDE
     *    f) program VSIZE last — this is what kicks the transfer */
    mmio_w(VDMA_IN_BASE + S2MM_REG_INDEX,     0u);
    mmio_w(VDMA_IN_BASE + S2MM_START_ADDR_1,  HDMI_IN_FB0);
    mmio_w(VDMA_IN_BASE + S2MM_START_ADDR_2,  HDMI_IN_FB1);
    mmio_w(VDMA_IN_BASE + S2MM_START_ADDR_3,  HDMI_IN_FB2);
    mmio_w(VDMA_IN_BASE + S2MM_PARK_PTR,      0u);

    /* RS=1, frame counter disabled → free-running 3-frame ring. */
    mmio_w(VDMA_IN_BASE + S2MM_DMACR,         DMACR_RS_BIT);

    mmio_w(VDMA_IN_BASE + S2MM_FRMDLY_STRIDE, HDMI_IN_ROW_STRIDE);   /* 1920 */
    mmio_w(VDMA_IN_BASE + S2MM_HSIZE,         HDMI_IN_ROW_STRIDE);   /* 1920 */
    mmio_w(VDMA_IN_BASE + S2MM_VSIZE,         HDMI_IN_H);            /* 480 — LAST */

    /* Cache the FB pointers in driver state. */
    g_fb[0] = (volatile uint8_t *)HDMI_IN_FB0;
    g_fb[1] = (volatile uint8_t *)HDMI_IN_FB1;
    g_fb[2] = (volatile uint8_t *)HDMI_IN_FB2;
    g_initialised = 1;
}

int hdmi_in_locked(void)
{
    if (!g_initialised) return 0;
    /* v_tc detector lock bit. */
    return (mmio_r(VTC_IN_BASE + VTC_STAT) & VTC_STAT_LOCK_BIT) ? 1 : 0;
}

int hdmi_in_frame_ready(void)
{
    /* Simple heuristic: VDMA is running and not halted. The caller polls
     * this and reads current_frame() at its own cadence — frame tearing
     * is acceptable for the slow-changing Paint-drawing input. */
    if (!g_initialised) return 0;
    return (mmio_r(VDMA_IN_BASE + S2MM_DMASR) & DMASR_HALTED_BIT) ? 0 : 1;
}

const uint8_t *hdmi_in_current_frame(void)
{
    if (!g_initialised) return (const uint8_t *)HDMI_IN_FB0;

    /* DMASR[28:24] reports the frame store the VDMA is currently writing
     * to. Return the *previous* frame in the ring so the caller always
     * reads a stable, fully-captured buffer. */
    const uint32_t sr   = mmio_r(VDMA_IN_BASE + S2MM_DMASR);
    const uint32_t curr = (sr & DMASR_FRMSTORE_MASK) >> DMASR_FRMSTORE_SHIFT;
    const uint32_t prev = (curr == 0u) ? 2u : (curr - 1u);
    return (const uint8_t *)g_fb[prev];
}
