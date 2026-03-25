`ifndef TB_SUITE_DMA_WRITEBACK_SVH
`define TB_SUITE_DMA_WRITEBACK_SVH
// ============================================================================
// SUITE: DMA WRITE-BACK VERIFICATION (Suite AE)
// ============================================================================
// Focus: AXI Write Channel (CGRA -> DDR)
// Protocol: Bi-directional DMA, Round-trip data integrity, AXI compliance
// ============================================================================

task automatic run_suite_AE_dma_writeback;
    $display("\n");
    $display("========================================");
    $display("   SUITE AE: DMA WRITE-BACK VERIFICATION");
    $display("   Focus: AXI Write Channel & Round-Trip");
    $display("========================================");
    
    test_AE01_round_trip();
    test_AE02_write_burst_protocol();
    test_AE03_bvalid_stress();
    test_AE04_4kb_boundary_write();
    test_AE05_multi_burst_write();
    test_AE06_concurrent_read_write();
    test_AE07_zero_length_write();
    test_AE08_stress_random_writes();
    
    $display("\n[SUITE AE COMPLETE]\n");
endtask

// ----------------------------------------------------------------------------
// AE01: Round-Trip Data Integrity (DDR -> DDR Memcpy)
// ----------------------------------------------------------------------------
task automatic test_AE01_round_trip();
    logic [31:0] src_addr, dst_addr;
    logic [31:0] size;
    logic ok;
    integer i;
    
    $display("\n[AE01] AXI Write Data Integrity (DDR -> DDR)");
    
    src_addr = 32'h0000_1000;
    dst_addr = 32'h0000_5000;
    size = 32; // 8 words
    
    // Init source
    for (i = 0; i < 8; i++) begin
        ram_write(src_addr + i*4, 32'hAE01_0000 + i);
    end
    
    // Clear dest
    for (i = 0; i < 8; i++) begin
        ram_write(dst_addr + i*4, 32'h0);
    end
    
    // Execute Direct Copy (DDR -> DMA -> DDR)
    // This verifies Read Engine -> FIFO -> Write Engine -> AXI Write
    dma_transfer(src_addr, dst_addr, size, 1000);
    
    // Verify
    check_data(src_addr, dst_addr, size, ok);
    if (ok) pass("AE01: Data integrity verified");
    else fail("AE01", "Data mismatch");
endtask

// ----------------------------------------------------------------------------
// AE02: AXI Write Burst Protocol (WLAST Check)
// ----------------------------------------------------------------------------
task automatic test_AE02_write_burst_protocol();
    logic [31:0] src_addr, dst_addr;
    integer j;
    
    $display("\n[AE02] AXI Write Burst Protocol (WLAST)");
    
    // FIX: Use DDR-range source with seeded data (0x1000_0000 aliased to mem[0] via 17-bit truncation)
    src_addr = 32'h0000_2000;
    dst_addr = 32'h0000_6000;
    
    // Seed source memory
    for (j = 0; j < 8; j++) ram_write(src_addr + j*4, 32'hAE02_0000 + j);
    
    // Setup DMA Write
    fork
        begin
            // Thread 1: Trigger DMA Write
            apb_write(ADDR_DMA_SRC, src_addr);
            apb_write(ADDR_DMA_DST, dst_addr);
            apb_write(ADDR_DMA_SIZE, 32'd32); // 8 beats
            apb_write(ADDR_DMA_CTRL, 32'h1);
            wait_dma_done(500);
        end
        begin
            // Thread 2: Monitor Protocol
            check_write_burst_protocol();
        end
    join
endtask

// ----------------------------------------------------------------------------
// AE03: BVALID/BREADY Stress (Backpressure)
// ----------------------------------------------------------------------------
task automatic test_AE03_bvalid_stress();
    logic [31:0] src, dst;
    logic ok;
    
    $display("\n[AE03] BVALID/BREADY Stress Test");
    
    // FIX: Use DDR-range source mapped via 22-bit address mask
    src = 32'h0000_3000;
    dst = 32'h0000_7000;
    
    // Seed source data
    for (int j = 0; j < 16; j++) ram_write(src + j*4, 32'hAE03_0000 + j);
    
    // Enable 80% stress (random BVALID delays if modeled, or random ready)
    enable_stress(80);
    
    dma_transfer(src, dst, 64, 2000); // 16 words
    
    disable_stress();
    
    // FIX: Verify data integrity after stress transfer
    check_data(src, dst, 64, ok);
    if (ok) pass("AE03: Write completed under high stress with data verified");
    else fail("AE03", "Data mismatch after BVALID stress transfer");
endtask

// ----------------------------------------------------------------------------
// AE04: 4KB Boundary Crossing (Write)
// ----------------------------------------------------------------------------
task automatic test_AE04_4kb_boundary_write();
    logic [31:0] src, dst;
    logic ok;
    
    $display("\n[AE04] 4KB Boundary Crossing (Write)");
    
    // FIX: Use DDR-range source mapped via 22-bit address mask
    src = 32'h0000_4000;
    dst = 32'h0000_0FE0; // 32 bytes from 4KB boundary
    
    // Seed source data
    for (int j = 0; j < 16; j++) ram_write(src + j*4, 32'hAE04_0000 + j);
    
    // Transfer 64 bytes (crosses 0x1000)
    dma_transfer(src, dst, 64, 2000);
    
    // FIX: Verify data integrity after boundary-crossing transfer
    check_data(src, dst, 64, ok);
    if (ok) pass("AE04: 4KB boundary crossing handled with data verified");
    else fail("AE04", "Data mismatch after 4KB boundary crossing write");
endtask

// ----------------------------------------------------------------------------
// AE05: Multi-Burst Write (Max Length)
// ----------------------------------------------------------------------------
task automatic test_AE05_multi_burst_write();
    logic [31:0] src, dst;
    logic ok;
    
    $display("\n[AE05] Multi-Burst Write (256 Bytes)");
    
    // FIX: Use DDR-range source mapped via 22-bit address mask
    src = 32'h0000_C000;
    dst = 32'h0000_8000;
    
    // Seed source data (64 words)
    for (int j = 0; j < 64; j++) ram_write(src + j*4, 32'hAE05_0000 + j);
    
    // 256 Bytes = 64 words (Max burst is usually 256 beats, ensuring multi-beat works)
    dma_transfer(src, dst, 256, 3000);
    
    // FIX: Verify data integrity after multi-burst transfer
    check_data(src, dst, 256, ok);
    if (ok) pass("AE05: 256-byte write completed with data verified");
    else fail("AE05", "Data mismatch after 256-byte multi-burst write");
endtask

// ----------------------------------------------------------------------------
// AE06: Large Transfer with Data Verification (Pipeline Stress)
// ----------------------------------------------------------------------------
task automatic test_AE06_concurrent_read_write();
    localparam SRC_ADDR = 32'h0000_1000;
    localparam DST_ADDR = 32'h0000_3000;
    localparam XFER_SIZE = 32'd128;      // 128 bytes = 32 words

    $display("\n[AE06] Large DMA Transfer with Data Verification");
    
    // 1. Seed source memory with known pattern
    for (int i = 0; i < XFER_SIZE; i += 4) begin
        logic [31:0] pattern;
        pattern = 32'hAE06_0000 | i[15:0];
        mem[SRC_ADDR[21:0] + i + 0] = pattern[7:0];
        mem[SRC_ADDR[21:0] + i + 1] = pattern[15:8];
        mem[SRC_ADDR[21:0] + i + 2] = pattern[23:16];
        mem[SRC_ADDR[21:0] + i + 3] = pattern[31:24];
    end
    
    // 2. Clear destination
    for (int i = 0; i < XFER_SIZE; i++)
        mem[DST_ADDR[21:0] + i] = 8'h00;
    
    // 3. DMA transfer: src -> dst
    apb_write(ADDR_DMA_SRC, SRC_ADDR);
    apb_write(ADDR_DMA_DST, DST_ADDR);
    apb_write(ADDR_DMA_SIZE, XFER_SIZE);
    apb_write(ADDR_DMA_CTRL, 32'h1);
    
    wait_dma_done(1000);
    
    // 4. Verify destination data matches source
    check_data_report(SRC_ADDR, DST_ADDR, XFER_SIZE, "AE06: Large transfer data integrity");
endtask

// ----------------------------------------------------------------------------
// AE07: Zero-Length Write (Robustness)
// ----------------------------------------------------------------------------
task automatic test_AE07_zero_length_write();
    logic [31:0] rd;
    localparam DST_ADDR = 32'h0000_9000;
    localparam GUARD_SIZE = 16;  // Check 16 bytes around destination
    logic [7:0] guard_pattern [0:GUARD_SIZE-1];

    $display("\n[AE07] Zero-Length Write");
    
    // FIX: Seed destination with known pattern, verify zero-length write doesn't corrupt it
    for (int i = 0; i < GUARD_SIZE; i++) begin
        guard_pattern[i] = 8'hA7 ^ i[7:0];
        mem[DST_ADDR[21:0] + i] = guard_pattern[i];
    end
    
    // FIX: Use DDR-range source mapped via 22-bit address mask
    apb_write(ADDR_DMA_SRC, 32'h0000_E000);
    apb_write(ADDR_DMA_DST, DST_ADDR);
    apb_write(ADDR_DMA_SIZE, 32'd0);
    apb_write(ADDR_DMA_CTRL, 32'h1);
    
    wait_dma_done(100);
    // FIX: Verify DMA is not stuck busy after zero-length command
    apb_read(ADDR_DMA_STATUS, rd);
    if (rd[0] == 1'b0)
        pass("AE07: Zero-length write handled (not busy)");
    else
        fail("AE07: Zero-length write", "DMA still busy after zero-length transfer");
    
    // FIX: Verify destination was NOT corrupted by zero-length transfer
    begin
        bit corrupted = 0;
        for (int i = 0; i < GUARD_SIZE; i++) begin
            if (mem[DST_ADDR[21:0] + i] !== guard_pattern[i]) begin
                $error("[AE07] Destination corrupted at offset %0d: expected 0x%02h, got 0x%02h",
                       i, guard_pattern[i], mem[DST_ADDR[21:0] + i]);
                corrupted = 1;
            end
        end
        if (!corrupted)
            pass("AE07: Zero-length write did not corrupt destination");
        else
            fail("AE07: Destination corruption", "Zero-length transfer modified destination bytes");
    end
endtask

// ----------------------------------------------------------------------------
// AE08: Stress Random Writes
// ----------------------------------------------------------------------------
task automatic test_AE08_stress_random_writes();
    integer i;
    logic [31:0] addr, rd;
    
    $display("\n[AE08] Random Write Stress (10 iterations)");
    
    for(i=0; i<10; i++) begin
        addr = 32'h0000_A000 + (i*64);
        // FIX: Use DDR-range source mapped via 22-bit address mask
        ram_write(32'h0000_B000, i); // Seed data
        dma_transfer(32'h0000_B000, addr, 4, 100);
        
        // FIX: Verify each write landed correctly
        rd = ram_read(addr);
        if (rd !== i[31:0]) begin
            fail("AE08", $sformatf("Iter %0d: expected 0x%08h, got 0x%08h", i, i, rd));
            return;
        end
    end
    
    pass("AE08: Random write stress passed with data verified");
endtask

`endif
