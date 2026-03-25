#include "image_io.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint16_t rd_u16(const unsigned char* p) {
    return (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
}

static uint32_t rd_u32(const unsigned char* p) {
    return (uint32_t)(p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24));
}

static int32_t rd_i32(const unsigned char* p) {
    return (int32_t)rd_u32(p);
}

int alpr_load_bmp24_rgb(const char* path, AlprImageU8* out_image) {
    if (!path || !out_image) {
        return -1;
    }

    memset(out_image, 0, sizeof(*out_image));

    FILE* f = fopen(path, "rb");
    if (!f) {
        return -2;
    }

    unsigned char file_hdr[14];
    unsigned char dib_hdr[40];
    if (fread(file_hdr, 1, sizeof(file_hdr), f) != sizeof(file_hdr)) {
        fclose(f);
        return -3;
    }
    if (fread(dib_hdr, 1, sizeof(dib_hdr), f) != sizeof(dib_hdr)) {
        fclose(f);
        return -4;
    }

    if (file_hdr[0] != 'B' || file_hdr[1] != 'M') {
        fclose(f);
        return -5;
    }

    uint32_t data_offset = rd_u32(&file_hdr[10]);
    uint32_t dib_size = rd_u32(&dib_hdr[0]);
    int32_t width = rd_i32(&dib_hdr[4]);
    int32_t height = rd_i32(&dib_hdr[8]);
    uint16_t planes = rd_u16(&dib_hdr[12]);
    uint16_t bpp = rd_u16(&dib_hdr[14]);
    uint32_t compression = rd_u32(&dib_hdr[16]);

    if (dib_size < 40 || width <= 0 || height == 0 || planes != 1 || bpp != 24 || compression != 0) {
        fclose(f);
        return -6;
    }

    int flip_vertical = 1;
    int abs_h = height;
    if (height < 0) {
        abs_h = -height;
        flip_vertical = 0;
    }

    int row_stride_bmp = ((width * 3 + 3) / 4) * 4;
    size_t out_stride = (size_t)width * 3u;
    size_t out_size = out_stride * (size_t)abs_h;
    unsigned char* out = (unsigned char*)malloc(out_size);
    if (!out) {
        fclose(f);
        return -7;
    }

    if (fseek(f, (long)data_offset, SEEK_SET) != 0) {
        free(out);
        fclose(f);
        return -8;
    }

    unsigned char* row = (unsigned char*)malloc((size_t)row_stride_bmp);
    if (!row) {
        free(out);
        fclose(f);
        return -9;
    }

    for (int y = 0; y < abs_h; y++) {
        if (fread(row, 1, (size_t)row_stride_bmp, f) != (size_t)row_stride_bmp) {
            free(row);
            free(out);
            fclose(f);
            return -10;
        }

        int dst_y = flip_vertical ? (abs_h - 1 - y) : y;
        unsigned char* dst = out + (size_t)dst_y * out_stride;

        for (int x = 0; x < width; x++) {
            unsigned char b = row[x * 3 + 0];
            unsigned char g = row[x * 3 + 1];
            unsigned char r = row[x * 3 + 2];
            dst[x * 3 + 0] = r;
            dst[x * 3 + 1] = g;
            dst[x * 3 + 2] = b;
        }
    }

    free(row);
    fclose(f);

    out_image->data = out;
    out_image->width = width;
    out_image->height = abs_h;
    out_image->channels = 3;
    out_image->stride = (int)out_stride;
    return 0;
}

void alpr_free_image(AlprImageU8* image) {
    if (!image) {
        return;
    }
    free(image->data);
    memset(image, 0, sizeof(*image));
}
