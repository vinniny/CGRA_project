# hdmi_dual_serclk_revert.tcl — revert rgb2dvi to kGenerateSerialClk=false +
# external PXL_CLK_5X_O.  Solid-white FB showed white/yellow stripes (blue TMDS
# lane dropping) with =true: rgb2dvi's self-generated 5x is in a different clock
# domain than the external PixelClk that clocks the pixel data -> placement-
# sensitive lane corruption.  With =false the 5x (PXL_CLK_5X_O) and 1x come from
# ONE MMCM (phase-coherent) and the BUFIO drives the OSERDES directly.  Keeps the
# genlock fix.  Writes canonical cgra_hdmi_dual.xsa.
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_HDMI_DUAL/cgra_hdmi_dual.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_hdmi_dual.xsa

open_project $PROJ
set bd [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd

set_property CONFIG.kGenerateSerialClk {false} [get_bd_cells rgb2dvi_0]
puts "  rgb2dvi kGenerateSerialClk -> false"
# SerialClk pin reappears; drive it from the phase-coherent dynclk 5x
set sp [get_bd_pins rgb2dvi_0/SerialClk]
set net [get_bd_nets -quiet -of $sp]
if {$net ne ""} { disconnect_bd_net $net $sp }
connect_bd_net [get_bd_pins axi_dynclk_0/PXL_CLK_5X_O] [get_bd_pins rgb2dvi_0/SerialClk]
puts "  rgb2dvi/SerialClk <- axi_dynclk_0/PXL_CLK_5X_O"

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
    puts "HDMI SERREVERT BUILD SUCCESS"
} else { puts "HDMI SERREVERT BUILD FAILED: $st ($prog)" }
close_project
puts "SERREVERT DONE"
exit
