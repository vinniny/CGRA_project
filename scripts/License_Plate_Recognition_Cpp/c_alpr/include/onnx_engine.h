#ifndef ONNX_ENGINE_H
#define ONNX_ENGINE_H

#include "alpr_types.h"

#include <stddef.h>

#define ALPR_MAX_TENSOR_DIMS 8

typedef struct AlprOnnxOutput {
    float* data;
    size_t data_len;
    size_t rank;
    long long shape[ALPR_MAX_TENSOR_DIMS];
} AlprOnnxOutput;

typedef struct AlprOnnxEngine AlprOnnxEngine;

AlprOnnxEngine* alpr_onnx_create(const char* model_path, int use_gpu);
void alpr_onnx_destroy(AlprOnnxEngine* engine);

int alpr_onnx_run(
    AlprOnnxEngine* engine,
    const float* input_chw,
    int input_w,
    int input_h,
    int input_c,
    AlprOnnxOutput* out
);

void alpr_onnx_output_free(AlprOnnxOutput* out);

#endif
