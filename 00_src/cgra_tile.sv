// cgra_tile.sv — one PE with mesh broadcast.
//
// PE computes from its 4 neighbor inputs; result broadcasts to all 4 outputs,
// with per-direction valid gated by the PE's configured route_mask.

module cgra_tile #(
    parameter DATA_WIDTH   = 32,
    parameter COORD_WIDTH  = 4,
    parameter ADDR_WIDTH   = 8,
    parameter SPM_DEPTH    = 256,
    parameter RF_DEPTH     = 16,
    parameter X_COORD      = 0,
    parameter Y_COORD      = 0,
    parameter CONTEXT_DEPTH = 16,
    parameter PC_WIDTH     = 4
)(
    input  logic                   clk,
    input  logic                   rst_n,
    input  logic [63:0]            config_frame,
    input  logic                   config_valid,

    input  logic [PC_WIDTH-1:0]    context_pc,
    input  logic                   global_stall,

    input  logic [PC_WIDTH-1:0]    cfg_wr_addr,
    input  logic [63:0]            cfg_wr_data,
    input  logic                   cfg_wr_en,

    // Mesh ports (N/E/S/W)
    input  logic [DATA_WIDTH-1:0]  data_in_n,
    input  logic [DATA_WIDTH-1:0]  data_in_e,
    input  logic [DATA_WIDTH-1:0]  data_in_s,
    input  logic [DATA_WIDTH-1:0]  data_in_w,

    output logic [DATA_WIDTH-1:0]  data_out_n,
    output logic [DATA_WIDTH-1:0]  data_out_e,
    output logic [DATA_WIDTH-1:0]  data_out_s,
    output logic [DATA_WIDTH-1:0]  data_out_w,
    output logic                   valid_out_n,
    output logic                   valid_out_e,
    output logic                   valid_out_s,
    output logic                   valid_out_w,

    output logic [PC_WIDTH-1:0]    branch_target_o,
    output logic                   branch_taken_o,

    // DMA→SPM write
    input  logic                                  dma_spm_we,
    input  logic [$clog2(SPM_DEPTH)-1:0]          dma_spm_waddr,
    input  logic [DATA_WIDTH-1:0]                 dma_spm_wdata
);

    logic [DATA_WIDTH-1:0] pe_result;
    logic                  pe_valid_n, pe_valid_e, pe_valid_s, pe_valid_w;

    cgra_pe #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_pe (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame),
        .config_valid(config_valid),

        .context_pc(context_pc),
        .global_stall(global_stall),

        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en),

        .data_in_n(data_in_n),
        .data_in_e(data_in_e),
        .data_in_s(data_in_s),
        .data_in_w(data_in_w),

        .data_out(pe_result),
        .valid_out_n(pe_valid_n),
        .valid_out_e(pe_valid_e),
        .valid_out_s(pe_valid_s),
        .valid_out_w(pe_valid_w),

        .branch_target_o(branch_target_o),
        .branch_taken_o(branch_taken_o),

        .dma_spm_we_i   (dma_spm_we),
        .dma_spm_waddr_i(dma_spm_waddr),
        .dma_spm_wdata_i(dma_spm_wdata)
    );

    assign data_out_n = pe_result;
    assign data_out_e = pe_result;
    assign data_out_s = pe_result;
    assign data_out_w = pe_result;

    assign valid_out_n = pe_valid_n;
    assign valid_out_e = pe_valid_e;
    assign valid_out_s = pe_valid_s;
    assign valid_out_w = pe_valid_w;

endmodule
