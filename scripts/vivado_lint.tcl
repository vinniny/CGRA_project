# ==============================================================================
# vivado_lint.tcl — Vivado RTL elaboration lint
# ==============================================================================
# Runs synth_design -rtl on the synthesizable CGRA sources.
# Catches: inferred latches, multi-driven nets, port-width mismatches,
# unresolved references, and unsynthesizable constructs.
#
# Usage (batch):
#   vivado -mode batch -source scripts/vivado_lint.tcl
# ==============================================================================

# Target device (Zynq-7000 on board)
set part xc7z020clg400-1

# Work in-memory (no project file created)
set_part $part

# ── BSG memory library (must be read first) ──────────────────────────────────
read_verilog -sv {
    00_src/bsg_mem/bsg_defines.sv
    00_src/bsg_mem/bsg_dff.sv
    00_src/bsg_mem/bsg_dff_en.sv
    00_src/bsg_mem/bsg_dff_en_bypass.sv
    00_src/bsg_mem/bsg_mem_1r1w_sync_synth.sv
    00_src/bsg_mem/bsg_mem_1r1w_sync.sv
    00_src/bsg_mem/cgra_config_mem_bsg.sv
}

# ── Synthesizable RTL (axi_ram.sv excluded — testbench model only) ────────────
read_verilog -sv {
    00_src/cgra_pe.sv
    00_src/cgra_tile.sv
    00_src/cgra_config_broadcaster.sv
    00_src/cgra_array.sv
    00_src/cgra_tile_memory.sv
    00_src/cgra_apb_csr.sv
    00_src/cgra_control_unit.sv
    00_src/cgra_dma_engine.sv
    00_src/cgra_dma_chain_ctrl.sv
    00_src/cgra_dma_subsystem.sv
    00_src/cgra_result_fifo.sv
    00_src/cgra_top.sv
}

# ── RTL elaboration (no mapping, no P&R) ──────────────────────────────────────
# -rtl          : elaboration only, no technology mapping
# -no_iobuf     : don't insert IOBUFs (top-level ports aren't board pads here)
# -keep_equivalent_registers : don't optimize away registers during RTL check
synth_design \
    -top cgra_top \
    -part $part \
    -rtl \
    -rtl_skip_ip \
    -no_iobuf

# ── Reports ──────────────────────────────────────────────────────────────────
report_drc             -file 02_log/vivado_lint_drc.rpt
report_methodology     -file 02_log/vivado_lint_methodology.rpt

# Print critical messages to stdout for make summary
puts "\n========== VIVADO LINT: ERRORS & WARNINGS =========="
set msgs [get_msg_config -severity ERROR -count]
puts "Errors  : $msgs"
set msgs [get_msg_config -severity {CRITICAL WARNING} -count]
puts "Critical warnings: $msgs"
set msgs [get_msg_config -severity WARNING -count]
puts "Warnings: $msgs"
puts "Full report → 02_log/vivado_lint_drc.rpt"
puts "            → 02_log/vivado_lint_methodology.rpt"
