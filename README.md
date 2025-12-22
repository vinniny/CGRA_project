# CGRA SoC Accelerator

A **Coarse-Grained Reconfigurable Array (CGRA)** accelerator with pipelined DMA engine, APB control interface, and AXI4-Lite memory master. Designed for efficient dataflow computation on FPGA with neuromorphic computing support.

---

## Datasheet Summary

| Parameter | Value |
|-----------|-------|
| **Array Size** | 4×4 = 16 Processing Elements |
| **Clock** | 50-100 MHz (100 MHz verified) |
| **Data Width** | 32-bit |
| **Payload Width** | 16-bit (mesh interconnect) |
| **Config Width** | 64-bit per context |
| **Context Depth** | 16 slots per PE |
| **Scratchpad** | 256×32-bit per PE |
| **Register File** | 16×32-bit per PE |
| **Accumulator** | 40-bit signed (MAC/LIF) |
| **Tile Memory** | 4 banks × 4KB (shared input buffer) |
| **DMA FIFO** | 8 × 32-bit (producer-consumer) |
| **ISA** | 19 operations (all verified) |
| **Verification** | 141 tests, 23 suites |
| **Target** | DE10-Standard (Cyclone V) |

---

## Quick Start

```bash
# Run 140-test verification (Icarus Verilog)
make sim

# Run with Cadence Xcelium
make sim TOOL=xcelium

# Run Xcelium in GUI mode
make gui

# View waveforms
make wave              # GTKWave (iverilog)
make wave TOOL=xcelium # SimVision (xcelium)

# Clean generated files
make clean
```

---

## How It Works

### System Overview

The CGRA accelerator offloads compute-intensive dataflow operations from the CPU. The typical workflow:

1. **CPU programs configuration** via APB registers
2. **DMA loads input data** from external RAM to Tile Memory
3. **DMA loads PE configurations** to config RAM
4. **CPU starts execution** via Control Unit register
5. **PE array processes data** in parallel (up to 16 cycles)
6. **Auto-stop or timeout** halts execution
7. **CPU reads results** via DMA or direct access

### Data Flow Architecture

```
           CPU / Host
               │
      ┌────────┴────────┐
      │   APB Slave     │ ← Config Registers
      │   (CSR Block)   │
      └────────┬────────┘
               │
      ┌────────┴────────┐     ┌──────────────────┐
      │  Control Unit   │────▶│  Tile Memory     │
      │  (FSM + Timer)  │     │  4 banks × 1024  │
      └────────┬────────┘     └────────┬─────────┘
               │                       │
      ┌────────┴────────┐              │
      │  DMA Engine     │──────────────┤
      │  (AXI Master)   │              │
      └────────┬────────┘              │
               │                       ▼
      ┌────────┴───────────────────────┴─────────┐
      │              4×4 PE Array                 │
      │  ┌────┐  ┌────┐  ┌────┐  ┌────┐          │
      │  │PE00│──│PE01│──│PE02│──│PE03│ ← Row 0  │
      │  └─┬──┘  └─┬──┘  └─┬──┘  └─┬──┘          │
      │    │       │       │       │              │
      │  ┌─▼──┐  ┌─▼──┐  ┌─▼──┐  ┌─▼──┐          │
      │  │PE10│──│PE11│──│PE12│──│PE13│ ← Row 1  │
      │  └────┘  └────┘  └────┘  └────┘          │
      │    ...   (mesh broadcast continues)       │
      └──────────────────────────────────────────┘
```

---

## Integration Guide

### Instantiating the IP

```systemverilog
cgra_top #(
    .DATA_WIDTH(32),
    .ADDR_WIDTH(32)
) u_cgra (
    .clk(clk_100mhz),
    .rst_n(system_reset_n),
    
    // APB Slave (from CPU/Processor)
    .psel(apb_psel),
    .penable(apb_penable),
    .pwrite(apb_pwrite),
    .paddr(apb_paddr),
    .pwdata(apb_pwdata),
    .prdata(apb_prdata),
    .pready(apb_pready),
    .pslverr(apb_pslverr),
    
    // AXI4-Lite Master (to external RAM)
    .m_axi_awaddr(axi_awaddr),
    .m_axi_awvalid(axi_awvalid),
    .m_axi_awready(axi_awready),
    .m_axi_wdata(axi_wdata),
    .m_axi_wstrb(axi_wstrb),
    .m_axi_wvalid(axi_wvalid),
    .m_axi_wready(axi_wready),
    .m_axi_bvalid(axi_bvalid),
    .m_axi_bready(axi_bready),
    .m_axi_araddr(axi_araddr),
    .m_axi_arvalid(axi_arvalid),
    .m_axi_arready(axi_arready),
    .m_axi_rdata(axi_rdata),
    .m_axi_rvalid(axi_rvalid),
    .m_axi_rready(axi_rready),
    
    // Interrupt
    .irq(cgra_irq),
    
    // Synthesis Keeper (prevents optimization)
    .synthesis_keep(cgra_keep)
);
```

### Address Map

The CGRA occupies a single APB address window. Base address is configurable in your SoC integration.

| Offset | Register | R/W | Description |
|--------|----------|-----|-------------|
| 0x00 | DMA_CTRL | RW | [0] Start (auto-clear) |
| 0x04 | DMA_STATUS | RO | [0] Busy, [1] Done |
| 0x08 | DMA_SRC | RW | Source address |
| 0x0C | DMA_DST | RW | Destination address |
| 0x10 | DMA_SIZE | RW | Transfer size (bytes) |
| 0x20 | CU_CTRL | RW | [0] Start, [1] Soft Reset |
| 0x24 | CU_STATUS | RO | [0] Busy, [1] Done |
| 0x28 | CU_CYCLES | RO | Cycle counter |
| **0x2C** | **CU_TIMEOUT** | **RW** | **Max cycles (0 = no limit)** |
| 0x30 | IRQ_STATUS | RO | [0] DMA Done, [1] CU Done |
| 0x34 | IRQ_MASK | RW | IRQ enable mask |

---

## C Driver Example

```c
#include <stdint.h>

// Base address (set by your SoC address map)
#define CGRA_BASE 0x40000000

// Register offsets
#define DMA_CTRL    0x00
#define DMA_STATUS  0x04
#define DMA_SRC     0x08
#define DMA_DST     0x0C
#define DMA_SIZE    0x10
#define CU_CTRL     0x20
#define CU_STATUS   0x24
#define CU_CYCLES   0x28
#define CU_TIMEOUT  0x2C

// Helper macros
#define REG(offset) (*(volatile uint32_t*)(CGRA_BASE + offset))

// Wait for DMA completion
void cgra_dma_wait(void) {
    while (!(REG(DMA_STATUS) & 0x2));  // Wait for Done bit
}

// Wait for execution completion
void cgra_exec_wait(void) {
    while (REG(CU_STATUS) & 0x1);  // Wait for Busy to clear
}

// Load data from external RAM to Tile Memory bank
void cgra_load_data(uint32_t src_addr, uint32_t bank, uint32_t offset, uint32_t size) {
    // Construct Tile Memory destination address
    // Format: 0x1XXX_XBOO where B=bank[1:0], O=offset
    uint32_t dst = 0x10000000 | (bank << 12) | offset;
    
    REG(DMA_SRC)  = src_addr;
    REG(DMA_DST)  = dst;
    REG(DMA_SIZE) = size;
    REG(DMA_CTRL) = 1;  // Start
    cgra_dma_wait();
}

// Load 64-bit configuration to PE config RAM
void cgra_config_pe(uint32_t pe_id, uint32_t slot, uint64_t config) {
    // Config Memory address format: 0x2PPP_SSSH
    // P = PE_ID[3:0], S = Slot[3:0], H = Hi/Lo select
    uint32_t base = 0x20000000 | (pe_id << 8) | (slot << 3);
    
    // Double-pump protocol: Hi word first, then Lo word
    uint32_t hi = (uint32_t)(config >> 32);
    uint32_t lo = (uint32_t)(config & 0xFFFFFFFF);
    
    // Write high word (addr | 0x4)
    REG(DMA_DST) = base | 0x4;
    dram_write(0x1004, hi);  // Temp location
    REG(DMA_SRC) = 0x1004;
    REG(DMA_SIZE) = 4;
    REG(DMA_CTRL) = 1;
    cgra_dma_wait();
    
    // Write low word (commits 64-bit)
    REG(DMA_DST) = base;
    dram_write(0x1004, lo);
    REG(DMA_SRC) = 0x1004;
    REG(DMA_SIZE) = 4;
    REG(DMA_CTRL) = 1;
    cgra_dma_wait();
}

// Execute CGRA with timeout
void cgra_run(uint32_t max_cycles) {
    REG(CU_TIMEOUT) = max_cycles;  // 0 = no limit
    REG(CU_CTRL) = 0x2;  // Soft reset first
    REG(CU_CTRL) = 0x1;  // Start
    cgra_exec_wait();
}

// Example: Vector addition
void vector_add_example(void) {
    // Load input vectors to Tile Memory Bank 0
    cgra_load_data(0x80000000, 0, 0, 64);  // 16 words
    
    // Configure PE[0,0] for ADD operation
    // opcode=1 (ADD), src0=4 (West), src1=6 (Immediate), imm=0
    uint64_t config = (1 << 0) | (4 << 6) | (6 << 10);
    cgra_config_pe(0, 0, config);
    
    // Execute for 16 cycles
    cgra_run(16);
    
    // Read cycle count
    uint32_t cycles = REG(CU_CYCLES);
}
```

---

## PE Architecture

### Processing Element Block Diagram

```
                    ┌─────────────────────────────────────┐
     N,E,S,W ──────▶│  Operand Mux (src0_sel, src1_sel)   │
     Immediate ────▶│  0=RF, 1=N, 2=E, 3=S, 4=W, 5=SPM, 6=Imm
     SPM/RF ───────▶│                                     │
                    └────────────┬────────────────────────┘
                                 │ operand0, operand1
                                 ▼
                    ┌─────────────────────────────────────┐
                    │         ALU / MAC Unit              │
                    │  • 19 opcodes (ADD, SUB, MUL, ...)  │
                    │  • 40-bit accumulator (saturating)  │
                    │  • SHL/SHR: 5-bit shift (0-31)      │
                    │  • SHR is arithmetic (sign-extend)  │
                    └────────────┬────────────────────────┘
                                 │ alu_result
                                 ▼
                    ┌─────────────────────────────────────┐
                    │   Output Routing (route_mask)       │
                    │   Broadcast to N/E/S/W neighbors    │
                    └─────────────────────────────────────┘
```

### Source Select Values

| Value | Source | Description |
|-------|--------|-------------|
| 0 | RF | Register File (local) |
| 1 | N | North neighbor |
| 2 | E | East neighbor |
| 3 | S | South neighbor |
| 4 | W | West neighbor (Tile Memory) |
| 5 | SPM | Scratchpad Memory |
| 6 | Imm | 16-bit Immediate |

### Important Design Notes

> [!IMPORTANT]
> **Payload Width Limitation**: The mesh interconnect uses 16-bit payloads. Data passed between PEs (via src=N/E/S/W) is **sign-extended from 16-bit to 32-bit**.

> [!NOTE]
> **Arithmetic Shift Right**: Op 9 (SHR) performs **arithmetic shift** (`>>>`), preserving the sign bit. This is optimal for DSP applications.

> [!NOTE]
> **Shift Range**: Both SHL and SHR use 5-bit shift amounts `operand1[4:0]`, supporting shifts from 0 to 31.

---

## ISA Reference (19 Operations)

| Op | Name | Operation | Verified |
|----|------|-----------|----------|
| 0 | NOP | No operation | ✅ |
| 1 | ADD | A + B (saturating) | ✅ |
| 2 | SUB | A - B (saturating) | ✅ |
| 3 | MUL | A × B (32-bit) | ✅ |
| 4 | MAC | Acc += A × B | ✅ Suite T |
| 5 | AND | A & B | ✅ |
| 6 | OR | A \| B | ✅ |
| 7 | XOR | A ^ B | ✅ |
| 8 | SHL | A << B (variable) | ✅ Suite U |
| 9 | SHR | A >> B (variable) | ✅ Suite T, U |
| 10 | CMP_GT | (A > B) ? 1 : 0 | ✅ Suite T |
| 11 | CMP_LT | (A < B) ? 1 : 0 | ✅ Suite T, U |
| 12 | CMP_EQ | (A == B) ? 1 : 0 | ✅ Suite P |
| 13 | LOAD_SPM | Load from scratchpad | ✅ Suite T |
| 14 | STORE_SPM | Store to scratchpad | ✅ Suite T |
| 15 | ACC_CLR | Clear accumulator | ✅ Suite T, V |
| 16 | PASS0 | Pass operand 0 | ✅ Suite T |
| 17 | PASS1 | Pass operand 1 | ✅ Suite T |
| 18 | LIF | Leaky Integrate-Fire (neuron) | ✅ Suite V |

---

## Configuration Frame Format (64-bit)

```
 63    40 39    24 23 22 21  18 17  14 13  10  9   6  5   0
┌────────┬────────┬──┬──┬──────┬──────┬──────┬──────┬──────┐
│extended│  imm   │pi│pe│route │ dst  │ src1 │ src0 │opcode│
│ 24-bit │ 16-bit │1 │1 │4-bit │4-bit │4-bit │4-bit │6-bit │
└────────┴────────┴──┴──┴──────┴──────┴──────┴──────┴──────┘
```

| Field | Bits | Description |
|-------|------|-------------|
| opcode | [5:0] | ALU operation (0-18) |
| src0_sel | [9:6] | Source 0: 0=RF, 1=N, 2=E, 3=S, 4=W, 5=SPM, 6=Imm |
| src1_sel | [13:10] | Source 1: same as src0 |
| dst_sel | [17:14] | Register file write address |
| route_mask | [21:18] | Output enable: [3]=N, [2]=E, [1]=S, [0]=W |
| pred_en | [22] | Predicate enable |
| pred_inv | [23] | Invert predicate |
| imm | [39:24] | 16-bit signed immediate |
| extended | [63:40] | Routing header / metadata |

---

## Verification Status

**141/141 TESTS PASSED - SILICON READY** ✅

| Simulator | Version | Status | Runtime |
|-----------|---------|--------|---------|
| Icarus Verilog | 10.0+ | ✅ Pass | ~3 min |
| Cadence Xcelium | 24.09-s005 | ✅ Pass | 11 sec |

### Test Suite Summary

| Suite | Focus | Tests |
|-------|-------|-------|
| A-F | Infrastructure, DMA, Protocol | 80 |
| G-I | Constrained Random, Assertions | 16 |
| J-P | Computation, Comparators | 32 |
| Q | Random ALU Stress | 1 |
| Q2 | Barrel Shifter (0-31) | 1 |
| R-S | Boundary, Reset | 2 |
| T | ISA Completion | 8 |
| U | Diagnostics | 3 |
| V | Neuromorphic LIF | 3 |
| **Total** | **23 Suites** | **141** |

### Stress Testing

Suite Q1 runs configurable random stress iterations:
- Default: 20 iterations (quick check)
- Stress mode: **100,000 iterations** verified with Xcelium
- Covers: **All 19 opcodes** with random operands (16-bit positive values)

Suite Q2 runs barrel shifter exhaustive tests:
- **64 vectors**: All shift amounts 0-31 for both SHL and SHR
- Verifies 5-bit shift amount fix (`[4:0]` instead of `[3:0]`)

---

## Design Constraints & Known Limitations

### Payload Width (16-bit)

| Aspect | Limitation |
|--------|------------|
| **Inter-PE Data** | 16-bit signed (-32768 to +32767) |
| **Sign Extension** | Automatic to 32-bit in PE |
| **Full 32-bit Path** | Only via local RF or SPM |

### State-Dependent Operations

| Opcode | Notes |
|--------|-------|
| MAC (4) | Requires ACC_CLR first; accumulates across cycles |
| SPM (13,14) | Write before read; 256-word addressable |
| LIF (18) | Membrane potential persists; threshold comparison |

### Pipeline Timing

| Operation | Min Cycles |
|-----------|------------|
| Config load | 2 cycles (DMA + commit) |
| Execute | 3 cycles (recommended) |
| ACC_CLR | 3 cycles (ensure propagation) |

---

## RTL Change Log

### Barrel Shifter Fix (December 2024)

**Files Modified**: `cgra_pe.sv` lines 396-400

```diff
- alu_result <= operand0 << operand1[3:0];  // 4-bit (0-15)
+ alu_result <= operand0 << operand1[4:0];  // 5-bit (0-31)

- alu_result <= operand0 >> operand1[3:0];  // Logical
+ alu_result <= $signed(operand0) >>> operand1[4:0];  // Arithmetic
```

**Reason**: RISC-V compatibility requires 32-bit shift support (0-31). The original 4-bit mask limited shifts to 0-15.

**Impact**: Verified with Suite Q2 (64 vectors covering all shift amounts).

---

## Key Features

### Mesh Broadcast
- Each PE broadcasts output to all 4 neighbors simultaneously
- Enables systolic-style spatial pipelines
- West edge receives data from Tile Memory banks

### Programmable Auto-Stop
- Set `CU_TIMEOUT` register to limit execution cycles
- Eliminates CPU polling for fixed-length computations
- Value 0 = infinite (manual stop required)

### 64-bit Double-Pump Configuration
- Config RAM stores 64-bit instructions
- DMA writes high word (addr | 0x4), then low word (addr)
- Low word write commits the full 64-bit frame

### Neuromorphic Support
- LIF (Leaky Integrate-Fire) opcode for spiking neural networks
- Built-in accumulator with configurable threshold
- Enables edge AI / low-power inference

---

## Project Structure

```
CGRA_project/
├── 00_src/                    # RTL Source (11 modules)
│   ├── cgra_top.sv               # Top-level integration
│   ├── cgra_axi_csr.sv           # APB CSR interface
│   ├── cgra_dma_engine.sv        # Pipelined DMA master
│   ├── cgra_control_unit.sv      # Execution FSM
│   ├── cgra_tile_memory.sv       # 4-bank shared memory
│   ├── cgra_array_4x4.sv         # 4×4 PE mesh
│   ├── cgra_tile.sv              # PE + Router wrapper
│   ├── cgra_pe.sv                # Processing Element
│   ├── cgra_router.sv            # 5-port XY router
│   ├── axi_ram.sv                # Memory model
│   └── bsg_mem/                  # BSG memory primitives
│
├── 01_bench/                  # Verification
│   ├── tb_top.sv                 # Master test harness
│   ├── tb_tasks.svh              # Driver layer
│   ├── tb_test_suites.svh        # 141 test vectors (23 suites)
│   ├── restore.tcl               # Xcelium waveform setup
│   └── cgra_protocol_monitor.sv  # AXI compliance checker
│
├── 02_test/                   # Test documentation
├── 03_sim/                    # Simulation outputs
├── 04_doc/                    # Design documentation
├── Makefile                   # Build system
└── README.md                  # This file
```

---

## Prerequisites

```bash
# Ubuntu/Debian (Icarus Verilog)
sudo apt-get install iverilog gtkwave

# Cadence Xcelium (requires license)
# Contact Cadence for installation
```

- [Icarus Verilog](http://iverilog.icarus.com/) (v10.0+) - Open source
- [Cadence Xcelium](https://www.cadence.com/) - Commercial (optional)
- [GTKWave](http://gtkwave.sourceforge.net/) / SimVision - Waveform viewers

---

## Makefile Commands

**Simulator Selection:**
- Default: Icarus Verilog
- Override: `make sim TOOL=xcelium`
- Permanent: Edit line 20 in Makefile: `TOOL ?= xcelium`

| Command | Description |
|---------|-------------|
| `make sim` | Run 140-test verification |
| `make sim TOOL=xcelium` | Run with Cadence Xcelium |
| `make gui` | Xcelium GUI mode with waveforms |
| `make wave` | Open waveform viewer |
| `make compile` | Compile only (iverilog) |
| `make create_flist` | Generate Xcelium file list |
| `make clean` | Remove generated files |
| `make help` | Show commands |

---

## RTL Coding Standards

| Standard | Status |
|----------|--------|
| `always_ff` / `always_comb` | ✅ |
| `unique case` with `default` | ✅ |
| `typedef enum` for FSMs | ✅ |
| `logic` type (no `reg`) | ✅ |
| Synchronous reset pattern | ✅ |
| No inferred latches | ✅ |

---

## License

Educational/Research project - December 2024
