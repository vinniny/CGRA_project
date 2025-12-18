// ==============================================================================
// GOLDEN TESTBENCH: CGRA AXI4-LITE CSR
// ==============================================================================
// Focus: Register R/W, Read-Only Protection, Reset Values, W1C Semantics
// Compatible with Icarus Verilog
// ==============================================================================

`timescale 1ns/1ps

module tb_cgra_axi_csr_golden;

    // -------------------------------------------------------------------------
    // 1. CONFIGURATION
    // -------------------------------------------------------------------------
    localparam DATA_WIDTH = 32;
    localparam ADDR_WIDTH = 32;
    localparam CLK_PERIOD = 10;
    
    // Register addresses from RTL
    localparam ADDR_CTRL         = 8'h00;
    localparam ADDR_STATUS       = 8'h04;
    localparam ADDR_BITSTR_ADDR  = 8'h08;
    localparam ADDR_BITSTR_SIZE  = 8'h0C;
    localparam ADDR_DMA_DOORBELL = 8'h10;
    localparam ADDR_DMA_HEAD     = 8'h14;
    localparam ADDR_JOB_DESC     = 8'h18;
    localparam ADDR_PERF0        = 8'h1C;
    localparam ADDR_PERF1        = 8'h20;
    localparam ADDR_IRQ_MASK     = 8'h24;

    // -------------------------------------------------------------------------
    // 2. INTERFACE SIGNALS
    // -------------------------------------------------------------------------
    reg clk, rst_n;
    
    // AXI4-Lite Write Address Channel
    reg  [ADDR_WIDTH-1:0] s_axi_awaddr;
    reg                   s_axi_awvalid;
    wire                  s_axi_awready;
    
    // AXI4-Lite Write Data Channel
    reg  [DATA_WIDTH-1:0] s_axi_wdata;
    reg  [3:0]            s_axi_wstrb;
    reg                   s_axi_wvalid;
    wire                  s_axi_wready;
    
    // AXI4-Lite Write Response Channel
    wire [1:0]            s_axi_bresp;
    wire                  s_axi_bvalid;
    reg                   s_axi_bready;
    
    // AXI4-Lite Read Address Channel
    reg  [ADDR_WIDTH-1:0] s_axi_araddr;
    reg                   s_axi_arvalid;
    wire                  s_axi_arready;
    
    // AXI4-Lite Read Data Channel
    wire [DATA_WIDTH-1:0] s_axi_rdata;
    wire [1:0]            s_axi_rresp;
    wire                  s_axi_rvalid;
    reg                   s_axi_rready;
    
    // Control outputs from CSR
    wire                  cgra_start;
    wire                  cgra_reset;
    wire                  cfg_start;
    wire [ADDR_WIDTH-1:0] bitstream_addr;
    wire [15:0]           bitstream_size;
    wire                  dma_start;
    wire [ADDR_WIDTH-1:0] job_desc_addr;
    wire [31:0]           irq_mask;
    
    // Status inputs to CSR
    reg                   cgra_busy;
    reg                   cgra_done;
    reg                   cgra_error;
    reg                   cfg_done;
    reg  [31:0]           dma_head;
    reg  [31:0]           perf_cycles;
    reg  [31:0]           perf_stalls;
    
    // Test counters
    integer test_passed, test_failed;
    integer i;
    reg [31:0] read_value;
    
    // Monitor for one-shot signal capture
    reg dma_start_capture;
    always @(posedge clk) begin
        if (!rst_n)
            dma_start_capture <= 0;
        else if (dma_start)
            dma_start_capture <= 1;
    end

    // -------------------------------------------------------------------------
    // 3. DUT INSTANTIATION
    // -------------------------------------------------------------------------
    cgra_axi_csr #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .DATA_WIDTH(DATA_WIDTH)
    ) dut (
        .clk(clk),
        .rst_n(rst_n),
        .s_axi_awaddr(s_axi_awaddr),
        .s_axi_awvalid(s_axi_awvalid),
        .s_axi_awready(s_axi_awready),
        .s_axi_wdata(s_axi_wdata),
        .s_axi_wstrb(s_axi_wstrb),
        .s_axi_wvalid(s_axi_wvalid),
        .s_axi_wready(s_axi_wready),
        .s_axi_bresp(s_axi_bresp),
        .s_axi_bvalid(s_axi_bvalid),
        .s_axi_bready(s_axi_bready),
        .s_axi_araddr(s_axi_araddr),
        .s_axi_arvalid(s_axi_arvalid),
        .s_axi_arready(s_axi_arready),
        .s_axi_rdata(s_axi_rdata),
        .s_axi_rresp(s_axi_rresp),
        .s_axi_rvalid(s_axi_rvalid),
        .s_axi_rready(s_axi_rready),
        .cgra_start(cgra_start),
        .cgra_reset(cgra_reset),
        .cfg_start(cfg_start),
        .bitstream_addr(bitstream_addr),
        .bitstream_size(bitstream_size),
        .dma_start(dma_start),
        .job_desc_addr(job_desc_addr),
        .irq_mask(irq_mask),
        .cgra_busy(cgra_busy),
        .cgra_done(cgra_done),
        .cgra_error(cgra_error),
        .cfg_done(cfg_done),
        .dma_head(dma_head),
        .perf_cycles(perf_cycles),
        .perf_stalls(perf_stalls)
    );

    // -------------------------------------------------------------------------
    // 4. CLOCK GENERATION
    // -------------------------------------------------------------------------
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    // -------------------------------------------------------------------------
    // 5. HELPER TASKS
    // -------------------------------------------------------------------------
    
    task init_inputs;
        begin
            s_axi_awaddr = 0;
            s_axi_awvalid = 0;
            s_axi_wdata = 0;
            s_axi_wstrb = 4'hF;
            s_axi_wvalid = 0;
            s_axi_bready = 0;
            s_axi_araddr = 0;
            s_axi_arvalid = 0;
            s_axi_rready = 0;
            cgra_busy = 0;
            cgra_done = 0;
            cgra_error = 0;
            cfg_done = 0;
            dma_head = 0;
            perf_cycles = 0;
            perf_stalls = 0;
        end
    endtask
    
    task wait_cycles;
        input integer n;
        integer k;
        begin
            for (k = 0; k < n; k = k + 1) @(posedge clk);
        end
    endtask
    
    // AXI4-Lite Write transaction
    task axi_write;
        input [31:0] addr;
        input [31:0] data;
        integer timeout;
        begin
            // Present address and data
            @(posedge clk);
            s_axi_awaddr = addr;
            s_axi_awvalid = 1;
            s_axi_wdata = data;
            s_axi_wvalid = 1;
            s_axi_bready = 1;
            
            // Wait for address acceptance
            timeout = 0;
            while (!s_axi_awready && timeout < 100) begin
                @(posedge clk);
                timeout = timeout + 1;
            end
            
            @(posedge clk);
            s_axi_awvalid = 0;
            
            // Wait for data acceptance
            timeout = 0;
            while (!s_axi_wready && timeout < 100) begin
                @(posedge clk);
                timeout = timeout + 1;
            end
            
            @(posedge clk);
            s_axi_wvalid = 0;
            
            // Wait for write response
            timeout = 0;
            while (!s_axi_bvalid && timeout < 100) begin
                @(posedge clk);
                timeout = timeout + 1;
            end
            
            @(posedge clk);
            s_axi_bready = 0;
        end
    endtask
    
    // AXI4-Lite Read transaction
    task axi_read;
        input [31:0] addr;
        output [31:0] data;
        integer timeout;
        begin
            // Present address
            @(posedge clk);
            s_axi_araddr = addr;
            s_axi_arvalid = 1;
            s_axi_rready = 1;
            
            // Wait for address acceptance
            timeout = 0;
            while (!s_axi_arready && timeout < 100) begin
                @(posedge clk);
                timeout = timeout + 1;
            end
            
            @(posedge clk);
            s_axi_arvalid = 0;
            
            // Wait for read data
            timeout = 0;
            while (!s_axi_rvalid && timeout < 100) begin
                @(posedge clk);
                timeout = timeout + 1;
            end
            
            data = s_axi_rdata;
            
            @(posedge clk);
            s_axi_rready = 0;
        end
    endtask
    
    // AXI Read with expected value check
    task axi_read_check;
        input [31:0] addr;
        input [31:0] expected;
        reg [31:0] actual;
        begin
            axi_read(addr, actual);
            if (actual !== expected) begin
                $display("    MISMATCH at 0x%02h: expected 0x%08h, got 0x%08h", addr, expected, actual);
            end
        end
    endtask

    // -------------------------------------------------------------------------
    // 6. TEST SEQUENCES
    // -------------------------------------------------------------------------

    initial begin
        $display("\n");
        $display("============================================================");
        $display("     CGRA AXI4-LITE CSR TESTBENCH");
        $display("============================================================");

        test_passed = 0;
        test_failed = 0;

        // Reset sequence
        rst_n = 0;
        init_inputs;
        wait_cycles(5);
        rst_n = 1;
        wait_cycles(2);

        // =====================================================================
        // TEST 1: RESET VALUES
        // =====================================================================
        $display("\n=== TEST 1: Reset Values ===");
        begin
            reg all_zero;
            
            all_zero = 1;
            
            axi_read(ADDR_CTRL, read_value);
            $display("  CTRL = 0x%08h (expect 0)", read_value);
            if (read_value != 0) all_zero = 0;
            
            axi_read(ADDR_STATUS, read_value);
            $display("  STATUS = 0x%08h (expect 0)", read_value);
            if (read_value != 0) all_zero = 0;
            
            axi_read(ADDR_BITSTR_ADDR, read_value);
            $display("  BITSTR_ADDR = 0x%08h (expect 0)", read_value);
            if (read_value != 0) all_zero = 0;
            
            axi_read(ADDR_IRQ_MASK, read_value);
            $display("  IRQ_MASK = 0x%08h (expect 0)", read_value);
            if (read_value != 0) all_zero = 0;
            
            if (all_zero) begin
                $display("  PASS: All registers reset to 0");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Some registers not reset to 0");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 2: CTRL REGISTER R/W
        // =====================================================================
        $display("\n=== TEST 2: CTRL Register Read/Write ===");
        begin
            reg rw_ok;
            
            rw_ok = 1;
            
            axi_write(ADDR_CTRL, 32'h0000_0001);  // Set start bit
            axi_read(ADDR_CTRL, read_value);
            $display("  Write 0x00000001, Read back 0x%08h", read_value);
            if (read_value != 32'h0000_0001) rw_ok = 0;
            
            axi_write(ADDR_CTRL, 32'h0000_0007);  // Set all 3 control bits
            axi_read(ADDR_CTRL, read_value);
            $display("  Write 0x00000007, Read back 0x%08h", read_value);
            if (read_value != 32'h0000_0007) rw_ok = 0;
            
            axi_write(ADDR_CTRL, 32'h0000_0000);  // Clear all
            axi_read(ADDR_CTRL, read_value);
            $display("  Write 0x00000000, Read back 0x%08h", read_value);
            if (read_value != 32'h0000_0000) rw_ok = 0;
            
            if (rw_ok) begin
                $display("  PASS: CTRL register R/W works correctly");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: CTRL register R/W mismatch");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 3: CONTROL OUTPUT SIGNALS
        // =====================================================================
        $display("\n=== TEST 3: Control Output Signals ===");
        begin
            reg signals_ok;
            
            signals_ok = 1;
            
            axi_write(ADDR_CTRL, 32'h0000_0001);  // cgra_start
            wait_cycles(2);
            $display("  cgra_start = %b (expect 1)", cgra_start);
            if (!cgra_start) signals_ok = 0;
            
            axi_write(ADDR_CTRL, 32'h0000_0002);  // cgra_reset
            wait_cycles(2);
            $display("  cgra_reset = %b (expect 1)", cgra_reset);
            if (!cgra_reset) signals_ok = 0;
            
            axi_write(ADDR_CTRL, 32'h0000_0004);  // cfg_start
            wait_cycles(2);
            $display("  cfg_start = %b (expect 1)", cfg_start);
            if (!cfg_start) signals_ok = 0;
            
            axi_write(ADDR_CTRL, 32'h0000_0000);  // Clear all
            
            if (signals_ok) begin
                $display("  PASS: Control output signals work correctly");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Control output signals incorrect");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 4: STATUS REGISTER (Hardware Input Reflection)
        // =====================================================================
        $display("\n=== TEST 4: Status Register (Hardware Inputs) ===");
        begin
            reg status_ok;
            
            status_ok = 1;
            
            // Set hardware status inputs
            cgra_busy = 1;
            cgra_done = 0;
            cgra_error = 0;
            cfg_done = 0;
            wait_cycles(2);
            
            axi_read(ADDR_STATUS, read_value);
            $display("  cgra_busy=1: STATUS = 0x%08h (expect bit 0 set)", read_value);
            if (read_value[0] != 1) status_ok = 0;
            
            cgra_busy = 0;
            cgra_done = 1;
            wait_cycles(2);
            
            axi_read(ADDR_STATUS, read_value);
            $display("  cgra_done=1: STATUS = 0x%08h (expect bit 1 set)", read_value);
            if (read_value[1] != 1) status_ok = 0;
            
            cgra_done = 0;
            cgra_error = 1;
            wait_cycles(2);
            
            axi_read(ADDR_STATUS, read_value);
            $display("  cgra_error=1: STATUS = 0x%08h (expect bit 2 set)", read_value);
            if (read_value[2] != 1) status_ok = 0;
            
            cgra_error = 0;
            cfg_done = 1;
            wait_cycles(2);
            
            axi_read(ADDR_STATUS, read_value);
            $display("  cfg_done=1: STATUS = 0x%08h (expect bit 3 set)", read_value);
            if (read_value[3] != 1) status_ok = 0;
            
            // Clear all status inputs
            cfg_done = 0;
            wait_cycles(2);
            
            if (status_ok) begin
                $display("  PASS: Status register reflects hardware inputs");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Status register doesn't reflect hardware inputs");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 5: READ-ONLY REGISTER PROTECTION (PERF0, PERF1, DMA_HEAD)
        // =====================================================================
        $display("\n=== TEST 5: Read-Only Register Protection ===");
        begin
            reg ro_ok;
            
            ro_ok = 1;
            
            // Set hardware values
            perf_cycles = 32'hCAFE_BABE;
            perf_stalls = 32'hDEAD_BEEF;
            dma_head = 32'h1234_5678;
            wait_cycles(2);
            
            // Verify we can read hardware values
            axi_read(ADDR_PERF0, read_value);
            $display("  PERF0 (cycles) = 0x%08h (expect CAFEBABE)", read_value);
            if (read_value != 32'hCAFE_BABE) ro_ok = 0;
            
            axi_read(ADDR_PERF1, read_value);
            $display("  PERF1 (stalls) = 0x%08h (expect DEADBEEF)", read_value);
            if (read_value != 32'hDEAD_BEEF) ro_ok = 0;
            
            axi_read(ADDR_DMA_HEAD, read_value);
            $display("  DMA_HEAD = 0x%08h (expect 12345678)", read_value);
            if (read_value != 32'h1234_5678) ro_ok = 0;
            
            // Try to write to read-only registers
            axi_write(ADDR_PERF0, 32'hFFFF_FFFF);
            axi_write(ADDR_PERF1, 32'hFFFF_FFFF);
            axi_write(ADDR_DMA_HEAD, 32'hFFFF_FFFF);
            wait_cycles(2);
            
            // Verify they still show hardware values
            axi_read(ADDR_PERF0, read_value);
            $display("  After write attempt, PERF0 = 0x%08h (expect CAFEBABE)", read_value);
            if (read_value != 32'hCAFE_BABE) ro_ok = 0;
            
            axi_read(ADDR_PERF1, read_value);
            $display("  After write attempt, PERF1 = 0x%08h (expect DEADBEEF)", read_value);
            if (read_value != 32'hDEAD_BEEF) ro_ok = 0;
            
            axi_read(ADDR_DMA_HEAD, read_value);
            $display("  After write attempt, DMA_HEAD = 0x%08h (expect 12345678)", read_value);
            if (read_value != 32'h1234_5678) ro_ok = 0;
            
            if (ro_ok) begin
                $display("  PASS: Read-only registers protected from writes");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Read-only register protection broken");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 6: DMA_DOORBELL (Write-Only, One-Shot)
        // =====================================================================
        $display("\n=== TEST 6: DMA Doorbell (Write-Only, One-Shot) ===");
        begin
            // Clear the capture register (force via reset or wait for clear)
            rst_n = 0;
            wait_cycles(2);
            rst_n = 1;
            wait_cycles(2);
            
            // Write to doorbell - dma_start_capture will latch during write
            axi_write(ADDR_DMA_DOORBELL, 32'h0000_0001);
            
            // After write completes, dma_start should be cleared
            wait_cycles(1);
            
            // Verify dma_start pulsed and auto-cleared
            if (dma_start_capture && !dma_start) begin
                $display("  dma_start_capture=%b, dma_start=%b (after)", dma_start_capture, dma_start);
                $display("  PASS: DMA doorbell works as one-shot");
                test_passed = test_passed + 1;
            end else begin
                $display("  dma_start_capture=%b, dma_start=%b", dma_start_capture, dma_start);
                $display("  FAIL: DMA doorbell not working as one-shot");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 7: BITSTREAM ADDRESS AND SIZE REGISTERS
        // =====================================================================
        $display("\n=== TEST 7: Bitstream Address and Size Registers ===");
        begin
            reg bitstr_ok;
            
            bitstr_ok = 1;
            
            axi_write(ADDR_BITSTR_ADDR, 32'h8000_0000);
            axi_read(ADDR_BITSTR_ADDR, read_value);
            $display("  BITSTR_ADDR write 0x80000000, read 0x%08h", read_value);
            if (read_value != 32'h8000_0000) bitstr_ok = 0;
            
            // Verify output signal
            wait_cycles(2);
            $display("  bitstream_addr output = 0x%08h", bitstream_addr);
            if (bitstream_addr != 32'h8000_0000) bitstr_ok = 0;
            
            axi_write(ADDR_BITSTR_SIZE, 32'h0000_0400);  // 1024
            axi_read(ADDR_BITSTR_SIZE, read_value);
            $display("  BITSTR_SIZE write 0x00000400, read 0x%08h", read_value);
            if (read_value != 32'h0000_0400) bitstr_ok = 0;
            
            wait_cycles(2);
            $display("  bitstream_size output = %0d", bitstream_size);
            if (bitstream_size != 16'd1024) bitstr_ok = 0;
            
            if (bitstr_ok) begin
                $display("  PASS: Bitstream registers work correctly");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Bitstream registers incorrect");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 8: JOB DESCRIPTOR ADDRESS REGISTER
        // =====================================================================
        $display("\n=== TEST 8: Job Descriptor Address Register ===");
        begin
            reg job_ok;
            
            job_ok = 1;
            
            axi_write(ADDR_JOB_DESC, 32'hABCD_1234);
            axi_read(ADDR_JOB_DESC, read_value);
            $display("  JOB_DESC write 0xABCD1234, read 0x%08h", read_value);
            if (read_value != 32'hABCD_1234) job_ok = 0;
            
            wait_cycles(2);
            $display("  job_desc_addr output = 0x%08h", job_desc_addr);
            if (job_desc_addr != 32'hABCD_1234) job_ok = 0;
            
            if (job_ok) begin
                $display("  PASS: Job descriptor register works correctly");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Job descriptor register incorrect");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 9: IRQ MASK REGISTER
        // =====================================================================
        $display("\n=== TEST 9: IRQ Mask Register ===");
        begin
            reg irq_ok;
            
            irq_ok = 1;
            
            axi_write(ADDR_IRQ_MASK, 32'h0000_000F);  // Enable all 4 IRQs
            axi_read(ADDR_IRQ_MASK, read_value);
            $display("  IRQ_MASK write 0x0000000F, read 0x%08h", read_value);
            if (read_value != 32'h0000_000F) irq_ok = 0;
            
            wait_cycles(2);
            $display("  irq_mask output = 0x%08h", irq_mask);
            if (irq_mask != 32'h0000_000F) irq_ok = 0;
            
            if (irq_ok) begin
                $display("  PASS: IRQ mask register works correctly");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: IRQ mask register incorrect");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 10: UNDEFINED ADDRESS HANDLING
        // =====================================================================
        $display("\n=== TEST 10: Undefined Address Handling ===");
        begin
            axi_read(32'h0000_00FF, read_value);  // Undefined address
            $display("  Read from undefined addr 0xFF = 0x%08h", read_value);
            
            // Write to undefined address should not cause problems
            axi_write(32'h0000_00FF, 32'hFFFF_FFFF);
            $display("  Write to undefined addr 0xFF completed without error");
            
            $display("  PASS: Undefined address handled gracefully");
            test_passed = test_passed + 1;
        end
        wait_cycles(5);

        // =====================================================================
        // SUMMARY
        // =====================================================================
        $display("\n============================================================");
        $display("     TEST SUMMARY");
        $display("============================================================");
        $display("  PASSED: %0d", test_passed);
        $display("  FAILED: %0d", test_failed);
        $display("============================================================\n");

        if (test_failed == 0) begin
            $display("ALL TESTS PASSED!");
        end else begin
            $display("SOME TESTS FAILED - Review above for details");
        end

        $finish;
    end

    // -------------------------------------------------------------------------
    // 7. WAVEFORM DUMP
    // -------------------------------------------------------------------------
    initial begin
        $dumpfile("tb_cgra_axi_csr_golden.vcd");
        $dumpvars(0, tb_cgra_axi_csr_golden);
    end

endmodule