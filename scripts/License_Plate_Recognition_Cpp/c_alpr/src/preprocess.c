#include "preprocess.h"

#include <string.h>

static int clamp_int(int v, int lo, int hi) {
    if (v < lo) {
        return lo;
    }
    if (v > hi) {
        return hi;
    }
    return v;
}

int alpr_letterbox_u8(
    const AlprImageU8* src,
    unsigned char* dst,
    int dst_w,
    int dst_h,
    unsigned char pad_value,
    AlprLetterboxMeta* meta
) {
    if (!src || !src->data || !dst || src->channels != 3 || dst_w <= 0 || dst_h <= 0) {
        return -1;
    }

    int i;
    int total = dst_w * dst_h * 3;
    for (i = 0; i < total; i++) {
        dst[i] = pad_value;
    }

    float scale_w = (float)dst_w / (float)src->width;
    float scale_h = (float)dst_h / (float)src->height;
    float scale = (scale_w < scale_h) ? scale_w : scale_h;

    int resized_w = (int)(src->width * scale + 0.5f);
    int resized_h = (int)(src->height * scale + 0.5f);
    int pad_x = (dst_w - resized_w) / 2;
    int pad_y = (dst_h - resized_h) / 2;

    for (int y = 0; y < resized_h; y++) {
        float sy = ((float)y + 0.5f) / scale - 0.5f;
        int syi = clamp_int((int)(sy + 0.5f), 0, src->height - 1);
        for (int x = 0; x < resized_w; x++) {
            float sx = ((float)x + 0.5f) / scale - 0.5f;
            int sxi = clamp_int((int)(sx + 0.5f), 0, src->width - 1);

            int src_idx = syi * src->stride + sxi * 3;
            int dst_idx = ((y + pad_y) * dst_w + (x + pad_x)) * 3;

            dst[dst_idx + 0] = src->data[src_idx + 0];
            dst[dst_idx + 1] = src->data[src_idx + 1];
            dst[dst_idx + 2] = src->data[src_idx + 2];
        }
    }

    if (meta) {
        meta->scale = scale;
        meta->pad_x = pad_x;
        meta->pad_y = pad_y;
        meta->out_w = dst_w;
        meta->out_h = dst_h;
    }

    return 0;
}

int alpr_normalize_chw_f32(
    const unsigned char* src_hwc_u8,
    int w,
    int h,
    int c,
    float* dst_chw
) {
    if (!src_hwc_u8 || !dst_chw || c != 3 || w <= 0 || h <= 0) {
        return -1;
    }

    int area = w * h;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int hwc = (y * w + x) * 3;
            int idx = y * w + x;
            dst_chw[idx + area * 0] = (float)src_hwc_u8[hwc + 0] / 255.0f;
            dst_chw[idx + area * 1] = (float)src_hwc_u8[hwc + 1] / 255.0f;
            dst_chw[idx + area * 2] = (float)src_hwc_u8[hwc + 2] / 255.0f;
        }
    }

    return 0;
}

void alpr_map_box_from_letterbox(
    float* x1,
    float* y1,
    float* x2,
    float* y2,
    const AlprLetterboxMeta* meta,
    int src_w,
    int src_h
) {
    if (!x1 || !y1 || !x2 || !y2 || !meta || meta->scale <= 0.0f) {
        return;
    }

    *x1 = (*x1 - (float)meta->pad_x) / meta->scale;
    *y1 = (*y1 - (float)meta->pad_y) / meta->scale;
    *x2 = (*x2 - (float)meta->pad_x) / meta->scale;
    *y2 = (*y2 - (float)meta->pad_y) / meta->scale;

    if (*x1 < 0.0f) {
        *x1 = 0.0f;
    }
    if (*y1 < 0.0f) {
        *y1 = 0.0f;
    }
    if (*x2 > (float)src_w) {
        *x2 = (float)src_w;
    }
    if (*y2 > (float)src_h) {
        *y2 = (float)src_h;
    }
}
