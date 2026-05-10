#ifndef LCD_MODES_H_
#define LCD_MODES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char *label;
    unsigned int width;
    unsigned int height;
    double freq;          /* MHz pixel clock */
    unsigned int hps;     /* hsync start */
    unsigned int hpe;     /* hsync end */
    unsigned int hmax;    /* total - 1 */
    unsigned int hpol;
    unsigned int vps;     /* vsync start */
    unsigned int vpe;     /* vsync end */
    unsigned int vmax;    /* total - 1 */
    unsigned int vpol;
} VideoMode;

/* Keep the same style as the Digilent examples. */
static const VideoMode VMODE_640x480 = {
    .label = "640x480@60",
    .width = 640, .height = 480, .freq = 25.175,
    .hps = 656, .hpe = 752, .hmax = 799, .hpol = 0,
    .vps = 490, .vpe = 492, .vmax = 524, .vpol = 0,
};

static const VideoMode VMODE_800x600 = {
    .label = "800x600@60",
    .width = 800, .height = 600, .freq = 40.0,
    .hps = 840, .hpe = 968, .hmax = 1055, .hpol = 1,
    .vps = 601, .vpe = 605, .vmax = 627, .vpol = 1,
};

static const VideoMode VMODE_1024x600 = {
    .label = "1024x600@60",
    .width = 1024, .height = 600, .freq = 51.2,
    .hps = 1048, .hpe = 1184, .hmax = 1343, .hpol = 1,
    .vps = 603, .vpe = 613, .vmax = 634, .vpol = 1,
};

static const VideoMode VMODE_1024x768 = {
    .label = "1024x768@60",
    .width = 1024, .height = 768, .freq = 65.0,
    .hps = 1048, .hpe = 1184, .hmax = 1343, .hpol = 0,
    .vps = 771, .vpe = 777, .vmax = 805, .vpol = 0,
};

static const VideoMode VMODE_1280x720 = {
    .label = "1280x720@60",
    .width = 1280, .height = 720, .freq = 74.25,
    .hps = 1390, .hpe = 1430, .hmax = 1649, .hpol = 1,
    .vps = 725, .vpe = 730, .vmax = 749, .vpol = 1,
};

#ifdef __cplusplus
}
#endif

#endif
