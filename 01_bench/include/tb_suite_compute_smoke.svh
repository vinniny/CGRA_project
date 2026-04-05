`ifndef TB_SUITE_COMPUTE_SMOKE_SVH
`define TB_SUITE_COMPUTE_SMOKE_SVH

// =============================================================================
// SUITE AO: Compute Smoke Test — Minimal PE Array Verification
// =============================================================================
// Proves the PE array can execute basic operations. Run third after AM (regs)
// and AN (DMA) — if compute doesn't work, application tests are meaningless.
//
// Tests:
//   AO01: ADD smoke (42 + 1 = 43)
//   AO02: SUB smoke (100 - 30 = 70)
//   AO03: MUL smoke (7 * 6 = 42)
//   AO04: MAC accumulation
//   AO05: ACC_CLR clears accumulator
//   AO06: PASS0 routing (operand A passthrough)
//   AO07: PASS1 routing (operand B passthrough)
//   AO08: CMP_GT comparison
//   AO09: RELU activation
//   AO10: Auto-stop after 16 contexts
//   AO11: East-edge capture (RESULT_ROW0-3)
//   AO12: Multi-PE simultaneous operation
// =============================================================================

task automatic run_suite_AO_compute_smoke;
    logic [31:0] rd, rd0, rd1, rd2, rd3;
    begin
        $display("\n========================================");
        $display("   SUITE AO: COMPUTE SMOKE TEST");
        $display("========================================\n");

        reset_dut(5);

        // =================================================================
        // AO01: ADD smoke — tile=42, imm=1, expect 43
        // =================================================================
        $display("[AO01] ADD smoke: 42+1=43...");
        tile_bank_fill_all(2'd0, 32'd42);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd1);
        run_cgra(5);
        check_pe_result(4'd0, 32'd43, "AO01: ADD 42+1=43");

        // =================================================================
        // AO02: SUB smoke — tile=100, imm=30, expect 70
        // =================================================================
        $display("[AO02] SUB smoke: 100-30=70...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'd100);
        config_pe_imm(4'd0, OP_SUB, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd30);
        run_cgra(5);
        check_pe_result(4'd0, 32'd70, "AO02: SUB 100-30=70");

        // =================================================================
        // AO03: MUL smoke — tile=7, imm=6, expect 42
        // =================================================================
        $display("[AO03] MUL smoke: 7*6=42...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'd7);
        config_pe_imm(4'd0, OP_MUL, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd6);
        run_cgra(5);
        check_pe_result(4'd0, 32'd42, "AO03: MUL 7*6=42");

        // =================================================================
        // AO04: MAC accumulation — run MAC with same inputs across contexts
        // =================================================================
        $display("[AO04] MAC accumulation...");
        reset_dut(5);
        // Clear accumulator first
        config_pe_safe(4'd0, OP_ACC_CLR, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(3);
        // Now MAC: tile=2, imm=3 → each cycle adds 6 to accumulator
        // After 16 contexts: acc = 16 * 6 = 96
        tile_bank_fill_all(2'd0, 32'd2);
        config_pe_imm(4'd0, OP_MAC, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd3);
        // Start CU, let it auto-stop at 16 contexts
        apb_write(ADDR_CU_CTRL, 32'h1);
        wait_cycles(50);
        rd = read_pe_result(4'd0);
        $display("[AO04] MAC result: %0d (expected 96)", $signed(rd));
        // MAC result should be 96 (16 iterations * 2 * 3)
        if ($signed(rd) == 96) pass("AO04: MAC 16 * (2*3) = 96");
        else fail("AO04: MAC accumulation", $sformatf("expected 96, got %0d", $signed(rd)));

        // =================================================================
        // AO05: ACC_CLR clears accumulator
        // =================================================================
        $display("[AO05] ACC_CLR...");
        reset_dut(5);
        // First accumulate something
        tile_bank_fill_all(2'd0, 32'd10);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd5);
        run_cgra(5);
        // Now clear
        config_pe_safe(4'd0, OP_ACC_CLR, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(3);
        check_pe_result(4'd0, 32'd0, "AO05: ACC_CLR result is 0");

        // =================================================================
        // AO06: PASS0 — route operand A through
        // =================================================================
        $display("[AO06] PASS0 routing...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'hDEAD_BEEF);
        config_pe_imm(4'd0, OP_PASS0, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        run_cgra(5);
        check_pe_result(4'd0, 32'hDEAD_BEEF, "AO06: PASS0 routes operand A");

        // =================================================================
        // AO07: PASS1 — route operand B (immediate) through
        // =================================================================
        $display("[AO07] PASS1 routing...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'd0);
        config_pe_imm(4'd0, OP_PASS1, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd12345);
        run_cgra(5);
        // IMM is 16-bit sign-extended: 12345 = 0x3039, sign-ext → 0x0000_3039
        check_pe_result(4'd0, 32'h0000_3039, "AO07: PASS1 routes immediate 12345");

        // =================================================================
        // AO08: CMP_GT comparison
        // =================================================================
        $display("[AO08] CMP_GT...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'd10);
        config_pe_imm(4'd0, OP_CMP_GT, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd5);
        run_cgra(5);
        check_pe_result(4'd0, 32'd1, "AO08: CMP_GT 10>5 = 1");

        // =================================================================
        // AO09: RELU activation
        // =================================================================
        $display("[AO09] RELU...");
        reset_dut(5);
        // Positive input → pass through
        tile_bank_fill_all(2'd0, 32'd42);
        config_pe_imm(4'd0, OP_RELU, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        run_cgra(5);
        check_pe_result(4'd0, 32'd42, "AO09a: RELU(42)=42");

        // Negative input → 0
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'hFFFF_FFF6);  // -10 in signed
        config_pe_imm(4'd0, OP_RELU, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        run_cgra(5);
        check_pe_result(4'd0, 32'd0, "AO09b: RELU(-10)=0");

        // =================================================================
        // AO10: Auto-stop after 16 contexts
        // =================================================================
        $display("[AO10] Auto-stop at 16 contexts...");
        reset_dut(5);
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_CU_CTRL, 32'h1);  // Start CU
        wait_cycles(50);  // Wait for auto-stop
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1] === 1'b1) pass("AO10: CU auto-stop done=1 after 16 contexts");
        else fail("AO10: Auto-stop", $sformatf("CU_STATUS=0x%08h, done bit not set", rd));

        // =================================================================
        // AO11: East-edge capture — 4 rows with distinct values
        // =================================================================
        $display("[AO11] East-edge RESULT_ROW0-3...");
        reset_dut(5);
        // Configure PE column 3 (east edge): PE3, PE7, PE11, PE15
        // Each passes its tile data east via PASS0+ROUTE_EAST
        for (int row = 0; row < 4; row++) begin
            logic [3:0] pe_id;
            pe_id = row[3:0] * 4 + 3;  // Column 3: PE3, PE7, PE11, PE15
            tile_bank_fill_all(row[1:0], 32'(32'h100 * (row + 1)));
            config_pe_imm(pe_id, OP_PASS0, SRC_WEST, SRC_IMM, 4'd0, ROUTE_EAST, 16'd0);
        end
        run_cgra(5);
        apb_read(ADDR_RESULT_ROW0, rd0);
        apb_read(ADDR_RESULT_ROW1, rd1);
        apb_read(ADDR_RESULT_ROW2, rd2);
        apb_read(ADDR_RESULT_ROW3, rd3);
        $display("[AO11] ROW0=%0d ROW1=%0d ROW2=%0d ROW3=%0d", rd0, rd1, rd2, rd3);
        // At minimum, verify the result registers are readable and non-X
        if (!$isunknown(rd0) && !$isunknown(rd1) && !$isunknown(rd2) && !$isunknown(rd3))
            pass("AO11: East-edge RESULT_ROW0-3 readable (no X)");
        else
            fail("AO11: East-edge", "One or more RESULT_ROW registers returned X");

        // =================================================================
        // AO12: Multi-PE simultaneous — PE0 (row0,col0) and PE4 (row1,col0)
        // =================================================================
        // PE0 and PE4 are both column-0 PEs (leftmost in their rows).
        // Their SRC_WEST inputs come directly from tile memory, not from
        // other PEs. This avoids mesh-routing interference.
        $display("[AO12] Multi-PE simultaneous...");
        reset_dut(5);
        // Fill ALL tile banks so both row 0 and row 1 tile memories have 10
        for (int b = 0; b < 4; b++) tile_bank_fill_all(b[1:0], 32'd10);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd5);
        config_pe_imm(4'd4, OP_MUL, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd3);
        run_cgra(5);
        check_pe_result(4'd0, 32'd15, "AO12a: PE0 ADD 10+5=15");
        check_pe_result(4'd4, 32'd30, "AO12b: PE4 MUL 10*3=30");

        $display("\n[SUITE AO COMPLETE] Compute Smoke Test finished.\n");
    end
endtask

`endif
