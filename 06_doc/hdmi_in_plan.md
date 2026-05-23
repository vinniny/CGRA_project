# HDMI-In Live-Input Demo Plan

**Goal**: Professor draws a digit in Microsoft Paint on a laptop. The laptop's
HDMI output goes to the PYNQ-Z2 J10 HDMI-in connector. The CGRA recognises the
digit in real time and shows the prediction on a second monitor connected to
the PYNQ-Z2 J11 HDMI-out connector.

**Why this path** (vs USB webcam): keeps the demo bare-metal. The 3.81× FC
speedup measurement stays uncontaminated by Linux scheduler jitter. No USB
host stack is needed.

## End-to-end signal path

```
┌──────────┐  HDMI cable   ┌──────────────────────────────────────┐  HDMI cable  ┌──────────┐
│ Laptop   │ ─────────────▶│ PYNQ-Z2 (XC7Z020)                    │─────────────▶│ Monitor  │
│ (Paint)  │   640×480     │  J10 in → dvi2rgb → v_tc detect →    │  640×480     │  prediction
│ Win 11   │   60 Hz       │  axi4s_vid_in → color_convert →      │  60 Hz       │  + ROI box
│          │               │  pixel_pack → VDMA S2MM →            │              │  + original
│          │               │  DDR @ 0x1F80_0000                   │              │  frame inset
│          │               │                                      │              │          │
│          │               │  ARM Cortex-A9 (bare-metal):         │              │          │
│          │               │   1. poll VDMA frame-ready           │              │          │
│          │               │   2. crop ROI (laptop's Paint area)  │              │          │
│          │               │   3. BGR→luma + box-filter to 28×28  │              │          │
│          │               │   4. invert (Paint black-on-white →  │              │          │
│          │               │      MNIST white-on-black)           │              │          │
│          │               │   5. CGRA FC1+FC2 inference          │              │          │
│          │               │   6. compose output frame:           │              │          │
│          │               │      original + ROI overlay + result │              │          │
│          │               │   7. VDMA MM2S → J11 HDMI-out        │              │          │
└──────────┘               └──────────────────────────────────────┘              └──────────┘
```

## New IPs to add to the existing Vivado BD

The current `cgra_pynq_base` block design (built by
`scripts/build_cgra_hdmi_pynqz2_clean.tcl`) has the **output side** already.
We append the **input side**:

| New IP | Vendor | Purpose |
|---|---|---|
| `dvi2rgb_0`        | Digilent v1.7  | TMDS-serial to 24-bit RGB recovery; recovers pixel clock from the HDMI cable |
| `v_tc_1`           | Xilinx 6.2     | Second VTC instance, configured as **detector** (not generator) — measures hsync/vsync from the recovered clock |
| `v_axi4s_vid_in_0` | Xilinx 4.0     | Converts RGB parallel to AXIS video stream, aligned to vsync from v_tc |
| `color_convert_1`  | Xilinx HLS 1.0 | RGB pass-through identity matrix (we don't need colour-space conversion; this IP is kept symmetric with the output chain for VDMA stream-width matching) |
| `pixel_pack_0`     | Xilinx HLS 1.0 | Already exists in the BD for the output chain; instantiate a second one for input |
| `axi_vdma_1`       | Xilinx 6.3     | S2MM-only configuration. Writes incoming frames to DDR @ `0x1F80_0000`. 3-frame ring with PARK_PTR. |

## Address map additions

```
0x4302_0000  axi_vdma_1            (S2MM control)
0x43C9_0000  v_tc_1                (detector mode)
0x43CA_0000  color_convert_1
0x43CB_0000  pixel_pack_0 (input)
              dvi2rgb_0 has no AXI-lite control — runtime is automatic from cable plug-in
```

(Spots picked so the existing 0x43Cx range stays contiguous. Verify
no collision with `cgra_pynq_base.tcl` allocations.)

## DDR memory map

```
0x0010_0000 – 0x001F_FFFF   bare-metal ELF + heap
…
0x1F00_0000 – 0x1F0E_0FFF   HDMI-OUT framebuffer  (existing, 921 KB)
0x1F80_0000 – 0x1F8E_0FFF   HDMI-IN  framebuffer  (NEW, 921 KB, 3-frame ring)
0x1FA0_0000 – 0x1FAE_0FFF   HDMI-IN  ring frame 1
0x1FC0_0000 – 0x1FCE_0FFF   HDMI-IN  ring frame 2
```

Each frame is 640 × 480 × 3 bytes = 921,600 bytes = ~900 KB. 3-frame ring
gives the laptop one frame of latency tolerance — good enough for ≤16.7 ms
processing budgets.

Frame pixel order in DDR: **BGR** (low byte = B, mid = G, high = R) per the
project's existing HDMI memory dump convention.

## EDID payload

`dvi2rgb` exposes an 128-byte EDID ROM. We override the default with a payload
advertising **only 640×480 @ 60 Hz**. When the laptop plugs in, Windows reads
this via DDC, auto-negotiates to that single mode, and the user doesn't have
to manually set display resolution.

Payload generation: hand-rolled binary blob committed to
`scripts/edid_640x480.bin`. Loaded into `dvi2rgb_0`'s EDID generic at
elaboration time.

## Bare-metal driver API (`07_sw/baremetal/hdmi_in_bm.h`)

```c
#define HDMI_IN_W   640
#define HDMI_IN_H   480
#define HDMI_IN_BPP 3
#define HDMI_IN_FRAME_BYTES  (HDMI_IN_W * HDMI_IN_H * HDMI_IN_BPP)
#define HDMI_IN_FB_BASE  0x1F800000UL

void hdmi_in_init(uint32_t fb_phys);
int  hdmi_in_frame_ready(void);           /* 1 = a new frame was captured */
const uint8_t *hdmi_in_current_frame(void);
```

## Frame → MNIST API (`07_sw/baremetal/frame_to_mnist.h`)

```c
typedef struct {
    uint32_t x, y;     /* top-left in pixels */
    uint32_t w, h;     /* width / height in pixels */
} hdmi_roi_t;

/* Default ROI: centred 240×240 region inside the 640×480 frame, matching
 * the Paint canvas area when the laptop opens Paint maximised. */
#define HDMI_ROI_DEFAULT  (hdmi_roi_t){.x=200, .y=120, .w=240, .h=240}

/* Downsample + invert + INT16-quantize, ready to feed cnn_fc1_run_group. */
void downsample_roi_to_mnist(const uint8_t *fb,
                              hdmi_roi_t roi,
                              int16_t out28[28*28]);
```

Implementation: for each of 28×28 output pixels, compute the average BGR
luma over the corresponding (roi_w/28) × (roi_h/28) source-pixel block.
Convert BGR → Y using `Y = (66*R + 129*G + 25*B + 128) >> 8` (BT.601
without the +16 offset since we'll invert next). Output `int16_t out = 255 - Y`
to convert Paint's black-on-white to MNIST's white-on-black.

Then scale to the same INT16 range that `sweep_input28[i]` uses (already
INT16, range ~[-128, 127] after a per-image mean subtract — match the
preprocessing pipeline in `cnn_eval/quantize_cgra.py`).

## Demo runtime mode flag

`demo_mnist_hdmi_bm.c` gets a build-time flag `-DLIVE_INPUT` and a runtime
check on a user button (e.g., BTN0 = toggle live mode). When live:

1. Replace `sweep_input28[i]` with the live downsampled frame.
2. Skip the `sweep_labels[i]` accuracy bookkeeping (no ground truth).
3. Draw the ROI box overlay on the **output** framebuffer so the user can
   see what region the CGRA is consuming.
4. Show the prediction with confidence (raw FC2 output max) instead of
   the GT vs PRED comparison.

## LUT-budget risk

Current util: **83.5%** of 53,200 LUTs on XC7Z020. The new input chain adds:

| IP | Rough LUT cost |
|---|---|
| dvi2rgb_0 | ~600 LUTs |
| v_tc_1 (detector) | ~400 |
| v_axi4s_vid_in_0 | ~250 |
| color_convert_1 | ~800 |
| pixel_pack_0 | ~300 |
| axi_vdma_1 (S2MM only) | ~1,200 |
| **Total est.** | **~3,550 LUTs (~6.7% of device)** |

Adding ~6.7% on top of 83.5% lands at **~90.2%**. Should fit, but the
timing report becomes the bigger concern — adding a second clock domain
from the recovered HDMI pixel clock means more synchronizers and CDC
analysis. If timing fails, the fall-back is `scripts/strip_pynq_iops.tcl`
which already strips PMOD/Arduino/RPi IOPs and recovers ~25k LUTs of
headroom (though we're already running on a stripped build).

## Sequencing (3-4 days, parallel where possible)

| Day | Track A (Windows/Vivado) | Track B (WSL2/C code) |
|---|---|---|
| Day 1 AM | Author `scripts/add_hdmi_in_pynqz2.tcl` | Write `hdmi_in_bm.h` + stub `.c` |
| Day 1 PM | Run TCL → check synth completes | Write `frame_to_mnist.{h,c}` standalone tests |
| Day 2 AM | Implementation + bitstream | Wire `-DLIVE_INPUT` into demo |
| Day 2 PM | Bitstream done, copy to repo | Build new ELF |
| Day 3 AM | Silicon: confirm v_tc detector locks, VDMA captures | ROI tuning, threshold tuning |
| Day 3 PM | End-to-end demo with Paint |
| Day 4 | Buffer / debug |

Track A and B run in parallel: SW work can be tested in standalone-host
mode against a saved BMP/RAW frame (no board needed) on Day 1-2.

## Risks and mitigations

| Risk | Mitigation |
|---|---|
| LUT bust | Use `strip_pynq_iops.tcl` to recover headroom |
| Timing fails on dvi2rgb's recovered clock | Drop target Fmax of HDMI chain to 25.175 MHz (640×480 pixel rate); cross-clock to CGRA fabric via async FIFO |
| EDID negotiation flakes | Manual fallback: set laptop display to 640×480 in Windows display settings; document in demo script |
| Paint canvas size mismatch with default ROI | Make ROI adjustable via PS user button (BTN1 = grow, BTN2 = shrink) |
| Inverted polarity / colour swap | First bring-up just dumps raw FB to UART hex for visual inspection; tune in C, not RTL |

## Bring-up checklist

1. [ ] Bitstream synthesises with no failed constraints
2. [ ] `make program` loads new bitstream, PS7 boot survives
3. [ ] Probe `dvi2rgb_0` lock bit via XSDB after laptop plug-in
4. [ ] Probe `v_tc_1` detect register (htotal/vtotal nonzero)
5. [ ] `xsdb mrd 0x1F80_0000 256` shows non-zero data while laptop screens content
6. [ ] Bare-metal `fb_paint`-style host program saves one HDMI-in frame to a BMP for visual sanity check
7. [ ] `demo_mnist_hdmi_bm -live` shows the captured ROI as the 28×28 inset on the output panel
8. [ ] First "0" drawn in Paint is recognised correctly
9. [ ] Stress: rapidly change digit; check no frame-tearing artefacts
10. [ ] Lock + record for thesis revision

## Files added/modified by this work

```
scripts/add_hdmi_in_pynqz2.tcl       NEW   Vivado BD extension
scripts/edid_640x480.bin             NEW   EDID payload for dvi2rgb
01_bench/constrs_pynq_z2.xdc         MOD   J10 HDMI-RX pin LOCs
07_sw/baremetal/hdmi_in_bm.h         NEW   driver API
07_sw/baremetal/hdmi_in_bm.c         NEW   driver implementation
07_sw/baremetal/frame_to_mnist.h     NEW   downsample API
07_sw/baremetal/frame_to_mnist.c     NEW   downsample impl
07_sw/baremetal/demo_mnist_hdmi_bm.c MOD   add live mode
07_sw/baremetal/Makefile             MOD   wire new sources into mnist_hdmi target
06_doc/hdmi_in_plan.md               NEW   this document
```

No RTL source changes — pure block-design + bare-metal additions.
