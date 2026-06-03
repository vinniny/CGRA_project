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
# Reference: 06_doc/hdmi/hdmi_in_plan.md
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
set IP_VDMA   [_pick_ip xilinx.com   ip   axi_vdma]
set IP_CONST  [_pick_ip xilinx.com   ip   xlconstant]
# PROVEN PYNQ framing IPs (from base.tcl capture chain):
#   color_swap  — RGB byte-order fixer; bridges dvi2rgb/RGB -> v_vid_in/vid_io_in
#                 via the vid_io INTERFACE (not error-prone direct pins).
#   pixel_pack  — HLS 24b->32b repacker that PRESERVES the AXIS SOF(tuser)/
#                 EOL(tlast) sidebands the VDMA needs to delimit frames
#                 (axis_subset_converter dropped them -> DMAIntErr, frozen
#                 capture, silicon 2026-06-03).
set IP_CSWAP  [_pick_ip xilinx.com   user color_swap]
set IP_PIXPK  [_pick_ip xilinx.com   hls  pixel_pack]

puts "  IPs:"
foreach v {IP_DVI2 IP_VTC IP_VIDIN IP_CSWAP IP_PIXPK IP_VDMA} {
    puts [format "    %-10s = %s" $v [set $v]]
}

# ----- 1. Enable FCLK_CLK2=200 (dvi2rgb RefClk) + FCLK_CLK3=142.857 (capture) --
# TWO clocks needed:
#   FCLK2 = 200 MHz  -> dvi2rgb RefClk ONLY (IDELAYCTRL needs ~200 MHz).
#   FCLK3 = 142.857  -> capture AXIS domain (v_vid_in aclk + pixel_pack ap_clk
#                       + vdma_1 s_axis + smartconnect aclk1).  This is the
#                       PROVEN PYNQ base.tcl capture frequency (1000/7, a clean
#                       IO-PLL divisor).  Running the capture domain at 200 MHz
#                       VIOLATED timing (clk_fpga_2 WNS=-0.281, 86 endpoints, the
#                       pixel_pack + 50->200 smartconnect crossing); 142.857 MHz
#                       (7 ns vs 5 ns) closes it with ~2 ns margin and still
#                       exceeds the 124 Mpix/s active 1080p rate (v_vid_in async
#                       FIFO absorbs the instantaneous 148.5 MHz, as PYNQ proves).
puts "\n=== 1. PS7: FCLK_CLK2=200 (dvi2rgb RefClk) + FCLK_CLK3=142.857 (capture) ==="
set_property -dict [list \
    CONFIG.PCW_EN_CLK2_PORT             {1} \
    CONFIG.PCW_FPGA2_PERIPHERAL_FREQMHZ {200} \
    CONFIG.PCW_FCLK_CLK2_BUF            {TRUE} \
    CONFIG.PCW_EN_CLK3_PORT             {1} \
    CONFIG.PCW_FPGA3_PERIPHERAL_FREQMHZ {142.857143} \
    CONFIG.PCW_FCLK_CLK3_BUF            {TRUE} \
] [get_bd_cells processing_system7_0]

# Reset for the 200 MHz dvi2rgb RefClk domain (CDC bookkeeping).
create_bd_cell -type ip -vlnv $IP_RST rst_ps7_0_200M
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK2]     [get_bd_pins rst_ps7_0_200M/slowest_sync_clk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_RESET0_N] [get_bd_pins rst_ps7_0_200M/ext_reset_in]

# Reset for the 142.857 MHz capture AXIS domain (drives v_vid_in/pixel_pack aresetns).
create_bd_cell -type ip -vlnv $IP_RST rst_ps7_0_143M
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK3]     [get_bd_pins rst_ps7_0_143M/slowest_sync_clk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_RESET0_N] [get_bd_pins rst_ps7_0_143M/ext_reset_in]

# ----- 2. Expand control fabric (ps7_0_axi_periph) NUM_MI 4 → 7 ----------
# M04 axi_vdma_1, M05 v_tc_1, M06 pixel_pack/s_axi_control.
# ps7_0_axi_periph is a SMARTCONNECT (not axi_interconnect) → no per-MI ACLK
# pins.  pixel_pack's s_axi_control runs on its single ap_clk = FCLK3 (142.857
# MHz), so add a 2nd clock domain: NUM_CLKS 1→2, wire aclk1=FCLK3.  SmartConnect
# auto-associates each MI to whichever provided aclk matches the connected
# IP's clock (M06→142.857 via aclk1; M00-M05 stay on aclk=50).
puts "\n=== 2. Expand ps7_0_axi_periph NUM_MI 4 → 7, NUM_CLKS 1 → 2 ==="
set_property -dict [list CONFIG.NUM_MI {7} CONFIG.NUM_CLKS {2}] [get_bd_cells ps7_0_axi_periph]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK3] [get_bd_pins ps7_0_axi_periph/aclk1]

# ----- 3. Expand smartconnect_1 NUM_SI 1 → 2 (HP1 also serves vdma_1) ----
puts "\n=== 3. Expand smartconnect_1 NUM_SI 1 → 2 (HP1 carries CGRA + vdma_1) ==="
set_property -dict [list CONFIG.NUM_SI {2} CONFIG.NUM_CLKS {2}] \
    [get_bd_cells smartconnect_1]

# ----- 4. dvi2rgb_0 ------------------------------------------------------
puts "\n=== 4. dvi2rgb_0 (J10 TMDS → 24b RGB, recovers PixelClk) ==="
create_bd_cell -type ip -vlnv $IP_DVI2 dvi2rgb_0
# EDID EMULATION = the final piece of the PROVEN PYNQ recipe.  Without a sink
# EDID the laptop sends a no-EDID signal (often CVT reduced-blanking at 1080p
# 148.5 MHz) that dvi2rgb on the XC7Z020-1 cannot VERTICALLY lock — silicon
# 2026-06-03: v_tc detector saw h~1920 but vsize jittered 1..31, never locked.
# Baking a 720p EDID forces the laptop to a clean standard 1280x720@60 mode
# (74.25 MHz, half the rate, generous blanking) that dvi2rgb locks reliably.
#   kEmulateDDC   = true            -> serve the EDID over the DDC I2C slave
#   kEdidFileName = dgl_720p_cea.data -> 1280x720@60 (this dvi2rgb's stock 720p
#                   EDID; valid set is dgl_1080p_cea / dgl_1280_1024_cea /
#                   dgl_720p_cea — NOT the PYNQ '720p_edid.data' name)
#   kClkRange     = 1               -> 25-80 MHz TMDS clock band (720p=74.25)
set_property -dict [list \
    CONFIG.kEmulateDDC      {true} \
    CONFIG.kEdidFileName    {dgl_720p_cea.data} \
    CONFIG.kRstActiveHigh   {false} \
    CONFIG.kAddBUFG         {true} \
    CONFIG.kClkRange        {1} \
] [get_bd_cells dvi2rgb_0]

# Reference clock (200 MHz, drives the internal IDELAYCTRL)
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK2] [get_bd_pins dvi2rgb_0/RefClk]
# DDC (I2C slave that serves the EDID) -> external iic port -> board HDMI-RX DDC
# pins (U14 scl / U15 sda, set in constrs_pynq_z2.xdc).  Creates inout ports
# hdmi_rx_ddc_scl_io / hdmi_rx_ddc_sda_io.  Without this the laptop cannot READ
# the emulated EDID and the forced-720p mechanism does nothing.
set _ddcport [create_bd_intf_port -mode Master -vlnv xilinx.com:interface:iic_rtl:1.0 hdmi_rx_ddc]
connect_bd_intf_net [get_bd_intf_pins dvi2rgb_0/DDC] $_ddcport
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
connect_bd_intf_net [get_bd_intf_pins ps7_0_axi_periph/M05_AXI] [get_bd_intf_pins v_tc_1/ctrl]
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
# Match the proven PYNQ base.tcl config exactly: C_ADDR_WIDTH=12 + async clk.
set_property -dict [list \
    CONFIG.C_ADDR_WIDTH {12} \
    CONFIG.C_HAS_ASYNC_CLK {1} \
    CONFIG.C_PIXELS_PER_CLOCK {1} \
    CONFIG.C_M_AXIS_VIDEO_FORMAT {2} \
] [get_bd_cells v_vid_in_axi4s_0]

# Clock domains (matches PYNQ base.tcl: v_vid_in/aclk on the 142.857 MHz video
# clock, NOT a slow PS clock):
#   vid_io_in_clk = dvi2rgb PixelClk  (~148.5MHz @1080p, pixel domain)
#   aclk          = FCLK_CLK3 = 142.857MHz (AXIS domain) — async FIFO PixelClk->143
# 142.857MHz is PYNQ's proven capture rate; > the 124 Mpix/s active 1080p rate,
# and the async FIFO absorbs the instantaneous 148.5MHz over blanking.  (200MHz
# violated timing on this domain; 50MHz could not drain at all -> capture froze.)
connect_bd_net [get_bd_pins dvi2rgb_0/PixelClk]                 [get_bd_pins v_vid_in_axi4s_0/vid_io_in_clk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK3]     [get_bd_pins v_vid_in_axi4s_0/aclk]
connect_bd_net [get_bd_pins rst_ps7_0_143M/peripheral_aresetn]  [get_bd_pins v_vid_in_axi4s_0/aresetn]
# vid_io_in_reset is ACTIVE_HIGH on this IP — use peripheral_reset (the
# active-high sibling of peripheral_aresetn from the same proc_sys_reset).
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_reset]    [get_bd_pins v_vid_in_axi4s_0/vid_io_in_reset]

# Parallel input from dvi2rgb via color_swap + the vid_io INTERFACE — EXACTLY
# as the proven PYNQ base.tcl does it (NOT direct pins, which risk active_video/
# sync mis-mapping or polarity inversion -> no valid framing -> frozen capture).
#   dvi2rgb/RGB  -> color_swap/pixel_input   (rbg)
#   color_swap/pixel_output (rgb) -> v_vid_in/vid_io_in
create_bd_cell -type ip -vlnv $IP_CSWAP color_swap_in
set_property -dict [list \
    CONFIG.input_format  {rbg} \
    CONFIG.output_format {rgb} \
] [get_bd_cells color_swap_in]
connect_bd_intf_net [get_bd_intf_pins dvi2rgb_0/RGB]            [get_bd_intf_pins color_swap_in/pixel_input]
connect_bd_intf_net [get_bd_intf_pins color_swap_in/pixel_output] [get_bd_intf_pins v_vid_in_axi4s_0/vid_io_in]
# Detected timing flows FROM v_vid_in_axi4s_0 TO v_tc_1 (which reports
# htotal/vtotal/active to PS via AXI-Lite ctrl regs at 0x43C9_0000).
connect_bd_intf_net [get_bd_intf_pins v_vid_in_axi4s_0/vtiming_out] [get_bd_intf_pins v_tc_1/vtiming_in]
# vid_io_in_ce / vid_io_in_clk_en: tie to constant 1 (we don't gate the pixel clock)
create_bd_cell -type ip -vlnv $IP_CONST xlconst_vidin_ce
set_property -dict [list CONFIG.CONST_VAL {1} CONFIG.CONST_WIDTH {1}] [get_bd_cells xlconst_vidin_ce]
connect_bd_net [get_bd_pins xlconst_vidin_ce/dout] [get_bd_pins v_vid_in_axi4s_0/vid_io_in_ce]
connect_bd_net [get_bd_pins xlconst_vidin_ce/dout] [get_bd_pins v_vid_in_axi4s_0/axis_enable]

# ----- 7. pixel_pack (HLS 24b → 32b, PRESERVES tuser/tlast) --------------
puts "\n=== 7. pixel_pack (AXIS 24b → 32b, preserves SOF/EOL sidebands) ==="
# The PROVEN PYNQ repacker. Interfaces: stream_in_24 (S), stream_out_32 (M),
# s_axi_control (AXI-Lite: ap_start/auto_restart + 'mode' pixel-format reg).
# It has ONE ap_clk for both stream and control, so it lives in the 142.857 MHz
# capture domain (matching v_vid_in/video_out); its AXI-Lite control crosses
# 50->142.857 internally on the ps7_0_axi_periph smartconnect (aclk1).
create_bd_cell -type ip -vlnv $IP_PIXPK pixel_pack_in
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK3]     [get_bd_pins pixel_pack_in/ap_clk]
connect_bd_net [get_bd_pins rst_ps7_0_143M/peripheral_aresetn]  [get_bd_pins pixel_pack_in/ap_rst_n]
connect_bd_intf_net [get_bd_intf_pins v_vid_in_axi4s_0/video_out] [get_bd_intf_pins pixel_pack_in/stream_in_24]
# AXI-Lite control on ps7_0_axi_periph M06.  SmartConnect crosses 50->142.857
# internally; M06 is auto-associated to aclk1=FCLK3 (wired in step 2) because
# pixel_pack's s_axi_control clock is FCLK3.
connect_bd_intf_net [get_bd_intf_pins ps7_0_axi_periph/M06_AXI] [get_bd_intf_pins pixel_pack_in/s_axi_control]

# ----- 8. axi_vdma_1 (S2MM only, 3-frame ring) ---------------------------
puts "\n=== 8. axi_vdma_1 (S2MM-only, 3-frame ring on HP1) ==="
create_bd_cell -type ip -vlnv $IP_VDMA axi_vdma_1
# c_s_axis_s2mm_tdata_width is derived from c_s_axi_s2mm_data_width — setting
# it explicitly raised [BD 41-737] read-only. Default 32-bit matches the
# pixel_pack stream_out_32 output, so we let it default.
set_property -dict [list \
    CONFIG.c_include_mm2s          {0} \
    CONFIG.c_include_s2mm          {1} \
    CONFIG.c_s2mm_linebuffer_depth {2048} \
    CONFIG.c_s2mm_max_burst_length {64} \
    CONFIG.c_num_fstores           {3} \
    CONFIG.c_include_internal_genlock {0} \
] [get_bd_cells axi_vdma_1]

connect_bd_intf_net [get_bd_intf_pins ps7_0_axi_periph/M04_AXI] [get_bd_intf_pins axi_vdma_1/S_AXI_LITE]
# S2MM AXIS from pixel_pack (24→32, sidebands preserved)
connect_bd_intf_net [get_bd_intf_pins pixel_pack_in/stream_out_32] [get_bd_intf_pins axi_vdma_1/S_AXIS_S2MM]
# S2MM MM goes to HP1 via smartconnect_1 S01_AXI (S00 already used by CGRA)
connect_bd_intf_net [get_bd_intf_pins axi_vdma_1/M_AXI_S2MM] [get_bd_intf_pins smartconnect_1/S01_AXI]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]    [get_bd_pins axi_vdma_1/s_axi_lite_aclk]
# BANDWIDTH FIX (Gemini sweep + matches PYNQ): the S2MM memory-write side must
# NOT run at FCLK0=50 MHz.  At 32-bit that's only 200 MB/s — BELOW the ~221 MB/s
# a 720p60 frame needs -> linebuffer overflow -> capture freeze (the same freeze
# we chased).  Move m_axi to FCLK1=100 MHz (-> 400 MB/s, 1.8x margin).
# smartconnect_1/aclk1 is ALREADY FCLK1=100, so S01 auto-associates with no
# smartconnect change; HP1 port stays 50 MHz x 64-bit = 400 MB/s (also > 221).
# (PYNQ runs this whole path at 142.857; 100 MHz is sufficient for 720p.)
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK1]    [get_bd_pins axi_vdma_1/m_axi_s2mm_aclk]
# S2MM AXIS write side on the 142.857MHz capture domain (matches pixel_pack
# output).  VDMA auto-detects async (s_axis 142.857 vs m_axi 100 vs lite 50;
# log confirms "configuring AXI-VDMA in ASYNC mode").
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK3]    [get_bd_pins axi_vdma_1/s_axis_s2mm_aclk]
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

# DDC SCL/SDA are NO LONGER plain IO ports — dvi2rgb_0/DDC is now an iic_rtl
# interface (kEmulateDDC=true) brought out as the external port 'hdmi_rx_ddc'
# in step 4, creating inout hdmi_rx_ddc_scl_io / hdmi_rx_ddc_sda_io.  The XDC
# (constrs_pynq_z2.xdc) maps those to U14/U15.  No tie-off needed.

# ----- 11. Address map (input chain new entries) ------------------------
puts "\n=== 11. Address map: input VDMA, v_tc_1, pixel_pack_in, DDR map for S2MM ==="
assign_bd_address [get_bd_addr_segs {axi_vdma_1/S_AXI_LITE/Reg}]
set_property offset 0x43020000 [get_bd_addr_segs {processing_system7_0/Data/SEG_axi_vdma_1_Reg}]
set_property range  64K        [get_bd_addr_segs {processing_system7_0/Data/SEG_axi_vdma_1_Reg}]

assign_bd_address [get_bd_addr_segs {v_tc_1/ctrl/Reg}]
set_property offset 0x43C90000 [get_bd_addr_segs {processing_system7_0/Data/SEG_v_tc_1_Reg}]

# pixel_pack control (HLS s_axi_control: ap_start/auto_restart + mode reg).
# HLS auto-names the PS-side segment unpredictably (SEG_pixel_pack_in_Reg vs
# ..._s_axi_control_Reg), so locate it by glob after assignment.
assign_bd_address [get_bd_addr_segs {pixel_pack_in/s_axi_control/Reg}]
set _ppseg [get_bd_addr_segs -filter {NAME =~ "SEG_pixel_pack_in*"} \
                processing_system7_0/Data/*]
set_property offset 0x43C40000 $_ppseg
set_property range  64K        $_ppseg

# vdma_1 S2MM access into DDR via HP1.
# Use -target_address_space form: the master-side SEG_X name only exists
# AFTER assignment, so passing it as a literal to get_bd_addr_segs trips
# [BD 5-699].
assign_bd_address -target_address_space /axi_vdma_1/Data_S2MM \
    [get_bd_addr_segs processing_system7_0/S_AXI_HP1/HP1_DDR_LOWOCM]

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
