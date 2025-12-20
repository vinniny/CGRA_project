// ==============================================================================
// CGRA Unified Master Testbench - The Harness
// ==============================================================================
// Consolidates all verification logic into a single, layered environment:
// - Suite A: Register Logic (from tb_cgra_axi_csr_golden)
// - Suite B: DMA Datapath (from tb_dma_axi_ram)
// - Suite C: Performance (new cycle-accurate)
// - Suite D: Protocol Compliance (cgra_protocol_monitor)
// - Suite E: Stress Testing (new torture tests)
// - Suite F: System Integration (from tb_pe_array_direct)
// ==============================================================================

`timescale 1ns/1ps

module tb_top;

    // =========================================================================
    // 1. SIGNAL DECLARATIONS
    // =========================================================================
    reg clk, rst_n;
    
    // APB Signals (Driven by Tasks)
    reg         psel, penable, pwrite;
    reg  [31:0] paddr, pwdata;
    wire [31:0] prdata;
    wire        pready, pslverr;

    // AXI Signals (DUT <-> Memory)
    wire [31:0] axi_awaddr, axi_wdata, axi_araddr, axi_rdata;
    wire        axi_awvalid, axi_awready, axi_wvalid, axi_wready;
    wire        axi_arvalid, axi_arready, axi_rvalid, axi_rready;
    wire [3:0]  axi_wstrb;
    wire        axi_bvalid, axi_bready;
    reg         axi_bvalid_reg;

    wire        irq_done;

    // Reporting
    integer error_count = 0;
    integer pass_count = 0;
    integer cycle_count = 0;

    // Memory Model (128KB)
    localparam MEM_SIZE = 128 * 1024;
    reg [7:0] mem [0:MEM_SIZE-1];

    // Stress Control
    reg         stress_enable = 0;
    integer     stress_probability = 0;
    
    // =========================================================================
    // 2. CLOCK & RESET
    // =========================================================================
    always #5 clk = ~clk;  // 100 MHz Clock
    always @(posedge clk) cycle_count = cycle_count + 1;

    initial begin
        clk = 0;
        rst_n = 0;
        psel = 0;
        penable = 0;
        pwrite = 0;
        paddr = 0;
        pwdata = 0;
        #50 rst_n = 1;
    end

    // =========================================================================
    // 3. DUT INSTANTIATION
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
        .m_axi_awaddr(axi_awaddr),
        .m_axi_awvalid(axi_awvalid),
        .m_axi_awready(axi_awready),
        .m_axi_wdata(axi_wdata),
        .m_axi_wstrb(axi_wstrb),
        .m_axi_wvalid(axi_wvalid),
        .m_axi_wready(axi_wready),
        .m_axi_bvalid(axi_bvalid),
        .m_axi_bready(axi_bready),
        .m_axi_araddr(axi_araddr),
        .m_axi_arvalid(axi_arvalid),
        .m_axi_arready(axi_arready),
        .m_axi_rdata(axi_rdata),
        .m_axi_rvalid(axi_rvalid),
        .m_axi_rready(axi_rready),
        .irq(irq_done)
    );

    // =========================================================================
    // 4. PROTOCOL MONITOR INSTANTIATION
    // =========================================================================
    cgra_protocol_monitor u_mon (
        .clk(clk),
        .rst_n(rst_n),
        .awaddr(axi_awaddr),
        .awvalid(axi_awvalid),
        .awready(axi_awready),
        .wdata(axi_wdata),
        .wstrb(axi_wstrb),
        .wvalid(axi_wvalid),
        .wready(axi_wready),
        .araddr(axi_araddr),
        .arvalid(axi_arvalid),
        .arready(axi_arready),
        .rdata(axi_rdata),
        .rvalid(axi_rvalid),
        .rready(axi_rready)
    );

    // =========================================================================
    // 5. AXI MEMORY MODEL (with Stress Support)
    // =========================================================================
    
    // Read Channel State Machine
    reg [1:0] r_state;
    reg [31:0] r_addr_reg;
    localparam R_IDLE = 0, R_DATA = 1;
    
    reg axi_arready_reg, axi_rvalid_reg;
    reg [31:0] axi_rdata_reg;
    
    assign axi_arready = axi_arready_reg;
    assign axi_rvalid = axi_rvalid_reg;
    assign axi_rdata = axi_rdata_reg;
    
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            r_state <= R_IDLE;
            axi_arready_reg <= 1'b1;
            axi_rvalid_reg <= 1'b0;
            axi_rdata_reg <= 32'd0;
        end else begin
            case (r_state)
                R_IDLE: begin
                    if (!stress_enable || $urandom_range(0,100) >= stress_probability)
                        axi_arready_reg <= 1'b1;
                    else
                        axi_arready_reg <= 1'b0;
                    
                    if (axi_arvalid && axi_arready_reg) begin
                        r_addr_reg <= axi_araddr;
                        axi_arready_reg <= 1'b0;
                        r_state <= R_DATA;
                    end
                end
                R_DATA: begin
                    axi_rdata_reg <= {mem[r_addr_reg[16:0] + 3],
                                      mem[r_addr_reg[16:0] + 2],
                                      mem[r_addr_reg[16:0] + 1],
                                      mem[r_addr_reg[16:0] + 0]};
                    axi_rvalid_reg <= 1'b1;
                    if (axi_rvalid_reg && axi_rready) begin
                        axi_rvalid_reg <= 1'b0;
                        r_state <= R_IDLE;
                    end
                end
            endcase
        end
    end
    
    // Write Channel with stress support
    reg axi_awready_reg, axi_wready_reg;
    assign axi_awready = axi_awready_reg;
    assign axi_wready = axi_wready_reg;
    assign axi_bvalid = axi_bvalid_reg;
    
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            axi_awready_reg <= 1'b1;
            axi_wready_reg <= 1'b1;
        end else begin
            if (stress_enable && $urandom_range(0,100) < stress_probability) begin
                axi_awready_reg <= 1'b0;
                axi_wready_reg <= 1'b0;
            end else begin
                axi_awready_reg <= 1'b1;
                axi_wready_reg <= 1'b1;
            end
        end
    end
    
    // B channel response
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            axi_bvalid_reg <= 1'b0;
        end else begin
            if (axi_wvalid && axi_wready_reg) begin
                axi_bvalid_reg <= 1'b1;
            end else if (axi_bvalid_reg && axi_bready) begin
                axi_bvalid_reg <= 1'b0;
            end
        end
    end
    
    // Memory write
    always @(posedge clk) begin
        if (axi_wvalid && axi_wready_reg) begin
            if (axi_wstrb[0]) mem[axi_awaddr[16:0] + 0] <= axi_wdata[7:0];
            if (axi_wstrb[1]) mem[axi_awaddr[16:0] + 1] <= axi_wdata[15:8];
            if (axi_wstrb[2]) mem[axi_awaddr[16:0] + 2] <= axi_wdata[23:16];
            if (axi_wstrb[3]) mem[axi_awaddr[16:0] + 3] <= axi_wdata[31:24];
        end
    end

    // =========================================================================
    // 6. INCLUDE MODULAR TEST LAYERS
    // =========================================================================
    `include "tb_tasks.svh"
    `include "tb_test_suites.svh"

    // =========================================================================
    // 7. MAIN EXECUTION
    // =========================================================================
    initial begin
        $dumpfile("cgra_master_sim.vcd");
        $dumpvars(0, tb_top);
        
        // Initialize memory with test pattern
        init_memory();
        
        wait(rst_n);
        #100;
        
        $display("\n");
        $display("================================================================");
        $display("  CGRA MASTER VERIFICATION - 77+ VECTOR SUITE");
        $display("================================================================");

        // === EXECUTE ALL SUITES ===
        run_suite_A_regs();       // Register Logic & Config (16 vectors)
        run_suite_B_dma();        // DMA Datapath & Segmentation (16 vectors)
        run_suite_C_protocol();   // Protocol Compliance (15 vectors)
        run_suite_D_perf();       // Performance & Timing (10 vectors)
        run_suite_E_stress();     // Stress Testing (10 vectors)
        run_suite_F_system();     // System Integration (10 vectors)

        // === FINAL REPORT ===
        $display("\n================================================================");
        $display("  FINAL RESULTS");
        $display("================================================================");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", error_count);
        $display("  TOTAL:  %0d", pass_count + error_count);
        $display("================================================================");
        
        if (error_count == 0)
            $display("\n  *** STATUS: PASSED (All Suites) - SILICON READY ***\n");
        else
            $display("\n  *** STATUS: FAILED (%0d Errors) - REVIEW REQUIRED ***\n", error_count);
        
        $finish;
    end

endmodule
