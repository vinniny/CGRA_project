/* =========================================================================
 * xparameters.h — hand-rolled stand-in for the Vitis Workbench-generated
 * file. ONLY used by the WSL2 build path of demo_ascii.elf. Provides the
 * minimum constants the Vitis BSP source files (xscugic, xil_cache,
 * xil_exception, xplatform_info) need to compile and link cleanly for a
 * Zynq-7000 (XC7Z020) Cortex-A9 #0 standalone application.
 *
 * On Windows Vitis Workbench, this file is NOT used — Vitis auto-generates
 * its own xparameters.h from the .hwh and the BSP regen step. The demo
 * source file (demo_ascii_inverter.c) only ever does `#include "xparameters.h"`
 * so it picks up whichever copy exists in the build path.
 *
 * Hand-rolled deliberately to keep the WSL2 build self-contained and to
 * avoid pulling in the entire Vitis BSP toolchain. ~30 lines.
 * ========================================================================= */
#ifndef XPARAMETERS_H
#define XPARAMETERS_H

/* ── Cortex-A9 #0 ──────────────────────────────────────────────────── */
#define XPAR_CPU_ID                              0U
#define XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ      666666687U
#define XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ     666666687U

/* ── GIC instance (only one on Zynq-7000) ─────────────────────────── */
#define XPAR_XSCUGIC_NUM_INSTANCES               1U
#define XPAR_SCUGIC_SINGLE_DEVICE_ID             0U

#define XPAR_PS7_SCUGIC_0_DEVICE_ID              0U
#define XPAR_PS7_SCUGIC_0_BASEADDR               0xF8F00100U
#define XPAR_PS7_SCUGIC_0_DIST_BASEADDR          0xF8F01000U

/* Aliases used by some BSP code paths */
#define XPAR_SCUGIC_0_DEVICE_ID                  XPAR_PS7_SCUGIC_0_DEVICE_ID
#define XPAR_SCUGIC_0_CPU_BASEADDR               XPAR_PS7_SCUGIC_0_BASEADDR
#define XPAR_SCUGIC_0_DIST_BASEADDR              XPAR_PS7_SCUGIC_0_DIST_BASEADDR

/* ── DDR (just so the BSP knows the memory map) ───────────────────── */
#define XPAR_PS7_DDR_0_S_AXI_BASEADDR            0x00100000U
#define XPAR_PS7_DDR_0_S_AXI_HIGHADDR            0x1FFFFFFFU

/* ── L2 cache controller (Cortex-A9 fixed location on Zynq-7000) ──── */
#define XPAR_PS7_L2CACHEC_0_S_AXI_BASEADDR       0xF8F02000U

/* ── Aliases the BSP source files reference internally ───────────── */
/* xil_cache.c uses XPS_L2CC_BASEADDR */
#define XPS_L2CC_BASEADDR                        0xF8F02000U
/* xscugic.c uses XPS_EFUSE_BASEADDR (only for an assertion in one place) */
#define XPS_EFUSE_BASEADDR                       0xF800D000U
/* xscugic_hw.c uses XPAR_SCUGIC_NUM_INSTANCES (without the X prefix) */
#define XPAR_SCUGIC_NUM_INSTANCES                XPAR_XSCUGIC_NUM_INSTANCES

/* ── Misc — required by xplatform_info.c ──────────────────────────── */
#define XPS_BOARD_ZC702                          0
#define STDOUT_BASEADDRESS                       0xE0000000U   /* UART0 */
#define STDIN_BASEADDRESS                        0xE0000000U

#endif /* XPARAMETERS_H */
