# CGRA Project

A Coarse-Grained Reconfigurable Array (CGRA) accelerator for SNN inference, targeting the DE10-Standard FPGA.

## Quick Start

```bash
# List available testbenches
make list

# Run a testbench
make sim TB=tb_cgra_top_golden

# View waveforms
make wave TB=tb_cgra_top_golden

# Clean generated files
make clean
```

## Project Structure

```
CGRA_project/
├── 00_src/                          # RTL Source (10 modules)
│   ├── cgra_pe.sv                   # Processing Element
│   ├── cgra_router.sv               # 5-port mesh router
│   ├── cgra_tile.sv                 # PE + Router wrapper
│   ├── cgra_array_4x4.sv            # 4×4 PE mesh array
│   ├── cgra_tile_memory.sv          # 4-bank row memory
│   ├── cgra_axi_csr.sv              # AXI4-Lite CSR interface
│   ├── cgra_control_unit.sv         # Execution FSM
│   ├── cgra_config_loader.sv        # Double-buffered config
│   ├── cgra_dma_engine.sv           # AXI4 DMA master
│   └── cgra_top.sv                  # Top-level integration
│
├── 01_bench/                        # Golden Testbenches (10 files)
│   ├── tb_cgra_top_golden.sv        # Top-level integration (6 tests)
│   ├── tb_cgra_array_4x4_golden.sv  # Mesh routing (6 tests)
│   ├── tb_cgra_tile_memory_golden.sv
│   ├── tb_cgra_axi_csr_golden.sv
│   ├── tb_cgra_dma_engine_golden.sv
│   ├── tb_cgra_config_loader_golden.sv
│   ├── tb_cgra_control_unit_golden.sv
│   ├── tb_cgra_pe_golden.sv
│   ├── tb_cgra_router_golden.sv
│   └── tb_cgra_tile_golden.sv
│
├── 03_sim/                          # Simulation outputs (.vvp, .vcd)
├── 04_doc/                          # Documentation
│   └── spec_CGRA.md                 # Full specification
├── Makefile                         # Build system
└── README.md
```

## Makefile Usage

| Command | Description |
|---------|-------------|
| `make sim TB=<name>` | Compile and run testbench |
| `make compile TB=<name>` | Compile only |
| `make wave TB=<name>` | Open waveform in GTKWave |
| `make list` | Show available testbenches |
| `make clean` | Remove generated files |
| `make help` | Show all commands |

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────┐
│                       cgra_top                              │
├─────────────────────────────────────────────────────────────┤
│  ┌──────────────┐  ┌───────────────┐  ┌─────────────────┐  │
│  │ AXI4-Lite    │  │ Control Unit  │  │  Config Loader  │  │
│  │ CSR          │──│ (FSM)         │──│ (Double-Buffer) │  │
│  └──────────────┘  └───────────────┘  └─────────────────┘  │
│         │                 │                    │            │
│  ┌──────┴──────┐  ┌───────┴───────┐   ┌───────┴───────┐   │
│  │ DMA Engine  │  │   4×4 CGRA    │   │ Tile Memory   │   │
│  │ (AXI4)      │  │   PE Array    │   │ (4 banks)     │   │
│  └─────────────┘  └───────────────┘   └───────────────┘   │
└─────────────────────────────────────────────────────────────┘
```

## CSR Register Map

| Offset | Name | Access | Description |
|--------|------|--------|-------------|
| 0x00 | CTRL | R/W | [0]=start, [1]=reset, [2]=cfg_start |
| 0x04 | STATUS | R/W1C | [0]=busy, [1]=done, [2]=error, [3]=cfg_done |
| 0x08 | BITSTR_ADDR | R/W | Bitstream base address |
| 0x0C | BITSTR_SIZE | R/W | Bitstream size (frames) |
| 0x10 | DMA_DOORBELL | W | DMA start trigger |
| 0x18 | JOB_DESC | R/W | DMA descriptor address |
| 0x24 | IRQ_MASK | R/W | [0]=done, [1]=error, [2]=dma_done |

## Configuration Frame (64-bit)

| Bits | Field | Description |
|------|-------|-------------|
| [5:0] | op_code | ALU operation |
| [9:6] | src0 | Source 0 select |
| [13:10] | src1 | Source 1 select |
| [17:14] | dst | Destination register |
| [21:18] | route | Output routing (N/E/S/W/L) |
| [22] | pred_en | Predicate enable |
| [39:24] | imm | 16-bit immediate |

## RTL Coding Standards

All RTL follows SystemVerilog synthesis best practices:
- ✅ `always_ff` / `always_comb` (no generic `always`)
- ✅ `unique case` with `default` clauses
- ✅ `typedef enum` for FSM states
- ✅ `logic` type (no `reg`)
- ✅ Sync reset, nonblocking (<=) in always_ff

## Prerequisites

- [Icarus Verilog](http://iverilog.icarus.com/) (`iverilog`)
- [GTKWave](http://gtkwave.sourceforge.net/) (optional, for waveforms)

## Target Platform

- **Board**: DE10-Standard (Intel Cyclone V)
- **Clock**: 50-100 MHz
- **Array Size**: 4×4 = 16 PEs
- **SPM per PE**: 256 entries × 32-bit

## License

Educational/Research project
