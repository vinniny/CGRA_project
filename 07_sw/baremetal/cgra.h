/* =========================================================================
 * cgra.h — Bare-metal CGRA register access + programming helpers
 *
 * Register base: 0x43C00000 (AXI GP0 on Zynq-7000)
 * DMA address prefixes:
 *   0x0XXXXXXX → External DDR (AXI4 master read/write)
 *   0x1XXXXXXX → Tile Memory (local distributed SRAM)
 *   0x2XXXXXXX → PE Config RAM (double-pump 64-bit)
 * ========================================================================= */
#ifndef CGRA_H
#define CGRA_H

#include <stdint.h>

/* ── DMA staging note ─────────────────────────────────────────────────── */
/* Use OCM (0x00020000) as DMA staging — DDR may not be configured yet.    */
/* OCM is reachable by CGRA DMA engine via the PS AXI HP slave port.       */

/* ── Base address ─────────────────────────────────────────────────────── */
#define CGRA_BASE           0x43C00000UL

/* ── DMA address space prefixes ───────────────────────────────────────── */
#define CGRA_PFX_AXI        0x00000000UL   /* External DDR */
#define CGRA_PFX_TILE       0x10000000UL   /* Tile memory */
#define CGRA_PFX_CONFIG     0x20000000UL   /* PE config RAM */

/* ── Register offsets (mirrors cgra_driver.h) ─────────────────────────── */
#define CGRA_DMA_CTRL        0x00
#define CGRA_DMA_STATUS      0x04
#define CGRA_DMA_SRC         0x08
#define CGRA_DMA_DST         0x0C
#define CGRA_DMA_SIZE        0x10
#define CGRA_DMA_SRC_STRIDE  0x14
#define CGRA_DMA_ROWS        0x18
#define CGRA_DMA_COLS        0x1C
#define CGRA_CU_CTRL         0x20
#define CGRA_CU_STATUS       0x24
#define CGRA_CU_CYCLES       0x28
#define CGRA_CU_TIMEOUT      0x2C
#define CGRA_IRQ_STATUS      0x30
#define CGRA_IRQ_MASK        0x34
#define CGRA_DMA_ERROR       0x38
#define CGRA_RESULT_DATA     0x40
#define CGRA_RESULT_STATUS   0x44
#define CGRA_LOOP_START      0x48
#define CGRA_LOOP_END        0x4C
#define CGRA_LOOP_COUNT      0x50
#define CGRA_RESULT_ROW0     0x58
#define CGRA_RESULT_ROW1     0x5C
#define CGRA_RESULT_ROW2     0x60
#define CGRA_RESULT_ROW3     0x64
#define CGRA_LOOP2_START     0x68
#define CGRA_LOOP2_END       0x6C
#define CGRA_LOOP2_COUNT     0x70
#define CGRA_TILE_BANK_SEL   0x74
#define CGRA_TILE_AUTO_INC   0x78

/* ── ISA opcodes ──────────────────────────────────────────────────────── */
#define OP_NOP        0u
#define OP_ADD        1u
#define OP_SUB        2u
#define OP_MUL        3u
#define OP_MAC        4u
#define OP_AND        5u
#define OP_OR         6u
#define OP_XOR        7u
#define OP_SHL        8u
#define OP_SHR        9u
#define OP_CMP_GT    10u
#define OP_CMP_LT    11u
#define OP_CMP_EQ    12u
#define OP_LOAD_SPM  13u
#define OP_STORE_SPM 14u
#define OP_ACC_CLR   15u
#define OP_PASS0     16u   /* result = src0 */
#define OP_PASS1     17u   /* result = src1 */
#define OP_LIF       18u
#define OP_RELU      19u
#define OP_MAX       20u

/* ── Status bit fields ────────────────────────────────────────────────── */
#define DMA_STATUS_BUSY  0x1u
#define DMA_STATUS_DONE  0x2u
#define CU_STATUS_BUSY   0x1u
#define CU_STATUS_DONE   0x2u
#define IRQ_DMA_DONE     0x1u
#define IRQ_CU_DONE      0x2u
#define IRQ_DMA_ERR      0x4u

/* ── Source selectors ─────────────────────────────────────────────────── */
#define SRC_RF      0u    /* Register file RF[0] */
#define SRC_N       1u    /* North neighbor output */
#define SRC_E       2u    /* East neighbor output */
#define SRC_S       3u    /* South neighbor output */
#define SRC_W       4u    /* West neighbor / tile port */
#define SRC_SPM     5u    /* Scratchpad */
#define SRC_IMM     6u    /* 16-bit immediate (sign-extended) */

/* ── Route mask bits [21:18] → East=bit20, which is bit2 of the field ─── */
#define ROUTE_N     0x8u  /* bit 21 */
#define ROUTE_E     0x4u  /* bit 20 */
#define ROUTE_S     0x2u  /* bit 19 */
#define ROUTE_W     0x1u  /* bit 18 */

/* ── Tile address auto-increment ──────────────────────────────────────── */
/* When enabled, tile memory address auto-advances by 16 words on each
 * hardware loop iteration. Pre-load tile with sequential data, run with
 * LOOP_COUNT=N to process N+1 chunks of 16 words in one CU pass. */
static inline void cgra_tile_auto_inc(int enable)
{
    cgra_wr(CGRA_TILE_AUTO_INC, enable ? 1u : 0u);
}

/* ── Data mode (SIMD) — config bits [50:49] = extended[10:9] ─────────── */
#define DATA_MODE_INT32   0u   /* 1× 32-bit (default) */
#define DATA_MODE_INT16X2 1u   /* 2× 16-bit SIMD */
#define DATA_MODE_INT8X4  2u   /* 4× 8-bit SIMD */

/* ── ARM Cortex-A9 Performance Monitor cycle counter (PMCCNTR) ───────── */
/* Runs at CPU clock (666.67 MHz). 32-bit, wraps at ~6.4 s. */
static inline void arm_pmu_enable(void)
{
    uint32_t v;
    asm volatile("mrc p15, 0, %0, c9, c12, 0" : "=r"(v));  /* PMCR */
    v |= 0x5u;   /* bit 0 = enable, bit 2 = reset CCNT */
    asm volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(v));
    asm volatile("mcr p15, 0, %0, c9, c12, 1" :: "r"(1u << 31));  /* PMCNTENSET: enable CCNT */
}
static inline uint32_t arm_ccnt_read(void)
{
    uint32_t v;
    asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(v));  /* PMCCNTR */
    return v;
}
static inline void arm_ccnt_reset(void)
{
    uint32_t v;
    asm volatile("mrc p15, 0, %0, c9, c12, 0" : "=r"(v));
    v |= 0x4u;   /* bit 2 = reset CCNT */
    asm volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(v));
}

/* ── Register access ──────────────────────────────────────────────────── */
static inline void cgra_wr(uint32_t off, uint32_t v) {
    *(volatile uint32_t *)(CGRA_BASE + off) = v;
}
static inline uint32_t cgra_rd(uint32_t off) {
    return *(volatile uint32_t *)(CGRA_BASE + off);
}

/* ── DMA polling ──────────────────────────────────────────────────────── */
static inline int cgra_dma_done(void)
{
    return (cgra_rd(CGRA_DMA_STATUS) & DMA_STATUS_DONE) != 0;
}
static inline int cgra_dma_busy(void)
{
    return (cgra_rd(CGRA_DMA_STATUS) & DMA_STATUS_BUSY) != 0;
}
static inline int cgra_dma_wait(uint32_t timeout)
{
    while (timeout--) {
        if (cgra_dma_done()) return 0;
    }
    return -1;
}

/* ── Async 1D DMA — kick the engine and return immediately ───────────── */
static inline void cgra_dma_start(uint32_t src, uint32_t dst, uint32_t bytes)
{
    cgra_wr(CGRA_DMA_SRC,        src);
    cgra_wr(CGRA_DMA_DST,        dst);
    cgra_wr(CGRA_DMA_SRC_STRIDE, 0u);
    cgra_wr(CGRA_DMA_ROWS,       0u);
    cgra_wr(CGRA_DMA_COLS,       0u);
    cgra_wr(CGRA_DMA_SIZE,       bytes);
    cgra_wr(CGRA_DMA_CTRL,       1u);
}

/* ── Blocking 1D DMA — wraps start + wait ────────────────────────────── */
static inline int cgra_dma(uint32_t src, uint32_t dst, uint32_t bytes)
{
    cgra_dma_start(src, dst, bytes);
    return cgra_dma_wait(1000000u);
}

/* ── Async CU control ────────────────────────────────────────────────── */
static inline int cgra_cu_done(void)
{
    return (cgra_rd(CGRA_CU_STATUS) & CU_STATUS_DONE) != 0;
}
static inline int cgra_cu_busy(void)
{
    return (cgra_rd(CGRA_CU_STATUS) & CU_STATUS_BUSY) != 0;
}
static inline void cgra_cu_start(void)
{
    cgra_wr(CGRA_CU_CTRL, 1u);
}
static inline int cgra_cu_wait(uint32_t timeout)
{
    while (timeout--) {
        if (cgra_cu_done()) return 0;
    }
    return -1;
}

/* ── Wait for both DMA and CU done with one timeout (concurrency test) ─ */
static inline int cgra_wait_dma_and_cu(uint32_t timeout)
{
    while (timeout--) {
        if (cgra_dma_done() && cgra_cu_done()) return 0;
    }
    return -1;
}

/* ── 2D strided DMA transfer ──────────────────────────────────────────── */
static inline int cgra_dma_2d(uint32_t src, uint32_t dst,
                              uint32_t rows, uint32_t cols_bytes,
                              uint32_t src_stride)
{
    cgra_wr(CGRA_DMA_SRC,        src);
    cgra_wr(CGRA_DMA_DST,        dst);
    cgra_wr(CGRA_DMA_SRC_STRIDE, src_stride);
    cgra_wr(CGRA_DMA_ROWS,       rows);
    cgra_wr(CGRA_DMA_COLS,       cols_bytes);
    cgra_wr(CGRA_DMA_SIZE,       rows * cols_bytes);
    cgra_wr(CGRA_DMA_CTRL,       1u);
    return cgra_dma_wait(1000000u);
}

/* ── Soft reset CU ────────────────────────────────────────────────────── */
static inline void cgra_cu_reset(void)
{
    cgra_wr(CGRA_CU_CTRL, 2u);   /* assert soft_reset */
    for (volatile int i = 0; i < 100; i++) asm volatile("nop");
    cgra_wr(CGRA_CU_CTRL, 0u);   /* release */
    for (volatile int i = 0; i < 50;  i++) asm volatile("nop");
}

/* ── Configure one PE (slot 0 — auto-broadcasts to all 16 slots) ──────── */
/* Config word layout: {24'd0, imm[15:0], 2'b00, route[3:0], dst[3:0],   */
/*                      src1[3:0], src0[3:0], opcode[5:0]}               */
/* Double-pump: write hi32 first (addr[2]=0), then lo32 (addr[2]=1)       */
static inline void cgra_pe_build(uint64_t *out,
                                  uint32_t opcode,
                                  uint32_t src0, uint32_t src1,
                                  uint32_t dst,  uint32_t route,
                                  uint16_t imm)
{
    uint64_t cfg = ((uint64_t)opcode & 0x3F)
                 | (((uint64_t)src0  & 0xF) << 6)
                 | (((uint64_t)src1  & 0xF) << 10)
                 | (((uint64_t)dst   & 0xF) << 14)
                 | (((uint64_t)route & 0xF) << 18)
                 | ((uint64_t)imm           << 24);
    *out = cfg;
}

/* Write a single 64-bit config word to PE[pe_id], slot[slot_idx].
 * Address layout for the PE Config RAM (cgra_top.sv:362-366):
 *   addr = 0x20000000 | (pe_id << 7) | (slot_idx << 3) | (hi_lo << 2)
 * Slot 0 writes auto-broadcast to slots 1..15 (cgra_top.sv:289). To get a
 * heterogeneous N-instruction program, write slot 0 first, then explicitly
 * overwrite slots 1..N-1. The broadcast FSM completes in 15 cycles, well
 * within DMA serialization, so subsequent slot writes land cleanly. */
static inline int cgra_config_pe_slot(uint32_t pe_id, uint32_t slot_idx,
                                      uint32_t staging_ddr,
                                      uint32_t opcode,
                                      uint32_t src0, uint32_t src1,
                                      uint32_t dst,  uint32_t route,
                                      uint16_t imm)
{
    uint64_t cfg;
    cgra_pe_build(&cfg, opcode, src0, src1, dst, route, imm);

    uint32_t hi32 = (uint32_t)(cfg >> 32);
    uint32_t lo32 = (uint32_t)(cfg & 0xFFFFFFFF);
    uint32_t cfg_base = CGRA_PFX_CONFIG
                      | ((pe_id & 0xF)   << 7)
                      | ((slot_idx & 0xF) << 3);

    volatile uint32_t *staging = (volatile uint32_t *)staging_ddr;

    /* Write HI word → addr[2]=0 (latches upper 32b) */
    *staging = hi32;
    if (cgra_dma(staging_ddr, cfg_base, 4u)) return -1;

    /* Write LO word → addr[2]=1 (commits 64-bit; if slot=0 also broadcasts) */
    *staging = lo32;
    if (cgra_dma(staging_ddr, cfg_base | 0x4u, 4u)) return -1;

    return 0;
}

/* Backwards-compatible single-slot helper — writes slot 0 (broadcasts). */
static inline int cgra_config_pe(uint32_t pe_id, uint32_t staging_ddr,
                                   uint32_t opcode,
                                   uint32_t src0, uint32_t src1,
                                   uint32_t dst,  uint32_t route,
                                   uint16_t imm)
{
    return cgra_config_pe_slot(pe_id, 0, staging_ddr,
                               opcode, src0, src1, dst, route, imm);
}

/* ── Extended config builder (with data_mode for SIMD) ───────────────── */
/* Config word layout with data_mode:
 *   [5:0]   opcode       [9:6]   src0_sel    [13:10] src1_sel
 *   [17:14] dst_sel      [21:18] route_mask  [23:22] pred_en/inv
 *   [39:24] immediate    [50:49] data_mode   [63:51] other extended */
static inline void cgra_pe_build_ex(uint64_t *out,
                                     uint32_t opcode,
                                     uint32_t src0, uint32_t src1,
                                     uint32_t dst,  uint32_t route,
                                     uint16_t imm,
                                     uint32_t data_mode)
{
    uint64_t cfg = ((uint64_t)opcode & 0x3F)
                 | (((uint64_t)src0  & 0xF) << 6)
                 | (((uint64_t)src1  & 0xF) << 10)
                 | (((uint64_t)dst   & 0xF) << 14)
                 | (((uint64_t)route & 0xF) << 18)
                 | ((uint64_t)imm           << 24)
                 | (((uint64_t)data_mode & 0x3) << 49);
    *out = cfg;
}

static inline int cgra_config_pe_slot_ex(uint32_t pe_id, uint32_t slot_idx,
                                          uint32_t staging_ddr,
                                          uint32_t opcode,
                                          uint32_t src0, uint32_t src1,
                                          uint32_t dst,  uint32_t route,
                                          uint16_t imm,
                                          uint32_t data_mode)
{
    uint64_t cfg;
    cgra_pe_build_ex(&cfg, opcode, src0, src1, dst, route, imm, data_mode);

    uint32_t hi32 = (uint32_t)(cfg >> 32);
    uint32_t lo32 = (uint32_t)(cfg & 0xFFFFFFFF);
    uint32_t cfg_base = CGRA_PFX_CONFIG
                      | ((pe_id & 0xF)   << 7)
                      | ((slot_idx & 0xF) << 3);

    volatile uint32_t *staging = (volatile uint32_t *)staging_ddr;

    *staging = hi32;
    if (cgra_dma(staging_ddr, cfg_base, 4u)) return -1;

    *staging = lo32;
    if (cgra_dma(staging_ddr, cfg_base | 0x4u, 4u)) return -1;

    return 0;
}

#endif /* CGRA_H */
