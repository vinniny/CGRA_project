# =============================================================================
# build_split_vdma_bitstream.tcl — base.tcl + separate HDMI-IN VDMA patch,
# then synth + impl + bitstream + .xsa.
# =============================================================================
puts "==========================================================="
puts " SPLIT-VDMA BITSTREAM BUILD (Vivado [version -short])"
puts "==========================================================="

proc _env_or_default {name def} {
    if {[info exists ::env($name)]} { return $::env($name) }
    return $def
}

set BASE_TCL     [_env_or_default CGRA_BASE_TCL "/mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/base.tcl"]
set PYNQ_REPO    [_env_or_default CGRA_PYNQ_REPO "/mnt/c/Users/thanh/Desktop/PYNQ_repo/boards/ip"]
set CGRA_IPREPO  [_env_or_default CGRA_CGRA_IPREPO "/mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/cgra_ip_repo"]
set PROJECT_DIR  [_env_or_default CGRA_SPLIT_VPROJ "$::env(HOME)/vivado_projects/cgra_split_vdma"]
set REPO_ROOT    [file normalize [file dirname [info script]]/..]
set PATCH        "$REPO_ROOT/scripts/add_separate_hdmi_in_vdma.tcl"

foreach req [list $BASE_TCL $PYNQ_REPO $CGRA_IPREPO $PATCH] {
    if {![file exists $req]} { error "Missing: $req" }
}

set_param general.maxThreads 2

# 1. Create project
puts "\n=== 1. Create project ==="
file delete -force $PROJECT_DIR
file mkdir $PROJECT_DIR
create_project -force cgra_split_vdma $PROJECT_DIR -part xc7z020clg400-1
set_property target_language Verilog [current_project]
set_property ip_repo_paths [list $PYNQ_REPO $CGRA_IPREPO] [current_project]
update_ip_catalog

# 2. Source patched base.tcl
puts "\n=== 2. Source patched base.tcl ==="
set overlay_name "base"
set tmp_base "$PROJECT_DIR/base_patched.tcl"
set fp [open $BASE_TCL r]; set src [read $fp]; close $fp
regsub -all {set scripts_vivado_version 2024.1} $src \
    "set scripts_vivado_version 2025.1" src
regsub -all {\$\{overlay_name\}} $src "base" src
set fp [open $tmp_base w]; puts $fp $src; close $fp
source $tmp_base

set bd_name "base"
open_bd_design [lindex [get_files ${bd_name}.bd] 0]

# 3. Apply VDMA-split patch
puts "\n=== 3. Apply add_separate_hdmi_in_vdma.tcl ==="
source $PATCH

# 4. Wrapper + constraints
puts "\n=== 4. Wrapper + constraints ==="
make_wrapper -files [get_files ${bd_name}.bd] -top -import
set_property top ${bd_name}_wrapper [current_fileset]
set xdc {/mnt/c/Users/thanh/Desktop/PYNQ_repo/boards/Pynq-Z2/base/vivado/constraints/base.xdc}
if {![file exists $xdc]} {
    set xdc "$REPO_ROOT/01_bench/constrs_pynq_z2.xdc"
}
add_files -fileset constrs_1 -norecurse $xdc
update_compile_order -fileset sources_1

# 5. Synth
puts "\n=== 5. launch_runs synth_1 -jobs 2 ==="
launch_runs synth_1 -jobs 2
wait_on_run synth_1
set st [get_property STATUS [get_runs synth_1]]
if {![string match "*Complete*" $st] || [string match "*ERROR*" $st]} {
    error "Synth failed — $PROJECT_DIR/cgra_split_vdma.runs/synth_1/runme.log"
}
open_run synth_1 -name synth_1
report_utilization -file $PROJECT_DIR/synth_util.rpt
close_design

# 6. Impl + bitstream
puts "\n=== 6. launch_runs impl_1 -to_step write_bitstream -jobs 2 ==="
launch_runs impl_1 -to_step write_bitstream -jobs 2
wait_on_run impl_1
set st [get_property STATUS [get_runs impl_1]]
if {![string match "*Complete*" $st]} {
    error "Impl failed — $PROJECT_DIR/cgra_split_vdma.runs/impl_1/runme.log"
}
open_run impl_1 -name impl_1
report_utilization    -file $PROJECT_DIR/impl_util.rpt
report_timing_summary -file $PROJECT_DIR/impl_timing.rpt -warn_on_violation
report_drc            -file $PROJECT_DIR/impl_drc.rpt

# 7. Export .xsa
set XSA "$PROJECT_DIR/cgra_split_vdma.runs/impl_1/${bd_name}_wrapper.xsa"
catch {write_hw_platform -fixed -include_bit -force -file $XSA}

set wns [get_property SLACK [get_timing_paths -delay_type max -nworst 1]]
set whs [get_property SLACK [get_timing_paths -delay_type min -nworst 1]]
puts ""
puts "==========================================================="
puts " SPLIT-VDMA BITSTREAM BUILD COMPLETE"
puts "==========================================================="
puts " Bitstream : $PROJECT_DIR/cgra_split_vdma.runs/impl_1/${bd_name}_wrapper.bit"
puts " XSA       : $XSA"
puts " WNS       : $wns"
puts " WHS       : $whs"
puts ""
puts " Stage:"
puts "   cp $PROJECT_DIR/cgra_split_vdma.runs/impl_1/${bd_name}_wrapper.bit \\"
puts "      bitstreams/cgra_split_vdma.bit"
puts "==========================================================="
