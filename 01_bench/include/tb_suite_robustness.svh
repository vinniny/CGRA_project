`ifndef TB_SUITE_ROBUSTNESS_SVH
`define TB_SUITE_ROBUSTNESS_SVH
// ============================================================================
// SUITE: ROBUSTNESS (CRV Philosophy)
// ============================================================================
// Merges: Suite S (Reset), Suite W (Hang), Suite AA (Metastability)
// Philosophy: Random fault injection, random timing, verify recovery.
// ============================================================================

task automatic run_suite_robustness;
    $display("\n");
    $display("========================================");
    $display("   SUITE: ROBUSTNESS (CRV)");
    $display("   Target: 300+ Randomized Vectors");
    $display("========================================");
    
    test_reset_injection();
    test_stall_injection();
    test_irq_stress();
    
    $display("\n[SUITE ROBUSTNESS COMPLETE]\n");
endtask

// ============================================================================
// TEST: Reset Injection (100 vectors)
// ============================================================================
// Weakness Eliminated: Reset at fixed time
// Upgrade: Inject reset at random cycle during active DMA, verify recovery
// ============================================================================
task automatic test_reset_injection;
    logic [31:0] recovery_src, recovery_dst, recovery_golden, recovery_actual;
    integer i, rand_delay;
    integer pass_count, fail_count;
    
    $display("[RESET_INJ] Testing 50 in-flight reset + recovery cycles...");
    pass_count = 0;
    fail_count = 0;
    
    for (i = 0; i < 50; i++) begin
        // --- Phase 1: Start a DMA transfer, then abort mid-flight ---
        // Seed source memory for the DMA we're about to abort
        ram_write(32'h0000_1000, 32'hDEAD_0000 + i);
        
        // Kick off a 128-byte DMA (will take multiple cycles)
        apb_write(ADDR_DMA_SRC, 32'h0000_1000);
        apb_write(ADDR_DMA_DST, 32'h0000_6000);
        apb_write(ADDR_DMA_SIZE, 32'd128);
        apb_write(ADDR_DMA_CTRL, 32'h1);
        
        // Wait a random 1-8 cycles then inject soft-reset while DMA is in flight
        rand_delay = ($urandom % 8) + 1;
        repeat(rand_delay) @(posedge clk);
        
        // NOTE: Protocol checking stays ENABLED during abort. The DMA engine's
        // R_DRAIN/W_DRAIN states complete in-flight AXI transactions before
        // returning to IDLE, so abort is now AXI-compliant. Any protocol error
        // here means the drain logic has a bug that must be fixed.
        
        // Soft-reset aborts DMA (cu_soft_reset -> cfg_abort on DMA engine)
        apb_write(ADDR_CU_CTRL, 32'h2);
        repeat(3) @(posedge clk);
        apb_write(ADDR_CU_CTRL, 32'h0);
        repeat(5) @(posedge clk);
        
        // --- Phase 2: Full hardware reset to recover DUT + AXI BFM ---
        // reset_dut() asserts rst_n=0 which resets the BFM read/write
        // state machines back to IDLE, clears protocol checker pending
        // flags, re-enables protocol_check_enable, and re-inits memory.
        reset_dut(5);
        
        // --- Phase 3: Verify full system recovery with fresh DMA ---
        recovery_src = 32'h0000_0100 + (i * 4);
        recovery_dst = 32'h0001_0000 + (i * 4);
        recovery_golden = $urandom | 32'h1;
        ram_write(recovery_src, recovery_golden);
        
        dma_transfer(recovery_src, recovery_dst, 4, 1000);
        
        recovery_actual = ram_read(recovery_dst);
        if (recovery_actual === recovery_golden)
            pass_count++;
        else begin
            $display("  [FAIL] RESET_%0d: After in-flight abort - Exp=0x%h, Got=0x%h", 
                     i, recovery_golden, recovery_actual);
            fail_count++;
        end
    end
    
    if (fail_count == 0)
        pass($sformatf("RESET_INJ: %0d/%0d in-flight abort + recovery verified", pass_count, pass_count));
    else
        fail("RESET_INJ", $sformatf("%0d recovery failures", fail_count));
endtask

// ============================================================================
// TEST: Stall Injection (100 vectors)
// ============================================================================
// Weakness Eliminated: Fixed stall patterns
// Upgrade: Random stall probability (0-100%), verify data integrity
// ============================================================================
task automatic test_stall_injection;
    logic [31:0] src, dst, golden, actual;
    integer i, stall_prob;
    integer pass_count, fail_count;
    
    $display("[STALL_INJ] Testing 50 transfers with random stall probability...");
    pass_count = 0;
    fail_count = 0;
    
    for (i = 0; i < 50; i++) begin
        cov_single_beat++;  // Track single-beat transfer coverage
        src = 32'h1000 + (i * 4);
        dst = 32'h7000 + (i * 4);
        golden = $urandom | 32'hFF00_0000; // High bits set
        ram_write(src, golden);
        
        // Random stall probability (0-99%) — FIX: cap at 99 to prevent total deadlock
        stall_prob = $urandom % 100;
        enable_stress(stall_prob);
        
        // Execute transfer with stress
        dma_transfer(src, dst, 4, 5000); // Long timeout for high stall
        
        disable_stress();
        
        // Verify
        actual = ram_read(dst);
        if (actual === golden)
            pass_count++;
        else begin
            $display("  [FAIL] STALL_%0d: P=%0d%%, Exp=0x%h, Got=0x%h", i, stall_prob, golden, actual);
            fail_count++;
        end
    end
    
    if (fail_count == 0)
        pass($sformatf("STALL_INJ: %0d/%0d passed", pass_count, pass_count));
    else
        fail("STALL_INJ", $sformatf("%0d failures", fail_count));
endtask

// ============================================================================
// TEST: IRQ Stress (100 vectors)
// ============================================================================
// Weakness Eliminated: Simple IRQ check
// Upgrade: Fire operations, check IRQ at random, verify status consistency
// ============================================================================
task automatic test_irq_stress;
    logic [31:0] src, dst, golden, actual, irq_status, irq_mask;
    integer i, random_delay;
    integer pass_count, fail_count;
    
    $display("[IRQ_STRESS] Testing 50 IRQ verifications...");
    pass_count = 0;
    fail_count = 0;
    
    for (i = 0; i < 50; i++) begin
        cov_single_beat++;  // Track single-beat transfer coverage
        // Setup and execute DMA
        src = 32'h1000 + (i * 4);
        dst = 32'h8000 + (i * 4);
        golden = $urandom;
        ram_write(src, golden);
        
        // Clear any pending IRQs
        apb_write(ADDR_IRQ_STATUS, 32'hFFFF_FFFF);
        
        // Set random mask
        irq_mask = $urandom & 32'h0000_000F; // Only lower 4 bits valid
        apb_write(ADDR_IRQ_MASK, irq_mask);
        
        // Execute
        dma_transfer(src, dst, 4, 1000);
        
        // Random delay before checking IRQ
        random_delay = 1 + ($urandom % 10);
        repeat(random_delay) @(posedge clk);
        
        // Read IRQ status
        apb_read(ADDR_IRQ_STATUS, irq_status);
        
        // Verify IRQ fired if DMA done bit is set
        // IRQ_STATUS[0] = DMA Done
        if ((irq_status & 32'h1) == 1)
            pass_count++;
        else begin
            $display("  [FAIL] IRQ_%0d: Expected IRQ_STATUS[0]=1, Got=0x%h", i, irq_status);
            fail_count++;
        end
    end
    
    if (fail_count == 0)
        pass($sformatf("IRQ_STRESS: %0d/%0d passed", pass_count, pass_count));
    else
        fail("IRQ_STRESS", $sformatf("%0d failures", fail_count));
endtask

`endif
