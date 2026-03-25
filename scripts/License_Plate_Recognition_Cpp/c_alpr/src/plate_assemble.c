#include "plate_assemble.h"

#include <ctype.h>
#include <string.h>

static void swap_char_det(AlprCharacterDetection* a, AlprCharacterDetection* b) {
    AlprCharacterDetection t = *a;
    *a = *b;
    *b = t;
}

static void sort_by_x(AlprCharacterDetection* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int best = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].x1 < arr[best].x1) {
                best = j;
            }
        }
        if (best != i) {
            swap_char_det(&arr[i], &arr[best]);
        }
    }
}

static int push_char(char* out, int out_size, int* pos, char c) {
    if (*pos >= out_size - 1) {
        return -1;
    }
    out[*pos] = c;
    (*pos)++;
    out[*pos] = '\0';
    return 0;
}

static int assemble_one_line(const AlprCharacterArray* chars, char* out, int out_size) {
    AlprCharacterDetection sorted[ALPR_MAX_DETECTIONS];
    int n = chars->count;
    for (int i = 0; i < n; i++) {
        sorted[i] = chars->items[i];
    }
    sort_by_x(sorted, n);

    int pos = 0;
    out[0] = '\0';

    for (int i = 0; i < n; i++) {
        char c = (char)toupper((unsigned char)sorted[i].label);
        if (push_char(out, out_size, &pos, c) != 0) {
            return -1;
        }

        if (i < n - 1) {
            char c_next = (char)toupper((unsigned char)sorted[i + 1].label);
            if (isalpha((unsigned char)c) && isdigit((unsigned char)c_next)) {
                if (push_char(out, out_size, &pos, '-') != 0) {
                    return -1;
                }
            }
        }
    }

    return 0;
}

static int assemble_two_line(const AlprCharacterArray* chars, char* out, int out_size) {
    AlprCharacterDetection top[ALPR_MAX_DETECTIONS];
    AlprCharacterDetection bottom[ALPR_MAX_DETECTIONS];
    int top_count = 0;
    int bottom_count = 0;

    float mean_y = 0.0f;
    for (int i = 0; i < chars->count; i++) {
        mean_y += chars->items[i].y1;
    }
    mean_y /= (float)chars->count;

    for (int i = 0; i < chars->count; i++) {
        if (chars->items[i].y1 < mean_y) {
            top[top_count++] = chars->items[i];
        } else {
            bottom[bottom_count++] = chars->items[i];
        }
    }

    sort_by_x(top, top_count);
    sort_by_x(bottom, bottom_count);

    int pos = 0;
    out[0] = '\0';

    for (int i = 0; i < top_count; i++) {
        char c = (char)toupper((unsigned char)top[i].label);
        if (push_char(out, out_size, &pos, c) != 0) {
            return -1;
        }
    }

    if (bottom_count > 0) {
        if (push_char(out, out_size, &pos, '-') != 0) {
            return -1;
        }
    }

    for (int i = 0; i < bottom_count; i++) {
        char c = (char)toupper((unsigned char)bottom[i].label);
        if (push_char(out, out_size, &pos, c) != 0) {
            return -1;
        }
    }

    return 0;
}

int alpr_assemble_plate_text(
    const AlprCharacterArray* chars,
    AlprPlateType plate_type,
    char* out,
    int out_size
) {
    if (!chars || !out || out_size <= 1 || chars->count <= 0) {
        return -1;
    }

    if (plate_type == ALPR_PLATE_ONE_LINE) {
        return assemble_one_line(chars, out, out_size);
    }
    return assemble_two_line(chars, out, out_size);
}
