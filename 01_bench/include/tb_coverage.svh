`ifndef TB_COVERAGE_SVH
`define TB_COVERAGE_SVH

// =============================================================================
// tb_coverage.svh — Functional Coverage Tracking
// =============================================================================
// Manual coverage counters compatible with Xcelium 20.09.
// Tracks DMA transfer patterns, PE ISA usage, and CU flow.
// =============================================================================

// ============================================================================
// DMA Transfer Coverage Counters
// ============================================================================
int cov_dma_read_count  = 0;
int cov_dma_write_count = 0;
int cov_dma_zero_len    = 0;
int cov_dma_cross_4kb   = 0;

task automatic cov_sample_dma(input logic [31:0] src, dst, size, input logic is_write);
    if (is_write) cov_dma_write_count++;
    else          cov_dma_read_count++;
    if (size == 0) cov_dma_zero_len++;
    // Check if transfer crosses 4KB boundary
    if (src[11:0] + size[11:0] > 13'h1000) cov_dma_cross_4kb++;
endtask

// ============================================================================
// PE ISA Coverage Counters (one per opcode)
// ============================================================================
int cov_isa_hit [0:20];

initial begin
    for (int i = 0; i <= 20; i++) cov_isa_hit[i] = 0;
end

task automatic cov_sample_pe(input logic [5:0] op, input logic [3:0] src0, src1,
                              input logic pred_en);
    if (op <= 20) cov_isa_hit[op]++;
endtask

// ============================================================================
// CU Flow Coverage Counters
// ============================================================================
int cov_cu_auto_stop  = 0;
int cov_cu_soft_reset = 0;
int cov_cu_with_loop  = 0;

task automatic cov_sample_cu(input logic [1:0] exit_reason, input logic loop_active);
    if (exit_reason == 0) cov_cu_auto_stop++;
    if (exit_reason == 2) cov_cu_soft_reset++;
    if (loop_active)      cov_cu_with_loop++;
endtask

// ============================================================================
// Coverage Report
// ============================================================================
task automatic print_functional_coverage();
    int isa_covered = 0;
    int isa_total   = 21;

    for (int i = 0; i <= 20; i++)
        if (cov_isa_hit[i] > 0) isa_covered++;

    $display("");
    $display("  4. FUNCTIONAL COVERAGE");
    $display("  ----------------------------------------------------------------");
    $display("    DMA Reads:         %6d", cov_dma_read_count);
    $display("    DMA Writes:        %6d", cov_dma_write_count);
    $display("    DMA Zero-Length:   %6d", cov_dma_zero_len);
    $display("    DMA 4KB Cross:     %6d", cov_dma_cross_4kb);
    $display("    ISA Opcodes Hit:   %3d / %3d (%0.0f%%)",
             isa_covered, isa_total, 100.0 * isa_covered / isa_total);
    $display("    CU Auto-Stop:      %6d", cov_cu_auto_stop);
    $display("    CU Soft-Reset:     %6d", cov_cu_soft_reset);
    $display("    CU With Loop:      %6d", cov_cu_with_loop);
    $display("");
endtask

`endif
