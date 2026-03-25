#ifndef CONFIG_H
#define CONFIG_H

#include <stddef.h>

typedef struct AlprConfig {
    char plate_model_path[260];
    char char_model_path[260];
    int plate_input_w;
    int plate_input_h;
    int char_input_w;
    int char_input_h;
    float plate_conf_threshold;
    float plate_iou_threshold;
    float char_conf_threshold;
    float char_iou_threshold;
    int plate_num_classes;
    int char_num_classes;
    int camera_index;
    int display_fps;
    int plate_one_line_class_id;
    int plate_two_line_class_id;
} AlprConfig;

int alpr_config_set_defaults(AlprConfig* cfg);
int alpr_config_load(const char* path, AlprConfig* cfg);
void alpr_config_print(const AlprConfig* cfg);

#endif
