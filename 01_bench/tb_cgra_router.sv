// ==============================================================================
// Testbench for CGRA Router
// ==============================================================================

`timescale 1ns/1ps

module tb_cgra_router;

    // Parameters
    localparam DATA_WIDTH = 16;
    localparam ADDR_WIDTH = 4;
    localparam CLK_PERIOD = 10;
    
    // DUT signals
    logic clk;
    logic rst_n;
    
    // North port
    logic [DATA_WIDTH-1:0] data_in_n, data_out_n;
    logic [ADDR_WIDTH-1:0] dest_x_n, dest_y_n, dest_x_out_n, dest_y_out_n;
    logic multicast_n, multicast_out_n;
    logic valid_in_n, valid_out_n;
    
    // East port
    logic [DATA_WIDTH-1:0] data_in_e, data_out_e;
    logic [ADDR_WIDTH-1:0] dest_x_e, dest_y_e, dest_x_out_e, dest_y_out_e;
    logic multicast_e, multicast_out_e;
    logic valid_in_e, valid_out_e;
    
    // South port
    logic [DATA_WIDTH-1:0] data_in_s, data_out_s;
    logic [ADDR_WIDTH-1:0] dest_x_s, dest_y_s, dest_x_out_s, dest_y_out_s;
    logic multicast_s, multicast_out_s;
    logic valid_in_s, valid_out_s;
    
    // West port
    logic [DATA_WIDTH-1:0] data_in_w, data_out_w;
    logic [ADDR_WIDTH-1:0] dest_x_w, dest_y_w, dest_x_out_w, dest_y_out_w;
    logic multicast_w, multicast_out_w;
    logic valid_in_w, valid_out_w;
    
    // Local port
    logic [DATA_WIDTH-1:0] data_in_local, data_out_local;
    logic [ADDR_WIDTH-1:0] dest_x_local, dest_y_local;
    logic multicast_local;
    logic valid_in_local, valid_out_local;
    
    // DUT instantiation (Router at position 1,1)
    cgra_router #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .X_COORD(1),
        .Y_COORD(1)
    ) dut (
        .clk(clk),
        .rst_n(rst_n),
        .data_in_n(data_in_n), .data_out_n(data_out_n),
        .dest_x_n(dest_x_n), .dest_y_n(dest_y_n),
        .dest_x_out_n(dest_x_out_n), .dest_y_out_n(dest_y_out_n),
        .multicast_n(multicast_n), .multicast_out_n(multicast_out_n),
        .valid_in_n(valid_in_n), .valid_out_n(valid_out_n),
        .data_in_e(data_in_e), .data_out_e(data_out_e),
        .dest_x_e(dest_x_e), .dest_y_e(dest_y_e),
        .dest_x_out_e(dest_x_out_e), .dest_y_out_e(dest_y_out_e),
        .multicast_e(multicast_e), .multicast_out_e(multicast_out_e),
        .valid_in_e(valid_in_e), .valid_out_e(valid_out_e),
        .data_in_s(data_in_s), .data_out_s(data_out_s),
        .dest_x_s(dest_x_s), .dest_y_s(dest_y_s),
        .dest_x_out_s(dest_x_out_s), .dest_y_out_s(dest_y_out_s),
        .multicast_s(multicast_s), .multicast_out_s(multicast_out_s),
        .valid_in_s(valid_in_s), .valid_out_s(valid_out_s),
        .data_in_w(data_in_w), .data_out_w(data_out_w),
        .dest_x_w(dest_x_w), .dest_y_w(dest_y_w),
        .dest_x_out_w(dest_x_out_w), .dest_y_out_w(dest_y_out_w),
        .multicast_w(multicast_w), .multicast_out_w(multicast_out_w),
        .valid_in_w(valid_in_w), .valid_out_w(valid_out_w),
        .data_in_local(data_in_local), .data_out_local(data_out_local),
        .dest_x_local(dest_x_local), .dest_y_local(dest_y_local),
        .multicast_local(multicast_local),
        .valid_in_local(valid_in_local), .valid_out_local(valid_out_local)
    );
    
    // Clock generation
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end
    
    // Test stimulus
    initial begin
        $display("======================================");
        $display("  CGRA Router Testbench Started");
        $display("  Router at position (1,1)");
        $display("======================================");
        
        // Initialize all inputs
        rst_n = 0;
        data_in_n = 0; dest_x_n = 0; dest_y_n = 0; multicast_n = 0; valid_in_n = 0;
        data_in_e = 0; dest_x_e = 0; dest_y_e = 0; multicast_e = 0; valid_in_e = 0;
        data_in_s = 0; dest_x_s = 0; dest_y_s = 0; multicast_s = 0; valid_in_s = 0;
        data_in_w = 0; dest_x_w = 0; dest_y_w = 0; multicast_w = 0; valid_in_w = 0;
        data_in_local = 0; dest_x_local = 0; dest_y_local = 0; multicast_local = 0; valid_in_local = 0;
        
        #(CLK_PERIOD*5);
        rst_n = 1;
        #(CLK_PERIOD*2);
        
        // Test 1: Route from Local to East (destination X=3, Y=1)
        $display("\n[TEST 1] Local to East routing");
        data_in_local = 16'hABCD;
        dest_x_local = 4'd3;
        dest_y_local = 4'd1;
        multicast_local = 0;
        valid_in_local = 1;
        #(CLK_PERIOD);
        if (valid_out_e && data_out_e == 16'hABCD) begin
            $display("  PASS: Packet routed to East");
        end else begin
            $display("  FAIL: Routing error");
        end
        valid_in_local = 0;
        #(CLK_PERIOD*2);
        
        // Test 2: Route from North to South (destination X=1, Y=3)
        $display("[TEST 2] North to South routing");
        data_in_n = 16'h1234;
        dest_x_n = 4'd1;
        dest_y_n = 4'd3;
        multicast_n = 0;
        valid_in_n = 1;
        #(CLK_PERIOD);
        if (valid_out_s && data_out_s == 16'h1234) begin
            $display("  PASS: Packet routed to South");
        end else begin
            $display("  FAIL: Routing error");
        end
        valid_in_n = 0;
        #(CLK_PERIOD*2);
        
        // Test 3: Route to local (destination X=1, Y=1)
        $display("[TEST 3] Route to local PE");
        data_in_w = 16'h5678;
        dest_x_w = 4'd1;
        dest_y_w = 4'd1;
        multicast_w = 0;
        valid_in_w = 1;
        #(CLK_PERIOD);
        if (valid_out_local && data_out_local == 16'h5678) begin
            $display("  PASS: Packet delivered to local PE");
        end else begin
            $display("  FAIL: Local delivery error");
        end
        valid_in_w = 0;
        #(CLK_PERIOD*2);
        
        // Test 4: Multicast test
        $display("[TEST 4] Multicast from local");
        data_in_local = 16'hFFFF;
        dest_x_local = 4'd0;
        dest_y_local = 4'd0;
        multicast_local = 1;
        valid_in_local = 1;
        #(CLK_PERIOD);
        if (valid_out_n && valid_out_e && valid_out_s && valid_out_w) begin
            $display("  PASS: Multicast to all directions");
        end else begin
            $display("  FAIL: Multicast incomplete - N:%b E:%b S:%b W:%b", 
                     valid_out_n, valid_out_e, valid_out_s, valid_out_w);
        end
        valid_in_local = 0;
        multicast_local = 0;
        #(CLK_PERIOD*2);
        
        // Test 5: XY routing West then North
        $display("[TEST 5] XY routing: West then North");
        data_in_e = 16'h9ABC;
        dest_x_e = 4'd0;
        dest_y_e = 4'd0;
        multicast_e = 0;
        valid_in_e = 1;
        #(CLK_PERIOD);
        if (valid_out_w) begin
            $display("  PASS: First hop West (X-dimension)");
        end else begin
            $display("  FAIL: Should route West first");
        end
        valid_in_e = 0;
        #(CLK_PERIOD*2);
        
        #(CLK_PERIOD*10);
        $display("\n======================================");
        $display("  CGRA Router Testbench Completed");
        $display("======================================\n");
        $finish;
    end
    
    // Monitor outputs
    initial begin
        $monitor("Time=%0t | N:%b E:%b S:%b W:%b Local:%b | Data_Local=%h",
                 $time, valid_out_n, valid_out_e, valid_out_s, valid_out_w, 
                 valid_out_local, data_out_local);
    end

endmodule
