# =============================================================================
# package_cgra_ip.tcl
#
# Package cgra_top.sv (and its dependencies) as an IP-XACT IP so it shows up
# in Vivado's IP catalog and can be added to a BD with bus inference for the
# APB slave (s_apb), AXI4 master (m_axi), clock, reset, and interrupt.
#
# Run-once: produces an IP at <IP_REPO>/cgra_top_1.0/. After this, point
# Vivado's ip_repo_paths at <IP_REPO> and the IP will appear under
# "User -> cgra_top". The BD script (build_cgra_hdmi_pynqz2_clean.tcl) then
# instantiates it with create_bd_cell -vlnv xilinx.com:user:cgra_top:1.0.
#
# Usage:
#   1. Open Vivado 2024.1 (or 2025.1).
#   2. set CGRA_ROOT C:/Users/thanh/Desktop/CGRA_project   ;# adjust per host
#   3. set IP_REPO   C:/Users/thanh/Desktop/cgra_ip_repo
#   4. source $CGRA_ROOT/scripts/package_cgra_ip.tcl
# =============================================================================

if {![info exists CGRA_ROOT]} {
    error "Set CGRA_ROOT to the path of the CGRA_project repo before sourcing."
}
if {![info exists IP_REPO]} {
    set IP_REPO "$CGRA_ROOT/../cgra_ip_repo"
    puts "  IP_REPO not set; defaulting to $IP_REPO"
}

file mkdir $IP_REPO
set ip_dir "$IP_REPO/cgra_top_1.0"
file mkdir $ip_dir

# Vivado 2024.1 doesn't allow create_project while another project is open.
if {![catch {current_project} cur_proj]} {
    puts "  Closing currently-open project '$cur_proj' before packaging."
    catch {save_project}
    close_project
}

# Use an on-disk packaging project (NOT -in_memory) so ipx::package_project
# doesn't print "non project mode is not supported" critical warning.
set pkg_proj_dir "$IP_REPO/.cgra_pkg_proj"
file delete -force $pkg_proj_dir
file mkdir $pkg_proj_dir
create_project -force cgra_pkg $pkg_proj_dir -part xc7z020clg400-1

# Build the source list defensively: glob each directory, skip empties.
set pkg_files [list]
foreach f [glob -nocomplain -directory $CGRA_ROOT/00_src *.sv] {
    if {[file tail $f] eq "axi_ram.sv"} { continue }
    lappend pkg_files $f
}
foreach f [glob -nocomplain -directory $CGRA_ROOT/00_src/bsg_mem *.sv] {
    lappend pkg_files $f
}
foreach f [glob -nocomplain -directory $CGRA_ROOT/00_src/bsg_mem *.v] {
    lappend pkg_files $f
}
if {[llength $pkg_files] == 0} {
    error "package_cgra_ip: no RTL files found at $CGRA_ROOT/00_src"
}
puts "  Packaging [llength $pkg_files] RTL files into IP"
add_files -norecurse -fileset sources_1 $pkg_files

set_property top cgra_top [current_fileset]
update_compile_order -fileset sources_1

# ---------- IP packaging ----------
ipx::package_project -root_dir $ip_dir \
                     -vendor xilinx.com -library user -taxonomy /UserIP \
                     -import_files -force

set core [ipx::current_core]
set_property version 1.0 $core
set_property core_revision 1 $core
set_property name cgra_top $core
set_property display_name "CGRA 4x4 Top" $core
# Description must differ from name/display_name or Vivado raises [IP_Flow 19-11888].
set_property description "4x4 reconfigurable accelerator (16 PEs, 21-op ISA, 40b MAC) — APB slave + AXI4 master DMA + GIC IRQ" $core
set_property vendor_display_name "CGRA Project" $core
set_property company_url "https://example.com/cgra" $core

# ---------- Bus interfaces ----------
# ipx::package_project already auto-inferred m_axi (AXI master), clk, rst_n,
# and irq from the standard port names. We just need to:
#   - Group the APB ports into a single bus interface named s_apb
#   - Set ASSOCIATED_BUSIF on clk so it drives both s_apb and m_axi
#
# Helpers:
#   ipx::get_bus_interfaces -of_objects $core <pattern>
#   ipx::get_bus_interfaces -of_objects $core -filter "BUS_TYPE_VLNV =~ *<x>*"
proc _get_ifs {core args} {
    return [ipx::get_bus_interfaces -of_objects $core {*}$args]
}

# Infer APB. Vivado picks an auto-name like "apb_1"; we rename to s_apb.
ipx::infer_bus_interface {psel penable pwrite paddr pwdata prdata pready pslverr} \
    xilinx.com:interface:apb_rtl:1.0 $core
set apb_ifs [_get_ifs $core -filter {BUS_TYPE_VLNV =~ "*:apb*"}]
if {[llength $apb_ifs] != 1} {
    error "Expected exactly 1 APB interface after inference; got [llength $apb_ifs]: $apb_ifs"
}
set apb_name [get_property NAME $apb_ifs]
puts "  Inferred APB interface as '$apb_name'"
if {$apb_name ne "s_apb"} {
    # ipx::rename_bus_interface doesn't exist in 2024.1 -- use set_property
    # on the bus_interface object directly. Falls back to keeping the auto
    # name if Vivado refuses to rename.
    if {[catch {set_property name s_apb $apb_ifs} err]} {
        puts "  WARN: rename failed ($err); keeping auto name '$apb_name'."
        set ::CGRA_APB_BUSIF_NAME $apb_name
    } else {
        puts "  Renamed APB interface to 's_apb'"
        set ::CGRA_APB_BUSIF_NAME s_apb
    }
} else {
    set ::CGRA_APB_BUSIF_NAME s_apb
}
set apb_if [_get_ifs $core $::CGRA_APB_BUSIF_NAME]
set_property interface_mode slave $apb_if

# m_axi: should already exist as auto-inferred. Ensure it's named correctly.
set axi_ifs [_get_ifs $core -filter {BUS_TYPE_VLNV =~ "*:aximm*"}]
if {[llength $axi_ifs] == 1} {
    set axi_name [get_property NAME $axi_ifs]
    if {$axi_name ne "m_axi"} {
        if {[catch {set_property name m_axi $axi_ifs} err]} {
            puts "  WARN: AXI rename failed ($err); keeping '$axi_name'."
            set ::CGRA_AXI_BUSIF_NAME $axi_name
        } else {
            puts "  Renamed AXI interface '$axi_name' -> 'm_axi'"
            set ::CGRA_AXI_BUSIF_NAME m_axi
        }
    } else {
        set ::CGRA_AXI_BUSIF_NAME m_axi
    }
    set_property interface_mode master [_get_ifs $core $::CGRA_AXI_BUSIF_NAME]
} else {
    puts "  WARN: expected 1 AXI master interface, got [llength $axi_ifs]"
    set ::CGRA_AXI_BUSIF_NAME m_axi
}

# Reset polarity and IRQ sensitivity are already auto-set by
# ipx::package_project (POLARITY=ACTIVE_LOW, SENSITIVITY=LEVEL_HIGH -- see
# the [IP_Flow 19-4728] messages above). No further config needed.

# Set ASSOCIATED_BUSIF on clk so Vivado knows clk drives both s_apb and m_axi.
# (When clk was auto-inferred, Vivado likely set ASSOCIATED_BUSIF=m_axi only.)
# Also set FREQ_HZ so downstream Vivado tooling doesn't raise [IP_Flow 19-11770]
# (default 100 MHz matches the FCLK0 in our PS7 config).
set clk_if [_get_ifs $core clk]
if {$clk_if ne ""} {
    set abp [ipx::get_bus_parameters ASSOCIATED_BUSIF -of_objects $clk_if]
    if {$abp eq ""} { ipx::add_bus_parameter ASSOCIATED_BUSIF $clk_if }
    set_property value "$::CGRA_APB_BUSIF_NAME:$::CGRA_AXI_BUSIF_NAME" \
        [ipx::get_bus_parameters ASSOCIATED_BUSIF -of_objects $clk_if]
    set arp [ipx::get_bus_parameters ASSOCIATED_RESET -of_objects $clk_if]
    if {$arp eq ""} { ipx::add_bus_parameter ASSOCIATED_RESET $clk_if }
    set_property value "rst_n" [ipx::get_bus_parameters ASSOCIATED_RESET -of_objects $clk_if]
    set fp [ipx::get_bus_parameters FREQ_HZ -of_objects $clk_if]
    if {$fp eq ""} { ipx::add_bus_parameter FREQ_HZ $clk_if }
    set_property value "100000000" [ipx::get_bus_parameters FREQ_HZ -of_objects $clk_if]
}

# ---------- Save + finalize ----------
ipx::create_xgui_files $core
ipx::update_checksums $core
ipx::save_core $core
ipx::archive_core "$ip_dir/cgra_top_1.0.zip" $core

close_project

puts ""
puts "==========================================================="
puts " cgra_top packaged successfully"
puts "   IP repo:      $IP_REPO"
puts "   Component:    xilinx.com:user:cgra_top:1.0"
puts "   Bus ifs:      s_apb (slave), m_axi (master)"
puts "   Clock+Reset:  clk + rst_n (ACTIVE_LOW), assoc s_apb:m_axi"
puts "   IRQ:          irq (level high)"
puts ""
puts " To use in your project:"
puts "   set_property ip_repo_paths {$IP_REPO} \[current_project\]"
puts "   update_ip_catalog"
puts "   create_bd_cell -type ip -vlnv xilinx.com:user:cgra_top:1.0 cgra_top_0"
puts "==========================================================="
