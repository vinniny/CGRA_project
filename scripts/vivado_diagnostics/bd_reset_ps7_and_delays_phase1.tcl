# bd_reset_ps7_and_delays_phase1.tcl (v11 phase1) — the PS-7 IP got cached
# for xc7z020clg400-2 (residual from a board_part experiment) while the
# project is -1, which LOCKS the IP and blocks all set_property. This:
#   1. resets the PS-7 IP output products so it re-targets the project -1 part
#   2. confirms it unlocks
#   3. applies the 45 PYNQ-Z2 board-trace-delay UIPARAMs
#   4. validates + regenerates  (NO impl — cheap, ~3 min)
# Keeps project part -1 throughout.

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set DICT scripts/vivado_diagnostics/pynqz2_boarddelay_settings.tcl

puts "=== open project (part -1) ==="
open_project $PROJ
puts "  project part: [get_property part [current_project]]"

set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
puts "  PS-7 IS_LOCKED (before): [get_property IS_LOCKED $ps7]"

puts "\n=== report_ip_status ==="
catch {report_ip_status}

# --- Try to clear the locked/part-mismatch state ---
# Approach 1: reset + regenerate the BD output products for the current part.
puts "\n=== reset_target + generate_target (re-target IP to project -1) ==="
catch {reset_target all [get_files $bd_file]} e1
puts "  reset_target: $e1"
catch {generate_target all [get_files $bd_file]} e2
puts "  generate_target: $e2"

# Re-open BD (regen may have closed it) and re-check lock
catch {open_bd_design $bd_file}
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
set locked [get_property IS_LOCKED $ps7]
puts "  PS-7 IS_LOCKED (after reset/regen): $locked"

if {$locked} {
    # Approach 2: upgrade_ip on the locked IP
    puts "\n=== upgrade_ip fallback ==="
    catch {upgrade_ip [get_ips -filter {IS_LOCKED}]} e3
    puts "  upgrade_ip: $e3"
    catch {open_bd_design $bd_file}
    set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
    set locked [get_property IS_LOCKED $ps7]
    puts "  PS-7 IS_LOCKED (after upgrade): $locked"
}

if {$locked} {
    puts "\nPHASE1 RESULT: PS-7 STILL LOCKED — cannot apply delays in batch."
    puts "  Likely needs project part change to -2, or a GUI re-customize."
    close_project
    exit
}

# --- IP unlocked: apply board-delay params ---
puts "\n=== PS-7 unlocked — apply 45 board-delay UIPARAMs ==="
source $DICT
set ok 1
if {[catch {set_property -dict $bd_delay_dict $ps7} err]} {
    puts "  -dict FAILED: $err"
    set ok 0
} else {
    puts "  -dict applied OK"
}
puts "  DQS_TO_CLK_DELAY_0 = [get_property CONFIG.PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 $ps7]"
puts "  BOARD_DELAY0       = [get_property CONFIG.PCW_UIPARAM_DDR_BOARD_DELAY0 $ps7]"

if {$ok} {
    if {[catch {validate_bd_design} err]} {
        puts "  VALIDATE FAILED: $err"
    } else {
        puts "  validate OK"
        save_bd_design
        reset_target all [get_files $bd_file]
        generate_target all [get_files $bd_file]
        puts "\nPHASE1 RESULT: SUCCESS — delays applied, validated, regenerated."
    }
} else {
    puts "\nPHASE1 RESULT: delays failed to apply."
}

close_project
puts "PHASE1 DONE"
exit
