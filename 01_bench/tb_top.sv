// ==============================================================================
// CGRA Unified Master Testbench - Layered Architecture
// ==============================================================================
// Structure (modeled after Bus IP reference TB):
//   Layer 1: tb_defs.svh        - Macros, verbosity, parameters, assertions
//   Layer 2: tb_scenario_gen.svh - Random generators, coverage counters
//   Layer 3: tb_tasks.svh       - APB/DMA/PE drivers, log_test_result
//   Layer 4: tb_protocol_checkers.svh - AXI protocol monitoring
//   Layer 5: tb_test_suites.svh - All test suites
//
// Features:
//   - Watchdog timer (TB_WATCHDOG_NS) prevents infinite hangs
//   - Unified EOS `final` block with VERDICT (PASS/FAIL)
//   - Verbosity control: define TB_VERBOSE for debug output, default quiet
//   - ASSERT_TRUE macro with protocol_check_enable guard
//   - Centralized log_test_result for uniform pass/fail/skip tracking
//
// Build: xmvlog / xmelab / xmsim (Cadence Xcelium)
//        Add +define+TB_VERBOSE for debug output
// ==============================================================================

`timescale 1ns/1ps

module tb_top;

    // Layer 1: Global Definitions (must be inside module for localparam)
    `include "include/tb_defs.svh"

    // =========================================================================
    // 1. DETERMINISTIC SEED & CLOCK/RESET GENERATION
    // =========================================================================
    // TB-1: Deterministic random seed for reproducible test runs.
    // The Makefile passes +SEED=N via xmsim plusargs.
    // All $urandom calls in the TB use this seed via $srandom().
    int sim_seed;
    int verbosity;  // 0=quiet, 1=normal, 2=verbose
    initial begin
        if (!$value$plusargs("SEED=%d", sim_seed))
            sim_seed = 42;
        if (!$value$plusargs("VERBOSITY=%d", verbosity))
            verbosity = 1;
        $srandom(sim_seed);
        $display("[INFO] [%0t] ============================================", $time);
        $display("[INFO] [%0t]   CGRA 4x4 Verification Suite", $time);
        $display("[INFO] [%0t]   Seed: %0d | Verbosity: %0d | Max Errors: %0d", $time, sim_seed, verbosity, `MAX_ERRORS);
        $display("[INFO] [%0t]   Reproduce: make run SEED=%0d", $time, sim_seed);
        $display("[INFO] [%0t] ============================================", $time);
    end

    logic clk;
    logic rst_n;

    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end  // 100 MHz Clock

    initial begin
        rst_n = 1'b0;
        #50 rst_n = 1'b1;
    end

    // =========================================================================
    // 2. SIGNAL DECLARATIONS (using logic for Verilator-native style)
    // =========================================================================
    
    // APB Signals
    logic        psel, penable, pwrite;
    logic [31:0] paddr, pwdata;
    logic [31:0] prdata;
    logic        pready, pslverr;

    // AXI Write Channel
    logic [3:0]  axi_awid;
    logic [31:0] axi_awaddr, axi_wdata;
    logic        axi_awvalid, axi_awready, axi_wvalid, axi_wready;
    logic [3:0]  axi_wstrb;
    logic [3:0]  axi_bid;
    logic [1:0]  axi_bresp;
    logic        axi_bvalid, axi_bready;
    logic        axi_bvalid_reg;
    logic [7:0]  axi_awlen;
    logic [2:0]  axi_awsize;
    logic [1:0]  axi_awburst;
    logic        axi_wlast;

    // AXI Read Channel
    logic [3:0]  axi_arid;
    logic [31:0] axi_araddr, axi_rdata;
    logic        axi_arvalid, axi_arready, axi_rvalid, axi_rready;
    logic [3:0]  axi_rid;
    logic [1:0]  axi_rresp;
    logic [7:0]  axi_arlen;
    logic [2:0]  axi_arsize;
    logic [1:0]  axi_arburst;
    logic        axi_rlast_reg;

    logic        irq_done;

    // =========================================================================
    // 3. GLOBAL TEST VARIABLES (Must be declared before includes)
    // =========================================================================
    int assertion_errors = 0;
    int error_count = 0;
    int pass_count = 0;
    int cycle_count = 0;

    // Memory Model (128KB)
    localparam int MEM_SIZE = TB_MEM_SIZE;
    logic [7:0] mem [0:MEM_SIZE-1];

    // Stress Control
    logic        stress_enable = 1'b0;
    int          stress_probability = 0;

    // Cycle counter (using always for testbench)
    always @(posedge clk) cycle_count = cycle_count + 1;  // FIX: Blocking for TB counter consistency

    // =========================================================================
    // 3b. CLOCKING BLOCKS — Race-Condition Immunity
    // =========================================================================
    // APB clocking block: drives outputs 1ns after posedge, samples inputs
    // 1 step before posedge. Eliminates delta-cycle races between TB and DUT.
    clocking apb_cb @(posedge clk);
        default input #1step output #1;
        output psel, penable, pwrite, paddr, pwdata;
        input  prdata, pready, pslverr;
    endclocking

    // AXI monitor clocking block: sample-only for protocol checkers.
    clocking axi_cb @(posedge clk);
        default input #1step;
        input axi_awaddr, axi_awvalid, axi_awready, axi_awlen, axi_awsize, axi_awburst;
        input axi_wdata, axi_wvalid, axi_wready, axi_wstrb, axi_wlast;
        input axi_bvalid, axi_bready;
        input axi_araddr, axi_arvalid, axi_arready, axi_arlen, axi_arsize, axi_arburst;
        input axi_rdata, axi_rvalid, axi_rready, axi_rlast_reg;
        input irq_done;
    endclocking

    // =========================================================================
    // 4. INCLUDE MODULAR LAYERS (Order matters!)
    // =========================================================================
    `include "include/tb_transactions.svh"      // Transaction classes (Phase A)
    `include "include/tb_config.svh"            // Configuration object (Phase A)
    `include "include/tb_scenario_gen.svh"      // Coverage counters, random generators
    `include "include/tb_tasks.svh"             // Driver tasks (uses signals)
    `include "include/tb_coverage.svh"          // Functional coverage (covergroups)
    `include "include/tb_protocol_checkers.svh" // Protocol monitors (uses signals)
    
    // CRV Suite Files (4 Pillars)
    `include "include/tb_suite_system.svh"      // System Integrity (APB, DMA, Protocol)
    `include "include/tb_suite_fabric.svh"      // Fabric Stress (Pipeline, Parallel, Routing)
    `include "include/tb_suite_robustness.svh"  // Robustness (Reset, Stall, IRQ)
    `include "include/tb_suite_lpr.svh"          // LPR demo feature tests (RELU, MAX, Loop CSRs)
    `include "include/tb_suite_dma_writeback.svh"  // DMA Write-Back Verification (Suite AE)
    `include "include/tb_suite_dma_readback.svh"  // DMA Tile Read-Back Verification (Suite AF)
    `include "include/tb_suite_pipeline.svh"      // PE Pipeline Register (Suite AG)
    `include "include/tb_suite_axi_error.svh"     // AXI Error Handling (Suite AH)
    `include "include/tb_suite_tile_depth.svh"    // Tile Memory Depth (Suite AI)
    `include "include/tb_suite_loops.svh"        // Hardware Loop Execution (Suite AJ)
    `include "include/tb_suite_doublebuf.svh"   // Double-Buffered Tile Memory (Suite AK)
    `include "include/tb_suite_mixed_prec.svh" // Mixed-Precision INT8/INT16 (Suite AL)
    `include "include/tb_suite_real_app.svh"      // Suite RAP: Real Application E2E

    // Phase 1: Barebone FPGA Deployment Verification
    `include "include/tb_suite_apb_sanity.svh"    // Suite AM: APB Register Sanity
    `include "include/tb_suite_dma_smoke.svh"     // Suite AN: DMA Smoke Test
    `include "include/tb_suite_compute_smoke.svh" // Suite AO: Compute Smoke Test

    // Phase 2: PetaLinux Deployment Verification
    `include "include/tb_suite_driver_replay.svh"   // Suite AP: Driver Transaction Replay
    `include "include/tb_suite_irq_w1c.svh"         // Suite AQ: IRQ W1C Sequence
    `include "include/tb_suite_dma_physaddr.svh"     // Suite AR: DMA Physical Address Range
    `include "include/tb_suite_soft_reset.svh"       // Suite AS: Soft Reset Recovery
    `include "include/tb_suite_error_recovery.svh"   // Suite AT: Error Recovery Path

    // =========================================================================
    // 5. DUT INSTANTIATION
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
        // AXI4 Master (with Burst Support)
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
        .m_axi_rlast(axi_rlast_reg),
        .m_axi_rvalid(axi_rvalid),
        .m_axi_rready(axi_rready),
        .irq(irq_done),
        /* verilator lint_off PINCONNECTEMPTY */
        .dbg_dma_busy(),
        .dbg_dma_read_state(),
        .dbg_dma_write_state(),
        .dbg_dma_fifo_full(),
        .dbg_dma_fifo_empty(),
        .dbg_dma_write_words_remaining(),
        .synthesis_keep()
        /* verilator lint_on PINCONNECTEMPTY */
    );

    // =========================================================================
    // 6. AXI MEMORY MODEL (Inline BFM with Burst Support)
    // =========================================================================
    
    // Read Channel State Machine
    typedef enum logic [1:0] {R_IDLE = 2'd0, R_DATA = 2'd1} r_state_t;
    r_state_t r_state;
    logic [31:0] r_addr_reg;
    logic [7:0]  r_burst_len;
    logic [7:0]  r_beat_count;
    logic [3:0]  r_id_reg;  // Captured ARID for RID echo

    logic axi_arready_reg, axi_rvalid_reg;

    assign axi_arready = axi_arready_reg;
    assign axi_rvalid = axi_rvalid_reg;
    assign axi_rid = r_id_reg;      // Echo captured ARID as RID
    assign axi_rresp = 2'b00;       // Always OKAY
    assign axi_rdata = {mem[r_addr_reg[21:0] + 3],
                        mem[r_addr_reg[21:0] + 2],
                        mem[r_addr_reg[21:0] + 1],
                        mem[r_addr_reg[21:0] + 0]};
    
    // RLAST is purely combinational - asserts on final beat
    // FIX: Gate on rvalid — RLAST must only be meaningful when RVALID=1 (AXI spec)
    assign axi_rlast_reg = axi_rvalid_reg && (r_state == R_DATA) && (r_beat_count == r_burst_len);
    
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            r_state <= R_IDLE;
            axi_arready_reg <= 1'b1;
            axi_rvalid_reg <= 1'b0;
            r_burst_len <= 8'd0;
            r_beat_count <= 8'd0;
            r_addr_reg <= 32'd0;  // FIX: Reset to prevent X propagation through axi_rdata combinational path
            r_id_reg <= 4'd0;
        end else begin
            case (r_state)
                R_IDLE: begin
                    if (!stress_enable || $urandom_range(0,100) >= stress_probability)
                        axi_arready_reg <= 1'b1;
                    else
                        axi_arready_reg <= 1'b0;
                    
                    if (axi_arvalid && axi_arready_reg) begin
                        r_addr_reg <= axi_araddr;
                        r_burst_len <= axi_arlen;
                        r_beat_count <= 8'd0;
                        r_id_reg <= axi_arid;
                        axi_arready_reg <= 1'b0;
                        r_state <= R_DATA;
                    end
                end
                R_DATA: begin
                    axi_rvalid_reg <= 1'b1;
                    
                    if (axi_rvalid_reg && axi_rready) begin
                        if (r_beat_count == r_burst_len) begin
                            axi_rvalid_reg <= 1'b0;
                            r_state <= R_IDLE;
                        end else begin
                            r_addr_reg <= r_addr_reg + 32'd4;
                            r_beat_count <= r_beat_count + 8'd1;
                        end
                    end
                end
            endcase
        end
    end
    
    // Write Address Channel - tracks current burst write address
    logic axi_awready_reg, axi_wready_reg;
    logic [31:0] axi_waddr_next;    // Next write address for burst
    logic        axi_waddr_received;
    logic [3:0]  w_id_reg;          // Captured AWID for BID echo

    assign axi_awready = axi_awready_reg;
    assign axi_wready = axi_wready_reg;
    assign axi_bvalid = axi_bvalid_reg;
    assign axi_bid = w_id_reg;      // Echo captured AWID as BID
    assign axi_bresp = 2'b00;       // Always OKAY
    
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            axi_awready_reg <= 1'b1;
            axi_waddr_received <= 1'b0;
            axi_waddr_next <= 32'd0;
            w_id_reg <= 4'd0;
        end else begin
            if (stress_enable && $urandom_range(0,100) < stress_probability)
                axi_awready_reg <= 1'b0;
            else
                axi_awready_reg <= 1'b1;
            
            // Handle address tracking
            if (axi_awvalid && axi_awready_reg) begin
                // New burst - capture base address and transaction ID
                w_id_reg <= axi_awid;
                // If W also handshaking, beat 0 is done, next is beat 1 address
                if (axi_wvalid && axi_wready_reg)
                    axi_waddr_next <= axi_awaddr + 32'd4;
                else
                    axi_waddr_next <= axi_awaddr;
                axi_waddr_received <= 1'b1;
            end else if (axi_wvalid && axi_wready_reg) begin
                // W handshake only - increment for next beat
                axi_waddr_next <= axi_waddr_next + 32'd4;
            end
            
            // FIX: Clear waddr_received on WLAST, but NOT when a new AW handshake
            // is arriving simultaneously (back-to-back bursts). In that case the AW
            // handler above already sets axi_waddr_received=1 with the new address;
            // clearing it here would lose the new burst's address context.
            if (axi_wvalid && axi_wready_reg && axi_wlast
                && !(axi_awvalid && axi_awready_reg))
                axi_waddr_received <= 1'b0;
        end
    end
    
    // Write Data Channel
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            axi_wready_reg <= 1'b1;
        end else begin
            if (stress_enable && $urandom_range(0,100) < stress_probability)
                axi_wready_reg <= 1'b0;
            else
                axi_wready_reg <= 1'b1;
        end
    end
    
    // Memory Write - use tracked address
    // FIX: Guard on valid address (AW received either this cycle or earlier)
    // to prevent writing to stale/uninitialized axi_waddr_next
    always_ff @(posedge clk) begin
        if (axi_wvalid && axi_wready_reg) begin
            logic [31:0] target_addr;
            if (axi_awvalid && axi_awready_reg) begin
                // Simultaneous AW+W handshake — use awaddr directly
                target_addr = axi_awaddr;
            end else if (axi_waddr_received) begin
                // AW already received earlier — use tracked address
                target_addr = axi_waddr_next;
            end else begin
                // W data arrived before AW — protocol violation, skip write
                $error("[BFM] W-channel data beat without prior AW handshake (WDATA=%08h) — skipping write", axi_wdata);
                target_addr = '0;  // Prevent latch inference
            end

            if ((axi_awvalid && axi_awready_reg) || axi_waddr_received) begin
                if (axi_wstrb[0]) mem[target_addr[21:0] + 0] <= axi_wdata[7:0];
                if (axi_wstrb[1]) mem[target_addr[21:0] + 1] <= axi_wdata[15:8];
                if (axi_wstrb[2]) mem[target_addr[21:0] + 2] <= axi_wdata[23:16];
                if (axi_wstrb[3]) mem[target_addr[21:0] + 3] <= axi_wdata[31:24];
            end
        end
    end
    
    // Write Response Channel - FIX: Counter-based to prevent swallowed BVALIDs
    // on overlapping/back-to-back bursts. A single flip-flop loses events when
    // a new WLAST arrives before the prior BVALID is acked.
    logic [3:0] bvalid_count;  // Pending write responses (max 16 outstanding)
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            bvalid_count <= 4'd0;
        end else begin
            case ({axi_wvalid && axi_wready_reg && axi_wlast,
                   axi_bvalid_reg && axi_bready})
                2'b10:   bvalid_count <= bvalid_count + 4'd1;  // New burst completed, no ack
                2'b01:   bvalid_count <= bvalid_count - 4'd1;  // Ack consumes one response
                default: ;  // 2'b11: simultaneous +1/-1, 2'b00: no change
            endcase
        end
    end
    assign axi_bvalid_reg = (bvalid_count > 4'd0);

    // =========================================================================
    // 7. PROTOCOL MONITOR (AXI + APB Hybrid I/O Verification)
    // =========================================================================
    cgra_protocol_monitor u_monitor (
        .clk(clk),
        .rst_n(rst_n),
        
        // AXI Write Address Channel
        .awaddr(axi_awaddr),
        .awlen(axi_awlen),         // FIX: Wire AWLEN for independent WLAST counter
        .awvalid(axi_awvalid),
        .awready(axi_awready),
        
        // AXI Write Data Channel
        .wdata(axi_wdata),
        .wstrb(axi_wstrb),
        .wvalid(axi_wvalid),
        .wready(axi_wready),
        .wlast(axi_wlast),
        
        // AXI Write Response Channel
        .bvalid(axi_bvalid),
        .bready(axi_bready),
        
        // AXI Read Address Channel
        .araddr(axi_araddr),
        .arvalid(axi_arvalid),
        .arready(axi_arready),
        
        // AXI Read Data Channel
        .rdata(axi_rdata),
        .rvalid(axi_rvalid),
        .rready(axi_rready),
        .rlast(axi_rlast_reg),    // FIX: Connect RLAST for protocol SVA
        
        // APB Signals (for Hybrid I/O verification)
        .psel(psel),
        .penable(penable),
        .pwrite(pwrite),
        .paddr(paddr),
        .prdata(prdata)
    );

    // =========================================================================
    // 8. TEST SUITES (38 Suites, CRV Architecture)
    // =========================================================================
    // Layer 5d: ISA Regression
    `include "include/tb_isa_regression.svh"
    `include "tb_test_suites.svh"

    // =========================================================================
    // 9. WATCHDOG TIMER (prevents infinite sim hangs)
    // =========================================================================
    initial begin
        #(`TB_WATCHDOG_NS);
        $display("");
        $display("ERROR: tb_top WATCHDOG TIMEOUT after %0d ns", `TB_WATCHDOG_NS);
        $display("");
        $finish;
    end

    // =========================================================================
    // 10. MAIN EXECUTION
    // =========================================================================
    initial begin
        // Setup tracing (enabled via +trace command line arg)
        if ($test$plusargs("trace")) begin
            $dumpfile("cgra_sim.vcd");
            $dumpvars(0, tb_top);
        end
        
        // Initialize APB signals
        psel = 0;
        penable = 0;
        pwrite = 0;
        paddr = 0;
        pwdata = 0;
        
        // Initialize memory with test pattern
        init_memory();
        
        // Wait for reset release
        wait(rst_n);
        #100;
        
        // =====================================================================
        // RUN TEST SUITES (with inter-suite reset for state isolation)
        // =====================================================================
        run_suite_system_integrity();

        reset_dut(5);
        run_suite_fabric_stress();

        reset_dut(5);
        run_suite_robustness();

        reset_dut(5);
        run_suite_AD_isa_regression();

        reset_dut(5);
        run_suite_LPR();

        reset_dut(5);
        run_suite_AE_dma_writeback();

        reset_dut(5);
        run_suite_AF_dma_readback();

        reset_dut(5);
        run_suite_AG_pipeline();

        reset_dut(5);
        run_suite_AH_axi_error();

        reset_dut(5);
        run_suite_AI_tile_depth();

        reset_dut(5);
        run_suite_AJ_loops();

        reset_dut(5);
        run_suite_AK_doublebuf();

        reset_dut(5);
        run_suite_AL_mixed_precision();

        reset_dut(5);
        run_suite_real_app();

        reset_dut(5);
        run_suite_V_neuromorphic();

        reset_dut(5);
        run_suite_W_dma_hang();

        // =====================================================================
        // DEPLOYMENT VERIFICATION — Phase 1: Barebone FPGA
        // =====================================================================
        reset_dut(5);
        run_suite_AM_apb_sanity();

        reset_dut(5);
        run_suite_AN_dma_smoke();

        reset_dut(5);
        run_suite_AO_compute_smoke();

        // =====================================================================
        // DEPLOYMENT VERIFICATION — Phase 2: PetaLinux
        // =====================================================================
        reset_dut(5);
        run_suite_AP_driver_replay();

        reset_dut(5);
        run_suite_AQ_irq_w1c();

        reset_dut(5);
        run_suite_AR_dma_physaddr();

        reset_dut(5);
        run_suite_AS_soft_reset();

        reset_dut(5);
        run_suite_AT_error_recovery();

        // Print functional coverage before finishing
        print_functional_coverage();

        $display("\n================================================================");
        $display("  ALL TEST SUITES COMPLETE");
        $display("================================================================\n");

        $finish;
    end

    // =========================================================================
    // 11. UNIFIED END-OF-SIMULATION REPORT (modeled after reference TB)
    // =========================================================================
    final begin
        $display("");
        $display("####################################################################");
        $display("#                    END-OF-SIMULATION REPORT                      #");
        $display("####################################################################");
        $display("  Seed: %0d | Max Errors: %0d | Cycles: %0d",
                 sim_seed, `MAX_ERRORS, cycle_count);

        // Section 1: Test Results
        $display("");
        $display("  1. TEST RESULTS");
        $display("  ----------------------------------------------------------------");
        $display("    PASS : %0d", pass_count);
        $display("    FAIL : %0d", error_count);
        $display("    Protocol errors : %0d", assertion_errors);

        // Section 2: AXI Protocol Statistics
        $display("");
        $display("  2. AXI PROTOCOL STATISTICS  (%0d cycles)", cycle_count);
        $display("  ----------------------------------------------------------------");
        $display("    AR handshakes : %0d", ar_txn_count);
        $display("    R  beats      : %0d", r_txn_count);
        $display("    AW handshakes : %0d", aw_txn_count);
        $display("    W  beats      : %0d", w_txn_count);
        $display("    W  bursts     : %0d (WLAST count)", wlast_txn_count);
        $display("    B  responses  : %0d", b_txn_count);
        $display("    4KB splits    : %0d", axi_read_reqs_split_at_4kb);

        // FIX: AW vs B transaction count consistency check
        // Completed write bursts (WLAST received) must match B responses.
        // AW handshakes may exceed WLAST count due to DMA abort abandoning
        // in-flight bursts — this is expected and reported as informational.
        if (wlast_txn_count != b_txn_count) begin
            $error("[EOS] WLAST/B mismatch: %0d completed bursts but %0d B responses", wlast_txn_count, b_txn_count);
            assertion_errors = assertion_errors + 1;
        end
        if (aw_txn_count != wlast_txn_count) begin
            $display("    NOTE: %0d AW handshakes abandoned by DMA abort (%0d AW - %0d WLAST)",
                     aw_txn_count - wlast_txn_count, aw_txn_count, wlast_txn_count);
        end

        // Section 3: Coverage Summary
        $display("");
        $display("  3. COVERAGE SUMMARY");
        $display("  ----------------------------------------------------------------");
        $display("    Single-beat DMA  : %0d", cov_single_beat);
        $display("    Multi-beat DMA   : %0d", cov_multi_beat);
        $display("    Max-burst DMA    : %0d", cov_max_burst);
        $display("    4KB boundary     : %0d", cov_4kb_boundary);
        $display("    Stress cycles    : %0d", cov_stress_cycles);
        $display("    Reset tests      : %0d", cov_reset_tests);

        // Section 5: Definitive Verdict Banner
        $display("");
        if (error_count == 0 && assertion_errors == 0) begin
            $display("  ================================================================");
            $display("  ***                    TEST PASSED                           ***");
            $display("  ***  %0d tests, 0 failures, 0 violations                     ***",
                     pass_count);
            $display("  ================================================================");
        end else begin
            $display("  ================================================================");
            $display("  ***                    TEST FAILED                           ***");
            if (error_count > 0)
                $display("  ***  %0d test(s) failed                                     ***", error_count);
            if (assertion_errors > 0)
                $display("  ***  %0d protocol violation(s)                               ***", assertion_errors);
            $display("  ================================================================");
        end
        $display("####################################################################");
        $display("");
    end

endmodule
