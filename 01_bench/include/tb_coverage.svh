`ifndef TB_COVERAGE_SVH
`define TB_COVERAGE_SVH

// =============================================================================
// tb_coverage.svh — Functional Coverage (covergroups + manual counters)
// =============================================================================
// Uses SystemVerilog covergroups for automated coverage closure tracking.
// Manual counters are retained for backward compatibility and for the
// end-of-simulation summary (covergroup reports go to Xcelium's IMC tool).
//
// NOTE: Xcelium 20.09 limitations:
//   - Auto-bin arrays (bins name[] = {range}) not supported → use single bins
//   - Reserved words (config, medium, large) cannot be bin names
//   - get_coverage() requires -coverage flag at elaboration (make cov)
// =============================================================================

// ============================================================================
// 1. DMA TRANSFER COVERAGE
// ============================================================================

// Manual counters (backward compatible — used by existing TB tasks)
int cov_dma_read_count  = 0;
int cov_dma_write_count = 0;
int cov_dma_zero_len    = 0;
int cov_dma_cross_4kb   = 0;

// Covergroup: DMA transfer characteristics
logic [31:0] cg_dma_src, cg_dma_dst, cg_dma_size;
logic        cg_dma_is_write;

covergroup cg_dma_xfer @(cg_dma_size);
    cp_size : coverpoint cg_dma_size {
        bins sz_single  = {4};
        bins sz_small   = {[8:32]};
        bins sz_medium  = {[36:128]};
        bins sz_big     = {[132:1024]};
        bins sz_xlarge  = {[1028:4096]};
    }
    cp_dir : coverpoint cg_dma_is_write {
        bins rd  = {0};
        bins wr  = {1};
    }
    cp_src_pfx : coverpoint cg_dma_src[31:28] {
        bins axi  = {4'h0};
        bins tile = {4'h1};
        bins cfg  = {4'h2};
    }
    cp_dst_pfx : coverpoint cg_dma_dst[31:28] {
        bins axi  = {4'h0};
        bins tile = {4'h1};
        bins cfg  = {4'h2};
    }
    cx_size_dir : cross cp_size, cp_dir;
endgroup

cg_dma_xfer cg_dma_inst = new;

task automatic cov_sample_dma(input logic [31:0] src, dst, size, input logic is_write);
    if (is_write) cov_dma_write_count++;
    else          cov_dma_read_count++;
    if (size == 0) cov_dma_zero_len++;
    if (src[11:0] + size[11:0] > 13'h1000) cov_dma_cross_4kb++;
    cg_dma_src      = src;
    cg_dma_dst      = dst;
    cg_dma_size     = size;
    cg_dma_is_write = is_write;
endtask

// ============================================================================
// 2. PE ISA COVERAGE
// ============================================================================

int cov_isa_hit [0:20];

initial begin
    for (int i = 0; i <= 20; i++) cov_isa_hit[i] = 0;
end

logic [5:0]  cg_pe_opcode;
logic [3:0]  cg_pe_src0, cg_pe_src1;
logic        cg_pe_pred;

covergroup cg_pe_isa @(cg_pe_opcode);
    cp_opcode : coverpoint cg_pe_opcode {
        bins op_nop       = {0};
        bins op_add       = {1};
        bins op_sub       = {2};
        bins op_mul       = {3};
        bins op_mac       = {4};
        bins op_and       = {5};
        bins op_or        = {6};
        bins op_xor       = {7};
        bins op_shl       = {8};
        bins op_shr       = {9};
        bins op_cmp_gt    = {10};
        bins op_cmp_lt    = {11};
        bins op_cmp_eq    = {12};
        bins op_load_spm  = {13};
        bins op_store_spm = {14};
        bins op_acc_clr   = {15};
        bins op_pass0     = {16};
        bins op_pass1     = {17};
        bins op_lif       = {18};
        bins op_relu      = {19};
        bins op_max       = {20};
    }
    cp_src0 : coverpoint cg_pe_src0 {
        bins s_rf    = {0};
        bins s_north = {1};
        bins s_east  = {2};
        bins s_south = {3};
        bins s_west  = {4};
        bins s_spm   = {5};
        bins s_imm   = {6};
    }
    cp_src1 : coverpoint cg_pe_src1 {
        bins s_rf    = {0};
        bins s_north = {1};
        bins s_east  = {2};
        bins s_south = {3};
        bins s_west  = {4};
        bins s_spm   = {5};
        bins s_imm   = {6};
    }
endgroup

cg_pe_isa cg_isa_inst = new;

task automatic cov_sample_pe(input logic [5:0] op, input logic [3:0] src0, src1,
                              input logic pred_en);
    if (op <= 20) cov_isa_hit[op]++;
    cg_pe_opcode = op;
    cg_pe_src0   = src0;
    cg_pe_src1   = src1;
    cg_pe_pred   = pred_en;
endtask

// ============================================================================
// 3. CU FLOW COVERAGE
// ============================================================================

int cov_cu_auto_stop  = 0;
int cov_cu_soft_reset = 0;
int cov_cu_with_loop  = 0;

logic [1:0] cg_cu_exit;
logic       cg_cu_loop;

covergroup cg_cu_flow @(cg_cu_exit);
    cp_exit : coverpoint cg_cu_exit {
        bins ex_auto_stop  = {0};
        bins ex_timeout    = {1};
        bins ex_soft_reset = {2};
    }
    cp_loop : coverpoint cg_cu_loop {
        bins no_loop   = {0};
        bins with_loop = {1};
    }
    cx_exit_loop : cross cp_exit, cp_loop;
endgroup

cg_cu_flow cg_cu_inst = new;

task automatic cov_sample_cu(input logic [1:0] exit_reason, input logic loop_active);
    if (exit_reason == 0) cov_cu_auto_stop++;
    if (exit_reason == 2) cov_cu_soft_reset++;
    if (loop_active)      cov_cu_with_loop++;
    cg_cu_exit = exit_reason;
    cg_cu_loop = loop_active;
endtask

// ============================================================================
// 4. APB REGISTER ACCESS COVERAGE
// ============================================================================

logic [31:0] cg_apb_addr;
logic        cg_apb_is_write;

covergroup cg_apb_access @(cg_apb_addr);
    cp_addr : coverpoint cg_apb_addr[7:0] {
        bins r_dma_ctrl       = {8'h00};
        bins r_dma_status     = {8'h04};
        bins r_dma_src        = {8'h08};
        bins r_dma_dst        = {8'h0C};
        bins r_dma_size       = {8'h10};
        bins r_dma_stride     = {8'h14};
        bins r_dma_rows       = {8'h18};
        bins r_dma_cols       = {8'h1C};
        bins r_cu_ctrl        = {8'h20};
        bins r_cu_status      = {8'h24};
        bins r_cu_cycles      = {8'h28};
        bins r_cu_timeout     = {8'h2C};
        bins r_irq_status     = {8'h30};
        bins r_irq_mask       = {8'h34};
        bins r_dma_error      = {8'h38};
        bins r_result_data    = {8'h40};
        bins r_result_status  = {8'h44};
        bins r_loop_start     = {8'h48};
        bins r_loop_end       = {8'h4C};
        bins r_loop_count     = {8'h50};
        bins r_result_row0    = {8'h58};
        bins r_result_row1    = {8'h5C};
        bins r_result_row2    = {8'h60};
        bins r_result_row3    = {8'h64};
        bins r_loop2_start    = {8'h68};
        bins r_loop2_end      = {8'h6C};
        bins r_loop2_count    = {8'h70};
        bins r_tile_bank_sel  = {8'h74};
    }
    cp_rw : coverpoint cg_apb_is_write {
        bins rd  = {0};
        bins wr  = {1};
    }
    cx_addr_rw : cross cp_addr, cp_rw;
endgroup

cg_apb_access cg_apb_inst = new;

task automatic cov_sample_apb(input logic [31:0] addr, input logic is_write);
    cg_apb_addr     = addr;
    cg_apb_is_write = is_write;
endtask

// ============================================================================
// 5. COVERAGE REPORT
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
    $display("  ----------------------------------------------------------------");
    $display("    Covergroups: cg_dma_xfer, cg_pe_isa, cg_cu_flow, cg_apb_access");
    $display("    (Run 'make cov' for covergroup metrics via IMC/SimVision)");
    $display("");
endtask

`endif
