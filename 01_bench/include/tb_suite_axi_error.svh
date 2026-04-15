`ifndef TB_SUITE_AXI_ERROR_SVH
`define TB_SUITE_AXI_ERROR_SVH

// =============================================================================
// SUITE AH: AXI Error Handling Verification
// =============================================================================
// Validates DMA error detection and recovery for AXI BRESP/RRESP errors.
// Note: Current top-level ties BRESP/RRESP to OKAY, so error injection
// requires whitebox access to the DMA engine's error capture logic.
// These tests verify the error path infrastructure is correctly wired.
// =============================================================================

task automatic run_suite_AH_axi_error;
    logic [31:0] status, rd;
    begin
        $display("\n========================================");
        $display("   SUITE AH: AXI ERROR HANDLING");
        $display("========================================\n");

        reset_dut(5);

        // =================================================================
        // AH01: Normal DMA with OKAY response (baseline)
        // =================================================================
        $display("[AH01] Normal DMA transfer (BRESP=OKAY)...");
        ram_write(32'h1000, 32'hA5A5_A5A5);
        ram_write(32'h1004, 32'h5A5A_5A5A);
        dma_transfer(32'h1000, 32'h10000000, 8, 100);
        apb_read(ADDR_DMA_STATUS, status);
        if (status[1]) pass("AH01: DMA done with OKAY response");
        else fail("AH01: DMA not done", "status bit[1] not set");

        // =================================================================
        // AH02: Verify DMA error flag is clear after normal transfer
        // =================================================================
        $display("[AH02] Error flag clear after normal transfer...");
        // Read the error status from the DMA engine via whitebox
        rd = tb_top.u_dut.u_dma.u_engine.error_flag;
        if (rd == 1'b0) pass("AH02: error_flag clear after OK transfer");
        else fail("AH02: error_flag unexpectedly set", "should be 0 after OKAY");

        // =================================================================
        // AH03: Verify error_code register is zero
        // =================================================================
        $display("[AH03] Error code zero after normal transfer...");
        rd = {30'd0, tb_top.u_dut.u_dma.u_engine.error_code_reg};
        if (rd == 32'd0) pass("AH03: error_code=0 after OK transfer");
        else fail("AH03: error_code non-zero", $sformatf("got 0x%08h", rd));

        // =================================================================
        // AH04: Inject SLVERR via whitebox and verify capture
        // =================================================================
        $display("[AH04] SLVERR injection test...");
        // Force the bresp_error combinational signal high for 1 cycle
        // This simulates an AXI slave returning SLVERR
        force tb_top.u_dut.u_dma.u_engine.bresp_error = 1'b1;
        force tb_top.u_dut.u_dma.u_engine.m_axi_bresp = 2'b10;  // SLVERR
        @(posedge clk);
        @(posedge clk);
        release tb_top.u_dut.u_dma.u_engine.bresp_error;
        release tb_top.u_dut.u_dma.u_engine.m_axi_bresp;
        @(posedge clk);

        rd = {30'd0, tb_top.u_dut.u_dma.u_engine.error_code_reg};
        if (rd == 32'd2) pass("AH04: SLVERR captured in error_code_reg");
        else fail("AH04: error_code_reg wrong", $sformatf("expected 2, got %0d", rd));

        // =================================================================
        // AH05: Error flag is sticky (persists)
        // =================================================================
        $display("[AH05] Error flag sticky...");
        @(posedge clk); @(posedge clk); @(posedge clk);
        rd = tb_top.u_dut.u_dma.u_engine.error_flag;
        if (rd == 1'b1) pass("AH05: error_flag sticky after injection");
        else fail("AH05: error_flag not sticky", "should persist");

        // =================================================================
        // AH06: Error cleared on new cfg_start
        // =================================================================
        $display("[AH06] Error cleared on new DMA start...");
        ram_write(32'h2000, 32'h1234_5678);
        dma_transfer(32'h2000, 32'h10000000, 4, 100);
        rd = tb_top.u_dut.u_dma.u_engine.error_flag;
        if (rd == 1'b0) pass("AH06: error_flag cleared after new transfer");
        else fail("AH06: error_flag not cleared", "cfg_start should clear error");

        // =================================================================
        // AH07: DMA recovery after error (next transfer succeeds)
        // =================================================================
        $display("[AH07] DMA recovery after error...");
        ram_write(32'h3000, 32'hBEEF_CAFE);
        dma_transfer(32'h3000, 32'h10000000, 4, 100);
        apb_read(ADDR_DMA_STATUS, status);
        if (status[1]) pass("AH07: DMA recovers after error");
        else fail("AH07: DMA stuck after error", "recovery failed");

        // =================================================================
        // AH08: DECERR injection
        // =================================================================
        $display("[AH08] DECERR injection test...");
        force tb_top.u_dut.u_dma.u_engine.bresp_error = 1'b1;
        force tb_top.u_dut.u_dma.u_engine.m_axi_bresp = 2'b11;  // DECERR
        @(posedge clk);
        @(posedge clk);
        release tb_top.u_dut.u_dma.u_engine.bresp_error;
        release tb_top.u_dut.u_dma.u_engine.m_axi_bresp;
        @(posedge clk);

        rd = {30'd0, tb_top.u_dut.u_dma.u_engine.error_code_reg};
        if (rd == 32'd3) pass("AH08: DECERR captured (code=3)");
        else fail("AH08: error_code_reg wrong", $sformatf("expected 3, got %0d", rd));

        // =================================================================
        // AH09: DMA_ERROR CSR readback (APB 0x38)
        // =================================================================
        $display("[AH09] DMA_ERROR CSR readback...");
        // DECERR is still latched from AH08
        apb_read(ADDR_DMA_ERROR, rd);
        if (rd[0] == 1'b1 && rd[2:1] == 2'b11)
            pass("AH09: DMA_ERROR CSR shows flag=1, code=DECERR(3)");
        else
            fail("AH09: DMA_ERROR CSR wrong", $sformatf("expected 0x7, got 0x%08h", rd));

        // =================================================================
        // AH10: IRQ_STATUS[2] reflects DMA error
        // =================================================================
        $display("[AH10] IRQ_STATUS[2] DMA error bit...");
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[2] == 1'b1)
            pass("AH10: IRQ_STATUS[2] set on DMA error");
        else
            fail("AH10: IRQ_STATUS[2] not set", $sformatf("got 0x%08h", rd));

        // =================================================================
        // AH11: W1C clears IRQ_STATUS[2] (DMA error bit only)
        // =================================================================
        $display("[AH11] W1C clear IRQ_STATUS[2]...");
        apb_write(ADDR_IRQ_STATUS, 32'h4);  // W1C bit [2] only
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[2] == 1'b0)
            pass("AH11: IRQ_STATUS[2] cleared by W1C");
        else
            fail("AH11: IRQ_STATUS[2] not cleared", $sformatf("got 0x%08h", rd));

        // =================================================================
        // AH12: DMA_ERROR cleared on new DMA start
        // =================================================================
        $display("[AH12] DMA_ERROR cleared on new transfer...");
        ram_write(32'h1000, 32'hDEAD_BEEF);
        dma_transfer(32'h1000, 32'h10000000, 4, 100);
        apb_read(ADDR_DMA_ERROR, rd);
        if (rd == 32'd0)
            pass("AH12: DMA_ERROR cleared after new transfer");
        else
            fail("AH12: DMA_ERROR not cleared", $sformatf("got 0x%08h", rd));

        $display("\n[SUITE AH COMPLETE] AXI Error handling verification finished.\n");
    end
endtask

`endif
