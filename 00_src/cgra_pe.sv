// cgra_pe.sv — Processing Element.
// 21-op ALU/MAC (40-bit saturating accumulator) + 16-entry RF +
// 256×32-bit scratchpad + 16-slot config BRAM.
// Operand sources (src*_sel): 0=RF  1=N  2=E  3=S  4=W  5=SPM  6=imm16.
// Directional outputs (data_out_n/e/s/w + valid_out_*) feed mesh broadcast.

module cgra_pe #(
    parameter DATA_WIDTH  = 32,
    parameter COORD_WIDTH = 4,
    parameter ADDR_WIDTH  = 8,
    parameter SPM_DEPTH   = 256,
    parameter RF_DEPTH    = 16,
    parameter CONTEXT_DEPTH = 16,
    parameter PC_WIDTH    = 4
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


    // PE broadcasts the same payload to all 4 directions; valid_out_*
    // are gated per-direction by the configured route_mask.
    output logic [DATA_WIDTH-1:0] data_out,
    output logic                  valid_out_n,
    output logic                  valid_out_e,
    output logic                  valid_out_s,
    output logic                  valid_out_w,

    // Dynamic branch output (from PE predicate to CU)
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
    // B4: Dynamic branching
    logic [PC_WIDTH-1:0]   branch_target;
    logic                  branch_en;
    // B1: Mixed-precision mode
    logic [1:0]            data_mode;  // 00=INT32, 01=INT16x2, 10=INT8x4

    // Config RAM: 16 slots × 64b via BSG SRAM wrapper (1-cycle read latency).
    logic [63:0] config_ram_data;
    logic [63:0] active_config;
    logic        config_ram_valid;
    
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

    // Active whenever a valid config is present (parent-driven or BSG-read).
    logic config_active;
    assign config_active = config_valid || config_ram_valid;

    // =========================================================================
    // Stall Logic
    // =========================================================================
    // Stall when router cannot accept output OR global stall is asserted
    logic stall;
    assign stall = global_stall;
    
    // =========================================================================
    // Configuration frame decoding (decodes active_config)
    // =========================================================================
    always_comb begin
        op_code    = active_config[5:0];
        src0_sel   = active_config[9:6];
        src1_sel   = active_config[13:10];
        dst_sel    = active_config[17:14];
        route_mask = {1'b0, active_config[21:18]};
        pred_en    = active_config[22];
        pred_inv   = active_config[23];
        immediate  = active_config[39:24];
        extended   = active_config[63:40];
        // B4: Branch target from config frame bits [47:44] = extended[7:4]
        branch_target = extended[PC_WIDTH+3:4];
        branch_en = extended[PC_WIDTH+4];  // bit [48] = extended[8]: enable branch
        // B1: Data mode from config frame bits [50:49] = extended[10:9]
        data_mode = extended[10:9];
    end
    
    // Scratchpad memory (256×32b)
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
    
    // Register file (16×32b flip-flops)
    logic [DATA_WIDTH-1:0] rf_mem [0:RF_DEPTH-1];
    logic [3:0]            rf_waddr;
    logic [DATA_WIDTH-1:0] rf_wdata;
    logic                  rf_we;
    wire  [DATA_WIDTH-1:0] rf_rdata0 = rf_mem[src0_sel];
    wire  [DATA_WIDTH-1:0] rf_rdata1 = rf_mem[src1_sel];
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            rf_mem[0]  <= '0; rf_mem[1]  <= '0; rf_mem[2]  <= '0; rf_mem[3]  <= '0;
            rf_mem[4]  <= '0; rf_mem[5]  <= '0; rf_mem[6]  <= '0; rf_mem[7]  <= '0;
            rf_mem[8]  <= '0; rf_mem[9]  <= '0; rf_mem[10] <= '0; rf_mem[11] <= '0;
            rf_mem[12] <= '0; rf_mem[13] <= '0; rf_mem[14] <= '0; rf_mem[15] <= '0;
        end else if (rf_we && !stall) begin
            rf_mem[rf_waddr] <= rf_wdata;
        end
    end
    
    // Operand multiplexing
    logic [DATA_WIDTH-1:0] operand0;
    logic [DATA_WIDTH-1:0] operand1;

    always_comb begin
        unique case (src0_sel)
            4'd0:    operand0 = rf_rdata0;
            4'd1:    operand0 = data_in_n;
            4'd2:    operand0 = data_in_e;
            4'd3:    operand0 = data_in_s;
            4'd4:    operand0 = data_in_w;
            4'd5:    operand0 = spm_rdata;
            4'd6:    operand0 = {{16{immediate[15]}}, immediate};
            default: operand0 = '0;
        endcase

        unique case (src1_sel)
            4'd0:    operand1 = rf_rdata1;
            4'd1:    operand1 = data_in_n;
            4'd2:    operand1 = data_in_e;
            4'd3:    operand1 = data_in_s;
            4'd4:    operand1 = data_in_w;
            4'd5:    operand1 = spm_rdata;
            4'd6:    operand1 = {{16{immediate[15]}}, immediate};
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
    logic                  config_active_r;
    logic [DATA_WIDTH-1:0] spm_rdata_r;
    logic [PC_WIDTH-1:0]   branch_target_r;
    logic                  branch_en_r;
    logic [1:0]            data_mode_r;

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            operand0_r     <= '0;
            operand1_r     <= '0;
            op_code_r      <= '0;
            dst_sel_r      <= '0;
            route_mask_r   <= '0;
            pred_en_r      <= 1'b0;
            pred_inv_r     <= 1'b0;
            config_active_r <= 1'b0;
            spm_rdata_r    <= '0;
            branch_target_r <= '0;
            branch_en_r    <= 1'b0;
            data_mode_r    <= 2'b00;
        end else if (!stall) begin
            operand0_r     <= operand0;
            operand1_r     <= operand1;
            op_code_r      <= op_code;
            dst_sel_r      <= dst_sel;
            route_mask_r   <= route_mask;
            pred_en_r      <= pred_en;
            pred_inv_r     <= pred_inv;
            config_active_r <= config_active;
            spm_rdata_r    <= spm_rdata;
            branch_target_r <= branch_target;
            branch_en_r    <= branch_en;
            data_mode_r    <= data_mode;
        end
    end

    // =========================================================================
    // OpCode Definitions
    // =========================================================================
    localparam OP_NOP   = 6'd0;
    localparam OP_ADD   = 6'd1;
    localparam OP_SUB   = 6'd2;
    localparam OP_MUL   = 6'd3;
    localparam OP_MAC   = 6'd4;
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
    localparam OP_RELU  = 6'd19;
    localparam OP_MAX   = 6'd20;

    // Saturation constants
    localparam signed [39:0] LIF_LEAK = 40'sd10;

    // Forward declarations for cross-stage signals
    logic [31:0]           alu_result;
    logic signed [39:0]    accumulator;
    logic                  predicate_flag;

    // =========================================================================
    // Stage 2 Combinational: Multiply + SIMD + Extend (feeds _r2 registers)
    // =========================================================================
    // This is the first half of the old monolithic ALU comb block.
    // Critical path: DSP48 multiply + 40-bit overflow check (~10ns)
    logic signed [39:0]    op0_ext;
    logic signed [39:0]    op1_ext;
    logic signed [63:0]    mult_full;
    logic signed [39:0]    mult_ext;
    logic signed [39:0]    add_result;
    logic signed [39:0]    sub_result;
    logic signed [39:0]    lif_next_v;
    logic signed [40:0]    lif_sum_temp;
    logic signed [31:0]    simd_dot_product;

    // INT8 lane extraction (signed)
    wire signed [7:0] op0_b3 = operand0_r[31:24];
    wire signed [7:0] op0_b2 = operand0_r[23:16];
    wire signed [7:0] op0_b1 = operand0_r[15:8];
    wire signed [7:0] op0_b0 = operand0_r[7:0];
    wire signed [7:0] op1_b3 = operand1_r[31:24];
    wire signed [7:0] op1_b2 = operand1_r[23:16];
    wire signed [7:0] op1_b1 = operand1_r[15:8];
    wire signed [7:0] op1_b0 = operand1_r[7:0];

    // INT16 lane extraction (signed)
    wire signed [15:0] op0_h1 = operand0_r[31:16];
    wire signed [15:0] op0_h0 = operand0_r[15:0];
    wire signed [15:0] op1_h1 = operand1_r[31:16];
    wire signed [15:0] op1_h0 = operand1_r[15:0];

    // SIMD dot-product (reads _r operands)
    always_comb begin
        case (data_mode_r)
            2'b10:   simd_dot_product = (32'(op0_b3) * 32'(op1_b3)) +
                                        (32'(op0_b2) * 32'(op1_b2)) +
                                        (32'(op0_b1) * 32'(op1_b1)) +
                                        (32'(op0_b0) * 32'(op1_b0));
            2'b01:   simd_dot_product = (32'(op0_h1) * 32'(op1_h1)) +
                                        (32'(op0_h0) * 32'(op1_h0));
            default: simd_dot_product = operand0_r * operand1_r;
        endcase
    end

    // Multiply, extend, add/sub, LIF (all read _r operands)
    always_comb begin
        op0_ext = {{(40-DATA_WIDTH){operand0_r[DATA_WIDTH-1]}}, operand0_r};
        op1_ext = {{(40-DATA_WIDTH){operand1_r[DATA_WIDTH-1]}}, operand1_r};

        // 64-bit multiply for overflow detection
        mult_full = $signed({{(64-DATA_WIDTH){operand0_r[DATA_WIDTH-1]}}, operand0_r})
                  * $signed({{(64-DATA_WIDTH){operand1_r[DATA_WIDTH-1]}}, operand1_r});

        // 40-bit overflow check + saturation
        if (&mult_full[63:39] == 1'b1 || |mult_full[63:39] == 1'b0)
            mult_ext = mult_full[39:0];
        else if (mult_full[63] == 1'b0)
            mult_ext = 40'sd549755813887;   // MAX_POS_40
        else
            mult_ext = -40'sd549755813888;  // MIN_NEG_40

        add_result = op0_ext + op1_ext;
        sub_result = op0_ext - op1_ext;

        // LIF: accumulator + input - leak, with 41-bit overflow detection
        lif_sum_temp = {accumulator[39], accumulator} + {op0_ext[39], op0_ext}
                     - {{1{LIF_LEAK[39]}}, LIF_LEAK};
        if (lif_sum_temp > 41'sd549755813887)
            lif_next_v = 40'sd549755813887;
        else if (lif_sum_temp < -41'sd549755813888)
            lif_next_v = -40'sd549755813888;
        else
            lif_next_v = lif_sum_temp[39:0];
    end

    // =========================================================================
    // Predicate Execution Logic (Stage 2 — feeds execute_enable into _r2)
    // =========================================================================
    logic execute_enable;

    always_comb begin
        if (pred_en_r)
            execute_enable = pred_inv_r ? ~predicate_flag : predicate_flag;
        else
            execute_enable = 1'b1;
    end

    // =========================================================================
    // Pipeline Register: Compute → Execute/Saturate (_r2)
    // =========================================================================
    // 3rd pipeline stage: registers between multiply and saturation/writeback.
    // Splits the ~18ns critical path into ~10ns (multiply) + ~7ns (saturate).
    logic signed [39:0] mult_ext_r2;
    logic        [31:0] mult_lower_r2;      // mult_full[31:0] for OP_MUL
    logic signed [31:0] simd_dot_r2;
    logic signed [39:0] add_result_r2;
    logic signed [39:0] sub_result_r2;
    logic signed [39:0] lif_next_v_r2;
    logic signed [39:0] op1_ext_r2;         // For LIF threshold compare

    // Control pipeline
    logic [5:0]  op_code_r2;
    logic [1:0]  data_mode_r2;
    logic        config_active_r2;
    logic        execute_enable_r2;
    logic [31:0] operand0_r2, operand1_r2;  // For simple ops
    logic [3:0]  dst_sel_r2;
    logic [4:0]  route_mask_r2;
    logic [31:0] spm_rdata_r2;
    logic [PC_WIDTH-1:0] branch_target_r2;
    logic        branch_en_r2;

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            mult_ext_r2      <= '0;
            mult_lower_r2    <= '0;
            simd_dot_r2      <= '0;
            add_result_r2    <= '0;
            sub_result_r2    <= '0;
            lif_next_v_r2    <= '0;
            op1_ext_r2       <= '0;
            op_code_r2       <= '0;
            data_mode_r2     <= 2'b00;
            config_active_r2 <= 1'b0;
            execute_enable_r2 <= 1'b0;
            operand0_r2      <= '0;
            operand1_r2      <= '0;
            dst_sel_r2       <= '0;
            route_mask_r2    <= '0;
            spm_rdata_r2     <= '0;
            branch_target_r2 <= '0;
            branch_en_r2     <= 1'b0;
        end else if (!stall) begin
            mult_ext_r2      <= mult_ext;
            mult_lower_r2    <= mult_full[31:0];
            simd_dot_r2      <= simd_dot_product;
            add_result_r2    <= add_result;
            sub_result_r2    <= sub_result;
            lif_next_v_r2    <= lif_next_v;
            op1_ext_r2       <= op1_ext;
            op_code_r2       <= op_code_r;
            data_mode_r2     <= data_mode_r;
            config_active_r2 <= config_active_r;
            execute_enable_r2 <= execute_enable;
            operand0_r2      <= operand0_r;
            operand1_r2      <= operand1_r;
            dst_sel_r2       <= dst_sel_r;
            route_mask_r2    <= route_mask_r;
            spm_rdata_r2     <= spm_rdata_r;
            branch_target_r2 <= branch_target_r;
            branch_en_r2     <= branch_en_r;
        end
    end

    // Branch outputs use _r2 (matches pipeline depth)
    assign branch_target_o = branch_target_r2;
    assign branch_taken_o  = config_active_r2 && !stall && branch_en_r2 && execute_enable_r2;

    // =========================================================================
    // Stage 3 Combinational: Saturation (reads _r2 + accumulator feedback)
    // =========================================================================
    // This is the second half: accumulate + saturate (~7ns)
    logic [31:0]           add_result_sat;
    logic [31:0]           sub_result_sat;
    logic [31:0]           mac_result_sat;
    logic signed [39:0]    mac_sum;
    logic signed [40:0]    mac_sum_temp;

    always_comb begin
        // MAC: accumulator + mult_ext_r2 (accumulator is fresh, mult is pipelined)
        mac_sum_temp = accumulator + mult_ext_r2;
        if (mac_sum_temp > 41'sd549755813887)
            mac_sum = 40'sd549755813887;
        else if (mac_sum_temp < -41'sd549755813888)
            mac_sum = -40'sd549755813888;
        else
            mac_sum = mac_sum_temp[39:0];

        // ADD saturation (40-bit → 32-bit)
        if (add_result_r2 > 40'sd2147483647)
            add_result_sat = 32'h7FFFFFFF;
        else if (add_result_r2 < -40'sd2147483648)
            add_result_sat = 32'h80000000;
        else
            add_result_sat = add_result_r2[31:0];

        // SUB saturation
        if (sub_result_r2 > 40'sd2147483647)
            sub_result_sat = 32'h7FFFFFFF;
        else if (sub_result_r2 < -40'sd2147483648)
            sub_result_sat = 32'h80000000;
        else
            sub_result_sat = sub_result_r2[31:0];

        // MAC saturation (40-bit → 32-bit)
        if (mac_sum > 40'sd2147483647)
            mac_result_sat = 32'h7FFFFFFF;
        else if (mac_sum < -40'sd2147483648)
            mac_result_sat = 32'h80000000;
        else
            mac_result_sat = mac_sum[31:0];
    end

    // =========================================================================
    // ALU Sequential: Execute + Writeback (reads _r2 signals)
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            accumulator <= '0;
            predicate_flag <= 1'b0;
        end else if (config_active_r2 && !stall && execute_enable_r2) begin
            unique case (op_code_r2)
                OP_NOP: begin
                    // Preserves alu_result (no-op)
                end
                OP_ADD: begin
                    accumulator <= add_result_r2;
                    alu_result <= add_result_sat;
                end
                OP_SUB: begin
                    accumulator <= sub_result_r2;
                    alu_result <= sub_result_sat;
                end
                OP_MUL: begin
                    if (data_mode_r2 != 2'b00)
                        alu_result <= simd_dot_r2;
                    else
                        alu_result <= mult_lower_r2;
                end
                OP_MAC: begin
                    if (data_mode_r2 != 2'b00) begin
                        // SIMD MAC: accumulate dot-product with 41-bit overflow detection
                        // (matches INT32 MAC saturation pattern using mac_sum_temp)
                        begin
                            logic signed [40:0] simd_mac_temp;
                            simd_mac_temp = {accumulator[39], accumulator}
                                          + {{9{simd_dot_r2[31]}}, simd_dot_r2};
                            if (simd_mac_temp > 41'sd549755813887)
                                accumulator <= 40'sd549755813887;   // MAX_POS_40
                            else if (simd_mac_temp < -41'sd549755813888)
                                accumulator <= -40'sd549755813888;  // MIN_NEG_40
                            else
                                accumulator <= simd_mac_temp[39:0];
                            // Saturate output to 32-bit
                            if (simd_mac_temp > 41'sd2147483647)
                                alu_result <= 32'h7FFF_FFFF;
                            else if (simd_mac_temp < -41'sd2147483648)
                                alu_result <= 32'h8000_0000;
                            else
                                alu_result <= simd_mac_temp[31:0];
                        end
                    end else begin
                        accumulator <= mac_sum;
                        alu_result <= mac_result_sat;
                    end
                end
                OP_AND:     alu_result <= operand0_r2 & operand1_r2;
                OP_OR:      alu_result <= operand0_r2 | operand1_r2;
                OP_XOR:     alu_result <= operand0_r2 ^ operand1_r2;
                OP_SHL:     alu_result <= operand0_r2 << operand1_r2[4:0];
                OP_SHR:     alu_result <= $signed(operand0_r2) >>> operand1_r2[4:0];
                OP_CMP_GT: begin
                    predicate_flag <= ($signed(operand0_r2) > $signed(operand1_r2));
                    alu_result <= ($signed(operand0_r2) > $signed(operand1_r2)) ? 32'd1 : 32'd0;
                end
                OP_CMP_LT: begin
                    predicate_flag <= ($signed(operand0_r2) < $signed(operand1_r2));
                    alu_result <= ($signed(operand0_r2) < $signed(operand1_r2)) ? 32'd1 : 32'd0;
                end
                OP_CMP_EQ: begin
                    predicate_flag <= (operand0_r2 == operand1_r2);
                    alu_result <= (operand0_r2 == operand1_r2) ? 32'd1 : 32'd0;
                end
                OP_LOAD_SPM:  alu_result <= spm_rdata_r2;
                OP_STORE_SPM: alu_result <= operand0_r2;
                OP_ACC_CLR: begin
                    accumulator <= '0;
                    alu_result <= '0;
                end
                OP_PASS0:   alu_result <= operand0_r2;
                OP_PASS1:   alu_result <= operand1_r2;
                OP_LIF: begin
                    if (lif_next_v_r2 >= op1_ext_r2) begin
                        predicate_flag <= 1'b1;
                        accumulator <= 40'sd0;
                        alu_result <= 32'd1;
                    end else begin
                        predicate_flag <= 1'b0;
                        accumulator <= lif_next_v_r2;
                        alu_result <= 32'd0;
                    end
                end
                OP_RELU:    alu_result <= ($signed(operand0_r2) > 0) ? operand0_r2 : 32'd0;
                OP_MAX:     alu_result <= ($signed(operand0_r2) > $signed(operand1_r2)) ? operand0_r2 : operand1_r2;
                default:    alu_result <= '0;
            endcase
        end
    end

    // =========================================================================
    // Write-back Logic (uses _r2 control signals)
    // =========================================================================
    always_comb begin
        rf_we = 1'b0;
        rf_waddr = dst_sel_r2;
        rf_wdata = alu_result[DATA_WIDTH-1:0];

        spm_we = 1'b0;
        spm_addr = operand1_r2[$clog2(SPM_DEPTH)-1:0];
        spm_wdata = operand0_r2;

        if (config_active_r2 && execute_enable_r2 && !stall) begin
            unique case (op_code_r2)
                OP_STORE_SPM: spm_we = 1'b1;
                OP_LOAD_SPM:  rf_we = 1'b1;
                OP_ADD, OP_SUB, OP_MUL, OP_MAC, OP_AND, OP_OR, OP_XOR,
                OP_SHL, OP_SHR, OP_CMP_GT, OP_CMP_LT, OP_CMP_EQ,
                OP_PASS0, OP_PASS1, OP_LIF, OP_RELU, OP_MAX: rf_we = 1'b1;
                default: rf_we = 1'b0;
            endcase
        end
    end

    // Output broadcast: single data bus, per-direction valid via route_mask
    // (bit[3]=N, bit[2]=E, bit[1]=S, bit[0]=W).
    wire output_valid = config_active_r2 && execute_enable_r2 && !stall;

    assign data_out     = alu_result;
    assign valid_out_n  = output_valid && route_mask_r2[3];
    assign valid_out_e  = output_valid && route_mask_r2[2];
    assign valid_out_s  = output_valid && route_mask_r2[1];
    assign valid_out_w  = output_valid && route_mask_r2[0];

endmodule
