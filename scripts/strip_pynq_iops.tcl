# =============================================================================
# strip_pynq_iops.tcl
#
# Slim the PYNQ base BD by deleting the four MicroBlaze IOP subsystems
# (PMODA, PMODB, Arduino, RPi) and the two trace analyzers. Keeps everything
# the CGRA + HDMI demo actually needs:
#   * PS7 + concat_interrupts + system_interrupts
#   * video subsystem (HDMI in + HDMI out + VDMA)
#   * audio_codec_ctrl + clk_wiz_10MHz
#   * board GPIOs: leds_gpio, btns_gpio, switches_gpio, rgbleds_gpio
#   * XADC + Vaux* analog ports
#   * ps7_0_axi_periph (control xbar for HDMI/audio/CGRA)
#   * cgra_top_0 + axi_apb_bridge_0 + smartconnect_cgra (added by add_cgra_to_base)
#
# Why: full PYNQ base + CGRA is ~66K LUTs; XC7Z020 has only 53.2K. The 4 IOPs
# (each ~3-5K LUTs of MB + intc + timers + iic + spi + io_switch + GPIO) plus
# the two trace analyzers (each ~1.5K LUTs of axi_dma + trace_cntrl + FIFO)
# account for the ~13K LUT overage. Stripping them brings the design comfortably
# under budget while preserving the demo path.
#
# Source AFTER add_cgra_to_base.tcl, BEFORE make_wrapper.
# =============================================================================

puts "==========================================================="
puts " strip_pynq_iops — slim PYNQ base for XC7Z020 fit"
puts "==========================================================="

if {[catch {current_bd_design} bd]} {
    error "No BD open. Source bootstrap_pynq_base_cgra.tcl first."
}

# ----- 0. Sanity: critical cells must exist (added by add_cgra_to_base) -----
foreach must {cgra_top_0 axi_apb_bridge_0 smartconnect_cgra ps7_0 video} {
    if {[get_bd_cells -quiet $must] eq ""} {
        error "strip_pynq_iops: required cell '$must' not found. Run add_cgra_to_base.tcl first."
    }
}

# Helper: delete a cell only if it exists.
proc _del_cell {name} {
    set obj [get_bd_cells -quiet $name]
    if {$obj ne ""} {
        puts "  delete cell  $name"
        delete_bd_objs $obj
        return 1
    }
    return 0
}
# Helper: delete an external (intf or scalar) port only if it exists.
proc _del_port {name} {
    set obj [get_bd_intf_ports -quiet $name]
    if {$obj ne ""} {
        puts "  delete iport $name"
        delete_bd_objs $obj
        return 1
    }
    set obj [get_bd_ports -quiet $name]
    if {$obj ne ""} {
        puts "  delete port  $name"
        delete_bd_objs $obj
        return 1
    }
    return 0
}

# ----- 1. Delete top-level hierarchical IOP / trace cells -------------------
# Each delete recursively removes everything inside the hier cell, including
# nested iic_subsystem, spi_subsystem, timers_subsystem, lmb, mb, intc, etc.
puts "\n=== 1. Deleting IOP / trace hierarchical cells ==="
foreach c {iop_arduino iop_pmoda iop_pmodb iop_rpi
           trace_analyzer_pi trace_analyzer_pmodb
           wire_distribution_network} {
    _del_cell $c
}

# ----- 1b. Delete the IOP→GP0 master path -----------------------------------
# In PYNQ base, the four IOPs' MicroBlaze M_AXI masters are aggregated by a
# top-level `axi_interconnect_0` (NUM_SI=4), pass through `address_remap_0`,
# then `axi_protocol_convert_0`, and finally drive `ps7_0/S_AXI_GP0`. With the
# IOPs gone, this entire chain is orphaned — its dangling resets got tied to 0
# by validate_bd_design, which then caused opt_design to fail with
# "[Opt 31-67] LUT1 missing connection on input pin I0" inside the protocol
# converter. Drop the chain and disable PS7 S_AXI_GP0.
puts "\n=== 1b. Deleting IOP → GP0 master path ==="
set gp0_dropped 0
set chain_alive 0
foreach c {axi_interconnect_0 address_remap_0 axi_protocol_convert_0} {
    if {[_del_cell $c]} { incr chain_alive }
}
if {$chain_alive > 0} { set gp0_dropped 1 }

# ----- 2. Delete top-level IOP glue cells -----------------------------------
# These have no consumers once the four IOPs are gone.
puts "\n=== 2. Deleting top-level IOP glue cells ==="
foreach c {iop_interrupts
           mb_iop_pmoda_intr_ack  mb_iop_pmoda_reset
           mb_iop_pmodb_intr_ack  mb_iop_pmodb_reset
           mb_iop_arduino_intr_ack mb_iop_arduino_reset
           mb_iop_rpi_intr_ack    mb_iop_rpi_reset
           mdm_1
           constant_8bit_0
           concat_pmodb concat_rp
           slice_pmodb_gpio
           pmoda_rp_pin_sel} {
    _del_cell $c
}

# ----- 3. Delete external ports tied solely to the IOPs ---------------------
# IIC_1 is NOT in this list — it is driven directly by ps7_0/IIC_1, not via an
# IOP. Audio/HDMI/board-GPIO ports are also kept.
puts "\n=== 3. Deleting IOP-only external ports ==="
foreach p {arduino_direct_iic
           arduino_direct_spi
           arduino_gpio
           pmoda_rpi_gpio
           pmodb_gpio
           rpi_gpio} {
    _del_port $p
}

# ----- 4. Tie disconnected concat_interrupts inputs to constant 0 -----------
# concat_interrupts originally has 7 inputs (In0..In6); add_cgra_to_base bumped
# to 8 (In7 = cgra_top_0/irq). After IOP / trace strip, In1 (trace_pmodb), In2
# (trace_pi), and In4 (iop_interrupts) are dangling. xlconcat with dangling
# inputs is a Vivado critical-warning, so tie them low explicitly.
puts "\n=== 4. Tying dangling concat_interrupts inputs to 0 ==="
set ci [get_bd_cells -quiet concat_interrupts]
if {$ci ne ""} {
    set num_p [get_property CONFIG.NUM_PORTS $ci]
    set tie_pins [list]
    for {set i 0} {$i < $num_p} {incr i} {
        set pin [get_bd_pins -quiet concat_interrupts/In${i}]
        if {$pin eq ""} { continue }
        if {[llength [get_bd_nets -quiet -of_objects $pin]] == 0} {
            puts "  In${i} dangling — tying low"
            lappend tie_pins $pin
        }
    }
    if {[llength $tie_pins] > 0} {
        if {[get_bd_cells -quiet const_zero_irq] eq ""} {
            create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 const_zero_irq
            set_property -dict [list \
                CONFIG.CONST_VAL   {0} \
                CONFIG.CONST_WIDTH {1} \
            ] [get_bd_cells const_zero_irq]
        }
        foreach pin $tie_pins {
            connect_bd_net [get_bd_pins const_zero_irq/dout] $pin
        }
    } else {
        puts "  no dangling inputs"
    }
} else {
    puts "  WARN: concat_interrupts not found"
}

# ----- 5. Drop trace-only HP2 / GP1 interconnects ---------------------------
# In PYNQ base, axi_mem_intercon serves *only* the two trace analyzers'
# M_AXI (S00/S01) routing into ps7_0/S_AXI_HP2. The video subsystem has its
# own internal axi interconnect — NOT this one.
# ps7_0_axi_periph_1 serves *only* the two trace analyzers' s_axi_lite
# control regs from ps7_0/M_AXI_GP1.
# Both are dead after step 1 trace deletes — unconditionally delete and
# disable the matching PS7 interfaces so the PS port logic can be elided.
puts "\n=== 5. Dropping HP2 / GP1 trace interconnects ==="
set hp2_dropped 0
set gp1_dropped 0
if {[_del_cell axi_mem_intercon]}     { set hp2_dropped 1 }
if {[_del_cell ps7_0_axi_periph_1]}   { set gp1_dropped 1 }

set ps7 [get_bd_cells -quiet ps7_0]
if {$ps7 ne ""} {
    set props [list]
    if {$hp2_dropped} { lappend props CONFIG.PCW_USE_S_AXI_HP2 {0} }
    if {$gp1_dropped} { lappend props CONFIG.PCW_USE_M_AXI_GP1 {0} }
    if {$gp0_dropped} { lappend props CONFIG.PCW_USE_S_AXI_GP0 {0} }
    if {[llength $props] > 0} {
        set_property -dict $props $ps7
        puts "  PS7 disabled: [join $props { }]"
    }
}

# ----- 6. Validate + save ---------------------------------------------------
puts "\n=== 6. Validate + save ==="
regenerate_bd_layout
set rc [catch {validate_bd_design -force} msg]
if {$rc != 0} {
    puts "WARN: validate_bd_design returned non-zero — $msg"
    puts "      Check Messages tab. Critical-warning is acceptable; ERROR is not."
}
save_bd_design

puts ""
puts "==========================================================="
puts " strip_pynq_iops COMPLETE"
puts "   Stripped:  4 IOPs + 2 trace analyzers + IOP glue"
puts "              + axi_mem_intercon (HP2) + ps7_0_axi_periph_1 (GP1)"
puts "   Kept:      HDMI in/out + VDMA + audio + board GPIOs + CGRA"
puts ""
puts " Next: make_wrapper -files \[get_files *.bd\] -top -force"
puts "==========================================================="
