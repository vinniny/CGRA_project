/* demo_mnist_hdmi_bm.c — Option-A HDMI demo: CGRA-FC vs ARM-FC head-to-head.
 *
 * The CGRA's pixel-by-pixel Conv2 saturates INT32 inside the result FIFO
 * (silicon-validated kernel, ~12% accuracy as a result), so we keep
 * Conv+Pool on ARM-VFP where the 97% accuracy actually lives, then
 * compare three FC1+FC2 implementations on the SAME act400:
 *
 *   1. CGRA FC   — cnn_fc1_run_group + cnn_fc2_run_group, silicon-validated
 *   2. ARM-INT FC — INT64 accumulator (matches CGRA math exactly)
 *   3. ARM-VFP FC — float MAC (modern compile baseline)
 *
 * All three should produce the same prediction (within INT-quant noise).
 * The thesis story is the FC speedup: "CGRA accelerates dense matrix
 * multiply layers on MNIST". Conv stays on ARM in all paths, so the
 * Conv time is constant and only the FC stage varies in the cycle
 * measurement. */

#include "uart.h"
#include "cgra.h"
#include "cgra_kernels_cnn.h"
#include "cgra_kernels_cnn_v2.h"     /* 16-PE FC with dual-port SPM */

/* Kernel-selection compile-time flags (precedence: V2_PARALLEL > FAST > v1):
 *   -DUSE_V2_PARALLEL=1  -> 16-PE parallel (cgra_kernels_cnn_v2.h, dst=15
 *                          fix). Theoretical ~4× over Tier-1 if silicon-
 *                          validated.
 *   -DUSE_FAST_CGRA_FC=1 -> Tier-1 fast FC (default, silicon-validated
 *                          97/100 on the sweep). 4 PEs × 16 groups.
 *   neither              -> v1 baseline. */
#ifndef USE_V2_PARALLEL
#define USE_V2_PARALLEL  0
#endif
#ifndef USE_FAST_CGRA_FC
#define USE_FAST_CGRA_FC 1
#endif
#if !USE_V2_PARALLEL && USE_FAST_CGRA_FC
#include "cgra_kernels_cnn_opt.h"
#endif
#include "arm_cnn_bm.h"
#include "arm_fc_bm.h"
#include "hdmi_bm.h"
#include "fb_lib_bm.h"
#include "mnist_sweep_fixture.h"
#include "../cnn_eval/mnist_weights_scale.h"
#ifdef LIVE_INPUT
#include "hdmi_in_bm.h"
#include "mmu_cache_bm.h"
#include "frame_to_mnist.h"
#endif

#include <stdint.h>

extern const uint32_t cnn_spm_start[];

#define CPU_HZ  666666666u

#define ACT400_DDR  0x00220000UL
#define ACT64_DDR   0x00221000UL

/* ── Layout (640×480) ────────────────────────────────────────────────── */
#define IMG_SCALE   8
#define IMG_W       (28 * IMG_SCALE)
#define IMG_H       (28 * IMG_SCALE)
#define IMG_X       ((640 - IMG_W) / 2)
#define IMG_Y       10
#define HEADER_TXT_Y  (IMG_Y + IMG_H + 8)

#define PANEL_W     213
#define PANEL_GAP   1
#define PANEL_Y     (HEADER_TXT_Y + 16)
#define PANEL_H     150

#define PANEL_CGRA_X  0
#define PANEL_INT_X   (PANEL_CGRA_X + PANEL_W + PANEL_GAP)
#define PANEL_VFP_X   (PANEL_INT_X  + PANEL_W + PANEL_GAP)

#define FOOTER_Y    (PANEL_Y + PANEL_H + 8)

#define COLOR_BG       FBM_DARKBG
#define COLOR_PANEL    0x002040u
#define COLOR_TXT      FBM_WHITE
#define COLOR_OK       FBM_GREEN
#define COLOR_MISS     FBM_RED
#define COLOR_ACCENT   FBM_YELLOW

/* ── FC post-processing for the CGRA path (bias + ReLU + requant) ───── */
static void fc1_post_process(const int32_t fc1_acc[64], int32_t act64_out[64])
{
    int32_t tmp[64];
    int32_t max_abs = 0;
    for (int n = 0; n < 64; ++n) {
        int64_t s = (int64_t)fc1_acc[n] + (int64_t)mnist_fc1_bias_q[n];
        if (s < 0) s = 0;
        if (s > 0x7FFFFFFFLL) s = 0x7FFFFFFFLL;
        tmp[n] = (int32_t)s;
        if (tmp[n] > max_abs) max_abs = tmp[n];
    }
    int shift = 0;
    while ((max_abs >> shift) > 32767 && shift < 31) shift++;
    for (int n = 0; n < 64; ++n) act64_out[n] = tmp[n] >> shift;
}

static int argmax_with_bias(const int32_t fc2_acc[10])
{
    int32_t v[10];
    for (int i = 0; i < 10; ++i) v[i] = fc2_acc[i] + mnist_fc2_bias_q[i];
    int best = 0;
    for (int i = 1; i < 10; ++i) if (v[i] > v[best]) best = i;
    return best;
}

/* CGRA FC1+FC2+argmax (v1: 4 PEs × 16 groups, silicon-validated accuracy).
 * Returns predicted class, -1 on kernel error.
 *
 * v1 chosen here (over v2) because v1's FC1-output capture is silicon-
 * validated: 97 % top-1 on the 2745-frame test (README headline). v2's
 * 16-PE parallel kernel discards FC1 outputs in demo_mnist_cgra_v2 --
 * it benchmarks v2's CYCLES against pre-computed activations, not v2's
 * accuracy. With live HDMI input we NEED accurate FC1 outputs to feed
 * FC2, so v1 it is. Cycle speedup is smaller (~2× over ARM-INT) but
 * the predictions are correct. */

/* Per-neuron FC1 accumulator correction (silicon-calibrated): the CGRA's
 * SPM auto-inc loop-wrap asymmetry + 40-bit saturation yield SYSTEMATIC
 * per-neuron deltas vs the ARM-INT golden. Calibrated offsets are subtracted
 * before fc1_post_process. Generate via CGRA_CALIB=1 build: per-image UART
 * deltas, average -> cgra_fc1_corr table. Zeros = uncalibrated. */
static int32_t cgra_fc1_corr[64] = { 0 };
#ifdef CALIB_DUMP
static int32_t calib_fc1_cgra[64];
#endif

static int run_cgra_fc(const int32_t act400[400])
{
    volatile int32_t *act400_ddr = (volatile int32_t *)ACT400_DDR;
    for (int j = 0; j < 400; ++j) act400_ddr[j] = act400[j];
    /* Cache-clean the ACT400 region so the CGRA AXI master sees the
     * fresh ARM-side writes via DDR (no-op if D-cache is disabled). */
    cgra_dcache_flush_range((const void *)ACT400_DDR, 400u * sizeof(int32_t));

    int32_t fc1_acc[64];
#if USE_V2_PARALLEL
    /* v2: broadcast acts to all 16 PE SPMs, 4 groups × 16 PEs in parallel */
    if (cnn_fc1_v2_act_preload(ACT400_DDR)) return -1;
    for (int g = 0; g < (int)CNN_FC1_V2_N_GROUPS; ++g) {
        int32_t grp[16];
        if (cnn_fc1_v2_run_group(g, grp)) return -1;
        for (int i = 0; i < 16 && g*16+i < (int)CNN_FC1_V2_N_OUTPUTS; ++i)
            fc1_acc[g*16+i] = grp[i];
    }
#else
    if (cnn_fc1_tile_preload(ACT400_DDR)) return -1;
# if USE_FAST_CGRA_FC
    cnn_fc_opt_layer_setup(CNN_FC1_LOOP_COUNT);
    for (int g = 0; g < (int)CNN_FC1_N_GROUPS; ++g) {
        int32_t grp[4];
        if (cnn_fc1_opt_run_group(g, grp)) return -1;
        for (int r = 0; r < 4; ++r) fc1_acc[g*4 + r] = grp[r];
    }
# else
    for (int g = 0; g < (int)CNN_FC1_N_GROUPS; ++g) {
        int32_t grp[4];
        if (cnn_fc1_run_group(g, grp)) return -1;
        for (int r = 0; r < 4; ++r) fc1_acc[g*4 + r] = grp[r];
    }
# endif
#endif
    /* Apply silicon-calibrated per-neuron correction (see cgra_fc1_corr). */
    for (int n = 0; n < 64; ++n) fc1_acc[n] -= cgra_fc1_corr[n];
#ifdef CALIB_DUMP
    for (int n = 0; n < 64; ++n) calib_fc1_cgra[n] = fc1_acc[n];
#endif

    int32_t act64[64];
    fc1_post_process(fc1_acc, act64);

    volatile int32_t *act64_ddr = (volatile int32_t *)ACT64_DDR;
    for (int j = 0; j < 64; ++j) act64_ddr[j] = act64[j];
    cgra_dcache_flush_range((const void *)ACT64_DDR, 64u * sizeof(int32_t));

    int32_t fc2_acc[12];
    for (int i = 0; i < 12; ++i) fc2_acc[i] = 0;
#if USE_V2_PARALLEL
    if (cnn_fc2_v2_act_preload(ACT64_DDR)) return -1;
    int32_t grp16[16];
    if (cnn_fc2_v2_run_group(0, grp16)) return -1;
    for (int i = 0; i < 10; ++i) fc2_acc[i] = grp16[i];
#else
    if (cnn_fc2_tile_preload(ACT64_DDR)) return -1;
# if USE_FAST_CGRA_FC
    cnn_fc_opt_layer_setup(CNN_FC2_LOOP_COUNT);
    for (int g = 0; g < (int)CNN_FC2_N_GROUPS; ++g) {
        int32_t grp[4];
        if (cnn_fc2_opt_run_group(g, grp)) return -1;
        for (int r = 0; r < 4 && g*4+r < 10; ++r) fc2_acc[g*4+r] = grp[r];
    }
# else
    for (int g = 0; g < (int)CNN_FC2_N_GROUPS; ++g) {
        int32_t grp[4];
        if (cnn_fc2_run_group(g, grp)) return -1;
        for (int r = 0; r < 4 && g*4+r < 10; ++r) fc2_acc[g*4+r] = grp[r];
    }
# endif
#endif
    return argmax_with_bias(fc2_acc);
}

/* ── Formatting helpers ──────────────────────────────────────────────── */
/* MNIST-style normalization of the live 28x28 crop — fixes the live-vs-trained
 * accuracy gap (silicon 2026-06-03): thin/off-centre/grayscale drawn digits are
 * out-of-distribution for the INT16-calibrated quantizers.  MNIST digits are
 * size-normalized to ~20px and CoM-centered in a 28x28 frame.
 *  1) Contrast stretch: min->0, max->255 so the working range matches MNIST.
 *  2) Threshold @96; bounding-box the bright digit; nearest-neighbor rescale
 *     longest side to 20px and centre.  No-op on near-empty/full frames. */
/* MNIST-faithful capture (Gemini-reviewed pipeline, 2026-06-03):
 *  1. find the white canvas box at coarse resolution,
 *  2. find the ink bounding box at FULL HDMI resolution,
 *  3. area-average (box-filter) the bbox to a 20x20 patch — preserves
 *     antialiased 2-3px strokes like MNIST,
 *  4. place patch in 28x28 with centre-of-mass at (14,14). */
#ifdef LIVE_INPUT
static inline uint32_t pix_luma(const uint8_t *fb, uint32_t x, uint32_t y)
{
    const uint8_t *p = fb + (uint32_t)y * HDMI_IN_ROW_STRIDE + (uint32_t)x * HDMI_IN_BPP;
    return (77u * p[2] + 150u * p[1] + 29u * p[0] + 128u) >> 8;
}

static void mnist_capture_digit(const uint8_t *fb, uint8_t out[28*28])
{
    for (int i = 0; i < 28*28; ++i) out[i] = 0;
    /* 1) Canvas = brightest region. Scan ROI at step 8. */
    const uint32_t RX0 = 95, RX1 = 1135, RY0 = 195, RY1 = 715;
    uint32_t maxl = 0;
    for (uint32_t y = RY0; y < RY1; y += 8)
        for (uint32_t x = RX0; x < RX1; x += 8) {
            uint32_t l = pix_luma(fb, x, y);
            if (l > maxl) maxl = l;
        }
    if (maxl < 96) return;                          /* no white canvas */
    const uint32_t th_canvas = (maxl * 3u) / 4u;
    uint32_t cx0 = RX1, cx1 = RX0, cy0 = RY1, cy1 = RY0;
    for (uint32_t y = RY0; y < RY1; y += 8)
        for (uint32_t x = RX0; x < RX1; x += 8)
            if (pix_luma(fb, x, y) >= th_canvas) {
                if (x < cx0) cx0 = x;  if (x > cx1) cx1 = x;
                if (y < cy0) cy0 = y;  if (y > cy1) cy1 = y;
            }
    if (cx1 - cx0 < 64 || cy1 - cy0 < 64) return;
    cx0 += 16; cx1 -= 16; cy0 += 16; cy1 -= 16;     /* trim window borders */
    /* 2) Ink bbox at FULL resolution (step 2). */
    const uint32_t th_ink = maxl / 2u;
    uint32_t ix0 = cx1, ix1 = cx0, iy0 = cy1, iy1 = cy0;
    for (uint32_t y = cy0; y < cy1; y += 2)
        for (uint32_t x = cx0; x < cx1; x += 2)
            if (pix_luma(fb, x, y) < th_ink) {
                if (x < ix0) ix0 = x;  if (x > ix1) ix1 = x;
                if (y < iy0) iy0 = y;  if (y > iy1) iy1 = y;
            }
    if (ix1 <= ix0 || iy1 <= iy0) return;           /* blank canvas */
    const uint32_t w = ix1 - ix0 + 1, h = iy1 - iy0 + 1;
    const uint32_t side = (w > h ? w : h);
    /* 3) Area-average into 20x20 patch (block side/20, subsample step 2). */
    uint8_t patch[20*20];
    const uint32_t blk = side / 20u + 1u;
    for (uint32_t py = 0; py < 20; ++py)
        for (uint32_t px = 0; px < 20; ++px) {
            uint64_t sum = 0; uint32_t cnt = 0;
            for (uint32_t dy = 0; dy < blk; dy += 2)
                for (uint32_t dx = 0; dx < blk; dx += 2) {
                    uint32_t sx = ix0 + px*blk + dx, sy = iy0 + py*blk + dy;
                    if (sx > cx1 || sy > cy1) continue;
                    sum += pix_luma(fb, sx, sy); cnt++;
                }
            uint32_t l = cnt ? (uint32_t)(sum / cnt) : maxl;
            uint32_t v = (l >= maxl) ? 0u : (255u * (maxl - l)) / maxl;
            patch[py*20 + px] = (uint8_t)(v > 255u ? 255u : v);
        }
    /* 4) Centre-of-mass placement at (14,14). */
    uint32_t m = 0, mx = 0, my = 0;
    for (int y = 0; y < 20; ++y)
        for (int x = 0; x < 20; ++x) {
            m += patch[y*20 + x]; mx += patch[y*20 + x] * x; my += patch[y*20 + x] * y;
        }
    if (m == 0) return;
    const int ox = 14 - (int)(mx / m), oy = 14 - (int)(my / m);
    for (int y = 0; y < 20; ++y)
        for (int x = 0; x < 20; ++x) {
            int tx = x + ox, ty = y + oy;
            if (tx >= 0 && tx < 28 && ty >= 0 && ty < 28)
                out[ty*28 + tx] = patch[y*20 + x];
        }
}

/* Wide variant: source is the WHOLE Paint canvas as a 56x28 grid, so the user
 * may draw anywhere.  Contrast-stretch, locate ink bbox, nearest-neighbor the
 * longest side to 20 px, centre in 28x28 (MNIST framing). */
static void mnist_normalize_wide(const uint8_t src[56*28], uint8_t out[28*28])
{
    uint8_t mn = 255, mx = 0;
    for (int i = 0; i < 56*28; ++i) {
        if (src[i] < mn) mn = src[i];
        if (src[i] > mx) mx = src[i];
    }
    for (int i = 0; i < 28*28; ++i) out[i] = 0;
    if ((uint8_t)(mx - mn) < 24) return;                    /* blank canvas */
    const int range = mx - mn;
    /* 1) Locate the white canvas (laptop letterboxes its screen into the
     *    720p frame; the surrounding black border inverts to bright "ink").
     *    Canvas = pixels close to the minimum (white inverts to ~mn). */
    int cx0 = 55, cx1 = 0, cy0 = 27, cy1 = 0;
    for (int y = 0; y < 28; ++y)
        for (int x = 0; x < 56; ++x)
            if (src[y*56 + x] <= mn + 32) {
                if (x < cx0) cx0 = x;  if (x > cx1) cx1 = x;
                if (y < cy0) cy0 = y;  if (y > cy1) cy1 = y;
            }
    if (cx1 - cx0 < 4 || cy1 - cy0 < 4) return;  /* no white area visible */
    /* 2) Ink = stretched-bright pixels INSIDE the canvas box only. */
    int x0 = 55, x1 = 0, y0 = 27, y1 = 0;
    static uint8_t st[56*28];
    for (int y = 0; y < 28; ++y)
        for (int x = 0; x < 56; ++x) {
            int inside = (x >= cx0 && x <= cx1 && y >= cy0 && y <= cy1);
            int v = inside ? ((src[y*56 + x] - mn) * 255) / range : 0;
            st[y*56 + x] = (uint8_t)v;
            if (v > 96) {
                if (x < x0) x0 = x;  if (x > x1) x1 = x;
                if (y < y0) y0 = y;  if (y > y1) y1 = y;
            }
        }
    if (x1 < x0 || y1 < y0) return;
    const int w = x1 - x0 + 1, h = y1 - y0 + 1;
    /* Fit the longest side to 16 px with 6-px margins — the tight 20-px fit
     * cropped digits too close (silicon feedback 2026-06-03). */
    const int side = (w > h ? w : h);
    for (int y = 0; y < 16; ++y)
        for (int x = 0; x < 16; ++x) {
            int sx = x0 + (x * side) / 16, sy = y0 + (y * side) / 16;
            out[(y + 6)*28 + x + 6] =
                (sx <= 55 && sy <= 27) ? st[sy*56 + sx] : 0;
        }
}

#endif /* LIVE_INPUT — capture/normalize helpers */

static void delay_cycles(uint32_t n)
{
    uint32_t start = arm_ccnt_read();
    while ((arm_ccnt_read() - start) < n) { asm volatile("nop"); }
}

static int u32_to_decimal(uint32_t n, char *buf, int width)
{
    char tmp[12]; int len = 0;
    if (n == 0) tmp[len++] = '0';
    while (n) { tmp[len++] = (char)('0' + (n % 10)); n /= 10; }
    int pad = (width > len) ? (width - len) : 0;
    int idx = 0;
    while (pad--) buf[idx++] = ' ';
    while (len--) buf[idx++] = tmp[len];
    buf[idx] = '\0';
    return idx;
}

/* Cycles → "ddd.d us" (microseconds with one decimal). FC paths are
 * sub-millisecond so microseconds is the natural unit. */
static void fmt_us_1dec(uint32_t cycles, char *buf)
{
    /* tenths-of-us = cycles * 10 / (CPU_HZ / 1e6) = cycles * 10 / 666.66 */
    uint32_t tenths = (uint32_t)(((uint64_t)cycles * 10u + 333u) / 667u);
    uint32_t whole  = tenths / 10u;
    uint32_t frac   = tenths % 10u;
    char tmp[12]; int len = u32_to_decimal(whole, tmp, 0);
    int idx = 0;
    for (int i = 0; i < len; ++i) buf[idx++] = tmp[i];
    buf[idx++] = '.';
    buf[idx++] = (char)('0' + frac);
    buf[idx]   = '\0';
}

/* FPS with one decimal, e.g. "178.6". The bare-metal paths are
 * sub-1%-jitter so the integer truncation made the panels look frozen;
 * a single fractional digit surfaces the real per-image variation. */
static void fmt_kfps(uint32_t cycles, char *buf)
{
    if (cycles == 0) { buf[0]='-'; buf[1]='\0'; return; }
    uint64_t tenths = ((uint64_t)CPU_HZ * 10u + cycles / 2u) / cycles;
    uint32_t whole = (uint32_t)(tenths / 10u);
    uint32_t frac  = (uint32_t)(tenths % 10u);
    char tmp[12]; int len = u32_to_decimal(whole, tmp, 0);
    int idx = 0;
    for (int i = 0; i < len; ++i) buf[idx++] = tmp[i];
    buf[idx++] = '.';
    buf[idx++] = (char)('0' + frac);
    buf[idx]   = '\0';
}

static void fmt_speedup(uint32_t baseline, uint32_t test, char *buf)
{
    if (test == 0) { buf[0]='-'; buf[1]='\0'; return; }
    uint32_t tenths = (uint32_t)(((uint64_t)baseline * 10u + test / 2u) / test);
    uint32_t whole = tenths / 10u;
    uint32_t frac  = tenths % 10u;
    char tmp[12]; int len = u32_to_decimal(whole, tmp, 0);
    int idx = 0;
    for (int i = 0; i < len; ++i) buf[idx++] = tmp[i];
    buf[idx++] = '.';
    buf[idx++] = (char)('0' + frac);
    buf[idx++] = 'x';
    buf[idx]   = '\0';
}

/* ── Rendering ───────────────────────────────────────────────────────── */
static void render_static_chrome(void)
{
    hdmi_clear(COLOR_BG);
    hdmi_rect(IMG_X - 4, IMG_Y - 4, IMG_W + 8, IMG_H + 8, FBM_GRAY);
    hdmi_rect(IMG_X,     IMG_Y,     IMG_W,     IMG_H,     FBM_BLACK);
    hdmi_rect(PANEL_CGRA_X, PANEL_Y, PANEL_W, PANEL_H, COLOR_PANEL);
    hdmi_rect(PANEL_INT_X,  PANEL_Y, PANEL_W, PANEL_H, COLOR_PANEL);
    hdmi_rect(PANEL_VFP_X,  PANEL_Y, PANEL_W, PANEL_H, COLOR_PANEL);

    fbm_draw_text(PANEL_CGRA_X + 8, PANEL_Y + 6,  "CGRA-FC",   COLOR_ACCENT, 2);
    fbm_draw_text(PANEL_CGRA_X + 8, PANEL_Y + 28, "*ACCEL.",   FBM_GRAY,     1);
    fbm_draw_text(PANEL_INT_X  + 8, PANEL_Y + 6,  "ARM-INT-FC", COLOR_ACCENT, 2);
    fbm_draw_text(PANEL_INT_X  + 8, PANEL_Y + 28, "*INT64 MAC", FBM_GRAY,    1);
    fbm_draw_text(PANEL_VFP_X  + 8, PANEL_Y + 6,  "ARM-VFP-FC", COLOR_ACCENT, 2);
    fbm_draw_text(PANEL_VFP_X  + 8, PANEL_Y + 28, "*HW FLOAT",  FBM_GRAY,    1);

    fbm_draw_text(IMG_X - 4, IMG_Y + IMG_H + 4,
                  "MNIST  CONV+POOL ON ARM-VFP  FC HEAD-TO-HEAD",
                  FBM_WHITE, 1);
}

static void render_panel(int px, int pred, int label, uint32_t cycles)
{
    hdmi_rect(px + 4, PANEL_Y + 50, PANEL_W - 8, PANEL_H - 56, COLOR_PANEL);

    char buf[32];

    buf[0]='P';buf[1]='R';buf[2]='E';buf[3]='D';buf[4]=':';buf[5]=' ';
    buf[6]=(char)('0'+(pred%10)); buf[7]='\0';
#ifdef LIVE_INPUT
    /* No ground truth in live mode -- always use the neutral text colour
     * and skip the GT label. The live panel just shows PRED + cycles. */
    fbm_draw_text(px + 8, PANEL_Y + 56, buf, COLOR_TXT, 2);
    (void)label;
#else
    fbm_draw_text(px + 8, PANEL_Y + 56, buf,
                  (pred == label) ? COLOR_OK : COLOR_MISS, 2);

    buf[0]='G';buf[1]='T';buf[2]=':';buf[3]=' ';buf[4]=(char)('0'+(label%10));buf[5]='\0';
    fbm_draw_text(px + 96, PANEL_Y + 56, buf, COLOR_TXT, 2);
#endif

    char us[16];
    fmt_us_1dec(cycles, us);
    int n = 0; while (us[n]) n++;
    char us_disp[24];
    int idx = 0;
    for (int i = 0; i < n; ++i) us_disp[idx++] = us[i];
    us_disp[idx++] = ' '; us_disp[idx++] = 'U'; us_disp[idx++] = 'S';
    us_disp[idx] = '\0';
    fbm_draw_text(px + 8, PANEL_Y + 86, us_disp, COLOR_TXT, 2);

    char fps[16];
    fmt_kfps(cycles, fps);
    n = 0; while (fps[n]) n++;
    char fps_disp[24];
    idx = 0;
    for (int i = 0; i < n; ++i) fps_disp[idx++] = fps[i];
    fps_disp[idx++] = ' '; fps_disp[idx++] = 'F'; fps_disp[idx++] = 'P'; fps_disp[idx++] = 'S';
    fps_disp[idx] = '\0';
    fbm_draw_text(px + 8, PANEL_Y + 114, fps_disp, COLOR_TXT, 2);
}

/* Append a "label: n/total" segment to dst starting at *idx_io. */
static void append_acc(char *dst, int *idx_io, const char *label,
                       uint32_t n, uint32_t total)
{
    int idx = *idx_io;
    while (*label) dst[idx++] = *label++;
    char numbuf[16];
    int k = u32_to_decimal(n, numbuf, 0);
    for (int i = 0; i < k; ++i) dst[idx++] = numbuf[i];
    dst[idx++] = '/';
    k = u32_to_decimal(total, numbuf, 0);
    for (int i = 0; i < k; ++i) dst[idx++] = numbuf[i];
    *idx_io = idx;
}

static void render_footer(uint32_t cyc_cgra, uint32_t cyc_int, uint32_t cyc_vfp,
                          int correct_cgra, int correct_int, int correct_vfp,
                          int total)
{
    hdmi_rect(0, FOOTER_Y, HDMI_FB_W, HDMI_FB_H - FOOTER_Y, COLOR_BG);

    char sp_int[16], sp_vfp[16];
    fmt_speedup(cyc_int, cyc_cgra, sp_int);
    fmt_speedup(cyc_vfp, cyc_cgra, sp_vfp);

    char line[128];
    int idx = 0;
    const char *p;
    p = "CGRA-FC SPEEDUP  vs ARM-INT-FC: ";  while (*p) line[idx++] = *p++;
    p = sp_int;                                while (*p) line[idx++] = *p++;
    p = "   vs ARM-VFP-FC: ";                  while (*p) line[idx++] = *p++;
    p = sp_vfp;                                while (*p) line[idx++] = *p++;
    line[idx] = '\0';
    fbm_draw_text(8, FOOTER_Y, line, COLOR_ACCENT, 1);

    char acc[128];
    idx = 0;
#ifdef LIVE_INPUT
    /* Live mode has no ground truth -- skip ACC counters; just show the
     * frame count. */
    (void)correct_cgra; (void)correct_int; (void)correct_vfp;
    p = "FRAME: ";  while (*p) acc[idx++] = *p++;
    char numbuf[16];
    int k = u32_to_decimal((uint32_t)total, numbuf, 0);
    for (int i = 0; i < k; ++i) acc[idx++] = numbuf[i];
#else
    append_acc(acc, &idx, "ACC  CGRA: ", (uint32_t)correct_cgra, (uint32_t)total);
    append_acc(acc, &idx, "   INT: ",    (uint32_t)correct_int,  (uint32_t)total);
    append_acc(acc, &idx, "   VFP: ",    (uint32_t)correct_vfp,  (uint32_t)total);
    p = "   FRAME: ";  while (*p) acc[idx++] = *p++;
    char numbuf[16];
    int k = u32_to_decimal((uint32_t)total, numbuf, 0);
    for (int i = 0; i < k; ++i) acc[idx++] = numbuf[i];
#endif
    acc[idx] = '\0';
    fbm_draw_text(8, FOOTER_Y + 14, acc, COLOR_TXT, 1);
}

int main(void)
{
    uart_init();
    uart_puts("\n=== B6 MNIST HDMI demo (Option A: CGRA-FC head-to-head) ===\n");
#ifdef ENABLE_DCACHE
    /* MMU + I/D-cache: ~20-30x faster ARM. DMA windows (CGRA staging 1-3 MB,
     * framebuffers 0x100-0x12F MB) are non-cacheable -> coherent. */
    mmu_cache_enable();
    uart_puts("  MMU + I/D-cache ENABLED\n");
#endif

    arm_pmu_enable();
    arm_ccnt_reset();

    /* HDMI-OUT first, then HDMI-IN. hdmi_in_init's DMACR.Reset will
     * disturb HDMI-OUT timing momentarily (right-shifted / colour-off
     * visible artefacts on J11) but signal IS produced. Tested in this
     * order on silicon -- the inverse (HDMI-IN first) results in J11
     * showing "no signal" entirely, which is worse. */
    if (hdmi_init() < 0) { uart_puts("FAIL: hdmi_init\n"); for(;;); }
    uart_puts("HDMI ready, building FC chains...\n");
#if USE_V2_PARALLEL
    uart_puts("CGRA-FC mode: V2 PARALLEL (16 PEs, dual-port SPM, dst=15 fix)\n");
#elif USE_FAST_CGRA_FC
    uart_puts("CGRA-FC mode: FAST (soft-reset + hoisted CU regs + short readout)\n");
#else
    uart_puts("CGRA-FC mode: BASELINE v1 (USE_FAST_CGRA_FC=0)\n");
#endif

#ifdef LIVE_INPUT
    hdmi_in_assert_hpd();
    for (volatile uint32_t i = 0; i < 2000000; i++) ;
    hdmi_in_init();
    hdmi_in_color_convert_identity();
    /* One-time diagnostic: v_tc_1 detector (AXI-lite @ 0x43C90000 on FCLK0 —
     * NOT pixel-clock gated, safe to read) reports the ACTUAL incoming
     * resolution; plus the VDMA's programmed HSIZE/VSIZE/DMASR.  Tells us
     * whether the SOFEarly/EOLLate geometry error is a resolution mismatch
     * (detected H/V != programmed) or a framing issue.  (The prior "hang" was
     * the stale wrong address 0x43C30000, now corrected.) */
    hdmi_in_diag();
    uart_puts("HDMI-in initialised, waiting for laptop signal on J10...\n");
#endif

    uint32_t fc1_w_ddr = (uint32_t)(uintptr_t)cnn_spm_start;
    uint32_t fc2_w_ddr = fc1_w_ddr + CNN_FC1_N_OUTPUTS * CNN_FC1_SPM_BPN;
#if USE_V2_PARALLEL
    if (cnn_fc1_v2_build_chains(fc1_w_ddr) || cnn_fc2_v2_build_chains(fc2_w_ddr)) {
        uart_puts("FAIL: v2 FC chain build\n"); for(;;);
    }
#ifdef ENABLE_DCACHE
    /* Weights + SG chains were CPU-written to cacheable DDR — clean before
     * first CGRA DMA read. */
    cache_clean_all();
#endif
#else
    /* v1 chains: silicon-validated 97 % accuracy on MNIST sweep. */
    if (cnn_fc1_build_chains(fc1_w_ddr) || cnn_fc2_build_chains(fc2_w_ddr)) {
        uart_puts("FAIL: FC chain build\n"); for(;;);
    }
#endif

    render_static_chrome();
    hdmi_flush_fb();

    int correct_cgra = 0;
    int correct_int  = 0;
    int correct_vfp  = 0;
    int frame = 0;

    for (;;) {
        int i = frame % SWEEP_N_IMAGES;
        int label = (int)sweep_labels[i];

        int32_t act400[400];

#ifdef LIVE_INPUT
        /* Live-input mode: grab the most recent HDMI frame from J10,
         * downsample its ROI to 28×28, and feed the demo with it.
         *
         * VDMA halts on SOFEarlyErr after each frame with this AXIS
         * config — recover before reading. Without this, the FB stays
         * frozen at the first frame and the demo doesn't update as
         * the user draws. */
        /* Free-running 3-frame ring (CIRC_PARK, started in hdmi_in_init):
         * the IN VDMA captures continuously at the source frame rate;
         * current_frame() returns the previously COMPLETED store, so we
         * always read a whole frame.  recover_if_halted only re-arms on a
         * real error.  Do NOT halt per-iteration + 0.3ms settle (that read a
         * frame where only the top ~1% of lines were captured). */
        hdmi_in_recover_if_halted();   /* no-op unless errored */
        uint8_t live28[28*28];
        uint8_t live56[56*28];
        const uint8_t *fb = hdmi_in_current_frame();
        /* Whole-canvas capture: draw ANYWHERE on the Paint canvas; the digit
         * bounding box is auto re-centred into the 28x28 (MNIST framing). */
        downsample_roi_to_grid(fb, HDMI_ROI_CANVAS, live56, 56, 28); /* liveness */
        mnist_capture_digit(fb, live28);   /* high-res bbox + box-filter + CoM */
        /* DIAG: ASCII-art dump of the normalized 28x28 every 16 frames so the
         * crop/scale/centering can be inspected over UART. */
        {
            static uint32_t af = 0;
            if ((af++ & 0xF) == 0) {
                uart_puts("=== live28 ===\n");
                for (int y = 0; y < 28; y++) {
                    char line[30];
                    for (int x = 0; x < 28; x++) {
                        uint8_t v = live28[y*28 + x];
                        line[x] = (v > 192) ? '#' : (v > 96) ? '+' :
                                  (v > 32)  ? '.' : ' ';
                    }
                    line[28] = '\n'; line[29] = 0;
                    uart_puts(line);
                }
            }
        }
        /* DIAG: HDMI-IN capture state + raw bytes at ROI centre + downsampled
         * sum, every 4 frames.  Tells us if vdma_1 advances stores & whether
         * the captured pixels actually change as the user draws.  (Computed
         * AFTER downsample so ds28sum reflects THIS frame, not stale data.) */
        {
            static uint32_t df = 0;
            if ((df++ & 0x3) == 0) {
                uint32_t roi_off = (uint32_t)540 * HDMI_IN_ROW_STRIDE
                                 + (uint32_t)960 * HDMI_IN_BPP;  /* 1080p frame centre */
                uint32_t dsum = 0; for (int k = 0; k < 28*28; k++) dsum += live28[k];
                uart_puts("IN inSR="); uart_puthex(hdmi_in_dmasr());
                uart_puts(" store="); uart_puthex(hdmi_in_cur_store());
                uart_puts(" px@roi="); uart_puthex(((const uint8_t*)fb)[roi_off]);
                uart_putchar(','); uart_puthex(((const uint8_t*)fb)[roi_off+1]);
                uart_putchar(','); uart_puthex(((const uint8_t*)fb)[roi_off+2]);
                uart_puts(" ds28sum="); uart_puthex(dsum); uart_putchar('\n');
            }
        }
        /* IN VDMA left free-running (no per-iteration halt) so the ring keeps
         * completing whole frames.  HP0 carries IN-capture (~166 MB/s) +
         * OUT-display (~166 MB/s); well under the port's ~1.2 GB/s. */

#ifdef FORCE_FIXTURE_INPUT28
        /* DIAG: bypass HDMI capture, use a known-good 28x28 fixture.
         * Then arm_cnn_vfp_run() processes the SAME deterministic
         * input the sweep test uses. If CGRA still disagrees with ARM,
         * the bug is INSIDE arm_cnn_vfp_run's runtime behavior; if
         * they agree, the bug is in downsample_roi_to_mnist output. */
        for (int dbg = 0; dbg < 28*28; ++dbg)
            live28[dbg] = sweep_input28[0][dbg];
#endif
        /* === ROBUST FALLBACK (presentation safety) =======================
         * If the live HDMI-in capture is NOT producing frames — VDMA frame-
         * store not advancing, or any S2MM error bit (DMAIntErr/Slv/Dec/SOF)
         * set — fall back to the built-in MNIST sweep so the demo ALWAYS
         * shows working CGRA inference + the speedup, never a frozen screen.
         * Detection uses only the SAFE VDMA DMASR read (FCLK0 AXI-lite); it
         * does NOT touch the pixel-clock-gated v_tc regs (those hang the bus).
         * When live capture works, store advances every loop iter -> live. */
        int using_fixture = 0;
        {
            /* Liveness = frame CONTENT changes (ds28sum). The VDMA parks on
             * store 0 (DMASR[28:24] stays 0) even with capture fully running,
             * so the store index is NOT a liveness signal — silicon 2026-06-03:
             * 720p EDID live capture shows inSR=0x11000 (no errors), pixels
             * update every frame, store stuck 0. Use ds28sum delta + error
             * bits; latch ever_live on first content change. */
            static uint32_t prev_dsum = 0xFFFFFFFFu;
            static int      stuck      = 0;
            static int      ever_live  = 0;
            /* NOTE: do NOT use DMASR error bits — DMAIntErr/SOFEarly are sticky
             * from pre-EDID negotiation; capture runs fine with them set.
             * Live capture has sensor noise: ds28sum jitters every frame even
             * on a static screen -> ever_live latches in seconds; a frozen
             * pipeline yields bit-identical frames -> fallback at 8. */
            /* Liveness must use the RAW canvas grid (live56): the normalized
             * 28x28 is all-zero while blank -> false 'stuck'. The raw grid
             * carries capture noise -> jitters every frame when live. */
            uint32_t dsum = 0;
            for (int k = 0; k < 56*28; k++) dsum += live56[k];
            if (prev_dsum != 0xFFFFFFFFu && dsum != prev_dsum) ever_live = 1;
            if (dsum == prev_dsum) { if (stuck < 99) stuck++; }
            else                    { stuck = 0; }
            prev_dsum = dsum;
            /* Fall back when: capture never came alive (store never advanced),
             * OR it went live then sustained an error/halt (live-then-died).
             * Either way `stuck` must persist >=8 polls so a transient blip
             * doesn't flip a healthy stream into fixture mode. */
            if (stuck >= 8 && !ever_live) {
                using_fixture = 1;
                for (int k = 0; k < 28*28; k++) live28[k] = sweep_input28[i][k];
                static uint32_t fbnote = 0;
                if ((fbnote++ & 0x1F) == 0)
                    uart_puts("[fallback] HDMI-in not live -> using built-in MNIST sweep\n");
            }
        }
        arm_cnn_vfp_run(live28, act400);

        /* Defensive: re-pack each act400 entry as a clean sign-extended
         * INT16 → INT32. */
        for (int dbg = 0; dbg < 400; ++dbg) {
            int16_t v16 = (int16_t)act400[dbg];
            act400[dbg] = (int32_t)v16;
        }
        asm volatile("dsb" ::: "memory");

        /* DIAG: dump act400[0..7] every 32 frames so we can compare
         * with what CGRA's tile sees. */
        static uint32_t diag_frame = 0;
        if ((diag_frame & 0x1F) == 0) {
            uart_puts("act400[0..7]:");
            for (int d = 0; d < 8; ++d) {
                uart_putchar(' ');
                uart_puthex((uint32_t)act400[d]);
            }
            uart_putchar('\n');
        }
        diag_frame++;

        /* live capture: no ground truth (label=-1).  Fallback (fixture):
         * keep the sweep label so the panels show correct/miss as usual. */
        if (!using_fixture) label = -1;
        else                label = (int)sweep_labels[i];

#ifdef FORCE_FIXTURE_ACT400
        /* DIAGNOSTIC: override the live-derived act400 with sweep_act400[0].
         * If CGRA + ARM-INT predictions now agree -> the divergence is in
         * how arm_cnn_vfp_run's output reaches CGRA differently from ARM,
         * not in the FC RTL itself. If they still disagree -> bug is in the
         * CGRA FC chain proper. Built with -DFORCE_FIXTURE_ACT400=1. */
        for (int dbg = 0; dbg < 400; dbg++) act400[dbg] = sweep_act400[0][dbg];
        label = sweep_labels[0];
#endif
#else
        /* ARM-VFP Conv+Pool — accuracy-of-record path. */
        arm_cnn_vfp_run(sweep_input28[i], act400);
#endif

        /* ── three FC implementations on the same act400 ── */
        uint32_t t0, t1;
        uint32_t cyc_cgra, cyc_int, cyc_vfp;
        int pred_cgra, pred_int, pred_vfp;

        t0 = arm_ccnt_read();
        pred_cgra = run_cgra_fc(act400);
#ifdef CALIB_DUMP
        /* Dump per-neuron FC1 delta (CGRA - ARM_INT64 golden) for offline
         * averaging into cgra_fc1_corr[]. */
        {
            const uint32_t *fc1_w = (const uint32_t *)cnn_spm_start;
            uart_puts("CAL "); uart_putdec((uint32_t)i);
            for (int n = 0; n < 64; ++n) {
                const uint32_t *w = fc1_w + (uint32_t)n * 400u;
                int64_t acc = 0;
                for (int k = 0; k < 400; ++k)
                    acc += (int64_t)act400[k] * (int64_t)(int16_t)(w[k] & 0xFFFFu);
                int32_t d = calib_fc1_cgra[n] - (int32_t)acc;
                uart_putchar(' ');
                if (d < 0) { uart_putchar('-'); d = -d; }
                uart_putdec((uint32_t)d);
            }
            uart_putchar('\n');
        }
#endif
        t1 = arm_ccnt_read();
        cyc_cgra = t1 - t0;

        t0 = arm_ccnt_read();
        pred_int = arm_fc_int_run(act400, cnn_spm_start);
        t1 = arm_ccnt_read();
        cyc_int = t1 - t0;

        t0 = arm_ccnt_read();
        pred_vfp = arm_fc_vfp_run(act400, cnn_spm_start);
        t1 = arm_ccnt_read();
        cyc_vfp = t1 - t0;

        /* Accuracy counter only meaningful in fixture mode (label = -1
         * in live mode means no ground truth). */
        if (label >= 0) {
            if (pred_cgra == label) correct_cgra++;
            if (pred_int  == label) correct_int++;
            if (pred_vfp  == label) correct_vfp++;
        }

#ifdef LIVE_INPUT
        /* Always show live downsampled frame (no locked() check, which
         * would hang on VTC AXI-Lite). */
        fbm_draw_image28(IMG_X, IMG_Y, live28, IMG_SCALE);
#else
        fbm_draw_image28(IMG_X, IMG_Y, sweep_input28[i], IMG_SCALE);
#endif
        render_panel(PANEL_CGRA_X, pred_cgra, label, cyc_cgra);
        render_panel(PANEL_INT_X,  pred_int,  label, cyc_int);
        render_panel(PANEL_VFP_X,  pred_vfp,  label, cyc_vfp);
        render_footer(cyc_cgra, cyc_int, cyc_vfp,
                      correct_cgra, correct_int, correct_vfp, frame + 1);
        hdmi_flush_fb();

        uart_puts("img "); uart_putdec((uint32_t)i);
        uart_puts(" lbl="); uart_putdec((uint32_t)label);
        uart_puts(" cgra=");  uart_putdec((uint32_t)pred_cgra);
        uart_puts(" int=");   uart_putdec((uint32_t)pred_int);
        uart_puts(" vfp=");   uart_putdec((uint32_t)pred_vfp);
        uart_puts("  cycCGRA="); uart_puthex(cyc_cgra);
        uart_puts(" cycINT="); uart_puthex(cyc_int);
        uart_puts(" cycVFP="); uart_puthex(cyc_vfp);
        uart_puts(" vdmaSR="); uart_puthex(hdmi_out_dmasr());
        uart_putchar('\n');

        delay_cycles(CPU_HZ / 10);  /* ~100 ms dwell (caches on) */
        frame++;
    }
    return 0;
}
