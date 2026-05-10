# =============================================================================
# add_cgra_to_base.tcl
#
# Bolts the CGRA (cgra_top IP-XACT, packaged via package_cgra_ip.tcl) onto an
# already-built PYNQ-Z2 base BD. Must be sourced AFTER PYNQ's base.tcl has
# already been sourced (so the BD exists with ps7_0, ps7_0_axi_periph, HP1
# free, etc.).
#
# What it adds:
#   * cgra_top_0  (CGRA IP, FCLK3 = 100 MHz domain)
#   * axi_apb_bridge_0 (AXI Lite -> APB for CGRA s_apb)
#   * smartconnect_cgra (CGRA m_axi -> PS7 S_AXI_HP1)
#   * Bumps ps7_0_axi_periph NUM_MI 4 -> 5 (M04_AXI -> APB bridge)
#   * Bumps concat_interrupts NUM_PORTS 7 -> 8 (In7 = cgra irq)
#   * Address map: cgra_top_0/s_apb @ 0x43C50000 (free slot in PYNQ space)
#                  cgra_top_0/m_axi -> ps7_0/S_AXI_HP1/HP1_DDR_LOWOCM
#
# Prerequisites:
#   * cgra_top:1.0 (xilinx.com:user:cgra_top:1.0) is in ip_repo_paths
#     (run package_cgra_ip.tcl first)
#   * design_1 (PYNQ base BD) is the current_bd_design
#   * PS7 has S_AXI_HP1 enabled (we will enable it here if not already)
# =============================================================================

puts "==========================================================="
puts " add_cgra_to_base — bolt CGRA onto PYNQ base BD"
puts "==========================================================="

# ----- 0. Sanity --------------------------------------------------------
if {[catch {current_bd_design} bd]} {
    error "No BD open. Source PYNQ base.tcl first."
}
puts "  BD: [get_property NAME $bd]"

# Pick latest IP versions for cross-Vivado portability.
proc _pick_ip {vendor library name} {
    set candidates [get_ipdefs -filter "VLNV =~ \"$vendor:$library:$name:*\""]
    if {[llength $candidates] == 0} {
        error "IP not found: $vendor:$library:$name -- check ip_repo_paths"
    }
    return [lindex [lsort -decreasing -dictionary $candidates] 0]
}
set IP_APB    [_pick_ip xilinx.com  ip   axi_apb_bridge]
set IP_SC     [_pick_ip xilinx.com  ip   smartconnect]
set IP_CGRA   [_pick_ip xilinx.com  user cgra_top]
puts "  IP_APB=$IP_APB"
puts "  IP_SC=$IP_SC"
puts "  IP_CGRA=$IP_CGRA"

# ----- 1. Enable PS7 HP1 -----------------------------------------------
puts "\n=== 1. PS7 config (enable HP1 for CGRA DMA) ==="
set ps7 [get_bd_cells ps7_0]
if {$ps7 eq ""} { set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7*"}] }
if {[llength $ps7] != 1} { error "Could not locate ps7_0 cell" }

# PCW_M_AXI_GP0_FREQMHZ is read-only (auto-tracks FCLK0) in 2024.1, so we
# don't need to set it -- PYNQ base already has it correct via FCLK0=100MHz.
#
# Drop FCLK3 from 100 MHz (PYNQ default) to 50 MHz: the CGRA's longest DMA
# path (read_addr / write_addr / read_words_remaining 32-bit adders) needs
# ~16 ns and fails timing by 6 ns at 100 MHz. After strip_pynq_iops the only
# things left on FCLK3 are CGRA + its reset block, so retargeting is safe.
set_property -dict [list \
    CONFIG.PCW_USE_S_AXI_HP1            {1} \
    CONFIG.PCW_FPGA3_PERIPHERAL_FREQMHZ {50} \
] $ps7

# ----- 2. Add CGRA (from packaged IP) + APB bridge + smartconnect -------
puts "\n=== 2. Adding CGRA + APB bridge + smartconnect ==="
# CGRA was packaged as IP-XACT by package_cgra_ip.tcl. Bus interfaces
# (s_apb/apb_1, m_axi, clk, rst_n, irq) are already declared.
create_bd_cell -type ip -vlnv $IP_CGRA cgra_top_0

# Discover the actual APB and AXI master interface names on the cell
# (rename to s_apb/m_axi may not succeed in all Vivado versions).
set cgra_apb_if [get_bd_intf_pins -of [get_bd_cells cgra_top_0] -filter {VLNV =~ "*:apb*"}]
if {$cgra_apb_if eq ""} { error "cgra_top_0 has no APB slave interface" }
set CGRA_APB_NAME [lindex [split $cgra_apb_if /] end]
set cgra_m_axi_if [get_bd_intf_pins -of [get_bd_cells cgra_top_0] -filter {VLNV =~ "*:aximm*" && MODE == "Master"}]
if {$cgra_m_axi_if eq ""} { error "cgra_top_0 has no AXI master interface" }
set CGRA_AXI_NAME [lindex [split $cgra_m_axi_if /] end]
puts "  CGRA APB interface name: $CGRA_APB_NAME"
puts "  CGRA AXI master name:    $CGRA_AXI_NAME"
create_bd_cell -type ip -vlnv $IP_APB  axi_apb_bridge_0
set_property -dict [list \
    CONFIG.C_M_APB_PROTOCOL {apb3} \
    CONFIG.C_APB_NUM_SLAVES {1} \
] [get_bd_cells axi_apb_bridge_0]

create_bd_cell -type ip -vlnv $IP_SC smartconnect_cgra
set_property -dict [list \
    CONFIG.NUM_SI {1} \
    CONFIG.NUM_MI {1} \
    CONFIG.NUM_CLKS {1} \
] [get_bd_cells smartconnect_cgra]

# ----- 3. Locate clock + reset to attach onto ----------------------------
# PYNQ base wires the FCLK3 reset block (rst_ps7_0_fclk3) to ps7_0_axi_periph
# clock domain (also FCLK3 = 100 MHz).
set fclk_pin   [get_bd_pins ps7_0/FCLK_CLK3]
set rst_pin    [get_bd_pins rst_ps7_0_fclk3/peripheral_aresetn]
if {$rst_pin eq ""} {
    # Fallback if base.tcl uses a different naming
    set rst_blk [lindex [get_bd_cells -filter {VLNV =~ "*proc_sys_reset*"}] 0]
    set rst_pin [get_bd_pins $rst_blk/peripheral_aresetn]
}
puts "  Using clock pin: $fclk_pin"
puts "  Using reset pin: $rst_pin"

# ----- 4. Bump ps7_0_axi_periph NUM_MI 4 -> 5 + connect new M04_AXI ------
puts "\n=== 4. Extending ps7_0_axi_periph for CGRA control ==="
set xbar [get_bd_cells ps7_0_axi_periph]
set old_mi [get_property CONFIG.NUM_MI $xbar]
puts "  ps7_0_axi_periph NUM_MI: $old_mi -> [expr $old_mi + 1]"
set_property CONFIG.NUM_MI [expr $old_mi + 1] $xbar
set new_idx [format "%02d" $old_mi]
# Connect new master clock + reset (mirrors the existing M00..M03 wiring)
connect_bd_net $fclk_pin [get_bd_pins ps7_0_axi_periph/M${new_idx}_ACLK]
connect_bd_net $rst_pin  [get_bd_pins ps7_0_axi_periph/M${new_idx}_ARESETN]
# Wire the new master through APB bridge to CGRA
connect_bd_intf_net [get_bd_intf_pins ps7_0_axi_periph/M${new_idx}_AXI] \
                    [get_bd_intf_pins axi_apb_bridge_0/AXI4_LITE]
connect_bd_intf_net [get_bd_intf_pins axi_apb_bridge_0/APB_M] \
                    [get_bd_intf_pins cgra_top_0/$CGRA_APB_NAME]
connect_bd_net $fclk_pin [get_bd_pins axi_apb_bridge_0/s_axi_aclk]
connect_bd_net $rst_pin  [get_bd_pins axi_apb_bridge_0/s_axi_aresetn]

# ----- 5. CGRA clock + reset ---------------------------------------------
puts "\n=== 5. CGRA clock + reset ==="
connect_bd_net $fclk_pin [get_bd_pins cgra_top_0/clk]
connect_bd_net $rst_pin  [get_bd_pins cgra_top_0/rst_n]

# ----- 6. CGRA m_axi -> smartconnect_cgra -> S_AXI_HP1 -------------------
puts "\n=== 6. CGRA DMA -> HP1 ==="
connect_bd_net $fclk_pin [get_bd_pins smartconnect_cgra/aclk]
connect_bd_net $rst_pin  [get_bd_pins smartconnect_cgra/aresetn]
connect_bd_intf_net [get_bd_intf_pins cgra_top_0/$CGRA_AXI_NAME] \
                    [get_bd_intf_pins smartconnect_cgra/S00_AXI]
connect_bd_intf_net [get_bd_intf_pins smartconnect_cgra/M00_AXI] \
                    [get_bd_intf_pins ps7_0/S_AXI_HP1]
# Wire S_AXI_HP1_ACLK to FCLK3 (same domain as CGRA)
connect_bd_net $fclk_pin [get_bd_pins ps7_0/S_AXI_HP1_ACLK]

# ----- 7. Extend concat_interrupts for CGRA irq -------------------------
puts "\n=== 7. Adding CGRA irq to concat_interrupts ==="
set ci [get_bd_cells concat_interrupts]
if {$ci ne ""} {
    set old_p [get_property CONFIG.NUM_PORTS $ci]
    puts "  concat_interrupts NUM_PORTS: $old_p -> [expr $old_p + 1]"
    set_property CONFIG.NUM_PORTS [expr $old_p + 1] $ci
    connect_bd_net [get_bd_pins cgra_top_0/irq] \
                   [get_bd_pins concat_interrupts/In${old_p}]
} else {
    puts "  WARN: concat_interrupts not found; CGRA irq left unconnected."
}

# ----- 8. Address map -- assign CGRA APB at 0x43C50000 ------------------
puts "\n=== 8. Assigning CGRA addresses ==="
assign_bd_address [get_bd_addr_segs cgra_top_0/$CGRA_APB_NAME/Reg]
# Find the assigned segment and force the offset
set seg [get_bd_addr_segs -filter "PATH =~ */cgra_top_0/$CGRA_APB_NAME/*" \
            -of [get_bd_addr_spaces /ps7_0/Data]]
if {$seg ne ""} {
    set_property offset 0x43C50000 $seg
    set_property range  64K        $seg
    puts "  cgra_top_0/$CGRA_APB_NAME at [get_property OFFSET $seg], range [get_property RANGE $seg]"
}

# CGRA m_axi -> HP1 -> DDR (auto-assign 1G window)
assign_bd_address [get_bd_addr_segs cgra_top_0/$CGRA_AXI_NAME/SEG_ps7_0_HP1_DDR_LOWOCM]

# ----- 9. Validate + save ----------------------------------------------
puts "\n=== 9. Validate + save ==="
regenerate_bd_layout
set rc [catch {validate_bd_design -force} msg]
if {$rc != 0} {
    puts "WARNING: validate_bd_design issues — see Messages tab."
}
save_bd_design

puts ""
puts "==========================================================="
puts " add_cgra_to_base COMPLETE"
puts "   CGRA control:  0x43C50000 (s_apb, 64K)"
puts "   CGRA DMA:      ps7_0/S_AXI_HP1/HP1_DDR_LOWOCM"
puts "   CGRA irq:      concat_interrupts In[get_property CONFIG.NUM_PORTS [get_bd_cells concat_interrupts]] (last)"
puts ""
puts " Next: make_wrapper -files \[get_files design_1.bd\] -top -force"
puts "       -> generate bitstream"
puts "==========================================================="
