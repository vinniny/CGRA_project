# hdmi_dual_build_p1.tcl — from-scratch dual-HDMI-in/out + CGRA BD, PHASE 1
# (assemble BD + DDR fix + constraints + validate; NO impl — gate before the
# ~50-60 min build).
#
# Flow: create project -> build_cgra_hdmi_pynqz2_clean.tcl (CGRA + HDMI-out)
#       -> add_hdmi_in_pynqz2.tcl (HDMI-in) -> REF DDR UIPARAMs -> constraints
#       -> wrapper -> validate.
set REPO /home/vinniny/centos_vm/projects/CGRA_project
set PROJDIR /home/vinniny/cgra_builds/CGRA_HDMI_DUAL
set PROJ cgra_hdmi_dual
set PART xc7z020clg400-1
set VLIB /mnt/c/Users/thanh/Desktop/vivado-library
set CGRAREPO /mnt/c/Users/thanh/Desktop/FPGA_CGRA
# PYNQ-Z2 base IP repos — supply the PROVEN HDMI-in framing IPs (color_swap,
# pixel_pack) from the silicon-validated base.tcl capture chain. pixel_pack is
# the HLS repacker that (unlike axis_subset_converter) preserves the AXIS
# SOF(tuser)/EOL(tlast) sidebands the VDMA needs to delimit a frame.
set PYNQIP    /mnt/c/Users/thanh/Desktop/PYNQ_repo/boards/ip
set PIXPACKIP /mnt/c/Users/thanh/Desktop/PYNQ_repo/boards/ip/hls/pixel_pack/solution1/impl/ip

file delete -force $PROJDIR
create_project $PROJ $PROJDIR -part $PART -force
catch {set_property board_part tul.com.tw:pynq-z2:part0:1.0 [current_project]}
# VLIB first (matches the known-good timing-met build).  The dvi2rgb that wins
# already ships the stock Digilent EDIDs (dgl_720p_cea.data etc.), so EDID
# emulation works without reordering.  color_swap (PYNQIP) and pixel_pack
# (PIXPACKIP) are uniquely sourced, so repo order doesn't affect them.
set_property ip_repo_paths [list $VLIB $CGRAREPO $PYNQIP $PIXPACKIP] [current_project]
update_ip_catalog
puts "board=[get_property board_part [current_project]] repos set"

# 1. CGRA + HDMI-out BD ------------------------------------------------------
puts "\n=== build_clean (CGRA + HDMI-out) ==="
if {[catch {source $REPO/scripts/build_cgra_hdmi_pynqz2_clean.tcl} e]} {
    puts "BUILD_CLEAN ERROR: $e"; puts "PHASE1 RESULT: FAILED (build_clean)"; exit
}
catch {open_bd_design [get_files design_1.bd]}

# 2. graft HDMI-in -----------------------------------------------------------
puts "\n=== add_hdmi_in ==="
if {[catch {source $REPO/scripts/add_hdmi_in_pynqz2.tcl} e]} {
    puts "ADD_HDMI_IN ERROR: $e"; puts "PHASE1 RESULT: FAILED (add_hdmi_in)"; exit
}

# 3. DDR fix (REF working delays; board preset gives broken 0.279) -----------
puts "\n=== DDR fix ==="
catch {set_property board_part "" [current_project]}
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
source $REPO/scripts/vivado_diagnostics/ref_ddr_uiparams.tcl
catch {set_property -dict $ref_ddr $ps7}
# CRYSTAL=50: board is 50MHz; build_clean defaults PS7 to 33.333 -> 1.5x
# overclock (UART baud + DDR + pixel clocks all wrong).  Set 50 here so the
# from-scratch build is correct (Vivado recomputes PLL FBDIVs to hold FCLK
# targets 50/100/200).  See memory project_hdmi_crystal_root_cause.
catch {set_property CONFIG.PCW_CRYSTAL_PERIPHERAL_FREQMHZ {50} $ps7}
foreach p {PCW_CRYSTAL_PERIPHERAL_FREQMHZ PCW_UIPARAM_DDR_BOARD_DELAY0 PCW_UIPARAM_DDR_DQS_TO_CLK_DELAY_0 PCW_UIPARAM_DDR_PARTNO
           PCW_FPGA0_PERIPHERAL_FREQMHZ PCW_FPGA1_PERIPHERAL_FREQMHZ PCW_FPGA2_PERIPHERAL_FREQMHZ} {
    catch {puts "  $p = [get_property CONFIG.$p $ps7]"}
}

# 4. validate + constraints + wrapper ---------------------------------------
puts "\n=== validate ==="
if {[catch {validate_bd_design} e]} { puts "VALIDATE FAILED: $e"; puts "PHASE1 RESULT: FAILED (validate)"; exit }
puts "  validate OK"
save_bd_design
set bd [get_files design_1.bd]
make_wrapper -files $bd -top -force
add_files -norecurse [file join [get_property DIRECTORY [current_project]] ${PROJ}.gen sources_1 bd design_1 hdl design_1_wrapper.v]
catch {add_files -fileset constrs_1 -norecurse $REPO/01_bench/constrs_pynq_z2.xdc}
set_property top design_1_wrapper [current_fileset]
catch {generate_target all $bd}

puts "\n=== HDMI in/out cells ==="
foreach c {dvi2rgb_0 v_vid_in_axi4s_0 axi_vdma_1 rgb2dvi_0 v_axi4s_vid_out_0 axi_vdma_0 cgra_top_0} {
    puts "  $c : [expr {[llength [get_bd_cells -quiet $c]]>0 ? {present} : {MISSING}}]"
}
puts "\nPHASE1 RESULT: SUCCESS — dual-HDMI BD assembled, DDR fix applied, validated"
puts "PHASE1 DONE"
exit
