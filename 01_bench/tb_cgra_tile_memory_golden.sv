// ==============================================================================
// GOLDEN TESTBENCH: CGRA TILE MEMORY
// ==============================================================================
// Focus: SRAM Read/Write, Data Retention, Banking Logic, Parallel Access
// Compatible with Icarus Verilog
// ==============================================================================

`timescale 1ns/1ps

module tb_cgra_tile_memory_golden;

    // -------------------------------------------------------------------------
    // 1. CONFIGURATION
    // -------------------------------------------------------------------------
    localparam DATA_WIDTH = 32;
    localparam ADDR_WIDTH = 12;
    localparam BANK_DEPTH = 1024;
    localparam NUM_BANKS = 4;
    localparam CLK_PERIOD = 10;

    // -------------------------------------------------------------------------
    // 2. INTERFACE SIGNALS
    // -------------------------------------------------------------------------
    reg clk, rst_n;
    
    // Bank 0 interface
    reg  [ADDR_WIDTH-1:0] bank0_addr;
    reg                   bank0_read;
    reg                   bank0_write;
    reg  [DATA_WIDTH-1:0] bank0_wdata;
    wire [DATA_WIDTH-1:0] bank0_rdata;
    wire                  bank0_valid;
    
    // Bank 1 interface
    reg  [ADDR_WIDTH-1:0] bank1_addr;
    reg                   bank1_read;
    reg                   bank1_write;
    reg  [DATA_WIDTH-1:0] bank1_wdata;
    wire [DATA_WIDTH-1:0] bank1_rdata;
    wire                  bank1_valid;
    
    // Bank 2 interface
    reg  [ADDR_WIDTH-1:0] bank2_addr;
    reg                   bank2_read;
    reg                   bank2_write;
    reg  [DATA_WIDTH-1:0] bank2_wdata;
    wire [DATA_WIDTH-1:0] bank2_rdata;
    wire                  bank2_valid;
    
    // Bank 3 interface
    reg  [ADDR_WIDTH-1:0] bank3_addr;
    reg                   bank3_read;
    reg                   bank3_write;
    reg  [DATA_WIDTH-1:0] bank3_wdata;
    wire [DATA_WIDTH-1:0] bank3_rdata;
    wire                  bank3_valid;
    
    // External (DMA) interface
    reg  [ADDR_WIDTH-1:0] ext_addr;
    reg  [1:0]            ext_bank_sel;
    reg                   ext_read;
    reg                   ext_write;
    reg  [DATA_WIDTH-1:0] ext_wdata;
    wire [DATA_WIDTH-1:0] ext_rdata;
    wire                  ext_valid;
    
    // Test counters
    integer test_passed, test_failed;
    integer i, j;
    reg [DATA_WIDTH-1:0] test_pattern [0:15];

    // -------------------------------------------------------------------------
    // 3. DUT INSTANTIATION
    // -------------------------------------------------------------------------
    cgra_tile_memory #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .BANK_DEPTH(BANK_DEPTH),
        .NUM_BANKS(NUM_BANKS)
    ) dut (
        .clk(clk),
        .rst_n(rst_n),
        .bank0_addr(bank0_addr),
        .bank0_read(bank0_read),
        .bank0_write(bank0_write),
        .bank0_wdata(bank0_wdata),
        .bank0_rdata(bank0_rdata),
        .bank0_valid(bank0_valid),
        .bank1_addr(bank1_addr),
        .bank1_read(bank1_read),
        .bank1_write(bank1_write),
        .bank1_wdata(bank1_wdata),
        .bank1_rdata(bank1_rdata),
        .bank1_valid(bank1_valid),
        .bank2_addr(bank2_addr),
        .bank2_read(bank2_read),
        .bank2_write(bank2_write),
        .bank2_wdata(bank2_wdata),
        .bank2_rdata(bank2_rdata),
        .bank2_valid(bank2_valid),
        .bank3_addr(bank3_addr),
        .bank3_read(bank3_read),
        .bank3_write(bank3_write),
        .bank3_wdata(bank3_wdata),
        .bank3_rdata(bank3_rdata),
        .bank3_valid(bank3_valid),
        .ext_addr(ext_addr),
        .ext_bank_sel(ext_bank_sel),
        .ext_read(ext_read),
        .ext_write(ext_write),
        .ext_wdata(ext_wdata),
        .ext_rdata(ext_rdata),
        .ext_valid(ext_valid)
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
            bank0_addr = 0; bank0_read = 0; bank0_write = 0; bank0_wdata = 0;
            bank1_addr = 0; bank1_read = 0; bank1_write = 0; bank1_wdata = 0;
            bank2_addr = 0; bank2_read = 0; bank2_write = 0; bank2_wdata = 0;
            bank3_addr = 0; bank3_read = 0; bank3_write = 0; bank3_wdata = 0;
            ext_addr = 0; ext_bank_sel = 0; ext_read = 0; ext_write = 0; ext_wdata = 0;
        end
    endtask
    
    task wait_cycles;
        input integer n;
        integer k;
        begin
            for (k = 0; k < n; k = k + 1) @(posedge clk);
        end
    endtask
    
    // Bank 0 write
    task bank0_write_word;
        input [ADDR_WIDTH-1:0] addr;
        input [DATA_WIDTH-1:0] data;
        begin
            @(posedge clk);
            bank0_addr = addr;
            bank0_wdata = data;
            bank0_write = 1;
            @(posedge clk);
            bank0_write = 0;
        end
    endtask
    
    // Bank 0 read (waits for valid)
    task bank0_read_word;
        input [ADDR_WIDTH-1:0] addr;
        output [DATA_WIDTH-1:0] data;
        begin
            @(posedge clk);
            bank0_addr = addr;
            bank0_read = 1;
            @(posedge clk);
            bank0_read = 0;
            // Data available after 1-cycle latency
            data = bank0_rdata;
        end
    endtask
    
    // External port write
    task ext_write_word;
        input [1:0] bank;
        input [ADDR_WIDTH-1:0] addr;
        input [DATA_WIDTH-1:0] data;
        begin
            @(posedge clk);
            ext_bank_sel = bank;
            ext_addr = addr;
            ext_wdata = data;
            ext_write = 1;
            @(posedge clk);
            ext_write = 0;
        end
    endtask
    
    // External port read
    task ext_read_word;
        input [1:0] bank;
        input [ADDR_WIDTH-1:0] addr;
        output [DATA_WIDTH-1:0] data;
        begin
            @(posedge clk);
            ext_bank_sel = bank;
            ext_addr = addr;
            ext_read = 1;
            @(posedge clk);
            ext_read = 0;
            data = ext_rdata;
        end
    endtask

    // -------------------------------------------------------------------------
    // 6. TEST SEQUENCES
    // -------------------------------------------------------------------------

    initial begin
        $display("\n");
        $display("============================================================");
        $display("     CGRA TILE MEMORY TESTBENCH");
        $display("============================================================");

        test_passed = 0;
        test_failed = 0;

        // Initialize test patterns
        for (i = 0; i < 16; i = i + 1) begin
            test_pattern[i] = 32'hDEAD_0000 + i;
        end

        // Reset sequence
        rst_n = 0;
        init_inputs;
        wait_cycles(5);
        rst_n = 1;
        wait_cycles(2);

        // =====================================================================
        // TEST 1: BANK 0 BASIC WRITE AND READ
        // =====================================================================
        $display("\n=== TEST 1: Bank 0 Basic Write and Read ===");
        begin
            reg test_ok;
            reg [DATA_WIDTH-1:0] rd_data;
            
            test_ok = 1;
            
            // Write to address 0
            bank0_write_word(12'd0, 32'hCAFE_BABE);
            
            // Read back
            bank0_read_word(12'd0, rd_data);
            $display("  Wrote 0xCAFEBABE, Read back 0x%08h", rd_data);
            if (rd_data != 32'hCAFE_BABE) test_ok = 0;
            
            // Write to another address
            bank0_write_word(12'd100, 32'h1234_5678);
            bank0_read_word(12'd100, rd_data);
            $display("  Wrote 0x12345678, Read back 0x%08h", rd_data);
            if (rd_data != 32'h1234_5678) test_ok = 0;
            
            if (test_ok) begin
                $display("  PASS: Bank 0 basic R/W works correctly");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Bank 0 basic R/W failed");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 2: READ LATENCY CHECK (1 CYCLE)
        // =====================================================================
        $display("\n=== TEST 2: Read Latency Check (1 Cycle) ===");
        begin
            reg valid_seen;
            
            // Write a known value
            bank0_write_word(12'd10, 32'hDEAD_BEEF);
            
            // Initiate read
            @(posedge clk);
            bank0_addr = 12'd10;
            bank0_read = 1;
            
            // Check valid is NOT asserted on same cycle
            if (bank0_valid) begin
                $display("  FAIL: valid asserted too early (same cycle)");
                test_failed = test_failed + 1;
            end else begin
                // Check valid IS asserted next cycle
                @(posedge clk);
                bank0_read = 0;
                
                if (bank0_valid && bank0_rdata == 32'hDEAD_BEEF) begin
                    $display("  PASS: 1-cycle read latency verified");
                    test_passed = test_passed + 1;
                end else begin
                    $display("  FAIL: valid=%b, rdata=0x%08h", bank0_valid, bank0_rdata);
                    test_failed = test_failed + 1;
                end
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 3: MULTIPLE BANKS INDEPENDENCE
        // =====================================================================
        $display("\n=== TEST 3: Multiple Banks Independence ===");
        begin
            reg test_ok;
            reg [DATA_WIDTH-1:0] rd0, rd1, rd2, rd3;
            
            test_ok = 1;
            
            // Write different values to same address in each bank
            bank0_write_word(12'd50, 32'hAAAA_0000);
            bank1_write_word(12'd50, 32'hBBBB_1111);
            bank2_write_word(12'd50, 32'hCCCC_2222);
            bank3_write_word(12'd50, 32'hDDDD_3333);
            
            // Read back from each bank
            bank0_read_word(12'd50, rd0);
            bank1_read_word(12'd50, rd1);
            bank2_read_word(12'd50, rd2);
            bank3_read_word(12'd50, rd3);
            
            $display("  Bank0[50] = 0x%08h (expect AAAA0000)", rd0);
            $display("  Bank1[50] = 0x%08h (expect BBBB1111)", rd1);
            $display("  Bank2[50] = 0x%08h (expect CCCC2222)", rd2);
            $display("  Bank3[50] = 0x%08h (expect DDDD3333)", rd3);
            
            if (rd0 != 32'hAAAA_0000) test_ok = 0;
            if (rd1 != 32'hBBBB_1111) test_ok = 0;
            if (rd2 != 32'hCCCC_2222) test_ok = 0;
            if (rd3 != 32'hDDDD_3333) test_ok = 0;
            
            if (test_ok) begin
                $display("  PASS: All banks are independent");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Banks are NOT independent");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 4: PARALLEL BANK ACCESS
        // =====================================================================
        $display("\n=== TEST 4: Parallel Bank Access ===");
        begin
            reg test_ok;
            
            test_ok = 1;
            
            // Write to all banks simultaneously
            @(posedge clk);
            bank0_addr = 12'd200; bank0_wdata = 32'h1111_1111; bank0_write = 1;
            bank1_addr = 12'd200; bank1_wdata = 32'h2222_2222; bank1_write = 1;
            bank2_addr = 12'd200; bank2_wdata = 32'h3333_3333; bank2_write = 1;
            bank3_addr = 12'd200; bank3_wdata = 32'h4444_4444; bank3_write = 1;
            
            @(posedge clk);
            bank0_write = 0; bank1_write = 0; bank2_write = 0; bank3_write = 0;
            
            // Read from all banks simultaneously
            @(posedge clk);
            bank0_addr = 12'd200; bank0_read = 1;
            bank1_addr = 12'd200; bank1_read = 1;
            bank2_addr = 12'd200; bank2_read = 1;
            bank3_addr = 12'd200; bank3_read = 1;
            
            @(posedge clk);
            bank0_read = 0; bank1_read = 0; bank2_read = 0; bank3_read = 0;
            
            // Check all valids and data
            if (bank0_valid && bank0_rdata == 32'h1111_1111 &&
                bank1_valid && bank1_rdata == 32'h2222_2222 &&
                bank2_valid && bank2_rdata == 32'h3333_3333 &&
                bank3_valid && bank3_rdata == 32'h4444_4444) begin
                $display("  PASS: Parallel access to all 4 banks works");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Parallel access failed");
                $display("    Bank0: valid=%b data=0x%08h", bank0_valid, bank0_rdata);
                $display("    Bank1: valid=%b data=0x%08h", bank1_valid, bank1_rdata);
                $display("    Bank2: valid=%b data=0x%08h", bank2_valid, bank2_rdata);
                $display("    Bank3: valid=%b data=0x%08h", bank3_valid, bank3_rdata);
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 5: EXTERNAL PORT WRITE/READ
        // =====================================================================
        $display("\n=== TEST 5: External Port Write/Read ===");
        begin
            reg test_ok;
            reg [DATA_WIDTH-1:0] rd_data;
            
            test_ok = 1;
            
            // Write via external port to each bank
            ext_write_word(2'd0, 12'd300, 32'hE0E0_0000);
            ext_write_word(2'd1, 12'd300, 32'hE1E1_1111);
            ext_write_word(2'd2, 12'd300, 32'hE2E2_2222);
            ext_write_word(2'd3, 12'd300, 32'hE3E3_3333);
            
            // Read via external port
            ext_read_word(2'd0, 12'd300, rd_data);
            $display("  Ext read bank0[300] = 0x%08h (expect E0E00000)", rd_data);
            if (rd_data != 32'hE0E0_0000) test_ok = 0;
            
            ext_read_word(2'd1, 12'd300, rd_data);
            $display("  Ext read bank1[300] = 0x%08h (expect E1E11111)", rd_data);
            if (rd_data != 32'hE1E1_1111) test_ok = 0;
            
            ext_read_word(2'd2, 12'd300, rd_data);
            $display("  Ext read bank2[300] = 0x%08h (expect E2E22222)", rd_data);
            if (rd_data != 32'hE2E2_2222) test_ok = 0;
            
            ext_read_word(2'd3, 12'd300, rd_data);
            $display("  Ext read bank3[300] = 0x%08h (expect E3E33333)", rd_data);
            if (rd_data != 32'hE3E3_3333) test_ok = 0;
            
            if (test_ok) begin
                $display("  PASS: External port R/W works for all banks");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: External port R/W failed");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 6: EXTERNAL WRITE, LOCAL READ (Cross-port Access)
        // =====================================================================
        $display("\n=== TEST 6: External Write, Local Read ===");
        begin
            reg test_ok;
            reg [DATA_WIDTH-1:0] rd_data;
            
            test_ok = 1;
            
            // Write via external port
            ext_write_word(2'd0, 12'd400, 32'hC0C0_AAEE);
            
            // Read via local bank port
            bank0_read_word(12'd400, rd_data);
            $display("  Ext wrote 0xC0C0AAEE to bank0[400]");
            $display("  Local read bank0[400] = 0x%08h", rd_data);
            
            if (rd_data == 32'hC0C0_AAEE) begin
                $display("  PASS: Cross-port access works");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Cross-port access failed");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 7: DATA RETENTION AFTER MULTIPLE OPERATIONS
        // =====================================================================
        $display("\n=== TEST 7: Data Retention ===");
        begin
            reg test_ok;
            reg [DATA_WIDTH-1:0] rd_data;
            
            test_ok = 1;
            
            // Write 16 values to bank 0
            for (i = 0; i < 16; i = i + 1) begin
                bank0_write_word(i, test_pattern[i]);
            end
            
            // Perform unrelated operations on other banks
            for (i = 0; i < 10; i = i + 1) begin
                bank1_write_word(i, 32'hFFFF_FFFF);
                bank2_write_word(i, 32'h0000_0000);
            end
            
            // Read back original values from bank 0
            for (i = 0; i < 16; i = i + 1) begin
                bank0_read_word(i, rd_data);
                if (rd_data != test_pattern[i]) begin
                    $display("    Mismatch at addr %0d: exp 0x%08h, got 0x%08h", i, test_pattern[i], rd_data);
                    test_ok = 0;
                end
            end
            
            if (test_ok) begin
                $display("  PASS: Data retained across operations");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Data retention failed");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 8: ADDRESS BOUNDARY (LAST ADDRESS)
        // =====================================================================
        $display("\n=== TEST 8: Address Boundary ===");
        begin
            reg test_ok;
            reg [DATA_WIDTH-1:0] rd_data;
            
            test_ok = 1;
            
            // Write to last address in bank
            bank0_write_word(BANK_DEPTH - 1, 32'hADD0_FFFE);
            bank0_read_word(BANK_DEPTH - 1, rd_data);
            $display("  bank0[%0d] = 0x%08h (expect ADD0FFFE)", BANK_DEPTH-1, rd_data);
            
            if (rd_data == 32'hADD0_FFFE) begin
                $display("  PASS: Last address accessible");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Last address access failed");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 9: VALID SIGNAL BEHAVIOR
        // =====================================================================
        $display("\n=== TEST 9: Valid Signal Behavior ===");
        begin
            reg test_ok;
            
            test_ok = 1;
            
            // Ensure no read is pending
            init_inputs;
            wait_cycles(2);
            
            // Valid should be 0 when not reading
            if (bank0_valid != 0) begin
                $display("  FAIL: valid should be 0 when not reading");
                test_ok = 0;
            end
            
            // Initiate read
            @(posedge clk);
            bank0_addr = 12'd0;
            bank0_read = 1;
            @(posedge clk);
            bank0_read = 0;
            
            // Valid should be 1
            if (bank0_valid != 1) begin
                $display("  FAIL: valid should be 1 after read");
                test_ok = 0;
            end
            
            // Wait one cycle, valid should go back to 0
            // Expected: valid deasserts after read deassertion
            // Note: #1 delay allows NBA to settle before sampling registered output
            @(posedge clk);
            #1;
            if (bank0_valid != 0) begin
                $display("  FAIL: valid should return to 0 (RTL bug: valid stays high too long)");
                test_ok = 0;
            end
            
            if (test_ok) begin
                $display("  PASS: Valid signal behaves correctly");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: Valid signal behavior incorrect");
                test_failed = test_failed + 1;
            end
        end
        wait_cycles(5);

        // =====================================================================
        // TEST 10: EXT_VALID SIGNAL BEHAVIOR
        // =====================================================================
        $display("\n=== TEST 10: External Valid Signal Behavior ===");
        begin
            reg test_ok;
            
            test_ok = 1;
            
            init_inputs;
            wait_cycles(2);
            
            // ext_valid should be 0 when not reading
            if (ext_valid != 0) begin
                $display("  FAIL: ext_valid should be 0 when not reading");
                test_ok = 0;
            end
            
            // Initiate read via external port
            @(posedge clk);
            ext_bank_sel = 2'd0;
            ext_addr = 12'd0;
            ext_read = 1;
            @(posedge clk);
            ext_read = 0;
            
            // ext_valid should be 1
            if (ext_valid != 1) begin
                $display("  FAIL: ext_valid should be 1 after read");
                test_ok = 0;
            end
            
            // Wait one cycle, ext_valid should go back to 0
            // Expected: ext_valid deasserts after read deassertion
            // Note: #1 delay allows NBA to settle before sampling registered output
            @(posedge clk);
            #1;
            if (ext_valid != 0) begin
                $display("  FAIL: ext_valid should return to 0 (RTL bug: ext_valid stays high too long)");
                test_ok = 0;
            end
            
            if (test_ok) begin
                $display("  PASS: External valid signal behaves correctly");
                test_passed = test_passed + 1;
            end else begin
                $display("  FAIL: External valid signal behavior incorrect");
                test_failed = test_failed + 1;
            end
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
        $dumpfile("tb_cgra_tile_memory_golden.vcd");
        $dumpvars(0, tb_cgra_tile_memory_golden);
    end

    // Helper tasks for bank1, bank2, bank3 similar to bank0
    task bank1_write_word;
        input [ADDR_WIDTH-1:0] addr;
        input [DATA_WIDTH-1:0] data;
        begin
            @(posedge clk);
            bank1_addr = addr;
            bank1_wdata = data;
            bank1_write = 1;
            @(posedge clk);
            bank1_write = 0;
        end
    endtask
    
    task bank1_read_word;
        input [ADDR_WIDTH-1:0] addr;
        output [DATA_WIDTH-1:0] data;
        begin
            @(posedge clk);
            bank1_addr = addr;
            bank1_read = 1;
            @(posedge clk);
            bank1_read = 0;
            data = bank1_rdata;
        end
    endtask
    
    task bank2_write_word;
        input [ADDR_WIDTH-1:0] addr;
        input [DATA_WIDTH-1:0] data;
        begin
            @(posedge clk);
            bank2_addr = addr;
            bank2_wdata = data;
            bank2_write = 1;
            @(posedge clk);
            bank2_write = 0;
        end
    endtask
    
    task bank2_read_word;
        input [ADDR_WIDTH-1:0] addr;
        output [DATA_WIDTH-1:0] data;
        begin
            @(posedge clk);
            bank2_addr = addr;
            bank2_read = 1;
            @(posedge clk);
            bank2_read = 0;
            data = bank2_rdata;
        end
    endtask
    
    task bank3_write_word;
        input [ADDR_WIDTH-1:0] addr;
        input [DATA_WIDTH-1:0] data;
        begin
            @(posedge clk);
            bank3_addr = addr;
            bank3_wdata = data;
            bank3_write = 1;
            @(posedge clk);
            bank3_write = 0;
        end
    endtask
    
    task bank3_read_word;
        input [ADDR_WIDTH-1:0] addr;
        output [DATA_WIDTH-1:0] data;
        begin
            @(posedge clk);
            bank3_addr = addr;
            bank3_read = 1;
            @(posedge clk);
            bank3_read = 0;
            data = bank3_rdata;
        end
    endtask

endmodule