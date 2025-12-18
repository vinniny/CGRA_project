// ==============================================================================
// CGRA Control Unit / Sequencer with Timestep FSM
// ==============================================================================
// Manages SNN timestep execution and context scheduling
// Features:
// - Timestep-based execution control
// - Context switching coordination
// - DMA and configuration loader orchestration
// - Performance monitoring

module cgra_control_unit #(
    parameter NUM_PES = 16,
    parameter NUM_TIMESTEPS = 256
)(
    input  logic clk,
    input  logic rst_n,
    
    // CSR interface signals
    input  logic        cgra_start,
    input  logic        cgra_reset,
    input  logic        cfg_start,
    input  logic [15:0] cfg_size,        // Number of cycles to run per timestep
    output logic        cgra_busy,
    output logic        cgra_done,
    output logic        cgra_error,
    
    // Configuration loader control
    output logic        cfg_load_start,
    input  logic        cfg_load_done,
    input  logic        cfg_load_error,
    output logic        cfg_swap_buffers,
    
    // DMA control
    output logic        dma_trigger,
    input  logic        dma_busy,
    input  logic        dma_done,
    input  logic        dma_error,
    
    // PE array control
    output logic        pe_array_enable,
    output logic        pe_array_reset,
    output logic [15:0] current_timestep,
    
    // Context control (read from config loader)
    input  logic        context_active_buf,  // 0=Bank0, 1=Bank1
    
    // Performance counters
    output logic [31:0] perf_cycles,
    output logic [31:0] perf_stalls,
    output logic [31:0] perf_timesteps
);

    // =========================================================================
    // FSM States
    // =========================================================================
    typedef enum logic [3:0] {
        STATE_IDLE           = 4'd0,
        STATE_WAIT_CFG       = 4'd1,
        STATE_SETUP_DMA      = 4'd2,
        STATE_LOAD_CONTEXT   = 4'd3,
        STATE_EXEC_INIT      = 4'd4,
        STATE_EXEC_RUN       = 4'd5,
        STATE_EXEC_DRAIN     = 4'd6,
        STATE_TIMESTEP_DONE  = 4'd7,
        STATE_CONTEXT_SWAP   = 4'd8,
        STATE_COMPLETE       = 4'd9,
        STATE_ERROR          = 4'd10
    } ctrl_state_t;
    ctrl_state_t state, state_next;
    
    // =========================================================================
    // Timestep management
    // =========================================================================
    logic [15:0] timestep_counter;
    logic [15:0] timestep_target;
    logic [15:0] cycles_in_timestep;
    
    // =========================================================================
    // Context buffer management
    // =========================================================================
    logic active_buffer;         // Currently executing buffer
    logic next_buffer_ready;     // Background buffer loaded
    
    // =========================================================================
    // Stall detection
    // =========================================================================
    logic pe_stalled;
    logic dma_stalled;
    logic [7:0] stall_counter;
    
    // =========================================================================
    // FSM Sequential Logic
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            state <= STATE_IDLE;
        end else begin
            state <= state_next;
        end
    end
    
    // =========================================================================
    // FSM Combinational Logic
    // =========================================================================
    always_comb begin
        state_next = state;
        
        unique case (state)
            STATE_IDLE: begin
                if (cgra_start && cfg_start) begin
                    state_next = STATE_WAIT_CFG;
                end else if (cgra_start) begin
                    state_next = STATE_EXEC_INIT;
                end
            end
            
            STATE_WAIT_CFG: begin
                if (cfg_load_done) begin
                    state_next = STATE_SETUP_DMA;
                end else if (cfg_load_error) begin
                    state_next = STATE_ERROR;
                end
            end
            
            STATE_SETUP_DMA: begin
                if (!cgra_start) begin
                    state_next = STATE_COMPLETE;
                end else if (dma_done) begin
                    state_next = STATE_LOAD_CONTEXT;
                end else if (dma_error) begin
                    state_next = STATE_ERROR;
                end
            end
            
            STATE_LOAD_CONTEXT: begin
                if (!cgra_start) begin
                    state_next = STATE_COMPLETE;
                end else if (next_buffer_ready) begin
                    state_next = STATE_EXEC_INIT;
                end
            end
            
            STATE_EXEC_INIT: begin
                // Initialize PE array for execution
                if (!cgra_start) begin
                    state_next = STATE_COMPLETE;
                end else begin
                    state_next = STATE_EXEC_RUN;
                end
            end
            
            STATE_EXEC_RUN: begin
                // Main execution phase
                if (!cgra_start) begin
                    state_next = STATE_COMPLETE;
                end else if (cycles_in_timestep >= cfg_size) begin
                    state_next = STATE_EXEC_DRAIN;
                end else if (cgra_error) begin
                    state_next = STATE_ERROR;
                end
            end
            
            STATE_EXEC_DRAIN: begin
                // Drain pipeline and prepare for next timestep
                if (!cgra_start) begin
                    state_next = STATE_COMPLETE;
                end else begin
                    state_next = STATE_TIMESTEP_DONE;
                end
            end
            
            STATE_TIMESTEP_DONE: begin
                if (!cgra_start) begin
                    state_next = STATE_COMPLETE;
                end else if (timestep_counter >= timestep_target) begin
                    state_next = STATE_COMPLETE;
                end else begin
                    // Check if context switch needed
                    if ((timestep_counter & 16'h000F) == 16'd0) begin
                        state_next = STATE_CONTEXT_SWAP;
                    end else begin
                        state_next = STATE_EXEC_INIT;
                    end
                end
            end
            
            STATE_CONTEXT_SWAP: begin
                // Swap active configuration buffer
                if (next_buffer_ready) begin
                    state_next = STATE_EXEC_INIT;
                end else begin
                    state_next = STATE_WAIT_CFG;
                end
            end
            
            STATE_COMPLETE: begin
                // Always return to IDLE, then IDLE will handle restart if needed
                state_next = STATE_IDLE;
            end
            
            STATE_ERROR: begin
                if (cgra_reset) begin
                    state_next = STATE_IDLE;
                end
            end
            
            default: state_next = STATE_IDLE;
        endcase
    end
    
    // =========================================================================
    // Timestep Counter
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            timestep_counter <= 16'd0;
            cycles_in_timestep <= 16'd0;
            timestep_target <= NUM_TIMESTEPS - 1;
        end else begin
            if (state == STATE_IDLE) begin
                timestep_counter <= 16'd0;
                cycles_in_timestep <= 16'd0;
            end else if (state == STATE_EXEC_RUN) begin
                cycles_in_timestep <= cycles_in_timestep + 16'd1;
            end else if (state == STATE_TIMESTEP_DONE) begin
                timestep_counter <= timestep_counter + 16'd1;
                cycles_in_timestep <= 16'd0;
            end
        end
    end
    
    always_comb begin
        current_timestep = timestep_counter;
    end
    
    // =========================================================================
    // Context Buffer Management
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            active_buffer <= 1'b0;
            next_buffer_ready <= 1'b0;
        end else begin
            // Buffer 0 starts as active
            if (state == STATE_IDLE) begin
                active_buffer <= 1'b0;
                next_buffer_ready <= 1'b0;
            end else if (state == STATE_WAIT_CFG && cfg_load_done) begin
                next_buffer_ready <= 1'b1;
            end else if (state == STATE_CONTEXT_SWAP) begin
                // Swap buffers
                active_buffer <= ~active_buffer;
                next_buffer_ready <= 1'b0;
            end
        end
    end
    
    // Note: context_active_buf is now an input from config_loader
    // It indicates which buffer the config loader is currently using
    
    // =========================================================================
    // Configuration Loader Control
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            cfg_load_start <= 1'b0;
            cfg_swap_buffers <= 1'b0;
        end else begin
            // Keep cfg_load_start asserted during configuration loading
            if (state == STATE_WAIT_CFG || state == STATE_CONTEXT_SWAP) begin
                cfg_load_start <= 1'b1;
            end else begin
                cfg_load_start <= 1'b0;
            end
            
            // Signal to swap buffers in config loader
            if (state == STATE_CONTEXT_SWAP) begin
                cfg_swap_buffers <= 1'b1;
            end else begin
                cfg_swap_buffers <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // DMA Control
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            dma_trigger <= 1'b0;
        end else begin
            if (state == STATE_SETUP_DMA && !dma_busy) begin
                dma_trigger <= 1'b1;
            end else begin
                dma_trigger <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // PE Array Control
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            pe_array_enable <= 1'b0;
            pe_array_reset <= 1'b1;
        end else begin
            if (state == STATE_EXEC_INIT) begin
                pe_array_reset <= 1'b0;
                pe_array_enable <= 1'b1;
            end else if (state == STATE_EXEC_RUN) begin
                pe_array_enable <= 1'b1;
            end else if (state == STATE_EXEC_DRAIN || state == STATE_TIMESTEP_DONE) begin
                pe_array_enable <= 1'b0;
            end else if (state == STATE_IDLE) begin
                pe_array_reset <= 1'b1;
            end
        end
    end
    
    // =========================================================================
    // Status Outputs
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            cgra_busy <= 1'b0;
            cgra_done <= 1'b0;
            cgra_error <= 1'b0;
        end else begin
            cgra_busy <= (state != STATE_IDLE) && (state != STATE_COMPLETE) && (state != STATE_ERROR);
            cgra_done <= (state == STATE_COMPLETE);
            cgra_error <= (state == STATE_ERROR) || cfg_load_error || dma_error;
        end
    end
    
    // =========================================================================
    // Stall Detection
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            stall_counter <= 8'd0;
            pe_stalled <= 1'b0;
            dma_stalled <= 1'b0;
        end else begin
            if (state == STATE_EXEC_RUN) begin
                // Simplified stall detection
                if (cycles_in_timestep > 16'd50 && timestep_counter == current_timestep) begin
                    pe_stalled <= 1'b1;
                end
            end else begin
                pe_stalled <= 1'b0;
            end
            
            if (state == STATE_SETUP_DMA && dma_busy) begin
                stall_counter <= stall_counter + 8'd1;
                if (stall_counter > 8'd100) begin
                    dma_stalled <= 1'b1;
                end
            end else begin
                stall_counter <= 8'd0;
                dma_stalled <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // Performance Counters
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            perf_cycles <= 32'd0;
            perf_stalls <= 32'd0;
            perf_timesteps <= 32'd0;
        end else begin
            if (state == STATE_IDLE) begin
                perf_cycles <= 32'd0;
                perf_stalls <= 32'd0;
                perf_timesteps <= 32'd0;
            end else begin
                // Count total cycles
                if (state != STATE_IDLE) begin
                    perf_cycles <= perf_cycles + 32'd1;
                end
                
                // Count stalls
                if (pe_stalled || dma_stalled) begin
                    perf_stalls <= perf_stalls + 32'd1;
                end
                
                // Count completed timesteps
                if (state == STATE_TIMESTEP_DONE) begin
                    perf_timesteps <= perf_timesteps + 32'd1;
                end
            end
        end
    end

endmodule
