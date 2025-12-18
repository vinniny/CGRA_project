// ==============================================================================
// GOLDEN TESTBENCH: CGRA ROUTER
// ==============================================================================
// Focus: Backpressure (Stall), Priority Arbitration, Routing Correctness
// ==============================================================================

`timescale 1ns/1ps

module tb_cgra_router_golden;

    // -------------------------------------------------------------------------
    // 1. CONFIGURATION
    // -------------------------------------------------------------------------
    localparam DATA_WIDTH = 32;
    localparam ADDR_WIDTH = 4;
    localparam COORD_WIDTH = 4;
    localparam PAYLOAD_WIDTH = 16;
    localparam HEADER_WIDTH = DATA_WIDTH - PAYLOAD_WIDTH;
    localparam RESERVED_WIDTH = HEADER_WIDTH - (1 + (2 * COORD_WIDTH));
    localparam CLK_PERIOD = 10;
    localparam X_COORD    = 1;
    localparam Y_COORD    = 1;
    localparam [COORD_WIDTH-1:0] X_COORD_L = X_COORD;
    localparam [COORD_WIDTH-1:0] Y_COORD_L = Y_COORD;

    // DUT Signals
    logic clk, rst_n;

    // North Port
    logic [DATA_WIDTH-1:0] data_in_n;
    logic                  valid_in_n;
    logic                  ready_out_n;
    logic [DATA_WIDTH-1:0] data_out_n;
    logic                  valid_out_n;
    logic                  ready_in_n;

    // East Port
    logic [DATA_WIDTH-1:0] data_in_e;
    logic                  valid_in_e;
    logic                  ready_out_e;
    logic [DATA_WIDTH-1:0] data_out_e;
    logic                  valid_out_e;
    logic                  ready_in_e;

    // South Port
    logic [DATA_WIDTH-1:0] data_in_s;
    logic                  valid_in_s;
    logic                  ready_out_s;
    logic [DATA_WIDTH-1:0] data_out_s;
    logic                  valid_out_s;
    logic                  ready_in_s;

    // West Port
    logic [DATA_WIDTH-1:0] data_in_w;
    logic                  valid_in_w;
    logic                  ready_out_w;
    logic [DATA_WIDTH-1:0] data_out_w;
    logic                  valid_out_w;
    logic                  ready_in_w;

    // Local Port
    logic [DATA_WIDTH-1:0] data_in_local;
    logic                  valid_in_local;
    logic                  ready_out_local;
    logic [DATA_WIDTH-1:0] data_out_local;
    logic                  valid_out_local;
    logic                  ready_in_local;

    // Instantiate DUT (Updated with Ready/Valid ports)
    cgra_router #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .X_COORD(X_COORD),
        .Y_COORD(Y_COORD)
    ) dut (.*);

    function automatic logic [DATA_WIDTH-1:0] pack_packet(
        input logic [PAYLOAD_WIDTH-1:0] payload,
        input logic [COORD_WIDTH-1:0] dest_x,
        input logic [COORD_WIDTH-1:0] dest_y,
        input logic multicast
    );
        pack_packet = {multicast, dest_x, dest_y, {RESERVED_WIDTH{1'b0}}, payload};
    endfunction

    // -------------------------------------------------------------------------
    // 2. TRANSACTION CLASS (Disabled under Icarus)
    // -------------------------------------------------------------------------
`ifndef __ICARUS__
    class Router_Packet;
        rand bit [DATA_WIDTH-1:0] data;
        rand bit [COORD_WIDTH-1:0] dest_x, dest_y;
        rand bit                  multicast;
        rand bit                  is_valid;

        constraint c_contention {
            dest_x dist { 1:/50, [0:3]:/50 };
            dest_y dist { 0:/50, [0:3]:/50 };
        }
    endclass
`endif

    // -------------------------------------------------------------------------
    // 3. SYSTEMVERILOG ASSERTIONS (Disabled under Icarus)
    // -------------------------------------------------------------------------
`ifndef __ICARUS__
    property p_backpressure_n;
        @(posedge clk) disable iff (!rst_n)
        (valid_out_n && !ready_in_n) |=> ($stable(valid_out_n) && $stable(data_out_n));
    endproperty
    assert_stall_n: assert property(p_backpressure_n) else $error("Backpressure Violation on North Port!");
`endif

    // -------------------------------------------------------------------------
    // Clock generation
    // -------------------------------------------------------------------------
    initial begin
        clk = 1'b0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    // -------------------------------------------------------------------------
    // Reset and default inputs
    // -------------------------------------------------------------------------
    task automatic init_inputs;
        begin
            data_in_n = '0; valid_in_n = 1'b0; ready_in_n = 1'b1;
            data_in_e = '0; valid_in_e = 1'b0; ready_in_e = 1'b1;
            data_in_s = '0; valid_in_s = 1'b0; ready_in_s = 1'b1;
            data_in_w = '0; valid_in_w = 1'b0; ready_in_w = 1'b1;
            data_in_local = '0; valid_in_local = 1'b0; ready_in_local = 1'b1;
        end
    endtask

    // -------------------------------------------------------------------------
    // 4. MAIN TEST SEQUENCER
    // -------------------------------------------------------------------------
    initial begin
        init_inputs();
        rst_n = 1'b0;
        #(CLK_PERIOD*4);
        rst_n = 1'b1;
        #(CLK_PERIOD*2);

        $display("=== TEST 1: Basic Routing (Local -> North) ===");
        data_in_local = pack_packet(16'h01A5, X_COORD_L, (Y_COORD_L - 1'b1), 1'b0);
        valid_in_local = 1'b1;
        #(CLK_PERIOD);
        if (valid_out_n && data_out_n == pack_packet(16'h01A5, X_COORD_L, (Y_COORD_L - 1'b1), 1'b0)) begin
            $display("  PASS: Routed to North");
        end else begin
            $display("  FAIL: Expected North output");
        end
        valid_in_local = 1'b0;
        #(CLK_PERIOD*2);

        $display("=== TEST 2: Backpressure Hold (North Ready=0) ===");
        ready_in_n = 1'b0;
        data_in_local = pack_packet(16'h03EF, X_COORD_L, (Y_COORD_L - 1'b1), 1'b0);
        valid_in_local = 1'b1;
        #(CLK_PERIOD);
        valid_in_local = 1'b0;
        if (!valid_out_n) $display("  FAIL: valid_out_n not asserted under backpressure");
        if (data_out_n != pack_packet(16'h03EF, X_COORD_L, (Y_COORD_L - 1'b1), 1'b0)) begin
            $display("  FAIL: data_out_n mismatch under backpressure");
        end
        #(CLK_PERIOD);
        if (data_out_n != pack_packet(16'h03EF, X_COORD_L, (Y_COORD_L - 1'b1), 1'b0)) begin
            $display("  FAIL: data_out_n not stable under backpressure");
        end
        ready_in_n = 1'b1;
        #(CLK_PERIOD*2);

        $display("=== TEST 3: Priority Arbitration (L > W) ===");
        data_in_local = pack_packet(16'h0111, X_COORD_L, (Y_COORD_L - 1'b1), 1'b0);
        valid_in_local = 1'b1;

        data_in_w = pack_packet(16'h0222, X_COORD_L, (Y_COORD_L - 1'b1), 1'b0);
        valid_in_w = 1'b1;

        #(CLK_PERIOD);
        if (valid_out_n && data_out_n == pack_packet(16'h0111, X_COORD_L, (Y_COORD_L - 1'b1), 1'b0)) begin
            $display("  PASS: Local wins arbitration");
        end else begin
            $display("  FAIL: Arbitration order incorrect");
        end
        if (ready_out_w) $display("  FAIL: West should be stalled");
        valid_in_local = 1'b0;
        valid_in_w = 1'b0;
        #(CLK_PERIOD*2);

        $display("=== TEST COMPLETE ===");
        #(CLK_PERIOD*5);
        $finish;
    end

endmodule
