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

## Accuracy (full sweep, 100 distinct labelled images, same run)

| FC implementation     | argmax accuracy | speedup vs CGRA |
|-----------------------|-----------------|-----------------|
| ARM-VFP-FC (float)    | **99 / 100**    | CGRA 3.96× faster |
| ARM-INT-FC (INT64)    | **94 / 100**    | CGRA 7.93× faster |
| **CGRA-FC** (INT16 tiled) | **86 / 100** | baseline |

All three FC paths consume the **same** `act400` (one ARM-VFP Conv+Pool front
end), so the accuracy gap is purely the FC arithmetic: float (99%) > INT64
(94%) > CGRA INT16-tiled (86%, the documented ~87% CGRA MNIST — INT16
quantization + SPM-auto-inc / result-FIFO per-neuron deltas).

**Defense framing:** the CGRA trades accuracy for throughput — **4–8× faster FC
at 86% accuracy vs the 99% float baseline**, end-to-end on silicon including
DMA + readout overhead.

## ⚠️ IMPORTANT caveat — ARM baseline optimization level

These numbers come from the **Vitis Debug build (`-O0`)** of the live demo (the
visual demo is built Debug). The ARM-INT/ARM-VFP FC loops are therefore
**unoptimized**, which inflates the speedup. The CGRA-FC path is mostly hardware
(clock-bound), so it barely changes with `-O0`; the ARM baselines do.

- **Fair, matched-optimization comparison** (`-O2` ARM, earlier silicon run,
  `demo_audit.md §6`): CGRA-FC ≈ **2.1× vs ARM-INT64**, ≈ **1.3× vs ARM-VFP**.
  (ARM-INT ~3.71 M cyc at -O2 vs ~17.3 M at -O0 — a ~4.7× -O0 penalty.)
- **Demo (`-O0`) figure**: 7.93× / 3.96× — honest for *that build*, but cite it as
  "the live-demo Debug build" and lead with the matched-O2 ~2.1× for rigor.

For the thesis, the defensible headline is **~2.1× at matched -O2** (plus the
perf/W advantage ≥6× and offloading the ARM entirely); the -O0 demo figure is a
secondary "as-demonstrated-live" data point.  To get a fair on-silicon number,
rebuild the demo `-O2` (`app config -set build-config Release`) and re-measure.
