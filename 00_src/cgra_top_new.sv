// ==============================================================================
// CGRA Top-Level Integration - Following Complete HAS-MAS-LAS Specification
// ==============================================================================
// Integrates all components per specification block diagram:
// - AXI4-Lite CSR interface (control/status registers)
// - Control Unit/Sequencer (timestep FSM + context scheduler)
// - Configuration Memory (Bank0/Bank1 double-buffered)
// - Tile Memory (4 row-banked memory)
// - DMA Engine (AXI4 Master for DDR access)
// - CGRA Fabric (4x4 PE array with routing)

module cgra_top_new #(
    parameter DATA_WIDTH = 16,
    parameter ADDR_WIDTH = 32,
    parameter SPM_DEPTH = 256,
    parameter RF_DEPTH = 16,
    parameter CONFIG_WIDTH = 64,
    parameter NUM_PES = 16
)(
    input  logic clk,
    input  logic rst_n,
    
    // =========================================================================
    // AXI4-Lite CSR Interface (from RISC-V / ARM / Host)
    // =========================================================================
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
    
    // =========================================================================
    // AXI4 Master Interface (DMA to External DDR3 SDRAM)
    // =========================================================================
    // Write Address Channel
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
    
    // Write Data Channel
    output logic [31:0]           m_axi_wdata,
    output logic [3:0]            m_axi_wstrb,
    output logic                  m_axi_wlast,
    output logic                  m_axi_wvalid,
    input  logic                  m_axi_wready,
    
    // Write Response Channel
    input  logic [3:0]            m_axi_bid,
    input  logic [1:0]            m_axi_bresp,
    input  logic                  m_axi_bvalid,
    output logic                  m_axi_bready,
    
    // Read Address Channel
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
    
    // Read Data Channel
    input  logic [3:0]            m_axi_rid,
    input  logic [31:0]           m_axi_rdata,
    input  logic [1:0]            m_axi_rresp,
    input  logic                  m_axi_rlast,
    input  logic                  m_axi_rvalid,
    output logic                  m_axi_rready,
    
    // =========================================================================
    // Configuration Memory Interface (External SRAM or On-Chip)
    // =========================================================================
    output logic [ADDR_WIDTH-1:0] cfg_mem_addr,
    output logic                  cfg_mem_read,
    input  logic [CONFIG_WIDTH-1:0] cfg_mem_rdata,
    input  logic                  cfg_mem_valid,
    
    // =========================================================================
    // Interrupt Output
    // =========================================================================
    output logic                  irq
);

    // =========================================================================
    // CSR → Control Unit Signals
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
    // Control Unit → Configuration Loader Signals
    // =========================================================================
    logic                  cfg_load_start;
    logic                  cfg_load_done;
    logic                  cfg_load_error;
    logic                  cfg_swap_buffers;
    logic                  cfg_active_buffer;
    
    // =========================================================================
    // Control Unit → DMA Engine Signals
    // =========================================================================
    logic                  dma_trigger;
    logic                  dma_busy;
    logic                  dma_done_int;
    logic                  dma_error;
    
    // =========================================================================
    // Control Unit → PE Array Signals
    // =========================================================================
    logic                  pe_array_enable;
    logic                  pe_array_reset;
    logic [15:0]           current_timestep;
    
    // =========================================================================
    // Configuration Loader → CGRA Array Signals
    // =========================================================================
    logic [CONFIG_WIDTH-1:0] config_frame_00, config_frame_01, config_frame_02, config_frame_03;
    logic [CONFIG_WIDTH-1:0] config_frame_10, config_frame_11, config_frame_12, config_frame_13;
    logic [CONFIG_WIDTH-1:0] config_frame_20, config_frame_21, config_frame_22, config_frame_23;
    logic [CONFIG_WIDTH-1:0] config_frame_30, config_frame_31, config_frame_32, config_frame_33;
    logic                   config_valid;
    
    // =========================================================================
    // Tile Memory Signals (Row-Banked)
    // =========================================================================
    logic [11:0]           bank0_addr, bank1_addr, bank2_addr, bank3_addr;
    logic                  bank0_read, bank1_read, bank2_read, bank3_read;
    logic                  bank0_write, bank1_write, bank2_write, bank3_write;
    logic [DATA_WIDTH-1:0] bank0_wdata, bank1_wdata, bank2_wdata, bank3_wdata;
    logic [DATA_WIDTH-1:0] bank0_rdata, bank1_rdata, bank2_rdata, bank3_rdata;
    logic                  bank0_valid, bank1_valid, bank2_valid, bank3_valid;
    
    // DMA to Tile Memory
    logic [11:0]           dma_mem_addr_int;
    logic [1:0]            dma_bank_sel_int;
    logic                  dma_mem_read;
    logic                  dma_mem_write;
    logic [DATA_WIDTH-1:0] dma_mem_wdata_int;
    logic [DATA_WIDTH-1:0] dma_mem_rdata_int;
    logic                  dma_mem_valid;
    
    // DMA interface width conversion
    logic [ADDR_WIDTH-1:0] dma_local_addr;
    logic [31:0]           dma_local_wdata_int;
    logic [31:0]           dma_local_rdata_int;
    
    // =========================================================================
    // Performance Counter Signals
    // =========================================================================
    logic [31:0]           perf_timesteps;
    
    // =========================================================================
    // Module Instantiations
    // =========================================================================
    
    // -------------------------------------------------------------------------
    // 1. AXI4-Lite CSR Block
    // -------------------------------------------------------------------------
    cgra_axi_csr #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .DATA_WIDTH(32)
    ) u_csr (
        .clk(clk),
        .rst_n(rst_n),
        
        // AXI4-Lite interface
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
        
        // Control outputs
        .cgra_start(cgra_start),
        .cgra_reset(cgra_reset),
        .cfg_start(cfg_start),
        .bitstream_addr(bitstream_addr),
        .bitstream_size(bitstream_size),
        .dma_start(dma_start),
        .job_desc_addr(job_desc_addr),
        .irq_mask(irq_mask),
        
        // Status inputs
        .cgra_busy(cgra_busy),
        .cgra_done(cgra_done),
        .cgra_error(cgra_error),
        .cfg_done(cfg_done),
        .dma_head(dma_head),
        .perf_cycles(perf_cycles),
        .perf_stalls(perf_stalls)
    );
    
    // -------------------------------------------------------------------------
    // 2. Control Unit / Sequencer (Timestep FSM)
    // -------------------------------------------------------------------------
    cgra_control_unit #(
        .NUM_PES(NUM_PES),
        .NUM_TIMESTEPS(256)
    ) u_control_unit (
        .clk(clk),
        .rst_n(rst_n),
        
        // CSR interface signals
        .cgra_start(cgra_start),
        .cgra_reset(cgra_reset),
        .cfg_start(cfg_start),
        .cfg_size(bitstream_size),
        .cgra_busy(cgra_busy),
        .cgra_done(cgra_done),
        .cgra_error(cgra_error),
        
        // Configuration loader control
        .cfg_load_start(cfg_load_start),
        .cfg_load_done(cfg_load_done),
        .cfg_load_error(cfg_load_error),
        .cfg_swap_buffers(cfg_swap_buffers),
        
        // DMA control
        .dma_trigger(dma_trigger),
        .dma_busy(dma_busy),
        .dma_done(dma_done_int),
        .dma_error(dma_error),
        
        // PE array control
        .pe_array_enable(pe_array_enable),
        .pe_array_reset(pe_array_reset),
        .current_timestep(current_timestep),
        
        // Context control (read from config loader)
        .context_active_buf(cfg_active_buffer),
        
        // Performance counters
        .perf_cycles(perf_cycles),
        .perf_stalls(perf_stalls),
        .perf_timesteps(perf_timesteps)
    );
    
    // -------------------------------------------------------------------------
    // 3. Configuration Loader (Bank0/Bank1 Context Memory)
    // -------------------------------------------------------------------------
    cgra_config_loader #(
        .NUM_PES(NUM_PES),
        .CONFIG_WIDTH(CONFIG_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .MAX_FRAMES(1024)
    ) u_config_loader (
        .clk(clk),
        .rst_n(rst_n),
        
        // Control interface
        .start_load(cfg_load_start),
        .bitstream_addr(bitstream_addr),
        .bitstream_size(bitstream_size),
        .load_done(cfg_load_done),
        .load_error(cfg_load_error),
        
        // Context swap control
        .swap_buffers(cfg_swap_buffers),
        .active_buffer(cfg_active_buffer),
        
        // Memory interface
        .mem_addr(cfg_mem_addr),
        .mem_read(cfg_mem_read),
        .mem_rdata(cfg_mem_rdata),
        .mem_valid(cfg_mem_valid),
        
        // Configuration outputs to CGRA array
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
    
    assign cfg_done = cfg_load_done;
    
    // -------------------------------------------------------------------------
    // 4. Tile Memory (Row-Banked 4 Banks)
    // -------------------------------------------------------------------------
    cgra_tile_memory #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(12),
        .BANK_DEPTH(1024),
        .NUM_BANKS(4)
    ) u_tile_memory (
        .clk(clk),
        .rst_n(rst_n),
        
        // Bank 0 (Row 0: PE 0,0 - PE 0,3)
        .bank0_addr(bank0_addr),
        .bank0_read(bank0_read),
        .bank0_write(bank0_write),
        .bank0_wdata(bank0_wdata),
        .bank0_rdata(bank0_rdata),
        .bank0_valid(bank0_valid),
        
        // Bank 1 (Row 1: PE 1,0 - PE 1,3)
        .bank1_addr(bank1_addr),
        .bank1_read(bank1_read),
        .bank1_write(bank1_write),
        .bank1_wdata(bank1_wdata),
        .bank1_rdata(bank1_rdata),
        .bank1_valid(bank1_valid),
        
        // Bank 2 (Row 2: PE 2,0 - PE 2,3)
        .bank2_addr(bank2_addr),
        .bank2_read(bank2_read),
        .bank2_write(bank2_write),
        .bank2_wdata(bank2_wdata),
        .bank2_rdata(bank2_rdata),
        .bank2_valid(bank2_valid),
        
        // Bank 3 (Row 3: PE 3,0 - PE 3,3)
        .bank3_addr(bank3_addr),
        .bank3_read(bank3_read),
        .bank3_write(bank3_write),
        .bank3_wdata(bank3_wdata),
        .bank3_rdata(bank3_rdata),
        .bank3_valid(bank3_valid),
        
        // DMA/External access port
        .ext_addr(dma_mem_addr_int),
        .ext_bank_sel(dma_bank_sel_int),
        .ext_read(dma_mem_read),
        .ext_write(dma_mem_write),
        .ext_wdata(dma_mem_wdata_int),
        .ext_rdata(dma_mem_rdata_int),
        .ext_valid(dma_mem_valid)
    );
    
    // -------------------------------------------------------------------------
    // 5. DMA Engine (AXI4 Master)
    // -------------------------------------------------------------------------
    cgra_dma_engine #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(ADDR_WIDTH),
        .MAX_BURST_LEN(16),
        .ID_WIDTH(4)
    ) u_dma_engine (
        .clk(clk),
        .rst_n(rst_n),
        
        // Control interface
        .dma_start(dma_trigger),
        .job_desc_addr(job_desc_addr),
        .dma_busy(dma_busy),
        .dma_done(dma_done_int),
        .dma_error(dma_error),
        .dma_head_ptr(dma_head),
        
        // AXI4 Master Write Address Channel
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
        
        // AXI4 Master Write Data Channel
        .m_axi_wdata(m_axi_wdata),
        .m_axi_wstrb(m_axi_wstrb),
        .m_axi_wlast(m_axi_wlast),
        .m_axi_wvalid(m_axi_wvalid),
        .m_axi_wready(m_axi_wready),
        
        // AXI4 Master Write Response Channel
        .m_axi_bid(m_axi_bid),
        .m_axi_bresp(m_axi_bresp),
        .m_axi_bvalid(m_axi_bvalid),
        .m_axi_bready(m_axi_bready),
        
        // AXI4 Master Read Address Channel
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
        
        // AXI4 Master Read Data Channel
        .m_axi_rid(m_axi_rid),
        .m_axi_rdata(m_axi_rdata),
        .m_axi_rresp(m_axi_rresp),
        .m_axi_rlast(m_axi_rlast),
        .m_axi_rvalid(m_axi_rvalid),
        .m_axi_rready(m_axi_rready),
        
        // Local memory interface (to Tile Memory)
        .local_mem_addr(dma_local_addr),
        .local_mem_write(dma_mem_write),
        .local_mem_wdata(dma_local_wdata_int),
        .local_mem_read(dma_mem_read),
        .local_mem_rdata(dma_local_rdata_int),
        .local_mem_valid(dma_mem_valid)
    );
    
    // -------------------------------------------------------------------------
    // 6. CGRA Fabric (4x4 PE Array)
    // -------------------------------------------------------------------------
    cgra_array_4x4 #(
        .DATA_WIDTH(DATA_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH)
    ) u_cgra_array (
        .clk(clk),
        .rst_n(rst_n && !pe_array_reset),
        
        // Configuration frames (from Config Loader)
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
        .config_valid(config_valid && pe_array_enable)
    );
    
    // =========================================================================
    // DMA Width Conversion (32-bit to 16-bit)
    // =========================================================================
    always_comb begin
        dma_mem_addr_int = dma_local_addr[11:0];
        dma_bank_sel_int = dma_local_addr[13:12];
    end
    
    // DMA writes to tile memory (32-bit from DMA -> 16-bit to memory)
    assign dma_mem_wdata_int = dma_local_wdata_int[15:0];
    
    // Tile memory reads to DMA (16-bit from memory -> 32-bit to DMA)
    assign dma_local_rdata_int = {16'd0, dma_mem_rdata_int};
    
    // =========================================================================
    // Tile Memory Access Connections (simplified for now)
    // =========================================================================
    // In a complete implementation, PEs would connect to their respective
    // row banks for local memory access
    always_comb begin
        bank0_addr = 12'd0;
        bank0_read = 1'b0;
        bank0_write = 1'b0;
        bank0_wdata = 16'd0;
        
        bank1_addr = 12'd0;
        bank1_read = 1'b0;
        bank1_write = 1'b0;
        bank1_wdata = 16'd0;
        
        bank2_addr = 12'd0;
        bank2_read = 1'b0;
        bank2_write = 1'b0;
        bank2_wdata = 16'd0;
        
        bank3_addr = 12'd0;
        bank3_read = 1'b0;
        bank3_write = 1'b0;
        bank3_wdata = 16'd0;
    end
    
    // =========================================================================
    // Interrupt Generation
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            irq <= 1'b0;
        end else begin
            // Generate interrupt on completion or error
            if (irq_mask[0] && cgra_done) begin
                irq <= 1'b1;
            end else if (irq_mask[1] && cgra_error) begin
                irq <= 1'b1;
            end else if (irq_mask[2] && dma_done_int) begin
                irq <= 1'b1;
            end else begin
                irq <= 1'b0;
            end
        end
    end

endmodule
