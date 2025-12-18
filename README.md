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
├── 03_sim/                          # Simulation outputs (.vvp, .vcd)
├── 04_doc/                          # Documentation
├── Makefile                         # Build system
└── README.md
```

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

---

## Core Modules

### 1. Processing Element (`cgra_pe.sv`)

The fundamental compute unit of the CGRA.

**Resources:**
| Resource | Size | Description |
|----------|------|-------------|
| Register File | 16 × 32-bit | General-purpose registers |
| Scratchpad Memory | 256 × 32-bit | Local data storage (BRAM) |
| Accumulator | 40-bit | Extended precision for MAC |

**ALU Operations:**
| Code | Op | Description |
|------|-----|-------------|
| 0 | NOP | No operation |
| 1 | ADD | Addition |
| 2 | SUB | Subtraction |
| 3 | MUL | Multiplication |
| 4 | MAC | Multiply-accumulate |
| 5-7 | AND/OR/XOR | Bitwise logic |
| 8-9 | SHL/SHR | Shift operations |
| 10-12 | CMP_GT/LT/EQ | Comparisons |
| 13-14 | LOAD/STORE | Scratchpad access |
| 15 | ACC_CLR | Clear accumulator |
| 16-17 | PASS0/1 | Passthrough |
| 18 | LIF | Leaky Integrate-and-Fire |

**Operand Sources:**
- `0-15`: Register file R0-R15
- `6`: Immediate value
- `7`: North input
- `8-11`: E/S/W/Local inputs
- `12`: Accumulator

---

### 2. Router (`cgra_router.sv`)

5-port packet router with XY deterministic routing.

**Ports:**
```
         ┌───┐
  North ─┤   ├─ South
         │ R │
   East ─┤   ├─ West
         │   │
  Local ─┤   │
         └───┘
```

**Features:**
- **Routing**: XY deterministic (horizontal first, then vertical)
- **Buffering**: 1-stage skid buffer per input port
- **Arbitration**: Fixed priority (Local > W > S > E > N)
- **Flow Control**: Ready/valid handshake, backpressure support
- **Throughput**: 50% under congestion (acceptable for multi-hop)

**Packet Format (32-bit):**
| Bits | Field | Description |
|------|-------|-------------|
| [31:28] | DX | Destination X coordinate |
| [27:24] | DY | Destination Y coordinate |
| [23:16] | Reserved | Future use |
| [15:0] | Payload | Data payload |

---

### 3. Tile (`cgra_tile.sv`)

Combines one PE and one Router into a single tile unit.

```
┌─────────────────────────┐
│        Tile             │
│  ┌─────────┐  ┌──────┐  │
│  │   PE    │──│Router│  │
│  └─────────┘  └──────┘  │
│       ↕          ↕      │
│   Config      N/E/S/W   │
└─────────────────────────┘
```

---

### 4. Array (`cgra_array_4x4.sv`)

4×4 mesh of 16 tiles with edge I/O ports.

**Topology:**
```
      N0   N1   N2   N3
       ↓    ↓    ↓    ↓
   ┌───┬───┬───┬───┐
W0→│0,0│0,1│0,2│0,3│→E0
   ├───┼───┼───┼───┤
W1→│1,0│1,1│1,2│1,3│→E1
   ├───┼───┼───┼───┤
W2→│2,0│2,1│2,2│2,3│→E2
   ├───┼───┼───┼───┤
W3→│3,0│3,1│3,2│3,3│→E3
   └───┴───┴───┴───┘
       ↓    ↓    ↓    ↓
      S0   S1   S2   S3
```

**Edge Ports:** 16 inputs + 16 outputs for external data I/O

---

### 5. Configuration Loader (`cgra_config_loader.sv`)

Double-buffered context memory for zero-stall reconfiguration.

**FSM States:**
```
IDLE → LOAD_HEADER → LOAD_FRAMES → DONE → SWAP
                           ↓
                        ERROR
```

**Features:**
- Two config banks (active + shadow)
- Atomic context swap on frame boundary
- Supports up to 1024 configuration frames
- Per-PE 64-bit configuration words

---

### 6. Control Unit (`cgra_control_unit.sv`)

Master execution FSM coordinating all components.

**States:**
| State | Description |
|-------|-------------|
| IDLE | Waiting for start |
| WAIT_CFG | Configuration loading |
| SETUP_DMA | DMA initialization |
| LOAD_CONTEXT | Loading execution context |
| EXEC_INIT | Preparing PE array |
| EXEC_RUN | Active computation |
| EXEC_DRAIN | Flushing pipeline |
| TIMESTEP_DONE | Timestep complete |
| CONTEXT_SWAP | Switching config bank |
| COMPLETE | All timesteps done |
| ERROR | Error state |

---

### 7. DMA Engine (`cgra_dma_engine.sv`)

AXI4 master for high-throughput memory transfers.

**Features:**
- Descriptor-based transfers
- Burst mode (up to 16 beats)
- Read and write channels
- Connects tile memory to external DDR

**Descriptor Format (128-bit):**
| Word | Field |
|------|-------|
| 0 | Source address |
| 1 | Destination address |
| 2 | Transfer length (bytes) |
| 3 | Control / Next descriptor |

---

### 8. AXI CSR (`cgra_axi_csr.sv`)

AXI4-Lite slave for CPU control interface.

**Register Map:**
| Offset | Name | Access | Description |
|--------|------|--------|-------------|
| 0x00 | CTRL | R/W | [0]=start, [1]=reset, [2]=cfg_start |
| 0x04 | STATUS | R/W1C | [0]=busy, [1]=done, [2]=error, [3]=cfg_done |
| 0x08 | BITSTR_ADDR | R/W | Bitstream base address |
| 0x0C | BITSTR_SIZE | R/W | Bitstream size (frames) |
| 0x10 | DMA_DOORBELL | W | DMA start trigger |
| 0x18 | JOB_DESC | R/W | DMA descriptor address |
| 0x24 | IRQ_MASK | R/W | Interrupt enable mask |

---

### 9. Tile Memory (`cgra_tile_memory.sv`)

Row-banked memory with external DMA port.

**Organization:**
- 4 banks (one per PE row)
- 256 entries × 32-bit per bank
- 1-cycle read latency
- Parallel bank access

---

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

---

## RTL Coding Standards

All RTL follows SystemVerilog synthesis best practices:

| Standard | Status |
|----------|--------|
| `always_ff` / `always_comb` | ✅ 42 / 38 blocks |
| `unique case` with `default` | ✅ 21 / 21 |
| `typedef enum` for FSMs | ✅ 6 enums |
| `logic` type (no `reg`) | ✅ |
| Sync reset pattern | ✅ |
| Nonblocking in always_ff | ✅ |

---

## Makefile Commands

| Command | Description |
|---------|-------------|
| `make sim TB=<name>` | Compile and run testbench |
| `make compile TB=<name>` | Compile only |
| `make wave TB=<name>` | Open waveform in GTKWave |
| `make list` | Show available testbenches |
| `make clean` | Remove generated files |

---

## Prerequisites

- [Icarus Verilog](http://iverilog.icarus.com/) (`iverilog`)
- [GTKWave](http://gtkwave.sourceforge.net/) (optional)

## Target Platform

- **Board**: DE10-Standard (Intel Cyclone V)
- **Clock**: 50-100 MHz
- **Array**: 4×4 = 16 PEs
- **SPM**: 256 × 32-bit per PE

## License

Educational/Research project
