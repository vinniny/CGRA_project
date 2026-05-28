# bd_fix_crystal_v3.tcl — delete the unused HDMI/video IPs that are
# locked (Digilent IP repo missing on this machine), then crystal fix,
# then rebuild. HDMI is not used by CGRA → safe to remove for our debug.

set PROJ /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.xpr
set XSA  /home/vinniny/centos_vm/projects/CGRA_project/bitstreams/cgra_top.xsa

puts "==========================================================="
puts " BD CRYSTAL FIX v3 (delete locked HDMI IPs first)"
puts "==========================================================="

open_project $PROJ
set bd_file [lindex [get_files -filter {FILE_TYPE == "Block Designs"}] 0]
open_bd_design $bd_file

# Step 1: Find and delete locked / video-related IPs
puts "\n=== Step 1: Delete unused HDMI/video IPs ==="

# The CGRA-irrelevant cells we can remove:
set to_delete {
    /hdmi_tx_0
    /axi_dynclk_0
    /v_tc_0
    /v_axi4s_vid_out_0
    /axis_subset_rgb
    /rst_pixel_clk
    /axi_vdma_0
    /smartconnect_hp1
    /ddc_high_0
}

# Also delete external HDMI/IIC ports
set ports_to_delete {
    hdmi_tx_clk_n hdmi_tx_clk_p hdmi_tx_data_n hdmi_tx_data_p
    hdmi_tx_hpd hdmi_tx_cec
    iic_main_scl_io iic_main_sda_io
    ddc_scl_io ddc_sda_io
}

foreach cell $to_delete {
    set obj [get_bd_cells -quiet $cell]
    if {[llength $obj] > 0} {
        puts "  Deleting cell: $cell"
        catch {delete_bd_objs [get_bd_intf_nets -of_objects $obj]}
        catch {delete_bd_objs [get_bd_nets -of_objects $obj]}
        catch {delete_bd_objs $obj}
    }
}

foreach port $ports_to_delete {
    set obj [get_bd_intf_ports -quiet $port]
    if {[llength $obj] > 0} {
        puts "  Deleting intf port: $port"
        catch {delete_bd_objs $obj}
    }
    set obj [get_bd_ports -quiet $port]
    if {[llength $obj] > 0} {
        puts "  Deleting port: $port"
        catch {delete_bd_objs $obj}
    }
}

# Step 2: Set the crystal frequency to 50
set ps7 [get_bd_cells -filter {VLNV =~ "*processing_system7:*"}]
puts "\n=== Step 2: Set PCW_CRYSTAL_PERIPHERAL_FREQMHZ = 50 ==="
set_property -dict [list \
    CONFIG.PCW_CRYSTAL_PERIPHERAL_FREQMHZ {50} \
    CONFIG.PCW_USE_S_AXI_HP1 {0} \
    CONFIG.PCW_EN_CLK1_PORT {0} \
    ] $ps7

foreach prop {
    PCW_CRYSTAL_PERIPHERAL_FREQMHZ
    PCW_FPGA0_PERIPHERAL_FREQMHZ
    PCW_USE_S_AXI_HP0
    PCW_USE_S_AXI_HP1
    PCW_UART_PERIPHERAL_FREQMHZ
} {
    catch {puts "  CONFIG.$prop = [get_property CONFIG.$prop $ps7]"}
}

# Step 3: Validate
puts "\n=== Step 3: Validate BD ==="
if {[catch {validate_bd_design} err]} {
    puts "validate_bd_design err: $err"
    puts "Trying to save anyway..."
    save_bd_design
} else {
    puts "  Validation OK"
    save_bd_design
}

# Step 4: Need to update the top wrapper since we removed ports
puts "\n=== Step 4: Re-create top HDL wrapper ==="
catch {make_wrapper -files [get_files $bd_file] -top -force}
set wrapper_file [file join [file dirname $bd_file] hdl design_1_wrapper.v]
if {[file exists $wrapper_file]} {
    catch {add_files -norecurse -force $wrapper_file}
}

# Step 5: Regenerate output products
puts "\n=== Step 5: Regenerate output products ==="
reset_target all [get_files $bd_file]
generate_target all [get_files $bd_file]

# Step 6: Rebuild
puts "\n=== Step 6: Synth + impl + bitgen ==="
catch {reset_run impl_1}
catch {reset_run synth_1}
launch_runs impl_1 -to_step write_bitstream -jobs 6
wait_on_run impl_1
set state [get_property STATUS [get_runs impl_1]]
puts "  impl_1 status: $state"

if {[string match "*Complete*" $state] && ![string match "*ERROR*" $state]} {
    puts "\n=== Step 7: Export .xsa ==="
    write_hw_platform -fixed -include_bit -force $XSA
    puts "  Wrote $XSA ([file size $XSA] bytes)"
} else {
    puts "ERROR: impl did not complete: $state"
}

close_bd_design [get_bd_designs]
close_project
puts "\n==========================================================="
puts " v3 DONE"
puts "==========================================================="
exit
