#ifndef DYNCLK_H_
#define DYNCLK_H_

#include <stdint.h>
#include "lcd_modes.h"

#define CLK_BIT_WEDGE 13
#define CLK_BIT_NOCOUNT 12
#define ERR_CLKDIVIDER ((1u << CLK_BIT_WEDGE) | (1u << CLK_BIT_NOCOUNT))
#define ERR_CLKCOUNTCALC 0xFFFFFFFFu

#define OFST_DYNCLK_CTRL          0x00
#define OFST_DYNCLK_STATUS        0x04
#define OFST_DYNCLK_CLK_L         0x08
#define OFST_DYNCLK_FB_L          0x0C
#define OFST_DYNCLK_FB_H_CLK_H    0x10
#define OFST_DYNCLK_DIV           0x14
#define OFST_DYNCLK_LOCK_L        0x18
#define OFST_DYNCLK_FLTR_LOCK_H   0x1C

#define BIT_DYNCLK_START   0
#define BIT_DYNCLK_RUNNING 0

typedef struct {
    uint32_t clk0L;
    uint32_t clkFBL;
    uint32_t clkFBH_clk0H;
    uint32_t divclk;
    uint32_t lockL;
    uint32_t fltr_lockH;
} ClkConfig;

typedef struct {
    double freq;
    uint32_t fbmult;
    uint32_t clkdiv;
    uint32_t maindiv;
} ClkMode;

uint32_t ClkDivider(uint32_t divide);
uint32_t ClkCountCalc(uint32_t divide);
uint32_t ClkFindReg(ClkConfig *regValues, ClkMode *clkParams);
double ClkFindParams(double freq, ClkMode *bestPick);
void ClkWriteReg(ClkConfig *regValues, volatile uint8_t *dynClkBase);
void ClkStart(volatile uint8_t *dynClkBase);
void ClkStop(volatile uint8_t *dynClkBase);
int dynclk_program(volatile uint8_t *dynClkBase, const VideoMode *mode, double *actual_freq_mhz);

#endif
