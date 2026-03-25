#ifndef DISPLAY_FFPLAY_H
#define DISPLAY_FFPLAY_H

#include "alpr_types.h"

typedef struct AlprDisplay AlprDisplay;

AlprDisplay* alpr_display_open_ffplay(int width, int height, int fps);
void alpr_display_close(AlprDisplay* disp);
int alpr_display_show_frame(AlprDisplay* disp, const AlprImageU8* frame);

#endif
