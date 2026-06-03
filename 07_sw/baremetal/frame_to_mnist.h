/* =============================================================================
 * frame_to_mnist.h — Convert a 640×480 BGR HDMI-input frame to a 28×28 INT16
 * MNIST input tensor matching the format used by cnn_eval/quantize_cgra.py.
 *
 * The professor draws a digit in Paint. Paint renders black ink on a white
 * canvas — the opposite polarity of MNIST. We invert in software so the
 * existing CGRA weights work without retraining.
 * ============================================================================= */
#ifndef FRAME_TO_MNIST_H
#define FRAME_TO_MNIST_H

#include <stdint.h>

/* Region of interest within the 640×480 frame, in pixels. */
typedef struct {
    uint32_t x;     /* top-left x (0..639) */
    uint32_t y;     /* top-left y (0..479) */
    uint32_t w;     /* width  in pixels (must be a multiple of 28) */
    uint32_t h;     /* height in pixels (must be a multiple of 28) */
} hdmi_roi_t;

/* Default ROI for a 1280×720 HDMI source with Paint maximized: 560×560
 * centred at (640, 360). Crops out title bar / ribbon at the top and
 * status bar at the bottom; covers most of the canvas area. Ratio
 * 560/28 = 20 → box-filter 20×20 source pixels per output pixel.
 *
 * If you want a smaller / different crop region (e.g. a small Paint
 * window not maximized), override per-call. */
/* 1280×720 source (EDID-forced 720p).  576×576 square centred at the frame
 * centre (640,360): x=(1280−576)/2=352, y=(720−576)/2=72.  Draw a big digit in
 * the MIDDLE of the laptop screen.  576/28 ≈ 20.6 → ~20×20 box-filter per
 * output pixel.  (Old 768² @ (576,156) was centred for the 1080p no-EDID era.) */
/* Silicon 2026-06-03: the laptop letterboxes its desktop into the 720p frame —
 * rows 0..~100 are black; content spans ~100..720.  Centre crop on that:
 * y = 100 + (620-576)/2 = 122. */
#define HDMI_ROI_DEFAULT  ((hdmi_roi_t){.x = 352, .y = 122, .w = 576, .h = 576})

/**
 * Downsample a region of the captured frame into a 28×28 UINT8 tensor.
 * The output format matches `sweep_input28[]` in mnist_sweep_fixture.h —
 * a plain `uint8_t[784]` with 0 = MNIST-black background, 255 = white-ink
 * digit — which `arm_cnn_vfp_run()` consumes directly.
 *
 * Pipeline:
 *   1. For each of 784 output pixels, compute the BGR average over the
 *      (w/28)×(h/28) source-pixel block.
 *   2. Convert to luma:  Y = (77*R + 150*G + 29*B + 128) >> 8.
 *                         (full-range BT.601, coeffs sum to 256 so white→255)
 *   3. Invert:           out = 255 - Y.
 *      (Paint draws black ink on a white canvas; MNIST is white digit
 *      on black background — invert in software so the existing CGRA
 *      weights work without retraining.)
 *
 * @param fb      base address of the 640×480 BGR frame (from
 *                hdmi_in_current_frame()).
 * @param roi     region of interest within the frame.
 * @param out784  output buffer of 28*28 = 784 uint8_t values.
 */
void downsample_roi_to_mnist(const uint8_t *fb,
                              hdmi_roi_t      roi,
                              uint8_t         out784[28*28]);

#endif /* FRAME_TO_MNIST_H */
