// ==============================================================================
// CGRA DMA Engine - Pipelined Producer-Consumer Architecture
// ==============================================================================
// AXI4-Lite master for data/config transfers between external RAM and CGRA.
//
// ARCHITECTURE:
//   - Read Engine (Producer): Fetches data from AXI, pushes to FIFO
//   - 8-Word FIFO: Decouples read/write timing
//   - Write Engine (Consumer): Pops FIFO, writes to destination
//
// DESTINATION ROUTING (by address prefix):
//   0x1XXX_XXXX → Tile Memory (4 banks × 4KB)
//   0x2XXX_XXXX → Config RAM (16 PEs × 16 slots × 64-bit)
//   Other       → AXI External Memory
//
// DOUBLE-PUMP CONFIG PROTOCOL:
//   1. Write high word to (addr | 0x4) - latches in config_high_reg
//   2. Write low word to (addr) - commits full 64-bit to PE config RAM
// ==============================================================================

module cgra_dma_engine #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 32,
    parameter FIFO_DEPTH = 8
)(
    input  logic clk,
    input  logic rst_n,
    
    // =========================================================================
    // CSR Configuration Interface
    // =========================================================================
    input  logic [31:0]           cfg_src,
    input  logic [31:0]           cfg_dst,
    input  logic [31:0]           cfg_size,
    input  logic                  cfg_start,
    input  logic                  cfg_abort,    // FIX: Abort/soft-reset to clear stuck busy
    output logic                  status_busy,
    output logic                  status_done,
    output logic                  irq_done,
    
    // =========================================================================
    // AXI4 Master Interface (Full AXI4 with Burst Support)
    // =========================================================================
    // Write Address Channel
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
    input  logic                  m_axi_bvalid,
    output logic                  m_axi_bready,
    // Read Address Channel
    output logic [ADDR_WIDTH-1:0] m_axi_araddr,
    output logic [7:0]            m_axi_arlen,     // Burst length (0 = 1 beat)
    output logic [2:0]            m_axi_arsize,    // Beat size (2 = 4 bytes)
    output logic [1:0]            m_axi_arburst,   // Burst type (1 = INCR)
    output logic                  m_axi_arvalid,
    input  logic                  m_axi_arready,
    // Read Data Channel
    input  logic [DATA_WIDTH-1:0] m_axi_rdata,
    input  logic                  m_axi_rlast,     // Last beat in burst
    input  logic                  m_axi_rvalid,
    output logic                  m_axi_rready,
    
    // =========================================================================
    // Local Memory Interface (To Tile Memory)
    // =========================================================================
    output logic [11:0]           tile_addr_o,
    output logic [1:0]            tile_bank_sel_o,
    output logic                  tile_we_o,
    output logic [31:0]           tile_wdata_o,
    
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
    // Use cfg_dst for destination type (base address determines routing)
    wire dst_is_axi    = (cfg_dst[31:28] == 4'h0);
    wire dst_is_tile   = (cfg_dst[31:28] == 4'h1);
    wire dst_is_config = (cfg_dst[31:28] == 4'h2);
    
    // Local write trigger (for tile/config - single cycle writes)
    logic local_write_en;
    logic local_fifo_pop;  // Explicit pop signal for local writes
    logic axi_fifo_pop;    // FIX: Explicit pop signal for AXI writes (set in W_WAIT)
    
    // FIFO pop conditions:
    // - AXI: pop in W_WAIT when latching data (same as local) - NOT in W_DATA!
    // - Local: pop via local_fifo_pop (set in W_WAIT when latching data)
    // FIX: Both AXI and Local pop at the same time (W_WAIT) to avoid race condition
    wire fifo_pop_axi   = (axi_fifo_pop && dst_is_axi && !fifo_empty);
    wire fifo_pop_local = (local_fifo_pop && !dst_is_axi && !fifo_empty);
    wire fifo_pop  = fifo_pop_axi || fifo_pop_local;
    wire fifo_push = (m_axi_rvalid && m_axi_rready && !fifo_full);
    
    // FIFO data output (registered read)
    logic [DATA_WIDTH-1:0] fifo_rdata;
    assign fifo_rdata = fifo_mem[r_ptr];
    
    // FIFO logic
    always_ff @(posedge clk) begin
        if (!rst_n) begin
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
                    fifo_mem[w_ptr] <= m_axi_rdata;
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
    typedef enum logic [1:0] {
        R_IDLE = 2'd0,
        R_ADDR = 2'd1,
        R_DATA = 2'd2,
        R_DONE = 2'd3
    } read_state_t;
    
    read_state_t r_state;
    logic [31:0] read_addr;
    logic [31:0] read_words_remaining;
    logic        read_complete;
    logic [7:0]  current_burst_len;  // Current burst length (ARLEN value, 0-indexed)
    
    // AXI4 Burst Configuration (constant for INCR bursts)
    assign m_axi_arsize  = 3'b010;  // 4 bytes per beat
    assign m_axi_arburst = 2'b01;   // INCR burst type
    
    // Chunked Burst Calculation with 4KB Boundary Protection
    // Max burst = FIFO_DEPTH words (default 8), so max ARLEN = 7
    localparam MAX_BURST_WORDS = FIFO_DEPTH;
    
    // AXI 4KB Boundary Protection - bursts cannot cross 4KB page boundaries
    // Calculate words remaining until next 4KB boundary
    wire [11:0] addr_offset = read_addr[11:0];  // Offset within 4KB page
    wire [31:0] words_to_boundary = (13'd4096 - {1'b0, addr_offset}) >> 2;  // Words until next 4KB boundary
    
    // Step 1: Clamp to remaining words or FIFO depth
    wire [31:0] len_limit_fifo = (read_words_remaining > MAX_BURST_WORDS) 
                                 ? MAX_BURST_WORDS 
                                 : read_words_remaining;
    
    // Step 2: Clamp to 4KB boundary - never cross page boundary
    wire [31:0] words_this_burst = (len_limit_fifo > words_to_boundary) 
                                   ? words_to_boundary 
                                   : len_limit_fifo;
    
    always_ff @(posedge clk) begin
        if (!rst_n || cfg_abort) begin  // Abort forces FSM to IDLE
            r_state <= R_IDLE;
            read_addr <= '0;
            read_words_remaining <= '0;
            read_complete <= 1'b0;
            current_burst_len <= '0;
            m_axi_araddr <= '0;
            m_axi_arlen <= '0;
            m_axi_arvalid <= 1'b0;
            m_axi_rready <= 1'b0;
        end else begin
            case (r_state)
                R_IDLE: begin
                    read_complete <= 1'b0;
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready <= 1'b0;
                    if (cfg_start && cfg_size != '0 && !status_busy) begin
                        read_addr <= cfg_src;
                        read_words_remaining <= (cfg_size + BYTES_PER_WORD - 1) / BYTES_PER_WORD;
                        r_state <= R_ADDR;
                    end
                end
                
                R_ADDR: begin
                    // Issue CHUNKED burst - max FIFO_DEPTH words per burst
                    // Only issue if FIFO has room for the burst (space >= words_this_burst)
                    // Available space = FIFO_DEPTH - count
                    // FIX: Only set arvalid if not already in handshake, and HOLD it until arready
                    if (!m_axi_arvalid) begin
                        // Not in handshake yet - check if we can start one
                        if ((FIFO_DEPTH - count) >= words_this_burst && read_words_remaining != '0) begin
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
                    // BURST MODE: Stay here receiving ALL beats until RLAST
                    m_axi_rready <= !fifo_full;  // Backpressure if FIFO full
                    
                    if (m_axi_rvalid && m_axi_rready) begin
                        // Data beat received - FIFO push happens via fifo_push wire
                        read_words_remaining <= read_words_remaining - 1'b1;
                        
                        // Check for RLAST (end of this burst chunk)
                        if (m_axi_rlast) begin
                            m_axi_rready <= 1'b0;
                            
                            // Update address for next chunk
                            // current_burst_len is ARLEN (N-1), so words = ARLEN+1
                            read_addr <= read_addr + ((current_burst_len + 1) * BYTES_PER_WORD);
                            
                            // Check if transfer complete
                            if (read_words_remaining == 32'd1) begin
                                // This was the last word of the last chunk
                                read_complete <= 1'b1;
                                r_state <= R_DONE;
                            end else begin
                                // More chunks to transfer - loop back to R_ADDR
                                r_state <= R_ADDR;
                            end
                        end
                        // Otherwise stay in R_DATA for next beat
                    end
                end
                
                R_DONE: begin
                    // Go directly to IDLE
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready <= 1'b0;
                    read_complete <= 1'b0;
                    r_state <= R_IDLE;
                end
                
                default: r_state <= R_IDLE;
            endcase
        end
    end
    
    // =========================================================================
    // 3. Write Engine (Consumer) - Drains FIFO to destination
    // =========================================================================
    typedef enum logic [2:0] {
        W_IDLE  = 3'd0,
        W_WAIT  = 3'd1,  // Wait for FIFO data
        W_ADDR  = 3'd2,  // AW phase
        W_DATA  = 3'd3,  // W phase
        W_RESP  = 3'd4,  // B phase
        W_DONE  = 3'd5
    } write_state_t;
    
    write_state_t w_state;
    logic [31:0] write_addr;
    logic [31:0] write_words_remaining;
    logic        write_complete;
    logic [DATA_WIDTH-1:0] write_data_reg;  // Latched FIFO data
    logic [31:0] local_write_addr;          // Address captured BEFORE increment for local writes
    
    // AXI4 Write Burst Configuration
    assign m_axi_awlen   = 8'h00;   // Single beat (no burst on writes yet)
    assign m_axi_awsize  = 3'b010;  // 4 bytes per beat
    assign m_axi_awburst = 2'b01;   // INCR burst type
    assign m_axi_wlast   = 1'b1;    // Always last beat (single-beat writes)
    // FIX: WSTRB must be continuously driven (was only set in reset!)
    assign m_axi_wstrb   = 4'hF;    // Always full word writes
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            w_state <= W_IDLE;
            write_addr <= '0;
            write_words_remaining <= '0;
            write_complete <= 1'b0;
            write_data_reg <= '0;
            local_write_en <= 1'b0;
            local_fifo_pop <= 1'b0;
            axi_fifo_pop <= 1'b0;    // FIX: Initialize new signal
            local_write_addr <= '0;
            m_axi_awaddr <= '0;
            m_axi_awvalid <= 1'b0;
            m_axi_wdata <= '0;
            m_axi_wstrb <= '1;
            m_axi_wvalid <= 1'b0;
            m_axi_bready <= 1'b0;
        end else if (cfg_abort) begin  // FIX: Abort forces write FSM to IDLE
            w_state <= W_IDLE;
            write_complete <= 1'b0;
            local_write_en <= 1'b0;
            local_fifo_pop <= 1'b0;
            axi_fifo_pop <= 1'b0;    // FIX: Clear on abort
            m_axi_awvalid <= 1'b0;
            m_axi_wvalid <= 1'b0;
            m_axi_bready <= 1'b0;
        end else begin
            case (w_state)
                W_IDLE: begin
                    write_complete <= 1'b0;
                    local_write_en <= 1'b0;
                    local_fifo_pop <= 1'b0;
                    axi_fifo_pop <= 1'b0;
                    m_axi_awvalid <= 1'b0;
                    m_axi_wvalid <= 1'b0;
                    m_axi_bready <= 1'b0;
                    if (cfg_start && cfg_size != '0 && !status_busy) begin
                        write_addr <= cfg_dst;
                        write_words_remaining <= (cfg_size + BYTES_PER_WORD - 1) / BYTES_PER_WORD;
                        w_state <= W_WAIT;
                    end
                end
                
                W_WAIT: begin
                    // Wait for FIFO to have data
                    local_write_en <= 1'b0;
                    local_fifo_pop <= 1'b0;
                    axi_fifo_pop <= 1'b0;
                    
                    if (!fifo_empty && write_words_remaining != '0) begin
                        // Latch data from FIFO
                        write_data_reg <= fifo_rdata;
                        
                        // Pop FIFO NOW for ALL destinations
                        if (dst_is_axi) begin
                            axi_fifo_pop <= 1'b1;
                        end else begin
                            local_fifo_pop <= 1'b1;
                        end
                        
                        w_state <= W_ADDR;
                    end else if (write_words_remaining == '0) begin
                        write_complete <= 1'b1;
                        w_state <= W_DONE;
                    end
                end
                
                W_ADDR: begin
                    // Clear pop signals from W_WAIT
                    axi_fifo_pop <= 1'b0;
                    local_fifo_pop <= 1'b0;
                    
                    if (dst_is_axi) begin
                        // AW phase - address for AXI
                        if (!m_axi_awvalid) begin
                            // First cycle - assert valid
                            m_axi_awaddr <= write_addr;
                            m_axi_awvalid <= 1'b1;
                        end else if (m_axi_awready) begin
                            // Handshake complete
                            m_axi_awvalid <= 1'b0;
                            w_state <= W_DATA;
                        end
                    end else begin
                        // Local destination (tile/config) - single-cycle write
                        local_write_addr <= write_addr;
                        local_write_en <= 1'b1;
                        write_addr <= write_addr + BYTES_PER_WORD;
                        write_words_remaining <= write_words_remaining - 1'b1;
                        
                        if (write_words_remaining == 32'd1) begin
                            write_complete <= 1'b1;
                            w_state <= W_DONE;
                        end else begin
                            w_state <= W_WAIT;
                        end
                    end
                end
                
                W_DATA: begin
                    // W phase - data
                    if (!m_axi_wvalid) begin
                        // First cycle - assert valid with data
                        m_axi_wdata <= write_data_reg;
                        m_axi_wvalid <= 1'b1;
                    end else if (m_axi_wready) begin
                        // Handshake complete
                        m_axi_wvalid <= 1'b0;
                        m_axi_bready <= 1'b1;
                        w_state <= W_RESP;
                    end
                end
                
                W_RESP: begin
                    // B phase - wait for response
                    if (m_axi_bvalid) begin
                        m_axi_bready <= 1'b0;
                        write_addr <= write_addr + BYTES_PER_WORD;
                        write_words_remaining <= write_words_remaining - 1'b1;
                        
                        if (write_words_remaining == 32'd1) begin
                            write_complete <= 1'b1;
                            w_state <= W_DONE;
                        end else begin
                            w_state <= W_WAIT;
                        end
                    end
                end
                
                W_DONE: begin
                    m_axi_awvalid <= 1'b0;
                    m_axi_wvalid <= 1'b0;
                    m_axi_bready <= 1'b0;
                    local_write_en <= 1'b0;
                    write_complete <= 1'b0;
                    w_state <= W_IDLE;
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
    assign tile_addr_o     = local_write_addr[11:0];   // 4KB wrapping per bank
    assign tile_bank_sel_o = local_write_addr[13:12];  // Bank select from addr bits
    assign tile_wdata_o    = write_data_reg;
    assign tile_we_o       = local_write_en && dst_is_tile;
    
    assign config_addr_o   = local_write_addr;
    assign config_wdata_o  = write_data_reg;
    assign config_we_o     = local_write_en && dst_is_config;
    
    // =========================================================================
    // 4. Status and IRQ Generation
    // =========================================================================
    logic transfer_active;
    logic transfer_started;  // FIX: One-cycle delay to let FSMs leave IDLE
    
    // Robust busy check: stays HIGH until ALL components are idle
    // This prevents producer-consumer mismatch where Write FSM finishes early
    wire engine_idle = (r_state == R_IDLE) && (w_state == W_IDLE) && fifo_empty;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            transfer_active <= 1'b0;
            transfer_started <= 1'b0;
            status_busy <= 1'b0;
            status_done <= 1'b0;
            irq_done <= 1'b0;
        end else if (cfg_abort) begin  // Abort clears busy immediately
            transfer_active <= 1'b0;
            transfer_started <= 1'b0;
            status_busy <= 1'b0;
            status_done <= 1'b0;  // Don't signal done on abort
            irq_done <= 1'b0;
        end else begin
            // Default: clear done pulse
            status_done <= 1'b0;
            irq_done <= 1'b0;
            
            if (cfg_start && cfg_size != '0 && !status_busy) begin
                // Start new transfer
                transfer_active <= 1'b1;
                transfer_started <= 1'b0;  // Will be set next cycle
                status_busy <= 1'b1;
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
    
    // Deadlock detection counter
    integer busy_cycle_count;
    
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
                r_state != R_DATA && r_state != R_DONE) begin
                $error("[DMA ASSERT] Read FSM in invalid state: %0d", r_state);
            end
            
            // Check 5: Write FSM State Valid
            if (w_state != W_IDLE && w_state != W_WAIT && w_state != W_ADDR && 
                w_state != W_DATA && w_state != W_RESP && w_state != W_DONE) begin
                $error("[DMA ASSERT] Write FSM in invalid state: %0d", w_state);
            end
            // Debug displays removed for synthesis - uncomment for debugging:
            // if (m_axi_rvalid && m_axi_rready) begin
            //     $display("[DMA_RD] Data=%h | RLAST=%b | Count=%0d", m_axi_rdata, m_axi_rlast, count);
            // end
            // if (fifo_pop) begin
            //     $display("[DMA_WR] PopData=%h | w_state=%0d | WrWordsLeft=%0d", fifo_rdata, w_state, write_words_remaining);
            // end
        end
    end
    
    // synthesis translate_on

    // =========================================================================
    // Debug Signal Assignments (For ILA probing)
    // =========================================================================
    assign dbg_status_busy           = status_busy;
    assign dbg_read_fsm_state        = {1'b0, r_state};  // Pad 2-bit to 3-bit
    assign dbg_write_fsm_state       = w_state;
    assign dbg_fifo_full             = fifo_full;
    assign dbg_fifo_empty            = fifo_empty;
    assign dbg_write_words_remaining = write_words_remaining;

endmodule
