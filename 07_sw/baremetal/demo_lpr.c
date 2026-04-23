/* =========================================================================
 * demo_lpr.c — Vietnamese License Plate Character Recognition Demo
 *
 * Runs golden_infer() on LPR_TEST_NUM_IMAGES embedded 28×28 character
 * images (default: 60 = 2 per class × 30 VN classes) and reports:
 *   - Per-character prediction + timing
 *   - Per-class accuracy table (all 30 VN characters)
 *   - Overall accuracy + throughput
 *
 * CGRA DMA stages each image into tile bank 0 before ARM float inference
 * (proves the hardware path and reports its overhead separately).
 *
 * Memory map:
 *   OCM 0x004000: code + labels header (.rodata) + GoldenContext (.bss)
 *   DDR 0x800000: golden_weights.bin      (.lpr_weights, 99 KB)
 *   DDR 0x900000: test images binary      (.lpr_images,  N×784×4 B)
 *   DDR 0x100000: DMA staging buffer      (one image = 3136 B)
 *   TILE 0x10000000: bank 0 (receives DMA'd image)
 *
 * Build:  make demo_lpr
 * Run:    make run_elf ELF=07_sw/baremetal/demo_lpr.elf BIT=bitstreams/cgra.bit
 * ========================================================================= */

#include <stdint.h>
#include "uart.h"
#include "cgra.h"
#include "../lib/lpr_golden.h"
#include "demo_lpr_test_images.h"   /* LPR_TEST_NUM_IMAGES, lpr_test_chars[],
                                       lpr_test_class_idx[], LPR_TEST_IMG_PIXELS */

/* ── DDR sections ─────────────────────────────────────────────────────── */
extern const uint8_t  lpr_weights_start[];        /* 0x800000 — GoldenWeights struct */
extern const int32_t  lpr_images_start[];          /* 0x900000 — flat image bank */
#if defined(USE_CGRA_INFER) || defined(USE_CGRA_INFER_V2)
extern const uint8_t  lpr_weights_int16_start[];  /* 0x820000 — INT16 weight/bias blob */
#endif
#ifdef USE_CGRA_INFER_V2
extern const int32_t  lpr_weights_spm_start[];    /* 0x830000 — SPM layout weights */
#endif

/* ── DMA staging ──────────────────────────────────────────────────────── */
#define DDR_STAGE  0x00100000UL
#define TILE_BANK0 0x10000000UL
#define IMG_BYTES  (LPR_TEST_IMG_PIXELS * 4U)   /* 784 × 4 = 3136 bytes */

/* ── Inference context (BSS → zero-init'd by start.s) ────────────────── */
static GoldenContext g_ctx;

/* ── Per-class accuracy counters (BSS) ───────────────────────────────── */
static uint8_t g_class_correct[VN_NUM_CLASSES];
static uint8_t g_class_total[VN_NUM_CLASSES];

/* ── gic_irq_entry stub ───────────────────────────────────────────────── */
void gic_irq_entry(void) { }

/* ── Print uint64 decimal (for 64-bit cycle totals) ──────────────────── */
static void uart_putdec64(uint64_t v)
{
    char buf[22];
    int len = 0;
    if (v == 0) { uart_putchar('0'); return; }
    while (v) { buf[len++] = '0' + (int)(v % 10u); v /= 10u; }
    for (int i = len - 1; i >= 0; i--) uart_putchar(buf[i]);
}

/* ── Right-justified decimal in field width w ─────────────────────────── */
static void uart_rjdec(uint32_t v, int w)
{
    char buf[12];
    int len = 0;
    if (v == 0) { buf[len++] = '0'; }
    else { uint32_t t = v; while (t) { buf[len++] = '0' + (t % 10u); t /= 10u; } }
    for (int i = len; i < w; i++) uart_putchar(' ');
    for (int i = len - 1; i >= 0; i--) uart_putchar(buf[i]);
}

/* ── Stage image to tile bank 0 via CGRA DMA, return elapsed cycles ──── */
static uint32_t stage_image_via_cgra(const int32_t *img)
{
    volatile int32_t *stage = (volatile int32_t *)DDR_STAGE;
    for (int i = 0; i < LPR_TEST_IMG_PIXELS; i++)
        stage[i] = img[i];

    uint32_t t0 = arm_ccnt_read();
    cgra_dma(DDR_STAGE, TILE_BANK0, IMG_BYTES);
    return arm_ccnt_read() - t0;
}

/* ── Main ─────────────────────────────────────────────────────────────── */

int main(void)
{
    uart_init();
    arm_pmu_enable();

    uart_puts("\n");
    uart_puts("============================================\n");
    uart_puts("  CGRA LPR Demo — Vietnamese Plate OCR\n");
#if defined(USE_CGRA_INFER_V2)
    uart_puts("  ARM VFP Conv/Pool + CGRA SPM-FC v2\n");
#elif defined(USE_CGRA_INFER)
    uart_puts("  ARM VFP Conv/Pool + CGRA INT16 FC\n");
#else
    uart_puts("  ARM Cortex-A9 VFP + CGRA DMA staging\n");
#endif
    uart_puts("  28x28 -> Conv1->Pool->Conv2->Pool->FC\n");
    uart_puts("  30 VN classes  |  99.87% trained acc\n");
    uart_puts("============================================\n");

    uart_puts("[ARM] Weights @ DDR 0x00800000  (");
    uart_putdec(sizeof(GoldenWeights));
    uart_puts(" bytes)\n");
    uart_puts("[ARM] Images  @ DDR 0x00900000  (");
    uart_putdec((uint32_t)LPR_TEST_NUM_IMAGES);
    uart_puts(" images x ");
    uart_putdec((uint32_t)LPR_TEST_IMG_PIXELS);
    uart_puts(" int32 = ");
    uart_putdec((uint32_t)(LPR_TEST_NUM_IMAGES * LPR_TEST_IMG_PIXELS * 4u));
    uart_puts(" bytes)\n\n");

    const GoldenWeights *w = (const GoldenWeights *)lpr_weights_start;

    /* ── Per-character inference ─────────────────────────────────────── */
    uart_puts("  #    GT  Pred  OK?  DMA(cyc)  Inf(cyc)\n");
    uart_puts("  ---- --  ----  ---  --------  --------\n");

    uint32_t total_correct    = 0;
    uint32_t dma_cyc_total    = 0;
    uint64_t infer_cyc_total  = 0;

#ifdef LPR_CGRA_PROFILE
    /* Truncate to 60 images for profiling runs — statistically sufficient
     * for per-operation averages and keeps wall-clock under 10 s. */
    const int _n_images = (LPR_TEST_NUM_IMAGES < 60) ? LPR_TEST_NUM_IMAGES : 60;
#else
    const int _n_images = LPR_TEST_NUM_IMAGES;
#endif
    for (int i = 0; i < _n_images; i++) {
        char     gt_ch  = lpr_test_chars[i];
        uint8_t  gt_cls = lpr_test_class_idx[i];
        const int32_t *img = lpr_images_start + (uint32_t)i * LPR_TEST_IMG_PIXELS;

        uint32_t dma_cyc = stage_image_via_cgra(img);
        dma_cyc_total += dma_cyc;

        uint32_t t0 = arm_ccnt_read();
        int cls; char pred_ch;
#if defined(USE_CGRA_INFER_V2)
        golden_infer_cgra_v2(img, w, &g_ctx, lpr_weights_int16_start,
                             lpr_weights_spm_start, &cls, &pred_ch);
#elif defined(USE_CGRA_INFER)
        golden_infer_cgra(img, w, &g_ctx, lpr_weights_int16_start, &cls, &pred_ch);
#else
        golden_infer(img, w, &g_ctx, &cls, &pred_ch);
#endif
        uint32_t infer_cyc = arm_ccnt_read() - t0;
        infer_cyc_total += infer_cyc;

        g_class_total[gt_cls]++;
        int hit = (pred_ch == gt_ch);
        if (hit) { total_correct++; g_class_correct[gt_cls]++; }

        /* Compact row: [NNN/60] 'X' → 'Y'  OK/ERR  DMA  INF */
        uart_puts("  [");
        uart_rjdec((uint32_t)(i + 1), 4);
        uart_puts("/");
        uart_putdec((uint32_t)_n_images);
        uart_puts("] '");
        uart_putchar(gt_ch);
        uart_puts("' -> '");
        uart_putchar(pred_ch);
        uart_puts("'  ");
        uart_puts(hit ? " OK" : "ERR");
        uart_puts("  ");
        uart_rjdec(dma_cyc,   8);
        uart_puts("  ");
        uart_rjdec(infer_cyc, 8);
        uart_puts("\n");
    }

    /* ── Per-class accuracy table ────────────────────────────────────── */
    uart_puts("\nPer-class accuracy (");
    uart_putdec(VN_NUM_CLASSES);
    uart_puts(" classes, ");
    uart_putdec((uint32_t)_n_images);
    uart_puts(" total):\n");

    for (int c = 0; c < VN_NUM_CLASSES; c++) {
        uart_puts("  '");
        uart_putchar(VN_CHAR_MAP[c]);
        uart_puts("': ");
        uart_putdec(g_class_correct[c]);
        uart_puts("/");
        uart_putdec(g_class_total[c]);
        if ((c + 1) % 6 == 0 || c == VN_NUM_CLASSES - 1)
            uart_puts("\n");
        else
            uart_puts("   ");
    }

    /* ── Overall summary ─────────────────────────────────────────────── */
    uart_puts("\n============================================\n");
    uart_puts("  Accuracy: ");
    uart_putdec(total_correct);
    uart_puts("/");
    uart_putdec((uint32_t)_n_images);
    uart_puts("  (");
    /* Print NNN.N% */
    uint32_t acc_x10 = (total_correct * 1000u) / (uint32_t)_n_images;
    uart_putdec(acc_x10 / 10u);
    uart_putchar('.');
    uart_putchar('0' + (acc_x10 % 10u));
    uart_puts("%)\n");
    uart_puts("============================================\n\n");

    /* Timing at 666.67 MHz ARM clock */
    uint32_t mhz       = 667u;
    uint32_t dma_us    = (dma_cyc_total + mhz / 2u) / mhz;
    uint32_t infer_us  = (uint32_t)((infer_cyc_total + mhz / 2u) / mhz);
    uint32_t per_char  = (uint32_t)(infer_cyc_total / (uint32_t)_n_images);
    uint32_t per_us    = (per_char + mhz / 2u) / mhz;

    uart_puts("[TIMING] CGRA DMA total:  ");
    uart_putdec(dma_cyc_total);
    uart_puts(" cyc = ");
    uart_putdec(dma_us);
    uart_puts(" us\n");

    uart_puts("[TIMING] ARM infer total: ");
    uart_putdec64(infer_cyc_total);
    uart_puts(" cyc = ");
    uart_putdec(infer_us);
    uart_puts(" us\n");

    uart_puts("[TIMING] Per character:   ");
    uart_putdec(per_char);
    uart_puts(" cyc = ");
    uart_putdec(per_us);
    uart_puts(" us\n");

    if (per_us > 0) {
        uint32_t chars_s  = 1000000u / per_us;
        uint32_t plates_s = chars_s / 7u;
        uart_puts("[TIMING] Throughput:      ");
        uart_putdec(chars_s);
        uart_puts(" chars/s  (");
        uart_putdec(plates_s);
        uart_puts(" plates/s @ 7 chars)\n");
    }

#if defined(USE_CGRA_INFER) && defined(LPR_CGRA_PROFILE)
    extern uint64_t g_fc_prof_program_cyc, g_fc_prof_dma_cyc, g_fc_prof_cu_cyc;
    extern uint64_t g_fc_prof_readout_cyc, g_fc_prof_accclr_cyc;
    extern uint32_t g_fc_prof_chunk_cnt;

    uart_puts("\n[FC PROFILE] per-operation breakdown (sum over all chars):\n");
    uart_puts("  chunks timed:   "); uart_putdec64(g_fc_prof_chunk_cnt); uart_puts("\n");
    uart_puts("  kernel program: "); uart_putdec64(g_fc_prof_program_cyc);
    uart_puts(" cyc  avg/chunk: "); uart_putdec((uint32_t)(g_fc_prof_program_cyc / (uint64_t)(g_fc_prof_chunk_cnt ? g_fc_prof_chunk_cnt : 1)));
    uart_puts(" cyc\n");
    uart_puts("  DMA tile (x4):  "); uart_putdec64(g_fc_prof_dma_cyc);
    uart_puts(" cyc  avg/chunk: "); uart_putdec((uint32_t)(g_fc_prof_dma_cyc / (uint64_t)(g_fc_prof_chunk_cnt ? g_fc_prof_chunk_cnt : 1)));
    uart_puts(" cyc\n");
    uart_puts("  CU start+wait:  "); uart_putdec64(g_fc_prof_cu_cyc);
    uart_puts(" cyc  avg/chunk: "); uart_putdec((uint32_t)(g_fc_prof_cu_cyc / (uint64_t)(g_fc_prof_chunk_cnt ? g_fc_prof_chunk_cnt : 1)));
    uart_puts(" cyc\n");
    uart_puts("  ACC_CLR (8x):   "); uart_putdec64(g_fc_prof_accclr_cyc); uart_puts(" cyc\n");
    uart_puts("  Readout (8x):   "); uart_putdec64(g_fc_prof_readout_cyc); uart_puts(" cyc\n");
#endif

    uart_puts("\n[ARM] Demo complete. Parked.\n");

    while (1) { __asm__ volatile ("wfi"); }
    return 0;
}
