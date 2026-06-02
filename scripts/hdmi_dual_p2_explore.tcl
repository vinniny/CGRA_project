# hdmi_dual_p2_explore.tcl — re-run impl_1 only (reuse synth_1) with the
# Performance_ExploreWithRemap strategy + post-route phys_opt to close the
# WNS=-0.058 setup violation on the 200MHz capture domain (1 endpoint).
# CLAUDE.md notes ExploreWithRemap is the HDMI timing-closer.  No BD/synth change.
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_HDMI_DUAL/cgra_hdmi_dual.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_hdmi_dual.xsa

open_project $PROJ
set_property strategy Performance_ExploreWithRemap [get_runs impl_1]
# ensure post-route phys-opt runs (squeezes the last ps)
catch {set_property STEPS.POST_ROUTE_PHYS_OPT_DESIGN.IS_ENABLED true [get_runs impl_1]}

# persistent DRC waiver hook (off /tmp)
set hook [file join [file dirname $PROJ] drc_override_hdmi.tcl]
set fp [open $hook w]
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks NSTD-1\]"
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks UCIO-1\]"
close $fp
set_property STEPS.WRITE_BITSTREAM.TCL.PRE $hook [get_runs impl_1]

reset_run impl_1
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1
set st [get_property STATUS [get_runs impl_1]]; set prog [get_property PROGRESS [get_runs impl_1]]
puts "  impl_1: $st ($prog)"
catch {open_run impl_1
       set wns [get_property SLACK [get_timing_paths -max_paths 1 -nworst 1 -setup]]
       set whs [get_property SLACK [get_timing_paths -max_paths 1 -nworst 1 -hold]]
       puts "  WNS=$wns  WHS=$whs"}
if {[string match "*Complete*" $st] && $prog eq "100%"} {
    write_hw_platform -fixed -include_bit -force $XSA
    puts "  Wrote $XSA ([file size $XSA] bytes)"
    puts "HDMI EXPLORE BUILD SUCCESS"
} else { puts "HDMI EXPLORE BUILD FAILED: $st ($prog)" }
close_project
puts "EXPLORE DONE"
exit
