#ifndef BATCH_PROCESS_H
#define BATCH_PROCESS_H

#include "alpr_types.h"
#include "config.h"
#include "alpr_pipeline.h"

typedef int (*AlprBatchCallback)(const char* image_path, const AlprPlateResult* result, int error_code, void* user_data);

int alpr_batch_process_folder(
    const char* folder_path,
    const char* pattern,
    AlprRuntime* runtime,
    AlprBatchCallback callback,
    void* user_data
);

#endif
