# CGRA Project README

## Project Structure

```
CGRA_project/
├── 00_src/           # Source files
│   ├── cgra_pe.sv              # Processing Element
│   ├── cgra_router.sv          # Router for mesh network
│   ├── cgra_array_4x4.sv       # 4x4 PE array
│   ├── cgra_config_loader.sv   # Configuration loader with double buffering
│   ├── cgra_axi_csr.sv         # AXI4-Lite CSR interface
│   └── cgra_top.sv             # Top-level wrapper
├── 01_bench/         # Testbenches
│   ├── tb_cgra_pe.sv
│   ├── tb_cgra_router.sv
│   ├── tb_cgra_config_loader.sv
│   ├── tb_cgra_top.sv
│   └── run_sim.sh              # Simulation script
├── 02_test/          # Test data and scripts
├── 03_sim/           # Simulation outputs
└── 04_doc/           # Documentation
    └── spec_CGRA.md            # Complete specification
```

## Module Overview

### 1. Processing Element (cgra_pe.sv)
- **Features**: ALU/MAC unit, scratchpad memory (256 entries), register file (16 registers)
- **Operations**: ADD, SUB, MUL, MAC, logical ops, comparisons, load/store
- **Configuration**: 64-bit frame per cycle
- **Routing**: Supports N/E/S/W/local output with multi-cast

### 2. Router (cgra_router.sv)
- **Routing**: XY deterministic routing
- **Features**: Unicast, multicast, broadcast support
- **Ports**: 5 ports (N/E/S/W/Local)

### 3. CGRA Array (cgra_array_4x4.sv)
- **Size**: 4×4 = 16 Processing Elements
- **Topology**: 2D mesh with torus connections
- **Configuration**: Simultaneous configuration of all PEs

### 4. Configuration Loader (cgra_config_loader.sv)
- **Features**: Double-buffered context storage
- **FSM States**: IDLE, LOAD_HEADER, LOAD_FRAMES, SWAP, DONE, ERROR
- **Atomic Swap**: Zero-stall context switching

### 5. AXI4-Lite CSR (cgra_axi_csr.sv)
- **Interface**: Standard AXI4-Lite slave
- **Registers**: Control, Status, Bitstream addr/size, Performance counters
- **Offsets**: See specification Section 4.2

### 6. Top-Level (cgra_top.sv)
- **Integration**: All components connected
- **FSM**: Execution control (IDLE, WAIT_CFG, SETUP, RUN, DRAIN, COMPLETE, ERROR)
- **Counters**: Cycle counter, stall counter

## Configuration Frame Format (64-bit)

| Bits    | Field     | Description                    |
|---------|-----------|--------------------------------|
| [5:0]   | op_code   | Operation code                 |
| [9:6]   | src0      | Source operand 0 select        |
| [13:10] | src1      | Source operand 1 select        |
| [17:14] | dst       | Destination register select    |
| [21:18] | route     | Routing mask (N/E/S/W/local)   |
| [22]    | pred_en   | Predicate enable               |
| [23]    | pred_inv  | Predicate invert               |
| [39:24] | imm       | 16-bit immediate value         |
| [63:40] | extended  | Extended metadata              |

## Operation Codes

| Code | Operation  | Description                    |
|------|------------|--------------------------------|
| 0    | NOP        | No operation                   |
| 1    | ADD        | Addition                       |
| 2    | SUB        | Subtraction                    |
| 3    | MUL        | Multiplication                 |
| 4    | MAC        | Multiply-accumulate            |
| 5    | AND        | Bitwise AND                    |
| 6    | OR         | Bitwise OR                     |
| 7    | XOR        | Bitwise XOR                    |
| 8    | SHL        | Shift left                     |
| 9    | SHR        | Shift right                    |
| 10   | CMP_GT     | Compare greater than           |
| 11   | CMP_LT     | Compare less than              |
| 12   | CMP_EQ     | Compare equal                  |
| 13   | LOAD_SPM   | Load from scratchpad           |
| 14   | STORE_SPM  | Store to scratchpad            |
| 15   | ACC_CLR    | Clear accumulator              |
| 16   | PASS0      | Pass operand 0                 |
| 17   | PASS1      | Pass operand 1                 |

## CSR Register Map (AXI4-Lite)

| Offset | Name          | Access | Description                    |
|--------|---------------|--------|--------------------------------|
| 0x00   | CTRL          | R/W    | Control: start, reset, cfg_start |
| 0x04   | STATUS        | R/W1C  | Status: busy, done, error, cfg_done |
| 0x08   | BITSTR_ADDR   | R/W    | Bitstream base address         |
| 0x0C   | BITSTR_SIZE   | R/W    | Bitstream size (frames)        |
| 0x10   | DMA_DOORBELL  | W      | DMA start trigger              |
| 0x14   | DMA_HEAD      | R      | DMA head pointer               |
| 0x18   | JOB_DESC_ADDR | R/W    | Job descriptor address         |
| 0x1C   | PERF0         | R      | Performance counter (cycles)   |
| 0x20   | PERF1         | R      | Performance counter (stalls)   |
| 0x24   | IRQ_MASK      | R/W    | Interrupt enable mask          |

## Running Simulations

### Prerequisites
- Icarus Verilog (`iverilog`)
- VVP (Verilog simulator)
- GTKWave (optional, for waveform viewing)

### Run a Testbench

```bash
cd 01_bench
chmod +x run_sim.sh
./run_sim.sh tb_cgra_pe
./run_sim.sh tb_cgra_router
./run_sim.sh tb_cgra_config_loader
./run_sim.sh tb_cgra_top
```

### View Waveforms

```bash
cd 03_sim
gtkwave cgra_top.vcd
```

## Design Constraints

Following SystemVerilog restrictions:
- No `typedef struct` - all signals defined directly
- No `integer`, `genvar`, `generate`, or `for` loops
- All PE instances and connections manually instantiated

## Synthesis Notes

Target: DE10-Standard FPGA (Intel Cyclone V)
- Clock target: 50-100 MHz
- Resources: 16 PEs with 256-entry SPM each
- Memory: Block RAM for scratchpads
- Configuration: Distributed to all PEs simultaneously

## Performance KPIs

- **Latency**: Target ≥2×-5× improvement over CPU baseline
- **PE Utilization**: Target ≥70% on mapped workloads
- **Memory Traffic Reduction**: Target ≥30% due to sparsity exploitation
- **Reconfiguration**: Zero-stall context switching

## Authors

CGRA design for SNN inference acceleration
Implementation follows specification in `04_doc/spec_CGRA.md`

## License

Educational/Research project
