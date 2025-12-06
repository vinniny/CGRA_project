// ==============================================================================
// CGRA Top-Level Wrapper
// ==============================================================================
// Integrates all CGRA components:
// - AXI4-Lite CSR interface
// - Configuration loader with double buffering
// - 4x4 PE array
// - Execution control FSM
// - Performance counters

module cgra_top #(
    parameter DATA_WIDTH = 16,
    parameter ADDR_WIDTH = 32,
    parameter SPM_DEPTH = 256,
    parameter RF_DEPTH = 16,
    parameter CONFIG_WIDTH = 64
)(
    input  logic clk,
    input  logic rst_n,
    
    // AXI4-Lite CSR interface
    input  logic [ADDR_WIDTH-1:0] s_axi_awaddr,
    input  logic                  s_axi_awvalid,
    output logic                  s_axi_awready,
    
    input  logic [31:0]           s_axi_wdata,
    input  logic [3:0]            s_axi_wstrb,
    input  logic                  s_axi_wvalid,
    output logic                  s_axi_wready,
    
    output logic [1:0]            s_axi_bresp,
    output logic                  s_axi_bvalid,
    input  logic                  s_axi_bready,
    
    input  logic [ADDR_WIDTH-1:0] s_axi_araddr,
    input  logic                  s_axi_arvalid,
    output logic                  s_axi_arready,
    
    output logic [31:0]           s_axi_rdata,
    output logic [1:0]            s_axi_rresp,
    output logic                  s_axi_rvalid,
    input  logic                  s_axi_rready,
    
    // Configuration memory interface
    output logic [ADDR_WIDTH-1:0] cfg_mem_addr,
    output logic                  cfg_mem_read,
    input  logic [CONFIG_WIDTH-1:0] cfg_mem_rdata,
    input  logic                  cfg_mem_valid,
    
    // Data memory interface (simplified)
    output logic [ADDR_WIDTH-1:0] data_mem_addr,
    output logic                  data_mem_read,
    output logic                  data_mem_write,
    output logic [DATA_WIDTH-1:0] data_mem_wdata,
    input  logic [DATA_WIDTH-1:0] data_mem_rdata,
    input  logic                  data_mem_valid,
    
    // AXI4 Master interface for DMA engine
    output logic [3:0]            m_axi_awid,
    output logic [ADDR_WIDTH-1:0] m_axi_awaddr,
    output logic [7:0]            m_axi_awlen,
    output logic [2:0]            m_axi_awsize,
    output logic [1:0]            m_axi_awburst,
    output logic                  m_axi_awlock,
    output logic [3:0]            m_axi_awcache,
    output logic [2:0]            m_axi_awprot,
    output logic                  m_axi_awvalid,
    input  logic                  m_axi_awready,
    output logic [31:0]           m_axi_wdata,
    output logic [3:0]            m_axi_wstrb,
    output logic                  m_axi_wlast,
    output logic                  m_axi_wvalid,
    input  logic                  m_axi_wready,
    input  logic [3:0]            m_axi_bid,
    input  logic [1:0]            m_axi_bresp,
    input  logic                  m_axi_bvalid,
    output logic                  m_axi_bready,
    output logic [3:0]            m_axi_arid,
    output logic [ADDR_WIDTH-1:0] m_axi_araddr,
    output logic [7:0]            m_axi_arlen,
    output logic [2:0]            m_axi_arsize,
    output logic [1:0]            m_axi_arburst,
    output logic                  m_axi_arlock,
    output logic [3:0]            m_axi_arcache,
    output logic [2:0]            m_axi_arprot,
    output logic                  m_axi_arvalid,
    input  logic                  m_axi_arready,
    input  logic [3:0]            m_axi_rid,
    input  logic [31:0]           m_axi_rdata,
    input  logic [1:0]            m_axi_rresp,
    input  logic                  m_axi_rlast,
    input  logic                  m_axi_rvalid,
    output logic                  m_axi_rready,
    
    // Interrupt output
    output logic                  irq
);

    // =========================================================================
    // CSR signals
    // =========================================================================
    logic                  cgra_start;
    logic                  cgra_reset;
    logic                  cfg_start;
    logic [ADDR_WIDTH-1:0] bitstream_addr;
    logic [15:0]           bitstream_size;
    logic                  dma_start;
    logic [ADDR_WIDTH-1:0] job_desc_addr;
    logic [31:0]           irq_mask;
    
    logic                  cgra_busy;
    logic                  cgra_done;
    logic                  cgra_error;
    logic                  cfg_done;
    logic [31:0]           dma_head;
    logic [31:0]           perf_cycles;
    logic [31:0]           perf_stalls;
    
    // =========================================================================
    // DMA engine and tile memory signals
    // =========================================================================
    logic                  dma_busy;
    logic                  dma_done;
    logic                  dma_error;
    logic [31:0]           dma_head_ptr;
    
    logic [ADDR_WIDTH-1:0] dma_local_addr;
    logic                  dma_mem_read;
    logic                  dma_mem_write;
    logic [31:0]           dma_local_wdata;
    logic [31:0]           dma_local_rdata;
    logic                  dma_local_valid;
    
    logic [11:0]           bank0_addr, bank1_addr, bank2_addr, bank3_addr;
    logic                  bank0_read, bank1_read, bank2_read, bank3_read;
    logic                  bank0_write, bank1_write, bank2_write, bank3_write;
    logic [DATA_WIDTH-1:0] bank0_wdata, bank1_wdata, bank2_wdata, bank3_wdata;
    logic [DATA_WIDTH-1:0] bank0_rdata, bank1_rdata, bank2_rdata, bank3_rdata;
    logic                  bank0_valid, bank1_valid, bank2_valid, bank3_valid;
    
    logic [11:0]           tm_ext_addr;
    logic [1:0]            tm_ext_bank_sel;
    logic                  tm_ext_read;
    logic                  tm_ext_write;
    logic [DATA_WIDTH-1:0] tm_ext_wdata;
    logic [DATA_WIDTH-1:0] tm_ext_rdata;
    logic                  tm_ext_valid;
    
    // =========================================================================
    // Configuration loader signals
    // =========================================================================
    logic                  load_start;
    logic                  load_done;
    logic                  load_error;
    logic                  swap_context;
    logic                  active_buffer;
    
    logic [CONFIG_WIDTH-1:0] config_frame_00, config_frame_01, config_frame_02, config_frame_03;
    logic [CONFIG_WIDTH-1:0] config_frame_10, config_frame_11, config_frame_12, config_frame_13;
    logic [CONFIG_WIDTH-1:0] config_frame_20, config_frame_21, config_frame_22, config_frame_23;
    logic [CONFIG_WIDTH-1:0] config_frame_30, config_frame_31, config_frame_32, config_frame_33;
    logic                   config_valid;
    
    // =========================================================================
    // Execution control FSM
    // =========================================================================
    typedef enum logic [2:0] {
        EXEC_IDLE     = 3'd0,
        EXEC_WAIT_CFG = 3'd1,
        EXEC_SETUP    = 3'd2,
        EXEC_RUN      = 3'd3,
        EXEC_DRAIN    = 3'd4,
        EXEC_COMPLETE = 3'd5,
        EXEC_ERROR    = 3'd6
    } exec_state_t;
    
    exec_state_t exec_state, exec_next_state;
    
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            exec_state <= EXEC_IDLE;
        end else begin
            exec_state <= exec_next_state;
        end
    end
    
    always_comb begin
        exec_next_state = exec_state;
        
        case (exec_state)
            EXEC_IDLE: begin
                if (cgra_start && cfg_start) begin
                    exec_next_state = EXEC_WAIT_CFG;
                end
            end
            
            EXEC_WAIT_CFG: begin
                if (cfg_done) begin
                    exec_next_state = EXEC_SETUP;
                end else if (load_error) begin
                    exec_next_state = EXEC_ERROR;
                end
            end
            
            EXEC_SETUP: begin
                exec_next_state = EXEC_RUN;
            end
            
            EXEC_RUN: begin
                if (!cgra_start) begin
                    exec_next_state = EXEC_DRAIN;
                end
            end
            
            EXEC_DRAIN: begin
                exec_next_state = EXEC_COMPLETE;
            end
            
            EXEC_COMPLETE: begin
                exec_next_state = EXEC_IDLE;
            end
            
            EXEC_ERROR: begin
                if (!cgra_start) begin
                    exec_next_state = EXEC_IDLE;
                end
            end
            
            default: exec_next_state = EXEC_IDLE;
        endcase
    end
    
    // =========================================================================
    // Control logic
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            load_start <= 1'b0;
            swap_context <= 1'b0;
        end else begin
            // Start configuration load
            if (cfg_start && exec_state == EXEC_IDLE) begin
                load_start <= 1'b1;
            end else if (load_done) begin
                load_start <= 1'b0;
            end
            
            // Swap context when load is complete
            if (load_done && exec_state == EXEC_WAIT_CFG) begin
                swap_context <= 1'b1;
            end else begin
                swap_context <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // Status signals
    // =========================================================================
    assign cgra_busy = ((exec_state != EXEC_IDLE) && (exec_state != EXEC_COMPLETE)) || dma_busy;
    assign cgra_done = (exec_state == EXEC_COMPLETE);
    assign cgra_error = (exec_state == EXEC_ERROR) || load_error || dma_error;
    assign cfg_done = load_done;
    
    // =========================================================================
    // Performance counters
    // =========================================================================
    logic [31:0] cycle_counter;
    logic [31:0] stall_counter;
    
    always_ff @(posedge clk) begin
        if (!rst_n || cgra_reset) begin
            cycle_counter <= '0;
            stall_counter <= '0;
        end else begin
            if (exec_state == EXEC_RUN) begin
                cycle_counter <= cycle_counter + 32'd1;
            end
            
            // Count stalls (simplified - increment when config not valid during run)
            if (exec_state == EXEC_RUN && !config_valid) begin
                stall_counter <= stall_counter + 32'd1;
            end
        end
    end
    
    assign perf_cycles = cycle_counter;
    assign perf_stalls = stall_counter;
    assign dma_head = dma_head_ptr;
    
    // =========================================================================
    // DMA ↔ Tile memory glue logic and data_mem visibility
    // =========================================================================
    always_comb begin
        tm_ext_addr = dma_local_addr[11:0];
        tm_ext_bank_sel = dma_local_addr[13:12];
        tm_ext_read = dma_mem_read;
        tm_ext_write = dma_mem_write;
        tm_ext_wdata = dma_local_wdata[DATA_WIDTH-1:0];
    end
    
    assign dma_local_rdata = {{(32-DATA_WIDTH){1'b0}}, tm_ext_rdata};
    assign dma_local_valid = tm_ext_valid;
    
    // Expose DMA local accesses on the simplified data memory port
    assign data_mem_addr = dma_local_addr;
    assign data_mem_read = dma_mem_read;
    assign data_mem_write = dma_mem_write;
    assign data_mem_wdata = dma_local_wdata[DATA_WIDTH-1:0];
    
    // =========================================================================
    // Interrupt generation
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            irq <= 1'b0;
        end else begin
            irq <= (irq_mask[0] && cgra_done) || 
                   (irq_mask[1] && cgra_error);
        end
    end
    
    // =========================================================================
    // Module instantiations
    // =========================================================================
    
    // AXI4-Lite CSR
    cgra_axi_csr #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .DATA_WIDTH(32)
    ) u_csr (
        .clk(clk),
        .rst_n(rst_n),
        .s_axi_awaddr(s_axi_awaddr),
        .s_axi_awvalid(s_axi_awvalid),
        .s_axi_awready(s_axi_awready),
        .s_axi_wdata(s_axi_wdata),
        .s_axi_wstrb(s_axi_wstrb),
        .s_axi_wvalid(s_axi_wvalid),
        .s_axi_wready(s_axi_wready),
        .s_axi_bresp(s_axi_bresp),
        .s_axi_bvalid(s_axi_bvalid),
        .s_axi_bready(s_axi_bready),
        .s_axi_araddr(s_axi_araddr),
        .s_axi_arvalid(s_axi_arvalid),
        .s_axi_arready(s_axi_arready),
        .s_axi_rdata(s_axi_rdata),
        .s_axi_rresp(s_axi_rresp),
        .s_axi_rvalid(s_axi_rvalid),
        .s_axi_rready(s_axi_rready),
        .cgra_start(cgra_start),
        .cgra_reset(cgra_reset),
        .cfg_start(cfg_start),
        .bitstream_addr(bitstream_addr),
        .bitstream_size(bitstream_size),
        .dma_start(dma_start),
        .job_desc_addr(job_desc_addr),
        .irq_mask(irq_mask),
        .cgra_busy(cgra_busy),
        .cgra_done(cgra_done),
        .cgra_error(cgra_error),
        .cfg_done(cfg_done),
        .dma_head(dma_head),
        .perf_cycles(perf_cycles),
        .perf_stalls(perf_stalls)
    );
    
    // Configuration loader
    cgra_config_loader #(
        .NUM_PES(16),
        .CONFIG_WIDTH(CONFIG_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .MAX_FRAMES(1024)
    ) u_config_loader (
        .clk(clk),
        .rst_n(rst_n),
        .start_load(load_start),
        .bitstream_addr(bitstream_addr),
        .bitstream_size(bitstream_size),
        .load_done(load_done),
        .load_error(load_error),
        .swap_buffers(swap_context),
        .active_buffer(active_buffer),
        .mem_addr(cfg_mem_addr),
        .mem_read(cfg_mem_read),
        .mem_rdata(cfg_mem_rdata),
        .mem_valid(cfg_mem_valid),
        .config_frame_00(config_frame_00),
        .config_frame_01(config_frame_01),
        .config_frame_02(config_frame_02),
        .config_frame_03(config_frame_03),
        .config_frame_10(config_frame_10),
        .config_frame_11(config_frame_11),
        .config_frame_12(config_frame_12),
        .config_frame_13(config_frame_13),
        .config_frame_20(config_frame_20),
        .config_frame_21(config_frame_21),
        .config_frame_22(config_frame_22),
        .config_frame_23(config_frame_23),
        .config_frame_30(config_frame_30),
        .config_frame_31(config_frame_31),
        .config_frame_32(config_frame_32),
        .config_frame_33(config_frame_33),
        .config_valid(config_valid)
    );
    
    // DMA engine
    cgra_dma_engine #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(ADDR_WIDTH),
        .MAX_BURST_LEN(16),
        .ID_WIDTH(4)
    ) u_dma_engine (
        .clk(clk),
        .rst_n(rst_n),
        .dma_start(dma_start),
        .job_desc_addr(job_desc_addr),
        .dma_busy(dma_busy),
        .dma_done(dma_done),
        .dma_error(dma_error),
        .dma_head_ptr(dma_head_ptr),
        .m_axi_awid(m_axi_awid),
        .m_axi_awaddr(m_axi_awaddr),
        .m_axi_awlen(m_axi_awlen),
        .m_axi_awsize(m_axi_awsize),
        .m_axi_awburst(m_axi_awburst),
        .m_axi_awlock(m_axi_awlock),
        .m_axi_awcache(m_axi_awcache),
        .m_axi_awprot(m_axi_awprot),
        .m_axi_awvalid(m_axi_awvalid),
        .m_axi_awready(m_axi_awready),
        .m_axi_wdata(m_axi_wdata),
        .m_axi_wstrb(m_axi_wstrb),
        .m_axi_wlast(m_axi_wlast),
        .m_axi_wvalid(m_axi_wvalid),
        .m_axi_wready(m_axi_wready),
        .m_axi_bid(m_axi_bid),
        .m_axi_bresp(m_axi_bresp),
        .m_axi_bvalid(m_axi_bvalid),
        .m_axi_bready(m_axi_bready),
        .m_axi_arid(m_axi_arid),
        .m_axi_araddr(m_axi_araddr),
        .m_axi_arlen(m_axi_arlen),
        .m_axi_arsize(m_axi_arsize),
        .m_axi_arburst(m_axi_arburst),
        .m_axi_arlock(m_axi_arlock),
        .m_axi_arcache(m_axi_arcache),
        .m_axi_arprot(m_axi_arprot),
        .m_axi_arvalid(m_axi_arvalid),
        .m_axi_arready(m_axi_arready),
        .m_axi_rid(m_axi_rid),
        .m_axi_rdata(m_axi_rdata),
        .m_axi_rresp(m_axi_rresp),
        .m_axi_rlast(m_axi_rlast),
        .m_axi_rvalid(m_axi_rvalid),
        .m_axi_rready(m_axi_rready),
        .local_mem_addr(dma_local_addr),
        .local_mem_write(dma_mem_write),
        .local_mem_wdata(dma_local_wdata),
        .local_mem_read(dma_mem_read),
        .local_mem_rdata(dma_local_rdata),
        .local_mem_valid(dma_local_valid)
    );
    
    // Default tile bank controls (placeholder for PE connections)
    always_comb begin
        bank0_addr = 12'd0;
        bank0_read = 1'b0;
        bank0_write = 1'b0;
        bank0_wdata = '0;
        
        bank1_addr = 12'd0;
        bank1_read = 1'b0;
        bank1_write = 1'b0;
        bank1_wdata = '0;
        
        bank2_addr = 12'd0;
        bank2_read = 1'b0;
        bank2_write = 1'b0;
        bank2_wdata = '0;
        
        bank3_addr = 12'd0;
        bank3_read = 1'b0;
        bank3_write = 1'b0;
        bank3_wdata = '0;
    end
    
    // Tile memory
    cgra_tile_memory #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(12),
        .BANK_DEPTH(1024),
        .NUM_BANKS(4)
    ) u_tile_memory (
        .clk(clk),
        .rst_n(rst_n),
        .bank0_addr(bank0_addr),
        .bank0_read(bank0_read),
        .bank0_write(bank0_write),
        .bank0_wdata(bank0_wdata),
        .bank0_rdata(bank0_rdata),
        .bank0_valid(bank0_valid),
        .bank1_addr(bank1_addr),
        .bank1_read(bank1_read),
        .bank1_write(bank1_write),
        .bank1_wdata(bank1_wdata),
        .bank1_rdata(bank1_rdata),
        .bank1_valid(bank1_valid),
        .bank2_addr(bank2_addr),
        .bank2_read(bank2_read),
        .bank2_write(bank2_write),
        .bank2_wdata(bank2_wdata),
        .bank2_rdata(bank2_rdata),
        .bank2_valid(bank2_valid),
        .bank3_addr(bank3_addr),
        .bank3_read(bank3_read),
        .bank3_write(bank3_write),
        .bank3_wdata(bank3_wdata),
        .bank3_rdata(bank3_rdata),
        .bank3_valid(bank3_valid),
        .ext_addr(tm_ext_addr),
        .ext_bank_sel(tm_ext_bank_sel),
        .ext_read(tm_ext_read),
        .ext_write(tm_ext_write),
        .ext_wdata(tm_ext_wdata),
        .ext_rdata(tm_ext_rdata),
        .ext_valid(tm_ext_valid)
    );
    
    // CGRA 4x4 array
    cgra_array_4x4 #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(4),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH)
    ) u_cgra_array (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame_00(config_frame_00),
        .config_frame_01(config_frame_01),
        .config_frame_02(config_frame_02),
        .config_frame_03(config_frame_03),
        .config_frame_10(config_frame_10),
        .config_frame_11(config_frame_11),
        .config_frame_12(config_frame_12),
        .config_frame_13(config_frame_13),
        .config_frame_20(config_frame_20),
        .config_frame_21(config_frame_21),
        .config_frame_22(config_frame_22),
        .config_frame_23(config_frame_23),
        .config_frame_30(config_frame_30),
        .config_frame_31(config_frame_31),
        .config_frame_32(config_frame_32),
        .config_frame_33(config_frame_33),
        .config_valid(config_valid && (exec_state == EXEC_RUN)),
        // Edge inputs
        .edge_data_in_n0(bank0_rdata), .edge_data_in_n1(bank1_rdata), .edge_data_in_n2(bank2_rdata), .edge_data_in_n3(bank3_rdata),
        .edge_valid_in_n0(bank0_valid), .edge_valid_in_n1(bank1_valid), .edge_valid_in_n2(bank2_valid), .edge_valid_in_n3(bank3_valid),
        .edge_data_in_s0('0), .edge_data_in_s1('0), .edge_data_in_s2('0), .edge_data_in_s3('0),
        .edge_valid_in_s0(1'b0), .edge_valid_in_s1(1'b0), .edge_valid_in_s2(1'b0), .edge_valid_in_s3(1'b0),
        .edge_data_in_e0('0), .edge_data_in_e1('0), .edge_data_in_e2('0), .edge_data_in_e3('0),
        .edge_valid_in_e0(1'b0), .edge_valid_in_e1(1'b0), .edge_valid_in_e2(1'b0), .edge_valid_in_e3(1'b0),
        .edge_data_in_w0('0), .edge_data_in_w1('0), .edge_data_in_w2('0), .edge_data_in_w3('0),
        .edge_valid_in_w0(1'b0), .edge_valid_in_w1(1'b0), .edge_valid_in_w2(1'b0), .edge_valid_in_w3(1'b0),
        // Edge outputs (not connected in this version)
        .edge_data_out_n0(), .edge_data_out_n1(), .edge_data_out_n2(), .edge_data_out_n3(),
        .edge_valid_out_n0(), .edge_valid_out_n1(), .edge_valid_out_n2(), .edge_valid_out_n3(),
        .edge_data_out_s0(), .edge_data_out_s1(), .edge_data_out_s2(), .edge_data_out_s3(),
        .edge_valid_out_s0(), .edge_valid_out_s1(), .edge_valid_out_s2(), .edge_valid_out_s3(),
        .edge_data_out_e0(), .edge_data_out_e1(), .edge_data_out_e2(), .edge_data_out_e3(),
        .edge_valid_out_e0(), .edge_valid_out_e1(), .edge_valid_out_e2(), .edge_valid_out_e3(),
        .edge_data_out_w0(), .edge_data_out_w1(), .edge_data_out_w2(), .edge_data_out_w3(),
        .edge_valid_out_w0(), .edge_valid_out_w1(), .edge_valid_out_w2(), .edge_valid_out_w3()
    );

endmodule
