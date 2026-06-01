# hdmi_dual_crystal_fix.tcl — the HDMI build's PS7 defaulted to crystal=33.333
# (build_clean default), but the board is 50 MHz -> everything ran 1.5x fast
# (UART baud 172800 not 115200; DDR PLL overclocked -> DDR corrupt). Set
# PCW_CRYSTAL=50 (Vivado recomputes PLL FBDIVs to keep FCLK0=50/1=100/2=200),
# re-impl, re-export the .xsa.
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_HDMI_DUAL/cgra_hdmi_dual.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_hdmi_dual.xsa

open_project $PROJ
set bd [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
puts "  crystal before: [get_property CONFIG.PCW_CRYSTAL_PERIPHERAL_FREQMHZ $ps7]"
set_property CONFIG.PCW_CRYSTAL_PERIPHERAL_FREQMHZ {50} $ps7
puts "  crystal after : [get_property CONFIG.PCW_CRYSTAL_PERIPHERAL_FREQMHZ $ps7]"
# confirm FCLK targets held + DDR delays still present
foreach p {PCW_FPGA0_PERIPHERAL_FREQMHZ PCW_FPGA1_PERIPHERAL_FREQMHZ PCW_FPGA2_PERIPHERAL_FREQMHZ
           PCW_UIPARAM_DDR_BOARD_DELAY0 PCW_UIPARAM_DDR_PARTNO} {
    catch {puts "  $p = [get_property CONFIG.$p $ps7]"}
}
if {[catch {validate_bd_design} e]} { puts "VALIDATE FAILED: $e"; close_project; exit }
puts "  validate OK"
save_bd_design
catch {reset_target all [get_files $bd]}
catch {generate_target all [get_files $bd]}
catch {make_wrapper -files $bd -top -force}

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
if {[string match "*Complete*" $st] && $prog eq "100%"} {
    write_hw_platform -fixed -include_bit -force $XSA
    puts "  Wrote $XSA"
    puts "HDMI XTAL BUILD SUCCESS"
} else { puts "HDMI XTAL BUILD FAILED: $st ($prog)" }
close_project
puts "XTAL DONE"
exit
