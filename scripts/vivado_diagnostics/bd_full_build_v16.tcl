# v16 — the complete DDR fix build, combining both lessons:
#   * board_part UNSET  -> no psr_aclk board-mismatch on sub-core regen
#   * upgrade_ip        -> clears the part/version lock on PS7 + rst_ps7 so
#                          synth regenerates them WITH the DDR delays
# (Neither alone works: unset-only leaves PS7 locked -> synth uses stale
#  products w/o delays; upgrade-only with board_part set breaks psr_aclk.)
# DDR board-trace delays already live in the BD as PS-7 UIPARAMs.
#
# Guard: abort before the (40 min) impl if any IP stays locked or generate
# fails.

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_top.xsa

open_project $PROJ
catch {set_property board_part "" [current_project]}
puts "  board_part: '[get_property board_part [current_project]]'"
set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file

# 1) upgrade_ip to clear part/version locks (board_part unset => no mismatch)
puts "\n=== upgrade_ip (clear locks) ==="
if {[catch {upgrade_ip [get_ips]} e]} { puts "  upgrade_ip: $e" } else { puts "  upgrade_ip OK" }

# 2) verify NO IP remains locked
catch {close_bd_design [current_bd_design]}
open_bd_design $bd_file
set locked {}
foreach ip [get_ips] { if {[get_property IS_LOCKED $ip]} { lappend locked $ip } }
puts "\n=== locked IPs after upgrade: [llength $locked] ==="
foreach ip $locked { puts "  LOCKED: $ip" }
if {[llength $locked] > 0} {
    puts "\nABORT: IPs still locked, not starting impl"
    close_project; exit
}

# 3) confirm DDR delays present
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
puts "\n  DDR DQS_TO_CLK_DELAY_0 = [get_property CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 $ps7]"
puts "  FCLK0 = [get_property CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ $ps7]"

# 4) regenerate
puts "\n=== generate_target ==="
catch {reset_target all [get_files $bd_file]}
if {[catch {generate_target all [get_files $bd_file]} e]} {
    puts "  generate FAILED: $e"; puts "ABORT"; close_project; exit
}
puts "  generate OK"
catch {make_wrapper -files [get_files $bd_file] -top -force}
save_bd_design

# 5) DRC override for floating tmds/ddc ports
set hook /tmp/drc_override.tcl
set fp [open $hook w]
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks NSTD-1\]"
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks UCIO-1\]"
close $fp
set_property STEPS.WRITE_BITSTREAM.TCL.PRE $hook [get_runs impl_1]

# 6) build
puts "\n=== synth + impl + bitstream ==="
catch {reset_run impl_1}
catch {reset_run synth_1}
launch_runs impl_1 -to_step write_bitstream -jobs 6
wait_on_run impl_1
set st   [get_property STATUS   [get_runs impl_1]]
set prog [get_property PROGRESS [get_runs impl_1]]
puts "  impl_1: $st ($prog)"
if {[string match "*Complete*" $st] && $prog eq "100%"} {
    write_hw_platform -fixed -include_bit -force $XSA
    puts "  Wrote $XSA ([file size $XSA] bytes)"
    puts "BUILD SUCCESS"
} else {
    puts "BUILD FAILED: $st ($prog)"
}
close_project
puts "V16 DONE"
exit
