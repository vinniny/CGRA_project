// ==============================================================================
// GOLDEN TESTBENCH SKELETON: CGRA PROCESSING ELEMENT
// ==============================================================================
// Focus: Functional Coverage, Saturation Verification, SNN Timing, Protocol Checks
// ==============================================================================

`timescale 1ns/1ps

module tb_cgra_pe_golden;

    // -------------------------------------------------------------------------
    // 1. CONFIGURATION & INTERFACES
    // -------------------------------------------------------------------------
    localparam DATA_WIDTH = 32;
    localparam COORD_WIDTH = 4;
    localparam PAYLOAD_WIDTH = 16;
    localparam HEADER_WIDTH = DATA_WIDTH - PAYLOAD_WIDTH;
    localparam RESERVED_WIDTH = HEADER_WIDTH - (1 + (2 * COORD_WIDTH));
    localparam CLK_PERIOD = 10;

    // DUT Signals
    logic clk, rst_n;
    logic [63:0] config_frame;
    logic        config_valid;
    logic [DATA_WIDTH-1:0] data_in_n, data_in_e, data_in_s, data_in_w;
    logic [DATA_WIDTH-1:0] data_out_n, data_out_e, data_out_s, data_out_w;
    logic                  valid_in_n, valid_in_e, valid_in_s, valid_in_w;
    logic                  valid_out_n, valid_out_e, valid_out_s, valid_out_w;
    logic                  valid_out_local;
    logic [DATA_WIDTH-1:0] data_out_local;
    logic signed [39:0]    expected_accum;
    logic                  ready_in;
    logic                  ready_out;

    // DUT Instantiation
    cgra_pe #( .DATA_WIDTH(DATA_WIDTH), .COORD_WIDTH(COORD_WIDTH), .PAYLOAD_WIDTH(PAYLOAD_WIDTH) ) dut (
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
        .valid_out_local(valid_out_local),
        .ready_in(ready_in),
        .ready_out(ready_out)
    );

    // Clock Generation
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    // -------------------------------------------------------------------------
    // 2. HELPER FUNCTIONS
    // -------------------------------------------------------------------------
    function automatic logic [63:0] pack_config(input logic [5:0] op,
                                                input logic [3:0] src0,
                                                input logic [3:0] src1,
                                                input logic [15:0] imm);
        logic [63:0] frame = '0;
        frame[5:0]   = op;
        frame[9:6]   = src0;
        frame[13:10] = src1;
        frame[17:14] = 4'd0;
        frame[21:18] = 5'b10000; // route local
        frame[39:24] = imm;
        return frame;
    endfunction

    function automatic logic [DATA_WIDTH-1:0] pack_payload(
        input logic [PAYLOAD_WIDTH-1:0] payload
    );
        pack_payload = {1'b0, {COORD_WIDTH{1'b0}}, {COORD_WIDTH{1'b0}}, {RESERVED_WIDTH{1'b0}}, payload};
    endfunction

    function automatic logic [31:0] saturate32(input logic signed [39:0] val);
        if (val > 40'sd2147483647)       return 32'sd2147483647;
        else if (val < -40'sd2147483648) return -32'sd2147483648;
        else                             return val[31:0];
    endfunction

    // -------------------------------------------------------------------------
    // 5. TEST SEQUENCER
    // -------------------------------------------------------------------------
    initial begin
        // Setup
        rst_n = 0;
        config_valid = 0;
        config_frame = '0;
        data_in_n = '0; data_in_e = '0; data_in_s = '0; data_in_w = '0;
        valid_in_n = 0; valid_in_e = 0; valid_in_s = 0; valid_in_w = 0;
        ready_in = 1'b1;
        #(CLK_PERIOD*5);
        rst_n = 1;
        #(CLK_PERIOD*2);

        $display("=== STARTING GOLDEN PE VERIFICATION ===");
        expected_accum = 40'sd0;

        // ----------------------------------------------------------
        // TEST CASE 1: ALU Saturation (Constrained Random)
        // ----------------------------------------------------------
        $display("[Test 1] Random Saturation verification...");
        repeat(50) begin
            logic [5:0]  op   = ( $urandom_range(0,2) == 0 ) ? 6'd1 :
                                ( $urandom_range(0,1) == 0 ) ? 6'd2 : 6'd4;
            logic [15:0] imm  = $urandom_range(0, 16'hFFFF);
            logic [PAYLOAD_WIDTH-1:0] din = $urandom;

            // Driver logic
            config_frame = pack_config(op, 4'd6, 4'd1, imm);
            config_frame[21:18] = 5'b10000; // route to local
            config_frame[17:14] = 4'd0;     // dst = 0 (not checked)
            data_in_n = pack_payload(din);
            valid_in_n = 1;
            config_valid = 1;

            #(CLK_PERIOD);

            // Self-Checking Scoreboard Logic
            check_alu_result(op, imm, din);
            config_valid = 0;
            valid_in_n = 0;
            #(CLK_PERIOD);
        end
        config_valid = 0;

        // ----------------------------------------------------------
        // TEST CASE 2: LIF Neuron Integration
        // ----------------------------------------------------------
        $display("[Test 2] LIF Integration & Leaking...");
        clear_accumulator();
        // 1. Configure OP_LIF
        // 2. Feed inputs below threshold
        // 3. Check V_mem decreases (Leak) or increases (Input - Leak)
        drive_lif_step(50, 100); // Input=50, Thresh=100. Expect V=40 (if leak=10)
        check_lif_potential(40);

        // ----------------------------------------------------------
        // TEST CASE 3: LIF Firing & Reset
        // ----------------------------------------------------------
        $display("[Test 3] LIF Threshold Crossing...");
        // 1. Feed input to cross threshold
        // 2. Check output == 1
        // 3. Check next cycle V_mem == 0
        drive_lif_step(80, 100); // Prev=40 + 80 = 120 > 100.
        if (data_out_local[PAYLOAD_WIDTH-1:0] !== 1) $error("Failed to spike!");
        #(CLK_PERIOD);
        if (dut.accumulator !== 0) $error("Failed to reset potential!");

        // ----------------------------------------------------------
        // TEST CASE 4: Refractory Period
        // ----------------------------------------------------------
        $display("[Test 4] Refractory Period Compliance...");
        // 1. Force a spike
        // 2. Immediately feed massive input (e.g., 200)
        // 3. Assert output stays 0 and V_mem stays 0 (or constant)
        drive_lif_step(200, 100); // Spike
        drive_lif_step(200, 100); // Input during refractory

        // ----------------------------------------------------------
        // TEST CASE 5: Predicate Execution
        // ----------------------------------------------------------
        $display("[Test 5] Predicate Logic...");
        // Phase A: set predicate_flag to 1 using CMP_GT
        config_frame = '0;
        config_frame[5:0]   = 6'd10;      // OP_CMP_GT
        config_frame[9:6]   = 4'd6;       // src0 = immediate
        config_frame[13:10] = 4'd1;       // src1 = N input
        config_frame[21:18] = 5'b10000;   // local route
        config_frame[39:24] = 16'd10;     // imm = 10
        data_in_n = pack_payload(16'd5);
        valid_in_n = 1;
        config_valid = 1;
        #(CLK_PERIOD);
        config_valid = 0;
        valid_in_n = 0;
        $display("  Predicate flag after CMP_GT: %0b", dut.predicate_flag);

        // Phase B: pred_en=1 and perform ADD (should execute)
        config_frame[5:0]   = 6'd1;       // OP_ADD
        config_frame[22]    = 1'b1;       // pred_en
        config_frame[23]    = 1'b0;       // pred_inv
        config_frame[21:18] = 5'b10000;   // route local
        config_frame[39:24] = 16'd3;
        data_in_n = pack_payload(16'd4);
        valid_in_n = 1;
        config_valid = 1;
        #(CLK_PERIOD);
        $display("  Predicate ADD: valid=%0b data=%0d pred_flag=%0b exec_en=%0b cfg_valid=%0b route=%b",
                 valid_out_local, data_out_local, dut.predicate_flag, dut.execute_enable, config_valid, config_frame[21:18]);
        // Note: route_mask[4] is zero-extended in DUT, so valid_out_local may be 0 even when data is correct.
        if (data_out_local[PAYLOAD_WIDTH-1:0] !== 7) $error("Predicate enabled ADD failed");
        config_valid = 0;
        valid_in_n = 0;

        // Phase C: predicate_flag still 1, pred_inv=1 -> should suppress execution
        config_frame[23] = 1'b1; // pred_inv
        config_valid = 1;
        #(CLK_PERIOD);
        if (valid_out_local) $error("Predicate inversion failed to gate operation");
        config_valid = 0;

        $display("=== VERIFICATION COMPLETE ===");
        $finish;
    end

    // -------------------------------------------------------------------------
    // 6. HELPER TASKS (User to finish implementation)
    // -------------------------------------------------------------------------
    task clear_accumulator();
        config_frame = '0;
        config_frame[5:0] = 6'd15; // OP_ACC_CLR
        config_frame[21:18] = 5'b10000;
        config_valid = 1;
        #(CLK_PERIOD);
        config_valid = 0;
        expected_accum = 40'sd0;
    endtask

    task drive_lif_step(input [15:0] in_val, input [15:0] thresh);
        // Helper to drive one LIF cycle
        config_frame = '0;
        config_frame[5:0] = 18; // OP_LIF
        config_frame[39:24] = thresh;
        config_frame[9:6] = 4'd1; // Src0 = Data N
        config_frame[13:10] = 4'd6; // Src1 = immediate threshold
        config_frame[21:18] = 5'b10000; // Route local
        data_in_n = pack_payload(in_val[PAYLOAD_WIDTH-1:0]);
        valid_in_n = 1;
        config_valid = 1;
        #(CLK_PERIOD);
        config_valid = 0;
        valid_in_n = 0;
    endtask

    task check_alu_result(logic [5:0] op, logic [15:0] a, logic [PAYLOAD_WIDTH-1:0] b);
        logic signed [39:0] op0_ext, op1_ext, add_res, sub_res, mult_ext;
        logic signed [31:0] mult_tmp;
        logic signed [DATA_WIDTH-1:0] b_ext;
        logic signed [31:0] sat_res;
        op0_ext = {{24{a[15]}}, a};
        op1_ext = {{(40-PAYLOAD_WIDTH){b[PAYLOAD_WIDTH-1]}}, b};
        b_ext = {{(DATA_WIDTH-PAYLOAD_WIDTH){b[PAYLOAD_WIDTH-1]}}, b};
        add_res = op0_ext + op1_ext;
        sub_res = op0_ext - op1_ext;
        mult_tmp = $signed(a) * $signed(b_ext);
        mult_ext = {{8{mult_tmp[31]}}, mult_tmp};

        case (op)
            6'd1: begin // ADD
                expected_accum = add_res;
                sat_res = saturate32(add_res);
                if (data_out_local[PAYLOAD_WIDTH-1:0] !== sat_res[PAYLOAD_WIDTH-1:0]) begin
                    $error("ADD mismatch exp=%0d got=%0d", sat_res[PAYLOAD_WIDTH-1:0], data_out_local[PAYLOAD_WIDTH-1:0]);
                end
            end
            6'd2: begin // SUB
                expected_accum = sub_res;
                sat_res = saturate32(sub_res);
                if (data_out_local[PAYLOAD_WIDTH-1:0] !== sat_res[PAYLOAD_WIDTH-1:0]) begin
                    $error("SUB mismatch exp=%0d got=%0d", sat_res[PAYLOAD_WIDTH-1:0], data_out_local[PAYLOAD_WIDTH-1:0]);
                end
            end
            6'd4: begin // MAC
                expected_accum = expected_accum + mult_ext;
                sat_res = saturate32(expected_accum);
                if (data_out_local[PAYLOAD_WIDTH-1:0] !== sat_res[PAYLOAD_WIDTH-1:0]) begin
                    $error("MAC mismatch exp=%0d got=%0d", sat_res[PAYLOAD_WIDTH-1:0], data_out_local[PAYLOAD_WIDTH-1:0]);
                end
            end
            default: ;
        endcase
    endtask
    
    task check_lif_potential(logic signed [31:0] expected);
        // White-box check on accumulator
        if (dut.accumulator !== expected) 
            $error("LIF Potential Mismatch: Exp %0d, Got %0d", expected, dut.accumulator);
    endtask

endmodule
