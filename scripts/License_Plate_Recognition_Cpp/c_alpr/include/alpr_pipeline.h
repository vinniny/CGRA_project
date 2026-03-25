#ifndef ALPR_PIPELINE_H
#define ALPR_PIPELINE_H

#include "alpr_types.h"
#include "config.h"
#include "onnx_engine.h"

typedef struct AlprRuntime {
    AlprConfig cfg;
    AlprOnnxEngine* plate_engine;
    AlprOnnxEngine* char_engine;
    unsigned char* plate_input_u8;
    float* plate_input_f32;
    unsigned char* char_input_u8;
    float* char_input_f32;
} AlprRuntime;

int alpr_runtime_init(AlprRuntime* rt, const AlprConfig* cfg, int use_gpu);
void alpr_runtime_destroy(AlprRuntime* rt);

int alpr_runtime_run_image(
    AlprRuntime* rt,
    const AlprImageU8* image,
    AlprPlateResult* out_best
);

int alpr_runtime_run_image_ex(
    AlprRuntime* rt,
    const AlprImageU8* image,
    AlprPlateResult* out_best,
    AlprDetection* out_best_plate_box
);

#endif
