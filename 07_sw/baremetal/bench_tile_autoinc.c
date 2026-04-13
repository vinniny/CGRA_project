/* =========================================================================
 * bench_tile_autoinc.c — Deep Verification + Performance Benchmark
 *                        for TILE_AUTO_INC (CSR 0x78)
 *
 * Part 1: Correctness (43 strict checks, exact golden values)
 *   G1: CSR interface (4)       G6: Multi-row parallel (4)
 *   G2: Basic addressing (4)    G7: MAC accumulation (3)
 *   G3: ISA ops (14)            G8: Nested loops (2)
 *   G4: Routing (4)             G9: Edge cases (5)
 *   G5: SIMD (3)                G10: Conv3x3 + data integrity (2)
 *
 * Part 2: Benchmark (cycle-level breakdown + resolution sweep)
 *   B1: Conv3x3 28x28 with/without auto-inc (DMA/CU/ARM split)
 *   B2: Resolution sweep 8x8..160x80 (with/without, side-by-side)
 *
 * Build: make bench_tai    Run: via XSDB + UART capture
 * ========================================================================= */
#include <stdint.h>
#include "uart.h"
#include "cgra.h"

/* ── Memory ──────────────────────────────────────────────────────────── */
#define DDR_BUF_A    0x00100000UL
#define DDR_BUF_B    0x00140000UL
#define DDR_STAGE    0x00180000UL
#define DDR_IM2COL   0x001C0000UL
#define TILE_BANK0   0x10000000UL
#define TILE_BANK1   0x10001000UL
#define TILE_BANK2   0x10002000UL
#define TILE_BANK3   0x10003000UL

/* ── Power constants ─────────────────────────────────────────────────── */
#define CGRA_POWER_MW   217u
#define PS7_POWER_MW    1532u

/* ── Test tracking ───────────────────────────────────────────────────── */
static int g_pass = 0, g_fail = 0;

static void check(const char *name, int ok, uint32_t got, uint32_t exp)
{
    uart_puts("  ");
    uart_puts(name);
    if (ok) {
        uart_puts("  PASS\n");
        g_pass++;
    } else {
        uart_puts("  FAIL got=");
        uart_putdec(got);
        uart_puts(" exp=");
        uart_putdec(exp);
        uart_putchar('\n');
        g_fail++;
    }
}

/* ── UART helpers ────────────────────────────────────────────────────── */
static void uart_putfix1(uint32_t v10)
{
    uart_putdec(v10 / 10); uart_putchar('.'); uart_putchar('0' + (v10 % 10));
}
static void uart_rj(uint32_t v, int w)
{
    char buf[12]; int len = 0;
    if (v == 0) { buf[len++] = '0'; }
    else { uint32_t t = v; while (t) { buf[len++] = '0' + (t % 10); t /= 10; } }
    for (int i = len; i < w; i++) uart_putchar(' ');
    for (int i = len - 1; i >= 0; i--) uart_putchar(buf[i]);
}
static void uart_lj(const char *s, int w)
{
    const char *p = s; int len = 0;
    while (*p++) len++;
    uart_puts(s);
    for (int i = len; i < w; i++) uart_putchar(' ');
}

/* ── CGRA helpers ────────────────────────────────────────────────────── */
static void cgra_clear_irqs(void) { cgra_wr(CGRA_IRQ_STATUS, 0x7u); }

static int cu_run_wait(void)
{
    cgra_wr(CGRA_CU_CTRL, 1u);
    for (uint32_t t = 0; t < 2000000; t++)
        if (cgra_rd(CGRA_CU_STATUS) & CU_STATUS_DONE) return 0;
    return -1;
}

static void setup(void)
{
    cgra_cu_reset();
    cgra_clear_irqs();
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END, 15);
    cgra_wr(CGRA_LOOP_COUNT, 0);
    cgra_wr(CGRA_LOOP2_START, 0);
    cgra_wr(CGRA_LOOP2_END, 0);
    cgra_wr(CGRA_LOOP2_COUNT, 0);
    cgra_wr(CGRA_TILE_BANK_SEL, 0);
    cgra_tile_auto_inc(0);
    for (uint32_t pe = 0; pe < 16; pe++)
        cgra_config_pe(pe, DDR_STAGE, OP_NOP, 0, 0, 0, 0, 0);
}

static void tile_load_seq(uint32_t bank, uint32_t n, uint32_t base)
{
    volatile uint32_t *d = (volatile uint32_t *)DDR_BUF_A;
    for (uint32_t i = 0; i < n; i++) d[i] = base + i;
    cgra_dma(DDR_BUF_A, bank, n * 4);
}

static void cfg_east_chain(uint32_t row, uint32_t op, uint32_t s0,
                           uint32_t s1, uint16_t imm)
{
    uint32_t b = row * 4;
    cgra_config_pe(b,     DDR_STAGE, op,       s0,    s1, 0, ROUTE_E, imm);
    cgra_config_pe(b + 1, DDR_STAGE, OP_PASS0, SRC_W, 0,  0, ROUTE_E, 0);
    cgra_config_pe(b + 2, DDR_STAGE, OP_PASS0, SRC_W, 0,  0, ROUTE_E, 0);
    cgra_config_pe(b + 3, DDR_STAGE, OP_PASS0, SRC_W, 0,  0, ROUTE_E, 0);
}

static uint32_t read_row(uint32_t r)
{
    static const uint32_t regs[] = {CGRA_RESULT_ROW0, CGRA_RESULT_ROW1,
                                    CGRA_RESULT_ROW2, CGRA_RESULT_ROW3};
    return cgra_rd(regs[r]);
}

/* =====================================================================
 * PART 1: CORRECTNESS (strict exact golden values)
 * ===================================================================== */

/* ── G1: CSR Interface ───────────────────────────────────────────────── */
static void test_g1(void)
{
    uint32_t rd;
    uart_puts("\n=== G1: CSR Interface ===\n");
    setup();
    cgra_wr(CGRA_TILE_AUTO_INC, 1);
    rd = cgra_rd(CGRA_TILE_AUTO_INC);
    check("T01: Write 1 readback", rd == 1, rd, 1);

    cgra_wr(CGRA_TILE_AUTO_INC, 0);
    rd = cgra_rd(CGRA_TILE_AUTO_INC);
    check("T02: Write 0 readback", rd == 0, rd, 0);

    cgra_wr(CGRA_TILE_AUTO_INC, 1);
    cgra_wr(CGRA_LOOP_COUNT, 200);
    cgra_wr(CGRA_CU_CTRL, 1);
    for (volatile int i = 0; i < 100; i++) asm volatile("nop");
    cgra_wr(CGRA_TILE_AUTO_INC, 0);
    rd = cgra_rd(CGRA_TILE_AUTO_INC);
    check("T03: Write-protect busy", rd == 1, rd, 1);
    cgra_wr(CGRA_CU_CTRL, 2);
    for (volatile int i = 0; i < 100; i++) asm volatile("nop");
    cgra_wr(CGRA_CU_CTRL, 0);
    cgra_wr(CGRA_TILE_AUTO_INC, 0);
    rd = cgra_rd(CGRA_TILE_AUTO_INC);
    check("T04: Write after stop", rd == 0, rd, 0);
}

/* ── G2: Basic Addressing ────────────────────────────────────────────── */
static void test_g2(void)
{
    uint32_t rd;
    uart_puts("\n=== G2: Basic Addressing ===\n");

    /* tile[i] = 100+i for addr 0-31 */
    setup(); tile_load_seq(TILE_BANK0, 256, 100);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);

    /* T05: Legacy */
    cgra_wr(CGRA_LOOP_COUNT, 1); cgra_tile_auto_inc(0);
    cu_run_wait();
    rd = read_row(0);
    check("T05: Legacy 2-pass", rd == 104, rd, 104);

    /* T06: Auto-inc 2 pass */
    setup(); tile_load_seq(TILE_BANK0, 256, 100);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_COUNT, 1); cgra_tile_auto_inc(1);
    cu_run_wait(); rd = read_row(0);
    check("T06: Auto-inc 2-pass", rd == 120, rd, 120);

    /* T07: 4 pass */
    setup(); tile_load_seq(TILE_BANK0, 256, 0);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_COUNT, 3); cgra_tile_auto_inc(1);
    cu_run_wait(); rd = read_row(0);
    check("T07: Auto-inc 4-pass", rd == 52, rd, 52);

    /* T08: 16 pass */
    setup(); tile_load_seq(TILE_BANK0, 256, 0);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_COUNT, 15); cgra_tile_auto_inc(1);
    cu_run_wait(); rd = read_row(0);
    check("T08: Auto-inc 16-pass", rd == 244, rd, 244);
    cgra_tile_auto_inc(0);
}

/* ── G3: ISA Ops ─────────────────────────────────────────────────────── */
static void test_g3(void)
{
    uart_puts("\n=== G3: ISA Ops Through Auto-Inc ===\n");
    /* tile[i]=(i+1)*10. 2 passes, auto-inc. Pipeline captures tile[20]=210. */
    static const struct {
        const char *n; uint32_t op, s0, s1; uint16_t imm; uint32_t exp;
    } t[] = {
        {"ADD",    OP_ADD,    SRC_W, SRC_IMM, 5,    215},
        {"SUB",    OP_SUB,    SRC_W, SRC_IMM, 5,    205},
        {"MUL",    OP_MUL,    SRC_W, SRC_IMM, 2,    420},
        {"AND",    OP_AND,    SRC_W, SRC_IMM, 0xFF, 210 & 0xFF},
        {"OR",     OP_OR,     SRC_W, SRC_IMM, 0xF00, 210 | 0xF00},
        {"XOR",    OP_XOR,    SRC_W, SRC_IMM, 0xFF, 210 ^ 0xFF},
        {"SHL",    OP_SHL,    SRC_W, SRC_IMM, 1,    420},
        {"SHR",    OP_SHR,    SRC_W, SRC_IMM, 1,    105},
        {"CMP_GT", OP_CMP_GT, SRC_W, SRC_IMM, 200,  1},
        {"CMP_LT", OP_CMP_LT, SRC_W, SRC_IMM, 200,  0},
        {"CMP_EQ", OP_CMP_EQ, SRC_W, SRC_IMM, 210,  1},
        {"PASS0",  OP_PASS0,  SRC_W, 0,       0,    210},
        {"RELU",   OP_RELU,   SRC_W, 0,       0,    210},
        {"MAX",    OP_MAX,    SRC_W, SRC_IMM, 100,  210},
    };
    for (int i = 0; i < 14; i++) {
        setup();
        volatile uint32_t *d = (volatile uint32_t *)DDR_BUF_A;
        for (uint32_t j = 0; j < 32; j++) d[j] = (j + 1) * 10;
        cgra_dma(DDR_BUF_A, TILE_BANK0, 128);
        cfg_east_chain(0, t[i].op, t[i].s0, t[i].s1, t[i].imm);
        cgra_wr(CGRA_LOOP_COUNT, 1); cgra_tile_auto_inc(1);
        cu_run_wait();
        uint32_t rd = read_row(0);
        check(t[i].n, rd == t[i].exp, rd, t[i].exp);
        cgra_tile_auto_inc(0);
    }
}

/* ── G4: Routing ─────────────────────────────────────────────────────── */
static void test_g4(void)
{
    uint32_t rd;
    uart_puts("\n=== G4: Routing ===\n");

    /* T30: East */
    setup(); tile_load_seq(TILE_BANK0, 32, 100);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_COUNT, 1); cgra_tile_auto_inc(1);
    cu_run_wait(); rd = read_row(0);
    check("T30: East", rd == 120, rd, 120);

    /* T31: South */
    setup(); tile_load_seq(TILE_BANK0, 32, 100);
    cgra_config_pe(0, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_S, 0);
    cgra_config_pe(4, DDR_STAGE, OP_PASS0, SRC_N, 0, 0, ROUTE_E, 0);
    cgra_config_pe(5, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(6, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(7, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_wr(CGRA_LOOP_COUNT, 1); cgra_tile_auto_inc(1);
    cu_run_wait(); rd = read_row(1);
    check("T31: South", rd == 117, rd, 117);

    /* T32: North */
    setup(); tile_load_seq(TILE_BANK1, 32, 200);
    cgra_config_pe(5, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_N, 0);
    cgra_config_pe(1, DDR_STAGE, OP_PASS0, SRC_S, 0, 0, ROUTE_E, 0);
    cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(3, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_wr(CGRA_LOOP_COUNT, 1); cgra_tile_auto_inc(1);
    cu_run_wait(); rd = read_row(0);
    check("T32: North", rd == 126, rd, 126);

    /* T33: Multicast N+E+S */
    setup(); tile_load_seq(TILE_BANK1, 32, 300);
    cgra_config_pe(5, DDR_STAGE, OP_PASS0, SRC_W, 0, 0,
                   ROUTE_N | ROUTE_E | ROUTE_S, 0);
    cgra_config_pe(6, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(7, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(1, DDR_STAGE, OP_PASS0, SRC_S, 0, 0, ROUTE_E, 0);
    cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(3, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(9,  DDR_STAGE, OP_PASS0, SRC_N, 0, 0, ROUTE_E, 0);
    cgra_config_pe(10, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(11, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_wr(CGRA_LOOP_COUNT, 1); cgra_tile_auto_inc(1);
    cu_run_wait();
    uint32_t r0 = read_row(0), r1 = read_row(1), r2 = read_row(2);
    check("T33: Mcast", r0 == 126 && r1 == 126 && r2 == 126,
          r0, 126);
    cgra_tile_auto_inc(0);
}

/* ── G5: SIMD ────────────────────────────────────────────────────────── */
static void test_g5(void)
{
    uart_puts("\n=== G5: SIMD ===\n");
    static const struct { const char *n; uint32_t m; uint16_t imm; uint32_t exp; } t[] = {
        {"INT32",   DATA_MODE_INT32,   1,      13},
        {"INT16x2", DATA_MODE_INT16X2, 1,      13},
        {"INT8x4",  DATA_MODE_INT8X4,  0x0101, 26},
    };
    for (int i = 0; i < 3; i++) {
        setup();
        cgra_config_pe_slot_ex(3, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0, t[i].m);
        for (int s = 1; s < 16; s++)
            cgra_config_pe_slot_ex(3, (uint32_t)s, DDR_STAGE,
                                    OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E, t[i].imm, t[i].m);
        cgra_wr(CGRA_LOOP_COUNT, 1); cgra_tile_auto_inc(1);
        cu_run_wait();
        uint32_t rd = read_row(0);
        check(t[i].n, rd == t[i].exp, rd, t[i].exp);
        cgra_tile_auto_inc(0);
    }
}

/* ── G6: Multi-Row ───────────────────────────────────────────────────── */
static void test_g6(void)
{
    uart_puts("\n=== G6: Multi-Row ===\n");
    setup();
    tile_load_seq(TILE_BANK0, 64, 1000);
    tile_load_seq(TILE_BANK1, 64, 2000);
    tile_load_seq(TILE_BANK2, 64, 3000);
    tile_load_seq(TILE_BANK3, 64, 4000);
    for (uint32_t r = 0; r < 4; r++) cfg_east_chain(r, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_COUNT, 3); cgra_tile_auto_inc(1);
    cu_run_wait();
    uint32_t r0=read_row(0), r1=read_row(1), r2=read_row(2), r3=read_row(3);
    check("T37a: Bank0", r0 == 1052, r0, 1052);
    check("T37b: Bank1", r1 == 2052, r1, 2052);
    check("T37c: Bank2", r2 == 3052, r2, 3052);
    check("T37d: Bank3", r3 == 4052, r3, 4052);
    cgra_tile_auto_inc(0);
}

/* ── G7: MAC Accumulation ────────────────────────────────────────────── */
static void test_g7(void)
{
    uart_puts("\n=== G7: MAC Accumulation ===\n");

    /* T41: ACC_CLR resets each iter (slot 0 inside loop) */
    setup();
    cgra_config_pe_slot(3, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
    for (int s = 1; s < 16; s++)
        cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE,
                            OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E, 1);
    cgra_wr(CGRA_LOOP_COUNT, 3); cgra_tile_auto_inc(1);
    cu_run_wait();
    uint32_t rd = read_row(0);
    check("T41: Per-iter MAC", rd == 13, rd, 13);

    /* T42: Cross-iter accumulation (LOOP_START=1 skips ACC_CLR) */
    setup();
    cgra_config_pe_slot(3, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
    for (int s = 1; s < 16; s++)
        cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE,
                            OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E, 1);
    cgra_wr(CGRA_LOOP_START, 1); cgra_wr(CGRA_LOOP_END, 15);
    cgra_wr(CGRA_LOOP_COUNT, 3); cgra_tile_auto_inc(1);
    cu_run_wait(); rd = read_row(0);
    check("T42: Cross-iter", rd == 58, rd, 58);

    /* T43: Monotonic — 8 iters > 4 iters */
    setup();
    cgra_config_pe_slot(3, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
    for (int s = 1; s < 16; s++)
        cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE,
                            OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E, 1);
    cgra_wr(CGRA_LOOP_START, 1); cgra_wr(CGRA_LOOP_END, 15);
    cgra_wr(CGRA_LOOP_COUNT, 7); cgra_tile_auto_inc(1);
    cu_run_wait();
    uint32_t rd8 = read_row(0);
    check("T43: 8-iter > 4-iter", rd8 > 58, rd8, 58);
    cgra_tile_auto_inc(0);
}

/* ── G8: Nested Loops ────────────────────────────────────────────────── */
static void test_g8(void)
{
    uart_puts("\n=== G8: Nested Loops ===\n");
    setup(); tile_load_seq(TILE_BANK0, 256, 0);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_COUNT, 1); cgra_wr(CGRA_LOOP2_COUNT, 1);
    cgra_tile_auto_inc(1); cu_run_wait();
    uint32_t rd = read_row(0);
    check("T44: Nested 2x2", rd == 52, rd, 52);

    setup(); tile_load_seq(TILE_BANK0, 256, 0);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_COUNT, 2); cgra_wr(CGRA_LOOP2_COUNT, 1);
    cgra_tile_auto_inc(1); cu_run_wait();
    rd = read_row(0);
    check("T45: Nested 3x2", rd == 84, rd, 84);
    cgra_tile_auto_inc(0);
}

/* ── G9: Edge Cases ──────────────────────────────────────────────────── */
static void test_g9(void)
{
    uint32_t rd;
    uart_puts("\n=== G9: Edge Cases ===\n");

    setup(); tile_load_seq(TILE_BANK0, 32, 100);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_COUNT, 0); cgra_tile_auto_inc(1);
    cu_run_wait(); rd = read_row(0);
    check("T46: No loop", rd == 104, rd, 104);

    setup(); tile_load_seq(TILE_BANK0, 512, 0);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_COUNT, 31); cgra_tile_auto_inc(1);
    cu_run_wait(); rd = read_row(0);
    check("T47: 32 passes", rd == 500, rd, 500);

    setup(); tile_load_seq(TILE_BANK0, 64, 0);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_START, 5); cgra_wr(CGRA_LOOP_END, 5);
    cgra_wr(CGRA_LOOP_COUNT, 3); cgra_tile_auto_inc(1);
    cu_run_wait(); rd = read_row(0);
    check("T48: Single-slot", rd == 37, rd, 37);

    /* T49: OFF then ON */
    setup(); tile_load_seq(TILE_BANK0, 32, 100);
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_tile_auto_inc(0); cgra_wr(CGRA_LOOP_COUNT, 1);
    cu_run_wait();
    uint32_t rd_off = read_row(0);
    check("T49a: OFF", rd_off == 104, rd_off, 104);

    cgra_cu_reset(); cgra_tile_auto_inc(1);
    cgra_wr(CGRA_LOOP_START, 0); cgra_wr(CGRA_LOOP_END, 15);
    cgra_wr(CGRA_LOOP_COUNT, 1);
    cu_run_wait();
    uint32_t rd_on = read_row(0);
    check("T49b: ON", rd_on == 120, rd_on, 120);
    cgra_tile_auto_inc(0);
}

/* ── G10: Data Integrity ─────────────────────────────────────────────── */
static void test_g10(void)
{
    uart_puts("\n=== G10: Data Integrity ===\n");

    /* Load 256 known values to tile bank 0, run auto-inc pass,
     * then DMA tile memory BACK to DDR and verify every word */
    setup();
    volatile uint32_t *src = (volatile uint32_t *)DDR_BUF_A;
    volatile uint32_t *dst = (volatile uint32_t *)DDR_BUF_B;
    for (uint32_t i = 0; i < 256; i++) src[i] = 0xCAFE0000 | i;
    cgra_dma(DDR_BUF_A, TILE_BANK0, 1024);

    /* Run auto-inc pass (reads tile but doesn't modify it) */
    cfg_east_chain(0, OP_PASS0, SRC_W, 0, 0);
    cgra_wr(CGRA_LOOP_COUNT, 15); cgra_tile_auto_inc(1);
    cu_run_wait(); cgra_tile_auto_inc(0);

    /* DMA tile bank 0 back to DDR_BUF_B */
    for (uint32_t i = 0; i < 256; i++) dst[i] = 0xDEADBEEF;
    cgra_dma(TILE_BANK0, DDR_BUF_B, 1024);

    /* Verify every word */
    uint32_t mismatches = 0;
    for (uint32_t i = 0; i < 256; i++) {
        if (dst[i] != (0xCAFE0000 | i)) {
            mismatches++;
            if (mismatches <= 3) {
                uart_puts("    mismatch addr="); uart_putdec(i);
                uart_puts(" got="); uart_puthex(dst[i]);
                uart_puts(" exp="); uart_puthex(0xCAFE0000 | i);
                uart_putchar('\n');
            }
        }
    }
    check("T50: Tile integrity 256w", mismatches == 0, mismatches, 0);

    /* T51: Conv3x3 data flow */
    static const int32_t img[5][5] = {
        {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25}};
    volatile uint32_t *d = (volatile uint32_t *)DDR_BUF_A;
    for (int oy = 0; oy < 3; oy++)
        for (int ox = 0; ox < 3; ox++) {
            int idx = (oy * 3 + ox) * 16;
            for (int ky = 0; ky < 3; ky++)
                for (int kx = 0; kx < 3; kx++)
                    d[idx + ky * 3 + kx] = (uint32_t)img[oy + ky][ox + kx];
            for (int i = 9; i < 16; i++) d[idx + i] = 0;
        }
    cgra_dma(DDR_BUF_A, TILE_BANK0, 144 * 4);
    setup();
    cgra_config_pe(0, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(1, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe_slot(3, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
    for (int s = 1; s <= 9; s++)
        cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE,
                            OP_MAC, SRC_W, SRC_IMM, 0, ROUTE_E, 1);
    for (int s = 10; s < 16; s++)
        cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE,
                            OP_NOP, 0, 0, 0, ROUTE_E, 0);
    cgra_wr(CGRA_LOOP_COUNT, 8); cgra_tile_auto_inc(1);
    cu_run_wait();
    uint32_t rd = read_row(0);
    check("T51: Conv3x3 flow", rd == 37, rd, 37);
    cgra_tile_auto_inc(0);
}

/* =====================================================================
 * PART 2: BENCHMARK (cycle-level breakdown + resolution sweep)
 * ===================================================================== */

static void cfg_conv3x3_pe(void)
{
    cgra_config_pe(0, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(1, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    cgra_config_pe_slot(3, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
    for (int s = 1; s <= 9; s++)
        cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE,
                            OP_MAC, SRC_W, SRC_IMM, 0, ROUTE_E, 1);
    for (int s = 10; s < 16; s++)
        cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE,
                            OP_NOP, 0, 0, 0, ROUTE_E, 0);
}

/* Prepare im2col in DDR for given image size */
static uint32_t prep_im2col(uint32_t h, uint32_t w)
{
    volatile uint32_t *img = (volatile uint32_t *)DDR_BUF_A;
    volatile uint32_t *im2col = (volatile uint32_t *)DDR_IM2COL;
    for (uint32_t i = 0; i < h * w; i++) img[i] = (i * 7 + 13) & 0xFF;
    uint32_t oh = h - 2, ow = w - 2, n = oh * ow;
    for (uint32_t oy = 0; oy < oh; oy++)
        for (uint32_t ox = 0; ox < ow; ox++) {
            uint32_t idx = (oy * ow + ox) * 16;
            for (int ky = 0; ky < 3; ky++)
                for (int kx = 0; kx < 3; kx++)
                    im2col[idx + ky * 3 + kx] = img[(oy + (uint32_t)ky) * w + (ox + (uint32_t)kx)];
            for (int i = 9; i < 16; i++) im2col[idx + i] = 0;
        }
    return n;
}

/* Run Conv3x3 WITHOUT auto-inc (per-pixel DMA) */
static void bench_no_autoinc(uint32_t h, uint32_t w,
                              uint32_t *out_total, uint32_t *out_dma,
                              uint32_t *out_cu)
{
    volatile uint32_t *patch = (volatile uint32_t *)(DDR_STAGE + 1024);
    volatile uint32_t *img = (volatile uint32_t *)DDR_BUF_A;
    uint32_t oh = h - 2, ow = w - 2;
    uint32_t dma_cyc = 0, cu_cyc = 0, t0, t1;

    setup(); cfg_conv3x3_pe();
    arm_ccnt_reset();
    uint32_t total_t0 = arm_ccnt_read();

    for (uint32_t oy = 0; oy < oh; oy++) {
        for (uint32_t ox = 0; ox < ow; ox++) {
            for (int ky = 0; ky < 3; ky++)
                for (int kx = 0; kx < 3; kx++)
                    patch[ky * 3 + kx] = img[(oy + (uint32_t)ky) * w + (ox + (uint32_t)kx)];
            for (int i = 9; i < 16; i++) patch[i] = 0;
            t0 = arm_ccnt_read();
            cgra_dma(DDR_STAGE + 1024, TILE_BANK0, 64);
            t1 = arm_ccnt_read();
            dma_cyc += t1 - t0;
            t0 = arm_ccnt_read();
            cgra_cu_reset(); cu_run_wait();
            t1 = arm_ccnt_read();
            cu_cyc += t1 - t0;
        }
    }

    uint32_t total_t1 = arm_ccnt_read();
    *out_total = total_t1 - total_t0;
    *out_dma = dma_cyc;
    *out_cu = cu_cyc;
}

/* Run Conv3x3 WITH auto-inc (bulk DMA) */
static void bench_with_autoinc(uint32_t h, uint32_t w,
                                uint32_t *out_total, uint32_t *out_dma,
                                uint32_t *out_cu)
{
    uint32_t oh = h - 2, ow = w - 2, n = oh * ow;
    uint32_t dma_cyc = 0, cu_cyc = 0, t0, t1;

    setup(); cfg_conv3x3_pe();
    arm_ccnt_reset();
    uint32_t total_t0 = arm_ccnt_read();

    uint32_t per_bulk = 256;
    uint32_t n_bulks = (n + per_bulk - 1) / per_bulk;

    for (uint32_t b = 0; b < n_bulks; b++) {
        uint32_t start = b * per_bulk;
        uint32_t cnt = per_bulk;
        if (start + cnt > n) cnt = n - start;

        t0 = arm_ccnt_read();
        cgra_dma(DDR_IM2COL + start * 64, TILE_BANK0, cnt * 64);
        t1 = arm_ccnt_read();
        dma_cyc += t1 - t0;

        cgra_cu_reset();
        cgra_wr(CGRA_LOOP_START, 0); cgra_wr(CGRA_LOOP_END, 15);
        cgra_wr(CGRA_LOOP_COUNT, cnt - 1);
        cgra_tile_auto_inc(1);
        t0 = arm_ccnt_read();
        cu_run_wait();
        t1 = arm_ccnt_read();
        cu_cyc += t1 - t0;
        cgra_tile_auto_inc(0);
    }

    uint32_t total_t1 = arm_ccnt_read();
    *out_total = total_t1 - total_t0;
    *out_dma = dma_cyc;
    *out_cu = cu_cyc;
}

static void bench_detailed(void)
{
    uart_puts("\n=== Benchmark: Conv3x3 28x28 Detailed ===\n");

    uint32_t h = 28, w = 28, n = 26 * 26;
    prep_im2col(h, w);

    uint32_t old_total, old_dma, old_cu;
    bench_no_autoinc(h, w, &old_total, &old_dma, &old_cu);
    uint32_t old_arm = old_total - old_dma - old_cu;

    uint32_t new_total, new_dma, new_cu;
    bench_with_autoinc(h, w, &new_total, &new_dma, &new_cu);
    uint32_t new_arm = new_total - new_dma - new_cu;

    uart_puts("                  Per-pixel DMA     Auto-inc bulk\n");
    uart_puts("Total ARM_CYC:  ");
    uart_rj(old_total, 12); uart_puts("    "); uart_rj(new_total, 12); uart_putchar('\n');
    uart_puts("  DMA cycles:   ");
    uart_rj(old_dma, 12); uart_puts("    "); uart_rj(new_dma, 12); uart_putchar('\n');
    uart_puts("  CU cycles:    ");
    uart_rj(old_cu, 12); uart_puts("    "); uart_rj(new_cu, 12); uart_putchar('\n');
    uart_puts("  ARM overhead: ");
    uart_rj(old_arm, 12); uart_puts("    "); uart_rj(new_arm, 12); uart_putchar('\n');

    /* Derived metrics */
    uint32_t old_ms_x10 = (old_total / 1000) * 15 / 10;
    uint32_t new_ms_x10 = (new_total / 1000) * 15 / 10;
    uint32_t old_fps_x10 = (old_total > 100) ? 66667000u / (old_total / 10) : 0;
    uint32_t new_fps_x10 = (new_total > 100) ? 66667000u / (new_total / 10) : 0;
    uint32_t speedup_x10 = (new_total > 0) ? (old_total * 10) / new_total : 0;
    /* Per-pixel: us*10 = arm_cyc * 15 / (n * 1000) */
    uint32_t old_perpix_x10 = (old_total / n) * 15 / 100;
    uint32_t new_perpix_x10 = (new_total / n) * 15 / 100;
    /* MACs: n * 9 (each output = 9 MACs for box filter) */
    uint32_t total_macs = n * 9;
    uint32_t old_mmacs_x10 = (old_total > 0) ? (total_macs * 6667) / (old_total / 10) : 0;
    uint32_t new_mmacs_x10 = (new_total > 0) ? (total_macs * 6667) / (new_total / 10) : 0;

    uart_puts("\nTotal ms:       ");
    uart_putfix1(old_ms_x10); uart_puts("            ");
    uart_putfix1(new_ms_x10); uart_putchar('\n');
    uart_puts("FPS:            ");
    uart_putfix1(old_fps_x10); uart_puts("            ");
    uart_putfix1(new_fps_x10); uart_putchar('\n');
    uart_puts("Per-pixel us:   ");
    uart_putfix1(old_perpix_x10); uart_puts("            ");
    uart_putfix1(new_perpix_x10); uart_putchar('\n');
    uart_puts("MMAC/s:         ");
    uart_putfix1(old_mmacs_x10); uart_puts("            ");
    uart_putfix1(new_mmacs_x10); uart_putchar('\n');
    uart_puts("Speedup:        "); uart_putfix1(speedup_x10); uart_puts("x\n");

    /* GOPS/W */
    uint32_t new_gopsw_x10 = (new_mmacs_x10 * 100) / CGRA_POWER_MW;
    uart_puts("CGRA MMAC/s/W:  "); uart_putfix1(new_gopsw_x10); uart_putchar('\n');
}

static void bench_resolution_sweep(void)
{
    uart_puts("\n=== Resolution Sweep: Conv3x3 w/ vs w/o Auto-Inc ===\n");
    uart_puts("Res       OutPix  Old_ms  Old_FPS  New_ms  New_FPS  Speedup\n");

    static const struct { const char *n; uint32_t h, w; } res[] = {
        {"8x8",    8,  8},  {"16x16", 16, 16}, {"28x28", 28, 28},
        {"64x64", 64, 64},  {"160x80",160,80},
    };

    for (int i = 0; i < 5; i++) {
        uint32_t h = res[i].h, w = res[i].w;
        if (h < 3 || w < 3) continue;
        uint32_t n = (h - 2) * (w - 2);
        prep_im2col(h, w);

        uint32_t ot, od, oc, nt, nd, nc;
        bench_no_autoinc(h, w, &ot, &od, &oc);
        bench_with_autoinc(h, w, &nt, &nd, &nc);

        uint32_t oms = (ot / 1000) * 15 / 10;
        uint32_t nms = (nt / 1000) * 15 / 10;
        uint32_t ofps = (ot > 100) ? 66667000u / (ot / 10) : 0;
        uint32_t nfps = (nt > 100) ? 66667000u / (nt / 10) : 0;
        uint32_t sp = (nt > 0) ? (ot * 10) / nt : 0;

        uart_lj(res[i].n, 10);
        uart_rj(n, 6); uart_puts("  ");
        uart_putfix1(oms); uart_puts("  ");
        uart_putfix1(ofps); uart_puts("  ");
        uart_putfix1(nms); uart_puts("  ");
        uart_putfix1(nfps); uart_puts("  ");
        uart_putfix1(sp); uart_puts("x\n");
    }
}

/* =====================================================================
 * Entry
 * ===================================================================== */
void main(void)
{
    uart_init();
    arm_pmu_enable();
    uart_puts("\n==========================================\n");
    uart_puts(" CGRA Tile Auto-Inc Deep Verification\n");
    uart_puts(" Zynq-7000 XC7Z020 / 4x4 CGRA @ 50 MHz\n");
    uart_puts("==========================================\n");

    test_g1(); test_g2(); test_g3(); test_g4(); test_g5();
    test_g6(); test_g7(); test_g8(); test_g9(); test_g10();

    uart_puts("\n==========================================\n");
    uart_puts(" RESULTS: ");
    uart_putdec((uint32_t)g_pass); uart_puts(" passed, ");
    uart_putdec((uint32_t)g_fail); uart_puts(" failed\n");
    uart_puts("==========================================\n");

    if (g_fail == 0) {
        bench_detailed();
        bench_resolution_sweep();
    } else {
        uart_puts("\nSkipping benchmark -- correctness failed.\n");
    }

    uart_puts("\n[TILE AUTO-INC DEEP VERIFICATION COMPLETE]\n");
    while (1) asm volatile("wfi");
}
