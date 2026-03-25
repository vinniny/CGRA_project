#include "nms.h"

#include <string.h>

static void swap_det(AlprDetection* a, AlprDetection* b) {
    AlprDetection t = *a;
    *a = *b;
    *b = t;
}

static void sort_by_score_desc(AlprDetectionArray* dets) {
    for (int i = 0; i < dets->count - 1; i++) {
        int best = i;
        for (int j = i + 1; j < dets->count; j++) {
            if (dets->items[j].score > dets->items[best].score) {
                best = j;
            }
        }
        if (best != i) {
            swap_det(&dets->items[i], &dets->items[best]);
        }
    }
}

float alpr_iou(const AlprDetection* a, const AlprDetection* b) {
    float xx1 = (a->x1 > b->x1) ? a->x1 : b->x1;
    float yy1 = (a->y1 > b->y1) ? a->y1 : b->y1;
    float xx2 = (a->x2 < b->x2) ? a->x2 : b->x2;
    float yy2 = (a->y2 < b->y2) ? a->y2 : b->y2;

    float w = xx2 - xx1;
    float h = yy2 - yy1;
    if (w <= 0.0f || h <= 0.0f) {
        return 0.0f;
    }

    float inter = w * h;
    float area_a = (a->x2 - a->x1) * (a->y2 - a->y1);
    float area_b = (b->x2 - b->x1) * (b->y2 - b->y1);
    float uni = area_a + area_b - inter;
    if (uni <= 0.0f) {
        return 0.0f;
    }

    return inter / uni;
}

void alpr_nms(AlprDetectionArray* dets, float iou_threshold) {
    if (!dets || dets->count <= 1) {
        return;
    }

    sort_by_score_desc(dets);

    unsigned char removed[ALPR_MAX_DETECTIONS];
    memset(removed, 0, sizeof(removed));

    AlprDetection keep[ALPR_MAX_DETECTIONS];
    int keep_count = 0;

    for (int i = 0; i < dets->count; i++) {
        if (removed[i]) {
            continue;
        }

        keep[keep_count++] = dets->items[i];
        for (int j = i + 1; j < dets->count; j++) {
            if (removed[j]) {
                continue;
            }
            if (dets->items[i].class_id != dets->items[j].class_id) {
                continue;
            }
            if (alpr_iou(&dets->items[i], &dets->items[j]) > iou_threshold) {
                removed[j] = 1;
            }
        }
    }

    dets->count = keep_count;
    for (int i = 0; i < keep_count; i++) {
        dets->items[i] = keep[i];
    }
}
