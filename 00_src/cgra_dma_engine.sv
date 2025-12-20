// ==============================================================================
// CGRA DMA Engine - AXI4-Lite Master (Simplified Pipelined)
// ==============================================================================
// Simpler implementation: Sequential read-then-write with small FIFO buffer
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
    
    // =========================================================================
    // Main FSM
    // =========================================================================
    typedef enum logic [2:0] {
        IDLE      = 3'd0,
        READ_ADDR = 3'd1,
        READ_DATA = 3'd2,
        WRITE_AW  = 3'd3,
        WRITE_W   = 3'd4,
        WRITE_B   = 3'd5,
        DONE      = 3'd6
    } state_t;
    
    state_t state;
    
    // Transfer registers
    logic [31:0] src_addr;
    logic [31:0] dst_addr;
    logic [31:0] bytes_remaining;
    logic [31:0] read_data_reg;
    
    // =========================================================================
    // FSM Logic
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            state <= IDLE;
            src_addr <= 32'd0;
            dst_addr <= 32'd0;
            bytes_remaining <= 32'd0;
            read_data_reg <= 32'd0;
            
            m_axi_araddr <= 32'd0;
            m_axi_arvalid <= 1'b0;
            m_axi_rready <= 1'b0;
            m_axi_awaddr <= 32'd0;
            m_axi_awvalid <= 1'b0;
            m_axi_wdata <= 32'd0;
            m_axi_wstrb <= 4'hF;
            m_axi_wvalid <= 1'b0;
            m_axi_bready <= 1'b0;
            
            status_busy <= 1'b0;
            status_done <= 1'b0;
            irq_done <= 1'b0;
        end else begin
            // Default: clear done pulse
            status_done <= 1'b0;
            irq_done <= 1'b0;
            
            case (state)
                IDLE: begin
                    status_busy <= 1'b0;
                    if (cfg_start && cfg_size > 0) begin
                        src_addr <= cfg_src;
                        dst_addr <= cfg_dst;
                        bytes_remaining <= cfg_size;
                        status_busy <= 1'b1;
                        state <= READ_ADDR;
                    end
                end
                
                READ_ADDR: begin
                    m_axi_araddr <= src_addr;
                    m_axi_arvalid <= 1'b1;
                    if (m_axi_arvalid && m_axi_arready) begin
                        m_axi_arvalid <= 1'b0;
                        m_axi_rready <= 1'b1;
                        state <= READ_DATA;
                    end
                end
                
                READ_DATA: begin
                    if (m_axi_rvalid && m_axi_rready) begin
                        read_data_reg <= m_axi_rdata;
                        m_axi_rready <= 1'b0;
                        state <= WRITE_AW;
                    end
                end
                
                WRITE_AW: begin
                    m_axi_awaddr <= dst_addr;
                    m_axi_awvalid <= 1'b1;
                    m_axi_wdata <= read_data_reg;
                    m_axi_wvalid <= 1'b1;
                    if (m_axi_awvalid && m_axi_awready) begin
                        m_axi_awvalid <= 1'b0;
                        state <= WRITE_W;
                    end
                end
                
                WRITE_W: begin
                    if (m_axi_wvalid && m_axi_wready) begin
                        m_axi_wvalid <= 1'b0;
                        m_axi_bready <= 1'b1;
                        state <= WRITE_B;
                    end
                end
                
                WRITE_B: begin
                    if (m_axi_bvalid && m_axi_bready) begin
                        m_axi_bready <= 1'b0;
                        src_addr <= src_addr + BYTES_PER_WORD;
                        dst_addr <= dst_addr + BYTES_PER_WORD;
                        
                        if (bytes_remaining <= BYTES_PER_WORD) begin
                            bytes_remaining <= 32'd0;
                            state <= DONE;
                        end else begin
                            bytes_remaining <= bytes_remaining - BYTES_PER_WORD;
                            state <= READ_ADDR;
                        end
                    end
                end
                
                DONE: begin
                    status_done <= 1'b1;
                    irq_done <= 1'b1;
                    status_busy <= 1'b0;
                    state <= IDLE;
                end
                
                default: state <= IDLE;
            endcase
        end
    end

endmodule
