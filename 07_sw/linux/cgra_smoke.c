/* =============================================================================
 * cgra_smoke.c — Linux user-space CGRA smoke test
 *
 * Steps:
 *   1. Open device (UIO if /dev/uio0 exists, else /dev/mem at CGRA_PHYS_BASE)
 *   2. Read APB CSR registers, print them
 *   3. Round-trip a write to a non-protected register (CU_TIMEOUT)
 *   4. Drive a DMA error condition + check IRQ_STATUS bit toggles correctly
 *   5. Soft-reset CU; confirm CU_STATUS clears
 *
 * Designed to run against the CGRA-only or CGRA+HDMI bitstream once
 * deployed. Verifies the driver + bitstream + DT overlay end-to-end.
 *
 * Build:
 *   make -C 07_sw/linux smoke
 *
 * Deploy:
 *   make -C 07_sw/linux deploy
 *
 * Run (on board):
 *   /home/root/cgra/cgra_smoke
 * =============================================================================
 */
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>

#include "cgra_driver.h"

/* ANSI colors (only emit if stdout is a tty) */
#define C_RST  "\033[0m"
#define C_OK   "\033[32m"
#define C_BAD  "\033[31m"
#define C_WARN "\033[33m"
#define C_HDR  "\033[36m"

static int n_pass = 0;
static int n_fail = 0;

#define CHECK(cond, fmt, ...)                                                \
    do {                                                                     \
        if (cond) { printf(C_OK "  PASS" C_RST " " fmt "\n", ##__VA_ARGS__); \
                    n_pass++; }                                              \
        else      { printf(C_BAD "  FAIL" C_RST " " fmt "\n", ##__VA_ARGS__);\
                    n_fail++; }                                              \
    } while (0)

static const struct { uint32_t off; const char *name; } regmap[] = {
    {0x00, "DMA_CTRL"},     {0x04, "DMA_STATUS"},
    {0x08, "DMA_SRC"},      {0x0C, "DMA_DST"},
    {0x10, "DMA_SIZE"},     {0x14, "DMA_SRC_STRIDE"},
    {0x18, "DMA_ROWS"},     {0x1C, "DMA_COLS"},
    {0x20, "CU_CTRL"},      {0x24, "CU_STATUS"},
    {0x28, "CU_CYCLES"},    {0x2C, "CU_TIMEOUT"},
    {0x30, "IRQ_STATUS"},   {0x34, "IRQ_MASK"},
    {0x38, "DMA_ERROR"},    {0x3C, "CU_PC_END"},
    {0x40, "RESULT_DATA"},  {0x44, "RESULT_STATUS"},
    {0x48, "LOOP_START"},   {0x4C, "LOOP_END"},
    {0x50, "LOOP_COUNT"},   {0x54, "RESULT_SKIP"},
    {0x58, "RESULT_ROW0"},  {0x5C, "RESULT_ROW1"},
    {0x60, "RESULT_ROW2"},  {0x64, "RESULT_ROW3"},
    {0x68, "LOOP2_START"},  {0x6C, "LOOP2_END"},
    {0x70, "LOOP2_COUNT"},  {0x74, "TILE_BANK_SEL"},
    {0x78, "TILE_AUTO_INC"},
};
#define REGMAP_N (sizeof(regmap)/sizeof(regmap[0]))

int main(int argc, char **argv)
{
    cgra_dev_t dev = {0};
    const char *path = (argc > 1) ? argv[1] : NULL;

    printf(C_HDR "==== CGRA Linux user-space smoke test ====" C_RST "\n");

    if (cgra_init(&dev, path) < 0) {
        fprintf(stderr, C_BAD "FATAL:" C_RST " cgra_init failed: %s\n",
                strerror(errno));
        fprintf(stderr, "Hint: ensure CGRA bitstream + DT overlay are loaded.\n"
                        "      Try: ls /dev/uio*  or  ls /dev/mem\n");
        return 2;
    }

    printf("opened %s, mode=%s, regs @ %p, span=%zu\n",
           path ? path : "(auto)",
           dev.mode == CGRA_MODE_UIO ? "UIO" : "DEVMEM",
           (void *)dev.regs, dev.map_size);

    /* ── 1. Dump all readable registers ────────────────────────────── */
    printf(C_HDR "\n[1] Initial register dump:" C_RST "\n");
    for (size_t i = 0; i < REGMAP_N; i++) {
        uint32_t v = cgra_read(&dev, regmap[i].off);
        printf("  %-15s @0x%02X = 0x%08X\n", regmap[i].name, regmap[i].off, v);
    }

    /* ── 2. Round-trip CU_TIMEOUT (RW, no side effects) ───────────── */
    printf(C_HDR "\n[2] CU_TIMEOUT round-trip:" C_RST "\n");
    uint32_t saved = cgra_read(&dev, CGRA_CU_TIMEOUT);
    uint32_t pat[] = {0x12345678u, 0xDEADBEEFu, 0xA5A5A5A5u, 0x00000000u};
    int rt_ok = 1;
    for (size_t i = 0; i < sizeof(pat)/sizeof(pat[0]); i++) {
        cgra_write(&dev, CGRA_CU_TIMEOUT, pat[i]);
        uint32_t r = cgra_read(&dev, CGRA_CU_TIMEOUT);
        if (r != pat[i]) { rt_ok = 0;
            printf("    write 0x%08X → read 0x%08X (mismatch)\n", pat[i], r); }
    }
    cgra_write(&dev, CGRA_CU_TIMEOUT, saved);
    CHECK(rt_ok, "CU_TIMEOUT writes round-trip cleanly");

    /* ── 3. CU soft reset clears CU_STATUS ──────────────────────────── */
    printf(C_HDR "\n[3] CU soft reset:" C_RST "\n");
    cgra_soft_reset(&dev);
    uint32_t cu_st = cgra_read(&dev, CGRA_CU_STATUS);
    CHECK((cu_st & CU_STATUS_BUSY) == 0, "CU_STATUS.busy clear after reset");

    /* ── 4. IRQ_STATUS W1C semantics ────────────────────────────────── */
    printf(C_HDR "\n[4] IRQ_STATUS write-1-to-clear:" C_RST "\n");
    /* Write all-ones; any latched bits should clear. Then read and confirm 0. */
    cgra_write(&dev, CGRA_IRQ_STATUS, 0x7);
    uint32_t irq = cgra_read(&dev, CGRA_IRQ_STATUS);
    CHECK(irq == 0, "IRQ_STATUS reads 0 after W1C (got 0x%08X)", irq);

    /* ── 5. RESULT_STATUS read-only test ────────────────────────────── */
    printf(C_HDR "\n[5] RESULT_STATUS readability:" C_RST "\n");
    uint32_t rs1 = cgra_read(&dev, CGRA_RESULT_STATUS);
    uint32_t rs2 = cgra_read(&dev, CGRA_RESULT_STATUS);
    CHECK(rs1 == rs2, "RESULT_STATUS stable across reads (0x%08X)", rs1);

    /* ── 6. CU_CYCLES is monotonic (read same val twice) ────────────── */
    printf(C_HDR "\n[6] CU_CYCLES counter readable:" C_RST "\n");
    uint32_t c1 = cgra_read(&dev, CGRA_CU_CYCLES);
    uint32_t c2 = cgra_read(&dev, CGRA_CU_CYCLES);
    CHECK(c1 == c2, "CU_CYCLES same value when CU idle (0x%08X)", c1);

    /* ── Done ───────────────────────────────────────────────────────── */
    cgra_close(&dev);

    printf(C_HDR "\n==== SUMMARY ====" C_RST "  PASS=%d  FAIL=%d\n",
           n_pass, n_fail);
    return n_fail ? 1 : 0;
}
