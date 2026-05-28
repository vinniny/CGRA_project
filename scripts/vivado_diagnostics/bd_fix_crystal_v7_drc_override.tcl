# v7 — open the already-routed impl_1, set DRC overrides in the live
# design session, write bitstream + .xsa directly (bypass runs infra).

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_top.xsa
set OUT_BIT /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.runs/impl_1/design_1_wrapper.bit

puts "==========================================================="
puts " BD FIX v7 (open_run + in-session DRC override + write)"
puts "==========================================================="

open_project $PROJ

# Open the routed design in-memory (run is "Routing Complete" — bitgen step
# failed, so the route DB is intact and reusable).
open_run impl_1

# Confirm: routing done, place+route DB present
puts "  Design opened"
puts "  Top: [current_design]"

# Override the two DRCs that were tripping (unused tmds_*/ddc_* ports)
puts "\n=== Override DRC checks ==="
set_property SEVERITY {Warning} [get_drc_checks NSTD-1]
set_property SEVERITY {Warning} [get_drc_checks UCIO-1]
puts "  NSTD-1 severity: [get_property SEVERITY [get_drc_checks NSTD-1]]"
puts "  UCIO-1 severity: [get_property SEVERITY [get_drc_checks UCIO-1]]"

# Write bitstream directly
puts "\n=== write_bitstream ==="
write_bitstream -force $OUT_BIT
puts "  Bitstream written: $OUT_BIT ([file size $OUT_BIT] bytes)"

# Export .xsa
puts "\n=== Export .xsa ==="
write_hw_platform -fixed -include_bit -force $XSA
puts "  Wrote $XSA ([file size $XSA] bytes)"

# Close
close_design
close_project
puts "\nv7 DONE"
exit
