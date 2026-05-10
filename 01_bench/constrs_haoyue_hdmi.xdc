# =============================================================================
# constrs_haoyue_hdmi.xdc — Haoyue HDMI pinout for the FPGA_CGRA project
#
# IMPORTANT: Only constrain the _p pins of differential pairs with TMDS_33.
# Vivado infers the _n pins from the OBUFDS internal to the IP.
# DO NOT constrain _n pins manually to avoid Single-Ended DRC errors.
# =============================================================================

# TMDS CLK
set_property PACKAGE_PIN U18 [get_ports TMDS_0_tmds_clk_p]
set_property IOSTANDARD TMDS_33 [get_ports TMDS_0_tmds_clk_p]

# TMDS DATA
set_property PACKAGE_PIN W18 [get_ports {TMDS_0_tmds_data_p[0]}]
set_property IOSTANDARD TMDS_33 [get_ports {TMDS_0_tmds_data_p[0]}]

set_property PACKAGE_PIN W14 [get_ports {TMDS_0_tmds_data_p[1]}]
set_property IOSTANDARD TMDS_33 [get_ports {TMDS_0_tmds_data_p[1]}]

set_property PACKAGE_PIN Y18 [get_ports {TMDS_0_tmds_data_p[2]}]
set_property IOSTANDARD TMDS_33 [get_ports {TMDS_0_tmds_data_p[2]}]

# DDC I2C (Keep at LVCMOS33 as these are 3.3V)
set_property PACKAGE_PIN P20 [get_ports I2C2_scl_io]
set_property PACKAGE_PIN N20 [get_ports I2C2_sda_io]
set_property IOSTANDARD LVCMOS33 [get_ports I2C2_scl_io]
set_property IOSTANDARD LVCMOS33 [get_ports I2C2_sda_io]
