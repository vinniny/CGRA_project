# CGRA IP Design Report Writing Guide

## Document Information
- **Project:** CGRA Accelerator for SNN Inference
- **Target Platform:** DE10-Standard FPGA (Intel Cyclone V)
- **Design Language:** SystemVerilog (IEEE 1800-2012)
- **Purpose:** Guide for writing comprehensive design reports following specifications and code

---

## Table of Contents
1. [Report Structure](#report-structure)
2. [Section-by-Section Guidelines](#section-by-section-guidelines)
3. [How to Extract Information from Spec](#how-to-extract-information-from-spec)
4. [How to Document Code Implementation](#how-to-document-code-implementation)
5. [Verification and Results](#verification-and-results)
6. [Writing Best Practices](#writing-best-practices)
7. [Report Template](#report-template)

---

## 1. Report Structure

### Standard VLSI/FPGA Design Report Organization
```
1. Executive Summary
2. Introduction
3. System Specification
4. Architecture Design
5. Module Implementation
6. Verification and Testing
7. Synthesis Results
8. Performance Analysis
9. Conclusion and Future Work
10. References
11. Appendices
```

---

## 2. Section-by-Section Guidelines

### 2.1 Executive Summary (1 page)
**What to include:**
- Project overview in 2-3 sentences
- Key design metrics (size, performance, resource usage)
- Main achievements and innovations
- High-level conclusions

**Example:**
```markdown
This report presents the design and implementation of a 4×4 CGRA (Coarse-Grained 
Reconfigurable Architecture) accelerator optimized for Spiking Neural Network (SNN) 
inference on the DE10-Standard FPGA. The design features 16 Processing Elements with 
double-buffered configuration, achieving zero-stall reconfiguration. Synthesis results 
show 12,450 ALMs utilization (26% of Cyclone V) with a maximum frequency of 95 MHz. 
The architecture successfully executes SNN operations including leaky integrate-and-fire 
neurons, synaptic processing, and multi-layer pipelines with 100% functional verification.
```

---

### 2.2 Introduction

#### 2.2.1 Background and Motivation
**From spec, extract:**
- Application domain (SNN inference)
- Why CGRA is needed (flexibility + performance)
- Target platform constraints

**Example based on spec_CGRA.md:**
```markdown
### 1.1 Background
Spiking Neural Networks (SNNs) offer energy-efficient computation through event-driven 
processing, making them ideal for edge computing applications. However, their irregular 
computation patterns challenge traditional architectures.

### 1.2 Motivation
- SNNs require flexible dataflow for various neuron models (LIF, ALIF, Izhikevich)
- Need low-latency reconfiguration between network layers
- Target: DE10-Standard FPGA with resource constraints (41K ALMs)

### 1.3 Design Goals
- 4×4 mesh of configurable Processing Elements
- Zero-stall context switching via double buffering
- Support 18 operations for SNN primitives
- AXI4-Lite control interface for embedded integration
```

#### 2.2.2 Design Objectives
**From spec sections 1.1-1.3, list:**
- Functional requirements
- Performance targets
- Resource constraints
- Interface specifications

**Example:**
```markdown
### 1.4 Design Objectives
| Objective | Specification | Achievement |
|-----------|---------------|-------------|
| PE Array Size | 4×4 (16 PEs) | ✓ Implemented |
| Data Width | 16-bit operations | ✓ Implemented |
| Configuration | Double-buffered, 64-bit frames | ✓ Implemented |
| Control Interface | AXI4-Lite slave (10 registers) | ✓ Implemented |
| Max Frequency | 50-100 MHz target | 95 MHz achieved |
| Operations | 18 opcodes for SNN | ✓ All implemented |
```

---

### 2.3 System Specification

#### 2.3.1 Functional Specification
**From spec_CGRA.md section 2:**

**Architecture Overview:**
```markdown
### 3.1 System Architecture
The CGRA consists of four major subsystems:

1. **PE Array (4×4 mesh):** 16 identical Processing Elements arranged in a 2D mesh 
   topology with nearest-neighbor connectivity (N, E, S, W).

2. **Configuration Subsystem:** Double-buffered configuration memory allowing zero-stall 
   context switching. Each PE receives a 64-bit configuration frame specifying operation, 
   operand sources, and routing.

3. **Control Interface (AXI4-Lite CSR):** Memory-mapped register interface for software 
   control, providing 10 32-bit registers (0x00-0x24) for execution control, configuration 
   management, and status monitoring.

4. **Interconnection Network:** XY deterministic routing with support for unicast, 
   multicast, and broadcast communication patterns.

[Include block diagram from spec_CGRA.md Figure 1]
```

#### 2.3.2 PE Specification
**From spec section 3.1:**
```markdown
### 3.2 Processing Element Specification

Each PE contains:
- **ALU/MAC Unit:** 18 operations (ADD, SUB, MUL, MAC, AND, OR, XOR, NOT, SHL, SHR, 
  CMP_EQ, CMP_GT, CMP_LT, SELECT, LOAD, STORE, LOAD_IMM, NOP)
- **Scratchpad Memory (SPM):** 256 entries × 16-bit for local data storage
- **Register File (RF):** 16 entries × 16-bit for intermediate values
- **Operand Multiplexing:** 7 sources per operand (RF, SPM, immediate, N, E, S, W inputs)
- **Routing Logic:** 5-way output (N, E, S, W, Local) with configurable mask
- **32-bit Accumulator:** For MAC operations with extended precision

#### Configuration Frame Format (64-bit):
| Bits | Field | Description |
|------|-------|-------------|
| [3:0] | opcode | Operation selection (0-17) |
| [6:4] | opA_sel | Operand A source (0-6) |
| [9:7] | opB_sel | Operand B source (0-6) |
| [17:10] | spm_addr | SPM address for LOAD/STORE |
| [21:18] | rf_addr | Register file address |
| [22] | rf_we | Register file write enable |
| [26:23] | route_mask | Output routing (N/E/S/W/Local) |
| [27] | predicate | Conditional execution |
| [43:28] | imm_val0 | Immediate value 0 (16-bit) |
| [59:44] | imm_val1 | Immediate value 1 (16-bit) |
| [63:60] | extended | Reserved for future use |
```

---

### 2.4 Architecture Design

#### 2.4.1 Top-Level Architecture
**From your code: `00_src/cgra_top.sv`**

```markdown
### 4.1 Top-Level Design

The CGRA top module (`cgra_top.sv`, 372 lines) integrates all subsystems and provides 
the external interface.

#### Module Hierarchy:
```
cgra_top
├── cgra_axi_csr (AXI4-Lite slave, 340 lines)
├── cgra_config_loader (Configuration FSM, 333 lines)
└── cgra_array_4x4 (PE array, 365 lines)
    └── cgra_pe × 16 (Processing Element, 343 lines each)
```

#### Interface Specification:
| Interface | Type | Width | Description |
|-----------|------|-------|-------------|
| clk | Input | 1-bit | System clock (50-100 MHz) |
| rst_n | Input | 1-bit | Active-low asynchronous reset |
| s_axi_* | AXI4-Lite | 32-bit data, 32-bit addr | Control/Status registers |
| cfg_mem_* | Memory | 64-bit read | Configuration bitstream |
| data_mem_* | Memory | 16-bit read/write | External data memory |
| irq | Output | 1-bit | Interrupt request |

#### Execution State Machine:
The top-level FSM controls CGRA execution flow:

[State Diagram]
IDLE → WAIT_CFG → SETUP → RUN → DRAIN → COMPLETE
  ↑                                          ↓
  ←────────────────────────────────────────←
```

**Include state transition conditions from code lines 119-160**

---

### 2.5 Module Implementation

#### 2.5.1 Processing Element (cgra_pe.sv)
**From your code: `00_src/cgra_pe.sv`**

```markdown
### 5.1 Processing Element Implementation

**File:** `00_src/cgra_pe.sv` (343 lines)

#### 5.1.1 ALU Implementation
The ALU supports 18 operations through a combinational always_comb block (lines 107-184):

```systemverilog
// Operation selection (from code)
case (opcode)
    4'd0:  alu_result = 32'd0;                    // NOP
    4'd1:  alu_result = operand_a + operand_b;    // ADD
    4'd2:  alu_result = operand_a - operand_b;    // SUB
    4'd3:  alu_result = operand_a * operand_b;    // MUL
    4'd4:  alu_result = accumulator + (operand_a * operand_b); // MAC
    // ... (document all 18 operations)
endcase
```

**Design Rationale:**
- Used combinational logic for single-cycle ALU operations
- MAC operation uses separate accumulator register for extended precision
- Comparison operations produce 1-bit result extended to 32-bit

#### 5.1.2 Memory Subsystem
**Scratchpad Memory (256×16):**
```systemverilog
logic [DATA_WIDTH-1:0] scratchpad [0:SPM_DEPTH-1];

always_ff @(posedge clk) begin
    if (opcode == 4'd15 && spm_addr < SPM_DEPTH) begin  // STORE
        scratchpad[spm_addr] <= alu_result[DATA_WIDTH-1:0];
    end
end
```

**Register File (16×16):**
- Synchronous write, asynchronous read
- Single write port, two read ports (for operands)
- Write-enable gated by rf_we configuration bit

#### 5.1.3 Operand Multiplexing
7 sources per operand (lines 60-90):
| sel | Source | Description |
|-----|--------|-------------|
| 0 | RF[rf_addr] | Register file output |
| 1 | SPM[spm_addr] | Scratchpad memory |
| 2 | imm_val0/1 | Immediate values from config |
| 3 | input_north | From North neighbor |
| 4 | input_east | From East neighbor |
| 5 | input_south | From South neighbor |
| 6 | input_west | From West neighbor |

**Implementation:** Two 7-to-1 multiplexers (one per operand) using case statements.

#### 5.1.4 Routing Network
5-way output routing controlled by route_mask[4:0] (lines 282-330):
```systemverilog
assign output_north = route_mask[4] ? result_out : 16'd0;
assign output_east  = route_mask[3] ? result_out : 16'd0;
assign output_south = route_mask[2] ? result_out : 16'd0;
assign output_west  = route_mask[1] ? result_out : 16'd0;
assign output_local = route_mask[0] ? result_out : 16'd0;
```

**Multicast Support:** Multiple bits in route_mask can be set simultaneously.
```

---

#### 2.5.2 Configuration Loader (cgra_config_loader.sv)
**From your code: `00_src/cgra_config_loader.sv`**

```markdown
### 5.2 Configuration Loader Implementation

**File:** `00_src/cgra_config_loader.sv` (333 lines)

#### 5.2.1 Double Buffering Architecture
Two complete sets of configuration registers (buffer0 and buffer1) allow atomic context 
switching:

```
Buffer 0: [config_00][config_01]...[config_33]  ← Active during execution
Buffer 1: [config_00][config_01]...[config_33]  ← Loading next context
```

**Key Features:**
- Zero-stall reconfiguration: New context loads while previous executes
- Atomic switching: swap_context signal toggles active_buffer in single cycle
- Double memory footprint: 2 × 16 × 64 bits = 2048 bits configuration storage

#### 5.2.2 Configuration Loading FSM
State machine (lines 75-140):

**States:**
1. **CFG_IDLE:** Waiting for load_start signal
2. **CFG_LOAD_HEADER:** Read configuration header (reserved for metadata)
3. **CFG_LOAD_FRAMES:** Load 16 PE configurations sequentially
4. **CFG_SWAP:** Signal completion, ready to swap contexts
5. **CFG_DONE:** Assert done flag, return to IDLE
6. **CFG_ERROR:** Error state for timeout or invalid config

**Frame Counter Logic:**
```systemverilog
if (cfg_state == CFG_LOAD_FRAMES && cfg_mem_valid) begin
    frame_counter <= frame_counter + 4'd1;
    if (frame_counter == 4'd15) begin  // All 16 PEs configured
        cfg_next_state = CFG_SWAP;
    end
end
```

#### 5.2.3 Memory Interface
```systemverilog
assign cfg_mem_addr = base_addr + {{28'd0}, frame_counter};
assign cfg_mem_read = (cfg_state == CFG_LOAD_FRAMES);
```

**Timing:** Single-cycle read latency assumed, expandable for multi-cycle memory.
```

---

#### 2.5.3 AXI4-Lite CSR (cgra_axi_csr.sv)
**From your code: `00_src/cgra_axi_csr.sv`**

```markdown
### 5.3 AXI4-Lite Control/Status Register Interface

**File:** `00_src/cgra_axi_csr.sv` (340 lines)

#### 5.3.1 Register Map
| Offset | Register | Access | Description |
|--------|----------|--------|-------------|
| 0x00 | CTRL | RW | Control: cgra_start[0], cgra_reset[1], cfg_start[2] |
| 0x04 | STATUS | RO | Status: cgra_busy[0], cgra_done[1], cfg_done[3], error[2] |
| 0x08 | BITSTR_ADDR | RW | Configuration bitstream base address |
| 0x0C | BITSTR_SIZE | RW | Bitstream size in frames (16 for 4×4 array) |
| 0x10 | DMA_DOORBELL | RW | DMA initiation trigger (W1C) |
| 0x14 | DMA_HEAD | RO | DMA head pointer |
| 0x18 | JOB_DESC_ADDR | RW | Job descriptor base address |
| 0x1C | PERF0 | RO | Performance counter: execution cycles |
| 0x20 | PERF1 | RO | Performance counter: stall cycles |
| 0x24 | IRQ_MASK | RW | Interrupt mask: done[0], error[1] |

#### 5.3.2 AXI4-Lite Protocol Implementation

**Write Channel FSM (lines 95-150):**
```
W_IDLE → W_DATA → W_RESP → W_IDLE
  ↑                   ↓
  ←──────────────────←
```

**Write Transaction Timing:**
```
Cycle: |  1  |  2  |  3  |  4  |
-------|-----|-----|-----|-----|
awvalid: ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|___
awready: ______|‾‾‾‾‾|__________
wvalid:  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|___
wready:  ______|‾‾‾‾‾|__________
bvalid:  _____________|‾‾‾‾‾|___
bready:  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
State:   IDLE | DATA| RESP| IDLE
```

**Read Channel FSM (lines 180-220):**
Single-cycle read latency with registered output.

#### 5.3.3 Special Register Behaviors

**STATUS Register (0x04):**
- Read-only, reflects internal state
- Bits [1:0] (done, busy) are Write-1-to-Clear (W1C)
- Reading automatically clears done/busy flags

**Performance Counters (0x1C, 0x20):**
- Auto-increment during EXEC_RUN state
- Reset on cgra_reset or explicit counter clear
- 32-bit wide, wraps on overflow
```

---

#### 2.5.4 Array Integration (cgra_array_4x4.sv)
**From your code: `00_src/cgra_array_4x4.sv`**

```markdown
### 5.4 PE Array Integration

**File:** `00_src/cgra_array_4x4.sv` (365 lines)

#### 5.4.1 Manual Instantiation Approach
**Design Constraint:** No generate blocks or for loops allowed

**Solution:** 16 explicit PE instantiations (lines 80-365):
```systemverilog
cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .SPM_DEPTH(SPM_DEPTH)) pe_00 (
    .clk(clk), .rst_n(rst_n),
    .config_frame(config_frame_00),
    .input_north(16'd0),              // North edge: external
    .input_east(pe_01_to_00_west),    // From East neighbor
    .input_south(pe_10_to_00_north),  // From South neighbor
    .input_west(16'd0),               // West edge: external
    .output_north(pe_00_to_10_south),
    .output_east(pe_00_to_01_west),
    // ...
);
// Repeat for pe_01, pe_02, ... pe_33
```

#### 5.4.2 Interconnection Wiring
**Naming Convention:** `pe_<src>_to_<dst>_<direction>`

**Example:** PE(0,1) → PE(0,0):
```systemverilog
logic [DATA_WIDTH-1:0] pe_01_to_00_west;  // PE(0,1).output_west → PE(0,0).input_east
```

**Total Wires:** 24 internal connections (6 per row/column, excluding edges)

#### 5.4.3 Edge I/O Handling
- North edge (row 0): Connected to external inputs or tied to 16'd0
- South edge (row 3): External outputs available
- East edge (col 3): External outputs available
- West edge (col 0): Connected to external inputs or tied to 16'd0

**Future Enhancement:** Add edge I/O ports for external data injection/extraction.
```

---

## 3. How to Extract Information from Spec

### 3.1 Specification Mining Checklist

**From spec_CGRA.md, extract:**

#### Architecture Section:
- [ ] Array dimensions (4×4)
- [ ] PE count (16)
- [ ] Data width (16-bit)
- [ ] Memory sizes (SPM: 256, RF: 16)
- [ ] Operation count (18 opcodes)

#### Interface Section:
- [ ] Control interface type (AXI4-Lite)
- [ ] Register count (10)
- [ ] Register addresses (0x00-0x24)
- [ ] Signal naming conventions

#### Configuration Section:
- [ ] Frame width (64-bit)
- [ ] Frame format (bit fields)
- [ ] Buffering scheme (double-buffered)
- [ ] Number of frames per context (16)

#### Performance Section:
- [ ] Target frequency (50-100 MHz)
- [ ] Resource estimates (ALMs, registers, RAM bits)
- [ ] Power targets (if specified)

---

## 4. How to Document Code Implementation

### 4.1 Code Documentation Template

For each module, document:

#### Header Information:
```markdown
### X.X ModuleName Implementation

**File:** `path/to/module.sv` (XXX lines)
**Purpose:** [1-sentence description]
**Dependencies:** [List of submodules or external modules]

#### Parameters:
| Parameter | Default | Description |
|-----------|---------|-------------|
| DATA_WIDTH | 16 | Data path width |
| ADDR_WIDTH | 32 | Address width |
```

#### Functional Blocks:
```markdown
#### X.X.1 Block Name
**Lines:** XXX-YYY
**Function:** [Description]

**Implementation:**
[Code snippet]

**Design Rationale:**
- Choice 1: Why this approach
- Choice 2: Alternative considered
```

### 4.2 Code Metrics to Include

For each module:
```markdown
| Metric | Value |
|--------|-------|
| Lines of Code | 343 |
| Combinational Logic Blocks | 5 |
| Sequential Logic Blocks | 3 |
| FSM States | 7 |
| Input Ports | 12 |
| Output Ports | 8 |
| Internal Registers | 15 |
| Memory Arrays | 2 |
```

---

## 5. Verification and Testing

### 5.1 Testbench Documentation

**From your code: `01_bench/tb_cgra_top.sv`**

```markdown
## 6. Verification and Testing

### 6.1 Testbench Architecture

**File:** `01_bench/tb_cgra_top.sv` (806 lines)

#### Test Organization:
1. **Basic Tests (10):** AXI interface, configuration, control flow
2. **Calculation Tests (12):** Arithmetic, logic, SNN operations with result verification
3. **SNN Behavior Tests (8):** LIF neurons, spike generation, multi-layer processing

**Total Test Cases:** 30

#### 6.1.1 Test Infrastructure
```systemverilog
// Test tracking variables
logic [31:0] test_pass_count;
logic [31:0] test_fail_count;
logic [31:0] total_tests;

// Result checking task
task check_result(input string test_name, input logic condition);
    total_tests = total_tests + 1;
    if (condition) begin
        test_pass_count = test_pass_count + 1;
        $display("  [PASS] %s", test_name);
    end else begin
        test_fail_count = test_fail_count + 1;
        $display("  [ERROR] %s", test_name);
    end
endtask
```

### 6.2 Test Results Summary

#### 6.2.1 Functional Verification Results
| Test Category | Tests | Passed | Failed | Pass Rate |
|---------------|-------|--------|--------|-----------|
| Basic Tests | 10 | 10 | 0 | 100% |
| Calculation Tests | 12 | 12 | 0 | 100% |
| SNN Behavior Tests | 8 | 8 | 0 | 100% |
| **Total** | **30** | **30** | **0** | **100%** |

#### 6.2.2 Calculation Verification Table
| Test | Operation | Result | Expected | Status |
|------|-----------|--------|----------|--------|
| 17 | 5 + 3 | 8 | 8 | PASS |
| 18 | 7 × 4 | 28 | 28 | PASS |
| 19 | 15 - 8 | 7 | 7 | PASS |
| 20 | 3 × 4 (MAC) | 12 | 12 | PASS |
| 21 | 10 > 5 | 1 | 1 | PASS |
| 22 | 0xFF & 0x0F | 15 | 15 | PASS |
| 23 | 0xF0 \| 0x0F | 255 | 255 | PASS |
| 24 | 5 << 2 | 20 | 20 | PASS |
| 25 | 8 × 3 (synapse) | 24 | 24 | PASS |
| 26 | 10+5-2 (integration) | 13 | 13 | PASS |
| 27 | 20 > 15 (threshold) | 1 | 1 | PASS |
| 28 | 2×3+4×5 (pipeline) | 26 | 26 | PASS |

### 6.3 Coverage Analysis

#### 6.3.1 Functional Coverage
- ✓ All 18 opcodes exercised
- ✓ All operand source combinations tested
- ✓ All routing patterns verified (unicast, multicast, broadcast)
- ✓ Double-buffer context switching validated
- ✓ AXI4-Lite protocol compliance verified

#### 6.3.2 Corner Cases Tested
1. Edge PE I/O handling (tied inputs)
2. Simultaneous read/write to same SPM address
3. MAC accumulator overflow
4. Configuration swap during execution
5. Performance counter rollover
6. Interrupt generation timing

### 6.4 Debug and Issue Resolution

#### Issue #1: PERF0 Counter Not Incrementing
**Problem:** Performance counter remained at 0 during execution
**Root Cause:** Counter only increments when exec_state == EXEC_RUN
**Solution:** Modified test to ensure FSM reaches RUN state:
```systemverilog
// Before (FAILED):
axi_write(32'h00, 32'h0001);  // Only cgra_start

// After (PASSED):
axi_write(32'h00, 32'h0005);  // cgra_start + cfg_start
#(CLK_PERIOD*10);              // Wait for FSM transition
axi_write(32'h00, 32'h0001);  // Maintain cgra_start
```
**Result:** PERF0 = 88 cycles counted ✓

### 6.5 Simulation Environment
- **Simulator:** Icarus Verilog (iverilog 11.0+)
- **Waveform Viewer:** GTKWave
- **Simulation Time:** 15.7 ms (1,570,000 timesteps @ 1ps resolution)
- **VCD File Size:** ~15 MB
```

---

## 6. Synthesis Results

### 6.1 Synthesis Reporting Template

```markdown
## 7. Synthesis Results

### 7.1 Target Device
- **FPGA:** Intel Cyclone V 5CSXFC6D6F31C6
- **DE10-Standard Board**
- **Available Resources:**
  - ALMs: 41,910
  - Registers: 167,640
  - M10K Blocks: 553
  - DSP Blocks: 112

### 7.2 Resource Utilization

#### 7.2.1 Post-Synthesis Results
| Resource | Used | Available | Utilization |
|----------|------|-----------|-------------|
| ALMs | 12,450 | 41,910 | 29.7% |
| Registers | 8,234 | 167,640 | 4.9% |
| M10K RAM Blocks | 64 | 553 | 11.6% |
| DSP Blocks | 16 | 112 | 14.3% |

**Notes:**
- 1 DSP block per PE for multiply operations
- SPM implemented using M10K blocks (16 PEs × 4 blocks = 64 blocks)
- RF implemented using distributed RAM (registers)

#### 7.2.2 Module-Level Breakdown
| Module | ALMs | Registers | M10K | DSP |
|--------|------|-----------|------|-----|
| cgra_pe (×16) | 650 ea | 450 ea | 4 ea | 1 ea |
| cgra_array_4x4 | 10,400 | 7,200 | 64 | 16 |
| cgra_config_loader | 850 | 512 | 0 | 0 |
| cgra_axi_csr | 450 | 320 | 0 | 0 |
| cgra_top (interconnect) | 750 | 202 | 0 | 0 |
| **Total** | **12,450** | **8,234** | **64** | **16** |

### 7.3 Timing Analysis

#### 7.3.1 Clock Constraints
```sdc
create_clock -name clk -period 10.0 [get_ports clk]  # 100 MHz
set_input_delay -clock clk 2.0 [all_inputs]
set_output_delay -clock clk 2.0 [all_outputs]
```

#### 7.3.2 Timing Results
| Path | Requirement | Achieved | Slack | Status |
|------|-------------|----------|-------|--------|
| Setup (clk) | 10.0 ns | 10.53 ns | 0.53 ns | ✓ PASS |
| Hold (clk) | 0.0 ns | 0.15 ns | 0.15 ns | ✓ PASS |
| Recovery | - | - | 2.3 ns | ✓ PASS |
| Removal | - | - | 1.8 ns | ✓ PASS |

**Maximum Frequency:** 95.0 MHz (10.53 ns period)

#### 7.3.3 Critical Paths
1. **Longest Path (10.2 ns):**
   ```
   PE[2,3].scratchpad[addr] → ALU → MAC accumulator → output_east → 
   PE[2,2].input_west → operand_mux → ALU
   ```
   - Combinational delay: 7.8 ns
   - Routing delay: 2.4 ns

2. **Second Longest (9.8 ns):**
   ```
   config_loader.frame_counter → buffer_select → PE[1,1].config_frame → 
   opcode_decode → ALU
   ```

### 7.4 Power Analysis

#### 7.4.1 Estimated Power (Quartus PowerPlay)
| Component | Power (mW) | Percentage |
|-----------|-----------|------------|
| Core Dynamic | 245 | 62% |
| Core Static | 95 | 24% |
| I/O | 55 | 14% |
| **Total** | **395 mW** | **100%** |

**Conditions:** 95 MHz, typical case, 25°C, 50% toggle rate

### 7.5 Synthesis Tool Flow

**Tools Used:**
- **Quartus Prime:** 20.1.1 Standard Edition
- **Alternative:** Vivado 2021.2 (for Xilinx comparison)

**Compilation Steps:**
1. Analysis & Synthesis
2. Fitter (Place & Route)
3. Timing Analysis
4. Assembler (Bitstream Generation)

**Compilation Time:** ~12 minutes on Intel i7-9700K
```

---

## 7. Performance Analysis

### 7.1 Performance Metrics Template

```markdown
## 8. Performance Analysis

### 8.1 Throughput Analysis

#### 8.1.1 Single PE Performance
- **Operations per cycle:** 1 (single-issue)
- **Pipeline depth:** Non-pipelined ALU (1 cycle latency)
- **MAC throughput:** 1 MAC/cycle (with accumulator reuse)

#### 8.1.2 Array-Level Performance
- **Peak GOPS (at 95 MHz):**
  ```
  16 PEs × 1 op/cycle × 95 MHz = 1.52 GOPS
  ```
- **Peak multiply throughput:**
  ```
  16 DSPs × 95 MHz = 1.52 billion 16×16 multiplications/second
  ```

### 8.2 Application-Specific Performance

#### 8.2.1 SNN Inference Benchmark
**Network:** 784-256-10 (MNIST classification)

**Configuration:**
- Input layer: 784 neurons (mapped to 50 cycles on 16 PEs)
- Hidden layer: 256 LIF neurons (16 cycles)
- Output layer: 10 neurons (1 cycle)

**Measured Performance:**
- **Latency per inference:** 3,420 cycles @ 95 MHz = 36 μs
- **Throughput:** 27,800 inferences/second
- **Energy per inference:** 14.2 μJ (395 mW × 36 μs)

**Comparison to CPU:**
| Metric | CGRA | ARM Cortex-A9 | Speedup |
|--------|------|---------------|---------|
| Latency | 36 μs | 2.8 ms | 77× |
| Energy | 14.2 μJ | 1.4 mJ | 98× |
| Throughput | 27.8k/s | 357/s | 77× |

### 8.3 Reconfiguration Overhead

**Context Switch Time:**
- Configuration load: 16 frames × 10 ns = 160 ns
- Context swap: 1 cycle = 10.5 ns
- **Total:** 170.5 ns

**Effective Overhead:**
- For 1000-cycle execution: 170.5 ns / 10,500 ns = 1.6%
- For 100-cycle execution: 170.5 ns / 1,050 ns = 16.2%

**Conclusion:** Double buffering effectively hides reconfiguration for workloads >500 cycles.

### 8.4 Scalability Analysis

**Array Size vs. Resources:**
| Array | PEs | ALMs | M10K | DSP | Max Freq |
|-------|-----|------|------|-----|----------|
| 2×2 | 4 | 3,200 | 16 | 4 | 110 MHz |
| 4×4 | 16 | 12,450 | 64 | 16 | 95 MHz |
| 8×8 | 64 | 50,800 | 256 | 64 | 75 MHz* |
| 16×16 | 256 | 206,000 | 1024 | 256 | 60 MHz* |

*Estimated based on routing congestion
```

---

## 8. Writing Best Practices

### 8.1 Technical Writing Guidelines

#### Use Clear Structure:
- ✓ Hierarchical numbering (1, 1.1, 1.1.1)
- ✓ Descriptive section titles
- ✓ Consistent terminology
- ✓ Cross-references between sections

#### Include Visual Aids:
- Block diagrams for architecture
- State diagrams for FSMs
- Timing diagrams for protocols
- Tables for specifications
- Charts for performance data

#### Balance Detail:
- **Executive Summary:** High-level only
- **Introduction:** Motivation and goals
- **Architecture:** Moderate detail with diagrams
- **Implementation:** Code snippets, design rationale
- **Results:** Tables, graphs, comparisons

#### Maintain Traceability:
- Spec requirement → Design decision → Implementation → Verification
- Example: "Spec 3.1 requires 18 operations → ALU case statement (lines 107-184) → Test case 17-24 verify all operations"

---

## 9. Report Template

### Complete Report Outline:

```markdown
# CGRA Accelerator for SNN Inference: Design Report

**Author:** [Your Name]
**Date:** December 3, 2025
**Course:** [Course Code]
**Instructor:** [Instructor Name]

---

## Executive Summary
[1 page: Overview, achievements, key metrics]

## 1. Introduction
### 1.1 Background and Motivation
### 1.2 Design Objectives
### 1.3 Report Organization

## 2. System Specification
### 2.1 Functional Requirements
### 2.2 Architecture Overview
### 2.3 Processing Element Specification
### 2.4 Configuration Subsystem
### 2.5 Control Interface

## 3. Architecture Design
### 3.1 Top-Level Architecture
### 3.2 Module Hierarchy
### 3.3 Interface Definition
### 3.4 Design Trade-offs

## 4. Implementation
### 4.1 Processing Element (cgra_pe.sv)
### 4.2 PE Array (cgra_array_4x4.sv)
### 4.3 Configuration Loader (cgra_config_loader.sv)
### 4.4 AXI4-Lite CSR (cgra_axi_csr.sv)
### 4.5 Top-Level Integration (cgra_top.sv)

## 5. Verification and Testing
### 5.1 Testbench Architecture
### 5.2 Test Cases
### 5.3 Functional Verification Results
### 5.4 Coverage Analysis
### 5.5 Debug and Issue Resolution

## 6. Synthesis and Implementation
### 6.1 Target Device
### 6.2 Resource Utilization
### 6.3 Timing Analysis
### 6.4 Power Analysis

## 7. Performance Evaluation
### 7.1 Throughput Analysis
### 7.2 SNN Benchmark Results
### 7.3 Reconfiguration Overhead
### 7.4 Comparison with Alternatives

## 8. Conclusion
### 8.1 Summary of Achievements
### 8.2 Lessons Learned
### 8.3 Future Work

## 9. References

## 10. Appendices
### A. Complete Source Code Listing
### B. Synthesis Reports
### C. Simulation Waveforms
### D. Configuration Examples
```

---

## 10. Quick Reference Checklist

### Before Writing:
- [ ] Read specification thoroughly (spec_CGRA.md)
- [ ] Review all source code (00_src/*.sv)
- [ ] Run all testbenches (01_bench/*.sv)
- [ ] Collect synthesis reports
- [ ] Gather performance measurements

### While Writing:
- [ ] Follow spec → design → code → test flow
- [ ] Include code line references
- [ ] Add diagrams and tables
- [ ] Document design rationale
- [ ] Explain trade-offs
- [ ] Show verification evidence

### After Writing:
- [ ] Verify all spec requirements addressed
- [ ] Check code references are accurate
- [ ] Ensure figures are numbered and referenced
- [ ] Proofread for technical accuracy
- [ ] Validate calculations and metrics
- [ ] Format code snippets properly

---

## 11. Common Mistakes to Avoid

❌ **Don't:**
- Copy spec verbatim without interpretation
- Show code without explanation
- Ignore failed tests or issues
- Omit design rationale
- Use vague language ("good performance", "fast")
- Include irrelevant information

✓ **Do:**
- Interpret spec in context of implementation
- Explain design choices and trade-offs
- Document issues and solutions
- Provide quantitative metrics
- Use precise technical language
- Focus on relevant details

---

## 12. SNN-Specific Interface and Application

### 12.1 SNN Computation Model on CGRA

#### 12.1.1 Leaky Integrate-and-Fire (LIF) Neuron Mapping

**Neuron State Equation:**
```
V_mem(t+1) = V_mem(t) + I_syn(t) - V_leak
if V_mem(t+1) > V_threshold:
    spike = 1
    V_mem = V_reset
else:
    spike = 0
```

**CGRA Implementation Using 3 PEs:**

```markdown
### SNN LIF Neuron Implementation

#### PE Configuration for Single LIF Neuron:

**PE 0 (Integration):** Membrane potential accumulation
```systemverilog
// Configuration Frame for PE 0:
opcode = 4'd1        // ADD operation
opA_sel = 3'd0       // RF[0] = V_mem (previous state)
opB_sel = 3'd3       // Input_north = I_syn (synaptic current)
rf_addr = 4'd0       // Store to RF[0]
rf_we = 1'b1         // Enable write to RF
route_mask = 5'b01010 // Route to East (PE 1) and Local (store)
imm_val0 = 16'd0
```

**PE 1 (Leak Subtraction):**
```systemverilog
// Configuration Frame for PE 1:
opcode = 4'd2        // SUB operation
opA_sel = 3'd6       // Input_west = result from PE 0
opB_sel = 3'd2       // Immediate = V_leak value
rf_addr = 4'd1       // Store to RF[1]
rf_we = 1'b1
route_mask = 5'b01010 // Route to East (PE 2) and Local
imm_val1 = 16'd5     // V_leak = 5 (configurable)
```

**PE 2 (Threshold Comparison & Spike Generation):**
```systemverilog
// Configuration Frame for PE 2:
opcode = 4'd8        // CMP_GT (greater than comparison)
opA_sel = 3'd6       // Input_west = V_mem after leak
opB_sel = 3'd2       // Immediate = V_threshold
rf_addr = 4'd2
rf_we = 1'b1
route_mask = 5'b11110 // Broadcast spike to all neighbors
imm_val1 = 16'd20    // V_threshold = 20 (configurable)
predicate = 1'b0     // Always execute
```

**PE 3 (Membrane Reset - Conditional):**
```systemverilog
// Configuration Frame for PE 3:
opcode = 4'd17       // SELECT operation
opA_sel = 3'd3       // Input_north = V_mem value
opB_sel = 3'd2       // Immediate = V_reset value
opC_sel = 3'd4       // Input_east = spike signal from PE 2
rf_addr = 4'd0       // Write back to V_mem storage
rf_we = 1'b1
imm_val0 = 16'd0     // V_reset = 0
predicate = 1'b1     // Conditional execution based on spike
```

**Data Flow Diagram:**
```
         I_syn (synaptic input)
              ↓
         ┌────────┐
         │  PE 0  │  V_mem + I_syn
         │  ADD   │
         └────────┘
              ↓ (V_mem + I_syn)
         ┌────────┐
         │  PE 1  │  (V_mem + I_syn) - V_leak
         │  SUB   │
         └────────┘
              ↓ (V_mem')
         ┌────────┐
         │  PE 2  │  V_mem' > V_threshold ?
         │ CMP_GT │
         └────────┘
              ↓ (spike)
    ┌─────────┴─────────┐
    │                   │
    ↓                   ↓
spike_out          ┌────────┐
(broadcast)        │  PE 3  │  spike ? V_reset : V_mem'
                   │ SELECT │
                   └────────┘
                        ↓
                   V_mem(t+1)
```

**Timing:** Complete LIF neuron update in 4 cycles (one per PE, pipelined)

#### 12.1.2 Synaptic Processing

**Synapse Equation:**
```
I_syn = Σ(w_i × spike_i)  // Weighted sum of input spikes
```

**CGRA Implementation:**

```markdown
### Synaptic Weight Application

**PE Configuration for Synapse:**
```systemverilog
// PE for weight × spike multiplication
opcode = 4'd3        // MUL operation
opA_sel = 3'd1       // SPM[addr] = synaptic weight w_i
opB_sel = 3'd3       // Input_north = spike_i (0 or 1)
spm_addr = 8'd0      // Address of weight in scratchpad
rf_addr = 4'd3
rf_we = 1'b1
route_mask = 5'b01010 // Route to next PE for accumulation
```

**Multiple Synapses (Fan-in):**
- Use multiple PEs in parallel for different input spikes
- Each PE: one synapse (weight × spike)
- Final PE: accumulate all weighted spikes using ADD or MAC

**Example: 4 Synapses → 1 Neuron:**
```
PE(0,0): w0 × spike0  ─┐
PE(0,1): w1 × spike1  ─┼─→ PE(0,3): Σ(w_i × spike_i) → Neuron
PE(0,2): w2 × spike2  ─┘
PE(1,0): w3 × spike3  ─┘

// PE(0,3) configuration for accumulation:
opcode = 4'd4        // MAC operation
opA_sel = 3'd6       // Input_west = previous sum
opB_sel = 3'd3       // Input_north = new weighted spike
accumulator_reset = (first_spike) ? 1'b1 : 1'b0
```

#### 12.1.3 Spike Routing and Communication

**Spike Broadcasting (1-to-Many):**
```systemverilog
// Source PE broadcasts spike to all neighbors
route_mask = 5'b11110  // N=1, E=1, S=1, W=1, Local=0

// Practical example: Layer 1 Neuron → 4 Layer 2 Neurons
PE(1,1) generates spike:
  output_north → PE(0,1) // Layer 2 Neuron 1
  output_east  → PE(1,2) // Layer 2 Neuron 2
  output_south → PE(2,1) // Layer 2 Neuron 3
  output_west  → PE(1,0) // Layer 2 Neuron 4
```

**Spike Routing (Point-to-Point):**
```systemverilog
// XY routing for distant neurons
// Example: PE(0,0) spike → PE(3,3)
// Route: East → East → East → South → South → South

PE(0,0): route_mask = 5'b01000  // East only
PE(0,1): route_mask = 5'b01000  // East only
PE(0,2): route_mask = 5'b01000  // East only
PE(0,3): route_mask = 5'b00100  // South only
PE(1,3): route_mask = 5'b00100  // South only
PE(2,3): route_mask = 5'b00100  // South only
PE(3,3): route_mask = 5'b00010  // Local (destination)
```

### 12.2 SNN Network Topologies on CGRA

#### 12.2.1 Feedforward Network (784-256-10 MNIST)

**Layer Mapping Strategy:**

```markdown
### Layer 1: Input Layer (784 neurons)
**Mapping:** Time-multiplexed over 16 PEs
- Each PE processes 49 neurons (784 ÷ 16)
- Processing time: 49 cycles per PE
- Configuration: LOAD_IMM or LOAD from external memory

**Configuration per PE:**
```systemverilog
// Load spike pattern from external memory
opcode = 4'd14       // LOAD operation
spm_addr = neuron_id % 49  // Local neuron index
route_mask = 5'b01010 // Route to Layer 2 PEs (East)
```

### Layer 2: Hidden Layer (256 neurons)
**Mapping:** Distributed across 16 PEs
- Each PE handles 16 neurons (256 ÷ 16)
- Each neuron receives from 784 weights
- Processing time: 16 cycles per PE (pipelined)

**Synaptic Processing:**
```systemverilog
// Each PE computes 16 synapses (16 weights × spikes from Layer 1)
// Time-step t:
opcode = 4'd4        // MAC (multiply-accumulate)
opA_sel = 3'd1       // SPM[addr] = weight
opB_sel = 3'd3       // Input from Layer 1 PE
spm_addr = spike_index  // Weight address
rf_addr = neuron_index  // Accumulator for this neuron
rf_we = 1'b1
```

**LIF Neuron Update:**
```systemverilog
// After accumulating all synaptic inputs (784 time-steps):
// Use PE configuration from section 12.1.1 for LIF dynamics
```

### Layer 3: Output Layer (10 neurons)
**Mapping:** 1 PE handles all 10 neurons
- Each neuron receives from 256 Layer 2 neurons
- Classification: argmax(spike_count)

**Timing Analysis:**
```
Layer 1: 49 cycles (time-multiplexed input presentation)
Layer 2: 784 cycles (synaptic accumulation) + 16 cycles (LIF update)
Layer 3: 256 cycles (synaptic accumulation) + 1 cycle (LIF update)
Context Switch: 2 cycles (between layers, hidden by double-buffering)

Total Latency: 49 + 800 + 257 + 4 = 1,110 cycles
At 95 MHz: 1,110 cycles × 10.5 ns = 11.66 μs per inference
```

#### 12.2.2 Recurrent Network (Echo State Network)

**Topology:** Neurons have feedback connections

```markdown
### Recurrent Connection Handling

**Challenge:** Output of neuron feeds back as input in next time-step

**Solution 1: RF Storage**
```systemverilog
// Store output in register file for next cycle
opcode = 4'd1        // ADD (or any operation producing output)
rf_addr = 4'd15      // RF[15] = feedback register
rf_we = 1'b1
route_mask = 5'b00010 // Local output

// Next time-step, use as input:
opA_sel = 3'd0       // RF[15] = previous output
```

**Solution 2: SPM Buffering**
```systemverilog
// Store recurrent spikes in scratchpad
// Time t: Store output
opcode = 4'd15       // STORE operation
spm_addr = time_step % SPM_DEPTH  // Circular buffer
result_out = spike_output

// Time t+1: Load previous spike
opcode = 4'd14       // LOAD operation  
spm_addr = (time_step - 1) % SPM_DEPTH
```

**Recurrent Topology Example:**
```
PE(0,0) ──→ PE(0,1) ──→ PE(0,2)
  ↑          ↑          ↑
  └──────────┴──────────┘ (feedback via RF or SPM)
```

#### 12.2.3 Convolutional SNN

**Convolution Kernel Application:**

```markdown
### 2D Convolution on Spike Maps

**3×3 Kernel Example:**
```
Kernel:        Spike Map:      Output:
[w0 w1 w2]     [s0 s1 s2]
[w3 w4 w5]  ×  [s3 s4 s5]  →  Σ(w_i × s_i)
[w6 w7 w8]     [s6 s7 s8]
```

**PE Mapping (9 PEs for one convolution window):**
```systemverilog
// PE(0,0): w0 × s0
opcode = 4'd3; opA_sel = SPM[0]; opB_sel = Input_north;

// PE(0,1): w1 × s1
opcode = 4'd3; opA_sel = SPM[1]; opB_sel = Input_north;

// ... (PE 0,2 through PE 2,1)

// PE(2,2): Accumulate all partial products
opcode = 4'd4; // MAC
// Accumulates results from all 9 PEs
```

**Sliding Window:**
- Reconfigure PEs for next window position
- Or: Use time-multiplexing with SPM storing entire feature map

### 12.3 SNN-CGRA Interface Protocol

#### 12.3.1 External Memory Interface for Spike Trains

**Spike Train Format:**
```
Memory Layout for Input Spikes:
Address | Data (16-bit)
--------|------------------
0x0000  | neuron[0] spike (0 or 1)
0x0002  | neuron[1] spike
0x0004  | neuron[2] spike
...
0x0618  | neuron[783] spike (784 total for MNIST)
```

**CGRA Access Pattern:**
```systemverilog
// PE configuration to read spike trains
opcode = 4'd14       // LOAD from external memory
spm_addr = neuron_id // Local buffer address
data_mem_addr = base_addr + (neuron_id << 1)  // Word-aligned
data_mem_read = 1'b1

// Sequence:
// Cycle 0: Request spike[0]
// Cycle 1: Request spike[1], receive spike[0]
// Cycle 2: Request spike[2], receive spike[1], process spike[0]
```

#### 12.3.2 Weight Memory Organization

**Synaptic Weight Storage in SPM:**

```markdown
### Weight Distribution Strategy

**Option 1: Distributed Weights (Each PE stores subset)**
```
PE(0,0) SPM: weights for neurons 0-15   (256 weights each)
PE(0,1) SPM: weights for neurons 16-31
...
PE(3,3) SPM: weights for neurons 240-255

Total Weight Storage: 16 PEs × 256 weights × 16-bit = 8 KB
```

**Option 2: Replicated Weights (Each PE stores all weights for its neurons)**
```systemverilog
// PE handling neuron_i stores all incoming weights
SPM[0] = weight from input[0] to neuron_i
SPM[1] = weight from input[1] to neuron_i
...
SPM[255] = weight from input[255] to neuron_i

// Access during processing:
opcode = 4'd3        // MUL
opA_sel = 3'd1       // SPM[input_spike_id]
opB_sel = 3'd3       // Input spike value
```

#### 12.3.3 Timestep Synchronization

**Global Time-step Counter:**
```systemverilog
// Implemented in cgra_top.sv or external controller
logic [15:0] global_timestep;

always_ff @(posedge clk) begin
    if (!rst_n || timestep_reset)
        global_timestep <= 16'd0;
    else if (timestep_increment)
        global_timestep <= global_timestep + 16'd1;
end

// Broadcast to all PEs via configuration frame or control signal
```

**Synchronization Protocol:**
```
Time-step t:
1. All PEs load configuration for time t
2. All PEs execute operations
3. All PEs exchange data via mesh network
4. Global sync signal increments timestep
5. Repeat for time-step t+1

Double-buffering ensures:
- Configuration for t+1 loads during execution of t
- Zero-stall transition between timesteps
```

### 12.4 SNN Programming Model

#### 12.4.1 High-Level SNN Description

**Python-like Pseudocode:**
```python
class LIFNeuron:
    def __init__(self, threshold=20, leak=5, reset=0):
        self.V_mem = 0
        self.V_threshold = threshold
        self.V_leak = leak
        self.V_reset = reset
    
    def update(self, I_syn):
        # Integration
        self.V_mem += I_syn
        # Leak
        self.V_mem -= self.V_leak
        # Threshold check
        if self.V_mem > self.V_threshold:
            spike = 1
            self.V_mem = self.V_reset
        else:
            spike = 0
        return spike

class SynapticLayer:
    def __init__(self, n_inputs, n_neurons):
        self.weights = random_weights(n_inputs, n_neurons)
    
    def process(self, input_spikes):
        return matmul(self.weights, input_spikes)

# Network definition
layer1 = SynapticLayer(784, 256)
neurons = [LIFNeuron() for _ in range(256)]

# Inference
for timestep in range(simulation_time):
    input_spikes = get_input_spikes(timestep)
    synaptic_currents = layer1.process(input_spikes)
    output_spikes = [n.update(I) for n, I in zip(neurons, synaptic_currents)]
```

#### 12.4.2 Mapping to CGRA Configuration

**Translation Process:**

```markdown
### Compilation Flow: SNN → CGRA Configuration

**Step 1: Network Analysis**
- Extract: number of layers, neurons per layer, connectivity
- Identify: weight matrices, neuron parameters (V_th, V_leak, etc.)

**Step 2: PE Allocation**
```
Layer 1 (784 neurons) → 16 PEs (49 neurons each, time-multiplexed)
Layer 2 (256 neurons) → 16 PEs (16 neurons each)
Layer 3 (10 neurons)  → 1 PE (all 10 neurons)
```

**Step 3: Configuration Generation**
For each PE, generate configuration frames:

```systemverilog
// Pseudo-code for configuration generator
function generate_config(layer, neuron_params, weights):
    config_frame = 64'b0
    
    // Set operation based on computation stage
    if stage == SYNAPTIC:
        config_frame.opcode = MAC
        config_frame.opA_sel = SPM  // Weight
        config_frame.opB_sel = INPUT_NORTH  // Spike
    elif stage == INTEGRATION:
        config_frame.opcode = ADD
        config_frame.opA_sel = RF[V_mem]
        config_frame.opB_sel = INPUT_WEST  // Synaptic current
    elif stage == LEAK:
        config_frame.opcode = SUB
        config_frame.imm_val1 = neuron_params.V_leak
    elif stage == THRESHOLD:
        config_frame.opcode = CMP_GT
        config_frame.imm_val1 = neuron_params.V_threshold
    
    // Set routing based on network topology
    config_frame.route_mask = get_routing(neuron_id, next_layer)
    
    return config_frame
```

**Step 4: Weight Loading**
```c
// Load weights into PE scratchpads
for pe_id in range(16):
    for addr in range(256):
        weight = weight_matrix[pe_id][addr]
        write_spm(pe_id, addr, weight)
```

**Step 5: Execution Control**
```c
// Configure CGRA for inference
write_csr(BITSTR_ADDR, config_base_address)
write_csr(BITSTR_SIZE, 16)  // 16 PEs
write_csr(CTRL, CGRA_START | CFG_START)

// Wait for completion
while (!(read_csr(STATUS) & CGRA_DONE)) {
    // Process intermediate results if needed
}

// Read output spikes
output = read_output_spikes()
```

### 12.5 Performance Metrics for SNN on CGRA

#### 12.5.1 Latency Analysis

**Single Neuron Update:**
```
Integration:     1 cycle (ADD)
Leak:            1 cycle (SUB)
Threshold:       1 cycle (CMP_GT)
Reset:           1 cycle (SELECT)
------------------------------------
Total:           4 cycles = 42 ns @ 95 MHz
```

**Full Network Inference (784-256-10):**
```
Input presentation:    49 cycles (time-multiplexed)
Synaptic processing:   784 cycles (sequential weight applications)
Layer 2 updates:       16 cycles (parallel across 16 PEs)
Layer 3 processing:    256 + 1 cycles
------------------------------------
Total:                 ~1,106 cycles = 11.6 μs @ 95 MHz
```

**Throughput:**
```
Inferences per second = 95 MHz / 1,106 cycles = 85,895 inferences/s
```

#### 12.5.2 Energy Efficiency

**Energy per Inference:**
```
Power consumption: 395 mW (from synthesis)
Latency:          11.6 μs
Energy:           395 mW × 11.6 μs = 4.58 μJ per inference
```

**Comparison:**
```
| Platform      | Energy/Inference | Speedup vs CGRA |
|---------------|------------------|-----------------|
| CGRA (ours)   | 4.58 μJ         | 1× (baseline)   |
| ARM Cortex-A9 | 1.4 mJ          | 0.003×          |
| GPU (Jetson)  | 250 μJ          | 0.018×          |
| Neuromorphic  | 0.5 μJ          | 9.2× better     |

Note: CGRA offers good balance of flexibility vs efficiency
```

#### 12.5.3 Resource Utilization Efficiency

**Operations per Unit Area:**
```
Total operations per inference: 
  Layer 1→2: 784 × 256 = 200,704 MACs
  Layer 2→3: 256 × 10 = 2,560 MACs
  Total: 203,264 operations

GOPS per inference: 203,264 ops / 11.6 μs = 17.5 GOPS peak

GOPS per ALM: 17.5 GOPS / 12,450 ALMs = 1.4 MOPS/ALM
```

### 12.6 Example SNN Application Configuration

#### 12.6.1 MNIST Digit Recognition

**Complete Configuration Sequence:**

```c
// Step 1: Load network weights into SPMs
for (int pe = 0; pe < 16; pe++) {
    for (int addr = 0; addr < 256; addr++) {
        int neuron_id = pe * 16 + (addr / 16);  // Layer 2 neuron
        int input_id = addr % 784;              // Layer 1 neuron
        float weight = layer1_weights[input_id][neuron_id];
        write_spm(pe, addr, float_to_fixed16(weight));
    }
}

// Step 2: Load configuration for synaptic processing
uint64_t synapse_config[16];
for (int pe = 0; pe < 16; pe++) {
    synapse_config[pe] = 
        (MAC << 0) |          // opcode
        (SPM << 4) |          // opA from SPM (weight)
        (INPUT_N << 7) |      // opB from North (spike)
        (0 << 10) |           // SPM addr (will auto-increment)
        (RF_ACCUM << 18) |    // Store in accumulator RF
        (1 << 22) |           // RF write enable
        (ROUTE_E << 23);      // Route to East neighbor
}
load_configuration(synapse_config, 16);

// Step 3: Load configuration for LIF neurons
uint64_t lif_config[16];
for (int pe = 0; pe < 16; pe++) {
    lif_config[pe] = 
        (ADD << 0) |          // Integration stage
        (RF_VMEM << 4) |      // Previous V_mem
        (INPUT_W << 7) |      // Synaptic current from West
        (5 << 44) |           // imm_val1 = V_leak
        (20 << 60);           // V_threshold (in extended field)
}

// Step 4: Stream input spikes
for (int time = 0; time < simulation_steps; time++) {
    uint16_t input_spikes[784];
    get_mnist_spikes(mnist_image, time, input_spikes);
    
    // Write spikes to data memory
    for (int i = 0; i < 784; i++) {
        write_data_mem(INPUT_SPIKE_BASE + i*2, input_spikes[i]);
    }
    
    // Trigger CGRA execution for this timestep
    write_csr(CTRL, CGRA_START);
    while (!(read_csr(STATUS) & CGRA_DONE));
    
    // Read intermediate spikes if needed
    // (for multi-layer processing)
}

// Step 5: Read final classification
uint16_t output_spikes[10];
for (int i = 0; i < 10; i++) {
    output_spikes[i] = read_output(OUTPUT_BASE + i*2);
}
int predicted_digit = argmax(output_spikes);
```

#### 12.6.2 Configuration Frame Examples

**LIF Neuron Complete 4-PE Pipeline:**
```systemverilog
// PE 0: Integration (V_mem + I_syn)
config_frame_00 = 64'h0000_0000_0241_0301;
//                    ^^^^ ^^^^ ^^^^ ^^^^
//                    |    |    |    └─ opcode=1 (ADD)
//                    |    |    └────── opA=RF[0], opB=Input_N
//                    |    └─────────── route_mask=00010 (East)
//                    └──────────────── imm values (unused)

// PE 1: Leak Subtraction (result - V_leak)
config_frame_01 = 64'h0005_0000_0241_0662;
//                    ^^^^ ^^^^ ^^^^ ^^^^
//                    |    |    |    └─ opcode=2 (SUB)
//                    |    |    └────── opA=Input_W, opB=Imm
//                    |    └─────────── route_mask=00010 (East)
//                    └──────────────── imm_val1=5 (V_leak)

// PE 2: Threshold Check (V_mem > V_threshold)
config_frame_02 = 64'h0014_0000_1E41_0668;
//                    ^^^^ ^^^^ ^^^^ ^^^^
//                    |    |    |    └─ opcode=8 (CMP_GT)
//                    |    |    └────── route=11110 (broadcast)
//                    └──────────────── imm_val1=20 (V_threshold)

// PE 3: Conditional Reset
config_frame_03 = 64'h0000_0000_0241_4711;
//                                  ^ ^^^
//                                  | └── opcode=17 (SELECT)
//                                  └──── predicate=1 (conditional)
```

### 12.7 Debugging SNN Applications on CGRA

#### 12.7.1 Common Issues and Solutions

**Issue 1: Neurons Not Spiking**
```markdown
Symptoms: All output_spikes = 0

Debug steps:
1. Check V_threshold value (might be too high)
2. Verify synaptic weights are loaded correctly
3. Confirm input spikes are being received
4. Check membrane potential accumulation (read RF values)

Solution:
// Add debug configuration to read V_mem
opcode = 4'd16       // LOAD_IMM (output V_mem for monitoring)
route_mask = 5'b00010 // Route to external output
```

**Issue 2: Excessive Spiking**
```markdown
Symptoms: All neurons spike every cycle

Debug steps:
1. Verify V_leak is applied (configuration frame PE 1)
2. Check reset mechanism (PE 3 SELECT operation)
3. Confirm V_threshold comparison is correct

Solution:
// Increase leak or threshold:
imm_val1 = 16'd10;   // Increase V_leak from 5 to 10
// Or:
imm_val1 = 16'd30;   // Increase V_threshold from 20 to 30
```

**Issue 3: Timing Misalignment**
```markdown
Symptoms: Spikes arrive at wrong neurons or timesteps

Debug steps:
1. Verify routing configuration (route_mask bits)
2. Check timestep synchronization
3. Confirm double-buffering is working

Solution:
// Add explicit sync points in configuration:
// Wait for all PEs to complete before advancing timestep
```

### 12.8 Advanced SNN Features

#### 12.8.1 Spike-Timing Dependent Plasticity (STDP)

**Weight Update Rule:**
```
Δw = A_+ × exp(-Δt/τ_+)   if pre before post (LTP)
Δw = -A_- × exp(Δt/τ_-)   if post before pre (LTD)
```

**CGRA Implementation:**
```systemverilog
// Requires additional PEs for weight updates
// PE for time difference calculation:
opcode = 4'd2        // SUB
opA_sel = 3'd0       // RF[t_post]
opB_sel = 3'd1       // RF[t_pre]
// Result: Δt

// PE for exponential approximation (piecewise linear):
opcode = 4'd12       // SHR (divide by 2^n for exp approximation)
opB_sel = 3'd2       // Immediate = shift amount
// Simplified: exp(-Δt/τ) ≈ 1 >> (Δt/τ)

// PE for weight update:
opcode = 4'd1        // ADD
opA_sel = 3'd1       // SPM[addr] = current weight
opB_sel = 3'd3       // Input = Δw from previous PE
spm_addr = synapse_id
// Write updated weight back to SPM
```

#### 12.8.2 Multiple Neuron Models

**ALIF (Adaptive LIF):**
```systemverilog
// Additional PE for threshold adaptation
// θ(t+1) = θ(t) + a(θ_rest - θ(t))

opcode = 4'd2        // SUB
opA_sel = 3'd2       // Immediate = θ_rest
opB_sel = 3'd0       // RF[θ_current]
// Multiply by adaptation rate 'a'
// Add to current threshold
```

**Izhikevich Model:**
```systemverilog
// More complex, requires multiple PEs
// v' = 0.04v² + 5v + 140 - u + I
// u' = a(bv - u)

// Needs 5-6 PEs per neuron:
// PE1: v² calculation (MUL v, v)
// PE2: 0.04v² (MUL by constant)
// PE3: 5v + 140 (MAC)
// PE4: subtract u, add I (SUB, ADD)
// PE5: bv (MUL)
// PE6: u update (SUB, MUL by a)
```

---

## End of SNN-Specific Guide Section

**Key Takeaway:** A good report tells the story of how you translated a specification into working hardware, showing the design decisions, implementation details, verification process, and final results with clear traceability throughout.

**Remember:** Your report should allow someone else to understand your design, reproduce your results, and extend your work.
