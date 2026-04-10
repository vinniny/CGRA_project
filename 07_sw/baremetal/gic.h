/* =========================================================================
 * gic.h — Bare-metal ARMv7-A GIC v1 driver for Zynq-7000 (Cortex-A9 MPCore)
 *
 * Distributor base : 0xF8F01000   (per-IRQ enable, priority, target CPU)
 * CPU interface    : 0xF8F00100   (acknowledge, end-of-interrupt, mask)
 *
 * Single-IRQ usage path:
 *   1. gic_init();                          // distributor + CPU interface
 *   2. gic_register_isr(id, handler, ctx);  // store callback
 *   3. gic_enable_irq(id, prio, cpu_mask);  // unmask in distributor
 *   4. cpu_irq_enable();                    // CPSR I-bit clear
 *   5. handler() runs in IRQ mode when the line asserts
 *   6. gic_acknowledge() / gic_eoi() are called by the IRQ vector entry,
 *      not by user code — the dispatcher in start.s does that.
 *
 * Reference: ARM IHI 0048B (GICv1 spec) + Zynq-7000 TRM (UG585) chapter 7.
 * ========================================================================= */
#ifndef GIC_H
#define GIC_H

#include <stdint.h>

/* ── Zynq-7000 GIC base addresses ─────────────────────────────────────── */
#define GIC_DIST_BASE   0xF8F01000UL
#define GIC_CPU_BASE    0xF8F00100UL

/* ── Distributor registers ────────────────────────────────────────────── */
#define GICD_CTLR       (GIC_DIST_BASE + 0x000)   /* Distributor enable     */
#define GICD_TYPER      (GIC_DIST_BASE + 0x004)   /* IRQ count info         */
#define GICD_ISENABLER0 (GIC_DIST_BASE + 0x100)   /* Set-enable, 32 IRQs/word*/
#define GICD_ICENABLER0 (GIC_DIST_BASE + 0x180)   /* Clear-enable           */
#define GICD_IPRIORITYR (GIC_DIST_BASE + 0x400)   /* 8-bit priority per IRQ */
#define GICD_ITARGETSR  (GIC_DIST_BASE + 0x800)   /* 8-bit CPU mask per IRQ */
#define GICD_ICFGR      (GIC_DIST_BASE + 0xC00)   /* 2-bit config per IRQ   */

/* ── CPU interface registers ──────────────────────────────────────────── */
#define GICC_CTLR       (GIC_CPU_BASE  + 0x00)    /* CPU enable             */
#define GICC_PMR        (GIC_CPU_BASE  + 0x04)    /* Priority mask          */
#define GICC_BPR        (GIC_CPU_BASE  + 0x08)    /* Binary point           */
#define GICC_IAR        (GIC_CPU_BASE  + 0x0C)    /* Acknowledge (read)     */
#define GICC_EOIR       (GIC_CPU_BASE  + 0x10)    /* End of interrupt       */

/* ── ISR table (small — sized for the largest IRQ ID we need) ─────────── */
#define GIC_NUM_IRQS    96u   /* covers SPIs up to ID 95; CGRA = 61 */

typedef void (*gic_isr_fn)(void *ctx);

extern volatile gic_isr_fn g_gic_isr[GIC_NUM_IRQS];
extern volatile void      *g_gic_ctx[GIC_NUM_IRQS];

/* ── Register IO inlines ─────────────────────────────────────────────── */
static inline void gic_wr(uint32_t addr, uint32_t v) {
    *(volatile uint32_t *)addr = v;
}
static inline uint32_t gic_rd(uint32_t addr) {
    return *(volatile uint32_t *)addr;
}

/* ── CPSR I-bit ──────────────────────────────────────────────────────── */
static inline void cpu_irq_enable(void)  { asm volatile("cpsie i" ::: "memory"); }
static inline void cpu_irq_disable(void) { asm volatile("cpsid i" ::: "memory"); }

/* ── Initialize the GIC distributor + CPU interface ──────────────────── */
static inline void gic_init(void)
{
    /* Disable the distributor and CPU interface while we configure */
    gic_wr(GICD_CTLR, 0);
    gic_wr(GICC_CTLR, 0);

    /* Allow all priority levels to interrupt the CPU */
    gic_wr(GICC_PMR, 0xFF);

    /* No sub-priority — full preemption granularity */
    gic_wr(GICC_BPR, 0x03);

    /* Enable the CPU interface and distributor */
    gic_wr(GICC_CTLR, 0x1);
    gic_wr(GICD_CTLR, 0x1);

    /* Clear the ISR table */
    for (unsigned i = 0; i < GIC_NUM_IRQS; i++) {
        g_gic_isr[i] = (gic_isr_fn)0;
        g_gic_ctx[i] = (void *)0;
    }
}

/* ── Per-IRQ configuration: priority + target CPU + enable ───────────── */
static inline void gic_set_priority(uint32_t irq_id, uint8_t prio)
{
    /* IPRIORITYR is byte-addressable, 1 byte per IRQ */
    *(volatile uint8_t *)(GICD_IPRIORITYR + irq_id) = prio;
}

static inline void gic_set_target(uint32_t irq_id, uint8_t cpu_mask)
{
    /* ITARGETSR is byte-addressable, 1 byte per IRQ.
     * Note: SGIs (ID 0-15) and PPIs (ID 16-31) ignore the target field. */
    *(volatile uint8_t *)(GICD_ITARGETSR + irq_id) = cpu_mask;
}

static inline void gic_set_level_high(uint32_t irq_id)
{
    /* GICD_ICFGR: 2 bits per IRQ. bit[1] = 1 → edge, 0 → level.
     * SPIs start at IRQ 32, so the field index for irq 32 is in word 2.
     * 16 IRQs per 32-bit word. */
    uint32_t word_off = (irq_id / 16) * 4;
    uint32_t bit_off  = (irq_id % 16) * 2;
    uint32_t v = gic_rd(GICD_ICFGR + word_off);
    v &= ~(0x3u << bit_off);          /* clear both bits → level-sensitive */
    gic_wr(GICD_ICFGR + word_off, v);
}

static inline void gic_enable_irq_id(uint32_t irq_id)
{
    /* GICD_ISENABLERn: write 1 to set, 1 IRQ per bit, 32 IRQs per word */
    uint32_t word_off = (irq_id / 32) * 4;
    uint32_t bit      = (uint32_t)(1u << (irq_id % 32));
    gic_wr(GICD_ISENABLER0 + word_off, bit);
}

static inline void gic_disable_irq_id(uint32_t irq_id)
{
    uint32_t word_off = (irq_id / 32) * 4;
    uint32_t bit      = (uint32_t)(1u << (irq_id % 32));
    gic_wr(GICD_ICENABLER0 + word_off, bit);
}

/* Register an ISR for a given IRQ id and configure the distributor entry. */
static inline void gic_register_isr(uint32_t irq_id, gic_isr_fn fn, void *ctx,
                                    uint8_t prio, uint8_t cpu_mask)
{
    if (irq_id >= GIC_NUM_IRQS) return;
    g_gic_isr[irq_id] = fn;
    g_gic_ctx[irq_id] = ctx;
    gic_set_priority(irq_id, prio);
    gic_set_target  (irq_id, cpu_mask);
    gic_set_level_high(irq_id);
    gic_enable_irq_id(irq_id);
}

/* ── Top-half dispatch — called from the IRQ vector in start.s ──────── */
/* Reads GICC_IAR, calls the registered handler, writes GICC_EOIR. */
static inline void gic_irq_dispatch(void)
{
    uint32_t iar = gic_rd(GICC_IAR);
    uint32_t id  = iar & 0x3FFu;          /* IRQ ID is bits [9:0] */
    if (id < GIC_NUM_IRQS) {
        gic_isr_fn fn = g_gic_isr[id];
        if (fn) fn((void *)g_gic_ctx[id]);
    }
    /* Spurious IDs (1023) and unregistered IDs both fall through to EOI. */
    gic_wr(GICC_EOIR, iar);
}

/* CGRA IRQ ID on this Zynq-7000 design:
 *   IRQ_F2P[0] = SPI #29 → GIC ID 29 + 32 = 61. */
#define CGRA_IRQ_ID  61u

#endif /* GIC_H */
