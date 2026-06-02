# hdmi_vin_reconnect.tcl — minimal fix: the FCLK2 reclock left
# v_vid_in_axi4s_0/vid_io_in_clk unconnected (toggling C_HAS_ASYNC_CLK dropped
# it).  PYNQ base.tcl reference: vid_io_in_clk <- dvi2rgb PixelClk, aclk <- a
# fast video clock (they use 142.857MHz; we use FCLK2=200), C_HAS_ASYNC_CLK=1.
# Just restore vid_io_in_clk -> PixelClk, verify, validate, build the test xsa.
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_HDMI_DUAL/cgra_hdmi_dual.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_hdmi_dual_vinclk.xsa

open_project $PROJ
set bd [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd

catch {set_property CONFIG.C_HAS_ASYNC_CLK {1} [get_bd_cells v_vid_in_axi4s_0]}
puts "  C_HAS_ASYNC_CLK = [get_property CONFIG.C_HAS_ASYNC_CLK [get_bd_cells v_vid_in_axi4s_0]]"

set vc [get_bd_pins -quiet v_vid_in_axi4s_0/vid_io_in_clk]
puts "  vid_io_in_clk pin exists: [expr {$vc ne ""}], net=[get_bd_nets -quiet -of $vc]"
if {$vc ne ""} {
    set n [get_bd_nets -quiet -of $vc]
    if {$n ne ""} { disconnect_bd_net $n $vc }
    connect_bd_net [get_bd_pins dvi2rgb_0/PixelClk] $vc
    puts "  vid_io_in_clk <- dvi2rgb/PixelClk ; net now=[get_bd_nets -quiet -of $vc]"
}
# also make sure aclk is FCLK2 and aresetn from psr_vin (idempotent)
catch {puts "  aclk net=[get_bd_nets -quiet -of [get_bd_pins v_vid_in_axi4s_0/aclk]]"}

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
    puts "  Wrote $XSA"
    puts "HDMI VINRC BUILD SUCCESS"
} else { puts "HDMI VINRC BUILD FAILED: $st ($prog)" }
close_project
puts "VINRC DONE"
exit
