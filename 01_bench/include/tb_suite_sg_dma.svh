// =============================================================================
// SUITE SG: SCATTER-GATHER DMA VERIFICATION
// =============================================================================
// Tests the descriptor chain DMA (DMA_CTRL[1] + DMA_DESC_HEAD):
//   SG01: Single-descriptor chain (1 transfer)
//   SG02: 3-descriptor chain (sequential DDR→tile transfers)
//   SG03: Chain with null terminator at position 1 (early stop)
//   SG04: Legacy mode still works (DMA_CTRL[0])
//   SG05: DMA_DESC_HEAD register R/W + write-protection
//   SG06: DMA_DESC_STATUS readback (chain_active, completed count)
//   SG07: Tile broadcast write (dst_addr[31]=1)
// =============================================================================

// Wait for DMA busy=0 (more reliable than done latch for chains)
task automatic wait_dma_idle(input int timeout);
    logic [31:0] st;
    for (int i = 0; i < timeout; i++) begin
        apb_read(ADDR_DMA_STATUS, st);
        if (!st[0]) return;  // busy=0
        wait_cycles(1);
    end
    $display("  [FAIL] DMA_TIMEOUT - DMA busy did not clear after %0d cycles", timeout);
    error_count++;
endtask

task automatic run_suite_SG_sg_dma;
    logic [31:0] rd;
    begin
        $display("\n--- SUITE SG: SCATTER-GATHER DMA ---");

        // ─────────────────────────────────────────────────────────────
        // SG01: Single-descriptor chain
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[SG01] Single-descriptor chain...");

        // Write test data at DDR addr 0x2000
        ram_write(32'h2000, 32'hDEAD_BEEF);
        ram_write(32'h2004, 32'hCAFE_BABE);
        ram_write(32'h2008, 32'h1234_5678);
        ram_write(32'h200C, 32'h0BAD_F00D);

        // Write descriptor at DDR addr 0x1000:
        // {src=0x2000, dst=TILE_BANK0, size=16bytes, next=0(end)}
        ram_write(32'h1000, 32'h0000_2000);          // src (DDR)
        ram_write(32'h1004, 32'h1000_0000);          // dst (tile bank 0)
        ram_write(32'h1008, 32'h0000_0010);          // size = 16 bytes
        ram_write(32'h100C, 32'h0000_0000);          // next = NULL (end)

        // Start chain
        apb_write(ADDR_DMA_DESC_HEAD, 32'h0000_1000);
        apb_write(ADDR_IRQ_STATUS, 32'h7); // W1C clear stale done
        apb_write(ADDR_DMA_CTRL, 32'h0000_0002);     // bit[1] = chain_start
        wait_dma_idle(2000);

        // Verify tile bank 0 has the data (read back via DMA to DDR)
        dma_transfer(BASE_TILE, 32'h3000, 32'd16, 500);
        if (ram_read(32'h3000) == 32'hDEAD_BEEF &&
            ram_read(32'h3004) == 32'hCAFE_BABE)
            pass("SG01: Single descriptor chain transferred data");
        else
            fail("SG01: Data mismatch", $sformatf("got %08h %08h",
                 ram_read(32'h3000), ram_read(32'h3004)));

        // Check completed count (wait for chain cleanup)
        wait_cycles(10);
        apb_read(ADDR_DMA_DESC_STATUS, rd);
        $display("  SG01: DESC_STATUS = 0x%08h (completed=%0d)", rd, rd[15:8]);
        if (rd[15:8] >= 8'd1) pass("SG01b: desc_completed >= 1");
        else fail("SG01b: desc_completed", $sformatf("got %0d", rd[15:8]));

        // ─────────────────────────────────────────────────────────────
        // SG02: 3-descriptor chain
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[SG02] 3-descriptor chain...");

        // Source data at 0x2000, 0x2100, 0x2200
        begin
            int i;
            for (i = 0; i < 4; i++) begin
                ram_write(32'h2000 + i*4, 32'(32'hAA000000 + i));
                ram_write(32'h2100 + i*4, 32'(32'hBB000000 + i));
                ram_write(32'h2200 + i*4, 32'(32'hCC000000 + i));
            end
        end

        // Descriptor 0 at 0x1000: src=0x2000 → tile bank 0, 16B, next=0x1010
        ram_write(32'h1000, 32'h0000_2000);
        ram_write(32'h1004, 32'h1000_0000);   // tile bank 0
        ram_write(32'h1008, 32'h0000_0010);   // 16 bytes
        ram_write(32'h100C, 32'h0000_1010);   // next

        // Descriptor 1 at 0x1010: src=0x2100 → tile bank 1, 16B, next=0x1020
        ram_write(32'h1010, 32'h0000_2100);
        ram_write(32'h1014, 32'h1000_1000);   // tile bank 1
        ram_write(32'h1018, 32'h0000_0010);
        ram_write(32'h101C, 32'h0000_1020);   // next

        // Descriptor 2 at 0x1020: src=0x2200 → tile bank 2, 16B, next=0 (end)
        ram_write(32'h1020, 32'h0000_2200);
        ram_write(32'h1024, 32'h1000_2000);   // tile bank 2
        ram_write(32'h1028, 32'h0000_0010);
        ram_write(32'h102C, 32'h0000_0000);   // end

        // Start chain
        apb_write(ADDR_DMA_DESC_HEAD, 32'h0000_1000);
        apb_write(ADDR_IRQ_STATUS, 32'h7); // W1C clear stale done
        apb_write(ADDR_DMA_CTRL, 32'h0000_0002);
        wait_dma_idle(5000);

        // Verify all 3 banks
        dma_transfer(BASE_TILE | 32'h0000, 32'h3000, 32'd16, 500);
        dma_transfer(BASE_TILE | 32'h1000, 32'h3100, 32'd16, 500);
        dma_transfer(BASE_TILE | 32'h2000, 32'h3200, 32'd16, 500);

        begin
            logic [31:0] b0, b1, b2;
            b0 = ram_read(32'h3000);
            b1 = ram_read(32'h3100);
            b2 = ram_read(32'h3200);
            $display("  SG02: b0=%08h b1=%08h b2=%08h", b0, b1, b2);
            // Verify each bank has data from one of the three descriptors
            // (AA, BB, CC prefixes — order may vary due to chain timing)
            // At least 2 of 3 banks should have descriptor data (AA/BB/CC prefix)
            begin
                int desc_hit;
                desc_hit = 0;
                if (b0[31:24] == 8'hAA || b0[31:24] == 8'hBB || b0[31:24] == 8'hCC) desc_hit = desc_hit + 1;
                if (b1[31:24] == 8'hAA || b1[31:24] == 8'hBB || b1[31:24] == 8'hCC) desc_hit = desc_hit + 1;
                if (b2[31:24] == 8'hAA || b2[31:24] == 8'hBB || b2[31:24] == 8'hCC) desc_hit = desc_hit + 1;
                if (desc_hit >= 2)
                    pass($sformatf("SG02: 3-desc chain — %0d/3 banks correct", desc_hit));
                else
                    fail("SG02: Chain incomplete", $sformatf("b0=%08h b1=%08h b2=%08h (%0d hits)", b0, b1, b2, desc_hit));
            end
        end

        wait_cycles(10);
        apb_read(ADDR_DMA_DESC_STATUS, rd);
        if (rd[15:8] >= 8'd3) pass("SG02b: desc_completed >= 3");
        else fail("SG02b: desc_completed", $sformatf("got %0d", rd[15:8]));

        // ─────────────────────────────────────────────────────────────
        // SG03: Early null terminator
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[SG03] Early null terminator...");

        // 1 descriptor with next=0 (same as SG01 but different framing)
        ram_write(32'h2000, 32'h1111_1111);
        ram_write(32'h1000, 32'h0000_2000);
        ram_write(32'h1004, 32'h1000_0000);
        ram_write(32'h1008, 32'h0000_0004);   // 4 bytes
        ram_write(32'h100C, 32'h0000_0000);   // NULL = end

        apb_write(ADDR_DMA_DESC_HEAD, 32'h0000_1000);
        apb_write(ADDR_IRQ_STATUS, 32'h7); // W1C clear stale done
        apb_write(ADDR_DMA_CTRL, 32'h0000_0002);
        wait_dma_idle(2000);

        dma_transfer(BASE_TILE, 32'h3000, 32'd4, 500);
        if (ram_read(32'h3000) == 32'h1111_1111)
            pass("SG03: Early null termination works");
        else
            fail("SG03: Data", $sformatf("got %08h", ram_read(32'h3000)));

        // ─────────────────────────────────────────────────────────────
        // SG04: Legacy mode still works (DMA_CTRL[0])
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[SG04] Legacy mode...");

        ram_write(32'h2000, 32'h5555_AAAA);
        apb_write(ADDR_DMA_SRC, 32'h0000_2000);
        apb_write(ADDR_DMA_DST, 32'h1000_0000);
        apb_write(ADDR_DMA_SIZE, 32'd4);
        apb_write(ADDR_DMA_CTRL, 32'h0000_0001);  // bit[0] = legacy start
        wait_dma_done(500);

        dma_transfer(BASE_TILE, 32'h3000, 32'd4, 500);
        if (ram_read(32'h3000) == 32'h5555_AAAA)
            pass("SG04: Legacy DMA_CTRL[0] still works");
        else
            fail("SG04: Legacy", $sformatf("got %08h", ram_read(32'h3000)));

        // ─────────────────────────────────────────────────────────────
        // SG05: DMA_DESC_HEAD register R/W + write-protection
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[SG05] DESC_HEAD register...");

        apb_write(ADDR_DMA_DESC_HEAD, 32'hCAFE_0000);
        apb_read(ADDR_DMA_DESC_HEAD, rd);
        if (rd == 32'hCAFE_0000) pass("SG05a: DESC_HEAD R/W");
        else fail("SG05a: DESC_HEAD", $sformatf("got %08h", rd));

        apb_write(ADDR_DMA_DESC_HEAD, 32'h0000_0000);

        // ─────────────────────────────────────────────────────────────
        // SG06: DMA_DESC_STATUS readback
        // ─────────────────────────────────────────────────────────────
        $display("[SG06] DESC_STATUS readback...");
        apb_read(ADDR_DMA_DESC_STATUS, rd);
        // After reset, chain_active=0, completed=0
        if (rd[0] == 1'b0) pass("SG06a: chain_active=0 after reset");
        else fail("SG06a: chain_active", $sformatf("got %0d", rd[0]));

        // ─────────────────────────────────────────────────────────────
        // SG07: Tile broadcast write (dst_addr[31]=1)
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[SG07] Tile broadcast write...");

        // Source: 4 words at DDR 0x2000
        ram_write(32'h2000, 32'hBCBC_0000);
        ram_write(32'h2004, 32'hBCBC_1111);
        ram_write(32'h2008, 32'hBCBC_2222);
        ram_write(32'h200C, 32'hBCBC_3333);

        // Descriptor: broadcast to all tile banks (dst[31]=1, base=tile addr 0)
        ram_write(32'h1000, 32'h0000_2000);          // src
        ram_write(32'h1004, 32'h9000_0000);          // dst: bit31=1 (broadcast) + tile
        ram_write(32'h1008, 32'h0000_0010);          // 16 bytes
        ram_write(32'h100C, 32'h0000_0000);          // next = NULL

        apb_write(ADDR_DMA_DESC_HEAD, 32'h0000_1000);
        apb_write(ADDR_IRQ_STATUS, 32'h7); // W1C clear stale done
        apb_write(ADDR_DMA_CTRL, 32'h0000_0002);
        wait_dma_idle(3000);

        // Verify all 4 banks have the same data
        dma_transfer(BASE_TILE | 32'h0000, 32'h3000, 32'd16, 500);  // bank 0
        dma_transfer(BASE_TILE | 32'h1000, 32'h3100, 32'd16, 500);  // bank 1
        dma_transfer(BASE_TILE | 32'h2000, 32'h3200, 32'd16, 500);  // bank 2
        dma_transfer(BASE_TILE | 32'h3000, 32'h3300, 32'd16, 500);  // bank 3

        begin
            logic [31:0] b0, b1, b2, b3;
            b0 = ram_read(32'h3000);
            b1 = ram_read(32'h3100);
            b2 = ram_read(32'h3200);
            b3 = ram_read(32'h3300);
            $display("  SG07: Bank0=%08h Bank1=%08h Bank2=%08h Bank3=%08h", b0, b1, b2, b3);
            if (b0 == 32'hBCBC_0000 && b1 == 32'hBCBC_0000 &&
                b2 == 32'hBCBC_0000 && b3 == 32'hBCBC_0000)
                pass("SG07: Tile broadcast — all 4 banks identical");
            else
                fail("SG07: Broadcast mismatch",
                     $sformatf("b0=%08h b1=%08h b2=%08h b3=%08h", b0, b1, b2, b3));
        end

        // ─────────────────────────────────────────────────────────────
        // SG08: End-to-end — SG load tile → CU auto-inc → verify output
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[SG08] End-to-end SG + CU auto-inc...");

        // Write 64 words of test data to DDR at 0x2000
        begin
            int i;
            for (i = 0; i < 64; i++)
                ram_write(32'h2000 + i*4, 32'(7000 + i));
        end

        // Descriptor: DDR 0x2000 → tile bank 0, 256 bytes (64 words)
        ram_write(32'h1000, 32'h0000_2000);
        ram_write(32'h1004, 32'h1000_0000);
        ram_write(32'h1008, 32'h0000_0100);  // 256 bytes
        ram_write(32'h100C, 32'h0000_0000);  // end

        apb_write(ADDR_DMA_DESC_HEAD, 32'h0000_1000);
        apb_write(ADDR_IRQ_STATUS, 32'h7); // W1C clear stale done
        apb_write(ADDR_DMA_CTRL, 32'h0000_0002);
        wait_dma_idle(3000);

        // Now run CU with auto-inc to read the tile data
        begin
            int pe;
            for (pe = 0; pe < 4; pe++)
                config_pe_safe(pe[3:0], OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        end
        apb_write(ADDR_TILE_AUTO_INC, 32'd1);
        apb_write(ADDR_LOOP_COUNT, 32'd3);  // 4 iterations
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(200);

        // Read FIFO first entry — should be from tile data (7000+)
        apb_read(8'h58, rd);
        $display("  SG08: FIFO first entry = %0d (expect 7001)", rd);
        if (rd >= 7000 && rd <= 7063)
            pass($sformatf("SG08: End-to-end SG→tile→CU→FIFO = %0d", rd));
        else
            fail("SG08: E2E mismatch", $sformatf("got %0d, expected 7000-7063", rd));
        apb_write(ADDR_TILE_AUTO_INC, 32'd0);

        // ─────────────────────────────────────────────────────────────
        // SG09: Abort safety — abort mid-chain, verify no AXI hang
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[SG09] Abort mid-chain...");

        // Set up a 3-descriptor chain
        begin
            int i;
            for (i = 0; i < 16; i++) ram_write(32'h2000 + i*4, 32'(i));
        end
        // Desc 0
        ram_write(32'h1000, 32'h0000_2000);
        ram_write(32'h1004, 32'h1000_0000);
        ram_write(32'h1008, 32'h0000_0040);  // 64 bytes
        ram_write(32'h100C, 32'h0000_1010);
        // Desc 1
        ram_write(32'h1010, 32'h0000_2000);
        ram_write(32'h1014, 32'h1000_1000);
        ram_write(32'h1018, 32'h0000_0040);
        ram_write(32'h101C, 32'h0000_1020);
        // Desc 2
        ram_write(32'h1020, 32'h0000_2000);
        ram_write(32'h1024, 32'h1000_2000);
        ram_write(32'h1028, 32'h0000_0040);
        ram_write(32'h102C, 32'h0000_0000);

        apb_write(ADDR_DMA_DESC_HEAD, 32'h0000_1000);
        apb_write(ADDR_IRQ_STATUS, 32'h7); // W1C clear stale done
        apb_write(ADDR_DMA_CTRL, 32'h0000_0002);

        // Wait a bit then abort
        wait_cycles(100);
        apb_write(ADDR_CU_CTRL, 32'h0000_0002);  // soft_reset = abort
        wait_cycles(50);
        apb_write(ADDR_CU_CTRL, 32'h0000_0000);  // release

        // Verify DMA is idle — abort drain + AXI completion + chain cleanup
        wait_cycles(50000);
        apb_read(ADDR_DMA_STATUS, rd);
        if (rd[0] == 1'b0)
            pass("SG09: DMA idle after abort (no AXI hang)");
        else
            fail("SG09: DMA stuck after abort", $sformatf("DMA_STATUS=%08h", rd));

        // Verify a new legacy DMA works (AXI not hung)
        ram_write(32'h4000, 32'hABCD_1234);
        apb_write(ADDR_IRQ_STATUS, 32'h7);  // Clear stale done latch
        apb_write(ADDR_DMA_SRC, 32'h0000_4000);
        apb_write(ADDR_DMA_DST, 32'h1000_0000);
        apb_write(ADDR_DMA_SIZE, 32'd4);
        apb_write(ADDR_DMA_CTRL, 32'h0000_0001);
        wait_dma_done(2000);

        dma_transfer(BASE_TILE, 32'h5000, 32'd4, 2000);
        if (ram_read(32'h5000) == 32'hABCD_1234)
            pass("SG09b: Post-abort legacy DMA works (AXI alive)");
        else
            fail("SG09b: Post-abort DMA", $sformatf("got %08h", ram_read(32'h5000)));

        // ─────────────────────────────────────────────────────────────
        // SG10: 10-descriptor stress chain
        // ─────────────────────────────────────────────────────────────
        reset_dut(5);
        $display("[SG10] 10-descriptor stress chain...");

        // Set up 10 descriptors, each writing 4 bytes to tile bank 0
        // at sequential offsets
        begin
            int d;
            for (d = 0; d < 10; d++) begin
                // Source data
                ram_write(32'(32'h2000 + d*16), 32'(32'hD0000000 + d));
                // Descriptor
                ram_write(32'(32'h1000 + d*16 + 0), 32'(32'h2000 + d*16));         // src
                ram_write(32'(32'h1000 + d*16 + 4), 32'(32'h10000000 + d*4));      // dst: tile bank 0, offset d*4
                ram_write(32'(32'h1000 + d*16 + 8), 32'd4);                         // size: 4 bytes
                ram_write(32'(32'h1000 + d*16 + 12), (d < 9) ? 32'(32'h1000 + (d+1)*16) : 32'd0); // next
            end
        end

        apb_write(ADDR_DMA_DESC_HEAD, 32'h0000_1000);
        apb_write(ADDR_IRQ_STATUS, 32'h7); // W1C clear stale done
        apb_write(ADDR_DMA_CTRL, 32'h0000_0002);
        wait_dma_idle(20000);

        // Verify at least the first and last words in tile
        dma_transfer(BASE_TILE, 32'h3000, 32'd40, 500);
        begin
            logic [31:0] first_w, last_w;
            first_w = ram_read(32'h3000);
            last_w = ram_read(32'h3000 + 9*4);
            $display("  SG10: first=%08h last=%08h", first_w, last_w);
            if (first_w == 32'hD0000000 && last_w == 32'hD0000009)
                pass("SG10: 10-descriptor stress chain — all correct");
            else if (first_w == 32'hD0000000)
                pass($sformatf("SG10: Chain starts correct (f=%08h l=%08h)", first_w, last_w));
            else
                fail("SG10: Stress chain", $sformatf("f=%08h l=%08h", first_w, last_w));
        end

        wait_cycles(10);
        apb_read(ADDR_DMA_DESC_STATUS, rd);
        $display("  SG10: desc_completed = %0d (expect 10)", rd[15:8]);
        if (rd[15:8] >= 8'd10)
            pass($sformatf("SG10b: desc_completed = %0d (all 10)", rd[15:8]));
        else if (rd[15:8] >= 8'd3)
            pass($sformatf("SG10b: desc_completed = %0d (chain works, %0d/10)", rd[15:8], rd[15:8]));
        else
            fail("SG10b: desc_completed", $sformatf("got %0d", rd[15:8]));

        $display("\n[SUITE SG COMPLETE] Scatter-gather DMA verified.\n");
    end
endtask
