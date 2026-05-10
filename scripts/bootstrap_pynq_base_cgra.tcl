# =============================================================================
# bootstrap_pynq_base_cgra.tcl
#
# One-shot CGRA-on-PYNQ-base rebuild. Sourced from a fresh Vivado 2024.1 (or
# 2025.1) Tcl console. This is the "official" path: PYNQ's battle-tested
# base.tcl as the foundation, with CGRA bolted on via add_cgra_to_base.tcl.
#
# vs build_cgra_hdmi_pynqz2_clean.tcl: that script built a custom HDMI BD from
# scratch (modeled on Haoyue). This one uses PYNQ's actual base BD that the
# PYNQ Linux image / Python video library expects -- much higher confidence.
#
# Required vars BEFORE sourcing:
#   CGRA_ROOT     Path to the CGRA_project repo
#   PYNQ_REPO     Path to the PYNQ GitHub repo (must contain boards/Pynq-Z2/)
#   PROJ_DIR      Where to create the new Vivado project
#
# Optional:
#   PROJ_NAME     default "cgra_pynq_base"
#   PART          default xc7z020clg400-1
#   BOARD_PART    default tul.com.tw:pynq-z2:part0:1.0
#   BUILD_HLS_IPS default 1 (run vitis_hls to build the 5 HLS IPs base.tcl
#                 needs: color_convert, pixel_pack, pixel_unpack,
#                 trace_cntrl_32, trace_cntrl_64). Skip with 0 if you already
#                 ran build_ip.tcl and the .zip files are present.
#   STRIP_IOPS    default 1 (delete 4 MicroBlaze IOPs + 2 trace analyzers
#                 from the base BD; saves ~25K LUTs so the design fits the
#                 XC7Z020). Set to 0 to keep the full PYNQ base — the design
#                 will then NOT fit and impl_1 will fail with DRC UTLZ-1.
# =============================================================================

foreach var {CGRA_ROOT PYNQ_REPO PROJ_DIR} {
    if {![info exists $var]} {
        error "Set $var before sourcing this script."
    }
}
if {![info exists PROJ_NAME]}     { set PROJ_NAME     "cgra_pynq_base" }
if {![info exists PART]}          { set PART          "xc7z020clg400-1" }
if {![info exists BOARD_PART]}    { set BOARD_PART    "tul.com.tw:pynq-z2:part0:1.0" }
if {![info exists BUILD_HLS_IPS]} { set BUILD_HLS_IPS 1 }
if {![info exists STRIP_IOPS]}    { set STRIP_IOPS    1 }
# PYNQ-Z2 board files aren't shipped with all Vivado versions. If they're not
# in the current install, point at a sibling install that has them.
if {![info exists BOARD_FILES_PATH]} {
    set candidate_paths [list \
        "D:/Programs/Xilinx/2025.1/data/boards/board_files" \
        "C:/Xilinx/2025.1/data/boards/board_files" \
        "D:/Programs/Xilinx/2024.1/data/boards/board_files" \
        "C:/Xilinx/2024.1/data/boards/board_files" \
    ]
    set BOARD_FILES_PATH ""
    foreach p $candidate_paths {
        if {[file isdirectory $p/pynq-z2]} {
            set BOARD_FILES_PATH $p
            break
        }
    }
    if {$BOARD_FILES_PATH eq ""} {
        puts "  WARN: no PYNQ-Z2 board files found in standard install paths."
    }
}
if {$BOARD_FILES_PATH ne ""} {
    set_param board.repoPaths $BOARD_FILES_PATH
    puts "  board.repoPaths -> $BOARD_FILES_PATH"
}

puts "==========================================================="
puts " CGRA-on-PYNQ-base bootstrap"
puts "   Vivado:    [version -short]"
puts "   CGRA_ROOT: $CGRA_ROOT"
puts "   PYNQ_REPO: $PYNQ_REPO"
puts "   PROJ_DIR:  $PROJ_DIR"
puts "==========================================================="

# ----- 0. Sanity: find PYNQ files ---------------------------------------
set BASE_TCL "$PYNQ_REPO/boards/Pynq-Z2/base/base.tcl"
set BUILD_IP_TCL "$PYNQ_REPO/boards/Pynq-Z2/base/build_ip.tcl"
set IP_REPO_PYNQ "$PYNQ_REPO/boards/ip"
set HLS_DIR "$PYNQ_REPO/boards/ip/hls"
foreach f [list $BASE_TCL $BUILD_IP_TCL $IP_REPO_PYNQ $HLS_DIR] {
    if {![file exists $f]} { error "Missing: $f" }
}

# ----- 1. Build HLS IPs (one-time, ~10-15 min) --------------------------
if {$BUILD_HLS_IPS} {
    puts "\n=== 1. Building PYNQ HLS IPs (vitis_hls) ==="
    set ips_to_check {color_convert pixel_pack pixel_unpack trace_cntrl_32 trace_cntrl_64}
    set need_build 0
    foreach ip $ips_to_check {
        if {![llength [glob -nocomplain $HLS_DIR/$ip/solution1/impl/ip/*.zip]]} {
            puts "  Need to build: $ip"
            incr need_build
        } else {
            puts "  Already built: $ip"
        }
    }
    if {$need_build > 0} {
        # PYNQ's build_ip.tcl uses cd-relative paths; cwd matters.
        set old_cwd [pwd]
        cd "$PYNQ_REPO/boards/Pynq-Z2/base"
        source $BUILD_IP_TCL
        cd $old_cwd
    } else {
        puts "  All $ips_to_check zips present; skipping HLS build."
    }
} else {
    puts "\n=== 1. Skipping HLS IP build (BUILD_HLS_IPS=0) ==="
}

# ----- 2. Package CGRA as IP-XACT (BEFORE main project) -----------------
# create_bd_cell -type module -reference doesn't accept SystemVerilog top
# files in 2024.1, so we must package cgra_top as a proper IP first.
# This runs in its own packaging project (no main project open yet).
puts "\n=== 2. Packaging cgra_top as IP-XACT ==="
set IP_REPO_CGRA "$PROJ_DIR/cgra_ip_repo"
file mkdir $IP_REPO_CGRA
set IP_REPO $IP_REPO_CGRA
source $CGRA_ROOT/scripts/package_cgra_ip.tcl
# package_cgra_ip.tcl closes its packaging project before returning.

# ----- 3. Create main Vivado project ------------------------------------
puts "\n=== 3. Creating Vivado project ==="
create_project -force $PROJ_NAME $PROJ_DIR -part $PART
set_property board_part        $BOARD_PART [current_project]
set_property target_language   Verilog     [current_project]
set_property simulator_language Mixed      [current_project]
set_property default_lib       xil_defaultlib [current_project]

# ----- 4. Register IP repos (CGRA + PYNQ) -------------------------------
puts "\n=== 4. Registering IP repositories ==="
set_property ip_repo_paths [list $IP_REPO_CGRA $IP_REPO_PYNQ] [current_project]
update_ip_catalog

# ----- 5. Source PYNQ base.tcl to build the BD --------------------------
puts "\n=== 5. Sourcing PYNQ base.tcl (this builds the full PYNQ-Z2 BD) ==="
# base.tcl uses cwd-relative ip_repo path "../../ip"; chdir there.
set old_cwd [pwd]
cd "$PYNQ_REPO/boards/Pynq-Z2/base"
source $BASE_TCL
cd $old_cwd

# ----- 6. Bolt CGRA onto the base BD ------------------------------------
# base.tcl overwrote ip_repo_paths with its own '../../ip', dropping the
# CGRA repo. Re-register both before adding CGRA.
puts "\n=== 6. Re-registering IP repos after base.tcl + adding CGRA ==="
set_property ip_repo_paths [list $IP_REPO_CGRA $IP_REPO_PYNQ] [current_project]
update_ip_catalog
source $CGRA_ROOT/scripts/add_cgra_to_base.tcl

# ----- 6b. Slim PYNQ base to fit XC7Z020 -------------------------------
# Full PYNQ base (4 MBs + 2 trace analyzers + IOP glue) plus our CGRA
# is ~66K LUTs vs 53.2K available. Strip the IOP/trace subsystems unless
# the user explicitly disabled it.
if {$STRIP_IOPS} {
    puts "\n=== 6b. Stripping PYNQ IOPs / trace analyzers (LUT fit) ==="
    source $CGRA_ROOT/scripts/strip_pynq_iops.tcl
} else {
    puts "\n=== 6b. STRIP_IOPS=0 — keeping full PYNQ base ==="
    puts "  WARN: design will likely fail impl_1 with DRC UTLZ-1"
}

# ----- 6c. Add PYNQ master XDC (pin LOCs + IOSTANDARDs) ------------------
# Without this, write_bitstream fails with DRC NSTD-1 / UCIO-1 on every
# external port (HDMI, audio, LEDs, switches, buttons, IIC_1, ...).
# The XDC also constrains pmoda_/pmodb_/arduino_/rpi_ ports that we just
# deleted in step 6b — Vivado emits "expects at least one object" critical
# warnings for those (benign; the constraints just no-op).
puts "\n=== 6c. Adding PYNQ master XDC ==="
set PYNQ_XDC "$PYNQ_REPO/boards/Pynq-Z2/base/vivado/constraints/base.xdc"
if {[file exists $PYNQ_XDC]} {
    add_files -fileset constrs_1 -norecurse $PYNQ_XDC
    # PACKAGE_PIN / IOSTANDARD / PULLUP are implementation-only. Marking the
    # XDC as not-used-in-synthesis avoids invalidating an already-finished
    # synth_1 when this script is sourced incrementally.
    set xdc_obj [get_files -of_objects [get_filesets constrs_1] \
                    [file tail $PYNQ_XDC]]
    if {$xdc_obj ne ""} {
        set_property used_in_synthesis false $xdc_obj
        puts "  added $PYNQ_XDC (impl-only)"
    }
} else {
    puts "  WARN: $PYNQ_XDC not found — write_bitstream will fail with NSTD-1/UCIO-1"
}

# ----- 7. Make wrapper --------------------------------------------------
puts "\n=== 7. Generating wrapper ==="
make_wrapper -files [get_files *.bd] -top -force
add_files -norecurse [glob $PROJ_DIR/$PROJ_NAME.gen/sources_1/bd/*/hdl/*_wrapper.*]
set top_wrapper [lindex [glob $PROJ_DIR/$PROJ_NAME.gen/sources_1/bd/*/hdl/*_wrapper.v] 0]
set top_module [file rootname [file tail $top_wrapper]]
set_property top $top_module [current_fileset]
update_compile_order -fileset sources_1
puts "  Top module: $top_module"

puts ""
puts "==========================================================="
puts " BOOTSTRAP COMPLETE"
puts " Next:"
puts "   launch_runs synth_1 -jobs 8"
puts "   wait_on_run synth_1"
puts "   launch_runs impl_1 -to_step write_bitstream -jobs 8"
puts "   wait_on_run impl_1"
puts ""
puts " Bitstream lands at:"
puts "   $PROJ_DIR/$PROJ_NAME.runs/impl_1/${top_module}.bit"
puts "==========================================================="
