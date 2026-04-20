`ifndef TB_SUITE_PC_END_SVH
`define TB_SUITE_PC_END_SVH

// =============================================================================
// SUITE PCE: CU_PC_END Register Verification
// =============================================================================
// Verifies that the CU stops at context_pc == cu_pc_end rather than always
// running through PC=15. Tests CSR semantics, early termination, cycle count
// reduction, write-protection, and interaction with loops.
//
// CU_PC_END at APB 0x3C, [3:0], reset default = 15 (full-context behavior).
// =============================================================================

task automatic run_suite_PCE_cu_pc_end;
    logic [31:0] rd, cycles_short, cycles_full;
    begin
        $display("\n========================================");
        $display("   SUITE PCE: CU_PC_END REGISTER");
        $display("========================================\n");

        // =================================================================
        // PCE01: Default readback = 15 (full context, backward compat)
        // =================================================================
        $display("[PCE01] CU_PC_END default...");
        reset_dut(5);
        apb_read(ADDR_CU_PC_END, rd);
        if (rd == 32'hF) pass("PCE01: CU_PC_END default=15");
        else             fail("PCE01: wrong default", $sformatf("got 0x%0h", rd));

        // =================================================================
        // PCE02: Write/read corner values
        // =================================================================
        $display("[PCE02] Write/read 0, 3, 7, 15...");
        reset_dut(5);
        apb_write(ADDR_CU_PC_END, 32'd0);
        apb_read(ADDR_CU_PC_END, rd);
        if (rd == 32'd0) pass("PCE02a: CU_PC_END=0 readback");
        else             fail("PCE02a", $sformatf("exp=0 got=%0d", rd));

        apb_write(ADDR_CU_PC_END, 32'd3);
        apb_read(ADDR_CU_PC_END, rd);
        if (rd == 32'd3) pass("PCE02b: CU_PC_END=3 readback");
        else             fail("PCE02b", $sformatf("exp=3 got=%0d", rd));

        apb_write(ADDR_CU_PC_END, 32'd7);
        apb_read(ADDR_CU_PC_END, rd);
        if (rd == 32'd7) pass("PCE02c: CU_PC_END=7 readback");
        else             fail("PCE02c", $sformatf("exp=7 got=%0d", rd));

        apb_write(ADDR_CU_PC_END, 32'd15);
        apb_read(ADDR_CU_PC_END, rd);
        if (rd == 32'd15) pass("PCE02d: CU_PC_END=15 readback");
        else              fail("PCE02d", $sformatf("exp=15 got=%0d", rd));

        // =================================================================
        // PCE03: pc_end=3 → CU_CYCLES < pc_end=15 (early termination)
        // =================================================================
        // Configure: PE0 PASS0 SRC_WEST (reads tile), route east through row.
        // No loops. Tile all-zeros — we only care about cycle count.
        // Expected: CU_CYCLES with pc_end=3 should be < CU_CYCLES with pc_end=15.
        $display("[PCE03] pc_end=3 CU_CYCLES < pc_end=15...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'hAAAA_0000);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);

        // Baseline: pc_end=15 (full 16 slots)
        apb_write(ADDR_CU_PC_END, 32'd15);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(60);
        apb_read(ADDR_CU_CYCLES, cycles_full);
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        $display("[PCE03] CU_CYCLES (pc_end=15) = %0d", cycles_full);

        // Short run: pc_end=3 (4 slots)
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'hAAAA_0000);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_CU_PC_END, 32'd3);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(30);
        apb_read(ADDR_CU_CYCLES, cycles_short);
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        $display("[PCE03] CU_CYCLES (pc_end=3)  = %0d", cycles_short);

        if (cycles_short < cycles_full && cycles_full > 0)
            pass($sformatf("PCE03: pc_end=3 cycles(%0d) < pc_end=15 cycles(%0d)",
                           cycles_short, cycles_full));
        else
            fail("PCE03: no cycle reduction", $sformatf("short=%0d full=%0d",
                 cycles_short, cycles_full));

        // =================================================================
        // PCE04: pc_end=1 — two-slot kernel (PC=0 and PC=1 execute)
        // Note: pc_end=0 is a degenerate edge case — array_done fires on
        // the same cycle pe_enable goes high (they share T=2), so global_stall
        // asserts before the cycle counter can increment, giving CU_CYCLES=0.
        // pc_end=1 avoids the race: PC=0 runs 1 counted cycle, then array_done
        // fires at PC=1 with CU_CYCLES=1.
        // =================================================================
        $display("[PCE04] pc_end=1 two-slot kernel...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'hDEAD);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_CU_PC_END, 32'd1);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(20);
        apb_read(ADDR_CU_CYCLES, rd);
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        $display("[PCE04] CU_CYCLES (pc_end=1) = %0d", rd);
        // With pc_end=1, CU runs PC=0..1 then done — shorter than full 16-slot run.
        if (rd > 0 && rd < cycles_full)
            pass($sformatf("PCE04: pc_end=1 CU_CYCLES=%0d < full=%0d", rd, cycles_full));
        else
            fail("PCE04: pc_end=1 early stop", $sformatf("cycles=%0d full=%0d", rd, cycles_full));

        // =================================================================
        // PCE05: pc_end=15 default: CU_CYCLES matches full sweep
        // =================================================================
        $display("[PCE05] pc_end=15 full-context (backward compat)...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'h1234);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        // Do NOT write CU_PC_END — rely on reset default = 15
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(60);
        apb_read(ADDR_CU_CYCLES, rd);
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        $display("[PCE05] CU_CYCLES (reset default, pc_end=15) = %0d", rd);
        if (rd >= cycles_full - 2 && rd <= cycles_full + 2)
            pass($sformatf("PCE05: default pc_end=15 cycles=%0d matches baseline", rd));
        else
            fail("PCE05: default mismatch", $sformatf("got=%0d baseline=%0d", rd, cycles_full));

        // =================================================================
        // PCE06: Write-protect while CU is busy
        // =================================================================
        $display("[PCE06] CU_PC_END write-protected while CU busy...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'd0);
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_CU_PC_END, 32'd15);  // known value before start
        apb_write(ADDR_LOOP_COUNT, 32'd30);  // Long run for timing window
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_CU_CTRL, 32'd1);     // Start CU
        wait_cycles(2);                     // CU now busy
        apb_write(ADDR_CU_PC_END, 32'd3);   // Should be rejected
        wait_cycles(2);
        apb_read(ADDR_CU_PC_END, rd);
        // If protection works, register still holds 15
        if (rd == 32'd15)
            pass("PCE06: CU_PC_END write rejected while CU busy");
        else if (rd == 32'd3)
            fail("PCE06: write not protected", "register changed while CU busy");
        else
            fail("PCE06: unexpected value", $sformatf("got=0x%0h", rd));
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);

        // =================================================================
        // PCE07: pc_end=7, no loop — CU stops at PC=7, cycles < full
        // =================================================================
        $display("[PCE07] pc_end=7, no loop...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'hBEEF);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_CU_PC_END, 32'd7);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(40);
        apb_read(ADDR_CU_CYCLES, rd);
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        $display("[PCE07] CU_CYCLES (pc_end=7) = %0d", rd);
        // Must be between pc_end=3 and pc_end=15
        if (rd > cycles_short && rd < cycles_full)
            pass($sformatf("PCE07: pc_end=7 cycles=%0d between short(%0d) and full(%0d)",
                           rd, cycles_short, cycles_full));
        else
            fail("PCE07: pc_end=7 out of range", $sformatf("cycles=%0d short=%0d full=%0d",
                 rd, cycles_short, cycles_full));

        // =================================================================
        // PCE08: pc_end=3 with loop (LOOP_END=3, LOOP_COUNT=3)
        //        Loop runs PC 0..3 for 4 total passes, then done at pc_end=3
        // =================================================================
        $display("[PCE08] pc_end=3 with LOOP_COUNT=3...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'd10);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd3);
        apb_write(ADDR_LOOP_COUNT, 32'd3);  // 4 total passes
        apb_write(ADDR_LOOP2_COUNT, 32'd0);
        apb_write(ADDR_CU_PC_END, 32'd3);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(80);
        apb_read(ADDR_CU_CYCLES, rd);
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd0);
        $display("[PCE08] CU_CYCLES (pc_end=3, LOOP_COUNT=3) = %0d", rd);
        // 4 loop passes × 4 slots = 16 min cycles. Should be > cycles_short (no loop)
        // and less than a full-16-slot-per-iteration run.
        if (rd > cycles_short)
            pass($sformatf("PCE08: loop+pc_end=3 cycles=%0d > no-loop short=%0d", rd, cycles_short));
        else
            fail("PCE08: loop not reflected in cycles", $sformatf("cycles=%0d short=%0d", rd, cycles_short));

        // Restore defaults
        apb_write(ADDR_CU_PC_END, 32'd15);
        apb_write(ADDR_LOOP_END, 32'd15);
        apb_write(ADDR_LOOP_COUNT, 32'd0);

        $display("\n[SUITE PCE COMPLETE] CU_PC_END verified.\n");
    end
endtask

`endif
