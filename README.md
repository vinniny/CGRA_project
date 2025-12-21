# CGRA SoC Accelerator

A **Coarse-Grained Reconfigurable Array (CGRA)** accelerator with pipelined DMA engine, APB control interface, and AXI4-Lite memory master. Designed for efficient dataflow computation on FPGA.

---

## Datasheet Summary

| Parameter | Value |
|-----------|-------|
| **Array Size** | 4×4 = 16 Processing Elements |
| **Clock** | 50-100 MHz |
| **Data Width** | 32-bit |
| **Config Width** | 64-bit per context |
| **Context Depth** | 16 slots per PE |
| **Scratchpad** | 256×32-bit per PE |
| **Register File** | 16×32-bit per PE |
| **Tile Memory** | 4 banks × 4KB (shared) |
| **DMA FIFO** | 8 × 32-bit |
| **ISA** | 9 verified operations |
| **Verification** | 126 tests, 19 suites |
| **Target** | DE10-Standard (Cyclone V) |

---

## Quick Start

```bash
# Run 126-test verification suite
make sim

# View waveforms (optional)
make wave

# Clean generated files
make clean
```

---

## Verification Status

**126/126 TESTS PASSED - SILICON READY** ✅

| Suite | Focus | Tests | Status |
|-------|-------|-------|--------|
| A | Register Logic & Config | 19 | ✅ |
| B | DMA Datapath | 16 | ✅ |
| C | Protocol Compliance | 15 | ✅ |
| D | Performance & Timing | 10 | ✅ |
| E | Stress Testing | 10 | ✅ |
| F | System Integration | 10 | ✅ |
| G | Constrained Random | 8 | ✅ |
| H | White-Box Assertions | 4 | ✅ |
| I | End-to-End Flow | 4 | ✅ |
| J | Computation Full Path | 5 | ✅ |
| K | Advanced Compute | 7 | ✅ |
| L | Spatial Pipeline (PE-to-PE) | 2 | ✅ |
| M | ISA Discovery | 7 | ✅ |
| N | Signed Arithmetic | 2 | ✅ |
| O | 16-Core Parallel Stress | 4 | ✅ |
| P | Comparator Decoder | 3 | ✅ |
| Q | Random Stress (20 vectors) | 1 | ✅ |
| R | Boundary Wrap | 1 | ✅ |
| S | Reset Recovery | 1 | ✅ |

---

## Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                          cgra_top                               │
├─────────────────────────────────────────────────────────────────┤
│  ┌──────────────┐  ┌───────────────┐  ┌──────────────────────┐ │
│  │  APB CSR     │  │ Control Unit  │  │   Tile Memory        │ │
│  │ (Registers)  │──│ (3-state FSM) │──│   (4 banks)          │ │
│  └──────────────┘  │  auto_stop    │  └──────────────────────┘ │
│         │          └───────────────┘           │               │
│  ┌──────┴──────────────────────────────────────┴──────────────┐│
│  │                 Pipelined DMA Engine                       ││
│  │  ┌─────────────┐   ┌────────┐   ┌──────────────┐          ││
│  │  │ Read Engine │──▶│  FIFO  │──▶│ Write Engine │          ││
│  │  │ (Producer)  │   │ (8-wd) │   │ (Consumer)   │          ││
│  │  └─────────────┘   └────────┘   └──────────────┘          ││
│  └───────────────────────────────────────────────────────────┘│
│                              │                                 │
│  ┌───────────────────────────┴────────────────────────────────┐│
│  │                    4×4 CGRA PE Array                       ││
│  │                  (Mesh Broadcast)                          ││
│  │  ┌───┬───┬───┬───┐                                         ││
│  │  │0,0│→0,1│→0,2│→0,3│ ← Row 0 (Bank 0)                     ││
│  │  ├───┼───┼───┼───┤                                         ││
│  │  │1,0│→1,1│→1,2│→1,3│ ← Row 1 (Bank 1)                     ││
│  │  ├───┼───┼───┼───┤                                         ││
│  │  │2,0│→2,1│→2,2│→2,3│ ← Row 2 (Bank 2)                     ││
│  │  ├───┼───┼───┼───┤                                         ││
│  │  │3,0│→3,1│→3,2│→3,3│ ← Row 3 (Bank 3)                     ││
│  │  └───┴───┴───┴───┘                                         ││
│  │     ↓ synthesis_keep                                       ││
│  └────────────────────────────────────────────────────────────┘│
└─────────────────────────────────────────────────────────────────┘
```

---

## APB Register Map

| Offset | Register | R/W | Description |
|--------|----------|-----|-------------|
| 0x00 | DMA_CTRL | RW | [0] Start (auto-clear) |
| 0x04 | DMA_STATUS | RO | [0] Busy, [1] Done (sticky) |
| 0x08 | DMA_SRC | RW | Source address (external RAM) |
| 0x0C | DMA_DST | RW | Destination address |
| 0x10 | DMA_SIZE | RW | Transfer size (bytes) |
| 0x14 | CU_CTRL | RW | [0] Start, [1] Soft Reset |
| 0x18 | CU_STATUS | RO | [0] Busy, [1] Done (sticky) |
| 0x1C | CU_CYCLES | RO | Cycle counter |

---

## ISA (Instruction Set Architecture)

| Opcode | Name | Operation | Verified |
|--------|------|-----------|----------|
| 0 | NOP | No operation | ✅ |
| 1 | ADD | A + B (saturating) | ✅ Suite M, Q |
| 2 | SUB | A - B (saturating) | ✅ Suite M, N |
| 3 | MUL | A × B (32-bit) | ✅ Suite M |
| 4 | MAC | Acc += A × B | |
| 5 | AND | A & B | ✅ Suite K, M, Q |
| 6 | OR | A \| B | ✅ Suite K, M, Q |
| 7 | XOR | A ^ B | ✅ Suite K, M, Q |
| 8 | SHL | A << B | ✅ Suite M |
| 9 | SHR | A >> B | |
| 10 | CMP_GT | (A > B) ? 1 : 0 | |
| 11 | CMP_LT | (A < B) ? 1 : 0 | |
| 12 | CMP_EQ | (A == B) ? 1 : 0 | ✅ Suite P |
| 13 | LOAD_SPM | Load from scratchpad | |
| 14 | STORE_SPM | Store to scratchpad | |
| 15 | ACC_CLR | Clear accumulator | |
| 16 | PASS0 | Pass operand 0 | |
| 17 | PASS1 | Pass operand 1 | |
| 18 | LIF | Leaky Integrate-Fire | |

**9 operations verified, 10 implemented but not yet tested**

---

## Source Select (src0_sel, src1_sel)

| Value | Source |
|-------|--------|
| 0 | Register File (RF) |
| 1 | North neighbor |
| 2 | East neighbor |
| 3 | South neighbor |
| 4 | West neighbor (Tile Memory) |
| 5 | Scratchpad Memory |
| 6 | Immediate value |

---

## Configuration Frame (64-bit)

| Bits | Field | Description |
|------|-------|-------------|
| [5:0] | opcode | ALU operation (19 ops) |
| [9:6] | src0_sel | Source 0 select |
| [13:10] | src1_sel | Source 1 select |
| [17:14] | dst_sel | Destination register |
| [21:18] | route_mask | Output direction (N/E/S/W) |
| [22] | pred_en | Predicate enable |
| [23] | pred_inv | Predicate invert |
| [39:24] | imm | 16-bit immediate |
| [63:40] | extended | Routing header metadata |

---

## Project Structure

```
CGRA_project/
├── 00_src/                      # RTL Source (11 modules)
│   ├── cgra_top.sv                  # Top-level + auto-stop
│   ├── cgra_axi_csr.sv              # APB CSR interface
│   ├── cgra_dma_engine.sv           # Pipelined DMA master
│   ├── cgra_control_unit.sv         # Execution FSM
│   ├── cgra_tile_memory.sv          # 4-bank row memory
│   ├── cgra_array_4x4.sv            # 4×4 PE mesh
│   ├── cgra_tile.sv                 # PE + Router wrapper
│   ├── cgra_pe.sv                   # Processing Element
│   ├── cgra_router.sv               # 5-port XY router
│   ├── axi_ram.sv                   # Memory model
│   └── bsg_mem/                     # BSG memory primitives
│
├── 01_bench/                    # Verification (4 files)
│   ├── tb_top.sv                    # Master test harness
│   ├── tb_tasks.svh                 # Driver layer
│   ├── tb_test_suites.svh           # 126 test vectors
│   └── cgra_protocol_monitor.sv     # AXI compliance checker
│
├── 02_test/                     # Test documentation
├── 03_sim/                      # Simulation outputs
├── 04_doc/                      # Design documentation
├── Makefile                     # Build system
└── README.md
```

---

## Key Features

### Mesh Broadcast
- PE outputs broadcast to all 4 neighbors (N/E/S/W)
- Enables systolic-style spatial pipelines
- Verified by Suite L (PE-to-PE communication)

### Auto-Stop
- Automatic termination after 16 context cycles
- Eliminates CPU polling for simple programs
- Configurable via cycle counter

### Synthesis Keeper
- All edge outputs OR-reduced to `synthesis_keep` pin
- Prevents optimizer from removing unused array

---

## Prerequisites

```bash
# Ubuntu/Debian
sudo apt-get install iverilog gtkwave
```

- [Icarus Verilog](http://iverilog.icarus.com/) (v10.0+)
- [GTKWave](http://gtkwave.sourceforge.net/) (optional)

---

## Makefile Commands

| Command | Description |
|---------|-------------|
| `make sim` | Run 126-test verification |
| `make compile` | Compile only |
| `make wave` | Open waveforms |
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

---

## License

Educational/Research project - December 2024
