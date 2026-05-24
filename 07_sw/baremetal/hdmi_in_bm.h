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
#define HDMI_IN_W            640u
#define HDMI_IN_H            480u
#define HDMI_IN_BPP          3u
#define HDMI_IN_ROW_STRIDE   (HDMI_IN_W * HDMI_IN_BPP)             /* 1920 */
#define HDMI_IN_FRAME_BYTES  (HDMI_IN_ROW_STRIDE * HDMI_IN_H)      /* 921 600 */

/* ── Triple-buffer base addresses in DDR ──────────────────────────────── */
#define HDMI_IN_FB0          0x1F800000UL
#define HDMI_IN_FB1          0x1FA00000UL
#define HDMI_IN_FB2          0x1FC00000UL

/* ── AXI-Lite register bases (matches add_hdmi_in_pynqz2.tcl assignment) ── */
#define VDMA_IN_BASE         0x43020000UL  /* axi_vdma_1 */
#define VTC_IN_BASE          0x43C90000UL  /* v_tc_1     */
/* color_convert_1 and pixel_pack_0 were originally planned but the BD now
 * uses axis_subset_converter_in (config-time-only, no AXI-Lite slave). The
 * driver no longer writes to these bases; left here for archival reference. */
/* #define CCONV_IN_BASE     0x43CA0000UL */
/* #define PIXPACK_IN_BASE   0x43CB0000UL */

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
 */
int  hdmi_in_locked(void);

#endif /* HDMI_IN_BM_H */
