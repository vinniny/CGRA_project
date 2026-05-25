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
#include "uart.h"

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
#define DMACR_CIRC_PARK_BIT     (1u << 1)   /* 1 = cycle through 3-frame ring */

#define DMASR_HALTED_BIT        (1u << 0)
#define DMASR_FRMSTORE_MASK     (0x1Fu << 24)
#define DMASR_FRMSTORE_SHIFT    24

/* ── VTC detector register offsets (Xilinx v_tc PG016) ───────────────── */
/* Offsets + bit masks pulled verbatim from Xilinx vtc_v8_7 driver:
 *   /tools/Xilinx/2025.1/data/embeddedsw/.../vtc_v8_7/src/xvtc_hw.h
 * Trust the source — don't guess. */
#define VTC_CTL                 0x000u  /* XVTC_CTL_OFFSET — Control (RW)   */
#define VTC_STAT                0x004u  /* XVTC_ISR_OFFSET — Status (RO)    */
#define VTC_ERROR               0x08u

/* V_TC CTL bit masks from xvtc_hw.h v8_7 (XVTC_CTL_*_MASK):
 *   bit 31 = SW_RESET  (XVTC_CTL_RESET_MASK   = 0x80000000)
 *   bit 30 = SRST      (frame-sync'd reset)
 *   bit  5 = SE        (sync-with-detector,   = 0x20)
 *   bit  3 = DE        (XVTC_CTL_DE_MASK      = 0x08, Detector Enable)
 *   bit  2 = GE        (XVTC_CTL_GE_MASK      = 0x04, Generator Enable)
 * ISR (offset 0x04) status bits (XVTC_STAT_*_MASK):
 *   bit  0 = LOCKED    (XVTC_STAT_LOCKED_MASK = 0x01)  */
#define VTC_CTL_DET_EN          0x00000008u   /* XVTC_CTL_DE_MASK   */
#define VTC_CTL_REG_UPDATE      0x00000000u   /* not needed for detect-only */
#define VTC_STAT_LOCK_BIT       0x00000001u   /* XVTC_STAT_LOCKED_MASK */

/* ── Color-convert (HLS) — register layout from xcolor_convert_hw.h ───
 * Coefficient format: ap_fixed<10,2,AP_RND,AP_SAT>. 1.0 = 0x100.
 * Bias  format:        ap_fixed<10,2> applied AFTER matrix mul.
 * Matrix is applied as: out = M·in + bias (per row).                  */
#define CC_C1_C1                0x10u
#define CC_C1_C2                0x18u
#define CC_C1_C3                0x20u
#define CC_C2_C1                0x28u
#define CC_C2_C2                0x30u
#define CC_C2_C3                0x38u
#define CC_C3_C1                0x40u
#define CC_C3_C2                0x48u
#define CC_C3_C3                0x50u
#define CC_BIAS_C1              0x58u
#define CC_BIAS_C2              0x60u
#define CC_BIAS_C3              0x68u
#define CC_COEFF_ONE            0x100u
#define CC_COEFF_ZERO           0x000u
/* YCbCr-444 (full-range BT.601) → RGB. Used when v_tpg or a 4:4:4 HDMI
 * source feeds the chain. Reset to identity (CC_COEFF_ONE on the
 * diagonal, zero biases) when the source is already RGB.
 *
 *   R = 1.000·Y + 0.000·Cb + 1.402·Cr − 0.701
 *   G = 1.000·Y − 0.344·Cb − 0.714·Cr + 0.529
 *   B = 1.000·Y + 1.772·Cb + 0.000·Cr − 0.886            */
#define CC_YCBCR2RGB_C1_C1      0x100u  /*  1.000 */
#define CC_YCBCR2RGB_C1_C2      0x000u  /*  0.000 */
#define CC_YCBCR2RGB_C1_C3      0x167u  /*  1.402 */
#define CC_YCBCR2RGB_C2_C1      0x100u  /*  1.000 */
#define CC_YCBCR2RGB_C2_C2      0x3A8u  /* -0.344 (10-bit 2c) */
#define CC_YCBCR2RGB_C2_C3      0x349u  /* -0.714 */
#define CC_YCBCR2RGB_C3_C1      0x100u  /*  1.000 */
#define CC_YCBCR2RGB_C3_C2      0x1C6u  /*  1.772 */
#define CC_YCBCR2RGB_C3_C3      0x000u  /*  0.000 */
#define CC_YCBCR2RGB_BIAS_C1    0x34Du  /* -0.701 */
#define CC_YCBCR2RGB_BIAS_C2    0x087u  /* +0.529 */
#define CC_YCBCR2RGB_BIAS_C3    0x31Du  /* -0.886 */

/* YCbCr-444 (full-range BT.709) → RGB. BT.709 is the HD-video colour
 * space — laptops/HDMI sources typically use it for ≥720p. Use this
 * helper when sourcing real HDMI; use BT.601 for v_tpg / SD content.
 *
 *   R = 1.000·Y + 0.000·Cb + 1.575·Cr − 0.7875
 *   G = 1.000·Y − 0.187·Cb − 0.468·Cr + 0.3275
 *   B = 1.000·Y + 1.856·Cb + 0.000·Cr − 0.928               */
#define CC_YCBCR2RGB709_C1_C3   0x192u  /*  1.575 (round 1.575*256=403) */
#define CC_YCBCR2RGB709_C2_C2   0x3D0u  /* -0.187 (round -48 → 10b 2c = 0x3D0) */
#define CC_YCBCR2RGB709_C2_C3   0x382u  /* -0.468 (round -120 → 0x382) */
#define CC_YCBCR2RGB709_C3_C2   0x1DBu  /*  1.856 (round 1.856*256=475) */
#define CC_YCBCR2RGB709_BIAS_C1 0x33Bu  /* -0.7875 (round -202 → 0x33B) */
#define CC_YCBCR2RGB709_BIAS_C2 0x054u  /* +0.3275 (round  +84 → 0x054) */
#define CC_YCBCR2RGB709_BIAS_C3 0x308u  /* -0.928   (round -238 → 0x308) */

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
    uart_puts(" [init.S1] HDMI-IN VDMA halt+reset (dedicated, no shared state)\n");
    /* 1. Hard reset the HDMI-IN VDMA. With the split-VDMA bitstream
     * (cgra_split_vdma.bit) this resets ONLY the HDMI-IN side; HDMI-OUT
     * VDMA at 0x43000000 is untouched. On the legacy shared-VDMA
     * bitstreams the reset still affects both, but the caller orders
     * hdmi_init() to run before hdmi_in_init() so HDMI-OUT comes up
     * after the disturbance. */
    mmio_w(VDMA_IN_BASE + S2MM_DMACR, 0u);                /* halt  */
    mmio_w(VDMA_IN_BASE + S2MM_DMACR, DMACR_RESET_BIT);   /* reset */
    for (int t = 0; t < 100; t++) {
        if ((mmio_r(VDMA_IN_BASE + S2MM_DMACR) & DMACR_RESET_BIT) == 0u) break;
        delay_us(1);
    }

    uart_puts(" [init.S2] color_convert + pixel_pack\n");
    /* 2. Identity 3x3 colour matrix (input RGB pass-through). The working
     *    cgra_pynq_base BD has color_convert at 0x43C5_0000 — these writes
     *    were restored when we switched to the working bitstream's address
     *    map. PYNQ Python overlay uses the same offsets. */
    mmio_w(CCONV_IN_BASE + CC_C1_C1, CC_COEFF_ONE);
    mmio_w(CCONV_IN_BASE + CC_C1_C2, CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C1_C3, CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C2_C1, CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C2_C2, CC_COEFF_ONE);
    mmio_w(CCONV_IN_BASE + CC_C2_C3, CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C3_C1, CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C3_C2, CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C3_C3, CC_COEFF_ONE);

    /* Pixel-pack: V_24 mode (3 bytes per pixel). */
    mmio_w(PIXPACK_IN_BASE + PIXPACK_MODE, PIXPACK_MODE_V24);

    uart_puts(" [init.S3] VTC detector enable (gated until HDMI plugged)\n");
    /* V_TC's AXI-Lite is clocked by dvi2rgb_0/PixelClk (the recovered HDMI
     * pixel clock). Without a TMDS signal that clock doesn't toggle, so a
     * blind write here stalls the AXI bus. Skip the write until SW knows
     * the cable is in (call hdmi_in_enable_vtc() externally). For bring-up
     * without real HDMI, the VDMA capture path still validates end-to-end
     * via DDR-injected test patterns (XSDB mwr) — VDMA only consumes AXIS
     * valids, which gate on dvi2rgb. */

    uart_puts(" [init.S5] S2MM config\n");
    /* 5. Configure the S2MM channel.
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

    /* RS=1, CIRCULAR_PARK=1, frame counter disabled → free-running 3-frame
     * ring. Without CIRC_PARK, VDMA stays parked on whatever frame
     * PARK_PTR indexes (default 0) and FrameStore in DMASR never
     * advances -- silicon-confirmed 2026-05-25. */
    mmio_w(VDMA_IN_BASE + S2MM_DMACR,
           DMACR_RS_BIT | DMACR_CIRC_PARK_BIT);

    mmio_w(VDMA_IN_BASE + S2MM_FRMDLY_STRIDE, HDMI_IN_ROW_STRIDE);   /* 1920 */
    mmio_w(VDMA_IN_BASE + S2MM_HSIZE,         HDMI_IN_ROW_STRIDE);   /* 1920 */
    mmio_w(VDMA_IN_BASE + S2MM_VSIZE,         HDMI_IN_H);            /* 480 — LAST */

    uart_puts(" [init.S6] FB pointers + done\n");
    /* Cache the FB pointers in driver state. */
    g_fb[0] = (volatile uint8_t *)HDMI_IN_FB0;
    g_fb[1] = (volatile uint8_t *)HDMI_IN_FB1;
    g_fb[2] = (volatile uint8_t *)HDMI_IN_FB2;
    g_initialised = 1;
}

int hdmi_in_locked(void)
{
    if (!g_initialised) return 0;
    /* v_tc detector lock bit. Reads from VTC also touch the PixelClk-gated
     * AXI slave; same caveat as hdmi_in_init step 3 — only call this when
     * the HDMI cable is known to be plugged in and dvi2rgb has locked. */
    return (mmio_r(VTC_IN_BASE + VTC_STAT) & VTC_STAT_LOCK_BIT) ? 1 : 0;
}

void hdmi_in_enable_vtc(void)
{
    /* External enable hook — call AFTER the HDMI cable is plugged in.
     * Writes the Detector Enable bit per XVtc_EnableDetector() in
     * xvtc.c v8_7. Safe to call once dvi2rgb has a stable PixelClk. */
    mmio_w(VTC_IN_BASE + VTC_CTL, VTC_CTL_DET_EN);
}

void hdmi_in_color_convert_ycbcr2rgb(void)
{
    mmio_w(CCONV_IN_BASE + CC_C1_C1,   CC_YCBCR2RGB_C1_C1);
    mmio_w(CCONV_IN_BASE + CC_C1_C2,   CC_YCBCR2RGB_C1_C2);
    mmio_w(CCONV_IN_BASE + CC_C1_C3,   CC_YCBCR2RGB_C1_C3);
    mmio_w(CCONV_IN_BASE + CC_C2_C1,   CC_YCBCR2RGB_C2_C1);
    mmio_w(CCONV_IN_BASE + CC_C2_C2,   CC_YCBCR2RGB_C2_C2);
    mmio_w(CCONV_IN_BASE + CC_C2_C3,   CC_YCBCR2RGB_C2_C3);
    mmio_w(CCONV_IN_BASE + CC_C3_C1,   CC_YCBCR2RGB_C3_C1);
    mmio_w(CCONV_IN_BASE + CC_C3_C2,   CC_YCBCR2RGB_C3_C2);
    mmio_w(CCONV_IN_BASE + CC_C3_C3,   CC_YCBCR2RGB_C3_C3);
    mmio_w(CCONV_IN_BASE + CC_BIAS_C1, CC_YCBCR2RGB_BIAS_C1);
    mmio_w(CCONV_IN_BASE + CC_BIAS_C2, CC_YCBCR2RGB_BIAS_C2);
    mmio_w(CCONV_IN_BASE + CC_BIAS_C3, CC_YCBCR2RGB_BIAS_C3);
}

void hdmi_in_color_convert_identity(void)
{
    mmio_w(CCONV_IN_BASE + CC_C1_C1,   CC_COEFF_ONE);
    mmio_w(CCONV_IN_BASE + CC_C1_C2,   CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C1_C3,   CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C2_C1,   CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C2_C2,   CC_COEFF_ONE);
    mmio_w(CCONV_IN_BASE + CC_C2_C3,   CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C3_C1,   CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C3_C2,   CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C3_C3,   CC_COEFF_ONE);
    mmio_w(CCONV_IN_BASE + CC_BIAS_C1, 0);
    mmio_w(CCONV_IN_BASE + CC_BIAS_C2, 0);
    mmio_w(CCONV_IN_BASE + CC_BIAS_C3, 0);
}

void hdmi_in_assert_hpd(void)
{
    /* Xilinx axi_gpio standard register map:
     *   0x00  GPIO_DATA   (channel 1 data, R/W)
     *   0x04  GPIO_TRI    (channel 1 tri-state, 0=output 1=input)
     * HDMI-in HPD is on channel 1 bit 0. Drive output mode + level high. */
    const uint32_t GPIO_DATA = 0x00u;
    const uint32_t GPIO_TRI  = 0x04u;
    mmio_w(GPIO_HDMIIN_BASE + GPIO_TRI,  0x00u);   /* bit 0 = output */
    mmio_w(GPIO_HDMIIN_BASE + GPIO_DATA, 0x01u);   /* HPD = 1 (asserted) */
}

void hdmi_in_color_convert_ycbcr2rgb_bt709(void)
{
    /* Row 1 (R): same constant col 1 (Y→R coeff = 1.0) as BT.601,
     *            col 2 (Cb→R) is 0,  col 3 (Cr→R) differs. */
    mmio_w(CCONV_IN_BASE + CC_C1_C1,   CC_COEFF_ONE);
    mmio_w(CCONV_IN_BASE + CC_C1_C2,   CC_COEFF_ZERO);
    mmio_w(CCONV_IN_BASE + CC_C1_C3,   CC_YCBCR2RGB709_C1_C3);
    /* Row 2 (G): Y→G = 1.0, Cb and Cr coeffs differ. */
    mmio_w(CCONV_IN_BASE + CC_C2_C1,   CC_COEFF_ONE);
    mmio_w(CCONV_IN_BASE + CC_C2_C2,   CC_YCBCR2RGB709_C2_C2);
    mmio_w(CCONV_IN_BASE + CC_C2_C3,   CC_YCBCR2RGB709_C2_C3);
    /* Row 3 (B): Y→B = 1.0, Cb→B differs, Cr→B = 0. */
    mmio_w(CCONV_IN_BASE + CC_C3_C1,   CC_COEFF_ONE);
    mmio_w(CCONV_IN_BASE + CC_C3_C2,   CC_YCBCR2RGB709_C3_C2);
    mmio_w(CCONV_IN_BASE + CC_C3_C3,   CC_COEFF_ZERO);
    /* Biases. */
    mmio_w(CCONV_IN_BASE + CC_BIAS_C1, CC_YCBCR2RGB709_BIAS_C1);
    mmio_w(CCONV_IN_BASE + CC_BIAS_C2, CC_YCBCR2RGB709_BIAS_C2);
    mmio_w(CCONV_IN_BASE + CC_BIAS_C3, CC_YCBCR2RGB709_BIAS_C3);
}

int hdmi_in_frame_ready(void)
{
    /* Simple heuristic: VDMA is running and not halted. The caller polls
     * this and reads current_frame() at its own cadence — frame tearing
     * is acceptable for the slow-changing Paint-drawing input. */
    if (!g_initialised) return 0;
    return (mmio_r(VDMA_IN_BASE + S2MM_DMASR) & DMASR_HALTED_BIT) ? 0 : 1;
}

int hdmi_in_recover_if_halted(void)
{
    if (!g_initialised) return 0;
    const uint32_t sr = mmio_r(VDMA_IN_BASE + S2MM_DMASR);
    /* Any error bit OR Halted set → VDMA needs reset. Error bits per
     * PG020: bits 4-10 (DMAIntErr/DMASlvErr/DMADecErr/SOFEarly/EOLEarly/
     * SOFLate/EOLLate). Mask = 0x7F0. Plus bit 0 (Halted). */
    const uint32_t ERR_MASK = 0x7F0u;
    if ((sr & (ERR_MASK | DMASR_HALTED_BIT)) == 0u) return 0;

    /* Reset VDMA, wait for self-clear (per PG020 spec ≤ a few µs). */
    mmio_w(VDMA_IN_BASE + S2MM_DMACR, DMACR_RESET_BIT);
    for (int t = 0; t < 200; t++) {
        if ((mmio_r(VDMA_IN_BASE + S2MM_DMACR) & DMACR_RESET_BIT) == 0u) break;
        delay_us(1);
    }

    /* Re-program in the same order hdmi_in_init() does it. */
    mmio_w(VDMA_IN_BASE + S2MM_REG_INDEX,     0u);
    mmio_w(VDMA_IN_BASE + S2MM_START_ADDR_1,  HDMI_IN_FB0);
    mmio_w(VDMA_IN_BASE + S2MM_START_ADDR_2,  HDMI_IN_FB1);
    mmio_w(VDMA_IN_BASE + S2MM_START_ADDR_3,  HDMI_IN_FB2);
    mmio_w(VDMA_IN_BASE + S2MM_PARK_PTR,      0u);
    mmio_w(VDMA_IN_BASE + S2MM_DMACR,
           DMACR_RS_BIT | DMACR_CIRC_PARK_BIT);
    mmio_w(VDMA_IN_BASE + S2MM_FRMDLY_STRIDE, HDMI_IN_ROW_STRIDE);
    mmio_w(VDMA_IN_BASE + S2MM_HSIZE,         HDMI_IN_ROW_STRIDE);
    mmio_w(VDMA_IN_BASE + S2MM_VSIZE,         HDMI_IN_H);     /* kicks the run */
    return 1;
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
