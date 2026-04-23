`ifndef TB_SUITE_CFG_BCAST_SVH
`define TB_SUITE_CFG_BCAST_SVH

// =============================================================================
// SUITE CBR: PE-Broadcast Config Write (R3)
// =============================================================================
// dma_cfg_addr[14] = 1 → cfg_wr_pe_bcast: all 16 PEs receive the write.
// Slot-0 write also triggers the broadcaster's 15-cycle slot replay, so a
// single slot-0 broadcast programs all 16 PEs × 16 slots in 2 DMAs (8+8 B).
//
// Tests:
//   CBR01: Broadcast PASS0(WEST→EAST) to all 16 PEs; load tile banks with 42;
//          run CU; verify RESULT_ROW0..3 all = 42 (data reaches col3 east).
//   CBR02: Unicast ADD(WEST+3) to PE0 (pe_sel=0, no bcast flag); re-run;
//          verify RESULT_ROW0 = 45 (42+3), RESULT_ROW1..3 stay 42 (unchanged).
// =============================================================================

localparam logic [31:0] BASE_CFG_BCAST_ADDR = 32'h2000_4000;  // PFX_CONFIG | bit[14]

// Write a single config slot to ALL PEs using the broadcast address flag.
// Protocol: HIGH word first (addr bit[2]=0 latches), LOW word second (bit[2]=1 commits).
task automatic bcast_write_slot(input logic [3:0] slot, input logic [63:0] cfg_word);
    logic [31:0] dst_base;
    dst_base = BASE_CFG_BCAST_ADDR | (32'({28'd0, slot}) << 3);
    // High word: bit[2]=0
    ram_write(32'h0002_0000, cfg_word[63:32]);
    dma_transfer(32'h0002_0000, dst_base, 32'd4, 200);
    // Low word: bit[2]=1 → commit
    ram_write(32'h0002_0000, cfg_word[31:0]);
    dma_transfer(32'h0002_0000, dst_base | 32'h4, 32'd4, 200);
endtask

task automatic run_suite_CBR_cfg_bcast;
    logic [31:0] r0, r1, r2, r3;
    logic [63:0] pass0_cfg, add3_cfg;
    begin
        $display("\n========================================");
        $display("   SUITE CBR: PE-BROADCAST CONFIG");
        $display("========================================\n");

        reset_dut(5);

        // =================================================================
        // CBR01: Broadcast PASS0(SRC_WEST → EAST) to all 16 PEs.
        //        Slot-0 write with bcast flag → broadcaster replicates to
        //        slots 1-15, all going to all 16 PEs.
        //        Load tile banks 0-3 with 42; run CU (16 slots).
        //        Data path: TileMem → PE(r,0).west → PASS0 → east →
        //          PE(r,1).west → PASS0 → … → PE(r,3) east = 42 → RESULT_ROW[r].
        // =================================================================
        $display("[CBR01] Broadcast PASS0 to all 16 PEs; verify RESULT_ROW0..3 = 42...");

        pass0_cfg = build_pe_config(OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST, 16'd0);

        // Broadcast slot 0 → broadcaster fills slots 1-15; bcast flag → all PEs
        bcast_write_slot(4'd0, pass0_cfg);

        // Load tile banks 0-3 with 42 (all 16 context slots)
        tile_bank_fill_all(2'd0, 32'd42);
        tile_bank_fill_all(2'd1, 32'd42);
        tile_bank_fill_all(2'd2, 32'd42);
        tile_bank_fill_all(2'd3, 32'd42);

        // Run: 16 slots, no loop. RESULT_SKIP=12 skips pipeline-fill warmup.
        // Use run_cgra_wait_done (no post-run soft_reset) so FIFO stays populated.
        apb_write(ADDR_CU_PC_END,   32'd15);
        apb_write(ADDR_RESULT_SKIP, 32'd12);
        apb_write(ADDR_LOOP_COUNT,  32'd0);
        run_cgra_wait_done(500);

        apb_read(ADDR_RESULT_ROW0, r0);
        apb_read(ADDR_RESULT_ROW1, r1);
        apb_read(ADDR_RESULT_ROW2, r2);
        apb_read(ADDR_RESULT_ROW3, r3);

        if (r0 === 32'd42)
            pass("CBR01a: RESULT_ROW0 = 42 after broadcast PASS0");
        else
            fail("CBR01a: RESULT_ROW0 wrong after broadcast", $sformatf("exp=42 got=%0d", r0));
        if (r1 === 32'd42)
            pass("CBR01b: RESULT_ROW1 = 42 after broadcast PASS0");
        else
            fail("CBR01b: RESULT_ROW1 wrong after broadcast", $sformatf("exp=42 got=%0d", r1));
        if (r2 === 32'd42)
            pass("CBR01c: RESULT_ROW2 = 42 after broadcast PASS0");
        else
            fail("CBR01c: RESULT_ROW2 wrong after broadcast", $sformatf("exp=42 got=%0d", r2));
        if (r3 === 32'd42)
            pass("CBR01d: RESULT_ROW3 = 42 after broadcast PASS0");
        else
            fail("CBR01d: RESULT_ROW3 wrong after broadcast", $sformatf("exp=42 got=%0d", r3));

        // =================================================================
        // CBR02: Unicast ADD(WEST+3) to PE0 only (pe_sel=0, no bcast flag).
        //        PE(0,0) computes 42+3=45; PE(0,1..3) still PASS0 → east.
        //        RESULT_ROW0 = 45.  RESULT_ROW1..3 unchanged = 42.
        // =================================================================
        $display("[CBR02] Unicast ADD(WEST+3) to PE0 only; verify row0=45, rows1-3=42...");

        add3_cfg = build_pe_config(OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_EAST, 16'd3);
        // Unicast: pe_id=0, no broadcast flag
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_EAST, 16'd3);

        run_cgra_wait_done(500);

        apb_read(ADDR_RESULT_ROW0, r0);
        apb_read(ADDR_RESULT_ROW1, r1);

        if (r0 === 32'd45)
            pass("CBR02a: RESULT_ROW0 = 45 (42+3) after unicast ADD override");
        else
            fail("CBR02a: RESULT_ROW0 wrong after unicast", $sformatf("exp=45 got=%0d", r0));
        if (r1 === 32'd42)
            pass("CBR02b: RESULT_ROW1 = 42 (unchanged, unicast did not touch row1)");
        else
            fail("CBR02b: RESULT_ROW1 changed by unicast write", $sformatf("exp=42 got=%0d", r1));

        // Restore defaults
        apb_write(ADDR_CU_PC_END,   32'd15);
        apb_write(ADDR_RESULT_SKIP, 32'd12);

        $display("\n[SUITE CBR COMPLETE] PE-broadcast config write verified.\n");
    end
endtask

`endif
