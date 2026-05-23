# =============================================================================
# report_power_impl.tcl — Generate Vivado power report from the routed design.
#
# Opens the impl_1 run of the project produced by create_synth_project.tcl +
# run_impl.tcl, runs report_power on the routed design, and writes the
# numeric breakdown to $VPROJ/impl_power.rpt.
#
# Usage:
#   CGRA_VPROJ=$HOME/vivado_projects/cgra_hdmi_synth_test \
#     /tools/Xilinx/2025.1/Vivado/bin/vivado -mode batch \
#       -source scripts/report_power_impl.tcl
# =============================================================================

proc _env_or_default {name def} {
    if {[info exists ::env($name)]} { return $::env($name) }
    return $def
}
set VPROJ_DIR [_env_or_default CGRA_VPROJ "$::env(HOME)/vivado_projects/cgra_hdmi_synth_test"]

set xpr [glob -nocomplain "$VPROJ_DIR/*.xpr"]
if {$xpr eq ""} {
    error "No .xpr at $VPROJ_DIR. Run create_synth_project.tcl + run_impl.tcl first."
}

set_param general.maxThreads 2
open_project [lindex $xpr 0]

set st [get_property STATUS [get_runs impl_1]]
if {![string match "*route_design Complete*" $st] && ![string match "*Complete*" $st]} {
    error "impl_1 not Complete (status: $st). Run run_impl.tcl first."
}

puts "==========================================================="
puts " POWER REPORT — opening routed impl_1"
puts "==========================================================="
open_run impl_1 -name impl_1

set rpt "$VPROJ_DIR/impl_power.rpt"
report_power -file $rpt
puts ""
puts " Power report written to: $rpt"
puts ""

# Brief stdout summary so the user sees the headline numbers
puts "==========================================================="
puts " HEADLINE (also at top of $rpt)"
puts "==========================================================="
report_power -no_propagation -no_header

close_project
