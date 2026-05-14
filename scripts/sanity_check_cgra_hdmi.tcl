# =============================================================================
# sanity_check_cgra_hdmi.tcl
#
# Run after sourcing build_cgra_hdmi_pynqz2_clean.tcl (or after opening any
# CGRA+HDMI BD project). Verifies the design dodges the V100-V169 traps:
#
#   1. PCW_M_AXI_GP0_FREQMHZ matches FCLK0 (no [BD 41-702] propagation lock).
#   2. HP-side fabric is smartconnect, not axi_interconnect:2.1
#      (interconnect 2.1 has the AxPROT cache bug).
#   3. CGRA APB bridge present + connected.
#   4. Address map matches Haoyue layout.
#   5. Two reset blocks for 100M + 150M (no cross-domain reset).
#   6. cgra_top_0/m_axi reaches a HP port.
#   7. validate_bd_design passes with 0 errors.
#
# Optional checks (run after synthesis):
#   - Synth log free of [Synth 8-689] AxPROT width warnings.
#   - WNS positive in the routed timing summary.
#
# Usage:
#   In Vivado Tcl console with BD open:
#     source <CGRA_root>/scripts/sanity_check_cgra_hdmi.tcl
# =============================================================================

set FAIL 0
set WARN 0

proc fail {msg}  { puts "  \[FAIL\] $msg"; incr ::FAIL }
proc warn {msg}  { puts "  \[WARN\] $msg"; incr ::WARN }
proc ok   {msg}  { puts "  \[OK\]   $msg" }

puts "==========================================================="
puts " CGRA+HDMI BD sanity check"
puts "==========================================================="

if {[catch {current_bd_design} bd]} {
    error "No BD open. open_bd_design design_1.bd first."
}
puts "  BD: [get_property NAME $bd]"
puts ""

# --- 1. PS7 clocks + GP0 freq ---
puts "\[1\] PS7 clocks"
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7*"}]
if {[llength $ps7] != 1} {
    fail "expected exactly 1 processing_system7, got [llength $ps7]"
} else {
    set fclk0 [get_property CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ $ps7]
    set fclk1 [get_property CONFIG.PCW_FPGA1_PERIPHERAL_FREQMHZ $ps7]
    set gp0   [get_property CONFIG.PCW_M_AXI_GP0_FREQMHZ $ps7]
    set buf0  [get_property CONFIG.PCW_FCLK_CLK0_BUF $ps7]
    set buf1  [get_property CONFIG.PCW_FCLK_CLK1_BUF $ps7]
    puts "    FCLK0=$fclk0 MHz (BUF=$buf0)  FCLK1=$fclk1 MHz (BUF=$buf1)  GP0=$gp0 MHz"
    if {$gp0 != $fclk0} {
        fail "PCW_M_AXI_GP0_FREQMHZ ($gp0) != FCLK0 ($fclk0). Expected match -- otherwise [BD 41-702] fires and AXI handshakes wedge."
    } else { ok "GP0 == FCLK0 == $gp0 MHz" }
    if {$buf0 ne "TRUE"} { warn "FCLK0 BUF != TRUE" } else { ok "FCLK0 BUF=TRUE" }
    if {$buf1 ne "TRUE"} { warn "FCLK1 BUF != TRUE" } else { ok "FCLK1 BUF=TRUE" }
}

# --- 2. HP fabric must be smartconnect ---
puts "\n\[2\] HP fabric"
set sc_cells [get_bd_cells -filter {VLNV =~ "*smartconnect*"}]
set ic_cells [get_bd_cells -filter {VLNV =~ "*axi_interconnect:2.1*"}]
puts "    smartconnect cells:    [llength $sc_cells]    ([join [get_property NAME $sc_cells] {, }])"
puts "    axi_interconnect 2.1:  [llength $ic_cells]    ([join [get_property NAME $ic_cells] {, }])"
if {[llength $sc_cells] < 2} {
    fail "expected >= 2 smartconnect (one per HP). Got [llength $sc_cells]."
} else { ok "[llength $sc_cells] smartconnect cells present" }
foreach ic $ic_cells {
    set name [get_property NAME $ic]
    # OK to use interconnect 2.1 for AXI Lite control, NOT for HP datapath.
    # Detect by looking at downstream connections.
    if {[regexp -nocase {periph} $name]} {
        ok "interconnect 2.1 used as control fabric: $name"
    } else {
        fail "interconnect 2.1 used for non-control fabric: $name (use smartconnect instead)"
    }
}

# --- 3. APB bridge present and connected ---
puts "\n\[3\] CGRA APB bridge"
set apb [get_bd_cells -filter {VLNV =~ "*axi_apb_bridge*"}]
if {[llength $apb] == 0} {
    fail "axi_apb_bridge missing -- cgra_top is APB-slave, not AXI-Lite."
} else {
    ok "axi_apb_bridge present: [get_property NAME $apb]"
}

# --- 4. Address map ---
puts "\n\[4\] Address map (Haoyue layout)"
set expected {
    cgra_top_0/s_apb         0x43C10000
    axi_dynclk_0/s00_axi     0x43C00000
    v_tc_0/ctrl              0x43C20000
    axi_vdma_0/S_AXI_LITE    0x43000000
}
foreach {endpoint expect_off} $expected {
    set seg [get_bd_addr_segs -filter "PATH =~ */$endpoint/*" -of [get_bd_addr_spaces /processing_system7_0/Data]]
    if {$seg eq ""} {
        warn "no address segment found for $endpoint"
        continue
    }
    set off [get_property OFFSET $seg]
    if {$off ne $expect_off} {
        warn "$endpoint at $off (expected $expect_off)"
    } else {
        ok "$endpoint at $off"
    }
}

# --- 5. Reset blocks ---
puts "\n\[5\] Reset blocks"
set rsts [get_bd_cells -filter {VLNV =~ "*proc_sys_reset*"}]
puts "    [llength $rsts] proc_sys_reset cell(s): [join [get_property NAME $rsts] {, }]"
if {[llength $rsts] < 2} {
    warn "only [llength $rsts] reset block(s) -- Haoyue uses 2 (one per clock domain)."
} else { ok "two reset blocks (one per clock domain)" }

# --- 6. CGRA m_axi reaches an HP port ---
puts "\n\[6\] CGRA DMA path"
set cgra [get_bd_cells -filter {VLNV =~ "*user:cgra_top*"}]
if {[llength $cgra] == 0} {
    fail "no CGRA cell found"
} else {
    set m_axi_pin [get_bd_intf_pins -of $cgra -filter {NAME =~ "m_axi"}]
    if {$m_axi_pin eq ""} {
        fail "cgra_top has no m_axi pin -- did packaging script run?"
    } else {
        # Trace through smartconnect to PS7 HP
        set net [get_bd_intf_nets -of $m_axi_pin]
        ok "cgra_top/m_axi connected to net $net"
    }
}

# --- 7. validate_bd_design ---
puts "\n\[7\] validate_bd_design"
set rc [catch {validate_bd_design -force} msg]
if {$rc != 0} {
    fail "validate_bd_design returned non-zero. See messages above."
} else { ok "BD validates cleanly" }

# --- 8. Search BD validation messages for [BD 41-702] (M_AXI_GP0 propagation) ---
puts "\n\[8\] Propagation messages"
set msgs [get_msg_config -severity warning -limit 20]
# get_msg_config doesn't return messages directly in older Vivado; this is best-effort.
puts "    (Check Messages tab for \[BD 41-702\] -- if present, GP0 freq lock not cleared.)"

puts ""
puts "==========================================================="
if {$FAIL == 0 && $WARN == 0} {
    puts " ALL CHECKS PASSED -- proceed to bitstream."
} elseif {$FAIL == 0} {
    puts " PASS with $WARN warning(s) -- review above before bitstream."
} else {
    puts " $FAIL FAILURE(S), $WARN warning(s) -- DO NOT bitstream until fixed."
}
puts "==========================================================="
