# bd_fix_crystal.tcl — fix PS-7 crystal config + re-run impl.
# Root cause: PCW_CRYSTAL_PERIPHERAL_FREQMHZ = 33.333333, but TUL
# PYNQ-Z2 board has 50 MHz crystal. This made everything 1.5× over-
# clocked → CGRA DMA fails timing.

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_top.xsa

puts "==========================================================="
puts " BD CRYSTAL FIX + REBUILD"
puts "==========================================================="

open_project $PROJ
set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file

set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]

puts "\n=== Before fix ==="
foreach prop {
    PCW_CRYSTAL_PERIPHERAL_FREQMHZ
    PCW_FPGA0_PERIPHERAL_FREQMHZ
    PCW_UART_PERIPHERAL_FREQMHZ
    PCW_ARM_PLL_CTRL_FBDIV
    PCW_IO_PLL_CTRL_FBDIV
    PCW_DDR_PLL_CTRL_FBDIV
} {
    catch {puts "  CONFIG.$prop = [get_property CONFIG.$prop $ps7]"}
}

puts "\n=== Setting PCW_CRYSTAL_PERIPHERAL_FREQMHZ = 50 ==="
set_property -dict [list \
    CONFIG.PCW_CRYSTAL_PERIPHERAL_FREQMHZ {50} \
    ] $ps7

puts "\n=== After fix ==="
foreach prop {
    PCW_CRYSTAL_PERIPHERAL_FREQMHZ
    PCW_FPGA0_PERIPHERAL_FREQMHZ
    PCW_UART_PERIPHERAL_FREQMHZ
    PCW_ARM_PLL_CTRL_FBDIV
    PCW_IO_PLL_CTRL_FBDIV
    PCW_DDR_PLL_CTRL_FBDIV
} {
    catch {puts "  CONFIG.$prop = [get_property CONFIG.$prop $ps7]"}
}

puts "\nValidating BD..."
validate_bd_design
save_bd_design

# Force regeneration of all PS-7 derived files (ps7_init.tcl,
# ps7_init.h/.c with new PLL FBDIVs computed for 50 MHz input)
puts "\nRegenerating output products..."
reset_target all [get_files $bd_file]
generate_target all [get_files $bd_file]

# Mark impl as out-of-date so it re-runs
puts "\nResetting + launching synth + impl..."
reset_run impl_1
reset_run synth_1
launch_runs impl_1 -to_step write_bitstream -jobs 6
wait_on_run impl_1
puts "Impl complete: status=[get_property STATUS [get_runs impl_1]]"

# Export the fresh, coherent .xsa
puts "\nExporting fresh .xsa to $XSA ..."
write_hw_platform -fixed -include_bit -force $XSA
puts "Wrote $XSA ([file size $XSA] bytes)"

# Print the new bitstream's MD5
set bit_file /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.runs/impl_1/design_1_wrapper.bit
if {[file exists $bit_file]} {
    puts "\nNew bitstream:"
    puts "  $bit_file"
    puts "  size: [file size $bit_file]"
}

close_bd_design [get_bd_designs]
close_project
puts "\n==========================================================="
puts " DONE — new .xsa with crystal=50 is at $XSA"
puts "==========================================================="
exit
