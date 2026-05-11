/* demo_mnist_hdmi.c — M5 main: MNIST live HDMI demo, side-by-side
 * ARM-vs-CGRA mode optional.
 *
 * Layout (640x480, --compare mode):
 *
 *   +-----------------------------------------------------+
 *   |              MNIST IMAGE (224x224)                  |   top centered
 *   |              28x28 raw input × 8 scale              |   y in [24..248]
 *   +-------------------------+---------------------------+
 *   |         ARM             |          CGRA             |
 *   |    PRED: 7  GT: 7       |     PRED: 7  GT: 7        |
 *   |    0.31 MS  3225 FPS    |     2.12 MS  472 FPS      |
 *   |    1.0X (BASE)          |     13.1X SPEEDUP (CYC)   |
 *   +-------------------------+---------------------------+
 *   |     ACC: 99/100   DISPLAY: 8.7 FPS   FRAME: 47      |
 *   +-----------------------------------------------------+
 *
 * CGRA-only / ARM-only modes use the same layout but only fill one column.
 *
 * Build: make demo_mnist_hdmi
 * Run:   sudo /tmp/demo_mnist_hdmi [--arm | --compare] [--delay MS]
 *
 * Requires: hdmi_first_light.sh + hdmi_paint.sh have run since boot
 * (configures FCLK0, dynclk, VTC, VDMA, color_convert identity,
 * pixel_unpack V_24 mode).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#include "fb_lib.h"
#include "font5x7.h"
#include "cgra_user.h"
#include "arm_fc.h"
#include "mnist_sweep_fixture.h"

extern const uint32_t cnn_spm_start[];

#define FC1_BYTES        (ARM_FC1_N_OUT * ARM_FC1_N_IN * 4)
#define CGRA_FC1_GROUPS  16
#define CGRA_FC2_GROUPS   3

/* ---- visual layout constants ---- */
#define IMG_SCALE         8                              /* 28×8 = 224 px */
#define IMG_W            (28 * IMG_SCALE)                /* 224 */
#define IMG_X            ((FB_WIDTH - IMG_W) / 2)        /* 208 */
#define IMG_Y             24
#define IMG_BOTTOM       (IMG_Y + IMG_W)                 /* 248 */

#define DIVIDER_Y         (IMG_BOTTOM + 16)              /* 264 */
#define PANEL_Y          (DIVIDER_Y + 4)                 /* 268 */
#define FOOTER_Y          (FB_HEIGHT - 28)               /* 452 */

#define LEFT_X            16
#define RIGHT_X           (FB_WIDTH / 2 + 8)

/* ---- timing helper ---- */
static double ms_since(const struct timespec *t0) {
    struct timespec t1;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    return (double)(t1.tv_sec - t0->tv_sec) * 1000.0
         + (double)(t1.tv_nsec - t0->tv_nsec) * 1e-6;
}

/* ---- modes ---- */
typedef enum { MODE_CGRA = 0, MODE_ARM = 1, MODE_COMPARE = 2 } mode_t;

/* ---- graceful shutdown on Ctrl-C ---- */
static volatile int keep_running = 1;
static void on_sigint(int sig) { (void)sig; keep_running = 0; }

/* ---- format short fixed-point with 1 decimal (no float printf flakiness) ---- */
static void format_ms(char *buf, size_t n, double ms) {
    /* 0..999.9 ms range; clamp */
    if (ms < 0.0) ms = 0.0;
    if (ms > 9999.9) ms = 9999.9;
    int whole = (int)ms;
    int frac  = (int)((ms - (double)whole) * 10.0 + 0.5);
    if (frac >= 10) { whole++; frac = 0; }
    snprintf(buf, n, "%d.%d MS", whole, frac);
}

static void format_fps(char *buf, size_t n, double ms_per) {
    if (ms_per <= 0.001) { snprintf(buf, n, "----- FPS"); return; }
    double fps = 1000.0 / ms_per;
    snprintf(buf, n, "%d FPS", (int)(fps + 0.5));
}

static void format_speedup(char *buf, size_t n, double mult) {
    if (mult < 0.0) mult = 0.0;
    int whole = (int)mult;
    int frac  = (int)((mult - (double)whole) * 10.0 + 0.5);
    if (frac >= 10) { whole++; frac = 0; }
    snprintf(buf, n, "%d.%dX", whole, frac);
}

/* ---- render a single panel (ARM or CGRA stats) ----
 *
 * For ARM:   header + PRED/GT + "WALL: 0.3 MS" + "3225 FPS"
 * For CGRA:  header + PRED/GT + "WALL: 2.1 MS" + "PURE: 0.24 MS"
 *                                + "SPEEDUP: 13.0X PURE"
 *
 * "WALL" includes Linux APB-poll overhead — the user-visible time.
 * "PURE" is CU_CYCLES at 50 MHz — the silicon's actual compute time.
 * Both shown honestly so the comparison can be assessed from either angle.
 */
static void draw_panel(fb_t *fb, int x, const char *label, uint32_t lbl_color,
                       int pred, int gt, double wall_ms,
                       int show_pure, double pure_ms, double pure_speedup)
{
    /* Clear panel area */
    fb_rect(fb, x, PANEL_Y, FB_WIDTH/2 - 16, FOOTER_Y - PANEL_Y - 8, FB_DARKBG);

    /* Header */
    fb_draw_text(fb, x, PANEL_Y, label, lbl_color, 3);

    char buf[64];
    int line_h = (FONT5X7_HEIGHT + 1) * 2 + 4;  /* ~20 px */

    /* PRED/GT line — green if matches ground truth, red otherwise. */
    int y = PANEL_Y + 28;
    snprintf(buf, sizeof(buf), "PRED: %d  GT: %d", pred, gt);
    fb_draw_text(fb, x, y, buf,
                 (pred == gt) ? FB_GREEN : FB_RED, 2);

    /* WALL line — wall-clock ms + derived FPS. */
    y += line_h;
    char ms_buf[24], fps_buf[24];
    format_ms(ms_buf, sizeof(ms_buf), wall_ms);
    format_fps(fps_buf, sizeof(fps_buf), wall_ms);
    snprintf(buf, sizeof(buf), "WALL: %s", ms_buf);
    fb_draw_text(fb, x, y, buf, FB_YELLOW, 2);

    y += line_h;
    fb_draw_text(fb, x, y, fps_buf, FB_WHITE, 2);

    /* PURE line + SPEEDUP line — only on CGRA panel in compare mode. */
    if (show_pure) {
        y += line_h;
        format_ms(ms_buf, sizeof(ms_buf), pure_ms);
        snprintf(buf, sizeof(buf), "PURE: %s", ms_buf);
        fb_draw_text(fb, x, y, buf, FB_CYAN, 2);

        y += line_h;
        char sp_buf[16];
        format_speedup(sp_buf, sizeof(sp_buf), pure_speedup);
        snprintf(buf, sizeof(buf), "SPEEDUP: %s", sp_buf);
        fb_draw_text(fb, x, y, buf, FB_CYAN, 2);
    }
}

int main(int argc, char **argv)
{
    mode_t mode = MODE_CGRA;
    int delay_ms = 100;

    for (int i = 1; i < argc; ++i) {
        if      (!strcmp(argv[i], "--arm"))     mode = MODE_ARM;
        else if (!strcmp(argv[i], "--cgra"))    mode = MODE_CGRA;
        else if (!strcmp(argv[i], "--compare")) mode = MODE_COMPARE;
        else if (!strcmp(argv[i], "--delay") && i + 1 < argc) {
            delay_ms = atoi(argv[++i]);
            if (delay_ms < 0) delay_ms = 0;
        } else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
            fprintf(stderr,
                "usage: %s [--arm | --cgra | --compare] [--delay MS]\n"
                "  --cgra     CGRA-only inference (default)\n"
                "  --arm      ARM scalar inference\n"
                "  --compare  side-by-side, both paths each frame\n"
                "  --delay MS frame dwell in milliseconds (default 100)\n",
                argv[0]);
            return 0;
        }
    }
    signal(SIGINT, on_sigint);

    /* ---- init: FB + CGRA (CGRA needed even in --arm so the hardware
     * stays warm and we report a consistent CGRA path; we just skip the
     * cgra_user_run_inference call in ARM-only mode). ---- */
    fb_t fb = {0};
    if (fb_open(&fb, FB_DEFAULT_PHYS) < 0) return 1;
    fprintf(stderr, "demo: FB mmap'd OK\n");

    cgra_user_t u;
    int cgra_ok = (cgra_user_init(&u) == 0);
    if (!cgra_ok && mode != MODE_ARM) {
        fprintf(stderr, "demo: CGRA init failed; forcing --arm mode\n");
        mode = MODE_ARM;
    }

    const uint32_t *fc1_w = cnn_spm_start;
    const uint32_t *fc2_w = cnn_spm_start + (FC1_BYTES / 4);
    int32_t fc1_acc[ARM_FC1_N_OUT];
    int32_t arm_fc2[ARM_FC2_N_OUT];
    int32_t cgra_fc2[ARM_FC2_N_OUT];

    /* ---- static UI: clear + banner + image-tile border ---- */
    fb_clear(&fb, FB_DARKBG);
    const char *banner =
        (mode == MODE_ARM)     ? "MNIST DEMO ARM-ONLY" :
        (mode == MODE_COMPARE) ? "MNIST DEMO ARM VS CGRA" :
                                 "MNIST DEMO CGRA";
    fb_draw_text(&fb, 16, 4, banner, FB_WHITE, 2);
    /* Border around image tile */
    fb_rect(&fb, IMG_X - 2, IMG_Y - 2, IMG_W + 4, 1,   FB_GRAY);
    fb_rect(&fb, IMG_X - 2, IMG_BOTTOM + 1, IMG_W + 4, 1, FB_GRAY);
    fb_rect(&fb, IMG_X - 2, IMG_Y - 2, 1, IMG_W + 4,   FB_GRAY);
    fb_rect(&fb, IMG_X + IMG_W + 1, IMG_Y - 2, 1, IMG_W + 4, FB_GRAY);
    /* Horizontal divider above the panels */
    fb_rect(&fb, 0, DIVIDER_Y, FB_WIDTH, 1, FB_GRAY);

    /* ---- main loop ---- */
    int frame = 0;
    int arm_correct = 0, cgra_correct = 0, seen = 0;

    /* Display-FPS moving average over last 30 frames */
    #define DISP_WIN 30
    double frame_ms_ring[DISP_WIN] = {0};
    int    ring_pos = 0;
    int    ring_n   = 0;
    double frame_ms_sum = 0.0;

    while (keep_running) {
        struct timespec t_frame_start;
        clock_gettime(CLOCK_MONOTONIC, &t_frame_start);

        int idx = frame % SWEEP_N_IMAGES;
        int label = (int)sweep_labels[idx];

        /* ---- inference paths ---- */
        double arm_ms = 0.0, cgra_ms = 0.0;
        int arm_pred = -1, cgra_pred = -1;
        uint64_t cgra_cycles = 0;

        if (mode != MODE_CGRA) {
            struct timespec t0; clock_gettime(CLOCK_MONOTONIC, &t0);
            arm_fc1_64x400(sweep_act400[idx], fc1_w, fc1_acc);
            arm_fc2_10x64 (sweep_act64[idx],  fc2_w, arm_fc2);
            arm_pred = arm_argmax(arm_fc2, 10);
            arm_ms = ms_since(&t0);
        }
        if (mode != MODE_ARM) {
            struct timespec t0; clock_gettime(CLOCK_MONOTONIC, &t0);
            if (cgra_user_run_inference(&u, sweep_act400[idx],
                                        sweep_act64[idx], cgra_fc2) == 0) {
                cgra_pred = arm_argmax(cgra_fc2, 10);
                cgra_ms = ms_since(&t0);
                uint32_t per_group_cyc = cgra_read(&u.dev, CGRA_CU_CYCLES);
                cgra_cycles = (uint64_t)per_group_cyc *
                              (CGRA_FC1_GROUPS + CGRA_FC2_GROUPS);
            }
        }

        /* Per-image correctness accumulator */
        seen++;
        if (arm_pred  == label) arm_correct++;
        if (cgra_pred == label) cgra_correct++;

        /* ---- render image tile ---- */
        fb_draw_image28(&fb, IMG_X, IMG_Y, sweep_input28[idx], IMG_SCALE);

        /* ---- render panels ----
         *
         * cgra_pure_ms is the CU's compute-only time (CU_CYCLES @ 50 MHz),
         * exclusive of the Linux APB-poll overhead that dominates cgra_ms
         * (wall-clock). Speedup is ARM-wall vs CGRA-pure: it answers "how
         * much faster is the silicon" rather than "how much faster is this
         * Linux harness", which is the thesis-relevant number. */
        double cgra_pure_ms = (double)cgra_cycles * 20e-6;  /* 20 ns/cycle */
        double pure_speedup = (cgra_pure_ms > 0.0) ? (arm_ms / cgra_pure_ms) : 0.0;

        if (mode == MODE_COMPARE) {
            draw_panel(&fb, LEFT_X,  "ARM",  FB_WHITE,
                       arm_pred, label, arm_ms,
                       0, 0.0, 0.0);
            draw_panel(&fb, RIGHT_X, "CGRA", FB_CYAN,
                       cgra_pred, label, cgra_ms,
                       1, cgra_pure_ms, pure_speedup);
        } else if (mode == MODE_ARM) {
            draw_panel(&fb, LEFT_X, "ARM SCALAR", FB_WHITE,
                       arm_pred, label, arm_ms,
                       0, 0.0, 0.0);
        } else {
            /* CGRA-only: still show PURE so the silicon's compute time is
             * visible alongside the user-visible wall-clock. */
            draw_panel(&fb, LEFT_X, "CGRA", FB_CYAN,
                       cgra_pred, label, cgra_ms,
                       1, cgra_pure_ms, pure_speedup);
        }

        /* ---- footer: accuracy + display FPS + frame number ---- */
        fb_rect(&fb, 0, FOOTER_Y, FB_WIDTH, FONT5X7_HEIGHT * 3, FB_DARKBG);
        char foot[96];
        int reported_correct = (mode == MODE_ARM) ? arm_correct
                              : (mode == MODE_CGRA) ? cgra_correct
                              : cgra_correct;   /* report CGRA in compare */
        double avg_frame_ms = (ring_n > 0) ? (frame_ms_sum / ring_n) : 0.0;
        char disp_fps[24];
        format_fps(disp_fps, sizeof(disp_fps), avg_frame_ms);
        snprintf(foot, sizeof(foot), "ACC: %d/%d   DISPLAY: %s   FRAME: %d",
                 reported_correct, seen, disp_fps, frame);
        fb_draw_text(&fb, 16, FOOTER_Y, foot, FB_WHITE, 2);

        /* ---- pacing ---- */
        if (delay_ms > 0) usleep((useconds_t)delay_ms * 1000u);

        /* ---- update display-FPS ring ---- */
        double frame_ms = ms_since(&t_frame_start);
        frame_ms_sum -= frame_ms_ring[ring_pos];
        frame_ms_ring[ring_pos] = frame_ms;
        frame_ms_sum += frame_ms;
        ring_pos = (ring_pos + 1) % DISP_WIN;
        if (ring_n < DISP_WIN) ring_n++;

        frame++;
    }

    fprintf(stderr, "\ndemo: stopped after %d frames\n", frame);
    if (cgra_ok) cgra_user_close(&u);
    fb_close(&fb);
    return 0;
}
