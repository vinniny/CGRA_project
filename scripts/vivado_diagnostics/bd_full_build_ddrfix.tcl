# Full build with the DDR board-trace delays applied + board_part unset.
# Produces a corrected bitstream + .xsa whose ps7_init has the proper
# distinct per-lane DDR PHY delays. The DDR delays live in the BD as direct
# PS-7 UIPARAMs; board_part stays UNSET (setting it broke sub-core regen).

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_top.xsa

open_project $PROJ
# Belt-and-suspenders: ensure board_part stays unset
catch {set_property board_part "" [current_project]}
puts "  board_part: '[get_property board_part [current_project]]'"

set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
puts "  DDR DQS_TO_CLK_DELAY_0 = [get_property CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 $ps7]"
puts "  FCLK0 = [get_property CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ $ps7]"

# Regenerate output products (clean, board_part unset)
catch {reset_target all [get_files $bd_file]}
if {[catch {generate_target all [get_files $bd_file]} e]} {
    puts "ERROR generate_target: $e"; close_project; exit
}
puts "  generate_target OK"

# Make sure the HDL wrapper is current
catch {make_wrapper -files [get_files $bd_file] -top -force}

# DRC override for the floating tmds_*/ddc_* ports (HDMI removed earlier)
set hook /tmp/drc_override.tcl
set fp [open $hook w]
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks NSTD-1\]"
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks UCIO-1\]"
close $fp
set_property STEPS.WRITE_BITSTREAM.TCL.PRE $hook [get_runs impl_1]

puts "\n=== synth + impl + bitstream ==="
catch {reset_run impl_1}
catch {reset_run synth_1}
launch_runs impl_1 -to_step write_bitstream -jobs 6
wait_on_run impl_1
set st [get_property STATUS [get_runs impl_1]]
puts "  impl_1 status: $st"
set prog [get_property PROGRESS [get_runs impl_1]]
puts "  impl_1 progress: $prog"

if {[string match "*Complete*" $st] && $prog eq "100%"} {
    puts "\n=== write_hw_platform .xsa ==="
    write_hw_platform -fixed -include_bit -force $XSA
    puts "  Wrote $XSA ([file size $XSA] bytes)"
} else {
    puts "ERROR: impl did not complete: $st ($prog)"
}
close_project
puts "FULL BUILD DONE"
exit
