# CGRA Accelerator for Edge CNN Inference on Zynq-7000

**A 4×4 Coarse-Grained Reconfigurable Array accelerator with multicast routing,
silicon-validated on the PYNQ-Z2 (XC7Z020) at 50 MHz.**

Senior Design Project · Department of Electronics · HCMUT · May 2026

[![Silicon](https://img.shields.io/badge/Status-Silicon%20Validated-brightgreen)]()
[![Sim](https://img.shields.io/badge/Sim-9148%20PASS%20%2F%200%20FAIL-brightgreen)]()
[![HW](https://img.shields.io/badge/Hardware-96%20PASS%20%2F%200%20FAIL-brightgreen)]()
[![Fmax](https://img.shields.io/badge/Fmax-50.66%20MHz%20(WNS%20%2B0.263%20ns)-blue)]()
[![Speedup](https://img.shields.io/badge/FC%20Speedup-3.81%C3%97%20vs%20ARM--INT-orange)]()

---

## What this is

The accelerator targets the FC (fully-connected) stage of CNN inference — the
matrix–vector dot products that dominate per-image runtime — and offloads them
from the Cortex-A9 to a reconfigurable PE mesh. The case study is **MNIST
handwritten digit recognition**: Conv+Pool runs on the ARM, FC1 (400→64) and
FC2 (64→10) run on the CGRA, giving a **3.81× speedup on the FC stage** at
**97% top-1 accuracy** on a 2,745-frame live test.

The design is fully open-source SystemVerilog plus a complete bare-metal
software stack (linker, GIC driver, UART, HDMI framebuffer, ISA assembler
helpers) that runs from on-chip memory without any operating system.

## Headline results

| Metric | Value |
|---|---|
| FC stage speedup (vs ARM-INT) | **3.81×** (5.52 ms → 1.45 ms) |
| Per-frame throughput | **665 FPS** (CGRA-FC) vs 180 FPS (ARM-INT) |
| Classification accuracy | **97%** (2664 / 2745) |
| Clock frequency | **50 MHz** (Fmax 50.66 MHz, WNS +0.263 ns) |
| Power | 2.46 W total (2.29 W dynamic + 0.17 W static) |
| LUT utilization | 83.5% of XC7Z020 |
| BRAM utilization | 31.4% |
| DSP utilization | 75.0% |
| Simulation tests | **9,148 PASS / 0 FAIL** |
| Bare-metal regression | **96 checks / 0 failures** across 25 test groups |
| ISA opcodes implemented | 21 (NOP, ADD, SUB, MUL, MAC, AND, OR, XOR, SHL, SHR, CMP_GT/LT/EQ, LOAD_SPM, STORE_SPM, ACC_CLR, PASS0/1, LIF, RELU, MAX) |

## Architecture

```
┌─────────────────────────  PS (ARM Cortex-A9 @ 666 MHz)  ──────────────────────────┐
│                                                                                    │
│   APB control plane                          AXI4 data plane                       │
│        │                                          │                                │
└────────┼──────────────────────────────────────────┼────────────────────────────────┘
         │ (register reads/writes)                  │ (DMA bursts ↔ DDR3)
┌────────▼─── PL (XC7Z020 fabric @ 50 MHz) ─────────▼────────────────────────────────┐
│                                                                                    │
│   cgra_apb_csr ──── 29 registers ──── cgra_control_unit (IDLE → RUN → FINISH)      │
│        │                                          │                                │
│        └─── cgra_dma_subsystem ──── 2 FSMs ──── cgra_tile_memory (4-bank, 2-buf)   │
│                                                          │                         │
│                                            west edge ────▼────────────────────┐    │
│   cgra_config_broadcaster (slot-0 → all 16 PEs replay)   ┌──────┬──────┐      │    │
│                       │                                  │ PE00 │ PE01 │ ...  │    │
│                       ▼                                  ├──────┼──────┤      │    │
│   cgra_array (4×4 mesh, multicast NoC) ◄──────────────── │ PE10 │ PE11 │ ...  │    │
│                       │                       east edge  ├──────┼──────┤      │    │
│                       ▼                                  │ ...  │ ...  │      │    │
│   cgra_result_fifo (4 banks × 256 entries, lockstep push)                     │    │
│                                                                               │    │
└───────────────────────────────────────────────────────────────────────────────┘────┘
```

- **AXI4 + APB decoupled planes** — zero bus contention between control and data
- **4×4 PE mesh** with broadcast topology (one PE result fans out N/E/S/W per cycle)
- **40-bit MAC accumulator** in every PE with INT8×4 / INT16×2 / INT32 SIMD modes
- **2-level hardware loops** (L1 inner, L2 outer) with zero-overhead branching
- **Double-buffered tile memory** for zero-stall layer reconfiguration
- **Scatter-Gather DMA** — descriptor-chain CPU-free weight movement
- **Config broadcaster** — 15× DDR bandwidth reduction on shared-kernel workloads

## Repository layout

```
00_src/        SystemVerilog RTL (13 modules, 4655 LOC)
01_bench/      Xcelium testbench — UVM-inspired, 9,148 tests
06_doc/        Thesis + supplementary documentation
07_sw/         Software stack
   baremetal/   Cortex-A9 bare-metal (start.s, gic, uart, hdmi, demos)
   linux/       PetaLinux userspace (lpr_eval, lpr_live_demo_v2, lpr_hdmi_demo)
   driver/      UIO + /dev/mem driver wrapper
   lib/         cgra_tiler, lpr_golden, cgra_baremetal_shim
   cnn_eval/    MNIST training + INT16 quantization pipeline (PyTorch)
   lprnet_eval/ LPR training + ONNX export + quantization
   dts/         PetaLinux device-tree overlays
bitstreams/    Pre-built FPGA bitstreams (silicon-validated)
scripts/       Vivado / Genus / Conformal / XSDB / deploy scripts
Makefile       Top-level orchestration (sim + synth + LEC + FPGA deploy)
```

## Quick start

### Run the full simulation suite

```bash
make sim                # Compile + elaborate + run all 9,148 tests
make cov                # Same, with coverage collection
make cov_report         # Text coverage summary
make gui                # Interactive SimVision waveform debugging
```

> **Note**: simulation uses Cadence Xcelium 20.09 on a CentOS 7 VM. From WSL2,
> tunnel through `ssh -p 2222 admin@127.0.0.1` (alias `vm`). Project source is
> SSHFS-mounted so edits on either side are live.

### Build the bare-metal MNIST HDMI demo

```bash
cd 07_sw/baremetal
make BOARD=PYNQ_BASE mnist_hdmi              # → demo_mnist_hdmi_bm.elf
cd ../..
make run_elf ELF=07_sw/baremetal/demo_mnist_hdmi_bm.elf \
             BIT=bitstreams/cgra_pynq_base/base.bit
python3 scripts/uart_monitor.py /dev/ttyUSB1 115200 30
```

Plug an HDMI monitor into the PYNQ-Z2 J11 connector. The three-panel demo
shows CGRA-FC vs ARM-INT-FC vs ARM-VFP-FC, with per-image cycle counts and a
running 97% accuracy counter.

Full walkthrough: [`07_sw/baremetal/MNIST_HDMI_DEMO.md`](07_sw/baremetal/MNIST_HDMI_DEMO.md)

### Re-build the bitstream from RTL

```bash
# Vivado 2024.1+ (Windows host) — PYNQ-base bolt-on flow
source scripts/bootstrap_pynq_base_cgra.tcl   # builds platform + adds CGRA
# Run synthesis + implementation from the Vivado GUI
```

The canonical clean-rebuild path is `scripts/build_cgra_hdmi_pynqz2_clean.tcl`.
Detailed flow: [`docs/petalinux_hdmi_backup.md`](06_doc/petalinux_hdmi_backup.md).

### Linux userspace path (PetaLinux)

```bash
cd 07_sw/linux
make CROSS=arm-linux-gnueabihf- all          # builds 6 binaries into build/
# Deploy to board and run head-to-head LPR eval:
./run_demo_arm.sh    # ARM-only baseline
./run_demo_cgra.sh   # ARM + CGRA-FC offload
```

## APB Register Map (summary)

29 registers across 0x00–0x84, base address `0x43C8_0000` on the
PYNQ-base bolt-on (`0x43C0_0000` on Haoyue). Zero wait-state APB slave.

| Group | Range | Registers |
|---|---|---|
| DMA control / status | `0x00–0x1C` | DMA_CTRL, DMA_STATUS, DMA_SRC, DMA_DST, DMA_SIZE, DMA_SRC_STRIDE, DMA_ROWS, DMA_COLS |
| Control Unit | `0x20–0x2C` | CU_CTRL, CU_STATUS, CU_CYCLES, CU_TIMEOUT |
| IRQ + error | `0x30–0x3C` | IRQ_STATUS (W1C), IRQ_MASK, DMA_ERROR, CU_PC_END |
| Inner loop (L1) | `0x48–0x50` | LOOP_START, LOOP_END, LOOP_COUNT |
| Result FIFO skip | `0x54` | RESULT_SKIP (default 12) |
| Result read window | `0x40, 0x44, 0x58–0x64` | RESULT_DATA, RESULT_STATUS, RESULT_ROW0–3 |
| Outer loop (L2) | `0x68–0x70` | LOOP2_START, LOOP2_END, LOOP2_COUNT |
| Memory control | `0x74, 0x78, 0x84` | TILE_BANK_SEL, TILE_AUTO_INC, SPM_AUTO_INC |
| Scatter-Gather DMA | `0x7C–0x80` | DMA_DESC_HEAD, DMA_DESC_STATUS |

Full bitfield documentation: [`06_doc/CGRA_Design_Documentation.docx`](06_doc/).
Authoritative source: [`00_src/cgra_apb_csr.sv`](00_src/cgra_apb_csr.sv).

## DMA Destination Routing

The upper nibble of `DMA_DST` selects the target memory:

| Prefix | Destination | Use |
|---|---|---|
| `0x1xxx_xxxx` | Tile memory | Activation rows for FC layers |
| `0x2xxx_xxxx` | PE config BRAM | Instruction words (double-pumped, broadcast-replayed) |
| `0x4xxx_xxxx` | PE scratchpad (SPM) | Weight data; offset `[15:12]` = PE ID |
| `0x0xxx_xxxx` | DDR3 (AXI write) | General memory transfer |

## Build flows

| Target | Tool | Command |
|---|---|---|
| Simulation | Xcelium 20.09 | `make sim` |
| RTL lint | Xcelium / Genus / Vivado | `make lint_static` |
| X-prop check | Xcelium | `make lint_all` |
| Coverage | Xcelium UCDB | `make cov && make cov_report` |
| Synthesis | Cadence Genus | `make syn` |
| LEC | Cadence Conformal | `make lec` |
| Full flow | sim + syn + lec | `make full` |
| FPGA program | Xilinx XSDB | `make program BIT=…` |
| Bare-metal run | XSDB + UART | `make run_elf ELF=… BIT=…` |
| FPGA status | XSDB | `make fpga_status` |
| Register dump | XSDB | `make reg_dump` |

## Verification

9,148 tests across 11 suites, all PASSING (verified `make sim` 2026-05-18):

| Suite | Tests | Coverage |
|---|---|---|
| Smoke / sanity | 80 | Basic register access, reset |
| AXI4 + APB protocol | 400+ | Bursts, 4 KB boundary, backpressure, W1C |
| DMA 1D + 2D transfers | 1,200 | All destination prefixes (TILE, CONFIG, SPM, AXI) |
| Scatter-Gather DMA | 50 | Linked-list chains, NULL termination, abort |
| PE ISA full regression | 8,500 | All 21 opcodes × all source/destination combos |
| 40-bit MAC saturation | 50 | Overflow, INT8×4 / INT16×2 / INT32 SIMD |
| Hardware loops L1 + L2 | 9 | Invalid bounds, mid-run stability, nesting |
| CNN end-to-end | 61 | Full MNIST inference (DMA + CU + IRQ) |
| CNN kernel suite | 300+ | FC1 + FC2 with known weights and activations |

Plus a **silicon-validated bare-metal regression** of 96 checks across 25 test
groups running on real hardware via UART (see `07_sw/baremetal/main.c`).

## Documentation

- [`CLAUDE.md`](CLAUDE.md) — Project context and AI tool instructions
- [`06_doc/CGRA_Design_Documentation.docx`](06_doc/) — Complete RTL design doc
- [`06_doc/petalinux_hdmi_backup.md`](06_doc/petalinux_hdmi_backup.md) — PetaLinux + HDMI flow
- [`06_doc/demo_audit.md`](06_doc/demo_audit.md) — Demo viability audit
- [`06_doc/thesis_ch4/`](06_doc/thesis_ch4/) — Thesis Chapter 4 (software design)
- [`06_doc/thesis_ch5/`](06_doc/thesis_ch5/) — Thesis Chapter 5 (results)
- [`07_sw/baremetal/MNIST_HDMI_DEMO.md`](07_sw/baremetal/MNIST_HDMI_DEMO.md) — Headline demo walkthrough

## Authors

- **Huynh Pham Anh Duy** — 2051095
- **Trieu Thanh Vinh** — 2213980

**Supervisor**: Assoc. Prof. PhD. Truong Quang Vinh
**Institution**: Department of Electronics · Faculty of Computer Science and Engineering · Ho Chi Minh City University of Technology (HCMUT)

## License

Copyright © 2026 the authors. All rights reserved.

This work was developed as a senior design project at HCMUT. The IP core
is provided for educational and evaluation purposes. Commercial licensing
is available upon request via the supervisor.
