# bd_pynqz2_delays_v13_phase1.tcl — the working recipe.
#
# Two locks were blocking the DDR board-delay fix:
#   1. PART lock  (PS-7 cached -2 vs project -1) -> cleared by upgrade_ip
#   2. BOARD lock (set_property board_part conflicts with the IP's
#      board='unset' customization, and apply_bd_automation can't
#      re-associate DDR because it's already an external port)
#
# Resolution: upgrade_ip to clear the part lock, then apply the PYNQ-Z2
# board-trace delays DIRECTLY as UIPARAMs (the exact values from the
# board_files preset.xml) — no board_part, so no board lock. Same data,
# no conflict.  NO impl (phase-1 gate).

set BOARD_REPO /mnt/d/Programs/Xilinx/2025.1/Vivado/data/boards/board_files
set_param board.repoPaths $BOARD_REPO
set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set DICT scripts/vivado_diagnostics/pynqz2_boarddelay_settings.tcl

puts "=== open project ==="
open_project $PROJ
puts "  project part: [get_property part [current_project]]"

set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file

# 1) Clear the part-mismatch lock
puts "\n=== upgrade_ip (clear -2/-1 part lock) ==="
if {[catch {upgrade_ip [get_ips]} e]} { puts "  upgrade_ip: $e" } else { puts "  upgrade_ip OK" }
catch {close_bd_design [current_bd_design]}
open_bd_design $bd_file
set ps7    [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
set ps7_ip [get_ips -filter {NAME =~ "*processing_system7*"}]
puts "  PS-7 IP locked after upgrade: [get_property IS_LOCKED $ps7_ip]"

# 2) Apply the 45 board-trace-delay UIPARAMs directly (NO board_part)
puts "\n=== apply 45 PYNQ-Z2 board-trace-delay UIPARAMs ==="
source $DICT
if {[catch {set_property -dict $bd_delay_dict $ps7} e]} {
    puts "  -dict FAILED: $e"
    puts "\nPHASE1 RESULT: FAILED applying delays"
    close_project; exit
}
puts "  -dict applied OK"
foreach p {PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_1
           PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_2 PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_3
           PCW_UIPARAM_DDR_BOARD_DELAY0 PCW_UIPARAM_DDR_BOARD_DELAY1
           PCW_UIPARAM_DDR_DQS_0_LENGTH_MM PCW_UIPARAM_DDR_DQS_1_LENGTH_MM} {
    catch {puts [format "  %-38s = %s" $p [get_property CONFIG.$p $ps7]]}
}

# 3) Confirm FCLK0 still 50, DDR freq/part intact
puts "\n=== sanity ==="
foreach p {PCW_FPGA0_PERIPHERAL_FREQMHZ PCW_CRYSTAL_PERIPHERAL_FREQMHZ
           PCW_UIPARAM_DDR_FREQ_MHZ PCW_UIPARAM_DDR_PARTNO} {
    catch {puts [format "  %-38s = %s" $p [get_property CONFIG.$p $ps7]]}
}

# 4) validate + save + regen
puts "\n=== validate ==="
if {[catch {validate_bd_design} e]} {
    puts "  VALIDATE FAILED: $e"
    puts "\nPHASE1 RESULT: FAILED at validate"
    close_project; exit
}
puts "  validate OK"
save_bd_design
reset_target all [get_files $bd_file]
generate_target all [get_files $bd_file]
puts "\nPHASE1 RESULT: SUCCESS — delays applied, validated, regenerated"
close_project
puts "PHASE1 DONE"
exit
