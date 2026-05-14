/* =============================================================================
 * lpr_live_demo_v2.c — Live LPR demo for Haoyue (Linux user-space)
 *
 * Pipeline:
 *   /dev/video0 (V4L2 — OV5640 PL camera or USB UVC if uvcvideo loaded)
 *     → ARM frame grab (YUYV → grayscale)
 *     → ARM plate-region detection (simple edge density + connected components)
 *     → ARM character segmentation (vertical projection)
 *     → CGRA inference per character (Conv1+Pool+Conv2+Pool+FC via /dev/uio0)
 *     → ARM render predictions onto frame
 *     → /dev/fb0 blit (HDMI)
 *
 * Build:    make -C 07_sw/linux demo
 * Deploy:   scp build/lpr_live_demo_v2 haoyue:/home/root/cgra/
 * Run:      /home/root/cgra/lpr_live_demo_v2 [-d /dev/video0] [-o /dev/fb0]
 *
 * Status: skeleton — V4L2 capture + framebuffer render are stubbed; the
 * algorithm hooks (detect_plate, segment_chars, cgra_infer_char) are TODOs
 * filled in during Phase L2 once the corrected algorithm is bit-exact in Python.
 * =============================================================================
 */
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <linux/videodev2.h>
#include <linux/fb.h>

#include "cgra_driver.h"

/* ── Frame buffer ────────────────────────────────────────────────────── */
typedef struct {
    int fd;
    uint8_t *map;
    size_t size;
    int w, h, bpp, stride;
} fb_t;

static int fb_open(fb_t *fb, const char *path)
{
    fb->fd = open(path, O_RDWR);
    if (fb->fd < 0) { perror("fb open"); return -1; }
    struct fb_var_screeninfo v;
    struct fb_fix_screeninfo f;
    if (ioctl(fb->fd, FBIOGET_VSCREENINFO, &v) < 0) { perror("FBIOGET_VSCREENINFO"); return -1; }
    if (ioctl(fb->fd, FBIOGET_FSCREENINFO, &f) < 0) { perror("FBIOGET_FSCREENINFO"); return -1; }
    fb->w      = v.xres;
    fb->h      = v.yres;
    fb->bpp    = v.bits_per_pixel;
    fb->stride = f.line_length;
    fb->size   = f.smem_len;
    fb->map = mmap(NULL, fb->size, PROT_READ | PROT_WRITE, MAP_SHARED, fb->fd, 0);
    if (fb->map == MAP_FAILED) { perror("fb mmap"); return -1; }
    fprintf(stderr, "[fb ] %dx%d %dbpp stride=%d size=%zu @%p\n",
            fb->w, fb->h, fb->bpp, fb->stride, fb->size, (void *)fb->map);
    return 0;
}

static void fb_close(fb_t *fb)
{
    if (fb->map && fb->map != MAP_FAILED) munmap(fb->map, fb->size);
    if (fb->fd >= 0) close(fb->fd);
}

/* Center-blit BGR888 frame into framebuffer (with letterbox).
 * src: BGR888 packed (3 bytes per pixel). */
static void fb_blit_bgr(fb_t *fb, const uint8_t *src, int sw, int sh)
{
    if (fb->bpp != 24 && fb->bpp != 32) return;
    int dst_x = (fb->w - sw) / 2; if (dst_x < 0) dst_x = 0;
    int dst_y = (fb->h - sh) / 2; if (dst_y < 0) dst_y = 0;
    int copy_w = sw < fb->w ? sw : fb->w;
    int copy_h = sh < fb->h ? sh : fb->h;
    int dst_bpp_bytes = fb->bpp / 8;

    for (int y = 0; y < copy_h; y++) {
        const uint8_t *s = src + y * sw * 3;
        uint8_t *d = fb->map + (dst_y + y) * fb->stride + dst_x * dst_bpp_bytes;
        if (fb->bpp == 24) {
            memcpy(d, s, copy_w * 3);
        } else { /* 32 bpp BGRA */
            for (int x = 0; x < copy_w; x++) {
                d[x*4 + 0] = s[x*3 + 0];
                d[x*4 + 1] = s[x*3 + 1];
                d[x*4 + 2] = s[x*3 + 2];
                d[x*4 + 3] = 0;
            }
        }
    }
}

/* ── V4L2 capture (basic, single-buffer) ────────────────────────────── */
typedef struct {
    int fd;
    void *buf;
    size_t buf_len;
    int w, h;
    uint32_t fourcc;
} cam_t;

static int cam_open(cam_t *c, const char *path, int w, int h)
{
    c->fd = open(path, O_RDWR | O_NONBLOCK);
    if (c->fd < 0) { perror("cam open"); return -1; }
    struct v4l2_format fmt = {0};
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    fmt.fmt.pix_mp.width = w;
    fmt.fmt.pix_mp.height = h;
    fmt.fmt.pix_mp.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix_mp.field = V4L2_FIELD_NONE;
    fmt.fmt.pix_mp.num_planes = 1;
    if (ioctl(c->fd, VIDIOC_S_FMT, &fmt) < 0) { perror("VIDIOC_S_FMT"); return -1; }
    c->w = fmt.fmt.pix_mp.width;
    c->h = fmt.fmt.pix_mp.height;
    c->fourcc = fmt.fmt.pix_mp.pixelformat;

    struct v4l2_requestbuffers req = {0};
    req.count = 1; req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE; req.memory = V4L2_MEMORY_MMAP;
    if (ioctl(c->fd, VIDIOC_REQBUFS, &req) < 0) { perror("VIDIOC_REQBUFS"); return -1; }
    struct v4l2_plane planes[1] = {{0}};
    struct v4l2_buffer bb = {0};
    bb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE; bb.memory = V4L2_MEMORY_MMAP;
    bb.index = 0; bb.m.planes = planes; bb.length = 1;
    if (ioctl(c->fd, VIDIOC_QUERYBUF, &bb) < 0) { perror("VIDIOC_QUERYBUF"); return -1; }
    c->buf_len = planes[0].length;
    c->buf = mmap(NULL, planes[0].length, PROT_READ | PROT_WRITE, MAP_SHARED, c->fd, planes[0].m.mem_offset);
    if (c->buf == MAP_FAILED) { perror("cam mmap"); return -1; }
    if (ioctl(c->fd, VIDIOC_QBUF, &bb) < 0) { perror("VIDIOC_QBUF"); return -1; }
    int t = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    if (ioctl(c->fd, VIDIOC_STREAMON, &t) < 0) { perror("VIDIOC_STREAMON"); return -1; }
    fprintf(stderr, "[cam] %s %dx%d fourcc=0x%08X\n", path, c->w, c->h, c->fourcc);
    return 0;
}

static int cam_grab(cam_t *c, void *out_buf, size_t out_len)
{
    struct v4l2_plane planes[1] = {{0}};
    struct v4l2_buffer bb = {0};
    bb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE; bb.memory = V4L2_MEMORY_MMAP;
    bb.m.planes = planes; bb.length = 1;
    /* Block-wait via poll-equivalent: small spin */
    for (int tries = 0; tries < 100; tries++) {
        if (ioctl(c->fd, VIDIOC_DQBUF, &bb) == 0) {
            size_t n = planes[0].bytesused < out_len ? planes[0].bytesused : out_len;
            memcpy(out_buf, c->buf, n);
            ioctl(c->fd, VIDIOC_QBUF, &bb);
            return (int)n;
        }
        if (errno != EAGAIN) { perror("VIDIOC_DQBUF"); return -1; }
        usleep(10000);
    }
    return -1;
}

static void cam_close(cam_t *c)
{
    int t = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    ioctl(c->fd, VIDIOC_STREAMOFF, &t);
    if (c->buf && c->buf != MAP_FAILED) munmap(c->buf, c->buf_len);
    if (c->fd >= 0) close(c->fd);
}

/* ── YUYV → BGR888 (full 8-bit, no chroma upsample optimization) ──── */
static void yuyv_to_bgr(const uint8_t *yuyv, uint8_t *bgr, int w, int h)
{
    for (int i = 0, j = 0; i < w*h*2; i += 4, j += 6) {
        int y0 = yuyv[i], u = yuyv[i+1] - 128, y1 = yuyv[i+2], v = yuyv[i+3] - 128;
        for (int k = 0; k < 2; k++) {
            int y = (k == 0) ? y0 : y1;
            int r = y + ((359 * v) >> 8);
            int g = y - ((88 * u + 183 * v) >> 8);
            int b = y + ((454 * u) >> 8);
            r = r < 0 ? 0 : (r > 255 ? 255 : r);
            g = g < 0 ? 0 : (g > 255 ? 255 : g);
            b = b < 0 ? 0 : (b > 255 ? 255 : b);
            bgr[j + k*3 + 0] = (uint8_t)b;
            bgr[j + k*3 + 1] = (uint8_t)g;
            bgr[j + k*3 + 2] = (uint8_t)r;
        }
    }
}

/* ── TODO (Phase L2.2): plate detect + char segmentation + CGRA inference ── */
static int detect_plate(const uint8_t *gray, int w, int h,
                        int *out_x, int *out_y, int *out_w, int *out_h)
{
    /* TODO: implement edge density + horizontal projection. For now: full frame. */
    (void)gray;
    *out_x = 0; *out_y = 0; *out_w = w; *out_h = h;
    return 1;
}

static int infer_chars(cgra_dev_t *dev, const uint8_t *plate_gray,
                       int pw, int ph, char *out_text, int max_chars)
{
    /* TODO: segment into 9 28×28 chars, run CGRA Conv1+Pool+Conv2+Pool+FC,
     * argmax → chars[]. Phase L2.2 work. */
    (void)dev; (void)plate_gray; (void)pw; (void)ph; (void)max_chars;
    strcpy(out_text, "?\?-?\?\?-?\?");
    return 9;
}

/* ── Main loop ──────────────────────────────────────────────────────── */
int main(int argc, char **argv)
{
    const char *cam_path = "/dev/video0";
    const char *fb_path  = "/dev/fb0";
    int w = 640, h = 480;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-d") && i+1 < argc) cam_path = argv[++i];
        else if (!strcmp(argv[i], "-o") && i+1 < argc) fb_path = argv[++i];
        else if (!strcmp(argv[i], "-w") && i+1 < argc) w = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-h") && i+1 < argc) h = atoi(argv[++i]);
    }

    cgra_dev_t dev = {0};
    if (cgra_init(&dev, NULL) < 0) {
        fprintf(stderr, "WARN: cgra_init failed (running ARM-only): %s\n",
                strerror(errno));
    }

    fb_t fb = {0};
    if (fb_open(&fb, fb_path) < 0) return 1;

    cam_t cam = {0};
    if (cam_open(&cam, cam_path, w, h) < 0) { fb_close(&fb); return 1; }

    /* Buffers */
    uint8_t *yuyv = malloc(cam.w * cam.h * 2);
    uint8_t *bgr  = malloc(cam.w * cam.h * 3);
    uint8_t *gray = malloc(cam.w * cam.h);
    if (!yuyv || !bgr || !gray) { fprintf(stderr, "malloc\n"); return 1; }

    int n_frames = 0;
    struct timeval t0, t1;
    gettimeofday(&t0, NULL);
    while (1) {
        int got = cam_grab(&cam, yuyv, cam.w * cam.h * 2);
        if (got < 0) { fprintf(stderr, "grab fail\n"); break; }

        /* YUYV → BGR for display, plus extract Y for inference */
        yuyv_to_bgr(yuyv, bgr, cam.w, cam.h);
        for (int i = 0; i < cam.w * cam.h; i++) gray[i] = yuyv[i*2];

        int px, py, pw_, ph_;
        if (detect_plate(gray, cam.w, cam.h, &px, &py, &pw_, &ph_)) {
            char text[32];
            infer_chars(&dev, gray + py*cam.w + px, pw_, ph_, text, sizeof(text));
            /* Draw a simple red box around the plate region in BGR buffer */
            for (int x = px; x < px + pw_; x++) {
                if (px >= 0 && px < cam.w && py >= 0 && py < cam.h) {
                    bgr[(py*cam.w + x)*3 + 2] = 255;
                    bgr[((py + ph_ - 1)*cam.w + x)*3 + 2] = 255;
                }
            }
            /* TODO: render `text` overlay */
        }

        fb_blit_bgr(&fb, bgr, cam.w, cam.h);

        n_frames++;
        if (n_frames % 30 == 0) {
            gettimeofday(&t1, NULL);
            double dt = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
            fprintf(stderr, "  frame %d  ~%.1f fps\n", n_frames, n_frames / dt);
        }
    }

    free(yuyv); free(bgr); free(gray);
    cam_close(&cam);
    fb_close(&fb);
    cgra_close(&dev);
    return 0;
}
