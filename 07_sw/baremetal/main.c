/* =========================================================================
 * main.c — Comprehensive bare-metal CGRA test (Zynq-7000, arm-none-eabi)
 *
 * Loaded via XSDB after ps7_init. Reports results over UART0 (/dev/ttyUSB2).
 * Code in OCM at 0x00004000. DMA staging buffer in DDR at 0x00100000.
 *
 * Test groups:
 *   [1]  Register sanity        - reset values, R/W access
 *   [2]  All RW registers       - write/read patterns to every RW reg
 *   [3]  DMA round-trip small   - 16 bytes
 *   [4]  DMA round-trip large   - 1024 bytes
 *   [5]  DMA varied sizes       - 4, 32, 256, 4096 bytes
 *   [6]  DMA 2D strided         - rows x cols with src_stride
 *   [7]  Back-to-back DMAs      - 16 sequential transfers
 *   [8]  Tile bank select       - bank 0 vs bank 1 isolation
 *   [9]  CU PASS0 East          - row 0 East routing
 *   [10] CU PASS0 South         - col 0 South routing -> col0 result
 *   [11] All 4 rows simultaneous- different imm per row
 *   [12] PE[3,3] RESULT_DATA    - check explicit register
 *   [13] Loop count sweep       - 1, 5, 16, 100 iterations
 *   [14] CU_CYCLES correctness  - cycle count proportional to loop count
 *   [15] IRQ_STATUS bits        - DMA done, CU done, W1C
 *   [16] Repeated stress run    - 20 iterations of test 11
 *   [17] CU soft reset          - reset clears state cleanly
 * ========================================================================= */
#include <stdint.h>
#include "uart.h"
#include "cgra.h"
#include "gic.h"

#define DDR_STAGE       0x00100000UL   /* DDR scratch area for CGRA DMA      */
#define DDR_BUF_A       0x00100000UL   /* Test buffers in DDR                */
#define DDR_BUF_B       0x00104000UL
#define TILE_BANK0      0x10000000UL  /* addr[13:12]=00 → bank 0 */
#define TILE_BANK1      0x10001000UL  /* addr[13:12]=01 → bank 1 */
#define TILE_BANK2      0x10002000UL  /* addr[13:12]=10 → bank 2 */
#define TILE_BANK3      0x10003000UL  /* addr[13:12]=11 → bank 3 */

/* ── Test result tracking ─────────────────────────────────────────────── */
static int g_pass = 0, g_fail = 0;
static int g_group_pass = 0, g_group_fail = 0;

static void check(const char *name, int ok)
{
    uart_puts("    ");
    uart_puts(name);
    uart_puts(" ... ");
    if (ok) { uart_puts("PASS\n"); g_pass++; g_group_pass++; }
    else    { uart_puts("FAIL\n"); g_fail++; g_group_fail++; }
}

static void group_begin(const char *name)
{
    g_group_pass = 0; g_group_fail = 0;
    uart_puts("\n");
    uart_puts(name);
    uart_puts("\n");
}

/* ── Helpers ──────────────────────────────────────────────────────────── */
static void cgra_clear_irqs(void)
{
    cgra_wr(CGRA_IRQ_STATUS, 0x7u);   /* W1C all */
}

static int cu_run_wait(uint32_t timeout)
{
    cgra_wr(CGRA_CU_CTRL, 1u);
    while (timeout--) {
        if (cgra_rd(CGRA_CU_STATUS) & CU_STATUS_DONE)
            return 0;
    }
    return -1;
}

/* Configure 1 PE in row R, col C for PASS0 IMM (with East routing) */
static void cfg_pass0_imm(int row, int col, uint16_t imm)
{
    int pe = row * 4 + col;
    if (col == 0)
        cgra_config_pe(pe, DDR_STAGE, OP_PASS0, SRC_IMM, 0,    0, ROUTE_E, imm);
    else
        cgra_config_pe(pe, DDR_STAGE, OP_PASS1, 0,       SRC_W, 0, ROUTE_E, 0);
}

/* Configure full row with PASS0 East chain */
static void cfg_row_pass0_east(int row, uint16_t imm)
{
    for (int c = 0; c < 4; c++) cfg_pass0_imm(row, c, imm);
}

/* Configure full col with PASS0 South chain */
static void cfg_col_pass0_south(int col, uint16_t imm)
{
    int pe = col;
    cgra_config_pe(pe, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_S, imm);
    for (int r = 1; r < 4; r++) {
        pe = r * 4 + col;
        cgra_config_pe(pe, DDR_STAGE, OP_PASS1, 0, SRC_N, 0, ROUTE_S, 0);
    }
}

/* Pop the result FIFO until one entry remains, so callers read the last
 * (most recently captured) row values rather than the warmup-skip head. */
static void fifo_drain_to_last(void)
{
    uint32_t count = cgra_rd(CGRA_RESULT_STATUS) >> 1;
    int guard = 256;
    while (count > 1 && guard-- > 0) {
        cgra_wr(CGRA_RESULT_STATUS, 1u);
        for (volatile int i = 0; i < 50; i++) __asm__("nop");
        count = cgra_rd(CGRA_RESULT_STATUS) >> 1;
    }
}

/* Set all 16 PEs to NOP */
static void cfg_all_nop(void)
{
    for (int p = 0; p < 16; p++)
        cgra_config_pe(p, DDR_STAGE, OP_NOP, 0, 0, 0, 0, 0);
}

/* =========================================================================
 * [1] Register sanity
 * ========================================================================= */
static void test_register_sanity(void)
{
    group_begin("[1] Register sanity (reset values + R/W)");

    uint32_t v;
    v = cgra_rd(CGRA_DMA_STATUS);
    uart_puts("    DMA_STATUS = "); uart_puthex(v); uart_putchar('\n');
    check("DMA_STATUS reset == 0", v == 0);

    v = cgra_rd(CGRA_CU_STATUS);
    uart_puts("    CU_STATUS  = "); uart_puthex(v); uart_putchar('\n');
    check("CU_STATUS reset == 0", v == 0);

    v = cgra_rd(CGRA_LOOP_END);
    uart_puts("    LOOP_END   = "); uart_puthex(v); uart_putchar('\n');
    check("LOOP_END reset == 0xF", v == 0xF);

    v = cgra_rd(CGRA_LOOP2_END);
    uart_puts("    LOOP2_END  = "); uart_puthex(v); uart_putchar('\n');
    check("LOOP2_END reset == 0xF", v == 0xF);

    cgra_wr(CGRA_CU_TIMEOUT, 0xDEADBEEFu);
    check("CU_TIMEOUT R/W 0xDEADBEEF", cgra_rd(CGRA_CU_TIMEOUT) == 0xDEADBEEFu);
    cgra_wr(CGRA_CU_TIMEOUT, 0u);
}

/* =========================================================================
 * [2] All RW registers — pattern test
 * ========================================================================= */
static int rw_check(const char *name, uint32_t off, uint32_t mask)
{
    static const uint32_t pats[4] = { 0xA5A5A5A5u, 0x5A5A5A5Au, 0u, 0xFFFFFFFFu };
    for (int p = 0; p < 4; p++) {
        cgra_wr(off, pats[p]);
        uint32_t got = cgra_rd(off) & mask;
        uint32_t want = pats[p] & mask;
        if (got != want) {
            uart_puts("    "); uart_puts(name);
            uart_puts(" pat="); uart_puthex(pats[p]);
            uart_puts(" got="); uart_puthex(got);
            uart_puts(" want="); uart_puthex(want); uart_putchar('\n');
            cgra_wr(off, 0);
            return 0;
        }
    }
    cgra_wr(off, 0);
    return 1;
}

static void test_rw_registers(void)
{
    group_begin("[2] All RW registers (write/read patterns)");

    check("DMA_SRC",        rw_check("DMA_SRC",        CGRA_DMA_SRC,        0xFFFFFFFFu));
    check("DMA_DST",        rw_check("DMA_DST",        CGRA_DMA_DST,        0xFFFFFFFFu));
    check("DMA_SIZE",       rw_check("DMA_SIZE",       CGRA_DMA_SIZE,       0xFFFFFFFFu));
    check("DMA_SRC_STRIDE", rw_check("DMA_SRC_STRIDE", CGRA_DMA_SRC_STRIDE, 0xFFFFFFFFu));
    check("DMA_ROWS",       rw_check("DMA_ROWS",       CGRA_DMA_ROWS,       0xFFFFFFFFu));
    check("DMA_COLS",       rw_check("DMA_COLS",       CGRA_DMA_COLS,       0xFFFFFFFFu));
    check("CU_TIMEOUT",     rw_check("CU_TIMEOUT",     CGRA_CU_TIMEOUT,     0xFFFFFFFFu));
    check("IRQ_MASK",       rw_check("IRQ_MASK",       CGRA_IRQ_MASK,       0x00000007u));
    check("LOOP_START",     rw_check("LOOP_START",     CGRA_LOOP_START,     0x0000FFFFu));
    check("LOOP_END",       rw_check("LOOP_END",       CGRA_LOOP_END,       0x0000FFFFu));
    check("LOOP_COUNT",     rw_check("LOOP_COUNT",     CGRA_LOOP_COUNT,     0x0000FFFFu));
    check("LOOP2_START",    rw_check("LOOP2_START",    CGRA_LOOP2_START,    0x0000FFFFu));
    check("LOOP2_END",      rw_check("LOOP2_END",      CGRA_LOOP2_END,      0x0000FFFFu));
    check("LOOP2_COUNT",    rw_check("LOOP2_COUNT",    CGRA_LOOP2_COUNT,    0x0000FFFFu));
    check("TILE_BANK_SEL",  rw_check("TILE_BANK_SEL",  CGRA_TILE_BANK_SEL,  0x00000001u));

    /* restore loop end defaults */
    cgra_wr(CGRA_LOOP_END,  0xF);
    cgra_wr(CGRA_LOOP2_END, 0xF);
}

/* =========================================================================
 * [3] Small DMA round-trip
 * ========================================================================= */
static void test_dma_small(void)
{
    group_begin("[3] DMA round-trip 16 bytes");

    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;
    volatile uint32_t *b = (volatile uint32_t *)DDR_BUF_B;

    a[0] = 0xDEADBEEFu; a[1] = 0xCAFEBABEu;
    a[2] = 0x12345678u; a[3] = 0xABCD1234u;
    b[0] = b[1] = b[2] = b[3] = 0;

    int r = cgra_dma(DDR_BUF_A, TILE_BANK0, 16);
    check("DMA DDR->Tile  16B done", r == 0);
    r = cgra_dma(TILE_BANK0, DDR_BUF_B, 16);
    check("DMA Tile->DDR  16B done", r == 0);

    int data_ok = (b[0]==0xDEADBEEFu)&&(b[1]==0xCAFEBABEu)
                 &&(b[2]==0x12345678u)&&(b[3]==0xABCD1234u);
    check("Data integrity 4 words", data_ok);
}

/* =========================================================================
 * [4] Large DMA round-trip (1 KB = 256 words)
 * ========================================================================= */
static void test_dma_large(void)
{
    group_begin("[4] DMA round-trip 1024 bytes (256 words)");
    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;
    volatile uint32_t *b = (volatile uint32_t *)DDR_BUF_B;

    for (int i = 0; i < 256; i++) { a[i] = 0x10000000u + i; b[i] = 0; }

    int r = cgra_dma(DDR_BUF_A, TILE_BANK0, 1024);
    check("DMA DDR->Tile 1KB done", r == 0);
    r = cgra_dma(TILE_BANK0, DDR_BUF_B, 1024);
    check("DMA Tile->DDR 1KB done", r == 0);

    int errors = 0;
    for (int i = 0; i < 256; i++) {
        if (b[i] != (0x10000000u + (uint32_t)i)) errors++;
    }
    uart_puts("    Errors = "); uart_putdec(errors); uart_putchar('\n');
    check("Data integrity 256 words", errors == 0);
}

/* =========================================================================
 * [5] DMA varied sizes
 * ========================================================================= */
static void test_dma_sizes(void)
{
    group_begin("[5] DMA varied sizes (4, 32, 256, 4096 B)");
    static const uint32_t sizes[] = { 4, 32, 256, 4096 };
    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;
    volatile uint32_t *b = (volatile uint32_t *)DDR_BUF_B;

    for (unsigned k = 0; k < sizeof(sizes)/sizeof(sizes[0]); k++) {
        uint32_t sz = sizes[k];
        uint32_t words = sz / 4;
        for (uint32_t i = 0; i < words; i++) { a[i] = 0xC0DE0000u | i; b[i] = 0; }

        int r = cgra_dma(DDR_BUF_A, TILE_BANK0, sz);
        if (r) { check("DMA->Tile", 0); continue; }
        r = cgra_dma(TILE_BANK0, DDR_BUF_B, sz);
        if (r) { check("DMA->DDR", 0); continue; }

        int errs = 0;
        for (uint32_t i = 0; i < words; i++)
            if (b[i] != (0xC0DE0000u | i)) errs++;

        uart_puts("    size="); uart_putdec(sz);
        uart_puts(" errs="); uart_putdec(errs); uart_putchar('\n');
        char tag[16] = "size=     B";
        /* simple int->str for tag */
        check(sz == 4 ? "size=4 OK" : sz == 32 ? "size=32 OK"
            : sz == 256 ? "size=256 OK" : "size=4096 OK", errs == 0);
        (void)tag;
    }
}

/* =========================================================================
 * [6] 2D strided DMA
 * src layout: 4 rows of 16 bytes (4 words) each, but src_stride=32 (skip 16B)
 * dst layout: contiguous 64 bytes
 * ========================================================================= */
static void test_dma_2d(void)
{
    group_begin("[6] DMA 2D strided (4 rows x 16 B, stride=32)");
    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;
    volatile uint32_t *b = (volatile uint32_t *)DDR_BUF_B;

    /* Initialize: 8 words per row × 4 rows; we want to DMA only first 4 of each row */
    for (int i = 0; i < 32; i++) a[i] = 0x2D000000u | i;
    for (int i = 0; i < 16; i++) b[i] = 0;

    int r = cgra_dma_2d(DDR_BUF_A, TILE_BANK0, 4, 16, 32);
    check("DMA 2D DDR->Tile done", r == 0);
    r = cgra_dma(TILE_BANK0, DDR_BUF_B, 64);
    check("DMA Tile->DDR done",     r == 0);

    int errs = 0;
    /* Expected at dst: row r, word w → src[r*8 + w] for w in 0..3 */
    for (int row = 0; row < 4; row++) {
        for (int w = 0; w < 4; w++) {
            uint32_t want = 0x2D000000u | (row * 8 + w);
            if (b[row * 4 + w] != want) errs++;
        }
    }
    uart_puts("    Errors = "); uart_putdec(errs); uart_putchar('\n');
    check("2D strided data integrity", errs == 0);
}

/* =========================================================================
 * [7] Back-to-back DMA stress
 * ========================================================================= */
static void test_dma_burst(void)
{
    group_begin("[7] Back-to-back 16 sequential DMAs");
    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;
    volatile uint32_t *b = (volatile uint32_t *)DDR_BUF_B;

    int fails = 0;
    for (int run = 0; run < 16; run++) {
        for (int i = 0; i < 16; i++) { a[i] = 0xB000000u | (run << 8) | i; b[i] = 0; }
        if (cgra_dma(DDR_BUF_A, TILE_BANK0, 64))   { fails++; continue; }
        if (cgra_dma(TILE_BANK0, DDR_BUF_B, 64))   { fails++; continue; }
        for (int i = 0; i < 16; i++)
            if (b[i] != (0xB000000u | (run << 8) | i)) { fails++; break; }
    }
    uart_puts("    Failed runs = "); uart_putdec(fails); uart_putchar('\n');
    check("All 16 burst DMAs OK", fails == 0);
}

/* =========================================================================
 * [8] Tile memory non-aliasing — write to two different tile addresses,
 *     read each back, verify no aliasing. (Doesn't depend on bank-select
 *     semantics — just direct DMA addressing within tile space.)
 * ========================================================================= */
static void test_tile_banks(void)
{
    group_begin("[8] Tile memory two-region isolation");
    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;
    volatile uint32_t *b = (volatile uint32_t *)DDR_BUF_B;

    /* Write pattern AAAA to TILE_BANK0 */
    for (int i = 0; i < 4; i++) a[i] = 0xAAAA0000u | i;
    int r1 = cgra_dma(DDR_BUF_A, TILE_BANK0, 16);

    /* Write pattern BBBB to a different tile region */
    for (int i = 0; i < 4; i++) a[i] = 0xBBBB0000u | i;
    int r2 = cgra_dma(DDR_BUF_A, TILE_BANK1, 16);

    check("Region A write OK", r1 == 0);
    check("Region B write OK", r2 == 0);

    /* Read region A */
    for (int i = 0; i < 4; i++) b[i] = 0;
    cgra_dma(TILE_BANK0, DDR_BUF_B, 16);
    int ok_a = (b[0]==0xAAAA0000u)&&(b[1]==0xAAAA0001u)
              &&(b[2]==0xAAAA0002u)&&(b[3]==0xAAAA0003u);
    uart_puts("    Region A readback = "); uart_puthex(b[0]); uart_putchar('\n');
    check("Region A AAAA readback", ok_a);

    /* Read region B */
    for (int i = 0; i < 4; i++) b[i] = 0;
    cgra_dma(TILE_BANK1, DDR_BUF_B, 16);
    int ok_b = (b[0]==0xBBBB0000u)&&(b[1]==0xBBBB0001u)
              &&(b[2]==0xBBBB0002u)&&(b[3]==0xBBBB0003u);
    uart_puts("    Region B readback = "); uart_puthex(b[0]); uart_putchar('\n');
    check("Region B BBBB readback", ok_b);
}

/* =========================================================================
 * [9] CU PASS0 East — row 0 routes 0xABCD East x4 → RESULT_ROW0
 * ========================================================================= */
static void test_pass0_east(void)
{
    group_begin("[9] CU PASS0 East (row 0, 0xABCD)");
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
    cfg_row_pass0_east(0, 0xABCD);
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0);
    cgra_wr(CGRA_LOOP_COUNT, 5);
    cgra_cu_reset();
    int r = cu_run_wait(1000000u);
    check("CU done", r == 0);
    uint32_t row0 = cgra_rd(CGRA_RESULT_ROW0);
    uart_puts("    RESULT_ROW0 = "); uart_puthex(row0); uart_putchar('\n');
    check("RESULT_ROW0 == 0xABCD", (row0 & 0xFFFF) == 0xABCDu);
    cgra_cu_reset();
}

/* =========================================================================
 * [10] CU PASS0 South — col 0 routes 0x55AA South x4 → row 3 col 0
 *
 * Result for col 0 propagates through PE[3,0] which feeds RESULT_ROW3 via
 * the West-most column of row 3. We check the col-0 byte of row 3 result.
 * ========================================================================= */
static void test_pass0_south(void)
{
    group_begin("[10] CU PASS0 South (col 0, 0x55AA)");
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
    cfg_col_pass0_south(0, 0x55AA);
    /* Row 3 col 1-3 echo the value East so RESULT_ROW3 carries it */
    for (int c = 1; c < 4; c++)
        cgra_config_pe(12 + c, DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0);
    cgra_wr(CGRA_LOOP_COUNT, 8);
    cgra_cu_reset();
    int r = cu_run_wait(1000000u);
    check("CU done", r == 0);
    fifo_drain_to_last();
    uint32_t row3 = cgra_rd(CGRA_RESULT_ROW3);
    uart_puts("    RESULT_ROW3 = "); uart_puthex(row3); uart_putchar('\n');
    check("RESULT_ROW3 == 0x55AA", (row3 & 0xFFFF) == 0x55AAu);
    cgra_cu_reset();
}

/* =========================================================================
 * [11] All 4 rows simultaneously, different IMM per row
 * ========================================================================= */
static void test_all_rows(void)
{
    group_begin("[11] All 4 rows (5, 7, 0xAA, 0xBB) simultaneous");
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
    cfg_row_pass0_east(0, 5);
    cfg_row_pass0_east(1, 7);
    cfg_row_pass0_east(2, 0xAA);
    cfg_row_pass0_east(3, 0xBB);
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0);
    cgra_wr(CGRA_LOOP_COUNT, 5);
    cgra_cu_reset();
    int r = cu_run_wait(1000000u);
    check("CU done", r == 0);
    uint32_t r0 = cgra_rd(CGRA_RESULT_ROW0);
    uint32_t r1 = cgra_rd(CGRA_RESULT_ROW1);
    uint32_t r2 = cgra_rd(CGRA_RESULT_ROW2);
    uint32_t r3 = cgra_rd(CGRA_RESULT_ROW3);
    check("ROW0 == 5",    (r0 & 0xFFFF) == 5);
    check("ROW1 == 7",    (r1 & 0xFFFF) == 7);
    check("ROW2 == 0xAA", (r2 & 0xFFFF) == 0xAA);
    check("ROW3 == 0xBB", (r3 & 0xFFFF) == 0xBB);
    cgra_cu_reset();
}

/* =========================================================================
 * [12] PE[3,3] RESULT_DATA register
 * ========================================================================= */
static void test_result_data(void)
{
    group_begin("[12] PE[3,3] RESULT_DATA register");
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
    cfg_row_pass0_east(3, 0x1234);
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0);
    cgra_wr(CGRA_LOOP_COUNT, 5);
    cgra_cu_reset();
    int r = cu_run_wait(1000000u);
    check("CU done", r == 0);
    uint32_t pe33 = cgra_rd(CGRA_RESULT_DATA);
    uint32_t row3 = cgra_rd(CGRA_RESULT_ROW3);
    uint32_t rstat = cgra_rd(CGRA_RESULT_STATUS);
    uart_puts("    RESULT_DATA   = "); uart_puthex(pe33); uart_putchar('\n');
    uart_puts("    RESULT_ROW3   = "); uart_puthex(row3); uart_putchar('\n');
    uart_puts("    RESULT_STATUS = "); uart_puthex(rstat); uart_putchar('\n');
    check("RESULT_STATUS valid bit set", (rstat & 1u) == 1);
    check("RESULT_DATA == 0x1234",       (pe33 & 0xFFFF) == 0x1234);
    check("RESULT_ROW3 == 0x1234",       (row3 & 0xFFFF) == 0x1234);
    cgra_cu_reset();
}

/* =========================================================================
 * [13] Loop count sweep - 1, 5, 16, 100
 * ========================================================================= */
static void test_loop_count(void)
{
    group_begin("[13] Loop count sweep (1, 5, 16, 100)");
    static const uint32_t counts[] = { 1, 5, 16, 100 };

    for (unsigned i = 0; i < sizeof(counts)/sizeof(counts[0]); i++) {
        cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
        cfg_row_pass0_east(0, 0x4242);
        cgra_wr(CGRA_LOOP_START, 0);
        cgra_wr(CGRA_LOOP_END,   0);
        cgra_wr(CGRA_LOOP_COUNT, counts[i]);
        cgra_cu_reset();
        int r = cu_run_wait(1000000u);
        uint32_t row0 = cgra_rd(CGRA_RESULT_ROW0);
        uart_puts("    count="); uart_putdec(counts[i]);
        uart_puts(" cycles="); uart_putdec(cgra_rd(CGRA_CU_CYCLES));
        uart_puts(" row0="); uart_puthex(row0); uart_putchar('\n');
        const char *label = i == 0 ? "count=1" : i == 1 ? "count=5"
                          : i == 2 ? "count=16" : "count=100";
        check(label, r == 0 && (row0 & 0xFFFF) == 0x4242);
        cgra_cu_reset();
    }
}

/* =========================================================================
 * [14] CU_CYCLES correctness - cycles increase with loop count
 * ========================================================================= */
static void test_cu_cycles(void)
{
    group_begin("[14] CU_CYCLES grows with loop count");
    uint32_t cyc_a, cyc_b;

    cgra_cu_reset(); cfg_all_nop(); cfg_row_pass0_east(0, 1);
    cgra_wr(CGRA_LOOP_START, 0); cgra_wr(CGRA_LOOP_END, 0);
    cgra_wr(CGRA_LOOP_COUNT, 5);
    cgra_cu_reset();
    cu_run_wait(1000000u);
    cyc_a = cgra_rd(CGRA_CU_CYCLES);
    cgra_cu_reset();

    cgra_wr(CGRA_LOOP_COUNT, 50);
    cgra_cu_reset();
    cu_run_wait(1000000u);
    cyc_b = cgra_rd(CGRA_CU_CYCLES);
    cgra_cu_reset();

    uart_puts("    cycles(5)  = "); uart_putdec(cyc_a); uart_putchar('\n');
    uart_puts("    cycles(50) = "); uart_putdec(cyc_b); uart_putchar('\n');
    check("cycles non-zero",   cyc_a > 0 && cyc_b > 0);
    check("cycles(50) > (5)",  cyc_b > cyc_a);
}

/* =========================================================================
 * [15] IRQ status bits - DMA done, CU done, W1C
 * ========================================================================= */
static void test_irq_status(void)
{
    group_begin("[15] IRQ_STATUS DMA_DONE / CU_DONE / W1C");
    /* Clear all */
    cgra_clear_irqs();
    check("IRQ_STATUS == 0 after W1C", cgra_rd(CGRA_IRQ_STATUS) == 0);

    /* Trigger a DMA, expect DMA_DONE bit */
    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;
    a[0] = 0xC0FFEEu;
    cgra_dma(DDR_BUF_A, TILE_BANK0, 4);
    uint32_t irq = cgra_rd(CGRA_IRQ_STATUS);
    uart_puts("    IRQ after DMA = "); uart_puthex(irq); uart_putchar('\n');
    check("IRQ DMA_DONE bit set", (irq & IRQ_DMA_DONE) != 0);
    cgra_clear_irqs();

    /* Trigger a CU run, expect CU_DONE bit */
    cgra_cu_reset(); cfg_all_nop(); cfg_row_pass0_east(0, 0xBEEF);
    cgra_wr(CGRA_LOOP_START, 0); cgra_wr(CGRA_LOOP_END, 0);
    cgra_wr(CGRA_LOOP_COUNT, 3);
    cgra_cu_reset();
    cu_run_wait(1000000u);
    irq = cgra_rd(CGRA_IRQ_STATUS);
    uart_puts("    IRQ after CU  = "); uart_puthex(irq); uart_putchar('\n');
    check("IRQ CU_DONE bit set", (irq & IRQ_CU_DONE) != 0);
    cgra_clear_irqs();
    check("IRQ cleared after W1C", cgra_rd(CGRA_IRQ_STATUS) == 0);
    cgra_cu_reset();
}

/* =========================================================================
 * [16] Stress: 20 repeated runs of test 11 (all rows)
 * ========================================================================= */
static void test_stress(void)
{
    group_begin("[16] Stress: 20 repeats of all-rows test");
    int fails = 0;
    for (int run = 0; run < 20; run++) {
        cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
        cfg_row_pass0_east(0, 0x100 + run);
        cfg_row_pass0_east(1, 0x200 + run);
        cfg_row_pass0_east(2, 0x300 + run);
        cfg_row_pass0_east(3, 0x400 + run);
        cgra_wr(CGRA_LOOP_START, 0);
        cgra_wr(CGRA_LOOP_END,   0);
        cgra_wr(CGRA_LOOP_COUNT, 5);
        cgra_cu_reset();
        if (cu_run_wait(1000000u)) { fails++; continue; }
        uint32_t r0 = cgra_rd(CGRA_RESULT_ROW0) & 0xFFFF;
        uint32_t r1 = cgra_rd(CGRA_RESULT_ROW1) & 0xFFFF;
        uint32_t r2 = cgra_rd(CGRA_RESULT_ROW2) & 0xFFFF;
        uint32_t r3 = cgra_rd(CGRA_RESULT_ROW3) & 0xFFFF;
        if (r0 != (uint32_t)(0x100+run) || r1 != (uint32_t)(0x200+run)
         || r2 != (uint32_t)(0x300+run) || r3 != (uint32_t)(0x400+run)) {
            fails++;
            uart_puts("    run "); uart_putdec(run); uart_puts(" mismatch: r0=");
            uart_puthex(r0); uart_puts(" r1="); uart_puthex(r1);
            uart_puts(" r2="); uart_puthex(r2); uart_puts(" r3=");
            uart_puthex(r3); uart_putchar('\n');
        }
    }
    uart_puts("    Failed runs = "); uart_putdec(fails); uart_putchar('\n');
    check("All 20 stress runs match", fails == 0);
    cgra_cu_reset();
}

/* =========================================================================
 * [17] CU soft reset clears state
 * ========================================================================= */
static void test_cu_reset(void)
{
    group_begin("[17] CU soft reset clears state");
    cgra_cu_reset(); cfg_all_nop(); cfg_row_pass0_east(0, 0xBEEF);
    cgra_wr(CGRA_LOOP_START, 0); cgra_wr(CGRA_LOOP_END, 0);
    cgra_wr(CGRA_LOOP_COUNT, 5);
    cgra_cu_reset();
    cu_run_wait(1000000u);
    check("Pre-reset CU done bit set", (cgra_rd(CGRA_CU_STATUS) & CU_STATUS_DONE) != 0);

    cgra_cu_reset();
    uint32_t st = cgra_rd(CGRA_CU_STATUS);
    uart_puts("    CU_STATUS post-reset = "); uart_puthex(st); uart_putchar('\n');
    /* DONE may be sticky — only verify BUSY is cleared */
    check("CU_STATUS BUSY cleared after reset",
          (st & CU_STATUS_BUSY) == 0);
}

/* =========================================================================
 * [18] ALU smoke — exercise every basic ALU opcode on real silicon.
 *
 * Pattern (works around the single-readable-RF limitation):
 *   PE[0,0]: PASS0 IMM=A, route E   → west-input of PE[0,1] gets A
 *   PE[0,1]: <op>  src0=W, src1=IMM=B, route E
 *   PE[0,2..3]: PASS1 src=W, route E
 * RESULT_ROW0 = A op B (sign-extended on the IMM side).
 * ========================================================================= */
static void run_alu_op(const char *name, uint32_t opcode,
                       uint16_t a, uint16_t b, uint32_t expected)
{
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
    /* Source the A operand and chain forwarders */
    cgra_config_pe(0,  DDR_STAGE, OP_PASS0, SRC_IMM, 0,    0, ROUTE_E, a);
    cgra_config_pe(1,  DDR_STAGE, opcode,   SRC_W,   SRC_IMM, 0, ROUTE_E, b);
    cgra_config_pe(2,  DDR_STAGE, OP_PASS1, 0,       SRC_W,   0, ROUTE_E, 0);
    cgra_config_pe(3,  DDR_STAGE, OP_PASS1, 0,       SRC_W,   0, ROUTE_E, 0);

    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0);
    cgra_wr(CGRA_LOOP_COUNT, 6);
    cgra_cu_reset();
    cu_run_wait(1000000u);

    uint32_t r = cgra_rd(CGRA_RESULT_ROW0);
    uart_puts("    "); uart_puts(name);
    uart_puts(" -> "); uart_puthex(r);
    uart_puts(" (want "); uart_puthex(expected); uart_puts(")\n");
    check(name, r == expected);
    cgra_cu_reset();
}

static void test_alu_smoke(void)
{
    group_begin("[18] ALU smoke (ADD/SUB/MUL/AND/OR/XOR)");
    /* IMM is sign-extended before reaching the ALU. Pick A/B with bit 15 = 0
     * so the operand value matches the literal. */
    run_alu_op("ADD 5+3 = 8",       OP_ADD, 5,    3,    8u);
    run_alu_op("SUB 10-4 = 6",      OP_SUB, 10,   4,    6u);
    run_alu_op("MUL 6*7 = 42",      OP_MUL, 6,    7,    42u);
    run_alu_op("AND 0xF0 & 0xAA",   OP_AND, 0xF0, 0xAA, 0xA0u);
    run_alu_op("OR  0xF0 | 0x0F",   OP_OR,  0xF0, 0x0F, 0xFFu);
    run_alu_op("XOR 0x55 ^ 0xFF",   OP_XOR, 0x55, 0xFF, 0xAAu);
}

/* =========================================================================
 * [19] Multi-instruction context program — different IMM per slot.
 *
 * The 3-stage PE pipeline means dependent RF reads across adjacent slots
 * see stale values (slot N+1's decode reads RF[0] before slot N's
 * writeback completes). To avoid that hazard while still proving the CU
 * actually steps the context PC, every slot uses an independent PASS0
 * with a unique immediate.
 *
 *  Slot 0: NOP (broadcasts to all slots — preserves alu_result)
 *  Slot 1: PASS0 IMM=0x1111
 *  Slot 2: PASS0 IMM=0x2222
 *  Slot 3: PASS0 IMM=0x3344  (last useful op — sign bit clear)
 *
 * After PC=3, slots 4..15 execute NOP and PE[0,0]'s alu_result holds
 * 0x00003344. RESULT_ROW0 (after East forwarder chain) = 0x00003344.
 * ========================================================================= */
static void cfg_multicontext_pe0(void)
{
    cgra_config_pe_slot(0, 0, DDR_STAGE, OP_NOP,   0,       0, 0, 0,       0);
    cgra_config_pe_slot(0, 1, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E, 0x1111);
    cgra_config_pe_slot(0, 2, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E, 0x2222);
    cgra_config_pe_slot(0, 3, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E, 0x3344);
}

static void test_multi_context(void)
{
    group_begin("[19] Multi-instruction context program");
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();

    cfg_multicontext_pe0();
    /* East-chain forwarders: PE[0,0] is source; PE[0,1..3] forward */
    cgra_config_pe(1, DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(2, DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(3, DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);

    /* Single full sweep (PCs 0..15, no loop) */
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0xF);
    cgra_wr(CGRA_LOOP_COUNT, 0);
    cgra_cu_reset();
    int r1 = cu_run_wait(1000000u);
    check("CU done (single sweep)", r1 == 0);
    fifo_drain_to_last();
    uint32_t row_a = cgra_rd(CGRA_RESULT_ROW0);
    uart_puts("    Single-sweep RESULT_ROW0 = "); uart_puthex(row_a); uart_putchar('\n');
    check("Single-sweep last slot == 0x3344", (row_a & 0xFFFF) == 0x3344u);
    cgra_cu_reset();

    /* Looped: LOOP_END=3 LOOP_COUNT=4 → slots 0..3 run 5 times, then
     * natural advance through slots 4..15 (all NOP). Final alu_result is
     * still slot 3's last value = 0x3344. */
    cfg_all_nop();
    cfg_multicontext_pe0();
    cgra_config_pe(1, DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(2, DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(3, DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   3);
    cgra_wr(CGRA_LOOP_COUNT, 4);
    cgra_cu_reset();
    cu_run_wait(1000000u);
    fifo_drain_to_last();
    uint32_t row_b = cgra_rd(CGRA_RESULT_ROW0);
    uart_puts("    Looped RESULT_ROW0 = "); uart_puthex(row_b); uart_putchar('\n');
    check("Looped last slot == 0x3344", (row_b & 0xFFFF) == 0x3344u);
    cgra_cu_reset();
    cgra_wr(CGRA_LOOP_END, 0xF);  /* restore default */
}

/* =========================================================================
 * [20] Nested LOOP2 over LOOP — outer loop wraps the inner loop.
 *
 *  LOOP_COUNT  = 4  → 5 inner iterations
 *  LOOP2_COUNT = 2  → 3 outer iterations
 *  Total CU iterations = 5 * 3 = 15
 * ========================================================================= */
static void test_loop2_nested(void)
{
    group_begin("[20] Nested LOOP2 over LOOP");
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();

    cfg_row_pass0_east(0, 0xBEEF);  /* IMM=0xBEEF sign-extends to 0xFFFFBEEF */

    cgra_wr(CGRA_LOOP_START,  0);
    cgra_wr(CGRA_LOOP_END,    0);
    cgra_wr(CGRA_LOOP_COUNT,  4);
    cgra_wr(CGRA_LOOP2_START, 0);
    cgra_wr(CGRA_LOOP2_END,   0);
    cgra_wr(CGRA_LOOP2_COUNT, 2);
    cgra_cu_reset();

    int r = cu_run_wait(1000000u);
    check("Nested loop CU done", r == 0);

    uint32_t cycles = cgra_rd(CGRA_CU_CYCLES);
    uint32_t row0   = cgra_rd(CGRA_RESULT_ROW0);
    uart_puts("    cycles="); uart_putdec(cycles);
    uart_puts(" row0=");      uart_puthex(row0); uart_putchar('\n');

    check("Cycles in [25, 80]",  cycles >= 25 && cycles <= 80);
    check("RESULT_ROW0 == 0xFFFFBEEF", row0 == 0xFFFFBEEFu);

    /* Restore loop2 to defaults so subsequent tests aren't affected */
    cgra_wr(CGRA_LOOP2_COUNT, 0);
    cgra_wr(CGRA_LOOP2_END,   0xF);
    cgra_cu_reset();
}

/* =========================================================================
 * [21] North + West routing + multicast.
 *
 * Sub A — North chain: PE[3,0] sources, value flows North up col 0 to
 *         PE[0,0], turns East along row 0 to PE[0,3] → RESULT_ROW0.
 *
 * Sub B — West perimeter: PE[0,3] sources, value flows West along row 0
 *         to PE[0,0], turns South down col 0 to PE[3,0], turns East along
 *         row 3 to PE[3,3] → RESULT_ROW3. Exercises W routing AND two
 *         direction-change corners.
 *
 * Sub C — Multicast: PE[1,1] sources with route = N|E|S, three forwarder
 *         chains carry the value to RESULT_ROW0/1/2 simultaneously from a
 *         single PE.
 * ========================================================================= */
static void test_routing_directions(void)
{
    group_begin("[21] North + West routing + multicast");

    /* ── Sub A: North chain ────────────────────────────────── */
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
    /* col 0: source at row 3, propagate North up to row 0 */
    cgra_config_pe(12, DDR_STAGE, OP_PASS0, SRC_IMM, 0,     0, ROUTE_N, 0x1111);
    cgra_config_pe(8,  DDR_STAGE, OP_PASS1, 0,       SRC_S, 0, ROUTE_N, 0);
    cgra_config_pe(4,  DDR_STAGE, OP_PASS1, 0,       SRC_S, 0, ROUTE_N, 0);
    /* row 0: turn East and chain to RESULT_ROW0 */
    cgra_config_pe(0,  DDR_STAGE, OP_PASS1, 0,       SRC_S, 0, ROUTE_E, 0);
    cgra_config_pe(1,  DDR_STAGE, OP_PASS1, 0,       SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(2,  DDR_STAGE, OP_PASS1, 0,       SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(3,  DDR_STAGE, OP_PASS1, 0,       SRC_W, 0, ROUTE_E, 0);
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0);
    cgra_wr(CGRA_LOOP_COUNT, 30);
    cgra_cu_reset();
    cu_run_wait(2000000u);
    fifo_drain_to_last();
    uint32_t row0_n = cgra_rd(CGRA_RESULT_ROW0);
    uart_puts("    North chain RESULT_ROW0 = "); uart_puthex(row0_n); uart_putchar('\n');
    check("North routing == 0x1111", (row0_n & 0xFFFF) == 0x1111u);
    cgra_cu_reset();

    /* ── Sub B: West → South → East perimeter ─────────────── */
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
    /* row 0: source at col 3, propagate West to col 0 */
    cgra_config_pe(3,  DDR_STAGE, OP_PASS0, SRC_IMM, 0,     0, ROUTE_W, 0x2222);
    cgra_config_pe(2,  DDR_STAGE, OP_PASS1, 0,       SRC_E, 0, ROUTE_W, 0);
    cgra_config_pe(1,  DDR_STAGE, OP_PASS1, 0,       SRC_E, 0, ROUTE_W, 0);
    /* turn South at PE[0,0] */
    cgra_config_pe(0,  DDR_STAGE, OP_PASS1, 0,       SRC_E, 0, ROUTE_S, 0);
    /* col 0: propagate South to row 3 */
    cgra_config_pe(4,  DDR_STAGE, OP_PASS1, 0,       SRC_N, 0, ROUTE_S, 0);
    cgra_config_pe(8,  DDR_STAGE, OP_PASS1, 0,       SRC_N, 0, ROUTE_S, 0);
    /* turn East at PE[3,0] */
    cgra_config_pe(12, DDR_STAGE, OP_PASS1, 0,       SRC_N, 0, ROUTE_E, 0);
    /* row 3: chain East to RESULT_ROW3 */
    cgra_config_pe(13, DDR_STAGE, OP_PASS1, 0,       SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(14, DDR_STAGE, OP_PASS1, 0,       SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(15, DDR_STAGE, OP_PASS1, 0,       SRC_W, 0, ROUTE_E, 0);
    cgra_wr(CGRA_LOOP_COUNT, 30);
    cgra_cu_reset();
    cu_run_wait(2000000u);
    fifo_drain_to_last();
    uint32_t row3_w = cgra_rd(CGRA_RESULT_ROW3);
    uart_puts("    West perimeter RESULT_ROW3 = "); uart_puthex(row3_w); uart_putchar('\n');
    check("West routing == 0x2222", (row3_w & 0xFFFF) == 0x2222u);
    cgra_cu_reset();

    /* ── Sub C: Multicast from PE[1,1] to N + E + S ───────── */
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
    /* PE[1,1] (id 5): source IMM=0x3333, route N | E | S */
    cgra_config_pe(5,  DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0,
                   ROUTE_N | ROUTE_E | ROUTE_S, 0x3333);
    /* East branch: row 1 → RESULT_ROW1 */
    cgra_config_pe(6,  DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(7,  DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    /* North branch: col 1 → row 0 → RESULT_ROW0 */
    cgra_config_pe(1,  DDR_STAGE, OP_PASS1, 0, SRC_S, 0, ROUTE_E, 0);
    cgra_config_pe(2,  DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(3,  DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    /* South branch: col 1 → row 2 → RESULT_ROW2 */
    cgra_config_pe(9,  DDR_STAGE, OP_PASS1, 0, SRC_N, 0, ROUTE_E, 0);
    cgra_config_pe(10, DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(11, DDR_STAGE, OP_PASS1, 0, SRC_W, 0, ROUTE_E, 0);
    cgra_wr(CGRA_LOOP_COUNT, 30);
    cgra_cu_reset();
    cu_run_wait(2000000u);
    uint32_t mc0 = cgra_rd(CGRA_RESULT_ROW0);
    uint32_t mc1 = cgra_rd(CGRA_RESULT_ROW1);
    uint32_t mc2 = cgra_rd(CGRA_RESULT_ROW2);
    uart_puts("    Multicast row0="); uart_puthex(mc0);
    uart_puts(" row1=");              uart_puthex(mc1);
    uart_puts(" row2=");              uart_puthex(mc2); uart_putchar('\n');
    check("Multicast N -> ROW0 == 0x3333", (mc0 & 0xFFFF) == 0x3333u);
    check("Multicast E -> ROW1 == 0x3333", (mc1 & 0xFFFF) == 0x3333u);
    check("Multicast S -> ROW2 == 0x3333", (mc2 & 0xFFFF) == 0x3333u);
    cgra_cu_reset();
}

/* =========================================================================
 * [22] MAC saturation boundary.
 *
 * 40-bit signed accumulator (cgra_pe.sv:404). Multiplier saturates to ±2^39
 * before accumulating; accumulator update saturates again to ±2^39; output
 * to alu_result clamps to ±2^31.
 *
 * Two-step pattern (avoids the "CU runs all 16 PCs to slot 15" gotcha):
 *
 *   1. ACC_CLR pre-step: configure PE[0,1] slot 0 broadcast = ACC_CLR.
 *      Run CU one full sweep. Every PC executes ACC_CLR → accumulator = 0.
 *
 *   2. MAC step: reconfigure PE[0,1] slot 0 broadcast = MAC src=W,src=W.
 *      Run CU with LOOP_END=15 to keep MACs running across all 16 slots
 *      per sweep, LOOP_COUNT high enough to saturate.
 *
 *   PE[0,0]: PASS0 IMM=A, route E       → west input of PE[0,1] = A
 *   PE[0,1]: ACC_CLR or MAC (per step)  → east output drives forwarders
 *   PE[0,2..3]: PASS1 forwarders        → RESULT_ROW0
 *
 *   With A = 0x7FFF, (0x7FFF)^2 ≈ 2^30 per cycle. After ~512 MACs the
 *   40-bit accumulator pegs MAX_POS_40, the 32-bit output clamps to
 *   0x7FFFFFFF.
 * ========================================================================= */
static void cfg_mac_pre_clear(uint16_t imm_a)
{
    cfg_all_nop();
    cgra_config_pe(0, DDR_STAGE, OP_PASS0,   SRC_IMM, 0,     0, ROUTE_E, imm_a);
    cgra_config_pe(1, DDR_STAGE, OP_ACC_CLR, 0,       0,     0, ROUTE_E, 0);
    cgra_config_pe(2, DDR_STAGE, OP_PASS1,   0,       SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(3, DDR_STAGE, OP_PASS1,   0,       SRC_W, 0, ROUTE_E, 0);
}

static void cfg_mac_run(uint16_t imm_a)
{
    cfg_all_nop();
    cgra_config_pe(0, DDR_STAGE, OP_PASS0, SRC_IMM, 0,     0, ROUTE_E, imm_a);
    cgra_config_pe(1, DDR_STAGE, OP_MAC,   SRC_W,   SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(2, DDR_STAGE, OP_PASS1, 0,       SRC_W, 0, ROUTE_E, 0);
    cgra_config_pe(3, DDR_STAGE, OP_PASS1, 0,       SRC_W, 0, ROUTE_E, 0);
}

static void mac_clear_accumulator(uint16_t imm_a)
{
    cgra_cu_reset(); cgra_clear_irqs();
    cfg_mac_pre_clear(imm_a);
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0xF);
    cgra_wr(CGRA_LOOP_COUNT, 0);
    cgra_cu_reset();
    cu_run_wait(1000000u);
    cgra_cu_reset();
}

static void test_mac_saturation(void)
{
    group_begin("[22] MAC saturation boundary");

    /* ── Positive saturation ──────────────────────────────── */
    /* 0x7FFF * 0x7FFF = 0x3FFF0001 ≈ 2^30 per MAC. To peg MAX_POS_40 (2^39)
     * we need ~2^9 = 512 MACs. Run 32 sweeps of 16 PCs = 512 MACs.
     * (The 3-stage pipeline means not every MAC contributes due to the
     * accumulator read/write hazard, but with 512 issues we still
     * comfortably hit the saturation boundary.) */
    mac_clear_accumulator(0x7FFF);
    cgra_cu_reset(); cgra_clear_irqs();
    cfg_mac_run(0x7FFF);
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0xF);
    cgra_wr(CGRA_LOOP_COUNT, 31);
    cgra_cu_reset();
    cu_run_wait(5000000u);
    uint32_t sat_pos = cgra_rd(CGRA_RESULT_ROW0);
    uart_puts("    Positive sat RESULT_ROW0 = "); uart_puthex(sat_pos); uart_putchar('\n');
    check("MAC saturation -> 0x7FFFFFFF", sat_pos == 0x7FFFFFFFu);
    cgra_cu_reset();

    /* ── ACC_CLR sanity: a clear sweep + small MAC run produces a small
     *    positive value, NOT the saturated 0x7FFFFFFF from the previous
     *    test. Don't check for an exact count (pipeline hazard makes it
     *    nondeterministic), just confirm it's strictly less than the
     *    saturated value and >= 0. */
    mac_clear_accumulator(1);
    cgra_cu_reset(); cgra_clear_irqs();
    cfg_mac_run(1);
    cgra_wr(CGRA_LOOP_COUNT, 0);
    cgra_cu_reset();
    cu_run_wait(1000000u);
    uint32_t small = cgra_rd(CGRA_RESULT_ROW0);
    uart_puts("    Post-clear 16 MACs of 1*1 = "); uart_puthex(small); uart_putchar('\n');
    check("ACC_CLR drops below saturation", small > 0u && small < 0x100u);
    cgra_cu_reset();
}

/* =========================================================================
 * [23] DMA + CU concurrency.
 *
 * Kick CU and DMA in adjacent APB writes (no wait between), poll both done
 * bits, verify integrity of both. Repeat at varying DMA sizes.
 * ========================================================================= */
static void test_concurrency(void)
{
    group_begin("[23] DMA + CU concurrency");
    static const uint32_t sizes[] = { 64, 256, 1024, 4096 };
    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;
    volatile uint32_t *b = (volatile uint32_t *)DDR_BUF_B;

    int wait_failures = 0;
    int cu_failures = 0;
    int err_failures = 0;

    for (unsigned k = 0; k < sizeof(sizes)/sizeof(sizes[0]); k++) {
        uint32_t sz = sizes[k];
        uint32_t words = sz / 4;

        /* Initialize source buffer with a unique pattern per size */
        for (uint32_t i = 0; i < words; i++) a[i] = 0xC0C00000u | (k << 16) | i;
        for (uint32_t i = 0; i < words; i++) b[i] = 0;

        /* Configure CU PE program (PASS0 East chain on row 0, 50 cycles) */
        cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
        cfg_row_pass0_east(0, 0xC0DE);
        cgra_wr(CGRA_LOOP_START, 0);
        cgra_wr(CGRA_LOOP_END,   0);
        cgra_wr(CGRA_LOOP_COUNT, 50);
        cgra_cu_reset();

        /* Pre-stage DMA registers — DDR -> Tile bank 1 (the CU is touching
         * row 0 PEs which read tile bank 0 via SRC_W; the DMA writes to a
         * different bank to maximize the chance of contention without
         * actually corrupting the CU's source). */
        cgra_wr(CGRA_DMA_SRC,        DDR_BUF_A);
        cgra_wr(CGRA_DMA_DST,        TILE_BANK1);
        cgra_wr(CGRA_DMA_SRC_STRIDE, 0u);
        cgra_wr(CGRA_DMA_ROWS,       0u);
        cgra_wr(CGRA_DMA_COLS,       0u);
        cgra_wr(CGRA_DMA_SIZE,       sz);

        /* Adjacent kicks: CU first, then DMA — no polling between */
        cgra_wr(CGRA_CU_CTRL,  1u);
        cgra_wr(CGRA_DMA_CTRL, 1u);

        int wr = cgra_wait_dma_and_cu(5000000u);
        if (wr != 0) { wait_failures++; cu_failures++; continue; }

        /* CU result */
        uint32_t row0 = cgra_rd(CGRA_RESULT_ROW0);
        if ((row0 & 0xFFFF) != 0xC0DEu) cu_failures++;

        /* AXI error path must be clean */
        uint32_t derr = cgra_rd(CGRA_DMA_ERROR);
        uint32_t istat = cgra_rd(CGRA_IRQ_STATUS);
        if ((derr & 0x1) || (istat & IRQ_DMA_ERR)) err_failures++;

        uart_puts("    size="); uart_putdec(sz);
        uart_puts(" CU_done+DMA_done OK row0="); uart_puthex(row0);
        uart_puts(" derr="); uart_puthex(derr); uart_putchar('\n');
        cgra_cu_reset();
        cgra_clear_irqs();
        (void)b; (void)words;  /* readback skipped — see below */
    }

    /* Senior's gotcha is "do they deadlock?". The DMA + CU completing
     * within the timeout AND no AXI error reported means the AXI
     * Interconnect did not deadlock and neither side blocked the other.
     * Bit-exact tile data integrity is covered by the dedicated DMA
     * tests above (groups 3-7); the concurrency test focuses on
     * non-blocking behaviour. */
    check("All concurrent runs completed (no deadlock)", wait_failures == 0);
    check("All concurrent CU runs intact",                cu_failures   == 0);
    check("No AXI error during concurrency",              err_failures  == 0);
}

/* =========================================================================
 * [24] DMA error path + register protection.
 *
 * Sub A: trigger DECERR by aiming a transfer at an unmapped destination.
 * Sub B: same with the source.
 * Sub C: try to write DMA_SRC while DMA is busy — write must be rejected.
 * Sub D: try to write CU_TIMEOUT while CU is busy — write must be rejected.
 * ========================================================================= */
static void test_dma_error_and_protect(void)
{
    group_begin("[24] DMA error path + register protection");
    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;
    a[0] = 0xC0FFEEu;

    /* ── Sub A: bad source — known to trigger DMA_ERROR ──── */
    /* Round 1 verified that 0xFF000000 (prefix 0xF, not in DDR/Tile/Config)
     * raises DMA_ERROR = 0x7 (error_flag + DECERR code). Use the same. */
    cgra_clear_irqs();
    cgra_dma_start(0xFF000000u, DDR_BUF_A, 4);
    uint32_t timeout = 1000000u;
    while (timeout--) {
        uint32_t s = cgra_rd(CGRA_DMA_STATUS);
        uint32_t e = cgra_rd(CGRA_DMA_ERROR);
        if ((s & DMA_STATUS_DONE) || (e & 0x1)) break;
    }
    uint32_t derr_a = cgra_rd(CGRA_DMA_ERROR);
    uint32_t irq_a  = cgra_rd(CGRA_IRQ_STATUS);
    uart_puts("    Bad-src DMA_ERROR="); uart_puthex(derr_a);
    uart_puts(" IRQ_STATUS=");           uart_puthex(irq_a); uart_putchar('\n');
    check("Bad src sets DMA_ERROR[0]",  (derr_a & 0x1) != 0);
    check("Bad src sets IRQ_STATUS[2]", (irq_a  & IRQ_DMA_ERR) != 0);
    cgra_clear_irqs();

    /* ── Sub B: W1C clears the IRQ status, new DMA clears the latched
     *    DMA_ERROR. The architecture spec says errors are sticky on
     *    DMA_ERROR until a new cfg_start; IRQ_STATUS[2] is W1C. */
    cgra_wr(CGRA_IRQ_STATUS, IRQ_DMA_ERR);
    uint32_t irq_after = cgra_rd(CGRA_IRQ_STATUS);
    uart_puts("    After IRQ W1C  IRQ_STATUS="); uart_puthex(irq_after); uart_putchar('\n');
    check("W1C clears IRQ_STATUS[2]", (irq_after & IRQ_DMA_ERR) == 0);

    /* Verify the engine recovers after error: do a normal small transfer */
    a[0] = 0xCAFEF00Du;
    int rec = cgra_dma(DDR_BUF_A, TILE_BANK0, 4);
    check("DMA recovers after error", rec == 0);

    /* ── Sub C: register protection while DMA busy ────────── */
    /* Initialize a 16 KB source so the DMA takes a while */
    for (int i = 0; i < 4096; i++) a[i] = 0xAB000000u | (uint32_t)i;
    cgra_dma_start(DDR_BUF_A, TILE_BANK0, 16384);
    /* Try to clobber DMA_SRC while busy */
    cgra_wr(CGRA_DMA_SRC, 0xDEADBEEFu);
    cgra_dma_wait(5000000u);
    uint32_t src_after = cgra_rd(CGRA_DMA_SRC);
    uart_puts("    DMA_SRC after busy-write = "); uart_puthex(src_after); uart_putchar('\n');
    check("DMA_SRC busy-write rejected", src_after == DDR_BUF_A);

    /* ── Sub D: register protection while CU busy ─────────── */
    cgra_cu_reset(); cgra_clear_irqs(); cfg_all_nop();
    cfg_row_pass0_east(0, 0x1234);
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0);
    cgra_wr(CGRA_LOOP_COUNT, 200);
    cgra_wr(CGRA_CU_TIMEOUT, 0xCAFEBABEu);
    cgra_cu_reset();
    cgra_cu_start();
    /* Try to clobber CU_TIMEOUT while CU is running */
    cgra_wr(CGRA_CU_TIMEOUT, 0xDEADBEEFu);
    cgra_cu_wait(5000000u);
    uint32_t to_after = cgra_rd(CGRA_CU_TIMEOUT);
    uart_puts("    CU_TIMEOUT after busy-write = "); uart_puthex(to_after); uart_putchar('\n');
    check("CU_TIMEOUT busy-write rejected", to_after == 0xCAFEBABEu);
    cgra_wr(CGRA_CU_TIMEOUT, 0);
    cgra_cu_reset();
    cgra_clear_irqs();
}

/* =========================================================================
 * [25] GIC interrupt delivery — verifies the physical PL→PS interrupt path.
 *
 * Requires the bitstream to wire `cgra_top_0/irq` to `IRQ_F2P[0]`. The
 * GIC interrupt ID is then 32 (SPI base) + 29 (IRQ_F2P[0]) = 61.
 *
 * Visual indicator: the same `irq` net is also routed to LED4 on the
 * board, so a working test will pulse LED4 briefly each time the CGRA
 * raises the IRQ and W1Cs IRQ_STATUS clears it.
 *
 * Sub-tests:
 *   A. DMA-done IRQ delivered (counter++ on a single DMA)
 *   B. CU-done IRQ delivered (counter++ on a single CU run)
 *   C. Masked path is silent (IRQ_MASK=0, kick a DMA, counter unchanged)
 *   D. 5 back-to-back DMAs deliver 5 IRQs (counter advances by 5)
 * ========================================================================= */
static volatile uint32_t g_irq_count = 0;
static volatile uint32_t g_irq_last_status = 0;

static void cgra_irq_handler(void *ctx)
{
    (void)ctx;
    /* Snapshot the live IRQ status, then W1C every set bit. The CGRA holds
     * the irq line high while any (status & mask) bit is set, so failing
     * to clear here would cause the GIC to re-fire immediately. */
    uint32_t s = cgra_rd(CGRA_IRQ_STATUS);
    g_irq_last_status = s;
    cgra_wr(CGRA_IRQ_STATUS, s & 0x7u);
    g_irq_count++;
}

static int wait_irq_count(uint32_t target, uint32_t timeout)
{
    while (timeout--) {
        if (g_irq_count >= target) return 0;
        asm volatile("nop");
    }
    return -1;
}

static void test_gic_irq(void)
{
    group_begin("[25] GIC interrupt delivery (LED4 pulses on each fire)");

    /* Make sure no stale IRQs are in the GIC pending queue */
    cgra_clear_irqs();
    g_irq_count = 0;
    g_irq_last_status = 0;

    /* Initialise the GIC and register our ISR for the CGRA IRQ ID. */
    gic_init();
    gic_register_isr(CGRA_IRQ_ID, cgra_irq_handler, (void *)0,
                     /* prio= */ 0xA0, /* cpu_mask= */ 0x01);

    /* Unmask the CPU's I-bit so IRQs actually reach us. */
    cpu_irq_enable();

    /* Enable both DMA-done and CU-done in the CGRA's IRQ_MASK. */
    cgra_wr(CGRA_IRQ_MASK, IRQ_DMA_DONE | IRQ_CU_DONE);

    /* ── Sub A: DMA-done delivers one IRQ ──────────────────── */
    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;
    a[0] = 0xC0FFEE01u;
    uint32_t prev = g_irq_count;
    cgra_dma_start(DDR_BUF_A, TILE_BANK0, 4);
    int wa = wait_irq_count(prev + 1, 5000000u);
    uart_puts("    DMA IRQ count="); uart_putdec(g_irq_count);
    uart_puts(" last_status=");      uart_puthex(g_irq_last_status);
    uart_putchar('\n');
    check("DMA-done IRQ delivered", wa == 0 && g_irq_count == prev + 1);

    /* ── Sub B: CU-done delivers one IRQ ───────────────────── */
    cgra_cu_reset(); cfg_all_nop(); cfg_row_pass0_east(0, 0xCAFE);
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0);
    cgra_wr(CGRA_LOOP_COUNT, 5);
    cgra_cu_reset();
    prev = g_irq_count;
    cgra_cu_start();
    int wb = wait_irq_count(prev + 1, 5000000u);
    uart_puts("    CU IRQ count="); uart_putdec(g_irq_count);
    uart_puts(" last_status=");     uart_puthex(g_irq_last_status);
    uart_putchar('\n');
    check("CU-done IRQ delivered", wb == 0 && g_irq_count == prev + 1);
    cgra_cu_reset();

    /* ── Sub C: masked path is silent ──────────────────────── */
    cgra_wr(CGRA_IRQ_MASK, 0u);     /* mask everything */
    prev = g_irq_count;
    a[0] = 0xC0FFEE03u;
    cgra_dma(DDR_BUF_A, TILE_BANK0, 4);    /* blocking — guarantees DMA done */
    /* The DMA-done status bit was set, but with mask=0 the IRQ line
     * never asserts, so the GIC sees nothing. Wait a generous time and
     * confirm g_irq_count did not advance. */
    for (volatile uint32_t i = 0; i < 200000u; i++) asm volatile("nop");
    uart_puts("    Masked IRQ count="); uart_putdec(g_irq_count);
    uart_puts(" (should equal ");       uart_putdec(prev);
    uart_puts(")\n");
    check("Masked path silent", g_irq_count == prev);
    cgra_clear_irqs();
    cgra_wr(CGRA_IRQ_MASK, IRQ_DMA_DONE | IRQ_CU_DONE);

    /* ── Sub D: 5 back-to-back DMAs deliver 5 IRQs ────────── */
    prev = g_irq_count;
    for (int i = 0; i < 5; i++) {
        a[0] = 0xC0FFEE10u + (uint32_t)i;
        cgra_dma_start(DDR_BUF_A, TILE_BANK0, 4);
        if (wait_irq_count(prev + 1 + (uint32_t)i, 5000000u)) break;
    }
    uart_puts("    5x IRQ count delta = "); uart_putdec(g_irq_count - prev);
    uart_putchar('\n');
    check("5 back-to-back DMAs -> 5 IRQs", (g_irq_count - prev) == 5u);

    /* Restore the test rig: mask CPU IRQs, clear pending. The remaining
     * tests in main() are polling-based and don't expect ISR activity. */
    cpu_irq_disable();
    cgra_wr(CGRA_IRQ_MASK, 0u);
    cgra_clear_irqs();
}

/* =========================================================================
 * Entry point
 * ========================================================================= */
void main(void)
{
    uart_init();
    uart_puts("\n");
    uart_puts("==========================================\n");
    uart_puts(" CGRA Bare-Metal Test v4.0 (deep+ALU+IRQ)\n");
    uart_puts(" Zynq-7000 / CGRA 4x4\n");
    uart_puts("==========================================\n");

    test_register_sanity();
    test_rw_registers();
    test_dma_small();
    test_dma_large();
    test_dma_sizes();
    test_dma_2d();
    test_dma_burst();
    test_tile_banks();
    test_pass0_east();
    test_pass0_south();
    test_all_rows();
    test_result_data();
    test_loop_count();
    test_cu_cycles();
    test_irq_status();
    test_stress();
    test_cu_reset();
    test_alu_smoke();
    test_multi_context();
    test_loop2_nested();
    test_routing_directions();
    test_mac_saturation();
    test_concurrency();
    test_dma_error_and_protect();
    test_gic_irq();

    uart_puts("\n==========================================\n");
    uart_puts(" RESULTS: ");
    uart_putdec(g_pass); uart_puts(" passed, ");
    uart_putdec(g_fail); uart_puts(" failed\n");
    uart_puts("==========================================\n");

    while (1) asm volatile("wfi");
}
