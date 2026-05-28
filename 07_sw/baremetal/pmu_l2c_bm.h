/* pmu_l2c_bm.h — PL310 L2C-310 event counter helpers for Zynq-7000.
 *
 * Cortex-A9 CP15 PMU (already provided by cgra.h:165-185) is L1-only.
 * For L2 hits/misses we must use the PL310 controller MMIO at
 * 0xF8F02000. Two 32-bit event counters; we wire counter 0 = data-read
 * request, counter 1 = data-read hit. L1D-refill / total-read / hit
 * rates can then be computed from CCNT + L1D-refill (CP15) + these.
 *
 * TrustZone gotcha (per senior review §15): if FSBL drops us to
 * Non-Secure EL1, PL310 event counter writes silently fail or trigger
 * a synchronous Data Abort. Xilinx FSBL leaves us in Secure EL1 for
 * bare-metal so this should not bite, but if it ever does, document
 * the symptom (zeros read back / Data Abort) here.
 */
#ifndef PMU_L2C_BM_H
#define PMU_L2C_BM_H

#include <stdint.h>

void     pmu_l2c_init(void);          /* counter0=DRREQ, counter1=DRHIT, enable */
void     pmu_l2c_reset(void);         /* zero both counters, keep enabled */
uint32_t pmu_l2c_read_reqs(void);     /* total L2 data-read requests */
uint32_t pmu_l2c_read_hits(void);     /* L2 data-read hits */

#endif /* PMU_L2C_BM_H */
