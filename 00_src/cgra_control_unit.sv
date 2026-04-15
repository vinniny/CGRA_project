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
    output logic [PC_WIDTH-1:0] next_context_pc_o, // Next PC (for tile prefetch, accounts for loops)
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
    input  logic [15:0] loop_count_i,    // Loop iteration count (0 = disabled)

    // Nested Loop (Level 2) — B3
    input  logic [15:0] loop2_start_pc_i,
    input  logic [15:0] loop2_end_pc_i,
    input  logic [15:0] loop2_count_i,

    // B4: Dynamic branch from PE array
    input  logic [PC_WIDTH-1:0] branch_target_i,
    input  logic                branch_taken_i,

    // Loop completion status (for auto-stop gating in cgra_top)
    output logic                loops_done_o,

    // Tile address auto-increment
    input  logic                tile_auto_inc_en_i,
    output logic [7:0]          tile_base_offset_o,
    output logic [7:0]          next_tile_base_offset_o
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
    logic [32:0] wall_counter;   // 33-bit: no wrap at 2^32 cycles (~85s @ 50 MHz)
    logic        timeout_reached;
    logic [31:0] max_cycles_reg;
    logic [7:0]  tile_base_offset;

    // L1 + L2 hardware-loop state (all latched on RUN entry to survive
    // mid-run APB writes to the loop config registers).
    logic [15:0]          loop_count_reg;
    logic [PC_WIDTH-1:0]  loop_start_reg;
    logic [PC_WIDTH-1:0]  loop_end_reg;
    logic [15:0]          loop2_count_reg;
    logic [PC_WIDTH-1:0]  loop2_start_reg;
    logic [PC_WIDTH-1:0]  loop2_end_reg;
    logic [15:0]          loop1_count_reload;  // L1 count saved for reload per L2 iteration

    assign timeout_reached = (max_cycles_reg != 32'd0) && (wall_counter >= max_cycles_reg);
    
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
    
    logic [PC_WIDTH-1:0] pc_counter;

    // Cycle counter + unified loop-counter management (single driver for
    // loop_count_reg across inner/outer loop paths).
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            cycle_counter <= 32'd0;
            wall_counter <= 33'd0;
            max_cycles_reg <= 32'd0;
            loop_count_reg <= 16'd0;
            loop_start_reg <= '0;
            loop_end_reg   <= '0;
            loop2_count_reg <= 16'd0;
            loop2_start_reg <= '0;
            loop2_end_reg   <= '0;
            loop1_count_reload <= 16'd0;
            tile_base_offset <= 8'd0;
        end else begin
            if (state == STATE_IDLE && start_i && !soft_reset_i) begin
                // RUN entry: latch all loop/timeout parameters so mid-run APB
                // writes can't corrupt the current execution.
                cycle_counter <= 32'd0;
                wall_counter  <= 33'd0;
                max_cycles_reg <= max_cycles_i;
                loop_start_reg <= loop_start_pc_i[PC_WIDTH-1:0];
                loop_end_reg   <= loop_end_pc_i[PC_WIDTH-1:0];
                // Hardware guard: invalid bounds (start > end) would never reach loop_end,
                // causing an infinite loop in silicon. Disable looping in that case.
                if (loop_count_i > 16'd0 &&
                    loop_start_pc_i[PC_WIDTH-1:0] > loop_end_pc_i[PC_WIDTH-1:0])
                    loop_count_reg <= 16'd0;
                else
                    loop_count_reg <= loop_count_i;
                // B3: Latch nested loop (level 2) parameters
                loop2_start_reg <= loop2_start_pc_i[PC_WIDTH-1:0];
                loop2_end_reg   <= loop2_end_pc_i[PC_WIDTH-1:0];
                if (loop2_count_i > 16'd0 &&
                    loop2_start_pc_i[PC_WIDTH-1:0] > loop2_end_pc_i[PC_WIDTH-1:0])
                    loop2_count_reg <= 16'd0;
                else
                    loop2_count_reg <= loop2_count_i;
                // Save initial loop1 count for reload on outer loop iteration
                loop1_count_reload <= loop_count_i;
                // Reset tile offset on every new CU run
                tile_base_offset <= 8'd0;
            end else if (state == STATE_RUN) begin
                wall_counter <= wall_counter + 33'd1;  // ticks during DMA stalls too
                if (!global_stall_o)
                    cycle_counter <= cycle_counter + 32'd1;

                // Loop-counter sequencing: inner L1 decrements per iteration;
                // when L1 exhausts and L2 still has work, reload L1 and tick L2.
                if ((pc_counter == loop_end_reg) && (pe_enable && !global_stall_o)) begin
                    if (loop_count_reg > 16'd0) begin
                        loop_count_reg <= loop_count_reg - 16'd1;
                    end else if (loop2_count_reg > 16'd0) begin
                        // B3: Outer loop iteration — reload inner, decrement outer
                        loop_count_reg  <= loop1_count_reload;
                        loop2_count_reg <= loop2_count_reg - 16'd1;
                    end
                    // Tile auto-increment: advance offset when loop wraps back
                    if (tile_auto_inc_en_i &&
                        (loop_count_reg > 16'd0 || loop2_count_reg > 16'd0))
                        tile_base_offset <= tile_base_offset + 8'd1;
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
        end else if (state == STATE_IDLE && start_i) begin
            pc_counter <= '0;
        end else if (pe_enable && !global_stall_o) begin
            // Priority: loop jump > branch > natural wrap > increment.
            if ((pc_counter == loop_end_reg) &&
                (loop_count_reg > 16'd0 || loop2_count_reg > 16'd0)) begin
                // Loop takes highest priority
                pc_counter <= loop_start_reg;
            end else if (branch_taken_i) begin
                // B4: Dynamic branch (when predicate condition met)
                pc_counter <= branch_target_i;
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
    // Next PC (combinational) — for tile memory prefetch
    // =========================================================================
    // Mirrors the sequential PC logic above, but computed combinationally so
    // cgra_top can prefetch tile[next_pc] one cycle ahead of execution.
    // Without this, hardware loop backward jumps cause tile prefetch to read
    // the wrong address for one cycle.
    always_comb begin
        if (pe_enable && !global_stall_o) begin
            if ((pc_counter == loop_end_reg) &&
                (loop_count_reg > 16'd0 || loop2_count_reg > 16'd0))
                next_context_pc_o = loop_start_reg;
            else if (branch_taken_i)
                next_context_pc_o = branch_target_i;
            else if (pc_counter == PC_WIDTH'(CONTEXT_DEPTH - 1))
                next_context_pc_o = '0;
            else
                next_context_pc_o = pc_counter + 1'b1;
        end else begin
            next_context_pc_o = pc_counter;
        end
    end

    // =========================================================================
    // Next Tile Base Offset (combinational) — for tile memory prefetch
    // =========================================================================
    // Mirrors the loop-wrap detection above. Advances the offset on the same
    // cycle as next_context_pc jumps to loop_start, so tile SRAM prefetch
    // reads from the correct address (new_offset + loop_start) one cycle
    // ahead of PE execution.
    always_comb begin
        if (tile_auto_inc_en_i && pe_enable && !global_stall_o &&
            (pc_counter == loop_end_reg) &&
            (loop_count_reg > 16'd0 || loop2_count_reg > 16'd0))
            next_tile_base_offset_o = tile_base_offset + 8'd1;
        else
            next_tile_base_offset_o = tile_base_offset;
    end

    assign tile_base_offset_o = tile_base_offset;

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
    //   4. Array done (prevent 17th execution: counter reaches 16 one cycle
    //      before the FSM transitions to FINISH, allowing the PE to execute
    //      context 0 a second time if not gated here)
    assign global_stall_o = dma_busy_i || !pe_enable || (state != STATE_RUN)
                          || array_done_i;
    
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

    // Loop completion: all internal loop counters exhausted.
    // Used by cgra_top auto-stop to wait for loops before asserting array_done.
    assign loops_done_o = (loop_count_reg == 16'd0) && (loop2_count_reg == 16'd0);

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

            if (state == STATE_RUN &&
                prev_loop_count == 16'd0 && loop_count_reg == 16'hFFFF)
                $error("[CU] loop_count_reg underflow: 0 -> 65535 @ %0t", $time);

            if (state == STATE_IDLE && start_i && !soft_reset_i) begin
                if (loop_start_pc_i[15:PC_WIDTH] != '0)
                    $warning("[CU] loop_start_pc_i=0x%04h exceeds CONTEXT_DEPTH=%0d",
                             loop_start_pc_i, CONTEXT_DEPTH);
                if (loop_end_pc_i[15:PC_WIDTH] != '0)
                    $warning("[CU] loop_end_pc_i=0x%04h exceeds CONTEXT_DEPTH=%0d",
                             loop_end_pc_i, CONTEXT_DEPTH);
                if (loop_count_i > 16'd0 &&
                    loop_start_pc_i[PC_WIDTH-1:0] > loop_end_pc_i[PC_WIDTH-1:0])
                    $warning("[CU] Invalid loop bounds: start(%0d) > end(%0d) — infinite loop",
                             loop_start_pc_i[PC_WIDTH-1:0], loop_end_pc_i[PC_WIDTH-1:0]);
            end
        end
    end
    // synthesis translate_on

endmodule
