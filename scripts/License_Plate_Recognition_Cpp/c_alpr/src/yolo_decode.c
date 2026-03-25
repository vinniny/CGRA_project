#include "yolo_decode.h"

#include <string.h>

static float maxf(float a, float b) {
    return (a > b) ? a : b;
}

static float minf(float a, float b) {
    return (a < b) ? a : b;
}

static int append_det(AlprDetectionArray* dets, const AlprDetection* d) {
    if (dets->count >= ALPR_MAX_DETECTIONS) {
        return -1;
    }
    dets->items[dets->count++] = *d;
    return 0;
}

static void xywh_to_xyxy(float cx, float cy, float w, float h, AlprDetection* d) {
    d->x1 = cx - w * 0.5f;
    d->y1 = cy - h * 0.5f;
    d->x2 = cx + w * 0.5f;
    d->y2 = cy + h * 0.5f;
}

static int decode_layout_n_rows(const AlprOnnxOutput* out, int n_rows, int row_size, int num_classes, float conf_threshold, AlprDetectionArray* dets) {
    for (int i = 0; i < n_rows; i++) {
        const float* r = out->data + (size_t)i * (size_t)row_size;
        float cx = r[0];
        float cy = r[1];
        float w = r[2];
        float h = r[3];
        float obj = r[4];

        float best_cls = 0.0f;
        int best_id = -1;
        for (int c = 0; c < num_classes; c++) {
            float score = r[5 + c];
            if (score > best_cls) {
                best_cls = score;
                best_id = c;
            }
        }

        float conf = obj * best_cls;
        if (best_id >= 0 && conf >= conf_threshold) {
            AlprDetection d;
            memset(&d, 0, sizeof(d));
            xywh_to_xyxy(cx, cy, w, h, &d);
            d.x1 = maxf(0.0f, d.x1);
            d.y1 = maxf(0.0f, d.y1);
            d.x2 = maxf(d.x1, d.x2);
            d.y2 = maxf(d.y1, d.y2);
            d.class_id = best_id;
            d.score = conf;
            if (append_det(dets, &d) != 0) {
                break;
            }
        }
    }
    return 0;
}

static int decode_layout_channels_first(const AlprOnnxOutput* out, int n_anchors, int channels, int num_classes, float conf_threshold, AlprDetectionArray* dets) {
    const float* p = out->data;
    for (int i = 0; i < n_anchors; i++) {
        float cx = p[(size_t)0 * (size_t)n_anchors + (size_t)i];
        float cy = p[(size_t)1 * (size_t)n_anchors + (size_t)i];
        float w = p[(size_t)2 * (size_t)n_anchors + (size_t)i];
        float h = p[(size_t)3 * (size_t)n_anchors + (size_t)i];

        int cls_offset = 4;
        float obj = 1.0f;
        if (channels == num_classes + 5) {
            obj = p[(size_t)4 * (size_t)n_anchors + (size_t)i];
            cls_offset = 5;
        }

        float best_cls = 0.0f;
        int best_id = -1;
        for (int c = 0; c < num_classes; c++) {
            float s = p[(size_t)(cls_offset + c) * (size_t)n_anchors + (size_t)i];
            if (s > best_cls) {
                best_cls = s;
                best_id = c;
            }
        }

        float conf = obj * best_cls;
        if (best_id >= 0 && conf >= conf_threshold) {
            AlprDetection d;
            memset(&d, 0, sizeof(d));
            xywh_to_xyxy(cx, cy, w, h, &d);
            d.x1 = maxf(0.0f, d.x1);
            d.y1 = maxf(0.0f, d.y1);
            d.x2 = maxf(d.x1, d.x2);
            d.y2 = maxf(d.y1, d.y2);
            d.class_id = best_id;
            d.score = conf;
            if (append_det(dets, &d) != 0) {
                break;
            }
        }
    }
    return 0;
}

int alpr_decode_yolo_tensor(
    const AlprOnnxOutput* out,
    int num_classes,
    float conf_threshold,
    AlprDetectionArray* dets
) {
    if (!out || !out->data || !dets || num_classes <= 0) {
        return -1;
    }

    dets->count = 0;

    if (out->rank == 3) {
        int d1 = (int)out->shape[1];
        int d2 = (int)out->shape[2];

        if (d2 == num_classes + 5) {
            return decode_layout_n_rows(out, d1, d2, num_classes, conf_threshold, dets);
        }

        if (d1 == num_classes + 5 || d1 == num_classes + 4) {
            return decode_layout_channels_first(out, d2, d1, num_classes, conf_threshold, dets);
        }
    }

    if (out->rank == 2) {
        int rows = (int)out->shape[0];
        int cols = (int)out->shape[1];
        if (cols == num_classes + 5) {
            return decode_layout_n_rows(out, rows, cols, num_classes, conf_threshold, dets);
        }
    }

    return -2;
}
