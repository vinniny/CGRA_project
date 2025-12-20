// ==============================================================================
// CGRA DMA Engine - Pipelined Producer-Consumer Architecture (Robust)
// ==============================================================================
// Features:
// - Decoupled Read (Producer) and Write (Consumer) engines
// - 8-word FIFO buffer for pipeline decoupling
// - Robust state machines with proper handshake handling
// - Flow control via FIFO full/empty signals
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
    output logic                  status_busy,
    output logic                  status_done,
    output logic                  irq_done,
    
    // =========================================================================
    // AXI4-Lite Master Interface
    // =========================================================================
    output logic [ADDR_WIDTH-1:0] m_axi_awaddr,
    output logic                  m_axi_awvalid,
    input  logic                  m_axi_awready,
    output logic [DATA_WIDTH-1:0] m_axi_wdata,
    output logic [DATA_WIDTH/8-1:0] m_axi_wstrb,
    output logic                  m_axi_wvalid,
    input  logic                  m_axi_wready,
    input  logic                  m_axi_bvalid,
    output logic                  m_axi_bready,
    output logic [ADDR_WIDTH-1:0] m_axi_araddr,
    output logic                  m_axi_arvalid,
    input  logic                  m_axi_arready,
    input  logic [DATA_WIDTH-1:0] m_axi_rdata,
    input  logic                  m_axi_rvalid,
    output logic                  m_axi_rready
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
    wire fifo_empty = (count == 0);
    wire fifo_push  = (m_axi_rvalid && m_axi_rready && !fifo_full);
    wire fifo_pop   = (m_axi_wvalid && m_axi_wready && !fifo_empty);
    
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
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            r_state <= R_IDLE;
            read_addr <= '0;
            read_words_remaining <= '0;
            read_complete <= 1'b0;
            m_axi_araddr <= '0;
            m_axi_arvalid <= 1'b0;
            m_axi_rready <= 1'b0;
        end else begin
            case (r_state)
                R_IDLE: begin
                    read_complete <= 1'b0;
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready <= 1'b0;
                    if (cfg_start && cfg_size > 0 && !status_busy) begin
                        read_addr <= cfg_src;
                        read_words_remaining <= (cfg_size + BYTES_PER_WORD - 1) / BYTES_PER_WORD;
                        r_state <= R_ADDR;
                    end
                end
                
                R_ADDR: begin
                    // Only issue read if FIFO has space
                    if (!fifo_full && read_words_remaining > 0) begin
                        m_axi_araddr <= read_addr;
                        m_axi_arvalid <= 1'b1;
                    end else begin
                        m_axi_arvalid <= 1'b0;
                    end
                    
                    if (m_axi_arvalid && m_axi_arready) begin
                        m_axi_arvalid <= 1'b0;
                        m_axi_rready <= 1'b1;
                        r_state <= R_DATA;
                    end
                end
                
                R_DATA: begin
                    // Wait for read data
                    if (m_axi_rvalid && m_axi_rready) begin
                        m_axi_rready <= 1'b0;
                        read_addr <= read_addr + BYTES_PER_WORD;
                        read_words_remaining <= read_words_remaining - 1'b1;
                        
                        if (read_words_remaining == 1) begin
                            read_complete <= 1'b1;
                            r_state <= R_DONE;
                        end else begin
                            r_state <= R_ADDR;
                        end
                    end
                end
                
                R_DONE: begin
                    // Stay here until transfer is fully complete
                    m_axi_arvalid <= 1'b0;
                    m_axi_rready <= 1'b0;
                    if (!status_busy) begin
                        read_complete <= 1'b0;
                        r_state <= R_IDLE;
                    end
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
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            w_state <= W_IDLE;
            write_addr <= '0;
            write_words_remaining <= '0;
            write_complete <= 1'b0;
            write_data_reg <= '0;
            m_axi_awaddr <= '0;
            m_axi_awvalid <= 1'b0;
            m_axi_wdata <= '0;
            m_axi_wstrb <= '1;
            m_axi_wvalid <= 1'b0;
            m_axi_bready <= 1'b0;
        end else begin
            case (w_state)
                W_IDLE: begin
                    write_complete <= 1'b0;
                    m_axi_awvalid <= 1'b0;
                    m_axi_wvalid <= 1'b0;
                    m_axi_bready <= 1'b0;
                    if (cfg_start && cfg_size > 0 && !status_busy) begin
                        write_addr <= cfg_dst;
                        write_words_remaining <= (cfg_size + BYTES_PER_WORD - 1) / BYTES_PER_WORD;
                        w_state <= W_WAIT;
                    end
                end
                
                W_WAIT: begin
                    // Wait for FIFO to have data
                    if (!fifo_empty && write_words_remaining > 0) begin
                        // Latch data from FIFO
                        write_data_reg <= fifo_rdata;
                        w_state <= W_ADDR;
                    end else if (write_words_remaining == 0 && read_complete) begin
                        write_complete <= 1'b1;
                        w_state <= W_DONE;
                    end
                end
                
                W_ADDR: begin
                    // AW phase - address
                    m_axi_awaddr <= write_addr;
                    m_axi_awvalid <= 1'b1;
                    
                    if (m_axi_awvalid && m_axi_awready) begin
                        m_axi_awvalid <= 1'b0;
                        w_state <= W_DATA;
                    end
                end
                
                W_DATA: begin
                    // W phase - data (FIFO popped when wready)
                    m_axi_wdata <= write_data_reg;
                    m_axi_wvalid <= 1'b1;
                    
                    if (m_axi_wvalid && m_axi_wready) begin
                        m_axi_wvalid <= 1'b0;
                        m_axi_bready <= 1'b1;
                        w_state <= W_RESP;
                    end
                end
                
                W_RESP: begin
                    // B phase - wait for response
                    if (m_axi_bvalid && m_axi_bready) begin
                        m_axi_bready <= 1'b0;
                        write_addr <= write_addr + BYTES_PER_WORD;
                        write_words_remaining <= write_words_remaining - 1'b1;
                        
                        if (write_words_remaining == 1) begin
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
                    if (!status_busy) begin
                        write_complete <= 1'b0;
                        w_state <= W_IDLE;
                    end
                end
                
                default: w_state <= W_IDLE;
            endcase
        end
    end
    
    // =========================================================================
    // 4. Status and IRQ Generation
    // =========================================================================
    logic transfer_active;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            transfer_active <= 1'b0;
            status_busy <= 1'b0;
            status_done <= 1'b0;
            irq_done <= 1'b0;
        end else begin
            // Default: clear done pulse
            status_done <= 1'b0;
            irq_done <= 1'b0;
            
            if (cfg_start && cfg_size > 0 && !status_busy) begin
                transfer_active <= 1'b1;
                status_busy <= 1'b1;
            end else if (transfer_active && write_complete) begin
                transfer_active <= 1'b0;
                status_busy <= 1'b0;
                status_done <= 1'b1;
                irq_done <= 1'b1;
            end
        end
    end

endmodule
