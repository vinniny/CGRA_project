// =============================================================================
// SUITE TAI: TILE AUTO-INCREMENT VERIFICATION
// =============================================================================
// Tests the TILE_AUTO_INC feature (CSR 0x78) that auto-advances tile
// memory read addresses by 16 words on each hardware loop iteration.
//
// When enabled, tile_addr = {offset[7:0], context_pc[3:0]}.
// Offset increments by 1 each time the CU's inner loop wraps.
// This allows pre-loading 4096 words and processing them in one CU run.
// =============================================================================

task automatic run_suite_TAI_tile_autoinc;
    logic [31:0] rd, res;
    begin
        $display("\n--- SUITE TAI: TILE AUTO-INCREMENT ---");

        // ─────────────────────────────────────────────────────────────
        // TAI01: CSR read/write + write-protection while CU busy
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[TAI01] CSR read/write...");

        // Write 1, read back
        apb_write(ADDR_TILE_AUTO_INC, 32'd1);
        apb_read(ADDR_TILE_AUTO_INC, rd);
        if (rd == 32'd1) pass("TAI01a: TILE_AUTO_INC write 1 readback");
        else fail("TAI01a: TILE_AUTO_INC readback", $sformatf("got %0h, expected 1", rd));

        // Write 0, read back
        apb_write(ADDR_TILE_AUTO_INC, 32'd0);
        apb_read(ADDR_TILE_AUTO_INC, rd);
        if (rd == 32'd0) pass("TAI01b: TILE_AUTO_INC write 0 readback");
        else fail("TAI01b: TILE_AUTO_INC readback", $sformatf("got %0h, expected 0", rd));

        // Write-protection: set to 1, start CU, try to write 0
        apb_write(ADDR_TILE_AUTO_INC, 32'd1);
        // Configure a minimal PE and start CU
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT, 32'd100);  // Long loop so CU stays busy
        apb_write(ADDR_CU_CTRL, 32'd1);       // Start
        wait_cycles(5);
        // Try write while busy — should be rejected
        apb_write(ADDR_TILE_AUTO_INC, 32'd0);
        apb_read(ADDR_TILE_AUTO_INC, rd);
        if (rd == 32'd1) pass("TAI01c: Write-protected while CU busy");
        else fail("TAI01c: Write protection", $sformatf("got %0h, expected 1 (rejected)", rd));
        // Stop CU
        apb_write(ADDR_CU_CTRL, 32'd2);
        wait_cycles(3);
        apb_write(ADDR_CU_CTRL, 32'd0);
        // Now write should succeed
        apb_write(ADDR_TILE_AUTO_INC, 32'd0);
        apb_read(ADDR_TILE_AUTO_INC, rd);
        if (rd == 32'd0) pass("TAI01d: Write succeeds after CU stop");
        else fail("TAI01d: Write after stop", $sformatf("got %0h, expected 0", rd));

        // ─────────────────────────────────────────────────────────────
        // TAI02: Legacy mode (auto_inc=0) — same 16 addrs every pass
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[TAI02] Legacy mode (auto_inc=0)...");

        // Load tile bank 0: addr 0-15 = {100..115}, addr 16-31 = {200..215}
        begin
            int i;
            for (i = 0; i < 16; i++)
                dma_load_tile_bank(2'd0, i[11:0] * 4, 32'(100 + i));
            for (i = 0; i < 16; i++)
                dma_load_tile_bank(2'd0, (16 + i[11:0]) * 4, 32'(200 + i));
        end

        // PE[0,0]: PASS0 SRC_W (reads tile), route east
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        config_pe_safe(4'd1, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        config_pe_safe(4'd2, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        config_pe_safe(4'd3, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);

        // Disable auto-increment
        apb_write(ADDR_TILE_AUTO_INC, 32'd0);

        // Loop: 2 passes (LOOP_COUNT=1 = 1 extra + 1 base = 2)
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd15);
        apb_write(ADDR_LOOP_COUNT, 32'd1);

        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(200);

        apb_read(ADDR_RESULT_ROW0, rd);
        $display("[TAI02] Legacy: RESULT_ROW0 = %0d (expect 104)", rd);
        // Without auto-inc, both passes read addr 0-15. RESULT_ROW0
        // captures the east-edge value with an 11-slot pipeline delay
        // (tile prefetch + 3-stage PE + 3-hop east forwarding).
        // Captured value = tile[15 - 11] = tile[4] = 100 + 4 = 104.
        if (rd == 32'd104)
            pass("TAI02: Legacy mode — correct pipeline-delayed value");
        else
            fail("TAI02: Legacy mode", $sformatf("got %0d, expected 104", rd));

        // ─────────────────────────────────────────────────────────────
        // TAI03: Auto-increment basic — second pass reads addr 16-31
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[TAI03] Auto-increment basic...");

        // Same tile data as TAI02
        begin
            int i;
            for (i = 0; i < 16; i++)
                dma_load_tile_bank(2'd0, i[11:0] * 4, 32'(100 + i));
            for (i = 0; i < 16; i++)
                dma_load_tile_bank(2'd0, (16 + i[11:0]) * 4, 32'(200 + i));
        end

        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        config_pe_safe(4'd1, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        config_pe_safe(4'd2, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        config_pe_safe(4'd3, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);

        // Enable auto-increment
        apb_write(ADDR_TILE_AUTO_INC, 32'd1);

        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd15);
        apb_write(ADDR_LOOP_COUNT, 32'd1);   // 2 passes

        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(200);

        apb_read(ADDR_RESULT_ROW0, rd);
        $display("[TAI03] Auto-inc: RESULT_ROW0 = %0d (expect 204)", rd);
        // With auto-inc: pass 0 reads addr 0-15, pass 1 reads addr 16-31.
        // Pipeline delay: captured = tile[16 + (15-11)] = tile[20] = 200+4 = 204.
        // The key: value is from addr 16-31 range (NOT 0-15), proving auto-inc works.
        if (rd == 32'd204)
            pass("TAI03: Auto-inc reads from addr 16-31 range (204)");
        else
            fail("TAI03: Auto-inc basic", $sformatf("got %0d, expected 204", rd));

        // Disable auto-inc for subsequent tests
        apb_write(ADDR_TILE_AUTO_INC, 32'd0);

        // ─────────────────────────────────────────────────────────────
        // TAI04: 4-pass auto-increment — verify sequential addressing
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[TAI04] 4-pass auto-increment...");

        // Load tile bank 0: addr 0-63 = {0, 1, 2, ..., 63}
        begin
            int i;
            for (i = 0; i < 64; i++)
                dma_load_tile_bank(2'd0, i[11:0] * 4, 32'(i));
        end

        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        config_pe_safe(4'd1, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        config_pe_safe(4'd2, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        config_pe_safe(4'd3, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);

        apb_write(ADDR_TILE_AUTO_INC, 32'd1);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd15);
        apb_write(ADDR_LOOP_COUNT, 32'd3);   // 4 passes total

        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(400);

        apb_read(ADDR_RESULT_ROW0, rd);
        $display("[TAI04] 4-pass: RESULT_ROW0 = %0d (expect 52)", rd);
        // Pass 3 (last) reads addr 48-63. Pipeline delay: tile[48+4] = 52.
        if (rd == 32'd52)
            pass("TAI04: 4-pass auto-inc reads addr 48-63 range (52)");
        else
            fail("TAI04: 4-pass auto-inc", $sformatf("got %0d, expected 52", rd));

        apb_write(ADDR_TILE_AUTO_INC, 32'd0);

        // ─────────────────────────────────────────────────────────────
        // TAI05: All 4 banks auto-increment independently
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[TAI05] All 4 banks auto-increment...");

        // Bank 0: addr 0-31 = {1000+i}; Bank 1: {2000+i}; etc.
        begin
            int i;
            for (i = 0; i < 32; i++) begin
                dma_load_tile_bank(2'd0, i[11:0] * 4, 32'(1000 + i));
                dma_load_tile_bank(2'd1, i[11:0] * 4, 32'(2000 + i));
                dma_load_tile_bank(2'd2, i[11:0] * 4, 32'(3000 + i));
                dma_load_tile_bank(2'd3, i[11:0] * 4, 32'(4000 + i));
            end
        end

        // All 4 rows: PASS0 SRC_W, route east chain
        begin
            int row;
            for (row = 0; row < 4; row++) begin
                config_pe_safe(row[3:0] * 4,     OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
                config_pe_safe(row[3:0] * 4 + 1, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
                config_pe_safe(row[3:0] * 4 + 2, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
                config_pe_safe(row[3:0] * 4 + 3, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
            end
        end

        apb_write(ADDR_TILE_AUTO_INC, 32'd1);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd15);
        apb_write(ADDR_LOOP_COUNT, 32'd1);   // 2 passes

        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(200);

        // Each row should capture last slot of pass 1 = bank[row][31]
        begin
            logic [31:0] r0, r1, r2, r3;
            apb_read(ADDR_RESULT_ROW0, r0);
            apb_read(ADDR_RESULT_ROW1, r1);
            apb_read(ADDR_RESULT_ROW2, r2);
            apb_read(ADDR_RESULT_ROW3, r3);
            $display("[TAI05] ROW0=%0d ROW1=%0d ROW2=%0d ROW3=%0d", r0, r1, r2, r3);
            // Pipeline delay: each bank captures tile[16+4] = base + 20
            $display("[TAI05] Expected: 1020 2020 3020 4020");
            if (r0 == 32'd1020) pass("TAI05a: Bank0 auto-inc (1020)");
            else fail("TAI05a: Bank0", $sformatf("got %0d, expected 1020", r0));
            if (r1 == 32'd2020) pass("TAI05b: Bank1 auto-inc (2020)");
            else fail("TAI05b: Bank1", $sformatf("got %0d, expected 2020", r1));
            if (r2 == 32'd3020) pass("TAI05c: Bank2 auto-inc (3020)");
            else fail("TAI05c: Bank2", $sformatf("got %0d, expected 3020", r2));
            if (r3 == 32'd4020) pass("TAI05d: Bank3 auto-inc (4020)");
            else fail("TAI05d: Bank3", $sformatf("got %0d, expected 4020", r3));
        end

        apb_write(ADDR_TILE_AUTO_INC, 32'd0);

        $display("\n[SUITE TAI COMPLETE] Tile auto-increment verified.\n");
    end
endtask
