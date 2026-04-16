// ==============================================================================
// cgra_result_fifo.sv — Per-Row Result FIFO with Warmup Skip + Pre-Fetch
// ==============================================================================
// Captures east-edge PE outputs every valid cycle (not just cu_done).
// 4 independent BRAMs share write/read pointers (lockstep push/pop).
//
// Features:
//   - Warmup skip: suppresses first N push events (configurable, default 11)
//   - Pre-fetched pop: BRAM output register always holds next entry
//   - Backpressure: fifo_full stalls the CU via global_stall
//   - Overflow/underflow: sticky flags for error detection
//
// BRAM inference: 4 × DEPTH × DATA_WIDTH bits.
//   Default 4 × 256 × 32 = 32 Kbit = 1 RAMB36E1 on XC7Z020.
// ==============================================================================

module cgra_result_fifo #(
    parameter DATA_WIDTH = 32,
    parameter DEPTH      = 256,
    parameter ROWS       = 4,
    parameter ADDR_BITS  = $clog2(DEPTH)   // 8 for DEPTH=256
)(
    input  logic                    clk,
    input  logic                    rst_n,

    // ── Push side (from PE east-edge) ────────────────────────────────
    input  logic [DATA_WIDTH-1:0]   push_data  [0:ROWS-1],
    input  logic                    push_valid,      // shared: all rows push in lockstep
    output logic                    fifo_full,

    // ── Pop side (APB read) ──────────────────────────────────────────
    output logic [DATA_WIDTH-1:0]   pop_data   [0:ROWS-1],
    output logic                    pop_valid,       // pre-fetched data is ready
    input  logic                    pop_read,        // consumer acknowledges (destructive)

    // ── Control ──────────────────────────────────────────────────────
    input  logic                    fifo_clear,      // assert on CU start / soft-reset
    input  logic [3:0]              skip_count,      // warmup values to suppress (default 11)

    // ── Status ───────────────────────────────────────────────────────
    output logic [ADDR_BITS:0]      count,           // entries in FIFO (0 to DEPTH)
    output logic                    empty,
    output logic                    overflow_pulse,   // 1-cycle pulse on push-while-full
    output logic                    underflow_pulse   // 1-cycle pulse on pop-while-empty
);

    // =========================================================================
    // BRAM Storage (4 independent arrays, shared pointers)
    // =========================================================================
    (* ram_style = "block" *)
    logic [DATA_WIDTH-1:0] mem [0:ROWS-1][0:DEPTH-1];

    logic [ADDR_BITS-1:0] wr_ptr;
    logic [ADDR_BITS-1:0] rd_ptr;
    logic [ADDR_BITS:0]   fifo_count;   // extra bit for full detection

    assign count     = fifo_count;
    assign empty     = (fifo_count == '0);
    assign fifo_full = (fifo_count == DEPTH[ADDR_BITS:0]);

    // =========================================================================
    // Warmup Skip Counter
    // =========================================================================
    logic [3:0] warmup_counter;
    wire        warmup_done = (warmup_counter >= skip_count);

    // Effective push: only after warmup and when not full
    wire do_push = push_valid && warmup_done && !fifo_full;
    wire do_pop  = pop_read && !empty;

    // Overflow / underflow detection (1-cycle pulses)
    assign overflow_pulse  = push_valid && warmup_done && fifo_full;
    assign underflow_pulse = pop_read && empty;

    // =========================================================================
    // BRAM Write (push side)
    // =========================================================================
    always_ff @(posedge clk) begin
        if (do_push) begin
            mem[0][wr_ptr] <= push_data[0];
            mem[1][wr_ptr] <= push_data[1];
            mem[2][wr_ptr] <= push_data[2];
            mem[3][wr_ptr] <= push_data[3];
        end
    end

    // =========================================================================
    // BRAM Read (pre-fetch side)
    // =========================================================================
    // Pre-fetch register: always holds the entry at rd_ptr.
    // On pop_read, advance rd_ptr and load next entry on the following cycle.
    logic [DATA_WIDTH-1:0] prefetch_reg [0:ROWS-1];
    logic                  prefetch_valid;

    // BRAM read data (1-cycle latency)
    logic [DATA_WIDTH-1:0] bram_rd [0:ROWS-1];
    logic                  bram_rd_pending;    // a BRAM read was issued last cycle
    logic                  first_push_bypass;  // bypass BRAM for first-push-into-empty

    // Issue BRAM read on:
    //  (1) pop with more entries remaining (prefetch next after pop)
    //  (2) one cycle after first push into empty (BRAM write committed)
    wire issue_bram_read = (do_pop && (fifo_count > 1)) || first_push_bypass;

    // BRAM read address:
    //  - On pop: read rd_ptr+1 (next entry to prefetch)
    //  - On first-push bypass: read rd_ptr (= 0, the entry just written)
    wire [ADDR_BITS-1:0] bram_rd_addr = first_push_bypass ? rd_ptr
                                                           : (rd_ptr + 1'b1);

    always_ff @(posedge clk) begin
        if (!rst_n || fifo_clear) begin
            bram_rd_pending   <= 1'b0;
            first_push_bypass <= 1'b0;
        end else begin
            bram_rd_pending   <= issue_bram_read;
            first_push_bypass <= do_push && empty && !do_pop;
        end
    end

    // BRAM synchronous read
    always_ff @(posedge clk) begin
        if (issue_bram_read) begin
            bram_rd[0] <= mem[0][bram_rd_addr];
            bram_rd[1] <= mem[1][bram_rd_addr];
            bram_rd[2] <= mem[2][bram_rd_addr];
            bram_rd[3] <= mem[3][bram_rd_addr];
        end
    end

    // Pre-fetch register update (single driver)
    // Two sources:
    //   1. BRAM read completed — either after first push (bypass delay) or
    //      after pop (prefetch next entry)
    //   2. Pop of last entry — invalidate prefetch
    always_ff @(posedge clk) begin
        if (!rst_n || fifo_clear) begin
            prefetch_reg[0] <= '0; prefetch_reg[1] <= '0;
            prefetch_reg[2] <= '0; prefetch_reg[3] <= '0;
            prefetch_valid <= 1'b0;
        end else if (bram_rd_pending) begin
            prefetch_reg[0] <= bram_rd[0]; prefetch_reg[1] <= bram_rd[1];
            prefetch_reg[2] <= bram_rd[2]; prefetch_reg[3] <= bram_rd[3];
            prefetch_valid <= 1'b1;
        end else if (do_pop && (fifo_count == 1)) begin
            prefetch_valid <= 1'b0;
        end
    end

    // Output
    assign pop_valid = prefetch_valid;
    assign pop_data[0] = prefetch_reg[0];
    assign pop_data[1] = prefetch_reg[1];
    assign pop_data[2] = prefetch_reg[2];
    assign pop_data[3] = prefetch_reg[3];

    // (debug probes removed after warmup skip calibration)

    // =========================================================================
    // Pointer + Count Management
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n || fifo_clear) begin
            wr_ptr         <= '0;
            rd_ptr         <= '0;
            fifo_count     <= '0;
            warmup_counter <= 4'd0;
        end else begin
            // Warmup counter
            if (push_valid && !warmup_done)
                warmup_counter <= warmup_counter + 4'd1;

            // Write pointer
            if (do_push)
                wr_ptr <= wr_ptr + 1'b1;

            // Read pointer
            if (do_pop)
                rd_ptr <= rd_ptr + 1'b1;

            // Count
            case ({do_push, do_pop})
                2'b10:   fifo_count <= fifo_count + 1'b1;
                2'b01:   fifo_count <= fifo_count - 1'b1;
                default: fifo_count <= fifo_count;  // 2'b00 or 2'b11 (simultaneous)
            endcase
        end
    end

endmodule
