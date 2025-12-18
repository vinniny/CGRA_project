// ==============================================================================
// CGRA Configuration Loader with Double Buffering
// ==============================================================================
// Implements FSM for loading configuration bitstreams into dual context buffers
// Supports atomic context swapping for zero-stall reconfiguration
// Bank0 and Bank1 context memory organization per spec

module cgra_config_loader #(
    parameter NUM_PES = 16,
    parameter CONFIG_WIDTH = 64,
    parameter ADDR_WIDTH = 32,
    parameter MAX_FRAMES = 1024
)(
    input  logic clk,
    input  logic rst_n,
    
    // Control interface from Control Unit
    input  logic                  start_load,
    input  logic [ADDR_WIDTH-1:0] bitstream_addr,
    input  logic [15:0]           bitstream_size,  // Number of frames
    output logic                  load_done,
    output logic                  load_error,
    
    // Context swap control (from Control Unit)
    input  logic                  swap_buffers,
    output logic                  active_buffer,  // 0 = Bank0, 1 = Bank1
    
    // Memory interface (simplified - reads config data)
    output logic [ADDR_WIDTH-1:0] mem_addr,
    output logic                  mem_read,
    input  logic [CONFIG_WIDTH-1:0] mem_rdata,
    input  logic                  mem_valid,
    
    // Configuration outputs to CGRA array (16 PEs)
    output logic [CONFIG_WIDTH-1:0] config_frame_00,
    output logic [CONFIG_WIDTH-1:0] config_frame_01,
    output logic [CONFIG_WIDTH-1:0] config_frame_02,
    output logic [CONFIG_WIDTH-1:0] config_frame_03,
    output logic [CONFIG_WIDTH-1:0] config_frame_10,
    output logic [CONFIG_WIDTH-1:0] config_frame_11,
    output logic [CONFIG_WIDTH-1:0] config_frame_12,
    output logic [CONFIG_WIDTH-1:0] config_frame_13,
    output logic [CONFIG_WIDTH-1:0] config_frame_20,
    output logic [CONFIG_WIDTH-1:0] config_frame_21,
    output logic [CONFIG_WIDTH-1:0] config_frame_22,
    output logic [CONFIG_WIDTH-1:0] config_frame_23,
    output logic [CONFIG_WIDTH-1:0] config_frame_30,
    output logic [CONFIG_WIDTH-1:0] config_frame_31,
    output logic [CONFIG_WIDTH-1:0] config_frame_32,
    output logic [CONFIG_WIDTH-1:0] config_frame_33,
    output logic                   config_valid
);

    // =========================================================================
    // FSM States
    // =========================================================================
    typedef enum logic [2:0] {
        IDLE        = 3'd0,
        LOAD_HEADER = 3'd1,
        LOAD_FRAMES = 3'd2,
        SWAP        = 3'd3,
        DONE        = 3'd4,
        ERROR       = 3'd5
    } state_t;
    
    state_t state, next_state;
    
    // =========================================================================
    // Dual Context Buffers - Bank0 and Bank1 per specification
    // =========================================================================
    // Bank0 Context Memory (16 PE configurations)
    logic [CONFIG_WIDTH-1:0] bank0_00, bank0_01, bank0_02, bank0_03;
    logic [CONFIG_WIDTH-1:0] bank0_10, bank0_11, bank0_12, bank0_13;
    logic [CONFIG_WIDTH-1:0] bank0_20, bank0_21, bank0_22, bank0_23;
    logic [CONFIG_WIDTH-1:0] bank0_30, bank0_31, bank0_32, bank0_33;
    
    // Bank1 Context Memory (16 PE configurations)
    logic [CONFIG_WIDTH-1:0] bank1_00, bank1_01, bank1_02, bank1_03;
    logic [CONFIG_WIDTH-1:0] bank1_10, bank1_11, bank1_12, bank1_13;
    logic [CONFIG_WIDTH-1:0] bank1_20, bank1_21, bank1_22, bank1_23;
    logic [CONFIG_WIDTH-1:0] bank1_30, bank1_31, bank1_32, bank1_33;
    
    logic active_buf_reg;
    logic target_buffer;  // Which bank we're loading into (0=Bank0, 1=Bank1)
    
    // =========================================================================
    // Control registers
    // =========================================================================
    logic [ADDR_WIDTH-1:0] base_addr;
    logic [15:0]           total_frames;
    logic [15:0]           frame_counter;
    logic [3:0]            pe_index;
    
    // =========================================================================
    // FSM Sequential Logic
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end
    
    // =========================================================================
    // FSM Combinational Logic
    // =========================================================================
    always_comb begin
        next_state = state;
        
        unique case (state)
            IDLE: begin
                if (start_load) begin
                    next_state = LOAD_HEADER;
                end
            end
            
            LOAD_HEADER: begin
                next_state = LOAD_FRAMES;
            end
            
            LOAD_FRAMES: begin
                if (frame_counter >= total_frames) begin
                    next_state = DONE;
                end else if (load_error) begin
                    next_state = ERROR;
                end
            end
            
            DONE: begin
                if (swap_buffers) begin
                    next_state = SWAP;
                end else if (!start_load) begin
                    next_state = IDLE;
                end
            end
            
            SWAP: begin
                next_state = IDLE;
            end
            
            ERROR: begin
                if (!start_load) begin
                    next_state = IDLE;
                end
            end
            
            default: next_state = IDLE;
        endcase
    end
    
    // =========================================================================
    // Configuration Loading Logic
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            base_addr <= '0;
            total_frames <= '0;
            frame_counter <= '0;
            pe_index <= '0;
            mem_addr <= '0;
            mem_read <= 1'b0;
            load_done <= 1'b0;
            load_error <= 1'b0;
            target_buffer <= 1'b0;
            
            bank0_00 <= '0; bank0_01 <= '0; bank0_02 <= '0; bank0_03 <= '0;
            bank0_10 <= '0; bank0_11 <= '0; bank0_12 <= '0; bank0_13 <= '0;
            bank0_20 <= '0; bank0_21 <= '0; bank0_22 <= '0; bank0_23 <= '0;
            bank0_30 <= '0; bank0_31 <= '0; bank0_32 <= '0; bank0_33 <= '0;
            
            bank1_00 <= '0; bank1_01 <= '0; bank1_02 <= '0; bank1_03 <= '0;
            bank1_10 <= '0; bank1_11 <= '0; bank1_12 <= '0; bank1_13 <= '0;
            bank1_20 <= '0; bank1_21 <= '0; bank1_22 <= '0; bank1_23 <= '0;
            bank1_30 <= '0; bank1_31 <= '0; bank1_32 <= '0; bank1_33 <= '0;
            
        end else begin
            unique case (state)
                IDLE: begin
                    // Only clear load_done when starting a new load
                    // (This allows external logic to see completion before next load)
                    load_error <= 1'b0;
                    mem_read <= 1'b0;
                    
                    if (start_load) begin
                        load_done <= 1'b0;  // Clear done flag for new load
                        base_addr <= bitstream_addr;
                        total_frames <= bitstream_size;
                        frame_counter <= '0;
                        pe_index <= '0;
                        target_buffer <= ~active_buf_reg;  // Load into inactive buffer
                    end
                end
                
                LOAD_HEADER: begin
                    load_done <= 1'b0;  // Ensure done is clear during loading
                    mem_addr <= base_addr;
                    mem_read <= 1'b1;
                end
                
                LOAD_FRAMES: begin
                    if (mem_read && mem_valid) begin
                        // Write to target buffer based on pe_index
                        if (target_buffer == 1'b0) begin
                            unique case (pe_index)
                                4'd0:  bank0_00 <= mem_rdata;
                                4'd1:  bank0_01 <= mem_rdata;
                                4'd2:  bank0_02 <= mem_rdata;
                                4'd3:  bank0_03 <= mem_rdata;
                                4'd4:  bank0_10 <= mem_rdata;
                                4'd5:  bank0_11 <= mem_rdata;
                                4'd6:  bank0_12 <= mem_rdata;
                                4'd7:  bank0_13 <= mem_rdata;
                                4'd8:  bank0_20 <= mem_rdata;
                                4'd9:  bank0_21 <= mem_rdata;
                                4'd10: bank0_22 <= mem_rdata;
                                4'd11: bank0_23 <= mem_rdata;
                                4'd12: bank0_30 <= mem_rdata;
                                4'd13: bank0_31 <= mem_rdata;
                                4'd14: bank0_32 <= mem_rdata;
                                4'd15: bank0_33 <= mem_rdata;
                                default: begin end
                            endcase
                        end else begin
                            unique case (pe_index)
                                4'd0:  bank1_00 <= mem_rdata;
                                4'd1:  bank1_01 <= mem_rdata;
                                4'd2:  bank1_02 <= mem_rdata;
                                4'd3:  bank1_03 <= mem_rdata;
                                4'd4:  bank1_10 <= mem_rdata;
                                4'd5:  bank1_11 <= mem_rdata;
                                4'd6:  bank1_12 <= mem_rdata;
                                4'd7:  bank1_13 <= mem_rdata;
                                4'd8:  bank1_20 <= mem_rdata;
                                4'd9:  bank1_21 <= mem_rdata;
                                4'd10: bank1_22 <= mem_rdata;
                                4'd11: bank1_23 <= mem_rdata;
                                4'd12: bank1_30 <= mem_rdata;
                                4'd13: bank1_31 <= mem_rdata;
                                4'd14: bank1_32 <= mem_rdata;
                                4'd15: bank1_33 <= mem_rdata;
                                default: begin end
                            endcase
                        end
                        
                        // Update counters
                        frame_counter <= frame_counter + 16'd1;
                        pe_index <= (pe_index == 4'd15) ? 4'd0 : (pe_index + 4'd1);
                        mem_addr <= mem_addr + 32'd1;
                        
                        if (frame_counter + 16'd1 >= total_frames) begin
                            mem_read <= 1'b0;
                        end
                    end else if (!mem_read) begin
                        mem_read <= 1'b1;
                    end
                end
                
                DONE: begin
                    load_done <= 1'b1;
                    mem_read <= 1'b0;
                end
                
                SWAP: begin
                    // Context swap handled in separate always block
                end
                
                ERROR: begin
                    load_error <= 1'b1;
                    mem_read <= 1'b0;
                end
                
                default: begin
                    mem_read <= 1'b0;
                end
            endcase
        end
    end
    
    // =========================================================================
    // Active Buffer Management (Atomic Swap)
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            active_buf_reg <= 1'b0;
        end else if (state == SWAP) begin
            active_buf_reg <= ~active_buf_reg;
        end
    end
    
    assign active_buffer = active_buf_reg;
    
    // =========================================================================
    // Configuration Output Multiplexing
    // =========================================================================
    always_comb begin
        if (active_buf_reg == 1'b0) begin
            // Output from Bank0
            config_frame_00 = bank0_00;
            config_frame_01 = bank0_01;
            config_frame_02 = bank0_02;
            config_frame_03 = bank0_03;
            config_frame_10 = bank0_10;
            config_frame_11 = bank0_11;
            config_frame_12 = bank0_12;
            config_frame_13 = bank0_13;
            config_frame_20 = bank0_20;
            config_frame_21 = bank0_21;
            config_frame_22 = bank0_22;
            config_frame_23 = bank0_23;
            config_frame_30 = bank0_30;
            config_frame_31 = bank0_31;
            config_frame_32 = bank0_32;
            config_frame_33 = bank0_33;
        end else begin
            // Output from Bank1
            config_frame_00 = bank1_00;
            config_frame_01 = bank1_01;
            config_frame_02 = bank1_02;
            config_frame_03 = bank1_03;
            config_frame_10 = bank1_10;
            config_frame_11 = bank1_11;
            config_frame_12 = bank1_12;
            config_frame_13 = bank1_13;
            config_frame_20 = bank1_20;
            config_frame_21 = bank1_21;
            config_frame_22 = bank1_22;
            config_frame_23 = bank1_23;
            config_frame_30 = bank1_30;
            config_frame_31 = bank1_31;
            config_frame_32 = bank1_32;
            config_frame_33 = bank1_33;
        end
    end
    
    // Configuration valid during execution
    assign config_valid = (state != IDLE) && (state != LOAD_HEADER) && (state != ERROR);

endmodule
