#include "draw_overlay.h"

static int clampi(int v, int lo, int hi) {
    if (v < lo) {
        return lo;
    }
    if (v > hi) {
        return hi;
    }
    return v;
}

static void set_px_rgb(AlprImageU8* frame, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    if (!frame || !frame->data) {
        return;
    }
    if (x < 0 || y < 0 || x >= frame->width || y >= frame->height) {
        return;
    }
    int idx = y * frame->stride + x * 3;
    frame->data[idx + 0] = r;
    frame->data[idx + 1] = g;
    frame->data[idx + 2] = b;
}

static void draw_rect(AlprImageU8* frame, int x1, int y1, int x2, int y2, int t, unsigned char r, unsigned char g, unsigned char b) {
    if (!frame || !frame->data || frame->width <= 0 || frame->height <= 0) {
        return;
    }

    x1 = clampi(x1, 0, frame->width - 1);
    y1 = clampi(y1, 0, frame->height - 1);
    x2 = clampi(x2, 0, frame->width - 1);
    y2 = clampi(y2, 0, frame->height - 1);
    if (x2 < x1 || y2 < y1) {
        return;
    }

    for (int k = 0; k < t; k++) {
        int xl = clampi(x1 + k, 0, frame->width - 1);
        int xr = clampi(x2 - k, 0, frame->width - 1);
        int yt = clampi(y1 + k, 0, frame->height - 1);
        int yb = clampi(y2 - k, 0, frame->height - 1);

        for (int x = xl; x <= xr; x++) {
            set_px_rgb(frame, x, yt, r, g, b);
            set_px_rgb(frame, x, yb, r, g, b);
        }
        for (int y = yt; y <= yb; y++) {
            set_px_rgb(frame, xl, y, r, g, b);
            set_px_rgb(frame, xr, y, r, g, b);
        }
    }
}

static void draw_filled_rect(AlprImageU8* frame, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b) {
    x1 = clampi(x1, 0, frame->width - 1);
    y1 = clampi(y1, 0, frame->height - 1);
    x2 = clampi(x2, 0, frame->width - 1);
    y2 = clampi(y2, 0, frame->height - 1);
    if (x2 < x1 || y2 < y1) {
        return;
    }
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            set_px_rgb(frame, x, y, r, g, b);
        }
    }
}

static int get_char_bit(unsigned char ch, int row, int col) {
    if (ch == '-') return 0;
    if (ch >= '0' && ch <= '9') {
        int digit = ch - '0';
        static const unsigned char patterns[][5] = {
            {0x0E, 0x11, 0x13, 0x1D, 0x0E},
            {0x02, 0x06, 0x02, 0x02, 0x07},
            {0x0E, 0x11, 0x02, 0x04, 0x1F},
            {0x1F, 0x02, 0x0E, 0x01, 0x1E},
            {0x04, 0x0C, 0x14, 0x1F, 0x04},
            {0x1F, 0x10, 0x1E, 0x01, 0x1E},
            {0x0E, 0x10, 0x1E, 0x11, 0x0E},
            {0x1F, 0x01, 0x02, 0x04, 0x08},
            {0x0E, 0x11, 0x0E, 0x11, 0x0E},
            {0x0E, 0x11, 0x0F, 0x01, 0x0E}
        };
        if (row >= 0 && row < 5) {
            return (patterns[digit][row] >> (4 - col)) & 1;
        }
    } else if (ch >= 'A' && ch <= 'Z') {
        int letter = ch - 'A';
        static const unsigned char patterns[][5] = {
            {0x0E, 0x11, 0x1F, 0x11, 0x11},
            {0x1E, 0x11, 0x1E, 0x11, 0x1E},
            {0x0E, 0x10, 0x10, 0x10, 0x0E},
            {0x1C, 0x12, 0x11, 0x12, 0x1C},
            {0x1F, 0x10, 0x1E, 0x10, 0x1F},
            {0x1F, 0x10, 0x1E, 0x10, 0x10},
            {0x0F, 0x10, 0x13, 0x11, 0x0F},
            {0x11, 0x11, 0x1F, 0x11, 0x11},
            {0x0E, 0x04, 0x04, 0x04, 0x0E},
            {0x07, 0x02, 0x02, 0x12, 0x0C},
            {0x11, 0x12, 0x1C, 0x12, 0x11},
            {0x10, 0x10, 0x10, 0x10, 0x1F},
            {0x11, 0x1B, 0x15, 0x11, 0x11},
            {0x11, 0x19, 0x15, 0x13, 0x11},
            {0x0E, 0x11, 0x11, 0x11, 0x0E},
            {0x1E, 0x11, 0x1E, 0x10, 0x10},
            {0x0E, 0x11, 0x11, 0x12, 0x0D},
            {0x1E, 0x11, 0x1E, 0x12, 0x11},
            {0x0E, 0x10, 0x0E, 0x01, 0x1E},
            {0x1F, 0x04, 0x04, 0x04, 0x04},
            {0x11, 0x11, 0x11, 0x11, 0x0E},
            {0x11, 0x11, 0x11, 0x0A, 0x04},
            {0x11, 0x11, 0x15, 0x1B, 0x11},
            {0x11, 0x0A, 0x04, 0x0A, 0x11},
            {0x11, 0x0A, 0x04, 0x04, 0x04},
            {0x1F, 0x02, 0x04, 0x08, 0x1F}
        };
        if (letter >= 0 && letter < 26 && row >= 0 && row < 5) {
            return (patterns[letter][row] >> (4 - col)) & 1;
        }
    }
    return 0;
}

static void draw_text_simple(AlprImageU8* frame, const char* text, int x, int y) {
    if (!frame || !text || !frame->data) {
        return;
    }

    int char_spacing = 16;
    int char_width = 10;
    int char_height = 10;
    int scale = 2;

    for (const char* p = text; *p; p++) {
        unsigned char ch = (unsigned char)*p;
        int char_idx = (int)(p - text);
        int x_base = x + char_idx * char_spacing;

        for (int row = 0; row < char_height; row++) {
            for (int col = 0; col < char_width; col++) {
                int bit_row = row / scale;
                int bit_col = col / scale;
                if (get_char_bit(ch, bit_row, bit_col)) {
                    int px = x_base + col;
                    int py = y + row;
                    if (px >= 0 && px < frame->width && py >= 0 && py < frame->height) {
                        set_px_rgb(frame, px, py, 255, 255, 0);
                    }
                }
            }
        }
    }
}

int alpr_draw_plate_box(
    AlprImageU8* frame,
    const AlprDetection* box,
    const char* text
) {
    if (!frame || !box) {
        return -1;
    }

    int x1 = (int)box->x1;
    int y1 = (int)box->y1;
    int x2 = (int)box->x2;
    int y2 = (int)box->y2;

    draw_rect(frame, x1, y1, x2, y2, 3, 0, 255, 0);

    /* Draw a label background area above the box. */
    int ly2 = y1 - 2;
    int ly1 = ly2 - 20;
    int lx2 = x1 + 150;
    int lx1 = x1;
    draw_filled_rect(frame, lx1, ly1, lx2, ly2, 0, 128, 0);

    /* Draw plate text on the label. */
    if (text && text[0] != '\0') {
        draw_text_simple(frame, text, x1 + 2, ly1 + 3);
    }

    return 0;
}

int alpr_draw_fps(AlprImageU8* frame, float fps) {
    if (!frame) {
        return -1;
    }

    if (fps < 0.0f) {
        fps = 0.0f;
    }
    if (fps > 120.0f) {
        fps = 120.0f;
    }

    int bar_w = 200;
    int bar_h = 12;
    int x1 = 20;
    int y1 = 20;
    int x2 = x1 + bar_w;
    int y2 = y1 + bar_h;

    draw_filled_rect(frame, x1, y1, x2, y2, 40, 40, 40);
    int filled = (int)(bar_w * (fps / 60.0f));
    if (filled > bar_w) {
        filled = bar_w;
    }
    draw_filled_rect(frame, x1, y1, x1 + filled, y2, 255, 220, 0);
    draw_rect(frame, x1, y1, x2, y2, 1, 255, 255, 255);

    return 0;
}
