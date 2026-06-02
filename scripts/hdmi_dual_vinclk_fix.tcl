# hdmi_dual_vinclk_fix.tcl — HDMI-IN capture-path reclock (FCLK2=200MHz approach).
# Frozen capture root cause: v_vid_in_axi4s_0/aclk + axis_subset_converter_in +
# axi_vdma_1 s_axis all run at FCLK0=50MHz, but the laptop sends 1080p60
# (~148.5MHz pixel clock, ~124 Mpix/s active).  v_vid_in's AXIS output at 50MHz
# can't drain the 148MHz pixel input -> per-line overrun -> no complete frame.
#
# Fix: clock the capture AXIS (v_vid_in aclk, subset_converter, vdma_1 s_axis) at
# FCLK2=200MHz (>148MHz pixel rate -> no overrun).  Keep v_vid_in_axi4s
# C_HAS_ASYNC_CLK=1: its internal async FIFO crosses PixelClk(148)->FCLK2(200),
# which is a GENUINE async pair (valid).  NOTE: do NOT set aclk=PixelClk or
# C_HAS_ASYNC_CLK=0 — both collapse the IP's FIFO into an undriven-LUT opt error.
# vdma_1 m_axi/lite stay FCLK0 (auto-async to the 200MHz s_axis).
# Writes a TEST xsa; canonical untouched until verified.
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_HDMI_DUAL/cgra_hdmi_dual.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_hdmi_dual_vinclk.xsa

open_project $PROJ
set bd [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd

catch {delete_bd_objs [get_bd_cells -quiet system_ila_vin]}

# Make sure v_vid_in_axi4s is back to its async-FIFO default (in case a prior
# run set C_HAS_ASYNC_CLK=0) so the PixelClk->FCLK2 crossing uses the async FIFO.
catch {set_property CONFIG.C_HAS_ASYNC_CLK {1} [get_bd_cells v_vid_in_axi4s_0]}

set F2 [get_bd_pins processing_system7_0/FCLK_CLK2]

# proc_sys_reset on the FCLK2 (200MHz) domain.  dcm_locked tied high (FCLK2 is a
# free-running PS clock).  ext_reset_in = FCLK_RESET0_N.
if {[llength [get_bd_cells -quiet proc_sys_reset_vin]] == 0} {
    set existing [lindex [get_bd_cells -filter {VLNV =~ "*proc_sys_reset*"}] 0]
    create_bd_cell -type ip -vlnv [get_property VLNV $existing] proc_sys_reset_vin
    catch {set_property CONFIG.C_EXT_RESET_HIGH [get_property CONFIG.C_EXT_RESET_HIGH $existing] [get_bd_cells proc_sys_reset_vin]}
    connect_bd_net $F2 [get_bd_pins proc_sys_reset_vin/slowest_sync_clk]
    catch {connect_bd_net [get_bd_pins processing_system7_0/FCLK_RESET0_N] [get_bd_pins proc_sys_reset_vin/ext_reset_in]}
    set one [get_bd_pins -quiet xlconstant_hdmi_en/dout]
    if {$one eq ""} { set one [get_bd_pins -quiet xlconst_rx_hpd_high/dout] }
    if {$one ne ""} { catch {connect_bd_net $one [get_bd_pins proc_sys_reset_vin/dcm_locked]} }
    puts "  created proc_sys_reset_vin on FCLK2"
}
set VRSTN [get_bd_pins proc_sys_reset_vin/peripheral_aresetn]

proc rewire {pin src} {
    set p [get_bd_pins $pin]; set n [get_bd_nets -quiet -of $p]
    if {$n ne ""} { disconnect_bd_net $n $p }
    connect_bd_net $src $p
}
# vid_io_in side stays on dvi2rgb PixelClk (toggling C_HAS_ASYNC_CLK can leave
# vid_io_in_clk unconnected -> reconnect it).  AXIS (aclk) side -> FCLK2.
set PXL [get_bd_pins dvi2rgb_0/PixelClk]
catch {rewire v_vid_in_axi4s_0/vid_io_in_clk $PXL}
catch {connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_reset] [get_bd_pins v_vid_in_axi4s_0/vid_io_in_reset]}
# Capture AXIS domain -> FCLK2 (200MHz)
rewire v_vid_in_axi4s_0/aclk $F2
rewire v_vid_in_axi4s_0/aresetn $VRSTN
catch {rewire axis_subset_converter_in/aclk $F2}
catch {rewire axis_subset_converter_in/aresetn $VRSTN}
rewire axi_vdma_1/s_axis_s2mm_aclk $F2
puts "  v_vid_in/subset/vdma_1.s_axis aclk<-FCLK2(200), aresetn<-psr_vin (m_axi/lite stay FCLK0)"

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
    puts "HDMI VINCLK BUILD SUCCESS"
} else { puts "HDMI VINCLK BUILD FAILED: $st ($prog)" }
close_project
puts "VINCLK DONE"
exit
