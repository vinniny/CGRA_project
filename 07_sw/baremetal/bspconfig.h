/* =========================================================================
 * bspconfig.h — minimal stand-in for the Vitis BSP configuration header.
 * Pulled in by xil_exception.c and a few other BSP source files. Vitis
 * Workbench normally generates this from the BSP settings dialog. We
 * provide just enough macros for the standalone Cortex-A9 build path.
 * Not used on Windows Vitis Workbench (Vitis generates its own).
 * ========================================================================= */
#ifndef BSPCONFIG_H
#define BSPCONFIG_H

#define MICROBLAZE_PVR_NONE
#define EL3                          1
#define EL1_NONSECURE                0
#define HYP_GUEST                    0

#endif /* BSPCONFIG_H */
