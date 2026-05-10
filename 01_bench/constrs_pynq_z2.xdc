## PYNQ-Z2 HDMI TX Constraints
## Based on official PYNQ-Z2 master XDC and board schematics.

## HDMI TX Clock
set_property -dict { PACKAGE_PIN L16   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_clk_p }];
set_property -dict { PACKAGE_PIN L17   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_clk_n }];

## HDMI TX Data Lanes
set_property -dict { PACKAGE_PIN K17   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_d_p[0] }];
set_property -dict { PACKAGE_PIN K18   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_d_n[0] }];
set_property -dict { PACKAGE_PIN K19   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_d_p[1] }];
set_property -dict { PACKAGE_PIN J19   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_d_n[1] }];
set_property -dict { PACKAGE_PIN J18   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_d_p[2] }];
set_property -dict { PACKAGE_PIN H18   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_d_n[2] }];

## HDMI TX Control Signals
set_property -dict { PACKAGE_PIN G15   IOSTANDARD LVCMOS33 } [get_ports { hdmi_tx_cec }];
set_property -dict { PACKAGE_PIN R19   IOSTANDARD LVCMOS33 } [get_ports { hdmi_tx_hpd }];
set_property -dict { PACKAGE_PIN M17   IOSTANDARD LVCMOS33 } [get_ports { hdmi_tx_scl }];
set_property -dict { PACKAGE_PIN M18   IOSTANDARD LVCMOS33 } [get_ports { hdmi_tx_sda }];

## CGRA Clocks (if needed, but usually FCLK is used)
## PS_CLK is 50MHz on PYNQ-Z2

## Debug LEDs
set_property -dict { PACKAGE_PIN R14   IOSTANDARD LVCMOS33 } [get_ports { led[0] }];
set_property -dict { PACKAGE_PIN P14   IOSTANDARD LVCMOS33 } [get_ports { led[1] }];
set_property -dict { PACKAGE_PIN N16   IOSTANDARD LVCMOS33 } [get_ports { led[2] }];
set_property -dict { PACKAGE_PIN M14   IOSTANDARD LVCMOS33 } [get_ports { led[3] }];
