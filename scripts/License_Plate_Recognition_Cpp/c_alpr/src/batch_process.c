#include "batch_process.h"
#include "image_io.h"
#include "result_dump.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>

static int match_pattern(const char* filename, const char* pattern) {
    if (!pattern || pattern[0] == '\0') {
        return 1;
    }
    const char* dot = strrchr(filename, '.');
    if (!dot) {
        return 0;
    }
    return strcmp(dot + 1, pattern) == 0;
}

int alpr_batch_process_folder(
    const char* folder_path,
    const char* pattern,
    AlprRuntime* runtime,
    AlprBatchCallback callback,
    void* user_data
) {
    if (!folder_path || !runtime || !callback) {
        return -1;
    }

    WIN32_FIND_DATAA find_data;
    HANDLE find_handle;
    char search_path[MAX_PATH];

    snprintf(search_path, sizeof(search_path), "%s\\*", folder_path);

    find_handle = FindFirstFileA(search_path, &find_data);
    if (find_handle == INVALID_HANDLE_VALUE) {
        return -2;
    }

    int processed = 0;
    do {
        if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            if (match_pattern(find_data.cFileName, pattern)) {
                char full_path[MAX_PATH];
                snprintf(full_path, sizeof(full_path), "%s\\%s", folder_path, find_data.cFileName);

                AlprImageU8 image;
                int load_ok = alpr_load_bmp24_rgb(full_path, &image);
                if (load_ok == 0) {
                    AlprPlateResult result;
                    int run_ok = alpr_runtime_run_image(runtime, &image, &result);

                    AlprFullResult full;
                    full.image_path = full_path;
                    full.plate = result;
                    full.error_code = run_ok;

                    callback(full_path, &result, run_ok, user_data);

                    alpr_free_image(&image);
                    processed++;
                }
            }
        }
    } while (FindNextFileA(find_handle, &find_data));

    FindClose(find_handle);
    return processed;
}

#else

#include <dirent.h>
#include <sys/stat.h>

static int match_extension(const char* filename, const char* ext) {
    if (!ext || ext[0] == '\0') {
        return 1;
    }
    const char* dot = strrchr(filename, '.');
    if (!dot) {
        return 0;
    }
    return strcmp(dot + 1, ext) == 0;
}

int alpr_batch_process_folder(
    const char* folder_path,
    const char* pattern,
    AlprRuntime* runtime,
    AlprBatchCallback callback,
    void* user_data
) {
    if (!folder_path || !runtime) {
        return -1;
    }

    DIR* dir = opendir(folder_path);
    if (!dir) {
        return -2;
    }

    int processed = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        char full_path[4096];
        snprintf(full_path, sizeof(full_path), "%s/%s", folder_path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) != 0 || !S_ISREG(st.st_mode)) {
            continue;
        }

        if (!match_extension(entry->d_name, pattern)) {
            continue;
        }

        AlprImageU8 image;
        int load_ok = alpr_load_bmp24_rgb(full_path, &image);
        if (load_ok == 0) {
            AlprPlateResult result;
            int run_ok = alpr_runtime_run_image(runtime, &image, &result);

            if (callback) {
                callback(full_path, &result, run_ok, user_data);
            }

            alpr_free_image(&image);
            processed++;
        }
    }

    closedir(dir);
    return processed;
}

#endif
