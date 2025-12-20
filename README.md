# CGRA SoC Accelerator

A Coarse-Grained Reconfigurable Array (CGRA) accelerator with APB control interface and AXI4-Lite DMA, targeting the DE10-Standard FPGA.

## Quick Start

```bash
# Run 80-test verification suite
make sim

# View waveforms
make wave

# Clean generated files
make clean
```

## Verification Status

**80/80 TESTS PASSED - SILICON READY** ✅

| Suite | Focus | Tests |
|-------|-------|-------|
| A | Register Logic & Config | 19 |
| B | DMA Datapath | 16 |
| C | Protocol Compliance | 15 |
| D | Performance & Timing | 10 |
| E | Stress Testing | 10 |
| F | System Integration | 10 |

## Project Structure

```
CGRA_project/
├── 00_src/              # RTL Source (11 modules)
│   ├── cgra_pe.sv           # Processing Element (ALU, RegFile, SPM)
│   ├── cgra_router.sv       # 5-port XY mesh router
│   ├── cgra_tile.sv         # PE + Router wrapper
│   ├── cgra_array_4x4.sv    # 4×4 PE mesh (16 PEs)
│   ├── cgra_tile_memory.sv  # 4-bank row memory
│   ├── cgra_axi_csr.sv      # APB CSR interface
│   ├── cgra_control_unit.sv # Execution FSM
│   ├── cgra_config_loader.sv# Double-buffered config
│   ├── cgra_dma_engine.sv   # AXI4-Lite DMA master
│   ├── cgra_top.sv          # Top-level integration
│   └── bsg_mem/             # BSG memory primitives
│
├── 01_bench/            # Verification (4 files)
│   ├── tb_top.sv            # Master test harness
│   ├── tb_tasks.svh         # Driver layer
│   ├── tb_test_suites.svh   # 80 test vectors
│   └── cgra_protocol_monitor.sv
│
├── 03_sim/              # Simulation outputs
├── 04_doc/              # Documentation
├── Makefile             # Build system
└── README.md
```

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                       cgra_top                              │
├─────────────────────────────────────────────────────────────┤
│  ┌──────────────┐  ┌───────────────┐  ┌─────────────────┐  │
│  │ APB CSR      │  │ Control Unit  │  │  Config Loader  │  │
│  │ (Registers)  │──│ (FSM)         │──│ (Double-Buffer) │  │
│  └──────────────┘  └───────────────┘  └─────────────────┘  │
│         │                 │                    │            │
│  ┌──────┴──────┐  ┌───────┴───────┐   ┌───────┴───────┐   │
│  │ DMA Engine  │  │   4×4 CGRA    │   │ Tile Memory   │   │
│  │ (AXI4-Lite) │  │   PE Array    │   │ (4 banks)     │   │
│  └─────────────┘  └───────────────┘   └───────────────┘   │
└─────────────────────────────────────────────────────────────┘
```

## APB Register Map

| Address | Register | R/W | Description |
|---------|----------|-----|-------------|
| 0x00 | DMA_CTRL | RW | [0] Start (auto-clear) |
| 0x04 | DMA_STATUS | RO | [0] Busy, [1] Done (sticky) |
| 0x08 | DMA_SRC | RW | Source address |
| 0x0C | DMA_DST | RW | Destination address |
| 0x10 | DMA_SIZE | RW | Transfer size (bytes) |
| 0x20 | CU_CTRL | RW | [0] Start, [1] Soft Reset |
| 0x24 | CU_STATUS | RO | [0] Busy, [1] Done (sticky) |
| 0x28 | CU_CYCLES | RO | Cycle counter |

## Performance

| Metric | Value |
|--------|-------|
| Start Latency | < 10 cycles |
| End Latency | < 10 cycles |
| Throughput | 0.49 B/cycle |
| 256B Transfer | 522 cycles |

## Makefile Commands

| Command | Description |
|---------|-------------|
| `make sim` | Compile and run 80-test suite |
| `make compile` | Compile only |
| `make wave` | Open waveform in GTKWave |
| `make clean` | Remove generated files |
| `make help` | Show help |

## Prerequisites

- [Icarus Verilog](http://iverilog.icarus.com/) (`iverilog`)
- [GTKWave](http://gtkwave.sourceforge.net/) (optional)

```bash
# Ubuntu/Debian
sudo apt-get install iverilog gtkwave
```

## Target Platform

- **Board**: DE10-Standard (Intel Cyclone V)
- **Clock**: 50-100 MHz
- **Array**: 4×4 = 16 PEs
- **SPM**: 256 × 32-bit per PE

## RTL Coding Standards

| Standard | Status |
|----------|--------|
| `always_ff` / `always_comb` | ✅ |
| `unique case` with `default` | ✅ |
| `typedef enum` for FSMs | ✅ |
| `logic` type (no `reg`) | ✅ |
| Sync reset pattern | ✅ |

## License

Educational/Research project
