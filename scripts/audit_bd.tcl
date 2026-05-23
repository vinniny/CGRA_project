# =============================================================================
# audit_bd.tcl — Comprehensive audit of the cgra_hdmi BD.
#
# Loads the BD in a fresh project and emits a structured report:
#   1. Address map     (every assigned segment with offset/range)
#   2. IRQ map         (every irq source wired into PS7 IRQ_F2P + bit position)
#   3. Clock domains   (every IP and which clock pin it sees, grouped)
#   4. Reset domains   (every IP and reset polarity)
#   5. AXI fabric      (every AXI master and the slave path it routes to)
#   6. Critical missing connections   (pins/intf_pins with no net)
#   7. CRITICAL WARNINGs from validate_bd_design
#
# Usage (Linux, alongside running Stage B):
#   CGRA_AUDIT_VPROJ=$HOME/vivado_projects/cgra_audit \
#     vivado -mode batch -source scripts/audit_bd.tcl -nojournal -nolog
#
# Independent project dir so it doesn't collide with Stage B's project.
# =============================================================================

puts "==========================================================="
puts " BD AUDIT — cgra_hdmi_synth (Vivado [version -short])"
puts "==========================================================="

proc _env_or_default {name def} {
    if {[info exists ::env($name)]} { return $::env($name) }
    return $def
}

set CGRA_ROOT [_env_or_default CGRA_SRC      [pwd]]
set VPROJ_DIR [_env_or_default CGRA_AUDIT_VPROJ "$::env(HOME)/vivado_projects/cgra_audit"]
set IP_REPO   [_env_or_default CGRA_IPREPO   "$::env(HOME)/vivado_projects/cgra_ip_repo"]
set DIG_IP    [_env_or_default CGRA_DIGILENT "/mnt/c/Users/thanh/Desktop/vivado-library/vivado-library-zmod-v1-2019.1-2"]

# IP repo must exist (Stage A or B already packaged the CGRA IP)
if {![file isdirectory $IP_REPO]} {
    error "IP_REPO not found: $IP_REPO — run create_synth_project.tcl Stage A first"
}

set_param general.maxThreads 2

file delete -force $VPROJ_DIR
file mkdir $VPROJ_DIR
create_project -force cgra_audit $VPROJ_DIR -part xc7z020clg400-1
set_property target_language Verilog [current_project]
set_property ip_repo_paths [list $IP_REPO $DIG_IP] [current_project]
update_ip_catalog

# Build the BD (reuses already-packaged CGRA IP).
source "$CGRA_ROOT/scripts/build_cgra_hdmi_pynqz2_clean.tcl"
source "$CGRA_ROOT/scripts/add_hdmi_in_pynqz2.tcl"
# validate_bd_design is already called inside add_hdmi_in_pynqz2.tcl

# ----- 1. Address map ---------------------------------------------------
puts ""
puts "==========================================================="
puts " 1. ADDRESS MAP"
puts "==========================================================="
set master_segs [get_bd_addr_segs -filter {USAGE == register || USAGE == memory}]
puts [format "  %-50s %-12s %-10s" "SEGMENT" "OFFSET" "RANGE"]
foreach seg $master_segs {
    set name   $seg
    set offset [get_property OFFSET $seg]
    set range  [get_property RANGE  $seg]
    if {$offset eq ""} continue
    puts [format "  %-50s 0x%-10x %-10s" $name $offset $range]
}

# ----- 2. IRQ map -------------------------------------------------------
puts ""
puts "==========================================================="
puts " 2. IRQ MAP (xlconcat_0 → PS7 IRQ_F2P)"
puts "==========================================================="
set concat [get_bd_cells xlconcat_0]
set nports [get_property CONFIG.NUM_PORTS $concat]
puts "  xlconcat_0 NUM_PORTS = $nports"
for {set i 0} {$i < $nports} {incr i} {
    set inpin [get_bd_pins $concat/In$i]
    set net   [get_bd_nets -of_objects $inpin]
    if {$net eq ""} {
        puts [format "    In%d : (unconnected)" $i]
        continue
    }
    # Find driving pin (other end of net, excluding xlconcat itself)
    set src ""
    foreach p [get_bd_pins -of_objects $net] {
        if {$p ne $inpin} { set src $p; break }
    }
    puts [format "    In%d : %s   →  PS7 IRQ_F2P\[%d\]" $i $src $i]
}

# ----- 3. Clock domains -------------------------------------------------
puts ""
puts "==========================================================="
puts " 3. CLOCK DOMAINS"
puts "==========================================================="
# Find all clock pins on cells and group by driving net.
set clk_pins [get_bd_pins -filter {TYPE == clk} -of_objects [get_bd_cells *]]
array unset clk_groups
foreach cp $clk_pins {
    set net [get_bd_nets -of_objects $cp]
    if {$net eq ""} {
        lappend clk_groups(__unconnected__) $cp
    } else {
        lappend clk_groups([get_property NAME $net]) $cp
    }
}
foreach netname [lsort [array names clk_groups]] {
    puts "  Net: $netname"
    foreach p $clk_groups($netname) {
        puts "    └─ $p"
    }
}

# ----- 4. Reset domains -------------------------------------------------
puts ""
puts "==========================================================="
puts " 4. RESET DOMAINS (polarity check)"
puts "==========================================================="
set rst_pins [get_bd_pins -filter {TYPE == rst} -of_objects [get_bd_cells *]]
foreach rp $rst_pins {
    set pol [get_property POLARITY $rp]
    set net [get_bd_nets -of_objects $rp]
    set netname "(unconnected)"
    if {$net ne ""} {set netname [get_property NAME $net]}
    puts [format "  %-60s POLARITY=%-12s NET=%s" $rp $pol $netname]
}

# ----- 5. AXI fabric ----------------------------------------------------
puts ""
puts "==========================================================="
puts " 5. AXI FABRIC (smartconnects)"
puts "==========================================================="
foreach sc [get_bd_cells -filter {VLNV =~ "*smartconnect*"}] {
    set num_si [get_property CONFIG.NUM_SI $sc]
    set num_mi [get_property CONFIG.NUM_MI $sc]
    puts "  $sc  (NUM_SI=$num_si, NUM_MI=$num_mi)"
    for {set i 0} {$i < $num_si} {incr i} {
        set sfx [format "S%02d_AXI" $i]
        set p [get_bd_intf_pins $sc/$sfx]
        if {$p eq ""} continue
        set net [get_bd_intf_nets -of_objects $p]
        if {$net eq ""} continue
        set ends [get_bd_intf_pins -of_objects $net]
        set src ""
        foreach e $ends {
            if {$e ne $p} {set src $e; break}
        }
        puts "    $sfx  ←  $src"
    }
    for {set i 0} {$i < $num_mi} {incr i} {
        set sfx [format "M%02d_AXI" $i]
        set p [get_bd_intf_pins $sc/$sfx]
        if {$p eq ""} continue
        set net [get_bd_intf_nets -of_objects $p]
        if {$net eq ""} continue
        set ends [get_bd_intf_pins -of_objects $net]
        set dst ""
        foreach e $ends {
            if {$e ne $p} {set dst $e; break}
        }
        puts "    $sfx  →  $dst"
    }
}

# ----- 6. Unconnected pins ----------------------------------------------
puts ""
puts "==========================================================="
puts " 6. UNCONNECTED PINS (excluding parameters/data)"
puts "==========================================================="
# Look for required (input or clk/rst type) pins with no driver.
set unconnected 0
foreach cell [get_bd_cells -hierarchical -filter {TYPE == ip || TYPE == hier}] {
    foreach p [get_bd_pins -of_objects $cell -filter {DIR == I && TYPE != data && TYPE != ud}] {
        if {[get_bd_nets -of_objects $p] eq ""} {
            puts "  [get_property NAME $cell]/[get_property NAME $p]   (DIR=I TYPE=[get_property TYPE $p])"
            incr unconnected
        }
    }
}
if {$unconnected == 0} {
    puts "  (none — every required input is driven)"
} else {
    puts "  Total: $unconnected unconnected required inputs"
}

# ----- 7. Validate output -----------------------------------------------
puts ""
puts "==========================================================="
puts " 7. validate_bd_design (final pass)"
puts "==========================================================="
if {[catch {validate_bd_design} err]} {
    puts "  ERROR: $err"
} else {
    puts "  OK — no errors."
}

puts ""
puts "==========================================================="
puts " AUDIT COMPLETE"
puts "==========================================================="
