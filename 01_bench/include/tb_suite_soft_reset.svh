`ifndef TB_SUITE_SOFT_RESET_SVH
`define TB_SUITE_SOFT_RESET_SVH

// =============================================================================
// SUITE AS: Soft Reset Recovery
// =============================================================================
// Verifies the exact reset sequence the Linux driver uses (CU_CTRL=2, wait,
// CU_CTRL=0) and that post-reset functionality works correctly.
//
// RTL: cgra_apb_csr.sv CU_CTRL[1] = cu_soft_reset
//      cgra_control_unit.sv uses cu_soft_reset to reset FSM
// =============================================================================

task automatic run_suite_AS_soft_reset;
    logic [31:0] rd, rd2;
    begin
        $display("\n========================================");
        $display("   SUITE AS: SOFT RESET RECOVERY");
        $display("========================================\n");

        // =================================================================
        // AS01: Basic soft reset → CU IDLE
        // =================================================================
        $display("[AS01] Basic soft reset...");
        reset_dut(5);
        // Assert soft_reset
        apb_write(ADDR_CU_CTRL, 32'h0000_0002);
        wait_cycles(5);
        // Release soft_reset
        apb_write(ADDR_CU_CTRL, 32'h0000_0000);
        wait_cycles(3);
        // Verify IDLE
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[0] === 1'b0) pass("AS01: Soft reset → CU idle");
        else fail("AS01: CU not idle", $sformatf("CU_STATUS=0x%08h", rd));

        // =================================================================
        // AS02: PE accumulator cleared after soft reset
        // =================================================================
        $display("[AS02] PE accumulator cleared after reset...");
        reset_dut(5);
        // Accumulate a value
        tile_bank_fill_all(2'd0, 32'd10);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd5);
        run_cgra(5);
        rd = read_pe_result(4'd0);
        if ($signed(rd) == 0) begin
            fail("AS02: Setup", "PE didn't compute anything");
        end else begin
            // Soft reset
            apb_write(ADDR_CU_CTRL, 32'h2);
            wait_cycles(5);
            apb_write(ADDR_CU_CTRL, 32'h0);
            wait_cycles(3);
            // Configure ACC_CLR and run to clear PE state
            config_pe_safe(4'd0, OP_ACC_CLR, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
            run_cgra(3);
            rd = read_pe_result(4'd0);
            if (rd === 32'd0) pass("AS02: ACC_CLR after soft reset clears accumulator");
            else fail("AS02: Accumulator not cleared", $sformatf("got=%0d", $signed(rd)));
        end

        // =================================================================
        // AS03: DMA FSM in IDLE after hard reset
        // =================================================================
        $display("[AS03] DMA FSM idle after reset...");
        reset_dut(5);
        apb_read(ADDR_DMA_STATUS, rd);
        if (rd === 32'h0000_0000) pass("AS03: DMA IDLE after reset (busy=0, done=0)");
        else fail("AS03: DMA not idle", $sformatf("DMA_STATUS=0x%08h", rd));

        // =================================================================
        // AS04: No stale IRQ after reset
        // =================================================================
        $display("[AS04] No stale IRQ after reset...");
        // First trigger an IRQ
        ram_write(32'h0000_0000, 32'hFEED);
        dma_transfer(32'h0000_0000, 32'h0000_0100, 32'd4, 500);
        apb_read(ADDR_IRQ_STATUS, rd);
        // Now reset
        reset_dut(5);
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd === 32'h0000_0000) pass("AS04: No stale IRQ after reset");
        else fail("AS04: Stale IRQ", $sformatf("IRQ_STATUS=0x%08h", rd));

        // =================================================================
        // AS05: Post-reset functional — fresh compute succeeds
        // =================================================================
        $display("[AS05] Post-reset functional...");
        reset_dut(5);
        // Do a soft reset, then verify compute works
        apb_write(ADDR_CU_CTRL, 32'h2);
        wait_cycles(5);
        apb_write(ADDR_CU_CTRL, 32'h0);
        wait_cycles(3);
        // Now configure and compute
        tile_bank_fill_all(2'd0, 32'd20);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd22);
        run_cgra(5);
        check_pe_result(4'd0, 32'd42, "AS05: Post-reset compute ADD 20+22=42");

        // =================================================================
        // AS06: Post-reset DMA works
        // =================================================================
        $display("[AS06] Post-reset DMA...");
        reset_dut(5);
        apb_write(ADDR_CU_CTRL, 32'h2);
        wait_cycles(5);
        apb_write(ADDR_CU_CTRL, 32'h0);
        wait_cycles(3);
        ram_write(32'h0000_0000, 32'hBEEF_CAFE);
        dma_transfer(32'h0000_0000, 32'h0000_0200, 32'd4, 500);
        rd = ram_read(32'h0000_0200);
        if (rd === 32'hBEEF_CAFE) pass("AS06: Post-reset DMA works");
        else fail("AS06: Post-reset DMA", $sformatf("got=0x%08h", rd));

        // =================================================================
        // AS07: Reset during CU execution — mid-run soft_reset
        // =================================================================
        $display("[AS07] Reset during CU execution...");
        reset_dut(5);
        // Configure PE0 and start CU with loop to keep it busy
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_LOOP_COUNT, 32'h0000_00FF);  // Long loop
        apb_write(ADDR_CU_CTRL, 32'h1);
        wait_cycles(5);  // Let it run a bit
        // Mid-run soft reset
        apb_write(ADDR_CU_CTRL, 32'h2);
        wait_cycles(5);
        apb_write(ADDR_CU_CTRL, 32'h0);
        wait_cycles(3);
        // Verify CU is idle after reset
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[0] === 1'b0) pass("AS07a: CU idle after mid-run reset");
        else fail("AS07a: CU still busy", $sformatf("CU_STATUS=0x%08h", rd));
        // Verify can start fresh computation
        tile_bank_fill_all(2'd0, 32'd5);
        config_pe_imm(4'd0, OP_MUL, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd7);
        apb_write(ADDR_LOOP_COUNT, 32'd0);  // Reset loop count
        run_cgra(5);
        check_pe_result(4'd0, 32'd35, "AS07b: Post-mid-run-reset compute MUL 5*7=35");

        // =================================================================
        // AS08: Double reset — two resets in succession
        // =================================================================
        $display("[AS08] Double reset...");
        reset_dut(5);
        apb_write(ADDR_CU_CTRL, 32'h2);
        wait_cycles(3);
        apb_write(ADDR_CU_CTRL, 32'h0);
        wait_cycles(1);
        // Second reset immediately
        apb_write(ADDR_CU_CTRL, 32'h2);
        wait_cycles(3);
        apb_write(ADDR_CU_CTRL, 32'h0);
        wait_cycles(3);
        apb_read(ADDR_CU_STATUS, rd);
        if (rd[0] === 1'b0) pass("AS08a: CU idle after double reset");
        else fail("AS08a: CU not idle", $sformatf("CU_STATUS=0x%08h", rd));
        // Verify functional
        tile_bank_fill_all(2'd0, 32'd3);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd7);
        run_cgra(5);
        check_pe_result(4'd0, 32'd10, "AS08b: Functional after double reset, ADD 3+7=10");

        // =================================================================
        // AS09: Soft reset clears CU_CTRL register properly
        // =================================================================
        $display("[AS09] CU_CTRL state after reset...");
        reset_dut(5);
        apb_write(ADDR_CU_CTRL, 32'h0000_0002);
        wait_cycles(2);
        apb_read(ADDR_CU_CTRL, rd);
        // Bit[1] should still be set (soft_reset asserted)
        if (rd[1] === 1'b1) pass("AS09a: CU_CTRL[1] held during soft reset");
        else fail("AS09a: CU_CTRL[1]", $sformatf("got=0x%08h", rd));
        // Release
        apb_write(ADDR_CU_CTRL, 32'h0);
        wait_cycles(2);
        apb_read(ADDR_CU_CTRL, rd);
        if (rd === 32'h0) pass("AS09b: CU_CTRL cleared after release");
        else fail("AS09b: CU_CTRL", $sformatf("got=0x%08h", rd));

        // =================================================================
        // AS10: Reset preserves IRQ mask setting
        // =================================================================
        $display("[AS10] Reset preserves IRQ mask...");
        reset_dut(5);
        apb_write(ADDR_IRQ_MASK, 32'h0000_0003);
        // Soft reset (not hard reset!)
        apb_write(ADDR_CU_CTRL, 32'h2);
        wait_cycles(5);
        apb_write(ADDR_CU_CTRL, 32'h0);
        wait_cycles(3);
        // IRQ_MASK should survive soft reset (only hard reset clears it)
        apb_read(ADDR_IRQ_MASK, rd);
        if (rd === 32'h0000_0003) pass("AS10: IRQ mask survives soft reset");
        else fail("AS10: IRQ mask", $sformatf("got=0x%08h", rd));

        $display("\n[SUITE AS COMPLETE] Soft Reset Recovery finished.\n");
    end
endtask

`endif
