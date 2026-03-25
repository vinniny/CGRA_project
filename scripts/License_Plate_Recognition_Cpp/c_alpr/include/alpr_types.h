#ifndef ALPR_TYPES_H
#define ALPR_TYPES_H

#include <stddef.h>

#define ALPR_MAX_DETECTIONS 512
#define ALPR_MAX_TEXT 64

typedef struct AlprImageU8 {
    unsigned char* data;
    int width;
    int height;
    int channels;
    int stride;
} AlprImageU8;

typedef struct AlprDetection {
    float x1;
    float y1;
    float x2;
    float y2;
    float score;
    int class_id;
} AlprDetection;

typedef struct AlprDetectionArray {
    AlprDetection items[ALPR_MAX_DETECTIONS];
    int count;
} AlprDetectionArray;

typedef struct AlprCharacterDetection {
    float x1;
    float y1;
    float x2;
    float y2;
    float score;
    char label;
} AlprCharacterDetection;

typedef struct AlprCharacterArray {
    AlprCharacterDetection items[ALPR_MAX_DETECTIONS];
    int count;
} AlprCharacterArray;

typedef enum AlprPlateType {
    ALPR_PLATE_ONE_LINE = 0,
    ALPR_PLATE_TWO_LINE = 1
} AlprPlateType;

typedef struct AlprPlateResult {
    char text[ALPR_MAX_TEXT];
    AlprPlateType type;
    float confidence;
} AlprPlateResult;

#endif
