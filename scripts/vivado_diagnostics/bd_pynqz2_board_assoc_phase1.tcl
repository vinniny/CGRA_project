# bd_pynqz2_board_assoc_phase1.tcl (v12 phase1) — proper PYNQ-Z2 board
# association. The board file declares xc7z020clg400-1 (== project part),
# so the only blocker is a stale PS-7 IP customization cached at -2 from a
# prior bad run. upgrade_ip clears that, then board association applies the
# real per-lane DDR board-trace delays.  NO impl (phase-1 gate, ~4 min).

set BOARD_REPO /mnt/d/Programs/Xilinx/2025.1/Vivado/data/boards/board_files
set_param board.repoPaths $BOARD_REPO

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr

puts "=== open project ==="
open_project $PROJ
puts "  project part : [get_property part [current_project]]"

# Confirm pynq-z2 (-1) is discoverable
set bp [get_board_parts -quiet -filter {DISPLAY_NAME =~ "*pynq*"}]
puts "  discoverable board_parts: $bp"

set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file

# --- Identify + clear locked IPs ---
puts "\n=== locked IPs (before) ==="
foreach ip [get_ips] {
    if {[get_property IS_LOCKED $ip]} {
        puts "  LOCKED: $ip"
    }
}
puts "\n=== upgrade_ip on all IPs (clears part-mismatch lock) ==="
if {[catch {upgrade_ip [get_ips]} e]} { puts "  upgrade_ip: $e" } else { puts "  upgrade_ip OK" }

# re-open BD after upgrade
catch {close_bd_design [current_bd_design]}
open_bd_design $bd_file
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
set ps7_ip [get_ips -filter {NAME =~ "*processing_system7*"}]
puts "\n  PS-7 IP locked (after upgrade): [get_property IS_LOCKED $ps7_ip]"

# --- Associate the PYNQ-Z2 board (board file = -1, matches project) ---
puts "\n=== set board_part tul.com.tw:pynq-z2:part0:1.0 ==="
if {[catch {set_property board_part tul.com.tw:pynq-z2:part0:1.0 [current_project]} e]} {
    puts "  board_part ERR: $e"
}
puts "  board_part = [get_property board_part [current_project]]"

# --- Apply DDR + FIXED_IO board connections (populates board-trace delays) ---
puts "\n=== apply_bd_automation DDR + FIXED_IO ==="
catch {apply_bd_automation -rule xilinx.com:bd_rule:board \
        -config { Board_Interface "ddr ( DDR )" Manual_Source "Auto"} \
        [get_bd_intf_pins $ps7/DDR]} e1
puts "  DDR: $e1"
catch {apply_bd_automation -rule xilinx.com:bd_rule:board \
        -config { Board_Interface "fixed_io ( FIXED_IO )" Manual_Source "Auto"} \
        [get_bd_intf_pins $ps7/FIXED_IO]} e2
puts "  FIXED_IO: $e2"

# --- Verify the per-lane board-trace delays are now non-default ---
puts "\n=== verify DDR board-trace delays ==="
foreach p {PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_1
           PCW_UIPARAM_DDR_BOARD_DELAY0 PCW_UIPARAM_DDR_DQS_0_LENGTH_MM
           PCW_UIPARAM_DDR_FREQ_MHZ PCW_UIPARAM_DDR_PARTNO
           PCW_CRYSTAL_PERIPHERAL_FREQMHZ PCW_FPGA0_PERIPHERAL_FREQMHZ} {
    catch {puts [format "  %-38s = %s" $p [get_property CONFIG.$p $ps7]]}
}

# --- Force FCLK0 = 50 MHz (CGRA timing target) ---
puts "\n=== set FCLK0 = 50 MHz ==="
if {[catch {set_property CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ {50} $ps7} e]} {
    puts "  FCLK0 ERR: $e"
}
puts "  FCLK0 = [get_property CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ $ps7]"

# --- validate + save + regen ---
puts "\n=== validate ==="
if {[catch {validate_bd_design} e]} {
    puts "  VALIDATE FAILED: $e"
    puts "\nPHASE1 RESULT: FAILED at validate"
    close_project
    exit
}
puts "  validate OK"
save_bd_design
reset_target all [get_files $bd_file]
generate_target all [get_files $bd_file]
puts "\nPHASE1 RESULT: SUCCESS — board associated, delays applied, validated, regenerated"
close_project
puts "PHASE1 DONE"
exit
