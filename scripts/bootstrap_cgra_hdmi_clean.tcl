# =============================================================================
# bootstrap_cgra_hdmi_clean.tcl
#
# One-shot CGRA+HDMI clean rebuild. Sourced from a fresh Vivado 2025.1 (or
# 2024.1) Tcl console. Creates the project, packages cgra_top, builds the BD,
# runs sanity checks, and (optionally) launches synthesis/implementation.
#
# Required variables (set BEFORE sourcing this file):
#   CGRA_ROOT    Path to the CGRA_project repo (forward slashes)
#                e.g.  C:/Users/thanh/Desktop/CGRA_project
#                or    //wsl.localhost/Ubuntu-22.04/home/vinniny/centos_vm/projects/CGRA_project
#   PROJ_DIR     Where to create the new Vivado project
#                e.g.  C:/Users/thanh/Desktop/CGRA_PYNQ_clean
#   IP_REPOS     List of IP repo paths (Digilent + Wildfire)
#                e.g.  {C:/Users/thanh/Desktop/vivado-library/ip C:/Users/thanh/Desktop/zynq7020_2022/zynq7020/ip_repo}
#
# Optional:
#   PROJ_NAME    default "cgra_hdmi_clean"
#   PART         default xc7z020clg400-1
#   BOARD_PART   default tul.com.tw:pynq-z2:part0:1.0
#   RUN_BUILD    1 to launch synth+impl+write_bitstream after BD save (default 0)
# =============================================================================

# ----- 0. Required vars -------------------------------------------------
foreach var {CGRA_ROOT PROJ_DIR IP_REPOS} {
    if {![info exists $var]} {
        error "Set $var before sourcing this script. See header for example."
    }
}
if {![info exists PROJ_NAME]}  { set PROJ_NAME  "cgra_hdmi_clean" }
if {![info exists PART]}       { set PART       "xc7z020clg400-1" }
if {![info exists BOARD_PART]} { set BOARD_PART "tul.com.tw:pynq-z2:part0:1.0" }
if {![info exists RUN_BUILD]}  { set RUN_BUILD  0 }

puts "==========================================================="
puts " CGRA+HDMI clean rebuild bootstrap"
puts "   Vivado:    [version -short]"
puts "   CGRA_ROOT: $CGRA_ROOT"
puts "   PROJ_DIR:  $PROJ_DIR"
puts "   IP_REPOS:  $IP_REPOS"
puts "==========================================================="

# ----- 1. Create project ------------------------------------------------
file mkdir $PROJ_DIR
create_project -force $PROJ_NAME $PROJ_DIR -part $PART
set_property board_part      $BOARD_PART [current_project]
set_property target_language  Verilog    [current_project]
set_property simulator_language Mixed    [current_project]
set_property default_lib      xil_defaultlib [current_project]

# ----- 2. Add CGRA RTL --------------------------------------------------
puts "\n=== Adding CGRA RTL from $CGRA_ROOT/00_src ==="
if {![file isdirectory $CGRA_ROOT/00_src]} {
    error "CGRA_ROOT/00_src does not exist or is not readable: $CGRA_ROOT/00_src"
}
# Skip axi_ram.sv -- it's a testbench-only memory model, not synthesized.
set rtl_files [list]
foreach f [glob -nocomplain -directory $CGRA_ROOT/00_src *.sv] {
    if {[file tail $f] eq "axi_ram.sv"} { continue }
    lappend rtl_files $f
}
foreach f [glob -nocomplain -directory $CGRA_ROOT/00_src/bsg_mem *.sv] {
    lappend rtl_files $f
}
foreach f [glob -nocomplain -directory $CGRA_ROOT/00_src/bsg_mem *.v] {
    lappend rtl_files $f
}
puts "  Glob found [llength $rtl_files] RTL file(s):"
foreach f $rtl_files { puts "    $f" }
if {[llength $rtl_files] == 0} {
    error "No RTL files found at $CGRA_ROOT/00_src. Check the path is visible to Vivado (try [file readable $CGRA_ROOT/00_src/cgra_top.sv])."
}
add_files -norecurse -fileset sources_1 $rtl_files
set added [llength [get_files -of [get_filesets sources_1] -filter {FILE_TYPE == "SystemVerilog"}]]
if {$added < [llength $rtl_files]} {
    puts "  WARNING: only $added of [llength $rtl_files] files visible after add_files"
}
set_property top cgra_top [current_fileset]
update_compile_order -fileset sources_1
puts "  Added $added RTL files (SystemVerilog). Top = cgra_top."

# ----- 3. Package cgra_top as IP ----------------------------------------
puts "\n=== Packaging cgra_top as IP-XACT ==="
set IP_REPO "$PROJ_DIR/cgra_ip_repo"
file mkdir $IP_REPO
source $CGRA_ROOT/scripts/package_cgra_ip.tcl

# ----- 4. Re-open the project and register all IP repos ------------------
# package_cgra_ip.tcl runs in -in_memory and closes; re-open ours.
open_project $PROJ_DIR/$PROJ_NAME.xpr
set all_repos [concat [list $IP_REPO] $IP_REPOS]
set_property ip_repo_paths $all_repos [current_project]
update_ip_catalog
puts "  Registered IP repos: $all_repos"

# ----- 5. Add HDMI constraints ------------------------------------------
puts "\n=== Adding constrs_pynq_z2.xdc ==="
set xdc "$CGRA_ROOT/01_bench/constrs_pynq_z2.xdc"
if {![file exists $xdc]} {
    error "Missing $xdc"
}
add_files -fileset constrs_1 $xdc

# ----- 6. Build the BD --------------------------------------------------
puts "\n=== Building the BD ==="
source $CGRA_ROOT/scripts/build_cgra_hdmi_pynqz2_clean.tcl

# ----- 7. Make wrapper --------------------------------------------------
puts "\n=== Generating wrapper ==="
make_wrapper -files [get_files design_1.bd] -top -force
add_files -norecurse [glob $PROJ_DIR/$PROJ_NAME.gen/sources_1/bd/design_1/hdl/design_1_wrapper.*]
set_property top design_1_wrapper [current_fileset]
update_compile_order -fileset sources_1

# ----- 8. Sanity check --------------------------------------------------
puts "\n=== Running sanity check ==="
source $CGRA_ROOT/scripts/sanity_check_cgra_hdmi.tcl

# ----- 9. Optional: launch synth + impl ---------------------------------
if {$RUN_BUILD} {
    puts "\n=== Launching synth + impl + bitstream ==="
    launch_runs synth_1 -jobs 8
    wait_on_run synth_1
    launch_runs impl_1 -to_step write_bitstream -jobs 8
    wait_on_run impl_1
    puts "Bitstream: $PROJ_DIR/$PROJ_NAME.runs/impl_1/design_1_wrapper.bit"
} else {
    puts ""
    puts "==========================================================="
    puts " BOOTSTRAP DONE. To build:"
    puts "   launch_runs synth_1 -jobs 8 ; wait_on_run synth_1"
    puts "   launch_runs impl_1 -to_step write_bitstream -jobs 8"
    puts "   wait_on_run impl_1"
    puts " Or from the GUI: Generate Bitstream."
    puts "==========================================================="
}
