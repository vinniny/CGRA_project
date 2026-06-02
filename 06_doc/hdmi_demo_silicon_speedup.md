# HDMI MNIST Demo — Silicon Speedup Measurement (PYNQ-Z2)

Captured live over UART from the working dual-HDMI demo (`demo_mnist_hdmi_bm`,
HDMI-OUT path, `bitstreams/cgra_hdmi_dual.xsa`) on **PYNQ-Z2 (XC7Z020)**,
2026-06-02. CGRA at FCLK0 = 50 MHz; ARM Cortex-A9 APU at 650 MHz.

## Workload

Identical fully-connected head (FC1 400→64 + FC2 64→10 + argmax) run three ways
on the same `act400` activations (produced by the ARM-VFP Conv+Pool front end):

1. **CGRA-FC** — 4 PE × 16-group INT16 tiled MAC on the CGRA accelerator
   (DMA→SPM, CU loop, result-FIFO readout); cycles include the ARM-side driving
   overhead (DMA setup + poll), i.e. fair wall-clock for the accelerated path.
2. **ARM-INT-FC** — INT64-accumulator integer FC on the A9 (bit-exact to CGRA math).
3. **ARM-VFP-FC** — hardware single-precision float FC on the A9.

## Result (mean over 40 inference frames, ARM CCNT)

| FC implementation     | mean cycles | hex        | speedup (CGRA = 1) |
|-----------------------|-------------|------------|--------------------|
| **CGRA-FC**           |  2,180,561  | 0x002145D1 | **1.00×**          |
| ARM-INT-FC (INT64)    | 17,292,252  | 0x0107DBDB | CGRA **7.93×** faster |
| ARM-VFP-FC (float)    |  8,644,381  | 0x0083E71D | CGRA **3.96×** faster |

**Headline:** the CGRA accelerates the dense FC head **7.9× over the INT64-ARM
baseline and 4.0× over the hardware-float (VFP) ARM baseline**, end-to-end and
including DMA/readout overhead, on silicon.

CGRA argmax accuracy on the labelled sweep images: **35/40** (consistent with the
~87% MNIST sweep validated earlier; the accuracy-of-record path is ARM-VFP
Conv+Pool feeding the CGRA FC).

(Speedup ratios are independent of the CCNT prescaler / exact APU frequency.)
