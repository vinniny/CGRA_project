// cgra_dma_chain_ctrl.sv — Scatter-Gather descriptor chain controller.
// Fetches {src, dst, size, next_ptr} descriptors from DDR via its own AXI
// AR/R port and issues one-shot commands to the DMA data-mover.
//
// FSM: IDLE -> FETCH -> ISSUE -> WAIT -> (loop) / DRAIN on abort.

module cgra_dma_chain_ctrl #(
    parameter ADDR_WIDTH = 32,
    parameter DATA_WIDTH = 32
)(
    input  logic                    clk,
    input  logic                    rst_n,

    // CSR
    input  logic [ADDR_WIDTH-1:0]   desc_head_i,
    input  logic                    chain_start_i,
    input  logic                    abort_i,
    output logic                    chain_active_o,
    output logic [15:0]             desc_completed_o,

    // DMA engine command interface
    output logic [ADDR_WIDTH-1:0]   cmd_src_o,
    output logic [ADDR_WIDTH-1:0]   cmd_dst_o,
    output logic [31:0]             cmd_size_o,
    output logic                    cmd_start_o,
    input  logic                    cmd_done_i,
    input  logic                    cmd_busy_i,

    // AXI read (descriptor fetch)
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

    // Mux control
    output logic                    fetch_active_o
);

    typedef enum logic [2:0] {
        C_IDLE  = 3'd0,
        C_FETCH = 3'd1,
        C_ISSUE = 3'd2,
        C_WAIT  = 3'd3,
        C_DRAIN = 3'd4
    } chain_state_t;

    chain_state_t state;

    logic [ADDR_WIDTH-1:0]  desc_ptr;
    logic [DATA_WIDTH-1:0]  desc_buf [0:3];
    logic [1:0]             desc_word_idx;
    logic [15:0]            desc_completed_cnt;
    logic                   ar_issued;

    assign m_axi_arsize  = 3'b010;
    assign m_axi_arburst = 2'b01;

    assign chain_active_o   = (state != C_IDLE);
    assign desc_completed_o = desc_completed_cnt;
    assign fetch_active_o   = (state == C_FETCH) || (state == C_DRAIN);

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            state              <= C_IDLE;
            desc_ptr           <= '0;
            desc_word_idx      <= '0;
            desc_completed_cnt <= '0;
            ar_issued          <= 1'b0;
            m_axi_araddr       <= '0;
            m_axi_arlen        <= '0;
            m_axi_arvalid      <= 1'b0;
            m_axi_rready       <= 1'b0;
            cmd_src_o          <= '0;
            cmd_dst_o          <= '0;
            cmd_size_o         <= '0;
            cmd_start_o        <= 1'b0;
        end else begin
            cmd_start_o <= 1'b0;

            case (state)
                C_IDLE: begin
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready  <= 1'b0;
                    if (chain_start_i && desc_head_i != '0) begin
                        desc_ptr           <= desc_head_i;
                        desc_completed_cnt <= 16'd0;
                        state              <= C_FETCH;
                    end
                end

                C_FETCH: begin
                    if (abort_i) begin
                        state <= (m_axi_arvalid || m_axi_rready || ar_issued) ? C_DRAIN : C_IDLE;
                    end else if (!ar_issued && !m_axi_arvalid) begin
                        m_axi_araddr  <= desc_ptr;
                        m_axi_arlen   <= 8'd3;
                        m_axi_arvalid <= 1'b1;
                        desc_word_idx <= 2'd0;
                    end else if (m_axi_arvalid && m_axi_arready) begin
                        m_axi_arvalid <= 1'b0;
                        m_axi_rready  <= 1'b1;
                        ar_issued     <= 1'b1;
                    end else if (ar_issued && m_axi_rvalid && m_axi_rready) begin
                        desc_buf[desc_word_idx] <= m_axi_rdata;
                        desc_word_idx <= desc_word_idx + 2'd1;
                        if (m_axi_rlast) begin
                            m_axi_rready <= 1'b0;
                            ar_issued    <= 1'b0;
                            state        <= C_ISSUE;
                        end
                    end
                end

                C_ISSUE: begin
                    if (abort_i) begin
                        state <= C_IDLE;
                    end else if (desc_buf[2] == '0) begin
                        // Zero-size descriptor: count and skip
                        desc_ptr <= desc_buf[3];
                        desc_completed_cnt <= desc_completed_cnt + 16'd1;
                        state <= (desc_buf[3] == '0) ? C_IDLE : C_FETCH;
                    end else if (!cmd_busy_i) begin
                        cmd_src_o   <= desc_buf[0];
                        cmd_dst_o   <= desc_buf[1];
                        cmd_size_o  <= desc_buf[2];
                        desc_ptr    <= desc_buf[3];
                        cmd_start_o <= 1'b1;
                        state       <= C_WAIT;
                    end
                end

                C_WAIT: begin
                    if (abort_i) begin
                        state <= C_IDLE;
                    end else if (cmd_done_i) begin
                        desc_completed_cnt <= desc_completed_cnt + 16'd1;
                        state <= (desc_ptr == '0) ? C_IDLE : C_FETCH;
                    end
                end

                C_DRAIN: begin
                    // Always drain pending R beats before letting slave accept new AR
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
