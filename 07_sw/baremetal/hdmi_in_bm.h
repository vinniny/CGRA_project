/* =============================================================================
 * hdmi_in_bm.h — Bare-metal HDMI input driver for the PYNQ-Z2 J10 connector.
 *
 * Capture chain: dvi2rgb → v_tc_1 (detector) → v_axi4s_vid_in →
 *                color_convert_1 → pixel_pack_0 → axi_vdma_1 (S2MM) →
 *                DDR @ 0x1F80_0000.
 *
 * Resolution is fixed at 640×480 @ 60 Hz by an EDID payload baked into
 * dvi2rgb. The laptop will auto-negotiate to that mode when the cable
 * is plugged in.
 *
 * Pixel layout in DDR (BGR byte order, matches the existing HDMI-OUT
 * convention in hdmi_bm.c):
 *
 *    byte offset 0    byte offset 1    byte offset 2
 *    ┌────────────┐  ┌────────────┐  ┌────────────┐
 *    │   blue     │  │   green    │  │    red     │   <- pixel (0,0)
 *    └────────────┘  └────────────┘  └────────────┘
 *    byte offset 3    byte offset 4    byte offset 5
 *    ┌────────────┐  ┌────────────┐  ┌────────────┐
 *    │   blue     │  │   green    │  │    red     │   <- pixel (1,0)
 *    └────────────┘  └────────────┘  └────────────┘
 *    ...
 *
 * Row stride = 640 * 3 = 1920 bytes. No padding.
 *
 * Triple-buffer: VDMA cycles through 3 frames at 0x1F80_0000, 0x1FA0_0000,
 * 0x1FC0_0000. Driver returns a const ptr to the most-recently-completed
 * frame via hdmi_in_current_frame().
 * ============================================================================= */
#ifndef HDMI_IN_BM_H
#define HDMI_IN_BM_H

#include <stdint.h>

/* ── Frame geometry ───────────────────────────────────────────────────── */
/* Default is 1280x720 -- this is what Windows actually puts on the HDMI
 * wire when desktop is "800x600" or any sub-720p resolution (no EDID =>
 * Windows defaults to 720p signal mode, upscales the desktop into it).
 * Override at compile time:
 *   make CFLAGS_EXTRA='-DHDMI_IN_W=800 -DHDMI_IN_H=600' <target>           */
#ifndef HDMI_IN_W
#define HDMI_IN_W            1280u
#endif
#ifndef HDMI_IN_H
#define HDMI_IN_H            720u
#endif
#define HDMI_IN_BPP          3u
#define HDMI_IN_ROW_STRIDE   (HDMI_IN_W * HDMI_IN_BPP)             /* 3840 */
#define HDMI_IN_FRAME_BYTES  (HDMI_IN_ROW_STRIDE * HDMI_IN_H)      /* 2 764 800 */

/* ── Triple-buffer base addresses in DDR ──────────────────────────────── */
/* In the cgra_pynq_base working BD, the HDMI VDMA's address range is
 * 0x10000000 - 0x1FFFFFFF (256 MB window into DDR). Frames lock inside that.
 * Choose 3 frames in the lower part of that window. */
/* 4 MB stride per FB (each 1280x720x3 = 2.64 MB; rounded up). */
#define HDMI_IN_FB0          0x11000000UL
#define HDMI_IN_FB1          0x11400000UL
#define HDMI_IN_FB2          0x11800000UL

/* ── AXI-Lite register bases (cgra_pynq_base working BD) ─────────────────
 * The working BD has ONE axi_vdma at 0x43000000 that handles both MM2S
 * (HDMI-out) and S2MM (HDMI-in) — different register banks within the
 * same IP. Our S2MM channel uses offsets ≥ 0x30 inside the IP. */
/* HDMI-IN now has its OWN VDMA at 0x4302_0000 (per the split-VDMA
 * bitstream cgra_split_vdma.bit). The shared VDMA at 0x4300_0000 stays
 * MM2S-only for HDMI-OUT. To go back to the legacy shared-VDMA
 * bitstream, override at compile time: -DVDMA_IN_BASE=0x43000000UL */
#ifndef VDMA_IN_BASE
#define VDMA_IN_BASE         0x43020000UL  /* dedicated HDMI-IN VDMA */
#endif
#define VTC_IN_BASE          0x43C30000UL  /* video/hdmi_in/frontend/vtc_in */
#define PIXPACK_IN_BASE      0x43C40000UL  /* video/hdmi_in/pixel_pack    */
#define CCONV_IN_BASE        0x43C50000UL  /* video/hdmi_in/color_convert */
#define GPIO_HDMIIN_BASE     0x41220000UL  /* axi_gpio_hdmiin (HPD / CEC) */

/* ── Public API ───────────────────────────────────────────────────────── */

/**
 * Initialise the HDMI-input chain.
 *  - configures v_tc_1 in detector mode
 *  - programs color_convert_1 with identity RGB→RGB matrix
 *  - sets pixel_pack_0 mode = V_24 (24-bit packed)
 *  - resets and starts axi_vdma_1 in S2MM mode pointing at the 3-frame ring
 *
 * Idempotent — safe to call multiple times (e.g., after a soft reset).
 * The dvi2rgb IP is purely passive (no AXI-lite); it locks automatically
 * when a valid TMDS signal arrives on J10.
 */
void hdmi_in_init(void);

/**
 * @return  1 if VDMA reports a new completed frame since the last call,
 *          0 otherwise. Polled from the demo's main loop at ~30 Hz.
 */
int  hdmi_in_frame_ready(void);

/**
 * @return  const pointer into DDR3 to the most-recently-completed frame
 *          (640×480 BGR, 921 600 bytes). The buffer is stable until
 *          the next hdmi_in_frame_ready() call returns 1.
 */
const uint8_t *hdmi_in_current_frame(void);

/**
 * Read the v_tc_1 detector status register and return 1 if the IP has
 * locked to a valid input signal, 0 otherwise. Useful as a "is the cable
 * plugged in and is the laptop sending?" check.
 *
 * NOTE: V_TC's AXI-Lite is clocked by dvi2rgb's recovered PixelClk —
 * only safe to call AFTER hdmi_in_enable_vtc() and once HDMI is plugged.
 */
int  hdmi_in_locked(void);

/**
 * Enable the V_TC detector. Separate from hdmi_in_init() because the
 * VTC slave is pixel-clock gated — wait for an HDMI source to be present
 * before calling this.
 */
void hdmi_in_enable_vtc(void);

/**
 * Program color_convert with a YCbCr-444 → RGB (BT.601 full-range)
 * matrix. Call AFTER hdmi_in_init() when the upstream source emits
 * YCbCr (e.g. v_tpg's COLOR_BARS pattern, which is YCbCr-444 regardless
 * of the colorFormat register). Silicon-validated 2026-05-24 against
 * v_tpg SMPTE 100% bars → captured 8 cleanly-converted RGB bars.
 */
void hdmi_in_color_convert_ycbcr2rgb(void);

/**
 * Program color_convert with a 3×3 identity matrix and zero biases —
 * the default for an RGB-in, RGB-out path. Idempotent.
 */
void hdmi_in_color_convert_identity(void);

/**
 * BT.709 (HD-video) full-range YCbCr-444 → RGB matrix. Most HDMI
 * laptops/sources at ≥720p emit BT.709 rather than BT.601; call this
 * helper instead of _ycbcr2rgb() when the source is HD. SD-content
 * sources (and v_tpg's COLOR_BARS pattern) use BT.601.
 */
void hdmi_in_color_convert_ycbcr2rgb_bt709(void);

/**
 * Restart VDMA if it has halted on a SOFEarlyErr / DMADecErr / similar
 * sticky-error condition. Reads DMASR; if any error bit or the Halted
 * bit is set, issues DMACR.Reset, re-programs HSIZE/VSIZE/START_ADDR,
 * and re-asserts RS+CIRCULAR_PARK. Cheap to call every frame (~few µs);
 * returns 1 if a recovery was performed, 0 if VDMA was already healthy.
 */
int  hdmi_in_recover_if_halted(void);

/**
 * Drive the HDMI-in HPD (Hot-Plug Detect) line HIGH via the
 * axi_gpio_hdmiin IP at 0x4122_0000. Without this, the laptop / source
 * sees the board's HDMI-in as "no monitor connected" and refuses to
 * transmit — even though the cable is physically plugged in. Some
 * splitters also gate their downstream forwarding on HPD assertion.
 *
 * Call this once BEFORE programming color_convert / enabling VDMA so
 * the source has time to renegotiate and start streaming. Silicon-
 * confirmed missing-link 2026-05-25 (TVALID 0% on axis_switch.M00 ILA
 * until HPD asserted).
 */
void hdmi_in_assert_hpd(void);

/**
 * Halt the HDMI-IN S2MM VDMA (clear DMACR.RS). Frees HP0 bandwidth
 * for HDMI-OUT MM2S to read framebuffer pixels at clean 60Hz without
 * contention. Call this AFTER reading the current frame; the next
 * iteration's hdmi_in_recover_if_halted() will detect the halt and
 * re-arm for the next capture.
 *
 * Rationale (silicon-validated 2026-05-27): with the split-VDMA
 * bitstream, HDMI-IN S2MM @ 64-bit M_AXI and HDMI-OUT MM2S @ 32-bit
 * MM2S both share ps7_0/S_AXI_HP0 via axi_mem_intercon. At 1280x720
 * S2MM @ 60Hz the HP0 traffic from HDMI-IN can starve HDMI-OUT
 * MM2S reads, producing colour glitches and pixel right-shift on
 * the J11 monitor. Demoing without LIVE_INPUT (HDMI-IN VDMA never
 * runs) confirmed the OUT side is clean; this halt restores that
 * cleanliness while keeping live capture functional at ~one
 * frame-per-inference rate.
 */
void hdmi_in_halt(void);

#endif /* HDMI_IN_BM_H */
