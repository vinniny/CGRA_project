# =============================================================================
# pynq_z2_setup.tcl
#
# Automated setup for the 4×4 CGRA + HDMI on the PYNQ-Z2 board using Vivado 2025.
# =============================================================================

set project_name "pynq_cgra_hdmi"
set project_dir  "C:/Users/thanh/Desktop/CGRA_PYNQ"
set board_part   "tul.com.tw:pynq-z2:part0:1.0"
set cgra_repo    "C:/Users/thanh/Desktop/FPGA_CGRA/cgra_block"

# 1. Create Project
create_project $project_name $project_dir -part xc7z020clg400-1 -force
set_property board_part $board_part [current_project]

# 2. Add IP Repositories
set_property  ip_repo_paths  $cgra_repo [current_project]
update_ip_catalog

# 3. Create Block Design
create_bd_design "zynq"

# 4. Instantiate and Configure PS7
create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 processing_system7_0
apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 -config {make_external "FIXED_IO, DDR" apply_board_preset "1" Master "Disable" Slave "Disable" }  [get_bd_cells processing_system7_0]

# Enable S_AXI_HP0 (for CGRA DMA) and FCLK_CLK1 (for CGRA 50MHz)
set_property -dict [list \
    CONFIG.PCW_USE_S_AXI_HP0 {1} \
    CONFIG.PCW_FPGA1_PERIPHERAL_FREQMHZ {50} \
    CONFIG.PCW_EN_CLK1_PORT {1} \
    CONFIG.PCW_USE_FABRIC_INTERRUPT {1} \
    CONFIG.PCW_IRQ_F2P_INTR {1} \
] [get_bd_cells processing_system7_0]

# 5. Add CGRA IP
create_bd_cell -type ip -vlnv xilinx.com:user:cgra_top:1.0 cgra_top_0

# 6. Add Interconnects and Reset
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Master "/processing_system7_0/M_AXI_GP0" intc_ip "New AXI Interconnect" Clk_xbar "Auto" Clk_master "Auto" Clk_slave "Auto" }  [get_bd_intf_pins cgra_top_0/interface_apb]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Master "/cgra_top_0/m_axi" intc_ip "New SmartConnect" Clk_xbar "Auto" Clk_master "Auto" Clk_slave "Auto" }  [get_bd_intf_pins processing_system7_0/S_AXI_HP0]

# Connect IRQ
create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0
connect_bd_net [get_bd_pins cgra_top_0/irq] [get_bd_pins xlconcat_0/In0]
connect_bd_net [get_bd_pins xlconcat_0/dout] [get_bd_pins processing_system7_0/IRQ_F2P]

# Connect FCLK_CLK1 to CGRA
connect_bd_net [get_bd_pins processing_system7_0/FCLK_CLK1] [get_bd_pins cgra_top_0/clk]
# (Note: Automation usually handles the 100MHz domain for AXI)

# 7. Add HDMI TX (Placeholder Ports)
# In a real project, you would add an HDMI transmitter IP here.
# For now, we'll create the external ports to match the XDC.
create_bd_port -dir O hdmi_tx_clk_p
create_bd_port -dir O hdmi_tx_clk_n
create_bd_port -dir O -from 2 -to 0 hdmi_tx_d_p
create_bd_port -dir O -from 2 -to 0 hdmi_tx_d_n
create_bd_port -dir O hdmi_tx_cec
create_bd_port -dir I hdmi_tx_hpd
create_bd_port -dir IO hdmi_tx_scl
create_bd_port -dir IO hdmi_tx_sda

# 8. Address Mapping
assign_bd_address [get_bd_addr_segs cgra_top_0/interface_apb/Reg]
set_property offset 0x43C00000 [get_bd_addr_segs {/processing_system7_0/Data/SEG_cgra_top_0_Reg}]
set_property range 64K [get_bd_addr_segs {/processing_system7_0/Data/SEG_cgra_top_0_Reg}]

# 9. Finalize
validate_bd_design
save_bd_design
make_wrapper -files [get_files $project_dir/$project_name.srcs/sources_1/bd/zynq/zynq.bd] -top
add_files -norecurse $project_dir/$project_name.gen/sources_1/bd/zynq/hdl/zynq_wrapper.v

puts "==========================================================="
puts " PYNQ-Z2 CGRA Setup Complete!"
puts " Project: $project_dir/$project_name.xpr"
puts " Next Steps:"
puts "   1. Add the constraints file: 01_bench/constrs_pynq_z2.xdc"
puts "   2. Run Synthesis, Implementation, and Bitstream."
puts "==========================================================="
