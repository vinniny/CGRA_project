# ==============================================================================
# xsdb_status.tcl — Read FPGA state + dump all 28 CGRA APB registers
# ==============================================================================
# Usage:
#   xsdb xsdb_status.tcl [--hw-host <host>] [--hw-port <port>]
# ==============================================================================

set hw_host "localhost"
set hw_port 3121
set cgra_base 0x43C00000

for {set i 0} {$i < $argc} {incr i} {
    set arg [lindex $argv $i]
    switch -- $arg {
        "--hw-host" { incr i; set hw_host [lindex $argv $i] }
        "--hw-port" { incr i; set hw_port [lindex $argv $i] }
    }
}
if {[info exists ::env(XSDB_HW_HOST)]} { set hw_host $::env(XSDB_HW_HOST) }
if {[info exists ::env(XSDB_HW_PORT)]} { set hw_port $::env(XSDB_HW_PORT) }

# --------------------------------------------------------------------------
# Register map (offset, name, access, decode_proc)
# --------------------------------------------------------------------------
set regmap {
    {0x00 DMA_CTRL      RW ""}
    {0x04 DMA_STATUS    RO "decode_dma_status"}
    {0x08 DMA_SRC       RW ""}
    {0x0C DMA_DST       RW ""}
    {0x10 DMA_SIZE      RW ""}
    {0x14 DMA_SRC_STRIDE RW ""}
    {0x18 DMA_ROWS      RW ""}
    {0x1C DMA_COLS      RW ""}
    {0x20 CU_CTRL       RW ""}
    {0x24 CU_STATUS     RO "decode_cu_status"}
    {0x28 CU_CYCLES     RO ""}
    {0x2C CU_TIMEOUT    RW ""}
    {0x30 IRQ_STATUS    W1C "decode_irq_status"}
    {0x34 IRQ_MASK      RW "decode_irq_mask"}
    {0x38 DMA_ERROR     RO "decode_dma_error"}
    {0x40 RESULT_DATA   RO ""}
    {0x44 RESULT_STATUS RO "decode_result_status"}
    {0x48 LOOP_START    RW ""}
    {0x4C LOOP_END      RW ""}
    {0x50 LOOP_COUNT    RW ""}
    {0x58 RESULT_ROW0   RO ""}
    {0x5C RESULT_ROW1   RO ""}
    {0x60 RESULT_ROW2   RO ""}
    {0x64 RESULT_ROW3   RO ""}
    {0x68 LOOP2_START   RW ""}
    {0x6C LOOP2_END     RW ""}
    {0x70 LOOP2_COUNT   RW ""}
    {0x74 TILE_BANK_SEL RW ""}
}

# --------------------------------------------------------------------------
# Decode helpers
# --------------------------------------------------------------------------
proc decode_dma_status {val} {
    set busy [expr {$val & 0x1}]
    set done [expr {($val >> 1) & 0x1}]
    return "busy=$busy done=$done"
}
proc decode_cu_status {val} {
    set busy [expr {$val & 0x1}]
    set done [expr {($val >> 1) & 0x1}]
    return "busy=$busy done=$done"
}
proc decode_irq_status {val} {
    set dma_done [expr {$val & 0x1}]
    set cu_done  [expr {($val >> 1) & 0x1}]
    set dma_err  [expr {($val >> 2) & 0x1}]
    return "dma_done=$dma_done cu_done=$cu_done dma_error=$dma_err"
}
proc decode_irq_mask {val} {
    set dma_en [expr {$val & 0x1}]
    set cu_en  [expr {($val >> 1) & 0x1}]
    return "dma_done_en=$dma_en cu_done_en=$cu_en"
}
proc decode_dma_error {val} {
    set flag [expr {$val & 0x1}]
    set code [expr {($val >> 1) & 0x3}]
    return "error_flag=$flag error_code=$code"
}
proc decode_result_status {val} {
    set valid [expr {$val & 0x1}]
    return "result_valid=$valid"
}

# --------------------------------------------------------------------------
# Connect
# --------------------------------------------------------------------------
puts "=========================================================================="
puts " XSDB Status — Zynq-7000 CGRA Register Dump"
puts "=========================================================================="
puts " HW Server : ${hw_host}:${hw_port}"
puts " CGRA Base : [format 0x%08X $cgra_base]"
puts "=========================================================================="

puts "\nConnecting to hw_server..."
if {[catch {connect -host $hw_host -port $hw_port} err]} {
    puts "ERROR: Cannot connect to hw_server: $err"
    exit 1
}

# --------------------------------------------------------------------------
# JTAG chain + PL state
# --------------------------------------------------------------------------
puts "\n--- JTAG Targets ---"
set target_list [targets]
puts $target_list

# Find FPGA and ARM targets
set fpga_id ""
set arm_id  ""
foreach line [split $target_list "\n"] {
    if {[regexp {^\s*(\d+)\*?\s+} $line -> id]} {
        if {[regexp -nocase {xc7z} $line]}              { set fpga_id $id }
        if {[regexp -nocase {Cortex-A9.*#0} $line]} { set arm_id $id }
    }
}

puts "\n--- PL Configuration State ---"
if {$fpga_id ne ""} {
    targets $fpga_id
    if {[catch {set pl_state [fpga -state]} err]} {
        puts "  PL State: UNKNOWN ($err)"
    } else {
        puts "  PL State: $pl_state"
    }
} else {
    puts "  WARNING: xc7z target not found in JTAG chain"
}

# --------------------------------------------------------------------------
# Register dump via ARM DAP
# --------------------------------------------------------------------------
puts "\n--- CGRA APB Register Dump ---"
if {$arm_id eq ""} {
    puts "  WARNING: ARM Cortex-A9 not found — cannot read registers"
} else {
    targets $arm_id
    configparams force-mem-accesses 1

    puts [format "  %-4s  %-16s  %-3s  %-12s  %s" "OFF" "REGISTER" "R/W" "VALUE" "DECODE"]
    puts "  ---------------------------------------------------------------"

    foreach entry $regmap {
        set offset   [lindex $entry 0]
        set name     [lindex $entry 1]
        set access   [lindex $entry 2]
        set decode   [lindex $entry 3]

        set addr [expr {$cgra_base + $offset}]

        if {[catch {set val [mrd -value $addr]} err]} {
            puts [format "  %-4s  %-16s  %-3s  %-12s  %s" $offset $name $access "READ_ERROR" $err]
            continue
        }

        set hex_val [format "0x%08X" $val]
        set decoded ""
        if {$decode ne ""} {
            set decoded [eval $decode $val]
        }

        puts [format "  %-4s  %-16s  %-3s  %-12s  %s" $offset $name $access $hex_val $decoded]
    }
}

puts "\n=========================================================================="
puts " Status dump complete"
puts "=========================================================================="

disconnect
exit 0
