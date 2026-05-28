# xsdb_per_stage_test.tcl — load the silicon-validated demo_mnist_per_stage
# ELF using the OLD .bit + legacy ps7_init.tcl. This is the EXACT combo
# the thesis cites for FC1+FC2 = 1.50 ms. If it works → bitstream + DMA
# is fine, my smoke ELF has a specific bug. If it hangs → real DMA
# regression somewhere.

connect -url tcp:localhost:3121
configparams force-mem-accesses 1
catch {targets -set -filter {name =~ "DAP*"}}
catch {rst -dap}
after 500

catch {targets -set -filter {name =~ "xc7z020"}}
puts "\n\[1\] Loading bitstreams/cgra_top.bit (OLD silicon-validated) ..."
if {[catch {fpga -file bitstreams/cgra_top.bit} err]} {
    puts "fpga err: $err"
}
after 1000

catch {targets -set -filter {name =~ "ARM*Cortex-A9*#0"}}
catch {stop} e
puts "\n\[2\] stop: '$e'"
after 200

puts "\n\[3\] Sourcing legacy scripts/ps7_init.tcl ..."
source scripts/ps7_init.tcl
catch {ps7_init} e ; puts "  ps7_init: '$e'"
catch {ps7_post_config} e ; puts "  ps7_post_config: '$e'"

puts "\n\[4\] dow 07_sw/baremetal/demo_mnist_per_stage.elf"
if {[catch {dow 07_sw/baremetal/demo_mnist_per_stage.elf} err]} {
    puts "dow err: $err"
    exit 1
}

puts "\n\[5\] con (launch)"
catch {con} e ; puts "  con: '$e'"
puts "ELF running."
exit
