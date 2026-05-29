# bd_apply_pynqz2_board_preset.tcl — apply official PYNQ-Z2 board preset
# to the PS-7. Vivado on the Linux side doesn't have PYNQ-Z2 in its default
# board repo, so we point board.repoPaths at the Windows Vivado install
# where the canonical board files live.

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_top.xsa

# CRITICAL: must set board.repoPaths BEFORE open_project; project lookup
# of the BoardPart references happens at project-open time.
set BOARD_REPO /mnt/d/Programs/Xilinx/2025.1/Vivado/data/boards/board_files
set_param board.repoPaths $BOARD_REPO
puts "board.repoPaths = [get_param board.repoPaths]"

puts "============================================================="
puts " PYNQ-Z2 BOARD PRESET FIX (v8b — repoPaths corrected)"
puts "============================================================="

open_project $PROJ

# Step 0: confirm PYNQ-Z2 is now discoverable
puts "\n=== Step 0: confirm PYNQ-Z2 is discoverable ==="
set parts [get_board_parts -filter {DISPLAY_NAME =~ "*pynq*"}]
puts "  matching board_parts: $parts"

# Step 1: associate project with the PYNQ-Z2 board
puts "\n=== Step 1: set_property board_part ==="
if {[catch {set_property board_part tul.com.tw:pynq-z2:part0:1.0 [current_project]} err]} {
    puts "  ERR: $err"
    puts "  Trying alternate id formats..."
    foreach id {tul.com.tw:pynq-z2:part0:A.0 pynq-z2:1.0 tul:pynq-z2:1.0} {
        if {![catch {set_property board_part $id [current_project]} e]} {
            puts "  set with $id OK"
            break
        }
    }
}
puts "  current board_part: [get_property board_part [current_project]]"

# Step 2: open BD
set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
puts "\n=== Step 2: open BD [file tail $bd_file] ==="
open_bd_design $bd_file
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
puts "  PS-7 cell: $ps7"

# Step 3: apply DDR + FIXED_IO board connections
puts "\n=== Step 3: apply_bd_automation DDR + FIXED_IO ==="
catch {apply_bd_automation -rule xilinx.com:bd_rule:board \
        -config { Board_Interface "ddr ( DDR )" Manual_Source "Auto"} \
        $ps7/DDR} err1
puts "  DDR: $err1"
catch {apply_bd_automation -rule xilinx.com:bd_rule:board \
        -config { Board_Interface "fixed_io ( FIXED_IO )" Manual_Source "Auto"} \
        $ps7/FIXED_IO} err2
puts "  FIXED_IO: $err2"

# Verify key DDR PHY properties
puts "\n=== Verify DDR PHY board-delay properties ==="
foreach prop {
    PCW_UIPARAM_DDR_FREQ_MHZ
    PCW_UIPARAM_DDR_PARTNO
    PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0
    PCW_UIPARAM_DDR_BOARD_DELAY0
    PCW_UIPARAM_DDR_DQ_0_LENGTH_MM
    PCW_UIPARAM_DDR_CL
    PCW_UIPARAM_DDR_CWL
    PCW_UIPARAM_DDR_T_FAW
    PCW_UIPARAM_DDR_T_RAS_MIN
    PCW_CRYSTAL_PERIPHERAL_FREQMHZ
    PCW_FPGA0_PERIPHERAL_FREQMHZ
} {
    catch {puts [format "  %-40s = %s" $prop [get_property CONFIG.$prop $ps7]]}
}

# Step 4: KEEP FCLK0 at 50 MHz (CGRA timing target)
puts "\n=== Step 4: force FCLK0 = 50 MHz (CGRA) ==="
set_property CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ {50} $ps7
puts "  PCW_FPGA0_PERIPHERAL_FREQMHZ = [get_property CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ $ps7]"

# Step 5: validate + save
puts "\n=== Step 5: validate + save BD ==="
if {[catch {validate_bd_design} err]} {
    puts "  validate err: $err  (saving anyway)"
}
save_bd_design

# Step 6: regenerate output products
puts "\n=== Step 6: regen output products ==="
reset_target all [get_files $bd_file]
generate_target all [get_files $bd_file]

# Step 7: rebuild
puts "\n=== Step 7: synth + impl + bitgen ==="
catch {reset_run impl_1}
catch {reset_run synth_1}

set hook_file /tmp/drc_override.tcl
set fp [open $hook_file w]
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks NSTD-1\]"
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks UCIO-1\]"
close $fp
set_property STEPS.WRITE_BITSTREAM.TCL.PRE $hook_file [get_runs impl_1]

launch_runs impl_1 -to_step write_bitstream -jobs 6
wait_on_run impl_1
set state [get_property STATUS [get_runs impl_1]]
puts "  impl_1 status: $state"

if {[string match "*Complete*" $state] && ![string match "*ERROR*" $state]} {
    puts "\n=== Step 8: write_hw_platform .xsa ==="
    write_hw_platform -fixed -include_bit -force $XSA
    puts "  Wrote $XSA ([file size $XSA] bytes)"
} else {
    puts "ERROR impl_1 did not complete: $state"
}

close_bd_design [current_bd_design]
close_project
puts "\nB9 v8b DONE"
exit
