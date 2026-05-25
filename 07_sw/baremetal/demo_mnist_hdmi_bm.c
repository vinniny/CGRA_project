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
#include "arm_cnn_bm.h"
#include "arm_fc_bm.h"
#include "hdmi_bm.h"
#include "fb_lib_bm.h"
#include "mnist_sweep_fixture.h"
#include "../cnn_eval/mnist_weights_scale.h"
#ifdef LIVE_INPUT
#include "hdmi_in_bm.h"
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
static int run_cgra_fc(const int32_t act400[400])
{
    volatile int32_t *act400_ddr = (volatile int32_t *)ACT400_DDR;
    for (int j = 0; j < 400; ++j) act400_ddr[j] = act400[j];
    asm volatile("dsb" ::: "memory");

    if (cnn_fc1_tile_preload(ACT400_DDR)) return -1;
    int32_t fc1_acc[64];
    for (int g = 0; g < (int)CNN_FC1_N_GROUPS; ++g) {
        int32_t grp[4];
        if (cnn_fc1_run_group(g, grp)) return -1;
        for (int r = 0; r < 4; ++r) fc1_acc[g*4 + r] = grp[r];
    }
    int32_t act64[64];
    fc1_post_process(fc1_acc, act64);

    volatile int32_t *act64_ddr = (volatile int32_t *)ACT64_DDR;
    for (int j = 0; j < 64; ++j) act64_ddr[j] = act64[j];
    asm volatile("dsb" ::: "memory");

    if (cnn_fc2_tile_preload(ACT64_DDR)) return -1;
    int32_t fc2_acc[12];
    for (int g = 0; g < (int)CNN_FC2_N_GROUPS; ++g) {
        int32_t grp[4];
        if (cnn_fc2_run_group(g, grp)) return -1;
        for (int r = 0; r < 4 && g*4+r < 10; ++r) fc2_acc[g*4+r] = grp[r];
    }
    return argmax_with_bias(fc2_acc);
}

/* ── Formatting helpers ──────────────────────────────────────────────── */
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

    arm_pmu_enable();
    arm_ccnt_reset();

    if (hdmi_init() < 0) { uart_puts("FAIL: hdmi_init\n"); for(;;); }
    uart_puts("HDMI ready, building FC chains...\n");

#ifdef LIVE_INPUT
    /* HDMI-in init order matters: assert HPD BEFORE re-init, so source
     * is already transmitting by the time VDMA starts. hdmi_in_init
     * also resets the SHARED VDMA which momentarily disturbs HDMI-OUT
     * (the MM2S side) but it recovers within a frame. */
    hdmi_in_assert_hpd();
    /* Brief settle for source renegotiation. */
    for (volatile uint32_t i = 0; i < 2000000; i++) ;
    hdmi_in_init();
    hdmi_in_color_convert_identity();
    uart_puts("HDMI-in initialised, waiting for laptop signal on J10...\n");
#endif

    uint32_t fc1_w_ddr = (uint32_t)(uintptr_t)cnn_spm_start;
    uint32_t fc2_w_ddr = fc1_w_ddr + CNN_FC1_N_OUTPUTS * CNN_FC1_SPM_BPN;
    /* v1 chains: silicon-validated 97 % accuracy on MNIST sweep. */
    if (cnn_fc1_build_chains(fc1_w_ddr) || cnn_fc2_build_chains(fc2_w_ddr)) {
        uart_puts("FAIL: FC chain build\n"); for(;;);
    }

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
        hdmi_in_recover_if_halted();
        /* Brief settle so VDMA has time to write at least the top of a
         * new frame before we sample it. */
        for (volatile int s = 0; s < 200000; s++) ;
        uint8_t live28[28*28];
        const uint8_t *fb = hdmi_in_current_frame();
        downsample_roi_to_mnist(fb, HDMI_ROI_DEFAULT, live28);
        arm_cnn_vfp_run(live28, act400);
        label = -1;                     /* no ground truth in live mode */
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
        uart_putchar('\n');

        delay_cycles(CPU_HZ / 5);  /* ~200 ms dwell */
        frame++;
    }
    return 0;
}
