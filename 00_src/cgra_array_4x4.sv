// ==============================================================================
// CGRA 4x4 Array
// ==============================================================================
// Instantiates 16 PEs and routers in a 4x4 mesh topology
// Provides configuration interface for all PEs

module cgra_array_4x4 #(
    parameter DATA_WIDTH = 16,
    parameter ADDR_WIDTH = 4,
    parameter SPM_DEPTH = 256,
    parameter RF_DEPTH = 16
)(
    input  logic clk,
    input  logic rst_n,
    
    // Configuration interface - 16 PEs x 64-bit config
    input  logic [63:0] config_frame_00,
    input  logic [63:0] config_frame_01,
    input  logic [63:0] config_frame_02,
    input  logic [63:0] config_frame_03,
    input  logic [63:0] config_frame_10,
    input  logic [63:0] config_frame_11,
    input  logic [63:0] config_frame_12,
    input  logic [63:0] config_frame_13,
    input  logic [63:0] config_frame_20,
    input  logic [63:0] config_frame_21,
    input  logic [63:0] config_frame_22,
    input  logic [63:0] config_frame_23,
    input  logic [63:0] config_frame_30,
    input  logic [63:0] config_frame_31,
    input  logic [63:0] config_frame_32,
    input  logic [63:0] config_frame_33,
    input  logic        config_valid,
    
    // Edge inputs (from external)
    input  logic [DATA_WIDTH-1:0] edge_data_in_n0,
    input  logic [DATA_WIDTH-1:0] edge_data_in_n1,
    input  logic [DATA_WIDTH-1:0] edge_data_in_n2,
    input  logic [DATA_WIDTH-1:0] edge_data_in_n3,
    input  logic                  edge_valid_in_n0,
    input  logic                  edge_valid_in_n1,
    input  logic                  edge_valid_in_n2,
    input  logic                  edge_valid_in_n3,
    
    input  logic [DATA_WIDTH-1:0] edge_data_in_s0,
    input  logic [DATA_WIDTH-1:0] edge_data_in_s1,
    input  logic [DATA_WIDTH-1:0] edge_data_in_s2,
    input  logic [DATA_WIDTH-1:0] edge_data_in_s3,
    input  logic                  edge_valid_in_s0,
    input  logic                  edge_valid_in_s1,
    input  logic                  edge_valid_in_s2,
    input  logic                  edge_valid_in_s3,
    
    input  logic [DATA_WIDTH-1:0] edge_data_in_e0,
    input  logic [DATA_WIDTH-1:0] edge_data_in_e1,
    input  logic [DATA_WIDTH-1:0] edge_data_in_e2,
    input  logic [DATA_WIDTH-1:0] edge_data_in_e3,
    input  logic                  edge_valid_in_e0,
    input  logic                  edge_valid_in_e1,
    input  logic                  edge_valid_in_e2,
    input  logic                  edge_valid_in_e3,
    
    input  logic [DATA_WIDTH-1:0] edge_data_in_w0,
    input  logic [DATA_WIDTH-1:0] edge_data_in_w1,
    input  logic [DATA_WIDTH-1:0] edge_data_in_w2,
    input  logic [DATA_WIDTH-1:0] edge_data_in_w3,
    input  logic                  edge_valid_in_w0,
    input  logic                  edge_valid_in_w1,
    input  logic                  edge_valid_in_w2,
    input  logic                  edge_valid_in_w3,
    
    // Edge outputs (to external)
    output logic [DATA_WIDTH-1:0] edge_data_out_n0,
    output logic [DATA_WIDTH-1:0] edge_data_out_n1,
    output logic [DATA_WIDTH-1:0] edge_data_out_n2,
    output logic [DATA_WIDTH-1:0] edge_data_out_n3,
    output logic                  edge_valid_out_n0,
    output logic                  edge_valid_out_n1,
    output logic                  edge_valid_out_n2,
    output logic                  edge_valid_out_n3,
    
    output logic [DATA_WIDTH-1:0] edge_data_out_s0,
    output logic [DATA_WIDTH-1:0] edge_data_out_s1,
    output logic [DATA_WIDTH-1:0] edge_data_out_s2,
    output logic [DATA_WIDTH-1:0] edge_data_out_s3,
    output logic                  edge_valid_out_s0,
    output logic                  edge_valid_out_s1,
    output logic                  edge_valid_out_s2,
    output logic                  edge_valid_out_s3,
    
    output logic [DATA_WIDTH-1:0] edge_data_out_e0,
    output logic [DATA_WIDTH-1:0] edge_data_out_e1,
    output logic [DATA_WIDTH-1:0] edge_data_out_e2,
    output logic [DATA_WIDTH-1:0] edge_data_out_e3,
    output logic                  edge_valid_out_e0,
    output logic                  edge_valid_out_e1,
    output logic                  edge_valid_out_e2,
    output logic                  edge_valid_out_e3,
    
    output logic [DATA_WIDTH-1:0] edge_data_out_w0,
    output logic [DATA_WIDTH-1:0] edge_data_out_w1,
    output logic [DATA_WIDTH-1:0] edge_data_out_w2,
    output logic [DATA_WIDTH-1:0] edge_data_out_w3,
    output logic                  edge_valid_out_w0,
    output logic                  edge_valid_out_w1,
    output logic                  edge_valid_out_w2,
    output logic                  edge_valid_out_w3
);

    // =========================================================================
    // Internal interconnect signals
    // =========================================================================
    // PE outputs
    logic [DATA_WIDTH-1:0] pe_data_n_00, pe_data_n_01, pe_data_n_02, pe_data_n_03;
    logic [DATA_WIDTH-1:0] pe_data_n_10, pe_data_n_11, pe_data_n_12, pe_data_n_13;
    logic [DATA_WIDTH-1:0] pe_data_n_20, pe_data_n_21, pe_data_n_22, pe_data_n_23;
    logic [DATA_WIDTH-1:0] pe_data_n_30, pe_data_n_31, pe_data_n_32, pe_data_n_33;
    
    logic [DATA_WIDTH-1:0] pe_data_e_00, pe_data_e_01, pe_data_e_02, pe_data_e_03;
    logic [DATA_WIDTH-1:0] pe_data_e_10, pe_data_e_11, pe_data_e_12, pe_data_e_13;
    logic [DATA_WIDTH-1:0] pe_data_e_20, pe_data_e_21, pe_data_e_22, pe_data_e_23;
    logic [DATA_WIDTH-1:0] pe_data_e_30, pe_data_e_31, pe_data_e_32, pe_data_e_33;
    
    logic [DATA_WIDTH-1:0] pe_data_s_00, pe_data_s_01, pe_data_s_02, pe_data_s_03;
    logic [DATA_WIDTH-1:0] pe_data_s_10, pe_data_s_11, pe_data_s_12, pe_data_s_13;
    logic [DATA_WIDTH-1:0] pe_data_s_20, pe_data_s_21, pe_data_s_22, pe_data_s_23;
    logic [DATA_WIDTH-1:0] pe_data_s_30, pe_data_s_31, pe_data_s_32, pe_data_s_33;
    
    logic [DATA_WIDTH-1:0] pe_data_w_00, pe_data_w_01, pe_data_w_02, pe_data_w_03;
    logic [DATA_WIDTH-1:0] pe_data_w_10, pe_data_w_11, pe_data_w_12, pe_data_w_13;
    logic [DATA_WIDTH-1:0] pe_data_w_20, pe_data_w_21, pe_data_w_22, pe_data_w_23;
    logic [DATA_WIDTH-1:0] pe_data_w_30, pe_data_w_31, pe_data_w_32, pe_data_w_33;
    
    logic pe_valid_n_00, pe_valid_n_01, pe_valid_n_02, pe_valid_n_03;
    logic pe_valid_n_10, pe_valid_n_11, pe_valid_n_12, pe_valid_n_13;
    logic pe_valid_n_20, pe_valid_n_21, pe_valid_n_22, pe_valid_n_23;
    logic pe_valid_n_30, pe_valid_n_31, pe_valid_n_32, pe_valid_n_33;
    
    logic pe_valid_e_00, pe_valid_e_01, pe_valid_e_02, pe_valid_e_03;
    logic pe_valid_e_10, pe_valid_e_11, pe_valid_e_12, pe_valid_e_13;
    logic pe_valid_e_20, pe_valid_e_21, pe_valid_e_22, pe_valid_e_23;
    logic pe_valid_e_30, pe_valid_e_31, pe_valid_e_32, pe_valid_e_33;
    
    logic pe_valid_s_00, pe_valid_s_01, pe_valid_s_02, pe_valid_s_03;
    logic pe_valid_s_10, pe_valid_s_11, pe_valid_s_12, pe_valid_s_13;
    logic pe_valid_s_20, pe_valid_s_21, pe_valid_s_22, pe_valid_s_23;
    logic pe_valid_s_30, pe_valid_s_31, pe_valid_s_32, pe_valid_s_33;
    
    logic pe_valid_w_00, pe_valid_w_01, pe_valid_w_02, pe_valid_w_03;
    logic pe_valid_w_10, pe_valid_w_11, pe_valid_w_12, pe_valid_w_13;
    logic pe_valid_w_20, pe_valid_w_21, pe_valid_w_22, pe_valid_w_23;
    logic pe_valid_w_30, pe_valid_w_31, pe_valid_w_32, pe_valid_w_33;

    // =========================================================================
    // Row 0 PEs
    // =========================================================================
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_00 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_00), .config_valid(config_valid),
        .data_in_n(edge_data_in_n0), .data_in_e(pe_data_w_01), .data_in_s(pe_data_n_10), .data_in_w(edge_data_in_w0),
        .valid_in_n(edge_valid_in_n0), .valid_in_e(pe_valid_w_01), .valid_in_s(pe_valid_n_10), .valid_in_w(edge_valid_in_w0),
        .data_out_n(pe_data_n_00), .data_out_e(pe_data_e_00), .data_out_s(pe_data_s_00), .data_out_w(pe_data_w_00),
        .valid_out_n(pe_valid_n_00), .valid_out_e(pe_valid_e_00), .valid_out_s(pe_valid_s_00), .valid_out_w(pe_valid_w_00),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_01 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_01), .config_valid(config_valid),
        .data_in_n(edge_data_in_n1), .data_in_e(pe_data_w_02), .data_in_s(pe_data_n_11), .data_in_w(pe_data_e_00),
        .valid_in_n(edge_valid_in_n1), .valid_in_e(pe_valid_w_02), .valid_in_s(pe_valid_n_11), .valid_in_w(pe_valid_e_00),
        .data_out_n(pe_data_n_01), .data_out_e(pe_data_e_01), .data_out_s(pe_data_s_01), .data_out_w(pe_data_w_01),
        .valid_out_n(pe_valid_n_01), .valid_out_e(pe_valid_e_01), .valid_out_s(pe_valid_s_01), .valid_out_w(pe_valid_w_01),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_02 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_02), .config_valid(config_valid),
        .data_in_n(edge_data_in_n2), .data_in_e(pe_data_w_03), .data_in_s(pe_data_n_12), .data_in_w(pe_data_e_01),
        .valid_in_n(edge_valid_in_n2), .valid_in_e(pe_valid_w_03), .valid_in_s(pe_valid_n_12), .valid_in_w(pe_valid_e_01),
        .data_out_n(pe_data_n_02), .data_out_e(pe_data_e_02), .data_out_s(pe_data_s_02), .data_out_w(pe_data_w_02),
        .valid_out_n(pe_valid_n_02), .valid_out_e(pe_valid_e_02), .valid_out_s(pe_valid_s_02), .valid_out_w(pe_valid_w_02),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_03 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_03), .config_valid(config_valid),
        .data_in_n(edge_data_in_n3), .data_in_e(edge_data_in_e0), .data_in_s(pe_data_n_13), .data_in_w(pe_data_e_02),
        .valid_in_n(edge_valid_in_n3), .valid_in_e(edge_valid_in_e0), .valid_in_s(pe_valid_n_13), .valid_in_w(pe_valid_e_02),
        .data_out_n(pe_data_n_03), .data_out_e(pe_data_e_03), .data_out_s(pe_data_s_03), .data_out_w(pe_data_w_03),
        .valid_out_n(pe_valid_n_03), .valid_out_e(pe_valid_e_03), .valid_out_s(pe_valid_s_03), .valid_out_w(pe_valid_w_03),
        .data_out_local(), .valid_out_local()
    );

    // =========================================================================
    // Row 1 PEs
    // =========================================================================
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_10 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_10), .config_valid(config_valid),
        .data_in_n(pe_data_s_00), .data_in_e(pe_data_w_11), .data_in_s(pe_data_n_20), .data_in_w(edge_data_in_w1),
        .valid_in_n(pe_valid_s_00), .valid_in_e(pe_valid_w_11), .valid_in_s(pe_valid_n_20), .valid_in_w(edge_valid_in_w1),
        .data_out_n(pe_data_n_10), .data_out_e(pe_data_e_10), .data_out_s(pe_data_s_10), .data_out_w(pe_data_w_10),
        .valid_out_n(pe_valid_n_10), .valid_out_e(pe_valid_e_10), .valid_out_s(pe_valid_s_10), .valid_out_w(pe_valid_w_10),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_11 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_11), .config_valid(config_valid),
        .data_in_n(pe_data_s_01), .data_in_e(pe_data_w_12), .data_in_s(pe_data_n_21), .data_in_w(pe_data_e_10),
        .valid_in_n(pe_valid_s_01), .valid_in_e(pe_valid_w_12), .valid_in_s(pe_valid_n_21), .valid_in_w(pe_valid_e_10),
        .data_out_n(pe_data_n_11), .data_out_e(pe_data_e_11), .data_out_s(pe_data_s_11), .data_out_w(pe_data_w_11),
        .valid_out_n(pe_valid_n_11), .valid_out_e(pe_valid_e_11), .valid_out_s(pe_valid_s_11), .valid_out_w(pe_valid_w_11),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_12 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_12), .config_valid(config_valid),
        .data_in_n(pe_data_s_02), .data_in_e(pe_data_w_13), .data_in_s(pe_data_n_22), .data_in_w(pe_data_e_11),
        .valid_in_n(pe_valid_s_02), .valid_in_e(pe_valid_w_13), .valid_in_s(pe_valid_n_22), .valid_in_w(pe_valid_e_11),
        .data_out_n(pe_data_n_12), .data_out_e(pe_data_e_12), .data_out_s(pe_data_s_12), .data_out_w(pe_data_w_12),
        .valid_out_n(pe_valid_n_12), .valid_out_e(pe_valid_e_12), .valid_out_s(pe_valid_s_12), .valid_out_w(pe_valid_w_12),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_13 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_13), .config_valid(config_valid),
        .data_in_n(pe_data_s_03), .data_in_e(edge_data_in_e1), .data_in_s(pe_data_n_23), .data_in_w(pe_data_e_12),
        .valid_in_n(pe_valid_s_03), .valid_in_e(edge_valid_in_e1), .valid_in_s(pe_valid_n_23), .valid_in_w(pe_valid_e_12),
        .data_out_n(pe_data_n_13), .data_out_e(pe_data_e_13), .data_out_s(pe_data_s_13), .data_out_w(pe_data_w_13),
        .valid_out_n(pe_valid_n_13), .valid_out_e(pe_valid_e_13), .valid_out_s(pe_valid_s_13), .valid_out_w(pe_valid_w_13),
        .data_out_local(), .valid_out_local()
    );

    // =========================================================================
    // Row 2 PEs
    // =========================================================================
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_20 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_20), .config_valid(config_valid),
        .data_in_n(pe_data_s_10), .data_in_e(pe_data_w_21), .data_in_s(pe_data_n_30), .data_in_w(edge_data_in_w2),
        .valid_in_n(pe_valid_s_10), .valid_in_e(pe_valid_w_21), .valid_in_s(pe_valid_n_30), .valid_in_w(edge_valid_in_w2),
        .data_out_n(pe_data_n_20), .data_out_e(pe_data_e_20), .data_out_s(pe_data_s_20), .data_out_w(pe_data_w_20),
        .valid_out_n(pe_valid_n_20), .valid_out_e(pe_valid_e_20), .valid_out_s(pe_valid_s_20), .valid_out_w(pe_valid_w_20),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_21 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_21), .config_valid(config_valid),
        .data_in_n(pe_data_s_11), .data_in_e(pe_data_w_22), .data_in_s(pe_data_n_31), .data_in_w(pe_data_e_20),
        .valid_in_n(pe_valid_s_11), .valid_in_e(pe_valid_w_22), .valid_in_s(pe_valid_n_31), .valid_in_w(pe_valid_e_20),
        .data_out_n(pe_data_n_21), .data_out_e(pe_data_e_21), .data_out_s(pe_data_s_21), .data_out_w(pe_data_w_21),
        .valid_out_n(pe_valid_n_21), .valid_out_e(pe_valid_e_21), .valid_out_s(pe_valid_s_21), .valid_out_w(pe_valid_w_21),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_22 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_22), .config_valid(config_valid),
        .data_in_n(pe_data_s_12), .data_in_e(pe_data_w_23), .data_in_s(pe_data_n_32), .data_in_w(pe_data_e_21),
        .valid_in_n(pe_valid_s_12), .valid_in_e(pe_valid_w_23), .valid_in_s(pe_valid_n_32), .valid_in_w(pe_valid_e_21),
        .data_out_n(pe_data_n_22), .data_out_e(pe_data_e_22), .data_out_s(pe_data_s_22), .data_out_w(pe_data_w_22),
        .valid_out_n(pe_valid_n_22), .valid_out_e(pe_valid_e_22), .valid_out_s(pe_valid_s_22), .valid_out_w(pe_valid_w_22),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_23 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_23), .config_valid(config_valid),
        .data_in_n(pe_data_s_13), .data_in_e(edge_data_in_e2), .data_in_s(pe_data_n_33), .data_in_w(pe_data_e_22),
        .valid_in_n(pe_valid_s_13), .valid_in_e(edge_valid_in_e2), .valid_in_s(pe_valid_n_33), .valid_in_w(pe_valid_e_22),
        .data_out_n(pe_data_n_23), .data_out_e(pe_data_e_23), .data_out_s(pe_data_s_23), .data_out_w(pe_data_w_23),
        .valid_out_n(pe_valid_n_23), .valid_out_e(pe_valid_e_23), .valid_out_s(pe_valid_s_23), .valid_out_w(pe_valid_w_23),
        .data_out_local(), .valid_out_local()
    );

    // =========================================================================
    // Row 3 PEs
    // =========================================================================
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_30 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_30), .config_valid(config_valid),
        .data_in_n(pe_data_s_20), .data_in_e(pe_data_w_31), .data_in_s(edge_data_in_s0), .data_in_w(edge_data_in_w3),
        .valid_in_n(pe_valid_s_20), .valid_in_e(pe_valid_w_31), .valid_in_s(edge_valid_in_s0), .valid_in_w(edge_valid_in_w3),
        .data_out_n(pe_data_n_30), .data_out_e(pe_data_e_30), .data_out_s(pe_data_s_30), .data_out_w(pe_data_w_30),
        .valid_out_n(pe_valid_n_30), .valid_out_e(pe_valid_e_30), .valid_out_s(pe_valid_s_30), .valid_out_w(pe_valid_w_30),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_31 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_31), .config_valid(config_valid),
        .data_in_n(pe_data_s_21), .data_in_e(pe_data_w_32), .data_in_s(edge_data_in_s1), .data_in_w(pe_data_e_30),
        .valid_in_n(pe_valid_s_21), .valid_in_e(pe_valid_w_32), .valid_in_s(edge_valid_in_s1), .valid_in_w(pe_valid_e_30),
        .data_out_n(pe_data_n_31), .data_out_e(pe_data_e_31), .data_out_s(pe_data_s_31), .data_out_w(pe_data_w_31),
        .valid_out_n(pe_valid_n_31), .valid_out_e(pe_valid_e_31), .valid_out_s(pe_valid_s_31), .valid_out_w(pe_valid_w_31),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_32 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_32), .config_valid(config_valid),
        .data_in_n(pe_data_s_22), .data_in_e(pe_data_w_33), .data_in_s(edge_data_in_s2), .data_in_w(pe_data_e_31),
        .valid_in_n(pe_valid_s_22), .valid_in_e(pe_valid_w_33), .valid_in_s(edge_valid_in_s2), .valid_in_w(pe_valid_e_31),
        .data_out_n(pe_data_n_32), .data_out_e(pe_data_e_32), .data_out_s(pe_data_s_32), .data_out_w(pe_data_w_32),
        .valid_out_n(pe_valid_n_32), .valid_out_e(pe_valid_e_32), .valid_out_s(pe_valid_s_32), .valid_out_w(pe_valid_w_32),
        .data_out_local(), .valid_out_local()
    );
    
    cgra_pe #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(8), .SPM_DEPTH(SPM_DEPTH), .RF_DEPTH(RF_DEPTH)) pe_33 (
        .clk(clk), .rst_n(rst_n),
        .config_frame(config_frame_33), .config_valid(config_valid),
        .data_in_n(pe_data_s_23), .data_in_e(edge_data_in_e3), .data_in_s(edge_data_in_s3), .data_in_w(pe_data_e_32),
        .valid_in_n(pe_valid_s_23), .valid_in_e(edge_valid_in_e3), .valid_in_s(edge_valid_in_s3), .valid_in_w(pe_valid_e_32),
        .data_out_n(pe_data_n_33), .data_out_e(pe_data_e_33), .data_out_s(pe_data_s_33), .data_out_w(pe_data_w_33),
        .valid_out_n(pe_valid_n_33), .valid_out_e(pe_valid_e_33), .valid_out_s(pe_valid_s_33), .valid_out_w(pe_valid_w_33),
        .data_out_local(), .valid_out_local()
    );

    // =========================================================================
    // Edge outputs
    // =========================================================================
    assign edge_data_out_n0 = pe_data_n_00;
    assign edge_data_out_n1 = pe_data_n_01;
    assign edge_data_out_n2 = pe_data_n_02;
    assign edge_data_out_n3 = pe_data_n_03;
    assign edge_valid_out_n0 = pe_valid_n_00;
    assign edge_valid_out_n1 = pe_valid_n_01;
    assign edge_valid_out_n2 = pe_valid_n_02;
    assign edge_valid_out_n3 = pe_valid_n_03;
    
    assign edge_data_out_s0 = pe_data_s_30;
    assign edge_data_out_s1 = pe_data_s_31;
    assign edge_data_out_s2 = pe_data_s_32;
    assign edge_data_out_s3 = pe_data_s_33;
    assign edge_valid_out_s0 = pe_valid_s_30;
    assign edge_valid_out_s1 = pe_valid_s_31;
    assign edge_valid_out_s2 = pe_valid_s_32;
    assign edge_valid_out_s3 = pe_valid_s_33;
    
    assign edge_data_out_e0 = pe_data_e_03;
    assign edge_data_out_e1 = pe_data_e_13;
    assign edge_data_out_e2 = pe_data_e_23;
    assign edge_data_out_e3 = pe_data_e_33;
    assign edge_valid_out_e0 = pe_valid_e_03;
    assign edge_valid_out_e1 = pe_valid_e_13;
    assign edge_valid_out_e2 = pe_valid_e_23;
    assign edge_valid_out_e3 = pe_valid_e_33;
    
    assign edge_data_out_w0 = pe_data_w_00;
    assign edge_data_out_w1 = pe_data_w_10;
    assign edge_data_out_w2 = pe_data_w_20;
    assign edge_data_out_w3 = pe_data_w_30;
    assign edge_valid_out_w0 = pe_valid_w_00;
    assign edge_valid_out_w1 = pe_valid_w_10;
    assign edge_valid_out_w2 = pe_valid_w_20;
    assign edge_valid_out_w3 = pe_valid_w_30;

endmodule
