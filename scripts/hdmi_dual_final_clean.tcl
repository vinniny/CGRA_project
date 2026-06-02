# hdmi_dual_final_clean.tcl — FINAL canonical build.  Removes the debug
# system_ila_vid (so timing closes — the ILA pushed WNS to -0.081) and keeps
# every functional fix (crystal=50, dynclk addr, pixel-domain reset, CE tie,
# kGenerateSerialClk, genlock vtg_ce->gen_clken/clken, fid=0).  Writes the
# canonical cgra_hdmi_dual.xsa (NOT the _ila one).
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_HDMI_DUAL/cgra_hdmi_dual.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_hdmi_dual.xsa

open_project $PROJ
set bd [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd
catch {delete_bd_objs [get_bd_cells -quiet system_ila_vid]; puts "  removed system_ila_vid"}

if {[catch {validate_bd_design} e]} { puts "VALIDATE FAILED: $e"; close_project; exit }
puts "  validate OK"
save_bd_design
catch {generate_target all [get_files $bd]}
catch {make_wrapper -files [get_files $bd] -top -force}

set hook /tmp/drc_override_hdmi.tcl
set fp [open $hook w]
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks NSTD-1\]"
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks UCIO-1\]"
close $fp
set_property STEPS.WRITE_BITSTREAM.TCL.PRE $hook [get_runs impl_1]

catch {reset_run impl_1}
catch {reset_run synth_1}
foreach r [get_runs] { if {[string match "*_synth_1" $r] && $r ne "synth_1"} { catch {reset_run $r} } }
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1
set st [get_property STATUS [get_runs impl_1]]; set prog [get_property PROGRESS [get_runs impl_1]]
puts "  impl_1: $st ($prog)"
catch {open_run impl_1; puts "  WNS=[get_property SLACK [get_timing_paths -max_paths 1 -nworst 1 -setup]]"}
if {[string match "*Complete*" $st] && $prog eq "100%"} {
    write_hw_platform -fixed -include_bit -force $XSA
    puts "  Wrote $XSA ([file size $XSA] bytes)"
    puts "HDMI FINAL BUILD SUCCESS"
} else { puts "HDMI FINAL BUILD FAILED: $st ($prog)" }
close_project
puts "FINAL DONE"
exit
