`ifndef TB_SUITE_APB_SANITY_SVH
`define TB_SUITE_APB_SANITY_SVH

// =============================================================================
// SUITE AM: APB Register Sanity — Deployment-First Verification
// =============================================================================
// Systematically verifies every register in the APB address map (0x00–0x74).
// This is the FIRST suite to run when a bitstream is loaded on FPGA — if APB
// register access is broken, nothing else matters.
//
// Categories:
//   AM01-AM17: RW round-trip (write → readback → compare)
//   AM18-AM25: RO immutability (write 0xFFFFFFFF → verify unchanged)
//   AM26-AM29: W1C behavior (IRQ_STATUS write-1-to-clear)
//   AM30-AM33: Unmapped address reads (return 0x00000000)
//   AM34-AM39: Protected register rejection (busy guards)
//   AM40:      Reset default verification
// =============================================================================

task automatic run_suite_AM_apb_sanity;
    logic [31:0] rd, rd2, saved;
    begin
        $display("\n========================================");
        $display("   SUITE AM: APB REGISTER SANITY");
        $display("========================================\n");

        reset_dut(5);

        // =================================================================
        // RW ROUND-TRIP TESTS (AM01–AM17)
        // =================================================================
        // Write a test pattern, read it back, verify match.
        // DMA_CTRL and CU_CTRL have auto-clear on bit[0], tested separately.

        // AM01: DMA_SRC
        $display("[AM01] RW round-trip: DMA_SRC...");
        apb_write(ADDR_DMA_SRC, 32'hA5A5_A5A5);
        apb_check(ADDR_DMA_SRC, 32'hA5A5_A5A5, "AM01: DMA_SRC RW round-trip");

        // AM02: DMA_DST
        $display("[AM02] RW round-trip: DMA_DST...");
        apb_write(ADDR_DMA_DST, 32'h5A5A_5A5A);
        apb_check(ADDR_DMA_DST, 32'h5A5A_5A5A, "AM02: DMA_DST RW round-trip");

        // AM03: DMA_SIZE
        $display("[AM03] RW round-trip: DMA_SIZE...");
        apb_write(ADDR_DMA_SIZE, 32'h0000_1000);
        apb_check(ADDR_DMA_SIZE, 32'h0000_1000, "AM03: DMA_SIZE RW round-trip");

        // AM04: DMA_SRC_STRIDE
        $display("[AM04] RW round-trip: DMA_SRC_STRIDE...");
        apb_write(ADDR_DMA_SRC_STRIDE, 32'h0000_0100);
        apb_check(ADDR_DMA_SRC_STRIDE, 32'h0000_0100, "AM04: DMA_SRC_STRIDE RW round-trip");

        // AM05: DMA_ROWS
        $display("[AM05] RW round-trip: DMA_ROWS...");
        apb_write(ADDR_DMA_ROWS, 32'h0000_0010);
        apb_check(ADDR_DMA_ROWS, 32'h0000_0010, "AM05: DMA_ROWS RW round-trip");

        // AM06: DMA_COLS
        $display("[AM06] RW round-trip: DMA_COLS...");
        apb_write(ADDR_DMA_COLS, 32'h0000_0040);
        apb_check(ADDR_DMA_COLS, 32'h0000_0040, "AM06: DMA_COLS RW round-trip");

        // AM07: CU_TIMEOUT
        $display("[AM07] RW round-trip: CU_TIMEOUT...");
        apb_write(ADDR_CU_TIMEOUT, 32'h0001_0000);
        apb_check(ADDR_CU_TIMEOUT, 32'h0001_0000, "AM07: CU_TIMEOUT RW round-trip");

        // AM08: IRQ_MASK
        $display("[AM08] RW round-trip: IRQ_MASK...");
        apb_write(ADDR_IRQ_MASK, 32'h0000_0003);
        apb_check(ADDR_IRQ_MASK, 32'h0000_0003, "AM08: IRQ_MASK RW round-trip");

        // AM09: LOOP_START
        $display("[AM09] RW round-trip: LOOP_START...");
        apb_write(ADDR_LOOP_START, 32'h0000_0004);
        apb_check(ADDR_LOOP_START, 32'h0000_0004, "AM09: LOOP_START RW round-trip");

        // AM10: LOOP_END
        $display("[AM10] RW round-trip: LOOP_END...");
        apb_write(ADDR_LOOP_END, 32'h0000_000C);
        apb_check(ADDR_LOOP_END, 32'h0000_000C, "AM10: LOOP_END RW round-trip");

        // AM11: LOOP_COUNT
        $display("[AM11] RW round-trip: LOOP_COUNT...");
        apb_write(ADDR_LOOP_COUNT, 32'h0000_0005);
        apb_check(ADDR_LOOP_COUNT, 32'h0000_0005, "AM11: LOOP_COUNT RW round-trip");

        // AM12: LOOP2_START
        $display("[AM12] RW round-trip: LOOP2_START...");
        apb_write(ADDR_LOOP2_START, 32'h0000_0002);
        apb_check(ADDR_LOOP2_START, 32'h0000_0002, "AM12: LOOP2_START RW round-trip");

        // AM13: LOOP2_END
        $display("[AM13] RW round-trip: LOOP2_END...");
        apb_write(ADDR_LOOP2_END, 32'h0000_000A);
        apb_check(ADDR_LOOP2_END, 32'h0000_000A, "AM13: LOOP2_END RW round-trip");

        // AM14: LOOP2_COUNT
        $display("[AM14] RW round-trip: LOOP2_COUNT...");
        apb_write(ADDR_LOOP2_COUNT, 32'h0000_0003);
        apb_check(ADDR_LOOP2_COUNT, 32'h0000_0003, "AM14: LOOP2_COUNT RW round-trip");

        // AM15: TILE_BANK_SEL
        $display("[AM15] RW round-trip: TILE_BANK_SEL...");
        apb_write(ADDR_TILE_BANK_SEL, 32'h0000_0001);
        apb_check(ADDR_TILE_BANK_SEL, 32'h0000_0001, "AM15: TILE_BANK_SEL RW round-trip");
        apb_write(ADDR_TILE_BANK_SEL, 32'h0000_0000);  // Restore

        // AM16: DMA_CTRL auto-clear bit[0]
        // Write with bit[0]=0 → should retain. Then test auto-clear.
        $display("[AM16] DMA_CTRL auto-clear bit[0]...");
        apb_write(ADDR_DMA_CTRL, 32'hFFFF_FFFE);  // bit[0]=0
        apb_read(ADDR_DMA_CTRL, rd);
        // bit[0] was 0, no auto-clear needed, upper bits retained
        if (rd == 32'hFFFF_FFFE) pass("AM16a: DMA_CTRL non-start bits retained");
        else fail("AM16a: DMA_CTRL non-start bits", $sformatf("exp=0xFFFFFFFE got=0x%08h", rd));
        // Now write with bit[0]=1 → auto-clears after 1 cycle
        apb_write(ADDR_DMA_CTRL, 32'h0000_0001);
        wait_cycles(2);  // Give time for auto-clear
        apb_read(ADDR_DMA_CTRL, rd);
        if (rd[0] == 1'b0) pass("AM16b: DMA_CTRL bit[0] auto-cleared");
        else fail("AM16b: DMA_CTRL auto-clear", $sformatf("bit[0] still set, got=0x%08h", rd));

        // AM17: CU_CTRL auto-clear bit[0]
        $display("[AM17] CU_CTRL auto-clear bit[0]...");
        // Write CU_CTRL with only bit[0]=1 (start pulse, no soft_reset)
        apb_write(ADDR_CU_CTRL, 32'h0000_0001);
        wait_cycles(2);
        apb_read(ADDR_CU_CTRL, rd);
        if (rd[0] == 1'b0) pass("AM17: CU_CTRL bit[0] auto-cleared");
        else fail("AM17: CU_CTRL auto-clear", $sformatf("bit[0] still set, got=0x%08h", rd));
        // Clean up: deassert soft_reset
        apb_write(ADDR_CU_CTRL, 32'h0000_0000);

        // =================================================================
        // RO IMMUTABILITY TESTS (AM18–AM25)
        // =================================================================
        // Writing to RO registers must not change their value.
        reset_dut(5);

        // AM18: DMA_STATUS (RO)
        $display("[AM18] RO immutability: DMA_STATUS...");
        apb_read(ADDR_DMA_STATUS, saved);
        apb_write(ADDR_DMA_STATUS, 32'hFFFF_FFFF);
        apb_read(ADDR_DMA_STATUS, rd);
        if (rd === saved) pass("AM18: DMA_STATUS unchanged after write");
        else fail("AM18: DMA_STATUS mutated", $sformatf("was=0x%08h now=0x%08h", saved, rd));

        // AM19: CU_STATUS (RO)
        $display("[AM19] RO immutability: CU_STATUS...");
        apb_read(ADDR_CU_STATUS, saved);
        apb_write(ADDR_CU_STATUS, 32'hFFFF_FFFF);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd === saved) pass("AM19: CU_STATUS unchanged after write");
        else fail("AM19: CU_STATUS mutated", $sformatf("was=0x%08h now=0x%08h", saved, rd));

        // AM20: CU_CYCLES (RO)
        $display("[AM20] RO immutability: CU_CYCLES...");
        apb_read(ADDR_CU_CYCLES, saved);
        apb_write(ADDR_CU_CYCLES, 32'hFFFF_FFFF);
        apb_read(ADDR_CU_CYCLES, rd);
        if (rd === saved) pass("AM20: CU_CYCLES unchanged after write");
        else fail("AM20: CU_CYCLES mutated", $sformatf("was=0x%08h now=0x%08h", saved, rd));

        // AM21: RESULT_DATA (RO, muxed in cgra_top)
        $display("[AM21] RO immutability: RESULT_DATA...");
        apb_read(ADDR_RESULT_DATA, saved);
        apb_write(ADDR_RESULT_DATA, 32'hFFFF_FFFF);
        apb_read(ADDR_RESULT_DATA, rd);
        if (rd === saved) pass("AM21: RESULT_DATA unchanged after write");
        else fail("AM21: RESULT_DATA mutated", $sformatf("was=0x%08h now=0x%08h", saved, rd));

        // AM22: RESULT_STATUS (RO, muxed in cgra_top)
        $display("[AM22] RO immutability: RESULT_STATUS...");
        apb_read(ADDR_RESULT_STATUS, saved);
        apb_write(ADDR_RESULT_STATUS, 32'hFFFF_FFFF);
        apb_read(ADDR_RESULT_STATUS, rd);
        if (rd === saved) pass("AM22: RESULT_STATUS unchanged after write");
        else fail("AM22: RESULT_STATUS mutated", $sformatf("was=0x%08h now=0x%08h", saved, rd));

        // AM23: RESULT_ROW0 (RO, muxed in cgra_top)
        $display("[AM23] RO immutability: RESULT_ROW0...");
        apb_read(ADDR_RESULT_ROW0, saved);
        apb_write(ADDR_RESULT_ROW0, 32'hFFFF_FFFF);
        apb_read(ADDR_RESULT_ROW0, rd);
        if (rd === saved) pass("AM23: RESULT_ROW0 unchanged after write");
        else fail("AM23: RESULT_ROW0 mutated", $sformatf("was=0x%08h now=0x%08h", saved, rd));

        // AM24: RESULT_ROW1 (RO)
        $display("[AM24] RO immutability: RESULT_ROW1...");
        apb_read(ADDR_RESULT_ROW1, saved);
        apb_write(ADDR_RESULT_ROW1, 32'hFFFF_FFFF);
        apb_read(ADDR_RESULT_ROW1, rd);
        if (rd === saved) pass("AM24: RESULT_ROW1 unchanged after write");
        else fail("AM24: RESULT_ROW1 mutated", $sformatf("was=0x%08h now=0x%08h", saved, rd));

        // AM25: RESULT_ROW2, RESULT_ROW3 (RO)
        $display("[AM25] RO immutability: RESULT_ROW2, ROW3...");
        apb_read(ADDR_RESULT_ROW2, saved);
        apb_write(ADDR_RESULT_ROW2, 32'hFFFF_FFFF);
        apb_read(ADDR_RESULT_ROW2, rd);
        if (rd === saved) pass("AM25a: RESULT_ROW2 unchanged after write");
        else fail("AM25a: RESULT_ROW2 mutated", $sformatf("was=0x%08h now=0x%08h", saved, rd));

        apb_read(ADDR_RESULT_ROW3, saved);
        apb_write(ADDR_RESULT_ROW3, 32'hFFFF_FFFF);
        apb_read(ADDR_RESULT_ROW3, rd);
        if (rd === saved) pass("AM25b: RESULT_ROW3 unchanged after write");
        else fail("AM25b: RESULT_ROW3 mutated", $sformatf("was=0x%08h now=0x%08h", saved, rd));

        // =================================================================
        // W1C TESTS (AM26–AM29): IRQ_STATUS write-1-to-clear
        // =================================================================
        reset_dut(5);

        // AM26: Trigger DMA done → W1C clear bit[0]
        $display("[AM26] W1C: DMA done → clear...");
        // Seed AXI RAM, do a tiny DMA to trigger dma_done
        ram_write(32'h0000_0000, 32'hDEAD_BEEF);
        apb_write(ADDR_DMA_SRC, 32'h0000_0000);
        apb_write(ADDR_DMA_DST, 32'h0000_0100);
        apb_write(ADDR_DMA_SIZE, 32'd4);
        apb_write(ADDR_DMA_CTRL, 32'h1);
        wait_dma_done(500);
        // IRQ_STATUS[0] should be set (dma_done_latch)
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[0] === 1'b1) pass("AM26a: IRQ_STATUS[0] set after DMA done");
        else fail("AM26a: IRQ_STATUS[0] not set", $sformatf("got=0x%08h", rd));
        // W1C: write 1 to bit[0] to clear
        apb_write(ADDR_IRQ_STATUS, 32'h0000_0001);
        wait_cycles(1);
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[0] === 1'b0) pass("AM26b: IRQ_STATUS[0] cleared by W1C");
        else fail("AM26b: W1C clear failed", $sformatf("got=0x%08h", rd));

        // AM27: Trigger CU done → W1C clear bit[1]
        $display("[AM27] W1C: CU done → clear...");
        reset_dut(5);
        // Configure PE0 with NOP, run CGRA to completion (auto-stop)
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_CU_CTRL, 32'h1);  // Start CU
        wait_cycles(50);  // Wait for auto-stop (16 contexts + margin)
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[1] === 1'b1) pass("AM27a: IRQ_STATUS[1] set after CU done");
        else fail("AM27a: IRQ_STATUS[1] not set", $sformatf("got=0x%08h", rd));
        // W1C: write 1 to bit[1]
        apb_write(ADDR_IRQ_STATUS, 32'h0000_0002);
        wait_cycles(1);
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[1] === 1'b0) pass("AM27b: IRQ_STATUS[1] cleared by W1C");
        else fail("AM27b: W1C clear failed", $sformatf("got=0x%08h", rd));

        // AM28: W1C with write-0 must NOT clear
        $display("[AM28] W1C: write-0 must not clear...");
        reset_dut(5);
        // Trigger DMA done again
        ram_write(32'h0000_0000, 32'h1234_5678);
        apb_write(ADDR_DMA_SRC, 32'h0000_0000);
        apb_write(ADDR_DMA_DST, 32'h0000_0200);
        apb_write(ADDR_DMA_SIZE, 32'd4);
        apb_write(ADDR_DMA_CTRL, 32'h1);
        wait_dma_done(500);
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[0] !== 1'b1) begin
            fail("AM28: Setup", "DMA done latch not set");
        end else begin
            // Write 0x0 → must NOT clear
            apb_write(ADDR_IRQ_STATUS, 32'h0000_0000);
            wait_cycles(1);
            apb_read(ADDR_IRQ_STATUS, rd);
            if (rd[0] === 1'b1) pass("AM28: W1C write-0 preserved DMA done bit");
            else fail("AM28: write-0 cleared bit", $sformatf("got=0x%08h", rd));
        end

        // AM29: Selective W1C — clear bit[0] only, bit[1] preserved
        $display("[AM29] W1C: selective clear...");
        reset_dut(5);
        // Trigger both DMA done and CU done
        ram_write(32'h0000_0000, 32'hCAFE_BABE);
        apb_write(ADDR_DMA_SRC, 32'h0000_0000);
        apb_write(ADDR_DMA_DST, 32'h0000_0300);
        apb_write(ADDR_DMA_SIZE, 32'd4);
        apb_write(ADDR_DMA_CTRL, 32'h1);
        wait_dma_done(500);
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_CU_CTRL, 32'h1);
        wait_cycles(50);
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[1:0] === 2'b11) begin
            // Clear only bit[0], preserve bit[1]
            apb_write(ADDR_IRQ_STATUS, 32'h0000_0001);
            wait_cycles(1);
            apb_read(ADDR_IRQ_STATUS, rd);
            if (rd[1] === 1'b1 && rd[0] === 1'b0) pass("AM29: Selective W1C — bit[0] cleared, bit[1] preserved");
            else fail("AM29: Selective W1C", $sformatf("exp=0x02 got=0x%08h", rd));
        end else begin
            fail("AM29: Setup", $sformatf("Both done bits not set: got=0x%08h", rd));
        end

        // =================================================================
        // UNMAPPED ADDRESS READS (AM30–AM33)
        // =================================================================
        $display("[AM30-33] Unmapped address reads...");
        reset_dut(5);

        // AM30: 0x38 (gap between IRQ_MASK and RESULT_DATA)
        apb_check(32'h38, 32'h0, "AM30: Unmapped 0x38 returns 0");

        // AM31: 0x3C (gap)
        apb_check(32'h3C, 32'h0, "AM31: Unmapped 0x3C returns 0");

        // AM32: 0x54 is now RESULT_SKIP (default 11 = 0x0B)
        apb_check(32'h54, 32'h0000_000D, "AM32: RESULT_SKIP default=13");

        // AM33: beyond register space
        apb_check(ADDR_UNMAPPED, 32'h0, "AM33: Unmapped returns 0");

        // =================================================================
        // PROTECTED REGISTER REJECTION (AM34–AM39)
        // =================================================================
        // DMA-protected: DMA_SRC/DST/SIZE rejected while DMA busy
        // CU-protected: CU_TIMEOUT/LOOP regs rejected while CU busy

        // AM34-AM36: DMA config rejected while busy
        $display("[AM34-36] Protected regs: DMA busy...");
        reset_dut(5);
        // Set up DMA registers with known values
        apb_write(ADDR_DMA_SRC, 32'h0000_1000);
        apb_write(ADDR_DMA_DST, 32'h0000_2000);
        apb_write(ADDR_DMA_SIZE, 32'h0000_0100);  // 256 bytes — enough to keep DMA busy
        // Seed memory
        for (int i = 0; i < 256; i++) mem[32'h1000 + i] = i[7:0];
        // Start DMA
        apb_write(ADDR_DMA_CTRL, 32'h1);
        wait_cycles(2);  // Let DMA start
        // Try to change DMA_SRC while busy
        apb_read(ADDR_DMA_STATUS, rd);
        if (rd[0] === 1'b1) begin  // Verify actually busy
            apb_write(ADDR_DMA_SRC, 32'hBAAD_F00D);
            apb_read(ADDR_DMA_SRC, rd);
            if (rd === 32'h0000_1000) pass("AM34: DMA_SRC write rejected while busy");
            else fail("AM34: DMA_SRC not protected", $sformatf("got=0x%08h", rd));

            apb_write(ADDR_DMA_DST, 32'hBAAD_F00D);
            apb_read(ADDR_DMA_DST, rd);
            if (rd === 32'h0000_2000) pass("AM35: DMA_DST write rejected while busy");
            else fail("AM35: DMA_DST not protected", $sformatf("got=0x%08h", rd));

            apb_write(ADDR_DMA_SIZE, 32'hBAAD_F00D);
            apb_read(ADDR_DMA_SIZE, rd);
            if (rd === 32'h0000_0100) pass("AM36: DMA_SIZE write rejected while busy");
            else fail("AM36: DMA_SIZE not protected", $sformatf("got=0x%08h", rd));
        end else begin
            // DMA_BUSY not asserted after 2 cycles — 256-byte transfer should never
            // complete this fast; either DMA_CTRL write failed or DMA engine has a bug.
            fail("AM34: DMA_SRC protection", "DMA not busy after start — protection untested");
            fail("AM35: DMA_DST protection", "DMA not busy after start — protection untested");
            fail("AM36: DMA_SIZE protection", "DMA not busy after start — protection untested");
        end
        wait_dma_done(1000);  // Let DMA finish

        // AM37-AM39: CU config rejected while busy
        // NOTE: cgra_top auto-stop fires after 16 PE cycles regardless of loops.
        // All write attempts must happen within that 16-cycle busy window.
        // Strategy: issue all 3 writes first (fast), then readback to verify.
        $display("[AM37-39] Protected regs: CU busy...");
        reset_dut(5);
        apb_write(ADDR_CU_TIMEOUT, 32'h0000_FFFF);
        apb_write(ADDR_LOOP_START, 32'h0000_0002);
        apb_write(ADDR_LOOP_COUNT, 32'h0000_000A);
        // Configure PE0 NOP so CU will run
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        // Start CU — auto-stop fires after 16 cycles (~posedge +20 from here)
        apb_write(ADDR_CU_CTRL, 32'h1);
        wait_cycles(2);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[0] === 1'b1) begin  // Verify busy — must be within 16-cycle window
            // Issue all three writes immediately (each 3 cycles, total ~9 cycles)
            // At cycle ~8 after start, CU is still busy (auto-stop at ~16)
            apb_write(ADDR_CU_TIMEOUT, 32'hBAAD_F00D);   // ~cycle 11
            apb_write(ADDR_LOOP_START, 32'hBAAD_F00D);    // ~cycle 14
            apb_write(ADDR_LOOP_COUNT, 32'hBAAD_F00D);    // ~cycle 17
            // CU may have finished by now — readbacks can happen after auto-stop.
            // What matters is the writes were during busy, so they were rejected.
            wait_cycles(20);  // Let CU finish
            apb_read(ADDR_CU_TIMEOUT, rd);
            if (rd === 32'h0000_FFFF) pass("AM37: CU_TIMEOUT write rejected while busy");
            else fail("AM37: CU_TIMEOUT not protected", $sformatf("got=0x%08h", rd));

            apb_read(ADDR_LOOP_START, rd);
            if (rd === 32'h0000_0002) pass("AM38: LOOP_START write rejected while busy");
            else fail("AM38: LOOP_START not protected", $sformatf("got=0x%08h", rd));

            apb_read(ADDR_LOOP_COUNT, rd);
            if (rd === 32'h0000_000A) pass("AM39: LOOP_COUNT write rejected while busy");
            else fail("AM39: LOOP_COUNT not protected", $sformatf("got=0x%08h", rd));
        end else begin
            // CU_BUSY not asserted — CU should be busy with LOOP_COUNT=10; something is wrong.
            fail("AM37: CU_TIMEOUT protection", "CU not busy after start — protection untested");
            fail("AM38: LOOP_START protection", "CU not busy after start — protection untested");
            fail("AM39: LOOP_COUNT protection", "CU not busy after start — protection untested");
        end
        // Stop CU
        apb_write(ADDR_CU_CTRL, 32'h2);
        wait_cycles(3);
        apb_write(ADDR_CU_CTRL, 32'h0);

        // =================================================================
        // RESET DEFAULT VERIFICATION (AM40)
        // =================================================================
        $display("[AM40] Reset defaults...");
        reset_dut(5);

        // After reset: LOOP_END=15, LOOP2_END=15, everything else=0
        apb_read(ADDR_LOOP_END, rd);
        apb_read(ADDR_LOOP2_END, rd2);
        if (rd === 32'd15 && rd2 === 32'd15) begin
            pass("AM40a: LOOP_END and LOOP2_END default to 15");
        end else begin
            fail("AM40a: Reset defaults", $sformatf("LOOP_END=%0d LOOP2_END=%0d (exp 15,15)", rd, rd2));
        end

        apb_read(ADDR_LOOP_COUNT, rd);
        apb_read(ADDR_DMA_SIZE, rd2);
        if (rd === 32'd0 && rd2 === 32'd0) begin
            pass("AM40b: LOOP_COUNT and DMA_SIZE default to 0");
        end else begin
            fail("AM40b: Reset defaults", $sformatf("LOOP_COUNT=%0d DMA_SIZE=%0d (exp 0,0)", rd, rd2));
        end

        apb_read(ADDR_DMA_SRC, rd);
        apb_read(ADDR_DMA_DST, rd2);
        if (rd === 32'd0 && rd2 === 32'd0) begin
            pass("AM40c: DMA_SRC and DMA_DST default to 0");
        end else begin
            fail("AM40c: Reset defaults", $sformatf("DMA_SRC=0x%08h DMA_DST=0x%08h", rd, rd2));
        end

        $display("\n[SUITE AM COMPLETE] APB Register Sanity finished.\n");
    end
endtask

`endif
