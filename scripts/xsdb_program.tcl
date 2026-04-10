# ==============================================================================
# xsdb_program.tcl — Program Zynq-7000 PL + optional PS initialization
# ==============================================================================
# Usage:
#   xsdb xsdb_program.tcl <bitstream.bit> [--ps-init] [--hw-host <host>]
#
# Examples:
#   xsdb xsdb_program.tcl ../bitstreams/cgra_top.bit
#   xsdb xsdb_program.tcl ../bitstreams/cgra_top.bit --ps-init
#   xsdb xsdb_program.tcl ../bitstreams/cgra_top.bit --ps-init --hw-host 192.168.1.100
# ==============================================================================

# --------------------------------------------------------------------------
# Parse arguments
# --------------------------------------------------------------------------
set bit_file   ""
set ps_init    0
set hw_host    "localhost"
set hw_port    3121
set script_dir [file dirname [info script]]

for {set i 0} {$i < $argc} {incr i} {
    set arg [lindex $argv $i]
    switch -- $arg {
        "--ps-init" {
            set ps_init 1
        }
        "--hw-host" {
            incr i
            set hw_host [lindex $argv $i]
        }
        "--hw-port" {
            incr i
            set hw_port [lindex $argv $i]
        }
        default {
            if {$bit_file eq ""} {
                set bit_file $arg
            } else {
                puts "ERROR: Unknown argument: $arg"
                exit 1
            }
        }
    }
}

# Override from environment if set
if {[info exists ::env(XSDB_HW_HOST)]} {
    set hw_host $::env(XSDB_HW_HOST)
}
if {[info exists ::env(XSDB_HW_PORT)]} {
    set hw_port $::env(XSDB_HW_PORT)
}
if {[info exists ::env(XSDB_PS_INIT)]} {
    set ps_init $::env(XSDB_PS_INIT)
}

# Validate bitstream path
if {$bit_file eq ""} {
    puts "ERROR: No bitstream file specified."
    puts "Usage: xsdb xsdb_program.tcl <bitstream.bit> \[--ps-init\] \[--hw-host <host>\]"
    exit 1
}
if {![file exists $bit_file]} {
    puts "ERROR: Bitstream not found: $bit_file"
    exit 1
}

puts "=========================================================================="
puts " XSDB Program — Zynq-7000 CGRA Deployment"
puts "=========================================================================="
puts " Bitstream : $bit_file"
puts " PS Init   : [expr {$ps_init ? "YES" : "NO"}]"
puts " HW Server : ${hw_host}:${hw_port}"
puts "=========================================================================="

# --------------------------------------------------------------------------
# Connect to hw_server
# --------------------------------------------------------------------------
puts "\n\[1/5\] Connecting to hw_server at ${hw_host}:${hw_port}..."
if {[catch {connect -host $hw_host -port $hw_port} err]} {
    puts "ERROR: Cannot connect to hw_server: $err"
    puts "  - Is hw_server running? (make hw_server_start)"
    puts "  - Is the JTAG cable connected?"
    puts "  - For remote: HW_HOST=<ip> make program BIT=..."
    exit 1
}
puts "  Connected."

# --------------------------------------------------------------------------
# Scan JTAG chain and find targets
# --------------------------------------------------------------------------
puts "\n\[2/5\] Scanning JTAG chain..."
set target_list [targets]
puts "$target_list"

# Find the FPGA (PL) target — look for xc7z or ARM
set fpga_id ""
set arm_id  ""

# Parse targets output to find IDs
foreach line [split $target_list "\n"] {
    if {[regexp {^\s*(\d+)\*?\s+} $line -> id]} {
        if {[regexp -nocase {xc7z} $line]} {
            set fpga_id $id
        }
        if {[regexp -nocase {Cortex-A9.*#0} $line]} {
            set arm_id $id
        }
    }
}

if {$fpga_id eq ""} {
    puts "WARNING: Could not identify xc7z target. Will try programming anyway."
}

# --------------------------------------------------------------------------
# Program PL
# --------------------------------------------------------------------------
puts "\n\[3/5\] Programming PL with bitstream..."
if {$fpga_id ne ""} {
    targets $fpga_id
}

if {[catch {fpga -file $bit_file} err]} {
    puts "ERROR: FPGA programming failed: $err"
    disconnect
    exit 1
}
puts "  Bitstream loaded."

# Wait for programming to settle
after 1000

# --------------------------------------------------------------------------
# Verify PL state
# --------------------------------------------------------------------------
puts "\n\[4/5\] Verifying PL configuration..."
if {[catch {set pl_state [fpga -state]} err]} {
    puts "WARNING: Could not read FPGA state: $err"
    set pl_state "UNKNOWN"
} else {
    puts "  PL State: $pl_state"
}

# --------------------------------------------------------------------------
# PS initialization (optional)
# --------------------------------------------------------------------------
set cgra_base 0x43C00000

if {$ps_init} {
    puts "\n\[5/5\] Initializing PS (Cortex-A9)..."

    # Check for ps7_init.tcl
    set ps7_init_path [file join $script_dir ps7_init.tcl]
    if {![file exists $ps7_init_path]} {
        puts "WARNING: ps7_init.tcl not found at $ps7_init_path"
        puts "  Export from Vivado: File > Export > Export Hardware"
        puts "  Copy ps7_init.tcl to scripts/ directory"
        puts "  Skipping PS init — PL programmed but registers may not be accessible."
    } else {
        if {$arm_id eq ""} {
            puts "WARNING: Could not find ARM Cortex-A9 target. Skipping PS init."
        } else {
            targets $arm_id
            puts "  Target: ARM Cortex-A9 #0 (ID $arm_id)"

            # Stop the processor
            puts "  Stopping processor..."
            if {[catch {stop} err]} {
                # May already be stopped
            }
            after 200

            # Source and run ps7_init
            puts "  Running ps7_init..."
            if {[catch {source $ps7_init_path} err]} {
                puts "ERROR: Failed to source ps7_init.tcl: $err"
                disconnect
                exit 1
            }
            if {[catch {ps7_init} err]} {
                puts "ERROR: ps7_init failed: $err"
                disconnect
                exit 1
            }
            if {[catch {ps7_post_config} err]} {
                puts "WARNING: ps7_post_config failed (may be optional): $err"
            }
            puts "  PS initialized — AXI GP0 clocks enabled."

            # Enable PL AXI slave port access through DAP
            configparams force-mem-accesses 1

            # Quick sanity read of CGRA base register
            puts "  Sanity check: reading CGRA DMA_CTRL (${cgra_base})..."
            if {[catch {set val [mrd -value $cgra_base]} err]} {
                puts "  WARNING: Register read failed: $err"
                puts "  (PL may need more time or clocking issue)"
            } else {
                puts [format "  DMA_CTRL = 0x%08X  (OK — PL accessible)" $val]
            }
        }
    }
} else {
    puts "\n\[5/5\] PS init skipped (--ps-init not set)."
}

# --------------------------------------------------------------------------
# Summary
# --------------------------------------------------------------------------
puts ""
puts "=========================================================================="
if {[regexp -nocase {done|configured|programmed} $pl_state]} {
    puts " DEPLOY SUCCESS"
} else {
    puts " DEPLOY COMPLETE (PL state: $pl_state — verify with 'make fpga_status')"
}
puts "=========================================================================="

disconnect
exit 0
