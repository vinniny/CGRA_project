#ifndef PREPROCESS_H
#define PREPROCESS_H

#include "alpr_types.h"

typedef struct AlprLetterboxMeta {
    float scale;
    int pad_x;
    int pad_y;
    int out_w;
    int out_h;
} AlprLetterboxMeta;

int alpr_letterbox_u8(
    const AlprImageU8* src,
    unsigned char* dst,
    int dst_w,
    int dst_h,
    unsigned char pad_value,
    AlprLetterboxMeta* meta
);

int alpr_normalize_chw_f32(
    const unsigned char* src_hwc_u8,
    int w,
    int h,
    int c,
    float* dst_chw
);

void alpr_map_box_from_letterbox(
    float* x1,
    float* y1,
    float* x2,
    float* y2,
    const AlprLetterboxMeta* meta,
    int src_w,
    int src_h
);

#endif
