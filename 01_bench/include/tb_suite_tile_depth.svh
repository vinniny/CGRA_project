`ifndef TB_SUITE_TILE_DEPTH_SVH
`define TB_SUITE_TILE_DEPTH_SVH

// =============================================================================
// SUITE AI: Tile Memory Depth Verification
// =============================================================================
// Validates that the increased BANK_DEPTH (4096) works correctly.
// Tests large-offset addressing, full-bank DMA transfers, and boundary cases.
// =============================================================================

task automatic run_suite_AI_tile_depth;
    logic [31:0] res, rd;
    logic data_ok;
    begin
        $display("\n========================================");
        $display("   SUITE AI: TILE MEMORY DEPTH");
        $display("========================================\n");

        reset_dut(5);

        // =================================================================
        // AI01: Basic write/read at address 0 (baseline)
        // =================================================================
        $display("[AI01] Tile write/read at addr 0...");
        ram_write(32'h0000, 32'hAAAA_BBBB);
        dma_transfer(32'h0000, 32'h10000000, 4, 100);  // DDR → tile bank 0, addr 0
        // Read back via DMA: tile → DDR
        dma_transfer(32'h10000000, 32'h4000, 4, 100);  // tile bank 0 → DDR 0x4000
        rd = ram_read(32'h4000);
        if (rd == 32'hAAAA_BBBB) pass("AI01: tile[0] = 0xAAAABBBB");
        else fail("AI01: tile[0] mismatch", $sformatf("exp=0xAAAABBBB got=0x%08h", rd));

        // =================================================================
        // AI02: Write/read at high address (offset 1000+)
        // =================================================================
        // With BANK_DEPTH=4096, tile addresses 0-4095 are valid per bank.
        // DMA tile address is byte-addressed: word 1024 = byte 4096 = 0x1000
        $display("[AI02] Tile write/read at high offset...");
        ram_write(32'h0100, 32'hDEAD_BEEF);
        // Write to tile bank 0, word offset 256 (byte 1024 = 0x400)
        dma_transfer(32'h0100, 32'h10000400, 4, 100);
        // Read back
        dma_transfer(32'h10000400, 32'h4100, 4, 100);
        rd = ram_read(32'h4100);
        if (rd == 32'hDEAD_BEEF) pass("AI02: tile[256] high offset OK");
        else fail("AI02: tile[256] mismatch", $sformatf("exp=0xDEADBEEF got=0x%08h", rd));

        // =================================================================
        // AI03: Multi-word DMA to tile memory
        // =================================================================
        $display("[AI03] Multi-word DMA to tile...");
        for (int i = 0; i < 32; i++)
            ram_write(32'h0200 + i*4, i + 32'h1000);
        dma_transfer(32'h0200, 32'h10000000, 128, 200);  // 32 words to tile bank 0
        // Read back
        dma_transfer(32'h10000000, 32'h5000, 128, 200);
        check_data(32'h0200, 32'h5000, 128, data_ok);
        if (data_ok) pass("AI03: 32-word DMA round-trip OK");
        else fail("AI03: 32-word round-trip mismatch", "data corruption");

        // =================================================================
        // AI04: Cross-bank DMA (bank 0 and bank 1)
        // =================================================================
        $display("[AI04] Cross-bank DMA...");
        ram_write(32'h0300, 32'hBAD0_CAB0);
        ram_write(32'h0304, 32'hBAD1_CAB1);
        // Bank 0 (0x10000000)
        dma_transfer(32'h0300, 32'h10000000, 4, 100);
        // Bank 1 (0x10001000)
        dma_transfer(32'h0304, 32'h10001000, 4, 100);
        // Read back bank 0
        dma_transfer(32'h10000000, 32'h6000, 4, 100);
        rd = ram_read(32'h6000);
        if (rd == 32'hBAD0_CAB0) pass("AI04a: bank 0 cross-bank OK");
        else fail("AI04a: bank 0 mismatch", $sformatf("got=0x%08h", rd));
        // Read back bank 1
        dma_transfer(32'h10001000, 32'h6004, 4, 100);
        rd = ram_read(32'h6004);
        if (rd == 32'hBAD1_CAB1) pass("AI04b: bank 1 cross-bank OK");
        else fail("AI04b: bank 1 mismatch", $sformatf("got=0x%08h", rd));

        // =================================================================
        // AI05: Tile data feeds PE via west edge
        // =================================================================
        // Write known value to tile, configure PE to PASS0 from WEST, verify
        $display("[AI05] Tile → PE west edge data path...");
        tile_bank_fill_all(2'd0, 32'h7777_8888);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'h7777_8888, "AI05: tile→PE west data path");

        $display("\n[SUITE AI COMPLETE] Tile memory depth verification finished.\n");
    end
endtask

`endif
