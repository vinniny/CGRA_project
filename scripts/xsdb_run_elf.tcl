# ==============================================================================
# xsdb_run_elf.tcl — Load and run bare-metal ELF on Zynq ARM Cortex-A9
# ==============================================================================
# Usage:
#   xsdb xsdb_run_elf.tcl <elf_file> [--bit <bitstream>] [--hw-host <host>] [--wait]
#
# Examples:
#   xsdb xsdb_run_elf.tcl ../07_sw/build/lpr_demo
#   xsdb xsdb_run_elf.tcl ../07_sw/build/lpr_demo --bit ../bitstreams/cgra_top.bit
#   xsdb xsdb_run_elf.tcl ../07_sw/build/test --wait
# ==============================================================================

set elf_file   ""
set bit_file   ""
set hw_host    "localhost"
set hw_port    3121
set wait_mode  0
set script_dir [file dirname [info script]]
set cgra_base  0x43C00000

# --------------------------------------------------------------------------
# Parse arguments
# --------------------------------------------------------------------------
for {set i 0} {$i < $argc} {incr i} {
    set arg [lindex $argv $i]
    switch -- $arg {
        "--bit"     { incr i; set bit_file [lindex $argv $i] }
        "--hw-host" { incr i; set hw_host  [lindex $argv $i] }
        "--hw-port" { incr i; set hw_port  [lindex $argv $i] }
        "--wait"    { set wait_mode 1 }
        default {
            if {$elf_file eq ""} {
                set elf_file $arg
            } else {
                puts "ERROR: Unknown argument: $arg"
                exit 1
            }
        }
    }
}

if {[info exists ::env(XSDB_HW_HOST)]} { set hw_host $::env(XSDB_HW_HOST) }
if {[info exists ::env(XSDB_HW_PORT)]} { set hw_port $::env(XSDB_HW_PORT) }

# Validate
if {$elf_file eq ""} {
    puts "ERROR: No ELF file specified."
    puts "Usage: xsdb xsdb_run_elf.tcl <elf_file> \[--bit <bitstream>\] \[--wait\]"
    exit 1
}
if {![file exists $elf_file]} {
    puts "ERROR: ELF not found: $elf_file"
    exit 1
}
if {$bit_file ne "" && ![file exists $bit_file]} {
    puts "ERROR: Bitstream not found: $bit_file"
    exit 1
}

puts "=========================================================================="
puts " XSDB Run ELF — Zynq-7000 Bare-Metal Execution"
puts "=========================================================================="
puts " ELF File  : $elf_file"
puts " Bitstream : [expr {$bit_file ne "" ? $bit_file : "(skip — assume PL already programmed)"}]"
puts " HW Server : ${hw_host}:${hw_port}"
puts " Wait Mode : [expr {$wait_mode ? "YES (block until processor stops)" : "NO"}]"
puts "=========================================================================="

# --------------------------------------------------------------------------
# Connect to hw_server
# --------------------------------------------------------------------------
puts "\n\[1/6\] Connecting to hw_server..."
if {[catch {connect -host $hw_host -port $hw_port} err]} {
    puts "ERROR: Cannot connect to hw_server: $err"
    exit 1
}
puts "  Connected."

# --------------------------------------------------------------------------
# Find targets
# --------------------------------------------------------------------------
puts "\n\[2/6\] Scanning JTAG chain..."
set target_list [targets]
puts "$target_list"

set fpga_id ""
set arm_id  ""
foreach line [split $target_list "\n"] {
    if {[regexp {^\s*(\d+)\*?\s+} $line -> id]} {
        if {[regexp -nocase {xc7z} $line]}              { set fpga_id $id }
        if {[regexp -nocase {Cortex-A9.*#0} $line]} { set arm_id $id }
    }
}

if {$arm_id eq ""} {
    puts "ERROR: ARM Cortex-A9 #0 not found in JTAG chain."
    disconnect
    exit 1
}

# --------------------------------------------------------------------------
# Program PL (optional)
# --------------------------------------------------------------------------
if {$bit_file ne ""} {
    puts "\n\[3/6\] Programming PL..."
    if {$fpga_id ne ""} { targets $fpga_id }
    if {[catch {fpga -file $bit_file} err]} {
        puts "ERROR: FPGA programming failed: $err"
        disconnect
        exit 1
    }
    after 1000
    puts "  PL programmed."
} else {
    puts "\n\[3/6\] Skipping PL programming (no --bit)."
}

# --------------------------------------------------------------------------
# Initialize PS
# --------------------------------------------------------------------------
puts "\n\[4/6\] Initializing PS..."
targets $arm_id

# Stop processor
puts "  Stopping processor..."
catch {stop}
after 200

# ps7_init
set ps7_init_path [file join $script_dir ps7_init.tcl]
if {![file exists $ps7_init_path]} {
    puts "ERROR: ps7_init.tcl not found at $ps7_init_path"
    puts "  Export from Vivado: File > Export > Export Hardware"
    puts "  Copy ps7_init.tcl to scripts/ directory"
    puts "  Cannot run ELF without PS initialization."
    disconnect
    exit 1
}

puts "  Running ps7_init..."
source $ps7_init_path
if {[catch {ps7_init} err]} {
    puts "ERROR: ps7_init failed: $err"
    disconnect
    exit 1
}
if {[catch {ps7_post_config} err]} {
    puts "  WARNING: ps7_post_config: $err (may be optional)"
}
puts "  PS initialized."

# --------------------------------------------------------------------------
# Load ELF
# --------------------------------------------------------------------------
puts "\n\[5/6\] Loading ELF: $elf_file"
if {[catch {dow $elf_file} err]} {
    puts "ERROR: Failed to load ELF: $err"
    disconnect
    exit 1
}
puts "  ELF loaded."

# --------------------------------------------------------------------------
# Run
# --------------------------------------------------------------------------
puts "\n\[6/6\] Starting execution..."
con

if {$wait_mode} {
    puts "  Waiting for processor to stop (breakpoint/exit)..."
    # Poll processor state — timeout after 60 seconds
    set timeout_ms 60000
    set poll_ms    500
    set elapsed    0
    while {$elapsed < $timeout_ms} {
        after $poll_ms
        incr elapsed $poll_ms
        # Check if processor stopped
        set state [targets -filter {name =~ "*Cortex-A9*#0*"} -target-properties]
        if {[regexp -nocase {stopped|halted} $state]} {
            puts "  Processor stopped after ${elapsed}ms."
            # Read PC
            if {[catch {set pc [rrd pc]} err]} {
                puts "  PC: unknown"
            } else {
                puts "  PC: $pc"
            }
            break
        }
    }
    if {$elapsed >= $timeout_ms} {
        puts "  TIMEOUT: Processor still running after ${timeout_ms}ms."
        puts "  Stopping processor..."
        catch {stop}
    }

    # Read CGRA result registers
    puts "\n  --- CGRA Results ---"
    foreach {name offset} {RESULT_DATA 0x40 RESULT_STATUS 0x44 RESULT_ROW0 0x58 RESULT_ROW1 0x5C RESULT_ROW2 0x60 RESULT_ROW3 0x64} {
        set addr [expr {$cgra_base + $offset}]
        if {[catch {set val [mrd -value $addr]} err]} {
            puts [format "  %-16s = READ_ERROR" $name]
        } else {
            puts [format "  %-16s = 0x%08X (%d)" $name $val $val]
        }
    }
} else {
    puts "  ELF running. Use 'make fpga_status' to check results."
}

puts "\n=========================================================================="
puts " ELF deployment complete"
puts "=========================================================================="

disconnect
exit 0
