# =============================================================================
# build_vtpg_ila_bitstream.tcl — Orchestrator: base.tcl + v_tpg patch + System
# ILA patch, then synth + impl + bitstream + .ltx debug probes.
#
# Output:
#   $PROJECT_DIR/cgra_vtpg_ila.runs/impl_1/base_wrapper.bit
#   $PROJECT_DIR/cgra_vtpg_ila.runs/impl_1/debug_nets.ltx   (probes file)
#   $PROJECT_DIR/impl_*.rpt
#
# !!! IMPORTANT WORKFLOW NOTE (learned the hard way 2026-05-24) !!!
# After build, ALWAYS program this bitstream via XSDB (`make program ...`
# or `make run_elf ...`), NEVER via Vivado HW Manager's program_hw_devices.
# Vivado's PL programming does NOT run ps7_init, so the PS is left
# unclocked. The DAP then errors with AHB-AP transaction failure, the
# ARM cores disappear from the JTAG target list, and no bare-metal
# demos can run. Recovery requires a physical SRST press.
#
# The ILA capture flow is split in two steps:
#   1. shell: `make run_elf ELF=demo_vtpg.elf BIT=cgra_vtpg_ila.bit`
#      (XSDB programs PL, runs ps7_init, loads + starts ELF)
#   2. vivado batch: scripts/ila_capture_vtpg.tcl
#      (attaches to the already-programmed device, just reads ILA)
# =============================================================================
puts "==========================================================="
puts " V_TPG + SYSTEM ILA BITSTREAM BUILD (Vivado [version -short])"
puts "==========================================================="

proc _env_or_default {name def} {
    if {[info exists ::env($name)]} { return $::env($name) }
    return $def
}

set BASE_TCL     [_env_or_default CGRA_BASE_TCL    "/mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/base.tcl"]
set PYNQ_REPO    [_env_or_default CGRA_PYNQ_REPO   "/mnt/c/Users/thanh/Desktop/PYNQ_repo/boards/ip"]
set CGRA_IPREPO  [_env_or_default CGRA_CGRA_IPREPO "/mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/cgra_ip_repo"]
set PROJECT_DIR  [_env_or_default CGRA_ILA_VPROJ   "$::env(HOME)/vivado_projects/cgra_vtpg_ila"]
set REPO_ROOT    [file normalize [file dirname [info script]]/..]
set VTPG_PATCH   "$REPO_ROOT/scripts/add_v_tpg_test_pattern.tcl"
set ILA_PATCH    "$REPO_ROOT/scripts/add_system_ila_to_vtpg.tcl"

puts "  base.tcl    : $BASE_TCL"
puts "  v_tpg patch : $VTPG_PATCH"
puts "  ILA patch   : $ILA_PATCH"
puts "  project     : $PROJECT_DIR"

foreach req [list $BASE_TCL $PYNQ_REPO $CGRA_IPREPO $VTPG_PATCH $ILA_PATCH] {
    if {![file exists $req]} { error "Missing: $req" }
}

set_param general.maxThreads 2

# 1. Create project
puts "\n=== 1. Create project ==="
file delete -force $PROJECT_DIR
file mkdir $PROJECT_DIR
create_project -force cgra_vtpg_ila $PROJECT_DIR -part xc7z020clg400-1
set_property target_language Verilog [current_project]

# 2. IP repos
puts "\n=== 2. IP repository paths ==="
set_property ip_repo_paths [list $PYNQ_REPO $CGRA_IPREPO] [current_project]
update_ip_catalog

# 3. Source patched base.tcl
puts "\n=== 3. Source base.tcl (patched) ==="
set overlay_name "base"
set tmp_base "$PROJECT_DIR/base_patched.tcl"
set fp [open $BASE_TCL r]; set src [read $fp]; close $fp
regsub -all {set scripts_vivado_version 2024.1} $src \
    "set scripts_vivado_version 2025.1" src
regsub -all {\$\{overlay_name\}} $src "base" src
set fp [open $tmp_base w]; puts $fp $src; close $fp
source $tmp_base

set bd_name "base"
set bd_files [get_files -quiet ${bd_name}.bd]
if {[llength $bd_files] == 0} { error "BD ${bd_name}.bd not found" }
open_bd_design [lindex $bd_files 0]

# 4. Apply v_tpg patch
puts "\n=== 4. Source add_v_tpg_test_pattern.tcl ==="
source $VTPG_PATCH

# 5. Apply ILA patch
puts "\n=== 5. Source add_system_ila_to_vtpg.tcl ==="
source $ILA_PATCH

# 6. Wrapper + constraints
puts "\n=== 6. Wrapper + constraints ==="
make_wrapper -files [get_files ${bd_name}.bd] -top -import
set_property top ${bd_name}_wrapper [current_fileset]
set xdc_candidates [list \
    {/mnt/c/Users/thanh/Desktop/PYNQ_repo/boards/Pynq-Z2/base/vivado/constraints/base.xdc} \
    "$REPO_ROOT/01_bench/constrs_pynq_z2.xdc"]
foreach xdc $xdc_candidates {
    if {[file exists $xdc]} {
        add_files -fileset constrs_1 -norecurse $xdc
        puts "  added: $xdc"
        break
    }
}
update_compile_order -fileset sources_1

# 7. Synth
puts "\n=== 7. launch_runs synth_1 -jobs 2 ==="
launch_runs synth_1 -jobs 2
wait_on_run synth_1
set st [get_property STATUS [get_runs synth_1]]
puts "  synth_1: $st"
if {![string match "*Complete*" $st] || [string match "*ERROR*" $st]} {
    error "Synth failed — see $PROJECT_DIR/cgra_vtpg_ila.runs/synth_1/runme.log"
}
open_run synth_1 -name synth_1
report_utilization -file $PROJECT_DIR/synth_util.rpt
close_design

# 8. Impl + bitstream + debug probes
puts "\n=== 8. launch_runs impl_1 -to_step write_bitstream -jobs 2 ==="
launch_runs impl_1 -to_step write_bitstream -jobs 2
wait_on_run impl_1
set st [get_property STATUS [get_runs impl_1]]
puts "  impl_1: $st"
if {![string match "*Complete*" $st]} {
    error "Impl failed — see $PROJECT_DIR/cgra_vtpg_ila.runs/impl_1/runme.log"
}

open_run impl_1 -name impl_1
report_utilization    -file $PROJECT_DIR/impl_util.rpt
report_timing_summary -file $PROJECT_DIR/impl_timing.rpt -warn_on_violation
report_drc            -file $PROJECT_DIR/impl_drc.rpt

# Explicitly write the .ltx debug probes file so the HW Manager can
# auto-decode the ILA samples.
write_debug_probes -force $PROJECT_DIR/cgra_vtpg_ila.runs/impl_1/debug_nets.ltx

set wns [get_property SLACK [get_timing_paths -delay_type max -nworst 1]]
set whs [get_property SLACK [get_timing_paths -delay_type min -nworst 1]]
puts ""
puts "==========================================================="
puts " V_TPG + ILA BITSTREAM BUILD COMPLETE"
puts "==========================================================="
puts " Bitstream  : $PROJECT_DIR/cgra_vtpg_ila.runs/impl_1/${bd_name}_wrapper.bit"
puts " Probes     : $PROJECT_DIR/cgra_vtpg_ila.runs/impl_1/debug_nets.ltx"
puts " WNS        : $wns"
puts " WHS        : $whs"
puts " Util       : $PROJECT_DIR/impl_util.rpt"
puts " Timing     : $PROJECT_DIR/impl_timing.rpt"
puts ""
puts " Stage:"
puts "   cp $PROJECT_DIR/cgra_vtpg_ila.runs/impl_1/${bd_name}_wrapper.bit \\"
puts "      bitstreams/cgra_vtpg_ila.bit"
puts "   cp $PROJECT_DIR/cgra_vtpg_ila.runs/impl_1/debug_nets.ltx \\"
puts "      bitstreams/cgra_vtpg_ila.ltx"
puts "==========================================================="
