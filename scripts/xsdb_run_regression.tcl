# =============================================================================
# xsdb_run_regression.tcl — Load + run the bare-metal CGRA regression ELF.
#
# Prerequisite: bitstream is already programmed (via Vivado HW Manager GUI:
# Program Device → C:\Users\thanh\Desktop\FPGA_CGRA\cgra_ip.runs\impl_1\design_1_wrapper.bit).
# DONE LED on the board should be lit.
#
# This script:
#   1. Connects to hw_server via Vivado HW Manager (Tools → XSDB Console)
#   2. Initializes PS7 via ps7_init.tcl
#   3. Downloads the ELF + sets PC to entry point
#   4. Resumes the ARM core
#   5. Caller monitors UART separately
#
# Usage from Vivado XSDB console (Tools → XSDB Console):
#   source /mnt/c/Users/thanh/Desktop/FPGA_CGRA/scripts/xsdb_run_regression.tcl
# (or copy this file to the Windows side and source from there)
#
# Or standalone:
#   xsdb scripts/xsdb_run_regression.tcl <path-to-elf>
# =============================================================================

set elf_path "07_sw/baremetal/cgra_test.elf"
if {[llength $argv] >= 1} { set elf_path [lindex $argv 0] }

puts "==========================================================="
puts " XSDB regression runner — ELF: $elf_path"
puts "==========================================================="

# Connect to local hw_server (xsdb auto-connects if not already)
if {[catch {targets} _err]} {
    puts "Already connected: $_err"
} else {
    if {[llength [targets]] == 0} {
        connect
    }
}

# Find the Cortex-A9 core
set core_idx [targets -filter {name =~ "ARM Cortex-A9 MPCore #0"}]
if {$core_idx eq ""} {
    puts "WARN: ARM Cortex-A9 MPCore #0 not found — listing all targets:"
    targets
    error "No ARM core; abort"
}
targets $core_idx
puts "Selected target: [target]"

# Initialize PS7 (DDR + clocks + MIO from your Vivado-exported ps7_init.tcl)
if {[file exists scripts/ps7_init.tcl]} {
    source scripts/ps7_init.tcl
    ps7_init
    if {[info procs ps7_post_config] ne ""} { ps7_post_config }
    puts "PS7 initialized"
} else {
    puts "WARN: scripts/ps7_init.tcl not found — DDR may not be initialized"
}

# Download ELF + run
if {![file exists $elf_path]} {
    error "ELF not found: $elf_path (build with: cd 07_sw/baremetal && make)"
}
rst -processor
dow $elf_path
puts "Loaded ELF: $elf_path"

con
puts "Resumed core. Monitor UART on /dev/ttyUSB2 @ 115200."
puts "  python3 scripts/uart_monitor.py /dev/ttyUSB2 115200 60"
