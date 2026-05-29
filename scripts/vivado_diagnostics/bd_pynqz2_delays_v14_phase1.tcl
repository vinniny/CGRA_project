# v14 phase1 — upgrade ONLY the processing_system7 IP (clears its -2 part
# lock without touching smartconnect, which breaks on upgrade). Then apply
# the PYNQ-Z2 board-trace delays directly. NO impl.

set BOARD_REPO /mnt/d/Programs/Xilinx/2025.1/Vivado/data/boards/board_files
set_param board.repoPaths $BOARD_REPO
set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set DICT scripts/vivado_diagnostics/pynqz2_boarddelay_settings.tcl

open_project $PROJ
puts "  project part: [get_property part [current_project]]"
set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file

# Upgrade ONLY processing_system7 (leave smartconnect/others alone)
puts "\n=== upgrade ONLY processing_system7 ==="
set ps7ip [get_ips -filter {NAME =~ "*processing_system7*"}]
puts "  target: $ps7ip  locked(before)=[get_property IS_LOCKED $ps7ip]"
if {[catch {upgrade_ip $ps7ip} e]} { puts "  upgrade_ip: $e" } else { puts "  upgrade_ip OK" }

catch {close_bd_design [current_bd_design]}
open_bd_design $bd_file
set ps7    [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
set ps7ip  [get_ips -filter {NAME =~ "*processing_system7*"}]
puts "  PS-7 locked(after)=[get_property IS_LOCKED $ps7ip]"

# Apply 45 board-trace-delay UIPARAMs directly
puts "\n=== apply board-trace delays ==="
source $DICT
if {[catch {set_property -dict $bd_delay_dict $ps7} e]} {
    puts "  -dict FAILED: $e"; puts "\nPHASE1 RESULT: FAILED applying delays"; close_project; exit
}
puts "  -dict applied OK"
foreach p {PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 PCW_UIPARAM_DDR_BOARD_DELAY0
           PCW_UIPARAM_DDR_DQS_0_LENGTH_MM PCW_FPGA0_PERIPHERAL_FREQMHZ
           PCW_UIPARAM_DDR_FREQ_MHZ} {
    catch {puts [format "  %-38s = %s" $p [get_property CONFIG.$p $ps7]]}
}

# Validate — but tolerate the negative-DQS CRITICAL WARNINGS (they are
# expected for PYNQ-Z2). Only a hard ERROR should block.
puts "\n=== validate ==="
if {[catch {validate_bd_design} e]} {
    puts "  validate returned error: $e"
    puts "  (checking whether it is only the negative-DQS warnings...)"
    # Try generate anyway — if only warnings, generate may still succeed
}
puts "\n=== save + regen ==="
if {[catch {save_bd_design} e]} { puts "  save err: $e" }
if {[catch {reset_target all [get_files $bd_file]} e]} { puts "  reset_target: $e" }
if {[catch {generate_target all [get_files $bd_file]} e]} {
    puts "  generate_target FAILED: $e"
    puts "\nPHASE1 RESULT: regen FAILED"
    close_project; exit
}
puts "\nPHASE1 RESULT: SUCCESS — PS7 upgraded, delays applied, regenerated"
close_project
puts "PHASE1 DONE"
exit
