/* =============================================================================
 * cgra_baremetal_shim.h — Make baremetal cgra.h + cgra_kernels_*.h work in
 * Linux user-space.
 *
 * Usage (in a Linux .c file):
 *
 *   #include "cgra_baremetal_shim.h"   // BEFORE cgra.h — overrides CGRA_BASE
 *   #include "cgra.h"
 *   #include "cgra_kernels_lpr.h"
 *
 *   int main(void) {
 *       cgra_dev_t dev = {0};
 *       cgra_init(&dev, NULL);
 *       cgra_shim_attach(&dev);          // route CGRA_BASE to dev->regs
 *       lpr_fc_init_chain(0x3FFF0100u);  // baremetal FC kernel just works
 *       cgra_close(&dev);
 *   }
 *
 * What it does:
 *   - Defines CGRA_BASE as a runtime expression pointing to the user-space mmap'd
 *     APB CSR window (cgra_dev_t::regs). The baremetal cgra.h's static inline
 *     cgra_wr/cgra_rd then route through the shim's pointer transparently.
 *   - Stubs out arm_ccnt_*() (Cortex-A9 PMU cycle counter) — Linux user-space
 *     can't access PMU; map to clock_gettime if profiling is needed.
 * ============================================================================= */
#ifndef CGRA_BAREMETAL_SHIM_H
#define CGRA_BAREMETAL_SHIM_H

#include <stdint.h>
#include <time.h>

#include "../driver/cgra_driver.h"

/* ── Runtime base pointer set by cgra_shim_attach() ─────────────────────────
 * This is a uintptr_t so it can be substituted for CGRA_BASE (which is used
 * as `*(volatile uint32_t *)(CGRA_BASE + off)` in baremetal cgra_wr/cgra_rd). */
extern uintptr_t _cgra_shim_base;

static inline void cgra_shim_attach(cgra_dev_t *dev)
{
    _cgra_shim_base = (uintptr_t)dev->regs;
}

/* Force baremetal cgra.h to use the runtime base.
 * cgra.h has `#ifndef CGRA_BASE` guard so this define wins. */
#define CGRA_BASE  _cgra_shim_base

/* Note: cgra.h's arm_pmu_enable / arm_ccnt_read / arm_ccnt_reset use Cortex-A9
 * PMU coprocessor instructions that would SIGILL in user-space. They're only
 * referenced inside `#ifdef LPR_CGRA_PROFILE` blocks in the kernels, so as
 * long as we don't define LPR_CGRA_PROFILE the references are dead. If profiling
 * is later needed, replace them with clock_gettime in a separate translation
 * unit. */

#endif /* CGRA_BAREMETAL_SHIM_H */
