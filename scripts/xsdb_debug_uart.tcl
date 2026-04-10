# Debug: check exception registers and re-load ELF
connect -host localhost -port 3121
targets 2
stop
after 300
configparams force-mem-accesses 1

puts "=== CPU State ==="
puts "PC:   [rrd pc]"
puts "CPSR: [rrd cpsr]"
puts "SP:   [rrd sp]"
puts "LR:   [rrd lr]"

# Data Fault Status/Address (only valid if data abort occurred)
# These are CP15 registers — not directly readable via rrd in all XSDB versions
# but let's try reading memory at our ELF load point
puts "\n=== Memory at ELF load point (0x00100000) ==="
targets 2
mrd 0x00100000 16

puts "\n=== Re-loading ELF and setting breakpoint at _start ==="
dow 07_sw/baremetal/cgra_test.elf
after 500

puts "PC after dow: [rrd pc]"
puts "Memory at 0x00100000 after dow:"
mrd 0x00100000 8

# Try to read UART0 (0xE0000000) - simpler peripheral
puts "\n=== UART0 check ==="
if {[catch {
    set val [mrd -value 0xE0000000]
    puts [format "UART0[0x00] = 0x%08X" $val]
} err]} {
    puts "UART0 inaccessible: $err"
}

# Start execution
puts "\n=== Starting ELF ==="
con
after 2000
stop
after 200
puts "PC after 2s run: [rrd pc]"

disconnect
