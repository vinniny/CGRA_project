# =============================================================================
# add_separate_hdmi_in_vdma.tcl — Split the shared HDMI VDMA into two so the
# HDMI-OUT MM2S timing isn't perturbed every time HDMI-IN S2MM is reconfigured.
#
# Why: the cgra_pynq_base BD has ONE axi_vdma serving both channels
# (MM2S → HDMI-out, S2MM ← HDMI-in). Per PG020 §6.4, DMACR.Reset on either
# channel resets the WHOLE IP. Tonight's silicon test shows this breaks the
# HDMI-OUT display whenever the LIVE_INPUT path re-inits VDMA.
#
# Fix: add a second axi_vdma (`axi_vdma_in`, S2MM-only) dedicated to HDMI-IN.
# Re-route pixel_pack → axi_vdma_in. Disable S2MM on the original VDMA.
# HDMI-OUT now runs uninterrupted on its own dedicated VDMA.
#
# Apply AFTER sourcing base.tcl, BEFORE wrapper/synth.
# =============================================================================

puts "==========================================================="
puts " ADD SEPARATE HDMI-IN VDMA"
puts "==========================================================="

if {[catch {current_bd_design} cur_bd]} {
    error "No open BD — source base.tcl first."
}
puts "  BD in scope: $cur_bd"

# ----- 1. Find handles --------------------------------------------------
set old_vdma [get_bd_cells /video/axi_vdma]
if {[llength $old_vdma] == 0} {
    error "Could not find /video/axi_vdma"
}
puts "  existing VDMA: $old_vdma"

# Drill into /video so we can wire local interconnections
current_bd_design $cur_bd
set ctrl_sc [get_bd_cells /ps7_0_axi_periph]
if {[llength $ctrl_sc] == 0} {
    error "Could not find /ps7_0_axi_periph"
}

# ----- 2. Disable S2MM on the existing VDMA ----------------------------
puts "\n=== 2. Disable S2MM on existing VDMA ==="
set_property -dict [list \
    CONFIG.c_include_s2mm {0} \
    CONFIG.c_include_s2mm_dre {0} \
    CONFIG.c_include_s2mm_sf {0} \
    CONFIG.c_num_fstores {3} \
    CONFIG.c_s2mm_genlock_mode {0} \
    CONFIG.c_s2mm_linebuffer_depth {512} \
] $old_vdma
puts "  $old_vdma now MM2S-only (HDMI-OUT)"

# ----- 3. Create new HDMI-IN VDMA --------------------------------------
puts "\n=== 3. Create axi_vdma_in (S2MM only) ==="
set new_vdma [create_bd_cell -type ip \
    -vlnv xilinx.com:ip:axi_vdma:6.3 /video/axi_vdma_in]
set_property -dict [list \
    CONFIG.c_include_mm2s         {0}    \
    CONFIG.c_include_mm2s_dre     {0}    \
    CONFIG.c_include_mm2s_sf      {0}    \
    CONFIG.c_include_s2mm         {1}    \
    CONFIG.c_include_s2mm_dre     {0}    \
    CONFIG.c_include_s2mm_sf      {1}    \
    CONFIG.c_m_axi_s2mm_data_width   {64}    \
    CONFIG.c_s_axis_s2mm_tdata_width {32}    \
    CONFIG.c_num_fstores           {4}    \
    CONFIG.c_s2mm_genlock_mode     {0}    \
    CONFIG.c_s2mm_linebuffer_depth {4096} \
    CONFIG.c_s2mm_max_burst_length {32}   \
    CONFIG.c_include_sg            {0}    \
] $new_vdma
puts "  $new_vdma created (S2MM-only)"

# ----- 4. Re-wire AXIS: pixel_pack -> new VDMA -------------------------
puts "\n=== 4. AXIS rewire ==="
# Find the AXIS net currently feeding the old VDMA's S_AXIS_S2MM. Inside
# the hdmi_in hierarchy it surfaces as `out_stream` and connects upstream
# to `/video/axi_vdma/S_AXIS_S2MM`.
set old_s2mm_pin [get_bd_intf_pins /video/axi_vdma/S_AXIS_S2MM]
set old_net [get_bd_intf_nets -of_objects $old_s2mm_pin]
if {[llength $old_net] > 0} {
    puts "  removing old AXIS net: $old_net"
    delete_bd_objs $old_net
}

# pixel_pack's output surfaces at /video/hdmi_in/out_stream (the
# hierarchy pin). We connect that to the new VDMA's S_AXIS_S2MM.
connect_bd_intf_net \
    [get_bd_intf_pins /video/hdmi_in/out_stream] \
    [get_bd_intf_pins $new_vdma/S_AXIS_S2MM]
puts "  hdmi_in/out_stream -> axi_vdma_in/S_AXIS_S2MM"

# ----- 5. Re-wire M_AXI: new VDMA -> axi_mem_intercon S00 --------------
puts "\n=== 5. M_AXI rewire ==="
set m_intercon [get_bd_cells /video/axi_mem_intercon]
if {[llength $m_intercon] == 0} {
    error "Could not find /video/axi_mem_intercon"
}

# Remove old S2MM connection between original VDMA's M_AXI_S2MM and intercon
set old_m_axi [get_bd_intf_nets -of_objects \
    [get_bd_intf_pins /video/axi_vdma/M_AXI_S2MM]]
if {[llength $old_m_axi] > 0} {
    puts "  removing old M_AXI_S2MM net: $old_m_axi"
    delete_bd_objs $old_m_axi
}
# (M_AXI_S2MM port disappears since c_include_s2mm = 0)

# Connect new VDMA's M_AXI_S2MM to axi_mem_intercon S00_AXI (was the
# original S2MM's slot, now free for the new VDMA)
connect_bd_intf_net \
    [get_bd_intf_pins $new_vdma/M_AXI_S2MM] \
    [get_bd_intf_pins $m_intercon/S00_AXI]
puts "  axi_vdma_in/M_AXI_S2MM -> axi_mem_intercon/S00_AXI"

# ----- 6. Clocks + resets ----------------------------------------------
puts "\n=== 6. Clocks + resets ==="
# AXIS data path runs on FCLK1 (the 142.857 MHz video clock; same as
# existing pixel_pack output side).
set fclk1     [get_bd_pins /ps7_0/FCLK_CLK1]
set fclk0     [get_bd_pins /ps7_0/FCLK_CLK0]
set rstn_vid  [get_bd_pins /rst_ps7_0_fclk1/peripheral_aresetn]
set rstn_ctrl [get_bd_pins /rst_ps7_0_fclk0/peripheral_aresetn]

# axi_vdma has these clock/reset pins:
#   s_axi_lite_aclk / s_axi_lite_aresetn  (S_AXI_LITE control)
#   s_axis_s2mm_aclk                       (S2MM input AXIS)
#   m_axi_s2mm_aclk                        (S2MM output AXI master)
# Plus optional m_axis_mm2s_aclk / m_axi_mm2s_aclk (we disabled MM2S).
connect_bd_net $fclk0     [get_bd_pins $new_vdma/s_axi_lite_aclk]
connect_bd_net $rstn_ctrl [get_bd_pins $new_vdma/axi_resetn]
connect_bd_net $fclk1     [get_bd_pins $new_vdma/s_axis_s2mm_aclk]
connect_bd_net $fclk1     [get_bd_pins $new_vdma/m_axi_s2mm_aclk]
puts "  $new_vdma clocks wired (FCLK1 data, FCLK0 ctrl)"

# ----- 7. S_AXI_LITE control via axi_interconnect_0 --------------------
puts "\n=== 7. S_AXI_LITE control ==="
# axi_interconnect_0 (the HDMI-side AXI control bus, NOT ps7_0_axi_periph)
# currently has M00..M03_AXI used. Grow NUM_MI by 1 to fit the new VDMA's
# S_AXI_LITE.
set hdmi_intercon [get_bd_cells /video/axi_interconnect_0]
if {[llength $hdmi_intercon] == 0} {
    error "Could not find /video/axi_interconnect_0"
}
set num_mi [get_property CONFIG.NUM_MI $hdmi_intercon]
set new_num [expr {$num_mi + 1}]
set_property CONFIG.NUM_MI $new_num $hdmi_intercon
set new_mi [format "M%02d_AXI" $num_mi]
puts "  grew /video/axi_interconnect_0 NUM_MI $num_mi -> $new_num (new MI: $new_mi)"

connect_bd_intf_net \
    [get_bd_intf_pins $hdmi_intercon/$new_mi] \
    [get_bd_intf_pins $new_vdma/S_AXI_LITE]

# Wire new MI clock + reset (FCLK0 = 100 MHz control clock)
set new_aclk_pin   [get_bd_pins $hdmi_intercon/[format "M%02d_ACLK" $num_mi]]
set new_arstn_pin  [get_bd_pins $hdmi_intercon/[format "M%02d_ARESETN" $num_mi]]
if {[llength $new_aclk_pin]  > 0} { connect_bd_net $fclk0      $new_aclk_pin }
if {[llength $new_arstn_pin] > 0} { connect_bd_net $rstn_ctrl  $new_arstn_pin }
puts "  $new_mi clock/reset wired"

# ----- 8. Address assignment -------------------------------------------
puts "\n=== 8. Address assignment ==="
# Assign new VDMA's S_AXI_LITE at 0x43020000 (free slot next to original
# VDMA at 0x43000000).
assign_bd_address -offset 0x43020000 -range 64K \
    [get_bd_addr_segs $new_vdma/S_AXI_LITE/Reg]

# CRITICAL: the new VDMA's M_AXI_S2MM master MUST be explicitly mapped
# to ps7_0/S_AXI_HP0/HP0_DDR_LOWOCM with the SAME 256 MB DDR window the
# original axi_vdma used (0x1000_0000 - 0x1FFF_FFFF). Without this,
# every S2MM write triggers an AXI decode error -> DMASR.DMADecErr=1 ->
# VDMA halts. (Silicon-validated 2026-05-26: previous build with auto-
# routing produced exactly this fault.)
assign_bd_address -offset 0x10000000 -range 0x10000000 \
    -target_address_space [get_bd_addr_spaces $new_vdma/Data_S2MM] \
    [get_bd_addr_segs ps7_0/S_AXI_HP0/HP0_DDR_LOWOCM] -force
puts "  $new_vdma/S_AXI_LITE @ 0x43020000"
puts "  $new_vdma/Data_S2MM -> ps7_0/S_AXI_HP0 @ 0x10000000 (256 MB)"

# ----- 9. Validate + save ----------------------------------------------
puts "\n=== 9. Validate + save ==="
regenerate_bd_layout
validate_bd_design
save_bd_design

puts ""
puts "==========================================================="
puts " SEPARATE HDMI-IN VDMA INSTALLED"
puts "==========================================================="
puts " HDMI-IN VDMA  S_AXI_LITE @ 0x43020000  (new — driver target)"
puts " HDMI-OUT VDMA S_AXI_LITE @ 0x43000000  (unchanged)"
puts ""
puts " SW change required: hdmi_in_bm.h VDMA_IN_BASE -> 0x43020000"
puts "==========================================================="
