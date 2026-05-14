// =============================================================================
// tb_wave_scenarios.sv
//
// Standalone scenario testbench that produces three SHM waveform databases
// for SimVision viewing — one per scenario referenced in Chapter 5,
// Figures 5.1–5.3 of the thesis.
//
// Scenario selection (plusarg):
//   +SCENARIO=DMA      → 16-beat 1-D AXI4 DMA read into tile bank 0
//   +SCENARIO=CUMAC    → CU MAC loop with TILE_AUTO_INC + SPM_AUTO_INC
//   +SCENARIO=FCGROUP  → East-readout pass draining RESULT_ROW0..3
//
// Each scenario:
//   1. Opens a uniquely-named SHM database (via `$shm_open`)
//   2. Probes the full tb hierarchy (`$shm_probe("AS")`)
//   3. Drives the specific stimulus required
//   4. Closes the SHM and `$finish`es
//
// SimVision the result with:
//   simvision wave_<scenario>.shm/wave_<scenario>.trn -input restore.tcl
//
// Build / elaboration / run is orchestrated by
// `01_bench/scenarios/run_scenarios.sh`, which is invoked by the
// `sample_waveforms` target in `06_doc/thesis_ch5/Makefile`.
// =============================================================================

`timescale 1ns/1ps

module tb_wave_scenarios;

    // =========================================================================
    // Clock, reset, parameters
    // =========================================================================
    localparam time CLK_PERIOD = 20ns;   // 50 MHz CGRA clock domain

    // CGRA APB register offsets (mirrored from cgra.h)
    localparam [31:0] CGRA_BASE        = 32'h4000_0000; // arbitrary in TB
    localparam logic [31:0] DMA_CTRL   = 32'h00;
    localparam logic [31:0] DMA_STATUS = 32'h04;
    localparam logic [31:0] DMA_SRC    = 32'h08;
    localparam logic [31:0] DMA_DST    = 32'h0C;
    localparam logic [31:0] DMA_SIZE   = 32'h10;
    localparam logic [31:0] CU_CTRL    = 32'h20;
    localparam logic [31:0] CU_STATUS  = 32'h24;
    localparam logic [31:0] CU_PC_END  = 32'h3C;
    localparam logic [31:0] LOOP_START = 32'h48;
    localparam logic [31:0] LOOP_END   = 32'h4C;
    localparam logic [31:0] LOOP_COUNT = 32'h50;
    localparam logic [31:0] TILE_AUTO_INC = 32'h78;
    localparam logic [31:0] SPM_AUTO_INC  = 32'h84;

    logic clk;
    logic rst_n;
    initial clk = 1'b0;
    always #(CLK_PERIOD/2) clk = ~clk;

    initial begin
        rst_n = 1'b0;
        #(CLK_PERIOD*4) rst_n = 1'b1;
    end

    // =========================================================================
    // DUT interface signals
    // =========================================================================
    // APB
    logic        psel, penable, pwrite;
    logic [31:0] paddr, pwdata, prdata;
    logic        pready, pslverr;

    // AXI4 master (CGRA → memory model)
    logic [3:0]  axi_awid, axi_arid, axi_bid, axi_rid;
    logic [31:0] axi_awaddr, axi_araddr;
    logic [7:0]  axi_awlen, axi_arlen;
    logic [2:0]  axi_awsize, axi_arsize;
    logic [1:0]  axi_awburst, axi_arburst, axi_bresp, axi_rresp;
    logic        axi_awvalid, axi_awready;
    logic [31:0] axi_wdata;
    logic [3:0]  axi_wstrb;
    logic        axi_wlast, axi_wvalid, axi_wready;
    logic        axi_bvalid, axi_bready;
    logic [31:0] axi_rdata;
    logic        axi_rlast, axi_rvalid, axi_rready;

    logic        irq_done;

    // Debug ports (probed by SimVision)
    logic        dbg_dma_busy;
    logic [2:0]  dbg_dma_read_state, dbg_dma_write_state;
    logic        dbg_dma_fifo_full, dbg_dma_fifo_empty;
    logic [31:0] dbg_dma_write_words_remaining;
    logic        synthesis_keep_q;

    // Packed mirrors of the result-FIFO's unpacked array so SimVision
    // can probe them via the normal "AS" flag without
    // unpacked-array gymnastics.
    wire [31:0] wave_result_row0;
    wire [31:0] wave_result_row1;
    wire [31:0] wave_result_row2;
    wire [31:0] wave_result_row3;

    // =========================================================================
    // DUT (real cgra_top from 00_src/)
    // =========================================================================
    cgra_top #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(32)
    ) u_dut (
        .clk(clk),
        .rst_n(rst_n),
        .psel(psel),
        .penable(penable),
        .pwrite(pwrite),
        .paddr(paddr),
        .pwdata(pwdata),
        .prdata(prdata),
        .pready(pready),
        .pslverr(pslverr),

        .m_axi_awid(axi_awid),
        .m_axi_awaddr(axi_awaddr),
        .m_axi_awlen(axi_awlen),
        .m_axi_awsize(axi_awsize),
        .m_axi_awburst(axi_awburst),
        .m_axi_awvalid(axi_awvalid),
        .m_axi_awready(axi_awready),
        .m_axi_wdata(axi_wdata),
        .m_axi_wstrb(axi_wstrb),
        .m_axi_wlast(axi_wlast),
        .m_axi_wvalid(axi_wvalid),
        .m_axi_wready(axi_wready),
        .m_axi_bid(axi_bid),
        .m_axi_bresp(axi_bresp),
        .m_axi_bvalid(axi_bvalid),
        .m_axi_bready(axi_bready),
        .m_axi_arid(axi_arid),
        .m_axi_araddr(axi_araddr),
        .m_axi_arlen(axi_arlen),
        .m_axi_arsize(axi_arsize),
        .m_axi_arburst(axi_arburst),
        .m_axi_arvalid(axi_arvalid),
        .m_axi_arready(axi_arready),
        .m_axi_rid(axi_rid),
        .m_axi_rresp(axi_rresp),
        .m_axi_rdata(axi_rdata),
        .m_axi_rlast(axi_rlast),
        .m_axi_rvalid(axi_rvalid),
        .m_axi_rready(axi_rready),

        .irq(irq_done),
        .synthesis_keep(synthesis_keep_q),

        .dbg_dma_busy(dbg_dma_busy),
        .dbg_dma_read_state(dbg_dma_read_state),
        .dbg_dma_write_state(dbg_dma_write_state),
        .dbg_dma_fifo_full(dbg_dma_fifo_full),
        .dbg_dma_fifo_empty(dbg_dma_fifo_empty),
        .dbg_dma_write_words_remaining(dbg_dma_write_words_remaining)
    );

    // Continuous mirrors of result_fifo_pop_data[0..3] into packed TB-level
    // wires — these are reachable by $shm_probe("AS") and don't need any
    // array-element gymnastics in the restore.tcl.
    assign wave_result_row0 = u_dut.result_fifo_pop_data[0];
    assign wave_result_row1 = u_dut.result_fifo_pop_data[1];
    assign wave_result_row2 = u_dut.result_fifo_pop_data[2];
    assign wave_result_row3 = u_dut.result_fifo_pop_data[3];

    // =========================================================================
    // Minimal AXI4 memory model
    // - Reads: respond with sequential 32-bit data (addr[15:2] as the value)
    //   so the burst pattern is visible in the waveform.
    // - Writes: accept WLAST, return OK BRESP.
    // - Always-ready handshake (no backpressure) so the burst is contiguous
    //   on the wave — easier to read in SimVision.
    // =========================================================================
    typedef enum logic [1:0] { R_IDLE = 2'd0, R_BURST = 2'd1 } r_state_t;
    typedef enum logic [1:0] { W_IDLE = 2'd0, W_DATA = 2'd1, W_RESP = 2'd2 } w_state_t;
    r_state_t r_state;
    w_state_t w_state;
    logic [31:0] r_addr_q;
    logic [7:0]  r_len_q;
    logic [7:0]  r_beat_q;
    logic [3:0]  r_id_q;
    logic [3:0]  w_id_q;

    // Memorable hex constants so the read-data burst is instantly
    // recognisable in screenshots. Cycles through the 8 famous "magic
    // numbers"; falls back to a counter pattern for longer bursts.
    function automatic logic [31:0] famous_word(input logic [7:0] beat);
        case (beat[2:0])
            3'd0: famous_word = 32'hDEAD_BEEF;
            3'd1: famous_word = 32'hCAFE_BABE;
            3'd2: famous_word = 32'hFEED_FACE;
            3'd3: famous_word = 32'hBAAD_F00D;
            3'd4: famous_word = 32'hDECA_FBAD;
            3'd5: famous_word = 32'hABAD_C0DE;
            3'd6: famous_word = 32'hC0DE_CAFE;
            3'd7: famous_word = 32'h1BAD_BABE;
        endcase
    endfunction

    assign axi_awready = (w_state == W_IDLE);
    assign axi_wready  = (w_state == W_DATA);
    assign axi_arready = (r_state == R_IDLE);
    // Note: m_axi_bready / m_axi_rready are DUT outputs (CGRA is the master);
    // the TB-side AXI BFM samples them, never drives them.

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            r_state <= R_IDLE;
            w_state <= W_IDLE;
            axi_rvalid <= 1'b0;
            axi_rlast  <= 1'b0;
            axi_rdata  <= 32'd0;
            axi_rid    <= 4'd0;
            axi_rresp  <= 2'd0;
            axi_bvalid <= 1'b0;
            axi_bresp  <= 2'd0;
            axi_bid    <= 4'd0;
            r_addr_q   <= 32'd0;
            r_len_q    <= 8'd0;
            r_beat_q   <= 8'd0;
            r_id_q     <= 4'd0;
            w_id_q     <= 4'd0;
        end else begin
            // Read channel
            case (r_state)
                R_IDLE: begin
                    axi_rvalid <= 1'b0;
                    axi_rlast  <= 1'b0;
                    if (axi_arvalid && axi_arready) begin
                        $display("[AXI BFM] AR handshake @ %0t: ARADDR=%h ARLEN=%0d",
                                 $time, axi_araddr, axi_arlen);
                        r_addr_q <= axi_araddr;
                        r_len_q  <= axi_arlen;
                        r_beat_q <= 8'd0;
                        r_id_q   <= axi_arid;
                        r_state  <= R_BURST;
                    end
                end
                R_BURST: begin
                    axi_rvalid <= 1'b1;
                    axi_rdata  <= famous_word(r_beat_q);   // DEADBEEF, CAFEBABE, ...
                    axi_rid    <= r_id_q;
                    axi_rresp  <= 2'b00; // OKAY
                    axi_rlast  <= (r_beat_q == r_len_q);
                    if (axi_rvalid && axi_rready) begin
                        $display("[AXI BFM] beat %0d: RDATA=%h%s",
                                 r_beat_q, famous_word(r_beat_q),
                                 (r_beat_q == r_len_q) ? " (RLAST)" : "");
                        if (r_beat_q == r_len_q) begin
                            axi_rvalid <= 1'b0;
                            axi_rlast  <= 1'b0;
                            r_state    <= R_IDLE;
                        end else begin
                            r_beat_q <= r_beat_q + 1;
                            axi_rdata <= famous_word(r_beat_q + 1);
                        end
                    end
                end
                default: r_state <= R_IDLE;
            endcase

            // Write channel (accept + respond OK)
            case (w_state)
                W_IDLE: begin
                    axi_bvalid <= 1'b0;
                    if (axi_awvalid && axi_awready) begin
                        w_id_q  <= axi_awid;
                        w_state <= W_DATA;
                    end
                end
                W_DATA: begin
                    if (axi_wvalid && axi_wready && axi_wlast) begin
                        w_state <= W_RESP;
                    end
                end
                W_RESP: begin
                    axi_bvalid <= 1'b1;
                    axi_bid    <= w_id_q;
                    axi_bresp  <= 2'b00; // OKAY
                    if (axi_bvalid && axi_bready) begin
                        axi_bvalid <= 1'b0;
                        w_state    <= W_IDLE;
                    end
                end
                default: w_state <= W_IDLE;
            endcase
        end
    end

    // =========================================================================
    // APB driver task — single 2-cycle transaction (setup + access phase)
    // =========================================================================
    task automatic apb_write(input logic [31:0] addr, input logic [31:0] data);
        @(posedge clk);
        psel    <= 1'b1;
        penable <= 1'b0;
        pwrite  <= 1'b1;
        paddr   <= addr;
        pwdata  <= data;
        @(posedge clk);
        penable <= 1'b1;
        @(posedge clk);
        while (!pready) @(posedge clk);
        psel    <= 1'b0;
        penable <= 1'b0;
        pwrite  <= 1'b0;
        paddr   <= 32'd0;
        pwdata  <= 32'd0;
    endtask

    task automatic apb_read(input logic [31:0] addr, output logic [31:0] data);
        @(posedge clk);
        psel    <= 1'b1;
        penable <= 1'b0;
        pwrite  <= 1'b0;
        paddr   <= addr;
        @(posedge clk);
        penable <= 1'b1;
        @(posedge clk);
        while (!pready) @(posedge clk);
        data    = prdata;
        psel    <= 1'b0;
        penable <= 1'b0;
        paddr   <= 32'd0;
    endtask

    // =========================================================================
    // Scenario tasks
    // =========================================================================

    // -- Shared helper: program the DMA to read 4 words from DDR (via the
    //    AXI BFM, which returns DEADBEEF / CAFEBABE / FEEDFACE / BAADF00D)
    //    into tile bank 0. Used by every scenario so the magic constants
    //    are visible on the AXI bus in all three waveforms.
    task automatic dma_preload_magic();
        apb_write(DMA_SRC,  32'h0020_0000);   // DDR address — AXI4 prefix
        apb_write(DMA_DST,  32'h1000_0000);   // Tile bank 0  — TILE prefix
        apb_write(DMA_SIZE, 32'd16);          // 4 words = 4 AXI beats
        apb_write(DMA_CTRL, 32'h0000_0001);   // start
        repeat (25) @(posedge clk);            // burst finishes well within 25 cycles
    endtask

    // -- Scenario 1: 4-beat AXI4 DMA read from DDR into tile bank 0.
    //    The TB-side AXI BFM returns memorable hex constants on RDATA
    //    so the burst is instantly readable in the screenshot.
    task automatic run_scenario_dma();
        $display("[WAVE] Scenario DMA: 4-beat AXI4 read into tile bank 0");
        @(posedge rst_n);
        repeat (2) @(posedge clk);
        dma_preload_magic();
        $display("[WAVE] DMA scenario complete");
    endtask

    // -- Scenario 2: DMA-preload (magic constants into tile bank 0) followed
    //    by a short CU MAC loop with TILE_AUTO_INC + SPM_AUTO_INC. The
    //    waveform tells a two-phase story:
    //      Phase 1 (cycles ~5–30): AXI4 burst with DEADBEEF / CAFEBABE /
    //                              FEEDFACE / BAADF00D appearing on RDATA.
    //      Phase 2 (cycles ~30–55): CU loop kicks, LOOP_COUNT decrements,
    //                                AUTO_INC bits assert, cu_status flips.
    task automatic run_scenario_cumac();
        $display("[WAVE] Scenario CUMAC: DMA preload + CU MAC loop");
        @(posedge rst_n);
        repeat (2) @(posedge clk);

        // Phase 1 — load magic constants into tile bank 0.
        dma_preload_magic();

        // Phase 2 — minimal CU setup, then kick.
        apb_write(LOOP_END,      32'd7);     // 8-slot loop body
        apb_write(LOOP_COUNT,    32'd0);     // 1 iteration
        apb_write(TILE_AUTO_INC, 32'd1);
        apb_write(SPM_AUTO_INC,  32'd1);
        apb_write(CU_PC_END,     32'd7);
        apb_write(CU_CTRL,       32'd1);     // start CU

        // Fixed wait — single 8-slot iteration completes well within 25 cycles.
        repeat (25) @(posedge clk);
        $display("[WAVE] CUMAC scenario complete");
    endtask

    // -- Scenario 3: DMA preload + brief MAC pass + east-readout CU pulse.
    //    Three-phase story:
    //      Phase 1 (cycles ~5–30):  AXI4 burst loads magic constants into tile.
    //      Phase 2 (cycles ~30–60): brief MAC kick — PE0 reads tile data and
    //                                writes RF[0]; col=1/2/3 chain it east.
    //      Phase 3 (cycles ~60–85): readout CU pulse moves col=0 RF[0] east
    //                                into RESULT_FIFO, so pop_data carries a
    //                                magic-derived value.
    task automatic run_scenario_fcgroup();
        $display("[WAVE] Scenario FCGROUP: DMA preload + MAC + east-readout");
        @(posedge rst_n);
        repeat (2) @(posedge clk);

        // Phase 1 — load magic constants into tile bank 0.
        dma_preload_magic();

        // Phase 2 — brief MAC pass so the col=0 PE RFs hold a value derived
        // from the magic-constant tile data.
        apb_write(LOOP_END,      32'd7);
        apb_write(LOOP_COUNT,    32'd0);     // 1 iteration
        apb_write(TILE_AUTO_INC, 32'd0);
        apb_write(SPM_AUTO_INC,  32'd0);
        apb_write(CU_PC_END,     32'd7);
        apb_write(CU_CTRL,       32'd1);
        repeat (20) @(posedge clk);

        // Phase 3 — short readout CU pulse (PC_END=3) drives the result FIFO.
        apb_write(CU_PC_END, 32'd3);
        apb_write(CU_CTRL,   32'd1);
        repeat (20) @(posedge clk);
        $display("[WAVE] FCGROUP scenario complete");
    endtask

    // =========================================================================
    // Main: choose scenario, open SHM, run, close
    //
    // Xcelium 20.09 requires literal strings as $shm_open arguments
    // (string-typed variables are not accepted), so the case statement
    // both opens the database and dispatches to the scenario.
    // =========================================================================
    string scenario;

    initial begin
        // Defaults
        psel    = 1'b0;
        penable = 1'b0;
        pwrite  = 1'b0;
        paddr   = 32'd0;
        pwdata  = 32'd0;

        // Resolve scenario from plusarg
        if (!$value$plusargs("SCENARIO=%s", scenario)) begin
            scenario = "DMA";
        end
        $display("[WAVE] tb_wave_scenarios: SCENARIO=%0s", scenario);

        case (scenario)
            "DMA": begin
                $shm_open("wave_dma.shm");
                $shm_probe("AS");
            end
            "CUMAC": begin
                $shm_open("wave_cumac.shm");
                $shm_probe("AS");
            end
            "FCGROUP": begin
                $shm_open("wave_fcgroup.shm");
                $shm_probe("AS");
            end
            default: begin
                $display("[WAVE] Unknown SCENARIO=%0s, falling back to DMA",
                         scenario);
                $shm_open("wave_other.shm");
                $shm_probe("AS");
            end
        endcase

        // The result-FIFO output is an unpacked array (skipped by "AS");
        // it's mirrored into TB-level packed wires (wave_result_row0..3)
        // which DO get probed via "AS" — see the assigns just below the
        // DUT instance above.

        // Now run the scenario chosen above.
        case (scenario)
            "DMA":     run_scenario_dma();
            "CUMAC":   run_scenario_cumac();
            "FCGROUP": run_scenario_fcgroup();
            default:   run_scenario_dma();
        endcase

        $shm_close();
        $finish;
    end

    // -------- Watchdog ------------------------------------------------------
    initial begin
        #50_000_000;  // 50 ms simulated
        $display("[WAVE] WATCHDOG TIMEOUT — forcing finish");
        $shm_close();
        $finish;
    end

endmodule
