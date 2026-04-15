// cgra_dma_engine.sv — AXI4 master + producer/consumer FIFO data mover.
// Destination routing by address prefix: 0x1=tile, 0x2=config, else=AXI.
// Config writes are double-pumped (high word then low word).

module cgra_dma_engine #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 32,
    parameter FIFO_DEPTH = 32,
    parameter AXI_ID_WIDTH = 4
)(
    input  logic clk,
    input  logic rst_n,

    // CSR config
    input  logic [31:0]           cfg_src,
    input  logic [31:0]           cfg_dst,
    input  logic [31:0]           cfg_size,
    input  logic [31:0]           cfg_src_stride,
    input  logic [31:0]           cfg_rows,
    input  logic [31:0]           cfg_cols,
    input  logic                  cfg_start,
    input  logic                  cfg_abort,
    output logic                  status_busy,
    output logic                  status_done,
    output logic                  irq_done,

    // AXI4 master
    output logic [AXI_ID_WIDTH-1:0] m_axi_awid,
    output logic [ADDR_WIDTH-1:0] m_axi_awaddr,
    output logic [7:0]            m_axi_awlen,
    output logic [2:0]            m_axi_awsize,
    output logic [1:0]            m_axi_awburst,
    output logic                  m_axi_awvalid,
    input  logic                  m_axi_awready,
    output logic [DATA_WIDTH-1:0] m_axi_wdata,
    output logic [DATA_WIDTH/8-1:0] m_axi_wstrb,
    output logic                  m_axi_wlast,
    output logic                  m_axi_wvalid,
    input  logic                  m_axi_wready,
    input  logic [AXI_ID_WIDTH-1:0] m_axi_bid,
    input  logic                  m_axi_bvalid,
    input  logic [1:0]            m_axi_bresp,
    output logic                  m_axi_bready,
    output logic [AXI_ID_WIDTH-1:0] m_axi_arid,
    output logic [ADDR_WIDTH-1:0] m_axi_araddr,
    output logic [7:0]            m_axi_arlen,
    output logic [2:0]            m_axi_arsize,
    output logic [1:0]            m_axi_arburst,
    output logic                  m_axi_arvalid,
    input  logic                  m_axi_arready,
    input  logic [AXI_ID_WIDTH-1:0] m_axi_rid,
    input  logic [DATA_WIDTH-1:0] m_axi_rdata,
    input  logic                  m_axi_rlast,
    input  logic                  m_axi_rvalid,
    input  logic [1:0]            m_axi_rresp,
    output logic                  m_axi_rready,

    // Error status
    output logic [1:0]            error_code,
    output logic                  error_valid,

    // Tile memory
    output logic [11:0]           tile_addr_o,
    output logic [1:0]            tile_bank_sel_o,
    output logic                  tile_we_o,
    output logic [31:0]           tile_wdata_o,
    output logic                  tile_re_o,
    input  logic [DATA_WIDTH-1:0] tile_rdata_i,
    input  logic                  tile_rvalid_i,

    // PE config
    output logic [31:0]           config_addr_o,
    output logic                  config_we_o,
    output logic [31:0]           config_wdata_o,

    // ILA debug
    output logic                  dbg_status_busy,
    output logic [2:0]            dbg_read_fsm_state,
    output logic [2:0]            dbg_write_fsm_state,
    output logic                  dbg_fifo_full,
    output logic                  dbg_fifo_empty,
    output logic [31:0]           dbg_write_words_remaining  // ILA probe
);

    localparam BYTES_PER_WORD = DATA_WIDTH / 8;
    localparam FIFO_ADDR_BITS = $clog2(FIFO_DEPTH);

    // FIX: FIFO pointer wrap relies on power-of-2 depth. Enforce at elaboration.
    initial begin
        if ((FIFO_DEPTH & (FIFO_DEPTH - 1)) != 0)
            $fatal(1, "[DMA] FIFO_DEPTH=%0d is not a power of 2 — pointer wrap broken", FIFO_DEPTH);
    end
    
    // FIFO between read and write engines
    logic [DATA_WIDTH-1:0] fifo_mem [0:FIFO_DEPTH-1];
    logic [FIFO_ADDR_BITS-1:0] w_ptr, r_ptr;
    logic [FIFO_ADDR_BITS:0] count;

    wire fifo_full  = (count == FIFO_DEPTH);
    wire fifo_empty = (count == '0);

    // Latched destination/source routing (captured on cfg_start)
    logic dst_is_axi;
    logic dst_is_tile;
    logic dst_is_config;
    logic src_is_tile;
    logic tile_read_phase;

    logic local_write_en;
    logic local_fifo_pop;
    logic axi_fifo_pop;

    typedef enum logic [2:0] {
        R_IDLE  = 3'd0,
        R_ADDR  = 3'd1,
        R_DATA  = 3'd2,
        R_DRAIN = 3'd3
    } read_state_t;

    typedef enum logic [2:0] {
        W_IDLE  = 3'd0,
        W_WAIT  = 3'd1,
        W_ADDR  = 3'd2,
        W_DATA  = 3'd3,
        W_RESP  = 3'd4,
        W_DRAIN = 3'd5,
        W_LOCAL = 3'd6
    } write_state_t;

    read_state_t  r_state;
    write_state_t w_state;

    wire fifo_pop_axi   = (axi_fifo_pop && dst_is_axi && !fifo_empty);
    wire fifo_pop_local = (local_fifo_pop && !dst_is_axi && !fifo_empty);
    wire fifo_pop       = fifo_pop_axi || fifo_pop_local;
    wire fifo_push_axi  = m_axi_rvalid && m_axi_rready && !fifo_full && r_state != R_DRAIN && !src_is_tile;
    wire fifo_push_tile = tile_rvalid_i && !fifo_full && src_is_tile && r_state == R_DATA && tile_read_phase;
    wire fifo_push      = fifo_push_axi || fifo_push_tile;

    logic [DATA_WIDTH-1:0] fifo_rdata;
    assign fifo_rdata = fifo_mem[r_ptr];

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            w_ptr <= '0;
            r_ptr <= '0;
            count <= '0;
        end else if (cfg_abort && r_state != R_DRAIN && w_state != W_DRAIN) begin
            w_ptr <= '0;
            r_ptr <= '0;
            count <= '0;
        end else begin
            if (cfg_start && !status_busy) begin
                // Reset FIFO on new transfer
                w_ptr <= '0;
                r_ptr <= '0;
                count <= '0;
            end else begin
                // Push data into FIFO
                if (fifo_push) begin
                    fifo_mem[w_ptr] <= src_is_tile ? tile_rdata_i : m_axi_rdata;
                    w_ptr <= w_ptr + 1'b1;
                end
                
                // Pop data from FIFO
                if (fifo_pop) begin
                    r_ptr <= r_ptr + 1'b1;
                end
                
                // Update count (handle simultaneous push/pop)
                if (fifo_push && !fifo_pop)
                    count <= count + 1'b1;
                else if (fifo_pop && !fifo_push)
                    count <= count - 1'b1;
            end
        end
    end
    
    // =========================================================================
    // 2. Read Engine (Producer) - Fills FIFO from source
    // =========================================================================
    logic [31:0] read_addr;
    logic [31:0] read_words_remaining;
    logic [7:0]  current_burst_len;  // Current burst length (ARLEN value, 0-indexed)
    logic        read_2d_mode;
    logic [31:0] read_row_base_addr;
    logic [31:0] read_row_stride;
    logic [31:0] read_rows_remaining;
    logic [31:0] read_cols_words;
    logic [31:0] read_row_words_remaining;
    
    // Tile broadcast: dst_addr[31] = broadcast flag
    logic        dst_broadcast;         // Broadcast write to all 4 tile banks
    logic [1:0]  broadcast_bank_cnt;    // 0-3 bank counter during broadcast

    assign m_axi_arsize  = 3'b010;
    assign m_axi_arburst = 2'b01;

    wire        cfg_2d_mode         = (cfg_rows != '0);
    wire [31:0] cfg_cols_words      = (cfg_cols + BYTES_PER_WORD - 1) / BYTES_PER_WORD;
    wire [31:0] cfg_transfer_words  = cfg_2d_mode
                                      ? (cfg_rows * cfg_cols_words)
                                      : ((cfg_size + BYTES_PER_WORD - 1) / BYTES_PER_WORD);

    localparam MAX_BURST_WORDS = FIFO_DEPTH;

    // 4KB boundary protection — bursts cannot cross 4KB pages
    wire [11:0] addr_offset      = read_addr[11:0];
    wire [31:0] words_to_boundary = (32'd4096 - {20'd0, addr_offset}) >> 2;
    wire [31:0] len_limit_fifo   = (read_words_remaining > MAX_BURST_WORDS)
                                   ? MAX_BURST_WORDS : read_words_remaining;
    wire [31:0] len_limit_row    = (read_2d_mode && (read_row_words_remaining < len_limit_fifo))
                                   ? read_row_words_remaining : len_limit_fifo;
    wire [31:0] words_this_burst_raw = (len_limit_row > words_to_boundary)
                                       ? words_to_boundary : len_limit_row;
    // Guard zero (unaligned addr at 4KB boundary underflows to ARLEN=255)
    wire [31:0] words_this_burst = (words_this_burst_raw == '0) ? 32'd1 : words_this_burst_raw;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            r_state <= R_IDLE;
            read_addr <= '0;
            read_words_remaining <= '0;
            read_2d_mode <= 1'b0;
            read_row_base_addr <= '0;
            read_row_stride <= '0;
            read_rows_remaining <= '0;
            read_cols_words <= '0;
            read_row_words_remaining <= '0;
            current_burst_len <= '0;
            m_axi_araddr <= '0;
            m_axi_arlen <= '0;
            m_axi_arvalid <= 1'b0;
            m_axi_rready <= 1'b0;
            src_is_tile <= 1'b0;
            tile_read_phase <= 1'b0;
        end else if (cfg_abort && r_state != R_DRAIN) begin
            read_words_remaining <= '0;
            read_2d_mode <= 1'b0;
            read_rows_remaining <= '0;
            read_row_words_remaining <= '0;
            if (src_is_tile) begin
                r_state <= R_IDLE;
                tile_read_phase <= 1'b0;
            end else case (r_state)
                R_ADDR: r_state <= R_DRAIN;
                R_DATA: begin
                    r_state <= R_DRAIN;
                    m_axi_rready <= 1'b1;
                end
                R_DRAIN: begin
                    if (m_axi_arvalid) begin
                        if (m_axi_arready) begin
                            m_axi_arvalid <= 1'b0;
                            m_axi_rready <= 1'b1;
                        end
                    end else if (m_axi_rvalid) begin
                        m_axi_rready <= 1'b1;
                        if (m_axi_rready && m_axi_rlast) begin
                            m_axi_rready <= 1'b0;
                            r_state <= R_IDLE;
                        end
                    end else if (!m_axi_rready) begin
                        r_state <= R_IDLE;
                    end
                end
                default: begin
                    r_state <= R_IDLE;
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready <= 1'b0;
                end
            endcase
        end else begin
            case (r_state)
                R_IDLE: begin
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready <= 1'b0;
                    tile_read_phase <= 1'b0;
                    if (cfg_start && cfg_transfer_words != '0 && !status_busy) begin
                        read_2d_mode <= cfg_2d_mode;
                        read_row_base_addr <= cfg_src;
                        read_row_stride <= cfg_src_stride;
                        read_rows_remaining <= cfg_2d_mode ? cfg_rows : 32'd1;
                        read_cols_words <= cfg_2d_mode ? cfg_cols_words : cfg_transfer_words;
                        read_row_words_remaining <= cfg_2d_mode ? cfg_cols_words : cfg_transfer_words;
                        read_addr <= cfg_src;
                        read_words_remaining <= cfg_transfer_words;
                        src_is_tile <= (cfg_src[31:28] == 4'h1);
                        r_state <= R_ADDR;
                    end
                end

                R_ADDR: begin
                    if (src_is_tile) begin
                        tile_read_phase <= 1'b0;
                        r_state <= R_DATA;
                    end else if (!m_axi_arvalid) begin
                        if ((32'(FIFO_DEPTH) - 32'(count)) >= words_this_burst && read_words_remaining != '0) begin
                            m_axi_araddr <= read_addr;
                            m_axi_arlen <= words_this_burst[7:0] - 8'd1;
                            current_burst_len <= words_this_burst[7:0] - 8'd1;
                            m_axi_arvalid <= 1'b1;
                        end
                    end else if (m_axi_arready) begin
                        m_axi_arvalid <= 1'b0;
                        m_axi_rready <= 1'b1;
                        r_state <= R_DATA;
                    end
                end

                R_DATA: begin
                    if (src_is_tile) begin
                        // Tile read-back: phase 0 issues read, phase 1 captures
                        if (!tile_read_phase) begin
                            if (!fifo_full && read_words_remaining != '0)
                                tile_read_phase <= 1'b1;
                        end else begin
                            read_words_remaining <= read_words_remaining - 1'b1;
                            read_addr <= read_addr + BYTES_PER_WORD;
                            if (read_row_words_remaining > 0)
                                read_row_words_remaining <= read_row_words_remaining - 1'b1;
                            tile_read_phase <= 1'b0;
                            if (read_words_remaining == 32'd1)
                                r_state <= R_IDLE;
                        end
                    end else begin
                        m_axi_rready <= !fifo_full;
                        if (m_axi_rvalid && m_axi_rready) begin
                            read_words_remaining <= read_words_remaining - 1'b1;
                            if (read_row_words_remaining > 0)
                                read_row_words_remaining <= read_row_words_remaining - 1'b1;
                            if (m_axi_rlast) begin
                                m_axi_rready <= 1'b0;
                                if (read_words_remaining == 32'd1) begin
                                    m_axi_arvalid <= 1'b0;
                                    r_state <= R_IDLE;
                                end else begin
                                    if (read_2d_mode && (read_row_words_remaining == 32'd1)) begin
                                        read_row_base_addr <= read_row_base_addr + read_row_stride;
                                        read_addr <= read_row_base_addr + read_row_stride;
                                        if (read_rows_remaining > 0)
                                            read_rows_remaining <= read_rows_remaining - 1'b1;
                                        read_row_words_remaining <= read_cols_words;
                                    end else begin
                                        read_addr <= read_addr + ((32'(current_burst_len) + 32'd1) * BYTES_PER_WORD);
                                    end
                                    r_state <= R_ADDR;
                                end
                            end
                        end
                    end
                end

                R_DRAIN: begin
                    // AR may still be pending; parallel AR+R drain (outstanding reads).
                    if (m_axi_arvalid && m_axi_arready)
                        m_axi_arvalid <= 1'b0;

                    if (m_axi_rvalid) begin
                        m_axi_rready <= 1'b1;
                        if (m_axi_rready && m_axi_rlast) begin
                            m_axi_rready <= 1'b0;
                            if (!m_axi_arvalid)
                                r_state <= R_IDLE;
                        end
                    end else if (!m_axi_arvalid && !m_axi_rready) begin
                        r_state <= R_IDLE;
                    end
                end

                default: r_state <= R_IDLE;
            endcase
        end
    end

    // Write engine: drains FIFO to destination
    logic [31:0] write_addr;
    logic [31:0] write_words_remaining;
    logic [DATA_WIDTH-1:0] write_data_reg;
    logic        write_data_reg_valid;
    logic [31:0] local_write_addr;

    logic [7:0]  write_burst_len;
    logic [7:0]  write_beat_counter;
    logic [31:0] write_burst_words;

    assign m_axi_awsize  = 3'b010;
    assign m_axi_awburst = 2'b01;
    assign m_axi_wstrb   = {(DATA_WIDTH/8){1'b1}};

    logic [11:0] write_addr_offset;
    logic [31:0] words_to_write_boundary;
    logic [31:0] len_limit_fifo_write;
    logic [31:0] words_this_write_burst;

    always_comb begin
        write_addr_offset       = write_addr[11:0];
        words_to_write_boundary = (32'd4096 - {20'd0, write_addr_offset}) >> 2;
        len_limit_fifo_write    = (write_words_remaining > MAX_BURST_WORDS)
                                  ? MAX_BURST_WORDS : write_words_remaining;
        words_this_write_burst  = (len_limit_fifo_write > words_to_write_boundary)
                                  ? words_to_write_boundary : len_limit_fifo_write;
        if (words_this_write_burst == '0) words_this_write_burst = 32'd1;
    end


    always_ff @(posedge clk) begin
        if (!rst_n) begin
            w_state <= W_IDLE;
            write_addr <= '0;
            write_words_remaining <= '0;
            dst_is_axi <= 1'b0;
            dst_is_tile <= 1'b0;
            dst_is_config <= 1'b0;
            write_data_reg <= '0;
            write_data_reg_valid <= 1'b0;
            local_write_en <= 1'b0;
            local_fifo_pop <= 1'b0;
            axi_fifo_pop <= 1'b0;
            local_write_addr <= '0;
            write_burst_len <= '0;
            write_beat_counter <= '0;
            write_burst_words <= '0;
            m_axi_awaddr <= '0;
            m_axi_awlen <= '0;
            m_axi_awvalid <= 1'b0;
            m_axi_wdata <= '0;
            m_axi_wlast <= 1'b0;
            m_axi_wvalid <= 1'b0;
            m_axi_bready <= 1'b0;
            dst_broadcast <= 1'b0;
            broadcast_bank_cnt <= 2'd0;
        end else if (cfg_abort && w_state != W_DRAIN) begin
            write_words_remaining <= '0;
            dst_is_axi <= 1'b0;
            dst_is_tile <= 1'b0;
            dst_is_config <= 1'b0;
            local_write_en <= 1'b0;
            local_fifo_pop <= 1'b0;
            axi_fifo_pop <= 1'b0;
            case (w_state)
                W_ADDR: begin
                    m_axi_bready <= 1'b0;
                    if (!m_axi_awvalid) begin
                        w_state <= W_IDLE;
                        write_data_reg_valid <= 1'b0;
                        write_beat_counter <= '0;
                    end else begin
                        if (m_axi_awready)
                            m_axi_awvalid <= 1'b0;
                        w_state <= W_DRAIN;
                    end
                end
                W_DATA: begin
                    m_axi_bready <= 1'b0;
                    if (m_axi_wvalid && m_axi_wready) begin
                        write_beat_counter <= write_beat_counter + 8'd1;
                        m_axi_wvalid <= 1'b0;
                        m_axi_wlast <= 1'b0;
                    end
                    w_state <= W_DRAIN;
                end
                W_RESP: begin
                    if (m_axi_bvalid && m_axi_bready) begin
                        m_axi_bready <= 1'b0;
                        write_data_reg_valid <= 1'b0;
                        write_beat_counter <= '0;
                        w_state <= W_IDLE;
                    end else begin
                        w_state <= W_DRAIN;
                    end
                end
                W_DRAIN: begin
                    if (m_axi_awvalid) begin
                        if (m_axi_awready) begin
                            m_axi_awvalid <= 1'b0;
                            write_beat_counter <= '0;
                            m_axi_wdata <= '0;
                            m_axi_wlast <= (write_burst_len == 8'd0);
                            m_axi_wvalid <= 1'b1;
                        end
                    end else if (m_axi_wvalid) begin
                        if (m_axi_wready) begin
                            if (write_beat_counter == write_burst_len) begin
                                m_axi_wvalid <= 1'b0;
                                m_axi_wlast <= 1'b0;
                                m_axi_bready <= 1'b1;
                            end else begin
                                write_beat_counter <= write_beat_counter + 8'd1;
                                m_axi_wdata <= '0;
                                m_axi_wlast <= ((write_beat_counter + 8'd1) == write_burst_len);
                                m_axi_wvalid <= 1'b1;
                            end
                        end
                    end else if (m_axi_bready) begin
                        if (m_axi_bvalid) begin
                            m_axi_bready <= 1'b0;
                            write_data_reg_valid <= 1'b0;
                            write_beat_counter <= '0;
                            w_state <= W_IDLE;
                        end
                    end else begin
                        if (write_beat_counter <= write_burst_len) begin
                            m_axi_wdata <= '0;
                            m_axi_wlast <= (write_beat_counter == write_burst_len);
                            m_axi_wvalid <= 1'b1;
                        end else begin
                            m_axi_bready <= 1'b1;
                        end
                    end
                end
                default: begin
                    w_state <= W_IDLE;
                    local_write_en <= 1'b0;
                    local_fifo_pop <= 1'b0;
                    write_data_reg_valid <= 1'b0;
                    write_beat_counter <= '0;
                    m_axi_awvalid <= 1'b0;
                    m_axi_wlast <= 1'b0;
                    m_axi_wvalid <= 1'b0;
                    m_axi_bready <= 1'b0;
                end
            endcase
        end else begin
            case (w_state)
                W_IDLE: begin
                    local_write_en <= 1'b0;
                    local_fifo_pop <= 1'b0;
                    axi_fifo_pop <= 1'b0;
                    write_data_reg_valid <= 1'b0;
                    m_axi_awvalid <= 1'b0;
                    m_axi_wvalid <= 1'b0;
                    m_axi_bready <= 1'b0;
                    broadcast_bank_cnt <= 2'd0;
                    if (cfg_start && cfg_transfer_words != '0 && !status_busy) begin
                        // cfg_dst[31] = broadcast (multi-bank write)
                        write_addr <= {1'b0, cfg_dst[30:0]};
                        write_words_remaining <= cfg_transfer_words;
                        dst_is_axi    <= (cfg_dst[31:28] == 4'h0) && !cfg_dst[31];
                        dst_is_tile   <= (cfg_dst[31:28] == 4'h1) || cfg_dst[31];
                        dst_is_config <= (cfg_dst[31:28] == 4'h2);
                        dst_broadcast <= cfg_dst[31];
                        w_state <= W_WAIT;
                    end
                end

                W_WAIT: begin
                    m_axi_bready <= 1'b1;
                    local_write_en <= 1'b0;
                    local_fifo_pop <= 1'b0;
                    axi_fifo_pop <= 1'b0;

                    if (!fifo_empty && write_words_remaining != '0) begin
                        if (dst_is_axi) begin
                            write_burst_len   <= words_this_write_burst[7:0] - 8'd1;
                            write_burst_words <= words_this_write_burst;
                            write_beat_counter <= '0;
                        end
                        write_data_reg       <= fifo_rdata;
                        write_data_reg_valid <= 1'b1;
                        if (dst_is_axi) axi_fifo_pop <= 1'b1;
                        else            local_fifo_pop <= 1'b1;
                        w_state <= dst_is_axi ? W_ADDR : W_LOCAL;
                    end else if (write_words_remaining == '0) begin
                        w_state <= W_IDLE;
                    end
                end

                W_ADDR: begin
                    axi_fifo_pop <= 1'b0;
                    local_fifo_pop <= 1'b0;
                    if (dst_is_axi) begin
                        if (!m_axi_awvalid) begin
                            m_axi_awaddr <= write_addr;
                            m_axi_awlen <= write_burst_len;
                            m_axi_awvalid <= 1'b1;
                        end else if (m_axi_awready) begin
                            m_axi_awvalid <= 1'b0;
                            w_state <= W_DATA;
                        end
                    end
                end

                W_DATA: begin
                    axi_fifo_pop <= 1'b0;
                    if (!m_axi_wvalid) begin
                        if (write_beat_counter == 0 || write_data_reg_valid) begin
                            m_axi_wdata <= write_data_reg;
                            m_axi_wlast <= (write_beat_counter == write_burst_len);
                            m_axi_wvalid <= 1'b1;
                            write_data_reg_valid <= 1'b0;
                        end else if (!fifo_empty) begin
                            write_data_reg <= fifo_rdata;
                            axi_fifo_pop <= 1'b1;
                            write_data_reg_valid <= 1'b1;
                        end
                    end else if (m_axi_wready) begin
                        write_words_remaining <= write_words_remaining - 1'b1;
                        if (write_beat_counter == write_burst_len) begin
                            m_axi_wvalid <= 1'b0;
                            m_axi_wlast <= 1'b0;
                            m_axi_bready <= 1'b1;
                            write_addr <= write_addr + (write_burst_words * BYTES_PER_WORD);
                            w_state <= W_RESP;
                        end else if (!fifo_empty) begin
                            write_beat_counter <= write_beat_counter + 1'b1;
                            write_data_reg <= fifo_rdata;
                            axi_fifo_pop <= 1'b1;
                            write_data_reg_valid <= 1'b1;
                            m_axi_wvalid <= 1'b0;
                            m_axi_wlast <= 1'b0;
                        end else begin
                            write_beat_counter <= write_beat_counter + 1'b1;
                            write_data_reg_valid <= 1'b0;
                            m_axi_wvalid <= 1'b0;
                            m_axi_wlast <= 1'b0;
                        end
                    end
                end

                W_RESP: begin
                    if (m_axi_bvalid) begin
                        m_axi_bready <= 1'b0;
                        w_state <= (write_words_remaining == 32'd0) ? W_IDLE : W_WAIT;
                    end
                end

                W_DRAIN: begin
                    // Complete AW, send dummy beats to WLAST, collect BVALID.
                    axi_fifo_pop <= 1'b0;
                    if (m_axi_awvalid) begin
                        if (m_axi_awready) begin
                            m_axi_awvalid <= 1'b0;
                            write_beat_counter <= '0;
                            m_axi_wdata <= '0;
                            m_axi_wlast <= (write_burst_len == 8'd0);
                            m_axi_wvalid <= 1'b1;
                        end
                    end else if (m_axi_wvalid) begin
                        if (m_axi_wready) begin
                            if (write_beat_counter == write_burst_len) begin
                                m_axi_wvalid <= 1'b0;
                                m_axi_wlast <= 1'b0;
                                m_axi_bready <= 1'b1;
                            end else begin
                                write_beat_counter <= write_beat_counter + 8'd1;
                                m_axi_wdata <= '0;
                                m_axi_wlast <= ((write_beat_counter + 8'd1) == write_burst_len);
                                m_axi_wvalid <= 1'b1;
                            end
                        end
                    end else if (m_axi_bready) begin
                        if (m_axi_bvalid) begin
                            m_axi_bready <= 1'b0;
                            write_data_reg_valid <= 1'b0;
                            write_beat_counter <= '0;
                            w_state <= W_IDLE;
                        end
                    end else begin
                        if (write_beat_counter <= write_burst_len) begin
                            m_axi_wdata <= '0;
                            m_axi_wlast <= (write_beat_counter == write_burst_len);
                            m_axi_wvalid <= 1'b1;
                        end else begin
                            m_axi_bready <= 1'b1;
                        end
                    end
                end

                W_LOCAL: begin
                    local_fifo_pop <= 1'b0;
                    if (dst_broadcast && dst_is_tile) begin
                        // Broadcast: replicate word across 4 banks (bank_cnt 0..3)
                        local_write_addr <= {write_addr[31:14],
                                             broadcast_bank_cnt, write_addr[11:0]};
                        local_write_en   <= 1'b1;
                        if (broadcast_bank_cnt == 2'd3) begin
                            broadcast_bank_cnt <= 2'd0;
                            write_addr <= write_addr + BYTES_PER_WORD;
                            write_words_remaining <= write_words_remaining - 1'b1;
                            w_state <= W_WAIT;
                        end else begin
                            broadcast_bank_cnt <= broadcast_bank_cnt + 2'd1;
                        end
                    end else begin
                        local_write_addr      <= write_addr;
                        local_write_en        <= 1'b1;
                        write_addr            <= write_addr + BYTES_PER_WORD;
                        write_words_remaining <= write_words_remaining - 1'b1;
                        w_state <= W_WAIT;
                    end
                end

                default: w_state <= W_IDLE;
            endcase
        end
    end

    // Tile / config output assignments (routed by dst_is_tile / dst_is_config)
    wire tile_rd_en = src_is_tile && (r_state == R_DATA) && !tile_read_phase
                      && !fifo_full && (read_words_remaining != '0);

    assign tile_addr_o     = src_is_tile ? read_addr[11:0]   : local_write_addr[11:0];
    assign tile_bank_sel_o = src_is_tile ? read_addr[13:12]  : local_write_addr[13:12];
    assign tile_re_o       = tile_rd_en;
    assign tile_wdata_o    = write_data_reg;
    assign tile_we_o       = local_write_en && dst_is_tile;

    assign config_addr_o   = local_write_addr;
    assign config_wdata_o  = write_data_reg;
    assign config_we_o     = local_write_en && dst_is_config;

    assign m_axi_awid = {AXI_ID_WIDTH{1'b0}};
    assign m_axi_arid = {AXI_ID_WIDTH{1'b0}};

    // Status and IRQ — single busy register derived from engine state
    logic [1:0] error_code_reg;
    logic       error_flag;
    logic       busy;
    logic       aborted;

    assign error_code  = error_code_reg;
    assign error_valid = error_flag;
    assign status_busy = busy;

    wire bresp_error = m_axi_bvalid && m_axi_bready && (m_axi_bresp != 2'b00);
    wire rresp_error = m_axi_rvalid && m_axi_rready && (m_axi_rresp != 2'b00);
    wire engine_idle = (r_state == R_IDLE) && (w_state == W_IDLE) && fifo_empty;

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            busy           <= 1'b0;
            aborted        <= 1'b0;
            status_done    <= 1'b0;
            irq_done       <= 1'b0;
            error_code_reg <= 2'b00;
            error_flag     <= 1'b0;
        end else begin
            status_done <= 1'b0;
            irq_done    <= 1'b0;

            if (bresp_error || rresp_error) begin
                error_code_reg <= bresp_error ? m_axi_bresp : m_axi_rresp;
                error_flag     <= 1'b1;
            end

            if (cfg_abort) begin
                busy    <= !engine_idle;
                aborted <= 1'b1;
            end else if (cfg_start && !busy) begin
                error_code_reg <= 2'b00;
                error_flag     <= 1'b0;
                aborted        <= 1'b0;
                if (cfg_transfer_words != '0) begin
                    busy <= 1'b1;
                end else begin
                    status_done <= 1'b1;
                    irq_done    <= 1'b1;
                end
            end else if (busy && engine_idle) begin
                busy <= 1'b0;
                if (!aborted) begin
                    status_done <= 1'b1;
                    irq_done    <= 1'b1;
                end
            end
        end
    end

    // ILA debug
    assign dbg_status_busy           = status_busy;
    assign dbg_read_fsm_state        = r_state;
    assign dbg_write_fsm_state       = w_state;
    assign dbg_fifo_full             = fifo_full;
    assign dbg_fifo_empty            = fifo_empty;
    assign dbg_write_words_remaining = write_words_remaining;

endmodule
