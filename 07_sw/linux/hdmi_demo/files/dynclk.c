#include "dynclk.h"
#include "mmio_util.h"

#include <math.h>
#include <unistd.h>

/* These lookup tables come from the original Digilent dynclk driver. */
static const uint64_t lock_lookup[64] = {
   0b0011000110111110100011111010010000000001ULL,
   0b0011000110111110100011111010010000000001ULL,
   0b0100001000111110100011111010010000000001ULL,
   0b0101101011111110100011111010010000000001ULL,
   0b0111001110111110100011111010010000000001ULL,
   0b1000110001111110100011111010010000000001ULL,
   0b1001110011111110100011111010010000000001ULL,
   0b1011010110111110100011111010010000000001ULL,
   0b1100111001111110100011111010010000000001ULL,
   0b1110011100111110100011111010010000000001ULL,
   0b1111111111111000010011111010010000000001ULL,
   0b1111111111110011100111111010010000000001ULL,
   0b1111111111101110111011111010010000000001ULL,
   0b1111111111101011110011111010010000000001ULL,
   0b1111111111101000101011111010010000000001ULL,
   0b1111111111100111000111111010010000000001ULL,
   0b1111111111100011111111111010010000000001ULL,
   0b1111111111100010011011111010010000000001ULL,
   0b1111111111100000110111111010010000000001ULL,
   0b1111111111011111010011111010010000000001ULL,
   0b1111111111011101101111111010010000000001ULL,
   0b1111111111011101101111111010010000000001ULL,
   0b1111111111011100001011111010010000000001ULL,
   0b1111111111011010100111111010010000000001ULL,
   0b1111111111011001000011111010010000000001ULL,
   0b1111111111011001000011111010010000000001ULL,
   0b1111111111010111011111111010010000000001ULL,
   0b1111111111010111011111111010010000000001ULL,
   0b1111111111010101111011111010010000000001ULL,
   0b1111111111010101111011111010010000000001ULL,
   0b1111111111010100010111111010010000000001ULL,
   0b1111111111010100010111111010010000000001ULL,
   0b1111111111010010110011111010010000000001ULL,
   0b1111111111010010110011111010010000000001ULL,
   0b1111111111010010110011111010010000000001ULL,
   0b1111111111010001001111111010010000000001ULL,
   0b1111111111010001001111111010010000000001ULL,
   0b1111111111010001001111111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL,
   0b1111111111001111101011111010010000000001ULL
};

static const uint32_t filter_lookup_low[64] = {
    0b0001011111, 0b0001010111, 0b0001111011, 0b0001011011,
    0b0001101011, 0b0001110011, 0b0001110011, 0b0001110011,
    0b0001110011, 0b0001001011, 0b0001001011, 0b0001001011,
    0b0010110011, 0b0001010011, 0b0001010011, 0b0001010011,
    0b0001010011, 0b0001010011, 0b0001010011, 0b0001010011,
    0b0001010011, 0b0001010011, 0b0001010011, 0b0001100011,
    0b0001100011, 0b0001100011, 0b0001100011, 0b0001100011,
    0b0001100011, 0b0001100011, 0b0001100011, 0b0001100011,
    0b0001100011, 0b0001100011, 0b0001100011, 0b0001100011,
    0b0001100011, 0b0010010011, 0b0010010011, 0b0010010011,
    0b0010010011, 0b0010010011, 0b0010010011, 0b0010010011,
    0b0010010011, 0b0010010011, 0b0010010011, 0b0010100011,
    0b0010100011, 0b0010100011, 0b0010100011, 0b0010100011,
    0b0010100011, 0b0010100011, 0b0010100011, 0b0010100011,
    0b0010100011, 0b0010100011, 0b0010100011, 0b0010100011,
    0b0010100011, 0b0010100011, 0b0010100011, 0b0010100011
};

uint32_t ClkCountCalc(uint32_t divide)
{
    uint32_t output = 0;
    uint32_t divCalc = ClkDivider(divide);
    if (divCalc == ERR_CLKDIVIDER) {
        output = ERR_CLKCOUNTCALC;
    } else {
        output = (0xFFFu & divCalc) | ((divCalc << 10) & 0x00C00000u);
    }
    return output;
}

uint32_t ClkDivider(uint32_t divide)
{
    uint32_t output = 0;
    uint32_t highTime = 0;
    uint32_t lowTime = 0;

    if ((divide < 1u) || (divide > 128u)) {
        return ERR_CLKDIVIDER;
    }
    if (divide == 1u) {
        return 0x1041u;
    }

    highTime = divide / 2u;
    if (divide & 0x1u) {
        lowTime = highTime + 1u;
        output = 1u << CLK_BIT_WEDGE;
    } else {
        lowTime = highTime;
    }

    output |= 0x03Fu & lowTime;
    output |= 0xFC0u & (highTime << 6);
    return output;
}

uint32_t ClkFindReg(ClkConfig *regValues, ClkMode *clkParams)
{
    if ((clkParams->fbmult < 2u) || (clkParams->fbmult > 64u)) {
        return 0;
    }

    regValues->clk0L = ClkCountCalc(clkParams->clkdiv);
    if (regValues->clk0L == ERR_CLKCOUNTCALC) return 0;

    regValues->clkFBL = ClkCountCalc(clkParams->fbmult);
    if (regValues->clkFBL == ERR_CLKCOUNTCALC) return 0;

    regValues->clkFBH_clk0H = 0u;
    regValues->divclk = ClkDivider(clkParams->maindiv);
    if (regValues->divclk == ERR_CLKDIVIDER) return 0;

    regValues->lockL = (uint32_t)(lock_lookup[clkParams->fbmult - 1u] & 0xFFFFFFFFULL);
    regValues->fltr_lockH = (uint32_t)((lock_lookup[clkParams->fbmult - 1u] >> 32) & 0x000000FFULL);
    regValues->fltr_lockH |= ((filter_lookup_low[clkParams->fbmult - 1u] << 16) & 0x03FF0000u);
    return 1;
}

double ClkFindParams(double freq, ClkMode *bestPick)
{
    double bestError = 2000.0;
    bestPick->freq = 0.0;

    /* Digilent core internally generates 5x pixel clock, then divides by 5. */
    freq *= 5.0;

    for (uint32_t curDiv = 1; curDiv <= 10; ++curDiv) {
        uint32_t minFb = curDiv * 6u;
        uint32_t maxFb = curDiv * 12u;
        if (maxFb > 64u) maxFb = 64u;

        double curClkMult = (100.0 / (double)curDiv) / freq;

        for (uint32_t curFb = minFb; curFb <= maxFb; ++curFb) {
            uint32_t curClkDiv = (uint32_t)((curClkMult * (double)curFb) + 0.5);
            if (curClkDiv == 0u) continue;
            double curFreq = ((100.0 / (double)curDiv) / (double)curClkDiv) * (double)curFb;
            double curError = fabs(curFreq - freq);
            if (curError < bestError) {
                bestError = curError;
                bestPick->clkdiv = curClkDiv;
                bestPick->fbmult = curFb;
                bestPick->maindiv = curDiv;
                bestPick->freq = curFreq;
            }
        }
    }

    bestPick->freq /= 5.0;
    return bestError / 5.0;
}

void ClkWriteReg(ClkConfig *regValues, volatile uint8_t *dynClkBase)
{
    mmio_write32(dynClkBase, OFST_DYNCLK_CLK_L, regValues->clk0L);
    mmio_write32(dynClkBase, OFST_DYNCLK_FB_L, regValues->clkFBL);
    mmio_write32(dynClkBase, OFST_DYNCLK_FB_H_CLK_H, regValues->clkFBH_clk0H);
    mmio_write32(dynClkBase, OFST_DYNCLK_DIV, regValues->divclk);
    mmio_write32(dynClkBase, OFST_DYNCLK_LOCK_L, regValues->lockL);
    mmio_write32(dynClkBase, OFST_DYNCLK_FLTR_LOCK_H, regValues->fltr_lockH);
}

void ClkStart(volatile uint8_t *dynClkBase)
{
    mmio_write32(dynClkBase, OFST_DYNCLK_CTRL, (1u << BIT_DYNCLK_START));
    while (!(mmio_read32(dynClkBase, OFST_DYNCLK_STATUS) & (1u << BIT_DYNCLK_RUNNING))) {
        usleep(1000);
    }
}

void ClkStop(volatile uint8_t *dynClkBase)
{
    mmio_write32(dynClkBase, OFST_DYNCLK_CTRL, 0u);
    while (mmio_read32(dynClkBase, OFST_DYNCLK_STATUS) & (1u << BIT_DYNCLK_RUNNING)) {
        usleep(1000);
    }
}

int dynclk_program(volatile uint8_t *dynClkBase, const VideoMode *mode, double *actual_freq_mhz)
{
    ClkMode clkMode;
    ClkConfig clkReg;

    (void)ClkFindParams(mode->freq, &clkMode);
    if (!ClkFindReg(&clkReg, &clkMode)) {
        return -1;
    }

    ClkWriteReg(&clkReg, dynClkBase);
    ClkStop(dynClkBase);
    ClkStart(dynClkBase);

    if (actual_freq_mhz) {
        *actual_freq_mhz = clkMode.freq;
    }
    return 0;
}
