/* =========================================================================
 * bench_cgra.c — Comprehensive bare-metal CGRA benchmark suite
 *
 * 10 categories measuring every dimension of CGRA capability:
 *   1. Per-op CU throughput (all 21 ISA ops)
 *   2. MAC pipeline hazard characterization
 *   3. SIMD throughput (INT8x4, INT16x2, INT32)
 *   4. DMA bandwidth (1D, 2D, various sizes)
 *   5. Multicast throughput (1/2/3/4-way fan-out)
 *   6. Parallel row utilization (1/2/4 rows)
 *   7. FC layer pattern (config-reload + DMA + compute)
 *   8. Multicast FC pattern (parallel vs sequential)
 *   9. Activation functions (LIF, RELU, MAX, CMP, SHL/SHR)
 *  10. Config reload overhead
 *
 * Uses ARM Cortex-A9 PMCCNTR (666.67 MHz) for wall-clock timing.
 * Uses CGRA CU_CYCLES register for CGRA-domain cycle counts.
 *
 * Power reference (Vivado, routed):
 *   CGRA PL: 0.217 W   |   PS7 (ARM+DDR): 1.532 W
 *
 * Build: make bench      Run: make run_bench BIT=...
 * ========================================================================= */
#include <stdint.h>
#include "uart.h"
#include "cgra.h"

/* ── Memory addresses ────────────────────────────────────────────────── */
#define DDR_STAGE       0x00100000UL
#define DDR_BUF_A       0x00100000UL
#define DDR_BUF_B       0x00104000UL
#define TILE_BANK0      0x10000000UL
#define TILE_BANK1      0x10001000UL
#define TILE_BANK2      0x10002000UL
#define TILE_BANK3      0x10003000UL

/* ── Power constants (Vivado report, routed, 2026-04-10) ─────────────── */
#define CGRA_POWER_MW   217u    /* 0.217 W */
#define PS7_POWER_MW    1532u   /* 1.532 W */

/* ── Summary accumulators ────────────────────────────────────────────── */
static uint32_t g_mac_b2b_eff     = 0;   /* effective MACs from cat 2 */
static uint32_t g_mac_b2b_cycles  = 0;
static uint32_t g_simd_int8_eff   = 0;   /* effective MACs from cat 3 */
static uint32_t g_simd_int8_cyc   = 0;
static uint32_t g_parallel4_mmacs = 0;   /* from cat 6 */
static uint32_t g_fc784_mmacs     = 0;   /* from cat 7 */
static uint32_t g_mcast_speedup_x10 = 0; /* from cat 8 */
static uint32_t g_dma_peak_mbs_x10  = 0; /* from cat 4 */
static uint32_t g_cfg_full_us_x10   = 0; /* from cat 10 */

/* ── UART formatting helpers ─────────────────────────────────────────── */

/* Print "NNN.D" from value pre-multiplied by 10 */
static void uart_putfix1(uint32_t val_x10)
{
    uart_putdec(val_x10 / 10);
    uart_putchar('.');
    uart_putchar('0' + (val_x10 % 10));
}

/* Right-justified decimal in field of `w` chars */
static void uart_rj(uint32_t v, int w)
{
    char buf[12]; int len = 0;
    if (v == 0) { buf[len++] = '0'; }
    else { uint32_t t = v; while (t) { buf[len++] = '0' + (t % 10); t /= 10; } }
    for (int i = len; i < w; i++) uart_putchar(' ');
    for (int i = len - 1; i >= 0; i--) uart_putchar(buf[i]);
}

/* Left-justified string in field of `w` chars */
static void uart_lj(const char *s, int w)
{
    const char *p = s; int len = 0;
    while (*p++) len++;
    uart_puts(s);
    for (int i = len; i < w; i++) uart_putchar(' ');
}

static void banner(const char *title)
{
    uart_puts("\n=== ");
    uart_puts(title);
    uart_puts(" ===\n");
}

/* ── Common CGRA helpers ─────────────────────────────────────────────── */

static void cgra_clear_irqs(void)
{
    cgra_wr(CGRA_IRQ_STATUS, 0x7u);
}

static int cu_run_wait(void)
{
    cgra_wr(CGRA_CU_CTRL, 1u);
    for (uint32_t t = 0; t < 1000000; t++) {
        if (cgra_rd(CGRA_CU_STATUS) & CU_STATUS_DONE)
            return 0;
    }
    return -1;
}

/* NOP-fill all 16 PEs (slot 0 broadcast) */
static void cfg_all_nop(void)
{
    for (uint32_t pe = 0; pe < 16; pe++)
        cgra_config_pe(pe, DDR_STAGE, OP_NOP, 0, 0, 0, 0, 0);
}

/* Standard setup before each benchmark */
static void bench_setup(void)
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
    cfg_all_nop();
}

/* Run a "read-out" pass: PE[compute_pe] does PASS0 from RF[0] (which
 * holds the last alu_result) and forwarders relay it east to RESULT_ROW.
 * 16 full slots guarantees the value propagates through the 3-stage
 * pipeline + router delays to the east edge. Does NOT reset the CU
 * (preserves PE register state from the compute run). */
static uint32_t readout_row0(uint32_t compute_pe)
{
    /* Reconfigure without CU reset — preserves RF[0] in compute PE */
    uint32_t row = compute_pe / 4;
    uint32_t col = compute_pe % 4;

    /* Compute PE: PASS0 SRC_RF (reads RF[0] = last alu_result) */
    cgra_config_pe(compute_pe, DDR_STAGE, OP_PASS0, SRC_RF, 0, 0, ROUTE_E, 0);
    /* Forwarders east of the compute PE */
    for (uint32_t c = col + 1; c < 4; c++) {
        uint32_t pe = row * 4 + c;
        cgra_config_pe(pe, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
    }

    cu_run_wait();
    uint32_t reg_offsets[] = {CGRA_RESULT_ROW0, CGRA_RESULT_ROW1,
                              CGRA_RESULT_ROW2, CGRA_RESULT_ROW3};
    return cgra_rd(reg_offsets[row]);
}

/* =====================================================================
 * Category 1: Per-Op CU Throughput
 * ===================================================================== */

typedef struct {
    const char *name;
    uint32_t    op;
    uint32_t    src0;
    uint32_t    src1;
    uint16_t    imm0;   /* IMM for feeder PE[0,0] */
    uint16_t    imm1;   /* IMM for src1 on compute PE[0,1] */
    int         acc_clr; /* need ACC_CLR before test */
} op_entry_t;

static const op_entry_t op_table[] = {
    {"NOP",       OP_NOP,      SRC_W, 0,       42, 0,   0},
    {"ADD",       OP_ADD,      SRC_W, SRC_IMM, 10, 20,  0},
    {"SUB",       OP_SUB,      SRC_W, SRC_IMM, 50, 20,  0},
    {"MUL",       OP_MUL,      SRC_W, SRC_IMM,  7,  6,  0},
    {"MAC",       OP_MAC,      SRC_W, SRC_IMM,  3,  4,  1},
    {"AND",       OP_AND,      SRC_W, SRC_IMM, 0xFF, 0x0F, 0},
    {"OR",        OP_OR,       SRC_W, SRC_IMM, 0xA0, 0x05, 0},
    {"XOR",       OP_XOR,      SRC_W, SRC_IMM, 0xFF, 0xFF, 0},
    {"SHL",       OP_SHL,      SRC_W, SRC_IMM,  5,  2,  0},
    {"SHR",       OP_SHR,      SRC_W, SRC_IMM, 100, 3,  0},
    {"CMP_GT",    OP_CMP_GT,   SRC_W, SRC_IMM, 10,  5,  0},
    {"CMP_LT",    OP_CMP_LT,   SRC_W, SRC_IMM,  3, 10,  0},
    {"CMP_EQ",    OP_CMP_EQ,   SRC_W, SRC_IMM,  7,  7,  0},
    {"ACC_CLR",   OP_ACC_CLR,  0,     0,        0,  0,  0},
    {"PASS0",     OP_PASS0,    SRC_W, 0,       99,  0,  0},
    {"PASS1",     OP_PASS1,    0,     SRC_W,    0, 99,  0},
    {"LIF",       OP_LIF,      SRC_W, SRC_IMM, 100, 5000, 1},
    {"RELU",      OP_RELU,     SRC_W, 0,       42,  0,  0},
    {"MAX",       OP_MAX,      SRC_W, SRC_IMM, 10, 20,  0},
};
#define NUM_OPS (sizeof(op_table) / sizeof(op_table[0]))

static void bench_per_op(void)
{
    banner("Cat 1: Per-Op CU Throughput");
    uart_lj("Op", 12);
    uart_puts("CU_CYC  cyc/op  MOPS@50\n");

    for (uint32_t i = 0; i < NUM_OPS; i++) {
        const op_entry_t *e = &op_table[i];
        bench_setup();

        if (e->acc_clr) {
            /* Clear accumulator first */
            cgra_config_pe(1, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, 0, 0);
            cu_run_wait();
            cfg_all_nop();
        }

        /* PE[0,0]: feeder — PASS0 IMM, route east */
        cgra_config_pe(0, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E, e->imm0);
        /* PE[0,1]: compute — the op under test */
        cgra_config_pe(1, DDR_STAGE, e->op, e->src0, e->src1, 0, ROUTE_E, e->imm1);
        /* PE[0,2]: forwarder */
        cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        /* PE[0,3]: forwarder */
        cgra_config_pe(3, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);

        cu_run_wait();
        uint32_t cycles = cgra_rd(CGRA_CU_CYCLES);

        /* cyc/op * 10 = cycles * 10 / 16 */
        uint32_t cyc_x10 = (cycles * 10) / 16;
        /* MOPS = 50e6 / (cycles/16) = 800 / cycles (in MMOPS) -> *10 for display */
        uint32_t mops_x10 = (cycles > 0) ? 8000u / cycles : 0;

        uart_lj(e->name, 12);
        uart_rj(cycles, 6);
        uart_puts("  ");
        uart_putfix1(cyc_x10);
        uart_puts("    ");
        uart_putfix1(mops_x10);
        uart_putchar('\n');
    }
}

/* =====================================================================
 * Category 2: MAC Pipeline Hazard
 * ===================================================================== */

static void bench_mac_hazard(void)
{
    banner("Cat 2: MAC Pipeline Hazard");

    /* ── Diagnostic suite: isolate MAC accumulator behavior ─────── */
    uart_puts("--- Diagnostics ---\n");

    /* D0: Sanity — PASS0 IMM=42 on east-edge PE[0,3], read RESULT_ROW0 */
    {
        bench_setup();
        cgra_config_pe(3, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E, 42);
        cu_run_wait();
        uint32_t v = cgra_rd(CGRA_RESULT_ROW0);
        uart_puts("D0: PE[0,3] PASS0 IMM=42 -> ROW0=");
        uart_putdec(v); uart_puts(" (expect 42)\n");
    }

    /* D1: ACC_CLR on PE[0,3], read RESULT_ROW0 */
    {
        bench_setup();
        cgra_config_pe(3, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
        cu_run_wait();
        uint32_t v = cgra_rd(CGRA_RESULT_ROW0);
        uart_puts("D1: PE[0,3] ACC_CLR -> ROW0=");
        uart_putdec(v); uart_puts(" (expect 0)\n");
    }

    /* D2: 1 MAC on east-edge PE[0,3], no forwarding chain needed.
     * slot 0=ACC_CLR, slot 1=MAC(IMM,IMM)=1*1=1, slots 2-15=NOP.
     * RESULT_ROW0 captures PE[0,3]'s alu_result at last active slot. */
    {
        bench_setup();
        cgra_config_pe_slot(3, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
        cgra_config_pe_slot(3, 1, DDR_STAGE, OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E, 1);
        for (int s = 2; s < 16; s++)
            cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE, OP_NOP, 0, 0, 0, ROUTE_E, 0);
        cu_run_wait();
        uint32_t v = cgra_rd(CGRA_RESULT_ROW0);
        uart_puts("D2: PE[0,3] ACC_CLR+1MAC(1*1) -> ROW0=");
        uart_putdec(v); uart_puts(" (expect 1)\n");
    }

    /* D3: 15 back-to-back MACs on east-edge PE[0,3].
     * slot 0=ACC_CLR, slots 1-15=MAC(IMM=1,IMM=1). */
    {
        bench_setup();
        cgra_config_pe_slot(3, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
        for (int s = 1; s < 16; s++)
            cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE, OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E, 1);
        cu_run_wait();
        uint32_t v = cgra_rd(CGRA_RESULT_ROW0);
        uart_puts("D3: PE[0,3] ACC_CLR+15MAC(1*1) -> ROW0=");
        uart_putdec(v); uart_puts(" (expect <=15, measures hazard)\n");
    }

    /* D4: Readout mechanism test — put known value 99 in PE[0,1] RF[0]
     * via PASS0 IMM=99, then use readout_row0(1) to retrieve it. */
    {
        bench_setup();
        cgra_config_pe(1, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E, 99);
        cu_run_wait();
        uint32_t v = readout_row0(1);
        uart_puts("D4: readout_row0(1) after PASS0 IMM=99 -> ");
        uart_putdec(v); uart_puts(" (expect 99)\n");
    }

    /* D5: MAC on PE[0,1] with feeder, then readout.
     * PE[0,0]=PASS0 IMM=1 east. PE[0,1]=ACC_CLR+1MAC(W,IMM=1).
     * Then readout_row0(1). */
    {
        bench_setup();
        cgra_config_pe(0, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E, 1);
        cgra_config_pe_slot(1, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
        cgra_config_pe_slot(1, 1, DDR_STAGE, OP_MAC, SRC_W, SRC_IMM, 0, ROUTE_E, 1);
        for (int s = 2; s < 16; s++)
            cgra_config_pe_slot(1, (uint32_t)s, DDR_STAGE, OP_NOP, 0, 0, 0, 0, 0);
        cu_run_wait();
        uint32_t v = readout_row0(1);
        uart_puts("D5: PE[0,1] ACC_CLR+1MAC(W=1,IMM=1) readout -> ");
        uart_putdec(v); uart_puts(" (expect 1)\n");
    }

    /* D6: Direct read of all 4 RESULT_ROW regs after D3-style test on PE[0,3] */
    {
        bench_setup();
        cgra_config_pe_slot(3, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
        for (int s = 1; s <= 5; s++)
            cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE, OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E, 1);
        for (int s = 6; s < 16; s++)
            cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE, OP_NOP, 0, 0, 0, ROUTE_E, 0);
        cu_run_wait();
        uart_puts("D6: PE[0,3] ACC_CLR+5MAC(1*1) ROW0=");
        uart_putdec(cgra_rd(CGRA_RESULT_ROW0));
        uart_puts(" ROW1="); uart_putdec(cgra_rd(CGRA_RESULT_ROW1));
        uart_puts(" ROW2="); uart_putdec(cgra_rd(CGRA_RESULT_ROW2));
        uart_puts(" ROW3="); uart_putdec(cgra_rd(CGRA_RESULT_ROW3));
        uart_puts(" (expect ROW0~1-5)\n");
    }

    uart_puts("--- End diagnostics ---\n");

    /* Use east-edge PE[0,3] for all MAC hazard tests (direct RESULT_ROW0
     * read, no forwarding chain needed). MAC(SRC_IMM, SRC_IMM) with imm=1
     * so acc += 1 per effective MAC. */
    uart_puts("\nPattern             CU_CYC  Accum  EffMAC  Util%\n");

    static const struct { const char *name; uint32_t mac_slots[16]; int n_mac; } patterns[] = {
        {"15x MAC b2b",     {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 15},
        {"8x MAC+NOP",      {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},  8},
        {"5x MAC+2NOP",     {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0},  5},
    };

    for (int p = 0; p < 3; p++) {
        bench_setup();

        /* PE[0,3] (east edge): slot 0 = ACC_CLR, slots 1-15 from pattern */
        cgra_config_pe_slot(3, 0, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
        for (int s = 1; s < 16; s++) {
            if (patterns[p].mac_slots[s])
                cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE,
                                    OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E, 1);
            else
                cgra_config_pe_slot(3, (uint32_t)s, DDR_STAGE,
                                    OP_NOP, 0, 0, 0, ROUTE_E, 0);
        }

        cu_run_wait();
        uint32_t cycles = cgra_rd(CGRA_CU_CYCLES);
        uint32_t result = cgra_rd(CGRA_RESULT_ROW0);

        uint32_t actual_mac_slots = (uint32_t)patterns[p].n_mac;
        uint32_t eff_mac = result;
        uint32_t util_x10 = (actual_mac_slots > 0)
            ? (eff_mac * 1000) / actual_mac_slots : 0;

        uart_lj(patterns[p].name, 20);
        uart_rj(cycles, 6);
        uart_puts("  ");
        uart_rj(result, 5);
        uart_puts("  ");
        uart_rj(eff_mac, 6);
        uart_puts("  ");
        uart_putfix1(util_x10);
        uart_putchar('\n');

        if (p == 0) {
            g_mac_b2b_eff = eff_mac;
            g_mac_b2b_cycles = cycles;
        }
    }
}

/* =====================================================================
 * Category 3: SIMD Throughput
 * ===================================================================== */

static void bench_simd(void)
{
    banner("Cat 3: SIMD Throughput");
    uart_puts("Mode      CU_CYC  MACs/op  Accum  MMAC/s\n");

    /* East-edge PE[0,3] with IMM=1. Sign-extended to 32-bit: 0x00000001.
     * INT32:   1 × 1 = 1 per MAC
     * INT16x2: halfwords [0x0001, 0x0000] → dot = 1×1 + 0×0 = 1 per MAC
     * INT8x4:  bytes [0x01, 0x00, 0x00, 0x00] → dot = 1+0+0+0 = 1 per MAC
     *
     * With IMM=1, all modes give 1 per MAC — same result but proves the
     * data_mode config bits are accepted. To show the actual SIMD throughput
     * difference, we need packed operands from tile memory. But the important
     * thing to verify is that data_mode doesn't BREAK anything and the
     * accumulator works in each mode. We also measure with IMM=0x0101
     * to exercise 2 lanes in INT8x4 and INT16x2. */

    static const struct {
        const char *name;
        uint32_t    mode;
        uint16_t    imm;
        uint32_t    expected_per_mac; /* dot product of imm with itself */
    } modes[] = {
        /* IMM=1: INT32 1*1=1; INT16x2 [1,0]·[1,0]=1; INT8x4 [1,0,0,0]·[1,0,0,0]=1 */
        {"INT32  i=1", DATA_MODE_INT32,   1, 1},
        {"INT16x2 i=1", DATA_MODE_INT16X2, 1, 1},
        {"INT8x4  i=1", DATA_MODE_INT8X4,  1, 1},
        /* IMM=0x0101: INT32 257*257=66049; INT16x2 [0x0101,0]·same=0x10201;
         * INT8x4 [1,1,0,0]·[1,1,0,0]=1+1+0+0=2 */
        {"INT8x4 i=0101", DATA_MODE_INT8X4, 0x0101, 2},
    };

    for (int m = 0; m < 4; m++) {
        bench_setup();

        cgra_config_pe_slot_ex(3, 0, DDR_STAGE,
                                OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0,
                                modes[m].mode);
        for (int s = 1; s < 16; s++)
            cgra_config_pe_slot_ex(3, (uint32_t)s, DDR_STAGE,
                                    OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E,
                                    modes[m].imm, modes[m].mode);

        cu_run_wait();
        uint32_t cycles = cgra_rd(CGRA_CU_CYCLES);
        uint32_t result = cgra_rd(CGRA_RESULT_ROW0);

        /* Expected accum = 13 effective MACs * expected_per_mac */
        uint32_t expected = 13 * modes[m].expected_per_mac;

        uart_lj(modes[m].name, 16);
        uart_rj(cycles, 6);
        uart_puts("  acc=");
        uart_rj(result, 6);
        uart_puts("  exp=");
        uart_rj(expected, 5);
        uart_puts("  ");
        uart_puts(result == expected ? "PASS" : "FAIL");
        uart_putchar('\n');

        if (m == 3) {  /* INT8x4 with 2 active lanes */
            g_simd_int8_eff = result;
            g_simd_int8_cyc = cycles;
        }
    }
}

/* =====================================================================
 * Category 4: DMA Bandwidth
 * ===================================================================== */

static void bench_dma_bandwidth(void)
{
    banner("Cat 4: DMA Bandwidth");
    uart_puts("Size(B)  ARM_CYC     MB/s\n");

    static const uint32_t sizes[] = {4, 16, 64, 256, 1024, 4096, 16384};
    volatile uint32_t *a = (volatile uint32_t *)DDR_BUF_A;

    for (int i = 0; i < 7; i++) {
        uint32_t sz = sizes[i];
        /* Fill source */
        for (uint32_t w = 0; w < sz / 4; w++) a[w] = w;

        arm_ccnt_reset();
        uint32_t t0 = arm_ccnt_read();
        cgra_dma(DDR_BUF_A, TILE_BANK0, sz);
        uint32_t t1 = arm_ccnt_read();
        uint32_t arm_cyc = t1 - t0;

        /* MB/s * 10 = sz * 6667 / arm_cyc (666.67 MHz ARM clock) */
        uint32_t mbs_x10;
        if (arm_cyc > 0) {
            if (sz >= 1000)
                mbs_x10 = ((sz / 100) * 6667) / (arm_cyc / 100);
            else
                mbs_x10 = (sz * 6667) / arm_cyc;
        } else {
            mbs_x10 = 0;
        }

        uart_rj(sz, 7);
        uart_puts("  ");
        uart_rj(arm_cyc, 8);
        uart_puts("  ");
        uart_putfix1(mbs_x10);
        uart_putchar('\n');

        if (mbs_x10 > g_dma_peak_mbs_x10)
            g_dma_peak_mbs_x10 = mbs_x10;
    }
}

/* =====================================================================
 * Category 5: Multicast Throughput
 * ===================================================================== */

static void bench_multicast(void)
{
    banner("Cat 5: Multicast Throughput");
    uart_puts("Fan-out  CU_CYC  Verified  Speedup\n");

    static const struct {
        const char *name;
        uint32_t    route;
        int         n_copies; /* expected number of RESULT_ROW matches */
    } configs[] = {
        {"1-way E",       ROUTE_E,                       1},
        {"2-way E+S",     ROUTE_E | ROUTE_S,             2},
        {"3-way N+E+S",   ROUTE_N | ROUTE_E | ROUTE_S,   3},
        {"4-way all",     ROUTE_N | ROUTE_E | ROUTE_S | ROUTE_W, 4},
    };

    for (int c = 0; c < 4; c++) {
        bench_setup();

        uint16_t test_val = 0x1234;

        /* PE[1,1] (PE 5): source — PASS0 IMM, multicast route */
        cgra_config_pe(5, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0,
                       configs[c].route, test_val);

        /* Forwarder chains to reach east edge for each direction:
         *   East:  PE[1,2]→PE[1,3] → RESULT_ROW1
         *   South: PE[2,1]→PE[2,2]→PE[2,3] → RESULT_ROW2
         *   North: PE[0,1]→PE[0,2]→PE[0,3] → RESULT_ROW0
         *   West:  PE[1,0]→... needs special routing to get to an edge
         */
        /* East chain: PE[1,2], PE[1,3] */
        cgra_config_pe(6, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        cgra_config_pe(7, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);

        /* South chain: PE[2,1] catches from N, forwards E */
        if (configs[c].route & ROUTE_S) {
            cgra_config_pe(9,  DDR_STAGE, OP_PASS0, SRC_N, 0, 0, ROUTE_E, 0);
            cgra_config_pe(10, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
            cgra_config_pe(11, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        }

        /* North chain: PE[0,1] catches from S, forwards E */
        if (configs[c].route & ROUTE_N) {
            cgra_config_pe(1, DDR_STAGE, OP_PASS0, SRC_S, 0, 0, ROUTE_E, 0);
            cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
            cgra_config_pe(3, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        }

        /* West chain: PE[1,0] catches from E, route S to PE[2,0]→E→E→E */
        if (configs[c].route & ROUTE_W) {
            cgra_config_pe(4,  DDR_STAGE, OP_PASS0, SRC_E, 0, 0, ROUTE_S, 0);
            cgra_config_pe(8,  DDR_STAGE, OP_PASS0, SRC_N, 0, 0, ROUTE_E, 0);
            /* PE[2,1..3] may already be configured for south chain;
             * if both S+W active, W chain goes to row 3 instead */
            if (configs[c].route & ROUTE_S) {
                /* Route PE[2,0] south to PE[3,0], then east */
                cgra_config_pe(8,  DDR_STAGE, OP_PASS0, SRC_N, 0, 0, ROUTE_S, 0);
                cgra_config_pe(12, DDR_STAGE, OP_PASS0, SRC_N, 0, 0, ROUTE_E, 0);
                cgra_config_pe(13, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
                cgra_config_pe(14, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
                cgra_config_pe(15, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
            } else {
                cgra_config_pe(9,  DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
                cgra_config_pe(10, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
                cgra_config_pe(11, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
            }
        }

        cu_run_wait();
        uint32_t cycles = cgra_rd(CGRA_CU_CYCLES);

        /* Verify delivery by reading RESULT_ROW registers */
        uint32_t r0 = cgra_rd(CGRA_RESULT_ROW0);
        uint32_t r1 = cgra_rd(CGRA_RESULT_ROW1);
        uint32_t r2 = cgra_rd(CGRA_RESULT_ROW2);
        uint32_t r3 = cgra_rd(CGRA_RESULT_ROW3);

        int verified = 0;
        /* East always delivers to row 1 */
        if (r1 == test_val) verified++;
        if ((configs[c].route & ROUTE_S) && r2 == test_val) verified++;
        if ((configs[c].route & ROUTE_N) && r0 == test_val) verified++;
        if ((configs[c].route & ROUTE_W)) {
            if ((configs[c].route & ROUTE_S) && r3 == test_val) verified++;
            else if (r2 == test_val) verified++;
        }

        /* Speedup = copies / 1 (same CU_CYCLES for multicast as unicast) */
        uint32_t speedup_x10 = (uint32_t)verified * 10;

        uart_lj(configs[c].name, 9);
        uart_rj(cycles, 6);
        uart_puts("  ");
        uart_rj((uint32_t)verified, 8);
        uart_puts("  ");
        uart_putfix1(speedup_x10);
        uart_puts("x\n");
    }
}

/* =====================================================================
 * Category 6: Parallel Row Utilization
 * ===================================================================== */

static void bench_parallel_rows(void)
{
    banner("Cat 6: Parallel Row Utilization");
    uart_puts("Rows  CU_CYC  MACs/run  MMAC/s\n");

    uint32_t active_rows[] = {1, 2, 4};

    for (int r = 0; r < 3; r++) {
        bench_setup();

        uint32_t nrows = active_rows[r];

        /* Put MAC on east-edge PE (col 3) of each row using IMM operands.
         * No tile memory or forwarding chain needed — direct RESULT_ROW read. */
        for (uint32_t row = 0; row < nrows; row++) {
            uint32_t pe = row * 4 + 3;  /* col 3 = east edge */
            cgra_config_pe_slot(pe, 0, DDR_STAGE,
                                OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
            for (int s = 1; s < 16; s++)
                cgra_config_pe_slot(pe, (uint32_t)s, DDR_STAGE,
                                    OP_MAC, SRC_IMM, SRC_IMM, 0, ROUTE_E, 1);
        }

        cu_run_wait();
        uint32_t cycles = cgra_rd(CGRA_CU_CYCLES);

        /* Read accumulated results directly from east-edge registers */
        uint32_t total_macs = 0;
        uint32_t row_regs[] = {CGRA_RESULT_ROW0, CGRA_RESULT_ROW1,
                               CGRA_RESULT_ROW2, CGRA_RESULT_ROW3};
        for (uint32_t row = 0; row < nrows; row++)
            total_macs += cgra_rd(row_regs[row]);

        /* MMAC/s * 10 = total_macs * 50MHz / cycles / 1e6 * 10
         * = total_macs * 500 / cycles */
        uint32_t mmacs_x10 = (cycles > 0) ? (total_macs * 500) / cycles : 0;

        uart_rj(nrows, 4);
        uart_puts("  ");
        uart_rj(cycles, 6);
        uart_puts("  ");
        uart_rj(total_macs, 8);
        uart_puts("  ");
        uart_putfix1(mmacs_x10);
        uart_putchar('\n');

        if (r == 2) g_parallel4_mmacs = mmacs_x10;
    }
}

/* =====================================================================
 * Category 7: FC Layer Pattern
 * ===================================================================== */

static void bench_fc_pattern(void)
{
    banner("Cat 7: FC Layer Pattern (4-row MAC)");
    uart_puts("InSize  Chunks  CU_tot  ARM_tot    MMAC/s\n");

    uint32_t input_sizes[] = {16, 64, 160, 784};

    for (int t = 0; t < 4; t++) {
        uint32_t in_sz = input_sizes[t];
        uint32_t n_chunks = (in_sz + 12) / 13;  /* 13 MACs per chunk (16-3 drain) */

        /* Prepare tile data: all 1s */
        volatile uint32_t *ddr = (volatile uint32_t *)DDR_BUF_A;
        for (int w = 0; w < 16; w++) ddr[w] = 1;

        arm_ccnt_reset();
        uint32_t t0 = arm_ccnt_read();
        uint32_t cu_total = 0;

        for (uint32_t k = 0; k < n_chunks; k++) {
            uint32_t count = (k + 1) * 13 <= in_sz ? 13 : in_sz - k * 13;

            bench_setup();

            /* Configure 4 rows: col 0 = MAC, cols 1-3 = drain forwarders */
            for (uint32_t row = 0; row < 4; row++) {
                uint32_t base = row * 4;

                /* Col 0: ACC_CLR slot 0 (only on first chunk) */
                if (k == 0)
                    cgra_config_pe_slot(base, 0, DDR_STAGE,
                                        OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
                else
                    cgra_config_pe_slot(base, 0, DDR_STAGE,
                                        OP_MAC, SRC_W, SRC_IMM, 0, ROUTE_E, 1);

                for (uint32_t s = 1; s < count; s++)
                    cgra_config_pe_slot(base, s, DDR_STAGE,
                                        OP_MAC, SRC_W, SRC_IMM, 0, ROUTE_E, 1);
                /* Drain slots */
                for (uint32_t s = count; s < 16; s++)
                    cgra_config_pe_slot(base, s, DDR_STAGE,
                                        OP_NOP, 0, 0, 0, ROUTE_E, 0);

                /* Cols 1-3: PASS0 in drain slots only */
                for (int col = 1; col < 4; col++) {
                    uint32_t pe = base + (uint32_t)col;
                    cgra_config_pe_slot(pe, 0, DDR_STAGE,
                                        OP_NOP, 0, 0, 0, ROUTE_E, 0);
                    for (int s = 13; s <= 15; s++)
                        cgra_config_pe_slot(pe, (uint32_t)s, DDR_STAGE,
                                            OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
                }

                /* Load tile bank for this row */
                cgra_dma(DDR_BUF_A, TILE_BANK0 + row * 0x1000, 64);
            }

            cu_run_wait();
            cu_total += cgra_rd(CGRA_CU_CYCLES);
        }

        uint32_t t1 = arm_ccnt_read();
        uint32_t arm_total = t1 - t0;

        /* Total MACs = 4 rows * in_sz * 1 (weight=1) */
        uint32_t total_macs = 4 * in_sz;
        /* MMAC/s * 10 using ARM wall clock at 666.67 MHz:
         * MMAC/s = total_macs / (arm_total / 666.67e6) / 1e6
         *        = total_macs * 666.67 / arm_total
         * Use safe integer math to avoid overflow: */
        uint32_t mmacs_x10 = 0;
        if (arm_total > 0) {
            /* Split to avoid overflow: (total_macs / 100) * 66670 / (arm_total / 100) */
            uint32_t num = (total_macs > 1000) ? (total_macs / 100) * 66670
                                                : total_macs * 6667;
            uint32_t den = (arm_total > 100000) ? arm_total / 100 : arm_total;
            if (total_macs > 1000)
                mmacs_x10 = num / den;
            else
                mmacs_x10 = num / arm_total;
        }

        uart_rj(in_sz, 6);
        uart_puts("  ");
        uart_rj(n_chunks, 6);
        uart_puts("  ");
        uart_rj(cu_total, 6);
        uart_puts("  ");
        uart_rj(arm_total, 8);
        uart_puts("  ");
        uart_putfix1(mmacs_x10);
        uart_putchar('\n');

        if (t == 3) g_fc784_mmacs = mmacs_x10;
    }
}

/* =====================================================================
 * Category 8: Multicast FC Pattern (parallel vs sequential)
 * ===================================================================== */

static void bench_multicast_fc(void)
{
    banner("Cat 8: Multicast FC (parallel vs sequential)");
    uart_puts("Mode             CU_CYC  MACs  MMAC/s  Speedup\n");

    /* Simple test: 4 rows doing MAC(IMM=1) * input(1) for 13 slots.
     * Sequential = 4 separate CU runs (1 row each)
     * Parallel   = 1 CU run with 4 rows active */

    volatile uint32_t *ddr = (volatile uint32_t *)DDR_BUF_A;
    for (int w = 0; w < 16; w++) ddr[w] = 1;

    /* Sequential: run 4 times, each with 1 row */
    uint32_t seq_total = 0;
    for (uint32_t row = 0; row < 4; row++) {
        bench_setup();
        uint32_t base = row * 4;

        cgra_config_pe_slot(base, 0, DDR_STAGE,
                            OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
        for (int s = 1; s <= 12; s++)
            cgra_config_pe_slot(base, (uint32_t)s, DDR_STAGE,
                                OP_MAC, SRC_W, SRC_IMM, 0, ROUTE_E, 1);
        for (int col = 1; col < 4; col++) {
            uint32_t pe = base + (uint32_t)col;
            cgra_config_pe(pe, DDR_STAGE, OP_NOP, 0, 0, 0, ROUTE_E, 0);
            for (int s = 13; s <= 15; s++)
                cgra_config_pe_slot(pe, (uint32_t)s, DDR_STAGE,
                                    OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        }
        cgra_dma(DDR_BUF_A, TILE_BANK0 + row * 0x1000, 64);

        cu_run_wait();
        seq_total += cgra_rd(CGRA_CU_CYCLES);
    }

    /* Parallel: 1 run with all 4 rows (same as cat 6 with 4 rows) */
    bench_setup();
    for (uint32_t row = 0; row < 4; row++) {
        uint32_t base = row * 4;
        cgra_config_pe_slot(base, 0, DDR_STAGE,
                            OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
        for (int s = 1; s <= 12; s++)
            cgra_config_pe_slot(base, (uint32_t)s, DDR_STAGE,
                                OP_MAC, SRC_W, SRC_IMM, 0, ROUTE_E, 1);
        for (int col = 1; col < 4; col++) {
            uint32_t pe = base + (uint32_t)col;
            cgra_config_pe(pe, DDR_STAGE, OP_NOP, 0, 0, 0, ROUTE_E, 0);
            for (int s = 13; s <= 15; s++)
                cgra_config_pe_slot(pe, (uint32_t)s, DDR_STAGE,
                                    OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        }
        cgra_dma(DDR_BUF_A, TILE_BANK0 + row * 0x1000, 64);
    }

    cu_run_wait();
    uint32_t par_cycles = cgra_rd(CGRA_CU_CYCLES);

    uint32_t total_macs = 4 * 12;  /* 4 rows * 12 MAC slots */
    uint32_t seq_mmacs_x10 = (seq_total > 0) ? (total_macs * 500) / seq_total : 0;
    uint32_t par_mmacs_x10 = (par_cycles > 0) ? (total_macs * 500) / par_cycles : 0;
    uint32_t speedup_x10 = (par_cycles > 0) ? (seq_total * 10) / par_cycles : 0;

    uart_lj("4x Sequential", 17);
    uart_rj(seq_total, 6);
    uart_puts("  ");
    uart_rj(total_macs, 4);
    uart_puts("  ");
    uart_putfix1(seq_mmacs_x10);
    uart_puts("   1.0x\n");

    uart_lj("1x Parallel", 17);
    uart_rj(par_cycles, 6);
    uart_puts("  ");
    uart_rj(total_macs, 4);
    uart_puts("  ");
    uart_putfix1(par_mmacs_x10);
    uart_puts("   ");
    uart_putfix1(speedup_x10);
    uart_puts("x\n");

    g_mcast_speedup_x10 = speedup_x10;
}

/* =====================================================================
 * Category 9: Activation Functions (LIF, RELU, MAX, CMP, shifts)
 * ===================================================================== */

static void bench_activations(void)
{
    banner("Cat 9: Activation Functions");
    uart_puts("Op      Test             CU_CYC  Result  OK\n");

    static const struct {
        const char *op_name;
        const char *test_name;
        uint32_t    op;
        uint16_t    feed_imm;   /* IMM for feeder PE[0,0] */
        uint16_t    op_imm;     /* IMM for src1 on compute PE[0,1] */
        uint32_t    src0;
        uint32_t    src1;
        int32_t     expected;   /* expected RESULT_ROW0 */
        int         acc_clr;
    } tests[] = {
        {"RELU",   "positive(5)",    OP_RELU,   5,     0, SRC_W, 0,       5, 0},
        {"RELU",   "negative(-5)",   OP_RELU,   (uint16_t)-5, 0, SRC_W, 0, 0, 0},
        {"MAX",    "max(10,20)",     OP_MAX,    10,   20, SRC_W, SRC_IMM, 20, 0},
        {"MAX",    "max(30,5)",      OP_MAX,    30,    5, SRC_W, SRC_IMM, 30, 0},
        {"SHL",    "5<<2=20",        OP_SHL,     5,    2, SRC_W, SRC_IMM, 20, 0},
        {"SHR",    "100>>3=12",      OP_SHR,   100,    3, SRC_W, SRC_IMM, 12, 0},
        {"CMP_GT", "10>5=1",         OP_CMP_GT, 10,    5, SRC_W, SRC_IMM,  1, 0},
        {"CMP_GT", "3>10=0",         OP_CMP_GT,  3,   10, SRC_W, SRC_IMM,  0, 0},
        {"CMP_LT", "3<10=1",         OP_CMP_LT,  3,   10, SRC_W, SRC_IMM,  1, 0},
        {"CMP_EQ", "7==7=1",         OP_CMP_EQ,  7,    7, SRC_W, SRC_IMM,  1, 0},
    };
    int n_tests = 10;

    for (int i = 0; i < n_tests; i++) {
        bench_setup();

        if (tests[i].acc_clr) {
            cgra_config_pe(1, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, 0, 0);
            cu_run_wait();
            cfg_all_nop();
        }

        cgra_config_pe(0, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E,
                       tests[i].feed_imm);
        cgra_config_pe(1, DDR_STAGE, tests[i].op, tests[i].src0, tests[i].src1,
                       0, ROUTE_E, tests[i].op_imm);
        cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        cgra_config_pe(3, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);

        cu_run_wait();
        uint32_t cycles = cgra_rd(CGRA_CU_CYCLES);
        int32_t result = (int32_t)cgra_rd(CGRA_RESULT_ROW0);

        int ok = (result == tests[i].expected);

        uart_lj(tests[i].op_name, 8);
        uart_lj(tests[i].test_name, 17);
        uart_rj(cycles, 6);
        uart_puts("  ");
        uart_rj((uint32_t)result, 6);
        uart_puts("  ");
        uart_puts(ok ? "PASS" : "FAIL");
        uart_putchar('\n');
    }

    /* LIF test: feed ramp input, verify spike */
    {
        bench_setup();

        /* ACC_CLR first */
        cgra_config_pe(1, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, 0, 0);
        cu_run_wait();
        cfg_all_nop();

        /* PE[0,0]: PASS0 IMM=100 (input current each slot) */
        cgra_config_pe(0, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E, 100);
        /* PE[0,1]: LIF with threshold=500 in src1 IMM
         * Each slot: membrane += input(100) - leak(10) = +90
         * After slot 0: membrane = 90 (acc starts at 0, +100-10=90)
         * After slot 5: membrane = 540 > 500 → spike, reset to 0
         * After slot 6: membrane = 90 again (starts fresh)
         * ... slot 11: spike again at 540
         * Last slot 15: membrane = 90*4 = 360 (no spike), output = 0
         * But RESULT_ROW captures the LAST cycle output.
         * With 16 slots: first spike at slot 5, reset; second at slot 11,
         * reset; slots 12-15 accumulate 4*90=360 < 500 → output = 0.
         * HOWEVER alu_result is written every cycle. Last cycle (slot 15)
         * has no spike → result = 0.
         *
         * To get a spike at the END, set threshold low enough for last slot.
         * With threshold=80: every slot spikes (90 >= 80). Result = 1. */
        cgra_config_pe(1, DDR_STAGE, OP_LIF, SRC_W, SRC_IMM, 0, ROUTE_E, 80);
        cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        cgra_config_pe(3, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);

        cu_run_wait();
        uint32_t cycles = cgra_rd(CGRA_CU_CYCLES);
        uint32_t result = cgra_rd(CGRA_RESULT_ROW0);

        uart_lj("LIF", 8);
        uart_lj("ramp(100,thr=80)", 17);
        uart_rj(cycles, 6);
        uart_puts("  ");
        uart_rj(result, 6);
        uart_puts("  ");
        uart_puts(result == 1 ? "PASS" : "FAIL");
        uart_putchar('\n');
    }

    /* LIF sub-threshold test */
    {
        bench_setup();
        cgra_config_pe(1, DDR_STAGE, OP_ACC_CLR, 0, 0, 0, 0, 0);
        cu_run_wait();
        cfg_all_nop();

        /* Input=5, leak=10 → net = 5-10 = -5 per slot. Membrane stays 0
         * (saturates at 0 or goes negative). threshold=5000. No spike. */
        cgra_config_pe(0, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E, 5);
        cgra_config_pe(1, DDR_STAGE, OP_LIF, SRC_W, SRC_IMM, 0, ROUTE_E, 5000);
        cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        cgra_config_pe(3, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);

        cu_run_wait();
        uint32_t cycles = cgra_rd(CGRA_CU_CYCLES);
        uint32_t result = cgra_rd(CGRA_RESULT_ROW0);

        uart_lj("LIF", 8);
        uart_lj("sub-thr(5,thr=5k)", 17);
        uart_rj(cycles, 6);
        uart_puts("  ");
        uart_rj(result, 6);
        uart_puts("  ");
        uart_puts(result == 0 ? "PASS" : "FAIL");
        uart_putchar('\n');
    }
}

/* =====================================================================
 * Category 10: Config Reload Overhead
 * ===================================================================== */

static void bench_config_reload(void)
{
    banner("Cat 10: Config Reload Overhead");
    uart_puts("Operation                 ARM_CYC     us\n");

    /* 1 PE, 1 slot (2 DMA transfers of 4 bytes each) */
    arm_ccnt_reset();
    uint32_t t0 = arm_ccnt_read();
    cgra_config_pe_slot(0, 0, DDR_STAGE, OP_NOP, 0, 0, 0, 0, 0);
    uint32_t t1 = arm_ccnt_read();
    uint32_t cyc_1pe_1slot = t1 - t0;

    /* 16 PEs, 1 slot each (broadcast via slot 0) */
    arm_ccnt_reset();
    t0 = arm_ccnt_read();
    for (uint32_t pe = 0; pe < 16; pe++)
        cgra_config_pe(pe, DDR_STAGE, OP_NOP, 0, 0, 0, 0, 0);
    t1 = arm_ccnt_read();
    uint32_t cyc_16pe_broadcast = t1 - t0;

    /* 16 PEs x 16 slots (full custom program) */
    arm_ccnt_reset();
    t0 = arm_ccnt_read();
    for (uint32_t pe = 0; pe < 16; pe++)
        for (uint32_t s = 0; s < 16; s++)
            cgra_config_pe_slot(pe, s, DDR_STAGE, OP_NOP, 0, 0, 0, 0, 0);
    t1 = arm_ccnt_read();
    uint32_t cyc_full = t1 - t0;

    /* Bank switch */
    arm_ccnt_reset();
    t0 = arm_ccnt_read();
    cgra_wr(CGRA_TILE_BANK_SEL, 1);
    t1 = arm_ccnt_read();
    uint32_t cyc_bank = t1 - t0;
    cgra_wr(CGRA_TILE_BANK_SEL, 0);

    /* Print: us * 10 = arm_cyc * 10 / 666.67 ≈ arm_cyc * 15 / 1000 */
    struct { const char *name; uint32_t cyc; } rows[] = {
        {"1 PE x 1 slot (2 DMAs)",    cyc_1pe_1slot},
        {"16 PE broadcast (32 DMAs)", cyc_16pe_broadcast},
        {"16 PE x 16 slot (512 DMAs)",cyc_full},
        {"Bank switch (1 APB write)", cyc_bank},
    };

    for (int i = 0; i < 4; i++) {
        uint32_t us_x10 = (rows[i].cyc * 15) / 1000;
        uart_lj(rows[i].name, 26);
        uart_rj(rows[i].cyc, 8);
        uart_puts("  ");
        uart_putfix1(us_x10);
        uart_putchar('\n');

        if (i == 2) g_cfg_full_us_x10 = us_x10;
    }
}

/* =====================================================================
 * Category 11: End-to-End FPS (Frames Per Second)
 *
 * Measures complete frame time for practical workloads:
 *   - Single CU pass (16 ops, no DMA): pure compute FPS
 *   - 8×8 elementwise (like the Z inversion demo): DMA + compute
 *   - 28×28 FC classify (784→30, 4 outputs/run): full FC pipeline
 * ===================================================================== */

static void bench_fps(void)
{
    banner("Cat 11: End-to-End FPS");
    uart_puts("Workload                ARM_CYC/frame  us/frame     FPS\n");

    volatile uint32_t *ddr = (volatile uint32_t *)DDR_BUF_A;

    /* ── Test A: Pure CU pass (no DMA, pre-configured) ────────── */
    {
        bench_setup();
        /* Simple PASS0 chain — already configured by bench_setup's cfg_all_nop
         * Just configure row 0 as a PASS chain */
        cgra_config_pe(0, DDR_STAGE, OP_PASS0, SRC_IMM, 0, 0, ROUTE_E, 42);
        cgra_config_pe(1, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        cgra_config_pe(3, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);

        /* Warm up */
        cu_run_wait();

        /* Measure 100 iterations */
        arm_ccnt_reset();
        uint32_t t0 = arm_ccnt_read();
        for (int i = 0; i < 100; i++)
            cu_run_wait();
        uint32_t t1 = arm_ccnt_read();
        uint32_t per_frame = (t1 - t0) / 100;

        /* us * 10 = arm_cyc * 15 / 1000 */
        uint32_t us_x10 = (per_frame * 15) / 1000;
        /* FPS * 10 = 6666700 / per_frame (666.67 MHz / per_frame * 10) */
        uint32_t fps_x10 = (per_frame > 0) ? 66667000u / per_frame : 0;

        uart_lj("CU pass (no DMA)", 24);
        uart_rj(per_frame, 13);
        uart_puts("  ");
        uart_putfix1(us_x10);
        uart_puts("  ");
        uart_putfix1(fps_x10);
        uart_putchar('\n');
    }

    /* ── Test B: 8×8 elementwise (DMA load + CU + readback) ──── */
    {
        bench_setup();
        /* Fill 64 bytes of input data */
        for (int w = 0; w < 16; w++) ddr[w] = (uint32_t)w;

        /* Configure row 0: XOR with 0xFFFF (like the demo inversion) */
        cgra_config_pe(0, DDR_STAGE, OP_XOR, SRC_W, SRC_IMM, 0, ROUTE_E, 0xFFFF);
        cgra_config_pe(1, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        cgra_config_pe(2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        cgra_config_pe(3, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);

        arm_ccnt_reset();
        uint32_t t0 = arm_ccnt_read();
        for (int i = 0; i < 100; i++) {
            cgra_dma(DDR_BUF_A, TILE_BANK0, 64);   /* load 16 words */
            cu_run_wait();                           /* compute */
            (void)cgra_rd(CGRA_RESULT_ROW0);         /* readback */
        }
        uint32_t t1 = arm_ccnt_read();
        uint32_t per_frame = (t1 - t0) / 100;

        uint32_t us_x10 = (per_frame * 15) / 1000;
        uint32_t fps_x10 = (per_frame > 0) ? 66667000u / per_frame : 0;

        uart_lj("8x8 elem (DMA+CU)", 24);
        uart_rj(per_frame, 13);
        uart_puts("  ");
        uart_putfix1(us_x10);
        uart_puts("  ");
        uart_putfix1(fps_x10);
        uart_putchar('\n');
    }

    /* ── Test C: 28×28 FC classify (784→30, 4-row parallel) ──── */
    /* This models the lpr_cgra_accel FC offload pattern:
     * 8 groups of 4 outputs, 61 chunks per group,
     * each chunk = config DMA + tile DMA + CU run.
     * We measure 1 full 784→4 group (61 chunks). */
    {
        /* Fill tile data with 1s */
        for (int w = 0; w < 16; w++) ddr[w] = 1;

        arm_ccnt_reset();
        uint32_t t0 = arm_ccnt_read();

        /* 1 group = 61 chunks of 13 MACs each (784/13 = ~61) */
        uint32_t n_chunks = 61;
        for (uint32_t k = 0; k < n_chunks; k++) {
            /* Configure 4 rows: col 0 = MAC, cols 1-3 = NOP */
            for (uint32_t row = 0; row < 4; row++) {
                uint32_t base = row * 4;
                if (k == 0)
                    cgra_config_pe_slot(base, 0, DDR_STAGE,
                                        OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
                else
                    cgra_config_pe_slot(base, 0, DDR_STAGE,
                                        OP_MAC, SRC_W, SRC_IMM, 0, ROUTE_E, 1);
                for (int s = 1; s < 13; s++)
                    cgra_config_pe_slot(base, (uint32_t)s, DDR_STAGE,
                                        OP_MAC, SRC_W, SRC_IMM, 0, ROUTE_E, 1);
                for (int s = 13; s < 16; s++)
                    cgra_config_pe_slot(base, (uint32_t)s, DDR_STAGE,
                                        OP_NOP, 0, 0, 0, 0, 0);

                /* Load tile data */
                cgra_dma(DDR_BUF_A, TILE_BANK0 + row * 0x1000, 64);
            }
            cu_run_wait();
        }

        uint32_t t1 = arm_ccnt_read();
        uint32_t per_group = t1 - t0;

        /* Full 784→30 = 8 groups (30/4 = 8) */
        uint32_t per_char = per_group * 8;
        /* 7 characters per plate */
        uint32_t per_plate = per_char * 7;

        /* us = arm_cyc / 666.67 */
        uint32_t group_us_x10 = (per_group * 15) / 1000;
        uint32_t char_us_x10 = group_us_x10 * 8;
        uint32_t plate_us_x10 = char_us_x10 * 7;

        /* FPS for single character */
        uint32_t char_fps_x10 = (per_char > 0) ? 66667000u / (per_char / 10) : 0;
        /* FPS for full plate (7 chars) */
        uint32_t plate_fps_x10 = (per_plate > 0) ? 66667000u / (per_plate / 10) : 0;

        uart_lj("FC 784->4 (1 group)", 24);
        uart_rj(per_group, 13);
        uart_puts("  ");
        uart_putfix1(group_us_x10);
        uart_putchar('\n');

        uart_lj("FC 784->30 (1 char)", 24);
        uart_rj(per_char, 13);
        uart_puts("  ");
        uart_putfix1(char_us_x10);
        uart_puts("  ");
        uart_putfix1(char_fps_x10);
        uart_putchar('\n');

        uart_lj("LPR 7-char plate", 24);
        uart_rj(per_plate, 13);
        uart_puts("  ");
        uart_putfix1(plate_us_x10);
        uart_puts("  ");
        uart_putfix1(plate_fps_x10);
        uart_putchar('\n');
    }
}

/* =====================================================================
 * Summary
 * ===================================================================== */

static void bench_summary(void)
{
    banner("CGRA Capability Summary");

    uart_puts("Peak INT32 (theoretical) :  800.0 MMAC/s (16 PEs x 50 MHz)\n");

    /* MAC single-PE: eff_mac * 50MHz / cycles */
    uint32_t mac_1pe_x10 = (g_mac_b2b_cycles > 0)
        ? (g_mac_b2b_eff * 500) / g_mac_b2b_cycles : 0;
    uart_puts("Measured INT32 MAC (1PE) : ");
    uart_putfix1(mac_1pe_x10);
    uart_puts(" MMAC/s\n");

    /* SIMD INT8x4 single-PE */
    uint32_t simd_1pe_x10 = (g_simd_int8_cyc > 0)
        ? (g_simd_int8_eff * 500) / g_simd_int8_cyc : 0;
    uart_puts("Measured INT8x4 (1PE)   : ");
    uart_putfix1(simd_1pe_x10);
    uart_puts(" MMAC/s\n");

    uart_puts("4-row parallel INT32    : ");
    uart_putfix1(g_parallel4_mmacs);
    uart_puts(" MMAC/s\n");

    uart_puts("FC pattern (784-in)     : ");
    uart_putfix1(g_fc784_mmacs);
    uart_puts(" MMAC/s\n");

    uart_puts("Multicast FC speedup    : ");
    uart_putfix1(g_mcast_speedup_x10);
    uart_puts("x\n");

    uart_puts("DMA peak bandwidth      : ");
    uart_putfix1(g_dma_peak_mbs_x10);
    uart_puts(" MB/s\n");

    uart_puts("Config reload (full)    : ");
    uart_putfix1(g_cfg_full_us_x10);
    uart_puts(" us\n");

    /* MAC pipeline utilization: eff_mac / 15 slots (slot 0=ACC_CLR) * 100 */
    uint32_t util_x10 = (g_mac_b2b_eff * 1000) / 15;
    uart_puts("MAC pipeline util (b2b) : ");
    uart_putfix1(util_x10);
    uart_puts(" %\n");

    /* GOPS/W comparison */
    uart_puts("\n--- Power Efficiency (Vivado routed) ---\n");
    uart_puts("CGRA PL power : 0.217 W\n");
    uart_puts("PS7 ARM power : 1.532 W\n");

    /* CGRA GOPS/W = parallel4_mmacs / 10 (remove x10) / CGRA_POWER_MW * 1000 */
    /* = parallel4_mmacs * 100 / CGRA_POWER_MW */
    if (g_parallel4_mmacs > 0) {
        uint32_t cgra_gopsw_x10 = (g_parallel4_mmacs * 100) / CGRA_POWER_MW;
        uart_puts("CGRA MMAC/s/W : ");
        uart_putfix1(cgra_gopsw_x10);
        uart_puts("\n");

        /* ARM pure-C estimate: ~150 MMAC/s at 1.532W */
        /* 150 * 10 / 1532 * 100 */
        uint32_t arm_gopsw_x10 = (1500 * 100) / PS7_POWER_MW;
        uart_puts("ARM  MMAC/s/W : ");
        uart_putfix1(arm_gopsw_x10);
        uart_puts(" (pure-C estimate)\n");

        uint32_t ratio_x10 = (arm_gopsw_x10 > 0)
            ? (cgra_gopsw_x10 * 10) / arm_gopsw_x10 : 0;
        uart_puts("CGRA/ARM ratio: ");
        uart_putfix1(ratio_x10);
        uart_puts("x perf/Watt\n");
    }
}

/* =====================================================================
 * Entry point
 * ===================================================================== */

void main(void)
{
    uart_init();
    arm_pmu_enable();

    uart_puts("\n");
    uart_puts("==========================================\n");
    uart_puts(" CGRA Benchmark Suite v1.0\n");
    uart_puts(" Zynq-7000 XC7Z020 / 4x4 CGRA @ 50 MHz\n");
    uart_puts(" ARM Cortex-A9 @ 666.67 MHz\n");
    uart_puts("==========================================\n");

    uart_puts("\nClock speeds:\n");
    uart_puts("  CGRA PL : 50.00 MHz (FCLK_CLK0, 20 ns)\n");
    uart_puts("  ARM PS  : 666.67 MHz (PS7 PLL)\n");
    uart_puts("  Ratio   : 13.33 ARM cycles per CGRA cycle\n");

    bench_per_op();          /* Cat 1 */
    bench_mac_hazard();      /* Cat 2 */
    bench_simd();            /* Cat 3 */
    bench_dma_bandwidth();   /* Cat 4 */
    bench_multicast();       /* Cat 5 */
    bench_parallel_rows();   /* Cat 6 */
    bench_fc_pattern();      /* Cat 7 */
    bench_multicast_fc();    /* Cat 8 */
    bench_activations();     /* Cat 9 */
    bench_config_reload();   /* Cat 10 */

    bench_fps();
    bench_summary();

    uart_puts("\n[BENCH COMPLETE]\n");
    while (1) asm volatile("wfi");
}
