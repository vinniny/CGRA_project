# =============================================================================
# create_synth_project.tcl — synth-only validation of the CGRA + HDMI BD.
#
# Purpose: spin a fresh Vivado project on Linux (or Windows) that
#   1. packages cgra_top as a user IP,
#   2. sources `build_cgra_hdmi_pynqz2_clean.tcl` to build the HDMI-OUT base BD,
#   3. sources `add_hdmi_in_pynqz2.tcl` to graft the HDMI-IN chain on top,
#   4. adds the J10 + J11 pin constraints from `01_bench/constrs_pynq_z2.xdc`,
#   5. validates the BD,
#   6. (optional) launches synth_1 — NO impl, NO bitstream.
#
# The point is to verify the TCL produces a synthesizable design before
# touching the Windows project at C:\Users\thanh\Desktop\CGRA_PYNQ_clean.
# Synth-only is small enough to run inside WSL2 (~10 min, ~4 GB peak RAM).
#
# Usage (Linux batch, walk-away):
#   vivado -mode batch -source scripts/create_synth_project.tcl
#
# Usage (Linux GUI, watch live):
#   vivado -mode gui -source scripts/create_synth_project.tcl
#
# Two stages controlled by env vars:
#   CGRA_SYNTH_STAGE=A  → bootstrap project + BD + validate, then exit (~2 min)
#   CGRA_SYNTH_STAGE=B  → also launch synth_1 (~10–15 min, 2 jobs to stay WSL-friendly)
#   default             → B
#
# Out-of-tree paths (Linux defaults; override via env):
#   CGRA_SRC      = path to this repo                  (default = pwd)
#   CGRA_VPROJ    = where the Vivado project goes      (default = ~/centos_vm/vivado_projects/cgra_hdmi_synth_test)
#   CGRA_IPREPO   = where the packaged CGRA IP lives   (default = ~/centos_vm/vivado_projects/cgra_ip_repo)
#   CGRA_DIGILENT = Digilent vivado-library ROOT       (default = /mnt/c/Users/thanh/Desktop/vivado-library/vivado-library-zmod-v1-2019.1-2)
#                   (must contain both ip/ and if/ subdirs so TMDS bus def is found)
# =============================================================================

puts "==========================================================="
puts " CGRA + HDMI synth-only validation (Vivado [version -short])"
puts "==========================================================="

# ----- 0. Resolve paths --------------------------------------------------
proc _env_or_default {name def} {
    if {[info exists ::env($name)]} { return $::env($name) }
    return $def
}

set CGRA_ROOT [_env_or_default CGRA_SRC      [pwd]]
set VPROJ_DIR [_env_or_default CGRA_VPROJ    "$::env(HOME)/centos_vm/vivado_projects/cgra_hdmi_synth_test"]
set IP_REPO   [_env_or_default CGRA_IPREPO   "$::env(HOME)/centos_vm/vivado_projects/cgra_ip_repo"]
set DIG_IP    [_env_or_default CGRA_DIGILENT "/mnt/c/Users/thanh/Desktop/vivado-library/vivado-library-zmod-v1-2019.1-2"]
set STAGE     [_env_or_default CGRA_SYNTH_STAGE "B"]

puts "  CGRA_ROOT     = $CGRA_ROOT"
puts "  VPROJ_DIR     = $VPROJ_DIR"
puts "  IP_REPO       = $IP_REPO"
puts "  DIG_IP        = $DIG_IP"
puts "  Stage         = $STAGE  (A = BD validate only, B = + synth_1)"

# Sanity checks
foreach req [list "$CGRA_ROOT/00_src/cgra_top.sv" \
                  "$CGRA_ROOT/scripts/package_cgra_ip.tcl" \
                  "$CGRA_ROOT/scripts/build_cgra_hdmi_pynqz2_clean.tcl" \
                  "$CGRA_ROOT/scripts/add_hdmi_in_pynqz2.tcl" \
                  "$CGRA_ROOT/01_bench/constrs_pynq_z2.xdc" \
                  "$DIG_IP"] {
    if {![file exists $req]} {
        error "Required path missing: $req"
    }
}

# Keep WSL2 happy: cap threads.
set_param general.maxThreads 2
puts "  general.maxThreads = 2 (WSL2-friendly)"

# ----- 1. Package the CGRA IP fresh (always — picks up latest RTL) ------
puts "\n=== 1. Package cgra_top as IP ==="
file mkdir $IP_REPO
set ::CGRA_ROOT $CGRA_ROOT
set ::IP_REPO   $IP_REPO
source "$CGRA_ROOT/scripts/package_cgra_ip.tcl"

# package_cgra_ip.tcl closes its temp project before returning.

# ----- 2. Create the synth project --------------------------------------
puts "\n=== 2. Create synth project ==="
file delete -force $VPROJ_DIR
file mkdir $VPROJ_DIR

create_project -force cgra_hdmi_synth $VPROJ_DIR -part xc7z020clg400-1
set_property target_language Verilog [current_project]
# simulator_language stays at default — synth uses source files directly
# (no board preset — board.xml not present on Linux; manual PS7 config in base script covers it)

# Point at the CGRA IP repo + the Digilent IP repo so dvi2rgb/rgb2dvi/axi_dynclk
# are visible in the catalog.
set_property ip_repo_paths [list $IP_REPO $DIG_IP] [current_project]
update_ip_catalog

# ----- 3. Build the BD (HDMI-OUT base + HDMI-IN graft) ------------------
puts "\n=== 3. Build BD: base (HDMI-OUT) + add_hdmi_in (HDMI-IN graft) ==="
# Base script's `apply_bd_automation ... apply_board_preset "1"` may warn
# without the PYNQ-Z2 board file present, but the manual `set_property -dict`
# calls right after configure PS7 correctly regardless. We catch a hard
# failure so the BD build still completes.
if {[catch {source "$CGRA_ROOT/scripts/build_cgra_hdmi_pynqz2_clean.tcl"} err]} {
    puts "  base script raised: $err"
    puts "  inspecting BD state — base may have partially completed."
}
source "$CGRA_ROOT/scripts/add_hdmi_in_pynqz2.tcl"

# ----- 4. Wrapper + constraints ------------------------------------------
puts "\n=== 4. Generate BD wrapper + add constraints ==="
make_wrapper -files [get_files design_1.bd] -top -import
set_property top design_1_wrapper [current_fileset]
add_files -fileset constrs_1 -norecurse "$CGRA_ROOT/01_bench/constrs_pynq_z2.xdc"
update_compile_order -fileset sources_1

# ----- 5. Stage A: validate only -----------------------------------------
puts "\n=== 5. Stage A: validate_bd_design ==="
validate_bd_design
save_bd_design

if {$STAGE eq "A"} {
    puts ""
    puts "==========================================================="
    puts " Stage A complete — BD validates."
    puts " Re-run with CGRA_SYNTH_STAGE=B to launch synth_1."
    puts "==========================================================="
    return
}

# ----- 6. Stage B: synth_1 only ------------------------------------------
puts "\n=== 6. Stage B: launch_runs synth_1 -jobs 2 ==="
launch_runs synth_1 -jobs 2
wait_on_run synth_1

# ----- 7. Report --------------------------------------------------------
puts "\n=== 7. Synth report ==="
set st [get_property STATUS [get_runs synth_1]]
puts "  synth_1 STATUS: $st"
if {[string match "synth_design Complete*" $st] || [string match "*Complete!*" $st]} {
    open_run synth_1 -name synth_1
    set rpt "$VPROJ_DIR/synth_util.rpt"
    report_utilization -file $rpt
    puts "  Utilization report → $rpt"
    # Brief stdout summary too
    report_utilization
} else {
    puts "  synth_1 did NOT complete — inspect $VPROJ_DIR/cgra_hdmi_synth.runs/synth_1/runme.log"
    error "Synthesis failed."
}

puts ""
puts "==========================================================="
puts " DONE — synth-only validation succeeded"
puts " Project: $VPROJ_DIR"
puts " Util:    $VPROJ_DIR/synth_util.rpt"
puts ""
puts " Confidence to proceed on Windows project at"
puts "   C:\\Users\\thanh\\Desktop\\CGRA_PYNQ_clean"
puts " by sourcing scripts/add_hdmi_in_pynqz2.tcl over the existing BD."
puts "==========================================================="
