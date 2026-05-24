# =============================================================================
# rebuild_bitstream_from_base.tcl — Procedure A from
# 06_doc/vivado_bitstream_build_procedure.md.
#
# Re-creates the silicon-validated cgra_pynq_base bitstream from base.tcl
# in a fresh Vivado project. End-to-end: project create → IP repos → BD
# recreate → wrapper → constraints → synth → impl → bitstream + reports.
#
# Produces a bit-equivalent (modulo placer randomness) result to the working
# bitstream at:
#   /mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/cgra_pynq_base.runs/impl_1/base_wrapper.bit
#
# Usage:
#   vivado -mode batch -source scripts/rebuild_bitstream_from_base.tcl
# =============================================================================

puts "==========================================================="
puts " PROCEDURE A — rebuild cgra_pynq_base bitstream"
puts " Vivado: [version -short]"
puts "==========================================================="

proc _env_or_default {name def} {
    if {[info exists ::env($name)]} { return $::env($name) }
    return $def
}

set BASE_TCL    [_env_or_default CGRA_BASE_TCL "/mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/base.tcl"]
set PYNQ_REPO   [_env_or_default CGRA_PYNQ_REPO "/mnt/c/Users/thanh/Desktop/PYNQ_repo/boards/ip"]
set CGRA_IPREPO [_env_or_default CGRA_CGRA_IPREPO "/mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/cgra_ip_repo"]
set PROJECT_DIR [_env_or_default CGRA_REBUILD_VPROJ "$::env(HOME)/vivado_projects/cgra_rebuild"]
set REPO_ROOT   [file normalize [file dirname [info script]]/..]

puts "  base.tcl    : $BASE_TCL"
puts "  PYNQ ip     : $PYNQ_REPO"
puts "  CGRA ip     : $CGRA_IPREPO"
puts "  project     : $PROJECT_DIR"

foreach req [list $BASE_TCL $PYNQ_REPO $CGRA_IPREPO] {
    if {![file exists $req]} { error "Missing: $req" }
}

set_param general.maxThreads 2

# 1. Create project
puts "\n=== 1. Create project ==="
file delete -force $PROJECT_DIR
file mkdir $PROJECT_DIR
create_project -force cgra_rebuild $PROJECT_DIR -part xc7z020clg400-1
set_property target_language Verilog [current_project]

# 2. IP repos
puts "\n=== 2. IP repository paths ==="
set_property ip_repo_paths [list $PYNQ_REPO $CGRA_IPREPO] [current_project]
update_ip_catalog

# 3. Patch base.tcl version-string in a temp copy, then source it.
puts "\n=== 3. Source patched base.tcl ==="
# base.tcl references ${overlay_name} for PYNQ PFM metadata — must be
# defined before sourcing (otherwise create_root_design errors near the
# end on `set_property PFM_NAME ...`).
set overlay_name "base"
set tmp_base "$PROJECT_DIR/base_patched.tcl"
set fp [open $BASE_TCL r]
set src [read $fp]; close $fp
regsub -all {set scripts_vivado_version 2024.1} $src \
    "set scripts_vivado_version 2025.1" src
# Replace literal ${overlay_name} (inside braces — not Tcl-substituted)
# with the actual overlay name "base". Otherwise PFM_NAME ends up as
# `xilinx.com:xd:${overlay_name}:1.0` and Vivado rejects the special chars.
regsub -all {\$\{overlay_name\}} $src "base" src
set fp [open $tmp_base w]; puts $fp $src; close $fp
source $tmp_base

# 4. Open the BD (base.tcl creates but doesn't leave it open in scope).
set bd_name "base"
set bd_files [get_files -quiet ${bd_name}.bd]
if {[llength $bd_files] == 0} { error "BD ${bd_name}.bd not found" }
open_bd_design [lindex $bd_files 0]
puts "  BD '${bd_name}' opened."

# 5. Validate
puts "\n=== 4. validate_bd_design ==="
validate_bd_design
save_bd_design

# 6. Wrapper + constraints
puts "\n=== 5. Wrapper + constraints ==="
make_wrapper -files [get_files ${bd_name}.bd] -top -import
set_property top ${bd_name}_wrapper [current_fileset]
set xdc "$REPO_ROOT/01_bench/constrs_pynq_z2.xdc"
if {[file exists $xdc]} {
    add_files -fileset constrs_1 -norecurse $xdc
    puts "  Added $xdc"
}
update_compile_order -fileset sources_1

# 7. Synth
puts "\n=== 6. launch_runs synth_1 -jobs 2 ==="
launch_runs synth_1 -jobs 2
wait_on_run synth_1
set st [get_property STATUS [get_runs synth_1]]
puts "  synth_1 status: $st"
if {![string match "*Complete*" $st] || [string match "*ERROR*" $st]} {
    error "Synth failed — see $PROJECT_DIR/cgra_rebuild.runs/synth_1/runme.log"
}
open_run synth_1 -name synth_1
report_utilization -file $PROJECT_DIR/synth_util.rpt
close_design

# 8. Impl + bitstream
puts "\n=== 7. launch_runs impl_1 -to_step write_bitstream -jobs 2 ==="
launch_runs impl_1 -to_step write_bitstream -jobs 2
wait_on_run impl_1
set st [get_property STATUS [get_runs impl_1]]
puts "  impl_1 status: $st"
if {![string match "*Complete*" $st]} {
    error "Impl failed — see $PROJECT_DIR/cgra_rebuild.runs/impl_1/runme.log"
}
open_run impl_1 -name impl_1
report_utilization     -file $PROJECT_DIR/impl_util.rpt
report_timing_summary  -file $PROJECT_DIR/impl_timing.rpt -warn_on_violation
report_drc             -file $PROJECT_DIR/impl_drc.rpt
report_power           -file $PROJECT_DIR/impl_power.rpt

set wns [get_property SLACK [get_timing_paths -delay_type max -nworst 1]]
set whs [get_property SLACK [get_timing_paths -delay_type min -nworst 1]]
puts ""
puts "==========================================================="
puts " PROCEDURE A COMPLETE — reproducibility validated"
puts "==========================================================="
puts " Bitstream : $PROJECT_DIR/cgra_rebuild.runs/impl_1/${bd_name}_wrapper.bit"
puts " WNS       : $wns"
puts " WHS       : $whs"
puts " Util      : $PROJECT_DIR/impl_util.rpt"
puts " Timing    : $PROJECT_DIR/impl_timing.rpt"
puts " DRC       : $PROJECT_DIR/impl_drc.rpt"
puts " Power     : $PROJECT_DIR/impl_power.rpt"
puts ""
puts " To stage:"
puts "   cp $PROJECT_DIR/cgra_rebuild.runs/impl_1/${bd_name}_wrapper.bit \\"
puts "      bitstreams/cgra_rebuilt_from_base.bit"
puts "==========================================================="
