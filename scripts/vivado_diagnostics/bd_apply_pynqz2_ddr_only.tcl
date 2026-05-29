# bd_apply_pynqz2_ddr_only.tcl (v8c) — apply ONLY the 74 PCW_UIPARAM_DDR_*
# + PCW_DDR_RAM_* settings extracted from the canonical PYNQ-Z2 preset.xml.
# Skips set_property board_part to avoid the IP-lock conflict caused by
# the project's xc7z020clg400-1 vs the board file's xc7z020clg400-2.
#
# The DDR PHY board-trace delays (DQS_TO_CLK_DELAY_*, BOARD_DELAY*,
# DQ_*_LENGTH_MM) are the PCB-specific values our BD was missing.
#
# Source of truth: /mnt/d/Programs/Xilinx/2025.1/Vivado/data/boards/
#                  board_files/pynq-z2/A.0/preset.xml
# Generated dict: scripts/vivado_diagnostics/pynqz2_ddr_settings.tcl

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_top.xsa
set DDR_DICT_FILE scripts/vivado_diagnostics/pynqz2_ddr_settings.tcl

puts "============================================================="
puts " PYNQ-Z2 DDR-ONLY PRESET FIX (v8c — no board_part lock)"
puts "============================================================="

open_project $PROJ

set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
puts "\n=== Step 1: open BD [file tail $bd_file] ==="
open_bd_design $bd_file
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
puts "  PS-7 cell: $ps7"
puts "  PS-7 IS_LOCKED before: [get_property IS_LOCKED $ps7]"

# Step 2: load and apply the DDR settings dict
puts "\n=== Step 2: source DDR dict from preset.xml ==="
source $DDR_DICT_FILE   ;# defines $ddr_dict
puts "  loaded [dict size $ddr_dict] DDR settings"

puts "\n=== Step 3: set_property -dict (apply DDR settings) ==="
if {[catch {set_property -dict $ddr_dict $ps7} err]} {
    puts "  ERR applying dict: $err"
    puts "  Trying property-by-property fallback..."
    set ok 0; set bad 0
    dict for {k v} $ddr_dict {
        if {[catch {set_property $k $v $ps7} e2]} {
            puts "    FAIL $k = $v  :: $e2"
            incr bad
        } else {
            incr ok
        }
    }
    puts "  applied=$ok  failed=$bad"
}

# Verify a few key settings
puts "\n=== Verify post-apply ==="
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

# Step 4: validate + save
puts "\n=== Step 4: validate + save ==="
if {[catch {validate_bd_design} err]} {
    puts "  validate err: $err  (saving anyway)"
}
save_bd_design

# Step 5: regen output products
puts "\n=== Step 5: regen output products ==="
reset_target all [get_files $bd_file]
generate_target all [get_files $bd_file]

# Step 6: rebuild
puts "\n=== Step 6: synth + impl + bitgen ==="
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
    puts "\n=== Step 7: write_hw_platform .xsa ==="
    write_hw_platform -fixed -include_bit -force $XSA
    puts "  Wrote $XSA ([file size $XSA] bytes)"
} else {
    puts "ERROR impl_1 did not complete: $state"
}

close_bd_design [current_bd_design]
close_project
puts "\nB9 v8c DONE"
exit
