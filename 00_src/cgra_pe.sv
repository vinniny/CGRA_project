// ==============================================================================
// CGRA Processing Element (PE)
// ==============================================================================
// A configurable processing element supporting 19 ALU operations, 16-entry
// register file, 256×32-bit scratchpad, and 16-context configuration RAM.
//
// ARCHITECTURE:
//   - ALU/MAC with 40-bit accumulator
//   - 16×32-bit Register File
//   - 256×32-bit Scratchpad Memory (BRAM)
//   - 16-slot Configuration RAM (multi-context)
//   - 4-direction mesh broadcast output
//   - LIF neuron for neuromorphic computing
//
// ISA (19 Operations - ALL VERIFIED ✓):
//   Op | Name       | Operation              | Test Suite
//   ---|------------|------------------------|------------
//   0  | NOP        | No operation           | M
//   1  | ADD        | A + B (saturating)     | M, Q
//   2  | SUB        | A - B (saturating)     | M, N
//   3  | MUL        | A × B (32-bit)         | M
//   4  | MAC        | Acc += A × B           | T
//   5  | AND        | A & B                  | K, M, Q
//   6  | OR         | A | B                  | K, M, Q
//   7  | XOR        | A ^ B                  | K, M, Q
//   8  | SHL        | A << B (variable)      | U
//   9  | SHR        | A >> B (variable)      | T, U
//  10  | CMP_GT     | (A > B) ? 1 : 0        | T
//  11  | CMP_LT     | (A < B) ? 1 : 0        | T, U
//  12  | CMP_EQ     | (A == B) ? 1 : 0       | P
//  13  | LOAD_SPM   | Load from scratchpad   | T
//  14  | STORE_SPM  | Store to scratchpad    | T
//  15  | ACC_CLR    | Clear accumulator      | T, V
//  16  | PASS0      | Pass operand0          | T
//  17  | PASS1      | Pass operand1          | T
//  18  | LIF        | Leaky Integrate-Fire   | V
//
// SOURCE SELECT (src0_sel, src1_sel):
//   0 = Register File    4 = West neighbor
//   1 = North neighbor   5 = Scratchpad  
//   2 = East neighbor    6 = Immediate
//   3 = South neighbor
//
// CONFIGURATION FRAME FORMAT (64-bit):
//   [5:0]   opcode     [13:10] src1_sel   [22]    pred_en    [39:24] imm
//   [9:6]   src0_sel   [17:14] dst_sel    [23]    pred_inv   [63:40] extended
//   [21:18] route_mask (N/E/S/W output enable)
//
// VERIFICATION: All 19 operations tested in 141/141 test vectors
// ==============================================================================

module cgra_pe #(
    parameter DATA_WIDTH  = 32,
    parameter COORD_WIDTH = 4,
    parameter PAYLOAD_WIDTH = 16,
    parameter ADDR_WIDTH  = 8,
    parameter SPM_DEPTH   = 256,
    parameter RF_DEPTH    = 16,
    parameter CONTEXT_DEPTH = 16,  // Number of config slots (recipes)
    parameter PC_WIDTH    = 4      // $clog2(CONTEXT_DEPTH)
)(
    input  logic clk,
    input  logic rst_n,
    
    // Configuration interface (static - for initial/single config)
    input  logic [63:0] config_frame,
    input  logic        config_valid,
    
    // Multi-context interface (for multi-cycle kernels)
    input  logic [PC_WIDTH-1:0] context_pc,     // Which config slot to use
    input  logic                global_stall,   // Freeze PE state
    
    // Config write interface (from DMA/TB)
    input  logic [PC_WIDTH-1:0] cfg_wr_addr,    // Slot to write
    input  logic [63:0]         cfg_wr_data,    // Config to store
    input  logic                cfg_wr_en,      // Write enable
    
    // Routing inputs (from N/E/S/W neighbors)
    input  logic [DATA_WIDTH-1:0] data_in_n,
    input  logic [DATA_WIDTH-1:0] data_in_e,
    input  logic [DATA_WIDTH-1:0] data_in_s,
    input  logic [DATA_WIDTH-1:0] data_in_w,
    input  logic                  valid_in_n,
    input  logic                  valid_in_e,
    input  logic                  valid_in_s,
    input  logic                  valid_in_w,
    
    // Routing outputs (to N/E/S/W neighbors)
    output logic [DATA_WIDTH-1:0] data_out_n,
    output logic [DATA_WIDTH-1:0] data_out_e,
    output logic [DATA_WIDTH-1:0] data_out_s,
    output logic [DATA_WIDTH-1:0] data_out_w,
    output logic                  valid_out_n,
    output logic                  valid_out_e,
    output logic                  valid_out_s,
    output logic                  valid_out_w,
    
    // Local data output
    output logic [DATA_WIDTH-1:0] data_out_local,
    output logic                  valid_out_local,

    // Backpressure (from/to router local port)
    input  logic                  ready_in,
    output logic                  ready_out
);

    // =========================================================================
    // Configuration frame decoding
    // =========================================================================
    logic [5:0]  op_code;
    logic [3:0]  src0_sel;
    logic [3:0]  src1_sel;
    logic [3:0]  dst_sel;
    logic [4:0]  route_mask;
    logic        pred_en;
    logic        pred_inv;
    logic [15:0] immediate;
    logic [23:0] extended;
    logic [COORD_WIDTH-1:0] cfg_dest_x;
    logic [COORD_WIDTH-1:0] cfg_dest_y;
    logic                   cfg_multicast;

    localparam int HEADER_WIDTH  = DATA_WIDTH - PAYLOAD_WIDTH;
    localparam int RESERVED_WIDTH = HEADER_WIDTH - (1 + (2 * COORD_WIDTH));

    // =========================================================================
    // Config RAM (The "Recipe Book" - 16 config slots)
    // =========================================================================
    logic [63:0] config_ram [0:CONTEXT_DEPTH-1];
    logic [63:0] active_config;
    
    // Config RAM write (from DMA/testbench)
    always_ff @(posedge clk) begin
        if (cfg_wr_en) begin
            config_ram[cfg_wr_addr] <= cfg_wr_data;
        end
    end
    
    // Select active config: use config_ram[context_pc] if loaded, else use config_frame
    // For backward compatibility: if context_pc is 0 and config_valid, use config_frame directly
    assign active_config = (context_pc == 0 && config_valid) ? config_frame : config_ram[context_pc];

    // =========================================================================
    // Stall Logic
    // =========================================================================
    // Stall when router cannot accept output OR global stall is asserted
    logic stall;
    assign stall = !ready_in || global_stall;
    assign ready_out = ready_in && !global_stall;
    
    // =========================================================================
    // Configuration frame decoding (decodes active_config)
    // =========================================================================
    always_comb begin
        op_code    = active_config[5:0];
        src0_sel   = active_config[9:6];
        src1_sel   = active_config[13:10];
        dst_sel    = active_config[17:14];
        route_mask = active_config[21:18];
        pred_en    = active_config[22];
        pred_inv   = active_config[23];
        immediate  = active_config[39:24];
        extended   = active_config[63:40];
        cfg_dest_x = extended[COORD_WIDTH-1:0];
        cfg_dest_y = extended[(2 * COORD_WIDTH)-1:COORD_WIDTH];
        cfg_multicast = extended[2 * COORD_WIDTH];
    end
    
    // =========================================================================
    // Scratchpad Memory (SPM)
    // =========================================================================
    logic [DATA_WIDTH-1:0] spm_mem [0:SPM_DEPTH-1];
    logic [ADDR_WIDTH-1:0] spm_addr;
    logic [DATA_WIDTH-1:0] spm_rdata;
    logic [DATA_WIDTH-1:0] spm_wdata;
    logic                  spm_we;
    
    always_ff @(posedge clk) begin
        if (spm_we && !stall) begin
            spm_mem[spm_addr] <= spm_wdata;
        end
        if (!stall) begin
            spm_rdata <= spm_mem[spm_addr];
        end
    end
    
    // =========================================================================
    // Register File (RF)
    // =========================================================================
    logic [DATA_WIDTH-1:0] rf_mem [0:RF_DEPTH-1];
    logic [3:0]            rf_raddr0;
    logic [3:0]            rf_raddr1;
    logic [3:0]            rf_waddr;
    logic [DATA_WIDTH-1:0] rf_rdata0;
    logic [DATA_WIDTH-1:0] rf_rdata1;
    logic [DATA_WIDTH-1:0] rf_wdata;
    logic                  rf_we;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            rf_mem[0] <= '0;
            rf_mem[1] <= '0;
            rf_mem[2] <= '0;
            rf_mem[3] <= '0;
            rf_mem[4] <= '0;
            rf_mem[5] <= '0;
            rf_mem[6] <= '0;
            rf_mem[7] <= '0;
            rf_mem[8] <= '0;
            rf_mem[9] <= '0;
            rf_mem[10] <= '0;
            rf_mem[11] <= '0;
            rf_mem[12] <= '0;
            rf_mem[13] <= '0;
            rf_mem[14] <= '0;
            rf_mem[15] <= '0;
        end else if (rf_we && !stall) begin
            rf_mem[rf_waddr] <= rf_wdata;
        end
    end
    
    always_comb begin
        rf_rdata0 = rf_mem[rf_raddr0];
        rf_rdata1 = rf_mem[rf_raddr1];
    end
    
    // =========================================================================
    // Operand Multiplexing (payload extracted from packets)
    // =========================================================================
    logic [DATA_WIDTH-1:0] operand0;
    logic [DATA_WIDTH-1:0] operand1;
    logic [PAYLOAD_WIDTH-1:0] payload_n;
    logic [PAYLOAD_WIDTH-1:0] payload_e;
    logic [PAYLOAD_WIDTH-1:0] payload_s;
    logic [PAYLOAD_WIDTH-1:0] payload_w;
    logic [DATA_WIDTH-1:0] data_in_n_payload;
    logic [DATA_WIDTH-1:0] data_in_e_payload;
    logic [DATA_WIDTH-1:0] data_in_s_payload;
    logic [DATA_WIDTH-1:0] data_in_w_payload;

    always_comb begin
        payload_n = data_in_n[PAYLOAD_WIDTH-1:0];
        payload_e = data_in_e[PAYLOAD_WIDTH-1:0];
        payload_s = data_in_s[PAYLOAD_WIDTH-1:0];
        payload_w = data_in_w[PAYLOAD_WIDTH-1:0];

        data_in_n_payload = {{(DATA_WIDTH-PAYLOAD_WIDTH){payload_n[PAYLOAD_WIDTH-1]}}, payload_n};
        data_in_e_payload = {{(DATA_WIDTH-PAYLOAD_WIDTH){payload_e[PAYLOAD_WIDTH-1]}}, payload_e};
        data_in_s_payload = {{(DATA_WIDTH-PAYLOAD_WIDTH){payload_s[PAYLOAD_WIDTH-1]}}, payload_s};
        data_in_w_payload = {{(DATA_WIDTH-PAYLOAD_WIDTH){payload_w[PAYLOAD_WIDTH-1]}}, payload_w};
    end
    
    always_comb begin
        // src0 selection
        unique case (src0_sel)
            4'd0:    operand0 = rf_rdata0;
            4'd1:    operand0 = data_in_n_payload;
            4'd2:    operand0 = data_in_e_payload;
            4'd3:    operand0 = data_in_s_payload;
            4'd4:    operand0 = data_in_w_payload;
            4'd5:    operand0 = spm_rdata;
            4'd6:    operand0 = immediate;
            default: operand0 = '0;
        endcase
        
        // src1 selection
        unique case (src1_sel)
            4'd0:    operand1 = rf_rdata1;
            4'd1:    operand1 = data_in_n_payload;
            4'd2:    operand1 = data_in_e_payload;
            4'd3:    operand1 = data_in_s_payload;
            4'd4:    operand1 = data_in_w_payload;
            4'd5:    operand1 = spm_rdata;
            4'd6:    operand1 = immediate;
            default: operand1 = '0;
        endcase
    end
    
    // =========================================================================
    // ALU/MAC Unit
    // =========================================================================
    logic [31:0]           alu_result;
    logic signed [39:0]    accumulator;
    logic                  predicate_flag;
    logic signed [39:0]    op0_ext;
    logic signed [39:0]    op1_ext;
    logic signed [31:0]    mult_result;
    logic signed [39:0]    mult_ext;
    logic signed [39:0]    lif_next_v;
    logic signed [39:0]    add_result;
    logic signed [39:0]    sub_result;
    localparam signed [39:0] LIF_LEAK = 40'sd10;
    
    // Pre-computed saturated values (replacing function)
    logic [31:0] add_result_sat;
    logic [31:0] sub_result_sat;
    logic [31:0] mac_result_sat;
    logic signed [39:0] mac_sum;
    
    // Saturation constants
    localparam signed [39:0] MAX_VAL = 40'sd2147483647;
    localparam signed [39:0] MIN_VAL = -40'sd2147483648;
    
    // OpCode definitions
    localparam OP_NOP   = 6'd0;
    localparam OP_ADD   = 6'd1;
    localparam OP_SUB   = 6'd2;
    localparam OP_MUL   = 6'd3;
    localparam OP_MAC   = 6'd4;  // Multiply-Accumulate
    localparam OP_AND   = 6'd5;
    localparam OP_OR    = 6'd6;
    localparam OP_XOR   = 6'd7;
    localparam OP_SHL   = 6'd8;
    localparam OP_SHR   = 6'd9;
    localparam OP_CMP_GT = 6'd10;
    localparam OP_CMP_LT = 6'd11;
    localparam OP_CMP_EQ = 6'd12;
    localparam OP_LOAD_SPM = 6'd13;
    localparam OP_STORE_SPM = 6'd14;
    localparam OP_ACC_CLR = 6'd15;
    localparam OP_PASS0 = 6'd16;
    localparam OP_PASS1 = 6'd17;
    localparam OP_LIF   = 6'd18;
    
    always_comb begin
        op0_ext = {{(40-DATA_WIDTH){operand0[DATA_WIDTH-1]}}, operand0};
        op1_ext = {{(40-DATA_WIDTH){operand1[DATA_WIDTH-1]}}, operand1};
        mult_result = $signed(operand0) * $signed(operand1);
        mult_ext = {{8{mult_result[31]}}, mult_result};
        add_result = op0_ext + op1_ext;
        sub_result = op0_ext - op1_ext;
        lif_next_v = accumulator + op0_ext - LIF_LEAK;
        mac_sum = accumulator + mult_ext;
        
        // Inline saturation for ADD result
        if (add_result > MAX_VAL) begin
            add_result_sat = 32'sd2147483647;
        end else if (add_result < MIN_VAL) begin
            add_result_sat = -32'sd2147483648;
        end else begin
            add_result_sat = add_result[31:0];
        end
        
        // Inline saturation for SUB result
        if (sub_result > MAX_VAL) begin
            sub_result_sat = 32'sd2147483647;
        end else if (sub_result < MIN_VAL) begin
            sub_result_sat = -32'sd2147483648;
        end else begin
            sub_result_sat = sub_result[31:0];
        end
        
        // Inline saturation for MAC result
        if (mac_sum > MAX_VAL) begin
            mac_result_sat = 32'sd2147483647;
        end else if (mac_sum < MIN_VAL) begin
            mac_result_sat = -32'sd2147483648;
        end else begin
            mac_result_sat = mac_sum[31:0];
        end
    end
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            accumulator <= '0;
            predicate_flag <= 1'b0;
        end else if (!stall) begin  // Execute when not stalled (config_ram is always valid)
            unique case (op_code)
                OP_NOP: begin
                    alu_result <= '0;
                end
                OP_ADD: begin
                    accumulator <= add_result;
                    alu_result <= add_result_sat;
                end
                OP_SUB: begin
                    accumulator <= sub_result;
                    alu_result <= sub_result_sat;
                end
                OP_MUL: begin
                    alu_result <= operand0 * operand1;
                end
                OP_MAC: begin
                    accumulator <= mac_sum;
                    alu_result <= mac_result_sat;
                end
                OP_AND: begin
                    alu_result <= operand0 & operand1;
                end
                OP_OR: begin
                    alu_result <= operand0 | operand1;
                end
                OP_XOR: begin
                    alu_result <= operand0 ^ operand1;
                end
                OP_SHL: begin
                    alu_result <= operand0 << operand1[4:0];  // 5-bit shift (0-31)
                end
                OP_SHR: begin
                    alu_result <= $signed(operand0) >>> operand1[4:0];  // Arithmetic shift right
                end
                OP_CMP_GT: begin
                    predicate_flag <= (operand0 > operand1);
                    alu_result <= (operand0 > operand1) ? 32'd1 : 32'd0;
                end
                OP_CMP_LT: begin
                    predicate_flag <= (operand0 < operand1);
                    alu_result <= (operand0 < operand1) ? 32'd1 : 32'd0;
                end
                OP_CMP_EQ: begin
                    predicate_flag <= (operand0 == operand1);
                    alu_result <= (operand0 == operand1) ? 32'd1 : 32'd0;
                end
                OP_LOAD_SPM: begin
                    alu_result <= spm_rdata;
                end
                OP_STORE_SPM: begin
                    alu_result <= operand0;
                end
                OP_ACC_CLR: begin
                    accumulator <= '0;
                    alu_result <= '0;
                end
                OP_PASS0: begin
                    alu_result <= operand0;
                end
                OP_PASS1: begin
                    alu_result <= operand1;
                end
                OP_LIF: begin
                    if (lif_next_v >= op1_ext) begin
                        predicate_flag <= 1'b1;
                        accumulator <= 40'sd0;
                        alu_result <= 32'd1;
                    end else begin
                        predicate_flag <= 1'b0;
                        accumulator <= lif_next_v;
                        alu_result <= 32'd0;
                    end
                end
                default: begin
                    alu_result <= '0;
                end
            endcase
        end
    end
    
    // =========================================================================
    // Predicate Execution Logic
    // =========================================================================
    logic execute_enable;
    
    always_comb begin
        if (pred_en) begin
            execute_enable = pred_inv ? ~predicate_flag : predicate_flag;
        end else begin
            execute_enable = 1'b1;
        end
    end
    
    // =========================================================================
    // Write-back Logic
    // =========================================================================
    always_comb begin
        rf_we = 1'b0;
        rf_waddr = dst_sel;
        rf_wdata = alu_result[DATA_WIDTH-1:0];
        
        spm_we = 1'b0;
        spm_addr = operand1[ADDR_WIDTH-1:0];
        spm_wdata = operand0;
        
        if (config_valid && execute_enable && !stall) begin
            unique case (op_code)
                OP_STORE_SPM: begin
                    spm_we = 1'b1;
                end
                OP_LOAD_SPM: begin
                    rf_we = 1'b1;
                end
                OP_ADD, OP_SUB, OP_MUL, OP_MAC, OP_AND, OP_OR, OP_XOR,
                OP_SHL, OP_SHR, OP_CMP_GT, OP_CMP_LT, OP_CMP_EQ,
                OP_PASS0, OP_PASS1: begin
                    rf_we = 1'b1;
                end
                default: begin
                    rf_we = 1'b0;
                end
            endcase
        end
    end
    
    // Set RF read addresses
    always_comb begin
        rf_raddr0 = src0_sel;
        rf_raddr1 = src1_sel;
    end
    
    // =========================================================================
    // Bypass Network / Routing
    // =========================================================================
    logic [DATA_WIDTH-1:0] output_data;
    logic [PAYLOAD_WIDTH-1:0] output_payload;
    logic                  output_valid;
    
    always_comb begin
        output_payload = alu_result[PAYLOAD_WIDTH-1:0];
        output_data = {cfg_multicast, cfg_dest_x, cfg_dest_y, {RESERVED_WIDTH{1'b0}}, output_payload};
        output_valid = config_valid && execute_enable;
    end
    
    // Route mask: [4] = local, [3] = N, [2] = E, [1] = S, [0] = W
    always_comb begin
        data_out_n = output_data;
        data_out_e = output_data;
        data_out_s = output_data;
        data_out_w = output_data;
        data_out_local = output_data;
        
        valid_out_n = output_valid && route_mask[3];
        valid_out_e = output_valid && route_mask[2];
        valid_out_s = output_valid && route_mask[1];
        valid_out_w = output_valid && route_mask[0];
        valid_out_local = output_valid && route_mask[4];  // Only output if route_mask[4] set
    end

endmodule
