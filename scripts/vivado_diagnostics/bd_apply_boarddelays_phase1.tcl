# bd_apply_boarddelays_phase1.tcl (v10 phase 1) — apply the 45 numeric
# PYNQ-Z2 board-trace-delay UIPARAMs to the PS-7, validate, regenerate
# output products, and REPORT. NO impl (so a bad apply costs ~2 min not 40).
#
# Root cause: BD built with BoardPart="" -> generic identical per-lane DDR
# PHY delays -> data eye not centered at 525 MHz -> DDR data corrupt.
# See memory/project_ddr_root_cause.md.
#
# Keeps project part xc7z020clg400-1 (no board_part -> no IP lock).

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set DICT scripts/vivado_diagnostics/pynqz2_boarddelay_settings.tcl

puts "============================================================="
puts " BOARD-DELAY FIX v10 phase 1 (apply + validate, NO impl)"
puts "============================================================="

open_project $PROJ
set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
puts "  PS-7: $ps7   IS_LOCKED=[get_property IS_LOCKED $ps7]"

# show BEFORE values for two representative params
puts "\n=== BEFORE ==="
foreach p {PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 PCW_UIPARAM_DDR_BOARD_DELAY0 PCW_UIPARAM_DDR_DQS_0_LENGTH_MM} {
    catch {puts "  $p = [get_property CONFIG.$p $ps7]"}
}

source $DICT   ;# defines $bd_delay_dict
puts "\n=== Applying [dict size $bd_delay_dict] board-delay params (atomic -dict) ==="
set applied 0
if {[catch {set_property -dict $bd_delay_dict $ps7} err]} {
    puts "  -dict FAILED: $err"
    puts "  fallback property-by-property:"
    dict for {k v} $bd_delay_dict {
        if {[catch {set_property $k $v $ps7} e]} {
            puts "    FAIL $k=$v :: $e"
        } else { incr applied }
    }
    puts "  applied=$applied / [dict size $bd_delay_dict]"
} else {
    set applied [dict size $bd_delay_dict]
    puts "  -dict applied OK ($applied params)"
}

puts "\n=== AFTER ==="
foreach p {PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 PCW_UIPARAM_DDR_BOARD_DELAY0 PCW_UIPARAM_DDR_DQS_0_LENGTH_MM} {
    catch {puts "  $p = [get_property CONFIG.$p $ps7]"}
}

puts "\n=== validate_bd_design ==="
set vok 1
if {[catch {validate_bd_design} err]} {
    puts "  VALIDATE FAILED: $err"
    set vok 0
} else {
    puts "  validate OK"
}

if {$vok} {
    save_bd_design
    puts "\n=== regen output products (generates fresh ps7_init) ==="
    reset_target all [get_files $bd_file]
    generate_target all [get_files $bd_file]
    puts "  regen done"
    puts "\nPHASE1 RESULT: SUCCESS (applied=$applied, validate OK, regen done)"
} else {
    puts "\nPHASE1 RESULT: VALIDATE FAILED — not saving, not regenerating"
}

close_bd_design [current_bd_design]
close_project
puts "PHASE1 DONE"
exit
