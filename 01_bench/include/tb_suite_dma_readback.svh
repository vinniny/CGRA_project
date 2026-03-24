`ifndef TB_SUITE_DMA_READBACK_SVH
`define TB_SUITE_DMA_READBACK_SVH
// ============================================================================
// SUITE: DMA TILE READ-BACK VERIFICATION (Suite AF)
// ============================================================================
// Focus: Tile Memory -> DDR via AXI Write Channel (read-back path)
// Protocol: Tile read -> FIFO -> AXI Write, Round-trip data integrity
// ============================================================================

task automatic run_suite_AF_dma_readback;
    $display("\n");
    $display("========================================");
    $display("   SUITE AF: DMA TILE READ-BACK");
    $display("   Focus: Tile -> DDR via AXI Write");
    $display("========================================");

    test_AF01_round_trip();
    test_AF02_multi_bank();
    test_AF03_large_transfer();
    test_AF04_4kb_boundary_write();
    test_AF05_stress();
    test_AF06_zero_length();
    test_AF07_abort_mid_transfer();
    test_AF08_random_stress();

    $display("\n[SUITE AF COMPLETE]\n");
endtask

// ----------------------------------------------------------------------------
// AF01: Round-Trip Data Integrity (DDR -> Tile -> DDR)
// ----------------------------------------------------------------------------
task automatic test_AF01_round_trip();
    logic [31:0] ddr_src, tile_dst, ddr_dst;
    logic ok;
    integer i;

    $display("\n[AF01] Round-Trip: DDR -> Tile -> DDR (8 words)");

    ddr_src  = 32'h0000_2000;
    tile_dst = BASE_TILE;             // Bank 0, offset 0
    ddr_dst  = 32'h0000_6000;

    // Seed source in DDR
    for (i = 0; i < 8; i++)
        ram_write(ddr_src + i*4, 32'hAF01_0000 + i);

    // Clear destination
    for (i = 0; i < 8; i++)
        ram_write(ddr_dst + i*4, 32'h0);

    // Phase 1: DDR -> Tile
    dma_transfer(ddr_src, tile_dst, 32, 1000);

    // Phase 2: Tile -> DDR (read-back)
    dma_transfer(tile_dst, ddr_dst, 32, 1000);

    // Verify
    check_data(ddr_src, ddr_dst, 32, ok);
    if (ok) pass("AF01: Round-trip data integrity verified");
    else fail("AF01", "Data mismatch after DDR->Tile->DDR round-trip");
endtask

// ----------------------------------------------------------------------------
// AF02: Multi-Bank Read-Back (All 4 Banks)
// ----------------------------------------------------------------------------
task automatic test_AF02_multi_bank();
    logic [31:0] tile_addr, ddr_dst, ddr_src;
    logic ok;
    integer bank, i;
    bit any_fail;

    $display("\n[AF02] Multi-Bank Read-Back (4 banks x 4 words)");

    any_fail = 0;
    for (bank = 0; bank < 4; bank++) begin
        ddr_src   = 32'h0000_1000 + bank * 32'h100;
        tile_addr = BASE_TILE | ({18'd0, bank[1:0], 12'd0});
        ddr_dst   = 32'h0000_8000 + bank * 32'h100;

        // Seed DDR source with bank-unique pattern
        for (i = 0; i < 4; i++)
            ram_write(ddr_src + i*4, 32'hAF020000 | (bank[7:0] << 8) | i[7:0]);

        // Clear destination
        for (i = 0; i < 4; i++)
            ram_write(ddr_dst + i*4, 32'h0);

        // DDR -> Tile
        dma_transfer(ddr_src, tile_addr, 16, 500);

        // Tile -> DDR
        dma_transfer(tile_addr, ddr_dst, 16, 500);

        // Verify
        check_data(ddr_src, ddr_dst, 16, ok);
        if (!ok) begin
            fail("AF02", $sformatf("Bank %0d data mismatch", bank));
            any_fail = 1;
        end
    end

    if (!any_fail)
        pass("AF02: All 4 banks read-back verified");
endtask

// ----------------------------------------------------------------------------
// AF03: Large Transfer (32 words = 128 bytes, multiple FIFO fill/drain)
// ----------------------------------------------------------------------------
task automatic test_AF03_large_transfer();
    logic [31:0] ddr_src, tile_dst, ddr_dst;
    logic ok;
    integer i;

    $display("\n[AF03] Large Transfer (32 words, exercises FIFO cycling)");

    ddr_src  = 32'h0000_3000;
    tile_dst = BASE_TILE;
    ddr_dst  = 32'h0000_7000;

    // Seed 32 words
    for (i = 0; i < 32; i++)
        ram_write(ddr_src + i*4, 32'hAF03_0000 + i);

    // Clear destination
    for (i = 0; i < 32; i++)
        ram_write(ddr_dst + i*4, 32'h0);

    // DDR -> Tile
    dma_transfer(ddr_src, tile_dst, 128, 2000);

    // Tile -> DDR
    dma_transfer(tile_dst, ddr_dst, 128, 2000);

    // Verify
    check_data(ddr_src, ddr_dst, 128, ok);
    if (ok) pass("AF03: 32-word round-trip verified");
    else fail("AF03", "Data mismatch on large transfer");
endtask

// ----------------------------------------------------------------------------
// AF04: 4KB Boundary Crossing on DDR Write Side
// ----------------------------------------------------------------------------
task automatic test_AF04_4kb_boundary_write();
    logic [31:0] ddr_src, tile_dst, ddr_dst;
    logic ok;
    integer i;

    $display("\n[AF04] 4KB Boundary Crossing (DDR write destination)");

    ddr_src  = 32'h0000_4000;
    tile_dst = BASE_TILE;
    ddr_dst  = 32'h0000_0FE0;  // 32 bytes before 4KB boundary

    // Seed 16 words (64 bytes, crosses 0x1000 boundary)
    for (i = 0; i < 16; i++)
        ram_write(ddr_src + i*4, 32'hAF04_0000 + i);

    // Clear destination
    for (i = 0; i < 16; i++)
        ram_write(ddr_dst + i*4, 32'h0);

    // DDR -> Tile
    dma_transfer(ddr_src, tile_dst, 64, 1500);

    // Tile -> DDR (write crosses 4KB boundary)
    dma_transfer(tile_dst, ddr_dst, 64, 1500);

    // Verify
    check_data(ddr_src, ddr_dst, 64, ok);
    if (ok) pass("AF04: 4KB boundary crossing with tile read-back verified");
    else fail("AF04", "Data mismatch on 4KB boundary crossing write");
endtask

// ----------------------------------------------------------------------------
// AF05: Stress (AXI Write Backpressure During Tile Read-Back)
// ----------------------------------------------------------------------------
task automatic test_AF05_stress();
    logic [31:0] ddr_src, tile_dst, ddr_dst;
    logic ok;
    integer i;

    $display("\n[AF05] Tile Read-Back Under AXI Write Stress (80%%)");

    ddr_src  = 32'h0000_5000;
    tile_dst = BASE_TILE;
    ddr_dst  = 32'h0000_9000;

    // Seed 16 words
    for (i = 0; i < 16; i++)
        ram_write(ddr_src + i*4, 32'hAF05_0000 + i);

    // Clear destination
    for (i = 0; i < 16; i++)
        ram_write(ddr_dst + i*4, 32'h0);

    // DDR -> Tile (no stress for loading phase)
    dma_transfer(ddr_src, tile_dst, 64, 1000);

    // Tile -> DDR with stress
    enable_stress(80);
    dma_transfer(tile_dst, ddr_dst, 64, 3000);
    disable_stress();

    // Verify
    check_data(ddr_src, ddr_dst, 64, ok);
    if (ok) pass("AF05: Tile read-back verified under write stress");
    else fail("AF05", "Data mismatch after stress tile read-back");
endtask

// ----------------------------------------------------------------------------
// AF06: Zero-Length Tile Read (Robustness)
// ----------------------------------------------------------------------------
task automatic test_AF06_zero_length();
    logic [31:0] rd;
    localparam DST_ADDR = 32'h0000_A000;
    localparam GUARD_SIZE = 16;
    logic [7:0] guard_pattern [0:GUARD_SIZE-1];
    integer i;

    $display("\n[AF06] Zero-Length Tile Read");

    // Seed destination with known guard pattern
    for (i = 0; i < GUARD_SIZE; i++) begin
        guard_pattern[i] = 8'hA6 ^ i[7:0];
        mem[DST_ADDR[16:0] + i] = guard_pattern[i];
    end

    // Issue zero-length tile read-back
    apb_write(ADDR_DMA_SRC, BASE_TILE);
    apb_write(ADDR_DMA_DST, DST_ADDR);
    apb_write(ADDR_DMA_SIZE, 32'd0);
    apb_write(ADDR_DMA_CTRL, 32'h1);
    wait_dma_done(100);

    // Verify DMA not stuck busy
    apb_read(ADDR_DMA_STATUS, rd);
    if (rd[0] == 1'b0)
        pass("AF06: Zero-length tile read handled (not busy)");
    else
        fail("AF06: Zero-length tile read", "DMA still busy");

    // Verify destination not corrupted
    begin
        bit corrupted;
        corrupted = 0;
        for (i = 0; i < GUARD_SIZE; i++) begin
            if (mem[DST_ADDR[16:0] + i] !== guard_pattern[i]) begin
                $error("[AF06] Destination corrupted at offset %0d: expected 0x%02h, got 0x%02h",
                       i, guard_pattern[i], mem[DST_ADDR[16:0] + i]);
                corrupted = 1;
            end
        end
        if (!corrupted)
            pass("AF06: Zero-length tile read did not corrupt destination");
        else
            fail("AF06: Destination corruption", "Zero-length transfer modified destination bytes");
    end
endtask

// ----------------------------------------------------------------------------
// AF07: Abort Mid-Transfer (Soft Reset During Tile-to-DDR)
// ----------------------------------------------------------------------------
task automatic test_AF07_abort_mid_transfer();
    logic [31:0] rd;
    integer i;

    $display("\n[AF07] Abort During Tile Read-Back");

    // Load tile memory with data first
    for (i = 0; i < 16; i++)
        ram_write(32'h0000_B000 + i*4, 32'hAF07_0000 + i);
    dma_transfer(32'h0000_B000, BASE_TILE, 64, 1000);

    // Start a tile-to-DDR transfer (large enough to be in-flight)
    apb_write(ADDR_DMA_SRC, BASE_TILE);
    apb_write(ADDR_DMA_DST, 32'h0000_C000);
    apb_write(ADDR_DMA_SIZE, 32'd64);
    apb_write(ADDR_DMA_CTRL, 32'h1);

    // Wait a few cycles then abort via CU soft reset
    wait_cycles(5);
    apb_write(ADDR_CU_CTRL, 32'h2);  // Soft reset (cfg_abort)
    wait_cycles(10);
    apb_write(ADDR_CU_CTRL, 32'h0);  // Release soft reset
    wait_cycles(5);

    // Verify DMA returned to idle
    apb_read(ADDR_DMA_STATUS, rd);
    if (rd[0] == 1'b0)
        pass("AF07: DMA returned to idle after tile read-back abort");
    else
        fail("AF07: Abort tile read-back", "DMA still busy after abort");
endtask

// ----------------------------------------------------------------------------
// AF08: Randomized Stress (10 iterations, varying bank/size)
// ----------------------------------------------------------------------------
task automatic test_AF08_random_stress();
    integer iter, i;
    logic [1:0]  bank;
    logic [31:0] num_words;
    logic [31:0] tile_addr, ddr_src, ddr_dst, size;
    logic [31:0] rd;
    logic ok;

    $display("\n[AF08] Random Tile Read-Back Stress (10 iterations)");

    for (iter = 0; iter < 10; iter++) begin
        bank      = $urandom_range(0, 3);
        num_words = $urandom_range(1, 8);
        size      = num_words * 4;
        tile_addr = BASE_TILE | ({18'd0, bank, 12'd0});
        ddr_src   = 32'h0000_1000 + iter * 32'h80;
        ddr_dst   = 32'h0000_A000 + iter * 32'h80;

        // Seed source
        for (i = 0; i < num_words; i++)
            ram_write(ddr_src + i*4, 32'hAF080000 | (iter[7:0] << 8) | i[7:0]);

        // Clear destination
        for (i = 0; i < num_words; i++)
            ram_write(ddr_dst + i*4, 32'h0);

        // DDR -> Tile
        dma_transfer(ddr_src, tile_addr, size, 500);

        // Tile -> DDR
        dma_transfer(tile_addr, ddr_dst, size, 500);

        // Verify
        check_data(ddr_src, ddr_dst, size, ok);
        if (!ok) begin
            fail("AF08", $sformatf("Iter %0d: bank=%0d words=%0d data mismatch", iter, bank, num_words));
            return;
        end
    end

    pass("AF08: Random tile read-back stress passed (10 iterations)");
endtask

`endif
