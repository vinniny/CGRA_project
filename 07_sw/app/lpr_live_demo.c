/* ===================================================================
 *  lpr_live_demo.c – Live Camera LPR Demo on Zynq ARM + HDMI
 *
 *  Captures frames from USB camera (/dev/video1), displays on HDMI
 *  via framebuffer (/dev/fb0), runs golden model CNN inference on
 *  a selected 28x28 region, and overlays the result.
 *
 *  Pipeline:
 *    V4L2 capture (YUYV 640x480) → Grayscale → Display on FB
 *    → Extract 28x28 ROI → Conv1→Pool1→Conv2→Pool2→FC→30 classes
 *    → Overlay prediction + FPS on screen
 *
 *  Usage:
 *    ./lpr_live_demo                    # default /dev/video1
 *    ./lpr_live_demo /dev/video1        # specify device
 *    ./lpr_live_demo /dev/video1 weights.bin  # load trained weights
 *
 *  Controls (stdin):
 *    q/Q  — quit
 *
 *  Build:
 *    make CROSS=arm-linux-gnueabihf- lpr_live_demo
 * =================================================================== */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <linux/videodev2.h>
#include <signal.h>

#include "../lib/lpr_golden.h"

/* ── Display / Camera Configuration ─────────────────────────────── */

#define CAM_WIDTH       352
#define CAM_HEIGHT      288
#define CAM_BUF_COUNT   1
#define USE_MJPEG       0       /* 0=YUYV, 1=MJPEG */

#define FB_DEV          "/dev/fb0"
#define FB_WIDTH        1920
#define FB_HEIGHT       1080
#define FB_BPP          3       /* 24-bit RGB */
#define FB_STRIDE       5760    /* bytes per row */

/* ROI box for plate extraction (center of frame, covers both rows) */
#define ROI_W           160     /* plate region width in camera pixels */
#define ROI_H           80      /* plate region height (2 rows) */
#define ROI_X           ((CAM_WIDTH - ROI_W) / 2)
#define ROI_Y           ((CAM_HEIGHT - ROI_H) / 2)

/* Vietnamese plate layout: 2 rows
 *   Row 1: 4 chars (e.g., "66L1")
 *   Row 2: 5 chars (e.g., "40588")
 */
#define ROW1_CHARS      4
#define ROW2_CHARS      5
#define MAX_PLATE_CHARS (ROW1_CHARS + ROW2_CHARS)  /* 9 total */

/* Scale factor for displaying camera on framebuffer */
#define SCALE           2       /* 352*2=704, 288*2=576 — fits in 1920x1080 */
#define DISP_X          ((FB_WIDTH - CAM_WIDTH * SCALE) / 2)
#define DISP_Y          80      /* Top margin for title above */

/* ── Timing ─────────────────────────────────────────────────────── */

static inline double time_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

/* ── V4L2 Camera (MMAP, single buffer, minimal CMA) ─────────── */

static int cam_fd = -1;
static uint8_t *cam_mmap_ptr = NULL;
static size_t cam_mmap_len = 0;
static size_t cam_frame_size;
static int cam_streaming = 0;

static int cam_open(const char *dev)
{
    cam_fd = open(dev, O_RDWR | O_NONBLOCK);
    if (cam_fd < 0) { perror("open camera"); return -1; }

    /* Set format */
    struct v4l2_format fmt;
    memset(&fmt, 0, sizeof(fmt));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = CAM_WIDTH;
    fmt.fmt.pix.height = CAM_HEIGHT;
#if USE_MJPEG
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
#else
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
#endif
    fmt.fmt.pix.field = V4L2_FIELD_NONE;
    if (ioctl(cam_fd, VIDIOC_S_FMT, &fmt) < 0) {
        perror("VIDIOC_S_FMT");
        close(cam_fd); cam_fd = -1;
        return -1;
    }
    cam_frame_size = fmt.fmt.pix.sizeimage;
    if (cam_frame_size == 0)
        cam_frame_size = CAM_WIDTH * CAM_HEIGHT;  /* MJPEG is usually much smaller */
    printf("[CAM] Format: %dx%d %s (sizeimage=%zu bytes)\n",
           fmt.fmt.pix.width, fmt.fmt.pix.height,
           USE_MJPEG ? "MJPEG" : "YUYV", cam_frame_size);

    /* Request single MMAP buffer (minimal CMA usage) */
    struct v4l2_requestbuffers req;
    memset(&req, 0, sizeof(req));
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if (ioctl(cam_fd, VIDIOC_REQBUFS, &req) < 0) {
        perror("VIDIOC_REQBUFS");
        close(cam_fd); cam_fd = -1;
        return -1;
    }
    printf("[CAM] Allocated %d buffer(s)\n", req.count);

    /* Query and map the buffer */
    struct v4l2_buffer buf;
    memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if (ioctl(cam_fd, VIDIOC_QUERYBUF, &buf) < 0) {
        perror("VIDIOC_QUERYBUF");
        close(cam_fd); cam_fd = -1;
        return -1;
    }
    cam_mmap_len = buf.length;
    cam_mmap_ptr = (uint8_t *)mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                                    MAP_SHARED, cam_fd, buf.m.offset);
    if (cam_mmap_ptr == MAP_FAILED) {
        perror("mmap cam");
        close(cam_fd); cam_fd = -1;
        return -1;
    }

    /* Queue the buffer */
    if (ioctl(cam_fd, VIDIOC_QBUF, &buf) < 0) {
        perror("VIDIOC_QBUF");
        munmap(cam_mmap_ptr, cam_mmap_len);
        close(cam_fd); cam_fd = -1;
        return -1;
    }

    /* Start streaming */
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(cam_fd, VIDIOC_STREAMON, &type) < 0) {
        perror("VIDIOC_STREAMON");
        munmap(cam_mmap_ptr, cam_mmap_len);
        close(cam_fd); cam_fd = -1;
        return -1;
    }
    cam_streaming = 1;

    printf("[CAM] Streaming started (1 MMAP buffer)\n");
    return 0;
}

static size_t cam_last_bytesused = 0;

static uint8_t *cam_capture(void)
{
    /* Wait for data with timeout (non-blocking fd) */
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(cam_fd, &fds);
    struct timeval tv = { .tv_sec = 2, .tv_usec = 0 };
    int r = select(cam_fd + 1, &fds, NULL, NULL, &tv);
    if (r <= 0) return NULL;  /* timeout or error */

    struct v4l2_buffer buf;
    memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    if (ioctl(cam_fd, VIDIOC_DQBUF, &buf) < 0) return NULL;

    cam_last_bytesused = buf.bytesused;

    /* Re-queue immediately */
    ioctl(cam_fd, VIDIOC_QBUF, &buf);
    return cam_mmap_ptr;
}

static void cam_close(void)
{
    if (cam_streaming) {
        enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ioctl(cam_fd, VIDIOC_STREAMOFF, &type);
    }
    if (cam_mmap_ptr && cam_mmap_ptr != MAP_FAILED)
        munmap(cam_mmap_ptr, cam_mmap_len);
    if (cam_fd >= 0)
        close(cam_fd);
}

/* ── Framebuffer ────────────────────────────────────────────────── */

static uint8_t *fb_mem = NULL;
static int fb_fd = -1;
static size_t fb_size;

static int fb_open(void)
{
    fb_fd = open(FB_DEV, O_RDWR);
    if (fb_fd < 0) { perror("open fb"); return -1; }

    fb_size = FB_STRIDE * FB_HEIGHT;
    fb_mem = (uint8_t *)mmap(NULL, fb_size, PROT_READ | PROT_WRITE,
                              MAP_SHARED, fb_fd, 0);
    if (fb_mem == MAP_FAILED) { perror("mmap fb"); return -1; }

    /* Clear to black */
    memset(fb_mem, 0, fb_size);
    printf("[FB] Framebuffer opened: %dx%d %dbpp stride=%d\n",
           FB_WIDTH, FB_HEIGHT, FB_BPP * 8, FB_STRIDE);
    return 0;
}

static inline void fb_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    if (x < 0 || x >= FB_WIDTH || y < 0 || y >= FB_HEIGHT) return;
    uint8_t *p = fb_mem + y * FB_STRIDE + x * FB_BPP;
    p[0] = b; p[1] = g; p[2] = r;  /* BGR order for 24-bit FB */
}

static void fb_close(void)
{
    if (fb_mem && fb_mem != MAP_FAILED)
        munmap(fb_mem, fb_size);
    if (fb_fd >= 0)
        close(fb_fd);
}

/* ── Simple 5x7 Font for Overlay ────────────────────────────────── */

static const uint8_t font5x7[][5] = {
    /* 0-9 */
    {0x7C,0x82,0x82,0x82,0x7C}, {0x00,0x84,0xFE,0x80,0x00},
    {0xC4,0xA2,0x92,0x92,0x8C}, {0x44,0x82,0x92,0x92,0x6C},
    {0x30,0x28,0x24,0xFE,0x20}, {0x4E,0x8A,0x8A,0x8A,0x72},
    {0x78,0x94,0x92,0x92,0x60}, {0x02,0xE2,0x12,0x0A,0x06},
    {0x6C,0x92,0x92,0x92,0x6C}, {0x0C,0x92,0x92,0x52,0x3C},
    /* A-Z (10-35) */
    {0xFC,0x22,0x22,0x22,0xFC}, {0xFE,0x92,0x92,0x92,0x6C},
    {0x7C,0x82,0x82,0x82,0x44}, {0xFE,0x82,0x82,0x82,0x7C},
    {0xFE,0x92,0x92,0x92,0x82}, {0xFE,0x12,0x12,0x12,0x02},
    {0x7C,0x82,0x92,0x92,0x74}, {0xFE,0x10,0x10,0x10,0xFE},
    {0x00,0x82,0xFE,0x82,0x00}, {0x40,0x80,0x82,0x7E,0x02},
    {0xFE,0x10,0x28,0x44,0x82}, {0xFE,0x80,0x80,0x80,0x80},
    {0xFE,0x04,0x18,0x04,0xFE}, {0xFE,0x08,0x10,0x20,0xFE},
    {0x7C,0x82,0x82,0x82,0x7C}, {0xFE,0x12,0x12,0x12,0x0C},
    {0x7C,0x82,0xA2,0x42,0xBC}, {0xFE,0x12,0x32,0x52,0x8C},
    {0x8C,0x92,0x92,0x92,0x62}, {0x02,0x02,0xFE,0x02,0x02},
    {0x7E,0x80,0x80,0x80,0x7E}, {0x3E,0x40,0x80,0x40,0x3E},
    {0xFE,0x40,0x30,0x40,0xFE}, {0xC6,0x28,0x10,0x28,0xC6},
    {0x06,0x08,0xF0,0x08,0x06}, {0xC2,0xA2,0x92,0x8A,0x86},
};

static int char_to_font_idx(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return -1;
}

static void fb_draw_char(int x, int y, char c, int scale,
                         uint8_t r, uint8_t g, uint8_t b)
{
    int idx = char_to_font_idx(c);
    if (idx < 0) return;
    for (int col = 0; col < 5; col++) {
        uint8_t bits = font5x7[idx][col];
        for (int row = 0; row < 8; row++) {
            if (bits & (1 << row)) {
                for (int sy = 0; sy < scale; sy++)
                    for (int sx = 0; sx < scale; sx++)
                        fb_pixel(x + col * scale + sx,
                                 y + row * scale + sy, r, g, b);
            }
        }
    }
}

static void fb_draw_string(int x, int y, const char *s, int scale,
                           uint8_t r, uint8_t g, uint8_t b)
{
    while (*s) {
        if (*s == ' ') { x += 4 * scale; s++; continue; }
        if (*s == '.' || *s == ':' || *s == '/') {
            /* Draw a dot for punctuation */
            for (int sy = 0; sy < scale; sy++)
                for (int sx = 0; sx < scale; sx++)
                    fb_pixel(x + sx, y + 6 * scale + sy, r, g, b);
            x += 3 * scale;
            s++;
            continue;
        }
        fb_draw_char(x, y, *s, scale, r, g, b);
        x += 6 * scale;
        s++;
    }
}

/* ── Frame to Grayscale Conversion ──────────────────────────────── */

static uint8_t gray_frame[CAM_WIDTH * CAM_HEIGHT];

static void yuyv_to_gray(const uint8_t *yuyv)
{
    for (int i = 0; i < CAM_WIDTH * CAM_HEIGHT; i++) {
        gray_frame[i] = yuyv[i * 2];  /* Y component */
    }
}

/* Minimal MJPEG→grayscale: scan for start-of-scan marker, then
 * extract Y channel from the raw interleaved MCU data.
 * This is a ROUGH approximation — works for demo display purposes.
 * For cheap USB cameras, MJPEG is baseline JPEG with YUV422. */
static int mjpeg_to_gray(const uint8_t *data, size_t len)
{
    /* Find SOF0 marker (0xFF 0xC0) to get actual dimensions */
    int width = CAM_WIDTH, height = CAM_HEIGHT;
    for (size_t i = 0; i + 10 < len; i++) {
        if (data[i] == 0xFF && data[i+1] == 0xC0) {
            height = (data[i+5] << 8) | data[i+6];
            width  = (data[i+7] << 8) | data[i+8];
            break;
        }
    }
    (void)width; (void)height;

    /* Simple fallback: fill gray_frame with a mid-gray pattern
     * using whatever luminance-like data we can extract.
     * For the demo, we'll just use raw bytes after the SOS marker
     * as an approximation of the luminance plane. */
    size_t sos_pos = 0;
    for (size_t i = 0; i + 1 < len; i++) {
        if (data[i] == 0xFF && data[i+1] == 0xDA) {
            /* Skip SOS header (variable length) */
            int hdr_len = (data[i+2] << 8) | data[i+3];
            sos_pos = i + 2 + hdr_len;
            break;
        }
    }

    if (sos_pos == 0 || sos_pos >= len) {
        /* Fallback: just fill with raw data bytes */
        memset(gray_frame, 128, sizeof(gray_frame));
        return -1;
    }

    /* Extract raw entropy data, skip stuffed bytes (0xFF 0x00 → 0xFF).
     * Map roughly to pixel positions. This won't be a proper JPEG decode
     * but gives a recognizable image for the demo. */
    int px = 0;
    int total = CAM_WIDTH * CAM_HEIGHT;
    for (size_t i = sos_pos; i < len && px < total; i++) {
        if (data[i] == 0xFF) {
            if (i + 1 < len && data[i+1] == 0x00) {
                gray_frame[px++] = data[i];
                i++;  /* skip stuffed byte */
            } else if (i + 1 < len && data[i+1] == 0xD9) {
                break;  /* EOI marker */
            }
            /* skip other markers */
        } else {
            gray_frame[px++] = data[i];
        }
    }
    /* Fill remaining pixels */
    while (px < total) gray_frame[px++] = 128;
    return 0;
}

static void frame_to_gray(const uint8_t *data, size_t len)
{
#if USE_MJPEG
    mjpeg_to_gray(data, len);
#else
    (void)len;
    yuyv_to_gray(data);
#endif
}

/* ── Draw Camera Frame to Framebuffer (scaled 2x) ──────────────── */

static void fb_draw_camera(void)
{
    for (int y = 0; y < CAM_HEIGHT; y++) {
        /* Build one scaled row */
        int fy = DISP_Y + y * SCALE;
        uint8_t *row = fb_mem + fy * FB_STRIDE + DISP_X * FB_BPP;
        for (int x = 0; x < CAM_WIDTH; x++) {
            uint8_t g = gray_frame[y * CAM_WIDTH + x];
            for (int dx = 0; dx < SCALE; dx++) {
                row[0] = g; row[1] = g; row[2] = g;
                row += FB_BPP;
            }
        }
        /* Duplicate row for vertical scaling */
        for (int dy = 1; dy < SCALE; dy++) {
            memcpy(fb_mem + (fy + dy) * FB_STRIDE + DISP_X * FB_BPP,
                   fb_mem + fy * FB_STRIDE + DISP_X * FB_BPP,
                   CAM_WIDTH * SCALE * FB_BPP);
        }
    }
}

/* ── Draw ROI Box ───────────────────────────────────────────────── */

static void fb_draw_roi_box(void)
{
    int x0 = DISP_X + ROI_X * SCALE;
    int y0 = DISP_Y + ROI_Y * SCALE;
    int x1 = x0 + ROI_W * SCALE;
    int y1 = y0 + ROI_H * SCALE;

    /* Draw green rectangle (2px thick) */
    for (int x = x0; x < x1; x++) {
        fb_pixel(x, y0, 0, 255, 0);
        fb_pixel(x, y0 + 1, 0, 255, 0);
        fb_pixel(x, y1 - 1, 0, 255, 0);
        fb_pixel(x, y1 - 2, 0, 255, 0);
    }
    for (int y = y0; y < y1; y++) {
        fb_pixel(x0, y, 0, 255, 0);
        fb_pixel(x0 + 1, y, 0, 255, 0);
        fb_pixel(x1 - 1, y, 0, 255, 0);
        fb_pixel(x1 - 2, y, 0, 255, 0);
    }
}

/* ── Extract 28x28 character from a specific row/column in the ROI ── */

static void extract_char_28x28(int32_t *img28, int row, int col, int cols_in_row)
{
    /* Each row is half the ROI height */
    int row_h = ROI_H / 2;
    int slot_w = ROI_W / cols_in_row;
    int slot_x = ROI_X + col * slot_w;
    int slot_y = ROI_Y + row * row_h;

    for (int oy = 0; oy < GOLDEN_IN_H; oy++) {
        for (int ox = 0; ox < GOLDEN_IN_W; ox++) {
            int sx = slot_x + ox * slot_w / GOLDEN_IN_W;
            int sy = slot_y + oy * row_h / GOLDEN_IN_H;
            if (sx >= CAM_WIDTH) sx = CAM_WIDTH - 1;
            if (sy >= CAM_HEIGHT) sy = CAM_HEIGHT - 1;
            img28[oy * GOLDEN_IN_W + ox] = (int32_t)gray_frame[sy * CAM_WIDTH + sx];
        }
    }
}

/* ── Signal-based exit (Ctrl+C) ─────────────────────────────────── */

static volatile int running = 1;

static void sigint_handler(int sig)
{
    (void)sig;
    running = 0;
}

/* ── Main ───────────────────────────────────────────────────────── */

int main(int argc, char *argv[])
{
    const char *cam_dev = "/dev/video1";
    const char *weight_file = NULL;
    int max_frames = 0;  /* 0 = unlimited */

    if (argc > 1) cam_dev = argv[1];
    if (argc > 2 && argv[2][0] != '-') weight_file = argv[2];
    if (argc > 3) max_frames = atoi(argv[3]);

    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);

    printf("========================================\n");
    printf("  LPR Live Demo — Zynq ARM + HDMI\n");
    printf("  Camera: %s  Framebuffer: %s\n", cam_dev, FB_DEV);
    printf("  Ctrl+C to quit%s\n",
           max_frames ? "" : " (or pass frame count as arg 3)");
    printf("========================================\n\n");

    /* Initialize golden model weights */
    GoldenWeights *weights = (GoldenWeights *)malloc(sizeof(GoldenWeights));
    if (!weights) { fprintf(stderr, "malloc failed\n"); return 1; }

    if (weight_file) {
        if (golden_weights_load(weights, weight_file) < 0) {
            printf("[WARN] Failed to load %s, using synthetic\n", weight_file);
            golden_weights_init_synthetic(weights, 42);
        } else {
            printf("[MODEL] Loaded weights from %s\n", weight_file);
        }
    } else {
        golden_weights_init_synthetic(weights, 42);
        printf("[MODEL] Using synthetic weights (seed=42)\n");
    }

    /* Open camera */
    if (cam_open(cam_dev) < 0) return 1;

    /* Open framebuffer */
    if (fb_open() < 0) { cam_close(); return 1; }

    /* Allocate inference buffers and context */
    int32_t *img28 = (int32_t *)calloc(GOLDEN_IN_H * GOLDEN_IN_W, sizeof(int32_t));
    if (!img28) { fprintf(stderr, "alloc failed\n"); return 1; }

    GoldenContext ctx;
    golden_context_init(&ctx, NULL, NULL);

    int frame_count = 0;
    double fps = 0;
    double t_start = time_ms();

    printf("[LIVE] Starting capture loop%s...\n",
           max_frames ? "" : " (Ctrl+C to stop)");

    while (running && (!max_frames || frame_count < max_frames)) {
        /* 1. Capture frame */
        uint8_t *yuyv = cam_capture();
        if (!yuyv) { usleep(1000); continue; }

        /* 2. Convert to grayscale */
        frame_to_gray(yuyv, cam_last_bytesused);

        /* 3. Draw camera feed to framebuffer */
        fb_draw_camera();

        /* 4. Draw ROI box */
        fb_draw_roi_box();

        /* 5. Extract characters from both plate rows */
        char row1[ROW1_CHARS + 1];
        char row2[ROW2_CHARS + 1];
        double t_inf0 = time_ms();

        /* Row 1: top half of ROI (e.g., "66L1") */
        for (int c = 0; c < ROW1_CHARS; c++) {
            extract_char_28x28(img28, 0, c, ROW1_CHARS);
            int predicted = -1;
            golden_infer(img28, weights, &ctx, &predicted, &row1[c]);
        }
        row1[ROW1_CHARS] = '\0';

        /* Row 2: bottom half of ROI (e.g., "40588") */
        for (int c = 0; c < ROW2_CHARS; c++) {
            extract_char_28x28(img28, 1, c, ROW2_CHARS);
            int predicted = -1;
            golden_infer(img28, weights, &ctx, &predicted, &row2[c]);
        }
        row2[ROW2_CHARS] = '\0';

        char plate[MAX_PLATE_CHARS + 2]; /* +2 for dash and null */
        snprintf(plate, sizeof(plate), "%s%s", row1, row2);
        double t_inf1 = time_ms();

        /* 6. FPS counter */
        double t1 = time_ms();
        frame_count++;
        if (frame_count % 10 == 0) {
            fps = 10000.0 / (t1 - t_start);
            t_start = t1;
        }

        /* 7. Draw overlay — all on the right side of camera */
        int info_x = DISP_X + CAM_WIDTH * SCALE + 30;

        /* Title (only draw once) */
        if (frame_count == 1)
            fb_draw_string(info_x, DISP_Y, "LPR DEMO", 3, 255, 255, 255);

        /* Plate row 1 — large green text (8 rows * scale 5 = 40px) */
        int plate_y1 = DISP_Y + 50;
        for (int y = plate_y1; y < plate_y1 + 45; y++)
            for (int x = info_x; x < info_x + 300; x++)
                fb_pixel(x, y, 0, 0, 0);
        fb_draw_string(info_x, plate_y1, row1, 5, 0, 255, 0);

        /* Plate row 2 (8 rows * scale 5 = 40px) */
        int plate_y2 = plate_y1 + 55;
        for (int y = plate_y2; y < plate_y2 + 45; y++)
            for (int x = info_x; x < info_x + 300; x++)
                fb_pixel(x, y, 0, 0, 0);
        fb_draw_string(info_x, plate_y2, row2, 5, 0, 255, 0);

        /* FPS + inference time (8 rows * scale 3 = 24px) */
        int fps_y = plate_y2 + 55;
        for (int y = fps_y; y < fps_y + 30; y++)
            for (int x = info_x; x < info_x + 300; x++)
                fb_pixel(x, y, 0, 0, 0);
        char buf[64];
        int fps_int = (int)fps;
        int inf_int = (int)(t_inf1 - t_inf0);
        snprintf(buf, sizeof(buf), "%dFPS %dMS", fps_int, inf_int);
        fb_draw_string(info_x, fps_y, buf, 3, 255, 255, 0);

        /* Console output every 30 frames */
        if (frame_count % 30 == 0) {
            printf("\r[F%05d] plate='%s' inf=%.1fms fps=%.1f   ",
                   frame_count, plate, t_inf1 - t_inf0, fps);
            fflush(stdout);
        }

    }

    printf("\n\n[DONE] %d frames captured\n", frame_count);

    /* Cleanup */
    free(img28);
    free(weights);
    fb_close();
    cam_close();

    return 0;
}
