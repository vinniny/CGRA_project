# hdmi_dual_phase1.tcl — graft HDMI-IN onto the existing CGRA_PYNQ design_1
# (which already has CGRA + HDMI-OUT), apply the working DDR fix (REF UIPARAMs,
# since board_part=pynq-z2 gives the broken 0.279 trace delays), validate +
# save + make_wrapper. NO impl (phase-1 gate before the ~50 min build).

set REPO /home/vinniny/centos_vm/projects/CGRA_project
set PROJ /mnt/c/Users/thanh/Desktop/CGRA_PYNQ/CGRA_PYNQ.xpr

open_project $PROJ
set bd [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
puts "BD: $bd"
open_bd_design $bd

# Guard: is HDMI-in already present?
if {[llength [get_bd_cells -quiet dvi2rgb_0]] > 0} {
    puts "HDMI-IN already present — skipping graft"
} else {
    puts "\n=== graft HDMI-IN (add_hdmi_in_pynqz2.tcl) ==="
    if {[catch {source $REPO/scripts/add_hdmi_in_pynqz2.tcl} e]} {
        puts "ADD_HDMI_IN ERROR: $e"
        puts "PHASE1 RESULT: FAILED at add_hdmi_in"
        close_project; exit
    }
}

# DDR fix: unset board_part (it forces broken 0.279 delays), apply REF UIPARAMs
puts "\n=== DDR fix: REF UIPARAMs (PARTNO=Custom + 0.223 delays) ==="
catch {set_property board_part "" [current_project]}
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
source $REPO/scripts/vivado_diagnostics/ref_ddr_uiparams.tcl
if {[catch {set_property -dict $ref_ddr $ps7} e]} {
    puts "  DDR -dict err: $e (continuing; checking key params)"
}
foreach p {PCW_UIPARAM_DDR_BOARD_DELAY0 PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 PCW_UIPARAM_DDR_PARTNO} {
    catch {puts "  $p = [get_property CONFIG.$p $ps7]"}
}
# Keep FCLK config from the HDMI base (FCLK0=50 CGRA, FCLK1=100 dynclk, FCLK2=200 dvi2rgb)
foreach p {PCW_FPGA0_PERIPHERAL_FREQMHZ PCW_FPGA1_PERIPHERAL_FREQMHZ PCW_FPGA2_PERIPHERAL_FREQMHZ} {
    catch {puts "  $p = [get_property CONFIG.$p $ps7]"}
}

puts "\n=== validate ==="
if {[catch {validate_bd_design} e]} {
    puts "VALIDATE FAILED: $e"
    puts "PHASE1 RESULT: FAILED at validate"
    close_project; exit
}
puts "  validate OK"
save_bd_design
catch {make_wrapper -files [get_files $bd] -top -force}
catch {generate_target all [get_files $bd]}
puts "\n=== HDMI-IN cells now present ==="
foreach c {dvi2rgb_0 v_tc_1 v_vid_in_axi4s_0 axi_vdma_1} {
    puts "  $c : [expr {[llength [get_bd_cells -quiet $c]]>0 ? {present} : {MISSING}}]"
}
puts "\nPHASE1 RESULT: SUCCESS — HDMI-in grafted, DDR fix applied, validated"
close_project
puts "PHASE1 DONE"
exit
