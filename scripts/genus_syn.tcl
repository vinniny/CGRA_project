# ==============================================================================
# Genus Synthesis Script for CGRA 4x4 Project
# ==============================================================================
# PDK:    FreePDK45 / GSCL 45nm (typical corner)
# Target: 100 MHz (10ns clock period)
# Usage:  genus -batch -files genus_syn.tcl -log genus.log
#         (or via: make syn)
# ==============================================================================

# ==============================================================================
# Output Directories
# ==============================================================================
file mkdir reports
file mkdir syn_out

# ==============================================================================
# Library Setup — FreePDK45 GSCL 45nm
# ==============================================================================
puts "=========================================================================="
puts " Library Setup: FreePDK45 GSCL 45nm (typical)"
puts "=========================================================================="

set LIB_DIR "/opt/PDKs/FreePDK45/osu_soc/lib/files"

set_db init_lib_search_path "$LIB_DIR ../00_src ../00_src/bsg_mem"
set_db init_hdl_search_path "../00_src ../00_src/bsg_mem"

set_db library "$LIB_DIR/gscl45nm.lib"
set_db lef_library "$LIB_DIR/gscl45nm.lef"

# ==============================================================================
# Read RTL Sources
# ==============================================================================
puts "=========================================================================="
puts " Reading RTL Sources"
puts "=========================================================================="

# Read ALL files in a single read_hdl so `define macros propagate.
# -define XCELIUM: BSG_INV_PARAM gives default values (param = -1) which
# Genus 15.x requires for ANSI parameter ports (bare params not supported).
read_hdl -sv -define XCELIUM \
    ../00_src/bsg_mem/bsg_defines.sv \
    ../00_src/bsg_mem/bsg_dff.sv \
    ../00_src/bsg_mem/bsg_dff_en.sv \
    ../00_src/bsg_mem/bsg_dff_en_bypass.sv \
    ../00_src/bsg_mem/bsg_mem_1r1w_sync_synth.sv \
    ../00_src/bsg_mem/bsg_mem_1r1w_sync.sv \
    ../00_src/bsg_mem/cgra_config_mem_bsg.sv \
    ../00_src/cgra_pe.sv \
    ../00_src/cgra_router.sv \
    ../00_src/cgra_tile.sv \
    ../00_src/cgra_array.sv \
    ../00_src/cgra_tile_memory.sv \
    ../00_src/cgra_apb_csr.sv \
    ../00_src/cgra_control_unit.sv \
    ../00_src/cgra_dma_engine.sv \
    ../00_src/cgra_top.sv

# ==============================================================================
# Elaborate
# ==============================================================================
puts "=========================================================================="
puts " Elaborating Design: cgra_top"
puts "=========================================================================="

elaborate cgra_top
check_design -unresolved

# ==============================================================================
# Constraints
# ==============================================================================
puts "=========================================================================="
puts " Applying Constraints (100 MHz target with 3-stage PE pipeline)"
puts "=========================================================================="

# Clock: 100 MHz (10ns period) — enabled by 3rd PE pipeline stage
create_clock -name clk -period 10.0 [get_ports clk]

# Async reset — exclude from timing analysis
set_false_path -from [get_ports rst_n]

# I/O timing (relaxed)
set_input_delay  -clock clk -max 4.0 [remove_from_collection [all_inputs] [get_ports clk]]
set_output_delay -clock clk -max 4.0 [all_outputs]

# ==============================================================================
# Synthesis — Full 3-Stage Flow
# ==============================================================================
puts "=========================================================================="
puts " Stage 1/3: syn_generic (technology-independent optimization)"
puts "=========================================================================="
syn_generic

puts "=========================================================================="
puts " Stage 2/3: syn_map (technology mapping to gscl45nm)"
puts "=========================================================================="
syn_map

puts "=========================================================================="
puts " Stage 3/3: syn_opt (timing/area optimization)"
puts "=========================================================================="
syn_opt

# ==============================================================================
# Reports
# ==============================================================================
puts "=========================================================================="
puts " Generating Reports"
puts "=========================================================================="

report_timing > reports/timing.rpt
report_area   > reports/area.rpt
report_power  > reports/power.rpt
report_qor    > reports/qor.rpt

# Print key metrics to log
puts ""
puts "===== TIMING SUMMARY ====="
report_timing -unconstrained
puts ""
puts "===== AREA SUMMARY ====="
report_area
puts ""
puts "===== POWER SUMMARY ====="
report_power

# ==============================================================================
# Write Outputs
# ==============================================================================
puts "=========================================================================="
puts " Writing Outputs"
puts "=========================================================================="

# Gate-level netlist
write_hdl > syn_out/netlist.v

# Standard Delay Format
write_sdf > syn_out/delay.sdf

# Timing constraints
write_sdc > syn_out/cgra_top.sdc

# Genus database (for session restore)
write_db syn_out/cgra_syn.db

# ==============================================================================
# Done
# ==============================================================================
puts ""
puts "=========================================================================="
puts " Synthesis Complete"
puts "=========================================================================="
puts " Reports:  reports/timing.rpt  area.rpt  power.rpt  qor.rpt"
puts " Outputs:  syn_out/netlist.v   delay.sdf  cgra_top.sdc  cgra_syn.db"
puts "=========================================================================="

exit
