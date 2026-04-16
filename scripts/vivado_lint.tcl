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

# ── Suppress known-good structural warnings ───────────────────────────────────
# Synth 8-7129 : "Port is unconnected or has no load"
#   88 instances, all by-design:
#   - APB paddr[25:10]: CGRA only decodes bits [7:2]; upper address lines unused
#   - loop_start/end_pc_i[15:4]: CU only uses PC_WIDTH=4 lower bits; upper tied to 0
#   - m_axi_rid/bid[3:0]: AXI response IDs not checked (single-master design)
#   - m_axi_rresp[1:0]: DECERR/SLVERR detection done in DMA engine; rresp OK path only
set_msg_config -id {Synth 8-7129} -new_severity INFO

# Synth 8-11357 : "Potential Runtime issue for 3D-RAM"
#   BSG bsg_mem_1r1w_sync_synth behavioral model inferred as a large register
#   array in -rtl mode. Tile memory: 4 banks × 4096 × 32b = 524288 bits.
#   In real synthesis this maps to BRAM primitives. RTL-mode only artifact.
set_msg_config -id {Synth 8-11357} -new_severity INFO

# ── RTL elaboration (no mapping, no P&R) ──────────────────────────────────────
# -rtl         : elaboration only, no technology mapping
# -no_iobuf    : don't insert IOBUFs (top-level ports aren't board pads here)
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
