# CGRA Build and Synthesis Guide

## Overview
This guide provides instructions for building, simulating, and synthesizing the CGRA IP core.

## Prerequisites

### For Simulation
- **Icarus Verilog** (iverilog) v10.0 or later
- **VVP** (Verilog simulator)
- **GTKWave** (optional, for waveform viewing)

Install on Ubuntu/Debian:
```bash
sudo apt-get install iverilog gtkwave
```

### For Synthesis (Intel/Altera FPGA)
- **Intel Quartus Prime** (Lite Edition or Standard)
- **DE10-Standard FPGA** board files
- **ModelSim** (optional, for advanced simulation)

### For Synthesis (Xilinx FPGA)
- **Vivado Design Suite**
- **Appropriate FPGA board files**

## Directory Structure
```
CGRA_project/
├── 00_src/           # RTL source files
├── 01_bench/         # Testbenches
├── 02_test/          # Test vectors and scripts
├── 03_sim/           # Simulation outputs
└── 04_doc/           # Documentation
```

## Simulation Workflow

### Step 1: Navigate to Testbench Directory
```bash
cd 01_bench
```

### Step 2: Run Individual Testbench
```bash
# PE testbench
./run_sim.sh tb_cgra_pe

# Router testbench
./run_sim.sh tb_cgra_router

# Configuration loader testbench
./run_sim.sh tb_cgra_config_loader

# Top-level integration testbench
./run_sim.sh tb_cgra_top
```

### Step 3: View Waveforms (if generated)
```bash
cd ../03_sim
gtkwave cgra_top.vcd
```

### Manual Simulation Commands
```bash
# Compile
iverilog -g2012 -o sim.vvp \
    ../00_src/cgra_pe.sv \
    ../00_src/cgra_router.sv \
    ../00_src/cgra_array_4x4.sv \
    ../00_src/cgra_config_loader.sv \
    ../00_src/cgra_axi_csr.sv \
    ../00_src/cgra_top.sv \
    tb_cgra_top.sv

# Run
vvp sim.vvp

# View
gtkwave dump.vcd
```

## Synthesis Workflow (Intel Quartus)

### Step 1: Create New Project
1. Open Quartus Prime
2. File → New Project Wizard
3. Select project directory and name
4. Choose device: Cyclone V (5CSXFC6D6F31C6)
5. Add design files from `00_src/`

### Step 2: Set Top-Level Entity
1. Project → Set as Top-Level Entity
2. Select `cgra_top`

### Step 3: Pin Assignment (if targeting DE10-Standard)
```tcl
# Create pin assignment file (cgra_pins.tcl)
set_location_assignment PIN_AF14 -to clk
set_location_assignment PIN_AA14 -to rst_n
# ... add more pins as needed
```

Load pins:
```bash
quartus_sta --tcl_script cgra_pins.tcl cgra_top
```

### Step 4: Compile Design
```bash
# Command-line compilation
quartus_sh --flow compile cgra_top

# Or use GUI: Processing → Start Compilation
```

### Step 5: Analyze Results
Check:
- **Logic utilization**: Should fit in ~20K LUTs
- **Memory usage**: ~70 Kbits
- **Timing**: Target 50-100 MHz (Fmax)
- **Warnings**: Address any critical warnings

### Step 6: Program FPGA
```bash
quartus_pgm -c USB-Blaster -m JTAG -o "p;output_files/cgra_top.sof"
```

## Synthesis Workflow (Xilinx Vivado)

### Step 1: Create Project
```tcl
# Create project script (create_project.tcl)
create_project cgra_project ./vivado_proj -part xc7a100tcsg324-1

# Add source files
add_files {
    ../00_src/cgra_pe.sv
    ../00_src/cgra_router.sv
    ../00_src/cgra_array_4x4.sv
    ../00_src/cgra_config_loader.sv
    ../00_src/cgra_axi_csr.sv
    ../00_src/cgra_top.sv
}

set_property top cgra_top [current_fileset]
```

Run script:
```bash
vivado -mode batch -source create_project.tcl
```

### Step 2: Synthesize
```tcl
# In Vivado TCL console
synth_design -top cgra_top -part xc7a100tcsg324-1
```

### Step 3: Implement
```tcl
opt_design
place_design
route_design
```

### Step 4: Generate Bitstream
```tcl
write_bitstream -force cgra_top.bit
```

## Constraints

### Timing Constraints (SDC/XDC)
```tcl
# Create constraints file (cgra_constraints.xdc)

# Clock constraint - 50 MHz target
create_clock -period 20.000 -name clk [get_ports clk]

# Input delays
set_input_delay -clock clk -max 3.0 [all_inputs]
set_input_delay -clock clk -min 1.0 [all_inputs]

# Output delays
set_output_delay -clock clk -max 3.0 [all_outputs]
set_output_delay -clock clk -min 1.0 [all_outputs]

# False paths for async reset
set_false_path -from [get_ports rst_n]
```

### Synthesis Directives
```systemverilog
// Add to top of modules for synthesis control

(* keep_hierarchy = "yes" *)  // Preserve module boundaries
(* ram_style = "block" *)      // Use block RAM
(* dont_touch = "yes" *)       // Prevent optimization
```

## Expected Resource Usage

### Intel Cyclone V
| Resource | Used | Available | Utilization |
|----------|------|-----------|-------------|
| ALMs     | ~10K | 41,910    | ~24%        |
| Registers| ~15K | 166,036   | ~9%         |
| M10K     | 20   | 553       | ~4%         |
| DSP      | 32   | 112       | ~29%        |

### Xilinx Artix-7
| Resource | Used | Available | Utilization |
|----------|------|-----------|-------------|
| LUTs     | ~20K | 63,400    | ~32%        |
| FFs      | ~15K | 126,800   | ~12%        |
| BRAM     | 10   | 135       | ~7%         |
| DSP48    | 32   | 240       | ~13%        |

## Common Build Issues

### Issue 1: Width Mismatch Warnings
**Symptom**: Width warnings during compilation
**Solution**: These are intentional for 16-bit to 32-bit conversions. Can be ignored or fixed with explicit casts.

```systemverilog
// Instead of:
alu_result <= operand0 + operand1;

// Use:
alu_result <= {16'h0, operand0} + {16'h0, operand1};
```

### Issue 2: Timing Not Met
**Symptom**: Fmax < 50 MHz
**Solution**: 
1. Add pipeline stages in critical paths
2. Use retiming optimization
3. Constrain placement of critical modules

### Issue 3: Memory Inference Failed
**Symptom**: SPM not mapped to block RAM
**Solution**: Ensure memory is accessed with synchronous reads

```systemverilog
always_ff @(posedge clk) begin
    spm_rdata <= spm_mem[spm_addr];  // Good
end

// Not: assign spm_rdata = spm_mem[spm_addr];  // Bad
```

### Issue 4: AXI Interface Errors
**Symptom**: AXI protocol violations
**Solution**: Verify handshake timing in simulation
- Check VALID/READY protocol
- Ensure no combinatorial loops
- Add pipeline stages if needed

## Verification Checklist

- [ ] All testbenches pass
- [ ] No synthesis errors
- [ ] No critical warnings
- [ ] Timing constraints met (Fmax ≥ 50 MHz)
- [ ] Resource usage within target
- [ ] No latch inference
- [ ] All memories mapped to block RAM
- [ ] AXI interface verified
- [ ] Reset behavior correct
- [ ] Clock domain crossings handled

## Performance Optimization

### 1. Increase Clock Frequency
- Pipeline deep combinatorial paths
- Use fast carry chains
- Optimize critical PE operations

### 2. Reduce Resource Usage
- Share resources between PEs
- Use distributed RAM for small memories
- Optimize routing network

### 3. Improve Throughput
- Increase PE utilization
- Optimize configuration loading
- Reduce pipeline bubbles

## Debug Techniques

### Simulation Debug
```systemverilog
// Add debug outputs
output logic [31:0] debug_pe_state;
output logic [15:0] debug_alu_result;

// Monitor internal signals
$monitor("Time=%0t PE_state=%h ALU=%h", 
         $time, debug_pe_state, debug_alu_result);
```

### Hardware Debug (Signal Tap / ILA)
1. Insert logic analyzer IP
2. Probe critical signals
3. Set trigger conditions
4. Capture runtime data

### ChipScope / SignalTap Example
```tcl
# Add probes to critical signals
create_debug_core u_ila ila
set_property C_DATA_DEPTH 1024 [get_debug_cores u_ila]
connect_debug_port u_ila/clk [get_nets clk]
connect_debug_port u_ila/probe0 [get_nets config_valid]
connect_debug_port u_ila/probe1 [get_nets cgra_busy]
```

## Testing on Hardware

### Test Sequence
1. Load bitstream
2. Initialize via AXI-Lite
3. Load configuration
4. Start execution
5. Monitor performance counters
6. Verify results

### Sample Test Code (C)
```c
// Memory-mapped register access
#define CGRA_BASE 0x43C00000
#define CTRL      (CGRA_BASE + 0x00)
#define STATUS    (CGRA_BASE + 0x04)
#define PERF0     (CGRA_BASE + 0x1C)

// Configure
*(volatile uint32_t*)(CGRA_BASE + 0x08) = 0x10000000; // Bitstream addr
*(volatile uint32_t*)(CGRA_BASE + 0x0C) = 16;         // Size

// Load config
*(volatile uint32_t*)CTRL = 0x04;  // cfg_start
while (!(*(volatile uint32_t*)STATUS & 0x08));  // Wait cfg_done

// Execute
*(volatile uint32_t*)CTRL = 0x01;  // cgra_start
while (*(volatile uint32_t*)STATUS & 0x01);  // Wait while busy

// Read results
uint32_t cycles = *(volatile uint32_t*)PERF0;
printf("Execution took %d cycles\n", cycles);
```

## Maintenance

### Adding New Operations
1. Add opcode to `cgra_pe.sv`
2. Implement in ALU case statement
3. Update documentation
4. Add testbench tests

### Scaling Array Size
1. Modify `cgra_array_4x4.sv` (e.g., to 8x8)
2. Update configuration loader for new PE count
3. Adjust resource parameters
4. Regenerate interconnect

---
**Build Guide v1.0** - December 3, 2025
