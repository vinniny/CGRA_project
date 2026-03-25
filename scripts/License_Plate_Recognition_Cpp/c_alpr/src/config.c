#include "config.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_absolute_path(const char* p) {
    if (!p || !p[0]) {
        return 0;
    }
#ifdef _WIN32
    if ((p[0] >= 'A' && p[0] <= 'Z' && p[1] == ':') || (p[0] >= 'a' && p[0] <= 'z' && p[1] == ':')) {
        return 1;
    }
    if (p[0] == '\\' && p[1] == '\\') {
        return 1;
    }
#else
    if (p[0] == '/') {
        return 1;
    }
#endif
    return 0;
}

static void get_parent_dir(const char* file_path, char* out_dir, size_t out_sz) {
    if (!out_dir || out_sz == 0) {
        return;
    }
    out_dir[0] = '\0';
    if (!file_path) {
        return;
    }

    strncpy(out_dir, file_path, out_sz - 1);
    out_dir[out_sz - 1] = '\0';

    char* s1 = strrchr(out_dir, '/');
    char* s2 = strrchr(out_dir, '\\');
    char* sep = s1;
    if (!sep || (s2 && s2 > sep)) {
        sep = s2;
    }
    if (sep) {
        *sep = '\0';
    } else {
        out_dir[0] = '.';
        out_dir[1] = '\0';
    }
}

static void join_path(const char* base_dir, const char* rel_path, char* out, size_t out_sz) {
    if (!out || out_sz == 0) {
        return;
    }
    out[0] = '\0';
    if (!base_dir || !rel_path) {
        return;
    }

    if (snprintf(out, out_sz, "%s/%s", base_dir, rel_path) < 0) {
        out[0] = '\0';
    }
}

static void trim(char* s) {
    char* p = s;
    while (*p && isspace((unsigned char)*p)) {
        p++;
    }
    if (p != s) {
        memmove(s, p, strlen(p) + 1);
    }

    size_t n = strlen(s);
    while (n > 0 && isspace((unsigned char)s[n - 1])) {
        s[n - 1] = '\0';
        n--;
    }
}

static int parse_int(const char* v, int* out) {
    char* end = NULL;
    long x = strtol(v, &end, 10);
    if (end == v) {
        return -1;
    }
    *out = (int)x;
    return 0;
}

static int parse_float(const char* v, float* out) {
    char* end = NULL;
    float x = (float)strtod(v, &end);
    if (end == v) {
        return -1;
    }
    *out = x;
    return 0;
}

int alpr_config_set_defaults(AlprConfig* cfg) {
    if (!cfg) {
        return -1;
    }

    memset(cfg, 0, sizeof(*cfg));
    strncpy(cfg->plate_model_path, "../models/license_plate.onnx", sizeof(cfg->plate_model_path) - 1);
    strncpy(cfg->char_model_path, "../models/character.onnx", sizeof(cfg->char_model_path) - 1);

    cfg->plate_input_w = 640;
    cfg->plate_input_h = 640;
    cfg->char_input_w = 640;
    cfg->char_input_h = 640;

    cfg->plate_conf_threshold = 0.80f;
    cfg->plate_iou_threshold = 0.45f;
    cfg->char_conf_threshold = 0.10f;
    cfg->char_iou_threshold = 0.45f;
    cfg->plate_num_classes = 2;
    cfg->char_num_classes = 30;

    cfg->camera_index = 0;
    cfg->display_fps = 1;

    cfg->plate_one_line_class_id = 0;
    cfg->plate_two_line_class_id = 1;

    return 0;
}

int alpr_config_load(const char* path, AlprConfig* cfg) {
    if (!path || !cfg) {
        return -1;
    }

    FILE* f = fopen(path, "r");
    if (!f) {
        return -2;
    }

    char line[1024];
    while (fgets(line, sizeof(line), f) != NULL) {
        trim(line);
        if (line[0] == '\0' || line[0] == '#' || line[0] == ';') {
            continue;
        }

        char* eq = strchr(line, '=');
        if (!eq) {
            continue;
        }
        *eq = '\0';

        char* key = line;
        char* value = eq + 1;
        trim(key);
        trim(value);

        if (strcmp(key, "plate_model_path") == 0) {
            strncpy(cfg->plate_model_path, value, sizeof(cfg->plate_model_path) - 1);
        } else if (strcmp(key, "char_model_path") == 0) {
            strncpy(cfg->char_model_path, value, sizeof(cfg->char_model_path) - 1);
        } else if (strcmp(key, "plate_input_w") == 0) {
            parse_int(value, &cfg->plate_input_w);
        } else if (strcmp(key, "plate_input_h") == 0) {
            parse_int(value, &cfg->plate_input_h);
        } else if (strcmp(key, "char_input_w") == 0) {
            parse_int(value, &cfg->char_input_w);
        } else if (strcmp(key, "char_input_h") == 0) {
            parse_int(value, &cfg->char_input_h);
        } else if (strcmp(key, "plate_conf_threshold") == 0) {
            parse_float(value, &cfg->plate_conf_threshold);
        } else if (strcmp(key, "plate_iou_threshold") == 0) {
            parse_float(value, &cfg->plate_iou_threshold);
        } else if (strcmp(key, "char_conf_threshold") == 0) {
            parse_float(value, &cfg->char_conf_threshold);
        } else if (strcmp(key, "char_iou_threshold") == 0) {
            parse_float(value, &cfg->char_iou_threshold);
        } else if (strcmp(key, "plate_num_classes") == 0) {
            parse_int(value, &cfg->plate_num_classes);
        } else if (strcmp(key, "char_num_classes") == 0) {
            parse_int(value, &cfg->char_num_classes);
        } else if (strcmp(key, "camera_index") == 0) {
            parse_int(value, &cfg->camera_index);
        } else if (strcmp(key, "display_fps") == 0) {
            parse_int(value, &cfg->display_fps);
        } else if (strcmp(key, "plate_one_line_class_id") == 0) {
            parse_int(value, &cfg->plate_one_line_class_id);
        } else if (strcmp(key, "plate_two_line_class_id") == 0) {
            parse_int(value, &cfg->plate_two_line_class_id);
        }
    }

    fclose(f);

    {
        char cfg_dir[512];
        char abs_model[512];

        get_parent_dir(path, cfg_dir, sizeof(cfg_dir));

        if (!is_absolute_path(cfg->plate_model_path)) {
            join_path(cfg_dir, cfg->plate_model_path, abs_model, sizeof(abs_model));
            if (abs_model[0] != '\0') {
                strncpy(cfg->plate_model_path, abs_model, sizeof(cfg->plate_model_path) - 1);
                cfg->plate_model_path[sizeof(cfg->plate_model_path) - 1] = '\0';
            }
        }

        if (!is_absolute_path(cfg->char_model_path)) {
            join_path(cfg_dir, cfg->char_model_path, abs_model, sizeof(abs_model));
            if (abs_model[0] != '\0') {
                strncpy(cfg->char_model_path, abs_model, sizeof(cfg->char_model_path) - 1);
                cfg->char_model_path[sizeof(cfg->char_model_path) - 1] = '\0';
            }
        }
    }

    return 0;
}

void alpr_config_print(const AlprConfig* cfg) {
    if (!cfg) {
        return;
    }

    printf("==== ALPR CONFIG ====\n");
    printf("plate_model_path        = %s\n", cfg->plate_model_path);
    printf("char_model_path         = %s\n", cfg->char_model_path);
    printf("plate_input             = %dx%d\n", cfg->plate_input_w, cfg->plate_input_h);
    printf("char_input              = %dx%d\n", cfg->char_input_w, cfg->char_input_h);
    printf("plate_conf_threshold    = %.3f\n", cfg->plate_conf_threshold);
    printf("plate_iou_threshold     = %.3f\n", cfg->plate_iou_threshold);
    printf("char_conf_threshold     = %.3f\n", cfg->char_conf_threshold);
    printf("char_iou_threshold      = %.3f\n", cfg->char_iou_threshold);
    printf("plate_num_classes       = %d\n", cfg->plate_num_classes);
    printf("char_num_classes        = %d\n", cfg->char_num_classes);
    printf("camera_index            = %d\n", cfg->camera_index);
    printf("display_fps             = %d\n", cfg->display_fps);
    printf("plate_one_line_class_id = %d\n", cfg->plate_one_line_class_id);
    printf("plate_two_line_class_id = %d\n", cfg->plate_two_line_class_id);
}
