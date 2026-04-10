# ==============================================================================
# xsdb_regmap.tcl — CGRA APB register read/write/dump via XSDB
# ==============================================================================
# Usage:
#   xsdb xsdb_regmap.tcl read  <REG_NAME>
#   xsdb xsdb_regmap.tcl write <REG_NAME> <VALUE>
#   xsdb xsdb_regmap.tcl dump
#
# Examples:
#   xsdb xsdb_regmap.tcl read DMA_STATUS
#   xsdb xsdb_regmap.tcl write DMA_SRC 0x10000000
#   xsdb xsdb_regmap.tcl dump
# ==============================================================================

set hw_host   "localhost"
set hw_port   3121
set cgra_base 0x43C00000

if {[info exists ::env(XSDB_HW_HOST)]} { set hw_host $::env(XSDB_HW_HOST) }
if {[info exists ::env(XSDB_HW_PORT)]} { set hw_port $::env(XSDB_HW_PORT) }

# Strip --hw-host / --hw-port from argv before command parsing
set clean_argv {}
for {set i 0} {$i < $argc} {incr i} {
    set arg [lindex $argv $i]
    switch -- $arg {
        "--hw-host" { incr i; set hw_host [lindex $argv $i] }
        "--hw-port" { incr i; set hw_port [lindex $argv $i] }
        default     { lappend clean_argv $arg }
    }
}
set argv $clean_argv
set argc [llength $argv]

# --------------------------------------------------------------------------
# Register map: name -> {offset access}
# --------------------------------------------------------------------------
array set regs {
    DMA_CTRL       {0x00 RW}
    DMA_STATUS     {0x04 RO}
    DMA_SRC        {0x08 RW}
    DMA_DST        {0x0C RW}
    DMA_SIZE       {0x10 RW}
    DMA_SRC_STRIDE {0x14 RW}
    DMA_ROWS       {0x18 RW}
    DMA_COLS       {0x1C RW}
    CU_CTRL        {0x20 RW}
    CU_STATUS      {0x24 RO}
    CU_CYCLES      {0x28 RO}
    CU_TIMEOUT     {0x2C RW}
    IRQ_STATUS     {0x30 W1C}
    IRQ_MASK       {0x34 RW}
    DMA_ERROR      {0x38 RO}
    RESULT_DATA    {0x40 RO}
    RESULT_STATUS  {0x44 RO}
    LOOP_START     {0x48 RW}
    LOOP_END       {0x4C RW}
    LOOP_COUNT     {0x50 RW}
    RESULT_ROW0    {0x58 RO}
    RESULT_ROW1    {0x5C RO}
    RESULT_ROW2    {0x60 RO}
    RESULT_ROW3    {0x64 RO}
    LOOP2_START    {0x68 RW}
    LOOP2_END      {0x6C RW}
    LOOP2_COUNT    {0x70 RW}
    TILE_BANK_SEL  {0x74 RW}
}

# Ordered list for dump
set reg_order {
    DMA_CTRL DMA_STATUS DMA_SRC DMA_DST DMA_SIZE DMA_SRC_STRIDE DMA_ROWS DMA_COLS
    CU_CTRL CU_STATUS CU_CYCLES CU_TIMEOUT
    IRQ_STATUS IRQ_MASK DMA_ERROR
    RESULT_DATA RESULT_STATUS
    LOOP_START LOOP_END LOOP_COUNT
    RESULT_ROW0 RESULT_ROW1 RESULT_ROW2 RESULT_ROW3
    LOOP2_START LOOP2_END LOOP2_COUNT
    TILE_BANK_SEL
}

# --------------------------------------------------------------------------
# Parse command
# --------------------------------------------------------------------------
if {$argc < 1} {
    puts "Usage: xsdb xsdb_regmap.tcl <read|write|dump> \[REG_NAME\] \[VALUE\]"
    puts ""
    puts "Registers:"
    foreach name $reg_order {
        set info $regs($name)
        puts [format "  %-16s  %s  %s" $name [lindex $info 0] [lindex $info 1]]
    }
    exit 1
}

set cmd [lindex $argv 0]

# --------------------------------------------------------------------------
# Connect + find ARM target
# --------------------------------------------------------------------------
if {[catch {connect -host $hw_host -port $hw_port} err]} {
    puts "ERROR: Cannot connect to hw_server: $err"
    exit 1
}

set arm_id ""
foreach line [split [targets] "\n"] {
    if {[regexp {^\s*(\d+)\*?\s+} $line -> id]} {
        if {[regexp -nocase {Cortex-A9.*#0} $line]} { set arm_id $id }
    }
}
if {$arm_id eq ""} {
    puts "ERROR: ARM Cortex-A9 not found"
    disconnect
    exit 1
}
targets $arm_id
configparams force-mem-accesses 1

# --------------------------------------------------------------------------
# Execute command
# --------------------------------------------------------------------------
switch -- $cmd {
    "read" {
        if {$argc < 2} {
            puts "Usage: xsdb xsdb_regmap.tcl read <REG_NAME>"
            disconnect
            exit 1
        }
        set name [string toupper [lindex $argv 1]]
        if {![info exists regs($name)]} {
            puts "ERROR: Unknown register: $name"
            disconnect
            exit 1
        }
        set offset [lindex $regs($name) 0]
        set addr [expr {$cgra_base + $offset}]
        if {[catch {set val [mrd -value $addr]} err]} {
            puts "ERROR: Read failed at [format 0x%08X $addr]: $err"
            disconnect
            exit 1
        }
        puts [format "%s (0x%02X) = 0x%08X (%d)" $name $offset $val $val]
    }

    "write" {
        if {$argc < 3} {
            puts "Usage: xsdb xsdb_regmap.tcl write <REG_NAME> <VALUE>"
            disconnect
            exit 1
        }
        set name [string toupper [lindex $argv 1]]
        set value [lindex $argv 2]
        if {![info exists regs($name)]} {
            puts "ERROR: Unknown register: $name"
            disconnect
            exit 1
        }
        set access [lindex $regs($name) 1]
        if {$access eq "RO"} {
            puts "ERROR: $name is read-only"
            disconnect
            exit 1
        }
        set offset [lindex $regs($name) 0]
        set addr [expr {$cgra_base + $offset}]
        if {[catch {mwr $addr $value} err]} {
            puts "ERROR: Write failed at [format 0x%08X $addr]: $err"
            disconnect
            exit 1
        }
        # Read back
        if {[catch {set rb [mrd -value $addr]} err]} {
            puts [format "%s (0x%02X) <= 0x%08X (readback failed)" $name $offset $value]
        } else {
            puts [format "%s (0x%02X) <= 0x%08X (readback: 0x%08X)" $name $offset $value $rb]
        }
    }

    "dump" {
        puts "=========================================================================="
        puts " CGRA Register Dump — Base [format 0x%08X $cgra_base]"
        puts "=========================================================================="
        puts [format "  %-16s  %-6s  %-3s  %s" "REGISTER" "OFFSET" "R/W" "VALUE"]
        puts "  ---------------------------------------------------------------"
        foreach name $reg_order {
            set info   $regs($name)
            set offset [lindex $info 0]
            set access [lindex $info 1]
            set addr   [expr {$cgra_base + $offset}]

            if {[catch {set val [mrd -value $addr]} err]} {
                puts [format "  %-16s  %-6s  %-3s  READ_ERROR" $name $offset $access]
            } else {
                puts [format "  %-16s  %-6s  %-3s  0x%08X  (%d)" $name $offset $access $val $val]
            }
        }
        puts "=========================================================================="
    }

    default {
        puts "ERROR: Unknown command: $cmd (use read, write, or dump)"
        disconnect
        exit 1
    }
}

disconnect
exit 0
