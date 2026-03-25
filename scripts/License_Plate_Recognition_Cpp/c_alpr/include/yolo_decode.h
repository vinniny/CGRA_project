#ifndef YOLO_DECODE_H
#define YOLO_DECODE_H

#include "alpr_types.h"
#include "onnx_engine.h"

int alpr_decode_yolo_tensor(
    const AlprOnnxOutput* out,
    int num_classes,
    float conf_threshold,
    AlprDetectionArray* dets
);

#endif
