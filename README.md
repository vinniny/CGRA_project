# CGRA Accelerator for SNN Inference

<div align="center">

**Coarse-Grained Reconfigurable Array IP Core**

*Version 3.0.0 | April 2026*

[![Silicon Ready](https://img.shields.io/badge/Status-Silicon%20Ready-brightgreen)]()
[![Sim Tests](https://img.shields.io/badge/Sim-8915%20PASS%20%7C%200%20FAIL-brightgreen)]()
[![HW Tests](https://img.shields.io/badge/Hardware-96%20PASS%20%7C%200%20FAIL-brightgreen)]()
[![ISA](https://img.shields.io/badge/ISA-21%20Operations%20(100%25%20covered)-blue)]()
[![License](https://img.shields.io/badge/License-Commercial-blue)]()

</div>

---

## Product Overview

High-performance **Coarse-Grained Reconfigurable Array (CGRA)** accelerator IP designed for **Sparse Spiking Neural Network (SNN) Inference** and **License Plate Recognition (LPR)**. Features a 4×4 mesh of processing elements with integrated DMA, APB control interface, hardware support for **Leaky Integrate-and-Fire (LIF)** neuron dynamics, and **ANN extensions** (RELU, MAX) for convolutional inference.

### Key Innovations
- **Parameterized N*M Mesh**: Scalable PE array (default 4x4) with multicast routing for efficient sparse matrix computation.
- **Hardware LIF Neurons**: Dedicated state-update logic within each PE for biologically plausible spiking dynamics.
- **ANN Activation Extensions**: Hardware RELU and MAX operations for convolutional neural network layers.
- **Mixed-Precision SIMD**: INT8x4 and INT16x2 dot-product modes for area/power-efficient inference.
- **Double-Buffered Tile Memory**: 4 banks x 4096 words with bank_sel for latency-hiding data swaps.
- **Bi-Directional DMA**: AXI4 burst master with 32-word FIFO, 2D strided transfers, W_LOCAL fast-drain path.
- **Nested Hardware Loops**: 2-level zero-overhead loops with loop-aware auto-stop for multi-tile execution.
- **Dynamic Branching**: PE predicate flag drives CU PC jump for data-dependent control flow.
- **Pipelined ALU**: 3-stage pipeline (decode → _r → _r2) for timing closure on DSP48 paths.
- **End-to-End FC Acceleration**: Verified 784->30 fully-connected layer offload matching software golden model bit-exactly.
- **UVM-Inspired Verification**: 8915 tests, 25 suites, transaction-based monitors/scoreboards, SystemVerilog covergroups, clocking blocks, constrained-random classes.

### Target Applications
- **Spiking Neural Networks**: Image classification, event-based sensing (DVS)
- **License Plate Recognition**: Convolutional inference with tiled MatMul offload (PYNQ-Z2 demo)
- **Sparse Linear Algebra**: Compressed Sparse Column (CSC) matrix operations
- **Signal Processing**: FIR/IIR filters, FFT acceleration
- **Edge AI**: Ultra-low latency inference on FPGA

---

## Datasheet

### Operating Points (Repository-Backed)

| Item | Value | Source in repo |
|------|-------|----------------|
| FPGA target | Xilinx Zynq-7000 XC7Z020 | XSDB scripts + bring-up flow |
| Hardware-validated clock | 50 MHz | Bare-metal bring-up / hardware regression flow |
| Synthesis constraint target | 100 MHz (10 ns period) | `scripts/genus_syn.tcl` (`create_clock -period 10.0`) |
| Reset polarity/type | Active-low, synchronous | RTL (`always_ff @(posedge clk)` + `if (!rst_n)`) |

### Architecture Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Array Configuration** | 4x4 (16 PEs) | Parameterized N*M via generate blocks |
| **Data Width** | 32-bit | Full precision throughout |
| **Config Width** | 64-bit | Per-context instruction |
| **Context Depth** | 16 slots/PE | Multi-context switching |
| **Instruction Set** | 21 operations | 100% verified (incl. RELU, MAX, LIF) |
| **Accumulator** | 40-bit signed | Saturating arithmetic |
| **SIMD Modes** | INT8x4 / INT16x2 | Config bits [50:49] |
| **Hardware Loops** | 2 levels (nested) | Zero-overhead, loop-aware auto-stop |

### Memory Resources

| Memory | Size | Width | Type |
|--------|------|-------|------|
| PE Register File | 16 entries | 32-bit | Flip-flop |
| PE Scratchpad | 256 entries | 32-bit | SRAM |
| PE Config RAM | 16 entries | 64-bit | BSG SRAM |
| Tile Memory | 4 x 4096 entries | 32-bit | SRAM (double-buffered) |
| DMA FIFO | 32 entries | 32-bit | Flip-flop |

### Interface Specifications

| Interface | Standard | Width | Description |
|-----------|----------|-------|-------------|
| Control | APB 2.0 | 32-bit | Register access |
| Memory | AXI4 Full | 32-bit | DMA burst master |
| Interrupt | Level | 1-bit | Active high |
| Clock | Single | - | Rising edge |
| Reset | Active-low | - | Synchronous |

### Timing and Resource Notes

- This repository does not include checked-in sign-off timing/resource reports for an UltraScale+ target.
- Current documented deployment target is **XC7Z020 at 50 MHz**.
- Synthesis scripts are configured with a **100 MHz** target clock for implementation experiments.

---

## Quick Start

### Simulation

```bash
# Run full verification suite (Cadence Xcelium 20.09+)
make sim                # Compile, elaborate, simulate (8915 tests)

# Split flow for debugging
make compile            # Compile RTL + TB sources
make build              # Elaborate design
make run                # Run simulation

# Interactive GUI mode
make gui                # Launch SimVision waveform viewer

# Coverage collection
make cov                # Simulate with -coverage all (4 covergroups)
make cov_report         # Extract coverage summary from sim log (IMC not required)
make cov_gui            # Open SimVision with coverage data

# Verbose mode (detailed PE/DMA trace output)
make sim DEFINES=+define+TB_VERBOSE

# Reproducible random seed
SEED=12345 make sim

# Clean build artifacts
make clean
```

### Building Software

```bash
cd 07_sw
make all                         # Build all targets (native x86_64)
make test                        # Build and run golden model test (no HW needed)
make test_tiler                  # Build and run tiler unit tests
make dump_hex                    # Generate config/image/golden .mem files for simulation
make clean                       # Clean build artifacts

# Cross-compile for Zynq ARM (Cortex-A9)
make CROSS=arm-linux-gnueabihf- all
```

### ASCII Image Accelerator Demo

A standalone Vitis-style C application that visually demonstrates the
full hardware pipeline (`ARM → DMA → CGRA → IRQ → ARM`) by inverting an
8×8 pixel-art letter "Z" through the CGRA. Designed for live audiences:
heavily commented, ANSI-colored UART output, single `wfi` block in
main(), and an LED4 visual indicator on every IRQ. Lives at
`07_sw/baremetal/demo_ascii_inverter.c` and uses the **real Xilinx Vitis
BSP** (`XScuGic`, `Xil_DCacheFlushRange`, `Xil_ExceptionRegisterHandler`)
rather than the round-3 hand-rolled GIC driver.

```bash
make demo                # builds 07_sw/baremetal/demo_ascii.elf
make run_demo            # programs FPGA, loads demo, captures UART
```

The demo source file is **identical** between two build paths:

| Build path | Who provides BSP / xparameters.h | Use case |
|---|---|---|
| WSL2 (this repo's Makefile) | The Makefile pulls Vitis BSP source from `/tools/Xilinx/2025.1/data/embeddedsw/` and links our hand-rolled `xparameters.h` + `xscugic_g.c` | Bring-up + iteration |
| Windows Vitis Workbench | Vitis auto-generates `xparameters.h`, `xscugic_g.c`, the linker script, and the boot/vector code from the bitstream `.hwh` | Live demo |

To port the demo to Vitis Workbench on Windows: create an Empty
Application project against the same `.xsa`, **import only
`demo_ascii_inverter.c`** into `src/`, build, and run. No other file
from this repo is needed — the demo source defines its own UART driver,
hardcodes the CGRA IRQ ID (61), and doesn't reference any project-local
header.

### FPGA Hardware Bring-Up (Zynq-7000)

End-to-end JTAG deployment from a Linux/WSL2 host to a Zynq XC7Z020 board
using Xilinx XSDB. Tested on a custom XC7Z020 board with a Digilent JTAG-SMT3
probe, a CH340C USB-serial bridge wired to UART0 (MIO[14]/MIO[15]), and
LED4 routed to the CGRA `irq` net for visual interrupt confirmation. The
in-tree bitstream also includes a Vivado **System ILA** core monitoring
the CGRA AXI master interface and the DMA debug signals (`dbg_dma_busy`,
`dbg_dma_read_state`, `dbg_dma_write_state`, `dbg_dma_fifo_full`,
`dbg_dma_fifo_empty`, `dbg_dma_write_words_remaining`, plus the `irq`
output) — open the Vivado hardware manager and refresh device to capture
traces if any future test misbehaves.

```bash
# One-time: start Xilinx hw_server (talks to the Digilent SMT3 over libusb)
make hw_server_start

# Pull the freshly built bitstream + ps7_init.tcl + .hwh from a Vivado project
make pull_all                                      # default: /mnt/c/Users/.../FPGA_CGRA
VIVADO_PROJECT=/path/to/proj make pull_all         # override path

# Program PL + run ps7_init (DDR, MIO, UART, clocks) + AXI sanity check
make program BIT=bitstreams/cgra_top.bit
make program BIT=... PS_INIT=0                     # PL only, skip PS init

# Inspect FPGA + every CGRA APB register
make fpga_status
make reg_dump                                      # all 28 registers, decoded
make reg_read  REG=DMA_STATUS
make reg_write REG=DMA_SRC VAL=0x10000000

# Build the bare-metal regression and run it on Cortex-A9 #0
make baremetal                                     # arm-none-eabi-gcc -> cgra_test.elf
make run_baremetal                                 # program + load + capture UART

# Load any other bare-metal ELF
make run_elf ELF=07_sw/build/my_app BIT=bitstreams/cgra_top.bit
```

The bare-metal regression covers 25 test groups / 96 checks across three
rounds. Round 1 verifies the APB CSR file, 1D and 2D DMA, varied transfer
sizes, back-to-back DMA stress, tile bank isolation, PASS0 routing in East
and South, all four `RESULT_ROW` registers + `PE[3,3] RESULT_DATA`, loop
count sweeps + `CU_CYCLES` monotonicity, `IRQ_STATUS` W1C, a 20-iteration
stress run, and CU soft reset. Round 2 adds the ALU smoke test (ADD, SUB,
MUL, AND, OR, XOR), multi-instruction context programs, nested LOOP2 over
LOOP, North + West routing + 3-way multicast, MAC saturation to the 40-bit
accumulator boundary, DMA + CU concurrent kicks, and DMA error / register
protection. Round 3 adds end-to-end GIC interrupt delivery: the bare-metal
ELF stands up its own ARMv7 GIC v1 driver, registers an ISR for the CGRA
IRQ (`IRQ_F2P[0]` → GIC ID 61), and verifies DMA-done + CU-done IRQs,
masked-path silence, and 5 back-to-back deliveries. The same `irq` net is
also exported to **LED4** on the board, and the LED has been visually
confirmed to pulse during the test — proving the physical PL→PS→GIC→CPU
→ISR→W1C path works end to end. Results are streamed over UART0 at 115200
baud and captured in `02_log/uart.log`. **Current result on hardware:
96 / 96 passed (LED4 pulse confirmed).**

> **WSL2 USB passthrough.** The JTAG probe (`0403:6010`, Digilent Adept) and
> the CH340C UART (`1a86:7523`) must both be attached via `usbipd-win` from
> Windows before running the flow:
> ```powershell
> usbipd attach --wsl --busid <jtag>; usbipd attach --wsl --busid <uart>
> ```

### C ALPR (Real-Time License Plate Recognition)

Pure C pipeline for video/webcam-based plate detection using ONNX Runtime + FFmpeg.
Located in `scripts/License_Plate_Recognition_Cpp/c_alpr/`.

```bash
cd scripts/License_Plate_Recognition_Cpp/c_alpr

# Build (Linux, without ONNX — stub mode)
cmake -S . -B build_linux -DENABLE_ONNXRUNTIME=OFF -DENABLE_FFMPEG=ON
cmake --build build_linux --config Release

# Build with ONNX Runtime (full inference)
cmake -S . -B build_linux -DENABLE_ONNXRUNTIME=ON \
      -DONNXRUNTIME_ROOT=/path/to/onnxruntime -DENABLE_FFMPEG=ON
cmake --build build_linux --config Release

# Run modes
build_linux/c_alpr configs/alpr_config.ini webcam:0     # Webcam
build_linux/c_alpr configs/alpr_config.ini video.mp4    # Video file
build_linux/c_alpr configs/alpr_config.ini image.bmp    # Single BMP image
build_linux/c_alpr configs/alpr_config.ini folder/      # Batch folder
```

---

## System Architecture

### Block Diagram

```
                        ┌─────────────────────────────────────────────┐
                        │              CGRA SoC Accelerator           │
                        │                                             │
    ┌─────────┐         │  ┌──────────────────────────────────────┐  │
    │   CPU   │◄────────┼──┤         APB Control Interface        │  │
    │  (Host) │  APB    │  │  • 28 Registers (17 RW, 1 W1C, 10 RO) │  │
    └─────────┘         │  │  • DMA, CU, IRQ, Loop, Result CSRs  │  │
                        │  │  • 256B address space, 32-bit access │  │
                        │  └────────────────┬─────────────────────┘  │
                        │                   │                         │
                        │  ┌────────────────┴─────────────────────┐  │
                        │  │           Control Unit                │  │
                        │  │  • 3-state FSM (IDLE/RUN/FINISH)     │  │
                        │  │  • Programmable timeout              │  │
                        │  │  • Hardware loop (start/end/count)   │  │
                        │  │  • Auto-stop on completion           │  │
                        │  └────────────────┬─────────────────────┘  │
                        │                   │                         │
    ┌─────────┐         │  ┌────────────────┴─────────────────────┐  │
    │ External│◄────────┼──┤         Pipelined DMA Engine         │  │
    │   RAM   │  AXI4   │  │  • Read/Write state machines         │  │
    └─────────┘ (Burst) │  │  • 32-entry synchronous FIFO          │  │
                        │  │  • AXI4 burst (up to 32 beats/req)    │  │
                        │  │  • W_LOCAL fast-drain for tile/cfg   │  │
                        │  │  • 4KB boundary protection           │  │
                        │  └────────────────┬─────────────────────┘  │
                        │                   │                         │
                        │  ┌────────────────┴─────────────────────┐  │
                        │  │       Tile Memory (64KB SRAM)         │  │
                        │  │  • 4 banks × 4096 × 32-bit          │  │
                        │  │  • Bank per row, double-buffered     │  │
                        │  └────────────────┬─────────────────────┘  │
                        │                   │ (feeds West edge)        │
                        │  ┌────────────────┴─────────────────────┐  │
                        │  │        4×4 Processing Element Array   │  │
                        │  │                                       │  │
                        │  │   PE00 ─── PE01 ─── PE02 ─── PE03    │  │
                        │  │    │       │       │       │         │  │
                        │  │   PE10 ─── PE11 ─── PE12 ─── PE13    │  │
                        │  │    │       │       │       │         │  │
                        │  │   PE20 ─── PE21 ─── PE22 ─── PE23    │  │
                        │  │    │       │       │       │         │  │
                        │  │   PE30 ─── PE31 ─── PE32 ─── PE33    │  │
                        │  │                                       │  │
                        │  │   Mesh Interconnect: 32-bit broadcast │  │
                        │  └───────────────────────────────────────┘  │
                        │                                             │
                        └─────────────────────────────────────────────┘
```

### Processing Element Architecture

```
                    ┌──────────────────────────────────────────────┐
   Config RAM ─────▶│  64-bit Configuration Decoder                │
   (16×64-bit BSG)  │  opcode, src_sel, dst_sel, route, imm       │
                    └──────────────────┬───────────────────────────┘
                                       │
    ┌──────────────────────────────────┼──────────────────────────────┐
    │                                  ▼                              │
    │  ┌────────────────────────────────────────────────────────┐    │
    │  │              Operand Multiplexer                        │    │
    │  │  Sources: RF(0), N(1), E(2), S(3), W(4), SPM(5), Imm(6) │    │
    │  └────────────────────┬─────────────────┬─────────────────┘    │
    │                       │ Operand A       │ Operand B            │
    │                       ▼                 ▼                      │
    │  ┌─────────────────────────────────────────────────────────┐   │
    │  │                   ALU / MAC Unit                         │   │
    │  │  • 21 Operations (arithmetic, logic, shift, compare, ANN) │   │
    │  │  • 40-bit saturating accumulator                        │   │
    │  │  • 64-bit full-precision multiply (no truncation)       │   │
    │  │  • 5-bit barrel shifter (0-31 positions)                │   │
    │  │  • Arithmetic right shift (sign-preserving)             │   │
    │  │  • LIF neuron (Leaky Integrate-and-Fire)               │   │
    │  └────────────────────┬────────────────────────────────────┘   │
    │                       │ Result (32-bit)                        │
    │                       ▼                                        │
    │  ┌─────────────────────────────────────────────────────────┐   │
    │  │              Mesh Broadcast Router                       │   │
    │  │        Outputs to: North, East, South, West              │   │
    │  └─────────────────────────────────────────────────────────┘   │
    │                                                                │
    │  Local Storage:                                                │
    │  ├─ Register File: 16 × 32-bit                                │
    │  └─ Scratchpad:   256 × 32-bit (SRAM)                         │
    │                                                                │
    └────────────────────────────────────────────────────────────────┘
```

### FC Layer Execution Pattern (784→30 Example)

The CGRA computes fully-connected layers as a sequence of 16-context MAC sweeps across tiled chunks:

```
For each input chunk k (0..60):                         61 chunks × 16 inputs = 976 ≈ 784 padded
  1. DMA config chunk k → all 16 PEs (256 config words, individual 4-byte DMAs)
  2. DMA image chunk k → tile memory banks 0-3 (64 bytes each)
  3. CU: run contexts 0-15 (LOOP_START=0, LOOP_END=15, START)
     • Context c: PE(row,0) executes MAC using tile[bank=row][c] as operand A
     • Contexts 13-15: PE(row,1..3) configured as PASS0 — propagate accumulator east
  4. Wait CU IRQ (W1C clear)
Read RESULT_ROW0-3 (east edge of row 0-3) → 4 accumulators → argmax → character class
```

---

## Register Map

### APB Address Space (28 Registers)

**DMA Engine Control (8 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x00 | DMA_CTRL | RW | 0x0 | [0] Start (auto-clear) |
| 0x04 | DMA_STATUS | RO | 0x0 | [0] Busy, [1] Done |
| 0x08 | DMA_SRC | RW | 0x0 | Source address (32-bit) |
| 0x0C | DMA_DST | RW | 0x0 | Destination address (32-bit) |
| 0x10 | DMA_SIZE | RW | 0x0 | Transfer size in bytes |
| 0x14 | DMA_SRC_STRIDE | RW | 0x0 | 2D: source row stride (bytes) |
| 0x18 | DMA_ROWS | RW | 0x0 | 2D: number of rows (0 = 1D mode) |
| 0x1C | DMA_COLS | RW | 0x0 | 2D: columns per row (bytes) |

**Control Unit (4 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x20 | CU_CTRL | RW | 0x0 | [0] Start, [1] Soft Reset |
| 0x24 | CU_STATUS | RO | 0x0 | [0] Busy, [1] Done |
| 0x28 | CU_CYCLES | RO | 0x0 | Active (non-stalled) execution cycle counter |
| 0x2C | CU_TIMEOUT | RW | 0x0 | Max wall-clock cycles before timeout (0 = unlimited) |

**Interrupt Control (2 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x30 | IRQ_STATUS | W1C | 0x0 | [0] DMA Done, [1] CU Done, [2] DMA Error |
| 0x34 | IRQ_MASK | RW | 0x0 | IRQ enable mask |

**DMA Error Status (1 register):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x38 | DMA_ERROR | RO | 0x0 | [0] Error flag, [2:1] Error code (01=SLVERR, 10=DECERR). W1C via IRQ_STATUS[2] |

**Global Result Capture (2 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x40 | RESULT_DATA | RO | 0x0 | PE[15] output (global_result) |
| 0x44 | RESULT_STATUS | RO | 0x0 | [0] result_valid |

**Hardware Loop Control (3 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x48 | LOOP_START | RW | 0x0 | Hardware loop start PC [15:0] |
| 0x4C | LOOP_END | RW | 0x0 | Hardware loop end PC [15:0] (inclusive) |
| 0x50 | LOOP_COUNT | RW | 0x0 | Extra iterations beyond the first pass [15:0] (0 = run once) |

**LPR Row Results (4 registers — East-edge output capture):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x58 | RESULT_ROW0 | RO | 0x0 | East-edge result row 0 (PE[0,3]) |
| 0x5C | RESULT_ROW1 | RO | 0x0 | East-edge result row 1 (PE[1,3]) |
| 0x60 | RESULT_ROW2 | RO | 0x0 | East-edge result row 2 (PE[2,3]) |
| 0x64 | RESULT_ROW3 | RO | 0x0 | East-edge result row 3 (PE[3,3]) |

**Nested Loop Level 2 (3 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x68 | LOOP2_START | RW | 0x0 | Outer loop start PC [15:0] |
| 0x6C | LOOP2_END | RW | 0xF | Outer loop end PC [15:0] (inclusive) |
| 0x70 | LOOP2_COUNT | RW | 0x0 | Outer loop extra iterations [15:0] (0 = disabled) |

**Double-Buffer Control (1 register):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x74 | TILE_BANK_SEL | RW | 0x0 | [0] PE buffer select (0/1). Protected: rejected while DMA or CU busy |

### DMA Address Decode

| Address Prefix | Target | Bit Fields |
|----------------|--------|------------|
| 0x0XXX_XXXX | External AXI / DDR | Direct AXI burst pass-through |
| 0x1XXX_XXXX | Tile Memory | [13:12]=Bank, [11:0]=Byte offset |
| 0x2XXX_XXXX | Config RAM | [10:7]=PE ID, [6:3]=Slot, [2]=Hi/Lo word |

**Important:** Staging buffers in DDR **must** use prefix `0x0`. Addresses with prefix `0x1` or `0x2` are routed to internal memories, not external RAM.

**Config double-pump write sequence (64-bit atomic):**
1. Write `data[63:32]` to `0x2XXXXXXX` — latches upper 32 bits (addr[2]=0)
2. Write `data[31:0]` to `0x2XXXXXXX | 0x4` — commits full 64-bit config entry (addr[2]=1)

**Slot 0 broadcast:** Writing config to slot 0 fills all 16 context slots of the target PE. Writing to slots 1–15 updates only that specific slot.

---

## Instruction Set Architecture

### Opcode Summary (21 Operations)

| Op | Mnemonic | Operation | Flags | Latency |
|----|----------|-----------|-------|---------|
| 0 | NOP | No operation | - | 1 |
| 1 | ADD | A + B (saturating) | OVF | 1 |
| 2 | SUB | A - B (saturating) | OVF | 1 |
| 3 | MUL | A × B (64-bit full precision) | - | 1 |
| 4 | MAC | Acc += A × B (64-bit, saturating to 40b) | OVF | 1 |
| 5 | AND | A & B | - | 1 |
| 6 | OR | A \| B | - | 1 |
| 7 | XOR | A ^ B | - | 1 |
| 8 | SHL | A << B[4:0] | - | 1 |
| 9 | SHR | A >>> B[4:0] (arithmetic) | - | 1 |
| 10 | CMP_GT | A > B ? 1 : 0 | - | 1 |
| 11 | CMP_LT | A < B ? 1 : 0 | - | 1 |
| 12 | CMP_EQ | A == B ? 1 : 0 | - | 1 |
| 13 | LOAD_SPM | RF ← SPM[A] | - | 1 |
| 14 | STORE_SPM | SPM[A] ← B | - | 1 |
| 15 | ACC_CLR | Acc = 0 | - | 1 |
| 16 | PASS0 | Output = A (pass operand A east) | - | 1 |
| 17 | PASS1 | Output = B (pass operand B east) | - | 1 |
| 18 | LIF | Spiking neuron (Leaky Integrate-and-Fire) | SPIKE | 1 |
| 19 | RELU | max(0, A) | - | 1 |
| 20 | MAX | max(A, B) signed | - | 1 |

**MUL/MAC precision:** Both operands are sign-extended to 64 bits before multiplication, yielding a full 64-bit product. For MAC, the product is accumulated into the 40-bit saturating accumulator with overflow detection on bits [63:39].

### Configuration Frame Format (64-bit)

```
Bit Position:
 63        40 39      24 23 22 21    18 17    14 13    10 9     6 5     0
┌────────────┬──────────┬──┬──┬────────┬────────┬────────┬────────┬───────┐
│  extended  │   imm    │pi│pe│ route  │  dst   │  src1  │  src0  │opcode │
│   24-bit   │  16-bit  │1b│1b│  4-bit │  4-bit │  4-bit │  4-bit │ 6-bit │
└────────────┴──────────┴──┴──┴────────┴────────┴────────┴────────┴───────┘
```

| Field | Bits | Description |
|-------|------|-------------|
| opcode | [5:0] | ALU operation code (0–20) |
| src0_sel | [9:6] | Operand A source: 0=RF, 1=N, 2=E, 3=S, 4=W, 5=SPM, 6=Imm |
| src1_sel | [13:10] | Operand B source (same encoding as src0) |
| dst_sel | [17:14] | RF write address (0–15) |
| route_mask | [21:18] | Output direction mask (N/E/S/W bits) |
| pred_en | [22] | Enable predication |
| pred_inv | [23] | Invert predicate |
| imm | [39:24] | Signed 16-bit immediate (+/-32767) |
| cfg_dest_x | [43:40] | XY routing X coordinate |
| branch_target | [47:44] | Dynamic branch PC target |
| branch_en | [48] | Enable dynamic branching |
| data_mode | [50:49] | 00=INT32, 01=INT16x2, 10=INT8x4 (SIMD) |
| reserved | [63:51] | Reserved |

---

## Verification

### Test Results

| Metric | Value |
|--------|-------|
| Total Tests | **8915 PASS, 0 FAIL** |
| Protocol Violations | **0** (AXI4 + APB monitors) |
| ISA Coverage | **21/21 (100%)** operations verified |
| Verification Method | CRV + directed + deployment replay + UVM-inspired TLM |
| Test Suites | **25** suites across 6 categories |
| Covergroups | 4 (DMA xfer, PE ISA, CU flow, APB regs) |
| Clocking Blocks | APB (drive/sample) + AXI (sample-only) |
| Transaction Layer | APB/AXI monitors, DMA/PE scoreboards, mailbox agents |
| Status | **SILICON READY** |

### Test Suite Breakdown

**Functional Verification (14 suites):**

| Suite | ID | Tests | Focus |
|-------|----|-------|-------|
| System Integrity | System | ~500 | APB randomization, DMA handshake stress, protocol edge cases |
| Fabric Stress (CRV) | Fabric | ~300 | Pipeline integrity, parallel PE routing, multicast |
| Robustness | Robust | ~300 | Reset injection, stall injection, IRQ stress |
| ISA Regression | AD | ~8,500 | All 21 opcodes: 500 random vectors each (100% ISA coverage) |
| LPR Features | LPR | ~150 | RELU/MAX, HW loop CSRs, east-edge results, double-buffer |
| DMA Write-Back | AE | ~100 | Round-trip, burst protocol, 4KB boundary, zero-length |
| DMA Read-Back | AF | ~100 | Multi-bank tile read, large transfers, abort mid-transfer |
| PE Pipeline | AG | 6 | Registered operand stage (_r) verification |
| AXI Error Handling | AH | 12 | BRESP/RRESP error injection, DMA_ERROR CSR, IRQ_STATUS[2], W1C |
| Tile Memory Depth | AI | 5 | BANK_DEPTH=4096 boundary verification |
| Hardware Loops | AJ | 9 | Single + nested loop execution |
| Double-Buffer | AK | 5 | bank_sel toggle and tile switching |
| Mixed-Precision SIMD | AL | 6 | INT8x4 / INT16x2 dot-product modes |
| Real Application E2E | RAP | 4 | FC 784->30: 61 chunks, bit-exact vs golden model |

**Neuromorphic & Recovery (2 suites):**

| Suite | ID | Tests | Focus |
|-------|----|-------|-------|
| Neuromorphic LIF | V | 3 | LIF neuron fire/no-fire, membrane dynamics |
| DMA Hang Recovery | W | 5 | Stuck DMA diagnosis, soft/hard reset recovery |

**Deployment Verification (8 suites):**

| Suite | ID | Tests | Focus |
|-------|----|-------|-------|
| APB Register Sanity | AM | ~40 | RW round-trip, RO immutability, W1C, protected rejection |
| DMA Smoke | AN | ~15 | Single word, block, tile round-trip, config load, 4KB boundary |
| Compute Smoke | AO | ~16 | Basic ALU ops, auto-stop, east-edge, multi-PE |
| Driver Replay | AP | ~14 | Mirrors exact cgra_driver.c register sequences |
| IRQ W1C Sequence | AQ | ~17 | Linux UIO interrupt handling: mask, clear, priority |
| DMA Physical Address | AR | ~11 | Large AXI offsets, realistic FC transfer sizes |
| Soft Reset Recovery | AS | ~14 | Mid-run reset, double reset, post-reset functional |
| Error Recovery | AT | ~14 | Timeout, double DMA start, protected regs during busy |

**Hardware Emulation (1 suite):**

| Suite | ID | Tests | Focus |
|-------|----|-------|-------|
| Hardware Emulation | HE | ~61 | Multi-inference loops, bank_sel double-buffer, IRQ-driven completion, error injection mid-inference, large DDR payloads, AXI stress, dynamic reconfiguration |

### Real Application Suite (RAP) Details

Suite RAP drives the complete end-to-end FC layer verification. It loads pre-generated hex files (`config.mem`, `image.mem`, `golden.mem`) and drives DMA and CU exactly as the production driver does:

1. ACC_CLR sweep — zeros all PE accumulators across 16 PEs
2. For each of 61 chunks: load config words → stage image to DDR → DMA to tile banks → run 16-context CU sweep → wait IRQ
3. Read RESULT_ROW0-3 and compare bit-exactly against the software golden model

Generate test fixtures before running simulation:
```bash
cd 07_sw && make dump_hex   # Produces ../01_bench/{config,image,golden}.mem
cd ..     && make sim       # Suite RAP verifies 4/4 result rows match golden
```

### Supported Simulators

| Simulator | Version | Status | Notes |
|-----------|---------|--------|-------|
| Cadence Xcelium | 20.09+ | Pass | Primary tool, covergroups supported |
| Verilator | 5.x+ | Not in checked-in flow | Testbench includes Verilator lint pragmas, but full regression flow is Xcelium-based |
| Synopsys VCS | 2023+ | Untested | No checked-in VCS run scripts in this repo |

---

## Integration Guide

### RTL Instantiation

```systemverilog
cgra_top #(
    .DATA_WIDTH   (32),
    .ADDR_WIDTH   (32),
    .COORD_WIDTH  (4),
    .PAYLOAD_WIDTH(16),   // Internal routing (compatibility)
    .SPM_DEPTH    (256),
    .RF_DEPTH     (16),
    .CONFIG_WIDTH (64),
    .NUM_PES      (16)
) u_cgra (
    // Clock and Reset
    .clk          (clk_100mhz),
    .rst_n        (system_reset_n),

    // APB Slave Interface
    .psel         (apb_psel),
    .penable      (apb_penable),
    .pwrite       (apb_pwrite),
    .paddr        (apb_paddr),
    .pwdata       (apb_pwdata),
    .prdata       (apb_prdata),
    .pready       (apb_pready),
    .pslverr      (apb_pslverr),

    // AXI4 Master Interface (Burst-Capable)
    .m_axi_awaddr (axi_awaddr),
    .m_axi_awlen  (axi_awlen),      // Burst length
    .m_axi_awsize (axi_awsize),     // Beat size
    .m_axi_awburst(axi_awburst),    // Burst type (INCR)
    .m_axi_awvalid(axi_awvalid),
    .m_axi_awready(axi_awready),
    .m_axi_wdata  (axi_wdata),
    .m_axi_wstrb  (axi_wstrb),
    .m_axi_wlast  (axi_wlast),      // Last beat in burst
    .m_axi_wvalid (axi_wvalid),
    .m_axi_wready (axi_wready),
    .m_axi_bvalid (axi_bvalid),
    .m_axi_bready (axi_bready),
    .m_axi_araddr (axi_araddr),
    .m_axi_arlen  (axi_arlen),      // Burst length
    .m_axi_arsize (axi_arsize),     // Beat size
    .m_axi_arburst(axi_arburst),    // Burst type (INCR)
    .m_axi_arvalid(axi_arvalid),
    .m_axi_arready(axi_arready),
    .m_axi_rdata  (axi_rdata),
    .m_axi_rlast  (axi_rlast),      // Last beat in burst
    .m_axi_rvalid (axi_rvalid),
    .m_axi_rready (axi_rready),

    // Interrupt
    .irq          (cgra_interrupt),

    // Debug (optional ILA probes)
    .synthesis_keep           (synthesis_keep_signal),
    .dbg_dma_busy             (),
    .dbg_dma_read_state       (),
    .dbg_dma_write_state      (),
    .dbg_dma_fifo_full        (),
    .dbg_dma_fifo_empty       (),
    .dbg_dma_write_words_remaining()
);
```

### Clock and Reset Requirements

| Signal | Requirement |
|--------|-------------|
| clk | 50 MHz validated on XC7Z020 hardware; synthesis scripts use 100 MHz target |
| rst_n | Synchronous, active-low (assert for at least 1 cycle; 2+ recommended) |

---

## C Driver API

```c
// CGRA Driver API — Version 3.0 (UIO+CMA+devmem for Zynq-7000)
#include <stdint.h>

#define CGRA_BASE     0x40000000  // Configure for your SoC

// Register offsets (see Register Map section for full descriptions)
#define DMA_CTRL      0x00    // [0]=start (auto-clear)
#define DMA_STATUS    0x04    // [0]=busy, [1]=done
#define DMA_SRC       0x08
#define DMA_DST       0x0C
#define DMA_SIZE      0x10
#define CU_CTRL       0x20    // [0]=start, [1]=soft_reset
#define CU_STATUS     0x24    // [0]=busy, [1]=done
#define CU_CYCLES     0x28    // Active (non-stalled) cycle count
#define CU_TIMEOUT    0x2C    // Max wall-clock cycles (0 = unlimited)
#define DMA_ERROR     0x38    // [0]=error_flag, [2:1]=error_code (RO, W1C via IRQ_STATUS[2])
#define IRQ_STATUS    0x30    // W1C: [0]=dma_done, [1]=cu_done, [2]=dma_error
#define IRQ_MASK      0x34
#define RESULT_DATA   0x40    // PE[15] output (global_result)
#define RESULT_STATUS 0x44    // [0]=result_valid
#define LOOP_START    0x48    // HW loop start PC [15:0]
#define LOOP_END      0x4C    // HW loop end PC [15:0] (inclusive)
#define LOOP_COUNT    0x50    // Extra iterations beyond first pass [15:0]
#define RESULT_ROW0   0x58    // East-edge row 0 accumulator
#define RESULT_ROW1   0x5C    // East-edge row 1 accumulator
#define RESULT_ROW2   0x60    // East-edge row 2 accumulator
#define RESULT_ROW3   0x64    // East-edge row 3 accumulator
#define LOOP2_START   0x68    // Outer loop start PC [15:0]
#define LOOP2_END     0x6C    // Outer loop end PC [15:0]
#define LOOP2_COUNT   0x70    // Outer loop extra iterations [15:0]
#define TILE_BANK_SEL 0x74    // Double-buffer select [0]
#define DMA_SRC_STRIDE 0x14   // 2D: source row stride (bytes)
#define DMA_ROWS      0x18    // 2D: row count (0 = 1D mode)
#define DMA_COLS      0x1C    // 2D: columns per row (bytes)

#define REG(off) (*(volatile uint32_t*)(CGRA_BASE + (off)))

// Wait for DMA completion
static inline void cgra_dma_wait(void) {
    while (!(REG(DMA_STATUS) & 0x2));  // Wait for Done bit
    REG(IRQ_STATUS) = 0x1;             // W1C clear DMA Done IRQ
}

// Wait for CU completion
static inline void cgra_exec_wait(void) {
    while (REG(CU_STATUS) & 0x1);     // Wait for not Busy
    REG(IRQ_STATUS) = 0x2;             // W1C clear CU Done IRQ
}

// Load data to Tile Memory (bank 0-3, offset in bytes)
void cgra_load_tile(uint32_t src_phys, uint32_t bank, uint32_t offset, uint32_t size) {
    REG(DMA_SRC)  = src_phys;
    REG(DMA_DST)  = 0x10000000 | (bank << 12) | offset;
    REG(DMA_SIZE) = size;
    REG(DMA_CTRL) = 1;
    cgra_dma_wait();
}

// Configure PE (64-bit config, double-pump: HI word first, LO word commits)
void cgra_config_pe(uint32_t pe_id, uint32_t slot, uint64_t config,
                    uint32_t scratch_phys, uint32_t scratch_virt) {
    uint32_t base = 0x20000000 | (pe_id << 7) | (slot << 3);
    // HI word (addr[2]=0 — latches upper 32 bits)
    *(uint32_t*)scratch_virt = (uint32_t)(config >> 32);
    REG(DMA_SRC) = scratch_phys; REG(DMA_DST) = base;
    REG(DMA_SIZE) = 4; REG(DMA_CTRL) = 1; cgra_dma_wait();
    // LO word (addr[2]=1 — commits full 64-bit entry)
    *(uint32_t*)scratch_virt = (uint32_t)config;
    REG(DMA_SRC) = scratch_phys; REG(DMA_DST) = base | 4;
    REG(DMA_SIZE) = 4; REG(DMA_CTRL) = 1; cgra_dma_wait();
}

// Execute context range with hardware loop (loop_count=0: run range once)
void cgra_run_loop(uint32_t loop_start, uint32_t loop_end, uint32_t loop_count) {
    REG(LOOP_START) = loop_start;
    REG(LOOP_END)   = loop_end;
    REG(LOOP_COUNT) = loop_count;
    REG(CU_CTRL)    = 1;
    cgra_exec_wait();
}

// Clear all PE accumulators (ACC_CLR to all 16 PEs, run once)
void cgra_acc_clr(uint32_t scratch_phys, uint32_t scratch_virt) {
    const uint64_t acc_clr_cfg = 0x000000000000000FULL;  // opcode=15
    for (int pe = 0; pe < 16; pe++)
        cgra_config_pe(pe, 0, acc_clr_cfg, scratch_phys, scratch_virt);
    cgra_run_loop(0, 0, 0);
}

// Read east-edge results (4 rows for 4×4 FC output)
void cgra_get_results(uint32_t results[4]) {
    results[0] = REG(RESULT_ROW0);
    results[1] = REG(RESULT_ROW1);
    results[2] = REG(RESULT_ROW2);
    results[3] = REG(RESULT_ROW3);
}
```

---

## RTL File Summary

| Module | File | Lines | Description |
|--------|------|-------|-------------|
| cgra_top | cgra_top.sv | ~904 | Top-level: DMA, CU, tile memory, APB CSR, PE array, loop-aware auto-stop |
| cgra_apb_csr | cgra_apb_csr.sv | ~381 | APB interface (28 registers, W1C IRQ, DMA_ERROR, protected write guards) |
| cgra_dma_engine | cgra_dma_engine.sv | ~1199 | AXI4 DMA: 32-word FIFO, 2D stride, W_LOCAL fast-drain, SLVERR/DECERR capture, abort safety |
| cgra_control_unit | cgra_control_unit.sv | ~379 | FSM, 2-level nested loops, timeout, loops_done_o, global stall |
| cgra_tile_memory | cgra_tile_memory.sv | ~302 | 4-bank x 4096 SRAM, double-buffer bank_sel, prefetch PC |
| cgra_array | cgra_array.sv | ~244 | Parameterized N*M PE mesh (generate blocks) |
| cgra_tile | cgra_tile.sv | ~230 | PE + Router wrapper with branch passthrough |
| cgra_pe | cgra_pe.sv | ~767 | 21-op ISA, 3-stage pipeline (_r/_r2), 40-bit sat MAC, INT8/16 SIMD with overflow-safe accumulation |
| cgra_router | cgra_router.sv | ~519 | 5-port mesh router (N/E/S/W/Local, unicast/multicast) |
| cgra_config_mem_bsg | bsg_mem/cgra_config_mem_bsg.sv | ~94 | BSG SRAM wrapper (16x64-bit config RAM per PE) |
| **Total** | **17 files** | **~5,900** | All `.sv` files under `00_src/` + `00_src/bsg_mem/` |

---

## Software Stack (07_sw/)

### Components

| Component | Files | Lines | Description |
|-----------|-------|-------|-------------|
| **CGRA Driver** | driver/cgra_driver.{c,h} | ~519 | UIO+CMA Linux driver for PYNQ-Z2; full register API, IRQ handling |
| **Tiler Library** | lib/cgra_tiler.{c,h} | ~340 | Im2Col + CSC conversion; CGRA-aware 4-row tile chunking |
| **LPR Golden Model** | lib/lpr_golden.{c,h} | ~400 | Pure-C reference CNN (no ONNX, no float); bit-exact int32 output |
| **LPR Demo** | app/lpr_demo.c | ~426 | HW/SW latency comparison: FC MatMul on CGRA vs. ARM |
| **CGRA Accelerator** | app/lpr_cgra_accel.c | ~350 | Production classifier: Conv/Pool on ARM, FC on CGRA (Q8.8 activations) |
| **Hex Dumper** | app/dump_cgra_hex.c | ~200 | Generates config.mem / image.mem / golden.mem for the RAP testbench suite |
| **Golden Model Test** | app/lpr_golden_test.c | ~180 | Standalone golden model validation (no hardware required) |
| **Tiler Test** | app/test_tiler.c | ~222 | Tiler library unit tests |
| **Bare-Metal Regression** | baremetal/{main.c, cgra.h, uart.h, gic.{h,c}, start.s, linker.ld} | ~1700 | OCM-resident ARM ELF, 25-group / 96-check CGRA regression streaming results over UART0; includes a self-contained ARMv7 GIC driver for the round-3 interrupt-delivery test |

### LPR Golden Model

The golden model is a pure-C11 CNN running the full Vietnamese LP character classifier with zero external dependencies.

**Network:** 28×28 grayscale → Conv1 (3×3, 1→8ch, ReLU) → MaxPool 2×2 → Conv2 (3×3, 8→16ch, ReLU) → MaxPool 2×2 → FC (784→30) → Argmax

**Character set (30 classes):** `0–9`, `A–Z` excluding I, O, Q

**Total weights:** 24,798 int32 values (97 KB); serialized to `golden_weights.bin`

```bash
cd 07_sw
make test                        # Build + run with synthetic weights (no HW needed)
build/lpr_golden_test weights.bin image.bin   # Run with trained weights + single image
```

Intermediate layer dumps are written to `golden_dump/` (Conv1, Pool1, Conv2, Pool2, FC outputs) for layer-by-layer comparison against CGRA hardware results.

### Driver Features
- UIO-based register access (userspace I/O, no kernel module needed)
- CMA buffer allocation (`/dev/cma`) for physically-contiguous DMA buffers
- Full register map API (DMA, CU, IRQ, Hardware Loop, Results)
- Interrupt-driven completion via `poll()` on UIO file descriptor

### Tiler Library
- `im2col_nhwc()` — Standard Im2Col for convolution layers
- `im2col_4x4_tile()` — CGRA-aware tiling (4-row chunks for west-edge input)
- `dense_to_csc()` — Dense matrix → Compressed Sparse Column conversion
- `csc_spmv_sw()` — Software SpMV reference (validation/fallback)

### CGRA Accelerator App
- Conv1/Pool1/Conv2/Pool2 layers run on ARM CPU using the golden model
- FC layer (784→30) is fully offloaded to the CGRA with Q8.8 activations and INT8 weights
- Calls `cgra_acc_clr` before each inference, then drives 61 DMA+CU chunk iterations
- Reads RESULT_ROW0-3 and applies argmax for the final character prediction

### Bare-Metal Hardware Regression (`07_sw/baremetal/`)

A standalone arm-none-eabi ELF that boots from OCM, brings up UART0 directly,
and exercises the CGRA over the AXI GP0 APB interface — no Linux, no driver,
no XSDB scripting in the loop. Used to validate the silicon-equivalent
hardware behaviour of the synthesized design after every Vivado push.

| File | Purpose |
|------|---------|
| `start.s` | ARM Cortex-A9 reset vector. Disables IRQ/FIQ, sets `VBAR=0x4000`, enables VFP/NEON (CPACR cp10/cp11 + FPEXC.EN), zeros BSS, calls `main`. Includes a vector table with tagged trap handlers (`r11` carries the trap type, `lr` carries the faulting PC). |
| `linker.ld` | OCM-only layout. Vectors at `0x4000`, `.init`/`.text` immediately after, stack top at `0x1FFC0`. DMA staging buffer is in DDR at `0x100000`. |
| `uart.h` | Polled Zynq PS UART0 driver. `uart_init()` resets the FIFOs and writes `BAUD_GEN=124, BAUD_DIV=6` (115200 baud at the 100 MHz UART reference clock that ps7_init configures). `uart_puts()` drains the TX FIFO at every newline so the host CH340 never drops a line on long bursts. |
| `cgra.h` | Full ISA opcode set, source/route field constants, status bit definitions, register-access inlines, 1D and 2D DMA helpers (`cgra_dma`, `cgra_dma_2d`), async DMA + CU helpers (`cgra_dma_start`, `cgra_dma_done`, `cgra_cu_start`, `cgra_cu_done`, `cgra_wait_dma_and_cu`), `cgra_config_pe` which drives the PE Config RAM double-pump with slot-0 broadcast to all 16 contexts, and `cgra_config_pe_slot` which targets a single context slot for heterogeneous multi-instruction PE programs. |
| `gic.h` / `gic.c` | Bare-metal ARMv7 GIC v1 driver targeting the Zynq-7000 GIC (distributor `0xF8F01000` / CPU interface `0xF8F00100`). ~150 LOC, no Vitis BSP dependency. APIs: `gic_init`, `gic_register_isr`, `gic_enable_irq_id`, `gic_set_priority`, `gic_set_target`, `gic_set_level_high`, plus a `gic_irq_dispatch` top-half that the IRQ vector calls to read `GICC_IAR`, dispatch the registered handler, and write `GICC_EOIR`. The CGRA IRQ ID is exposed as `CGRA_IRQ_ID = 61` (IRQ_F2P[0] = SPI 29 + 32 base). |
| `main.c` | The 25-group / 96-check regression itself. |

#### Test Groups (96 checks total)

**Round 1 — register, DMA, basic CU, IRQ polling, stress (64 checks)**

| # | Group | Checks | Coverage |
|---|-------|--------|----------|
| 1 | Register sanity | 5 | Reset values for `DMA_STATUS`, `CU_STATUS`, `LOOP_END`, `LOOP2_END`; `CU_TIMEOUT` round-trip |
| 2 | All RW registers | 15 | Four-pattern (A5/5A/00/FF) write/read on every R/W register including `IRQ_MASK`, `LOOP*`, `LOOP2*`, `TILE_BANK_SEL` |
| 3 | DMA round-trip 16 B | 3 | DDR→Tile→DDR with 4-word integrity check |
| 4 | DMA round-trip 1 KB | 3 | 256-word integrity check |
| 5 | DMA varied sizes | 4 | 4 / 32 / 256 / 4096 byte transfers |
| 6 | DMA 2D strided | 3 | 4 rows × 16 B with `SRC_STRIDE=32` |
| 7 | Back-to-back DMA | 1 | 16 sequential DMAs, no state leak |
| 8 | Tile bank isolation | 4 | Two banks at `addr[13:12]` stride |
| 9 | PASS0 East routing | 2 | Row 0, 4× East hops |
| 10 | PASS0 South routing | 2 | Col 0, 4× South + 3× East hops |
| 11 | All four rows | 5 | Different immediates on rows 0-3 |
| 12 | `RESULT_DATA` (PE[3,3]) | 5 | Direct register + `RESULT_STATUS` valid bit |
| 13 | Loop count sweep | 4 | Counts of 1, 5, 16, 100 |
| 14 | `CU_CYCLES` monotonicity | 2 | Cycles grow with loop count |
| 15 | `IRQ_STATUS` W1C | 4 | DMA done, CU done, write-1-to-clear |
| 16 | Stress repeats | 1 | 20 iterations of test 11 with varying immediates |
| 17 | CU soft reset | 2 | `BUSY` clears, `DONE` correctly sticky |

**Round 2 — ALU, MAC, multi-context, routing, concurrency, error path (28 checks)**

| # | Group | Checks | Coverage |
|---|-------|--------|----------|
| 18 | ALU smoke | 6 | `ADD`, `SUB`, `MUL`, `AND`, `OR`, `XOR` end-to-end on real silicon (`src0=W`, `src1=IMM`, RESULT_ROW0 captures the operation result) |
| 19 | Multi-instruction context | 3 | Heterogeneous slots 0..3 written via `cgra_config_pe_slot`, single-sweep + looped, last-slot value propagates through to `RESULT_ROW0` |
| 20 | Nested LOOP2 over LOOP | 3 | 5 inner × 3 outer = 15 iterations, `CU_CYCLES` in expected range |
| 21 | N + W routing + multicast | 5 | North column chain → row 0; West→South→East perimeter chain → row 3; PE[1,1] multicast to N/E/S landing on three `RESULT_ROW`s simultaneously |
| 22 | MAC saturation boundary | 2 | 512 cycles of `0x7FFF² ≈ 2³⁰` peg the 40-bit accumulator (MAX_POS_40), 32-bit output clamps to `0x7FFFFFFF`; `ACC_CLR` pre-step proves the accumulator resets |
| 23 | DMA + CU concurrency | 3 | CU and DMA kicked in adjacent APB writes at sizes 64 / 256 / 1 K / 4 K B — both finish without deadlock or AXI error, CU result intact |
| 24 | DMA error + register protection | 6 | Bad source raises `DMA_ERROR=0x7` + `IRQ_STATUS[2]`; W1C clears IRQ; engine recovers on next start; `DMA_SRC` busy-write rejected; `CU_TIMEOUT` busy-write rejected |

**Round 3 — GIC interrupt delivery (4 checks)**

| # | Group | Checks | Coverage |
|---|-------|--------|----------|
| 25 | GIC interrupt delivery | 4 | DMA-done IRQ delivered (counter advances), CU-done IRQ delivered (counter advances — typically a rapid burst of ~37 fires while the CU's east-edge result-row register churns), masked path is silent (`IRQ_MASK=0` produces no ISR fires), 5 back-to-back DMAs deliver 5 IRQs. Uses an OCM-resident ARMv7 GIC v1 driver and an IRQ-mode dispatcher in `start.s`. The same `irq` net is exported to LED4 on the board — **LED4 has been visually confirmed to pulse** during the test, proving the full PL→PS interrupt path works end to end. |

#### Running on hardware

```bash
make baremetal           # arm-none-eabi-gcc -> 07_sw/baremetal/cgra_test.elf
make run_baremetal       # programs PL, runs ps7_init, loads ELF, captures UART
cat 02_log/uart.log      # full test transcript
```

The flow expects the JTAG probe and CH340 UART to be visible in WSL2 (see the
USB passthrough note in the FPGA bring-up section above). Diagnostic registers
can be inspected from the host at any time via `make reg_dump` / `make reg_read
REG=...` even while the ELF is parked in its `wfi` hang loop.

---

## Design Quality

### RTL Coding Standards

| Standard | Compliance |
|----------|------------|
| SystemVerilog IEEE 1800-2017 | ✅ |
| `always_ff` / `always_comb` | ✅ |
| `unique case` with `default` | ✅ |
| `typedef enum` for FSMs | ✅ |
| `logic` type (no `reg`/`wire` mix) | ✅ |
| Synchronous reset pattern | ✅ |
| No inferred latches | ✅ |
| lowRISC style guide (logic rules) | ✅ |

### Synthesis Readiness

| Check | Status |
|-------|--------|
| Lint clean (major) | ✅ |
| No combinational loops | ✅ |
| Clock domain: single | ✅ |
| Reset: synchronous active-low | ✅ |
| Memory inference | ✅ SRAM/BRAM |
| BSG memory macros | ✅ Integrated |

### Known Design Constraints

- **Tile memory prefetch:** Uses `next_context_pc` (not `context_pc+1`) for SRAM read-ahead. Correctly handles hardware loop backward jumps and dynamic branches.
- **DMA local write path:** Tile/config destination addresses use the W_LOCAL state machine (1 cycle/word). DDR destinations use the AXI burst path. Both share the same 32-entry FIFO; do not mix local and AXI transfers in a single DMA transaction.
- **ACC_CLR required between inferences:** The MAC accumulator persists across CU runs. Always execute an ACC_CLR sweep (opcode 15, slot 0 broadcast to all PEs) before starting a new FC computation.
- **Hardware loop count:** `LOOP_COUNT=N` runs the context range N+1 total times (N additional passes beyond the first). Use `LOOP_COUNT=0` to run the range exactly once.
- **Loop-aware auto-stop:** The CU asserts `done` only when all loop iterations are exhausted AND context_pc reaches slot 15. Dynamic branches at PC=15 are respected (auto-stop deferred until branch completes).
- **Protected registers:** DMA config registers (SRC/DST/SIZE/STRIDE/ROWS/COLS) are write-protected while DMA is busy. CU config registers (TIMEOUT/LOOP*/LOOP2*) are write-protected while CU is busy. TILE_BANK_SEL is write-protected while either DMA or CU is busy.
- **AXI error detection:** DMA engine detects both SLVERR (2'b01) and DECERR (2'b10) on BRESP/RRESP channels. Error code and flag are captured in DMA_ERROR (0x38) and IRQ_STATUS[2]. Errors are sticky (cleared on new cfg_start or via W1C on IRQ_STATUS).
- **Current Fmax:** 50 MHz on Zynq-7000 (3-stage pipeline already implemented; timing closure on DSP48 paths may require additional constraints for 100 MHz).

---

## Roadmap

### Completed Features

| Feature | Status |
|---------|--------|
| Predicated Execution | `pred_en`, `pred_inv` in config frame |
| Memory Banking | 4 banks x 4096 words, double-buffered (bank_sel) |
| Multicast Broadcast | PE outputs to all 4 neighbors |
| Parameterized N*M Array | `generate` blocks with ROWS/COLS (default 4x4) |
| Mixed-Precision SIMD | INT8x4 / INT16x2 dot-product (config bits [50:49]) |
| Dynamic Branching | PE predicate drives CU PC jump (config bits [48:44]) |
| Nested Hardware Loops | 2-level (L1+L2) with loop-aware auto-stop |
| 2D Strided DMA | DMA_SRC_STRIDE, DMA_ROWS, DMA_COLS registers |
| Pipelined ALU | 3-stage pipeline: decode → _r (operand register) → _r2 (multiply/compute register) |
| BSG Memory Macros | ASIC-ready SRAM wrappers |
| RELU / MAX Operations | ANN/LPR extensions (opcodes 19-20) |
| LIF Neuron | Hardware Leaky Integrate-and-Fire (opcode 18) |
| East-Edge Result Capture | 4-row APB-readable registers |
| Bi-Directional DMA | AXI4 read + write engines, 32-word FIFO, W_LOCAL fast-drain |
| Linux Driver (UIO+CMA) | Zynq-7000 PetaLinux 2022.2 ready |
| **JTAG Bring-Up Flow** | XSDB-driven program / ps7_init / reg dump / ELF load from WSL2 over usbipd |
| **Bare-Metal HW Regression** | 25-group / 96-check OCM-resident ARM ELF — APB CSR + 1D/2D DMA + ALU (ADD/SUB/MUL/AND/OR/XOR) + MAC saturation + multi-context PC + N/W routing + multicast + DMA-CU concurrency + AXI error + register protection + end-to-end GIC interrupt delivery via PL→PS `IRQ_F2P[0]` (96/96 PASS on Zynq XC7Z020) |
| LPR Golden Model | Pure-C int32 reference (Vietnamese 30-class) |
| CGRA-Accelerated Classifier | FC offload with Q8.8 activations |
| End-to-End Simulation | Suite RAP: 61-chunk FC verified bit-exact |
| Protocol Monitor | AXI4 + APB assertion-based verification |
| UVM-Inspired Testbench | 8915 tests, 25 suites, covergroups, TLM scoreboards, clocking blocks |
| **Verdict Hardening** | Scoreboard errors propagate to global verdict; zero-test guard; watchdog signals failure; 8 checks tightened to exact/bounded values |

### Future Enhancements

| Enhancement | Priority | Description |
|-------------|----------|-------------|
| **Device Tree Overlay** | High | UIO entry for PetaLinux `/dev/uio0` (Vivado bitstream + bring-up flow already done) |
| **On-Chip Learning (STDP)** | Medium | Spike-Timing-Dependent Plasticity for local weight updates |
| **Python Config Generator** | Medium | Script to generate 64-bit config frames from assembly syntax |
| **Floating-Point PE** | Low | Optional FPU datapath for scientific computing |

---

## References

1. A. Podobas, K. Sano, and S. Matsuoka, "A Survey on Coarse-Grained Reconfigurable Architectures from a Performance Perspective," arXiv preprint arXiv:2004.04509, 2020.
2. L. Liu et al., "A Survey of Coarse-Grained Reconfigurable Architecture," ACM Computing Surveys, 2019.
3. W. Maass, "Networks of Spiking Neurons: The Third Generation of Neural Network Models," Neural Networks, vol. 10, no. 9, pp. 1659–1671, 1997.
4. W. Gerstner and W. M. Kistler, *Spiking Neuron Models: Single Neurons, Populations, Plasticity*. Cambridge University Press, 2002.
5. M. Pfeiffer and T. Pfeil, "Deep Learning With Spiking Neurons: Opportunities and Challenges," Frontiers in Neuroscience, vol. 12, 2018.
6. K. Roy, A. Jaiswal, and P. Panda, "Towards Spike-Based Machine Intelligence with Neuromorphic Computing," Nature, vol. 575, pp. 607–617, 2019.
7. E. O. Neftci, H. Mostafa, and F. Zenke, "Surrogate Gradient Learning in Spiking Neural Networks," arXiv preprint arXiv:1901.09948, 2019.

---

## License

Copyright © 2026. All rights reserved.

This IP core is provided for evaluation purposes. Commercial licensing available upon request.

---

<div align="center">

**CGRA Accelerator for SNN Inference**

*Silicon-Ready | 8915/8915 Sim Tests | 96/96 Hardware Tests | 100% ISA Coverage | 25 Sim Suites*

</div>
