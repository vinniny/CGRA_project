#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H

#include "lcd_modes.h"

/* Must match reserved-memory in system-user.dtsi */
#define HDMI_FB_BASE   0x1F000000u
#define HDMI_FB_SIZE   0x00800000u   /* 8 MiB */

/* Physical base addresses from XSA. Pick one board:
 *   -DBOARD_HAOYUE   : Embedfire Zynq-7020 (cgra_SoC_main BD, validated 2026-04)
 *   -DBOARD_PYNQ_Z2  : TUL PYNQ-Z2 (current SD card target, /mnt/e build 2026-05-10)
 * Default is BOARD_PYNQ_Z2 because that is what we are bringing up.
 *
 * Note: DynClk and CGRA addresses are SWAPPED between the two BDs.
 * Verify against `dtc -I dtb -O dts system.dtb` from the actual SD card
 * before trusting these constants.
 */
#if !defined(BOARD_HAOYUE) && !defined(BOARD_PYNQ_Z2)
#define BOARD_PYNQ_Z2
#endif

#if defined(BOARD_HAOYUE)
#define DYNCLK_BASE    0x43C00000u
#define VDMA_BASE      0x43000000u
#define VTC_BASE       0x43C20000u
/* CGRA APB sits at 0x43C10000 on Haoyue */
#elif defined(BOARD_PYNQ_Z2)
#define DYNCLK_BASE    0x43C10000u   /* matches /mnt/e/system.dtb axi_dynclk@43c10000 */
#define VDMA_BASE      0x43000000u
#define VTC_BASE       0x43C20000u
/* CGRA APB sits at 0x43C00000 on this PYNQ-Z2 BD */
#else
#error "Define BOARD_HAOYUE or BOARD_PYNQ_Z2"
#endif

#define DYNCLK_SIZE    0x00010000u
#define VDMA_SIZE      0x00010000u
#define VTC_SIZE       0x00010000u

/* Safe bring-up mode for HDMI monitors */
#define HDMI_DEFAULT_MODE    VMODE_640x480

#endif
