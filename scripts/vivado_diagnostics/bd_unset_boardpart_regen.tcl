# THE FIX: v12's board_part=pynq-z2 persisted to the project and now every
# internal sub-core (e.g. smartconnect's psr_aclk, customized with board=
# 'unset') fails a board-mismatch check during regen -> the C_AUX_RESET_HIGH
# "failure". Unset board_part. The DDR board-trace delays were applied as
# direct PS-7 UIPARAMs (independent of board_part), so they stay.
#
# Phase-1: unset board_part, regenerate BD, verify smartconnect generates
# and a fresh ps7_init with distinct per-lane DDR delays is emitted. NO impl.

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
open_project $PROJ
puts "  board_part (before): [get_property board_part [current_project]]"

# UNSET board_part (the poison)
set_property board_part "" [current_project]
puts "  board_part (after) : '[get_property board_part [current_project]]'"

set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]

# Confirm DDR delays still present
puts "\n=== DDR delays still in BD ==="
foreach p {PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 PCW_UIPARAM_DDR_BOARD_DELAY0 PCW_FPGA0_PERIPHERAL_FREQMHZ} {
    catch {puts "  $p = [get_property CONFIG.$p $ps7]"}
}

puts "\n=== reset + regenerate BD (should now succeed) ==="
catch {reset_target all [get_files $bd_file]}
if {[catch {generate_target all [get_files $bd_file]} e]} {
    puts "  generate_target FAILED: $e"
    puts "\nPHASE1 RESULT: FAILED"
    close_project; exit
}
puts "  generate_target OK"

# Find fresh ps7_init and check per-lane DDR values
set found ""
foreach base {cgra_ip.gen cgra_ip.srcs} {
    set p /mnt/c/Users/thanh/Desktop/FPGA_CGRA/$base/sources_1/bd/design_1/ip/design_1_processing_system7_0_0/ps7_init.tcl
    if {[file exists $p]} { set found $p; break }
}
puts "\n=== fresh ps7_init: $found ==="
if {$found ne ""} {
    set fp [open $found r]; set txt [read $fp]; close $fp
    foreach reg {0XF800612C 0XF8006130 0XF8006134 0XF8006138} {
        foreach line [split $txt "\n"] {
            if {[string match "*$reg *" $line]} { puts "  [string trim $line]"; break }
        }
    }
}

# Save the (now-clean) project state
save_bd_design
puts "\nPHASE1 RESULT: SUCCESS — board_part unset, BD regenerated, ps7_init emitted"
close_project
puts "PHASE1 DONE"
exit
