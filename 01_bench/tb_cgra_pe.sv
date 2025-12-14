// ==============================================================================
// Testbench for CGRA Processing Element (PE)
// ==============================================================================

`timescale 1ns/1ps

module tb_cgra_pe;

    // Parameters
    localparam DATA_WIDTH = 16;
    localparam ADDR_WIDTH = 8;
    localparam SPM_DEPTH = 256;
    localparam RF_DEPTH = 16;
    localparam CLK_PERIOD = 10;
    
    // DUT signals
    logic clk;
    logic rst_n;
    logic [63:0] config_frame;
    logic        config_valid;
    logic [DATA_WIDTH-1:0] data_in_n, data_in_e, data_in_s, data_in_w;
    logic valid_in_n, valid_in_e, valid_in_s, valid_in_w;
    logic [DATA_WIDTH-1:0] data_out_n, data_out_e, data_out_s, data_out_w;
    logic valid_out_n, valid_out_e, valid_out_s, valid_out_w;
    logic [DATA_WIDTH-1:0] data_out_local;
    logic valid_out_local;
    
    // DUT instantiation
    cgra_pe #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH)
    ) dut (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame),
        .config_valid(config_valid),
        .data_in_n(data_in_n),
        .data_in_e(data_in_e),
        .data_in_s(data_in_s),
        .data_in_w(data_in_w),
        .valid_in_n(valid_in_n),
        .valid_in_e(valid_in_e),
        .valid_in_s(valid_in_s),
        .valid_in_w(valid_in_w),
        .data_out_n(data_out_n),
        .data_out_e(data_out_e),
        .data_out_s(data_out_s),
        .data_out_w(data_out_w),
        .valid_out_n(valid_out_n),
        .valid_out_e(valid_out_e),
        .valid_out_s(valid_out_s),
        .valid_out_w(valid_out_w),
        .data_out_local(data_out_local),
        .valid_out_local(valid_out_local)
    );
    
    // Clock generation
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end
    
    // Test stimulus
    initial begin
        $display("======================================");
        $display("  CGRA PE Testbench Started");
        $display("======================================");
        
        // Initialize
        rst_n = 0;
        config_frame = 64'h0;
        config_valid = 0;
        data_in_n = 16'h0;
        data_in_e = 16'h0;
        data_in_s = 16'h0;
        data_in_w = 16'h0;
        valid_in_n = 0;
        valid_in_e = 0;
        valid_in_s = 0;
        valid_in_w = 0;
        
        // Reset
        #(CLK_PERIOD*5);
        rst_n = 1;
        #(CLK_PERIOD*2);
        
        // Test 1: ADD operation
        $display("\n[TEST 1] ADD operation: 10 + 20 = 30");
        config_frame[5:0] = 6'd1;     // OP_ADD
        config_frame[9:6] = 4'd6;     // src0 = immediate
        config_frame[13:10] = 4'd6;   // src1 = immediate
        config_frame[17:14] = 4'd0;   // dst = RF[0]
        config_frame[21:18] = 5'b10000; // route to local
        config_frame[39:24] = 16'd10; // immediate = 10
        data_in_n = 16'd20;           // Use N input as second operand
        valid_in_n = 1;
        config_frame[13:10] = 4'd1;   // Change src1 to N input
        config_valid = 1;
        #(CLK_PERIOD);
        config_valid = 0;
        #(CLK_PERIOD*2);
        
        // Test 2: MUL operation
        $display("[TEST 2] MUL operation: 5 * 6 = 30");
        config_frame[5:0] = 6'd3;     // OP_MUL
        config_frame[39:24] = 16'd5;  // immediate = 5
        data_in_n = 16'd6;
        config_valid = 1;
        #(CLK_PERIOD);
        config_valid = 0;
        #(CLK_PERIOD*2);
        
        // Test 3: MAC operation
        $display("[TEST 3] MAC operation");
        config_frame[5:0] = 6'd4;     // OP_MAC
        config_frame[39:24] = 16'd2;
        data_in_n = 16'd3;
        config_valid = 1;
        #(CLK_PERIOD);
        config_frame[39:24] = 16'd4;
        data_in_n = 16'd5;
        #(CLK_PERIOD);
        config_valid = 0;
        #(CLK_PERIOD*2);
        
        // Test 4: Compare operation
        $display("[TEST 4] CMP_GT operation: 10 > 5");
        config_frame[5:0] = 6'd10;    // OP_CMP_GT
        config_frame[39:24] = 16'd10;
        data_in_n = 16'd5;
        config_valid = 1;
        #(CLK_PERIOD);
        config_valid = 0;
        #(CLK_PERIOD*2);
        
        // Test 5: Routing test
        $display("[TEST 5] Routing to multiple outputs");
        config_frame[5:0] = 6'd16;    // OP_PASS0
        config_frame[21:18] = 5'b01111; // Route to N, E, S, W
        config_frame[39:24] = 16'hABCD;
        config_valid = 1;
        #(CLK_PERIOD);
        if (valid_out_n && valid_out_e && valid_out_s && valid_out_w) begin
            $display("  PASS: Multi-output routing successful");
        end else begin
            $display("  FAIL: Multi-output routing failed");
        end
        config_valid = 0;
        #(CLK_PERIOD*2);
        
        // Test 6: Predicate execution
        $display("[TEST 6] Predicate execution test");
        config_frame[5:0] = 6'd1;     // OP_ADD
        config_frame[22] = 1'b1;      // pred_en = 1
        config_frame[23] = 1'b0;      // pred_inv = 0
        config_frame[39:24] = 16'd100;
        data_in_n = 16'd50;
        config_valid = 1;
        #(CLK_PERIOD);
        config_valid = 0;
        #(CLK_PERIOD*2);
        
        // Test 7: Hardware LIF operation
        $display("[TEST 7] Hardware LIF Operation (OP_LIF)");
        // Clear accumulator before LIF sequence
        config_frame = 64'h0;
        config_frame[5:0]   = 6'd15;     // OP_ACC_CLR
        config_valid = 1;
        #(CLK_PERIOD);
        config_valid = 0;
        #(CLK_PERIOD);

        // src0 = data_in_n (input current), src1 = immediate (threshold)
        config_frame = 64'h0;
        config_frame[5:0]   = 6'd18;      // OP_LIF
        config_frame[9:6]   = 4'd1;       // src0 = N input
        config_frame[13:10] = 4'd6;       // src1 = immediate (threshold)
        config_frame[17:14] = 4'd0;       // dst (unused for LIF)
        config_frame[21:18] = 5'b10000;   // route to local
        config_frame[39:24] = 16'd100;    // threshold = 100
        config_valid = 1;

        // Cycle 1: 0 + 50 - leak(10) = 40 < 100 (no spike)
        data_in_n = 16'd50;
        #(CLK_PERIOD);
        $display("  Cycle 1: Input=50, Thresh=100 -> Spike=%b", data_out_local[0]);
        if (data_out_local == 0) $display("  PASS: No spike as expected"); else $display("  FAIL: Spiked early");

        // Cycle 2: 40 + 80 - leak(10) = 110 >= 100 (spike)
        data_in_n = 16'd80;
        #(CLK_PERIOD);
        $display("  Cycle 2: Input=80, Thresh=100 -> Spike=%b", data_out_local[0]);
        if (data_out_local == 1) $display("  PASS: Spike generated"); else $display("  FAIL: Missing spike");

        config_valid = 0;
        data_in_n = 16'd0;
        #(CLK_PERIOD*2);
        
        // End simulation
        #(CLK_PERIOD*10);
        $display("\n======================================");
        $display("  CGRA PE Testbench Completed");
        $display("======================================\n");
        $finish;
    end
    
    // Monitor
    initial begin
        $monitor("Time=%0t | Valid=%b | Out_N=%h | Out_E=%h | Out_S=%h | Out_W=%h | Out_Local=%h",
                 $time, valid_out_local, data_out_n, data_out_e, data_out_s, data_out_w, data_out_local);
    end

endmodule
