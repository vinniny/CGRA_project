#ifndef VTC_H
#define VTC_H

#include <stdint.h>
#include "lcd_modes.h"

/* Minimal subset from xvtc_hw.h */
#define XVTC_CTL_OFFSET         0x000
#define XVTC_GASIZE_OFFSET      0x060
#define XVTC_GFENC_OFFSET       0x068
#define XVTC_GPOL_OFFSET        0x06C
#define XVTC_GHSIZE_OFFSET      0x070
#define XVTC_GVSIZE_OFFSET      0x074
#define XVTC_GHSYNC_OFFSET      0x078
#define XVTC_GVBHOFF_OFFSET     0x07C
#define XVTC_GVSYNC_OFFSET      0x080
#define XVTC_GVSHOFF_OFFSET     0x084
#define XVTC_GGD_OFFSET         0x140

#define XVTC_CTL_VCSS_MASK      0x00040000u
#define XVTC_CTL_VASS_MASK      0x00020000u
#define XVTC_CTL_VBSS_MASK      0x00010000u
#define XVTC_CTL_VSSS_MASK      0x00008000u
#define XVTC_CTL_VFSS_MASK      0x00004000u
#define XVTC_CTL_VTSS_MASK      0x00002000u
#define XVTC_CTL_HBSS_MASK      0x00000800u
#define XVTC_CTL_HSSS_MASK      0x00000400u
#define XVTC_CTL_HFSS_MASK      0x00000200u
#define XVTC_CTL_HTSS_MASK      0x00000100u
#define XVTC_CTL_GE_MASK        0x00000004u
#define XVTC_CTL_RU_MASK        0x00000002u
#define XVTC_CTL_SW_MASK        0x00000001u

#define XVTC_CTL_ALLGENSRC_MASK \
    (XVTC_CTL_VCSS_MASK | XVTC_CTL_VASS_MASK | XVTC_CTL_VBSS_MASK | \
     XVTC_CTL_VSSS_MASK | XVTC_CTL_VFSS_MASK | XVTC_CTL_VTSS_MASK | \
     XVTC_CTL_HBSS_MASK | XVTC_CTL_HSSS_MASK | XVTC_CTL_HFSS_MASK | \
     XVTC_CTL_HTSS_MASK)

#define XVTC_ENC_PROG_MASK      0x00000040u
#define XVTC_POL_HSP_MASK       0x00000008u
#define XVTC_POL_VSP_MASK       0x00000004u
#define XVTC_POL_AVP_MASK       0x00000010u

int vtc_configure_generator(volatile uint8_t *vtcBase, const VideoMode *mode);
void vtc_enable_generator(volatile uint8_t *vtcBase);
void vtc_disable_generator(volatile uint8_t *vtcBase);

#endif
