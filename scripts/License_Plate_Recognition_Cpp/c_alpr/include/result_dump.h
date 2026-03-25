#ifndef RESULT_DUMP_H
#define RESULT_DUMP_H

#include "alpr_types.h"

typedef struct AlprFullResult {
    const char* image_path;
    AlprPlateResult plate;
    int error_code;
} AlprFullResult;

int alpr_dump_result_json(const char* output_path, const AlprFullResult* result);
int alpr_dump_result_txt(const char* output_path, const AlprFullResult* result);

#endif
