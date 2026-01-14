# ==============================================================================
# Genus Synthesis Script for CGRA Project
# ==============================================================================
# Usage: genus -batch -files genus_syn.tcl -log genus.log
# ==============================================================================

# ==============================================================================
# Setup
# ==============================================================================
set_db init_lib_search_path "../00_src ../00_src/bsg_mem"
set_db hdl_search_path "../00_src ../00_src/bsg_mem"

# Technology library (update for your target)
# For academic/evaluation: use generic library
# set_db library {slow.lib fast.lib}

# ==============================================================================
# Read RTL
# ==============================================================================
puts "=========================================================================="
puts " Reading RTL Sources"
puts "=========================================================================="

# BSG Memory Library
read_hdl -sv ../00_src/bsg_mem/bsg_defines.sv
read_hdl -sv ../00_src/bsg_mem/bsg_dff.sv
read_hdl -sv ../00_src/bsg_mem/bsg_dff_en_bypass.sv
read_hdl -sv ../00_src/bsg_mem/bsg_mem_1r1w_sync_synth.sv
read_hdl -sv ../00_src/bsg_mem/bsg_mem_1r1w_sync.sv
read_hdl -sv ../00_src/bsg_mem/cgra_config_mem_bsg.sv

# RTL Source Files
read_hdl -sv ../00_src/cgra_pe.sv
read_hdl -sv ../00_src/cgra_router.sv
read_hdl -sv ../00_src/cgra_tile.sv
read_hdl -sv ../00_src/cgra_array_4x4.sv
read_hdl -sv ../00_src/cgra_tile_memory.sv
read_hdl -sv ../00_src/cgra_apb_csr.sv
read_hdl -sv ../00_src/cgra_control_unit.sv
read_hdl -sv ../00_src/cgra_dma_engine.sv
read_hdl -sv ../00_src/cgra_top.sv

# ==============================================================================
# Elaborate
# ==============================================================================
puts "=========================================================================="
puts " Elaborating Design: cgra_top"
puts "=========================================================================="

elaborate cgra_top

# Check for issues
check_design -unresolved

# ==============================================================================
# Constraints
# ==============================================================================
puts "=========================================================================="
puts " Applying Constraints"
puts "=========================================================================="

# Clock: 100 MHz (10ns period)
create_clock -name clk -period 10 [get_ports clk]

# Reset is async, create false path
set_false_path -from [get_ports rst_n]

# Input/Output delays
set_input_delay -clock clk -max 2.0 [all_inputs]
set_output_delay -clock clk -max 2.0 [all_outputs]

# Area optimization
set_db design:cgra_top .max_fanout 32

# ==============================================================================
# Synthesis
# ==============================================================================
puts "=========================================================================="
puts " Running Synthesis"
puts "=========================================================================="

# Generic synthesis (no library)
syn_generic

# Mapping (requires library)
# syn_map

# Optimization
# syn_opt

# ==============================================================================
# Reports
# ==============================================================================
puts "=========================================================================="
puts " Generating Reports"
puts "=========================================================================="

report_timing > timing_report.txt
report_area > area_report.txt
report_power > power_report.txt
report_qor > qor_report.txt

# ==============================================================================
# Write Outputs
# ==============================================================================
puts "=========================================================================="
puts " Writing Outputs"
puts "=========================================================================="

# Write synthesized netlist
write_hdl > cgra_top_syn.v

# Write constraints
write_sdc > cgra_top.sdc

# Save session for restore
write_db cgra_syn.db

puts "=========================================================================="
puts " Synthesis Complete"
puts "=========================================================================="
puts " Outputs:"
puts "   cgra_top_syn.v  - Synthesized netlist"
puts "   cgra_top.sdc    - Timing constraints"
puts "   cgra_syn.db     - Genus database (for restore)"
puts "   timing_report.txt, area_report.txt, power_report.txt"
puts "=========================================================================="

# Exit (comment out for GUI mode)
# exit
