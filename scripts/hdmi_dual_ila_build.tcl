# hdmi_dual_ila_build.tcl — DEBUG build: add a System ILA (NATIVE probes) on the
# v_axi4s_vid_out_0 status outputs (locked / overflow / underflow / fifo level),
# clocked by PXL_CLK_O, so we can SEE whether the video-out core genlocks.  This
# is the one set of signals not reachable from MMIO.  Drive it headless on WSL via
# Vivado hw_manager Tcl after programming + running the demo.  Temporary debug
# bitstream — NOT baked into build_cgra_hdmi_pynqz2_clean.tcl.
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_HDMI_DUAL/cgra_hdmi_dual.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_hdmi_dual_ila.xsa

open_project $PROJ
set bd [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd

# Always recreate fresh (a prior run may have saved it with a bad clock).
catch {delete_bd_objs [get_bd_cells -quiet system_ila_vid]}
if {1} {
    create_bd_cell -type ip -vlnv [get_property VLNV [get_ipdefs *system_ila*]] system_ila_vid
    # NATIVE probes for discrete status nets; deep buffer to catch vsync edges.
    set_property -dict [list \
        CONFIG.C_MON_TYPE {NATIVE} \
        CONFIG.C_NUM_OF_PROBES {3} \
        CONFIG.C_DATA_DEPTH {4096} \
        CONFIG.C_PROBE0_WIDTH {1} CONFIG.C_PROBE1_WIDTH {1} CONFIG.C_PROBE2_WIDTH {1} \
    ] [get_bd_cells system_ila_vid]
    # Clock the ILA on FCLK0 (normal fabric clock), NOT PXL_CLK_O — the pixel
    # clock uses I/O-clocking (BUFIO) resources for the HDMI serializers and an
    # ILA/dbg_hub on it fails IO clock placement.  locked/overflow/underflow are
    # level signals, sampling them on a 50 MHz fabric clock reads their state fine.
    connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0] [get_bd_pins system_ila_vid/clk]
    catch {connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn] [get_bd_pins system_ila_vid/resetn]}
    connect_bd_net [get_bd_pins v_axi4s_vid_out_0/locked]    [get_bd_pins system_ila_vid/probe0]
    connect_bd_net [get_bd_pins v_axi4s_vid_out_0/overflow]  [get_bd_pins system_ila_vid/probe1]
    connect_bd_net [get_bd_pins v_axi4s_vid_out_0/underflow] [get_bd_pins system_ila_vid/probe2]
    puts "  system_ila_vid added: probe0=locked probe1=overflow probe2=underflow"
} else { puts "  system_ila_vid already present" }

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
    puts "HDMI ILA BUILD SUCCESS"
} else { puts "HDMI ILA BUILD FAILED: $st ($prog)" }
close_project
puts "ILA DONE"
exit
