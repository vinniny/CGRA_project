#include "alpr_pipeline.h"
#include "batch_process.h"
#include "capture_ffmpeg.h"
#include "config.h"
#include "display_ffplay.h"
#include "draw_overlay.h"
#include "image_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <sys/stat.h>
#endif

static volatile int g_quit_requested = 0;

static void signal_handler(int sig) {
    (void)sig;
    g_quit_requested = 1;
}

static int is_webcam_mode(const char* arg) {
    if (!arg) {
        return 0;
    }
    if (strcmp(arg, "webcam") == 0 || strcmp(arg, "--webcam") == 0 || strcmp(arg, "-w") == 0) {
        return 1;
    }
    if (strncmp(arg, "webcam:", 7) == 0) {
        return 1;
    }
    return 0;
}

static int parse_webcam_index(const char* arg, int fallback_index) {
    if (!arg) {
        return fallback_index;
    }
    if (strncmp(arg, "webcam:", 7) != 0) {
        return fallback_index;
    }
    const char* p = arg + 7;
    if (*p == '\0') {
        return fallback_index;
    }
    char* end = NULL;
    long v = strtol(p, &end, 10);
    if (end == p) {
        return fallback_index;
    }
    if (v < 0) {
        v = 0;
    }
    return (int)v;
}

static void canonicalize_plate_text(const char* text, char* out, int out_size) {
    int pos = 0;
    if (!out || out_size <= 0) {
        return;
    }
    out[0] = '\0';
    if (!text) {
        return;
    }

    for (const char* p = text; *p; p++) {
        unsigned char ch = (unsigned char)*p;
        if (!isalnum(ch)) {
            continue;
        }
        if (pos >= out_size - 1) {
            break;
        }
        out[pos++] = (char)toupper(ch);
    }
    out[pos] = '\0';
}

static void correct_plate_text(char* text, int text_size) {
    if (!text || text_size <= 0) {
        return;
    }

    for (int i = 0; text[i]; i++) {
        unsigned char ch = (unsigned char)text[i];
        
        if (isdigit(ch)) {
            char digitc = (char)ch;
            if (digitc == '0' && i > 0 && isalpha((unsigned char)text[i - 1])) {
                continue;
            }
            if (digitc == '8' && i > 0 && isalpha((unsigned char)text[i - 1])) {
                if (text[i - 1] == 'S' || text[i - 1] == 'B') {
                    text[i - 1] = (text[i - 1] == 'S') ? '5' : '8';
                }
            }
        } else if (isalpha(ch)) {
            if (ch == 'O' && (i + 1 < (int)strlen(text) && isdigit((unsigned char)text[i + 1]))) {
                text[i] = '0';
            } else if (ch == 'S' && (i + 1 < (int)strlen(text) && isdigit((unsigned char)text[i + 1]))) {
                text[i] = '5';
            } else if (ch == 'B' && (i + 1 < (int)strlen(text) && isdigit((unsigned char)text[i + 1]))) {
                text[i] = '8';
            } else if (ch == 'I' && (i + 1 < (int)strlen(text) && isdigit((unsigned char)text[i + 1]))) {
                text[i] = '1';
            } else if (ch == 'L' && (i + 1 < (int)strlen(text) && isdigit((unsigned char)text[i + 1]))) {
                text[i] = '1';
            } else if (ch == 'Z' && (i + 1 < (int)strlen(text) && isdigit((unsigned char)text[i + 1]))) {
                text[i] = '2';
            }
        }
    }
}

static int is_plausible_plate_text(const char* text) {
    if (!text || text[0] == '\0') {
        return 0;
    }

    char canon[ALPR_MAX_TEXT];
    canonicalize_plate_text(text, canon, (int)sizeof(canon));

    int n = (int)strlen(canon);
    if (n < 5 || n > 10) {
        return 0;
    }

    int digit_count = 0;
    for (int i = 0; i < n; i++) {
        if (isdigit((unsigned char)canon[i])) {
            digit_count++;
        }
    }

    return (digit_count >= 3) ? 1 : 0;
}

static int is_video_file(const char* arg) {
    if (!arg) {
        return 0;
    }
    if (strncmp(arg, "video:", 6) == 0) {
        return 1;
    }
    const char* dot = strrchr(arg, '.');
    if (!dot) {
        return 0;
    }
    dot++;
    if (strcmp(dot, "mp4") == 0 || strcmp(dot, "avi") == 0 ||
        strcmp(dot, "mkv") == 0 || strcmp(dot, "mov") == 0 ||
        strcmp(dot, "webm") == 0 || strcmp(dot, "flv") == 0 ||
        strcmp(dot, "ts") == 0 || strcmp(dot, "m4v") == 0) {
        return 1;
    }
    return 0;
}

static const char* get_video_path(const char* arg) {
    if (!arg) {
        return NULL;
    }
    if (strncmp(arg, "video:", 6) == 0) {
        return arg + 6;
    }
    return arg;
}

#define PLATE_HISTORY 8

typedef struct {
    char raw[ALPR_MAX_TEXT];
    char canon[ALPR_MAX_TEXT];
    float conf;
} PlateHistoryEntry;

static int pick_stable_plate(
    const PlateHistoryEntry* hist,
    int hist_count,
    char* out_text,
    int out_text_size,
    float* out_conf
) {
    if (!hist || hist_count <= 0 || !out_text || out_text_size <= 1) {
        return 0;
    }

    int best_count = 0;
    float best_avg_conf = 0.0f;
    int best_idx = -1;

    for (int i = 0; i < hist_count; i++) {
        if (hist[i].canon[0] == '\0') {
            continue;
        }

        int count = 0;
        float sum_conf = 0.0f;
        for (int j = 0; j < hist_count; j++) {
            if (strcmp(hist[i].canon, hist[j].canon) == 0) {
                count++;
                sum_conf += hist[j].conf;
            }
        }

        float avg_conf = (count > 0) ? (sum_conf / (float)count) : 0.0f;
        if (count > best_count || (count == best_count && avg_conf > best_avg_conf)) {
            best_count = count;
            best_avg_conf = avg_conf;
            best_idx = i;
        }
    }

    if (best_idx < 0) {
        return 0;
    }

    int best_raw_idx = best_idx;
    float best_raw_conf = -1.0f;
    for (int i = 0; i < hist_count; i++) {
        if (strcmp(hist[i].canon, hist[best_idx].canon) == 0 && hist[i].conf > best_raw_conf) {
            best_raw_conf = hist[i].conf;
            best_raw_idx = i;
        }
    }

    strncpy(out_text, hist[best_raw_idx].raw, out_text_size - 1);
    out_text[out_text_size - 1] = '\0';
    if (out_conf) {
        *out_conf = hist[best_raw_idx].conf;
    }
    return 1;
}

static int run_capture_loop(AlprRuntime* runtime, const AlprConfig* cfg, int camera_index, const char* video_path) {
    const int cam_w = 640;
    const int cam_h = 360;
    const int cam_fps = 8;
    const int infer_every_n = 2;

    AlprCapture* cap = NULL;
    if (video_path) {
        cap = alpr_capture_open_video(video_path, cam_w, cam_h);
        if (!cap) {
            fprintf(stderr, "Video open failed: %s\n", video_path);
            fprintf(stderr, "Ensure ffmpeg is installed and the file exists.\n");
            return -1;
        }
        printf("Video mode started: %s. Press Ctrl+C to quit.\n", video_path);
    } else {
        cap = alpr_capture_open_camera(camera_index, cam_w, cam_h, cam_fps);
        if (!cap) {
            fprintf(stderr, "Camera open failed. Ensure ffmpeg is installed and webcam index is correct.\n");
            fprintf(stderr, "Try camera index: webcam:0, webcam:1, webcam:2\n");
            return -1;
        }
        printf("Webcam mode started (index=%d). Press Ctrl+C to quit.\n", camera_index);
    }

    AlprDisplay* disp = alpr_display_open_ffplay(cam_w, cam_h, cam_fps);
    if (!disp) {
        printf("Warning: ffplay window unavailable, fallback to console-only mode.\n");
    }

    int frame_count = 0;
    int detected_count = 0;
    int infer_count = 0;
    clock_t t0 = clock();
    clock_t t_last = t0;
    int has_last_detection = 0;
    AlprPlateResult last_best;
    AlprDetection last_box;
    char stable_text[ALPR_MAX_TEXT];
    PlateHistoryEntry hist[PLATE_HISTORY];
    int hist_count = 0;
    int hist_next = 0;
    memset(&last_best, 0, sizeof(last_best));
    memset(&last_box, 0, sizeof(last_box));
    memset(stable_text, 0, sizeof(stable_text));
    memset(hist, 0, sizeof(hist));

    for (;;) {
        AlprImageU8 frame;
        memset(&frame, 0, sizeof(frame));

        int cr = alpr_capture_read(cap, &frame);
        if (cr != 0) {
            fprintf(stderr, "Camera read failed: %d\n", cr);
            break;
        }

        frame_count++;
        int rc = 1;
        AlprPlateResult best;
        AlprDetection best_box;
        memset(&best, 0, sizeof(best));
        memset(&best_box, 0, sizeof(best_box));

        if ((frame_count % infer_every_n) == 0) {
            rc = alpr_runtime_run_image_ex(runtime, &frame, &best, &best_box);
            infer_count++;
            if (best.text[0] != '\0') {
                printf("[infer #%d] raw='%s' conf=%.3f plausible=%d\n", infer_count, best.text, best.confidence, is_plausible_plate_text(best.text));
            }
            if (rc == 0 && is_plausible_plate_text(best.text)) {
                char canon[ALPR_MAX_TEXT];
                canonicalize_plate_text(best.text, canon, (int)sizeof(canon));

                if (canon[0] != '\0') {
                    PlateHistoryEntry* e = &hist[hist_next];
                    strncpy(e->raw, best.text, sizeof(e->raw) - 1);
                    e->raw[sizeof(e->raw) - 1] = '\0';
                    strncpy(e->canon, canon, sizeof(e->canon) - 1);
                    e->canon[sizeof(e->canon) - 1] = '\0';
                    e->conf = best.confidence;

                    hist_next = (hist_next + 1) % PLATE_HISTORY;
                    if (hist_count < PLATE_HISTORY) {
                        hist_count++;
                    }
                }

                char voted_text[ALPR_MAX_TEXT];
                float voted_conf = 0.0f;
                if (pick_stable_plate(hist, hist_count, voted_text, (int)sizeof(voted_text), &voted_conf)) {
                    printf("[voting PASS] voted='%s' (hist_cnt=%d)\n", voted_text, hist_count);
                    
                    correct_plate_text(voted_text, (int)sizeof(voted_text));
                    printf("[corrected] after post-process='%s'\n", voted_text);
                    
                    if (strcmp(stable_text, voted_text) != 0) {
                        printf("[plate DISPLAY] %s (conf=%.3f)\n", voted_text, voted_conf);
                    }
                    strncpy(stable_text, voted_text, sizeof(stable_text) - 1);
                    stable_text[sizeof(stable_text) - 1] = '\0';

                    has_last_detection = 1;
                    last_best = best;
                    strncpy(last_best.text, stable_text, sizeof(last_best.text) - 1);
                    last_best.text[sizeof(last_best.text) - 1] = '\0';
                    last_box = best_box;
                    detected_count++;
                } else {
                    printf("[voting FAIL] hist_cnt=%d no_consensus\n", hist_count);
                }
            }
        }

        if (has_last_detection && stable_text[0] != '\0') {
            printf("[DRAW] stable_text='%s' box=(%.0f,%.0f,%.0f,%.0f)\n", stable_text, last_box.x1, last_box.y1, last_box.x2, last_box.y2);
            (void)alpr_draw_plate_box(&frame, &last_box, stable_text);
        }

        clock_t now = clock();
        double sec_since_last = (double)(now - t_last) / (double)CLOCKS_PER_SEC;
        double fps_now = 0.0;
        {
            double total_sec = (double)(now - t0) / (double)CLOCKS_PER_SEC;
            fps_now = (total_sec > 0.0) ? ((double)frame_count / total_sec) : 0.0;
        }

        if (cfg->display_fps) {
            (void)alpr_draw_fps(&frame, (float)fps_now);
        }

        if (disp) {
            int dr = alpr_display_show_frame(disp, &frame);
            if (dr != 0) {
                fprintf(stderr, "Display write failed: %d\n", dr);
                alpr_display_close(disp);
                disp = NULL;
            }
        }

        if (cfg->display_fps && sec_since_last >= 1.0) {
            double infer_fps = (fps_now > 0.0) ? (fps_now / (double)infer_every_n) : 0.0;
            printf("[stats] frames=%d infer=%d detected=%d fps=%.2f infer_fps=%.2f\n", frame_count, infer_count, detected_count, fps_now, infer_fps);
            t_last = now;
        }

        alpr_capture_release_frame(&frame);

        if (g_quit_requested) {
            printf("Quit requested by user.\n");
            break;
        }
    }

    if (disp) {
        alpr_display_close(disp);
    }

    alpr_capture_close(cap);
    return 0;
}

int main(int argc, char** argv) {
    const char* config_path = "configs/alpr_config.ini";
    const char* image_path = NULL;
    if (argc > 1) {
        config_path = argv[1];
    }
    if (argc > 2) {
        image_path = argv[2];
    }

    AlprConfig cfg;
    if (alpr_config_set_defaults(&cfg) != 0) {
        fprintf(stderr, "Failed to create default config.\n");
        return 1;
    }

    if (alpr_config_load(config_path, &cfg) != 0) {
        fprintf(stderr, "Cannot load config at: %s\n", config_path);
        fprintf(stderr, "Using defaults.\n");
    }

    alpr_config_print(&cfg);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    AlprRuntime runtime;
    if (alpr_runtime_init(&runtime, &cfg, 1) != 0) {
        fprintf(stderr, "Runtime init failed. Check model paths and ONNX backend settings.\n");
    } else {
#ifdef _WIN32
        DWORD attrib = GetFileAttributesA(image_path ? image_path : ".");
        int is_directory = (attrib != INVALID_FILE_ATTRIBUTES) && (attrib & FILE_ATTRIBUTE_DIRECTORY);
#else
        int is_directory = 0;
        if (image_path) {
            struct stat st;
            if (stat(image_path, &st) == 0 && S_ISDIR(st.st_mode)) {
                is_directory = 1;
            }
        }
#endif

        if (is_webcam_mode(image_path)) {
            int cam_idx = parse_webcam_index(image_path, cfg.camera_index);
            (void)run_capture_loop(&runtime, &cfg, cam_idx, NULL);
        } else if (is_video_file(image_path)) {
            const char* vpath = get_video_path(image_path);
            (void)run_capture_loop(&runtime, &cfg, -1, vpath);
        } else if (is_directory && image_path) {
            fprintf(stderr, "Batch folder mode: %s\n", image_path);
            (void)alpr_batch_process_folder(image_path, "bmp", &runtime, NULL, NULL);
        } else if (image_path && !is_directory) {
            AlprImageU8 image;
            if (alpr_load_bmp24_rgb(image_path, &image) == 0) {
                AlprPlateResult result;
                int rc = alpr_runtime_run_image(&runtime, &image, &result);
                if (rc == 0 && result.text[0] != '\0') {
                    printf("Plate: %s (conf=%.3f)\n", result.text, result.confidence);
                } else {
                    printf("No plate detected.\n");
                }
                alpr_free_image(&image);
            } else {
                fprintf(stderr, "Failed to load image: %s\n", image_path);
            }
        } else {
            fprintf(stderr, "Usage: %s [config] <webcam[:<index>] | video:<path> | file.mp4 | image.bmp | folder/>\n", argv[0]);
        }

        alpr_runtime_destroy(&runtime);
    }

    return 0;
}
