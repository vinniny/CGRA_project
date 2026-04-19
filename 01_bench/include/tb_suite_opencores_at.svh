`ifndef TB_SUITE_OPENCORES_AT_SVH
`define TB_SUITE_OPENCORES_AT_SVH
// ==============================================================================
// tb_suite_opencores_at.svh — Suite OAT: OpenCores Adder Tree Parallel Reduction
// ==============================================================================
// Instantiates the OpenCores adder_tree (N=4, DATA_WIDTH=32) as a pipelined
// golden reference model to verify all four CGRA RESULT_ROW outputs simultaneously.
//
// This is the first suite to exercise the full 4×4 PE grid in parallel: all four
// rows compute results concurrently and the adder_tree independently verifies their
// combined sum. Each test checks both individual row correctness (whitebox) and the
// cross-row reduction via the RTL tree adder (2-cycle pipelined).
//
// adder_tree instance:  u_ref_adder_tree in tb_top.sv
// Control signals:      at_data[3:0], at_ena, at_result[33:0]
// Latency:              $clog2(4) = 2 clock cycles with clock_ena=1
// RESULT_WIDTH:         34 bits for N=4, DATA_WIDTH=32
//
// Operand constraints (prevent 34-bit result overflow and sign-extension issues):
//   OAT01: 12-bit per row value     → sum ≤ 4×4095 = 16380 < 2^14
//   OAT02: 12-bit per row a,b pair  → row sum ≤ 8190, total ≤ 32760 < 2^15
//   OAT03: 10-bit per row a,b pair  → product ≤ 2^20, total ≤ 4×2^20 < 2^22
//
// PE topology (all tests use row 0..3, col 2 and/or col 3):
//   pe_id = row×4 + col  (row 0..3, col 0..3)
//   col 3 pe_ids: 3 (row 0), 7 (row 1), 11 (row 2), 15 (row 3)
//   col 2 pe_ids: 2 (row 0), 6 (row 1), 10 (row 2), 14 (row 3)
//
// Tests: 3 groups × 8 LFSR vectors = 24 tests total.
// ==============================================================================

// Helper: feed 4 values into adder_tree, clock 3 times, read result.
// Caller must set at_data[0..3] before calling.
task automatic at_reduce(output logic [33:0] tree_sum);
    at_ena = 1'b1;
    wait_cycles(3);   // $clog2(4)=2 stages + 1 margin
    at_ena = 1'b0;
    tree_sum = at_result;
endtask

task automatic run_suite_OAT_opencores_at;
    logic [31:0] lfsr_state;
    logic [31:0] a, b, c, d;
    logic [31:0] ar, br, cr, dr;  // per-row a,b pairs
    logic [31:0] r0, r1, r2, r3;
    logic [33:0] tree_sum;
    logic [33:0] sw_sum;
    int          i, row;
    string       tname;

    $display("\n--- SUITE OAT: OpenCores Adder Tree Parallel Reduction (24 Tests) ---");

    // =========================================================================
    // OAT01: 4-row PASS0 parallel — each east-edge PE outputs one IMM value.
    //   All four rows execute simultaneously; adder_tree sums all four results.
    // =========================================================================
    $display("[OAT01] 4-row PASS0 parallel output (8 vectors)...");
    lfsr_state = 32'hA5F3_C1B2;

    for (i = 0; i < 8; i++) begin
        lfsr_state = lfsr32_next(lfsr_state); a = lfsr_state & 32'h00000FFF;
        lfsr_state = lfsr32_next(lfsr_state); b = lfsr_state & 32'h00000FFF;
        lfsr_state = lfsr32_next(lfsr_state); c = lfsr_state & 32'h00000FFF;
        lfsr_state = lfsr32_next(lfsr_state); d = lfsr_state & 32'h00000FFF;

        // Configure col-3 PE in each row: PASS0(SRC_IMM=val_r)
        config_pe_imm(4'd3,  OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_NONE, a[15:0]);
        config_pe_imm(4'd7,  OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_NONE, b[15:0]);
        config_pe_imm(4'd11, OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_NONE, c[15:0]);
        config_pe_imm(4'd15, OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_NONE, d[15:0]);
        run_cgra(8);

        // Whitebox: read all four row outputs directly
        r0 = read_pe_result(4'd3);
        r1 = read_pe_result(4'd7);
        r2 = read_pe_result(4'd11);
        r3 = read_pe_result(4'd15);

        // Feed into adder_tree reference model
        at_data[0] = r0; at_data[1] = r1; at_data[2] = r2; at_data[3] = r3;
        at_reduce(tree_sum);
        sw_sum = {2'b00, a} + {2'b00, b} + {2'b00, c} + {2'b00, d};

        tname = $sformatf("OAT01[%0d]: PASS0 a=%0d b=%0d c=%0d d=%0d exp_sum=%0d",
                          i, a, b, c, d, sw_sum);
        if (r0===a && r1===b && r2===c && r3===d && tree_sum===sw_sum) begin
            pass_count++;
            `ifdef TB_VERBOSE
            $display("[PASS] %s tree=0x%09h", tname, tree_sum);
            `endif
        end else begin
            error_count++;
            $display("[FAIL] %s r0=%0d r1=%0d r2=%0d r3=%0d tree=0x%09h",
                     tname, r0, r1, r2, r3, tree_sum);
        end
    end
    $display("[OAT01] Done.");

    // =========================================================================
    // OAT02: 4-row parallel ADD east-chain.
    //   pe[r][2] PASS0(a_r)→East, pe[r][3] ADD(SRC_WEST, IMM=b_r) → a_r+b_r
    //   All four rows run in parallel; adder_tree sums the four row sums.
    // =========================================================================
    $display("[OAT02] 4-row parallel ADD chains (8 vectors)...");

    for (i = 0; i < 8; i++) begin
        // 8 LFSR advances: 2 per row
        lfsr_state = lfsr32_next(lfsr_state); a  = lfsr_state & 32'h00000FFF; // row 0 a
        lfsr_state = lfsr32_next(lfsr_state); ar = lfsr_state & 32'h00000FFF; // row 0 b
        lfsr_state = lfsr32_next(lfsr_state); b  = lfsr_state & 32'h00000FFF; // row 1 a
        lfsr_state = lfsr32_next(lfsr_state); br = lfsr_state & 32'h00000FFF; // row 1 b
        lfsr_state = lfsr32_next(lfsr_state); c  = lfsr_state & 32'h00000FFF; // row 2 a
        lfsr_state = lfsr32_next(lfsr_state); cr = lfsr_state & 32'h00000FFF; // row 2 b
        lfsr_state = lfsr32_next(lfsr_state); d  = lfsr_state & 32'h00000FFF; // row 3 a
        lfsr_state = lfsr32_next(lfsr_state); dr = lfsr_state & 32'h00000FFF; // row 3 b

        // Row 0: pe_id 2 → 3
        config_pe_imm(4'd2,  OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, a[15:0]);
        config_pe_imm(4'd3,  OP_ADD,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, ar[15:0]);
        // Row 1: pe_id 6 → 7
        config_pe_imm(4'd6,  OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, b[15:0]);
        config_pe_imm(4'd7,  OP_ADD,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, br[15:0]);
        // Row 2: pe_id 10 → 11
        config_pe_imm(4'd10, OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, c[15:0]);
        config_pe_imm(4'd11, OP_ADD,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, cr[15:0]);
        // Row 3: pe_id 14 → 15
        config_pe_imm(4'd14, OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, d[15:0]);
        config_pe_imm(4'd15, OP_ADD,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, dr[15:0]);
        run_cgra(8);

        r0 = read_pe_result(4'd3);
        r1 = read_pe_result(4'd7);
        r2 = read_pe_result(4'd11);
        r3 = read_pe_result(4'd15);

        at_data[0] = r0; at_data[1] = r1; at_data[2] = r2; at_data[3] = r3;
        at_reduce(tree_sum);
        sw_sum = ({2'b00,a}+{2'b00,ar}) + ({2'b00,b}+{2'b00,br})
               + ({2'b00,c}+{2'b00,cr}) + ({2'b00,d}+{2'b00,dr});

        tname = $sformatf("OAT02[%0d]: ADD chains exp_sum=%0d", i, sw_sum);
        if (r0===(a+ar) && r1===(b+br) && r2===(c+cr) && r3===(d+dr) && tree_sum===sw_sum) begin
            pass_count++;
            `ifdef TB_VERBOSE
            $display("[PASS] %s tree=0x%09h", tname, tree_sum);
            `endif
        end else begin
            error_count++;
            $display("[FAIL] %s r0=%0d(exp %0d) r1=%0d(exp %0d) r2=%0d(exp %0d) r3=%0d(exp %0d) tree=0x%09h",
                     tname, r0, a+ar, r1, b+br, r2, c+cr, r3, d+dr, tree_sum);
        end
    end
    $display("[OAT02] Done.");

    // =========================================================================
    // OAT03: 4-row parallel dot-product (element-wise MUL then tree sum).
    //   pe[r][2] PASS0(a_r)→East, pe[r][3] MUL(SRC_WEST, IMM=b_r) → a_r×b_r
    //   adder_tree sums the four products → dot product a·b over 4 elements.
    // =========================================================================
    $display("[OAT03] 4-row parallel dot-product MUL + adder_tree (8 vectors)...");

    for (i = 0; i < 8; i++) begin
        lfsr_state = lfsr32_next(lfsr_state); a  = lfsr_state & 32'h000003FF; // row 0 a (10-bit)
        lfsr_state = lfsr32_next(lfsr_state); ar = lfsr_state & 32'h000003FF; // row 0 b
        lfsr_state = lfsr32_next(lfsr_state); b  = lfsr_state & 32'h000003FF; // row 1 a
        lfsr_state = lfsr32_next(lfsr_state); br = lfsr_state & 32'h000003FF; // row 1 b
        lfsr_state = lfsr32_next(lfsr_state); c  = lfsr_state & 32'h000003FF; // row 2 a
        lfsr_state = lfsr32_next(lfsr_state); cr = lfsr_state & 32'h000003FF; // row 2 b
        lfsr_state = lfsr32_next(lfsr_state); d  = lfsr_state & 32'h000003FF; // row 3 a
        lfsr_state = lfsr32_next(lfsr_state); dr = lfsr_state & 32'h000003FF; // row 3 b

        config_pe_imm(4'd2,  OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, a[15:0]);
        config_pe_imm(4'd3,  OP_MUL,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, ar[15:0]);
        config_pe_imm(4'd6,  OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, b[15:0]);
        config_pe_imm(4'd7,  OP_MUL,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, br[15:0]);
        config_pe_imm(4'd10, OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, c[15:0]);
        config_pe_imm(4'd11, OP_MUL,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, cr[15:0]);
        config_pe_imm(4'd14, OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, d[15:0]);
        config_pe_imm(4'd15, OP_MUL,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, dr[15:0]);
        run_cgra(8);

        r0 = read_pe_result(4'd3);
        r1 = read_pe_result(4'd7);
        r2 = read_pe_result(4'd11);
        r3 = read_pe_result(4'd15);

        at_data[0] = r0; at_data[1] = r1; at_data[2] = r2; at_data[3] = r3;
        at_reduce(tree_sum);
        sw_sum = {2'b00,a*ar} + {2'b00,b*br} + {2'b00,c*cr} + {2'b00,d*dr};

        tname = $sformatf("OAT03[%0d]: dot-product exp=%0d", i, sw_sum);
        if (r0===(a*ar) && r1===(b*br) && r2===(c*cr) && r3===(d*dr) && tree_sum===sw_sum) begin
            pass_count++;
            `ifdef TB_VERBOSE
            $display("[PASS] %s tree=0x%09h", tname, tree_sum);
            `endif
        end else begin
            error_count++;
            $display("[FAIL] %s r0=%0d(exp %0d) r1=%0d(exp %0d) r2=%0d(exp %0d) r3=%0d(exp %0d) tree=0x%09h",
                     tname, r0, a*ar, r1, b*br, r2, c*cr, r3, d*dr, tree_sum);
        end
    end
    $display("[OAT03] Done.");

    $display("\n[SUITE OAT COMPLETE] OpenCores adder_tree parallel reduction tests done.\n");
endtask

`endif  // TB_SUITE_OPENCORES_AT_SVH
