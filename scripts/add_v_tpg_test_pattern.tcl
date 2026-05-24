# =============================================================================
# add_v_tpg_test_pattern.tcl — Insert a Video Test Pattern Generator into the
# cgra_pynq_base BD's HDMI-in capture path for AXIS-path validation without
# a real HDMI source.
#
# Topology BEFORE (working BD):
#
#   J10 (TMDS) -> dvi2rgb_0 -> [frontend AXIS] -> color_convert_in
#                                                       |
#                                                       v
#                                                  pixel_pack_in
#                                                       |
#                                                       v
#                                                  axi_vdma S2MM
#                                                       |
#                                                       v
#                                                  DDR @ 0x1100_0000
#
# Topology AFTER (with this patch):
#
#   J10 (TMDS) -> dvi2rgb_0 ----.
#                                +-> axis_switch_in.M00_AXIS -> color_convert_in -> ...
#   v_tpg_test (200×200 bars) --'
#
# axis_switch_in is software-programmable via AXI-Lite:
#   S00 = dvi2rgb path  (real HDMI)
#   S01 = v_tpg path    (synthesized test pattern in PL)
#
# This is a Vivado-only, no-external-source way to prove the AXIS data
# pipeline works end-to-end. With S01 selected, the V_TPG runs in the
# PL, drives synthesized 24-bit RGB bars into color_convert -> pixel_pack
# -> VDMA -> DDR. SW then reads DDR back and dumps to BMP.
#
# Requires: the working cgra_pynq_base BD already open (in our case
# recreated from CGRA_PYNQ_clean/base.tcl). Run AFTER the BD is built
# but BEFORE wrapper generation / synth.
# =============================================================================

puts "==========================================================="
puts " ADD V_TPG TEST PATTERN to HDMI-in pipeline"
puts "==========================================================="

if {[catch {current_bd_design} cur_bd]} {
    error "No open BD. Source base.tcl (from CGRA_PYNQ_clean) first."
}
puts "  BD in scope: $cur_bd"

# Sanity: the IPs we're modifying must exist
foreach req {ps7_0 video/hdmi_in/color_convert video/hdmi_in/frontend/dvi2rgb_0} {
    if {[llength [get_bd_cells $req]] == 0} {
        error "Required cell '$req' not found — wrong BD?"
    }
}

proc _pick_ip {vendor library name} {
    set cands [get_ipdefs -filter "VLNV =~ \"$vendor:$library:$name:*\""]
    if {[llength $cands] == 0} {
        error "No IP $vendor:$library:$name. Check ip_repo_paths."
    }
    return [lindex [lsort -decreasing -dictionary $cands] 0]
}
set IP_TPG    [_pick_ip xilinx.com ip v_tpg]
set IP_SWITCH [_pick_ip xilinx.com ip axis_switch]
puts "  v_tpg        VLNV = $IP_TPG"
puts "  axis_switch  VLNV = $IP_SWITCH"

# ----- 1. Create v_tpg_test_0 -------------------------------------------
puts "\n=== 1. Add v_tpg_test_0 (640×480 @ 30 Hz, colour bars) ==="
create_bd_cell -type ip -vlnv $IP_TPG v_tpg_test_0
# 640×480 frame, 24-bit RGB, internal timing (no external v_tc required),
# colour-bar pattern is default at SW-programmable register 0x40.
set_property -dict [list \
    CONFIG.HAS_AXI4_LITE     {1}  \
    CONFIG.PIXELS_PER_CLOCK  {1}  \
    CONFIG.MAX_COLS          {640} \
    CONFIG.MAX_ROWS          {480} \
    CONFIG.MAX_DATA_WIDTH    {8}  \
    CONFIG.SAMPLES_PER_CLOCK {1}  \
    CONFIG.HAS_INTC_IF       {0}  \
] [get_bd_cells v_tpg_test_0]

# ----- 2. Add axis_switch_in --------------------------------------------
puts "\n=== 2. Add axis_switch_in (2 → 1) ==="
create_bd_cell -type ip -vlnv $IP_SWITCH axis_switch_in
# ROUTING_MODE=1 = "Control Register Routing" → IP exposes S_AXI_CTRL
# AXI-Lite slave. ROUTING_MODE=0 is TDEST-routed (no AXI-Lite, useless
# for SW-selectable source switching).
set_property -dict [list \
    CONFIG.ROUTING_MODE      {1}    \
    CONFIG.NUM_SI            {2}    \
    CONFIG.NUM_MI            {1}    \
    CONFIG.HAS_TLAST         {1}    \
    CONFIG.HAS_TKEEP         {0}    \
    CONFIG.HAS_TSTRB         {0}    \
    CONFIG.HAS_TID           {0}    \
    CONFIG.HAS_TDEST         {0}    \
    CONFIG.HAS_TUSER         {1}    \
    CONFIG.TDATA_NUM_BYTES   {3}    \
] [get_bd_cells axis_switch_in]

# ----- 3. Clock + reset (dual-domain: video FCLK1 + AXI-Lite FCLK0) ----
puts "\n=== 3. Clock + reset hookup ==="
# The HDMI-in video pipeline (color_convert / pixel_pack / VDMA stream
# side) runs on FCLK1 = 142.857 MHz (via /video/hdmi_in/clk_142M). The
# AXIS streaming clock of v_tpg + axis_switch MUST match that, otherwise
# validate_bd_design errors with:
#   ERROR: [BD 41-237] FREQ_HZ does not match between
#   /video/hdmi_in/color_convert/stream_in_24(142857132) and
#   /axis_switch_in/M00_AXIS(100000000)
# AXI-Lite control stays on FCLK0 = 100 MHz (matches ps7_0_axi_periph).
proc _pick_pin {paths} {
    foreach p $paths {
        # Try direct (current-scope) lookup first.
        set hits [get_bd_pins -quiet $p]
        if {[llength $hits] > 0} { return [lindex $hits 0] }
    }
    return ""
}
# Resolve aresetn by walking the reset cells and matching the clock that
# drives slowest_sync_clk. Bulletproof to any naming convention.
proc _find_aresetn_for_clk {clk_pin} {
    foreach c [get_bd_cells -filter {VLNV =~ "*proc_sys_reset*"}] {
        set slk [get_bd_pins -quiet $c/slowest_sync_clk]
        if {[llength $slk] == 0} continue
        foreach n [get_bd_nets -of_objects $slk] {
            set drivers [get_bd_pins -of_objects $n]
            foreach d $drivers {
                if {$d eq $clk_pin} {
                    set out [get_bd_pins -quiet $c/peripheral_aresetn]
                    if {[llength $out] > 0} { return [lindex $out 0] }
                }
            }
        }
    }
    return ""
}
set fclk_vid  [get_bd_pins ps7_0/FCLK_CLK1]
set fclk_ctrl [get_bd_pins ps7_0/FCLK_CLK0]
# Try direct names first (working BD uses fclk0/fclk1 suffix), then walk.
set rstn_vid  [_pick_pin [list \
    rst_ps7_0_fclk1/peripheral_aresetn \
    rst_ps7_0_142M/peripheral_aresetn]]
if {$rstn_vid eq ""} { set rstn_vid [_find_aresetn_for_clk $fclk_vid] }
set rstn_ctrl [_pick_pin [list \
    rst_ps7_0_fclk0/peripheral_aresetn \
    rst_ps7_0_100M/peripheral_aresetn]]
if {$rstn_ctrl eq ""} { set rstn_ctrl [_find_aresetn_for_clk $fclk_ctrl] }
if {$rstn_vid eq "" || $rstn_ctrl eq ""} {
    error "Could not find peripheral_aresetn for FCLK0 ($fclk_ctrl) or FCLK1 ($fclk_vid)."
}
puts "  video clock : $fclk_vid    @ 142.857 MHz"
puts "  video reset : $rstn_vid"
puts "  ctrl  clock : $fclk_ctrl  @ 100 MHz"
puts "  ctrl  reset : $rstn_ctrl"

# v_tpg: ap_clk drives BOTH its m_axis_video stream and s_axi_CTRL slave.
# Clock it on the video clock so the streaming output matches downstream.
# The ps7_0_axi_periph interconnect bridges FCLK0->FCLK1 on M09 (set later).
connect_bd_net $fclk_vid [get_bd_pins v_tpg_test_0/ap_clk]
connect_bd_net $rstn_vid [get_bd_pins v_tpg_test_0/ap_rst_n]

# axis_switch_in: separate clocks for data (aclk) + AXI-Lite control.
connect_bd_net $fclk_vid  [get_bd_pins axis_switch_in/aclk]
connect_bd_net $rstn_vid  [get_bd_pins axis_switch_in/aresetn]
connect_bd_net $fclk_ctrl [get_bd_pins axis_switch_in/s_axi_ctrl_aclk]
connect_bd_net $rstn_ctrl [get_bd_pins axis_switch_in/s_axi_ctrl_aresetn]

# ----- 4. AXIS rewire: dvi2rgb chain → switch.S00, v_tpg → switch.S01,
#         switch.M00 → existing color_convert AXIS input.
puts "\n=== 4. AXIS rewire ==="
# Find the existing AXIS net feeding color_convert. In the working BD the
# net is named via the frontend hierarchy — query by intf_pin and walk.
set cc_input [get_bd_intf_pins video/hdmi_in/color_convert/stream_in_24]
if {[llength $cc_input] == 0} {
    error "color_convert input intf_pin not found"
}
set old_net [get_bd_intf_nets -of_objects $cc_input]
puts "  Existing AXIS source net: $old_net"
delete_bd_objs $old_net

# Re-route: previous-source -> axis_switch_in.S00
# We need to know the previous source. In the working BD the chain typically is:
#   /video/hdmi_in/frontend → /video/hdmi_in/color_convert
# Look up the source pin by inspecting the frontend hierarchy.
# In the working cgra_pynq_base BD the frontend's AXIS master is the
# `video_out` intf pin (the chain ends in v_vid_in_axi4s_0 inside the
# hierarchy and gets re-exposed as `video_out`). Probed via /tmp/probe_pins.
set frontend_out_candidates {
    video/hdmi_in/frontend/video_out
    video/hdmi_in/frontend/m_axis_video
    video/hdmi_in/frontend/M_AXIS
    video/hdmi_in/frontend/m_axis
}
set frontend_out ""
foreach c $frontend_out_candidates {
    set hits [get_bd_intf_pins -quiet $c]
    if {[llength $hits] > 0} {
        set frontend_out [lindex $hits 0]
        break
    }
}
if {$frontend_out eq ""} {
    error "frontend AXIS output pin not detected — list candidates with `get_bd_intf_pins -of_objects \[get_bd_cells video/hdmi_in/frontend\]`."
}
connect_bd_intf_net $frontend_out [get_bd_intf_pins axis_switch_in/S00_AXIS]
puts "  frontend AXIS  → axis_switch_in.S00_AXIS  (source: $frontend_out)"
connect_bd_intf_net [get_bd_intf_pins v_tpg_test_0/m_axis_video] \
                    [get_bd_intf_pins axis_switch_in/S01_AXIS]
puts "  v_tpg AXIS     → axis_switch_in.S01_AXIS"
connect_bd_intf_net [get_bd_intf_pins axis_switch_in/M00_AXIS] $cc_input
puts "  axis_switch.M0 → color_convert.stream_in_24"

# ----- 5. AXI-Lite control (attach to control SmartConnect M_AXI line) -
puts "\n=== 5. AXI-Lite ==="
# The working BD has a SmartConnect (ps7_0_axi_periph) with several free MIs.
# Get its current NUM_MI and grow by two for v_tpg + axis_switch ctrl.
set ctrl_sc [get_bd_cells ps7_0_axi_periph]
if {[llength $ctrl_sc] == 0} {
    set ctrl_sc [get_bd_cells -filter {VLNV =~ "*smartconnect*"} -hierarchical]
    if {[llength $ctrl_sc] == 0} {
        error "Could not locate the control SmartConnect"
    }
    set ctrl_sc [lindex $ctrl_sc 0]
}
set num_mi  [get_property CONFIG.NUM_MI $ctrl_sc]
set new_num [expr {$num_mi + 2}]
puts "  Growing $ctrl_sc NUM_MI $num_mi → $new_num"
set_property CONFIG.NUM_MI $new_num $ctrl_sc
# The two new MI ports are M<old>_AXI and M<old+1>_AXI
set tpg_mi    [format "M%02d_AXI" $num_mi]
set switch_mi [format "M%02d_AXI" [expr {$num_mi + 1}]]
connect_bd_intf_net [get_bd_intf_pins $ctrl_sc/$tpg_mi] \
                    [get_bd_intf_pins v_tpg_test_0/s_axi_CTRL]
connect_bd_intf_net [get_bd_intf_pins $ctrl_sc/$switch_mi] \
                    [get_bd_intf_pins axis_switch_in/S_AXI_CTRL]

# ps7_0_axi_periph is an axi_interconnect (not a smartconnect) — each
# MI port has its own M%02d_ACLK / M%02d_ARESETN pin that must be
# driven and MUST match the clock domain of the downstream slave's
# AXI-Lite interface. Otherwise BD 41-758 / 41-237.
#
# v_tpg's s_axi_CTRL is clocked by ap_clk (= FCLK1, video)
# axis_switch's S_AXI_CTRL is clocked by s_axi_ctrl_aclk (= FCLK0)
foreach {mi clk rstn} [list \
        $tpg_mi    $fclk_vid  $rstn_vid  \
        $switch_mi $fclk_ctrl $rstn_ctrl] {
    set base [string range $mi 0 end-4]   ;# "M09_AXI" -> "M09"
    set aclk_pin  [get_bd_pins -quiet $ctrl_sc/${base}_ACLK]
    set arstn_pin [get_bd_pins -quiet $ctrl_sc/${base}_ARESETN]
    if {[llength $aclk_pin]  > 0} { connect_bd_net $clk  [lindex $aclk_pin  0] }
    if {[llength $arstn_pin] > 0} { connect_bd_net $rstn [lindex $arstn_pin 0] }
    puts "  $ctrl_sc/${base}_ACLK = $clk"
}

# Address assignment — pick fixed offsets so the SW driver can hard-code
# them. The working BD uses `ps7_0` (not `processing_system7_0`) as the
# PS cell name, so segment names auto-generate as /ps7_0/Data/SEG_*.
# `assign_bd_address` accepts `-offset` + `-range` directly — avoids
# any post-hoc seg name lookup.
assign_bd_address -offset 0x43CC0000 -range 64K \
    [get_bd_addr_segs v_tpg_test_0/s_axi_CTRL/Reg]
assign_bd_address -offset 0x43CD0000 -range 64K \
    [get_bd_addr_segs axis_switch_in/S_AXI_CTRL/Reg]

# ----- 6. Validate + save -----------------------------------------------
puts "\n=== 6. validate_bd_design + save_bd_design ==="
regenerate_bd_layout
validate_bd_design
save_bd_design

puts ""
puts "==========================================================="
puts " V_TPG TEST PATTERN INSERTED"
puts "==========================================================="
puts " New AXI-Lite slaves:"
puts "   v_tpg_test_0       @ 0x43CC_0000"
puts "   axis_switch_in     @ 0x43CD_0000"
puts ""
puts " SW selects source via axis_switch routing register:"
puts "   write 0x00000000 @ axis_switch+0x40 → S00 (dvi2rgb / real HDMI)"
puts "   write 0x00000001 @ axis_switch+0x40 → S01 (v_tpg / test pattern)"
puts ""
puts " v_tpg start sequence (HLS AP_CTRL):"
puts "   write COLS=640      @ tpg+0x10"
puts "   write ROWS=480      @ tpg+0x18"
puts "   write FORMAT=2(RGB) @ tpg+0x20"
puts "   write PATTERN=1     @ tpg+0x30 (1 = colour bars)"
puts "   write AP_START=1    @ tpg+0x00 (or 0x81 for auto-restart)"
puts ""
puts " Next: make_wrapper, launch_runs synth_1 + impl_1, write_bitstream"
puts "==========================================================="
