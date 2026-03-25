#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include "alpr_types.h"

int alpr_load_bmp24_rgb(const char* path, AlprImageU8* out_image);
void alpr_free_image(AlprImageU8* image);

#endif
