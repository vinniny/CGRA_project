/* cnn_conv_bm.h — bare-metal full CNN forward pass for MNIST.
 *
 * Pipeline (B4 pixel-by-pixel):
 *   uint8 input -> int32 normalize
 *   -> Conv1 (1->8, 28x28 -> 26x26): pixel-by-pixel cnn_conv3x3_pixel calls
 *   -> ReLU + 2x2 MaxPool (ARM-side)
 *   -> Conv2 (8->16, 13x13 -> 11x11): same pattern
 *   -> ReLU + 2x2 MaxPool (ARM-side)
 *   -> CHW-flatten + per-image quantize to INT16-range INT32 -> act400[400]
 *
 * The caller then feeds act400 to FC1 via the existing cnn_fc1_* path.
 *
 * Pool + ReLU + quantize are kept on ARM: they're tiny (compared to Conv)
 * and require no CGRA setup. Doing them on ARM keeps the CGRA invocations
 * focused on the MAC-heavy Conv loops where the speedup lives.
 */
#ifndef CNN_CONV_BM_H
#define CNN_CONV_BM_H

#include <stdint.h>

/* Input/output tensor sizes (no padding, stride 1 conv; stride 2 pool). */
#define CONV1_IN_H   28
#define CONV1_IN_W   28
#define CONV1_IN_C   1
#define CONV1_OUT_H  26
#define CONV1_OUT_W  26
#define CONV1_OUT_C  8
#define POOL1_OUT_H  13
#define POOL1_OUT_W  13
#define CONV2_IN_H   POOL1_OUT_H
#define CONV2_IN_W   POOL1_OUT_W
#define CONV2_IN_C   CONV1_OUT_C
#define CONV2_OUT_H  11
#define CONV2_OUT_W  11
#define CONV2_OUT_C  16
#define POOL2_OUT_H  5
#define POOL2_OUT_W  5
#define POOL2_OUT_N  (POOL2_OUT_H * POOL2_OUT_W * CONV2_OUT_C)  /* 400 */

/* Buffer addresses in DDR for inter-layer activations and CGRA staging.
 * (Co-located with the existing fixture-data region at 0x002xxxxx.)     */
#define CONV_INPUT_DDR     0x00280000UL  /* int32[784] normalized input */
#define CONV1_OUT_DDR      0x00281000UL  /* int32[26*26*8] = 21632 B */
#define POOL1_OUT_DDR      0x00287000UL  /* int32[13*13*8] = 5408 B */
#define CONV2_OUT_DDR      0x00288800UL  /* int32[11*11*16] = 7744 B */
#define POOL2_OUT_DDR      0x0028A800UL  /* int32[5*5*16] = 1600 B */
#define CONV_WBUF_DDR      0x0028B000UL  /* 16 words = 64 B (cnn_conv3x3_pixel weights) */
#define CONV_INBUF_DDR     0x0028B040UL  /* 16 words = 64 B (cnn_conv3x3_pixel inputs) */
#define CONV_STAGING_DDR   0x0028B080UL  /* 64 B scratch */

/* Run the full Conv1+Pool1+Conv2+Pool2 path on CGRA + ARM.
 *   input_uint8: raw 28x28 image (e.g. sweep_input28[i]).
 *   act400_out:  the 400-element CHW-flattened post-pool2 activation
 *                in INT32 (sweep_act400-compatible format) for FC1.
 * Returns 0 on success, -1 on CGRA timeout. */
int cnn_full_inference(const uint8_t input_uint8[CONV1_IN_H * CONV1_IN_W],
                       int32_t       act400_out[POOL2_OUT_N]);

#endif /* CNN_CONV_BM_H */
