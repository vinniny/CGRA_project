# CGRA SoC Accelerator

A Coarse-Grained Reconfigurable Array (CGRA) accelerator with pipelined DMA engine, APB control interface, and AXI4-Lite memory master. Targeting DE10-Standard FPGA (Intel Cyclone V).

## Quick Start

```bash
# Run 80-test verification suite
make sim

# View waveforms
make wave

# Clean generated files
make clean

# Show help
make help
```

## Verification Status

**80/80 TESTS PASSED - SILICON READY** ✅

| Suite | Focus | Tests | Status |
|-------|-------|-------|--------|
| A | Register Logic & Config | 19 | ✅ |
| B | DMA Datapath | 16 | ✅ |
| C | Protocol Compliance | 15 | ✅ |
| D | Performance & Timing | 10 | ✅ |
| E | Stress Testing | 10 | ✅ |
| F | System Integration | 10 | ✅ |

## Project Structure

```
CGRA_project/
├── 00_src/                      # RTL Source (10 modules)
│   ├── cgra_top.sv                  # Top-level integration
│   ├── cgra_axi_csr.sv              # APB CSR interface
│   ├── cgra_dma_engine.sv           # Pipelined DMA master
│   ├── cgra_control_unit.sv         # Execution FSM
│   ├── cgra_array_4x4.sv            # 4×4 PE mesh (16 PEs)
│   ├── cgra_pe.sv                   # Processing Element
│   ├── cgra_router.sv               # 5-port XY mesh router
│   ├── cgra_tile.sv                 # PE + Router wrapper
│   ├── cgra_tile_memory.sv          # 4-bank row memory
│   ├── axi_ram.sv                   # Memory model
│   └── bsg_mem/                     # BSG memory primitives
│
├── 01_bench/                    # Verification (4 files)
│   ├── tb_top.sv                    # Master test harness
│   ├── tb_tasks.svh                 # Driver layer
│   ├── tb_test_suites.svh           # 80 test vectors
│   └── cgra_protocol_monitor.sv     # AXI compliance checker
│
├── 03_sim/                      # Simulation outputs
├── 04_doc/                      # Documentation
├── Makefile                     # Build system
└── README.md
```

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                       cgra_top                              │
├─────────────────────────────────────────────────────────────┤
│  ┌──────────────┐  ┌───────────────┐  ┌─────────────────┐  │
│  │ APB CSR      │  │ Control Unit  │  │  Tile Memory    │  │
│  │ (Registers)  │──│ (3-state FSM) │──│  (4 banks)      │  │
│  └──────────────┘  └───────────────┘  └─────────────────┘  │
│         │                 │                                 │
│  ┌──────┴──────────────────┴───────────────────────────────┐│
│  │              Pipelined DMA Engine                       ││
│  │  ┌─────────────┐   ┌────────┐   ┌──────────────┐       ││
│  │  │ Read Engine │──▶│  FIFO  │──▶│ Write Engine │       ││
│  │  │ (Producer)  │   │ (8-wd) │   │ (Consumer)   │       ││
│  │  └─────────────┘   └────────┘   └──────────────┘       ││
│  └─────────────────────────────────────────────────────────┘│
│                              │                              │
│  ┌───────────────────────────┴─────────────────────────────┐│
│  │                    4×4 CGRA PE Array                    ││
│  │  ┌───┬───┬───┬───┐                                      ││
│  │  │0,0│0,1│0,2│0,3│  Each tile:                          ││
│  │  ├───┼───┼───┼───┤  - Processing Element (ALU/MAC)      ││
│  │  │1,0│1,1│1,2│1,3│  - 5-port XY Router                  ││
│  │  ├───┼───┼───┼───┤  - 256×32 Scratchpad                 ││
│  │  │2,0│2,1│2,2│2,3│  - 16×32 Register File               ││
│  │  ├───┼───┼───┼───┤                                      ││
│  │  │3,0│3,1│3,2│3,3│                                      ││
│  │  └───┴───┴───┴───┘                                      ││
│  └─────────────────────────────────────────────────────────┘│
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
| 0x30 | IRQ_STATUS | RO | [0] DMA Done, [1] CU Done |
| 0x34 | IRQ_MASK | RW | Interrupt enable mask |

## DMA Engine Architecture

The DMA features a **Producer-Consumer** pipelined design:

```
┌─────────────┐   ┌────────┐   ┌──────────────┐
│ Read Engine │──▶│  FIFO  │──▶│ Write Engine │
│ (Producer)  │   │ (8-wd) │   │ (Consumer)   │
│             │   │        │   │              │
│ R_IDLE      │   │ count  │   │ W_IDLE       │
│ R_ADDR      │   │ w_ptr  │   │ W_WAIT       │
│ R_DATA      │   │ r_ptr  │   │ W_ADDR       │
│ R_DONE      │   │        │   │ W_DATA       │
└─────────────┘   └────────┘   │ W_RESP       │
                               │ W_DONE       │
                               └──────────────┘
```

**Key Features:**
- Decoupled Read/Write engines for concurrent operation
- 8-word FIFO buffer for pipeline decoupling
- Flow control via `fifo_full` / `fifo_empty`
- Robust stress handling (100% stall recovery)

## Performance

| Metric | Value |
|--------|-------|
| Start Latency | < 10 cycles |
| End Latency | < 10 cycles |
| Throughput | 0.64 B/cycle |
| 256B Transfer | 398 cycles |
| Pipeline Overlap | 101 cycles |
| Efficiency | 64.3% |

## Test Highlights

### Suite D: Performance & Architecture
- **D05**: Pipeline overlap measurement (101 cycles concurrent R/W)
- **D06**: FIFO isolation (reader ahead while writer stalled)
- **D07**: Concurrency verification (57 overlap cycles)

### Suite E: Stress Testing
- **E01**: Full stall recovery (100% READY=0 for 100 cycles)
- **E02**: Random throttling (30% backpressure)
- **E05**: Register spam during DMA
- **E10**: Burn test (10 iterations)

## Processing Element (PE)

Each PE contains:
- **ALU**: 18 operations (ADD, SUB, MUL, MAC, logic, compare, LIF neuron)
- **Register File**: 16 × 32-bit
- **Scratchpad**: 256 × 32-bit (BRAM)
- **Accumulator**: 40-bit extended precision

**ALU Operations:**
| Code | Op | Description |
|------|-----|-------------|
| 0 | NOP | No operation |
| 1-3 | ADD/SUB/MUL | Arithmetic |
| 4 | MAC | Multiply-accumulate |
| 5-7 | AND/OR/XOR | Bitwise |
| 8-9 | SHL/SHR | Shift |
| 10-12 | CMP_GT/LT/EQ | Compare |
| 13-14 | LOAD/STORE | Scratchpad |
| 15 | ACC_CLR | Clear accumulator |
| 18 | LIF | Leaky integrate-and-fire |

## Router

5-port XY deterministic router with:
- **Routing**: Horizontal first, then vertical
- **Ports**: North, East, South, West, Local
- **Arbitration**: Fixed priority (L > W > S > E > N)
- **Buffer**: 1-stage skid buffer per port

## Prerequisites

```bash
# Ubuntu/Debian
sudo apt-get install iverilog gtkwave
```

- [Icarus Verilog](http://iverilog.icarus.com/) (iverilog v10.0+)
- [GTKWave](http://gtkwave.sourceforge.net/) (optional, for waveforms)

## Makefile Commands

| Command | Description |
|---------|-------------|
| `make sim` | Run 80-test verification suite |
| `make compile` | Compile testbench only |
| `make wave` | Open waveform in GTKWave |
| `make clean` | Remove generated files |
| `make help` | Show available commands |

## Target Platform

- **Board**: DE10-Standard (Intel Cyclone V 5CSXFC6D6F31C6)
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
| Synchronous reset pattern | ✅ |
| Non-blocking in always_ff | ✅ |

## Configuration Frame Format (64-bit)

| Bits | Field | Description |
|------|-------|-------------|
| [5:0] | op_code | ALU operation |
| [9:6] | src0 | Source 0 select |
| [13:10] | src1 | Source 1 select |
| [17:14] | dst | Destination register |
| [21:18] | route | Output mask (N/E/S/W/L) |
| [22] | pred_en | Predicate enable |
| [39:24] | imm | 16-bit immediate |
| [63:40] | extended | Reserved |

## Next Steps

1. **FPGA Synthesis**: Run Quartus/Vivado synthesis
2. **UVM Migration**: Convert testbench for coverage metrics
3. **Performance Tuning**: Add burst support for higher throughput
4. **Integration**: Connect to ARM core via AXI interconnect

## License

Educational/Research project - December 2024
