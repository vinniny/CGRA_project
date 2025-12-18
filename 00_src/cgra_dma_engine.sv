// ==============================================================================
// CGRA DMA Engine - AXI4 Master for High-Throughput Data Transfer
// ==============================================================================
// Provides high-bandwidth data movement between external DDR3 memory and CGRA
// Features:
// - AXI4 master interface for burst transfers
// - Descriptor-based job queue
// - Read/write channels with independent operation
// - Doorbell trigger mechanism from CSR

module cgra_dma_engine #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 32,
    parameter MAX_BURST_LEN = 16,
    parameter ID_WIDTH = 4
)(
    input  logic clk,
    input  logic rst_n,
    
    // Control interface from CSR
    input  logic                  dma_start,
    input  logic [ADDR_WIDTH-1:0] job_desc_addr,
    output logic                  dma_busy,
    output logic                  dma_done,
    output logic                  dma_error,
    output logic [31:0]           dma_head_ptr,
    
    // AXI4 Master Write Address Channel
    output logic [ID_WIDTH-1:0]   m_axi_awid,
    output logic [ADDR_WIDTH-1:0] m_axi_awaddr,
    output logic [7:0]            m_axi_awlen,
    output logic [2:0]            m_axi_awsize,
    output logic [1:0]            m_axi_awburst,
    output logic                  m_axi_awlock,
    output logic [3:0]            m_axi_awcache,
    output logic [2:0]            m_axi_awprot,
    output logic                  m_axi_awvalid,
    input  logic                  m_axi_awready,
    
    // AXI4 Master Write Data Channel
    output logic [DATA_WIDTH-1:0] m_axi_wdata,
    output logic [DATA_WIDTH/8-1:0] m_axi_wstrb,
    output logic                  m_axi_wlast,
    output logic                  m_axi_wvalid,
    input  logic                  m_axi_wready,
    
    // AXI4 Master Write Response Channel
    input  logic [ID_WIDTH-1:0]   m_axi_bid,
    input  logic [1:0]            m_axi_bresp,
    input  logic                  m_axi_bvalid,
    output logic                  m_axi_bready,
    
    // AXI4 Master Read Address Channel
    output logic [ID_WIDTH-1:0]   m_axi_arid,
    output logic [ADDR_WIDTH-1:0] m_axi_araddr,
    output logic [7:0]            m_axi_arlen,
    output logic [2:0]            m_axi_arsize,
    output logic [1:0]            m_axi_arburst,
    output logic                  m_axi_arlock,
    output logic [3:0]            m_axi_arcache,
    output logic [2:0]            m_axi_arprot,
    output logic                  m_axi_arvalid,
    input  logic                  m_axi_arready,
    
    // AXI4 Master Read Data Channel
    input  logic [ID_WIDTH-1:0]   m_axi_rid,
    input  logic [DATA_WIDTH-1:0] m_axi_rdata,
    input  logic [1:0]            m_axi_rresp,
    input  logic                  m_axi_rlast,
    input  logic                  m_axi_rvalid,
    output logic                  m_axi_rready,
    
    // Local memory interface (to Tile Memory or Config Memory)
    output logic [ADDR_WIDTH-1:0] local_mem_addr,
    output logic                  local_mem_write,
    output logic [DATA_WIDTH-1:0] local_mem_wdata,
    output logic                  local_mem_read,
    input  logic [DATA_WIDTH-1:0] local_mem_rdata,
    input  logic                  local_mem_valid
);

    // =========================================================================
    // Job Descriptor Format (128 bits / 4 words)
    // =========================================================================
    // Word 0: src_addr[31:0]
    // Word 1: dst_addr[31:0]
    // Word 2: length[31:0] (in bytes)
    // Word 3: control[31:0] (bit 0: direction 0=DDR->Local, 1=Local->DDR)
    
    logic [ADDR_WIDTH-1:0] desc_src_addr;
    logic [ADDR_WIDTH-1:0] desc_dst_addr;
    logic [31:0]           desc_length;
    logic                  desc_dir;  // 0=read from DDR, 1=write to DDR
    
    // =========================================================================
    // DMA FSM States
    // =========================================================================
    typedef enum logic [2:0] {
        STATE_IDLE        = 3'd0,
        STATE_FETCH_DESC  = 3'd1,
        STATE_READ_SETUP  = 3'd2,
        STATE_READ_DATA   = 3'd3,
        STATE_WRITE_SETUP = 3'd4,
        STATE_WRITE_DATA  = 3'd5,
        STATE_WAIT_RESP   = 3'd6,
        STATE_DONE        = 3'd7
    } dma_state_t;
    dma_state_t state, state_next;
    
    // =========================================================================
    // Transfer counters
    // =========================================================================
    logic [31:0] bytes_remaining;
    logic [31:0] current_src_addr;
    logic [31:0] current_dst_addr;
    logic [7:0]  burst_count;
    logic [7:0]  beat_count;
    
    // =========================================================================
    // Descriptor fetch FSM
    // =========================================================================
    typedef enum logic [1:0] {
        DESC_IDLE = 2'd0,
        DESC_READ = 2'd1,
        DESC_WAIT = 2'd2,
        DESC_DONE = 2'd3
    } desc_state_t;
    desc_state_t desc_fetch_state;
    logic [31:0] desc_buffer[0:3];
    logic [1:0] desc_word_idx;
    
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
                if (dma_start) begin
                    state_next = STATE_FETCH_DESC;
                end
            end
            
            STATE_FETCH_DESC: begin
                if (desc_fetch_state == DESC_DONE) begin
                    if (desc_dir == 1'b0) begin
                        state_next = STATE_READ_SETUP;
                    end else begin
                        state_next = STATE_WRITE_SETUP;
                    end
                end
            end
            
            STATE_READ_SETUP: begin
                if (m_axi_arvalid && m_axi_arready) begin
                    state_next = STATE_READ_DATA;
                end
            end
            
            STATE_READ_DATA: begin
                if (m_axi_rvalid && m_axi_rready && m_axi_rlast) begin
                    if (bytes_remaining == 32'd0) begin
                        state_next = STATE_DONE;
                    end else begin
                        state_next = STATE_READ_SETUP;
                    end
                end
            end
            
            STATE_WRITE_SETUP: begin
                if (m_axi_awvalid && m_axi_awready) begin
                    state_next = STATE_WRITE_DATA;
                end
            end
            
            STATE_WRITE_DATA: begin
                if (m_axi_wvalid && m_axi_wready && m_axi_wlast) begin
                    state_next = STATE_WAIT_RESP;
                end
            end
            
            STATE_WAIT_RESP: begin
                if (m_axi_bvalid && m_axi_bready) begin
                    if (bytes_remaining == 32'd0) begin
                        state_next = STATE_DONE;
                    end else begin
                        state_next = STATE_WRITE_SETUP;
                    end
                end
            end
            
            STATE_DONE: begin
                state_next = STATE_IDLE;
            end
            
            default: state_next = STATE_IDLE;
        endcase
    end
    
    // =========================================================================
    // Descriptor Fetch Logic
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            desc_fetch_state <= DESC_IDLE;
            desc_word_idx <= 2'd0;
            desc_src_addr <= 32'd0;
            desc_dst_addr <= 32'd0;
            desc_length <= 32'd0;
            desc_dir <= 1'b0;
        end else begin
            unique case (desc_fetch_state)
                DESC_IDLE: begin
                    if (state == STATE_FETCH_DESC) begin
                        desc_fetch_state <= DESC_READ;
                        desc_word_idx <= 2'd0;
                    end
                end
                
                DESC_READ: begin
                    if (m_axi_arvalid && m_axi_arready) begin
                        desc_fetch_state <= DESC_WAIT;
                    end
                end
                
                DESC_WAIT: begin
                    if (m_axi_rvalid && m_axi_rready) begin
                        desc_buffer[desc_word_idx] <= m_axi_rdata;
                        if (desc_word_idx == 2'd3) begin
                            desc_fetch_state <= DESC_DONE;
                            desc_src_addr <= desc_buffer[0];
                            desc_dst_addr <= desc_buffer[1];
                            desc_length <= desc_buffer[2];
                            desc_dir <= desc_buffer[3][0];
                        end else begin
                            desc_word_idx <= desc_word_idx + 2'd1;
                            desc_fetch_state <= DESC_READ;
                        end
                    end
                end
                
                DESC_DONE: begin
                    if (state != STATE_FETCH_DESC) begin
                        desc_fetch_state <= DESC_IDLE;
                    end
                end
                
                default: begin
                    desc_fetch_state <= DESC_IDLE;
                end
            endcase
        end
    end
    
    // =========================================================================
    // Transfer Counter Management
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            bytes_remaining <= 32'd0;
            current_src_addr <= 32'd0;
            current_dst_addr <= 32'd0;
            burst_count <= 8'd0;
            beat_count <= 8'd0;
        end else begin
            if (state == STATE_FETCH_DESC && desc_fetch_state == DESC_DONE) begin
                bytes_remaining <= desc_length;
                current_src_addr <= desc_src_addr;
                current_dst_addr <= desc_dst_addr;
            end else if (state == STATE_READ_SETUP || state == STATE_WRITE_SETUP) begin
                // Compute burst_count with underflow guard
                if (bytes_remaining >= (MAX_BURST_LEN * (DATA_WIDTH/8))) begin
                    burst_count <= MAX_BURST_LEN - 1;
                end else if (bytes_remaining >= (DATA_WIDTH/8)) begin
                    burst_count <= (bytes_remaining / (DATA_WIDTH/8)) - 1;
                end else begin
                    burst_count <= 8'd0;  // Single beat for small transfers
                end
                beat_count <= 8'd0;
            end else if ((state == STATE_READ_DATA && m_axi_rvalid && m_axi_rready) ||
                         (state == STATE_WRITE_DATA && m_axi_wvalid && m_axi_wready)) begin
                beat_count <= beat_count + 8'd1;
                if (beat_count == burst_count) begin
                    bytes_remaining <= bytes_remaining - ((burst_count + 1) * (DATA_WIDTH/8));
                    current_src_addr <= current_src_addr + ((burst_count + 1) * (DATA_WIDTH/8));
                    current_dst_addr <= current_dst_addr + ((burst_count + 1) * (DATA_WIDTH/8));
                end
            end
        end
    end
    
    // =========================================================================
    // AXI4 Read Address Channel
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            m_axi_arid <= 4'd0;
            m_axi_araddr <= 32'd0;
            m_axi_arlen <= 8'd0;
            m_axi_arsize <= 3'b010;  // 4 bytes
            m_axi_arburst <= 2'b01;  // INCR
            m_axi_arlock <= 1'b0;
            m_axi_arcache <= 4'b0011;
            m_axi_arprot <= 3'b000;
            m_axi_arvalid <= 1'b0;
        end else begin
            if (state == STATE_FETCH_DESC && desc_fetch_state == DESC_READ) begin
                m_axi_araddr <= job_desc_addr + (desc_word_idx << 2);
                m_axi_arlen <= 8'd0;  // Single beat for descriptor
                m_axi_arvalid <= 1'b1;
            end else if (state == STATE_READ_SETUP && !m_axi_arvalid) begin
                m_axi_araddr <= current_src_addr;
                // Compute burst length directly to avoid timing issue with burst_count
                // Guard against underflow when bytes_remaining is 0
                if (bytes_remaining >= (MAX_BURST_LEN * (DATA_WIDTH/8))) begin
                    m_axi_arlen <= MAX_BURST_LEN - 1;
                end else if (bytes_remaining >= (DATA_WIDTH/8)) begin
                    m_axi_arlen <= (bytes_remaining / (DATA_WIDTH/8)) - 1;
                end else begin
                    m_axi_arlen <= 8'd0;  // Single beat for small transfers
                end
                m_axi_arvalid <= 1'b1;
            end else if (m_axi_arvalid && m_axi_arready) begin
                m_axi_arvalid <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // AXI4 Read Data Channel
    // =========================================================================
    always_comb begin
        m_axi_rready = (state == STATE_READ_DATA) || (desc_fetch_state == DESC_WAIT);
    end
    
    // =========================================================================
    // AXI4 Write Address Channel
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            m_axi_awid <= 4'd0;
            m_axi_awaddr <= 32'd0;
            m_axi_awlen <= 8'd0;
            m_axi_awsize <= 3'b010;
            m_axi_awburst <= 2'b01;
            m_axi_awlock <= 1'b0;
            m_axi_awcache <= 4'b0011;
            m_axi_awprot <= 3'b000;
            m_axi_awvalid <= 1'b0;
        end else begin
            if (state == STATE_WRITE_SETUP && !m_axi_awvalid) begin
                m_axi_awaddr <= current_dst_addr;
                m_axi_awlen <= burst_count;
                m_axi_awvalid <= 1'b1;
            end else if (m_axi_awvalid && m_axi_awready) begin
                m_axi_awvalid <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // AXI4 Write Data Channel
    // =========================================================================
    logic [ADDR_WIDTH-1:0] local_read_addr;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            m_axi_wdata <= 32'd0;
            m_axi_wstrb <= 4'hF;
            m_axi_wlast <= 1'b0;
            m_axi_wvalid <= 1'b0;
            local_read_addr <= 32'd0;
        end else begin
            if (state == STATE_WRITE_SETUP) begin
                local_read_addr <= desc_src_addr;
            end else if (state == STATE_WRITE_DATA && local_mem_valid) begin
                m_axi_wdata <= local_mem_rdata;
                m_axi_wlast <= (beat_count == burst_count);
                m_axi_wvalid <= 1'b1;
            end else if (m_axi_wvalid && m_axi_wready) begin
                m_axi_wvalid <= 1'b0;
                local_read_addr <= local_read_addr + (DATA_WIDTH/8);
            end
        end
    end
    
    // =========================================================================
    // AXI4 Write Response Channel
    // =========================================================================
    always_comb begin
        m_axi_bready = (state == STATE_WAIT_RESP);
    end
    
    // =========================================================================
    // Local Memory Interface
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            local_mem_addr <= 32'd0;
            local_mem_write <= 1'b0;
            local_mem_wdata <= 32'd0;
            local_mem_read <= 1'b0;
        end else begin
            // Write path: DDR -> Local
            if (state == STATE_READ_DATA && m_axi_rvalid && m_axi_rready) begin
                local_mem_addr <= current_dst_addr + (beat_count * (DATA_WIDTH/8));
                local_mem_wdata <= m_axi_rdata;
                local_mem_write <= 1'b1;
            end else begin
                local_mem_write <= 1'b0;
            end
            
            // Read path: Local -> DDR
            if (state == STATE_WRITE_DATA && !m_axi_wvalid) begin
                local_mem_addr <= local_read_addr;
                local_mem_read <= 1'b1;
            end else begin
                local_mem_read <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // Status Outputs
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            dma_busy <= 1'b0;
            dma_done <= 1'b0;
            dma_error <= 1'b0;
            dma_head_ptr <= 32'd0;
        end else begin
            dma_busy <= (state != STATE_IDLE);
            dma_done <= (state == STATE_DONE);
            
            // Error detection
            if ((m_axi_rvalid && m_axi_rresp != 2'b00) ||
                (m_axi_bvalid && m_axi_bresp != 2'b00)) begin
                dma_error <= 1'b1;
            end else if (state == STATE_IDLE) begin
                dma_error <= 1'b0;
            end
            
            // Head pointer updates after successful transfer
            if (state == STATE_DONE) begin
                dma_head_ptr <= dma_head_ptr + 32'd16;  // 4 words = 16 bytes
            end
        end
    end

endmodule
