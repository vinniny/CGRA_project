/* arm_cnn.h — ARM scalar reference for the FULL MNIST CNN.
 *
 *   28x28 uint8 input
 *     -> normalize: (val/255 - 0.1307) / 0.3081       (matches torchvision)
 *     -> Conv3x3 (1->8 channels, no padding)          -> 26x26x8 float
 *     -> ReLU
 *     -> MaxPool 2x2                                  -> 13x13x8
 *     -> Conv3x3 (8->16 channels, no padding)         -> 11x11x16
 *     -> ReLU
 *     -> MaxPool 2x2                                  -> 5x5x16 = 400
 *     -> per-image quantize to INT32 (matches sweep_act400 format)
 *     -> FC1 (400->64) + bias + ReLU + per-image quantize  (arm_fc.c)
 *     -> FC2 (64->10) + bias                          (arm_fc.c)
 *     -> argmax => predicted digit 0..9
 *
 * The Conv/Pool/ReLU layers use FLOAT32 throughout (Cortex-A9 VFPv3) to
 * mirror golden_sim.py::infer_one — guaranteed bit-identical to the
 * Python golden, no quantization noise in the reference.
 *
 * Weights are dequantized from the INT16-quantized `mnist_weights_conv.bin`
 * blob (loaded into `.cnn_conv_spm` section by `demo_mnist_conv_weights.S`):
 *   bytes [   0..  143]  Conv1 INT16 weights  [8, 3, 3, 1] (OKHWI layout)
 *   bytes [ 144..  175]  Conv1 INT32 biases   [8]
 *   bytes [ 176..2479]   Conv2 INT16 weights  [16, 3, 3, 8]
 *   bytes [2480..2543]   Conv2 INT32 biases   [16]
 *
 * Scale factors from `mnist_weights_scale.h`:
 *   MNIST_CONV1_SCALE_W_F = 0.00003041f  (per-tensor symmetric)
 *   MNIST_CONV2_SCALE_W_F = 0.00004060f
 *   w_float = w_int16 * scale_w
 *   b_float = b_int32 * scale_w  (bias was stored in accumulator units)
 */
#ifndef ARM_CNN_H
#define ARM_CNN_H

#include <stdint.h>

#include "arm_fc.h"   /* reuse existing FC1+FC2 + argmax */

#define ARM_CNN_INPUT_W   28
#define ARM_CNN_INPUT_H   28
#define ARM_CNN_INPUT_N   (ARM_CNN_INPUT_W * ARM_CNN_INPUT_H)  /* 784 */

/* Compute full CNN argmax for one MNIST input.
 *   input_uint8: 784-byte raw image (matches sweep_input28[i]).
 *   fc1_w, fc2_w: same INT16-packed FC weight blobs the CGRA uses (cnn_spm_start).
 *   out_act400 (optional, may be NULL): if non-NULL, receives the quantized
 *     INT32 400-element post-pool2 activation — useful for downstream CGRA
 *     FC validation. Layout matches the existing `sweep_act400` format.
 *
 * Returns the predicted digit (0..9) or -1 on internal error. */
int arm_cnn_run(const uint8_t input_uint8[ARM_CNN_INPUT_N],
                const uint32_t fc1_w[ARM_FC1_N_OUT * ARM_FC1_N_IN],
                const uint32_t fc2_w[ARM_FC2_N_OUT * ARM_FC2_N_IN],
                int32_t out_act400[ARM_FC1_N_IN] /* may be NULL */);

#endif /* ARM_CNN_H */
