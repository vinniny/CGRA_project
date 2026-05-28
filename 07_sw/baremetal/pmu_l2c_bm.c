/* pmu_l2c_bm.c — PL310 L2C-310 event counter access at 0xF8F02000.
 *
 * Register map (PL310 r3p2 TRM, also Zynq-7000 TRM UG585 §3.4):
 *   0x100 ctrl_reg            (bit 0 = L2 enable)
 *   0x200 event_counter_ctrl  (bit 0 = enable; bits 1..2 = reset cnt1/0)
 *   0x204 event_counter1_cfg  (bits 5..2 = event source code)
 *   0x208 event_counter0_cfg  (bits 5..2 = event source code)
 *   0x20C event_counter1_val  (32-bit count, write 0 to reset)
 *   0x210 event_counter0_val  (32-bit count)
 *
 * Event source codes (TRM Table 2-9):
 *   0x3 = DRREQ — data-read request          (total)
 *   0x2 = DRHIT — data-read hit              (hits)
 *   misses = DRREQ - DRHIT
 */

#include "pmu_l2c_bm.h"

#define PL310_BASE        0xF8F02000u
#define REG(off)          (*(volatile uint32_t *)(PL310_BASE + (off)))

#define PL310_EVCNT_CTRL  REG(0x200)
#define PL310_EVCNT1_CFG  REG(0x204)
#define PL310_EVCNT0_CFG  REG(0x208)
#define PL310_EVCNT1_VAL  REG(0x20C)
#define PL310_EVCNT0_VAL  REG(0x210)

#define L2C_EVENT_DRREQ   0x3u
#define L2C_EVENT_DRHIT   0x2u

void pmu_l2c_init(void)
{
    /* Disable counters before reconfiguring source */
    PL310_EVCNT_CTRL = 0u;
    /* Counter cfg: bits [5:2] = event source, bits [1:0] = interrupt (off) */
    PL310_EVCNT0_CFG = (L2C_EVENT_DRREQ << 2);
    PL310_EVCNT1_CFG = (L2C_EVENT_DRHIT << 2);
    /* Zero counters then enable */
    PL310_EVCNT0_VAL = 0u;
    PL310_EVCNT1_VAL = 0u;
    PL310_EVCNT_CTRL = 0x1u;
}

void pmu_l2c_reset(void)
{
    /* Bits 1..2: reset counter0/1. Self-clearing after one cycle. */
    PL310_EVCNT_CTRL = (PL310_EVCNT_CTRL & ~0x6u) | 0x6u | 0x1u;
}

uint32_t pmu_l2c_read_reqs(void) { return PL310_EVCNT0_VAL; }
uint32_t pmu_l2c_read_hits(void) { return PL310_EVCNT1_VAL; }
