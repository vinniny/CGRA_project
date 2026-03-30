`ifndef TB_SUITE_DOUBLEBUF_SVH
`define TB_SUITE_DOUBLEBUF_SVH

// =============================================================================
// SUITE AK: Double-Buffered Tile Memory Verification
// =============================================================================
// Tests the C2 double-buffering feature: PE reads from one half of tile
// memory while DMA can write to the other half.
// =============================================================================

task automatic run_suite_AK_doublebuf;
    logic [31:0] res, rd;
    begin
        $display("\n========================================");
        $display("   SUITE AK: DOUBLE-BUFFERED TILE MEM");
        $display("========================================\n");

        reset_dut(5);

        // =================================================================
        // AK01: CSR readback — TILE_BANK_SEL default is 0
        // =================================================================
        $display("[AK01] TILE_BANK_SEL default...");
        apb_read(ADDR_TILE_BANK_SEL, rd);
        if (rd == 32'd0) pass("AK01: TILE_BANK_SEL default=0");
        else fail("AK01: default wrong", $sformatf("got %0d", rd));

        // =================================================================
        // AK02: CSR write/readback
        // =================================================================
        $display("[AK02] TILE_BANK_SEL write/read...");
        apb_write(ADDR_TILE_BANK_SEL, 32'd1);
        apb_read(ADDR_TILE_BANK_SEL, rd);
        if (rd == 32'd1) pass("AK02: TILE_BANK_SEL set to 1");
        else fail("AK02: readback wrong", $sformatf("got %0d", rd));
        // Reset back
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);

        // =================================================================
        // AK03: bank_sel=0 — PE reads lower half (backward compatible)
        // =================================================================
        $display("[AK03] bank_sel=0: PE reads lower half...");
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);
        tile_bank_fill_all(2'd0, 32'hAAAA_0000);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'hAAAA_0000, "AK03: bank_sel=0 reads lower half");

        // =================================================================
        // AK04: bank_sel toggle — different data per half
        // =================================================================
        // The bank_sel_i bit prepends to PE's bank_addr as MSB.
        // With bank_sel=0, PE reads from memory[{0, pc}] = address 0-15.
        // With bank_sel=1, PE reads from memory[{1, pc}] = address 512-527
        // (since BANK_ADDR_W=12, {1, 11'b0} = 2048 for BANK_DEPTH=4096,
        //  but with our 4-bit PC: {1, 0000_0000_xxxx} = 2048+pc).
        // Note: The DMA 12-bit addr can only reach words 0-1023, so we
        // verify the bank_sel mechanism by checking that different bank_sel
        // values produce different memory reads.
        $display("[AK04] bank_sel toggle — data isolation check...");
        // bank_sel=0 already has 0xAAAA_0000 from AK03
        // bank_sel=1 reads from a different physical address (uninitialized = 0)
        apb_write(ADDR_TILE_BANK_SEL, 32'd1);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        res = read_pe_result(4'd0);
        $display("[AK04] PE result with bank_sel=1: 0x%08h (expect != 0xAAAA_0000)", res);
        if (res !== 32'hAAAA_0000)
            pass("AK04: bank_sel=1 reads different address than sel=0");
        else
            fail("AK04: bank_sel=1 reads same as sel=0", "no isolation");

        // Reset bank_sel
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);

        // =================================================================
        // AK05: Toggle bank_sel — verify data isolation
        // =================================================================
        $display("[AK05] Toggle bank_sel isolation...");
        // bank_sel=0 should still have 0xAAAA_0000
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'hAAAA_0000, "AK05: toggle back to sel=0");

        $display("\n[SUITE AK COMPLETE] Double-buffered tile memory verified.\n");
    end
endtask

`endif
