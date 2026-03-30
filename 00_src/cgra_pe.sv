// ==============================================================================
// CGRA Processing Element (PE) - v2.4
// ==============================================================================
// A configurable processing element supporting 21 ALU operations, 16-entry
// register file, 256×32-bit scratchpad, and 16-context configuration RAM.
//
// CHANGELOG (v2.4 - January 2026):
//   - Fixed immediate sign-extension logic (opcode 2/11 bugs)
//   - Fixed routing mask width mismatches (lint clean)
//   - Validated against 6000-vector constrained random regression (AD suite)
//
//
// ARCHITECTURE:
//   - ALU/MAC with 40-bit saturating accumulator
//   - 16×32-bit Register File (flip-flop)
//   - 256×32-bit Scratchpad Memory (SRAM)
//   - 16×64-bit Configuration RAM (BSG SRAM wrapper)
//   - 4-direction mesh broadcast (32-bit full precision)
//   - LIF neuron for neuromorphic computing (spiking)
//
// ISA (21 Operations, opcodes 0-20, including LPR/ANN extensions):
//   Op | Name       | Operation              | Latency
//   ---|------------|------------------------|--------
//   0  | NOP        | No operation           | 1 cycle
//   1  | ADD        | A + B (sat), Acc=ext   | 1 cycle  (also updates accumulator)
//   2  | SUB        | A - B (sat), Acc=ext   | 1 cycle  (also updates accumulator)
//   3  | MUL        | A × B (32-bit)         | 1 cycle
//   4  | MAC        | Acc += A × B           | 1 cycle
//   5  | AND        | A & B                  | 1 cycle
//   6  | OR         | A | B                  | 1 cycle
//   7  | XOR        | A ^ B                  | 1 cycle
//   8  | SHL        | A << B[4:0]            | 1 cycle
//   9  | SHR        | A >>> B[4:0] (arith)   | 1 cycle
//  10  | CMP_GT     | (A > B) ? 1 : 0        | 1 cycle
//  11  | CMP_LT     | (A < B) ? 1 : 0        | 1 cycle
//  12  | CMP_EQ     | (A == B) ? 1 : 0       | 1 cycle
//  13  | LOAD_SPM   | Load from scratchpad   | 1 cycle
//  14  | STORE_SPM  | Store to scratchpad    | 1 cycle
//  15  | ACC_CLR    | Clear accumulator      | 1 cycle
//  16  | PASS0      | Pass operand A         | 1 cycle
//  17  | PASS1      | Pass operand B         | 1 cycle
//  18  | LIF        | Leaky Integrate-Fire   | 1 cycle
//  19  | RELU       | max(0, A)              | 1 cycle
//  20  | MAX        | max(A, B) signed       | 1 cycle
//
// OPERAND SOURCES (src0_sel, src1_sel):
//   0 = Register File    4 = West neighbor (Tile Memory)
//   1 = North neighbor   5 = Scratchpad Memory
//   2 = East neighbor    6 = 16-bit Immediate
//   3 = South neighbor
//
// VERIFICATION: 141/141 tests passed (base ISA) + LPR extensions pending
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
    
    // Routing inputs (from N/E/S/W neighbors) - Full 32-bit data path
    input  logic [DATA_WIDTH-1:0] data_in_n,
    input  logic [DATA_WIDTH-1:0] data_in_e,
    input  logic [DATA_WIDTH-1:0] data_in_s,
    input  logic [DATA_WIDTH-1:0] data_in_w,
    /* verilator lint_off UNUSEDSIGNAL */
    input  logic                  valid_in_n,  // Unused: mesh broadcast mode — data always available (ASSIGN-10)
    input  logic                  valid_in_e,  // Unused: kept for interface compatibility & future flow-control
    input  logic                  valid_in_s,  // Unused: tile.sv bypasses router, feeds PE direct from neighbors
    input  logic                  valid_in_w,  // Unused: tile memory valid comes via edge_valid_in_w instead
    /* verilator lint_on UNUSEDSIGNAL */
    
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
    output logic                  ready_out,

    // B4: Dynamic branch output (from PE to CU via top level)
    output logic [PC_WIDTH-1:0]   branch_target_o,
    output logic                  branch_taken_o
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
    // B4: Dynamic branching
    logic [PC_WIDTH-1:0]   branch_target;
    logic                  branch_en;

    localparam int HEADER_WIDTH  = DATA_WIDTH - PAYLOAD_WIDTH;
    localparam int RESERVED_WIDTH = HEADER_WIDTH - (1 + (2 * COORD_WIDTH));

    // =========================================================================
    // Config RAM (The "Recipe Book" - 16 config slots using BSG Memory)
    // =========================================================================
    // Uses cgra_config_mem_bsg wrapper around bsg_mem_1r1w_sync for ASIC synthesis
    // Note: BSG memory has 1-cycle read latency, rd_valid indicates data ready
    // FIX: read_write_same_addr_p=1 prevents X on simultaneous read/write
    
    logic [63:0] config_ram_data;
    logic [63:0] active_config;
    logic        config_ram_valid;  // Used in config_active OR gate below
    
    cgra_config_mem_bsg #(
        .DATA_WIDTH(64),
        .DEPTH     (CONTEXT_DEPTH),
        .ADDR_WIDTH(PC_WIDTH)
    ) u_config_mem (
        .clk     (clk),
        .rst_n   (rst_n),
        // Write port (from DMA/testbench)
        .wr_addr (cfg_wr_addr),
        .wr_data (cfg_wr_data),
        .wr_en   (cfg_wr_en),
        // Read port (indexed by context_pc)
        .rd_addr (context_pc),
        .rd_en   (1'b1),              // Always read (PE needs config every cycle)
        .rd_data (config_ram_data),
        .rd_valid(config_ram_valid)   // 1-cycle delayed valid
    );
    
    // Select active config:
    // - config_valid=1 (execution): Use config_frame from cgra_top.sv.
    //   cgra_top indexes config_frames[pe_id][context_pc] — a 2D register
    //   array with combinational read, zero latency, cycling per-context.
    // - config_valid=0 (idle): Use config_ram_data from BSG SRAM.
    assign active_config = config_valid ? config_frame : config_ram_data;

    // FIX: config_active is true whenever PE has valid configuration
    // In single-config mode: config_valid=1 from parent
    // In multi-context mode: config_ram_valid=1 after 1-cycle BSG read latency
    // This replaces the incorrect use of config_valid alone which broke multi-context
    logic config_active;
    assign config_active = config_valid || config_ram_valid;

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
        route_mask = {1'b0, active_config[21:18]};  // FIX: Zero-extend 4-bit to 5-bit
        pred_en    = active_config[22];
        pred_inv   = active_config[23];
        immediate  = active_config[39:24];
        extended   = active_config[63:40];
        cfg_dest_x = extended[COORD_WIDTH-1:0];
        cfg_dest_y = extended[(2 * COORD_WIDTH)-1:COORD_WIDTH];
        cfg_multicast = extended[2 * COORD_WIDTH];
        // B4: Branch target from config frame bits [47:44] = extended[7:4]
        branch_target = extended[PC_WIDTH+3:4];
        branch_en = extended[PC_WIDTH+4];  // bit [48] = extended[8]: enable branch
    end
    
    // =========================================================================
    // Scratchpad Memory (SPM)
    // =========================================================================
    logic [DATA_WIDTH-1:0] spm_mem [0:SPM_DEPTH-1];
    logic [$clog2(SPM_DEPTH)-1:0] spm_addr;
    logic [DATA_WIDTH-1:0] spm_rdata;
    logic [DATA_WIDTH-1:0] spm_wdata;
    logic                  spm_we;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            spm_rdata <= '0;
        end else begin
            if (spm_we && !stall) begin
                spm_mem[spm_addr] <= spm_wdata;
            end
            if (!stall) begin
                spm_rdata <= spm_mem[spm_addr];
            end
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
    
    // =========================================================================
    // FULL 32-BIT DATA PATH (FIX: Removed 16-bit payload bottleneck)
    // =========================================================================
    // Previously extracted only PAYLOAD_WIDTH (16) bits and sign-extended.
    // Now using full DATA_WIDTH (32) for proper data flow between PEs.
    logic [DATA_WIDTH-1:0] data_in_n_full;
    logic [DATA_WIDTH-1:0] data_in_e_full;
    logic [DATA_WIDTH-1:0] data_in_s_full;
    logic [DATA_WIDTH-1:0] data_in_w_full;

    assign data_in_n_full = data_in_n;  // Full 32-bit passthrough
    assign data_in_e_full = data_in_e;
    assign data_in_s_full = data_in_s;
    assign data_in_w_full = data_in_w;
    
    always_comb begin
        // src0 selection (now uses full 32-bit data)
        unique case (src0_sel)
            4'd0:    operand0 = rf_rdata0;
            4'd1:    operand0 = data_in_n_full;   // Full 32-bit from North
            4'd2:    operand0 = data_in_e_full;   // Full 32-bit from East
            4'd3:    operand0 = data_in_s_full;   // Full 32-bit from South
            4'd4:    operand0 = data_in_w_full;   // Full 32-bit from West
            4'd5:    operand0 = spm_rdata;
            4'd6:    operand0 = {{16{immediate[15]}}, immediate};  // FIX: Sign-extend 16-bit to 32-bit
            default: operand0 = '0;
        endcase
        
        // src1 selection (now uses full 32-bit data)
        unique case (src1_sel)
            4'd0:    operand1 = rf_rdata1;
            4'd1:    operand1 = data_in_n_full;   // Full 32-bit from North
            4'd2:    operand1 = data_in_e_full;   // Full 32-bit from East
            4'd3:    operand1 = data_in_s_full;   // Full 32-bit from South
            4'd4:    operand1 = data_in_w_full;   // Full 32-bit from West
            4'd5:    operand1 = spm_rdata;
            4'd6:    operand1 = {{16{immediate[15]}}, immediate};  // FIX: Sign-extend 16-bit to 32-bit
            default: operand1 = '0;
        endcase
    end
    
    // =========================================================================
    // Pipeline Register: Decode/Fetch → Execute
    // =========================================================================
    // Cuts the critical path between operand mux and ALU compute.
    // Stage 1 (this cycle): config decode + operand mux → latch into _r regs
    // Stage 2 (next cycle): ALU compute on registered operands → alu_result
    // Enables DSP48 input pipelining (AREG=1, BREG=1) for timing closure.
    logic [DATA_WIDTH-1:0] operand0_r, operand1_r;
    logic [5:0]            op_code_r;
    logic [3:0]            dst_sel_r;
    logic [4:0]            route_mask_r;
    logic                  pred_en_r, pred_inv_r;
    logic [15:0]           immediate_r;
    logic                  config_active_r;
    logic [DATA_WIDTH-1:0] spm_rdata_r;
    logic [PC_WIDTH-1:0]   branch_target_r;
    logic                  branch_en_r;

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            operand0_r     <= '0;
            operand1_r     <= '0;
            op_code_r      <= '0;
            dst_sel_r      <= '0;
            route_mask_r   <= '0;
            pred_en_r      <= 1'b0;
            pred_inv_r     <= 1'b0;
            immediate_r    <= '0;
            config_active_r <= 1'b0;
            spm_rdata_r    <= '0;
            branch_target_r <= '0;
            branch_en_r    <= 1'b0;
        end else if (!stall) begin
            operand0_r     <= operand0;
            operand1_r     <= operand1;
            op_code_r      <= op_code;
            dst_sel_r      <= dst_sel;
            route_mask_r   <= route_mask;
            pred_en_r      <= pred_en;
            pred_inv_r     <= pred_inv;
            immediate_r    <= immediate;
            config_active_r <= config_active;
            spm_rdata_r    <= spm_rdata;
            branch_target_r <= branch_target;
            branch_en_r    <= branch_en;
        end
    end

    // B4: branch_target_o assigned here; branch_taken_o assigned after execute_enable decl

    assign branch_target_o = branch_target_r;

    // =========================================================================
    // ALU/MAC Unit (operates on REGISTERED operands from pipeline stage)
    // =========================================================================
    logic [31:0]           alu_result;
    logic signed [39:0]    accumulator;
    logic                  predicate_flag;
    logic signed [39:0]    op0_ext;
    logic signed [39:0]    op1_ext;
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
    logic signed [40:0] mac_sum_temp;
    logic signed [40:0] lif_sum_temp;   // FIX: 41-bit intermediate for LIF overflow saturation
    logic signed [63:0] mult_full;
    
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
    localparam OP_RELU  = 6'd19;  // ReLU: max(0, A) for ANN activation
    localparam OP_MAX   = 6'd20;  // MAX: max(A, B) signed for pooling
    
    always_comb begin
        op0_ext = {{(40-DATA_WIDTH){operand0_r[DATA_WIDTH-1]}}, operand0_r};
        op1_ext = {{(40-DATA_WIDTH){operand1_r[DATA_WIDTH-1]}}, operand1_r};

        // Widen registered operands to 64-bit BEFORE multiply for full precision.
        mult_full = $signed({{(64-DATA_WIDTH){operand0_r[DATA_WIDTH-1]}}, operand0_r})
                  * $signed({{(64-DATA_WIDTH){operand1_r[DATA_WIDTH-1]}}, operand1_r});
        
        // Check for 40-bit overflow
        // If all bits from [63:39] are NOT identical, we have overflow beyond 40 bits.
        // (Sign bit [63] must match effectively the sign of the 40-bit result [39]).
        // Actually, valid 40-bit number has [63:39] all 0 (positive) or all 1 (negative).
        // So we check if mult_full[63:39] are ALL 0 or ALL 1.
        if (&mult_full[63:39] == 1'b1 || |mult_full[63:39] == 1'b0) begin
            // No overflow, fits in 40 bits
            mult_ext = mult_full[39:0];
        end else begin
            // Overflow. Saturate to MAX/MIN 40-bit value based on sign (bit 63)
            if (mult_full[63] == 1'b0) mult_ext = 40'sd549755813887;  // MAX_POS (2^39 - 1)
            else                       mult_ext = -40'sd549755813888; // MIN_NEG (-2^39)
        end
        
        add_result = op0_ext + op1_ext;
        sub_result = op0_ext - op1_ext;
        
        // ========================================================================
        // LIF SATURATION FIX — January 2026
        // ========================================================================
        // Problem: lif_next_v = accumulator + op0_ext - LIF_LEAK could overflow
        //          the 40-bit signed range if accumulator is near saturation.
        // Solution: Use 41-bit intermediate (lif_sum_temp) to detect overflow,
        //           then saturate to 40-bit MAX_POS/MIN_NEG, matching MAC pattern.
        // ========================================================================
        lif_sum_temp = {accumulator[39], accumulator} + {op0_ext[39], op0_ext} - {{1{LIF_LEAK[39]}}, LIF_LEAK};
        if (lif_sum_temp > 41'sd549755813887)
            lif_next_v = 40'sd549755813887;   // MAX_POS_40 = 2^39 - 1
        else if (lif_sum_temp < -41'sd549755813888)
            lif_next_v = -40'sd549755813888;  // MIN_NEG_40 = -2^39
        else
            lif_next_v = lif_sum_temp[39:0];
        
        // ========================================================================
        // MULTIPLY-ACCUMULATE (MAC) SATURATION FIX - January 2026
        // ========================================================================
        // Problem: 40-bit accumulator can overflow when adding 40-bit mult_ext.
        //          Simple addition `accumulator + mult_ext` wraps at 40 bits.
        // Solution: Use 41-bit intermediate (mac_sum_temp) to detect overflow,
        //           then saturate to 40-bit MAX_POS/MIN_NEG before storing.
        // ========================================================================
        mac_sum_temp = accumulator + mult_ext;
        if (mac_sum_temp > 41'sd549755813887) begin
            mac_sum = 40'sd549755813887;  // MAX_POS_40 = 2^39 - 1
        end else if (mac_sum_temp < -41'sd549755813888) begin
            mac_sum = -40'sd549755813888; // MIN_NEG_40 = -2^39
        end else begin
            mac_sum = mac_sum_temp[39:0];
        end
        
        // Inline saturation for ADD result (FIX: Use explicit 40-bit signed literals)
        if (add_result > 40'sd2147483647) begin
            add_result_sat = 32'h7FFFFFFF;
        end else if (add_result < -40'sd2147483648) begin
            add_result_sat = 32'h80000000;
        end else begin
            add_result_sat = add_result[31:0];
        end
        
        // Inline saturation for SUB result (FIX: Use explicit 40-bit signed literals)
        if (sub_result > 40'sd2147483647) begin
            sub_result_sat = 32'h7FFFFFFF;
        end else if (sub_result < -40'sd2147483648) begin
            sub_result_sat = 32'h80000000;
        end else begin
            sub_result_sat = sub_result[31:0];
        end
        
        // Inline saturation for MAC result (FIX: Saturate to 32-bit signed range)
        if (mac_sum > 40'sd2147483647) begin
            mac_result_sat = 32'h7FFFFFFF;
        end else if (mac_sum < -40'sd2147483648) begin
            mac_result_sat = 32'h80000000;
        end else begin
            mac_result_sat = mac_sum[31:0];
        end
    end
    
    // =========================================================================
    // Predicate Execution Logic (must precede ALU for Xcelium forward-ref)
    // =========================================================================
    logic execute_enable;
    
    always_comb begin
        if (pred_en_r) begin
            execute_enable = pred_inv_r ? ~predicate_flag : predicate_flag;
        end else begin
            execute_enable = 1'b1;
        end
    end
    
    // B4: Branch taken when branch enabled in config AND predicate condition met
    assign branch_taken_o = config_active_r && !stall && branch_en_r && execute_enable;

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            accumulator <= '0;
            predicate_flag <= 1'b0;
            // NOTE: alu_result intentionally NOT reset here.
            // run_cgra() stops execution via soft_reset which triggers pe_reset_n → 0.
            // If alu_result were reset, the computed result would be wiped before
            // the testbench reads it. NOP preserves alu_result (no-op).
        end else if (config_active_r && !stall && execute_enable) begin
            unique case (op_code_r)
                OP_NOP: begin
                    // FIX: NOP preserves alu_result (no-op means no change).
                    // Previously zeroed alu_result, which destroyed routed data
                    // mid-pipeline in multi-context execution scenarios.
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
                    // FIX: Reuse mult_full (already computed above) instead of
                    // inferring a second 32×32 multiplier per PE.
                    alu_result <= mult_full[31:0];
                end
                OP_MAC: begin
                    accumulator <= mac_sum;
                    alu_result <= mac_result_sat;
                end
                OP_AND: begin
                    alu_result <= operand0_r & operand1_r;
                end
                OP_OR: begin
                    alu_result <= operand0_r | operand1_r;
                end
                OP_XOR: begin
                    alu_result <= operand0_r ^ operand1_r;
                end
                OP_SHL: begin
                    alu_result <= operand0_r << operand1_r[4:0];
                end
                OP_SHR: begin
                    alu_result <= $signed(operand0_r) >>> operand1_r[4:0];
                end
                OP_CMP_GT: begin
                    predicate_flag <= ($signed(operand0_r) > $signed(operand1_r));
                    alu_result <= ($signed(operand0_r) > $signed(operand1_r)) ? 32'd1 : 32'd0;
                end
                OP_CMP_LT: begin
                    predicate_flag <= ($signed(operand0_r) < $signed(operand1_r));
                    alu_result <= ($signed(operand0_r) < $signed(operand1_r)) ? 32'd1 : 32'd0;
                end
                OP_CMP_EQ: begin
                    predicate_flag <= (operand0_r == operand1_r);
                    alu_result <= (operand0_r == operand1_r) ? 32'd1 : 32'd0;
                end
                OP_LOAD_SPM: begin
                    alu_result <= spm_rdata_r;
                end
                OP_STORE_SPM: begin
                    alu_result <= operand0_r;
                end
                OP_ACC_CLR: begin
                    accumulator <= '0;
                    alu_result <= '0;
                end
                OP_PASS0: begin
                    alu_result <= operand0_r;
                end
                OP_PASS1: begin
                    alu_result <= operand1_r;
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
                OP_RELU: begin
                    // ReLU activation: max(0, A) — used by ANN/LPR layers
                    // Treats operand0 as signed; clamps negative to zero
                    alu_result <= ($signed(operand0_r) > 0) ? operand0_r : 32'd0;
                end
                OP_MAX: begin
                    // Signed maximum: max(A, B) — used for max-pooling layers
                    alu_result <= ($signed(operand0_r) > $signed(operand1_r)) ? operand0_r : operand1_r;
                end
                default: begin
                    alu_result <= '0;
                end
            endcase
        end
    end
    
    // =========================================================================
    // Write-back Logic
    // =========================================================================
    always_comb begin
        rf_we = 1'b0;
        rf_waddr = dst_sel_r;
        rf_wdata = alu_result[DATA_WIDTH-1:0];

        spm_we = 1'b0;
        spm_addr = operand1_r[$clog2(SPM_DEPTH)-1:0];
        spm_wdata = operand0_r;

        if (config_active_r && execute_enable && !stall) begin
            unique case (op_code_r)
                OP_STORE_SPM: begin
                    spm_we = 1'b1;
                end
                OP_LOAD_SPM: begin
                    rf_we = 1'b1;
                end
                OP_ADD, OP_SUB, OP_MUL, OP_MAC, OP_AND, OP_OR, OP_XOR,
                OP_SHL, OP_SHR, OP_CMP_GT, OP_CMP_LT, OP_CMP_EQ,
                OP_PASS0, OP_PASS1, OP_LIF, OP_RELU, OP_MAX: begin
                    // FIX: Added OP_LIF — LIF produces spike result (0/1)
                    // that should be written to RF like other result-producing ops.
                    // Without this, LIF output was only available via the routing
                    // network, not the register file, preventing downstream RF use.
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
    logic                  output_valid;
    
    always_comb begin
        // FIX: Output full 32-bit ALU result instead of 16-bit truncated payload
        // Previous code packed {multicast, dest_x, dest_y, reserved, payload[15:0]}
        // which lost upper 16 bits of computation. Since the PE array uses direct
        // broadcast (not XY routing), full 32-bit precision is required.
        output_data = alu_result;
        // FIX: Gate output_valid with !stall to prevent re-consumption of stale data
        output_valid = config_active_r && execute_enable && !stall;
    end

    // Route mask: [4] = local, [3] = N, [2] = E, [1] = S, [0] = W
    always_comb begin
        data_out_n = output_data;
        data_out_e = output_data;
        data_out_s = output_data;
        data_out_w = output_data;
        data_out_local = output_data;

        valid_out_n = output_valid && route_mask_r[3];
        valid_out_e = output_valid && route_mask_r[2];
        valid_out_s = output_valid && route_mask_r[1];
        valid_out_w = output_valid && route_mask_r[0];
        valid_out_local = output_valid && route_mask_r[4];
    end

endmodule
