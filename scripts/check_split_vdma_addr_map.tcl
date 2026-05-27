# =============================================================================
# check_split_vdma_addr_map.tcl — diagnostic: query the v3b BD's address
# segments to verify the new axi_vdma_in/Data_S2MM is actually routed to
# ps7_0/S_AXI_HP0/HP0_DDR_LOWOCM. Also inspects axi_mem_intercon connectivity.
# Read-only; does not modify the BD.
# =============================================================================
set proj_dir "$::env(HOME)/vivado_projects/cgra_split_vdma"
open_project $proj_dir/cgra_split_vdma.xpr
open_bd_design $proj_dir/cgra_split_vdma.srcs/sources_1/bd/base/base.bd

puts "\n=== Address segments for axi_vdma_in/Data_S2MM ==="
set master_space [get_bd_addr_spaces /video/axi_vdma_in/Data_S2MM]
if {[llength $master_space] == 0} {
    puts "  axi_vdma_in/Data_S2MM NOT FOUND"
} else {
    set segs [get_bd_addr_segs -of_objects $master_space]
    if {[llength $segs] == 0} {
        puts "  NO ADDRESS SEGMENTS ASSIGNED  <-- this is the bug if so"
    }
    foreach seg $segs {
        puts "  $seg"
        puts "    offset = [get_property OFFSET $seg]"
        puts "    range  = [get_property RANGE $seg]"
    }
}

puts "\n=== Address segments for axi_vdma/Data_MM2S (HDMI-out, sanity) ==="
set mm2s [get_bd_addr_spaces /video/axi_vdma/Data_MM2S]
foreach seg [get_bd_addr_segs -of_objects $mm2s] {
    puts "  $seg"
    puts "    offset = [get_property OFFSET $seg]"
    puts "    range  = [get_property RANGE $seg]"
}

puts "\n=== axi_mem_intercon configuration ==="
set ami [get_bd_cells /video/axi_mem_intercon]
puts "  NUM_SI: [get_property CONFIG.NUM_SI $ami]"
puts "  NUM_MI: [get_property CONFIG.NUM_MI $ami]"

puts "\n=== axi_mem_intercon S00 connectivity ==="
foreach pin [get_bd_intf_pins -filter {NAME =~ "S0*_AXI"} -of_objects $ami] {
    set nets [get_bd_intf_nets -of_objects $pin]
    puts "  $pin <- $nets"
    foreach n $nets {
        foreach p [get_bd_intf_pins -of_objects $n] {
            if {$p != $pin} { puts "    other end: $p" }
        }
    }
}

close_project
