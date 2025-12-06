// ==============================================================================
// CGRA AXI4-Lite CSR (Control and Status Register) Interface
// ==============================================================================
// Implements control and status registers per specification
// Register Map (32-bit aligned):
//   0x00 - CTRL: start, reset, cfg_start
//   0x04 - STATUS: busy, done, error, cfg_done
//   0x08 - BITSTR_ADDR: bitstream base address
//   0x0C - BITSTR_SIZE: bitstream size
//   0x10 - DMA_DOORBELL: DMA start (write-only)
//   0x14 - DMA_HEAD: head pointer
//   0x18 - JOB_DESC_ADDR: descriptor address
//   0x1C - PERF0: cycles counter
//   0x20 - PERF1: stalls/memory ops counter
//   0x24 - IRQ_MASK: interrupt enable mask

module cgra_axi_csr #(
    parameter ADDR_WIDTH = 32,
    parameter DATA_WIDTH = 32
)(
    input  logic clk,
    input  logic rst_n,
    
    // AXI4-Lite interface
    input  logic [ADDR_WIDTH-1:0] s_axi_awaddr,
    input  logic                  s_axi_awvalid,
    output logic                  s_axi_awready,
    
    input  logic [DATA_WIDTH-1:0] s_axi_wdata,
    input  logic [3:0]            s_axi_wstrb,
    input  logic                  s_axi_wvalid,
    output logic                  s_axi_wready,
    
    output logic [1:0]            s_axi_bresp,
    output logic                  s_axi_bvalid,
    input  logic                  s_axi_bready,
    
    input  logic [ADDR_WIDTH-1:0] s_axi_araddr,
    input  logic                  s_axi_arvalid,
    output logic                  s_axi_arready,
    
    output logic [DATA_WIDTH-1:0] s_axi_rdata,
    output logic [1:0]            s_axi_rresp,
    output logic                  s_axi_rvalid,
    input  logic                  s_axi_rready,
    
    // Control outputs
    output logic                  cgra_start,
    output logic                  cgra_reset,
    output logic                  cfg_start,
    output logic [ADDR_WIDTH-1:0] bitstream_addr,
    output logic [15:0]           bitstream_size,
    output logic                  dma_start,
    output logic [ADDR_WIDTH-1:0] job_desc_addr,
    output logic [31:0]           irq_mask,
    
    // Status inputs
    input  logic                  cgra_busy,
    input  logic                  cgra_done,
    input  logic                  cgra_error,
    input  logic                  cfg_done,
    input  logic [31:0]           dma_head,
    input  logic [31:0]           perf_cycles,
    input  logic [31:0]           perf_stalls
);

    // =========================================================================
    // Register addresses
    // =========================================================================
    localparam ADDR_CTRL         = 8'h00;
    localparam ADDR_STATUS       = 8'h04;
    localparam ADDR_BITSTR_ADDR  = 8'h08;
    localparam ADDR_BITSTR_SIZE  = 8'h0C;
    localparam ADDR_DMA_DOORBELL = 8'h10;
    localparam ADDR_DMA_HEAD     = 8'h14;
    localparam ADDR_JOB_DESC     = 8'h18;
    localparam ADDR_PERF0        = 8'h1C;
    localparam ADDR_PERF1        = 8'h20;
    localparam ADDR_IRQ_MASK     = 8'h24;
    
    // =========================================================================
    // Internal registers
    // =========================================================================
    logic [31:0] ctrl_reg;
    logic [31:0] status_reg;
    logic [31:0] bitstr_addr_reg;
    logic [31:0] bitstr_size_reg;
    logic [31:0] job_desc_reg;
    logic [31:0] irq_mask_reg;
    
    // =========================================================================
    // AXI4-Lite Write FSM
    // =========================================================================
    typedef enum logic [1:0] {
        W_IDLE  = 2'd0,
        W_ADDR  = 2'd1,
        W_DATA  = 2'd2,
        W_RESP  = 2'd3
    } write_state_t;
    
    write_state_t w_state, w_next_state;
    logic [ADDR_WIDTH-1:0] w_addr_reg;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            w_state <= W_IDLE;
        end else begin
            w_state <= w_next_state;
        end
    end
    
    always_comb begin
        w_next_state = w_state;
        
        case (w_state)
            W_IDLE: begin
                if (s_axi_awvalid) begin
                    w_next_state = W_DATA;
                end
            end
            
            W_DATA: begin
                if (s_axi_wvalid) begin
                    w_next_state = W_RESP;
                end
            end
            
            W_RESP: begin
                if (s_axi_bready) begin
                    w_next_state = W_IDLE;
                end
            end
            
            default: w_next_state = W_IDLE;
        endcase
    end
    
    // Write address channel
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            w_addr_reg <= '0;
            s_axi_awready <= 1'b0;
        end else begin
            if (w_state == W_IDLE && s_axi_awvalid) begin
                w_addr_reg <= s_axi_awaddr;
                s_axi_awready <= 1'b1;
            end else begin
                s_axi_awready <= 1'b0;
            end
        end
    end
    
    // Write data channel
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            s_axi_wready <= 1'b0;
        end else begin
            s_axi_wready <= (w_state == W_DATA);
        end
    end
    
    // Write response channel
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            s_axi_bvalid <= 1'b0;
            s_axi_bresp <= 2'b00;
        end else begin
            if (w_state == W_RESP) begin
                s_axi_bvalid <= 1'b1;
                s_axi_bresp <= 2'b00;  // OKAY
            end else if (s_axi_bready) begin
                s_axi_bvalid <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // Register Write Logic
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            ctrl_reg <= '0;
            bitstr_addr_reg <= '0;
            bitstr_size_reg <= '0;
            job_desc_reg <= '0;
            irq_mask_reg <= '0;
            dma_start <= 1'b0;
        end else begin
            // Auto-clear one-shot signals
            dma_start <= 1'b0;
            
            if (w_state == W_DATA && s_axi_wvalid) begin
                case (w_addr_reg[7:0])
                    ADDR_CTRL: begin
                        ctrl_reg <= s_axi_wdata;
                    end
                    
                    ADDR_STATUS: begin
                        // W1C (Write 1 to Clear) for status bits
                        status_reg <= status_reg & ~s_axi_wdata;
                    end
                    
                    ADDR_BITSTR_ADDR: begin
                        bitstr_addr_reg <= s_axi_wdata;
                    end
                    
                    ADDR_BITSTR_SIZE: begin
                        bitstr_size_reg <= s_axi_wdata;
                    end
                    
                    ADDR_DMA_DOORBELL: begin
                        dma_start <= 1'b1;
                    end
                    
                    ADDR_JOB_DESC: begin
                        job_desc_reg <= s_axi_wdata;
                    end
                    
                    ADDR_IRQ_MASK: begin
                        irq_mask_reg <= s_axi_wdata;
                    end
                    
                    default: begin
                        // Read-only or undefined registers
                    end
                endcase
            end
            
            // Update status register from hardware
            status_reg[0] <= cgra_busy;
            status_reg[1] <= cgra_done;
            status_reg[2] <= cgra_error;
            status_reg[3] <= cfg_done;
        end
    end
    
    // =========================================================================
    // AXI4-Lite Read FSM
    // =========================================================================
    typedef enum logic [1:0] {
        R_IDLE = 2'd0,
        R_ADDR = 2'd1,
        R_DATA = 2'd2
    } read_state_t;
    
    read_state_t r_state, r_next_state;
    logic [ADDR_WIDTH-1:0] r_addr_reg;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            r_state <= R_IDLE;
        end else begin
            r_state <= r_next_state;
        end
    end
    
    always_comb begin
        r_next_state = r_state;
        
        case (r_state)
            R_IDLE: begin
                if (s_axi_arvalid) begin
                    r_next_state = R_DATA;
                end
            end
            
            R_DATA: begin
                if (s_axi_rready) begin
                    r_next_state = R_IDLE;
                end
            end
            
            default: r_next_state = R_IDLE;
        endcase
    end
    
    // Read address channel
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            r_addr_reg <= '0;
            s_axi_arready <= 1'b0;
        end else begin
            if (r_state == R_IDLE && s_axi_arvalid) begin
                r_addr_reg <= s_axi_araddr;
                s_axi_arready <= 1'b1;
            end else begin
                s_axi_arready <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // Register Read Logic
    // =========================================================================
    logic [31:0] read_data;
    
    always_comb begin
        case (r_addr_reg[7:0])
            ADDR_CTRL:         read_data = ctrl_reg;
            ADDR_STATUS:       read_data = status_reg;
            ADDR_BITSTR_ADDR:  read_data = bitstr_addr_reg;
            ADDR_BITSTR_SIZE:  read_data = bitstr_size_reg;
            ADDR_DMA_HEAD:     read_data = dma_head;
            ADDR_JOB_DESC:     read_data = job_desc_reg;
            ADDR_PERF0:        read_data = perf_cycles;
            ADDR_PERF1:        read_data = perf_stalls;
            ADDR_IRQ_MASK:     read_data = irq_mask_reg;
            default:           read_data = 32'hDEADBEEF;
        endcase
    end
    
    // Read data channel
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            s_axi_rdata <= '0;
            s_axi_rvalid <= 1'b0;
            s_axi_rresp <= 2'b00;
        end else begin
            if (r_state == R_DATA) begin
                s_axi_rdata <= read_data;
                s_axi_rvalid <= 1'b1;
                s_axi_rresp <= 2'b00;  // OKAY
            end else if (s_axi_rready) begin
                s_axi_rvalid <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // Output assignments
    // =========================================================================
    assign cgra_start     = ctrl_reg[0];
    assign cgra_reset     = ctrl_reg[1];
    assign cfg_start      = ctrl_reg[2];
    assign bitstream_addr = bitstr_addr_reg;
    assign bitstream_size = bitstr_size_reg[15:0];
    assign job_desc_addr  = job_desc_reg;
    assign irq_mask       = irq_mask_reg;

endmodule
