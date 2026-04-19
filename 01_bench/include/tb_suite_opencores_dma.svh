`ifndef TB_SUITE_OPENCORES_DMA_SVH
`define TB_SUITE_OPENCORES_DMA_SVH
// ==============================================================================
// tb_suite_opencores_dma.svh — Suite OC: OpenCores LFSR DMA Integrity (3 tests)
// ==============================================================================
// Validates DMA data integrity under deterministic LFSR-driven AXI backpressure.
// Uses the same 32-bit Galois LFSR polynomial (mask 0xA3000000) as the hardware
// u_lfsr_ar/aw/w instances in the BFM so data patterns are cross-verifiable.
//
// DDR test addresses (all above existing suite range 0x0000..0xE000):
//   Source:   0x0001_8000 (also row-strided layout for OC03)
//   Readback: 0x0001_9000 (OC01, OC02)  0x0001_A000 (OC03)
// ==============================================================================

function automatic logic [31:0] lfsr32_next(input logic [31:0] s);
    return s[0] ? ((s >> 1) ^ 32'hA3000000) : (s >> 1);
endfunction

task automatic run_suite_OC_opencores_dma;
    logic        ok;
    logic [31:0] lfsr_state;
    logic        saved_stress_en;
    int          saved_stress_prob;
    int          i, r, c;
    logic [31:0] expected, actual;

    $display("\n--- SUITE OC: OpenCores LFSR DMA Integrity (3 Tests) ---");

    saved_stress_en   = stress_enable;
    saved_stress_prob = stress_probability;

    // =========================================================================
    // OC01: Incrementing-word pattern, 1D DMA DDR → tile → DDR, no backpressure
    // =========================================================================
    $display("[OC01] Incrementing pattern round-trip (no backpressure)...");
    disable_stress();
    for (i = 0; i < 64; i++) begin
        ram_write(32'h0001_8000 + 32'(i * 4), 32'(i));
        ram_write(32'h0001_9000 + 32'(i * 4), 32'hDEAD_BEEF);
    end
    dma_transfer(32'h0001_8000, 32'h1000_0000, 256, 2000);  // DDR → tile bank 0
    dma_transfer(32'h1000_0000, 32'h0001_9000, 256, 2000);  // tile → DDR readback
    check_data(32'h0001_8000, 32'h0001_9000, 256, ok);
    if (ok) begin
        pass_count++;
        $display("[PASS] OC01: Incrementing pattern round-trip");
    end else begin
        error_count++;
        $display("[FAIL] OC01: Incrementing pattern round-trip — data mismatch");
    end

    // =========================================================================
    // OC02: LFSR data pattern, 1D DMA DDR → tile → DDR, 50% AXI backpressure
    // Software LFSR seed matches hardware u_lfsr_ar SEED_VALUE (0x1ACA3107).
    // =========================================================================
    $display("[OC02] LFSR data pattern round-trip (50%% backpressure)...");
    enable_stress(50);
    lfsr_state = 32'h1ACA_3107;
    for (i = 0; i < 64; i++) begin
        lfsr_state = lfsr32_next(lfsr_state);
        ram_write(32'h0001_8000 + 32'(i * 4), lfsr_state);
        ram_write(32'h0001_9000 + 32'(i * 4), 32'h0);
    end
    dma_transfer(32'h0001_8000, 32'h1000_0000, 256, 6000);
    dma_transfer(32'h1000_0000, 32'h0001_9000, 256, 6000);
    disable_stress();
    check_data(32'h0001_8000, 32'h0001_9000, 256, ok);
    if (ok) begin
        pass_count++;
        $display("[PASS] OC02: LFSR data pattern under 50%% backpressure");
    end else begin
        error_count++;
        $display("[FAIL] OC02: LFSR data pattern — data mismatch under backpressure");
    end

    // =========================================================================
    // OC03: 2D strided DMA, DDR → DDR, 75% AXI backpressure
    // Source: 4 rows × 16 words at 32-word (128-byte) stride.
    // Dest:   flat at 0x0001_A000 (4×16=64 words packed).
    // =========================================================================
    $display("[OC03] 2D strided DMA 4x16w (75%% backpressure)...");
    enable_stress(75);
    for (r = 0; r < 4; r++) begin
        for (c = 0; c < 16; c++) begin
            ram_write(32'h0001_8000 + 32'(r * 128 + c * 4), 32'h0C00_0000 | 32'(r * 16 + c));
        end
    end
    for (i = 0; i < 64; i++)
        ram_write(32'h0001_A000 + 32'(i * 4), 32'h0);
    apb_write(ADDR_DMA_SRC,        32'h0001_8000);
    apb_write(ADDR_DMA_DST,        32'h0001_A000);
    apb_write(ADDR_DMA_SRC_STRIDE, 32'd128);   // 32-word row pitch
    apb_write(ADDR_DMA_ROWS,       32'd4);
    apb_write(ADDR_DMA_COLS,       32'd64);    // 16 words per row
    apb_write(ADDR_DMA_SIZE,       32'd256);   // 4 × 64 bytes
    apb_write(ADDR_DMA_CTRL,       32'h1);
    wait_dma_done(10000);
    disable_stress();
    ok = 1'b1;
    for (r = 0; r < 4; r++) begin
        for (c = 0; c < 16; c++) begin
            expected = 32'h0C00_0000 | 32'(r * 16 + c);
            actual   = ram_read(32'h0001_A000 + 32'(r * 64 + c * 4));
            if (actual !== expected) ok = 1'b0;
        end
    end
    if (ok) begin
        pass_count++;
        $display("[PASS] OC03: 2D strided DMA under 75%% backpressure");
    end else begin
        error_count++;
        $display("[FAIL] OC03: 2D strided DMA — data mismatch under heavy backpressure");
    end

    $display("\n[SUITE OC COMPLETE] OpenCores LFSR DMA tests done.\n");

    if (saved_stress_en) enable_stress(saved_stress_prob);
    else disable_stress();
endtask

`endif  // TB_SUITE_OPENCORES_DMA_SVH
