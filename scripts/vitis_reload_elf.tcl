# Light ELF reload — bitstream + ps7_init already live from a prior launch.
# Halt the running demo, download the new ELF, resume. NO fpga -file / ps7_init,
# so this never reprograms the PL (avoids the reprogram-over-running-demo wedge).
proc _e {n d} { if {[info exists ::env($n)]} { return $::env($n) }; return $d }
set ELF [_e CGRA_ELF ""]
connect
after 300
targets -set -filter {name =~ "*Cortex-A9 MPCore #0*"}
catch {stop}
after 200
dow $ELF
after 200
con
puts "ELF reloaded (no PL reprogram)."
exit
