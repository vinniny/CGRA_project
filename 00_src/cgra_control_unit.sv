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
    input  logic [31:0] max_cycles_i,   // Timeout limit (0 = no limit)
    
    // =========================================================================
    // Hardware Loop Configuration (Zero-Overhead Loops)
    // =========================================================================
    input  logic [15:0] loop_start_pc_i, // Loop start address (context PC)
    input  logic [15:0] loop_end_pc_i,   // Loop end address (inclusive)
    input  logic [15:0] loop_count_i     // Loop iteration count (0 = disabled)
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
    logic [31:0] wall_counter;   // FIX: Wall-clock counter (counts all cycles in RUN, even stalled)
    logic        timeout_reached;
    
    // Hardware Loop Registers
    logic [15:0] loop_count_reg;  // Remaining loop iterations (internal counter)
    logic [PC_WIDTH-1:0] loop_start_reg;  // FIX: Latched loop start PC (prevents mid-run corruption)
    logic [PC_WIDTH-1:0] loop_end_reg;    // FIX: Latched loop end PC
    
    // =========================================================================
    // Timeout Detection — uses wall_counter for DMA-hang protection
    // =========================================================================
    assign timeout_reached = (max_cycles_i != 32'd0) && (wall_counter >= max_cycles_i);
    
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
                // Note: Use soft_reset_i to stop execution (testbench writes 0x2 to stop)
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
    // Context PC Counter (Multi-context scheduling with Hardware Loops)
    // =========================================================================
    // CRITICAL: Declare pc_counter here, before Cycle Counter block references it
    logic [PC_WIDTH-1:0] pc_counter;
    
    // =========================================================================
    // Cycle Counter + Loop Counter Management
    // =========================================================================
    // CRITICAL: Consolidate all loop_count_reg updates here to avoid multiple drivers
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            cycle_counter <= 32'd0;
            wall_counter <= 32'd0;
            loop_count_reg <= 16'd0;
            loop_start_reg <= '0;
            loop_end_reg   <= '0;
        end else begin
            if (state == STATE_IDLE && start_i && !soft_reset_i) begin
                // FIX: Match FSM guard - reload only when actually transitioning to RUN
                cycle_counter <= 32'd0;
                wall_counter  <= 32'd0;
                // FIX: Latch all loop parameters on RUN entry to prevent mid-run corruption
                loop_count_reg <= loop_count_i;
                loop_start_reg <= loop_start_pc_i[PC_WIDTH-1:0];
                loop_end_reg   <= loop_end_pc_i[PC_WIDTH-1:0];
            end else if (state == STATE_RUN) begin
                // Wall counter: increments every cycle (including stalls) for DMA-hang timeout
                wall_counter <= wall_counter + 32'd1;
                // FIX: Only count cycles when PEs actually execute (not stalled by DMA)
                if (!global_stall_o)
                    cycle_counter <= cycle_counter + 32'd1;
                
                // CRITICAL: Decrement loop counter when PC matches end address
                // This is the ONLY place loop_count_reg is decremented
                // FIX: Use latched loop_end_reg instead of live input
                if ((pc_counter == loop_end_reg) && (loop_count_reg > 16'd0) && 
                    (pe_enable && !global_stall_o)) begin
                    loop_count_reg <= loop_count_reg - 16'd1;
                end
            end
        end
    end
    
    // =========================================================================
    // Context PC Counter Sequential Logic (Multi-context scheduling with Hardware Loops)
    // =========================================================================
    // Hardware Loop Logic:
    //   - If PC reaches loop_end_pc AND loop_count_reg > 0:
    //       * Jump back to loop_start_pc
    //       * Decrement loop_count_reg
    //   - Else: Normal increment with wrap-around
    //
    // This enables zero-overhead loops for repeated kernel execution.
    // Example: Repeat contexts 2-7 for 101 total iterations:
    //   loop_start_pc = 2, loop_end_pc = 7, loop_count = 100
    //   (1 base pass + 100 extra = 101 total; use loop_count=N-1 for N iterations)
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            pc_counter <= '0;
        end else if (soft_reset_i) begin
            pc_counter <= '0;
        end else if (state == STATE_IDLE && start_i && !soft_reset_i) begin
            // FIX: Clear pc_counter on new RUN to prevent stale start address
            pc_counter <= '0;
        end else if (pe_enable && !global_stall_o) begin
            // Increment PC only when running and not stalled
            
            // FIX: Use latched loop registers instead of live inputs
            if ((pc_counter == loop_end_reg) && (loop_count_reg > 16'd0)) begin
                // Loop active and at end address - jump back to start
                // NOTE: loop_count_reg is decremented in Cycle Counter block
                pc_counter <= loop_start_reg;
            end else if (pc_counter == PC_WIDTH'(CONTEXT_DEPTH - 1)) begin
                // Natural wrap-around at context depth boundary
                pc_counter <= '0;
            end else begin
                // Normal increment
                pc_counter <= pc_counter + 1'b1;
            end
        end
    end
    
    assign context_pc_o = pc_counter;
    
    // =========================================================================
    // Global Stall Logic
    // =========================================================================
    // Stall the PE array when:
    //   1. DMA is active (prevent data hazards during load)
    //   2. PE is not enabled (prevent spurious execution before/after run)
    //   3. FSM is not in RUN state (prevent extra execution during FINISH)
    //      pe_enable is registered and lags FSM by 1 cycle, so during FINISH
    //      pe_enable is still HIGH. Without the state check, PEs execute an
    //      extra cycle with a stale/wrapped context_pc.
    assign global_stall_o = dma_busy_i || !pe_enable || (state != STATE_RUN);
    
    // =========================================================================
    // Output Assignments
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            busy_o <= 1'b0;
            done_o <= 1'b0;
            pe_enable <= 1'b0;
            pe_reset_n <= 1'b1;  // PEs not in reset after hard reset (global_stall prevents execution)
        end else begin
            // Busy when running
            busy_o <= (state == STATE_RUN);
            
            // Done pulse when finishing (suppress on soft-reset abort to avoid
            // spurious CU Done IRQ — software cannot distinguish abort from completion)
            done_o <= (state == STATE_FINISH) && !soft_reset_i;
            
            // Enable array during RUN state
            pe_enable <= (state == STATE_RUN);
            
            // Reset array when soft_reset is active
            pe_reset_n <= !soft_reset_i;
        end
    end
    
    // Cycle count - always show running value
    assign cycle_count_o = cycle_counter;

    // =========================================================================
    // SAFETY ASSERTIONS (synthesis translate_off)
    // =========================================================================
    // synthesis translate_off
    logic [15:0] prev_loop_count;
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            prev_loop_count <= 16'd0;
        end else begin
            prev_loop_count <= loop_count_reg;
            
            // FIX: Detect loop_count_reg underflow (wrap from 0 to 65535).
            // The "loop_count_reg > 16'd0" guard in the decrement logic prevents this,
            // but this assertion catches regressions if the guard is accidentally removed.
            if (rst_n && state == STATE_RUN) begin
                if (prev_loop_count == 16'd0 && loop_count_reg == 16'hFFFF)
                    $error("[CU] loop_count_reg underflow detected! Wrapped from 0 to 65535 @ %0t", $time);
            end
        end
    end
    // synthesis translate_on

endmodule
