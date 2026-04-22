/* =========================================================================
 * demo_lpr.c — Vietnamese License Plate Character Recognition Demo
 *
 * Runs golden_infer() on 7 embedded 28×28 character images and prints
 * the decoded plate string over UART.  Uses CGRA DMA to stage each image
 * into tile memory before ARM float inference (proves the hardware path).
 *
 * Memory map:
 *   OCM 0x004000: code + test images (.rodata) + GoldenContext (.bss)
 *   DDR 0x800000: golden_weights.bin (.lpr_weights, loaded by XSDB)
 *   DDR 0x100000: DMA staging buffer (1 image × 784 × 4 B = 3136 B)
 *   TILE 0x10000000: bank 0 (receives staged image, shows CGRA DMA path)
 *
 * Build:  make demo_lpr
 * Run:    make run_demo_lpr BIT=bitstreams/cgra.bit
 * ========================================================================= */

#include <stdint.h>
#include "uart.h"
#include "cgra.h"
#include "../lib/lpr_golden.h"
#include "demo_lpr_test_images.h"

/* ── Address constants ────────────────────────────────────────────────── */
#define DDR_STAGE      0x00100000UL   /* 16 KB scratch, matches bench_cgra */
#define TILE_BANK0     0x10000000UL   /* tile bank 0 — receives DMA'd image */
#define IMG_BYTES      (GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C * 4U)  /* 3136 B */

/* ── Weights from DDR (.lpr_weights section, loaded by XSDB) ──────────── */
extern const uint8_t lpr_weights_start[];

/* ── Inference context (large float buffers; BSS → zero-init'd by start.s) */
static GoldenContext g_ctx;

/* ── gic_irq_entry stub ───────────────────────────────────────────────── */
/* start.s trap_irq branches here.  demo_lpr never enables GIC interrupts,
 * so this stub is never called in practice. */
void gic_irq_entry(void) { }

/* ── Formatting helpers ───────────────────────────────────────────────── */

static void uart_putdec32s(int32_t v)
{
    if (v < 0) { uart_putchar('-'); v = -v; }
    uart_putdec((uint32_t)v);
}

/* ── Stage one image to tile bank 0 via CGRA DMA ─────────────────────── */
/* Copies img[784] (int32_t) to the DDR staging buffer, then kicks the
 * CGRA DMA to transfer 3136 bytes from DDR to tile bank 0.
 * The ARM then runs golden_infer() directly from the original img[] in
 * OCM — the DMA step demonstrates the hardware path and its overhead. */
static uint32_t stage_image_via_cgra(const int32_t *img)
{
    /* Write image to DDR staging (direct store — no cache flush needed in
     * bare-metal without L1 dcache enabled by BSP startup code). */
    volatile int32_t *stage = (volatile int32_t *)DDR_STAGE;
    for (int i = 0; i < GOLDEN_IN_H * GOLDEN_IN_W * GOLDEN_IN_C; i++)
        stage[i] = img[i];

    /* Time the CGRA DMA transfer */
    uint32_t t0 = arm_ccnt_read();
    cgra_dma(DDR_STAGE, TILE_BANK0, IMG_BYTES);
    uint32_t t1 = arm_ccnt_read();

    return t1 - t0;
}

/* ── Main ─────────────────────────────────────────────────────────────── */

int main(void)
{
    uart_init();
    arm_pmu_enable();

    uart_puts("\n");
    uart_puts("============================================\n");
    uart_puts("  CGRA LPR Demo — Vietnamese Plate OCR\n");
    uart_puts("  ARM Cortex-A9 VFP + CGRA DMA staging\n");
    uart_puts("  28x28 -> Conv1->Pool1->Conv2->Pool2->FC\n");
    uart_puts("  30-class VN charset  |  99.87% test acc\n");
    uart_puts("============================================\n");
    uart_puts("\n");

    /* Weights are in DDR at 0x800000 (loaded by XSDB into .lpr_weights).
     * Cast directly — binary layout matches GoldenWeights struct exactly. */
    const GoldenWeights *w = (const GoldenWeights *)lpr_weights_start;

    /* g_ctx is already zero (BSS) — no need to call golden_context_init() */
    g_ctx.dump_fn        = (void *)0;
    g_ctx.dump_user_data = (void *)0;

    /* Print weight summary from DDR */
    uart_puts("[ARM] Weights @ DDR 0x00800000 (99192 bytes)\n");
    uart_puts("[ARM] VN_CHAR_MAP: ");
    for (int i = 0; i < VN_NUM_CLASSES; i++) uart_putchar(VN_CHAR_MAP[i]);
    uart_puts("\n\n");

    /* ── Per-character inference ─────────────────────────────────────── */
    char  plate_str[LPR_TEST_NUM_IMAGES + 1];
    uint32_t dma_cyc_total  = 0;
    uint32_t infer_cyc_total = 0;

    uart_puts("  #   GT   Pred  Match  DMA(cyc)  Inf(cyc)  Logit\n");
    uart_puts("  --- ---- ----  -----  --------  --------  -----\n");

    for (int i = 0; i < LPR_TEST_NUM_IMAGES; i++) {
        char gt_ch  = lpr_test_chars[i];
        const int32_t *img = lpr_test_images[i];

        /* CGRA DMA: stage image into tile bank 0 */
        uint32_t dma_cyc = stage_image_via_cgra(img);
        dma_cyc_total += dma_cyc;

        /* ARM inference: golden_infer() with float weights */
        uint32_t t0 = arm_ccnt_read();
        int cls; char pred_ch;
        golden_infer(img, w, &g_ctx, &cls, &pred_ch);
        uint32_t t1 = arm_ccnt_read();
        uint32_t infer_cyc = t1 - t0;
        infer_cyc_total += infer_cyc;

        plate_str[i] = pred_ch;

        /* Top logit (×100 for two-decimal print) */
        const float *logits = golden_get_fc_output(&g_ctx);
        int32_t logit_x100 = (int32_t)(logits[cls] * 100.0f);

        /* Print result row */
        uart_puts("  [");
        uart_putdec((uint32_t)(i + 1));
        uart_puts("]  '");
        uart_putchar(gt_ch);
        uart_puts("'  '");
        uart_putchar(pred_ch);
        uart_puts("'   ");
        uart_puts((pred_ch == gt_ch) ? " OK " : "FAIL");
        uart_puts("  ");
        uart_putdec(dma_cyc);
        uart_puts("      ");
        uart_putdec(infer_cyc);
        uart_puts("   ");
        uart_putdec32s(logit_x100 / 100);
        uart_putchar('.');
        uint32_t frac = (uint32_t)(logit_x100 < 0 ? -logit_x100 : logit_x100) % 100u;
        uart_putchar('0' + (frac / 10u));
        uart_putchar('0' + (frac % 10u));
        uart_puts("\n");
    }

    plate_str[LPR_TEST_NUM_IMAGES] = '\0';

    /* ── Summary ──────────────────────────────────────────────────────── */
    uart_puts("\n");
    uart_puts("============================================\n");
    uart_puts("  Decoded plate: ");
    uart_puts(plate_str);
    uart_puts("\n");
    uart_puts("============================================\n");
    uart_puts("\n");

    /* Timing (ARM PMU at 666.67 MHz) */
    uint32_t arm_mhz = 667u;  /* 666.67 MHz rounded */
    uint32_t dma_us  = (dma_cyc_total + arm_mhz / 2u) / arm_mhz;
    uint32_t infer_us = (infer_cyc_total + arm_mhz / 2u) / arm_mhz;
    uint32_t total_us = dma_us + infer_us;

    uart_puts("[TIMING]  CGRA DMA total:  ");
    uart_putdec(dma_cyc_total);
    uart_puts(" cyc = ");
    uart_putdec(dma_us);
    uart_puts(" us\n");

    uart_puts("[TIMING]  ARM infer total: ");
    uart_putdec(infer_cyc_total);
    uart_puts(" cyc = ");
    uart_putdec(infer_us);
    uart_puts(" us\n");

    uart_puts("[TIMING]  Per character:   ");
    uart_putdec(infer_cyc_total / LPR_TEST_NUM_IMAGES);
    uart_puts(" cyc = ");
    uart_putdec(infer_us / LPR_TEST_NUM_IMAGES);
    uart_puts(" us\n");

    /* Characters per second */
    if (infer_us > 0) {
        uint32_t chars_per_s = (uint32_t)(7000000UL / infer_us);
        uart_puts("[TIMING]  Throughput:      ");
        uart_putdec(chars_per_s);
        uart_puts(" chars/s  (");
        uart_putdec(chars_per_s / 7u);
        uart_puts(" plates/s @ 7 chars)\n");
    }

    uart_puts("[TIMING]  Total (DMA+inf): ");
    uart_putdec(total_us);
    uart_puts(" us\n");

    uart_puts("\n");
    uart_puts("[ARM] Demo complete. Parked.\n");

    while (1) {
        __asm__ volatile ("wfi");
    }
    return 0;
}
