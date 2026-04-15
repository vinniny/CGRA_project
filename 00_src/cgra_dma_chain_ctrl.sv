// ==============================================================================
// cgra_dma_chain_ctrl.sv — Scatter-Gather Descriptor Chain Controller
// ==============================================================================
// Owns the entire SG descriptor chain lifecycle. Fetches descriptors from
// DDR via a shared AXI AR/R port, parses {src, dst, size, next_ptr}, and
// issues one-shot DMA commands to the data-mover engine per descriptor.
//
// FSM: C_IDLE → C_FETCH → C_LOAD → C_XFER → C_WAIT → C_NEXT → (loop)
//      C_DRAIN on abort (AXI-safe drain of in-flight descriptor burst)
//
// Every state has an explicit abort_i transition.
// cmd_done_i is edge-detected to prevent double-counting.
// ==============================================================================

module cgra_dma_chain_ctrl #(
    parameter ADDR_WIDTH = 32,
    parameter DATA_WIDTH = 32
)(
    input  logic                    clk,
    input  logic                    rst_n,

    // ── CSR interface ────────────────────────────────────────────────
    input  logic [ADDR_WIDTH-1:0]   desc_head_i,        // DMA_DESC_HEAD register
    input  logic                    chain_start_i,       // 1-cycle pulse from DMA_CTRL[1]
    input  logic                    abort_i,             // cu_soft_reset
    output logic                    chain_active_o,      // DMA_DESC_STATUS[0]
    output logic [15:0]             desc_completed_o,    // DMA_DESC_STATUS[15:8]

    // ── DMA engine command interface ─────────────────────────────────
    output logic [ADDR_WIDTH-1:0]   cmd_src_o,
    output logic [ADDR_WIDTH-1:0]   cmd_dst_o,
    output logic [31:0]             cmd_size_o,
    output logic                    cmd_start_o,         // 1-cycle pulse
    input  logic                    cmd_done_i,          // from DMA engine status_done
    input  logic                    cmd_busy_i,          // from DMA engine status_busy

    // ── AXI read interface (descriptor fetch) ────────────────────────
    output logic [ADDR_WIDTH-1:0]   m_axi_araddr,
    output logic [7:0]              m_axi_arlen,
    output logic [2:0]              m_axi_arsize,
    output logic [1:0]              m_axi_arburst,
    output logic                    m_axi_arvalid,
    input  logic                    m_axi_arready,
    input  logic [DATA_WIDTH-1:0]   m_axi_rdata,
    input  logic [1:0]              m_axi_rresp,
    input  logic                    m_axi_rvalid,
    input  logic                    m_axi_rlast,
    output logic                    m_axi_rready,

    // ── Mux control (to cgra_top AXI arbiter) ────────────────────────
    output logic                    fetch_active_o       // high during C_FETCH (owns AXI AR/R)
);

    // =========================================================================
    // FSM State Definitions
    // =========================================================================
    typedef enum logic [2:0] {
        C_IDLE  = 3'd0,
        C_FETCH = 3'd1,
        C_LOAD  = 3'd2,
        C_XFER  = 3'd3,
        C_WAIT  = 3'd4,
        C_NEXT  = 3'd5,
        C_DRAIN = 3'd6
    } chain_state_t;

    chain_state_t state;

    // =========================================================================
    // Internal Registers
    // =========================================================================
    logic [ADDR_WIDTH-1:0]  desc_ptr;           // Current descriptor DDR address
    logic [DATA_WIDTH-1:0]  desc_buf [0:3];     // 4-word descriptor buffer
    logic [1:0]             desc_word_idx;       // Beat counter during fetch
    logic [15:0]            desc_completed_cnt;
    logic                   ar_issued;           // AR handshake completed

    // cmd_done_i edge detector (prevents double-count)
    logic                   cmd_done_prev;
    wire                    cmd_done_pulse = cmd_done_i && !cmd_done_prev;

    // AXI AR constants
    assign m_axi_arsize  = 3'b010;  // 4 bytes per beat
    assign m_axi_arburst = 2'b01;   // INCR

    // Outputs
    assign chain_active_o   = (state != C_IDLE);
    assign desc_completed_o = desc_completed_cnt;
    assign fetch_active_o   = (state == C_FETCH) || (state == C_DRAIN);

    // =========================================================================
    // Main FSM
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            state              <= C_IDLE;
            desc_ptr           <= '0;
            desc_word_idx      <= '0;
            desc_completed_cnt <= '0;
            ar_issued          <= 1'b0;
            cmd_done_prev      <= 1'b0;
            m_axi_araddr       <= '0;
            m_axi_arlen        <= '0;
            m_axi_arvalid      <= 1'b0;
            m_axi_rready       <= 1'b0;
            cmd_src_o          <= '0;
            cmd_dst_o          <= '0;
            cmd_size_o         <= '0;
            cmd_start_o        <= 1'b0;
        end else begin
            // Default: clear 1-cycle pulses
            cmd_start_o   <= 1'b0;
            cmd_done_prev <= cmd_done_i;

            case (state)
                // ─────────────────────────────────────────────────────
                C_IDLE: begin
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready  <= 1'b0;
                    if (chain_start_i && desc_head_i != '0) begin
                        desc_ptr           <= desc_head_i;
                        desc_completed_cnt <= 16'd0;
                        state              <= C_FETCH;
                    end
                end

                // ─────────────────────────────────────────────────────
                C_FETCH: begin
                    if (abort_i) begin
                        // AXI in-flight — must drain
                        if (m_axi_arvalid || m_axi_rready || ar_issued)
                            state <= C_DRAIN;
                        else
                            state <= C_IDLE;
                    end else if (!ar_issued && !m_axi_arvalid) begin
                        // Issue AXI AR for 4-word descriptor
                        m_axi_araddr  <= desc_ptr;
                        m_axi_arlen   <= 8'd3;  // 4 beats
                        m_axi_arvalid <= 1'b1;
                        desc_word_idx <= 2'd0;
                    end else if (m_axi_arvalid && m_axi_arready) begin
                        // AR handshake complete
                        m_axi_arvalid <= 1'b0;
                        m_axi_rready  <= 1'b1;
                        ar_issued     <= 1'b1;
                    end else if (ar_issued && m_axi_rvalid && m_axi_rready) begin
                        // Capture descriptor words
                        desc_buf[desc_word_idx] <= m_axi_rdata;
                        desc_word_idx <= desc_word_idx + 2'd1;
                        if (m_axi_rlast) begin
                            m_axi_rready <= 1'b0;
                            ar_issued    <= 1'b0;
                            state        <= C_LOAD;
                        end
                    end
                end

                // ─────────────────────────────────────────────────────
                C_LOAD: begin
                    if (abort_i) begin
                        state <= C_IDLE;  // No AXI in-flight
                    end else begin
                        // Parse descriptor: {src, dst, size, next_ptr}
                        cmd_src_o  <= desc_buf[0];
                        cmd_dst_o  <= desc_buf[1];
                        cmd_size_o <= desc_buf[2];
                        desc_ptr   <= desc_buf[3];  // Save next pointer

                        if (desc_buf[2] == '0) begin
                            // Zero-size descriptor: skip, follow next
                            desc_completed_cnt <= desc_completed_cnt + 16'd1;
                            if (desc_buf[3] == '0)
                                state <= C_IDLE;  // End of chain
                            else
                                state <= C_FETCH;
                        end else begin
                            state <= C_XFER;
                        end
                    end
                end

                // ─────────────────────────────────────────────────────
                C_XFER: begin
                    if (abort_i) begin
                        state <= C_IDLE;  // Suppress cmd_start (already 0 from default)
                    end else if (!cmd_busy_i) begin
                        cmd_start_o <= 1'b1;  // 1-cycle pulse
                        state       <= C_WAIT;
                    end
                    // else: DMA engine busy from previous — wait
                end

                // ─────────────────────────────────────────────────────
                C_WAIT: begin
                    if (abort_i) begin
                        state <= C_IDLE;  // DMA engine handles its own abort
                    end else if (cmd_done_pulse) begin
                        desc_completed_cnt <= desc_completed_cnt + 16'd1;
                        state              <= C_NEXT;
                    end
                end

                // ─────────────────────────────────────────────────────
                C_NEXT: begin
                    if (abort_i) begin
                        state <= C_IDLE;
                    end else if (desc_ptr == '0) begin
                        // End of chain
                        state <= C_IDLE;
                    end else begin
                        // Follow chain to next descriptor
                        state <= C_FETCH;
                    end
                end

                // ─────────────────────────────────────────────────────
                C_DRAIN: begin
                    // AXI-safe abort drain. Always accept pending R beats
                    // (rvalid may be high from in-flight burst — must drain
                    // before slave accepts new AR).
                    if (m_axi_rvalid) m_axi_rready <= 1'b1;

                    if (m_axi_arvalid && m_axi_arready) begin
                        m_axi_arvalid <= 1'b0;
                        ar_issued     <= 1'b1;
                    end

                    if (m_axi_rvalid && m_axi_rready && m_axi_rlast) begin
                        m_axi_rready <= 1'b0;
                        ar_issued    <= 1'b0;
                        if (!m_axi_arvalid)
                            state <= C_IDLE;
                    end else if (!m_axi_arvalid && !ar_issued && !m_axi_rvalid) begin
                        m_axi_rready <= 1'b0;
                        state        <= C_IDLE;
                    end
                end

                default: state <= C_IDLE;
            endcase
        end
    end

endmodule
