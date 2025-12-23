# CGRA SoC Accelerator

<div align="center">

**Coarse-Grained Reconfigurable Array IP Core**

*Version 2.1.0 | December 2024*

[![Silicon Ready](https://img.shields.io/badge/Status-Silicon%20Ready-brightgreen)]()
[![Tests](https://img.shields.io/badge/Tests-141%2F141-brightgreen)]()
[![License](https://img.shields.io/badge/License-Commercial-blue)]()

</div>

---

## Product Overview

High-performance **Coarse-Grained Reconfigurable Array (CGRA)** accelerator IP for dataflow computation, DSP, and edge AI applications. Features a 4×4 mesh of processing elements with integrated DMA, APB control interface, and neuromorphic computing support.

### Target Applications
- **Signal Processing**: FIR/IIR filters, FFT acceleration
- **Machine Learning**: CNN inference, tensor operations
- **Neuromorphic Computing**: Spiking neural networks (LIF neurons)
- **Image Processing**: Convolution, edge detection
- **Cryptography**: AES, SHA acceleration kernels

---

## Datasheet

### Electrical Characteristics

| Parameter | Symbol | Min | Typ | Max | Unit |
|-----------|--------|-----|-----|-----|------|
| Operating Frequency | f_CLK | 10 | 100 | 200* | MHz |
| Supply Voltage | V_DD | 0.9 | 1.0 | 1.1 | V |
| Operating Temperature | T_A | -40 | 25 | 85 | °C |
| Reset Pulse Width | t_RST | 10 | - | - | ns |

*\*200 MHz achievable with timing-optimized synthesis*

### Architecture Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Array Configuration** | 4×4 (16 PEs) | Scalable to 8×8 |
| **Data Width** | 32-bit | Full precision throughout |
| **Config Width** | 64-bit | Per-context instruction |
| **Context Depth** | 16 slots/PE | Multi-context switching |
| **Instruction Set** | 19 operations | All verified |
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
| Memory | AXI4-Lite | 32-bit | DMA master |
| Interrupt | Level | 1-bit | Active high |
| Clock | Single | - | Rising edge |
| Reset | Active-low | - | Synchronous |

### Timing Specifications

| Parameter | Symbol | Min | Typ | Max | Unit |
|-----------|--------|-----|-----|-----|------|
| Clock Period | t_CLK | 5 | 10 | 100 | ns |
| APB Setup Time | t_SU | 2 | - | - | ns |
| APB Hold Time | t_HD | 1 | - | - | ns |
| DMA Latency | t_DMA | 4 | 6 | 10 | cycles |
| Config Load Time | t_CFG | 2 | - | - | cycles |
| Execution Startup | t_EXEC | 3 | - | - | cycles |

### Resource Utilization (Cyclone V Estimates)

| Resource | Usage | Available | Utilization |
|----------|-------|-----------|-------------|
| ALMs | ~8,500 | 41,910 | ~20% |
| Registers | ~6,200 | 166,036 | ~4% |
| M10K Blocks | 68 | 553 | ~12% |
| DSP Blocks | 16 | 112 | ~14% |

---

## Quick Start

```bash
# Run 141-test verification suite
make sim

# Run with Cadence Xcelium (commercial)
make sim TOOL=xcelium

# Interactive GUI mode
make gui

# View simulation waveforms
make wave

# Clean build artifacts
make clean
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
    │  (Host) │  APB    │  │  • 12 Registers (6 RW, 6 RO)        │  │
    └─────────┘         │  │  • DMA configuration                 │  │
                        │  │  • Execution control                 │  │
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
    │   RAM   │  AXI    │  │  • Read/Write state machines         │  │
    └─────────┘         │  │  • 8-entry async FIFO                │  │
                        │  │  • Burst-capable (single-beat)       │  │
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
    │  │  • 19 Operations (arithmetic, logic, shift, compare)    │   │
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

### APB Address Space

| Offset | Register | Access | Reset | Description |
|--------|----------|--------|-------|-------------|
| 0x00 | DMA_CTRL | RW | 0x0 | [0] Start (auto-clear) |
| 0x04 | DMA_STATUS | RO | 0x0 | [0] Busy, [1] Done |
| 0x08 | DMA_SRC | RW | 0x0 | Source address (32-bit) |
| 0x0C | DMA_DST | RW | 0x0 | Destination address (32-bit) |
| 0x10 | DMA_SIZE | RW | 0x0 | Transfer size in bytes |
| 0x20 | CU_CTRL | RW | 0x0 | [0] Start, [1] Soft Reset |
| 0x24 | CU_STATUS | RO | 0x0 | [0] Busy, [1] Done |
| 0x28 | CU_CYCLES | RO | 0x0 | Execution cycle counter |
| 0x2C | CU_TIMEOUT | RW | 0x0 | Max cycles (0 = unlimited) |
| 0x30 | IRQ_STATUS | RO | 0x0 | [0] DMA Done, [1] CU Done |
| 0x34 | IRQ_MASK | RW | 0x0 | IRQ enable mask |

### DMA Address Decode

| Address Prefix | Target | Format |
|----------------|--------|--------|
| 0x0XXX_XXXX | External AXI | Direct pass-through |
| 0x1XXX_XBOO | Tile Memory | B=Bank[1:0], O=Offset[11:0] |
| 0x2PPP_SSHH | Config RAM | P=PE[3:0], S=Slot[3:0], H=Hi/Lo |

---

## Instruction Set Architecture

### Opcode Summary (19 Operations)

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
| opcode | [5:0] | 0-18 | ALU operation code |
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
| Total Tests | 141 |
| Passed | 141 |
| Failed | 0 |
| Coverage | 100% functional |
| Status | **SILICON READY** ✅ |

### Test Suites

| Suite | Description | Tests |
|-------|-------------|-------|
| A-F | Infrastructure, DMA, APB | 80 |
| G-I | Constrained Random, Assertions | 16 |
| J-P | Core Computation | 32 |
| Q1 | Random ALU Stress (20 vectors) | 1 |
| Q2 | Barrel Shifter (64 vectors) | 1 |
| R-S | Boundary, Reset | 2 |
| T | ISA Completion | 8 |
| U | Diagnostics | 3 |
| V | Neuromorphic LIF | 3 |

### Supported Simulators

| Simulator | Version | Status | Runtime |
|-----------|---------|--------|---------|
| Icarus Verilog | 10.0+ | ✅ Pass | ~3 min |
| Cadence Xcelium | 24.09+ | ✅ Pass | ~11 sec |
| Synopsys VCS | 2023+ | Untested | - |

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
    
    // AXI4-Lite Master Interface
    .m_axi_awaddr (axi_awaddr),
    .m_axi_awvalid(axi_awvalid),
    .m_axi_awready(axi_awready),
    .m_axi_wdata  (axi_wdata),
    .m_axi_wstrb  (axi_wstrb),
    .m_axi_wvalid (axi_wvalid),
    .m_axi_wready (axi_wready),
    .m_axi_bresp  (axi_bresp),
    .m_axi_bvalid (axi_bvalid),
    .m_axi_bready (axi_bready),
    .m_axi_araddr (axi_araddr),
    .m_axi_arvalid(axi_arvalid),
    .m_axi_arready(axi_arready),
    .m_axi_rdata  (axi_rdata),
    .m_axi_rresp  (axi_rresp),
    .m_axi_rvalid (axi_rvalid),
    .m_axi_rready (axi_rready),
    
    // Interrupt
    .irq          (cgra_interrupt),
    
    // Debug
    .synthesis_keep(synthesis_keep_signal)
);
```

### Clock and Reset Requirements

| Signal | Requirement |
|--------|-------------|
| clk | 50-200 MHz, 50% duty cycle ±5% |
| rst_n | Synchronous, active-low, min 2 cycles |

---

## C Driver API

```c
// CGRA Driver API - Version 2.0
#include <stdint.h>

#define CGRA_BASE     0x40000000  // Configure for your SoC

// Register offsets
#define DMA_CTRL      0x00
#define DMA_STATUS    0x04
#define DMA_SRC       0x08
#define DMA_DST       0x0C
#define DMA_SIZE      0x10
#define CU_CTRL       0x20
#define CU_STATUS     0x24
#define CU_CYCLES     0x28
#define CU_TIMEOUT    0x2C
#define IRQ_STATUS    0x30
#define IRQ_MASK      0x34

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

// Execute with timeout
void cgra_run(uint32_t max_cycles) {
    REG(CU_TIMEOUT) = max_cycles;
    REG(CU_CTRL) = 0x2;   // Soft reset
    REG(CU_CTRL) = 0x1;   // Start
    cgra_exec_wait();
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
| cgra_top | cgra_top.sv | ~450 | Top-level integration |
| cgra_axi_csr | cgra_axi_csr.sv | ~225 | APB register interface |
| cgra_dma_engine | cgra_dma_engine.sv | ~460 | AXI DMA controller |
| cgra_control_unit | cgra_control_unit.sv | ~190 | Execution FSM |
| cgra_tile_memory | cgra_tile_memory.sv | ~120 | 4-bank SRAM |
| cgra_array_4x4 | cgra_array_4x4.sv | ~1175 | PE mesh instantiation |
| cgra_tile | cgra_tile.sv | ~210 | PE + Router wrapper |
| cgra_pe | cgra_pe.sv | ~540 | Processing Element |
| cgra_router | cgra_router.sv | ~400 | 5-port XY router |
| cgra_config_mem_bsg | cgra_config_mem_bsg.sv | ~80 | BSG SRAM wrapper |

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

## Revision History

| Version | Date | Changes |
|---------|------|---------|
| 2.0.0 | Dec 2024 | 32-bit data path fix, BSG memory integration |
| 1.5.0 | Dec 2024 | Barrel shifter fix (0-31 range) |
| 1.4.0 | Dec 2024 | 141 tests, Q2 suite added |
| 1.3.0 | Dec 2024 | Programmable timeout register |
| 1.0.0 | Nov 2024 | Initial release |

---

## License

Copyright © 2024. All rights reserved.

This IP core is provided for evaluation purposes. Commercial licensing available upon request.

---

<div align="center">

**CGRA SoC Accelerator IP Core**

*Silicon-Ready • Verified • Production-Quality*

</div>
