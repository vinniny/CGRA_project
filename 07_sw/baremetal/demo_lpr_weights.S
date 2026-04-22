/* demo_lpr_weights.S — Embed golden_weights.bin into the .lpr_weights section.
 *
 * The linker_lpr.ld script maps this section to DDR at 0x00800000.
 * demo_lpr.c casts lpr_weights_start to (const GoldenWeights *) — valid
 * because the binary is the raw GoldenWeights struct in field order:
 *   conv1_w [72 float32] + conv1_b [8] + conv2_w [1152] + conv2_b [16]
 *   + fc_w [23520] + fc_b [30]  = 24798 float32 = 99192 bytes.
 */
    .section .lpr_weights, "a"
    .global lpr_weights_start
    .global lpr_weights_end

lpr_weights_start:
    .incbin "../lprnet_eval/golden_weights.bin"
lpr_weights_end:

#ifdef USE_CGRA_INFER
    .section .lpr_weights_int16, "a"
    .global lpr_weights_int16_start
    .global lpr_weights_int16_end

lpr_weights_int16_start:
    .incbin "../lprnet_eval/golden_weights_int16.bin"
lpr_weights_int16_end:
#endif
