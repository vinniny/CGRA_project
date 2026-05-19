# A CGRA-Based Accelerator with Multicast Routing for Edge CNN Inference on Zynq-7000

Senior Design Project · Department of Electronics · Ho Chi Minh City University of Technology · May 2026

**Authors**

- Huynh Pham Anh Duy — 2051095
- Trieu Thanh Vinh — 2213980

**Supervisor**: Assoc. Prof. PhD. Truong Quang Vinh

---

## Overview

This project implements a 4×4 Coarse-Grained Reconfigurable Array (CGRA)
accelerator on the Xilinx Zynq-7000 XC7Z020 SoC (PYNQ-Z2 board). The CGRA
offloads the fully-connected (FC) stage of CNN inference from the
Cortex-A9 to a reconfigurable mesh of processing elements with multicast
routing.

The case study is MNIST handwritten digit recognition. Conv+Pool runs on
the ARM in software; FC1 (400→64) and FC2 (64→10) run on the CGRA. The
result is a measured FC-stage speedup over the ARM software baseline at
competitive accuracy.

## Measured Results

All numbers verified on silicon (PYNQ-Z2, XC7Z020) and via `make sim`
on Cadence Xcelium 20.09 on 2026-05-18.

| Metric | Value |
|---|---|
| FC-stage speedup (CGRA vs ARM-INT) | 3.81× (5.52 ms → 1.45 ms) |
| Per-image throughput | 665 FPS (CGRA-FC) vs 180 FPS (ARM-INT) vs 235 FPS (ARM-VFP) |
| Top-1 accuracy on 2,745-frame live test | 97.0% (CGRA-FC) · 96.9% (ARM-INT) · 100% (ARM-VFP reference) |
| Achieved Fmax | 50.66 MHz (target 50 MHz, WNS +0.263 ns) |
| LUT utilization | 83.5% of XC7Z020 |
| BRAM utilization | 31.4% |
| DSP utilization | 75.0% |
| Total power | 2.46 W (2.29 W dynamic + 0.17 W static) |
| Simulation tests | 9,148 PASS / 0 FAIL / 0 violations |
| Bare-metal regression | 96 checks PASS across 25 groups |
| ISA opcodes | 21 implemented |

## Hardware

- 4×4 mesh of identical processing elements (16 PEs total)
- Each PE: 3-stage pipeline, 21-opcode ISA, 40-bit saturating accumulator,
  16-entry register file, 1024-word scratchpad, 16-slot configuration BRAM
- INT32 scalar plus INT16×2 and INT8×4 SIMD modes
- Multicast NoC: 5-bit route mask drives single-cycle broadcast to any
  combination of N/E/S/W neighbours
- Two-level hardware loop counters (L1 inner, L2 outer) with zero-overhead
  branching and a watchdog timeout
- Double-buffered tile memory (4 banks × 4096 × 32 bits) for zero-stall
  layer reconfiguration
- Scatter-gather AXI4 DMA with descriptor-chain weight movement

## Software

- Bare-metal stack on Cortex-A9: custom `start.s`, linker scripts, GIC v1
  interrupt driver, UART0 driver, HDMI framebuffer + 5×7 font rendering,
  no operating system, no dynamic allocation
- PetaLinux userspace alternative under `07_sw/linux/` with UIO and
  `/dev/mem` access paths
- Python training and INT16 quantization pipeline under `07_sw/cnn_eval/`

## Repository Layout

```
00_src/        SystemVerilog RTL (13 modules)
01_bench/      Cadence Xcelium testbench (UVM-inspired, layered)
06_doc/        Thesis documentation (active chapters in thesis_ch4/, thesis_ch5/)
07_sw/         Software
  baremetal/   Cortex-A9 bare-metal demos, drivers, regression
  linux/       PetaLinux userspace tools
  driver/      UIO + /dev/mem wrapper
  lib/         Shared C: tiler, golden model, bare-metal shim
  cnn_eval/    MNIST training + quantization (PyTorch)
  lprnet_eval/ LPR training + ONNX export + quantization
  dts/         Device-tree overlays
bitstreams/    Pre-built FPGA bitstreams (silicon-validated)
scripts/       Vivado / Genus / Conformal / XSDB / deploy scripts
Makefile       Top-level orchestration
```

## Build

The top-level `Makefile` drives every flow.

```bash
make sim              # Compile, elaborate, and run all 9,148 simulation tests
make cov              # Same, with coverage collection
make lint_static      # Xcelium, Genus, and Vivado lint checks
make syn              # Cadence Genus synthesis
make lec              # Cadence Conformal logical equivalence check
make full             # sim + syn + lec
```

Simulation requires Cadence Xcelium 20.09. The host environment used
during development is a CentOS 7 VM (`ssh -p 2222 admin@127.0.0.1`),
because Xcelium is not present on the WSL2 host that holds the working
copy. The project is SSHFS-mounted from WSL2 into the VM so edits on
either side propagate live.

## Running on the FPGA

```bash
# Build the bare-metal MNIST HDMI demo
cd 07_sw/baremetal
make BOARD=PYNQ_BASE mnist_hdmi
cd ../..

# Program FPGA + load ELF + start execution via XSDB
make run_elf ELF=07_sw/baremetal/demo_mnist_hdmi_bm.elf \
             BIT=bitstreams/cgra_pynq_base/base.bit

# Watch UART telemetry (CH340 USB-UART, 115200 baud)
python3 scripts/uart_monitor.py /dev/ttyUSB1 115200 30
```

An HDMI monitor on the PYNQ-Z2 J11 connector shows the three-panel
demo: CGRA-FC, ARM-INT-FC, ARM-VFP-FC running the same MNIST FC stage
side by side with per-image cycle counts.

Walkthrough: [`07_sw/baremetal/MNIST_HDMI_DEMO.md`](07_sw/baremetal/MNIST_HDMI_DEMO.md)

## APB Register Map

Base address `0x43C8_0000` on the PYNQ-base bolt-on bitstream.
Zero wait-state APB slave.

### Registers implemented in `cgra_apb_csr.sv` (29)

| Offset | Name | Type | Description |
|---|---|---|---|
| 0x00 | DMA_CTRL | RW pulse | [0] Start, [1] Chain start (both auto-clear) |
| 0x04 | DMA_STATUS | RO | [0] busy, [1] done latch |
| 0x08 | DMA_SRC | RW | Source address |
| 0x0C | DMA_DST | RW | Destination address (upper nibble selects routing) |
| 0x10 | DMA_SIZE | RW | Transfer size in bytes |
| 0x14 | DMA_SRC_STRIDE | RW | 2D source row stride |
| 0x18 | DMA_ROWS | RW | 2D row count (0 = 1D mode) |
| 0x1C | DMA_COLS | RW | 2D bytes per row |
| 0x20 | CU_CTRL | RW pulse | [0] Start, [1] Soft Reset |
| 0x24 | CU_STATUS | RO | [0] busy, [1] done latch |
| 0x28 | CU_CYCLES | RO | Active cycle count since last cu_start |
| 0x2C | CU_TIMEOUT | RW | Watchdog limit (0 = disabled) |
| 0x30 | IRQ_STATUS | W1C | [0] DMA Done, [1] CU Done, [2] DMA Error |
| 0x34 | IRQ_MASK | RW | IRQ enable mask |
| 0x38 | DMA_ERROR | RO | [0] error flag, [2:1] AXI BRESP/RRESP |
| 0x3C | CU_PC_END | RW | [3:0] last PC slot before array_done (default 15) |
| 0x48 | LOOP_START | RW | Inner loop start PC |
| 0x4C | LOOP_END | RW | Inner loop end PC |
| 0x50 | LOOP_COUNT | RW | Inner loop iterations (total = count + 1) |
| 0x54 | RESULT_SKIP | RW | [7:0] FIFO warmup skip count (default 12) |
| 0x68 | LOOP2_START | RW | Outer loop start PC |
| 0x6C | LOOP2_END | RW | Outer loop end PC |
| 0x70 | LOOP2_COUNT | RW | Outer loop iterations (0 = disabled) |
| 0x74 | TILE_BANK_SEL | RW | [0] active tile memory half |
| 0x78 | TILE_AUTO_INC | RW | [0] enable tile addr auto-increment on loop wrap |
| 0x7C | DMA_DESC_HEAD | RW | Scatter-gather descriptor chain head pointer |
| 0x80 | DMA_DESC_STATUS | RO | [0] chain_active, [23:8] descriptors completed |
| 0x84 | SPM_AUTO_INC | RW | [0] enable spm_iter_cnt auto-increment on loop wrap |

### Result read window (decoded inside `cgra_apb_csr.sv`)

These addresses are part of the public APB map and the read/write
decode now lives inside `cgra_apb_csr.sv` alongside every other
register. The data signals (`global_result_i`, `result_fifo_pop_data_i`,
status flags) come in as input ports from `cgra_top.sv`; the pop pulse
(`result_fifo_pop_read`) is generated from a write to `0x44` and routed
out as an output port. Splitting the overloaded behaviour at `0x44` into
separate named registers is left as a future cleanup.

| Offset | Read returns | Write effect | Notes |
|---|---|---|---|
| 0x40 | `global_result` — registered east-edge value of PE[3][3] | — | Legacy single-cell debug latch, not FIFO data |
| 0x44 | FIFO status: `[0]` pop_valid, `[8:1]` count, `[9]` overflow, `[10]` underflow | — (writes are no-ops; RO) | Pop trigger moved to 0x88 in commit refactoring the overload |
| 0x58 | `result_fifo_pop_data[0]` — pre-fetched result, PE row 0 | — | Non-destructive |
| 0x5C | `result_fifo_pop_data[1]` — pre-fetched result, PE row 1 | — | Non-destructive |
| 0x60 | `result_fifo_pop_data[2]` — pre-fetched result, PE row 2 | — | Non-destructive |
| 0x64 | `result_fifo_pop_data[3]` — pre-fetched result, PE row 3 | — | Non-destructive |
| 0x88 | reads as 0 | `RESULT_POP` — write any value to pop one entry | Newly separated from 0x44 (see Implementation Notes) |

Correct read sequence per FIFO entry: read 0x58 → 0x5C → 0x60 → 0x64
(non-destructive), then **write to 0x88** (`RESULT_POP`) to advance
the pre-fetch register. Writes to 0x44 (`RESULT_STATUS`) are no-ops.

## Implementation Notes & Known Limitations

The following items are real and documented as-is. They do not block
the demonstrated functionality; cleaning them up is left for a future
revision.

### `0x40` returns `PE[3][3]` east-edge, not "RESULT_DATA"

Address `0x40` returns `global_result`, which `cgra_top.sv:737–744`
defines as the registered east-edge output of PE row 3 (the bottom-row
rightmost cell). This is a single-cell debug latch left over from an
earlier scalar-result API and is unrelated to the four-row Result FIFO.

The address is still mapped because removing it would break any test
or demo that polls `0x40` expecting a result-shaped value. A future
rename would be either `PE3_EAST_LAST` (descriptive) or retirement
(retire the address and reclaim the offset).

### Convolution stage runs on ARM, not the CGRA

The MNIST demo's Conv1 and Conv2 layers execute on the Cortex-A9 with
VFP, not on the CGRA. The reason is documented in the `cnn_conv3x3_pixel`
kernel: the 9-MAC reduction in a 3×3 convolution saturates the INT32
accumulator on realistic input magnitudes, dropping accuracy below the
97% target. Widening the result-readout path so that Conv can keep its
40-bit partial-sum precision is listed as future work in the thesis.

The FC stage — which dominates per-image runtime — is fully on the
CGRA and delivers the 3.81× speedup that drives the headline result.

### MAC pipeline RF read-after-write hazard

The 3-stage PE pipeline (decode → `_r` → `_r2`) has no register-file
bypass. A dependent RF read in slot N+1 sees stale data because slot
N's writeback has not landed yet. Effective MAC throughput is roughly
86% (13 of 15 back-to-back MACs contribute) on the canonical FC kernel
program. Routing through neighbour mesh ports or inserting spacing
slots is the documented workaround.

## Verification

Two independent regressions are run against every bitstream.

**Pre-silicon (Cadence Xcelium)**: 9,148 tests across 11 suites covering
APB and AXI4 protocol, 1D and 2D DMA, scatter-gather DMA, the full
21-opcode ISA, 40-bit MAC saturation, hardware loops, and end-to-end
CNN inference. All passing; zero failures, zero protocol violations.

**Silicon (bare-metal on PYNQ-Z2)**: 96 checks across 25 test groups
running directly on the Cortex-A9 against the live FPGA. Results
streamed over UART0; full pass on the current bitstream.

## Documentation

- [`CLAUDE.md`](CLAUDE.md) — Project context for AI tools
- [`06_doc/thesis_ch4/`](06_doc/thesis_ch4/) — Thesis Chapter 4 (software design)
- [`06_doc/thesis_ch5/`](06_doc/thesis_ch5/) — Thesis Chapter 5 (results)
- [`06_doc/demo_audit.md`](06_doc/demo_audit.md) — Feature × demo silicon-confirmation matrix
- [`06_doc/petalinux_hdmi_backup.md`](06_doc/petalinux_hdmi_backup.md) — PetaLinux + HDMI fallback flow
- [`07_sw/baremetal/MNIST_HDMI_DEMO.md`](07_sw/baremetal/MNIST_HDMI_DEMO.md) — Headline demo walkthrough

## License

Copyright © 2026 the authors. All rights reserved.

This work was developed as a senior design project at the Ho Chi Minh
City University of Technology. The source is provided for educational
and evaluation purposes. Commercial licensing is available upon request
via the supervisor.
