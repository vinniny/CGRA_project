# ==============================================================================
# Conformal LEC Script for CGRA Project
# ==============================================================================
# Usage: lec -nogui -dofile conformal_lec.tcl -logfile lec.log
# ==============================================================================

# ==============================================================================
# Setup
# ==============================================================================
vpxmode

# Set LEC effort level
set compare_effort Auto

# ==============================================================================
# Read Golden (RTL) Design
# ==============================================================================
puts "=========================================================================="
puts " Reading Golden (RTL) Design"
puts "=========================================================================="

read design -golden -sv \
    ../00_src/bsg_mem/bsg_defines.sv \
    ../00_src/bsg_mem/bsg_dff.sv \
    ../00_src/bsg_mem/bsg_dff_en_bypass.sv \
    ../00_src/bsg_mem/bsg_mem_1r1w_sync_synth.sv \
    ../00_src/bsg_mem/bsg_mem_1r1w_sync.sv \
    ../00_src/bsg_mem/cgra_config_mem_bsg.sv \
    ../00_src/cgra_pe.sv \
    ../00_src/cgra_router.sv \
    ../00_src/cgra_tile.sv \
    ../00_src/cgra_array_4x4.sv \
    ../00_src/cgra_tile_memory.sv \
    ../00_src/cgra_apb_csr.sv \
    ../00_src/cgra_control_unit.sv \
    ../00_src/cgra_dma_engine.sv \
    ../00_src/cgra_top.sv

set root module cgra_top -golden

# ==============================================================================
# Read Revised (Synthesized) Design
# ==============================================================================
puts "=========================================================================="
puts " Reading Revised (Synthesized) Design"
puts "=========================================================================="

read design -revised ../04_syn/cgra_top_syn.v

set root module cgra_top -revised

# ==============================================================================
# Setup Compare Points
# ==============================================================================
puts "=========================================================================="
puts " Setting Up Compare Points"
puts "=========================================================================="

# Map key points
set flatten model -golden
set flatten model -revised

set mapping method -noname

# ==============================================================================
# Add Constraints
# ==============================================================================
# Handle async reset
add notranslate module -both *async*

# ==============================================================================
# Run Comparison
# ==============================================================================
puts "=========================================================================="
puts " Running Equivalence Check"
puts "=========================================================================="

add compare point -all

compare

# ==============================================================================
# Report Results
# ==============================================================================
puts "=========================================================================="
puts " LEC Results"
puts "=========================================================================="

report compare data > lec_compare_data.txt
report unmapped point > lec_unmapped.txt
report nonequivalent point > lec_noneq.txt

# Summary
diagnose

# ==============================================================================
# Exit
# ==============================================================================
puts "=========================================================================="
puts " LEC Complete - See reports:"
puts "   lec_compare_data.txt"
puts "   lec_unmapped.txt"
puts "   lec_noneq.txt"
puts "=========================================================================="

# exit (comment for GUI)
