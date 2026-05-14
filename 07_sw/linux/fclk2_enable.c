/* =============================================================================
 * fclk2_enable.c — Configure PS7 FCLK_CLK2 = 50 MHz at runtime via SLCR poke.
 *
 * Wildfire's stock BOOT.BIN ps7_init only programs FCLK_CLK0/1; FCLK_CLK2 is
 * left at its reset default (effectively dead). After hot-loading a bitstream
 * that uses FCLK_CLK2, this helper unlocks the SLCR and writes the FPGA2_CLK_CTRL
 * register to derive 50 MHz from IO_PLL (1000 MHz / 20 / 1).
 *
 * Run as root after fpgautil:
 *   /home/root/cgra/fclk2_enable           # set FCLK_CLK2 = 50 MHz
 *   /home/root/cgra/fclk2_enable show      # just print current value
 *
 * SLCR registers (Zynq-7000 TRM Ch.4 + Ch.25):
 *   0xF8000008  SLCR_UNLOCK  (write 0xDF0D to unlock; locked at boot)
 *   0xF8000004  SLCR_LOCK    (write 0x767B to relock)
 *   0xF8000190  FPGA2_CLK_CTRL:
 *                 [25:20] DIVISOR1 (6-bit, ÷1..63)
 *                 [13:8]  DIVISOR0 (6-bit, ÷1..63)
 *                 [5:4]   SRCSEL   (00=IO_PLL, 10=ARM_PLL, 11=DDR_PLL)
 *   FCLK = pll / (DIVISOR0 × DIVISOR1)
 *   IO_PLL on Zynq-7020 default = 1000 MHz → 20 × 1 → 50 MHz
 * ============================================================================= */
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define SLCR_BASE      0xF8000000UL
#define SLCR_SIZE      0x1000
#define SLCR_LOCK      0x004
#define SLCR_UNLOCK    0x008
#define FPGA2_CLK_CTRL 0x190

#define UNLOCK_KEY     0xDF0D
#define LOCK_KEY       0x767B

/* IO_PLL on Zynq is normally 1000 MHz on Wildfire. Verify by reading
 * IO_PLL_CTRL/IO_PLL_CFG if you suspect otherwise. */
#define IO_PLL_HZ      1000000000UL
#define TARGET_HZ      50000000UL
#define DIV1           20
#define DIV2           1
#define SRCSEL_IO_PLL  0x0   /* bits[5:4] = 00 */

int main(int argc, char **argv)
{
    int show_only = (argc > 1 && !strcmp(argv[1], "show"));

    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) { perror("open /dev/mem"); return 1; }

    volatile uint32_t *slcr = mmap(NULL, SLCR_SIZE, PROT_READ | PROT_WRITE,
                                    MAP_SHARED, fd, SLCR_BASE);
    if (slcr == MAP_FAILED) { perror("mmap SLCR"); close(fd); return 1; }

    uint32_t cur = slcr[FPGA2_CLK_CTRL >> 2];
    uint32_t cur_d1 = (cur >> 20) & 0x3F;
    uint32_t cur_d0 = (cur >> 8)  & 0x3F;
    uint32_t cur_src = (cur >> 4) & 0x3;
    uint32_t cur_hz = (cur_d0 && cur_d1) ? (uint32_t)(IO_PLL_HZ / (cur_d0 * cur_d1)) : 0;
    fprintf(stderr, "FPGA2_CLK_CTRL = 0x%08x  DIV1=%u DIV0=%u SRCSEL=%u  → ~%.2f MHz\n",
            cur, cur_d1, cur_d0, cur_src, cur_hz / 1e6);

    if (show_only) { munmap((void *)slcr, SLCR_SIZE); close(fd); return 0; }

    /* Build new value: SRCSEL=IO_PLL, DIVISOR1=DIV1, DIVISOR0=DIV2 (or vice-versa,
     * either order divides the same total). Keep other bits zero. */
    uint32_t new_val = ((DIV1 & 0x3F) << 20) | ((DIV2 & 0x3F) << 8) | (SRCSEL_IO_PLL << 4);

    fprintf(stderr, "Unlocking SLCR...\n");
    slcr[SLCR_UNLOCK >> 2] = UNLOCK_KEY;

    fprintf(stderr, "Writing FPGA2_CLK_CTRL = 0x%08x  (DIV1=%u DIV0=%u → %.2f MHz)\n",
            new_val, DIV1, DIV2, (double)IO_PLL_HZ / (DIV1 * DIV2) / 1e6);
    slcr[FPGA2_CLK_CTRL >> 2] = new_val;

    fprintf(stderr, "Relocking SLCR...\n");
    slcr[SLCR_LOCK >> 2] = LOCK_KEY;

    /* Read back to confirm */
    uint32_t check = slcr[FPGA2_CLK_CTRL >> 2];
    fprintf(stderr, "FPGA2_CLK_CTRL readback = 0x%08x %s\n",
            check, (check == new_val) ? "✓" : "✗ MISMATCH");

    munmap((void *)slcr, SLCR_SIZE);
    close(fd);
    return (check == new_val) ? 0 : 2;
}
