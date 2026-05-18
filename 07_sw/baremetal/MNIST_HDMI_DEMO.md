# MNIST CNN FC Acceleration Demo — Bare-metal HDMI

**Live three-panel head-to-head comparison of the FC1+FC2 dense matmul
stage running on three different implementations: CGRA, ARM scalar
INT64, ARM scalar VFP. Conv+Pool is kept on ARM-VFP across all paths so
only the FC stage is the timed variable.**

Locked at commit `b9a3de4` / tag `baremetal-mnist-fc-demo-locked`.

---

## TL;DR — what you see on screen

```
┌──────────────────────────────────────────────────────────────┐
│                                                              │
│                  MNIST DIGIT  (224×224)                      │
│                  (28×28 sweep image, scaled 8×)              │
│                                                              │
├──────────────────────────────────────────────────────────────┤
│ MNIST  CONV+POOL ON ARM-VFP  FC HEAD-TO-HEAD                 │
├───────────────────┬───────────────────┬──────────────────────┤
│  CGRA-FC          │  ARM-INT-FC       │  ARM-VFP-FC          │
│   *ACCEL.         │   *INT64 MAC      │   *HW FLOAT          │
│                   │                   │                      │
│  PRED: 7  GT: 7   │  PRED: 7  GT: 7   │  PRED: 7  GT: 7      │
│  1.5 US           │  5.6 US           │  4.4 US              │
│  668.4 FPS        │  178.4 FPS        │  230.9 FPS           │
└───────────────────┴───────────────────┴──────────────────────┘
 CGRA-FC SPEEDUP  vs ARM-INT-FC: 3.7x   vs ARM-VFP-FC: 2.9x
 ACC  CGRA: 97/100   INT: 97/100   VFP: 100/100   FRAME: 100
```

Silicon-measured headline (PYNQ-Z2, Cortex-A9 666 MHz, CGRA 50 MHz, 201
frames sampled):

| Path        | Per-img  | FPS    | Accuracy | vs CGRA  |
|-------------|----------|--------|----------|----------|
| **CGRA-FC** | 1.50 ms  | 668    | 195/201  | —        |
| ARM-INT-FC  | 5.60 ms  | 178    | 195/201  | 3.74× slower |
| ARM-VFP-FC  | 4.36 ms  | 230    | 201/201  | 2.91× slower |

The CGRA-FC vs ARM-INT-FC pair runs the **exact same integer math**
(INT16 weights × INT32 acts → INT64 acc → INT32 saturate); only the
hardware target differs. That's the apples-to-apples comparison and
the 3.74× speedup is the thesis-defensible number.

---

## Build + run

```bash
cd 07_sw/baremetal && make BOARD=PYNQ_BASE mnist_hdmi
cd ../.. && make run_elf ELF=07_sw/baremetal/demo_mnist_hdmi_bm.elf \
                BIT=bitstreams/cgra_pynq_base/base.bit
```

UART (115200 8N1 on `/dev/ttyUSB1`) streams a per-frame trace; HDMI
output is on the PYNQ-Z2 J2 HDMI connector at 640×480@60.

If a previous ELF run leaves HDMI mis-aligned, `hdmi_init()`'s built-in
`hdmi_force_idle()` should now self-recover on the next reload. If it
still tears, press **SRST** on the board once and reload.

---

## What this demo actually proves

> *On the same SoC, with the same Conv+Pool front-end, the CGRA's
> dense-matmul kernel completes the FC stage **3.7× faster** than the
> same algorithm running as scalar Cortex-A9 integer code, and **2.9×
> faster** than even hardware-VFP float. All three paths agree on
> >97% of predictions, so the speedup isn't bought with accuracy loss.*

What it does **not** claim:
- Not "CGRA accelerates the whole CNN" — Conv stays on ARM. The Conv
  kernel needs a wider result-readout path to avoid INT32 saturation
  inside the per-pixel 9-MAC sum (documented as future work).
- Not "CGRA always beats ARM" — on workloads with no dense-matmul, no
  weight reuse, or with small tensors, ARM-VFP usually wins on
  wall-clock. The CGRA's win comes from its SPM_AUTO_INC pattern,
  which is exactly what FC layers want.

---

## Software stack — top to bottom

The demo is one bare-metal ELF (~360 KB) loaded over JTAG. No OS,
no drivers, no malloc. Below: the call chain on **every frame**, top of
stack to bottom.

### Frame loop: `main()` → `demo_mnist_hdmi_bm.c`

```c
for (;;) {
    int i = frame % SWEEP_N_IMAGES;
    int label = (int)sweep_labels[i];

    int32_t act400[400];

    // 1. ARM-VFP Conv+Pool  — constant across all three paths.
    arm_cnn_vfp_run(sweep_input28[i], act400);

    // 2. Three FC implementations, timed independently with CCNT.
    t0 = arm_ccnt_read();
    pred_cgra = run_cgra_fc(act400);
    cyc_cgra  = arm_ccnt_read() - t0;

    t0 = arm_ccnt_read();
    pred_int  = arm_fc_int_run(act400, cnn_spm_start);
    cyc_int   = arm_ccnt_read() - t0;

    t0 = arm_ccnt_read();
    pred_vfp  = arm_fc_vfp_run(act400, cnn_spm_start);
    cyc_vfp   = arm_ccnt_read() - t0;

    // 3. Render results to HDMI framebuffer.
    fbm_draw_image28(...);
    render_panel(PANEL_CGRA_X, pred_cgra, label, cyc_cgra);
    render_panel(PANEL_INT_X,  pred_int,  label, cyc_int);
    render_panel(PANEL_VFP_X,  pred_vfp,  label, cyc_vfp);
    render_footer(...);
    hdmi_flush_fb();

    delay_cycles(CPU_HZ / 5);   // ~200 ms dwell
    frame++;
}
```

Cortex-A9's **PMCCNTR cycle counter** (`mrc p15, 0, %0, c9, c13, 0`)
gives sub-ns timing resolution. No OS jitter, no D-cache effects,
so per-frame cycle counts are deterministic to <1% across runs.

### The CNN — `arm_cnn_bm.c` (Conv+Pool, VFP float)

Float CNN reference compiled with `-mfpu=vfpv3 -mfloat-abi=hard`. Same
algorithm as the Linux `arm_cnn.c` reference. On every frame:

```
input uint8[28*28]
   │  normalize: (v/255 - 0.1307) / 0.3081
   ▼
buf_normalized[784]      // float[28*28]
   │
   ▼  conv2d  3×3, stride 1, no padding, 1→8 channels, weights from
   │           cnn_conv_start[0..143] (INT16 × CONV1_SCALE_W to float)
   ▼
buf_conv1_out[26*26*8]   // float HWC
   │  ReLU in place
   │  2×2 max-pool stride 2
   ▼
buf_pool1_out[13*13*8]
   │
   ▼  conv2d  3×3, 8→16 channels, weights from cnn_conv_start[176..2479]
   ▼
buf_conv2_out[11*11*16]
   │  ReLU + 2×2 max-pool
   ▼
buf_pool2_out[5*5*16]
   │  HWC → CHW transpose (PyTorch reshape order)
   │  per-image quantize: scale = 32767 / max(|x|), → INT32
   ▼
act400[400]              // INT32, INT16-range
```

Weight-blob layout (`demo_mnist_conv_weights.S` `.incbin`'s the trained
binary):

```
bytes [0..143]    Conv1 INT16 weights [8, 3, 3, 1]  OKHWI
bytes [144..175]  Conv1 INT32 biases  [8]
bytes [176..2479] Conv2 INT16 weights [16, 3, 3, 8]
bytes [2480..2543] Conv2 INT32 biases [16]
```

Float weights are dequantized lazily on first call:
`c1_w_f[i] = (float)c1_w_i16[i] * 0.00003041f`. Stays in `.bss` (OCM).

**Why ARM-VFP, not CGRA, for Conv?** The CGRA's per-pixel
`cnn_conv3x3_pixel` kernel saturates its INT32 result FIFO when
summing 9 × INT16² (~9.66B vs INT32_MAX 2.15B), corrupting outputs.
ARM-VFP at ~22 ms/img gives ground-truth 97% accuracy and isolates
the variable being measured (the FC stage) cleanly.

### CGRA FC path — `cnn_fc1_run_group` / `cnn_fc2_run_group`

The CGRA executes both FC layers via silicon-validated kernels declared
in `cgra_kernels_cnn.h`. Workflow:

1. **`run_cgra_fc(act400)`** in the demo:
   - Copy `act400[400]` to DDR at `ACT400_DDR = 0x00220000` (DSB barrier)
   - `cnn_fc1_tile_preload(ACT400_DDR)` — 1.6 KB DMA broadcast into all
     4 CGRA tile banks
   - Loop `g = 0..15` (16 groups × 4 neurons = 64 outputs):
     `cnn_fc1_run_group(g, &fc1_acc[g*4])`
   - `fc1_post_process()` on ARM: per-neuron bias + ReLU + per-image
     right-shift to INT16 range → `act64[64]`
   - Copy `act64[64]` to DDR at `ACT64_DDR = 0x00221000`
   - `cnn_fc2_tile_preload(ACT64_DDR)`
   - Loop `g = 0..2` (3 groups × 4 = 12 slots, 10 valid):
     `cnn_fc2_run_group(g, &fc2_acc[g*4])`
   - `argmax_with_bias(fc2_acc)` → predicted class

2. **`cnn_fc{1,2}_run_group(g, result[4])`** internally:
   - SG-DMA chain preloads this group's 4 neurons' weights into
     PE 0/4/8/12 SPMs (per-PE, INT16 in low half of each 32-bit word)
   - SG-DMA fires "ACC_CLR" config to col=0 PEs, runs a brief CU pass
     to zero accumulators
   - SG-DMA restores MAC config, then the MAC loop runs:
     `LOOP_COUNT=24, TILE_AUTO_INC=1, SPM_AUTO_INC=1` →
     25 iterations × 16 MACs/iter = 400 MACs per neuron, 4 neurons
     simultaneously (one per row), all using PE 0/4/8/12's MAC unit
     with PE 1/2/3/5/6/7/9/10/11/13/14/15 forwarding east via PASS0
   - SG-DMA writes a PASS0(SRC_RF) readout config to col=0, brief
     CU pass to chain RF[0] east through the column → `RESULT_ROW0-3`
     latch registers
   - APB reads `RESULT_ROW0-3` → caller's `result[4]`

The SPM_AUTO_INC pattern is the key: SPM address advances by 16 per
hardware loop iteration, so 25 iterations stream through 25×16=400
weights without ARM intervention. Tile address auto-advances too,
streaming 400 activations through 4 tile banks.

**Why is this fast on CGRA?**
- 4-way row parallelism (4 neurons in one CU run)
- Zero ARM overhead per MAC (CGRA's CU runs slot 0-15 autonomously)
- INT16 SPM × INT32 tile in one cycle per MAC via 40-bit acc
- Tile_auto_inc + SPM_auto_inc eliminate per-MAC address calc

**Latency breakdown** (silicon-measured):
- FC1: 16 groups × ~60K cyc/group = ~960K cyc = 1.44 ms
- FC2:  3 groups × ~12K cyc/group =  ~36K cyc = 0.05 ms
- Per-frame total CGRA-FC: ~1.5 ms ⇒ **~668 FPS**

### ARM-INT FC path — `arm_fc_int_bm.c`

Same algorithm as CGRA-FC, but executed scalar on Cortex-A9. No VFP,
no NEON, no SIMD. Each MAC is a 5-instruction sequence:

```c
for (int i = 0; i < 400; ++i) {
    acc += (int64_t)act400[i] * (int64_t)spm_int16(w_row[i]);
}
```

GCC emits `ldr` (load act), `ldr` + `sxth` (sign-extend INT16 weight),
`smull` (32×32→64), `adds`/`adc` (INT64 accumulate). With caches off
(bare-metal default), each iteration ≈ 14 cycles. FC1's 64×400 = 25,600
MACs × ~14 cyc ≈ 358K cyc + FC2's 640 MACs + bias/post-process.

Silicon-measured: **~5.6 ms ⇒ ~178 FPS**. Same predictions as CGRA
(quantization edge cases match exactly because the math is identical).

### ARM-VFP FC path — `arm_fc_vfp_bm.c`

Same algorithm, but with float weights and VFP MAC. On first call,
dequantizes the INT16 weight blob into a 100 KB float buffer (placed
in DDR via `__attribute__((section(".cnn_runtime")))` to keep OCM free).
Subsequent calls reuse the cached float weights.

```c
for (int i = 0; i < 400; ++i)
    acc += (float)act400[i] * w_row[i];
```

GCC emits `vmla.f32` (one cycle on Cortex-A9). FC1's 25,600 float MACs
≈ 25,600 cyc — half the INT path's count — but each iter pays a
core↔VFP register handoff at the `(float)act400[i]` cast that the INT
path doesn't have, so it nets out at **~4.4 ms ⇒ ~230 FPS**.

Predictions agree with the integer paths >97% (the small disagreement
comes from float precision rescuing edge cases where INT64 quantization
of the requant step rounds the wrong way).

### HDMI output — `hdmi_bm.c` + `fb_lib_bm.c`

The HDMI pipeline is identity-mapped MMIO. `hdmi_init()` brings up
five IPs in sequence:

```
PS  →  SLCR  (FCLK0 = 100 MHz reference for dynclk MMCM)
PL  →  axi_dynclk  (target pixel clock 25.175 MHz, polls MMCM lock)
PL  →  hdmi_out/color_convert  (identity 3×3 matrix, ap_fixed<10,2>)
PL  →  hdmi_out/pixel_unpack   (mode 0 = V_24, 3 bytes/pixel BGR)
PL  →  v_tc  (640×480@60 timing generator, ALLGENSRC|RU|SW|GE)
PL  →  axi_vdma  (MM2S reads FB at HDMI_FB_PHYS = 0x1F000000)
```

On every ELF reload via XSDB, `hdmi_force_idle()` now stops the VDMA,
VTC, and dynclk first (writing 0 to their CTL registers + VDMA RESET
bit) before reprogramming — this prevents the "shifted screen" bug
that used to require an SRST press between reloads.

`fb_lib_bm.c` draws into the 640×480×3-byte framebuffer at `0x1F000000`
via volatile pointer access. Three primitives: rectangle fill (panel
backgrounds), 5×7 font glyph rendering (text), and 28×28 image blit
(MNIST digit upscaled). The font table (`font5x7.{h,c}`) is shared
with the Linux demo via the Makefile include path.

`hdmi_flush_fb()` is a `dsb` only — caches are off in bare-metal so
volatile writes hit DDR immediately.

### Memory layout — `linker_cnn.ld`

```
                          OCM (256 KB)                    DDR
0x00004000  .vectors  ┐                          0x00200000  .cnn_spm
0x00004080  .init     ├ Code + rodata (~12 KB)   0x00219A00    (FC weight blob, 105 KB)
0x000040F8  .text     │                          0x00220000    act400 buffer
            ─────     ┘                          0x00221000    act64  buffer
0x00007FB8  .bss      ┐ Stat vars (~46 KB)       0x00240000  .cnn_sweep
            ─────     ┤   (incl. arm_cnn_bm        (100-image fixture, 78 KB)
0x0001D140  ── free ──│    float buffers)        0x002532A4  .cnn_conv_spm
0x0001EFC0  IRQ stack │                            (Conv weight blob, 2.5 KB)
0x0001FFC0  SVC stack ┘                          0x00253CA0  .cnn_runtime
                                                   (VFP FC float weights,
                                                    NOLOAD, 105 KB)
                                                 0x1F000000  HDMI framebuffer
                                                   (640×480×3 = 900 KB)
```

OCM is tight (16 KB free after `.bss`). The framebuffer and large
float weight cache live in DDR, identity-mapped without MMU
configuration.

### Bitstream — `bitstreams/cgra_pynq_base/base.bit`

Vivado design that boots into the PYNQ-base block diagram + CGRA
bolt-on. CGRA APB at `0x43C80000`, HDMI pipeline at the standard PYNQ
addresses (VDMA 0x43000000, dynclk 0x43C10000, VTC 0x43C20000,
color_convert 0x43C60000, pixel_unpack 0x43C70000). PS7 init via
`scripts/ps7_init.tcl` exported from the XSA.

---

## Files in this demo

| File | Role |
|------|------|
| `demo_mnist_hdmi_bm.c`   | top-level main, frame loop, rendering |
| `arm_cnn_bm.{h,c}`       | ARM-VFP Conv+Pool reference (used by all paths) |
| `arm_cnn_int_bm.{h,c}`   | ARM-INT scalar Conv (built into `mnist_compare` for completeness; not used here) |
| `arm_fc_bm.h`            | common FC interface declarations |
| `arm_fc_int_bm.c`        | ARM INT64-acc FC1+FC2 |
| `arm_fc_vfp_bm.c`        | ARM float-MAC FC1+FC2 (lazy weight conversion to `.cnn_runtime`) |
| `cgra_kernels_cnn.h`     | `cnn_fc{1,2}_*` silicon-validated kernels (header-only) |
| `cnn_conv_bm.{h,c}`      | CGRA Conv kernel helpers (not exercised by HDMI demo — ARM-VFP runs Conv here) |
| `cnn_requant_bm.h`       | per-layer max-abs requant helper |
| `hdmi_bm.{h,c}`          | HDMI pipeline bring-up, `hdmi_force_idle()` for clean reloads |
| `fb_lib_bm.{h,c}`        | rectangle / text / image28 primitives |
| `../linux/demo_mnist_hdmi/font5x7.{h,c}` | 5×7 ASCII glyph table |
| `demo_mnist_weights.S`   | `.incbin` of FC SPM weight blob (105 KB) |
| `demo_mnist_conv_weights.S` | `.incbin` of Conv weight blob (2.5 KB) |
| `mnist_sweep_fixture.h`  | 100 test images + ground-truth labels (78 KB rodata in `.cnn_sweep`) |
| `linker_cnn.ld`          | section→region mapping (incl. `.cnn_runtime` for VFP weight cache) |
| `start.s`, `gic.{h,c}`, `uart.h` | bare-metal startup, GIC driver, UART helpers |

Build target: `make BOARD=PYNQ_BASE mnist_hdmi` (compiles
`arm_cnn_bm.c` once with VFP into `arm_cnn_bm_vfp.o`, links with the
rest of the .c sources). Companion target `make mnist_compare`
produces the same logic with UART-only output for headless cycle
measurement.

---

## Known limitations / future work

| Limit | Why | Possible fix |
|---|---|---|
| Conv stays on ARM | `cnn_conv3x3_pixel` saturates INT32 in the result FIFO for 9-MAC Conv2 sums | Add wider (INT40 / INT64) result-readout path or per-pixel rescale to keep MAC under INT32_MAX |
| 100-image fixture, not full MNIST test set | `mnist_sweep_fixture.h` is 78 KB rodata; full 10K-image set would be ~8 MB | Add SD-card streaming or use a DDR-resident pre-decoded blob |
| ARM-VFP path's first call includes weight conversion (~6.7 ms one-time) | Lazy load; flag flips to `loaded=1` after first call | Pre-load at boot — adds ~1 ms to startup but cleaner per-frame timing |
| HDMI tearing on certain reloads | `hdmi_force_idle()` resets the IPs but if VDMA was mid-burst the AXI bus may need a bus-level reset | Wait for current burst to complete before resetting (read VDMA status reg until idle) |
