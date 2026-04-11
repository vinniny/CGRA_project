/* =========================================================================
 * demo_ascii_inverter.c — CGRA "ASCII Image Accelerator" Demo
 *
 * Demonstrates the full PL <-> PS hardware pipeline of the CGRA SoC
 * end-to-end:
 *
 *   ARM Cortex-A9
 *      │  1) write input image to DDR (ARM cache flush)
 *      ▼
 *   AXI HP slave  ◄── CGRA AXI master (DMA reads input from DDR)
 *      │
 *      ▼
 *   CGRA tile memory  →  4x4 PE array  →  XOR each pixel with 0xFFFFFFFF
 *      │                                       │
 *      ▼                                       ▼
 *   Result row registers  ◄────────  east-edge taps captured by APB CSR
 *      │
 *      ▼
 *   GIC IRQ_F2P[0] (level-high)  →  Cortex-A9 GIC ID 61
 *      │
 *      ▼
 *   ISR — read 4 results, kick the next chunk, eventually wake main()
 *      │
 *      ▼
 *   ARM main() — invalidate dcache, print the inverted image
 *
 * Visual confirmation: the same `irq` net is wired to **LED4** on the
 * board, so the LED briefly pulses each time the CGRA fires the IRQ.
 *
 * Build paths
 * ===========
 * 1) WSL2 standalone (this repo's Makefile):
 *      make demo && make run_demo
 *    Pulls the Vitis BSP source files from
 *    /tools/Xilinx/2025.1/data/embeddedsw/ and links them with our
 *    hand-rolled start.s, xparameters.h, and xscugic_g.c.
 *
 * 2) Windows Vitis Workbench live demo (planned):
 *      File -> New -> Application Project -> select the same .xsa
 *      Empty Application (C) -> Import -> demo_ascii_inverter.c
 *      Build, Run on hardware.
 *    Vitis auto-generates xparameters.h, xscugic_g.c, the linker
 *    script, and the boot/vector code. The user does NOT import any
 *    other file from this repo. The single .c source you are reading
 *    is identical between both flows — no #ifdefs.
 *
 * Hardware constraint that shapes the design
 * ==========================================
 * The CGRA's east-edge result registers (RESULT_ROW0..3) capture only
 * one value per CU run (the LAST cycle's east-edge value, latched by
 * an always_ff at cgra_top.sv:847-850). For an 8x8 = 64-pixel image
 * we therefore need 16 CU runs of 4 pixels each (one pixel per row).
 *
 * To honour the user's "single blocking wfi" spec, the demo uses an
 * **ISR-driven chunk pump**: the ISR reads its chunk's 4 results,
 * kicks the next chunk, and only sets `g_all_done = 1` after the 16th
 * chunk fires. main() therefore has exactly one `while (!g_all_done)
 * { wfi; }` block — but the wfi naturally drains all 16 chunks
 * because each chunk's IRQ wakes the loop just to immediately go
 * back to sleep.
 * ========================================================================= */

#include <stdint.h>
#include "xparameters.h"          /* hand-rolled on WSL2, auto-gen on Windows */
#include "xscugic.h"
#include "xil_cache.h"
#include "xil_exception.h"
#include "xil_io.h"

/* ── Inline UART0 driver ──────────────────────────────────────────────
 * Drives the Zynq PS UART0 FIFO at 0xE0000030 directly. ps7_init has
 * already configured baud + MIO[14]/[15], so this driver only needs to
 * spin on the TX-full bit and write bytes. Used instead of xil_printf
 * to avoid pulling libc (_ctype_, strlen) into the link, and to keep
 * the demo source file 100% self-contained for the Windows Vitis
 * Workbench port (no extra files to import). */
#define UART0_BASE      0xE0000000UL
#define UART_SR_OFF     0x2CU            /* Channel Status Register   */
#define UART_FIFO_OFF   0x30U            /* Tx/Rx FIFO                */
#define UART_SR_TXFULL  (1U << 4)
#define UART_SR_TXEMPTY (1U << 3)

static inline void uart_putc(char c)
{
    volatile uint32_t *sr   = (volatile uint32_t *)(UART0_BASE + UART_SR_OFF);
    volatile uint32_t *fifo = (volatile uint32_t *)(UART0_BASE + UART_FIFO_OFF);
    /* Wait for TX FIFO to be fully EMPTY (not just non-full) before
     * writing the next byte. This caps effective throughput at 1 byte
     * per ~87 us at 115200 baud (~ 11520 B/s), which prevents the
     * CH340 USB-serial bridge downstream from dropping bytes when the
     * Cortex-A9 runs at full 666 MHz with the dcache enabled. Dropped
     * bytes in the middle of a 3-byte UTF-8 block char sequence show
     * up as replacement characters in the terminal. */
    while (!(*sr & UART_SR_TXEMPTY)) { /* spin */ }
    *fifo = (uint32_t)(unsigned char)c;
}

static inline void uart_drain(void)
{
    volatile uint32_t *sr = (volatile uint32_t *)(UART0_BASE + UART_SR_OFF);
    while (!(*sr & UART_SR_TXEMPTY)) { /* spin */ }
}

static void uart_puts(const char *s)
{
    while (*s) {
        if (*s == '\n') {
            uart_putc('\r');
            uart_putc('\n');
            /* Drain TX FIFO at every line break so the host CH340-USB
             * adapter never drops characters on long bursts. */
            uart_drain();
            for (volatile int i = 0; i < 5000; i++) { /* short pacing */ }
            s++;
            continue;
        }
        uart_putc(*s++);
    }
}

static void __attribute__((unused)) uart_puthex(uint32_t v)
{
    static const char hex[] = "0123456789ABCDEF";
    uart_puts("0x");
    for (int i = 28; i >= 0; i -= 4) {
        uart_putc(hex[(v >> i) & 0xFU]);
    }
}

static void uart_putdec(uint32_t v)
{
    char buf[12];
    int i = 11;
    buf[i] = '\0';
    if (v == 0) { uart_putc('0'); return; }
    while (v && i > 0) { buf[--i] = (char)('0' + (v % 10U)); v /= 10U; }
    uart_puts(&buf[i]);
}

/* CGRA fabric IRQ ID. Hardcoded so the source is identical between WSL2
 * and Windows Vitis Workbench builds (Vitis-auto-generated names like
 * XPAR_FABRIC_CGRA_TOP_0_IRQ_INTR depend on block-design hierarchy). */
#define DEMO_CGRA_IRQ_ID            61U

/* ── CGRA register map (28 regs at AXI GP0 base 0x43C00000) ─────────── */
#define CGRA_BASE                   0x43C00000UL
#define CGRA_DMA_CTRL               (CGRA_BASE + 0x00)
#define CGRA_DMA_STATUS             (CGRA_BASE + 0x04)
#define CGRA_DMA_SRC                (CGRA_BASE + 0x08)
#define CGRA_DMA_DST                (CGRA_BASE + 0x0C)
#define CGRA_DMA_SIZE               (CGRA_BASE + 0x10)
#define CGRA_DMA_SRC_STRIDE         (CGRA_BASE + 0x14)
#define CGRA_DMA_ROWS               (CGRA_BASE + 0x18)
#define CGRA_DMA_COLS               (CGRA_BASE + 0x1C)
#define CGRA_CU_CTRL                (CGRA_BASE + 0x20)
#define CGRA_CU_STATUS              (CGRA_BASE + 0x24)
#define CGRA_CU_CYCLES              (CGRA_BASE + 0x28)
#define CGRA_IRQ_STATUS             (CGRA_BASE + 0x30)
#define CGRA_IRQ_MASK               (CGRA_BASE + 0x34)
#define CGRA_LOOP_START             (CGRA_BASE + 0x48)
#define CGRA_LOOP_END               (CGRA_BASE + 0x4C)
#define CGRA_LOOP_COUNT             (CGRA_BASE + 0x50)
#define CGRA_RESULT_ROW0            (CGRA_BASE + 0x58)
#define CGRA_RESULT_ROW1            (CGRA_BASE + 0x5C)
#define CGRA_RESULT_ROW2            (CGRA_BASE + 0x60)
#define CGRA_RESULT_ROW3            (CGRA_BASE + 0x64)

#define IRQ_DMA_DONE                0x1U
#define IRQ_CU_DONE                 0x2U
#define IRQ_DMA_ERR                 0x4U

/* DMA-side address-space prefixes */
#define TILE_BANK0                  0x10000000UL   /* PE row 0 ← bank 0 */
#define TILE_BANK1                  0x10001000UL   /* PE row 1 ← bank 1 */
#define TILE_BANK2                  0x10002000UL   /* PE row 2 ← bank 2 */
#define TILE_BANK3                  0x10003000UL   /* PE row 3 ← bank 3 */
#define CFG_BASE                    0x20000000UL   /* PE config RAM     */

/* ── CGRA ISA (subset used by the demo) ──────────────────────────────── */
#define OP_NOP                      0U
#define OP_XOR                      7U
#define OP_PASS1                    17U
#define SRC_W                       4U   /* read from west neighbour port */
#define SRC_IMM                     6U   /* 16-bit immediate, sign-extended */
#define ROUTE_E                     0x4U /* route mask: east only          */

/* ── Image data: an 8x8 pixel-art letter Z ───────────────────────────── */
#define IMG_W                       8
#define IMG_H                       8
#define IMG_PIXELS                  (IMG_W * IMG_H)
#define ON                          0xFFFFFFFFU
#define OFF                         0x00000000U

/* Aligned to a 64-byte cache line so Xil_DCacheFlushRange / Invalidate
 * operate cleanly without partial-line writebacks. */
static uint32_t g_input_image[IMG_PIXELS] __attribute__((aligned(64))) = {
    ON,  ON,  ON,  ON,  ON,  ON,  ON,  ON,
    OFF, OFF, OFF, OFF, OFF, OFF, ON,  OFF,
    OFF, OFF, OFF, OFF, OFF, ON,  OFF, OFF,
    OFF, OFF, OFF, OFF, ON,  OFF, OFF, OFF,
    OFF, OFF, OFF, ON,  OFF, OFF, OFF, OFF,
    OFF, OFF, ON,  OFF, OFF, OFF, OFF, OFF,
    OFF, ON,  OFF, OFF, OFF, OFF, OFF, OFF,
    ON,  ON,  ON,  ON,  ON,  ON,  ON,  ON,
};

static uint32_t g_output_image[IMG_PIXELS] __attribute__((aligned(64)));

/* Per-chunk staging buffer the CGRA's DMA reads from. Each pixel is
 * replicated into all 16 entries of its tile bank so that the CU's
 * 16-cycle PC sweep stably reads the same value every cycle, and the
 * east-edge RESULT_ROW captures that pixel's XOR. */
static uint32_t g_chunk_stage[64] __attribute__((aligned(64)));

/* Tiny single-word buffer used for PE config double-pump DMAs */
static uint32_t g_cfg_word[1] __attribute__((aligned(64)));

/* ── ISR plumbing — globals shared between main() and cgra_isr() ─────── */
static volatile int      g_chunks_done   = 0;
static volatile int      g_all_done      = 0;
static volatile uint32_t g_total_cycles  = 0;
static          XScuGic  g_intc;

/* ── Tiny CGRA register helpers (no driver — direct AXI GP0 writes) ──
 * The Vitis 2025.1 editor runs a clangd language server that (mis-)
 * configures itself for the host x86_64 target where pointers are
 * 64 bits, so it flags the 32-bit-int-to-pointer cast. The real
 * build target is arm-none-eabi / Cortex-A9 where
 *   sizeof(uint32_t) == sizeof(void *) == 4
 * and the cast is a safe no-op, which arm-none-eabi-gcc correctly
 * accepts without any warning. Wrap the two helpers in a pragma so
 * the editor's red squiggles don't distract during live demos. */
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#endif
static inline void cgra_wr(uint32_t addr, uint32_t v)
{
    *(volatile uint32_t *)addr = v;
}
static inline uint32_t cgra_rd(uint32_t addr)
{
    return *(volatile uint32_t *)addr;
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif

/* Blocking 1D DMA wrapper. Always clears stale 2D state first. */
static void cgra_dma_blocking(uint32_t src, uint32_t dst, uint32_t bytes)
{
    cgra_wr(CGRA_DMA_SRC,        src);
    cgra_wr(CGRA_DMA_DST,        dst);
    cgra_wr(CGRA_DMA_SRC_STRIDE, 0);
    cgra_wr(CGRA_DMA_ROWS,       0);
    cgra_wr(CGRA_DMA_COLS,       0);
    cgra_wr(CGRA_DMA_SIZE,       bytes);
    cgra_wr(CGRA_DMA_CTRL,       1);
    while ((cgra_rd(CGRA_DMA_STATUS) & 0x2) == 0) { /* spin */ }
}

/* Build a 64-bit PE config word from individual fields.
 * Layout: opcode[5:0] | src0[9:6] | src1[13:10] | dst[17:14]
 *       | route[21:18] | imm[39:24]                            */
static uint64_t cgra_pe_build(uint32_t opcode, uint32_t src0, uint32_t src1,
                              uint32_t dst, uint32_t route, uint16_t imm)
{
    return ((uint64_t)opcode & 0x3F)
         | (((uint64_t)src0  & 0xF) << 6)
         | (((uint64_t)src1  & 0xF) << 10)
         | (((uint64_t)dst   & 0xF) << 14)
         | (((uint64_t)route & 0xF) << 18)
         | ((uint64_t)imm           << 24);
}

/* Write one PE's slot-0 config word. Slot 0 broadcasts to slots 1..15
 * automatically (cgra_top.sv:289), so this configures the entire 16-PC
 * context for that PE with one logical instruction. The hi32 word must
 * be written first (addr[2]=0 latches it), then the lo32 word
 * (addr[2]=1 commits the 64-bit pair and triggers the broadcast FSM). */
static void cgra_config_pe(uint32_t pe_id, uint64_t cfg)
{
    uint32_t base = CFG_BASE | (pe_id << 7);

    g_cfg_word[0] = (uint32_t)(cfg >> 32);                /* hi32 */
    Xil_DCacheFlushRange((UINTPTR)g_cfg_word, sizeof(g_cfg_word));
    cgra_dma_blocking((uint32_t)(uintptr_t)g_cfg_word, base,        4);

    g_cfg_word[0] = (uint32_t)(cfg & 0xFFFFFFFFU);        /* lo32 */
    Xil_DCacheFlushRange((UINTPTR)g_cfg_word, sizeof(g_cfg_word));
    cgra_dma_blocking((uint32_t)(uintptr_t)g_cfg_word, base | 0x4U, 4);
}

/* ── Pretty-print an 8x8 image to UART using pure 7-bit ASCII ────────
 *
 * Each ON pixel renders as "##", each OFF pixel as "  ". The earlier
 * version used UTF-8 green block characters (U+2588) wrapped in ANSI
 * color escapes, but the Vitis Serial Terminal's Eclipse-Java receive
 * pipeline occasionally drops a byte on sustained 115200-baud bursts,
 * which landed in the middle of 3-byte UTF-8 sequences and produced
 * replacement characters (U+FFFD) on screen. With pure ASCII every
 * byte is standalone, so at worst a single dropped byte turns one
 * '#' into something else rather than corrupting a whole codepoint.
 * This renders pristine in the Vitis Terminal, Hercules, PuTTY,
 * and any other terminal. For a fancier UTF-8 + green-block render,
 * use Tera Term with encoding set to UTF-8. */
static void print_ascii_image(const uint32_t *img)
{
    for (int r = 0; r < IMG_H; r++) {
        uart_puts("    ");
        for (int c = 0; c < IMG_W; c++) {
            if (img[r * IMG_W + c] == ON) {
                uart_puts("##");
            } else {
                uart_puts("  ");
            }
        }
        uart_puts("\n");
    }
}

/* ── Configure the CGRA PE array for bitwise NOT (XOR with 0xFFFFFFFF) ─
 *
 * Bitwise NOT is implemented as XOR with the all-ones constant. The 16-bit
 * immediate field sign-extends to 32 bits before reaching the ALU
 * (cgra_pe.sv:306), so IMM=0xFFFF becomes 0xFFFFFFFF — exactly what we
 * need. Verified end-to-end by the round-2 test_alu_smoke regression.
 *
 * Per row:
 *   col 0:  XOR src0=W src1=IMM=0xFFFF        → ~(west input)
 *   col 1:  PASS1 src1=W route=E              → forward east
 *   col 2:  PASS1 src1=W route=E              → forward east
 *   col 3:  PASS1 src1=W route=E              → captured by RESULT_ROWr
 *
 * The CU loop is set to one full PC sweep (PC 0..15, no inner loop). */
static void configure_cgra_for_inversion(void)
{
    /* Start with NOP everywhere (slot 0 broadcast — fills all 16 slots
     * of all 16 PEs with NOP, leaving alu_result and RF undisturbed). */
    for (int pe = 0; pe < 16; pe++) {
        cgra_config_pe(pe, cgra_pe_build(OP_NOP, 0, 0, 0, 0, 0));
    }
    /* Then overwrite the row chains with XOR + east forwarders. */
    for (int row = 0; row < 4; row++) {
        int b = row * 4;
        cgra_config_pe(b + 0, cgra_pe_build(OP_XOR,   SRC_W, SRC_IMM, 0, ROUTE_E, 0xFFFF));
        cgra_config_pe(b + 1, cgra_pe_build(OP_PASS1, 0,     SRC_W,   0, ROUTE_E, 0));
        cgra_config_pe(b + 2, cgra_pe_build(OP_PASS1, 0,     SRC_W,   0, ROUTE_E, 0));
        cgra_config_pe(b + 3, cgra_pe_build(OP_PASS1, 0,     SRC_W,   0, ROUTE_E, 0));
    }
    /* CU loop: one full PC sweep (slot 0..15, no looping). */
    cgra_wr(CGRA_LOOP_START, 0);
    cgra_wr(CGRA_LOOP_END,   0xF);
    cgra_wr(CGRA_LOOP_COUNT, 0);
}

/* ── Stage the next chunk into tile memory + kick the CU ──────────────
 *
 * One chunk = 4 pixels (one per row). We replicate each pixel into 16
 * words of its tile bank so the 16-cycle CU sweep reads the same value
 * every cycle. Cache-flush the staging buffer so the CGRA's AXI master
 * sees fresh DDR contents instead of cached stale data, then DMA each
 * 16-word slice into its bank. Finally soft-reset the CU (clears the
 * sticky DONE bit from the previous run) and start it. */
static void start_chunk(int chunk)
{
    for (int row = 0; row < 4; row++) {
        uint32_t pix = g_input_image[chunk * 4 + row];
        for (int i = 0; i < 16; i++) {
            g_chunk_stage[row * 16 + i] = pix;
        }
    }
    Xil_DCacheFlushRange((UINTPTR)g_chunk_stage, sizeof(g_chunk_stage));

    cgra_dma_blocking((uint32_t)(uintptr_t)&g_chunk_stage[ 0], TILE_BANK0, 64);
    cgra_dma_blocking((uint32_t)(uintptr_t)&g_chunk_stage[16], TILE_BANK1, 64);
    cgra_dma_blocking((uint32_t)(uintptr_t)&g_chunk_stage[32], TILE_BANK2, 64);
    cgra_dma_blocking((uint32_t)(uintptr_t)&g_chunk_stage[48], TILE_BANK3, 64);

    cgra_wr(CGRA_CU_CTRL, 2);                           /* assert soft reset */
    for (volatile int i = 0; i < 200; i++) { /* spin */ }
    cgra_wr(CGRA_CU_CTRL, 0);                           /* release reset    */
    cgra_wr(CGRA_CU_CTRL, 1);                           /* start CU run     */
}

/* ── Interrupt Service Routine ────────────────────────────────────────
 *
 * Called by the Vitis BSP's XScuGic_InterruptHandler when the CGRA
 * raises its IRQ line (level-high, GIC ID 61, mapped from IRQ_F2P[0]).
 *
 * The ISR:
 *   1. W1Cs the CGRA-side IRQ_STATUS so the level-high `irq` line drops
 *      (the GIC re-fires immediately if any status bit is still set).
 *   2. Reads the four RESULT_ROW registers — these hold the PE output
 *      from the LAST cycle of the just-finished CU run, which is each
 *      row's pixel inversion.
 *   3. Accumulates the cycle count from CU_CYCLES.
 *   4. If more chunks remain, kicks the next one and the CGRA fires
 *      another IRQ when that one finishes.
 *   5. Otherwise sets g_all_done = 1, which lets main()'s wfi loop exit.  */
static void cgra_isr(void *callback_ref)
{
    (void)callback_ref;

    uint32_t s = cgra_rd(CGRA_IRQ_STATUS);
    cgra_wr(CGRA_IRQ_STATUS, s & 0x7U);   /* W1C every set bit */

    int chunk = g_chunks_done;
    g_output_image[chunk * 4 + 0] = cgra_rd(CGRA_RESULT_ROW0);
    g_output_image[chunk * 4 + 1] = cgra_rd(CGRA_RESULT_ROW1);
    g_output_image[chunk * 4 + 2] = cgra_rd(CGRA_RESULT_ROW2);
    g_output_image[chunk * 4 + 3] = cgra_rd(CGRA_RESULT_ROW3);
    g_total_cycles += cgra_rd(CGRA_CU_CYCLES);
    g_chunks_done++;

    if (g_chunks_done < 16) {
        start_chunk(g_chunks_done);
    } else {
        g_all_done = 1;
    }
}

/* ── Bridge from our hand-rolled start.s IRQ vector to the Vitis BSP ──
 *
 * Only used in the WSL2 build path: our 07_sw/baremetal/start.s vector
 * at OCM 0x4018 calls `bl gic_irq_entry`, which lands here. We just
 * forward to the BSP's standard XScuGic dispatcher. On Windows Vitis
 * Workbench this function is dead code (Vitis BSP boot.S installs its
 * own IRQ vector that calls XScuGic_InterruptHandler directly), and
 * the linker's --gc-sections drops it from the final ELF.   */
void gic_irq_entry(void)
{
    XScuGic_InterruptHandler(&g_intc);
}

/* ── Set up the Vitis ScuGic driver and register our ISR ─────────── */
static int setup_interrupt_system(void)
{
    XScuGic_Config *cfg;
    int status;

    cfg = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
    if (cfg == 0) return XST_FAILURE;

    status = XScuGic_CfgInitialize(&g_intc, cfg, cfg->CpuBaseAddress);
    if (status != XST_SUCCESS) return status;

    /* Register cgra_isr as the handler for the CGRA IRQ ID. */
    status = XScuGic_Connect(&g_intc,
                             DEMO_CGRA_IRQ_ID,
                             (Xil_InterruptHandler)cgra_isr,
                             (void *)0);
    if (status != XST_SUCCESS) return status;

    /* Configure the IRQ as level-high (matches the CGRA's irq output:
     * apb_csr asserts the line whenever (IRQ_STATUS & IRQ_MASK) != 0). */
    XScuGic_SetPriorityTriggerType(&g_intc,
                                   DEMO_CGRA_IRQ_ID,
                                   0xA0U,    /* priority */
                                   0x1U);    /* 0x1 = level-sensitive, active-high */
    XScuGic_Enable(&g_intc, DEMO_CGRA_IRQ_ID);

    /* Hook the ARM exception vector. On Windows this is what installs
     * the BSP's IRQ handler chain. On WSL2 our start.s already has its
     * own vector — these calls are harmless duplicates. */
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
                                 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
                                 &g_intc);
    Xil_ExceptionEnable();

    return XST_SUCCESS;
}

/* =========================================================================
 * main
 * ========================================================================= */
int main(void)
{
    /* Turn on the L1 caches so the Xil_DCache* calls below actually
     * exercise real cache management. (On WSL2 standalone without an
     * MMU, the dcache stays bypassed and the calls are effectively
     * no-ops, but they're present for educational purposes and
     * activate automatically on the Windows Vitis Workbench port
     * which gets a full MMU + cache setup from the BSP boot code.) */
    Xil_DCacheEnable();
    Xil_ICacheEnable();

    uart_puts("\n");
    uart_puts("==========================================\n");
    uart_puts("  CGRA ASCII Image Accelerator Demo\n");
    uart_puts("  Inverts an 8x8 letter 'Z' via the CGRA\n");
    uart_puts("==========================================\n");

    uart_puts("\n[ARM] Original Image:\n");
    print_ascii_image(g_input_image);

    /* ── Stand up the GIC and register our ISR ────────────────────── */
    if (setup_interrupt_system() != XST_SUCCESS) {
        uart_puts("\n[ERROR] GIC setup failed!\n");
        return -1;
    }

    /* Configure the CGRA's IRQ_MASK so only CU-done fires the line.
     * (DMA-done would otherwise also fire and pollute our chunk pump.) */
    cgra_wr(CGRA_IRQ_STATUS, 0x7U);            /* clear any stale bits */
    cgra_wr(CGRA_IRQ_MASK,   IRQ_CU_DONE);

    /* Build the PE configuration once — it persists across CU runs. */
    configure_cgra_for_inversion();

    /* Cache-flush the input image so the CGRA's AXI master reads
     * the fresh DDR contents instead of stale cached lines. */
    Xil_DCacheFlushRange((UINTPTR)g_input_image, sizeof(g_input_image));

    /* Reset the chunk-pump state and kick chunk 0. The ISR will
     * re-arm the next chunk every time the previous one finishes. */
    g_chunks_done  = 0;
    g_all_done     = 0;
    g_total_cycles = 0;
    start_chunk(0);

    uart_puts("\n[ARM] CGRA is running. CPU goes to sleep "
              "waiting for IRQ...\n");

    /* The user-spec'd single blocking wait. Behind the scenes the ISR
     * fires 16 times (once per chunk) — the wfi wakes for each fire,
     * the loop predicate stays false until the 16th chunk completes,
     * then g_all_done flips to 1 and we drop out cleanly. */
    while (!g_all_done) {
        __asm__ volatile ("wfi");
    }

    /* Note: do NOT Xil_DCacheInvalidateRange(g_output_image). That array
     * is filled by the ISR's own ARM stores (not by a peripheral DMA),
     * so it lives entirely inside the Cortex-A9 cache — no coherency
     * action is needed. On Cortex-A9 with write-back dcache enabled,
     * invalidate-by-MVA on a DIRTY line actually *drops* the pending
     * writebacks, which would zero the whole output array. Only buffers
     * that a DMA engine writes into (from outside the CPU) need
     * invalidation after the DMA. */

    uart_puts("\n[IRQ] Interrupt received! CGRA Finished.\n");

    uart_puts("\n[ARM] Processed Image (Inverted):\n");
    print_ascii_image(g_output_image);

    uart_puts("\n[STAT] Hardware processing took ");
    uart_putdec(g_total_cycles);
    uart_puts(" cycles (16 chunks).\n");
    uart_puts("==========================================\n");

    /* Done — disable IRQs, drop the caches, park forever. */
    Xil_ExceptionDisable();
    Xil_DCacheDisable();
    Xil_ICacheDisable();

    while (1) {
        __asm__ volatile ("wfi");
    }
    return 0;
}
