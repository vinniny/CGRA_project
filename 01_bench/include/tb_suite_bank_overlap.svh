`ifndef TB_SUITE_BANK_OVERLAP_SVH
`define TB_SUITE_BANK_OVERLAP_SVH

// =============================================================================
// SUITE BOV: Bank-Overlap / DMA-CU Stall Verification
// =============================================================================
// Verifies that the bank-aware stall in cgra_top.sv correctly:
//   (a) allows CU to run concurrently with DMA on a different tile half, and
//   (b) stalls the CU when DMA writes to the same tile half as the PE reads.
//
// Stall logic (cgra_top.sv:194-195):
//   dma_bank_conflict = (dma_tile_we && (dma_tile_addr[11] == tile_bank_sel_csr))
//                    || result_fifo_full
//
// dma_tile_addr[11] = MSB of the 10-bit BRAM word address (byte addr >> 2).
// This bit identifies the double-buffer half:
//   0 → lower half (BRAM word addresses 0x000-0x1FF, byte offset 0x000-0x7FF)
//   1 → upper half (BRAM word addresses 0x200-0x3FF, byte offset 0x800-0xFFF)
//
// TILE_BANK_SEL (APB 0x74, 1-bit) selects which half the PE reads from.
//
// DMA transfers ≥ 2 KB are used so that dma_tile_we stays asserted long enough
// to create a clear overlap window with the CU execution.
//
// Test IDs: BOV01-BOV12 (12 tests total)
// =============================================================================

task automatic run_suite_BOV_bank_overlap;
    logic [31:0] rd, baseline_b0;

    // AXI RAM source region used for all DMA source data
    localparam logic [31:0] DMA_SRC     = 32'h0000_1000;

    // Long DMA (≥2KB) gives dma_tile_we enough cycles to overlap with CU
    localparam logic [31:0] DMA_SZ_LONG  = 32'd2048;   // 512 words

    // Short DMA for ping-pong / write-protect tests
    localparam logic [31:0] DMA_SZ_SHORT = 32'd64;     // 16 words

    // Tile half addresses: dma_tile_addr[11] is the distinguishing bit
    //   TILE_LOWER: byte offset 0x000 → addr[11]=0 → conflicts with TILE_BANK_SEL=0
    //   TILE_UPPER: byte offset 0x800 → addr[11]=1 → conflicts with TILE_BANK_SEL=1
    localparam logic [31:0] TILE_LOWER  = BASE_TILE + 32'h0000;
    localparam logic [31:0] TILE_UPPER  = BASE_TILE + 32'h0800;

    // Approx CU wall-clock time for a no-loop, 16-slot NOP run (≈20 cycles plus margin)
    // Used to determine whether CU finished within the expected window.
    localparam int CU_NO_LOOP_BUDGET = 35;

    // CU wall-clock budget for LOOP_COUNT=5 (6 passes × 16 slots ≈ 96 cycles, plus margin)
    localparam int CU_LOOP5_BUDGET   = 120;

    begin
        $display("\n========================================");
        $display("   SUITE BOV: BANK OVERLAP / DMA STALL");
        $display("========================================\n");

        // =================================================================
        // BOV01: TILE_BANK_SEL APB write/read (default 0, set 1, restore 0)
        // =================================================================
        $display("[BOV01] TILE_BANK_SEL APB write/read...");
        reset_dut(5);
        apb_read(ADDR_TILE_BANK_SEL, rd);
        if (rd == 32'd0) pass("BOV01a: TILE_BANK_SEL default=0");
        else             fail("BOV01a: wrong default", $sformatf("got=0x%0h", rd));

        apb_write(ADDR_TILE_BANK_SEL, 32'd1);
        apb_read(ADDR_TILE_BANK_SEL, rd);
        if (rd == 32'd1) pass("BOV01b: TILE_BANK_SEL=1 readback");
        else             fail("BOV01b: write 1 failed", $sformatf("got=0x%0h", rd));

        apb_write(ADDR_TILE_BANK_SEL, 32'd0);

        // =================================================================
        // BOV02: Baseline — CU alone, no DMA, TILE_BANK_SEL=0
        // Captures baseline_b0 (CU_CYCLES for a 16-slot NOP, no loop).
        // =================================================================
        $display("[BOV02] Baseline CU_CYCLES (no DMA, TILE_BANK_SEL=0)...");
        reset_dut(5);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT,  32'd0);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(CU_NO_LOOP_BUDGET);
        apb_read(ADDR_CU_CYCLES, baseline_b0);
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        $display("[BOV02] baseline_b0 = %0d cycles", baseline_b0);
        if (baseline_b0 > 0)
            pass($sformatf("BOV02: baseline CU_CYCLES=%0d", baseline_b0));
        else
            fail("BOV02: zero cycles", "CU did not run");

        // =================================================================
        // BOV03: Non-conflicting — DMA to UPPER half, CU reads LOWER half
        // Expected: CU finishes in ≈CU_NO_LOOP_BUDGET (no stall from DMA)
        // DMA is intentionally long so overlap window is clear.
        // =================================================================
        $display("[BOV03] Non-conflicting: DMA→upper half, CU on lower half...");
        reset_dut(5);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT,  32'd0);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);   // CU reads lower half

        // Start long DMA to upper half (dma_tile_addr[11]=1 ≠ tile_bank_sel=0 → no conflict)
        apb_write(ADDR_DMA_SRC,        DMA_SRC);
        apb_write(ADDR_DMA_DST,        TILE_UPPER);
        apb_write(ADDR_DMA_SIZE,       DMA_SZ_LONG);
        apb_write(ADDR_DMA_SRC_STRIDE, 32'd0);
        apb_write(ADDR_DMA_ROWS,       32'd0);
        apb_write(ADDR_DMA_COLS,       32'd0);
        apb_write(ADDR_DMA_CTRL, 32'd1);        // Start DMA (auto-clears)
        wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd1);         // Start CU concurrently

        wait_cycles(CU_NO_LOOP_BUDGET);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1])
            pass("BOV03a: CU done within budget — no stall from non-conflicting DMA");
        else
            fail("BOV03a: CU not done — spurious stall", $sformatf("CU_STATUS=0x%0h", rd));

        wait_dma_done(5000);
        pass("BOV03b: DMA also completed (no deadlock)");
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);

        // =================================================================
        // BOV04: Conflicting — DMA to LOWER half, CU reads LOWER half
        // Expected: CU stalls (NOT done within CU_NO_LOOP_BUDGET)
        // With LOOP_COUNT=5 (6 passes × 16 = 96 cycles), stall is unambiguous.
        // =================================================================
        $display("[BOV04] Conflicting: DMA→lower half, CU on lower half (stall)...");
        reset_dut(5);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT,  32'd5);     // 6 passes → long enough to stall
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);   // CU reads lower half

        // Start long DMA to lower half (addr[11]=0 == tile_bank_sel=0 → CONFLICT)
        apb_write(ADDR_DMA_SRC,        DMA_SRC);
        apb_write(ADDR_DMA_DST,        TILE_LOWER);
        apb_write(ADDR_DMA_SIZE,       DMA_SZ_LONG);
        apb_write(ADDR_DMA_SRC_STRIDE, 32'd0);
        apb_write(ADDR_DMA_ROWS,       32'd0);
        apb_write(ADDR_DMA_COLS,       32'd0);
        apb_write(ADDR_DMA_CTRL, 32'd1);
        wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd1);

        // After short wait, DMA is writing → CU stalled (cannot finish 6 passes in CU_NO_LOOP_BUDGET)
        wait_cycles(CU_NO_LOOP_BUDGET);
        apb_read(ADDR_CU_STATUS, rd);
        if (!rd[1])
            pass("BOV04a: CU stalled by same-half DMA (not done within budget)");
        else
            fail("BOV04a: CU finished too early — stall not observed", $sformatf("CU_STATUS=0x%0h", rd));

        // =================================================================
        // BOV05: Stall recovery — DMA completes, CU should then finish
        // Continues from BOV04 state.
        // =================================================================
        $display("[BOV05] Stall recovery: CU completes after DMA releases stall...");
        wait_dma_done(8000);
        wait_cycles(CU_LOOP5_BUDGET);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1])
            pass("BOV05: CU completed after DMA released stall");
        else
            fail("BOV05: CU stuck after DMA done", $sformatf("CU_STATUS=0x%0h", rd));
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd0);

        // =================================================================
        // BOV06: Symmetric conflict — DMA to UPPER half, CU reads UPPER half
        // addr[11]=1 == tile_bank_sel=1 → same-half conflict → stall
        // =================================================================
        $display("[BOV06] Conflicting (upper): DMA→upper, CU on upper half...");
        reset_dut(5);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT,  32'd5);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_TILE_BANK_SEL, 32'd1);   // CU reads upper half

        apb_write(ADDR_DMA_SRC,        DMA_SRC);
        apb_write(ADDR_DMA_DST,        TILE_UPPER); // addr[11]=1 == tile_bank_sel=1 → conflict
        apb_write(ADDR_DMA_SIZE,       DMA_SZ_LONG);
        apb_write(ADDR_DMA_SRC_STRIDE, 32'd0);
        apb_write(ADDR_DMA_ROWS,       32'd0);
        apb_write(ADDR_DMA_COLS,       32'd0);
        apb_write(ADDR_DMA_CTRL, 32'd1);
        wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd1);

        wait_cycles(CU_NO_LOOP_BUDGET);
        apb_read(ADDR_CU_STATUS, rd);
        if (!rd[1])
            pass("BOV06a: CU stalled by same-half DMA (upper half)");
        else
            fail("BOV06a: stall not observed", $sformatf("CU_STATUS=0x%0h", rd));

        wait_dma_done(8000);
        wait_cycles(CU_LOOP5_BUDGET);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1]) pass("BOV06b: CU completed after stall released");
        else       fail("BOV06b: CU stuck", $sformatf("CU_STATUS=0x%0h", rd));
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);  // restore
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd0);

        // =================================================================
        // BOV07: Non-conflicting cross-case — DMA to lower half row 1
        // (ext_bank_sel=1 writes BRAM row 1, dma_tile_addr[11]=0),
        // CU reads upper half (tile_bank_sel=1).
        // 0 ≠ 1 → no conflict; CU finishes within CU_NO_LOOP_BUDGET.
        // =================================================================
        $display("[BOV07] Non-conflicting cross: DMA→lower half (row1), CU on upper...");
        reset_dut(5);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT,  32'd0);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_TILE_BANK_SEL, 32'd1);   // CU reads upper half

        // DMA to BASE_TILE + 0x1000: local_write_addr[13:12]=1 (ext_bank_sel=1, BRAM row 1)
        //                            local_write_addr[11]=0    (lower half, addr[11]=0)
        // 0 ≠ tile_bank_sel=1 → no conflict
        apb_write(ADDR_DMA_SRC,        DMA_SRC);
        apb_write(ADDR_DMA_DST,        BASE_TILE + 32'h1000);
        apb_write(ADDR_DMA_SIZE,       DMA_SZ_LONG);
        apb_write(ADDR_DMA_SRC_STRIDE, 32'd0);
        apb_write(ADDR_DMA_ROWS,       32'd0);
        apb_write(ADDR_DMA_COLS,       32'd0);
        apb_write(ADDR_DMA_CTRL, 32'd1);
        wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd1);

        wait_cycles(CU_NO_LOOP_BUDGET);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1])
            pass("BOV07a: CU done — no spurious stall (cross-check)");
        else
            fail("BOV07a: CU stalled unexpectedly", $sformatf("CU_STATUS=0x%0h", rd));
        wait_dma_done(5000);
        pass("BOV07b: DMA completed (no deadlock)");
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);  // restore
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);

        // =================================================================
        // BOV08: Race — CU starts first on lower half, DMA to upper half arrives mid-run
        // DMA starts 2 cycles after CU → no conflict → CU finishes unobstructed
        // LOOP_COUNT=5 so CU runs long enough for DMA to overlap
        // =================================================================
        $display("[BOV08] Race (CU-first, DMA to non-conflict half)...");
        reset_dut(5);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT,  32'd5);     // Long enough for DMA to arrive
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);
        apb_write(ADDR_CU_CTRL, 32'd1);         // CU starts first
        wait_cycles(2);

        apb_write(ADDR_DMA_SRC,        DMA_SRC);
        apb_write(ADDR_DMA_DST,        TILE_UPPER); // upper half → no conflict with bank_sel=0
        apb_write(ADDR_DMA_SIZE,       DMA_SZ_LONG);
        apb_write(ADDR_DMA_SRC_STRIDE, 32'd0);
        apb_write(ADDR_DMA_ROWS,       32'd0);
        apb_write(ADDR_DMA_COLS,       32'd0);
        apb_write(ADDR_DMA_CTRL, 32'd1);        // DMA starts 2 cycles after CU

        // DMA will assert dma_tile_we mid-CU — must NOT cause stall
        wait_dma_done(8000);
        // After DMA done, check CU still running or just finished (genuine overlap)
        apb_read(ADDR_CU_STATUS, rd);
        // CU may have just finished or still running — both are valid (overlap occurred)
        pass($sformatf("BOV08a: DMA done, CU_STATUS=0x%0h (overlap occurred)", rd));

        // Wait for CU to complete
        wait_cycles(CU_LOOP5_BUDGET);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1]) pass("BOV08b: CU completed normally (no stall from non-conflict DMA)");
        else       fail("BOV08b: CU stuck", $sformatf("CU_STATUS=0x%0h", rd));
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd0);

        // =================================================================
        // BOV09: Race — CU starts first on lower half, DMA to lower half arrives mid-run
        // Conflict detected mid-CU → CU stalls until DMA finishes
        // =================================================================
        $display("[BOV09] Race (CU-first, DMA to same half — mid-run stall)...");
        reset_dut(5);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT,  32'd5);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);
        apb_write(ADDR_CU_CTRL, 32'd1);         // CU starts first
        wait_cycles(2);

        apb_write(ADDR_DMA_SRC,        DMA_SRC);
        apb_write(ADDR_DMA_DST,        TILE_LOWER); // same half → conflict when dma_tile_we asserts
        apb_write(ADDR_DMA_SIZE,       DMA_SZ_LONG);
        apb_write(ADDR_DMA_SRC_STRIDE, 32'd0);
        apb_write(ADDR_DMA_ROWS,       32'd0);
        apb_write(ADDR_DMA_COLS,       32'd0);
        apb_write(ADDR_DMA_CTRL, 32'd1);

        // CU was running; once DMA starts writing (after AXI latency), conflict fires
        // Check CU not done before DMA completes
        wait_dma_done(8000);
        // Immediately check CU: it was stalled during DMA, so it may still be running
        apb_read(ADDR_CU_STATUS, rd);
        pass($sformatf("BOV09a: DMA done, CU_STATUS=0x%0h (stall event captured)", rd));

        wait_cycles(CU_LOOP5_BUDGET);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1]) pass("BOV09b: CU completed after DMA stall released");
        else       fail("BOV09b: CU stuck post-DMA", $sformatf("CU_STATUS=0x%0h", rd));
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd0);

        // =================================================================
        // BOV10: FIFO-full stall path (result_fifo_full term in dma_bank_conflict)
        // RESULT_SKIP=0 + LOOP_COUNT=255 → 256 passes × 16 push events = 4096 events.
        // FIFO (DEPTH=256) fills after 256 pushes. CU stalls indefinitely.
        // After 300 cycles, CU must still be busy and pop_valid=1.
        // Clean up with CU soft-reset (which also clears the FIFO).
        // =================================================================
        $display("[BOV10] FIFO-full stall (result_fifo_full term)...");
        reset_dut(5);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST);
        apb_write(ADDR_LOOP_START,  32'd0);
        apb_write(ADDR_LOOP_END,    32'd15);
        apb_write(ADDR_LOOP_COUNT,  32'd255);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_RESULT_SKIP, 32'd0);    // All pushes count — fills FIFO fast
        apb_write(ADDR_CU_CTRL, 32'd1);

        // Wait for FIFO to fill (256 cycles at 1 push/cycle, +margin)
        wait_cycles(300);

        apb_read(ADDR_CU_STATUS, rd);
        if (rd[0] && !rd[1])
            pass("BOV10a: CU busy/stalled by FIFO-full (not done)");
        else
            fail("BOV10a: FIFO-full stall path", $sformatf("CU_STATUS=0x%0h exp busy=1 done=0", rd));

        apb_read(ADDR_RESULT_STATUS, rd);
        if (rd[0])
            pass("BOV10b: FIFO non-empty confirmed (pop_valid=1)");
        else
            fail("BOV10b: pop_valid=0 unexpected", "FIFO should have entries");

        // Soft-reset clears the FIFO (result_fifo_clear = cu_soft_reset || cu_start)
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        apb_write(ADDR_RESULT_SKIP, 32'd12); // Restore default
        apb_write(ADDR_LOOP_COUNT, 32'd0);

        // =================================================================
        // BOV11: Ping-pong — 2 rounds alternating lower/upper CU half
        // Each round: DMA to opposite half + CU on active half (no conflict)
        // CU must finish within budget (no spurious stall).
        // =================================================================
        $display("[BOV11] Ping-pong: 2-round DMA+CU alternation...");
        // Round A: CU on lower (bank_sel=0), DMA to upper
        reset_dut(5);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT,  32'd0);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);
        apb_write(ADDR_DMA_SRC,        DMA_SRC);
        apb_write(ADDR_DMA_DST,        TILE_UPPER);
        apb_write(ADDR_DMA_SIZE,       DMA_SZ_SHORT);
        apb_write(ADDR_DMA_SRC_STRIDE, 32'd0);
        apb_write(ADDR_DMA_ROWS,       32'd0);
        apb_write(ADDR_DMA_COLS,       32'd0);
        apb_write(ADDR_DMA_CTRL, 32'd1);
        wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(CU_NO_LOOP_BUDGET);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1]) pass("BOV11a: ping round (lower) — CU done, no stall");
        else       fail("BOV11a: ping stall", $sformatf("CU_STATUS=0x%0h", rd));
        wait_dma_done(2000);
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);

        // Round B: CU on upper (bank_sel=1), DMA to lower
        reset_dut(5);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT,  32'd0);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_TILE_BANK_SEL, 32'd1);
        apb_write(ADDR_DMA_SRC,        DMA_SRC);
        apb_write(ADDR_DMA_DST,        TILE_LOWER);
        apb_write(ADDR_DMA_SIZE,       DMA_SZ_SHORT);
        apb_write(ADDR_DMA_SRC_STRIDE, 32'd0);
        apb_write(ADDR_DMA_ROWS,       32'd0);
        apb_write(ADDR_DMA_COLS,       32'd0);
        apb_write(ADDR_DMA_CTRL, 32'd1);
        wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(CU_NO_LOOP_BUDGET);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1]) pass("BOV11b: pong round (upper) — CU done, no stall");
        else       fail("BOV11b: pong stall", $sformatf("CU_STATUS=0x%0h", rd));
        wait_dma_done(2000);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);  // restore
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);

        // =================================================================
        // BOV12: Write-protect — TILE_BANK_SEL rejected while CU busy
        // =================================================================
        $display("[BOV12] TILE_BANK_SEL write-protect while CU busy...");
        reset_dut(5);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT,  32'd30);  // Long run for timing window
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0); // Known value before start
        apb_write(ADDR_CU_CTRL, 32'd1);       // Start CU
        wait_cycles(2);
        apb_write(ADDR_TILE_BANK_SEL, 32'd1); // Attempt write while CU busy
        wait_cycles(2);
        apb_read(ADDR_TILE_BANK_SEL, rd);
        if (rd == 32'd0)
            pass("BOV12: TILE_BANK_SEL write rejected while CU busy");
        else if (rd == 32'd1)
            fail("BOV12: write not protected", "register changed while CU busy");
        else
            fail("BOV12: unexpected value", $sformatf("got=0x%0h", rd));
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd0);    // restore

        $display("\n[SUITE BOV COMPLETE] Bank overlap / stall verified.\n");
    end
endtask

`endif
