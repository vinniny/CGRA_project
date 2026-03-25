#include "display_ffplay.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define ALPR_POPEN _popen
#define ALPR_PCLOSE _pclose
#else
#define ALPR_POPEN popen
#define ALPR_PCLOSE pclose
#endif

struct AlprDisplay {
    int width;
    int height;
    int fps;
    FILE* pipe;
    size_t frame_bytes;
};

AlprDisplay* alpr_display_open_ffplay(int width, int height, int fps) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }
    if (fps <= 0) {
        fps = 30;
    }

    AlprDisplay* disp = (AlprDisplay*)calloc(1, sizeof(AlprDisplay));
    if (!disp) {
        return NULL;
    }

    disp->width = width;
    disp->height = height;
    disp->fps = fps;
    disp->frame_bytes = (size_t)width * (size_t)height * 3u;

    char cmd[1024];
    snprintf(
        cmd,
        sizeof(cmd),
        "ffplay -hide_banner -loglevel error -fflags nobuffer -flags low_delay -framedrop -sync ext -f rawvideo -pixel_format rgb24 -video_size %dx%d -framerate %d -i -",
        width,
        height,
        fps
    );

    disp->pipe = ALPR_POPEN(cmd, "wb");
    if (!disp->pipe) {
        free(disp);
        return NULL;
    }

    return disp;
}

void alpr_display_close(AlprDisplay* disp) {
    if (!disp) {
        return;
    }
    if (disp->pipe) {
        ALPR_PCLOSE(disp->pipe);
        disp->pipe = NULL;
    }
    free(disp);
}

int alpr_display_show_frame(AlprDisplay* disp, const AlprImageU8* frame) {
    if (!disp || !frame || !frame->data) {
        return -1;
    }
    if (frame->width != disp->width || frame->height != disp->height || frame->channels != 3) {
        return -2;
    }
    if (!disp->pipe) {
        return -3;
    }

    size_t n = fwrite(frame->data, 1, disp->frame_bytes, disp->pipe);
    if (n != disp->frame_bytes) {
        return -4;
    }
    fflush(disp->pipe);
    return 0;
}
