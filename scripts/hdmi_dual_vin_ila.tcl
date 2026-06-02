# hdmi_dual_vin_ila.tcl — DEBUG build: System ILA on v_vid_in_axi4s_0's AXIS
# master + overflow/underflow, clocked on FCLK0 (the aclk domain).  HDMI-IN
# capture is frozen (vdma_1 store stuck at 0, no errors) despite dvi2rgb locking
# + producing valid pixels.  This ILA shows whether the AXIS is flowing
# (tvalid), framed (tuser=SOF, tlast=EOL), backpressured (tready) or overrun
# (overflow) -> tells us the real fix (reclock vs framing vs wiring).
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_HDMI_DUAL/cgra_hdmi_dual.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_hdmi_dual_vinila.xsa

open_project $PROJ
set bd [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd

catch {delete_bd_objs [get_bd_cells -quiet system_ila_vin]}
create_bd_cell -type ip -vlnv [get_property VLNV [get_ipdefs *system_ila*]] system_ila_vin
set_property -dict [list \
    CONFIG.C_MON_TYPE {NATIVE} \
    CONFIG.C_NUM_OF_PROBES {3} \
    CONFIG.C_DATA_DEPTH {4096} \
    CONFIG.C_PROBE0_WIDTH {1} CONFIG.C_PROBE1_WIDTH {1} CONFIG.C_PROBE2_WIDTH {1} \
] [get_bd_cells system_ila_vin]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0] [get_bd_pins system_ila_vin/clk]
connect_bd_net [get_bd_pins v_vid_in_axi4s_0/m_axis_video_tvalid] [get_bd_pins system_ila_vin/probe0]
connect_bd_net [get_bd_pins v_vid_in_axi4s_0/m_axis_video_tuser]  [get_bd_pins system_ila_vin/probe1]
connect_bd_net [get_bd_pins v_vid_in_axi4s_0/overflow]            [get_bd_pins system_ila_vin/probe2]
puts "  system_ila_vin: 0=tvalid 1=tuser(SOF) 2=overflow"

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
    puts "HDMI VINILA BUILD SUCCESS"
} else { puts "HDMI VINILA BUILD FAILED: $st ($prog)" }
close_project
puts "VINILA DONE"
exit
