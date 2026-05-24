/* =============================================================================
 * vtpg.h — Bare-metal driver for the v_tpg + axis_switch IPs added in the
 *          Procedure-B (cgra_vtpg_test.bit) bitstream.
 *
 * Pipeline (Procedure B BD):
 *   J10 / dvi2rgb  ─┐
 *                   ├→ axis_switch_in (2→1) → color_convert → pixel_pack
 *   v_tpg (PL TPG) ─┘                                              → VDMA → DDR
 *
 * SW-selectable source via axis_switch's MI_MUX register:
 *   S00 = real HDMI    (dvi2rgb path)
 *   S01 = synthetic    (v_tpg)
 *
 * Register offsets pulled verbatim from the Vitis 2025.1 embeddedsw drivers:
 *   v_tpg_v8_6/src/xv_tpg_hw.h
 *   axis_switch_v1_7/src/xaxis_switch_hw.h
 * ============================================================================= */
#ifndef VTPG_H
#define VTPG_H

#include <stdint.h>

/* ── AXI-Lite base addresses (Procedure-B BD) ──────────────────────────── */
#define VTPG_BASE              0x43CC0000UL
#define AXIS_SWITCH_BASE       0x43CD0000UL

/* ── v_tpg v8.6 register map ───────────────────────────────────────────── */
#define VTPG_AP_CTRL           0x00     /* [0]=ap_start, [7]=auto_restart */
#define VTPG_AP_START          0x01u
#define VTPG_AUTO_RESTART      0x80u
#define VTPG_HEIGHT            0x10     /* rows  [15:0] */
#define VTPG_WIDTH             0x18     /* cols  [15:0] */
#define VTPG_BCKGND_ID         0x20     /* pattern id [7:0] */
#define VTPG_OVRLAY_ID         0x28     /* overlay  id [7:0] (0=none) */
#define VTPG_MOTION_SPEED      0x38     /* 0 = static */
#define VTPG_COLOR_FORMAT      0x40     /* 0=YUV422 1=YUV444 2=RGB 3=YUV420 */
#define VTPG_ENABLE_INPUT      0x98     /* 0 = ignore pass-through stream */

/* Pattern IDs (v_tpg v8.x) */
#define VTPG_PATTERN_PASSTHRU      0x00
#define VTPG_PATTERN_H_RAMP        0x01
#define VTPG_PATTERN_V_RAMP        0x02
#define VTPG_PATTERN_TEMPORAL_RAMP 0x03
#define VTPG_PATTERN_SOLID_RED     0x04
#define VTPG_PATTERN_SOLID_GREEN   0x05
#define VTPG_PATTERN_SOLID_BLUE    0x06
#define VTPG_PATTERN_SOLID_BLACK   0x07
#define VTPG_PATTERN_SOLID_WHITE   0x08
#define VTPG_PATTERN_COLOR_BARS    0x09
#define VTPG_PATTERN_ZONE_PLATE    0x0A
#define VTPG_PATTERN_TARTAN_BARS   0x0B
#define VTPG_PATTERN_CROSS_HATCH   0x0C
#define VTPG_PATTERN_CHECKER       0x0E

/* Color format */
#define VTPG_FORMAT_RGB        2

/* ── axis_switch v1.7 register map ─────────────────────────────────────── */
#define AXIS_SWITCH_CTRL       0x000    /* [1] = commit register update */
#define AXIS_SWITCH_COMMIT     0x02u
#define AXIS_SWITCH_MI_MUX0    0x040    /* [3:0]=SI source, [31]=disable */
#define AXIS_SWITCH_SRC_HDMI   0x00u    /* S00 = dvi2rgb */
#define AXIS_SWITCH_SRC_VTPG   0x01u    /* S01 = v_tpg */
#define AXIS_SWITCH_DISABLE    0x80000000u

/* ── Minimal mmio helpers ──────────────────────────────────────────────── */
static inline void vtpg_mmio_w(uintptr_t addr, uint32_t val)
{
    *(volatile uint32_t *)addr = val;
}
static inline uint32_t vtpg_mmio_r(uintptr_t addr)
{
    return *(volatile uint32_t *)addr;
}

/**
 * Route an axis_switch MI port to a particular SI source, then commit.
 *   src = AXIS_SWITCH_SRC_HDMI  (S00, real HDMI)
 *   src = AXIS_SWITCH_SRC_VTPG  (S01, synthetic test pattern)
 *
 * After the write to MI_MUX0, the CTRL[1] commit bit must be pulsed for
 * the new routing to take effect (this is how the v1.7 IP applies updates
 * atomically).
 */
static inline void vtpg_axis_switch_route(uint32_t src)
{
    vtpg_mmio_w(AXIS_SWITCH_BASE + AXIS_SWITCH_MI_MUX0, src & 0x0F);
    vtpg_mmio_w(AXIS_SWITCH_BASE + AXIS_SWITCH_CTRL,    AXIS_SWITCH_COMMIT);
}

/**
 * Configure v_tpg for a static colour-bar (or other) pattern and kick it
 * with auto-restart so it free-runs forever. Streams 24-bit RGB at the
 * 142.857 MHz video clock.
 */
static inline void vtpg_start(uint32_t width, uint32_t height, uint32_t pattern)
{
    vtpg_mmio_w(VTPG_BASE + VTPG_HEIGHT,        height);
    vtpg_mmio_w(VTPG_BASE + VTPG_WIDTH,         width);
    vtpg_mmio_w(VTPG_BASE + VTPG_COLOR_FORMAT,  VTPG_FORMAT_RGB);
    vtpg_mmio_w(VTPG_BASE + VTPG_BCKGND_ID,     pattern);
    vtpg_mmio_w(VTPG_BASE + VTPG_OVRLAY_ID,     0);
    vtpg_mmio_w(VTPG_BASE + VTPG_MOTION_SPEED,  0);
    vtpg_mmio_w(VTPG_BASE + VTPG_ENABLE_INPUT,  0);
    vtpg_mmio_w(VTPG_BASE + VTPG_AP_CTRL,
                VTPG_AP_START | VTPG_AUTO_RESTART);
}

#endif /* VTPG_H */
