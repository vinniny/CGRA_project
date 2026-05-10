/* demo_mnist_weights.S — Embed mnist_weights_spm.bin into .cnn_spm section.
 *
 * linker_cnn.ld maps this section to DDR at 0x00200000.
 * demo_mnist_smoke.c uses cnn_spm_start for the FC1+FC2 weight blob:
 *   FC1: bytes [0 .. 64*400*4 - 1]  = [0 .. 102399]
 *   FC2: bytes [102400 .. 104959]
 */
    .section .cnn_spm, "a"
    .global cnn_spm_start
    .global cnn_spm_end

cnn_spm_start:
    .incbin "../cnn_eval/mnist_weights_spm.bin"
cnn_spm_end:
