# =============================================================================
# build_cgra_hdmi_pynqz2_clean.tcl
#
# Clean rebuild of the CGRA + HDMI BD on PYNQ-Z2, modeled on the Haoyue
# Zynq-7020 reference at /mnt/c/Users/thanh/Desktop/petalinux files/XSA create/
# CGRA_SoC/CGRA_SoC.srcs/sources_1/bd/cgra_SoC_main/cgra_SoC_main.bd which
# was confirmed working (see /notebooklm "RISC-V Acceleration for Post-Quantum
# Cryptography").
#
# Substitutions for PYNQ-Z2 (vs Haoyue):
#   - HDMI_Transmitter (custom Haoyue IP) -> rgb2dvi (Digilent, same function)
#   - PYNQ-Z2 board preset for PS7 DDR / MIO / Ethernet pinout
#   - HDMI constraint file constrs_pynq_z2.xdc (already in 01_bench/)
#
# Verbatim from Haoyue (the parts that fixed our V162-V169 hangs):
#   * PCW_FCLK_CLK0_FREQ = 50 MHz, BUF = TRUE
#     (CGRA's silicon-validated target — 100 MHz violates 25 logic-level
#     DMA path read_words_remaining→m_axi_araddr by -5.155 ns)
#   * PCW_FCLK_CLK1_FREQ = 100 MHz, BUF = TRUE  (axi_dynclk REF_CLK_I expects
#     100 MHz; 150 MHz drove MMCM VCO to 1500 MHz, above the -1 speed grade
#     1200 MHz limit → [DRC AVAL-46] critical violation)
#   * PCW_M_AXI_GP0_FREQMHZ tracks FCLK0 automatically
#   * smartconnect (modern) instead of axi_interconnect 2.1 for HP paths
#   * separate proc_sys_reset for 100M and 150M clock domains
#   * HP0 + HP1 both enabled (one VDMA per HP port -> no contention)
#
# Run order:
#   1. Open Vivado 2024.1 (or later)
#   2. Create project: PYNQ-Z2 board, target xc7z020clg400-1, SystemVerilog
#   3. Add IP repos:
#        set_property ip_repo_paths { \
#          C:/Users/thanh/Desktop/zynq7020_2022/zynq7020/ip_repo \
#          C:/Users/thanh/Desktop/vivado-library/ip \
#        } [current_project]
#        update_ip_catalog
#   4. Add CGRA RTL: 00_src/cgra_top.sv + dependencies, plus any package files
#   5. source <this script>
#   6. Make wrapper, add constrs_pynq_z2.xdc, generate bitstream
# =============================================================================

puts "==========================================================="
puts " CGRA+HDMI clean BD build (Haoyue-modeled, PYNQ-Z2 target)"
puts "==========================================================="

# ----- 0. Sanity ---------------------------------------------------------
if {[catch {current_project} cur]} {
    error "No project open. Create the PYNQ-Z2 project first, then source this."
}
set vivado_ver [version -short]
puts "  Vivado:   $vivado_ver"
puts "  Project:  $cur"
puts "  Part:     [get_property part $cur]"
puts "  Board:    [get_property board_part $cur]"

# Pick latest available version of an IP family. Returns full VLNV.
proc pick_latest_ip {vendor library name} {
    set candidates [get_ipdefs -filter "VLNV =~ \"$vendor:$library:$name:*\""]
    if {[llength $candidates] == 0} {
        error "No IP found matching $vendor:$library:$name. Check ip_repo_paths."
    }
    # Sort by revision descending and return the newest.
    set sorted [lsort -decreasing -dictionary $candidates]
    return [lindex $sorted 0]
}

set IP_PS7    [pick_latest_ip xilinx.com   ip   processing_system7]
set IP_RST    [pick_latest_ip xilinx.com   ip   proc_sys_reset]
set IP_SC     [pick_latest_ip xilinx.com   ip   smartconnect]
set IP_APB    [pick_latest_ip xilinx.com   ip   axi_apb_bridge]
set IP_DYN    [pick_latest_ip digilentinc.com  ip  axi_dynclk]
set IP_VTC    [pick_latest_ip xilinx.com   ip   v_tc]
set IP_VDMA   [pick_latest_ip xilinx.com   ip   axi_vdma]
set IP_VID    [pick_latest_ip xilinx.com   ip   v_axi4s_vid_out]
set IP_RGB    [pick_latest_ip digilentinc.com  ip  rgb2dvi]
set IP_CONST  [pick_latest_ip xilinx.com   ip   xlconstant]
set IP_CONCAT [pick_latest_ip xilinx.com   ip   xlconcat]
set IP_CGRA   [pick_latest_ip xilinx.com   user cgra_top]

puts "  IP versions in use:"
foreach v {IP_PS7 IP_RST IP_SC IP_APB IP_DYN IP_VTC IP_VDMA IP_VID IP_RGB IP_CONST IP_CONCAT IP_CGRA} {
    puts [format "    %-12s = %s" $v [set $v]]
}

set design_name design_1
set bd_path [get_files -quiet ${design_name}.bd]
if {$bd_path ne ""} {
    puts "  BD ${design_name}.bd already exists. Open it instead, or remove first."
    return
}

create_bd_design $design_name
current_bd_design $design_name

# ----- 1. Processing System 7 -------------------------------------------
puts "\n=== 1. Adding processing_system7_0 ==="
create_bd_cell -type ip -vlnv $IP_PS7 processing_system7_0
apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 \
    -config { \
        make_external "FIXED_IO, DDR" \
        apply_board_preset "1" \
        Master "Disable" \
        Slave "Disable" } \
    [get_bd_cells processing_system7_0]

# Override clocks/AXI to Haoyue values.
# (PCW_M_AXI_GP0_FREQMHZ is read-only — it tracks PCW_FPGA0_PERIPHERAL_FREQMHZ
# via the GP0 clock tie. Setting it explicitly triggered [BD 41-737].)
set_property -dict [list \
    CONFIG.PCW_USE_M_AXI_GP0       {1} \
    CONFIG.PCW_USE_S_AXI_HP0       {1} \
    CONFIG.PCW_USE_S_AXI_HP1       {1} \
    CONFIG.PCW_EN_CLK0_PORT        {1} \
    CONFIG.PCW_EN_CLK1_PORT        {1} \
    CONFIG.PCW_EN_CLK2_PORT        {0} \
    CONFIG.PCW_EN_CLK3_PORT        {0} \
    CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ {50}  \
    CONFIG.PCW_FPGA1_PERIPHERAL_FREQMHZ {100} \
    CONFIG.PCW_FCLK_CLK0_BUF       {TRUE} \
    CONFIG.PCW_FCLK_CLK1_BUF       {TRUE} \
    CONFIG.PCW_USE_FABRIC_INTERRUPT {1} \
    CONFIG.PCW_IRQ_F2P_INTR        {1} \
    CONFIG.PCW_UART0_PERIPHERAL_ENABLE  {1} \
    CONFIG.PCW_UART0_UART0_IO           {MIO 14 .. 15} \
    CONFIG.PCW_UART0_BAUD_RATE          {115200} \
    CONFIG.PCW_UART_PERIPHERAL_FREQMHZ  {100} \
    CONFIG.PCW_UART_PERIPHERAL_CLKSRC   {IO PLL} \
    CONFIG.PCW_IOPLL_CTRL_FBDIV         {30} \
    CONFIG.PCW_IO_PLL_FREQMHZ           {1000} \
] [get_bd_cells processing_system7_0]

# ----- 2. Reset blocks (one per clock domain) ----------------------------
puts "\n=== 2. Adding proc_sys_reset for 100M + 150M ==="
create_bd_cell -type ip -vlnv $IP_RST rst_ps7_0_100M
create_bd_cell -type ip -vlnv $IP_RST rst_ps7_0_150M

connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]      [get_bd_pins rst_ps7_0_100M/slowest_sync_clk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK1]      [get_bd_pins rst_ps7_0_150M/slowest_sync_clk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_RESET0_N]  [get_bd_pins rst_ps7_0_100M/ext_reset_in]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_RESET0_N]  [get_bd_pins rst_ps7_0_150M/ext_reset_in]

# ----- 3. AXI Lite control fabric ---------------------------------------
puts "\n=== 3. Adding ps7_0_axi_periph (control fabric) ==="
# Use smartconnect for the control plane -- modern, no AxPROT cache bug.
# 4 masters in the base BD: M00=dynclk, M01=vdma_0, M02=apb_bridge(CGRA),
# M03=v_tc_0. add_hdmi_in_pynqz2.tcl extends NUM_MI to 6 (M04=vdma_1,
# M05=v_tc_1). Contiguous to avoid [BD 41-2670] incomplete-address warnings.
create_bd_cell -type ip -vlnv $IP_SC ps7_0_axi_periph
set_property -dict [list \
    CONFIG.NUM_SI {1} \
    CONFIG.NUM_MI {4} \
    CONFIG.NUM_CLKS {1} \
] [get_bd_cells ps7_0_axi_periph]
connect_bd_intf_net [get_bd_intf_pins processing_system7_0/M_AXI_GP0] [get_bd_intf_pins ps7_0_axi_periph/S00_AXI]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]      [get_bd_pins ps7_0_axi_periph/aclk]
connect_bd_net [get_bd_pins processing_system7_0/M_AXI_GP0_ACLK] [get_bd_pins processing_system7_0/FCLK_CLK0]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn]   [get_bd_pins ps7_0_axi_periph/aresetn]

# ----- 4. HP0 + HP1 smartconnects ---------------------------------------
puts "\n=== 4. Adding smartconnect_0 (HP0) and smartconnect_1 (HP1) ==="
create_bd_cell -type ip -vlnv $IP_SC smartconnect_0
set_property -dict [list CONFIG.NUM_SI {1} CONFIG.NUM_MI {1} CONFIG.NUM_CLKS {2}] [get_bd_cells smartconnect_0]
connect_bd_intf_net [get_bd_intf_pins smartconnect_0/M00_AXI] [get_bd_intf_pins processing_system7_0/S_AXI_HP0]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]   [get_bd_pins smartconnect_0/aclk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK1]   [get_bd_pins smartconnect_0/aclk1]
connect_bd_net [get_bd_pins processing_system7_0/S_AXI_HP0_ACLK] [get_bd_pins processing_system7_0/FCLK_CLK0]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn] [get_bd_pins smartconnect_0/aresetn]

create_bd_cell -type ip -vlnv $IP_SC smartconnect_1
set_property -dict [list CONFIG.NUM_SI {1} CONFIG.NUM_MI {1} CONFIG.NUM_CLKS {2}] [get_bd_cells smartconnect_1]
connect_bd_intf_net [get_bd_intf_pins smartconnect_1/M00_AXI] [get_bd_intf_pins processing_system7_0/S_AXI_HP1]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]   [get_bd_pins smartconnect_1/aclk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK1]   [get_bd_pins smartconnect_1/aclk1]
connect_bd_net [get_bd_pins processing_system7_0/S_AXI_HP1_ACLK] [get_bd_pins processing_system7_0/FCLK_CLK0]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn] [get_bd_pins smartconnect_1/aresetn]

# ----- 5. CGRA + APB bridge ---------------------------------------------
puts "\n=== 5. Adding cgra_top + axi_apb_bridge ==="
# cgra_top is APB-slave, AXI-master, IRQ-out. It must be packaged as an IP
# first via scripts/package_cgra_ip.tcl so the APB ports are grouped under
# the s_apb bus interface and AXI master under m_axi.
create_bd_cell -type ip -vlnv $IP_CGRA cgra_top_0

# AXI-Lite -> APB bridge (PS7 M_AXI_GP0 is AXI-Lite; cgra_top's slave is APB)
create_bd_cell -type ip -vlnv $IP_APB axi_apb_bridge_0
set_property -dict [list \
    CONFIG.C_M_APB_PROTOCOL {apb3} \
    CONFIG.C_APB_NUM_SLAVES {1} \
] [get_bd_cells axi_apb_bridge_0]

# AXI-Lite from periph fabric (M02) -> bridge -> CGRA APB
connect_bd_intf_net [get_bd_intf_pins ps7_0_axi_periph/M02_AXI] [get_bd_intf_pins axi_apb_bridge_0/AXI4_LITE]
connect_bd_intf_net [get_bd_intf_pins axi_apb_bridge_0/APB_M]   [get_bd_intf_pins cgra_top_0/interface_apb]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]    [get_bd_pins axi_apb_bridge_0/s_axi_aclk]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn] [get_bd_pins axi_apb_bridge_0/s_axi_aresetn]

# CGRA clock + reset (active-low, FCLK0 = 100 MHz domain)
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]    [get_bd_pins cgra_top_0/clk]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn] [get_bd_pins cgra_top_0/rst_n]

# CGRA AXI master (DMA) -> smartconnect_1 -> HP1
# (smartconnect_1 already created in section 4; we add CGRA as the SI)
# NB: we route VDMA to HP0 (smartconnect_0) and CGRA DMA to HP1
# so the two masters never contend on the same HP port.
connect_bd_intf_net [get_bd_intf_pins cgra_top_0/m_axi] [get_bd_intf_pins smartconnect_1/S00_AXI]

# ----- 6. HDMI pipeline: VDMA + TC + AXIS -> RGB + dynclk + rgb2dvi ------
puts "\n=== 6. Adding HDMI pipeline IPs ==="
# 6a. axi_dynclk_0
create_bd_cell -type ip -vlnv $IP_DYN axi_dynclk_0
connect_bd_intf_net [get_bd_intf_pins ps7_0_axi_periph/M00_AXI] [get_bd_intf_pins axi_dynclk_0/s00_axi]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK1]    [get_bd_pins axi_dynclk_0/REF_CLK_I]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]    [get_bd_pins axi_dynclk_0/s00_axi_aclk]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn] [get_bd_pins axi_dynclk_0/s00_axi_aresetn]

# 6a'. proc_sys_reset_video — PIXEL clock domain reset.  CRITICAL (silicon-
# confirmed 2026-06-01): v_axi4s_vid_out + rgb2dvi run on PXL_CLK_O; resetting
# them from the 100M-domain reset leaves their pixel-domain logic without a
# clean reset release -> no DE/valid video -> monitor shows "no signal" even
# though dynclk locks, v_tc generates and the VDMA streams.  dcm_locked =
# dynclk LOCKED_O so the video reset deasserts only after PXL_CLK locks.
create_bd_cell -type ip -vlnv $IP_RST proc_sys_reset_video
catch {set_property CONFIG.C_EXT_RESET_HIGH \
    [get_property CONFIG.C_EXT_RESET_HIGH [get_bd_cells rst_ps7_0_100M]] [get_bd_cells proc_sys_reset_video]}
connect_bd_net [get_bd_pins axi_dynclk_0/PXL_CLK_O]             [get_bd_pins proc_sys_reset_video/slowest_sync_clk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_RESET0_N] [get_bd_pins proc_sys_reset_video/ext_reset_in]
connect_bd_net [get_bd_pins axi_dynclk_0/LOCKED_O]             [get_bd_pins proc_sys_reset_video/dcm_locked]

# 6b. v_tc_0 (timing generator only)
create_bd_cell -type ip -vlnv $IP_VTC v_tc_0
set_property CONFIG.enable_detection {false} [get_bd_cells v_tc_0]
connect_bd_intf_net [get_bd_intf_pins ps7_0_axi_periph/M03_AXI] [get_bd_intf_pins v_tc_0/ctrl]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]    [get_bd_pins v_tc_0/s_axi_aclk]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn] [get_bd_pins v_tc_0/s_axi_aresetn]
connect_bd_net [get_bd_pins axi_dynclk_0/PXL_CLK_O]            [get_bd_pins v_tc_0/clk]

# 6c. axi_vdma_0 (24-bit RGB MM2S)
create_bd_cell -type ip -vlnv $IP_VDMA axi_vdma_0
# c_m_axis_mm2s_tdata_width=24 is required to match v_axi4s_vid_out_0/video_in
# (24-bit RGB stream). NOT read-only on MM2S side — only the s2mm variant on
# vdma_1 raises [BD 41-737] because its tdata_width is propagated from
# c_s_axi_s2mm_data_width on this IP version.
set_property -dict [list \
    CONFIG.c_include_s2mm {0} \
    CONFIG.c_m_axis_mm2s_tdata_width {24} \
    CONFIG.c_mm2s_linebuffer_depth {2048} \
    CONFIG.c_mm2s_max_burst_length {64} \
    CONFIG.c_num_fstores {1} \
] [get_bd_cells axi_vdma_0]
connect_bd_intf_net [get_bd_intf_pins ps7_0_axi_periph/M01_AXI] [get_bd_intf_pins axi_vdma_0/S_AXI_LITE]
connect_bd_intf_net [get_bd_intf_pins axi_vdma_0/M_AXI_MM2S]   [get_bd_intf_pins smartconnect_0/S00_AXI]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]    [get_bd_pins axi_vdma_0/s_axi_lite_aclk]
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK0]    [get_bd_pins axi_vdma_0/m_axi_mm2s_aclk]
connect_bd_net [get_bd_pins axi_dynclk_0/PXL_CLK_O]            [get_bd_pins axi_vdma_0/m_axis_mm2s_aclk]
connect_bd_net [get_bd_pins rst_ps7_0_100M/peripheral_aresetn] [get_bd_pins axi_vdma_0/axi_resetn]

# 6d. v_axi4s_vid_out_0
create_bd_cell -type ip -vlnv $IP_VID v_axi4s_vid_out_0
set_property CONFIG.C_HAS_ASYNC_CLK {1} [get_bd_cells v_axi4s_vid_out_0]
connect_bd_intf_net [get_bd_intf_pins axi_vdma_0/M_AXIS_MM2S]  [get_bd_intf_pins v_axi4s_vid_out_0/video_in]
connect_bd_intf_net [get_bd_intf_pins v_tc_0/vtiming_out]      [get_bd_intf_pins v_axi4s_vid_out_0/vtiming_in]
connect_bd_net [get_bd_pins axi_dynclk_0/PXL_CLK_O]            [get_bd_pins v_axi4s_vid_out_0/aclk]
connect_bd_net [get_bd_pins axi_dynclk_0/PXL_CLK_O]            [get_bd_pins v_axi4s_vid_out_0/vid_io_out_clk]
connect_bd_net [get_bd_pins proc_sys_reset_video/peripheral_aresetn] [get_bd_pins v_axi4s_vid_out_0/aresetn]
# CRITICAL (silicon-confirmed 2026-06-01): aclken + vid_io_out_ce must be tied
# HIGH or the video datapath is gated off -> no DE -> rgb2dvi blanks -> monitor
# "no signal".  (The HDMI-IN v_vid_in path ties its CE via xlconst_vidin_ce;
# the OUT path needs the same.)
create_bd_cell -type ip -vlnv $IP_CONST xlconst_vidout_ce
set_property -dict [list CONFIG.CONST_VAL {1} CONFIG.CONST_WIDTH {1}] [get_bd_cells xlconst_vidout_ce]
connect_bd_net [get_bd_pins xlconst_vidout_ce/dout] [get_bd_pins v_axi4s_vid_out_0/aclken]
connect_bd_net [get_bd_pins xlconst_vidout_ce/dout] [get_bd_pins v_axi4s_vid_out_0/vid_io_out_ce]
connect_bd_net [get_bd_pins proc_sys_reset_video/peripheral_reset] [get_bd_pins v_axi4s_vid_out_0/vid_io_out_reset]

# 6e. rgb2dvi (Digilent) -- replaces Haoyue's HDMI_Transmitter_0
puts "  NOTE: rgb2dvi VLNV must match what is in your ip_repo. Adjust below."
create_bd_cell -type ip -vlnv $IP_RGB rgb2dvi_0
# Disable internal SerialClk generation so the external SerialClk pin appears
# and can be driven by axi_dynclk_0/PXL_CLK_5X_O. Default (kGenerateSerialClk=true)
# hides the pin, which trips the Linux Vivado build.
set_property -dict [list \
    CONFIG.kGenerateSerialClk {true} \
    CONFIG.kRstActiveHigh     {false} \
] [get_bd_cells rgb2dvi_0]
# kGenerateSerialClk=true (silicon-confirmed 2026-06-01): rgb2dvi self-generates
# the 5x TMDS serial clock internally from the locked 25.175 MHz PixelClk.  The
# earlier false setting (depending on dynclk PXL_CLK_5X_O) produced no valid TMDS
# -> monitor "no signal".  With true, the external SerialClk pin is hidden, so
# do NOT connect PXL_CLK_5X_O.
# kRstActiveHigh=false     → aRst_n becomes visible (matches active-low resets here)
connect_bd_net [get_bd_pins axi_dynclk_0/PXL_CLK_O]            [get_bd_pins rgb2dvi_0/PixelClk]
connect_bd_net [get_bd_pins proc_sys_reset_video/peripheral_aresetn] [get_bd_pins rgb2dvi_0/aRst_n]
connect_bd_intf_net [get_bd_intf_pins v_axi4s_vid_out_0/vid_io_out] [get_bd_intf_pins rgb2dvi_0/RGB]

# 6f. xlconstant for hdmi_tx_en (must be 1 -- default is 0 = disabled!)
create_bd_cell -type ip -vlnv $IP_CONST xlconstant_hdmi_en
set_property CONFIG.CONST_VAL {1} [get_bd_cells xlconstant_hdmi_en]

# ----- 7. xlconcat for IRQs ---------------------------------------------
puts "\n=== 7. xlconcat -> PS7 IRQ_F2P ==="
create_bd_cell -type ip -vlnv $IP_CONCAT xlconcat_0
set_property CONFIG.NUM_PORTS {3} [get_bd_cells xlconcat_0]
connect_bd_net [get_bd_pins axi_vdma_0/mm2s_introut] [get_bd_pins xlconcat_0/In0]
connect_bd_net [get_bd_pins v_tc_0/irq]              [get_bd_pins xlconcat_0/In1]
connect_bd_net [get_bd_pins cgra_top_0/irq]          [get_bd_pins xlconcat_0/In2]
connect_bd_net [get_bd_pins xlconcat_0/dout]         [get_bd_pins processing_system7_0/IRQ_F2P]

# ----- 8. External HDMI ports (flat, matching constrs_pynq_z2.xdc) ------
puts "\n=== 8. External HDMI TMDS + control ports ==="
# Flat ports -- do NOT use make_bd_intf_pins_external on TMDS_0 (causes UCIO-1)
# Names + widths must match 01_bench/constrs_pynq_z2.xdc exactly:
#   hdmi_tx_clk_p / hdmi_tx_clk_n  (1-bit scalars)
#   hdmi_tx_d_p / hdmi_tx_d_n      ([2:0] 3-bit vectors)
#   hdmi_tx_cec, hdmi_tx_hpd, hdmi_tx_scl, hdmi_tx_sda  (1-bit control)
#   led                             ([3:0] 4-bit)
create_bd_port -dir O hdmi_tx_clk_p
create_bd_port -dir O hdmi_tx_clk_n
create_bd_port -dir O -from 2 -to 0 hdmi_tx_d_p
create_bd_port -dir O -from 2 -to 0 hdmi_tx_d_n
connect_bd_net [get_bd_ports hdmi_tx_clk_p] [get_bd_pins rgb2dvi_0/TMDS_Clk_p]
connect_bd_net [get_bd_ports hdmi_tx_clk_n] [get_bd_pins rgb2dvi_0/TMDS_Clk_n]
connect_bd_net [get_bd_ports hdmi_tx_d_p]   [get_bd_pins rgb2dvi_0/TMDS_Data_p]
connect_bd_net [get_bd_ports hdmi_tx_d_n]   [get_bd_pins rgb2dvi_0/TMDS_Data_n]

# HDMI control: tie cec=0, drive hpd as input (used by sw / leave float),
# drive scl/sda from a simple I/O. For a minimal display-only demo, tie cec
# and let scl/sda be high-Z (board has pull-ups).
create_bd_port -dir O hdmi_tx_cec
create_bd_port -dir I hdmi_tx_hpd
create_bd_port -dir IO hdmi_tx_scl
create_bd_port -dir IO hdmi_tx_sda

# Tie cec low using xlconstant
create_bd_cell -type ip -vlnv $IP_CONST xlconst_cec_low
set_property -dict [list CONFIG.CONST_VAL {0} CONFIG.CONST_WIDTH {1}] [get_bd_cells xlconst_cec_low]
connect_bd_net [get_bd_pins xlconst_cec_low/dout] [get_bd_ports hdmi_tx_cec]
# scl/sda left disconnected -> Vivado will infer high-Z which is correct for
# a display that handles EDID pull-ups itself; if the design needs EDID,
# wire them to an axi_iic IP instead.

# Optional debug LEDs (4 bits, tied to status signals)
create_bd_port -dir O -from 3 -to 0 led
create_bd_cell -type ip -vlnv $IP_CONCAT xlconcat_led
set_property CONFIG.NUM_PORTS {4} [get_bd_cells xlconcat_led]
# led[0] = MMCM lock, led[1] = vdma running, led[2] = cgra irq, led[3] = 0
connect_bd_net [get_bd_pins axi_dynclk_0/LOCKED_O]   [get_bd_pins xlconcat_led/In0]
create_bd_cell -type ip -vlnv $IP_CONST xlconst_led_zero
set_property -dict [list CONFIG.CONST_VAL {0} CONFIG.CONST_WIDTH {1}] [get_bd_cells xlconst_led_zero]
connect_bd_net [get_bd_pins xlconst_led_zero/dout]   [get_bd_pins xlconcat_led/In1]
connect_bd_net [get_bd_pins cgra_top_0/irq]          [get_bd_pins xlconcat_led/In2]
connect_bd_net [get_bd_pins xlconst_led_zero/dout]   [get_bd_pins xlconcat_led/In3]
connect_bd_net [get_bd_pins xlconcat_led/dout]       [get_bd_ports led]

# ----- 9. Address map (Haoyue layout) -----------------------------------
puts "\n=== 9. Assigning addresses ==="
assign_bd_address [get_bd_addr_segs {axi_vdma_0/S_AXI_LITE/Reg}]
set_property offset 0x43000000 [get_bd_addr_segs {processing_system7_0/Data/SEG_axi_vdma_0_Reg}]
set_property range  64K        [get_bd_addr_segs {processing_system7_0/Data/SEG_axi_vdma_0_Reg}]

assign_bd_address [get_bd_addr_segs {axi_dynclk_0/s00_axi/reg0}]
set_property offset 0x43C00000 [get_bd_addr_segs {processing_system7_0/Data/SEG_axi_dynclk_0_reg0}]

assign_bd_address [get_bd_addr_segs {cgra_top_0/interface_apb/Reg}]
set_property offset 0x43C10000 [get_bd_addr_segs {processing_system7_0/Data/SEG_cgra_top_0_Reg}]
set_property range  64K        [get_bd_addr_segs {processing_system7_0/Data/SEG_cgra_top_0_Reg}]

# CGRA DMA address space (m_axi -> HP1).
# Use -target_address_space form: the SEG_X master-side names only exist
# AFTER assignment, so passing them by literal name to get_bd_addr_segs
# raises [BD 5-699]. The target_address_space form is unambiguous.
assign_bd_address -target_address_space /cgra_top_0/m_axi \
    [get_bd_addr_segs processing_system7_0/S_AXI_HP1/HP1_DDR_LOWOCM]

assign_bd_address [get_bd_addr_segs v_tc_0/ctrl/Reg]
set_property offset 0x43C20000 [get_bd_addr_segs processing_system7_0/Data/SEG_v_tc_0_Reg]

assign_bd_address -target_address_space /axi_vdma_0/Data_MM2S \
    [get_bd_addr_segs processing_system7_0/S_AXI_HP0/HP0_DDR_LOWOCM]

# ----- 10. Validate + save ---------------------------------------------
puts "\n=== 10. Validate + save ==="
regenerate_bd_layout
validate_bd_design
save_bd_design

puts ""
puts "==========================================================="
puts " CLEAN BD COMPLETE"
puts " Next:"
puts "   1. make_wrapper -files [get_files design_1.bd] -top"
puts "   2. add_files (constrs_pynq_z2.xdc)"
puts "   3. launch_runs synth_1; wait_on_run synth_1"
puts "   4. launch_runs impl_1 -to_step write_bitstream; wait_on_run impl_1"
puts "==========================================================="
