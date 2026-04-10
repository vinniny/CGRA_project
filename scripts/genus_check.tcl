# ==============================================================================
# Genus RTL Synthesizability Check (make hal)
# ==============================================================================
# Runs check_design -unresolved in batch mode to flag inferred latches,
# combinational loops, multi-driven nets, and unsynthesizable constructs.
# No PDK library required — library-free elaboration only.
# Usage: genus -batch -files scripts/genus_check.tcl -log 02_log/hal.log
# ==============================================================================

file mkdir reports

# ------------------------------------------------------------------------------
# Read RTL — no PDK library needed for check_design
# ------------------------------------------------------------------------------
puts "=========================================================================="
puts " \[HAL\] Reading RTL Sources (BSG + CGRA)"
puts "=========================================================================="

set LIB_DIR "/opt/PDKs/FreePDK45/osu_soc/lib/files"
set_db init_lib_search_path  "$LIB_DIR ../00_src ../00_src/bsg_mem"
set_db init_hdl_search_path  "../00_src ../00_src/bsg_mem"
set_db library                "$LIB_DIR/gscl45nm.lib"

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

# ------------------------------------------------------------------------------
# Elaborate
# ------------------------------------------------------------------------------
puts "=========================================================================="
puts " \[HAL\] Elaborating cgra_top"
puts "=========================================================================="

set elab_status [catch {elaborate cgra_top} elab_msg]
if {$elab_status != 0} {
    puts "ERROR: Elaboration failed: $elab_msg"
    puts "Check reports/check_design.rpt for details."
    exit 1
}

# ------------------------------------------------------------------------------
# check_design — synthesizability rules
# ------------------------------------------------------------------------------
puts "=========================================================================="
puts " \[HAL\] Running check_design"
puts "=========================================================================="

check_design -unresolved > reports/check_design.rpt
check_design -all       >> reports/check_design.rpt

# ------------------------------------------------------------------------------
# Summary report
# ------------------------------------------------------------------------------
puts "=========================================================================="
puts " \[HAL\] Design Status Summary"
puts "=========================================================================="
report_design_status

puts ""
puts "\[HAL\] Full report: reports/check_design.rpt"
puts "\[HAL\] Genus log:   02_log/hal.log"

exit 0
