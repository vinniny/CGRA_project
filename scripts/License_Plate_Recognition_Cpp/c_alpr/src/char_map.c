#include "char_map.h"

/*
Mapping copied from config_character.yaml:
29->0, 0->1, 1->2, ... 8->9, 9->A, 10->B, ... 28->Z
*/
static const char k_char_map[30] = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'K',
    'L', 'M', 'N', 'P', 'S', 'T', 'U', 'V', 'X',
    'Y', 'Z', '0'
};

int alpr_is_valid_class_id(int class_id) {
    return (class_id >= 0 && class_id < 30) ? 1 : 0;
}

char alpr_char_from_class_id(int class_id) {
    if (!alpr_is_valid_class_id(class_id)) {
        return '?';
    }
    return k_char_map[class_id];
}
