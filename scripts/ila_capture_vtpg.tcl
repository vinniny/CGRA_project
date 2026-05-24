# =============================================================================
# ila_capture_vtpg.tcl — Headless Vivado HW Manager ILA capture for the
# v_tpg AXIS chain.
#
# PRECONDITION: the FPGA must already be programmed with cgra_vtpg_ila.bit
# AND demo_vtpg.elf must already be loaded + running on the ARM (so v_tpg
# is configured and pushing data into axis_switch). This is typically done
# via:
#   make run_elf ELF=07_sw/baremetal/demo_vtpg.elf BIT=bitstreams/cgra_vtpg_ila.bit
#
# This script then attaches to the live hw_server (shared with XSDB), loads
# the .ltx probes, arms the System ILA in free-running ALWAYS-capture mode,
# uploads 1024 samples and dumps them as both CSV and VCD.
# =============================================================================

puts "==========================================================="
puts " ILA CAPTURE — v_tpg AXIS chain"
puts " Vivado [version -short]"
puts "==========================================================="

set REPO_ROOT [file normalize [file dirname [info script]]/..]
set LTX_FILE  "$REPO_ROOT/bitstreams/cgra_vtpg_ila.ltx"
if {![file exists $LTX_FILE]} { error "Missing probes file: $LTX_FILE" }

# --- 1. Attach (do NOT re-program — assume XSDB already programmed +
#         loaded ELF). hw_server is shared between Vivado + XSDB. ---
puts "\n=== 1. Attach to live hw_server ==="
open_hw_manager
connect_hw_server -url localhost:3121
set targets [get_hw_targets]
puts "  targets: $targets"
current_hw_target [lindex $targets 0]
open_hw_target
set device [get_hw_devices xc7z020*]
current_hw_device $device
puts "  device: $device"

# Tell Vivado about the probes (without re-programming).
set_property PROBES.FILE      $LTX_FILE $device
set_property FULL_PROBES.FILE $LTX_FILE $device
refresh_hw_device -update_hw_probes false $device
puts "  probes loaded."

# --- 2. Locate ILA + configure free-running capture ---
puts "\n=== 2. Configure ILA for ALWAYS-capture ==="
set ilas [get_hw_ilas]
if {[llength $ilas] == 0} {
    error "No ILA found — was the bitstream actually programmed with the ILA bit?"
}
set ila [lindex $ilas 0]
puts "  ILA: $ila"

set_property CONTROL.TRIGGER_POSITION 0 $ila
catch { set_property CONTROL.DATA_DEPTH 1024 $ila }
catch { set_property CONTROL.WINDOW_COUNT 1 $ila }
catch { set_property CONTROL.CAPTURE_MODE ALWAYS $ila }
catch { set_property CONTROL.TRIGGER_MODE BASIC_ONLY $ila }
# Pick the first 1-bit AXIS TVALID probe and set don't-care -> immediate.
set trig_set 0
foreach pr [get_hw_probes -of_objects $ila] {
    set name [get_property NAME $pr]
    if {[string match "*TVALID*" $name] && [get_property WIDTH $pr] == 1} {
        if {![catch {set_property TRIGGER_COMPARE_VALUE "eq1'bX" $pr}]} {
            puts "  trigger probe (don't-care): $name"
            set trig_set 1
            break
        }
    }
}
if {!$trig_set} {
    puts "  WARN: no TVALID probe found; ILA may not arm without trigger source."
}

# --- 3. Arm + wait + upload ---
puts "\n=== 3. run_hw_ila + wait ==="
run_hw_ila $ila
if {[catch {wait_on_hw_ila -timeout 8 $ila} err]} {
    puts "  WARN: wait_on_hw_ila: $err"
    puts "        (continuing — will try to upload whatever's there)"
}
upload_hw_ila_data $ila
set data [current_hw_ila_data]
puts "  Captured data: $data"

# --- 4. Dump samples ---
puts "\n=== 4. Dump CSV + VCD ==="
set csv "/tmp/ila_capture_vtpg.csv"
set vcd "/tmp/ila_capture_vtpg.vcd"
write_hw_ila_data -csv_file $csv -force $data
write_hw_ila_data -vcd_file $vcd -force $data
puts "  CSV: $csv"
puts "  VCD: $vcd"

# --- 5. Print probe names so the user knows what to look for ---
puts "\n=== 5. ILA probe list ==="
foreach pr [lsort [get_hw_probes -of_objects $ila]] {
    puts "    [get_property NAME $pr]  (W=[get_property WIDTH $pr])"
}

close_hw_target
disconnect_hw_server
puts ""
puts "==========================================================="
puts " ILA CAPTURE COMPLETE"
puts "==========================================================="
