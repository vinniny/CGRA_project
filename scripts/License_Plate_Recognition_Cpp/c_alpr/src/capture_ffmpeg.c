#include "capture_ffmpeg.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define ALPR_POPEN _popen
#define ALPR_PCLOSE _pclose
#else
#define ALPR_POPEN popen
#define ALPR_PCLOSE pclose
#endif

struct AlprCapture {
    int camera_index;
    int width;
    int height;
    int fps;
    FILE* pipe;
    unsigned char* frame_buf;
    size_t frame_bytes;
    int has_prefetched;
};

static int contains_text_ci(const char* hay, const char* needle) {
    if (!hay || !needle || !*needle) {
        return 0;
    }
    size_t nlen = strlen(needle);
    for (const char* p = hay; *p; p++) {
        size_t i = 0;
        while (i < nlen) {
            unsigned char a = (unsigned char)p[i];
            unsigned char b = (unsigned char)needle[i];
            if (!a) {
                return 0;
            }
            if ((unsigned char)tolower(a) != (unsigned char)tolower(b)) {
                break;
            }
            i++;
        }
        if (i == nlen) {
            return 1;
        }
    }
    return 0;
}

#ifdef _WIN32
static int parse_quoted_token(const char* s, char* out, size_t out_sz) {
    if (!s || !out || out_sz < 2) {
        return -1;
    }
    const char* q1 = strchr(s, '"');
    if (!q1) {
        return -1;
    }
    const char* q2 = strchr(q1 + 1, '"');
    if (!q2 || q2 <= q1 + 1) {
        return -1;
    }
    size_t n = (size_t)(q2 - (q1 + 1));
    if (n >= out_sz) {
        n = out_sz - 1;
    }
    memcpy(out, q1 + 1, n);
    out[n] = '\0';
    return 0;
}

static int alpr_list_dshow_video_devices(char names[][256], int max_names) {
    if (!names || max_names <= 0) {
        return 0;
    }

    FILE* fp = ALPR_POPEN("ffmpeg -hide_banner -list_devices true -f dshow -i dummy 2>&1", "r");
    if (!fp) {
        return 0;
    }

    char line[1024];
    int in_video_section = 0;
    int count = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (contains_text_ci(line, "DirectShow video devices")) {
            in_video_section = 1;
            continue;
        }
        if (contains_text_ci(line, "DirectShow audio devices")) {
            break;
        }
        if (!in_video_section) {
            continue;
        }
        if (contains_text_ci(line, "Alternative name")) {
            continue;
        }
        if (strchr(line, '"') == NULL) {
            continue;
        }

        if (count < max_names) {
            if (parse_quoted_token(line, names[count], 256) == 0 && names[count][0] != '\0') {
                count++;
            }
        }
    }

    ALPR_PCLOSE(fp);
    return count;
}
#endif

static FILE* alpr_open_capture_pipe(int camera_index, int width, int height, int fps) {
    char cmd[1024];

#ifdef _WIN32
    char dshow_names[16][256];
    int name_count = alpr_list_dshow_video_devices(dshow_names, 16);
    if (name_count > 0) {
        int idx = camera_index;
        if (idx < 0 || idx >= name_count) {
            idx = 0;
        }
        snprintf(
            cmd,
            sizeof(cmd),
            "ffmpeg -hide_banner -loglevel quiet -fflags nobuffer -flags low_delay -f dshow -rtbufsize 32M -video_size %dx%d -framerate %d -i video=\"%s\" -an -vf fps=%d,scale=%d:%d -pix_fmt rgb24 -f rawvideo -",
            width,
            height,
            fps,
            dshow_names[idx],
            fps,
            width,
            height
        );
        FILE* fp = ALPR_POPEN(cmd, "rb");
        if (fp) {
            return fp;
        }
    }

    /* Fallback to vfwcap for older setups. */
    snprintf(
        cmd,
        sizeof(cmd),
        "ffmpeg -hide_banner -loglevel quiet -fflags nobuffer -flags low_delay -framerate %d -f vfwcap -i %d -an -vf fps=%d,scale=%d:%d -pix_fmt rgb24 -f rawvideo -",
        fps,
        camera_index,
        fps,
        width,
        height
    );
    return ALPR_POPEN(cmd, "rb");
#else
    snprintf(
        cmd,
        sizeof(cmd),
        "ffmpeg -hide_banner -loglevel error -fflags nobuffer -flags low_delay -f video4linux2 -framerate %d -video_size %dx%d -i /dev/video%d -an -pix_fmt rgb24 -f rawvideo -",
        fps,
        width,
        height,
        camera_index
    );
    return ALPR_POPEN(cmd, "rb");
#endif
}

static FILE* alpr_open_video_pipe(const char* video_path, int width, int height) {
    char cmd[2048];
    snprintf(
        cmd,
        sizeof(cmd),
        "ffmpeg -hide_banner -loglevel error -i \"%s\" -an -vf scale=%d:%d -pix_fmt rgb24 -f rawvideo -",
        video_path,
        width,
        height
    );
    return ALPR_POPEN(cmd, "rb");
}

AlprCapture* alpr_capture_open_video(const char* video_path, int width, int height) {
    if (!video_path) {
        return NULL;
    }

    if (width <= 0) {
        width = 640;
    }
    if (height <= 0) {
        height = 360;
    }

    AlprCapture* cap = (AlprCapture*)calloc(1, sizeof(AlprCapture));
    if (!cap) {
        return NULL;
    }

    cap->camera_index = -1;
    cap->width = width;
    cap->height = height;
    cap->fps = 0;
    cap->frame_bytes = (size_t)width * (size_t)height * 3u;

    cap->frame_buf = (unsigned char*)malloc(cap->frame_bytes);
    if (!cap->frame_buf) {
        free(cap);
        return NULL;
    }

    cap->pipe = alpr_open_video_pipe(video_path, width, height);
    if (!cap->pipe) {
        free(cap->frame_buf);
        free(cap);
        return NULL;
    }

    /* Validate pipeline by reading one frame immediately. */
    size_t got = fread(cap->frame_buf, 1, cap->frame_bytes, cap->pipe);
    if (got != cap->frame_bytes) {
        ALPR_PCLOSE(cap->pipe);
        free(cap->frame_buf);
        free(cap);
        return NULL;
    }
    cap->has_prefetched = 1;

    return cap;
}

AlprCapture* alpr_capture_open_camera(int camera_index, int width, int height, int fps) {
    AlprCapture* cap = (AlprCapture*)calloc(1, sizeof(AlprCapture));
    if (!cap) {
        return NULL;
    }

    if (width <= 0) {
        width = 1280;
    }
    if (height <= 0) {
        height = 720;
    }
    if (fps <= 0) {
        fps = 30;
    }

    cap->camera_index = camera_index;
    cap->width = width;
    cap->height = height;
    cap->fps = fps;
    cap->frame_bytes = (size_t)width * (size_t)height * 3u;

    cap->frame_buf = (unsigned char*)malloc(cap->frame_bytes);
    if (!cap->frame_buf) {
        free(cap);
        return NULL;
    }

    cap->pipe = alpr_open_capture_pipe(camera_index, width, height, fps);
    if (!cap->pipe) {
        free(cap->frame_buf);
        free(cap);
        return NULL;
    }

    /* Validate pipeline by reading one frame immediately. */
    size_t got = fread(cap->frame_buf, 1, cap->frame_bytes, cap->pipe);
    if (got != cap->frame_bytes) {
        ALPR_PCLOSE(cap->pipe);
        free(cap->frame_buf);
        free(cap);
        return NULL;
    }
    cap->has_prefetched = 1;

    return cap;
}

void alpr_capture_close(AlprCapture* cap) {
    if (!cap) {
        return;
    }

    if (cap->pipe) {
        ALPR_PCLOSE(cap->pipe);
        cap->pipe = NULL;
    }

    if (cap->frame_buf) {
        free(cap->frame_buf);
        cap->frame_buf = NULL;
    }

    free(cap);
}

int alpr_capture_read(AlprCapture* cap, AlprImageU8* out_frame) {
    if (!cap || !out_frame || !cap->pipe || !cap->frame_buf) {
        return -1;
    }

    if (cap->has_prefetched) {
        cap->has_prefetched = 0;
    } else {
        size_t got = fread(cap->frame_buf, 1, cap->frame_bytes, cap->pipe);
        if (got != cap->frame_bytes) {
            return -2;
        }
    }

    out_frame->data = cap->frame_buf;
    out_frame->width = cap->width;
    out_frame->height = cap->height;
    out_frame->channels = 3;
    out_frame->stride = cap->width * 3;
    return 0;
}

void alpr_capture_release_frame(AlprImageU8* frame) {
    if (!frame) {
        return;
    }

    frame->data = NULL;
    frame->width = 0;
    frame->height = 0;
    frame->channels = 0;
    frame->stride = 0;
}
