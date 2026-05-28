# bd_inspect.tcl — read-only BD audit. No changes. Reports everything
# we need to know about why DMA is failing on this PYNQ-Z2.
#
# Sections:
#   §1  Project metadata (top module, part, board)
#   §2  All BD cells (name, type, VLNV)
#   §3  PS-7 config (every PCW property that matters for HP/FCLK/UART)
#   §4  CGRA IP config (BASEADDR, parameters)
#   §5  All interface connections (intf_nets between cells)
#   §6  All signal nets (clocks, resets)
#   §7  Address map (all AXI master views)
#   §8  Existing ILAs / debug cells
#   §9  Critical-path / timing summary if impl is available

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr

puts "==========================================================="
puts " BD INSPECT — read-only audit"
puts "==========================================================="

open_project $PROJ

# ──────────────────────────────────────────────────────────────
puts "\n=== §1 Project metadata ==="
puts "  Top module: [get_property TOP [current_fileset]]"
puts "  Part:       [get_property PART [current_project]]"
puts "  Board:      [get_property BOARD_PART [current_project]]"

# Open the block design
set bds [get_files -filter {FILE_TYPE == "Block Designs"}]
if {[llength $bds] == 0} { puts "ERROR: no BD"; exit 1 }
set bd [lindex $bds 0]
puts "  BD file:    $bd"
open_bd_design $bd

# ──────────────────────────────────────────────────────────────
puts "\n=== §2 All BD cells ==="
foreach cell [get_bd_cells] {
    set vlnv [get_property VLNV $cell]
    puts "  $cell  →  $vlnv"
}

# ──────────────────────────────────────────────────────────────
puts "\n=== §3 PS-7 configuration ==="
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
if {[llength $ps7] == 0} {
    puts "  WARNING: no PS-7 cell found"
} else {
    puts "  PS-7: $ps7"
    foreach prop {
        PCW_PRESET_BANK0_VOLTAGE PCW_PRESET_BANK1_VOLTAGE
        PCW_USE_S_AXI_HP0 PCW_USE_S_AXI_HP1 PCW_USE_S_AXI_HP2 PCW_USE_S_AXI_HP3
        PCW_USE_M_AXI_GP0 PCW_USE_M_AXI_GP1
        PCW_FPGA0_PERIPHERAL_FREQMHZ PCW_FPGA1_PERIPHERAL_FREQMHZ
        PCW_FPGA2_PERIPHERAL_FREQMHZ PCW_FPGA3_PERIPHERAL_FREQMHZ
        PCW_EN_CLK0_PORT PCW_EN_CLK1_PORT
        PCW_S_AXI_HP0_DATA_WIDTH PCW_S_AXI_HP1_DATA_WIDTH
        PCW_S_AXI_HP0_FREQMHZ
        PCW_PRESET_BANK0_FREQMHZ
        PCW_UART0_PERIPHERAL_ENABLE PCW_UART0_UART0_IO
        PCW_UART_PERIPHERAL_FREQMHZ
        PCW_CRYSTAL_PERIPHERAL_FREQMHZ
        PCW_ARM_PLL_CTRL_FBDIV PCW_IO_PLL_CTRL_FBDIV PCW_DDR_PLL_CTRL_FBDIV
        PCW_FCLK_CLK0_BUF PCW_FCLK_CLK1_BUF
    } {
        catch {set v [get_property CONFIG.$prop $ps7]; puts "  CONFIG.$prop = $v"}
    }
}

# ──────────────────────────────────────────────────────────────
puts "\n=== §4 CGRA IP config ==="
foreach cell [get_bd_cells] {
    set vlnv [get_property VLNV $cell]
    if {[string match "*cgra*" $vlnv] || [string match "*CGRA*" $vlnv]} {
        puts "  $cell ($vlnv)"
        foreach prop {C_BASEADDR C_HIGHADDR C_S_APB_BASEADDR C_M_AXI_DATA_WIDTH C_S_APB_DATA_WIDTH} {
            catch {set v [get_property CONFIG.$prop $cell]; puts "    CONFIG.$prop = $v"}
        }
    }
}

# ──────────────────────────────────────────────────────────────
puts "\n=== §5 Interface connections (relevant ones) ==="
foreach intf [get_bd_intf_nets] {
    set pins [get_bd_intf_pins -of_objects $intf]
    set src ""
    set dst ""
    foreach pin $pins {
        if {[get_property MODE $pin] eq "Master"} { set src $pin } else { set dst $pin }
    }
    if {$src eq ""} { set src [lindex $pins 0] }
    if {$dst eq ""} { set dst [lindex $pins 1] }
    set intf_short [file tail $intf]
    set src_short  [string map {"/" "/"} $src]
    set dst_short  [string map {"/" "/"} $dst]
    puts "  $intf_short:  $src_short  -->  $dst_short"
}

# ──────────────────────────────────────────────────────────────
puts "\n=== §6 Critical signal nets (clocks/resets) ==="
foreach net [get_bd_nets] {
    set name [get_property NAME $net]
    if {[regexp -nocase {clk|rst|reset} $name]} {
        set pins [get_bd_pins -of_objects $net]
        puts "  $name: [llength $pins] pins"
        foreach p $pins { puts "    - $p" }
    }
}

# ──────────────────────────────────────────────────────────────
puts "\n=== §7 Address map ==="
foreach seg [get_bd_addr_segs] {
    set offset [get_property OFFSET $seg]
    set range  [get_property RANGE $seg]
    puts "  $seg  @  $offset  size=$range"
}

# ──────────────────────────────────────────────────────────────
puts "\n=== §8 System ILA / debug cells ==="
set ilas [get_bd_cells -filter {VLNV =~ "*system_ila*"}]
if {[llength $ilas] == 0} {
    puts "  (no system_ila in BD)"
} else {
    foreach ila $ilas {
        puts "  $ila"
        catch {puts "    NUM_OF_PROBES=[get_property CONFIG.C_NUM_OF_PROBES $ila]"}
        # Show probes
        foreach intf [get_bd_intf_pins -of_objects $ila] {
            puts "    intf-pin: $intf"
        }
    }
}

# ──────────────────────────────────────────────────────────────
puts "\n=== §9 Timing summary (impl_1 if available) ==="
set impl [get_runs -filter {IS_IMPLEMENTATION}]
foreach r $impl {
    set state [get_property STATUS $r]
    puts "  $r  state=$state"
    if {$state eq "Implementation Complete"} {
        catch {
            open_run $r
            report_timing_summary -no_header -file /tmp/ts_summary.rpt
            close_design
            puts "    Timing summary at /tmp/ts_summary.rpt"
        }
    }
}

close_bd_design [get_bd_designs]
close_project
puts ""
puts "==========================================================="
puts " INSPECT COMPLETE"
puts "==========================================================="
exit
