# =============================================================================
# audit_bd_report.tcl — Load an already-built BD project and emit a full audit.
#
# Fast variant of audit_bd.tcl: assumes the project at $VPROJ_DIR already
# exists (e.g. after create_synth_project.tcl Stage B finishes) and just
# generates the connectivity / address / IRQ reports.
#
# Usage:
#   CGRA_VPROJ=$HOME/vivado_projects/cgra_hdmi_synth_test \
#     /tools/Xilinx/2025.1/Vivado/bin/vivado -mode batch \
#       -source scripts/audit_bd_report.tcl \
#       -log /tmp/cgra_audit.log -journal /tmp/cgra_audit.jou
# =============================================================================

proc _env_or_default {name def} {
    if {[info exists ::env($name)]} { return $::env($name) }
    return $def
}
set VPROJ_DIR [_env_or_default CGRA_VPROJ "$::env(HOME)/vivado_projects/cgra_hdmi_synth_test"]

set xpr [glob -nocomplain "$VPROJ_DIR/*.xpr"]
if {$xpr eq ""} {
    error "No .xpr at $VPROJ_DIR. Run create_synth_project.tcl Stage A or B first."
}
puts "==========================================================="
puts " BD AUDIT REPORT — loading $xpr"
puts "==========================================================="

set_param general.maxThreads 2
open_project [lindex $xpr 0]
open_bd_design [glob -directory "$VPROJ_DIR/cgra_hdmi_synth.srcs/sources_1/bd/design_1" "design_1.bd"]

# ----- 1. ADDRESS MAP ---------------------------------------------------
puts ""
puts "==========================================================="
puts " 1. ADDRESS MAP (M_AXI_GP0 → slave segments)"
puts "==========================================================="
puts [format "  %-55s %-12s %-10s" "SEGMENT" "OFFSET" "RANGE"]
puts [format "  %-55s %-12s %-10s" [string repeat - 55] [string repeat - 12] [string repeat - 10]]
set segs [get_bd_addr_segs -filter {USAGE == register || USAGE == memory}]
set sorted [list]
foreach seg $segs {
    set off [get_property OFFSET $seg]
    if {$off ne ""} { lappend sorted [list $off $seg] }
}
set sorted [lsort -integer -index 0 $sorted]
foreach entry $sorted {
    lassign $entry off seg
    set rng [get_property RANGE $seg]
    set short [string trimleft $seg "/"]
    puts [format "  %-55s 0x%-10x %-10s" $short $off $rng]
}

# ----- 2. IRQ_F2P ROUTING -----------------------------------------------
puts ""
puts "==========================================================="
puts " 2. IRQ_F2P (xlconcat_0 → PS7)"
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
    set src ""
    foreach p [get_bd_pins -of_objects $net] {
        if {$p ne $inpin} { set src $p; break }
    }
    puts [format "    In%d  →  IRQ_F2P\[%d\]  driven by  %s" $i $i $src]
}

# ----- 3. CLOCK DOMAINS -------------------------------------------------
puts ""
puts "==========================================================="
puts " 3. CLOCK DOMAINS"
puts "==========================================================="
set clk_pins [get_bd_pins -filter {TYPE == clk}]
array unset clk_groups
foreach cp $clk_pins {
    set net [get_bd_nets -of_objects $cp]
    set key [expr {$net eq "" ? "__unconnected__" : [get_property NAME $net]}]
    lappend clk_groups($key) $cp
}
foreach netname [lsort [array names clk_groups]] {
    set count [llength $clk_groups($netname)]
    puts "  Clock net: $netname  ($count sinks)"
    foreach p $clk_groups($netname) {
        puts "    └─ $p"
    }
}

# ----- 4. RESET POLARITY AUDIT ------------------------------------------
puts ""
puts "==========================================================="
puts " 4. RESET PINS (polarity-mismatch hunt)"
puts "==========================================================="
puts [format "  %-60s %-15s %s" "PIN" "POLARITY" "NET"]
puts [format "  %-60s %-15s %s" [string repeat - 60] [string repeat - 15] [string repeat - 30]]
set mismatches 0
foreach rp [get_bd_pins -filter {TYPE == rst}] {
    set pol [get_property POLARITY $rp]
    set net [get_bd_nets -of_objects $rp]
    set netname "(unconnected)"
    if {$net ne ""} {set netname [get_property NAME $net]}
    # Heuristic: any pin whose name contains "n" (aresetn, rst_n, ...) should
    # be ACTIVE_LOW; otherwise ACTIVE_HIGH. Flag mismatches.
    set pname [get_property NAME $rp]
    set expected ""
    if {[regexp {(?i)(_n$|aresetn|rst_n|_low)} $pname]} {
        set expected "ACTIVE_LOW"
    } elseif {[regexp {(?i)(reset$|rst$|_high)} $pname]} {
        set expected "ACTIVE_HIGH"
    }
    set mark ""
    if {$expected ne "" && $pol ne $expected} {
        set mark "  ⚠ NAME suggests $expected"
        incr mismatches
    }
    puts [format "  %-60s %-15s %s%s" $rp $pol $netname $mark]
}
puts "  Total likely-mismatches: $mismatches"

# ----- 5. AXI FABRIC ----------------------------------------------------
puts ""
puts "==========================================================="
puts " 5. AXI FABRIC (smartconnects + interconnects)"
puts "==========================================================="
foreach sc [get_bd_cells -filter {VLNV =~ "*smartconnect*" || VLNV =~ "*axi_interconnect*"}] {
    set num_si [get_property CONFIG.NUM_SI $sc]
    set num_mi [get_property CONFIG.NUM_MI $sc]
    puts "  $sc  (NUM_SI=$num_si, NUM_MI=$num_mi)"
    for {set i 0} {$i < $num_si} {incr i} {
        set sfx [format "S%02d_AXI" $i]
        set p [get_bd_intf_pins $sc/$sfx]
        if {$p eq ""} continue
        set net [get_bd_intf_nets -of_objects $p]
        if {$net eq ""} { puts "    $sfx  ←  (unconnected)" ; continue }
        set ends [get_bd_intf_pins -of_objects $net]
        set src ""
        foreach e $ends { if {$e ne $p} {set src $e; break} }
        puts "    $sfx  ←  $src"
    }
    for {set i 0} {$i < $num_mi} {incr i} {
        set sfx [format "M%02d_AXI" $i]
        set p [get_bd_intf_pins $sc/$sfx]
        if {$p eq ""} continue
        set net [get_bd_intf_nets -of_objects $p]
        if {$net eq ""} { puts "    $sfx  →  (unconnected)" ; continue }
        set ends [get_bd_intf_pins -of_objects $net]
        set dst ""
        foreach e $ends { if {$e ne $p} {set dst $e; break} }
        puts "    $sfx  →  $dst"
    }
}

# ----- 6. UNDRIVEN PINS -------------------------------------------------
puts ""
puts "==========================================================="
puts " 6. UNDRIVEN REQUIRED INPUTS (ignore opt/aux pins)"
puts "==========================================================="
set unconn 0
foreach cell [get_bd_cells -hierarchical -filter {TYPE == ip}] {
    foreach p [get_bd_pins -of_objects $cell -filter {DIR == I && TYPE != data && TYPE != ud}] {
        if {[get_bd_nets -of_objects $p] eq ""} {
            puts "  [get_property NAME $cell]/[get_property NAME $p]   TYPE=[get_property TYPE $p]"
            incr unconn
        }
    }
}
if {$unconn == 0} {
    puts "  (none — every required input is driven)"
}

# ----- 7. EXTERNAL PORTS ------------------------------------------------
puts ""
puts "==========================================================="
puts " 7. EXTERNAL PORTS (board pins via XDC)"
puts "==========================================================="
foreach pt [get_bd_ports] {
    set dir [get_property DIR $pt]
    set ll [get_property LEFT $pt]
    set rr [get_property RIGHT $pt]
    if {$ll eq "" || $rr eq ""} {
        puts [format "  %-25s DIR=%-3s width=1" $pt $dir]
    } else {
        puts [format "  %-25s DIR=%-3s width=%d \[%d:%d\]" $pt $dir [expr {abs($ll-$rr)+1}] $ll $rr]
    }
}

# ----- 8. SUMMARY -------------------------------------------------------
puts ""
puts "==========================================================="
puts " 8. SUMMARY"
puts "==========================================================="
puts "  Total BD cells:     [llength [get_bd_cells]]"
puts "  Total nets:         [llength [get_bd_nets]]"
puts "  Total intf_nets:    [llength [get_bd_intf_nets]]"
puts "  Total addr segs:    [llength [get_bd_addr_segs]]"
puts "  Total ports:        [llength [get_bd_ports]]"
puts ""
puts " AUDIT COMPLETE — review above carefully before silicon."
puts "==========================================================="

close_bd_design [current_bd_design]
close_project
