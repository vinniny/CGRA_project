#include "result_dump.h"

#include <stdio.h>
#include <string.h>

int alpr_dump_result_json(const char* output_path, const AlprFullResult* result) {
    if (!output_path || !result) {
        return -1;
    }

    FILE* f = fopen(output_path, "w");
    if (!f) {
        return -2;
    }

    fprintf(f, "{\n");
    fprintf(f, "  \"image_path\": \"%s\",\n", result->image_path ? result->image_path : "");
    fprintf(f, "  \"error_code\": %d,\n", result->error_code);
    fprintf(f, "  \"plate_text\": \"%s\",\n", result->plate.text);
    fprintf(f, "  \"plate_confidence\": %.6f,\n", result->plate.confidence);
    fprintf(f, "  \"plate_type\": %d\n", (int)result->plate.type);
    fprintf(f, "}\n");

    fclose(f);
    return 0;
}

int alpr_dump_result_txt(const char* output_path, const AlprFullResult* result) {
    if (!output_path || !result) {
        return -1;
    }

    FILE* f = fopen(output_path, "w");
    if (!f) {
        return -2;
    }

    fprintf(f, "Image: %s\n", result->image_path ? result->image_path : "unknown");
    fprintf(f, "Error Code: %d\n", result->error_code);
    fprintf(f, "Plate Text: %s\n", result->plate.text);
    fprintf(f, "Confidence: %.6f\n", result->plate.confidence);
    fprintf(f, "Type: %d (0=one-line, 1=two-line)\n", (int)result->plate.type);

    fclose(f);
    return 0;
}
