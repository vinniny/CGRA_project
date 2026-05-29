# v18 — CLEAN canonical-flow DDR .xsa. Applies REF's EXACT working DDR
# UIPARAMs (from cgra_rebuilt_from_base/ps7_parameters.xml — the PYNQ base.tcl
# values that actually train on this board) to the cgra_ip PS-7 via
# set_property (tool API, no hand-modding), then rebuilds ONE consistent
# .xsa (bitstream + ps7_init from the same BD state).
#
# board_part stays UNSET: the DDR params are applied EXPLICITLY
# (PARTNO=Custom + full geometry/delays), so no board association is needed
# — which also avoids the psr_aclk board-mismatch lock.
#
# Gate: verify key params took + validate passes BEFORE the (~40 min) impl.

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_top.xsa
set DDR  scripts/vivado_diagnostics/ref_ddr_uiparams.tcl

open_project $PROJ
catch {set_property board_part "" [current_project]}
set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]

# Ensure no IP stays locked (clears any residual part lock)
if {[llength [get_ips -filter {IS_LOCKED}]] > 0} {
    puts "=== upgrade_ip to clear locks ==="
    catch {upgrade_ip [get_ips]}
    catch {close_bd_design [current_bd_design]}; open_bd_design $bd_file
    set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
}

puts "=== apply REF DDR UIPARAMs (set_property -dict) ==="
source $DDR
if {[catch {set_property -dict $ref_ddr $ps7} e]} {
    puts "  -dict failed ($e); per-param fallback:"
    set ok 0; set bad 0
    dict for {k v} $ref_ddr {
        if {[catch {set_property $k $v $ps7} e2]} { puts "    SKIP $k=$v"; incr bad } else { incr ok }
    }
    puts "  applied=$ok skipped=$bad"
} else { puts "  -dict applied OK" }

# Verify the critical values took (these distinguish REF-working from board-file)
puts "\n=== verify key params ==="
set okkey 1
foreach {p exp} {
    PCW_UIPARAM_DDR_BOARD_DELAY0 0.223
    PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 0.040
    PCW_UIPARAM_DDR_DQS_0_LENGTH_MM 15.6
    PCW_UIPARAM_DDR_PARTNO Custom
    PCW_UIPARAM_DDR_USE_INTERNAL_VREF 0
} {
    set got [get_property CONFIG.$p $ps7]
    set match [expr {$got eq $exp}]
    if {!$match} { set okkey 0 }
    puts [format "  %-38s = %-10s (exp %s) %s" $p $got $exp [expr {$match ? {OK} : {MISMATCH}}]]
}
if {!$okkey} { puts "\nABORT: key DDR params did not take"; close_project; exit }

puts "\n=== validate ==="
if {[catch {validate_bd_design} e]} { puts "VALIDATE FAILED: $e"; puts "ABORT"; close_project; exit }
puts "  validate OK"
save_bd_design
catch {reset_target all [get_files $bd_file]}
if {[catch {generate_target all [get_files $bd_file]} e]} { puts "generate FAILED: $e"; puts "ABORT"; close_project; exit }
catch {make_wrapper -files [get_files $bd_file] -top -force}
puts "  generate OK"

# DRC override for floating tmds/ddc ports
set hook /tmp/drc_override.tcl
set fp [open $hook w]
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks NSTD-1\]"
puts $fp "set_property SEVERITY {Warning} \[get_drc_checks UCIO-1\]"
close $fp
set_property STEPS.WRITE_BITSTREAM.TCL.PRE $hook [get_runs impl_1]

puts "\n=== synth + impl + bitstream ==="
catch {reset_run impl_1}; catch {reset_run synth_1}
launch_runs impl_1 -to_step write_bitstream -jobs 6
wait_on_run impl_1
set st [get_property STATUS [get_runs impl_1]]; set prog [get_property PROGRESS [get_runs impl_1]]
puts "  impl_1: $st ($prog)"
if {[string match "*Complete*" $st] && $prog eq "100%"} {
    write_hw_platform -fixed -include_bit -force $XSA
    puts "  Wrote $XSA ([file size $XSA] bytes)"
    puts "V18 BUILD SUCCESS"
} else { puts "V18 BUILD FAILED: $st ($prog)" }
close_project
puts "V18 DONE"
exit
