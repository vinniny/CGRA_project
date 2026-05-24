# =============================================================================
# add_system_ila_to_vtpg.tcl — Insert a Vivado System ILA to monitor every
# AXIS net between v_tpg, axis_switch_in, color_convert, pixel_pack, and the
# VDMA S2MM write side. Lets us probe TVALID/TREADY/TUSER/TLAST/TDATA via
# the Vivado HW Manager to find where the chain stalls.
#
# Use AFTER add_v_tpg_test_pattern.tcl. Requires the v_tpg-extended BD to
# already be open.
#
# Approach: mark each AXIS interface net with HDL_ATTRIBUTE.MARK_DEBUG, then
# apply the xilinx.com:bd_rule:debug automation. Vivado will auto-instantiate
# a System ILA, attach AXIS monitor slots to each net, and AXI-Lite-connect
# the ILA's debug hub to the PS7 control SmartConnect. The result: post-impl
# Vivado generates a .ltx file matching the .bit, which the HW Manager can
# load to render TVALID/TREADY waveforms.
# =============================================================================

puts "==========================================================="
puts " ADD SYSTEM ILA to v_tpg AXIS pipeline"
puts "==========================================================="

if {[catch {current_bd_design} cur_bd]} {
    error "No open BD — source base.tcl + add_v_tpg_test_pattern.tcl first."
}
puts "  BD in scope: $cur_bd"

# --- 1. Identify AXIS nets to monitor ----------------------------------
# We probe by intf_pin (most reliable) and walk to the net.
proc _net_of_intf_pin {p} {
    set hits [get_bd_intf_pins -quiet $p]
    if {[llength $hits] == 0} { return "" }
    set net [get_bd_intf_nets -quiet -of_objects [lindex $hits 0]]
    if {[llength $net] == 0} { return "" }
    return [lindex $net 0]
}

# Order matters — we monitor each link in the chain so the stall point
# shows up unambiguously between two adjacent ILA slots.
set targets {
    "v_tpg.m_axis_video    -> axis_switch.S01"  v_tpg_test_0/m_axis_video
    "axis_switch.M00       -> color_convert.in" axis_switch_in/M00_AXIS
    "color_convert.in      <-                 " video/hdmi_in/color_convert/stream_in_24
    "color_convert.out     -> register_slice  " video/hdmi_in/color_convert/stream_out_24
    "pixel_pack.out        -> vdma.S2MM       " video/hdmi_in/pixel_pack/stream_out_32
}

set nets_to_debug [list]
foreach {label pin} $targets {
    set n [_net_of_intf_pin $pin]
    if {$n eq ""} {
        puts "  WARN: no net for intf pin '$pin' (label: $label)"
    } else {
        puts "  $label  =>  net $n"
        lappend nets_to_debug $n
    }
}

if {[llength $nets_to_debug] == 0} {
    error "No AXIS nets found to debug — check the intf_pin candidates."
}

# --- 2. Mark each net for debug ----------------------------------------
puts "\n=== Marking nets for MARK_DEBUG ==="
foreach n $nets_to_debug {
    set_property HDL_ATTRIBUTE.MARK_DEBUG true [get_bd_intf_nets $n]
    puts "  marked: $n"
}

# --- 3. Apply the debug automation rule --------------------------------
# This is the IP-Integrator rule that creates a System ILA, hooks AXIS
# monitor slots to each debug-marked net, and auto-routes clk/reset.
# We anchor the ILA's clock to FCLK1 (the AXIS data clock used by all
# the nets we are tracing).
set fclk_vid [get_bd_pins ps7_0/FCLK_CLK1]
puts "\n=== Applying debug automation (clk: $fclk_vid) ==="
foreach n $nets_to_debug {
    set ok [catch {
        apply_bd_automation -rule xilinx.com:bd_rule:debug -dict [list \
            [get_bd_intf_nets $n] [list AXIS_SIGNALS {Data and Trigger} \
                                       CLK_SRC $fclk_vid]]
    } err]
    if {$ok != 0} {
        puts "  WARN: automation on $n: $err"
    } else {
        puts "  debug attached to: $n"
    }
}

# --- 4. Validate + save ------------------------------------------------
puts "\n=== validate + save ==="
regenerate_bd_layout
validate_bd_design
save_bd_design

puts ""
puts "==========================================================="
puts " SYSTEM ILA INSTALLED"
puts "==========================================================="
puts " A system_ila_<N> cell now monitors each AXIS link."
puts " After synth+impl+bitstream, Vivado writes a .ltx probes file"
puts " alongside the .bit (cgra_vtpg.runs/impl_1/debug_nets.ltx)."
puts ""
puts " To use:"
puts "   1. Open Vivado HW Manager"
puts "   2. Program FPGA with the new bitstream"
puts "   3. Right-click on hw_ila_1 → Refresh Device, then Load .ltx"
puts "   4. Set trigger e.g. TVALID rising on v_tpg.m_axis_video"
puts "   5. Capture — waveform shows stall point in the chain"
puts "==========================================================="
