# =============================================================================
# add_hdmi_in_pynqz2.tcl
#
# Additive Vivado script that grafts an HDMI input chain onto the existing
# CGRA+HDMI-OUT block design built by `build_cgra_hdmi_pynqz2_clean.tcl`.
#
# End state after sourcing:
#   - dvi2rgb_0     (J10 TMDS → parallel RGB + recovered pixel clock)
#   - v_tc_1        (detector mode, hsync/vsync from dvi2rgb pixel domain)
#   - v_vid_in_axi4s_0 (parallel video to AXIS video, vsync-aligned)
#   - axis_subset_converter_in (AXIS 24b → 32b zero-pad for VDMA write side,
#                               replaces PYNQ-HLS pixel_pack which isn't in
#                               the standard Xilinx catalog)
#   - axi_vdma_1    (S2MM-only, 3-frame ring at 0x1F80_0000)
#   - Detector clock = dvi2rgb PixelClk; AXIS-MM clock = FCLK_CLK0
#   - VDMA S2MM ↔ HP1 (shares with CGRA m_axi via smartconnect_1, NUM_SI=2)
#   - AXI-Lite control fabric (ps7_0_axi_periph) expanded NUM_MI 5 → 7
#       M05 axi_vdma_1
#       M06 v_tc_1
#       (subset_converter is config-time only, no AXI-Lite slave)
#   - dvi2rgb RefClk = FCLK_CLK2 (200 MHz, enabled here on PS7)
#   - IRQ_F2P xlconcat extended 3 → 4 ports (In3 = vdma_1 s2mm_introut)
#
# Run order:
#   1. Source build_cgra_hdmi_pynqz2_clean.tcl (creates design_1, the output side)
#   2. (without closing the BD) source THIS file
#   3. validate_bd_design ; save_bd_design
#   4. make_wrapper + add updated constrs_pynq_z2.xdc (already includes J10 LOCs)
#   5. launch_runs synth_1 ; wait_on_run synth_1
#   6. launch_runs impl_1 -to_step write_bitstream ; wait_on_run impl_1
#
# Reference: 06_doc/hdmi_in_plan.md
# =============================================================================

puts "==========================================================="
puts " ADD HDMI-IN CHAIN (graft onto cgra_pynq_base design_1)"
puts "==========================================================="

# ----- 0. Sanity ---------------------------------------------------------
if {[catch {current_bd_design} cur_bd]} {
    error "No open BD. Source build_cgra_hdmi_pynqz2_clean.tcl first, then this."
}
puts "  BD in scope: $cur_bd"

foreach req {processing_system7_0 ps7_0_axi_periph smartconnect_1
             rst_ps7_0_100M xlconcat_0} {
    if {[llength [get_bd_cells $req]] == 0} {
        error "Required cell '$req' not found. Base BD missing — rebuild first."
    }
}

# Pick latest IPs (same helper as base script)
proc _pick_ip {vendor library name} {
    set cands [get_ipdefs -filter "VLNV =~ \"$vendor:$library:$name:*\""]
    if {[llength $cands] == 0} {
        error "No IP $vendor:$library:$name. Check ip_repo_paths."
    }
    return [lindex [lsort -decreasing -dictionary $cands] 0]
}
set IP_RST    [_pick_ip xilinx.com   ip   proc_sys_reset]
set IP_DVI2   [_pick_ip digilentinc.com ip dvi2rgb]
set IP_VTC    [_pick_ip xilinx.com   ip   v_tc]
set IP_VIDIN  [_pick_ip xilinx.com   ip   v_vid_in_axi4s]
set IP_SUBCV  [_pick_ip xilinx.com   ip   axis_subset_converter]
set IP_VDMA   [_pick_ip xilinx.com   ip   axi_vdma]
set IP_CONST  [_pick_ip xilinx.com   ip   xlconstant]

puts "  IPs:"
foreach v {IP_DVI2 IP_VTC IP_VIDIN IP_SUBCV IP_VDMA} {
    puts [format "    %-10s = %s" $v [set $v]]
}

# ----- 1. Enable FCLK_CLK2 at 200 MHz (dvi2rgb RefClk requirement) -------
puts "\n=== 1. PS7: enable FCLK_CLK2 = 200 MHz for dvi2rgb RefClk ==="
set_property -dict [list \
    CONFIG.PCW_EN_CLK2_PORT             {1} \
    CONFIG.PCW_FPGA2_PERIPHERAL_FREQMHZ {200} \
    CONFIG.PCW_FCLK_CLK2_BUF            {TRUE} \
] [get_bd_cells processing_system7_0]

# A dedicated reset for the 200 MHz domain is not strictly required (dvi2rgb's
# RefClk only feeds IDELAYCTRL which is async to RefClk's reset edge), but
# add one for clean CDC bookkeeping in implementation.
create_bd_cell -type ip -vlnv $IP_RST rst_ps7_0_200M
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK2]     [get_bd_pins rst_ps7_0_200M/slowest_sync_clk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_RESET0_N] [get_bd_pins rst_ps7_0_200M/ext_reset_in]

# ----- 2. Expand control fabric (ps7_0_axi_periph) NUM_MI 5 → 7 ----------
puts "\n=== 2. Expand ps7_0_axi_periph NUM_MI 5 → 7 ==="
set_property CONFIG.NUM_MI {7} [get_bd_cells ps7_0_axi_periph]

# ----- 3. Expand smartconnect_1 NUM_SI 1 → 2 (HP1 also serves vdma_1) ----
puts "\n=== 3. Expand smartconnect_1 NUM_SI 1 → 2 (HP1 carries CGRA + vdma_1) ==="
set_property -dict [list CONFIG.NUM_SI {2} CONFIG.NUM_CLKS {2}] \
    [get_bd_cells smartconnect_1]

# ----- 4. dvi2rgb_0 ------------------------------------------------------
puts "\n=== 4. dvi2rgb_0 (J10 TMDS → 24b RGB, recovers PixelClk) ==="
create_bd_cell -type ip -vlnv $IP_DVI2 dvi2rgb_0
# Common config:
#   kEmulateDDC = false (we are not emulating an EDID DDC slave here yet — board's
#       passive pull-ups are sufficient for a laptop that already cached EDID)
#   kRstActiveHigh = false  (we use active-low resets everywhere)
#   kAddBUFG = true (so PixelClk drives a global buffer that downstream IPs can use)
set_property -dict [list \
    CONFIG.kEmulateDDC      {false} \
    CONFIG.kRstActiveHigh   {false} \
    CONFIG.kAddBUFG         {true} \
    CONFIG.kClkRange        {2} \
] [get_bd_cells dvi2rgb_0]

# Reference clock (200 MHz, drives the internal IDELAYCTRL)
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK2] [get_bd_pins dvi2rgb_0/RefClk]
# Active-low reset shared with the 100 MHz fabric domain (release is gated by
# the 200M reset internally for the IDELAYCTRL)
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn] [get_bd_pins dvi2rgb_0/aRst_n]

# ----- 5. v_tc_1 in detector mode ----------------------------------------
puts "\n=== 5. v_tc_1 (detector mode, clocked on dvi2rgb PixelClk) ==="
create_bd_cell -type ip -vlnv $IP_VTC v_tc_1
# Detection-only: v_tc_1 observes the vtiming_out interface emitted by
# v_vid_in_axi4s_0 (which itself extracts timing from dvi2rgb sync signals).
# Detected htotal/vtotal/active are reported back to PS via AXI-Lite at
# 0x43C9_0000 — that's how the SW driver decides "source locked".
set_property -dict [list \
    CONFIG.enable_generation {false} \
    CONFIG.enable_detection  {true} \
] [get_bd_cells v_tc_1]
connect_bd_intf_net [get_bd_intf_pins ps7_0_axi_periph/M06_AXI] [get_bd_intf_pins v_tc_1/ctrl]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]     [get_bd_pins v_tc_1/s_axi_aclk]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn]  [get_bd_pins v_tc_1/s_axi_aresetn]
# Detector clock = recovered PixelClk from dvi2rgb
connect_bd_net [get_bd_pins dvi2rgb_0/PixelClk]                 [get_bd_pins v_tc_1/clk]
# Reset for the pixel-clock side of v_tc — leave at hi (no reset wire); the IP
# tolerates a free-run as long as ctrl regs are not active

# Wiring v_tc_1 inputs is done after v_vid_in_axi4s_0 is created (step 6),
# since the detected vtiming comes from v_vid_in_axi4s_0's vtiming_out
# interface, not from dvi2rgb sync signals directly. See step 6.

# ----- 6. v_vid_in_axi4s_0 (parallel → AXIS) -----------------------------
puts "\n=== 6. v_vid_in_axi4s_0 (parallel RGB → AXIS, aligned to v_tc_1 timing) ==="
create_bd_cell -type ip -vlnv $IP_VIDIN v_vid_in_axi4s_0
set_property -dict [list \
    CONFIG.C_HAS_ASYNC_CLK {1} \
    CONFIG.C_PIXELS_PER_CLOCK {1} \
    CONFIG.C_M_AXIS_VIDEO_FORMAT {2} \
] [get_bd_cells v_vid_in_axi4s_0]

# Clock domains:
#   vid_io_in_clk = dvi2rgb PixelClk  (pixel domain)
#   aclk          = FCLK_CLK0         (memory/AXIS domain) — async crossing inside IP
connect_bd_net [get_bd_pins dvi2rgb_0/PixelClk]                 [get_bd_pins v_vid_in_axi4s_0/vid_io_in_clk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]     [get_bd_pins v_vid_in_axi4s_0/aclk]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn]  [get_bd_pins v_vid_in_axi4s_0/aresetn]
# vid_io_in_reset is ACTIVE_HIGH on this IP — use peripheral_reset (the
# active-high sibling of peripheral_aresetn from the same proc_sys_reset).
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_reset]    [get_bd_pins v_vid_in_axi4s_0/vid_io_in_reset]

# Parallel input from dvi2rgb (24-bit RGB + hsync/vsync/VDE).
# Direct pin connections (Vivado warns about overriding the vid_io_in interface
# bundle — non-fatal; the bundle is reconstructed by the connection).
connect_bd_net [get_bd_pins dvi2rgb_0/vid_pData]  [get_bd_pins v_vid_in_axi4s_0/vid_data]
connect_bd_net [get_bd_pins dvi2rgb_0/vid_pHSync] [get_bd_pins v_vid_in_axi4s_0/vid_hsync]
connect_bd_net [get_bd_pins dvi2rgb_0/vid_pVSync] [get_bd_pins v_vid_in_axi4s_0/vid_vsync]
connect_bd_net [get_bd_pins dvi2rgb_0/vid_pVDE]   [get_bd_pins v_vid_in_axi4s_0/vid_active_video]
# Detected timing flows FROM v_vid_in_axi4s_0 TO v_tc_1 (which reports
# htotal/vtotal/active to PS via AXI-Lite ctrl regs at 0x43C9_0000).
connect_bd_intf_net [get_bd_intf_pins v_vid_in_axi4s_0/vtiming_out] [get_bd_intf_pins v_tc_1/vtiming_in]
# vid_io_in_ce / vid_io_in_clk_en: tie to constant 1 (we don't gate the pixel clock)
create_bd_cell -type ip -vlnv $IP_CONST xlconst_vidin_ce
set_property -dict [list CONFIG.CONST_VAL {1} CONFIG.CONST_WIDTH {1}] [get_bd_cells xlconst_vidin_ce]
connect_bd_net [get_bd_pins xlconst_vidin_ce/dout] [get_bd_pins v_vid_in_axi4s_0/vid_io_in_ce]
connect_bd_net [get_bd_pins xlconst_vidin_ce/dout] [get_bd_pins v_vid_in_axi4s_0/axis_enable]

# ----- 7. axis_subset_converter_in (AXIS 24b → 32b, byte-padded) --------
puts "\n=== 7. axis_subset_converter_in (AXIS 24b → 32b zero-pad) ==="
create_bd_cell -type ip -vlnv $IP_SUBCV axis_subset_converter_in
# 3-byte (24-bit) in, 4-byte (32-bit) out, with the high byte forced to 0.
# Remap string syntax: <tdata-out-msb..lsb> = <expr in source bits>
set_property -dict [list \
    CONFIG.S_TDATA_NUM_BYTES   {3} \
    CONFIG.M_TDATA_NUM_BYTES   {4} \
    CONFIG.TDATA_REMAP         {8'b00000000,tdata[23:0]} \
    CONFIG.HAS_TKEEP           {0} \
    CONFIG.HAS_TLAST           {1} \
    CONFIG.HAS_TUSER           {1} \
    CONFIG.S_HAS_TSTRB         {0} \
    CONFIG.M_HAS_TSTRB         {0} \
] [get_bd_cells axis_subset_converter_in]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]     [get_bd_pins axis_subset_converter_in/aclk]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn]  [get_bd_pins axis_subset_converter_in/aresetn]
connect_bd_intf_net [get_bd_intf_pins v_vid_in_axi4s_0/video_out] [get_bd_intf_pins axis_subset_converter_in/S_AXIS]

# ----- 8. axi_vdma_1 (S2MM only, 3-frame ring) ---------------------------
puts "\n=== 8. axi_vdma_1 (S2MM-only, 3-frame ring on HP1) ==="
create_bd_cell -type ip -vlnv $IP_VDMA axi_vdma_1
set_property -dict [list \
    CONFIG.c_include_mm2s          {0} \
    CONFIG.c_include_s2mm          {1} \
    CONFIG.c_s2mm_linebuffer_depth {2048} \
    CONFIG.c_s2mm_max_burst_length {64} \
    CONFIG.c_num_fstores           {3} \
    CONFIG.c_include_internal_genlock {0} \
    CONFIG.c_s_axis_s2mm_tdata_width {32} \
] [get_bd_cells axi_vdma_1]

connect_bd_intf_net [get_bd_intf_pins ps7_0_axi_periph/M05_AXI] [get_bd_intf_pins axi_vdma_1/S_AXI_LITE]
# S2MM AXIS from subset_converter (24→32 padded)
connect_bd_intf_net [get_bd_intf_pins axis_subset_converter_in/M_AXIS] [get_bd_intf_pins axi_vdma_1/S_AXIS_S2MM]
# S2MM MM goes to HP1 via smartconnect_1 S01_AXI (S00 already used by CGRA)
connect_bd_intf_net [get_bd_intf_pins axi_vdma_1/M_AXI_S2MM] [get_bd_intf_pins smartconnect_1/S01_AXI]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]    [get_bd_pins axi_vdma_1/s_axi_lite_aclk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]    [get_bd_pins axi_vdma_1/m_axi_s2mm_aclk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]    [get_bd_pins axi_vdma_1/s_axis_s2mm_aclk]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn] [get_bd_pins axi_vdma_1/axi_resetn]

# ----- 9. IRQ_F2P: extend xlconcat 3 → 4 ports (vdma_1 s2mm done) --------
puts "\n=== 9. xlconcat_0: add In3 = vdma_1 s2mm_introut ==="
set_property CONFIG.NUM_PORTS {4} [get_bd_cells xlconcat_0]
connect_bd_net [get_bd_pins axi_vdma_1/s2mm_introut] [get_bd_pins xlconcat_0/In3]

# ----- 10. External HDMI-RX ports (matching constrs_pynq_z2.xdc J10) ----
puts "\n=== 10. External HDMI-RX ports + DDC pull-ups ==="
create_bd_port -dir I hdmi_rx_clk_p
create_bd_port -dir I hdmi_rx_clk_n
create_bd_port -dir I -from 2 -to 0 hdmi_rx_d_p
create_bd_port -dir I -from 2 -to 0 hdmi_rx_d_n
connect_bd_net [get_bd_ports hdmi_rx_clk_p] [get_bd_pins dvi2rgb_0/TMDS_Clk_p]
connect_bd_net [get_bd_ports hdmi_rx_clk_n] [get_bd_pins dvi2rgb_0/TMDS_Clk_n]
connect_bd_net [get_bd_ports hdmi_rx_d_p]   [get_bd_pins dvi2rgb_0/TMDS_Data_p]
connect_bd_net [get_bd_ports hdmi_rx_d_n]   [get_bd_pins dvi2rgb_0/TMDS_Data_n]

# Drive HPD = 1 on the J10 connector (tells laptop a sink is plugged in)
create_bd_port -dir O hdmi_rx_hpd
create_bd_cell -type ip -vlnv $IP_CONST xlconst_rx_hpd_high
set_property -dict [list CONFIG.CONST_VAL {1} CONFIG.CONST_WIDTH {1}] [get_bd_cells xlconst_rx_hpd_high]
connect_bd_net [get_bd_pins xlconst_rx_hpd_high/dout] [get_bd_ports hdmi_rx_hpd]

# CEC: tie low. SCL/SDA: leave as IO ports (high-Z; board pull-ups handle DDC
# read-only for the laptop). When we later add an axi_iic for live EDID emulation,
# wire those ports there instead.
create_bd_port -dir O hdmi_rx_cec
create_bd_cell -type ip -vlnv $IP_CONST xlconst_rx_cec_low
set_property -dict [list CONFIG.CONST_VAL {0} CONFIG.CONST_WIDTH {1}] [get_bd_cells xlconst_rx_cec_low]
connect_bd_net [get_bd_pins xlconst_rx_cec_low/dout] [get_bd_ports hdmi_rx_cec]

create_bd_port -dir IO hdmi_rx_scl
create_bd_port -dir IO hdmi_rx_sda

# Optionally wire dvi2rgb DDC pins (SDA_I/SDA_O/SDA_T, SCL_I/SCL_O/SCL_T) into a
# tristate buffer here. For first bring-up we omit DDC (dvi2rgb's kEmulateDDC=false
# disables internal DDC slave; the laptop sees no EDID and falls back to its
# cached profile, which is fine for the demo).
# Tie unused dvi2rgb DDC pins to safe defaults:
foreach pin {DDC_SDA_I DDC_SCL_I} {
    if {[llength [get_bd_pins dvi2rgb_0/$pin]] > 0} {
        create_bd_cell -type ip -vlnv $IP_CONST [format "xlconst_%s" [string tolower $pin]]
        set_property -dict [list CONFIG.CONST_VAL {1} CONFIG.CONST_WIDTH {1}] \
            [get_bd_cells [format "xlconst_%s" [string tolower $pin]]]
        connect_bd_net [get_bd_pins [format "xlconst_%s/dout" [string tolower $pin]]] \
                       [get_bd_pins dvi2rgb_0/$pin]
    }
}

# ----- 11. Address map (input chain new entries) ------------------------
puts "\n=== 11. Address map: input VDMA, v_tc_1, pixel_pack_in, DDR map for S2MM ==="
assign_bd_address [get_bd_addr_segs {axi_vdma_1/S_AXI_LITE/Reg }]
set_property offset 0x43020000 [get_bd_addr_segs {processing_system7_0/Data/SEG_axi_vdma_1_Reg}]
set_property range  64K        [get_bd_addr_segs {processing_system7_0/Data/SEG_axi_vdma_1_Reg}]

assign_bd_address [get_bd_addr_segs {v_tc_1/ctrl/Reg }]
set_property offset 0x43C90000 [get_bd_addr_segs {processing_system7_0/Data/SEG_v_tc_1_Reg}]

# subset_converter is config-time only — no AXI-Lite address needed.

# vdma_1 S2MM access into DDR via HP1
assign_bd_address [get_bd_addr_segs {axi_vdma_1/Data_S2MM/SEG_processing_system7_0_HP1_DDR_LOWOCM }]

# ----- 12. Validate + save ----------------------------------------------
puts "\n=== 12. validate_bd_design + save ==="
regenerate_bd_layout
validate_bd_design
save_bd_design

puts ""
puts "==========================================================="
puts " HDMI-IN GRAFT COMPLETE"
puts " Address summary (new):"
puts "   axi_vdma_1                S_AXI_LITE @ 0x4302_0000"
puts "   v_tc_1                    ctrl       @ 0x43C9_0000"
puts "   axis_subset_converter_in              (no AXI-Lite — config at synth time)"
puts "   S2MM target               DDR        @ 0x1F80_0000 (SW-set, 3-frame ring)"
puts ""
puts " Next steps:"
puts "   1. update_compile_order -fileset sources_1"
puts "   2. make_wrapper -files [get_files design_1.bd] -top"
puts "   3. Verify constrs_pynq_z2.xdc already has J10 LOCs (it does as of"
puts "      commit 302e920)."
puts "   4. launch_runs synth_1 ; wait_on_run synth_1"
puts "   5. launch_runs impl_1 -to_step write_bitstream ; wait_on_run impl_1"
puts "   6. open_run impl_1 ; report_utilization -file impl_1_util.rpt"
puts "      → expect ~90% LUTs, < 95%; if higher, run strip_pynq_iops.tcl first."
puts "==========================================================="
