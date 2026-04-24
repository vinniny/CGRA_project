`ifndef TB_SUITE_RESULT_FIFO_STRESS_SVH
`define TB_SUITE_RESULT_FIFO_STRESS_SVH

// =============================================================================
// SUITE FRS: Result FIFO Stress Tests (T2)
// =============================================================================
// Regression oracle for Bug #1: result_fifo_full incorrectly gated into
// dma_bank_conflict → global_stall, permanently stalling the CU on long loops.
//
// With RESULT_SKIP=12 and FIFO DEPTH=256, the FIFO fills at cycle 268 of any
// CU run that generates >268 push_valid cycles (784 for the FC v2 MAC loop,
// 2048 for FRS03's LOOP_COUNT=127).
//
// FRS01: LOOP_COUNT=48 (784 cyc) — CU must complete; FAILS pre-fix, passes post
// FRS02: RESULT_SKIP/LOOP_COUNT sweep — all combos must complete
// FRS03: LOOP_COUNT=127 (2048 cyc) — overflow confirmed AND CU completes
// =============================================================================

task automatic frs_cu_wait_done(input int timeout_cyc, input string testname);
    logic [31:0] cu_stat;
    int t;
    t = 0;
    do begin
        wait_cycles(1);
        apb_read(ADDR_CU_STATUS, cu_stat);
        t++;
    end while (!cu_stat[1] && t < timeout_cyc);
    if (t >= timeout_cyc)
        fail({testname, ": CU timeout — FIFO-overflow stall pre-fix?"},
             $sformatf("timeout=%0d fifo_full=%b fifo_count=%0d",
                 timeout_cyc,
                 tb_top.u_dut.result_fifo_full,
                 tb_top.u_dut.result_fifo_count));
endtask

task automatic frs_start_cu_no_reset;
    apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(3);
    apb_write(ADDR_CU_CTRL, 32'd0); wait_cycles(2);
    apb_write(ADDR_CU_CTRL, 32'd1);
endtask

task automatic run_suite_FRS_result_fifo_stress;
    logic [31:0] rd;
    int          overflow_before, overflow_after;
    begin
        $display("\n========================================");
        $display("   SUITE FRS: RESULT FIFO STRESS");
        $display("========================================\n");

        // =================================================================
        // FRS01: LOOP_COUNT=48 → 784 push_valid cycles.
        //        RESULT_SKIP=12 → FIFO fills at cycle 268 pre-fix → stall.
        //        Post-fix: FIFO overflows silently, CU runs to completion.
        // =================================================================
        $display("[FRS01] LOOP_COUNT=48 (784 CU cycles) — CU must complete...");
        reset_dut(5);

        // Simple NOP on all PEs — still generates push_valid every cycle
        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);

        apb_write(ADDR_RESULT_SKIP, 32'd12);
        apb_write(ADDR_LOOP_START,  32'd0);
        apb_write(ADDR_LOOP_END,    32'd15);
        apb_write(ADDR_LOOP_COUNT,  32'd48);
        apb_write(ADDR_CU_PC_END,   32'd15);
        frs_start_cu_no_reset();
        frs_cu_wait_done(2000, "FRS01");

        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1])
            pass("FRS01: CU completed LOOP_COUNT=48 without FIFO-induced stall");
        else
            fail("FRS01: CU did not assert done", $sformatf("CU_STATUS=%08h", rd));

        // =================================================================
        // FRS02: RESULT_SKIP × LOOP_COUNT sweep — all must complete.
        //        Tests boundary around FIFO depth: skip=12 loop=16 is safe
        //        (16×16+12=268 exactly fills FIFO); skip=0 loop=16 overflows.
        // =================================================================
        $display("[FRS02] RESULT_SKIP × LOOP_COUNT sweep...");
        begin
            int skip_vals[3];
            int loop_vals[3];
            skip_vals[0] = 0;  skip_vals[1] = 12; skip_vals[2] = 255;
            loop_vals[0] = 0;  loop_vals[1] = 16; loop_vals[2] = 48;

            for (int si = 0; si < 3; si++) begin
                for (int li = 0; li < 3; li++) begin
                    reset_dut(5);
                    config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
                    apb_write(ADDR_RESULT_SKIP, 32'(skip_vals[si]));
                    apb_write(ADDR_LOOP_START,  32'd0);
                    apb_write(ADDR_LOOP_END,    32'd15);
                    apb_write(ADDR_LOOP_COUNT,  32'(loop_vals[li]));
                    apb_write(ADDR_CU_PC_END,   32'd15);
                    frs_start_cu_no_reset();
                    frs_cu_wait_done(4000, $sformatf("FRS02[skip=%0d,loop=%0d]",
                                                      skip_vals[si], loop_vals[li]));
                    apb_read(ADDR_CU_STATUS, rd);
                    if (rd[1])
                        pass($sformatf("FRS02[skip=%0d,loop=%0d]: CU done",
                                        skip_vals[si], loop_vals[li]));
                    else
                        fail($sformatf("FRS02[skip=%0d,loop=%0d]: CU not done",
                                        skip_vals[si], loop_vals[li]),
                             $sformatf("CU_STATUS=%08h", rd));
                end
            end
        end
        // Restore default skip
        apb_write(ADDR_RESULT_SKIP, 32'd12);

        // =================================================================
        // FRS03: LOOP_COUNT=127 (128×16=2048 CU cycles) — deep overflow.
        //        (a) overflow_pulse fires at least once (FIFO data dropped)
        //        (b) CU still completes — this is the regression oracle.
        //        Disable stall observer for this test (intentional overflow).
        // =================================================================
        $display("[FRS03] LOOP_COUNT=127 (2048 CU cycles) — overflow + CU completes...");
        reset_dut(5);

        stall_observer_en = 0;  // suppress false-positive from stall observer
        overflow_before = stall_obs_overflow_total;

        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        apb_write(ADDR_RESULT_SKIP, 32'd12);
        apb_write(ADDR_LOOP_START,  32'd0);
        apb_write(ADDR_LOOP_END,    32'd15);
        apb_write(ADDR_LOOP_COUNT,  32'd127);
        apb_write(ADDR_CU_PC_END,   32'd15);
        frs_start_cu_no_reset();
        // Use long timeout — 2048 cycles + margin; stall observer is off
        frs_cu_wait_done(4000, "FRS03");

        overflow_after = stall_obs_overflow_total;

        apb_read(ADDR_CU_STATUS, rd);
        if (rd[1])
            pass("FRS03a: CU completed with LOOP_COUNT=127 (deep overflow, no stall)");
        else
            fail("FRS03a: CU stuck at LOOP_COUNT=127", $sformatf("CU_STATUS=%08h", rd));

        if (overflow_after > overflow_before)
            pass($sformatf("FRS03b: overflow_pulse fired %0d times (FIFO data dropped as expected)",
                            overflow_after - overflow_before));
        else
            fail("FRS03b: overflow_pulse never fired despite deep loop",
                 $sformatf("overflow_before=%0d after=%0d", overflow_before, overflow_after));

        stall_observer_en = 1;

        // Restore defaults
        apb_write(ADDR_RESULT_SKIP, 32'd12);
        apb_write(ADDR_LOOP_COUNT,  32'd0);

        $display("\n[SUITE FRS COMPLETE] Result FIFO stress tests done.\n");
    end
endtask

`endif
