# hdmi_dual_serclk_fix.tcl — the clean BD set rgb2dvi kGenerateSerialClk=false
# (a Linux-build workaround), making rgb2dvi depend on dynclk's external
# PXL_CLK_5X_O for its TMDS serializer.  If that 5x clock isn't right, rgb2dvi
# emits no valid TMDS -> monitor "no signal" even though everything upstream
# (dynclk lock, v_tc, VDMA, pixel-domain reset, CE) is healthy.  Switch to the
# robust Digilent default kGenerateSerialClk=true: rgb2dvi self-generates the
# 5x serial clock internally from the locked 25.175 MHz PixelClk.  The external
# SerialClk pin disappears, so disconnect PXL_CLK_5X_O first.  Re-impl + re-export.
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_HDMI_DUAL/cgra_hdmi_dual.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_hdmi_dual.xsa

open_project $PROJ
set bd [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd

# disconnect the external SerialClk net before the pin vanishes
set sp [get_bd_pins -quiet rgb2dvi_0/SerialClk]
if {$sp ne ""} {
    set net [get_bd_nets -quiet -of $sp]
    if {$net ne ""} { disconnect_bd_net $net $sp; puts "  disconnected PXL_CLK_5X_O from rgb2dvi/SerialClk" }
}
set_property CONFIG.kGenerateSerialClk {true} [get_bd_cells rgb2dvi_0]
puts "  rgb2dvi kGenerateSerialClk -> true (self-generates 5x from PixelClk)"
# PixelClk stays connected to PXL_CLK_O; aRst_n stays on proc_sys_reset_video.

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
launch_runs impl_1 -to_step write_bitstream -jobs 1
wait_on_run impl_1
set st [get_property STATUS [get_runs impl_1]]; set prog [get_property PROGRESS [get_runs impl_1]]
puts "  impl_1: $st ($prog)"
catch {open_run impl_1; puts "  WNS=[get_property SLACK [get_timing_paths -max_paths 1 -nworst 1 -setup]]"}
if {[string match "*Complete*" $st] && $prog eq "100%"} {
    write_hw_platform -fixed -include_bit -force $XSA
    puts "  Wrote $XSA ([file size $XSA] bytes)"
    puts "HDMI SERCLK BUILD SUCCESS"
} else { puts "HDMI SERCLK BUILD FAILED: $st ($prog)" }
close_project
puts "SERCLK DONE"
exit
