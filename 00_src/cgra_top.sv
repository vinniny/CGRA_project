// ==============================================================================
// CGRA Top-Level Integration - Centralized CSR + Pipelined DMA Architecture
// ==============================================================================
// Integrates:
// - APB CSR interface (control/status registers)
// - Control Unit (3-state FSM with cycle counter)
// - Pipelined DMA Engine (FIFO + separate Read/Write FSMs)
// - CGRA Fabric (4x4 PE array with routing)
// ==============================================================================

module cgra_top #(
    parameter DATA_WIDTH = 32,
    parameter COORD_WIDTH = 4,
    parameter PAYLOAD_WIDTH = 16,
    parameter ADDR_WIDTH = 32,
    parameter SPM_DEPTH = 256,
    parameter RF_DEPTH = 16,
    parameter CONFIG_WIDTH = 64,
    parameter NUM_PES = 16
)(
    input  logic clk,
    input  logic rst_n,
    
    // =========================================================================
    // APB Slave Interface (from CPU/Testbench)
    // =========================================================================
    input  logic                  psel,
    input  logic                  penable,
    input  logic                  pwrite,
    input  logic [ADDR_WIDTH-1:0] paddr,
    input  logic [31:0]           pwdata,
    output logic [31:0]           prdata,
    output logic                  pready,
    output logic                  pslverr,
    
    // =========================================================================
    // AXI4-Lite Master Interface (DMA to External RAM)
    // =========================================================================
    // Write Address Channel
    output logic [ADDR_WIDTH-1:0] m_axi_awaddr,
    output logic                  m_axi_awvalid,
    input  logic                  m_axi_awready,
    
    // Write Data Channel
    output logic [31:0]           m_axi_wdata,
    output logic [3:0]            m_axi_wstrb,
    output logic                  m_axi_wvalid,
    input  logic                  m_axi_wready,
    
    // Write Response Channel
    input  logic                  m_axi_bvalid,
    output logic                  m_axi_bready,
    
    // Read Address Channel
    output logic [ADDR_WIDTH-1:0] m_axi_araddr,
    output logic                  m_axi_arvalid,
    input  logic                  m_axi_arready,
    
    // Read Data Channel
    input  logic [31:0]           m_axi_rdata,
    input  logic                  m_axi_rvalid,
    output logic                  m_axi_rready,
    
    // =========================================================================
    // Interrupt Output
    // =========================================================================
    output logic                  irq
);

    // =========================================================================
    // Internal Wires: CSR → DMA
    // =========================================================================
    logic [31:0] dma_src;
    logic [31:0] dma_dst;
    logic [31:0] dma_size;
    logic        dma_start;
    logic        dma_busy;
    logic        dma_done;
    
    // =========================================================================
    // Internal Wires: CSR → Control Unit
    // =========================================================================
    logic        cu_start;
    logic        cu_soft_reset;
    logic        cu_busy;
    logic        cu_done;
    logic [31:0] cu_cycles;
    
    // =========================================================================
    // Internal Wires: Control Unit → Array
    // =========================================================================
    logic        pe_enable;
    logic        pe_reset_n;
    logic        array_done;
    
    // =========================================================================
    // Internal Wires: Configuration (simplified for now)
    // =========================================================================
    logic [CONFIG_WIDTH-1:0] config_frames [0:15];  // 16 PE configs
    
    // =========================================================================
    // 1. APB CSR Module
    // =========================================================================
    cgra_axi_csr #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .DATA_WIDTH(32)
    ) u_csr (
        .clk(clk),
        .rst_n(rst_n),
        
        // APB Interface
        .psel(psel),
        .penable(penable),
        .pwrite(pwrite),
        .paddr(paddr),
        .pwdata(pwdata),
        .prdata(prdata),
        .pready(pready),
        .pslverr(pslverr),
        
        // DMA Config Wires
        .dma_src(dma_src),
        .dma_dst(dma_dst),
        .dma_size(dma_size),
        .dma_start(dma_start),
        .dma_busy_i(dma_busy),
        .dma_done_i(dma_done),
        
        // Control Unit Config Wires
        .cu_start(cu_start),
        .cu_soft_reset(cu_soft_reset),
        .cu_busy_i(cu_busy),
        .cu_done_i(cu_done),
        .cu_cycles_i(cu_cycles),
        
        // IRQ
        .irq(irq)
    );
    
    // =========================================================================
    // 2. Pipelined DMA Engine
    // =========================================================================
    cgra_dma_engine #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(ADDR_WIDTH),
        .FIFO_DEPTH(8)
    ) u_dma (
        .clk(clk),
        .rst_n(rst_n),
        
        // CSR Config
        .cfg_src(dma_src),
        .cfg_dst(dma_dst),
        .cfg_size(dma_size),
        .cfg_start(dma_start),
        .status_busy(dma_busy),
        .status_done(dma_done),
        .irq_done(),  // Not used here - IRQ from CSR
        
        // AXI4-Lite Master
        .m_axi_awaddr(m_axi_awaddr),
        .m_axi_awvalid(m_axi_awvalid),
        .m_axi_awready(m_axi_awready),
        .m_axi_wdata(m_axi_wdata),
        .m_axi_wstrb(m_axi_wstrb),
        .m_axi_wvalid(m_axi_wvalid),
        .m_axi_wready(m_axi_wready),
        .m_axi_bvalid(m_axi_bvalid),
        .m_axi_bready(m_axi_bready),
        .m_axi_araddr(m_axi_araddr),
        .m_axi_arvalid(m_axi_arvalid),
        .m_axi_arready(m_axi_arready),
        .m_axi_rdata(m_axi_rdata),
        .m_axi_rvalid(m_axi_rvalid),
        .m_axi_rready(m_axi_rready)
    );
    
    // =========================================================================
    // 3. Control Unit
    // =========================================================================
    cgra_control_unit u_cu (
        .clk(clk),
        .rst_n(rst_n),
        
        // CSR Interface
        .start_i(cu_start),
        .soft_reset_i(cu_soft_reset),
        .busy_o(cu_busy),
        .done_o(cu_done),
        .cycle_count_o(cu_cycles),
        
        // Array Interface
        .pe_enable(pe_enable),
        .pe_reset_n(pe_reset_n),
        .array_done_i(array_done),
        
        // Configuration
        .max_cycles_i(32'd0)  // No timeout limit
    );
    
    // =========================================================================
    // 4. CGRA Array (4x4 PE Mesh)
    // =========================================================================
    // Array done signal - for now, tie to 0 (array never signals done)
    // TODO: Connect to actual array completion logic
    assign array_done = 1'b0;
    
    cgra_array_4x4 #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(4),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH)
    ) u_array (
        .clk(clk),
        .rst_n(rst_n & pe_reset_n),  // Combined reset
        
        // Configuration (simplified - all PEs same config for now)
        .config_frame_00(64'd0),
        .config_frame_01(64'd0),
        .config_frame_02(64'd0),
        .config_frame_03(64'd0),
        .config_frame_10(64'd0),
        .config_frame_11(64'd0),
        .config_frame_12(64'd0),
        .config_frame_13(64'd0),
        .config_frame_20(64'd0),
        .config_frame_21(64'd0),
        .config_frame_22(64'd0),
        .config_frame_23(64'd0),
        .config_frame_30(64'd0),
        .config_frame_31(64'd0),
        .config_frame_32(64'd0),
        .config_frame_33(64'd0),
        .config_valid(1'b1),
        
        // North edge inputs - tie off
        .edge_data_in_n0(32'd0),
        .edge_data_in_n1(32'd0),
        .edge_data_in_n2(32'd0),
        .edge_data_in_n3(32'd0),
        .edge_valid_in_n0(1'b0),
        .edge_valid_in_n1(1'b0),
        .edge_valid_in_n2(1'b0),
        .edge_valid_in_n3(1'b0),
        
        // South edge inputs - tie off
        .edge_data_in_s0(32'd0),
        .edge_data_in_s1(32'd0),
        .edge_data_in_s2(32'd0),
        .edge_data_in_s3(32'd0),
        .edge_valid_in_s0(1'b0),
        .edge_valid_in_s1(1'b0),
        .edge_valid_in_s2(1'b0),
        .edge_valid_in_s3(1'b0),
        
        // East edge inputs - tie off
        .edge_data_in_e0(32'd0),
        .edge_data_in_e1(32'd0),
        .edge_data_in_e2(32'd0),
        .edge_data_in_e3(32'd0),
        .edge_valid_in_e0(1'b0),
        .edge_valid_in_e1(1'b0),
        .edge_valid_in_e2(1'b0),
        .edge_valid_in_e3(1'b0),
        
        // West edge inputs - tie off
        .edge_data_in_w0(32'd0),
        .edge_data_in_w1(32'd0),
        .edge_data_in_w2(32'd0),
        .edge_data_in_w3(32'd0),
        .edge_valid_in_w0(1'b0),
        .edge_valid_in_w1(1'b0),
        .edge_valid_in_w2(1'b0),
        .edge_valid_in_w3(1'b0),
        
        // Edge outputs - unused
        .edge_data_out_n0(),
        .edge_data_out_n1(),
        .edge_data_out_n2(),
        .edge_data_out_n3(),
        .edge_valid_out_n0(),
        .edge_valid_out_n1(),
        .edge_valid_out_n2(),
        .edge_valid_out_n3(),
        
        .edge_data_out_s0(),
        .edge_data_out_s1(),
        .edge_data_out_s2(),
        .edge_data_out_s3(),
        .edge_valid_out_s0(),
        .edge_valid_out_s1(),
        .edge_valid_out_s2(),
        .edge_valid_out_s3(),
        
        .edge_data_out_e0(),
        .edge_data_out_e1(),
        .edge_data_out_e2(),
        .edge_data_out_e3(),
        .edge_valid_out_e0(),
        .edge_valid_out_e1(),
        .edge_valid_out_e2(),
        .edge_valid_out_e3(),
        
        .edge_data_out_w0(),
        .edge_data_out_w1(),
        .edge_data_out_w2(),
        .edge_data_out_w3(),
        .edge_valid_out_w0(),
        .edge_valid_out_w1(),
        .edge_valid_out_w2(),
        .edge_valid_out_w3()
    );

endmodule
