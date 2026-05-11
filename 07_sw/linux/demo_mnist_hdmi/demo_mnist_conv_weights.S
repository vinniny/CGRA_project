/* demo_mnist_conv_weights.S — embed mnist_weights_conv.bin as
 * cnn_conv_start..cnn_conv_end. Mirrors the demo_mnist_weights.S
 * pattern used for the FC SPM blob.
 *
 * Layout (per quantize_cgra.py::emit_conv_bin):
 *   bytes [   0..  143]  Conv1 INT16 weights [8, 3, 3, 1]  OKHWI
 *   bytes [ 144..  175]  Conv1 INT32 biases  [8]   (accumulator units)
 *   bytes [ 176..2479]   Conv2 INT16 weights [16, 3, 3, 8]
 *   bytes [2480..2543]   Conv2 INT32 biases  [16]
 *   Total: 2544 bytes.
 *
 * The section name is arbitrary for the Linux build — gets folded into
 * default rodata regardless. */
    .section .cnn_conv_spm, "a"
    .global cnn_conv_start
    .global cnn_conv_end

cnn_conv_start:
    .incbin "../../cnn_eval/mnist_weights_conv.bin"
cnn_conv_end:
