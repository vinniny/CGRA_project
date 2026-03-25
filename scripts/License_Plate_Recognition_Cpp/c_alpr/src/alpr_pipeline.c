#include "alpr_pipeline.h"

#include "char_map.h"
#include "nms.h"
#include "plate_assemble.h"
#include "preprocess.h"
#include "yolo_decode.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

static int clampi(int v, int lo, int hi) {
    if (v < lo) {
        return lo;
    }
    if (v > hi) {
        return hi;
    }
    return v;
}

static int resize_linear_rgb(
    const unsigned char* src,
    int src_w,
    int src_h,
    int src_stride,
    unsigned char* dst,
    int dst_w,
    int dst_h
) {
    if (!src || !dst || src_w <= 0 || src_h <= 0 || dst_w <= 0 || dst_h <= 0) {
        return -1;
    }

    for (int y = 0; y < dst_h; y++) {
        float fy = (dst_h > 1) ? ((float)y * (float)(src_h - 1) / (float)(dst_h - 1)) : 0.0f;
        int y0 = clampi((int)fy, 0, src_h - 1);
        int y1 = clampi(y0 + 1, 0, src_h - 1);
        float wy = fy - (float)y0;

        for (int x = 0; x < dst_w; x++) {
            float fx = (dst_w > 1) ? ((float)x * (float)(src_w - 1) / (float)(dst_w - 1)) : 0.0f;
            int x0 = clampi((int)fx, 0, src_w - 1);
            int x1 = clampi(x0 + 1, 0, src_w - 1);
            float wx = fx - (float)x0;

            int didx = (y * dst_w + x) * 3;

            int idx00 = y0 * src_stride + x0 * 3;
            int idx10 = y0 * src_stride + x1 * 3;
            int idx01 = y1 * src_stride + x0 * 3;
            int idx11 = y1 * src_stride + x1 * 3;

            for (int c = 0; c < 3; c++) {
                float v00 = (float)src[idx00 + c];
                float v10 = (float)src[idx10 + c];
                float v01 = (float)src[idx01 + c];
                float v11 = (float)src[idx11 + c];

                float top = v00 * (1.0f - wx) + v10 * wx;
                float bot = v01 * (1.0f - wx) + v11 * wx;
                float val = top * (1.0f - wy) + bot * wy;

                int ival = (int)(val + 0.5f);
                if (ival < 0) {
                    ival = 0;
                } else if (ival > 255) {
                    ival = 255;
                }
                dst[didx + c] = (unsigned char)ival;
            }
        }
    }

    return 0;
}

int alpr_runtime_init(AlprRuntime* rt, const AlprConfig* cfg, int use_gpu) {
    if (!rt || !cfg) {
        return -1;
    }

    memset(rt, 0, sizeof(*rt));
    rt->cfg = *cfg;

    rt->plate_engine = alpr_onnx_create(cfg->plate_model_path, use_gpu);
    rt->char_engine = alpr_onnx_create(cfg->char_model_path, use_gpu);
    if (!rt->plate_engine || !rt->char_engine) {
        alpr_runtime_destroy(rt);
        return -2;
    }

    size_t plate_len = (size_t)cfg->plate_input_w * (size_t)cfg->plate_input_h * 3u;
    size_t char_len = (size_t)cfg->char_input_w * (size_t)cfg->char_input_h * 3u;

    rt->plate_input_u8 = (unsigned char*)malloc(plate_len);
    rt->plate_input_f32 = (float*)malloc(plate_len * sizeof(float));
    rt->char_input_u8 = (unsigned char*)malloc(char_len);
    rt->char_input_f32 = (float*)malloc(char_len * sizeof(float));

    if (!rt->plate_input_u8 || !rt->plate_input_f32 || !rt->char_input_u8 || !rt->char_input_f32) {
        alpr_runtime_destroy(rt);
        return -3;
    }

    return 0;
}

void alpr_runtime_destroy(AlprRuntime* rt) {
    if (!rt) {
        return;
    }

    if (rt->plate_engine) {
        alpr_onnx_destroy(rt->plate_engine);
    }
    if (rt->char_engine) {
        alpr_onnx_destroy(rt->char_engine);
    }

    free(rt->plate_input_u8);
    free(rt->plate_input_f32);
    free(rt->char_input_u8);
    free(rt->char_input_f32);

    memset(rt, 0, sizeof(*rt));
}

static int run_plate_detector(AlprRuntime* rt, const AlprImageU8* image, AlprDetectionArray* out) {
    AlprLetterboxMeta meta;
    if (alpr_letterbox_u8(
            image,
            rt->plate_input_u8,
            rt->cfg.plate_input_w,
            rt->cfg.plate_input_h,
            114,
            &meta
        ) != 0) {
        return -1;
    }

    if (alpr_normalize_chw_f32(
            rt->plate_input_u8,
            rt->cfg.plate_input_w,
            rt->cfg.plate_input_h,
            3,
            rt->plate_input_f32
        ) != 0) {
        return -2;
    }

    AlprOnnxOutput out_tensor;
    if (alpr_onnx_run(
            rt->plate_engine,
            rt->plate_input_f32,
            rt->cfg.plate_input_w,
            rt->cfg.plate_input_h,
            3,
            &out_tensor
        ) != 0) {
        return -3;
    }

    int dec = alpr_decode_yolo_tensor(&out_tensor, rt->cfg.plate_num_classes, rt->cfg.plate_conf_threshold, out);
    alpr_onnx_output_free(&out_tensor);
    if (dec != 0) {
        return -4;
    }

    alpr_nms(out, rt->cfg.plate_iou_threshold);

    for (int i = 0; i < out->count; i++) {
        alpr_map_box_from_letterbox(
            &out->items[i].x1,
            &out->items[i].y1,
            &out->items[i].x2,
            &out->items[i].y2,
            &meta,
            image->width,
            image->height
        );
    }

    return 0;
}

static int run_char_detector_for_plate(
    AlprRuntime* rt,
    const AlprImageU8* image,
    const AlprDetection* plate,
    AlprCharacterArray* out_chars
) {
    out_chars->count = 0;

    int x1 = clampi((int)plate->x1 - 2, 0, image->width - 1);
    int y1 = clampi((int)plate->y1 - 2, 0, image->height - 1);
    int x2 = clampi((int)plate->x2 + 2, 0, image->width);
    int y2 = clampi((int)plate->y2 + 2, 0, image->height);

    int crop_w = x2 - x1;
    int crop_h = y2 - y1;
    if (crop_w <= 1 || crop_h <= 1) {
        return -1;
    }

    int scale = (crop_w < 60) ? 5 : 4;
    int up_w = crop_w * scale;
    int up_h = crop_h * scale;
    size_t up_len = (size_t)up_w * (size_t)up_h * 3u;
    unsigned char* up = (unsigned char*)malloc(up_len);
    if (!up) {
        return -2;
    }

    const unsigned char* crop_ptr = image->data + y1 * image->stride + x1 * 3;
    if (resize_linear_rgb(crop_ptr, crop_w, crop_h, image->stride, up, up_w, up_h) != 0) {
        free(up);
        return -3;
    }

    AlprImageU8 up_img;
    up_img.data = up;
    up_img.width = up_w;
    up_img.height = up_h;
    up_img.channels = 3;
    up_img.stride = up_w * 3;

    AlprLetterboxMeta meta;
    if (alpr_letterbox_u8(
            &up_img,
            rt->char_input_u8,
            rt->cfg.char_input_w,
            rt->cfg.char_input_h,
            114,
            &meta
        ) != 0) {
        free(up);
        return -4;
    }

    if (alpr_normalize_chw_f32(
            rt->char_input_u8,
            rt->cfg.char_input_w,
            rt->cfg.char_input_h,
            3,
            rt->char_input_f32
        ) != 0) {
        free(up);
        return -5;
    }

    AlprOnnxOutput out_tensor;
    if (alpr_onnx_run(
            rt->char_engine,
            rt->char_input_f32,
            rt->cfg.char_input_w,
            rt->cfg.char_input_h,
            3,
            &out_tensor
        ) != 0) {
        free(up);
        return -6;
    }

    AlprDetectionArray dets;
    int dec = alpr_decode_yolo_tensor(&out_tensor, rt->cfg.char_num_classes, rt->cfg.char_conf_threshold, &dets);
    alpr_onnx_output_free(&out_tensor);
    if (dec != 0) {
        free(up);
        return -7;
    }

    alpr_nms(&dets, rt->cfg.char_iou_threshold);

    for (int i = 0; i < dets.count; i++) {
        AlprDetection d = dets.items[i];
        alpr_map_box_from_letterbox(
            &d.x1,
            &d.y1,
            &d.x2,
            &d.y2,
            &meta,
            up_w,
            up_h
        );

        int class_id = d.class_id;
        if (!alpr_is_valid_class_id(class_id)) {
            continue;
        }
        if (out_chars->count >= ALPR_MAX_DETECTIONS) {
            break;
        }

        AlprCharacterDetection cd;
        cd.x1 = d.x1;
        cd.y1 = d.y1;
        cd.x2 = d.x2;
        cd.y2 = d.y2;
        cd.score = d.score;
        cd.label = alpr_char_from_class_id(class_id);
        out_chars->items[out_chars->count++] = cd;
    }

    free(up);
    return 0;
}

int alpr_runtime_run_image_ex(
    AlprRuntime* rt,
    const AlprImageU8* image,
    AlprPlateResult* out_best,
    AlprDetection* out_best_plate_box
) {
    if (!rt || !image || !image->data || image->channels != 3 || !out_best) {
        return -1;
    }

    memset(out_best, 0, sizeof(*out_best));
    if (out_best_plate_box) {
        memset(out_best_plate_box, 0, sizeof(*out_best_plate_box));
    }

    AlprDetectionArray plates;
    if (run_plate_detector(rt, image, &plates) != 0) {
        return -2;
    }

    float best_score = -1.0f;
    for (int i = 0; i < plates.count; i++) {
        AlprCharacterArray chars;
        if (run_char_detector_for_plate(rt, image, &plates.items[i], &chars) != 0) {
            continue;
        }
        if (chars.count <= 0) {
            continue;
        }

        AlprPlateType type = (plates.items[i].class_id == rt->cfg.plate_two_line_class_id)
            ? ALPR_PLATE_TWO_LINE
            : ALPR_PLATE_ONE_LINE;

        char text[ALPR_MAX_TEXT];
        if (alpr_assemble_plate_text(&chars, type, text, (int)sizeof(text)) != 0) {
            continue;
        }

        if (plates.items[i].score > best_score) {
            best_score = plates.items[i].score;
            out_best->type = type;
            out_best->confidence = plates.items[i].score;
            strncpy(out_best->text, text, sizeof(out_best->text) - 1);
            out_best->text[sizeof(out_best->text) - 1] = '\0';
            if (out_best_plate_box) {
                *out_best_plate_box = plates.items[i];
            }
        }
    }

    if (best_score < 0.0f) {
        return 1;
    }

    return 0;
}

int alpr_runtime_run_image(
    AlprRuntime* rt,
    const AlprImageU8* image,
    AlprPlateResult* out_best
) {
    return alpr_runtime_run_image_ex(rt, image, out_best, NULL);
}
