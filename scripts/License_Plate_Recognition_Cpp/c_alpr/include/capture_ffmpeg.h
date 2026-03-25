#ifndef CAPTURE_FFMPEG_H
#define CAPTURE_FFMPEG_H

#include "alpr_types.h"

typedef struct AlprCapture AlprCapture;

AlprCapture* alpr_capture_open_camera(int camera_index, int width, int height, int fps);
AlprCapture* alpr_capture_open_video(const char* video_path, int width, int height);
void alpr_capture_close(AlprCapture* cap);
int alpr_capture_read(AlprCapture* cap, AlprImageU8* out_frame);
void alpr_capture_release_frame(AlprImageU8* frame);

#endif
