#ifndef NMS_H
#define NMS_H

#include "alpr_types.h"

float alpr_iou(const AlprDetection* a, const AlprDetection* b);
void alpr_nms(AlprDetectionArray* dets, float iou_threshold);

#endif
