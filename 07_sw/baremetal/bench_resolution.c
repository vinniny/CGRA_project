/* =========================================================================
 * bench_resolution.c — Resolution sweep benchmark for LPR demo planning
 *
 * Measures CGRA processing time at different image resolutions to find
 * the sweet spot for the real-time LPR demo. Two processing patterns:
 *
 *   Pattern A: Element-wise (XOR invert) — preprocessing throughput
 *   Pattern B: Conv3×3 with 4-channel multicast — CNN feature extraction
 *
 * Plus an LPR pipeline estimate combining Conv (CGRA) + Pool + FC (ARM).
 *
 * All images are synthetic (generated at runtime in DDR). No camera needed.
 * Build: make bench_res     Run: via XSDB + UART capture on /dev/ttyUSB0
 * ========================================================================= */
#include <stdint.h>
#include "uart.h"
#include "cgra.h"

/* ── Memory ──────────────────────────────────────────────────────────── */
#define DDR_IMAGE    0x00100000UL   /* Image buffer in DDR */
#define DDR_STAGE    0x00180000UL   /* DMA staging area */
#define TILE_BANK0   0x10000000UL
#define TILE_BANK1   0x10001000UL
#define TILE_BANK2   0x10002000UL
#define TILE_BANK3   0x10003000UL

/* ── Resolutions to test ─────────────────────────────────────────────── */
typedef struct { const char *name; uint32_t h; uint32_t w; } res_t;
static const res_t resolutions[] = {
    {"8x8",       8,    8},
    {"16x16",    16,   16},
    {"28x28",    28,   28},
    {"64x64",    64,   64},
    {"128x128", 128,  128},
    {"160x80",  160,   80},
    {"352x288", 352,  288},
};
#define N_RES (sizeof(resolutions) / sizeof(resolutions[0]))

/* ── UART formatting (reused from bench_cgra.c) ─────────────────────── */
static void uart_putfix1(uint32_t val_x10)
{
    uart_putdec(val_x10 / 10);
    uart_putchar('.');
    uart_putchar('0' + (val_x10 % 10));
}

static void uart_rj(uint32_t v, int w)
{
    char buf[12]; int len = 0;
    if (v == 0) { buf[len++] = '0'; }
    else { uint32_t t = v; while (t) { buf[len++] = '0' + (t % 10); t /= 10; } }
    for (int i = len; i < w; i++) uart_putchar(' ');
    for (int i = len - 1; i >= 0; i--) uart_putchar(buf[i]);
}

static void uart_lj(const char *s, int w)
{
    const char *p = s; int len = 0;
    while (*p++) len++;
    uart_puts(s);
    for (int i = len; i < w; i++) uart_putchar(' ');
}

/* ── Common CGRA helpers ─────────────────────────────────────────────── */
static void cgra_clear_irqs(void) { cgra_wr(CGRA_IRQ_STATUS, 0x7u); }

static int cu_run_wait(void)
{
    cgra_wr(CGRA_CU_CTRL, 1u);
    for (uint32_t t = 0; t < 1000000; t++)
        if (cgra_rd(CGRA_CU_STATUS) & CU_STATUS_DONE) return 0;
    return -1;
}

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
    for (uint32_t pe = 0; pe < 16; pe++)
        cgra_config_pe(pe, DDR_STAGE, OP_NOP, 0, 0, 0, 0, 0);
}

/* Fill DDR with synthetic image data */
static void fill_image(uint32_t h, uint32_t w)
{
    volatile uint32_t *buf = (volatile uint32_t *)DDR_IMAGE;
    for (uint32_t i = 0; i < h * w; i++)
        buf[i] = (i * 7 + 13) & 0xFF;
}

/* =====================================================================
 * Pattern A: Element-wise (XOR invert)
 * 4 pixels per CU pass (1 per row, replicated 16× for PC sweep)
 * ===================================================================== */
static void bench_elementwise(void)
{
    uart_puts("\n--- Pattern A: Element-wise XOR (4 pix/pass) ---\n");
    uart_puts("Resolution  Pixels  Passes  Total_ms     FPS\n");

    for (uint32_t r = 0; r < N_RES; r++) {
        uint32_t h = resolutions[r].h;
        uint32_t w = resolutions[r].w;
        uint32_t n_pixels = h * w;
        uint32_t n_passes = (n_pixels + 3) / 4;

        fill_image(h, w);
        bench_setup();

        /* Configure: row N col 0 = XOR IMM=0xFFFF, cols 1-3 = PASS east */
        for (uint32_t row = 0; row < 4; row++) {
            uint32_t base = row * 4;
            cgra_config_pe(base,     DDR_STAGE, OP_XOR,   SRC_W, SRC_IMM, 0, ROUTE_E, 0xFFFF);
            cgra_config_pe(base + 1, DDR_STAGE, OP_PASS0, SRC_W, 0,       0, ROUTE_E, 0);
            cgra_config_pe(base + 2, DDR_STAGE, OP_PASS0, SRC_W, 0,       0, ROUTE_E, 0);
            cgra_config_pe(base + 3, DDR_STAGE, OP_PASS0, SRC_W, 0,       0, ROUTE_E, 0);
        }

        volatile uint32_t *image = (volatile uint32_t *)DDR_IMAGE;
        volatile uint32_t *stage = (volatile uint32_t *)DDR_STAGE;

        arm_ccnt_reset();
        uint32_t t0 = arm_ccnt_read();

        for (uint32_t chunk = 0; chunk < n_passes; chunk++) {
            uint32_t base_idx = chunk * 4;
            /* Stage 4 pixels, each replicated 16× */
            for (int row = 0; row < 4; row++) {
                uint32_t pix = (base_idx + (uint32_t)row < n_pixels)
                             ? image[base_idx + (uint32_t)row] : 0;
                for (int i = 0; i < 16; i++)
                    stage[row * 16 + i] = pix;
            }
            /* DMA to 4 tile banks */
            cgra_dma(DDR_STAGE,        TILE_BANK0, 64);
            cgra_dma(DDR_STAGE + 64,   TILE_BANK1, 64);
            cgra_dma(DDR_STAGE + 128,  TILE_BANK2, 64);
            cgra_dma(DDR_STAGE + 192,  TILE_BANK3, 64);
            cu_run_wait();
        }

        uint32_t t1 = arm_ccnt_read();
        uint32_t total_cyc = t1 - t0;

        /* ms * 10 = arm_cyc * 15 / 10000 */
        uint32_t ms_x10 = (total_cyc / 1000) * 15 / 10;
        /* FPS * 10 = 6666700 / (total_cyc / 10) */
        uint32_t fps_x10 = (total_cyc > 100) ? 66667000u / (total_cyc / 10) : 0;

        uart_lj(resolutions[r].name, 12);
        uart_rj(n_pixels, 6);
        uart_puts("  ");
        uart_rj(n_passes, 6);
        uart_puts("  ");
        uart_putfix1(ms_x10);
        uart_puts("  ");
        uart_putfix1(fps_x10);
        uart_putchar('\n');
    }
}

/* =====================================================================
 * Pattern B: Conv3×3 with 4-channel multicast
 * Config loads once. Per output pixel: DMA 3×3 patch + CU run.
 * ===================================================================== */
static void config_conv3x3(void)
{
    /* 4 rows on east-edge PE (col 3), each with different 3×3 weights.
     * Col 0: reads tile (input patch), forwards east.
     * Cols 1-2: relay east.
     * Col 3: ACC_CLR slot 0, MAC(SRC_W, SRC_IMM) slots 1-9, NOP 10-15.
     * Different IMM weights per row = different output channels. */
    static const int16_t weights[4][9] = {
        { 1,  1,  1,  1, -8,  1,  1,  1,  1},  /* Edge detect */
        { 0, -1,  0, -1,  5, -1,  0, -1,  0},  /* Sharpen */
        { 1,  2,  1,  2,  4,  2,  1,  2,  1},  /* Gaussian blur (×1/16) */
        { 1,  0, -1,  2,  0, -2,  1,  0, -1},  /* Sobel X */
    };

    for (uint32_t row = 0; row < 4; row++) {
        uint32_t base = row * 4;

        /* Col 0: PASS0 SRC_W (tile → east) */
        cgra_config_pe(base, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        /* Col 1-2: relay east */
        cgra_config_pe(base + 1, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);
        cgra_config_pe(base + 2, DDR_STAGE, OP_PASS0, SRC_W, 0, 0, ROUTE_E, 0);

        /* Col 3 (east edge): ACC_CLR + 9 MAC + NOP */
        uint32_t pe3 = base + 3;
        cgra_config_pe_slot(pe3, 0, DDR_STAGE,
                            OP_ACC_CLR, 0, 0, 0, ROUTE_E, 0);
        for (int s = 1; s <= 9; s++)
            cgra_config_pe_slot(pe3, (uint32_t)s, DDR_STAGE,
                                OP_MAC, SRC_W, SRC_IMM, 0, ROUTE_E,
                                (uint16_t)weights[row][s - 1]);
        for (int s = 10; s < 16; s++)
            cgra_config_pe_slot(pe3, (uint32_t)s, DDR_STAGE,
                                OP_NOP, 0, 0, 0, ROUTE_E, 0);
    }
}

static void bench_conv3x3(void)
{
    uart_puts("\n--- Pattern B: Conv3x3 (4-ch multicast, east-edge MAC) ---\n");
    uart_puts("Resolution  OutPix  Passes  Total_ms     FPS\n");

    for (uint32_t r = 0; r < N_RES; r++) {
        uint32_t h = resolutions[r].h;
        uint32_t w = resolutions[r].w;

        if (h < 3 || w < 3) {
            uart_lj(resolutions[r].name, 12);
            uart_puts("  (too small for 3x3)\n");
            continue;
        }

        uint32_t out_h = h - 2;
        uint32_t out_w = w - 2;
        uint32_t n_out = out_h * out_w;

        fill_image(h, w);
        bench_setup();
        config_conv3x3();

        volatile uint32_t *image = (volatile uint32_t *)DDR_IMAGE;
        volatile uint32_t *patch = (volatile uint32_t *)(DDR_STAGE + 1024);

        arm_ccnt_reset();
        uint32_t t0 = arm_ccnt_read();

        for (uint32_t oy = 0; oy < out_h; oy++) {
            for (uint32_t ox = 0; ox < out_w; ox++) {
                /* Extract 3×3 patch, pad to 16 words */
                for (int ky = 0; ky < 3; ky++)
                    for (int kx = 0; kx < 3; kx++)
                        patch[ky * 3 + kx] = image[(oy + (uint32_t)ky) * w + (ox + (uint32_t)kx)];
                for (int i = 9; i < 16; i++)
                    patch[i] = 0;

                /* DMA patch to all 4 tile banks (multicast input) */
                uint32_t patch_addr = DDR_STAGE + 1024;
                cgra_dma(patch_addr, TILE_BANK0, 64);
                cgra_dma(patch_addr, TILE_BANK1, 64);
                cgra_dma(patch_addr, TILE_BANK2, 64);
                cgra_dma(patch_addr, TILE_BANK3, 64);

                /* CU run — 4 output channels computed simultaneously */
                cgra_cu_reset();
                cu_run_wait();
            }
        }

        uint32_t t1 = arm_ccnt_read();
        uint32_t total_cyc = t1 - t0;

        uint32_t ms_x10 = (total_cyc / 1000) * 15 / 10;
        uint32_t fps_x10 = (total_cyc > 100) ? 66667000u / (total_cyc / 10) : 0;

        uart_lj(resolutions[r].name, 12);
        uart_rj(n_out, 6);
        uart_puts("  ");
        uart_rj(n_out, 6);
        uart_puts("  ");
        uart_putfix1(ms_x10);
        uart_puts("  ");
        uart_putfix1(fps_x10);
        uart_putchar('\n');
    }
}

/* =====================================================================
 * LPR Pipeline Estimate (9 characters, Vietnamese 2-row plate)
 * Conv3×3 on CGRA + MaxPool on ARM + FC on ARM
 * ===================================================================== */
static void bench_lpr_pipeline(void)
{
    uart_puts("\n--- LPR Pipeline Estimate (9 chars, 28x28 each) ---\n");

    uint32_t char_h = 28, char_w = 28;
    uint32_t out_h = char_h - 2, out_w = char_w - 2;
    uint32_t n_out = out_h * out_w;  /* 676 */

    fill_image(char_h, char_w);

    /* ── Measure Conv3×3 CGRA time for 1 character ─────────── */
    bench_setup();
    config_conv3x3();

    volatile uint32_t *image = (volatile uint32_t *)DDR_IMAGE;
    volatile uint32_t *patch = (volatile uint32_t *)(DDR_STAGE + 1024);

    arm_ccnt_reset();
    uint32_t t0 = arm_ccnt_read();

    for (uint32_t oy = 0; oy < out_h; oy++) {
        for (uint32_t ox = 0; ox < out_w; ox++) {
            for (int ky = 0; ky < 3; ky++)
                for (int kx = 0; kx < 3; kx++)
                    patch[ky * 3 + kx] = image[(oy + (uint32_t)ky) * char_w + (ox + (uint32_t)kx)];
            for (int i = 9; i < 16; i++) patch[i] = 0;

            uint32_t pa = DDR_STAGE + 1024;
            cgra_dma(pa, TILE_BANK0, 64);
            cgra_dma(pa, TILE_BANK1, 64);
            cgra_dma(pa, TILE_BANK2, 64);
            cgra_dma(pa, TILE_BANK3, 64);
            cgra_cu_reset();
            cu_run_wait();
        }
    }

    uint32_t t1 = arm_ccnt_read();
    uint32_t conv_1char_cyc = t1 - t0;

    /* ── Measure MaxPool ARM time (26×26×4 → 13×13×4) ──────── */
    /* Simple simulation: iterate output pixels, find max of 2×2 */
    arm_ccnt_reset();
    t0 = arm_ccnt_read();
    volatile uint32_t dummy = 0;
    for (uint32_t ch = 0; ch < 4; ch++) {
        for (uint32_t py = 0; py < 13; py++) {
            for (uint32_t px = 0; px < 13; px++) {
                /* Simulate 2×2 max — just do the memory accesses */
                uint32_t a = (py * 2) * 26 + px * 2 + ch * 676;
                uint32_t v0 = a, v1 = a + 1, v2 = a + 26, v3 = a + 27;
                uint32_t m = v0; if (v1 > m) m = v1; if (v2 > m) m = v2; if (v3 > m) m = v3;
                dummy += m;
            }
        }
    }
    t1 = arm_ccnt_read();
    uint32_t pool_cyc = t1 - t0;
    (void)dummy;

    /* ── Measure FC ARM time (784→30 matmul, pure C) ──────── */
    /* Simulate: 784 multiplies × 30 outputs */
    arm_ccnt_reset();
    t0 = arm_ccnt_read();
    volatile int32_t fc_dummy = 0;
    for (int j = 0; j < 30; j++) {
        int32_t acc = 0;
        for (int i = 0; i < 784; i++)
            acc += (int32_t)(i & 0xFF) * (int32_t)((i + j) & 0xFF);
        fc_dummy += acc;
    }
    t1 = arm_ccnt_read();
    uint32_t fc_cyc = t1 - t0;
    (void)fc_dummy;

    /* ── Print results ──────────────────────────────────────── */
    uint32_t conv_9_cyc = conv_1char_cyc * 9;
    uint32_t pool_9_cyc = pool_cyc * 9;
    uint32_t fc_9_cyc   = fc_cyc * 9;
    uint32_t total_cyc  = conv_9_cyc + pool_9_cyc + fc_9_cyc;

    /* Convert to ms * 10 */
    uint32_t conv_ms_x10 = (conv_9_cyc / 1000) * 15 / 10;
    uint32_t pool_ms_x10 = (pool_9_cyc / 1000) * 15 / 10;
    uint32_t fc_ms_x10   = (fc_9_cyc / 1000) * 15 / 10;
    uint32_t total_ms_x10 = (total_cyc / 1000) * 15 / 10;
    uint32_t plates_fps_x10 = (total_cyc > 100) ? 66667000u / (total_cyc / 10) : 0;

    uart_puts("Stage         Processor  ARM_CYC       ms\n");

    uart_puts("Conv3x3 x9    CGRA       ");
    uart_rj(conv_9_cyc, 10);
    uart_puts("  ");
    uart_putfix1(conv_ms_x10);
    uart_putchar('\n');

    uart_puts("MaxPool x9    ARM        ");
    uart_rj(pool_9_cyc, 10);
    uart_puts("  ");
    uart_putfix1(pool_ms_x10);
    uart_putchar('\n');

    uart_puts("FC 784->30 x9 ARM        ");
    uart_rj(fc_9_cyc, 10);
    uart_puts("  ");
    uart_putfix1(fc_ms_x10);
    uart_putchar('\n');

    uart_puts("TOTAL         ARM+CGRA   ");
    uart_rj(total_cyc, 10);
    uart_puts("  ");
    uart_putfix1(total_ms_x10);
    uart_putchar('\n');

    uart_puts("\nPlates/sec: ");
    uart_putfix1(plates_fps_x10);
    uart_putchar('\n');

    /* ── Sweet spot analysis ────────────────────────────────── */
    uart_puts("\n--- Sweet spot (Conv3x3, 4-ch multicast) ---\n");
    uart_puts("Per-pixel overhead: ~");
    uint32_t per_pix_us_x10 = (conv_1char_cyc > 0)
        ? ((conv_1char_cyc / n_out) * 15) / 1000 : 0;
    uart_putfix1(per_pix_us_x10);
    uart_puts(" us/output_pixel\n");

    /* Project max resolution for target FPS */
    uint32_t us_per_pix = (conv_1char_cyc * 10) / (n_out * 6667);
    if (us_per_pix == 0) us_per_pix = 1;
    uart_puts("  30 FPS target: ~");
    uint32_t pix_30 = 33333 / us_per_pix;  /* 33.3 ms budget in us */
    uart_putdec(pix_30);
    uart_puts(" output pixels (approx ");
    /* sqrt approximation */
    uint32_t side = 1; while (side * side < pix_30) side++;
    uart_putdec(side);
    uart_putchar('x');
    uart_putdec(side);
    uart_puts(")\n");

    uart_puts("  10 FPS target: ~");
    uint32_t pix_10 = 100000 / us_per_pix;
    uart_putdec(pix_10);
    uart_puts(" output pixels (approx ");
    side = 1; while (side * side < pix_10) side++;
    uart_putdec(side);
    uart_putchar('x');
    uart_putdec(side);
    uart_puts(")\n");
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
    uart_puts(" CGRA Resolution Benchmark\n");
    uart_puts(" Zynq-7000 XC7Z020 / 4x4 CGRA @ 50 MHz\n");
    uart_puts(" ARM Cortex-A9 @ 666.67 MHz\n");
    uart_puts("==========================================\n");

    bench_elementwise();
    bench_conv3x3();
    bench_lpr_pipeline();

    uart_puts("\n[RESOLUTION BENCH COMPLETE]\n");
    while (1) asm volatile("wfi");
}
