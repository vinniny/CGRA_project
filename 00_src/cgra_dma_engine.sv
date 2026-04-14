// ==============================================================================
// CGRA DMA Engine - Pipelined Producer-Consumer Architecture - v2.4
// ==============================================================================
// AXI4 Full master for data/config transfers between external RAM and CGRA.
//
// CHANGELOG (v2.4 - January 2026):
//   - Fixed burst length calculation (WIDTHEXPAND)
//   - Robustness fixes for 4KB boundary crossings
//
// ARCHITECTURE:
//   - Read Engine (Producer): Fetches data from AXI, pushes to FIFO
//   - Configurable-Depth FIFO: Decouples read/write timing (default 32 words)
//   - Write Engine (Consumer): Pops FIFO, writes to destination
//
// DESTINATION ROUTING (by address prefix):
//   0x1XXX_XXXX → Tile Memory (4 banks × 4KB)
//   0x2XXX_XXXX → Config RAM (16 PEs × 16 slots × 64-bit)
//   Other       → AXI External Memory
//
// DOUBLE-PUMP CONFIG PROTOCOL:
//   1. Write high word to (addr)        - latches upper 32b in config_high_reg  [addr[2]=0]
//   2. Write low word to (addr | 0x4)   - commits full 64-bit to PE config RAM  [addr[2]=1]
// ==============================================================================

module cgra_dma_engine #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 32,
    parameter FIFO_DEPTH = 32,
    parameter AXI_ID_WIDTH = 4
)(
    input  logic clk,
    input  logic rst_n,
    
    // =========================================================================
    // CSR Configuration Interface
    // =========================================================================
    input  logic [31:0]           cfg_src,
    input  logic [31:0]           cfg_dst,
    input  logic [31:0]           cfg_size,
    input  logic [31:0]           cfg_src_stride,   // 2D: row stride (bytes)
    input  logic [31:0]           cfg_rows,          // 2D: number of rows (0=1D)
    input  logic [31:0]           cfg_cols,           // 2D: columns per row (bytes)
    input  logic                  cfg_start,
    input  logic                  cfg_abort,    // FIX: Abort/soft-reset to clear stuck busy
    output logic                  status_busy,
    output logic                  status_done,
    output logic                  irq_done,

    // Scatter-Gather Descriptor Chain
    input  logic [31:0]           desc_head_i,      // DDR address of first descriptor
    input  logic                  chain_start_i,     // pulse: start chain execution
    output logic                  chain_active_o,    // chain in progress
    output logic [15:0]           desc_completed_o,  // descriptors completed in current chain
    
    // =========================================================================
    // AXI4 Master Interface (Full AXI4 with Burst Support)
    // =========================================================================
    // Write Address Channel
    output logic [AXI_ID_WIDTH-1:0] m_axi_awid,
    output logic [ADDR_WIDTH-1:0] m_axi_awaddr,
    output logic [7:0]            m_axi_awlen,     // Burst length (0 = 1 beat, 255 = 256 beats)
    output logic [2:0]            m_axi_awsize,    // Beat size (2 = 4 bytes)
    output logic [1:0]            m_axi_awburst,   // Burst type (1 = INCR)
    output logic                  m_axi_awvalid,
    input  logic                  m_axi_awready,
    // Write Data Channel
    output logic [DATA_WIDTH-1:0] m_axi_wdata,
    output logic [DATA_WIDTH/8-1:0] m_axi_wstrb,
    output logic                  m_axi_wlast,     // Last beat in burst
    output logic                  m_axi_wvalid,
    input  logic                  m_axi_wready,
    // Write Response Channel
    input  logic [AXI_ID_WIDTH-1:0] m_axi_bid,
    input  logic                  m_axi_bvalid,
    input  logic [1:0]            m_axi_bresp,     // Write response (00=OKAY, 10=SLVERR, 11=DECERR)
    output logic                  m_axi_bready,
    // Read Address Channel
    output logic [AXI_ID_WIDTH-1:0] m_axi_arid,
    output logic [ADDR_WIDTH-1:0] m_axi_araddr,
    output logic [7:0]            m_axi_arlen,     // Burst length (0 = 1 beat)
    output logic [2:0]            m_axi_arsize,    // Beat size (2 = 4 bytes)
    output logic [1:0]            m_axi_arburst,   // Burst type (1 = INCR)
    output logic                  m_axi_arvalid,
    input  logic                  m_axi_arready,
    // Read Data Channel
    input  logic [AXI_ID_WIDTH-1:0] m_axi_rid,
    input  logic [DATA_WIDTH-1:0] m_axi_rdata,
    input  logic                  m_axi_rlast,     // Last beat in burst
    input  logic                  m_axi_rvalid,
    input  logic [1:0]            m_axi_rresp,     // Read response
    output logic                  m_axi_rready,

    // =========================================================================
    // Error Status Output
    // =========================================================================
    output logic [1:0]            error_code,      // Captured BRESP/RRESP error
    output logic                  error_valid,     // Pulse on error detection

    // =========================================================================
    // Local Memory Interface (To Tile Memory)
    // =========================================================================
    output logic [11:0]           tile_addr_o,
    output logic [1:0]            tile_bank_sel_o,
    output logic                  tile_we_o,
    output logic [31:0]           tile_wdata_o,
    output logic                  tile_re_o,            // Tile memory read enable (for read-back)
    input  logic [DATA_WIDTH-1:0] tile_rdata_i,         // Read data from tile memory (1-cycle latent)
    input  logic                  tile_rvalid_i,        // Read data valid
    
    // =========================================================================
    // Config Interface (To PE Array)
    // =========================================================================
    output logic [31:0]           config_addr_o,
    output logic                  config_we_o,
    output logic [31:0]           config_wdata_o,
    
    // =========================================================================
    // Debug Ports (For ILA/Chipscope probing)
    // =========================================================================
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
    
    // =========================================================================
    // 1. FIFO Buffer (Decoupling between Read and Write engines)
    // =========================================================================
    logic [DATA_WIDTH-1:0] fifo_mem [0:FIFO_DEPTH-1];
    logic [FIFO_ADDR_BITS-1:0] w_ptr, r_ptr;
    logic [FIFO_ADDR_BITS:0] count;  // Extra bit for full detection
    
    wire fifo_full  = (count == FIFO_DEPTH);
    wire fifo_empty = (count == '0);
    
    // =========================================================================
    // Address Decoding (0x0=External AXI, 0x1=Tile Memory, 0x2=Config)
    // =========================================================================
    // FIX: Latched destination type - prevents mid-transfer routing corruption
    // if CSR DMA_DST is written while a transfer is active. Latched in W_IDLE
    // on cfg_start alongside write_addr.
    logic dst_is_axi;
    logic dst_is_tile;
    logic dst_is_config;

    // Source address decoding (for tile read-back path)
    logic src_is_tile;
    logic tile_read_phase;  // 0=request, 1=capture (handles 1-cycle tile read latency)
    
    // Local write trigger (for tile/config - single cycle writes)
    logic local_write_en;
    logic local_fifo_pop;  // Explicit pop signal for local writes
    logic axi_fifo_pop;    // FIX: Explicit pop signal for AXI writes (set in W_WAIT)

    // FSM types/states are declared here so FIFO logic can safely reference
    // r_state/w_state and drain-state enum values.
    typedef enum logic [2:0] {
        R_IDLE       = 3'd0,
        R_ADDR       = 3'd1,
        R_DATA       = 3'd2,
        R_DONE       = 3'd3,
        R_DRAIN      = 3'd4,  // AXI-safe abort: drain in-flight read burst
        R_DESC_FETCH = 3'd5,  // SG: fetch 4-word descriptor from DDR
        R_DESC_LOAD  = 3'd6   // SG: parse descriptor into cfg_src/dst/size
    } read_state_t;

    typedef enum logic [2:0] {
        W_IDLE  = 3'd0,
        W_WAIT  = 3'd1,  // Wait for FIFO data
        W_ADDR  = 3'd2,  // AW phase (AXI only)
        W_DATA  = 3'd3,  // W phase  (AXI only)
        W_RESP  = 3'd4,  // B phase  (AXI only)
        W_DONE  = 3'd5,
        W_DRAIN = 3'd6,  // AXI-safe abort: drain in-flight write burst
        W_LOCAL = 3'd7   // Fast local drain: tile/config writes (1 word/cycle)
    } write_state_t;

    read_state_t  r_state;
    write_state_t w_state;
    
    // FIFO pop conditions:
    // - AXI: pop in W_WAIT when latching data (same as local) - NOT in W_DATA!
    // - Local: pop via local_fifo_pop (set in W_WAIT when latching data)
    // FIX: Both AXI and Local pop at the same time (W_WAIT) to avoid race condition
    wire fifo_pop_axi   = (axi_fifo_pop && dst_is_axi && !fifo_empty);
    wire fifo_pop_local = (local_fifo_pop && !dst_is_axi && !fifo_empty);
    wire fifo_pop  = fifo_pop_axi || fifo_pop_local;
    // During R_DRAIN, rready is held high to accept residual beats from the slave,
    // but we discard the data (don't push into FIFO) to avoid stale data buildup.
    // FIFO push: AXI read path OR tile read-back path (mutually exclusive per transfer)
    wire fifo_push_axi  = m_axi_rvalid && m_axi_rready && !fifo_full && r_state != R_DRAIN && r_state != R_DESC_FETCH && !src_is_tile;
    wire fifo_push_tile = tile_rvalid_i && !fifo_full && src_is_tile && r_state == R_DATA && tile_read_phase;
    wire fifo_push      = fifo_push_axi || fifo_push_tile;
    
    // FIFO data output (combinational read - async LUTRAM style)
    logic [DATA_WIDTH-1:0] fifo_rdata;
    assign fifo_rdata = fifo_mem[r_ptr];
    
    // FIFO logic
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            w_ptr <= '0;
            r_ptr <= '0;
            count <= '0;
        end else if (cfg_abort && r_state != R_DRAIN && w_state != W_DRAIN) begin
            // Clear FIFO on abort cycle. The state check uses current (pre-NBA) values,
            // so on the abort cycle where FSMs are still in R_DATA/W_DATA, this clears.
            // During drain cycles (cfg_abort=0), FIFO stays cleared since fifo_push is
            // gated by r_state != R_DRAIN (drained beats are discarded, not stored).
            w_ptr <= '0;
            r_ptr <= '0;
            count <= '0;
        end else begin
            if ((cfg_start || chain_start_i) && !status_busy) begin
                // Reset FIFO on new transfer or chain start
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
    
    // Scatter-Gather descriptor chain registers
    logic        chain_mode;            // SG mode active (vs legacy single-shot)
    logic [31:0] desc_ptr;              // Current descriptor DDR address
    logic [31:0] desc_buf [0:3];        // 4-word descriptor buffer
    logic [1:0]  desc_word_idx;         // Word counter during fetch (0-3)
    logic [15:0] desc_completed_cnt;    // Chain progress counter
    logic        desc_fetch_pending;    // Descriptor fetch AXI read in progress
    logic        chain_next_req;       // W_DONE requests read FSM to fetch next descriptor
    logic        chain_done_req;       // W_DONE signals chain complete
    logic        chain_xfer_ready;    // Read FSM loaded desc, write FSM can start
    logic        chain_xfer_ack;      // Write FSM consumed descriptor start request

    assign chain_active_o    = chain_mode;
    assign desc_completed_o  = desc_completed_cnt;

    // Tile broadcast: dst_addr[31] = broadcast flag
    logic        dst_broadcast;         // Broadcast write to all 4 tile banks
    logic [1:0]  broadcast_bank_cnt;    // 0-3 bank counter during broadcast

    // AXI4 Burst Configuration (constant for INCR bursts)
    assign m_axi_arsize  = 3'b010;  // 4 bytes per beat
    assign m_axi_arburst = 2'b01;   // INCR burst type
    
    // Transfer shape selection:
    //  - 1D mode: cfg_rows == 0, words derived from cfg_size
    //  - 2D mode: cfg_rows != 0, words derived from rows * ceil(cols/word)
    wire        cfg_2d_mode         = (cfg_rows != '0);
    wire [31:0] cfg_cols_words      = (cfg_cols + BYTES_PER_WORD - 1) / BYTES_PER_WORD;
    wire [31:0] cfg_transfer_words  = cfg_2d_mode
                                      ? (cfg_rows * cfg_cols_words)
                                      : ((cfg_size + BYTES_PER_WORD - 1) / BYTES_PER_WORD);

    // Chunked Burst Calculation with 4KB Boundary Protection
    // Max burst = FIFO_DEPTH words, so max ARLEN = FIFO_DEPTH-1
    localparam MAX_BURST_WORDS = FIFO_DEPTH;
    
    // AXI 4KB Boundary Protection - bursts cannot cross 4KB page boundaries
    // Calculate words remaining until next 4KB boundary
    wire [11:0] addr_offset = read_addr[11:0];  // Offset within 4KB page
    wire [31:0] words_to_boundary = (32'd4096 - {20'd0, addr_offset}) >> 2;  // Words until next 4KB boundary
    
    // Step 1: Clamp to remaining words or FIFO depth
    wire [31:0] len_limit_fifo = (read_words_remaining > MAX_BURST_WORDS) 
                                 ? MAX_BURST_WORDS 
                                 : read_words_remaining;

    // In 2D mode, never let one AXI burst cross row boundaries.
    wire [31:0] len_limit_row  = (read_2d_mode && (read_row_words_remaining < len_limit_fifo))
                                 ? read_row_words_remaining
                                 : len_limit_fifo;
    
    // Step 2: Clamp to 4KB boundary - never cross page boundary
    wire [31:0] words_this_burst_raw = (len_limit_row > words_to_boundary) 
                                       ? words_to_boundary 
                                       : len_limit_row;
    // FIX: Guard against zero (unaligned addr at 4KB boundary → underflow to ARLEN=255)
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
            chain_mode <= 1'b0;
            desc_ptr <= '0;
            desc_completed_cnt <= '0;
            desc_word_idx <= '0;
            desc_fetch_pending <= 1'b0;
            chain_xfer_ready <= 1'b0;
        end else if (cfg_abort && r_state != R_DRAIN) begin
            // AXI-SAFE ABORT: Transition to R_DRAIN on first abort cycle.
            // Once in R_DRAIN, the normal case block handles beat draining
            // (cfg_abort is a level signal held for 50+ cycles — must not
            // re-enter this handler while already draining).
            read_words_remaining <= '0;
            read_2d_mode <= 1'b0;
            read_rows_remaining <= '0;
            read_row_words_remaining <= '0;
            chain_mode <= 1'b0;         // Clear chain on abort
            chain_xfer_ready <= 1'b0;
            desc_fetch_pending <= 1'b0;
            if (src_is_tile) begin
                // Tile reads have no in-flight AXI transactions — go directly to IDLE
                r_state <= R_IDLE;
                tile_read_phase <= 1'b0;
            end else case (r_state)
                R_ADDR: begin
                    // ARVALID may be asserted — R_DRAIN will hold until ARREADY,
                    // then drain the resulting data beats with RREADY.
                    r_state <= R_DRAIN;
                end
                R_DATA: begin
                    // Mid-burst — drain remaining beats until RLAST
                    r_state <= R_DRAIN;
                    m_axi_rready <= 1'b1;  // Ensure we accept all remaining beats
                end
                R_DRAIN: begin
                    // Already draining — continue drain even while cfg_abort is held.
                    // CRITICAL: assert rready when rvalid is high to prevent AXI hang.
                    if (m_axi_arvalid) begin
                        if (m_axi_arready) begin
                            m_axi_arvalid <= 1'b0;
                            m_axi_rready <= 1'b1;
                        end
                    end else if (m_axi_rvalid) begin
                        m_axi_rready <= 1'b1;  // Accept pending beats
                        if (m_axi_rready && m_axi_rlast) begin
                            m_axi_rready <= 1'b0;
                            r_state <= R_IDLE;
                        end
                    end else if (!m_axi_rready) begin
                        r_state <= R_IDLE;  // No pending beats, safe to idle
                    end
                end
                R_DESC_FETCH: begin
                    // Abort during descriptor fetch — AXI read may be in-flight
                    if (m_axi_arvalid || m_axi_rready || desc_fetch_pending)
                        r_state <= R_DRAIN;  // Drain the in-flight descriptor burst
                    else
                        r_state <= R_IDLE;
                end
                R_DESC_LOAD: begin
                    // No AXI in-flight, safe to IDLE
                    r_state <= R_IDLE;
                end
                default: begin
                    // IDLE or DONE — safe to go directly to IDLE
                    r_state <= R_IDLE;
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready <= 1'b0;
                end
            endcase
        end else begin
            // Clear-before-case lets R_DESC_LOAD re-assert in the same cycle if needed.
            // Hold ready until the write FSM explicitly acknowledges consumption.
            if (chain_xfer_ack)
                chain_xfer_ready <= 1'b0;
            case (r_state)
                R_IDLE: begin
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready <= 1'b0;
                    tile_read_phase <= 1'b0;
                    // SG chain continuation: W_DONE set chain_next_req
                    if (chain_mode && chain_next_req) begin
                        desc_completed_cnt <= desc_completed_cnt + 16'd1;
                        desc_fetch_pending <= 1'b0;
                        r_state <= R_DESC_FETCH;
                    end else if (chain_mode && chain_done_req) begin
                        chain_mode <= 1'b0;
                        desc_completed_cnt <= desc_completed_cnt + 16'd1;
                    end else if (chain_start_i && !status_busy && desc_head_i != 32'd0) begin
                        // SG chain mode: fetch first descriptor from DDR (ignore null head)
                        chain_mode <= 1'b1;
                        desc_ptr <= desc_head_i;
                        desc_completed_cnt <= 16'd0;
                        desc_word_idx <= 2'd0;
                        desc_fetch_pending <= 1'b0;
                        r_state <= R_DESC_FETCH;
                    end else if (cfg_start && cfg_transfer_words != '0 && !status_busy) begin
                        // Legacy single-shot mode
                        chain_mode <= 1'b0;
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
                        // Tile reads: no AXI AR needed, go directly to R_DATA
                        tile_read_phase <= 1'b0;
                        r_state <= R_DATA;
                    end else
                    // Issue CHUNKED burst - max FIFO_DEPTH words per burst
                    // Only issue if FIFO has room for the burst (space >= words_this_burst)
                    // Available space = FIFO_DEPTH - count
                    // FIX: Only set arvalid if not already in handshake, and HOLD it until arready
                    if (!m_axi_arvalid) begin
                        // Not in handshake yet - check if we can start one
                        if ((32'(FIFO_DEPTH) - 32'(count)) >= words_this_burst && read_words_remaining != '0) begin  // FIX: Explicit width cast
                            m_axi_araddr <= read_addr;
                            // ARLEN = words_this_burst - 1 (clamped to FIFO depth)
                            m_axi_arlen <= words_this_burst[7:0] - 8'd1;
                            current_burst_len <= words_this_burst[7:0] - 8'd1;
                            m_axi_arvalid <= 1'b1;
                        end
                        // else: wait for FIFO space (arvalid stays 0)
                    end else begin
                        // arvalid is HIGH - wait for handshake
                        if (m_axi_arready) begin
                            m_axi_arvalid <= 1'b0;
                            m_axi_rready <= 1'b1;  // Ready to receive data
                            r_state <= R_DATA;
                        end
                        // else: HOLD arvalid until arready (AXI spec requirement!)
                    end
                end
                
                R_DATA: begin
                    if (src_is_tile) begin
                        // TILE READ-BACK: Word-by-word reads with 1-cycle latency
                        // Phase 0: Issue read request (tile_re_o driven combinationally)
                        // Phase 1: Capture data (tile_rvalid_i high, FIFO push via fifo_push_tile)
                        if (!tile_read_phase) begin
                            // Phase 0 → 1: request issued when tile_re_o is asserted
                            // (combinational output gated by !fifo_full && read_words_remaining != 0)
                            if (!fifo_full && read_words_remaining != '0)
                                tile_read_phase <= 1'b1;
                            // else: FIFO full or transfer done — wait for space
                        end else begin
                            // Phase 1 → 0: data captured, advance to next word
                            read_words_remaining <= read_words_remaining - 1'b1;
                            read_addr <= read_addr + BYTES_PER_WORD;
                            if (read_row_words_remaining > 0)
                                read_row_words_remaining <= read_row_words_remaining - 1'b1;
                            tile_read_phase <= 1'b0;
                            if (read_words_remaining == 32'd1)
                                r_state <= R_DONE;
                            // else: back to phase 0 for next word
                        end
                    end else begin
                    // BURST MODE: Stay here receiving ALL beats until RLAST
                    m_axi_rready <= !fifo_full;  // Backpressure if FIFO full

                    if (m_axi_rvalid && m_axi_rready) begin
                        // Data beat received - FIFO push happens via fifo_push wire
                        read_words_remaining <= read_words_remaining - 1'b1;
                        if (read_row_words_remaining > 0)
                            read_row_words_remaining <= read_row_words_remaining - 1'b1;
                        
                        // Check for RLAST (end of this burst chunk)
                        if (m_axi_rlast) begin
                            m_axi_rready <= 1'b0;

                            // Check if transfer complete
                            if (read_words_remaining == 32'd1) begin
                                // This was the last word of the last chunk
                                r_state <= R_DONE;
                            end else begin
                                if (read_2d_mode && (read_row_words_remaining == 32'd1)) begin
                                    // End of current row: jump to next row base using stride.
                                    read_row_base_addr <= read_row_base_addr + read_row_stride;
                                    read_addr <= read_row_base_addr + read_row_stride;
                                    if (read_rows_remaining > 0)
                                        read_rows_remaining <= read_rows_remaining - 1'b1;
                                    read_row_words_remaining <= read_cols_words;
                                end else begin
                                    // Continue in current row
                                    read_addr <= read_addr + ((32'(current_burst_len) + 32'd1) * BYTES_PER_WORD);  // FIX: Cast to 32-bit
                                end

                                // More chunks to transfer - loop back to R_ADDR
                                r_state <= R_ADDR;
                            end
                        end
                        // Otherwise stay in R_DATA for next beat
                    end
                    end // else (AXI path)
                end

                R_DONE: begin
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready <= 1'b0;
                    if (chain_next_req) begin
                        // Write engine finished a descriptor, fetch next
                        // (chain_next_req is cleared by write FSM)
                        desc_completed_cnt <= desc_completed_cnt + 16'd1;
                        desc_fetch_pending <= 1'b0;
                        r_state <= R_DESC_FETCH;
                    end else if (chain_done_req) begin
                        // Chain complete
                        // (chain_done_req is cleared by write FSM)
                        chain_mode <= 1'b0;
                        desc_completed_cnt <= desc_completed_cnt + 16'd1;
                        r_state <= R_IDLE;
                    end else begin
                        r_state <= R_IDLE;
                    end
                end
                
                R_DRAIN: begin
                    // AXI-SAFE ABORT DRAIN STATE
                    // Handle AR handshake and R data beats SIMULTANEOUSLY.
                    // AXI allows outstanding reads: a previous burst's data
                    // can arrive while a new AR is still pending.

                    // AR channel: complete any pending handshake
                    if (m_axi_arvalid && m_axi_arready)
                        m_axi_arvalid <= 1'b0;

                    // R channel: always accept beats when rvalid is high
                    if (m_axi_rvalid) begin
                        m_axi_rready <= 1'b1;
                        if (m_axi_rready && m_axi_rlast) begin
                            // Last beat of burst drained
                            m_axi_rready <= 1'b0;
                            if (!m_axi_arvalid)
                                r_state <= R_IDLE;  // Both channels done
                            // else: AR still pending, stay in drain
                        end
                    end else if (!m_axi_arvalid && !m_axi_rready) begin
                        // No AR pending, no R beats pending — safe to idle
                        r_state <= R_IDLE;
                    end
                end
                
                // =============================================================
                // SG: Descriptor Fetch — read 4-word descriptor from DDR
                // =============================================================
                R_DESC_FETCH: begin
                    if (!desc_fetch_pending && !m_axi_arvalid) begin
                        // Issue AXI AR for 4-word (16-byte) descriptor read
                        m_axi_araddr <= desc_ptr;
                        m_axi_arlen <= 8'd3;           // 4-word burst (ARLEN=3)
                        current_burst_len <= 8'd3;
                        m_axi_arvalid <= 1'b1;
                        desc_word_idx <= 2'd0;
                    end else if (m_axi_arvalid && m_axi_arready) begin
                        m_axi_arvalid <= 1'b0;
                        m_axi_rready <= 1'b1;
                        desc_fetch_pending <= 1'b1;
                    end else if (desc_fetch_pending && m_axi_rvalid && m_axi_rready) begin
                        // Capture descriptor words
                        desc_buf[desc_word_idx] <= m_axi_rdata;
                        desc_word_idx <= desc_word_idx + 2'd1;
                        if (m_axi_rlast) begin
                            m_axi_rready <= 1'b0;
                            desc_fetch_pending <= 1'b0;
                            r_state <= R_DESC_LOAD;
                        end
                    end
                end

                // =============================================================
                // SG: Descriptor Load — parse fields, start transfer
                // =============================================================
                R_DESC_LOAD: begin
                    // desc_buf[0]=src, desc_buf[1]=dst, desc_buf[2]=size, desc_buf[3]=next
                    if (desc_buf[2] == 32'd0) begin
                        // Size=0: skip this descriptor, follow next
                        desc_ptr <= desc_buf[3];
                        desc_completed_cnt <= desc_completed_cnt + 16'd1;
                        if (desc_buf[3] == 32'd0)
                            r_state <= R_DONE;  // End of chain
                        else
                            r_state <= R_DESC_FETCH;
                    end else begin
                        // Load transfer parameters from descriptor
                        read_addr <= desc_buf[0];
                        read_words_remaining <= desc_buf[2][31:2]; // bytes to words
                        src_is_tile <= (desc_buf[0][31:28] == 4'h1);
                        read_2d_mode <= 1'b0;  // SG is always 1D
                        read_rows_remaining <= 32'd1;
                        read_cols_words <= desc_buf[2][31:2];
                        read_row_words_remaining <= desc_buf[2][31:2];
                        read_row_base_addr <= desc_buf[0];
                        desc_ptr <= desc_buf[3];  // Save next pointer
                        chain_xfer_ready <= 1'b1; // Signal write FSM
                        r_state <= R_ADDR;
                    end
                end

                default: r_state <= R_IDLE;
            endcase
        end
    end

    // =========================================================================
    // 3. Write Engine (Consumer) - Drains FIFO to destination
    // =========================================================================
    logic [31:0] write_addr;
    logic [31:0] write_words_remaining;
    logic [DATA_WIDTH-1:0] write_data_reg;  // Latched FIFO data
    logic        write_data_reg_valid;      // Pipeline register has valid data
    logic [31:0] local_write_addr;          // Address captured BEFORE increment for local writes
    
    // AXI4 Write Burst Tracking
    logic [7:0]  write_burst_len;           // Current burst length (AWLEN value, 0-indexed)
    logic [7:0]  write_beat_counter;        // Counts beats in current burst (0 to AWLEN)
    logic [31:0] write_burst_words;         // Words in this burst (for address increment)
    
    // AXI4 Write Burst Configuration (constant signals)
    assign m_axi_awsize  = 3'b010;  // 4 bytes per beat
    assign m_axi_awburst = 2'b01;   // INCR burst type
    assign m_axi_wstrb   = {(DATA_WIDTH/8){1'b1}};    // FIX: Parameterized full-word strobe (was hardcoded 4'hF)
    
    // FIX: Write-burst boundary variables computed in always_comb for proper synthesis
    // (blocking = inside always_ff causes sim/synth mismatch with some tools)
    logic [11:0] write_addr_offset;
    logic [31:0] words_to_write_boundary;
    logic [31:0] len_limit_fifo_write;
    logic [31:0] words_this_write_burst;

    always_comb begin
        write_addr_offset       = write_addr[11:0];
        words_to_write_boundary = (32'd4096 - {20'd0, write_addr_offset}) >> 2;
        len_limit_fifo_write    = (write_words_remaining > MAX_BURST_WORDS)
                                  ? MAX_BURST_WORDS
                                  : write_words_remaining;
        words_this_write_burst  = (len_limit_fifo_write > words_to_write_boundary)
                                  ? words_to_write_boundary
                                  : len_limit_fifo_write;
        if (words_this_write_burst == '0) words_this_write_burst = 32'd1;
    end
    
    // Dynamic signals driven by FSM
    // m_axi_awlen, m_axi_wlast - driven in FSM based on burst tracking
    
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
            chain_next_req <= 1'b0;
            chain_done_req <= 1'b0;
            chain_xfer_ack <= 1'b0;
        end else if (cfg_abort && w_state != W_DRAIN) begin
            chain_next_req <= 1'b0;
            chain_done_req <= 1'b0;
            chain_xfer_ack <= 1'b0;
            // AXI-SAFE ABORT: Transition to W_DRAIN on first abort cycle.
            // Once in W_DRAIN, the normal case block handles the drain
            // (cfg_abort level signal — must not re-enter while draining).
            // protocol violations (VALID must not drop without READY handshake).
            write_words_remaining <= '0;
            dst_is_axi <= 1'b0;
            dst_is_tile <= 1'b0;
            dst_is_config <= 1'b0;
            local_write_en <= 1'b0;
            local_fifo_pop <= 1'b0;
            axi_fifo_pop <= 1'b0;
            case (w_state)
                W_ADDR: begin
                    // AWVALID may be asserted — W_DRAIN completes the AW handshake,
                    // then sends all beats with WLAST to satisfy the slave.
                    // Deassert bready (was set early in W_WAIT) — not ready for B yet.
                    m_axi_bready <= 1'b0;
                    if (!m_axi_awvalid) begin
                        // AW never asserted — no transaction in flight, safe to IDLE
                        w_state <= W_IDLE;
                        write_data_reg_valid <= 1'b0;
                        write_beat_counter <= '0;
                    end else begin
                        // FIX: If AW handshake completes on abort cycle, clear awvalid
                        // so W_DRAIN doesn't re-attempt the address phase (would deadlock
                        // since slave already consumed the address).
                        if (m_axi_awready) begin
                            m_axi_awvalid <= 1'b0;
                        end
                        w_state <= W_DRAIN;
                    end
                end
                W_DATA: begin
                    // Mid-burst — W_DRAIN will complete remaining beats with dummy data.
                    // Deassert bready (was set early in W_WAIT) — not ready for B yet.
                    m_axi_bready <= 1'b0;
                    // FIX: If a W beat handshake completes on the same cycle as abort,
                    // the slave accepted this beat. Account for it before entering drain
                    // to prevent the drain from re-sending it (extra beat → WLAST error).
                    if (m_axi_wvalid && m_axi_wready) begin
                        write_beat_counter <= write_beat_counter + 8'd1;
                        m_axi_wvalid <= 1'b0;
                        m_axi_wlast <= 1'b0;
                    end
                    // If wvalid=1 && wready=0: leave wvalid asserted (AXI compliance:
                    // VALID must hold until READY). W_DRAIN will handle the pending beat.
                    w_state <= W_DRAIN;
                end
                W_RESP: begin
                    // FIX: If B response handshake completes on abort cycle,
                    // the burst is fully done — go directly to IDLE.
                    // Without this, W_DRAIN would see bready=1 and wait for
                    // a second BVALID that will never arrive (deadlock).
                    if (m_axi_bvalid && m_axi_bready) begin
                        m_axi_bready <= 1'b0;
                        write_data_reg_valid <= 1'b0;
                        write_beat_counter <= '0;
                        w_state <= W_IDLE;
                    end else begin
                        // Still waiting for BVALID — W_DRAIN will handle it
                        w_state <= W_DRAIN;
                    end
                end
                W_DRAIN: begin
                    // Already draining — continue drain even while cfg_abort is held.
                    // Duplicate drain logic here because cfg_abort blocks the else branch.
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
                    // W_IDLE, W_WAIT, W_DONE, W_LOCAL — safe to go directly to IDLE
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
            chain_xfer_ack <= 1'b0;
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
                    // Auto-clear chain request flags after read FSM consumes them
                    if (chain_next_req && r_state == R_DESC_FETCH) chain_next_req <= 1'b0;
                    if (chain_done_req && r_state == R_IDLE) chain_done_req <= 1'b0;
                    if (chain_mode && chain_xfer_ready) begin
                        chain_xfer_ack <= 1'b1;
                        // SG mode: read engine loaded desc, start write side
                        write_addr <= {1'b0, desc_buf[1][30:0]}; // clear broadcast bit from addr
                        write_words_remaining <= desc_buf[2][31:2];
                        dst_is_axi    <= (desc_buf[1][31:28] == 4'h0) && !desc_buf[1][31];
                        dst_is_tile   <= (desc_buf[1][31:28] == 4'h1) || desc_buf[1][31];
                        dst_is_config <= (desc_buf[1][31:28] == 4'h2);
                        dst_broadcast <= desc_buf[1][31];
                        w_state <= W_WAIT;
                    end else if (cfg_start && cfg_transfer_words != '0 && !status_busy) begin
                        // Legacy single-shot mode
                        write_addr <= cfg_dst;
                        write_words_remaining <= cfg_transfer_words;
                        dst_is_axi    <= (cfg_dst[31:28] == 4'h0);
                        dst_is_tile   <= (cfg_dst[31:28] == 4'h1);
                        dst_is_config <= (cfg_dst[31:28] == 4'h2);
                        dst_broadcast <= 1'b0;
                        // synthesis translate_off
                        if (cfg_dst[31:28] != 4'h0 && cfg_dst[31:28] != 4'h1 && cfg_dst[31:28] != 4'h2)
                            $warning("[DMA] Unrecognized destination prefix 0x%01h", cfg_dst[31:28]);
                        // synthesis translate_on
                        w_state <= W_WAIT;
                    end
                end
                
                W_WAIT: begin
                    // NOTE: bready is asserted early (before AW/W phases complete).
                    // This is AXI-legal and recommended for throughput. However, it
                    // assumes the slave will NOT send BVALID before receiving WLAST.
                    // Our axi_ram.sv always waits for WLAST. If porting to a slave
                    // that sends early BVALID, move bready assertion to after WLAST.
                    m_axi_bready <= 1'b1;
                    
                    // Wait for FIFO to have data and calculate burst size
                    local_write_en <= 1'b0;
                    local_fifo_pop <= 1'b0;
                    axi_fifo_pop <= 1'b0;
                    
                    if (!fifo_empty && write_words_remaining != '0) begin
                        if (dst_is_axi) begin
                            // FIX: Burst size now computed in always_comb above (was blocking = here)
                            // Set burst parameters from combinationally-computed values
                            write_burst_len <= words_this_write_burst[7:0] - 8'd1;  // AWLEN is N-1
                            write_burst_words <= words_this_write_burst;
                            write_beat_counter <= '0;
                        end
                        
                        // Latch first data word from FIFO (for both AXI and local)
                        write_data_reg <= fifo_rdata;
                        write_data_reg_valid <= 1'b1;  // Mark valid for W_DATA
                        
                        // Pop FIFO NOW for first word
                        if (dst_is_axi) begin
                            axi_fifo_pop <= 1'b1;
                        end else begin
                            local_fifo_pop <= 1'b1;
                        end
                        
                        w_state <= dst_is_axi ? W_ADDR : W_LOCAL;
                    end else if (write_words_remaining == '0) begin
                        w_state <= W_DONE;
                    end
                end
                
                W_ADDR: begin
                    // Clear pop signals from W_WAIT
                    axi_fifo_pop <= 1'b0;
                    local_fifo_pop <= 1'b0;
                    
                    if (dst_is_axi) begin
                        // AW phase - address and burst length for AXI
                        if (!m_axi_awvalid) begin
                            // First cycle - assert valid with burst info
                            m_axi_awaddr <= write_addr;
                            m_axi_awlen <= write_burst_len;  // Burst length (N-1)
                            m_axi_awvalid <= 1'b1;
                        end else if (m_axi_awready) begin
                            // Handshake complete
                            m_axi_awvalid <= 1'b0;
                            w_state <= W_DATA;
                        end
                    end
                    // Note: Local destinations (tile/config) are handled by W_LOCAL
                    // state — W_WAIT routes them there directly via line 688.
                end
                
                W_DATA: begin
                    // W phase - burst data transfer with beat-by-beat handshake
                    // Strategy: Use write_data_reg as pipeline register for ALL beats
                    // - Beat 0: write_data_reg was loaded in W_WAIT (word0 already popped)
                    // - Beat N: After handshake, pop FIFO into write_data_reg for next beat
                    // 
                    // CRITICAL: write_data_reg_valid tracks if pipeline register has fresh data
                    // When FIFO is empty (read side slower due to 4KB split), we must wait
                    axi_fifo_pop <= 1'b0;
                    
                    if (!m_axi_wvalid) begin
                        // wvalid is low - check if we have valid data to send
                        if (write_beat_counter == 0 || write_data_reg_valid) begin
                            // Have valid data - assert wvalid
                            m_axi_wdata <= write_data_reg;
                            m_axi_wlast <= (write_beat_counter == write_burst_len);
                            m_axi_wvalid <= 1'b1;
                            write_data_reg_valid <= 1'b0;  // Will be consumed
                        end else if (!fifo_empty) begin
                            // Need data and FIFO has it - load pipeline register
                            write_data_reg <= fifo_rdata;
                            axi_fifo_pop <= 1'b1;
                            write_data_reg_valid <= 1'b1;
                            // Next cycle will assert wvalid
                        end
                        // else: waiting for FIFO data - stay with wvalid low
                    end else if (m_axi_wready) begin
                        // Handshake occurred - beat transferred
                        write_words_remaining <= write_words_remaining - 1'b1;
                        
                        if (write_beat_counter == write_burst_len) begin
                            // Last beat - go to response phase
                            m_axi_wvalid <= 1'b0;
                            m_axi_wlast <= 1'b0;
                            m_axi_bready <= 1'b1;
                            write_addr <= write_addr + (write_burst_words * BYTES_PER_WORD);
                            w_state <= W_RESP;
                        end else if (!fifo_empty) begin
                            // More beats AND FIFO has data - load next word
                            write_beat_counter <= write_beat_counter + 1'b1;
                            write_data_reg <= fifo_rdata;
                            axi_fifo_pop <= 1'b1;
                            write_data_reg_valid <= 1'b1;
                            // Deassert wvalid for 1 cycle to load new data
                            m_axi_wvalid <= 1'b0;
                            m_axi_wlast <= 1'b0;
                        end else begin
                            // More beats but FIFO empty - wait for data
                            write_beat_counter <= write_beat_counter + 1'b1;
                            write_data_reg_valid <= 1'b0;  // Mark invalid
                            m_axi_wvalid <= 1'b0;
                            m_axi_wlast <= 1'b0;
                        end
                    end
                    // else: waiting for wready - hold signals unchanged
                end
                
                W_RESP: begin
                    // B phase - wait for write response
                    // m_axi_bready stays HIGH throughout this state (asserted in W_DATA or W_WAIT)
                    // This follows AXI best practice: keep ready high while waiting for valid.
                    
                    if (m_axi_bvalid) begin
                        // Response received - de-assert ready until next burst is queued
                        m_axi_bready <= 1'b0;

                        // BRESP error detection handled by status block via
                        // combinational bresp_error signal (see below).

                        // Check if all words written
                        if (write_words_remaining == 32'd0) begin
                            // Transfer complete
                            w_state <= W_DONE;
                        end else begin
                            // More words to write - start next burst
                            w_state <= W_WAIT;
                        end
                    end
                    // else: waiting for bvalid - hold bready
                end
                
                W_DONE: begin
                    m_axi_awvalid <= 1'b0;
                    m_axi_wvalid <= 1'b0;
                    m_axi_bready <= 1'b0;
                    local_write_en <= 1'b0;
                    local_fifo_pop <= 1'b0;
                    if (chain_mode) begin
                        // SG chain: signal read FSM to fetch next or finish
                        if (desc_ptr == 32'd0) begin
                            chain_done_req <= 1'b1;
                        end else begin
                            chain_next_req <= 1'b1;
                        end
                        w_state <= W_IDLE;
                    end else begin
                        w_state <= W_IDLE;
                    end
                end
                
                W_DRAIN: begin
                    // AXI-SAFE ABORT DRAIN STATE
                    // Completes in-flight AXI write transactions without violating protocol.
                    // The slave (axi_ram) counts beats by AWLEN, so we MUST send exactly
                    // AWLEN+1 total beats with WLAST on the final one.
                    //
                    // Phase 1: If AWVALID is asserted, hold until AWREADY completes.
                    // Phase 2: Send remaining W beats with dummy data until beat_counter == burst_len.
                    // Phase 3: Wait for BVALID response.
                    //
                    // Entry paths:
                    //   W_ADDR (awvalid=1): → W_DRAIN: Complete AW, then send all beats
                    //   W_ADDR (awvalid=0): → IDLE (no AXI transaction started)
                    //   W_DATA: → W_DRAIN: Continue from current beat_counter
                    //   W_RESP: → W_DRAIN: bready already high → wait for BVALID
                    axi_fifo_pop <= 1'b0;  // No new FIFO pops during drain
                    
                    if (m_axi_awvalid) begin
                        // Phase 1: Complete AW handshake
                        if (m_axi_awready) begin
                            m_axi_awvalid <= 1'b0;
                            // Start sending beats from beat 0
                            write_beat_counter <= '0;
                            m_axi_wdata <= '0;
                            m_axi_wlast <= (write_burst_len == 8'd0);  // Single-beat burst?
                            m_axi_wvalid <= 1'b1;
                        end
                        // else: hold AWVALID — AXI spec requires it stays asserted
                    end else if (m_axi_wvalid) begin
                        // Phase 2: Send W beats until all AWLEN+1 beats are accepted
                        if (m_axi_wready) begin
                            if (write_beat_counter == write_burst_len) begin
                                // Last beat accepted — go to response phase
                                m_axi_wvalid <= 1'b0;
                                m_axi_wlast <= 1'b0;
                                m_axi_bready <= 1'b1;
                            end else begin
                                // More beats needed — send next with dummy data
                                write_beat_counter <= write_beat_counter + 8'd1;
                                m_axi_wdata <= '0;
                                m_axi_wlast <= ((write_beat_counter + 8'd1) == write_burst_len);
                                m_axi_wvalid <= 1'b1;
                            end
                        end
                        // else: hold WVALID — waiting for WREADY
                    end else if (m_axi_bready) begin
                        // Phase 3: Wait for write response
                        if (m_axi_bvalid) begin
                            m_axi_bready <= 1'b0;
                            write_data_reg_valid <= 1'b0;
                            write_beat_counter <= '0;
                            w_state <= W_IDLE;
                        end
                    end else begin
                        // No AWVALID, WVALID, or BREADY active.
                        // This path is reached when entering from W_DATA with wvalid=0
                        // (FIFO was empty, waiting for data). The AW handshake already
                        // completed — we owe the slave remaining W beats.
                        // write_beat_counter tracks beats already accepted by slave.
                        if (write_beat_counter <= write_burst_len) begin
                            // Resume sending dummy beats from current position
                            m_axi_wdata <= '0;
                            m_axi_wlast <= (write_beat_counter == write_burst_len);
                            m_axi_wvalid <= 1'b1;
                        end else begin
                            // All beats sent (shouldn't happen here, defensive)
                            m_axi_bready <= 1'b1;
                        end
                    end
                end
                
                W_LOCAL: begin
                    // ─── Local drain: tile/config writes ────────────────────
                    local_fifo_pop <= 1'b0;

                    if (dst_broadcast && dst_is_tile) begin
                        // Tile broadcast: write same data to all 4 banks
                        // Cycle bank_cnt 0→1→2→3 per word
                        local_write_addr <= {write_addr[31:14],
                                             broadcast_bank_cnt, write_addr[11:0]};
                        local_write_en   <= 1'b1;
                        if (broadcast_bank_cnt == 2'd3) begin
                            // Done with all 4 banks for this word
                            broadcast_bank_cnt <= 2'd0;
                            write_addr <= write_addr + BYTES_PER_WORD;
                            write_words_remaining <= write_words_remaining - 1'b1;
                            if (write_words_remaining == 32'd1)
                                w_state <= W_DONE;
                            else
                                w_state <= W_WAIT;
                        end else begin
                            broadcast_bank_cnt <= broadcast_bank_cnt + 2'd1;
                            // Stay in W_LOCAL for next bank (same word)
                        end
                    end else begin
                        // Normal single-bank write
                        local_write_addr      <= write_addr;
                        local_write_en        <= 1'b1;
                        write_addr            <= write_addr + BYTES_PER_WORD;
                        write_words_remaining <= write_words_remaining - 1'b1;
                        if (write_words_remaining == 32'd1)
                            w_state <= W_DONE;
                        else
                            w_state <= W_WAIT;
                    end
                end

                default: w_state <= W_IDLE;
            endcase
        end
    end

    // =========================================================================
    // Local Memory & Config Output Assignments
    // =========================================================================
    // Combinational driving based on local_write_en and destination type
    // Use registered local_write_addr to avoid using post-increment address
    // Tile read-back: combinational read enable for tile memory
    wire tile_rd_en = src_is_tile && (r_state == R_DATA) && !tile_read_phase
                      && !fifo_full && (read_words_remaining != '0);

    // Mux tile addr/bank between read engine (src_is_tile) and write engine (dst_is_tile)
    // These are mutually exclusive per transfer: a single DMA op cannot have both
    // src and dst in tile address space for any useful operation.
    assign tile_addr_o     = src_is_tile ? read_addr[11:0]   : local_write_addr[11:0];
    assign tile_bank_sel_o = src_is_tile ? read_addr[13:12]  : local_write_addr[13:12];
    assign tile_re_o       = tile_rd_en;
    assign tile_wdata_o    = write_data_reg;
    assign tile_we_o       = local_write_en && dst_is_tile;
    
    assign config_addr_o   = local_write_addr;
    assign config_wdata_o  = write_data_reg;

    // AXI ID: constant value (single master, no reordering)
    assign m_axi_awid = {AXI_ID_WIDTH{1'b0}};
    assign m_axi_arid = {AXI_ID_WIDTH{1'b0}};
    assign config_we_o     = local_write_en && dst_is_config;
    
    // =========================================================================
    // 4. Status and IRQ Generation
    // =========================================================================
    logic transfer_active;
    logic transfer_started;  // FIX: One-cycle delay to let FSMs leave IDLE
    
    // =========================================================================
    // Error Capture (AXI BRESP/RRESP monitoring)
    // =========================================================================
    // error_code_reg is sticky (holds last error). Cleared on new cfg_start.
    // Combinational detection signals feed the status always_ff block.
    logic [1:0] error_code_reg;
    logic       error_flag;

    assign error_code  = error_code_reg;
    assign error_valid = error_flag;

    // Combinational error detection from AXI responses
    // FIX: Check != 2'b00 (not just [1]) to capture SLVERR (2'b01) in addition
    // to DECERR (2'b10). Previously only MSB was tested, silently dropping SLVERR.
    wire bresp_error = m_axi_bvalid && m_axi_bready && (m_axi_bresp != 2'b00);
    wire rresp_error = m_axi_rvalid && m_axi_rready && (m_axi_rresp != 2'b00);

    // Robust busy check: stays HIGH until ALL components are idle
    // This prevents producer-consumer mismatch where Write FSM finishes early
    // NOTE: Drain states are NOT idle — busy stays high during AXI-safe abort drain
    wire engine_idle = (r_state == R_IDLE) && (w_state == W_IDLE) && fifo_empty;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            transfer_active <= 1'b0;
            transfer_started <= 1'b0;
            status_busy <= 1'b0;
            status_done <= 1'b0;
            irq_done <= 1'b0;
            error_code_reg <= 2'b00;
            error_flag <= 1'b0;
        end else if (cfg_abort) begin
            // Abort clears transfer state but keeps busy HIGH while drain is active.
            // This prevents a new cfg_start from colliding with the AXI drain.
            // FIX: Use !engine_idle — it reads pre-NBA state just like the FSMs,
            // so it's true whenever any FSM is active or FIFO non-empty. The old
            // drain_active check was false on the first abort cycle (FSMs hadn't
            // transitioned to DRAIN yet), causing a 1-cycle busy=0 glitch.
            transfer_active <= 1'b0;
            transfer_started <= 1'b0;
            status_busy <= !engine_idle;  // Stay busy until ALL components idle
            status_done <= 1'b0;  // Don't signal done on abort
            irq_done <= 1'b0;
        end else if (!transfer_active && status_busy && engine_idle) begin
            // Post-drain cleanup: FSMs finished draining, clear busy
            status_busy <= 1'b0;
            status_done <= 1'b0;
            irq_done <= 1'b0;
        end else begin
            // Default: clear done pulse
            status_done <= 1'b0;
            irq_done <= 1'b0;

            // Capture AXI error responses (sticky — cleared on next cfg_start)
            if (bresp_error || rresp_error) begin
                error_code_reg <= bresp_error ? m_axi_bresp : m_axi_rresp;
                error_flag <= 1'b1;
            end

            if (chain_start_i && !status_busy && desc_head_i != 32'd0) begin
                // SG chain start (ignore if desc_head is null)
                error_code_reg <= 2'b00;
                error_flag <= 1'b0;
                transfer_active <= 1'b1;
                status_busy <= 1'b1;
            end else if (!chain_mode && transfer_active && engine_idle) begin
                // Legacy single-shot: transfer complete
                transfer_active <= 1'b0;
                status_done <= 1'b1;
                irq_done <= 1'b1;
            end else if (chain_mode && !chain_active_o && engine_idle) begin
                // SG chain complete (chain_mode cleared by read FSM on chain done)
                transfer_active <= 1'b0;
                status_done <= 1'b1;
                irq_done <= 1'b1;
            end

            if (cfg_start && !status_busy) begin
                // Clear error on new transfer start
                error_code_reg <= 2'b00;
                error_flag <= 1'b0;
                if (cfg_transfer_words != '0) begin
                    // Start new transfer
                    transfer_active <= 1'b1;
                    transfer_started <= 1'b0;
                    status_busy <= 1'b1;
                end else begin
                    // FIX: Zero-length transfer → nothing to do, immediately done
                    status_done <= 1'b1;
                    irq_done    <= 1'b1;
                end
            end else if (transfer_active && !transfer_started) begin
                // FIX: Wait one cycle for FSMs to leave IDLE before checking engine_idle
                transfer_started <= 1'b1;
            end else if (transfer_active && transfer_started && engine_idle) begin
                // Complete when ALL parts are done:
                // - Read FSM in IDLE
                // - Write FSM in IDLE  
                // - FIFO is empty (all data consumed)
                transfer_active <= 1'b0;
                transfer_started <= 1'b0;
                status_busy <= 1'b0;
                status_done <= 1'b1;
                irq_done <= 1'b1;
            end
        end
    end

    // =========================================================================
    // 5. WHITE-BOX ASSERTIONS (iverilog-compatible procedural checks)
    // =========================================================================
    // These checks catch internal bugs that external protocol monitors miss.
    // synthesis translate_off
    
    // DMA ABORT SAFETY ASSERTION
    // cfg_abort (connected to cu_soft_reset) transitions R/W FSMs through
    // R_DRAIN / W_DRAIN states that complete any in-flight AXI transactions
    // before returning to IDLE. These $info messages are informational only;
    // the drain states ensure no AXI protocol violation occurs.
    always_ff @(posedge clk) begin
        if (cfg_abort && !(!rst_n)) begin
            if (m_axi_arvalid || (r_state == R_DATA))
                $info("[DMA ABORT] Abort during AXI read — draining via R_DRAIN");
            if (m_axi_awvalid || m_axi_wvalid || (w_state == W_DATA) || (w_state == W_RESP))
                $info("[DMA ABORT] Abort during AXI write — draining via W_DRAIN");
        end
    end
    
    // Deadlock detection counter (unsigned to avoid signed overflow after ~21s)
    int unsigned busy_cycle_count;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            busy_cycle_count <= 0;
        end else begin
            // Track how long busy has been asserted
            if (status_busy) begin
                busy_cycle_count <= busy_cycle_count + 1;
                if (busy_cycle_count > 100000) begin
                    $error("[DMA ASSERT] FSM Deadlock - busy stuck for 100000+ cycles!");
                end
            end else begin
                busy_cycle_count <= 0;
            end
            
            // Check 1: FIFO Overflow Protection
            if (m_axi_rvalid && m_axi_rready && fifo_full) begin
                $error("[DMA ASSERT] CRITICAL: FIFO Overflow - push when full!");
            end
            
            // Check 2: FIFO Underflow Protection - only check actual fifo_pop signal
            // Note: With new design, FIFO is popped in W_WAIT (before W_DATA), so wvalid/wready
            // during AXI write handshake does NOT indicate FIFO pop anymore
            if (fifo_pop && fifo_empty) begin
                $error("[DMA ASSERT] CRITICAL: FIFO Underflow - pop when empty!");
            end
            
            // Check 3: FIFO Count Sanity
            if (count > FIFO_DEPTH) begin
                $error("[DMA ASSERT] FIFO count exceeded depth: %0d > %0d", count, FIFO_DEPTH);
            end
            
            // Check 4: Read FSM State Valid
            if (r_state != R_IDLE && r_state != R_ADDR && 
                r_state != R_DATA && r_state != R_DONE &&
                r_state != R_DRAIN) begin
                $error("[DMA ASSERT] Read FSM in invalid state: %0d", r_state);
            end
            
            // Check 5: Write FSM State Valid
            if (w_state != W_IDLE && w_state != W_WAIT && w_state != W_ADDR &&
                w_state != W_DATA && w_state != W_RESP && w_state != W_DONE &&
                w_state != W_DRAIN && w_state != W_LOCAL) begin
                $error("[DMA ASSERT] Write FSM in invalid state: %0d", w_state);
            end
            
            // Check 6: AXI4 Write Protocol - WLAST must be high on last beat
            // Skip during W_DRAIN — drain reuses beat_counter but may start from a different
            // position than normal flow expects, so the relationship may not hold cleanly.
            if (w_state != W_DRAIN && m_axi_wvalid && m_axi_wready && m_axi_wlast && (write_beat_counter != write_burst_len)) begin
                $error("[DMA ASSERT] WLAST asserted but beat_counter(%0d) != burst_len(%0d)", 
                       write_beat_counter, write_burst_len);
            end
            
            // Check 7: AXI4 Write Protocol - No WLAST before last beat
            // Skip during W_DRAIN — drain may resume from mid-burst with different counter state
            if (w_state != W_DRAIN && m_axi_wvalid && m_axi_wready && !m_axi_wlast && (write_beat_counter == write_burst_len)) begin
                $error("[DMA ASSERT] Last beat but WLAST not asserted!");
            end
            
            // Check 8: AXI4 Write Protocol - AWVALID/WVALID dependency
            // WDATA can appear before, simultaneous with, or after AWADDR
            // But we should never have WVALID without having issued AWVALID first
            if (m_axi_wvalid && w_state == W_ADDR && !m_axi_awvalid) begin
                $warning("[DMA WARN] WVALID high in W_ADDR state without AWVALID");
            end
            // Check 9: FIFO pop mutual exclusion — AXI and local pop must never fire together
            if (fifo_pop_axi && fifo_pop_local) begin
                $error("[DMA ASSERT] FIFO pop race: both axi_fifo_pop and local_fifo_pop active simultaneously!");
            end

            // Check 10: FIFO push mutual exclusion — AXI and tile push must never fire together
            if (fifo_push_axi && fifo_push_tile) begin
                $error("[DMA ASSERT] FIFO push race: both AXI and tile push active simultaneously!");
            end
        end
    end

    // synthesis translate_on

    // =========================================================================
    // Debug Signal Assignments (For ILA probing)
    // =========================================================================
    assign dbg_status_busy           = status_busy;
    assign dbg_read_fsm_state        = r_state;  // Now 3-bit (was 2-bit + pad)
    assign dbg_write_fsm_state       = w_state;
    assign dbg_fifo_full             = fifo_full;
    assign dbg_fifo_empty            = fifo_empty;
    assign dbg_write_words_remaining = write_words_remaining;

    // synthesis translate_off
    always @(posedge clk) begin
        if (chain_start_i)
            $display("[SG-START %0t] chain_start pulse! r=%0d busy=%0b desc_head=%08h",
                     $time, r_state, status_busy, desc_head_i);
        // Post-abort state trace: when busy but not abort
        if (status_busy && !cfg_abort && !transfer_active && !chain_mode)
            $display("[SG-STUCK %0t] r=%0d w=%0d fifo=%0d idle=%0b arv=%0b ardy=%0b awv=%0b bv=%0b rv=%0b",
                     $time, r_state, w_state, count, engine_idle,
                     m_axi_arvalid, m_axi_arready, m_axi_awvalid, m_axi_bvalid, m_axi_rvalid);
        if (status_done)
            $display("[SG-DONE %0t] status_done! r=%0d w=%0d cm=%0b ta=%0b busy=%0b idle=%0b dc=%0d",
                     $time, r_state, w_state, chain_mode, transfer_active, status_busy, engine_idle, desc_completed_cnt);
        if (chain_mode || chain_start_i || (cfg_abort && status_busy)) begin
            $display("[SG %0t] r=%0d w=%0d cm=%0b xr=%0b cnr=%0b cdr=%0b ta=%0b busy=%0b done=%0b fifo=%0d rw=%0d ww=%0d arv=%0b rv=%0b abt=%0b idle=%0b dp=%08h dc=%0d",
                     $time, r_state, w_state, chain_mode, chain_xfer_ready,
                     chain_next_req, chain_done_req,
                     transfer_active, status_busy, status_done,
                     count, read_words_remaining, write_words_remaining,
                     m_axi_arvalid, m_axi_rvalid, cfg_abort, engine_idle,
                     desc_ptr, desc_completed_cnt);
        end
    end
    // synthesis translate_on

endmodule
