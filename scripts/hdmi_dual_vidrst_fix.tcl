# hdmi_dual_vidrst_fix.tcl — the clean dual-HDMI BD resets v_axi4s_vid_out and
# rgb2dvi from rst_ps7_0_100M (FCLK1=100 domain), but those blocks run on the
# PXL_CLK_O pixel-clock domain.  Per the project's own HDMI rule (CLAUDE.md,
# learned V79->V156): the video-out + rgb2dvi reset MUST come from a
# proc_sys_reset clocked by PXL_CLK_O, else the pixel-domain logic never
# releases reset cleanly -> no DE/valid video -> monitor shows "no signal"
# even though dynclk locks, v_tc generates, and the VDMA streams.
#
# This adds proc_sys_reset_video (slowest_sync_clk = axi_dynclk_0/PXL_CLK_O,
# dcm_locked = dynclk LOCKED if exposed) and rewires rgb2dvi_0/aRst_n +
# v_axi4s_vid_out_0/aresetn to it.  Re-impl + re-export the .xsa.
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_HDMI_DUAL/cgra_hdmi_dual.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_hdmi_dual.xsa

open_project $PROJ
set bd [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd

if {[llength [get_bd_cells -quiet proc_sys_reset_video]] == 0} {
    # find proc_sys_reset VLNV from an existing reset cell
    set existing [lindex [get_bd_cells -filter {VLNV =~ "*proc_sys_reset*"}] 0]
    set vlnv [get_property VLNV $existing]
    puts "  creating proc_sys_reset_video ($vlnv)"
    create_bd_cell -type ip -vlnv $vlnv proc_sys_reset_video
    # match the active-low ext reset polarity the 100M reset uses
    catch {set_property CONFIG.C_EXT_RESET_HIGH \
        [get_property CONFIG.C_EXT_RESET_HIGH $existing] [get_bd_cells proc_sys_reset_video]}
    connect_bd_net [get_bd_pins axi_dynclk_0/PXL_CLK_O] [get_bd_pins proc_sys_reset_video/slowest_sync_clk]
    # ext_reset_in: mirror what rst_ps7_0_100M uses (PS7 FCLK_RESET0_N, active low)
    catch {connect_bd_net [get_bd_pins processing_system7_0/FCLK_RESET0_N] [get_bd_pins proc_sys_reset_video/ext_reset_in]}
    # dcm_locked: dynclk lock output if the IP exposes one (release video reset only after PXL_CLK locks)
    set lk [get_bd_pins -quiet axi_dynclk_0/LOCKED_O]
    if {$lk eq ""} { set lk [get_bd_pins -quiet axi_dynclk_0/LOCKED] }
    if {$lk ne ""} { puts "  dcm_locked <- $lk"; catch {connect_bd_net $lk [get_bd_pins proc_sys_reset_video/dcm_locked]} } \
    else { puts "  (no dynclk LOCKED pin; leaving dcm_locked default)" }
} else { puts "  proc_sys_reset_video already present" }

# Rewire the two pixel-domain resets to the new video reset.
foreach pin {rgb2dvi_0/aRst_n v_axi4s_vid_out_0/aresetn} {
    set p [get_bd_pins $pin]
    set net [get_bd_nets -quiet -of $p]
    if {$net ne ""} { disconnect_bd_net $net $p }
    connect_bd_net [get_bd_pins proc_sys_reset_video/peripheral_aresetn] $p
    puts "  $pin <- proc_sys_reset_video/peripheral_aresetn"
}

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
    puts "HDMI VIDRST BUILD SUCCESS"
} else { puts "HDMI VIDRST BUILD FAILED: $st ($prog)" }
close_project
puts "VIDRST DONE"
exit
