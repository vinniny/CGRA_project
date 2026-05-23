# =============================================================================
# run_impl.tcl — Launch impl_1 against an already-synthesized project.
#
# Use AFTER create_synth_project.tcl Stage B has completed. Opens the existing
# project, runs implementation (place + route) and write_bitstream. Produces
# the actual .bit file under <project>/cgra_hdmi_synth.runs/impl_1/.
#
# Resource cost on XC7Z020 @ 83% LUT util:
#   ~30-40 min total
#   ~5-6 GiB RAM peak during route
#   ~2-3 GiB additional disk under runs/impl_1/
#
# Usage:
#   CGRA_VPROJ=$HOME/vivado_projects/cgra_hdmi_synth_test \
#     /tools/Xilinx/2025.1/Vivado/bin/vivado -mode batch \
#       -source scripts/run_impl.tcl \
#       -log /tmp/cgra_impl.log -journal /tmp/cgra_impl.jou
#
# Output:
#   <VPROJ>/cgra_hdmi_synth.runs/impl_1/design_1_wrapper.bit
#   <VPROJ>/impl_util.rpt        (post-route utilization)
#   <VPROJ>/impl_timing.rpt      (worst-case slack)
#   <VPROJ>/impl_drc.rpt         (design rule check)
# =============================================================================

proc _env_or_default {name def} {
    if {[info exists ::env($name)]} { return $::env($name) }
    return $def
}
set VPROJ_DIR [_env_or_default CGRA_VPROJ "$::env(HOME)/vivado_projects/cgra_hdmi_synth_test"]

set xpr [glob -nocomplain "$VPROJ_DIR/*.xpr"]
if {$xpr eq ""} {
    error "No .xpr at $VPROJ_DIR. Run create_synth_project.tcl Stage B first."
}

puts "==========================================================="
puts " IMPL — opening $xpr"
puts "==========================================================="

set_param general.maxThreads 2
open_project [lindex $xpr 0]

# Ensure synth is up to date (no-op if already current).
if {[get_property STATUS [get_runs synth_1]] ne "synth_design Complete!"} {
    puts "  synth_1 not complete — launching it first."
    launch_runs synth_1 -jobs 2
    wait_on_run synth_1
}

# Launch impl through write_bitstream.
puts "\n=== launch_runs impl_1 -to_step write_bitstream -jobs 2 ==="
launch_runs impl_1 -to_step write_bitstream -jobs 2
wait_on_run impl_1

set st [get_property STATUS [get_runs impl_1]]
puts "\n=== impl_1 STATUS: $st ==="

if {[string match "*Complete*" $st] && ![string match "*ERROR*" $st]} {
    open_run impl_1 -name impl_1
    set util_rpt   "$VPROJ_DIR/impl_util.rpt"
    set timing_rpt "$VPROJ_DIR/impl_timing.rpt"
    set drc_rpt    "$VPROJ_DIR/impl_drc.rpt"

    report_utilization -file $util_rpt
    report_timing_summary -file $timing_rpt -warn_on_violation
    report_drc -file $drc_rpt

    puts ""
    puts "==========================================================="
    puts " IMPL COMPLETE"
    puts "==========================================================="
    puts "  Bitstream: $VPROJ_DIR/cgra_hdmi_synth.runs/impl_1/design_1_wrapper.bit"
    puts "  Util:      $util_rpt"
    puts "  Timing:    $timing_rpt"
    puts "  DRC:       $drc_rpt"
    puts ""

    # Quick stdout summary
    set wns [get_property SLACK [get_timing_paths -delay_type min_max -nworst 1]]
    puts "  Worst slack (WNS/min): $wns"
} else {
    error "impl_1 did NOT complete cleanly — inspect $VPROJ_DIR/cgra_hdmi_synth.runs/impl_1/runme.log"
}

close_project
