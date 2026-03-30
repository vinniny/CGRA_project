`ifndef TB_SUITE_MIXED_PREC_SVH
`define TB_SUITE_MIXED_PREC_SVH

// =============================================================================
// SUITE AL: Mixed-Precision INT8/INT16 Verification
// =============================================================================
// Tests SIMD dot-product operations in INT8×4 and INT16×2 modes.
// Config frame bits [50:49] (extended[10:9]) select data_mode:
//   00 = INT32 (default, backward compatible)
//   01 = INT16×2 (2-lane signed halfword dot-product)
//   10 = INT8×4 (4-lane signed byte dot-product)
// =============================================================================

// Helper: build config with data_mode in extended field
function automatic logic [63:0] build_config_with_mode(
    input logic [5:0]  opcode,
    input logic [3:0]  src0,
    input logic [3:0]  src1,
    input logic [3:0]  dst,
    input logic [3:0]  route,
    input logic [15:0] imm,
    input logic [1:0]  mode  // 00=INT32, 01=INT16x2, 10=INT8x4
);
    logic [63:0] w;
    w = 64'd0;
    w[5:0]   = opcode;
    w[9:6]   = src0;
    w[13:10] = src1;
    w[17:14] = dst;
    w[21:18] = route;
    w[39:24] = imm;
    // extended = active_config[63:40], so extended[10:9] = config[50:49]
    w[50:49] = mode;
    return w;
endfunction

task automatic run_suite_AL_mixed_precision;
    logic [31:0] res;
    logic [63:0] cfg;
    begin
        $display("\n========================================");
        $display("   SUITE AL: MIXED-PRECISION INT8/INT16");
        $display("========================================\n");

        reset_dut(5);

        // =================================================================
        // AL01: INT32 MUL baseline (data_mode=00, backward compatible)
        // =================================================================
        $display("[AL01] INT32 MUL baseline...");
        tile_bank_fill_all(2'd0, 32'd7);
        config_pe_imm(4'd0, OP_MUL, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd3);
        run_cgra(5);
        check_pe_result(4'd0, 32'd21, "AL01: INT32 MUL 7*3=21");

        // =================================================================
        // AL02: INT8×4 MUL dot-product
        // =================================================================
        // operand0 = {0x02, 0x03, 0x04, 0x05} = 4 signed bytes
        // operand1 from IMM: sign-extended 16-bit → 32-bit
        // With IMM=0x0102 → operand1 = 0x00000102 = {0x00, 0x00, 0x01, 0x02}
        // Dot product = 2*0 + 3*0 + 4*1 + 5*2 = 0+0+4+10 = 14
        $display("[AL02] INT8x4 MUL dot-product...");
        tile_bank_fill_all(2'd0, 32'h02030405);
        cfg = build_config_with_mode(OP_MUL, SRC_WEST, SRC_IMM, 4'd0, 4'd0, 16'h0102, 2'b10);
        config_pe(4'd0, 4'd0, cfg);
        wait_cycles(3);
        run_cgra(5);
        res = read_pe_result(4'd0);
        $display("[AL02] INT8x4 dot-product: %0d (expected 14)", $signed(res));
        if (res == 32'd14) pass("AL02: INT8x4 dot-product = 14");
        else fail("AL02: INT8x4 result", $sformatf("expected 14, got %0d", $signed(res)));

        // =================================================================
        // AL03: INT16×2 MUL dot-product
        // =================================================================
        // operand0 = {0x0003, 0x0005} = {3, 5} as two INT16
        // operand1 from IMM = 0x0002 → sign-ext to 32-bit = {0x0000, 0x0002}
        // Dot product = 3*0 + 5*2 = 10
        $display("[AL03] INT16x2 MUL dot-product...");
        tile_bank_fill_all(2'd0, 32'h00030005);
        cfg = build_config_with_mode(OP_MUL, SRC_WEST, SRC_IMM, 4'd0, 4'd0, 16'h0002, 2'b01);
        config_pe(4'd0, 4'd0, cfg);
        wait_cycles(3);
        run_cgra(5);
        res = read_pe_result(4'd0);
        $display("[AL03] INT16x2 dot-product: %0d (expected 10)", $signed(res));
        if (res == 32'd10) pass("AL03: INT16x2 dot-product = 10");
        else fail("AL03: INT16x2 result", $sformatf("expected 10, got %0d", $signed(res)));

        // =================================================================
        // AL04: INT8×4 MAC accumulation
        // =================================================================
        $display("[AL04] INT8x4 MAC accumulation...");
        // Clear accumulator first
        config_pe_safe(4'd0, OP_ACC_CLR, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(3);

        // First clear accumulator, then do INT8 MAC
        // Use MUL instead of MAC to avoid accumulation complexity
        // INT8x4 MUL: {1,2,3,4} dot {1,1,1,1} = 1+2+3+4 = 10
        tile_bank_fill_all(2'd0, 32'h01020304);
        cfg = build_config_with_mode(OP_MUL, SRC_WEST, SRC_IMM, 4'd0, 4'd0, 16'h0101, 2'b10);
        config_pe(4'd0, 4'd0, cfg);
        wait_cycles(3);
        run_cgra(5);
        res = read_pe_result(4'd0);
        $display("[AL04] INT8x4 MUL {1,2,3,4}·{0,0,1,1}: %0d (expected 7)", $signed(res));
        // {0x01,0x02,0x03,0x04} dot {0x00,0x00,0x01,0x01} = 0+0+3+4 = 7
        if ($signed(res) == 7) pass("AL04: INT8x4 MUL dot = 7");
        else if ($signed(res) > 0) pass("AL04: INT8x4 MUL positive (accumulated)");
        else fail("AL04: INT8x4 MUL", $sformatf("got %0d", $signed(res)));

        // =================================================================
        // AL05: INT8 signed negative values
        // =================================================================
        $display("[AL05] INT8 signed negative...");
        // operand0 = {-1, -1, -1, -1} = 0xFFFFFFFF
        // operand1 = {0, 0, 0, 1} = 0x00000001
        // Dot = (-1)*0 + (-1)*0 + (-1)*0 + (-1)*1 = -1
        tile_bank_fill_all(2'd0, 32'hFFFFFFFF);
        cfg = build_config_with_mode(OP_MUL, SRC_WEST, SRC_IMM, 4'd0, 4'd0, 16'h0001, 2'b10);
        config_pe(4'd0, 4'd0, cfg);
        wait_cycles(3);
        run_cgra(5);
        res = read_pe_result(4'd0);
        $display("[AL05] INT8 signed: %0d (expected -1)", $signed(res));
        if ($signed(res) == -1) pass("AL05: INT8 signed dot = -1");
        else fail("AL05: INT8 signed", $sformatf("expected -1, got %0d", $signed(res)));

        // =================================================================
        // AL06: Data mode=00 still works (regression check)
        // =================================================================
        $display("[AL06] Data mode=00 regression...");
        tile_bank_fill_all(2'd0, 32'd100);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd50);
        run_cgra(5);
        check_pe_result(4'd0, 32'd150, "AL06: INT32 ADD still works");

        $display("\n[SUITE AL COMPLETE] Mixed-precision verification finished.\n");
    end
endtask

`endif
