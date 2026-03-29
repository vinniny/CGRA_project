`ifndef TB_SUITE_REAL_APP_SVH
`define TB_SUITE_REAL_APP_SVH
// ============================================================================
// Suite RAP: Real Application End-to-End FC Layer Verification
// ============================================================================
// Loads config.mem / image.mem / golden.mem into the AXI DDR model,
// drives DMA+CU exactly as cgra_driver.c does, and compares east-edge
// RESULT_ROW0-3 against the software golden accumulators.
//
// Config loading uses per-entry config_pe()-style two-DMA writes (proven
// reliable) rather than bulk DMA (which has a known FIFO drain issue for
// local config destinations in the current DMA engine).
//
// Files expected (relative to 03_sim/ xmsim working directory):
//   ../01_bench/config.mem  — 64-bit PE config words (61 chunks × 256 entries)
//   ../01_bench/image.mem   — 32-bit tile words      (61 chunks × 16 entries)
//   ../01_bench/golden.mem  — 4 × 32-bit raw accumulators
//
// Generate with:  cd 07_sw && make dump_hex
// ============================================================================

// ── Staging addresses ────────────────────────────────────────────────────
// IMPORTANT: DMA engine routes addresses by prefix: 0x0=AXI/DDR, 0x1=tile, 0x2=config.
// Staging buffers must use prefix 0x0 so the DMA reads them via AXI from the DDR BFM.
localparam logic [31:0] RAP_CFG_STAGE = 32'h0002_0000;  // 128KB offset in DDR BFM
localparam logic [31:0] RAP_IMG_STAGE = 32'h0003_0000;   // 192KB offset in DDR BFM

// Scratch area for single-word DMA staging (low DDR, same range as config_pe)
localparam logic [31:0] RAP_SCRATCH = 32'h0000_1004;

// ACC_CLR config word: opcode=15, everything else 0
localparam logic [63:0] RAP_ACC_CLR_CFG = 64'h000000000000000F;

// $readmemh arrays (module-scope for Xcelium compatibility)
logic [63:0] rap_cfg [0:15615];  // 61 chunks × 256 config words
logic [31:0] rap_img [0:975];    // 61 chunks × 16  tile words
logic [31:0] rap_gld [0:3];      // 4 expected raw accumulators

// =========================================================================
// Helper: rap_wait_cu_irq — spin on irq_done, then W1C clear
// =========================================================================
task automatic rap_wait_cu_irq(input int timeout_cycles);
    for (int t = 0; t < timeout_cycles; t++) begin
        if (irq_done) break;
        @(posedge clk);
    end
    if (!irq_done) begin
        $error("[RAP] wait_cu_irq: CU IRQ timeout after %0d cycles @ %0t",
               timeout_cycles, $time);
        error_count = error_count + 1;
    end
    apb_write(ADDR_IRQ_STATUS, 32'h2);  // W1C — clear CU Done bit
endtask

// =========================================================================
// Helper: rap_config_pe — write one 64-bit config entry via two 4-byte DMAs
// Uses config_pe()-style individual DMAs (proven reliable).
// pe_id: 0-15, slot: 0-15, data: 64-bit config word
// =========================================================================
task automatic rap_config_pe(input int pe_id, input int slot, input logic [63:0] data);
    logic [31:0] cfg_addr_base;
    cfg_addr_base = BASE_CONFIG | (32'(pe_id) << 7) | (32'(slot) << 3);

    // HI word: addr bit[2]=0 latches upper 32 bits
    ram_write(RAP_SCRATCH, data[63:32]);
    apb_write(ADDR_DMA_SRC, RAP_SCRATCH);
    apb_write(ADDR_DMA_DST, cfg_addr_base);
    apb_write(ADDR_DMA_SIZE, 32'd4);
    apb_write(ADDR_DMA_CTRL, 32'd1);
    wait_dma_done(100);

    // LO word: addr bit[2]=1 commits full 64-bit config
    ram_write(RAP_SCRATCH, data[31:0]);
    apb_write(ADDR_DMA_SRC, RAP_SCRATCH);
    apb_write(ADDR_DMA_DST, cfg_addr_base | 32'h4);
    apb_write(ADDR_DMA_SIZE, 32'd4);
    apb_write(ADDR_DMA_CTRL, 32'd1);
    wait_dma_done(100);
endtask

// =========================================================================
// Helper: rap_load_config_chunk — load 256 config entries via individual DMAs
// =========================================================================
task automatic rap_load_config_chunk(input int k);
    for (int i = 0; i < 256; i++) begin
        int pe_id = i / 16;
        int ctx   = i % 16;
        rap_config_pe(pe_id, ctx, rap_cfg[k * 256 + i]);
    end
endtask

// =========================================================================
// Helper: rap_stage_image_chunk — copy rap_img[k*16..+15] into mem[]
// =========================================================================
task automatic rap_stage_image_chunk(input int k);
    for (int i = 0; i < 16; i++)
        ram_write(RAP_IMG_STAGE + i * 4, rap_img[k * 16 + i]);
endtask

// =========================================================================
// Helper: rap_acc_clr_phase — configure ACC_CLR for all PEs, run CU once
// =========================================================================
task automatic rap_acc_clr_phase;
    // Write ACC_CLR config to all 16 PEs, slot 0 (broadcasts to all contexts)
    for (int pe = 0; pe < 16; pe++)
        rap_config_pe(pe, 0, RAP_ACC_CLR_CFG);

    // LOOP: run context 0 once (START=0, END=0, COUNT=0)
    apb_write(ADDR_LOOP_START, 32'd0);
    apb_write(ADDR_LOOP_END,   32'd0);
    apb_write(ADDR_LOOP_COUNT, 32'd0);
    apb_write(ADDR_CU_CTRL,    32'd1);   // start
    rap_wait_cu_irq(500);
endtask

// =========================================================================
// Main suite task
// =========================================================================
task automatic run_suite_real_app;
    logic [31:0] got_row [0:3];
    logic [31:0] rd;
    integer      k, r;

    $display("\n");
    $display("========================================");
    $display("   SUITE RAP: REAL APPLICATION E2E");
    $display("   FC Layer: 784->30 (group 0, 61 chunks)");
    $display("   HW matches cgra_driver.c DMA sequence");
    $display("========================================\n");

    reset_dut(5);

    // ── Load .mem files ───────────────────────────────────────────────
    $readmemh("../01_bench/config.mem", rap_cfg);
    $readmemh("../01_bench/image.mem",  rap_img);
    $readmemh("../01_bench/golden.mem", rap_gld);

    // Validate that .mem files were actually loaded (readmemh silently fails if missing)
    if (rap_gld[0] === 32'hx || (rap_gld[0] == 32'h0 && rap_gld[1] == 32'h0 &&
                                  rap_gld[2] == 32'h0 && rap_gld[3] == 32'h0)) begin
        $error("[RAP] golden.mem appears empty or failed to load — skipping suite");
        error_count = error_count + 1;
        return;
    end
    if (rap_cfg[0] === 64'hx || rap_cfg[0] == 64'h0) begin
        $error("[RAP] config.mem appears empty or failed to load — skipping suite");
        error_count = error_count + 1;
        return;
    end
    $display("[RAP] Loaded config.mem / image.mem / golden.mem");
    $display("[RAP] Golden: row0=0x%08h row1=0x%08h row2=0x%08h row3=0x%08h",
             rap_gld[0], rap_gld[1], rap_gld[2], rap_gld[3]);

    // ── Enable CU Done IRQ ────────────────────────────────────────────
    apb_write(ADDR_IRQ_MASK, 32'h2);

    // ── Clear all PE accumulators before FC run ───────────────────────
    $display("[RAP] ACC_CLR phase...");
    rap_acc_clr_phase();
    $display("[RAP] Accumulators cleared.");

    // ── 61-chunk FC accumulation loop ────────────────────────────────
    $display("[RAP] Starting 61-chunk FC loop...");
    for (k = 0; k < 61; k++) begin

        // Load config chunk k → all 16 PEs × 16 contexts via individual DMAs
        rap_load_config_chunk(k);

        // Stage + DMA image chunk k → all 4 tile banks (64 bytes each)
        rap_stage_image_chunk(k);
        for (r = 0; r < 4; r++)
            dma_transfer(RAP_IMG_STAGE, BASE_TILE | (r << 12), 32'd64, 500);

        // LOOP: run contexts 0–15 (full 16-context sweep)
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd15);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_CU_CTRL,    32'd1);  // start
        rap_wait_cu_irq(500);

        `ifdef TB_VERBOSE
            if (k == 0) begin
                apb_read(ADDR_RESULT_ROW0, rd);
                $display("[RAP_DBG] chunk0: result_row[0]=%08h  PE00_acc=%0h  PE03_alu=%08h",
                         rd, u_dut.u_array.row[0].col[0].u_tile.u_pe.accumulator,
                         u_dut.u_array.row[0].col[3].u_tile.u_pe.alu_result);
            end
        `endif

        `ifdef TB_VERBOSE
            if (k % 10 == 0)
                $display("[RAP]   chunk %0d/61 done", k);
        `endif
    end
    $display("[RAP] All 61 chunks complete.");

    // ── Read east-edge result registers ──────────────────────────────
    apb_read(ADDR_RESULT_STATUS, rd);
    if (rd[0] !== 1'b1) begin
        $error("[RAP] RESULT_STATUS[0] not set — result_valid=0 (got 0x%08h)", rd);
        error_count = error_count + 1;
    end

    apb_read(ADDR_RESULT_ROW0, got_row[0]);
    apb_read(ADDR_RESULT_ROW1, got_row[1]);
    apb_read(ADDR_RESULT_ROW2, got_row[2]);
    apb_read(ADDR_RESULT_ROW3, got_row[3]);

    $display("[RAP] Results: row0=0x%08h row1=0x%08h row2=0x%08h row3=0x%08h",
             got_row[0], got_row[1], got_row[2], got_row[3]);

    // ── Compare against golden ────────────────────────────────────────
    for (r = 0; r < 4; r++) begin
        if (got_row[r] === rap_gld[r]) begin
            $display("[PASS] RAP01: Row%0d raw_acc match (0x%08h)", r, rap_gld[r]);
            pass_count = pass_count + 1;
        end else begin
            $error("[FAIL] RAP01: Row%0d raw_acc mismatch: exp=0x%08h got=0x%08h",
                   r, rap_gld[r], got_row[r]);
            error_count = error_count + 1;
        end
    end

    $display("\n[Suite RAP complete]\n");
endtask

`endif // TB_SUITE_REAL_APP_SVH
