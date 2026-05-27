# =============================================================================
# rerun_impl_explore.tcl — reset impl_1, switch to ExploreWithRemap, relaunch.
# Keeps the cached synth_1 outputs so total time is ~15-20 min, not 50.
# =============================================================================
set proj_dir "$::env(HOME)/vivado_projects/cgra_split_vdma"
open_project $proj_dir/cgra_split_vdma.xpr

# Reset just impl_1 (synth_1 stays cached)
reset_run impl_1

# Switch to the ExploreWithRemap strategy — proven to close timing on
# the Procedure-D / v_tpg-style designs where default fails by < 1 ns.
set_property strategy Performance_ExploreWithRemap [get_runs impl_1]

# Relaunch impl + write_bitstream, 2 jobs
launch_runs impl_1 -to_step write_bitstream -jobs 2
wait_on_run impl_1

set st [get_property STATUS [get_runs impl_1]]
if {![string match "*Complete*" $st]} {
    error "Impl failed: $st  See $proj_dir/cgra_split_vdma.runs/impl_1/runme.log"
}

open_run impl_1 -name impl_1
set wns [get_property SLACK [get_timing_paths -delay_type max -nworst 1]]
set whs [get_property SLACK [get_timing_paths -delay_type min -nworst 1]]
report_timing_summary -file $proj_dir/impl_timing_explore.rpt -warn_on_violation

# Re-export .xsa with bitstream
set XSA "$proj_dir/cgra_split_vdma.runs/impl_1/base_wrapper.xsa"
catch {write_hw_platform -fixed -include_bit -force -file $XSA}

puts "==========================================================="
puts " IMPL_1 RE-RUN WITH ExploreWithRemap COMPLETE"
puts " WNS : $wns"
puts " WHS : $whs"
puts "==========================================================="
