/* gic.c — storage for the GIC ISR table + non-inline dispatch entry that
 * the IRQ vector in start.s can `bl` to (the gic.h dispatch is `static
 * inline` and not visible from assembly). */
#include "gic.h"

volatile gic_isr_fn g_gic_isr[GIC_NUM_IRQS];
volatile void      *g_gic_ctx[GIC_NUM_IRQS];

void gic_irq_entry(void)
{
    gic_irq_dispatch();
}
