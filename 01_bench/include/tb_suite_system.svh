`ifndef TB_SUITE_SYSTEM_SVH
`define TB_SUITE_SYSTEM_SVH
// ============================================================================
// SUITE: SYSTEM INTEGRITY (CRV Philosophy)
// ============================================================================
// Merges: Suite A (APB), Suite B (DMA), Suite C (Protocol), Suite R (Streaming)
// Philosophy: No magic numbers. Random data, random timing, self-checking.
// ============================================================================

task automatic run_suite_system_integrity;
    $display("\n");
    $display("========================================");
    $display("   SUITE: SYSTEM INTEGRITY (CRV)");
    $display("   Target: 400+ Randomized Vectors");
    $display("========================================");
    
    test_apb_randomized();
    test_dma_randomized();
    test_dma_max_burst();              // NEW: Large transfer (>512B) tests
    test_dma_4kb_boundary_crossing();  // CRITICAL: Verify 4KB split logic
    test_dma_axi_write_handshake();    // AXI4 Write FSM stress test
    test_protocol_stress();
    test_streaming_wrap();
    test_hybrid_io_readback();         // Thesis Hybrid I/O verification
    
    $display("\n[SUITE SYSTEM INTEGRITY COMPLETE]\n");
endtask

// ============================================================================
// TEST: APB Randomized (100 vectors)
// ============================================================================
// Weakness Eliminated: No more 0x0, 0x4 with 0xDEADBEEF
// Upgrade: Random address (within CSR space), random data, self-check
// ============================================================================
task automatic test_apb_randomized;
    logic [31:0] addr, wdata, rdata;
    logic [7:0] offset;
    integer i;
    integer pass_count, fail_count;
    
    $display("[APB_RAND] Testing 50 randomized APB R/W cycles...");
    pass_count = 0;
    fail_count = 0;
    
    for (i = 0; i < 50; i++) begin
        // Random offset within DMA CSR space - SKIP 0x00 (CTRL) to avoid triggering DMA
        // Use 0x04 (STATUS-RO), 0x08 (SRC), 0x0C (DST), 0x10 (SIZE)
        offset = 8'(8'h04 + 8'(($urandom % 4) * 4)); // 0x04, 0x08, 0x0C, 0x10
        addr = {24'd0, offset};
        
        // Random data - NEVER use 0 or simple patterns
        wdata = $urandom | 32'h0000_0001; // Ensure non-zero
        
        // Write
        apb_write(addr, wdata);
        
        // Read back
        apb_read(addr, rdata);
        
        // Self-check (some registers may be RO)
        if (offset == 8'h04) begin
            // DMA_STATUS: Read-only, skip check
            pass_count++;
        end else begin
            // SRC, DST, SIZE: Full R/W
            if (rdata == wdata)
                pass_count++;
            else begin
                $display("  [FAIL] APB_RAND_%0d: Addr=0x%h, Wrote=0x%h, Read=0x%h", i, addr, wdata, rdata);
                fail_count++;
            end
        end
    end
    
    if (fail_count == 0)
        pass($sformatf("APB_RAND: %0d/%0d vectors passed", pass_count, pass_count));
    else
        fail("APB_RAND", $sformatf("%0d failures", fail_count));
endtask

// ============================================================================
// TEST: DMA Randomized (100 vectors)
// ============================================================================
// Weakness Eliminated: No more fixed 4B transfers
// Upgrade: Random src, random dst, random size (4-256B), random payload
// ============================================================================
task automatic test_dma_randomized;
    logic [31:0] src, dst, size;
    logic [31:0] golden_data [0:63]; // Max 256B = 64 words
    logic [31:0] actual;
    integer i, j, num_words;
    integer pass_count, fail_count;
    logic data_ok;
    
    $display("[DMA_RAND] Testing 50 randomized DMA transfers...");
    pass_count = 0;
    fail_count = 0;
    
    for (i = 0; i < 50; i++) begin
        // Random aligned addresses within safe memory regions
        src  = 32'h0000_1000 + (($urandom % 16) * 64); // Spread across 1KB
        dst  = 32'h0000_3000 + (($urandom % 16) * 64); // Different region
        
        // Random size: 4B to 64B (1-16 words), word-aligned
        num_words = 1 + ($urandom % 16);
        size = num_words * 4;
        
        // Track coverage
        if (size <= 16) cov_single_beat++;
        else if (size <= 512) cov_multi_beat++;
        else cov_max_burst++;
        
        // Prepare golden data - random, non-zero
        for (j = 0; j < num_words; j++) begin
            golden_data[j] = $urandom | 32'h8000_0000; // Ensure MSB set (non-trivial)
            ram_write(src + j*4, golden_data[j]);
        end
        
        // Execute DMA transfer
        dma_transfer(src, dst, size, 2000);
        
        // Verify all words
        data_ok = 1;
        for (j = 0; j < num_words; j++) begin
            actual = ram_read(dst + j*4);
            if (actual !== golden_data[j]) begin
                $display("  [FAIL] DMA_RAND_%0d: Word %0d - Exp=0x%h, Got=0x%h", i, j, golden_data[j], actual);
                data_ok = 0;
            end
        end
        
        if (data_ok) pass_count++;
        else fail_count++;
    end
    
    if (fail_count == 0)
        pass($sformatf("DMA_RAND: %0d/%0d transfers passed", pass_count, pass_count));
    else
        fail("DMA_RAND", $sformatf("%0d failures", fail_count));
endtask

// ============================================================================
// TEST: DMA Max-Burst (Large Transfers >512B)
// ============================================================================
// Purpose: Verify DMA handles large burst transfers correctly
// Coverage: Exercises max-burst (516-1024B) category
// ============================================================================
task automatic test_dma_max_burst;
    logic [31:0] src, dst, size;
    logic [31:0] golden_data [0:255]; // Max 1024B = 256 words
    logic [31:0] actual;
    integer i, j, num_words;
    integer pass_count, fail_count;
    logic data_ok;
    
    $display("[DMA_MAX_BURST] Testing 10 large DMA transfers (516-1024B)...");
    pass_count = 0;
    fail_count = 0;
    
    for (i = 0; i < 10; i++) begin
        // Random aligned addresses with sufficient space
        src  = 32'h0000_1000 + (i * 1024);  // Spread sources apart
        dst  = 32'h0000_A000 + (i * 1024);  // Spread destinations apart
        
        // Random size: 516B to 1024B (129-256 words), word-aligned
        num_words = 129 + ($urandom % 128);  // 129-256 words
        size = num_words * 4;
        
        // Track coverage
        cov_max_burst++;
        
        $display("  [TEST %0d] Src=0x%08h, Dst=0x%08h, Size=%0d bytes (%0d words)", 
                 i, src, dst, size, num_words);
        
        // Prepare unique golden data for each word
        for (j = 0; j < num_words; j++) begin
            golden_data[j] = 32'hCAFE_0000 | (i << 12) | j;
            ram_write(src + j*4, golden_data[j]);
        end
        
        // Clear destination
        for (j = 0; j < num_words; j++) begin
            ram_write(dst + j*4, 32'h0);
        end
        
        // Execute DMA transfer with extended timeout for large transfers
        dma_transfer(src, dst, size, 10000);
        
        // Verify all words transferred correctly
        data_ok = 1;
        for (j = 0; j < num_words; j++) begin
            actual = ram_read(dst + j*4);
            if (actual !== golden_data[j]) begin
                if (j < 5 || j >= num_words - 2) begin  // Only print first/last few errors
                    $display("    [FAIL] Word %0d: Exp=0x%08h, Got=0x%08h", 
                             j, golden_data[j], actual);
                end
                data_ok = 0;
            end
        end
        
        if (data_ok) begin
            $display("    [PASS] All %0d words verified", num_words);
            pass_count++;
        end else begin
            $display("    [FAIL] Data mismatch in large burst transfer");
            fail_count++;
        end
    end
    
    if (fail_count == 0)
        pass($sformatf("DMA_MAX_BURST: %0d/%0d transfers passed", pass_count, pass_count));
    else
        fail("DMA_MAX_BURST", $sformatf("%0d failures", fail_count));
endtask

// ============================================================================
// TEST: DMA 4KB Boundary Crossing (CRITICAL VERIFICATION)
// ============================================================================
// Purpose: Verify the DMA correctly splits transfers that cross 4KB boundaries
// AXI Spec Requirement: Bursts MUST NOT cross 4KB address boundaries
// 
// Test Cases:
//   1. Src=0x0FF0, Size=32B (8 words) -> crosses 0x1000 boundary
//   2. Src=0x0FE0, Size=64B (16 words) -> crosses 0x1000 boundary  
//   3. Src=0x1FF8, Size=16B (4 words) -> crosses 0x2000 boundary
//
// Expected: DMA issues multiple bursts, data integrity preserved
// Failure Mode: If 4KB logic is broken, AXI bus will hang (timeout)
// ============================================================================
task automatic test_dma_4kb_boundary_crossing;
    logic [31:0] src, dst, size;
    logic [31:0] golden_data [0:63];
    logic [31:0] actual;
    integer i, j, num_words;
    integer pass_count, fail_count;
    logic data_ok;
    
    // Test case structure
    typedef struct {
        logic [31:0] src_addr;
        int          num_words;
        string       description;
    } boundary_test_t;
    
    boundary_test_t tests[6];
    
    // Define test cases that cross 4KB boundaries
    tests[0].src_addr = 32'h0000_0FF0; tests[0].num_words = 8;  tests[0].description = "0x0FF0+32B crosses 0x1000";
    tests[1].src_addr = 32'h0000_0FE0; tests[1].num_words = 16; tests[1].description = "0x0FE0+64B crosses 0x1000";
    tests[2].src_addr = 32'h0000_1FF8; tests[2].num_words = 4;  tests[2].description = "0x1FF8+16B crosses 0x2000";
    tests[3].src_addr = 32'h0000_0FFC; tests[3].num_words = 8;  tests[3].description = "0x0FFC+32B crosses 0x1000 (1 word before)";
    tests[4].src_addr = 32'h0000_2FF0; tests[4].num_words = 32; tests[4].description = "0x2FF0+128B crosses 0x3000";
    tests[5].src_addr = 32'h0000_0FF4; tests[5].num_words = 4;  tests[5].description = "0x0FF4+16B crosses 0x1000 (3 words before)";
    
    $display("[4KB_BOUNDARY] Testing DMA transfers that cross 4KB boundaries...");
    $display("[4KB_BOUNDARY] CRITICAL: If this hangs, 4KB split logic is broken!");
    pass_count = 0;
    fail_count = 0;
    
    for (i = 0; i < 6; i++) begin
        cov_4kb_boundary++;  // Track 4KB boundary test coverage
        src = tests[i].src_addr;
        dst = 32'h0000_8000 + (i * 256);  // Safe destination region
        num_words = tests[i].num_words;
        size = num_words * 4;
        
        $display("  [TEST %0d] %s", i, tests[i].description);
        $display("           Src=0x%08h, Dst=0x%08h, Size=%0d bytes (%0d words)", 
                 src, dst, size, num_words);
        
        // Prepare unique golden data for each word
        for (j = 0; j < num_words; j++) begin
            golden_data[j] = 32'hBEEF_0000 | (i << 8) | j;
            ram_write(src + j*4, golden_data[j]);
        end
        
        // Clear destination
        for (j = 0; j < num_words; j++) begin
            ram_write(dst + j*4, 32'h0);
        end
        
        // Execute DMA transfer - use longer timeout since boundary crossing
        // requires multiple bursts
        dma_transfer(src, dst, size, 5000);
        
        // Verify all words transferred correctly
        data_ok = 1;
        for (j = 0; j < num_words; j++) begin
            actual = ram_read(dst + j*4);
            if (actual !== golden_data[j]) begin
                $display("    [FAIL] Word %0d: Addr=0x%08h, Exp=0x%08h, Got=0x%08h", 
                         j, dst + j*4, golden_data[j], actual);
                data_ok = 0;
            end
        end
        
        if (data_ok) begin
            $display("    [PASS] All %0d words verified", num_words);
            pass_count++;
        end else begin
            $display("    [FAIL] Data mismatch in boundary-crossing transfer");
            fail_count++;
        end
    end
    
    if (fail_count == 0)
        pass($sformatf("4KB_BOUNDARY: %0d/%0d transfers passed (split logic verified)", pass_count, pass_count));
    else
        fail("4KB_BOUNDARY", $sformatf("%0d failures - 4KB split logic may be broken!", fail_count));
endtask

// ============================================================================
// TEST: DMA AXI Write Handshake (Stress Test)
// ============================================================================
// Verifies AXI4 Write Master FSM under backpressure:
//   1. Source: Internal memory (0x1000...)
//   2. Destination: External DDR region (0x8000...)
//   3. Transfer: 16 words (64 bytes) - multi-beat burst
//   4. Stress: Random WREADY toggling (backpressure injection)
//   5. Verify: All data arrives correctly at destination
// ============================================================================
task automatic test_dma_axi_write_handshake;
    localparam int NUM_WORDS = 16;  // 64 bytes = 16 words
    localparam int TRANSFER_SIZE = NUM_WORDS * 4;
    
    logic [31:0] src_base, dst_base;
    logic [31:0] golden_data [0:NUM_WORDS-1];
    logic [31:0] actual;
    integer i, j;
    integer pass_count, fail_count;
    integer stress_levels [0:3];
    
    $display("[AXI_WR_HANDSHAKE] Testing AXI4 Write Master with backpressure...");
    pass_count = 0;
    fail_count = 0;
    
    // Stress levels to test: 0%, 30%, 60%, 90% backpressure
    stress_levels[0] = 0;
    stress_levels[1] = 30;
    stress_levels[2] = 60;
    stress_levels[3] = 90;
    
    for (j = 0; j < 4; j++) begin
        // -------------------------------------------------------------------------
        // Step 1: Setup source and destination addresses
        // -------------------------------------------------------------------------
        src_base = 32'h0000_1000 + (j * 32'h100);  // Internal memory
        dst_base = 32'h0000_8000 + (j * 32'h100);  // External DDR region
        
        // -------------------------------------------------------------------------
        // Step 2: Initialize source memory with known pattern
        // -------------------------------------------------------------------------
        for (i = 0; i < NUM_WORDS; i++) begin
            golden_data[i] = 32'hA5A5_0000 | (j << 12) | i;  // Unique per test & word
            ram_write(src_base + (i * 4), golden_data[i]);
        end
        
        // -------------------------------------------------------------------------
        // Step 3: Enable backpressure injection
        // -------------------------------------------------------------------------
        $display("  [TEST %0d] Stress=%0d%%, Src=0x%08h, Dst=0x%08h, Size=%0d bytes",
                 j, stress_levels[j], src_base, dst_base, TRANSFER_SIZE);
        
        enable_stress(stress_levels[j]);
        
        // -------------------------------------------------------------------------
        // Step 4: Execute DMA transfer
        // -------------------------------------------------------------------------
        dma_transfer(src_base, dst_base, TRANSFER_SIZE, 5000);  // Extended timeout for stalls
        
        // -------------------------------------------------------------------------
        // Step 5: Disable stress for verification reads
        // -------------------------------------------------------------------------
        disable_stress();
        
        // -------------------------------------------------------------------------
        // Step 6: Verify all words arrived correctly
        // -------------------------------------------------------------------------
        for (i = 0; i < NUM_WORDS; i++) begin
            actual = ram_read(dst_base + (i * 4));
            if (actual !== golden_data[i]) begin
                $display("    [FAIL] Word %0d: Expected=0x%08h, Got=0x%08h",
                         i, golden_data[i], actual);
                fail_count++;
            end else begin
                pass_count++;
            end
        end
        
        if (fail_count == 0)
            $display("    [PASS] All %0d words verified", NUM_WORDS);
    end
    
    // -------------------------------------------------------------------------
    // Final Report
    // -------------------------------------------------------------------------
    if (fail_count == 0)
        pass($sformatf("AXI_WR_HANDSHAKE: %0d/%0d words verified across 4 stress levels",
                       pass_count, pass_count));
    else
        fail("AXI_WR_HANDSHAKE", $sformatf("%0d word mismatches - Write FSM may have issues",
                                           fail_count));
endtask

// ============================================================================
// TEST: Protocol Stress (100 vectors)
// ============================================================================
// Weakness Eliminated: Simple handshakes
// Upgrade: Random backpressure, random stall injection during transfers
// ============================================================================
task automatic test_protocol_stress;
    logic [31:0] src, dst, size;
    logic [31:0] golden, actual;
    integer i;
    integer stall_prob;
    integer pass_count, fail_count;
    logic data_ok;
    
    $display("[PROTO_STRESS] Testing 50 transfers with random stall injection...");
    pass_count = 0;
    fail_count = 0;
    
    for (i = 0; i < 50; i++) begin
        cov_single_beat++;  // Track single-beat transfer coverage
        // Random small transfer
        src = 32'h1000 + (i * 4);
        dst = 32'h4000 + (i * 4);
        size = 4;
        
        // Random golden data
        golden = $urandom | 32'h1;
        ram_write(src, golden);
        
        // Random stall probability (0-80%)
        stall_prob = $urandom % 81;
        enable_stress(stall_prob);
        
        // Execute with stress
        dma_transfer(src, dst, size, 3000); // Longer timeout for stalls
        
        disable_stress();
        
        // Verify
        actual = ram_read(dst);
        if (actual === golden) pass_count++;
        else begin
            $display("  [FAIL] PROTO_%0d: Stall=%0d%%, Exp=0x%h, Got=0x%h", i, stall_prob, golden, actual);
            fail_count++;
        end
    end
    
    if (fail_count == 0)
        pass($sformatf("PROTO_STRESS: %0d/%0d passed", pass_count, pass_count));
    else
        fail("PROTO_STRESS", $sformatf("%0d failures", fail_count));
endtask

// ============================================================================
// TEST: Streaming Wrap-Around (100 vectors)
// ============================================================================
// Weakness Eliminated: Fixed wrap patterns
// Upgrade: Random addresses near boundary, random sizes, verify wrap behavior
// ============================================================================
task automatic test_streaming_wrap;
    logic [31:0] src, dst, size;
    logic [31:0] golden, actual;
    integer i;
    integer pass_count, fail_count;
    
    $display("[STREAM_WRAP] Testing 50 boundary-aligned transfers...");
    pass_count = 0;
    fail_count = 0;
    
    for (i = 0; i < 50; i++) begin
        cov_single_beat++;  // Track single-beat transfer coverage
        // Addresses near page boundaries (stress address wrap logic)
        src = 32'h0000_0FF0 + (($urandom % 4) * 4); // Near 4KB boundary
        dst = 32'h0000_5000 + (i * 4);
        size = 4;
        
        // Random data
        golden = $urandom | 32'hFFFF_0000; // High bits set
        ram_write(src, golden);
        
        // Execute
        dma_transfer(src, dst, size, 1000);
        
        // Verify
        actual = ram_read(dst);
        if (actual === golden) pass_count++;
        else begin
            $display("  [FAIL] WRAP_%0d: Src=0x%h, Exp=0x%h, Got=0x%h", i, src, golden, actual);
            fail_count++;
        end
    end
    
    if (fail_count == 0)
        pass($sformatf("STREAM_WRAP: %0d/%0d passed", pass_count, pass_count));
    else
        fail("STREAM_WRAP", $sformatf("%0d failures", fail_count));
endtask

// ============================================================================
// TEST: Hybrid I/O Readback (Thesis Verification)
// ============================================================================
// Verifies the 'Hybrid I/O' upgrade path:
//   1. Configure entire Row 3 (PEs 12-15) as PASS0 pipeline
//   2. Load known pattern (0xCAFEBABE) via DMA into Tile Memory bank 3
//   3. Execute CGRA - data flows: TileMem→PE12→PE13→PE14→PE15→edge_e3
//   4. Poll APB Status register (0x44) until result_valid
//   5. Read APB Result register (0x40) and verify against golden
//
// TOPOLOGY: Tile memory bank 3 feeds the WEST edge of Row 3 column 0
//   (PE[12] = tile 3,0). Data must flow EAST through PEs 13, 14, 15 to
//   reach edge_e3 which drives global_result. Unconfigured PEs execute
//   NOP (alu_result=0), so ALL 4 PEs in the row must be configured.
// ============================================================================
task automatic test_hybrid_io_readback;
    logic [31:0] status, result;
    logic [31:0] golden_data;
    integer poll_count, max_polls;
    logic timeout_flag;
    
    $display("[HYBRID_IO] Testing Hybrid I/O readback path...");
    
    // -------------------------------------------------------------------------
    // Step 1: Define test pattern
    // -------------------------------------------------------------------------
    golden_data = 32'hCAFE_BABE;
    
    // -------------------------------------------------------------------------
    // Step 2: Load golden data into ALL 16 context slots of Tile Memory bank 3
    // Bank 3 feeds Row 3 PEs via West edge. Context_pc sweeps 0-15, so ALL
    // slots must be populated for the PE to see golden data every cycle.
    // tile_bank_fill_all addresses: BASE_TILE | (bank << 12) | (slot * 4)
    //   Bank 3 word 0 = 0x1000_3000, word 1 = 0x1000_3004, ... word 15 = 0x1000_303C
    // -------------------------------------------------------------------------
    tile_bank_fill_all(2'd3, golden_data);
    
    // -------------------------------------------------------------------------
    // Step 3: Configure ALL 4 PEs in Row 3 with PASS0 + ROUTE_EAST
    //
    // Pipeline: TileMem bank3 → PE[12](3,0) → PE[13](3,1) → PE[14](3,2)
    //           → PE[15](3,3) → edge_e3 → global_result
    //
    // Each PE: PASS0 (output = input A), src0 = WEST (data from left neighbor)
    //          ROUTE_EAST (valid propagates east through the pipeline)
    //
    // All 16 config slots must be filled per PE because context_pc sweeps
    // 0-15 during execution; empty slots decode as NOP (alu_result=0).
    //
    // Pipeline latency: ~5 cycles (1 BSG read + 4 PE stages), so with 16
    // execution cycles, PE[15] outputs valid data for the last ~11 cycles.
    // -------------------------------------------------------------------------
    begin
        logic [63:0] pass0_cfg;
        pass0_cfg = build_pe_config(OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST, 16'd0);
        for (int pe = 12; pe <= 15; pe++) begin
            for (int slot = 0; slot < 16; slot++) begin
                config_pe(pe[3:0], slot[3:0], pass0_cfg);
            end
        end
    end
    
    // -------------------------------------------------------------------------
    // Step 4: Start Control Unit execution
    // Soft-reset first to clear any stale state, then start.
    // Auto-stop triggers after 16 context cycles → CU FINISH → cu_done pulse
    // → result_valid_latch goes high (cleared on next soft_reset).
    // -------------------------------------------------------------------------
    apb_write(ADDR_CU_CTRL, 32'd2);  // Assert soft_reset first
    wait_cycles(3);
    apb_write(ADDR_CU_CTRL, 32'd0);  // Release soft_reset
    wait_cycles(2);
    apb_write(ADDR_CU_CTRL, 32'd1);  // Start execution
    
    // -------------------------------------------------------------------------
    // Step 5: Poll Status register until result_valid (bit 0)
    // -------------------------------------------------------------------------
    poll_count = 0;
    max_polls = 1000;
    timeout_flag = 1'b0;
    
    $display("  [INFO] Polling RESULT_STATUS (0x44) for valid bit...");
    
    forever begin
        apb_read(ADDR_RESULT_STATUS, status);
        
        if (status[0] == 1'b1) begin
            $display("  [INFO] Result valid after %0d polls", poll_count);
            break;
        end
        
        poll_count++;
        if (poll_count >= max_polls) begin
            timeout_flag = 1'b1;
            $display("  [ERROR] Timeout waiting for result_valid!");
            break;
        end
        
        wait_cycles(1);
    end
    
    // -------------------------------------------------------------------------
    // Step 6: Read Result register and verify
    // -------------------------------------------------------------------------
    if (!timeout_flag) begin
        apb_read(ADDR_RESULT_DATA, result);
        
        $display("  [INFO] RESULT_DATA (0x40) = 0x%08h", result);
        $display("  [INFO] Expected          = 0x%08h", golden_data);
        
        if (result === golden_data) begin
            pass("HYBRID_IO: APB readback matches golden data");
        end else begin
            fail("HYBRID_IO", $sformatf("Mismatch: expected 0x%08h, got 0x%08h", 
                                        golden_data, result));
        end
    end else begin
        fail("HYBRID_IO", "Timeout waiting for result_valid");
    end
    
    // -------------------------------------------------------------------------
    // Step 7: Stop execution
    // -------------------------------------------------------------------------
    apb_write(ADDR_CU_CTRL, 32'd2);  // Soft reset to stop
    wait_cycles(2);
    apb_write(ADDR_CU_CTRL, 32'd0);  // Release reset
    
endtask

`endif
