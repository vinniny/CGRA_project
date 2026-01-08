// ==============================================================================
// CGRA Control Unit - Array Conductor
// ==============================================================================
// 3-state FSM (IDLE → RUN → FINISH) to control PE array execution.
//
// FEATURES:
//   - Start/Stop control via CSR
//   - Programmable timeout (max_cycles from CSR 0x2C)
//   - Context PC counter (0-15, wraps)
//   - Global stall when DMA is busy
//   - Cycle counter for performance monitoring
//
// FSM STATES:
//   IDLE   → RUN    : On start_i assertion
//   RUN    → FINISH : On array_done, timeout, or soft_reset
//   FINISH → IDLE   : After 1-cycle done pulse
// ==============================================================================

module cgra_control_unit #(
    parameter CONTEXT_DEPTH = 16,
    parameter PC_WIDTH      = 4
)(
    input  logic        clk,
    input  logic        rst_n,
    
    // =========================================================================
    // CSR Interface (from cgra_axi_csr)
    // =========================================================================
    input  logic        start_i,        // Pulse to start execution
    input  logic        soft_reset_i,   // Soft reset (hold array in reset)
    output logic        busy_o,         // Currently executing
    output logic        done_o,         // Execution completed
    output logic [31:0] cycle_count_o,  // Performance counter
    
    // =========================================================================
    // Array Interface
    // =========================================================================
    output logic        pe_enable,      // Enable PE array execution
    output logic        pe_reset_n,     // Array reset (active low)
    input  logic        array_done_i,   // Array signals completion
    
    // =========================================================================
    // Multi-Context Flow Control
    // =========================================================================
    output logic [PC_WIDTH-1:0] context_pc_o,   // Current context slot (0-15)
    output logic                global_stall_o, // Freeze PE array
    input  logic                dma_busy_i,     // DMA is active
    
    // =========================================================================
    // Configuration
    // =========================================================================
    input  logic [31:0] max_cycles_i    // Timeout limit (0 = no limit)
);

    // =========================================================================
    // FSM State Definitions
    // =========================================================================
    typedef enum logic [1:0] {
        STATE_IDLE   = 2'd0,
        STATE_RUN    = 2'd1,
        STATE_FINISH = 2'd2
    } state_t;
    
    state_t state, state_next;
    
    // =========================================================================
    // Internal Registers
    // =========================================================================
    logic [31:0] cycle_counter;
    logic        timeout_reached;
    
    // =========================================================================
    // Timeout Detection
    // =========================================================================
    assign timeout_reached = (max_cycles_i != 32'd0) && (cycle_counter >= max_cycles_i);
    
    // =========================================================================
    // FSM Sequential Logic
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
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
                if (start_i && !soft_reset_i) begin
                    state_next = STATE_RUN;
                end
            end
            
            STATE_RUN: begin
                // Exit conditions: array done OR timeout OR soft reset
                if (array_done_i || timeout_reached || soft_reset_i) begin
                    state_next = STATE_FINISH;
                end
            end
            
            STATE_FINISH: begin
                // Return to IDLE after 1 cycle (done pulse)
                state_next = STATE_IDLE;
            end
            
            default: state_next = STATE_IDLE;
        endcase
    end
    
    // =========================================================================
    // Cycle Counter
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            cycle_counter <= 32'd0;
        end else begin
            if (state == STATE_IDLE && start_i) begin
                // Reset counter on new start
                cycle_counter <= 32'd0;
            end else if (state == STATE_RUN) begin
                // Increment during execution
                cycle_counter <= cycle_counter + 32'd1;
            end
        end
    end
    
    // =========================================================================
    // Context PC Counter (Multi-context scheduling)
    // =========================================================================
    logic [PC_WIDTH-1:0] pc_counter;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            pc_counter <= '0;
        end else if (soft_reset_i) begin
            pc_counter <= '0;
        end else if (pe_enable && !global_stall_o) begin
            // Increment PC only when running and not stalled
            if (pc_counter == PC_WIDTH'(CONTEXT_DEPTH - 1))  // FIX: Cast to PC_WIDTH bits
                pc_counter <= '0;  // Wrap around
            else
                pc_counter <= pc_counter + 1'b1;
        end
    end
    
    assign context_pc_o = pc_counter;
    
    // =========================================================================
    // Global Stall Logic
    // =========================================================================
    // Stall the PE array when DMA is active (prevent data hazards during load)
    assign global_stall_o = dma_busy_i;
    
    // =========================================================================
    // Output Assignments
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            busy_o <= 1'b0;
            done_o <= 1'b0;
            pe_enable <= 1'b0;
            pe_reset_n <= 1'b1;
        end else begin
            // Busy when running
            busy_o <= (state == STATE_RUN);
            
            // Done pulse when finishing
            done_o <= (state == STATE_FINISH);
            
            // Enable array during RUN state
            pe_enable <= (state == STATE_RUN);
            
            // Reset array when soft_reset is active
            pe_reset_n <= !soft_reset_i;
        end
    end
    
    // Cycle count - always show running value
    assign cycle_count_o = cycle_counter;

endmodule
