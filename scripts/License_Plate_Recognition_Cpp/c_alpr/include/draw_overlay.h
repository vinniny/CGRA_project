#ifndef DRAW_OVERLAY_H
#define DRAW_OVERLAY_H

#include "alpr_types.h"

int alpr_draw_plate_box(
    AlprImageU8* frame,
    const AlprDetection* box,
    const char* text
);

int alpr_draw_fps(AlprImageU8* frame, float fps);

#endif
