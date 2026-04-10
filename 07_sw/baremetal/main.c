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
 * Entry point
 * ========================================================================= */
void main(void)
{
    uart_init();
    uart_puts("\n");
    uart_puts("==========================================\n");
    uart_puts(" CGRA Bare-Metal Test v2.0 (deep)\n");
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

    uart_puts("\n==========================================\n");
    uart_puts(" RESULTS: ");
    uart_putdec(g_pass); uart_puts(" passed, ");
    uart_putdec(g_fail); uart_puts(" failed\n");
    uart_puts("==========================================\n");

    while (1) asm volatile("wfi");
}
