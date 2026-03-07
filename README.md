# CGRA Accelerator for SNN Inference

<div align="center">

**Coarse-Grained Reconfigurable Array IP Core**

*Version 2.6.0 | March 2026*

[![Silicon Ready](https://img.shields.io/badge/Status-Silicon%20Ready-brightgreen)]()
[![Tests](https://img.shields.io/badge/Tests-All%20Passing-brightgreen)]()
[![ISA](https://img.shields.io/badge/ISA-21%20Operations-blue)]()
[![License](https://img.shields.io/badge/License-Commercial-blue)]()

</div>

---

## Product Overview

High-performance **Coarse-Grained Reconfigurable Array (CGRA)** accelerator IP designed for **Sparse Spiking Neural Network (SNN) Inference** and **License Plate Recognition (LPR)**. Features a 4×4 mesh of processing elements with integrated DMA, APB control interface, hardware support for **Leaky Integrate-and-Fire (LIF)** neuron dynamics, and **ANN extensions** (RELU, MAX) for convolutional inference.

### Key Innovations
- **Spatially Programmable Mesh**: 4×4 PE array with multicast routing for efficient sparse matrix computation.
- **Hardware LIF Neurons**: Dedicated state-update logic within each PE for biologically plausible spiking dynamics.
- **ANN Activation Extensions**: Hardware RELU and MAX operations for convolutional neural network layers.
- **Double-Buffered Configuration**: Latency-hiding context memory allowing "hot-swap" reconfiguration between network layers.
- **Row-Banked Memory**: 4-bank interleaved SRAM system to maximize parallel data access.
- **Bi-Directional DMA**: AXI4 burst master with read and write engines for zero-copy data movement.
- **Hardware Loop Controller**: Programmable loop start/end/count CSRs for autonomous iteration.

### Target Applications
- **Spiking Neural Networks**: Image classification, event-based sensing (DVS)
- **License Plate Recognition**: Convolutional inference with tiled MatMul offload (PYNQ-Z2 demo)
- **Sparse Linear Algebra**: Compressed Sparse Column (CSC) matrix operations
- **Signal Processing**: FIR/IIR filters, FFT acceleration
- **Edge AI**: Ultra-low latency inference on FPGA

---

## Datasheet

### Electrical Characteristics

| Parameter | Symbol | Min | Typ | Max | Unit |
|-----------|--------|-----|-----|-----|------|
| Operating Frequency | f_CLK | 10 | 100 | 213.72 | MHz |
| Supply Voltage | V_DD | 0.9 | 1.0 | 1.1 | V |
| Operating Temperature | T_A | -40 | 25 | 85 | °C |
| Reset Pulse Width | t_RST | 10 | - | - | ns |

*Fmax of 213.72 MHz achieved with timing-optimized synthesis on Zynq UltraScale+*

### Architecture Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Array Configuration** | 4×4 (16 PEs) | Scalable to 8×8, N×M |
| **Data Width** | 32-bit | Full precision throughout |
| **Config Width** | 64-bit | Per-context instruction |
| **Context Depth** | 16 slots/PE | Multi-context switching |
| **Instruction Set** | 21 operations | All verified (incl. RELU, MAX) |
| **Accumulator** | 40-bit signed | Saturating arithmetic |

### Memory Resources

| Memory | Size | Width | Type |
|--------|------|-------|------|
| PE Register File | 16 entries | 32-bit | Flip-flop |
| PE Scratchpad | 256 entries | 32-bit | SRAM |
| PE Config RAM | 16 entries | 64-bit | BSG SRAM |
| Tile Memory | 4 × 1024 entries | 32-bit | SRAM |
| DMA FIFO | 8 entries | 32-bit | Flip-flop |

### Interface Specifications

| Interface | Standard | Width | Description |
|-----------|----------|-------|-------------|
| Control | APB 2.0 | 32-bit | Register access |
| Memory | AXI4 Full | 32-bit | DMA burst master |
| Interrupt | Level | 1-bit | Active high |
| Clock | Single | - | Rising edge |
| Reset | Active-low | - | Synchronous |

### Timing Specifications

| Parameter | Symbol | Min | Typ | Max | Unit |
|-----------|--------|-----|-----|-----|------|
| Clock Period | t_CLK | 4.68 | 10 | 100 | ns |
| APB Setup Time | t_SU | 2 | - | - | ns |
| APB Hold Time | t_HD | 1 | - | - | ns |
| DMA Latency | t_DMA | 4 | 6 | 10 | cycles |
| Config Load Time | t_CFG | 2 | - | - | cycles |
| Execution Startup | t_EXEC | 3 | - | - | cycles |

### Resource Utilization (Target: Xilinx Zynq UltraScale+ XCZU4EV)

| Resource | Usage | Available | Utilization |
|----------|-------|-----------|-------------|
| CLB LUTs | ~12,500 | 230,400 | ~5.5% |
| Flip-Flops | ~8,200 | 460,800 | ~1.8% |
| Block RAM (36Kb) | 24 | 312 | ~7.7% |
| DSP48E2 Slices | 32 | 1,728 | ~1.9% |

---

## Quick Start

### Simulation

```bash
# Run full verification suite (Cadence Xcelium 24.09+)
make sim                # Compile, elaborate, simulate (6169 tests)

# Split flow for debugging
make compile            # Compile RTL + TB sources
make build              # Elaborate design
make run                # Run simulation

# Interactive GUI mode  
make gui                # Launch SimVision waveform viewer

# Clean build artifacts
make clean              # Remove logs and compiled databases
```

### Building Software

```bash
cd 07_sw
make all                # Build driver + tiler + LPR demo
make test               # Run tiler unit tests
make clean              # Clean build artifacts
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
    │  (Host) │  APB    │  │  • 20 Registers (10 RW, 1 W1C, 9 RO) │  │
    └─────────┘         │  │  • DMA, CU, IRQ, Loop, Result CSRs  │  │
                        │  │  • 256B address space, 32-bit access │  │
                        │  └────────────────┬─────────────────────┘  │
                        │                   │                         │
                        │  ┌────────────────┴─────────────────────┐  │
                        │  │           Control Unit                │  │
                        │  │  • 3-state FSM (IDLE/RUN/FINISH)     │  │
                        │  │  • Programmable timeout              │  │
                        │  │  • Auto-stop on completion           │  │
                        │  └────────────────┬─────────────────────┘  │
                        │                   │                         │
    ┌─────────┐         │  ┌────────────────┴─────────────────────┐  │
    │ External│◄────────┼──┤         Pipelined DMA Engine         │  │
    │   RAM   │  AXI4   │  │  • Read/Write state machines         │  │
    └─────────┘ (Burst) │  │  • 8-entry synchronous FIFO          │  │
                        │  │  • AXI4 burst (up to 8 beats/req)    │  │
                        │  │  • 4KB boundary protection           │  │
                        │  └────────────────┬─────────────────────┘  │
                        │                   │                         │
                        │  ┌────────────────┴─────────────────────┐  │
                        │  │       Tile Memory (16KB SRAM)         │  │
                        │  │  • 4 banks × 1024 × 32-bit           │  │
                        │  │  • Bank per array row                │  │
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

---

## Register Map

### APB Address Space (20 Registers)

**DMA Engine Control (5 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x00 | DMA_CTRL | RW | 0x0 | [0] Start (auto-clear) |
| 0x04 | DMA_STATUS | RO | 0x0 | [0] Busy, [1] Done |
| 0x08 | DMA_SRC | RW | 0x0 | Source address (32-bit) |
| 0x0C | DMA_DST | RW | 0x0 | Destination address (32-bit) |
| 0x10 | DMA_SIZE | RW | 0x0 | Transfer size in bytes |

**Control Unit (4 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x20 | CU_CTRL | RW | 0x0 | [0] Start, [1] Soft Reset |
| 0x24 | CU_STATUS | RO | 0x0 | [0] Busy, [1] Done |
| 0x28 | CU_CYCLES | RO | 0x0 | Execution cycle counter |
| 0x2C | CU_TIMEOUT | RW | 0x0 | Max cycles (0 = unlimited) |

**Interrupt Control (2 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x30 | IRQ_STATUS | W1C | 0x0 | [0] DMA Done, [1] CU Done |
| 0x34 | IRQ_MASK | RW | 0x0 | IRQ enable mask |

**Global Result Capture (2 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x40 | RESULT_DATA | RO | 0x0 | PE[15] output (global_result) |
| 0x44 | RESULT_STATUS | RO | 0x0 | [0] result_valid |

**Hardware Loop Control (3 registers):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x48 | LOOP_START | RW | 0x0 | Hardware loop start PC [15:0] |
| 0x4C | LOOP_END | RW | 0x0 | Hardware loop end PC [15:0] |
| 0x50 | LOOP_COUNT | RW | 0x0 | Hardware loop iteration count [15:0] |

**LPR Row Results (4 registers - East-edge output capture):**

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x58 | RESULT_ROW0 | RO | 0x0 | East-edge result row 0 (PE[0,3]) |
| 0x5C | RESULT_ROW1 | RO | 0x0 | East-edge result row 1 (PE[1,3]) |
| 0x60 | RESULT_ROW2 | RO | 0x0 | East-edge result row 2 (PE[2,3]) |
| 0x64 | RESULT_ROW3 | RO | 0x0 | East-edge result row 3 (PE[3,3]) |

### DMA Address Decode

| Address Prefix | Target | Bit Fields |
|----------------|--------|------------|
| 0x0XXX_XXXX | External AXI | Direct pass-through |
| 0x1XXX_XXXX | Tile Memory | [13:12]=Bank, [11:0]=Byte offset |
| 0x2XXX_XXXX | Config RAM | [11:8]=PE, [6:3]=Slot, [2]=Hi/Lo |

---

## Instruction Set Architecture

### Opcode Summary (21 Operations)

| Op | Mnemonic | Operation | Flags | Latency |
|----|----------|-----------|-------|---------|
| 0 | NOP | No operation | - | 1 |
| 1 | ADD | A + B (sat) | OVF | 1 |
| 2 | SUB | A - B (sat) | OVF | 1 |
| 3 | MUL | A × B | - | 1 |
| 4 | MAC | Acc += A × B | OVF | 1 |
| 5 | AND | A & B | - | 1 |
| 6 | OR | A \| B | - | 1 |
| 7 | XOR | A ^ B | - | 1 |
| 8 | SHL | A << B[4:0] | - | 1 |
| 9 | SHR | A >>> B[4:0] | - | 1 |
| 10 | CMP_GT | A > B ? 1 : 0 | - | 1 |
| 11 | CMP_LT | A < B ? 1 : 0 | - | 1 |
| 12 | CMP_EQ | A == B ? 1 : 0 | - | 1 |
| 13 | LOAD_SPM | RF ← SPM[A] | - | 1 |
| 14 | STORE_SPM | SPM[A] ← B | - | 1 |
| 15 | ACC_CLR | Acc = 0 | - | 1 |
| 16 | PASS0 | Output = A | - | 1 |
| 17 | PASS1 | Output = B | - | 1 |
| 18 | LIF | Spiking neuron | SPIKE | 1 |
| 19 | RELU | max(0, A) | - | 1 |
| 20 | MAX | max(A, B) signed | - | 1 |

### Configuration Frame Format (64-bit)

```
Bit Position:
 63        40 39      24 23 22 21    18 17    14 13    10 9     6 5     0
┌────────────┬──────────┬──┬──┬────────┬────────┬────────┬────────┬───────┐
│  extended  │   imm    │pi│pe│ route  │  dst   │  src1  │  src0  │opcode │
│   24-bit   │  16-bit  │1b│1b│  4-bit │  4-bit │  4-bit │  4-bit │ 6-bit │
└────────────┴──────────┴──┴──┴────────┴────────┴────────┴────────┴───────┘
```

| Field | Bits | Range | Description |
|-------|------|-------|-------------|
| opcode | [5:0] | 0-20 | ALU operation code |
| src0_sel | [9:6] | 0-6 | Operand A source |
| src1_sel | [13:10] | 0-6 | Operand B source |
| dst_sel | [17:14] | 0-15 | RF write address |
| route_mask | [21:18] | 0-15 | Output direction mask |
| pred_en | [22] | 0-1 | Enable predication |
| pred_inv | [23] | 0-1 | Invert predicate |
| imm | [39:24] | ±32767 | Signed immediate |
| extended | [63:40] | - | Reserved/routing |

---

## Verification

### Test Results

| Metric | Value |
|--------|-------|
| Total Tests Executed | **6169 PASS** |
| Test Failures | **0** |
| Protocol Violations | **0** |
| Verification Architecture | Constrained Random Verification (CRV) |
| Test Suites | 38 suites (A-AC + AD + AE + LPR + 3 meta-suites) |
| ISA Coverage | 21/21 operations verified |
| Protocol Compliance | AXI4 + APB assertion-based monitors |
| Status | **SILICON READY** ✅ |

### Test Execution Summary

**Latest Simulation Run (March 2026):**
- **6169 tests PASSED**
- **0 tests FAILED**
- **0 protocol errors** (AXI4/APB)
- **83 warnings** (all from intentional DMA abort tests - expected behavior)
- **2819189 simulation cycles**
- **Verdict: PASS** ✅

### CRV Meta-Suites (Restructured Test Architecture)

| Meta-Suite | Merges | Focus | Vectors | Status |
|------------|--------|-------|---------|--------|
| System Integrity | A, B, C, R | APB, DMA, Protocol, Streaming | 400+ randomized | ✅ PASS |
| Fabric Stress | L, O | Pipeline, Parallel, Routing | 300+ randomized | ✅ PASS |
| Robustness | S, W, AA | Reset, Stall, IRQ injection | 300+ randomized | ✅ PASS |
| ISA Regression (AD) | M, N, Q, T | 500 random vectors/opcode | 6000+ | ✅ PASS |
| LPR Features | — | RELU, MAX, Loop CSRs, East-edge | 20+ | ✅ PASS |
| DMA Writeback (AE) | — | AXI Write, Round-trip, Burst | 8 tests | ✅ PASS |

### Legacy Test Suites (A-AC)

| Suite | Description | Vectors |
|-------|-------------|---------|
| A-F | Infrastructure (APB, DMA, Protocol, Stress, System) | ~80 |
| G-I | Advanced (CRV, Negative, Compute Core) | ~16 |
| J-P | Computation (ISA, Spatial, Math, Comparators) | ~32 |
| Q1-Q4 | Random Stress (ALU, Shifter, MAC, SPM) | ~4 |
| R-S | Robustness (Boundary, Reset) | ~2 |
| T-V | ISA Completion, Diagnostics, Neuromorphic | ~14 |
| W-Z | DMA Hang, Advanced Diag, IRQ, Burst Regression | ~22 |
| AA-AC | Metastability, Advanced Stress, Precision Math | ~9 |

### Supported Simulators

| Simulator | Version | Status | Notes |
|-----------|---------|--------|-------|
| Cadence Xcelium | 24.09+ | ✅ Pass | Primary tool |
| Verilator | 5.x+ | ✅ Pass | CI/local |
| Synopsys VCS | 2023+ | Untested | — |

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
    
    // Synthesis Keeper & Debug
    .synthesis_keep(synthesis_keep_signal),
    .dbg_dma_busy (/* optional ILA probe */),
    .dbg_dma_read_state (),
    .dbg_dma_write_state(),
    .dbg_dma_fifo_full  (),
    .dbg_dma_fifo_empty (),
    .dbg_dma_write_words_remaining()
);
```

### Clock and Reset Requirements

| Signal | Requirement |
|--------|-------------|
| clk | 10-200 MHz, 50% duty cycle ±5% (Fmax 213 MHz) |
| rst_n | Synchronous, active-low, min 2 cycles |

---

## C Driver API

```c
// CGRA Driver API - Version 2.6 (UIO+CMA for PYNQ-Z2)
#include <stdint.h>

#define CGRA_BASE     0x40000000  // Configure for your SoC

// Register offsets
#define DMA_CTRL      0x00    // [0]=start (auto-clear)
#define DMA_STATUS    0x04    // [0]=busy, [1]=done
#define DMA_SRC       0x08
#define DMA_DST       0x0C
#define DMA_SIZE      0x10
#define CU_CTRL       0x20    // [0]=start, [1]=soft_reset
#define CU_STATUS     0x24    // [0]=busy, [1]=done
#define CU_CYCLES     0x28
#define CU_TIMEOUT    0x2C
#define IRQ_STATUS    0x30    // W1C: [0]=dma_done, [1]=cu_done
#define IRQ_MASK      0x34
#define RESULT_DATA   0x40    // PE[15] output (global_result)
#define RESULT_STATUS 0x44    // [0]=result_valid
#define LOOP_START    0x48    // HW loop start PC
#define LOOP_END      0x4C    // HW loop end PC
#define LOOP_COUNT    0x50    // HW loop iteration count
#define RESULT_ROW0   0x58    // East-edge row 0
#define RESULT_ROW1   0x5C    // East-edge row 1
#define RESULT_ROW2   0x60    // East-edge row 2
#define RESULT_ROW3   0x64    // East-edge row 3

// Register access macro
#define REG(off) (*(volatile uint32_t*)(CGRA_BASE + (off)))

// Wait for DMA completion
static inline void cgra_dma_wait(void) {
    while (!(REG(DMA_STATUS) & 0x2));  // Wait for Done
}

// Wait for execution completion
static inline void cgra_exec_wait(void) {
    while (REG(CU_STATUS) & 0x1);  // Wait for not Busy
}

// Load data to Tile Memory
void cgra_load_tile(uint32_t src, uint32_t bank, uint32_t offset, uint32_t size) {
    uint32_t dst = 0x10000000 | (bank << 12) | offset;
    REG(DMA_SRC)  = src;
    REG(DMA_DST)  = dst;
    REG(DMA_SIZE) = size;
    REG(DMA_CTRL) = 1;    // Start
    cgra_dma_wait();
}

// Configure PE (64-bit config)
void cgra_config_pe(uint32_t pe, uint32_t slot, uint64_t config) {
    uint32_t base = 0x20000000 | (pe << 8) | (slot << 3);
    // High word first, then low word commits
    REG(DMA_DST) = base | 0x4;
    // ... write high word via DMA
    REG(DMA_DST) = base;
    // ... write low word via DMA
}

// Execute with timeout and hardware loop
void cgra_run(uint32_t max_cycles) {
    REG(CU_TIMEOUT) = max_cycles;
    REG(CU_CTRL) = 0x2;   // Soft reset
    REG(CU_CTRL) = 0x1;   // Start
    cgra_exec_wait();
}

// Read east-edge results (4 rows for 4×4 matrix output)
void cgra_read_results(uint32_t results[4]) {
    results[0] = REG(RESULT_ROW0);
    results[1] = REG(RESULT_ROW1);
    results[2] = REG(RESULT_ROW2);
    results[3] = REG(RESULT_ROW3);
}

// Read cycle count
static inline uint32_t cgra_get_cycles(void) {
    return REG(CU_CYCLES);
}
```

---

## RTL File Summary

| Module | File | Lines | Description |
|--------|------|-------|-------------|
| cgra_top | cgra_top.sv | ~764 | Top-level integration with LPR result registers |
| cgra_apb_csr | cgra_apb_csr.sv | ~268 | APB register interface (20 registers) |
| cgra_dma_engine | cgra_dma_engine.sv | ~780 | Bi-directional AXI DMA controller |
| cgra_control_unit | cgra_control_unit.sv | ~293 | Execution FSM with hardware loop |
| cgra_tile_memory | cgra_tile_memory.sv | ~280 | 4-bank SRAM with boundary checks |
| cgra_array_4x4 | cgra_array_4x4.sv | ~1175 | PE mesh instantiation |
| cgra_tile | cgra_tile.sv | ~224 | PE + Router wrapper |
| cgra_pe | cgra_pe.sv | ~631 | Processing Element (21-op ISA) |
| cgra_router | cgra_router.sv | ~417 | 5-port mesh router |
| cgra_config_mem_bsg | bsg_mem/cgra_config_mem_bsg.sv | ~81 | BSG SRAM wrapper |
| axi_ram | axi_ram.sv | ~373 | AXI RAM model (simulation) |
| **Total RTL** | **17 files** | **~5825** | — |

---

## Software Stack (07_sw/)

### Components

| Component | Files | Lines | Description |
|-----------|-------|-------|-------------|
| **CGRA Driver** | driver/cgra_driver.{c,h} | ~519 | UIO+CMA Linux driver for PYNQ-Z2 |
| **Tiler Library** | lib/cgra_tiler.{c,h} | ~340 | Im2Col + CSC conversion for convolution |
| **LPR Demo** | app/lpr_demo.c | ~426 | License Plate Recognition demo application |
| **Tiler Test** | app/test_tiler.c | ~222 | Tiler library unit tests |

### Driver Features (cgra_driver.h)
- UIO-based register access (userspace I/O)
- CMA buffer allocation for DMA transfers
- Full register map API (DMA, CU, IRQ, Loop, Results)
- Hardware loop configuration (start/end/count)
- East-edge result readback (4 rows)

### Tiler Library (cgra_tiler.h)
- `im2col_nhwc()` — Standard Im2Col for convolution layers
- `im2col_4x4_tile()` — CGRA-aware tiling (4-row chunks for west-edge input)
- `dense_to_csc()` — Dense matrix → Compressed Sparse Column conversion
- `csc_spmv_sw()` — Software SpMV reference (validation/fallback)

### LPR Demo Pipeline (lpr_demo.c)
1. Load pre-extracted character images (28×28 grayscale, int32)
2. Dense-to-CSC weight conversion
3. Im2Col tiling for conv layer input
4. DMA input tiles into CGRA tile memory
5. Load MatMul config, execute on CGRA (timed)
6. Read back east-edge results via APB
7. Software-only MatMul for comparison (timed)
8. Display latency comparison (HW vs SW)

### Building

```bash
cd 07_sw
make all        # Build driver, tiler, LPR demo, and tests
make test       # Run tiler tests
make clean      # Clean build artifacts
```

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

---

## Roadmap

### Current Capabilities

| Feature | Status | Notes |
|---------|--------|-------|
| Predicated Execution | ✅ Implemented | `pred_en`, `pred_inv` in config frame |
| Memory Banking | ✅ Implemented | 4 banks × 1024 words (bank per row) |
| Multicast Broadcast | ✅ Implemented | PE outputs to all 4 neighbors |
| Self-Checking TB | ✅ Implemented | CRV with golden models |
| BSG Memory Macros | ✅ Implemented | ASIC-ready SRAM wrappers |
| Double-Buffer Config | ✅ Implemented | Ping-pong config memory |
| RELU / MAX Operations | ✅ Implemented | ANN/LPR extensions (opcodes 19-20) |
| Hardware Loop CSRs | ✅ Implemented | Programmable start/end/count |
| East-Edge Result Capture | ✅ Implemented | 4-row APB-readable registers |
| Bi-Directional DMA | ✅ Implemented | AXI4 read + write engines |
| Linux Driver (UIO+CMA) | ✅ Implemented | PYNQ-Z2 ready |
| Im2Col Tiler Library | ✅ Implemented | CSC + tile-aware conversion |
| LPR Demo Application | ✅ Implemented | MatMul offload with HW/SW comparison |
| Protocol Monitor | ✅ Implemented | AXI4 assertion-based verification |

### Future Enhancements

| Enhancement | Priority | Effort | Description |
|-------------|----------|--------|-------------|
| **Parameterized Array** | High | Medium | Convert to `generate` blocks with `ROWS`/`COLS` parameters for 2×2, 8×8, N×M exploration |
| **2D Strided DMA** | High | High | Add `STRIDE` register for efficient matrix/image sub-block access |
| **On-Chip Learning (STDP)** | Medium | High | Integrate Spike-Timing-Dependent Plasticity for local learning |
| **Mixed-Precision Support** | Medium | Medium | Support INT8/INT16 modes for efficiency |
| **Python Config Generator** | Medium | Low | Script to generate 64-bit config frames from assembly-like syntax |
| **Floating-Point PE** | Low | High | Optional FPU datapath for scientific computing |

### Software Toolchain

A complete CGRA deployment requires:

1. **Compiler**: Map Data Flow Graphs (DFG) to PE configuration
2. **Assembler**: Convert assembly → binary config files
3. **Runtime**: C/C++ API for kernel loading and execution

Reference implementations: [Morpher](https://github.com/ecolab-nus/morpher), [OpenCGRA](https://github.com/pnnl/OpenCGRA)

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

*Silicon-Ready • Verified • Production-Quality*

</div>
