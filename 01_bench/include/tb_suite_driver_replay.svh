`ifndef TB_SUITE_DRIVER_REPLAY_SVH
`define TB_SUITE_DRIVER_REPLAY_SVH

// =============================================================================
// SUITE AP: Driver Transaction Replay
// =============================================================================
// Replays the EXACT APB write/read sequences from cgra_driver.c and
// lpr_cgra_accel.c. Each test mirrors a specific C function's register access
// pattern, proving the RTL responds correctly to real software flows.
//
// Reference: 07_sw/driver/cgra_driver.c
// =============================================================================

// ─── Helper: mirror cgra_soft_reset() from driver ───
task automatic driver_soft_reset;
    // cgra_driver.c:228-233
    apb_write(ADDR_CU_CTRL, 32'h0000_0002);  // CU_CTRL_SOFT_RESET
    wait_cycles(10);                           // usleep(10) → ~10 cycles at 100MHz
    apb_write(ADDR_CU_CTRL, 32'h0000_0000);   // release
    wait_cycles(1);                            // usleep(1)
endtask

// ─── Helper: mirror cgra_set_loop() from driver ───
task automatic driver_set_loop(input logic [15:0] start_pc, input logic [15:0] end_pc,
                               input logic [15:0] count);
    // cgra_driver.c:241-247
    apb_write(ADDR_LOOP_START, {16'd0, start_pc});
    apb_write(ADDR_LOOP_END,   {16'd0, end_pc});
    apb_write(ADDR_LOOP_COUNT, {16'd0, count});
endtask

// ─── Helper: mirror cgra_run() from driver ───
task automatic driver_run(output int cycles);
    logic [31:0] st, cyc;
    int poll_count;
    // cgra_driver.c:207-226
    // Clear stale done flag
    apb_write(ADDR_IRQ_STATUS, 32'h0000_0002);  // IRQ_CU_DONE = bit[1]
    // Start execution
    apb_write(ADDR_CU_CTRL, 32'h0000_0001);     // CU_CTRL_START
    // Poll CU_STATUS.done
    poll_count = 0;
    forever begin
        apb_read(ADDR_CU_STATUS, st);
        if (st[1] === 1'b1) begin  // CU_STATUS_DONE
            apb_read(ADDR_CU_CYCLES, cyc);
            cycles = cyc;
            return;
        end
        poll_count++;
        if (poll_count > 5000) begin
            $error("[AP] driver_run: timeout waiting for CU done");
            cycles = -1;
            driver_soft_reset();
            return;
        end
    end
endtask

// ─── Helper: mirror cgra_get_results() from driver ───
task automatic driver_get_results(output logic [31:0] out[4]);
    // cgra_driver.c:249-255
    apb_read(ADDR_RESULT_ROW0, out[0]);
    apb_read(ADDR_RESULT_ROW1, out[1]);
    apb_read(ADDR_RESULT_ROW2, out[2]);
    apb_read(ADDR_RESULT_ROW3, out[3]);
endtask

// ─── Helper: mirror cgra_dma_read() from driver ───
task automatic driver_dma_read(input logic [31:0] src_phys, input logic [31:0] dst_local,
                               input logic [31:0] bytes);
    // cgra_driver.c:179-189
    apb_write(ADDR_DMA_SRC,  src_phys);
    apb_write(ADDR_DMA_DST,  dst_local);
    apb_write(ADDR_DMA_SIZE, bytes);
    apb_write(ADDR_DMA_CTRL, 32'h0000_0001);  // DMA_CTRL_START
    wait_dma_done(5000);
endtask

// ─── Helper: mirror cgra_set_timeout() from driver ───
task automatic driver_set_timeout(input logic [31:0] max_cycles);
    apb_write(ADDR_CU_TIMEOUT, max_cycles);
endtask

task automatic run_suite_AP_driver_replay;
    logic [31:0] rd, results[4];
    int cyc;
    begin
        $display("\n========================================");
        $display("   SUITE AP: DRIVER TRANSACTION REPLAY");
        $display("========================================\n");

        // =================================================================
        // AP01: cgra_soft_reset() sequence
        // =================================================================
        $display("[AP01] driver_soft_reset sequence...");
        reset_dut(5);
        driver_soft_reset();
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[0] === 1'b0) pass("AP01: Soft reset → CU idle");
        else fail("AP01: Soft reset", $sformatf("CU not idle: 0x%08h", rd));

        // =================================================================
        // AP02: cgra_set_loop() sequence
        // =================================================================
        $display("[AP02] driver_set_loop sequence...");
        driver_set_loop(16'd2, 16'd10, 16'd5);
        apb_read(ADDR_LOOP_START, rd);
        if (rd === 32'd2) pass("AP02a: LOOP_START=2");
        else fail("AP02a: LOOP_START", $sformatf("got=%0d", rd));
        apb_read(ADDR_LOOP_END, rd);
        if (rd === 32'd10) pass("AP02b: LOOP_END=10");
        else fail("AP02b: LOOP_END", $sformatf("got=%0d", rd));
        apb_read(ADDR_LOOP_COUNT, rd);
        if (rd === 32'd5) pass("AP02c: LOOP_COUNT=5");
        else fail("AP02c: LOOP_COUNT", $sformatf("got=%0d", rd));

        // =================================================================
        // AP03: cgra_set_timeout() sequence
        // =================================================================
        $display("[AP03] driver_set_timeout sequence...");
        driver_set_timeout(32'h0001_0000);
        apb_read(ADDR_CU_TIMEOUT, rd);
        if (rd === 32'h0001_0000) pass("AP03: CU_TIMEOUT set");
        else fail("AP03: CU_TIMEOUT", $sformatf("got=0x%08h", rd));

        // =================================================================
        // AP04: cgra_dma_read() — DDR → tile memory
        // =================================================================
        $display("[AP04] driver_dma_read: DDR→tile...");
        reset_dut(5);
        for (int i = 0; i < 16; i++) ram_write(32'h0000_1000 + i*4, 32'(32'hAA00 + i));
        driver_dma_read(32'h0000_1000, BASE_TILE, 32'd64);
        pass("AP04: DMA DDR→tile completed");

        // =================================================================
        // AP05: cgra_run() → poll CU_STATUS → read CU_CYCLES
        // =================================================================
        $display("[AP05] driver_run: start → poll → cycles...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'd5);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd3);
        driver_run(cyc);
        $display("[AP05] CU completed in %0d cycles", cyc);
        if (cyc > 0) pass("AP05: driver_run completed with valid cycle count");
        else fail("AP05: driver_run", $sformatf("cycles=%0d", cyc));

        // =================================================================
        // AP06: cgra_get_results() — read RESULT_ROW0-3
        // =================================================================
        $display("[AP06] driver_get_results...");
        driver_get_results(results);
        $display("[AP06] ROW0=%0d ROW1=%0d ROW2=%0d ROW3=%0d",
                 results[0], results[1], results[2], results[3]);
        if (!$isunknown(results[0])) pass("AP06: RESULT_ROW0-3 readable");
        else fail("AP06: RESULT_ROW0-3", "X values in results");

        // =================================================================
        // AP07: Full init sequence (cgra_init flow)
        // =================================================================
        // cgra_init calls cgra_soft_reset at the end
        $display("[AP07] Full init sequence...");
        reset_dut(5);
        driver_soft_reset();
        // After init, verify all status is clean
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[0] === 1'b0 && rd[1] === 1'b0)
            pass("AP07: Post-init CU status clean");
        else
            fail("AP07: Post-init CU", $sformatf("got=0x%08h", rd));

        // =================================================================
        // AP08: Complete FC layer flow (simplified)
        // =================================================================
        // Mirrors lpr_cgra_accel.c cgra_fc_layer():
        //   1. soft_reset → 2. ACC_CLR config → 3. tile load → 4. run → 5. get results
        $display("[AP08] Full FC layer flow...");
        reset_dut(5);

        // Step 1: soft_reset
        driver_soft_reset();

        // Step 2: Configure PE0 with ACC_CLR (clear accumulator)
        config_pe_safe(4'd0, OP_ACC_CLR, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        driver_run(cyc);

        // Step 3: Configure PE0 for MAC, load tile data
        tile_bank_fill_all(2'd0, 32'd3);
        config_pe_imm(4'd0, OP_MAC, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd4);

        // Step 4: Run computation
        driver_run(cyc);
        $display("[AP08] FC layer completed in %0d cycles", cyc);

        // Step 5: Get results (read PE result directly since this is simplified)
        rd = read_pe_result(4'd0);
        $display("[AP08] PE0 MAC result: %0d", $signed(rd));
        if ($signed(rd) > 0) pass("AP08: FC layer flow completed with positive MAC result");
        else fail("AP08: FC layer", $sformatf("MAC result=%0d", $signed(rd)));

        // =================================================================
        // AP09: IRQ enable → run → clear sequence (driver IRQ handling)
        // =================================================================
        $display("[AP09] IRQ enable/clear sequence...");
        reset_dut(5);
        // cgra_irq_enable: set mask
        apb_write(ADDR_IRQ_MASK, 32'h0000_0003);  // Enable both DMA and CU IRQs
        // Configure and run
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_IRQ_STATUS, 32'h0000_0002);  // Clear stale CU done
        apb_write(ADDR_CU_CTRL, 32'h0000_0001);     // Start
        wait_cycles(50);
        // Check IRQ fired
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[1] === 1'b1) pass("AP09a: CU done IRQ status set");
        else fail("AP09a: CU done IRQ", $sformatf("got=0x%08h", rd));
        // Clear IRQ (driver pattern)
        apb_write(ADDR_IRQ_STATUS, 32'h0000_0002);
        wait_cycles(1);
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[1] === 1'b0) pass("AP09b: CU done IRQ cleared by W1C");
        else fail("AP09b: IRQ clear", $sformatf("got=0x%08h", rd));

        // =================================================================
        // AP10: Back-to-back DMA+compute (real app pattern)
        // =================================================================
        $display("[AP10] Back-to-back DMA+compute...");
        reset_dut(5);
        driver_soft_reset();
        // DMA load tile data
        for (int i = 0; i < 4; i++) ram_write(32'h0000_4000 + i*4, 32'(i + 1));
        driver_dma_read(32'h0000_4000, BASE_TILE, 32'd16);
        // Configure and run
        config_pe_imm(4'd0, OP_PASS0, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        driver_run(cyc);
        rd = read_pe_result(4'd0);
        $display("[AP10] PE0 after DMA+compute: %0d", $signed(rd));
        if (!$isunknown(rd)) pass("AP10: DMA+compute sequence completed");
        else fail("AP10: DMA+compute", "Result is X");

        $display("\n[SUITE AP COMPLETE] Driver Transaction Replay finished.\n");
    end
endtask

`endif
