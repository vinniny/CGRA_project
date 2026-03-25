#include "plate_assemble.h"

#include <stdio.h>
#include <string.h>

static int test_one_line(void) {
    AlprCharacterArray a;
    memset(&a, 0, sizeof(a));

    a.items[0] = (AlprCharacterDetection){.x1 = 40, .label = '2'};
    a.items[1] = (AlprCharacterDetection){.x1 = 10, .label = 'A'};
    a.items[2] = (AlprCharacterDetection){.x1 = 20, .label = 'B'};
    a.items[3] = (AlprCharacterDetection){.x1 = 30, .label = '1'};
    a.count = 4;

    char out[64];
    if (alpr_assemble_plate_text(&a, ALPR_PLATE_ONE_LINE, out, (int)sizeof(out)) != 0) {
        return -1;
    }

    return strcmp(out, "AB1-2") == 0 ? 0 : -1;
}

static int test_two_line(void) {
    AlprCharacterArray a;
    memset(&a, 0, sizeof(a));

    a.items[0] = (AlprCharacterDetection){.x1 = 10, .y1 = 10, .label = '3'};
    a.items[1] = (AlprCharacterDetection){.x1 = 20, .y1 = 10, .label = '0'};
    a.items[2] = (AlprCharacterDetection){.x1 = 10, .y1 = 30, .label = 'A'};
    a.items[3] = (AlprCharacterDetection){.x1 = 20, .y1 = 30, .label = '1'};
    a.count = 4;

    char out[64];
    if (alpr_assemble_plate_text(&a, ALPR_PLATE_TWO_LINE, out, (int)sizeof(out)) != 0) {
        return -1;
    }

    return strcmp(out, "30-A1") == 0 ? 0 : -1;
}

int main(void) {
    int ok1 = test_one_line();
    int ok2 = test_two_line();

    if (ok1 == 0 && ok2 == 0) {
        printf("test_plate_assemble: PASS\n");
        return 0;
    }

    printf("test_plate_assemble: FAIL\n");
    return 1;
}
