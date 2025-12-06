# CGRA Quick Reference Guide

## Operation Codes

| Code | Mnemonic   | Operation              | Example Config                    |
|------|------------|------------------------|-----------------------------------|
| 0    | NOP        | No operation           | `64'h0000_0000_0000_0000`        |
| 1    | ADD        | dst = src0 + src1      | `64'h0000_000A_0000_6641`        |
| 2    | SUB        | dst = src0 - src1      | `64'h0000_000A_0000_6642`        |
| 3    | MUL        | dst = src0 * src1      | `64'h0000_000A_0000_6643`        |
| 4    | MAC        | acc += src0 * src1     | `64'h0000_000A_0000_6644`        |
| 5    | AND        | dst = src0 & src1      | `64'h0000_000A_0000_6645`        |
| 6    | OR         | dst = src0 \| src1     | `64'h0000_000A_0000_6646`        |
| 7    | XOR        | dst = src0 ^ src1      | `64'h0000_000A_0000_6647`        |
| 8    | SHL        | dst = src0 << src1     | `64'h0000_000A_0000_6648`        |
| 9    | SHR        | dst = src0 >> src1     | `64'h0000_000A_0000_6649`        |
| 10   | CMP_GT     | dst = (src0 > src1)    | `64'h0000_000A_0000_664A`        |
| 11   | CMP_LT     | dst = (src0 < src1)    | `64'h0000_000A_0000_664B`        |
| 12   | CMP_EQ     | dst = (src0 == src1)   | `64'h0000_000A_0000_664C`        |
| 13   | LOAD_SPM   | dst = SPM[src1]        | `64'h0000_0000_0000_004D`        |
| 14   | STORE_SPM  | SPM[src1] = src0       | `64'h0000_0000_0000_004E`        |
| 15   | ACC_CLR    | acc = 0                | `64'h0000_0000_0000_000F`        |
| 16   | PASS0      | dst = src0             | `64'h0000_0000_0000_0650`        |
| 17   | PASS1      | dst = src1             | `64'h0000_0000_0000_0651`        |

## Source/Destination Selectors

| Code | Source           | Description                    |
|------|------------------|--------------------------------|
| 0    | RF[addr]         | Register file at addr          |
| 1    | North input      | Data from north neighbor       |
| 2    | East input       | Data from east neighbor        |
| 3    | South input      | Data from south neighbor       |
| 4    | West input       | Data from west neighbor        |
| 5    | SPM[addr]        | Scratchpad memory              |
| 6    | Immediate        | 16-bit immediate value         |
| 7+   | Reserved         | Future use                     |

## Routing Mask (5 bits)

| Bit | Direction | Description                    |
|-----|-----------|--------------------------------|
| [4] | Local     | Output to local PE             |
| [3] | North     | Output to north neighbor       |
| [2] | East      | Output to east neighbor        |
| [1] | South     | Output to south neighbor       |
| [0] | West      | Output to west neighbor        |

Example: `5'b11111` = broadcast to all directions

## Configuration Frame Builder

```systemverilog
// Helper function to build config frame
function [63:0] build_config(
    input [5:0]  opcode,
    input [3:0]  src0,
    input [3:0]  src1,
    input [3:0]  dst,
    input [4:0]  route,
    input        pred_en,
    input        pred_inv,
    input [15:0] immediate
);
    build_config = {24'h0, immediate, pred_inv, pred_en, route, dst, src1, src0, opcode};
endfunction

// Example: ADD RF[0] and immediate 10, store in RF[1], output to local
config_frame = build_config(
    .opcode(6'd1),        // ADD
    .src0(4'd0),          // RF[0]
    .src1(4'd6),          // Immediate
    .dst(4'd1),           // RF[1]
    .route(5'b10000),     // Local only
    .pred_en(1'b0),
    .pred_inv(1'b0),
    .immediate(16'd10)
);
```

## AXI4-Lite Transaction Examples

### Write to Control Register
```systemverilog
// Start CGRA execution
s_axi_awaddr = 32'h0000_0000;  // CTRL register
s_axi_wdata = 32'h0000_0001;   // Set start bit
s_axi_awvalid = 1;
s_axi_wvalid = 1;
// ... handshake ...
```

### Read Status Register
```systemverilog
// Check if CGRA is busy
s_axi_araddr = 32'h0000_0004;  // STATUS register
s_axi_arvalid = 1;
// ... wait for rvalid ...
// s_axi_rdata[0] = busy flag
```

### Configure Bitstream
```systemverilog
// Step 1: Set bitstream address
s_axi_awaddr = 32'h0000_0008;
s_axi_wdata = 32'h0001_0000;   // Address in memory

// Step 2: Set bitstream size
s_axi_awaddr = 32'h0000_000C;
s_axi_wdata = 32'h0000_0010;   // 16 frames

// Step 3: Start configuration load
s_axi_awaddr = 32'h0000_0000;
s_axi_wdata = 32'h0000_0004;   // Set cfg_start bit
```

## Common Usage Patterns

### Pattern 1: Simple MAC Loop
```
Frame 0: LOAD_SPM  - Load weight from SPM
Frame 1: MUL       - Multiply with input
Frame 2: MAC       - Accumulate result
Frame 3: STORE_SPM - Store result
```

### Pattern 2: Broadcast Spike
```
Config: PASS0 with route=5'b01111  - Send to all neighbors
```

### Pattern 3: Conditional Execution
```
Frame 0: CMP_GT    - Compare values, set predicate
Frame 1: ADD       - Executed only if predicate true
         (pred_en=1)
```

## PE Coordinate Mapping

```
        X=0    X=1    X=2    X=3
Y=0   PE(0,0) PE(0,1) PE(0,2) PE(0,3)
Y=1   PE(1,0) PE(1,1) PE(1,2) PE(1,3)
Y=2   PE(2,0) PE(2,1) PE(2,2) PE(2,3)
Y=3   PE(3,0) PE(3,1) PE(3,2) PE(3,3)
```

## Typical Workflow

1. **Configuration Phase**
   - Write bitstream address to CSR[0x08]
   - Write bitstream size to CSR[0x0C]
   - Set cfg_start bit in CSR[0x00]
   - Wait for cfg_done in CSR[0x04]

2. **Execution Phase**
   - Set cgra_start bit in CSR[0x00]
   - Monitor busy flag in CSR[0x04]
   - Wait for done flag in CSR[0x04]

3. **Results Collection**
   - Read performance counters CSR[0x1C], CSR[0x20]
   - Access PE scratchpad memories (if needed)
   - Clear done flag (W1C to CSR[0x04])

## Debug Tips

1. **Check Config Valid**: Ensure config_valid is asserted during execution
2. **Monitor Routing**: Check valid_out_* signals on PEs
3. **Verify FSM States**: Use simulation to track state transitions
4. **Performance Analysis**: Compare PERF0 and PERF1 counters
5. **Waveform Analysis**: Use GTKWave to visualize signal flow

## Common Errors

| Error | Symptom | Solution |
|-------|---------|----------|
| No output | valid_out_* = 0 | Check route mask in config |
| Wrong result | Incorrect data | Verify opcode and operand selectors |
| Config not loading | load_done = 0 | Check memory interface handshake |
| Stalls | PERF1 high | Verify config_valid during RUN state |

## Simulation Quick Start

```bash
# Single testbench
cd 01_bench
./run_sim.sh tb_cgra_pe

# View waveforms
cd ../03_sim
gtkwave cgra_top.vcd

# Run all tests
for tb in tb_cgra_pe tb_cgra_router tb_cgra_config_loader tb_cgra_top; do
    ./run_sim.sh $tb
done
```

## Memory Map Summary

| Address Range | Module                | Access |
|---------------|----------------------|--------|
| 0x00 - 0x24   | CSR Registers        | R/W    |
| TBD           | PE Scratchpads       | R/W    |
| TBD           | Configuration Memory | R      |
| TBD           | Data Memory          | R/W    |

---
**Quick Reference v1.0** - December 3, 2025
