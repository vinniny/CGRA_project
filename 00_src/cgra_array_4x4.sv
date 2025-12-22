// ==============================================================================
// CGRA 4x4 Array - Mesh Broadcast Topology
// ==============================================================================
// 16 tiles in 4x4 mesh. Each tile wraps PE + Router.
// PE outputs broadcast to all 4 neighbors (mesh broadcast architecture).
//
// FEATURES:
//   - 16 Processing Elements with local config RAM
//   - Mesh broadcast: PE result → all 4 neighbors
//   - Edge inputs: West = Tile Memory banks, others = tie-off
//   - Edge outputs: synthesis_keep prevents optimization
//   - Multi-context: 16 config slots per PE (context_pc)
// ==============================================================================

module cgra_array_4x4 #(
    parameter DATA_WIDTH = 32,
    parameter COORD_WIDTH = 4,
    parameter PAYLOAD_WIDTH = 16,
    parameter ADDR_WIDTH = 4,
    parameter SPM_DEPTH = 256,
    parameter RF_DEPTH = 16,
    parameter CONTEXT_DEPTH = 16,
    parameter PC_WIDTH = 4
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
    
    // Multi-context interface (broadcast to all PEs)
    input  logic [PC_WIDTH-1:0] context_pc,
    input  logic                global_stall,
    
    // Config write interface (for writing to specific PE's config RAM)
    input  logic [PC_WIDTH-1:0] cfg_wr_addr,
    input  logic [63:0]         cfg_wr_data,
    input  logic [3:0]          cfg_wr_pe_sel,  // Which PE (0-15)
    input  logic                cfg_wr_en,

    // Edge inputs (from external) - North
    input  logic [DATA_WIDTH-1:0] edge_data_in_n0,
    input  logic [DATA_WIDTH-1:0] edge_data_in_n1,
    input  logic [DATA_WIDTH-1:0] edge_data_in_n2,
    input  logic [DATA_WIDTH-1:0] edge_data_in_n3,
    input  logic                  edge_valid_in_n0,
    input  logic                  edge_valid_in_n1,
    input  logic                  edge_valid_in_n2,
    input  logic                  edge_valid_in_n3,

    // Edge inputs (from external) - South
    input  logic [DATA_WIDTH-1:0] edge_data_in_s0,
    input  logic [DATA_WIDTH-1:0] edge_data_in_s1,
    input  logic [DATA_WIDTH-1:0] edge_data_in_s2,
    input  logic [DATA_WIDTH-1:0] edge_data_in_s3,
    input  logic                  edge_valid_in_s0,
    input  logic                  edge_valid_in_s1,
    input  logic                  edge_valid_in_s2,
    input  logic                  edge_valid_in_s3,

    // Edge inputs (from external) - East
    input  logic [DATA_WIDTH-1:0] edge_data_in_e0,
    input  logic [DATA_WIDTH-1:0] edge_data_in_e1,
    input  logic [DATA_WIDTH-1:0] edge_data_in_e2,
    input  logic [DATA_WIDTH-1:0] edge_data_in_e3,
    input  logic                  edge_valid_in_e0,
    input  logic                  edge_valid_in_e1,
    input  logic                  edge_valid_in_e2,
    input  logic                  edge_valid_in_e3,

    // Edge inputs (from external) - West
    input  logic [DATA_WIDTH-1:0] edge_data_in_w0,
    input  logic [DATA_WIDTH-1:0] edge_data_in_w1,
    input  logic [DATA_WIDTH-1:0] edge_data_in_w2,
    input  logic [DATA_WIDTH-1:0] edge_data_in_w3,
    input  logic                  edge_valid_in_w0,
    input  logic                  edge_valid_in_w1,
    input  logic                  edge_valid_in_w2,
    input  logic                  edge_valid_in_w3,

    // Edge outputs (to external) - North
    output logic [DATA_WIDTH-1:0] edge_data_out_n0,
    output logic [DATA_WIDTH-1:0] edge_data_out_n1,
    output logic [DATA_WIDTH-1:0] edge_data_out_n2,
    output logic [DATA_WIDTH-1:0] edge_data_out_n3,
    output logic                  edge_valid_out_n0,
    output logic                  edge_valid_out_n1,
    output logic                  edge_valid_out_n2,
    output logic                  edge_valid_out_n3,

    // Edge outputs (to external) - South
    output logic [DATA_WIDTH-1:0] edge_data_out_s0,
    output logic [DATA_WIDTH-1:0] edge_data_out_s1,
    output logic [DATA_WIDTH-1:0] edge_data_out_s2,
    output logic [DATA_WIDTH-1:0] edge_data_out_s3,
    output logic                  edge_valid_out_s0,
    output logic                  edge_valid_out_s1,
    output logic                  edge_valid_out_s2,
    output logic                  edge_valid_out_s3,

    // Edge outputs (to external) - East
    output logic [DATA_WIDTH-1:0] edge_data_out_e0,
    output logic [DATA_WIDTH-1:0] edge_data_out_e1,
    output logic [DATA_WIDTH-1:0] edge_data_out_e2,
    output logic [DATA_WIDTH-1:0] edge_data_out_e3,
    output logic                  edge_valid_out_e0,
    output logic                  edge_valid_out_e1,
    output logic                  edge_valid_out_e2,
    output logic                  edge_valid_out_e3,

    // Edge outputs (to external) - West
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
    // Inter-tile connection wires
    // =========================================================================
    // Naming convention: tile_YX_dir_data/valid/ready
    // Y = row (0-3), X = column (0-3)
    // dir = n (north), e (east), s (south), w (west)
    
    // -------------------------------------------------------------------------
    // Horizontal links (East-West connections)
    // -------------------------------------------------------------------------
    // Row 0: Tile(0,0) <-> Tile(0,1) <-> Tile(0,2) <-> Tile(0,3)
    logic [DATA_WIDTH-1:0] tile_00_e_data, tile_01_w_data, tile_01_e_data, tile_02_w_data;
    logic [DATA_WIDTH-1:0] tile_02_e_data, tile_03_w_data;
    logic tile_00_e_valid, tile_01_w_valid, tile_01_e_valid, tile_02_w_valid;
    logic tile_02_e_valid, tile_03_w_valid;
    logic tile_00_e_ready, tile_01_w_ready, tile_01_e_ready, tile_02_w_ready;
    logic tile_02_e_ready, tile_03_w_ready;
    
    // Row 1: Tile(1,0) <-> Tile(1,1) <-> Tile(1,2) <-> Tile(1,3)
    logic [DATA_WIDTH-1:0] tile_10_e_data, tile_11_w_data, tile_11_e_data, tile_12_w_data;
    logic [DATA_WIDTH-1:0] tile_12_e_data, tile_13_w_data;
    logic tile_10_e_valid, tile_11_w_valid, tile_11_e_valid, tile_12_w_valid;
    logic tile_12_e_valid, tile_13_w_valid;
    logic tile_10_e_ready, tile_11_w_ready, tile_11_e_ready, tile_12_w_ready;
    logic tile_12_e_ready, tile_13_w_ready;
    
    // Row 2: Tile(2,0) <-> Tile(2,1) <-> Tile(2,2) <-> Tile(2,3)
    logic [DATA_WIDTH-1:0] tile_20_e_data, tile_21_w_data, tile_21_e_data, tile_22_w_data;
    logic [DATA_WIDTH-1:0] tile_22_e_data, tile_23_w_data;
    logic tile_20_e_valid, tile_21_w_valid, tile_21_e_valid, tile_22_w_valid;
    logic tile_22_e_valid, tile_23_w_valid;
    logic tile_20_e_ready, tile_21_w_ready, tile_21_e_ready, tile_22_w_ready;
    logic tile_22_e_ready, tile_23_w_ready;
    
    // Row 3: Tile(3,0) <-> Tile(3,1) <-> Tile(3,2) <-> Tile(3,3)
    logic [DATA_WIDTH-1:0] tile_30_e_data, tile_31_w_data, tile_31_e_data, tile_32_w_data;
    logic [DATA_WIDTH-1:0] tile_32_e_data, tile_33_w_data;
    logic tile_30_e_valid, tile_31_w_valid, tile_31_e_valid, tile_32_w_valid;
    logic tile_32_e_valid, tile_33_w_valid;
    logic tile_30_e_ready, tile_31_w_ready, tile_31_e_ready, tile_32_w_ready;
    logic tile_32_e_ready, tile_33_w_ready;
    
    // -------------------------------------------------------------------------
    // Vertical links (North-South connections)
    // -------------------------------------------------------------------------
    // Column 0: Tile(0,0) <-> Tile(1,0) <-> Tile(2,0) <-> Tile(3,0)
    logic [DATA_WIDTH-1:0] tile_00_s_data, tile_10_n_data, tile_10_s_data, tile_20_n_data;
    logic [DATA_WIDTH-1:0] tile_20_s_data, tile_30_n_data;
    logic tile_00_s_valid, tile_10_n_valid, tile_10_s_valid, tile_20_n_valid;
    logic tile_20_s_valid, tile_30_n_valid;
    logic tile_00_s_ready, tile_10_n_ready, tile_10_s_ready, tile_20_n_ready;
    logic tile_20_s_ready, tile_30_n_ready;
    
    // Column 1: Tile(0,1) <-> Tile(1,1) <-> Tile(2,1) <-> Tile(3,1)
    logic [DATA_WIDTH-1:0] tile_01_s_data, tile_11_n_data, tile_11_s_data, tile_21_n_data;
    logic [DATA_WIDTH-1:0] tile_21_s_data, tile_31_n_data;
    logic tile_01_s_valid, tile_11_n_valid, tile_11_s_valid, tile_21_n_valid;
    logic tile_21_s_valid, tile_31_n_valid;
    logic tile_01_s_ready, tile_11_n_ready, tile_11_s_ready, tile_21_n_ready;
    logic tile_21_s_ready, tile_31_n_ready;
    
    // Column 2: Tile(0,2) <-> Tile(1,2) <-> Tile(2,2) <-> Tile(3,2)
    logic [DATA_WIDTH-1:0] tile_02_s_data, tile_12_n_data, tile_12_s_data, tile_22_n_data;
    logic [DATA_WIDTH-1:0] tile_22_s_data, tile_32_n_data;
    logic tile_02_s_valid, tile_12_n_valid, tile_12_s_valid, tile_22_n_valid;
    logic tile_22_s_valid, tile_32_n_valid;
    logic tile_02_s_ready, tile_12_n_ready, tile_12_s_ready, tile_22_n_ready;
    logic tile_22_s_ready, tile_32_n_ready;
    
    // Column 3: Tile(0,3) <-> Tile(1,3) <-> Tile(2,3) <-> Tile(3,3)
    logic [DATA_WIDTH-1:0] tile_03_s_data, tile_13_n_data, tile_13_s_data, tile_23_n_data;
    logic [DATA_WIDTH-1:0] tile_23_s_data, tile_33_n_data;
    logic tile_03_s_valid, tile_13_n_valid, tile_13_s_valid, tile_23_n_valid;
    logic tile_23_s_valid, tile_33_n_valid;
    logic tile_03_s_ready, tile_13_n_ready, tile_13_s_ready, tile_23_n_ready;
    logic tile_23_s_ready, tile_33_n_ready;
    
    // -------------------------------------------------------------------------
    // Edge output wires (from boundary tiles)
    // -------------------------------------------------------------------------
    // North edge outputs (from row 0)
    logic [DATA_WIDTH-1:0] tile_00_n_data, tile_01_n_data, tile_02_n_data, tile_03_n_data;
    logic tile_00_n_valid, tile_01_n_valid, tile_02_n_valid, tile_03_n_valid;
    
    // South edge outputs (from row 3)
    logic [DATA_WIDTH-1:0] tile_30_s_data, tile_31_s_data, tile_32_s_data, tile_33_s_data;
    logic tile_30_s_valid, tile_31_s_valid, tile_32_s_valid, tile_33_s_valid;
    
    // West edge outputs (from column 0)
    logic [DATA_WIDTH-1:0] tile_00_w_data, tile_10_w_data, tile_20_w_data, tile_30_w_data;
    logic tile_00_w_valid, tile_10_w_valid, tile_20_w_valid, tile_30_w_valid;
    
    // East edge outputs (from column 3)
    logic [DATA_WIDTH-1:0] tile_03_e_data, tile_13_e_data, tile_23_e_data, tile_33_e_data;
    logic tile_03_e_valid, tile_13_e_valid, tile_23_e_valid, tile_33_e_valid;
    
    // Edge ready signals (directly from tiles for boundary)
    logic tile_00_n_ready, tile_01_n_ready, tile_02_n_ready, tile_03_n_ready;
    logic tile_30_s_ready, tile_31_s_ready, tile_32_s_ready, tile_33_s_ready;
    logic tile_00_w_ready, tile_10_w_ready, tile_20_w_ready, tile_30_w_ready;
    logic tile_03_e_ready, tile_13_e_ready, tile_23_e_ready, tile_33_e_ready;

    // =========================================================================
    // Per-PE Config Write Enable Decode
    // =========================================================================
    // Decode cfg_wr_pe_sel to generate individual write enables per PE
    logic cfg_wr_en_00, cfg_wr_en_01, cfg_wr_en_02, cfg_wr_en_03;
    logic cfg_wr_en_10, cfg_wr_en_11, cfg_wr_en_12, cfg_wr_en_13;
    logic cfg_wr_en_20, cfg_wr_en_21, cfg_wr_en_22, cfg_wr_en_23;
    logic cfg_wr_en_30, cfg_wr_en_31, cfg_wr_en_32, cfg_wr_en_33;
    
    assign cfg_wr_en_00 = cfg_wr_en && (cfg_wr_pe_sel == 4'd0);
    assign cfg_wr_en_01 = cfg_wr_en && (cfg_wr_pe_sel == 4'd1);
    assign cfg_wr_en_02 = cfg_wr_en && (cfg_wr_pe_sel == 4'd2);
    assign cfg_wr_en_03 = cfg_wr_en && (cfg_wr_pe_sel == 4'd3);
    assign cfg_wr_en_10 = cfg_wr_en && (cfg_wr_pe_sel == 4'd4);
    assign cfg_wr_en_11 = cfg_wr_en && (cfg_wr_pe_sel == 4'd5);
    assign cfg_wr_en_12 = cfg_wr_en && (cfg_wr_pe_sel == 4'd6);
    assign cfg_wr_en_13 = cfg_wr_en && (cfg_wr_pe_sel == 4'd7);
    assign cfg_wr_en_20 = cfg_wr_en && (cfg_wr_pe_sel == 4'd8);
    assign cfg_wr_en_21 = cfg_wr_en && (cfg_wr_pe_sel == 4'd9);
    assign cfg_wr_en_22 = cfg_wr_en && (cfg_wr_pe_sel == 4'd10);
    assign cfg_wr_en_23 = cfg_wr_en && (cfg_wr_pe_sel == 4'd11);
    assign cfg_wr_en_30 = cfg_wr_en && (cfg_wr_pe_sel == 4'd12);
    assign cfg_wr_en_31 = cfg_wr_en && (cfg_wr_pe_sel == 4'd13);
    assign cfg_wr_en_32 = cfg_wr_en && (cfg_wr_pe_sel == 4'd14);
    assign cfg_wr_en_33 = cfg_wr_en && (cfg_wr_pe_sel == 4'd15);

    // =========================================================================
    // Tile Instantiations - Row 0
    // =========================================================================
    
    // Tile (0,0) - Top-left corner
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(0),
        .Y_COORD(0),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_00 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_00),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_00),
        // North - external edge
        .data_in_n(edge_data_in_n0),
        .valid_in_n(edge_valid_in_n0),
        .ready_out_n(tile_00_n_ready),
        .data_out_n(tile_00_n_data),
        .valid_out_n(tile_00_n_valid),
        .ready_in_n(1'b1),
        // East - to tile(0,1)
        .data_in_e(tile_01_w_data),
        .valid_in_e(tile_01_w_valid),
        .ready_out_e(tile_00_e_ready),
        .data_out_e(tile_00_e_data),
        .valid_out_e(tile_00_e_valid),
        .ready_in_e(tile_01_w_ready),
        // South - to tile(1,0)
        .data_in_s(tile_10_n_data),
        .valid_in_s(tile_10_n_valid),
        .ready_out_s(tile_00_s_ready),
        .data_out_s(tile_00_s_data),
        .valid_out_s(tile_00_s_valid),
        .ready_in_s(tile_10_n_ready),
        // West - external edge
        .data_in_w(edge_data_in_w0),
        .valid_in_w(edge_valid_in_w0),
        .ready_out_w(tile_00_w_ready),
        .data_out_w(tile_00_w_data),
        .valid_out_w(tile_00_w_valid),
        .ready_in_w(1'b1)
    );
    
    // Tile (0,1)
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(1),
        .Y_COORD(0),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_01 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_01),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_01),
        // North - external edge
        .data_in_n(edge_data_in_n1),
        .valid_in_n(edge_valid_in_n1),
        .ready_out_n(tile_01_n_ready),
        .data_out_n(tile_01_n_data),
        .valid_out_n(tile_01_n_valid),
        .ready_in_n(1'b1),
        // East - to tile(0,2)
        .data_in_e(tile_02_w_data),
        .valid_in_e(tile_02_w_valid),
        .ready_out_e(tile_01_e_ready),
        .data_out_e(tile_01_e_data),
        .valid_out_e(tile_01_e_valid),
        .ready_in_e(tile_02_w_ready),
        // South - to tile(1,1)
        .data_in_s(tile_11_n_data),
        .valid_in_s(tile_11_n_valid),
        .ready_out_s(tile_01_s_ready),
        .data_out_s(tile_01_s_data),
        .valid_out_s(tile_01_s_valid),
        .ready_in_s(tile_11_n_ready),
        // West - to tile(0,0)
        .data_in_w(tile_00_e_data),
        .valid_in_w(tile_00_e_valid),
        .ready_out_w(tile_01_w_ready),
        .data_out_w(tile_01_w_data),
        .valid_out_w(tile_01_w_valid),
        .ready_in_w(tile_00_e_ready)
    );
    
    // Tile (0,2)
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(2),
        .Y_COORD(0),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_02 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_02),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_02),
        // North - external edge
        .data_in_n(edge_data_in_n2),
        .valid_in_n(edge_valid_in_n2),
        .ready_out_n(tile_02_n_ready),
        .data_out_n(tile_02_n_data),
        .valid_out_n(tile_02_n_valid),
        .ready_in_n(1'b1),
        // East - to tile(0,3)
        .data_in_e(tile_03_w_data),
        .valid_in_e(tile_03_w_valid),
        .ready_out_e(tile_02_e_ready),
        .data_out_e(tile_02_e_data),
        .valid_out_e(tile_02_e_valid),
        .ready_in_e(tile_03_w_ready),
        // South - to tile(1,2)
        .data_in_s(tile_12_n_data),
        .valid_in_s(tile_12_n_valid),
        .ready_out_s(tile_02_s_ready),
        .data_out_s(tile_02_s_data),
        .valid_out_s(tile_02_s_valid),
        .ready_in_s(tile_12_n_ready),
        // West - to tile(0,1)
        .data_in_w(tile_01_e_data),
        .valid_in_w(tile_01_e_valid),
        .ready_out_w(tile_02_w_ready),
        .data_out_w(tile_02_w_data),
        .valid_out_w(tile_02_w_valid),
        .ready_in_w(tile_01_e_ready)
    );
    
    // Tile (0,3) - Top-right corner
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(3),
        .Y_COORD(0),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_03 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_03),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_03),
        // North - external edge
        .data_in_n(edge_data_in_n3),
        .valid_in_n(edge_valid_in_n3),
        .ready_out_n(tile_03_n_ready),
        .data_out_n(tile_03_n_data),
        .valid_out_n(tile_03_n_valid),
        .ready_in_n(1'b1),
        // East - external edge
        .data_in_e(edge_data_in_e0),
        .valid_in_e(edge_valid_in_e0),
        .ready_out_e(tile_03_e_ready),
        .data_out_e(tile_03_e_data),
        .valid_out_e(tile_03_e_valid),
        .ready_in_e(1'b1),
        // South - to tile(1,3)
        .data_in_s(tile_13_n_data),
        .valid_in_s(tile_13_n_valid),
        .ready_out_s(tile_03_s_ready),
        .data_out_s(tile_03_s_data),
        .valid_out_s(tile_03_s_valid),
        .ready_in_s(tile_13_n_ready),
        // West - to tile(0,2)
        .data_in_w(tile_02_e_data),
        .valid_in_w(tile_02_e_valid),
        .ready_out_w(tile_03_w_ready),
        .data_out_w(tile_03_w_data),
        .valid_out_w(tile_03_w_valid),
        .ready_in_w(tile_02_e_ready)
    );

    // =========================================================================
    // Tile Instantiations - Row 1
    // =========================================================================
    
    // Tile (1,0) - Left edge
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(0),
        .Y_COORD(1),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_10 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_10),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_10),
        // North - to tile(0,0)
        .data_in_n(tile_00_s_data),
        .valid_in_n(tile_00_s_valid),
        .ready_out_n(tile_10_n_ready),
        .data_out_n(tile_10_n_data),
        .valid_out_n(tile_10_n_valid),
        .ready_in_n(tile_00_s_ready),
        // East - to tile(1,1)
        .data_in_e(tile_11_w_data),
        .valid_in_e(tile_11_w_valid),
        .ready_out_e(tile_10_e_ready),
        .data_out_e(tile_10_e_data),
        .valid_out_e(tile_10_e_valid),
        .ready_in_e(tile_11_w_ready),
        // South - to tile(2,0)
        .data_in_s(tile_20_n_data),
        .valid_in_s(tile_20_n_valid),
        .ready_out_s(tile_10_s_ready),
        .data_out_s(tile_10_s_data),
        .valid_out_s(tile_10_s_valid),
        .ready_in_s(tile_20_n_ready),
        // West - external edge
        .data_in_w(edge_data_in_w1),
        .valid_in_w(edge_valid_in_w1),
        .ready_out_w(tile_10_w_ready),
        .data_out_w(tile_10_w_data),
        .valid_out_w(tile_10_w_valid),
        .ready_in_w(1'b1)
    );
    
    // Tile (1,1) - Internal
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(1),
        .Y_COORD(1),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_11 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_11),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_11),
        // North - to tile(0,1)
        .data_in_n(tile_01_s_data),
        .valid_in_n(tile_01_s_valid),
        .ready_out_n(tile_11_n_ready),
        .data_out_n(tile_11_n_data),
        .valid_out_n(tile_11_n_valid),
        .ready_in_n(tile_01_s_ready),
        // East - to tile(1,2)
        .data_in_e(tile_12_w_data),
        .valid_in_e(tile_12_w_valid),
        .ready_out_e(tile_11_e_ready),
        .data_out_e(tile_11_e_data),
        .valid_out_e(tile_11_e_valid),
        .ready_in_e(tile_12_w_ready),
        // South - to tile(2,1)
        .data_in_s(tile_21_n_data),
        .valid_in_s(tile_21_n_valid),
        .ready_out_s(tile_11_s_ready),
        .data_out_s(tile_11_s_data),
        .valid_out_s(tile_11_s_valid),
        .ready_in_s(tile_21_n_ready),
        // West - to tile(1,0)
        .data_in_w(tile_10_e_data),
        .valid_in_w(tile_10_e_valid),
        .ready_out_w(tile_11_w_ready),
        .data_out_w(tile_11_w_data),
        .valid_out_w(tile_11_w_valid),
        .ready_in_w(tile_10_e_ready)
    );
    
    // Tile (1,2) - Internal
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(2),
        .Y_COORD(1),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_12 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_12),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_12),
        // North - to tile(0,2)
        .data_in_n(tile_02_s_data),
        .valid_in_n(tile_02_s_valid),
        .ready_out_n(tile_12_n_ready),
        .data_out_n(tile_12_n_data),
        .valid_out_n(tile_12_n_valid),
        .ready_in_n(tile_02_s_ready),
        // East - to tile(1,3)
        .data_in_e(tile_13_w_data),
        .valid_in_e(tile_13_w_valid),
        .ready_out_e(tile_12_e_ready),
        .data_out_e(tile_12_e_data),
        .valid_out_e(tile_12_e_valid),
        .ready_in_e(tile_13_w_ready),
        // South - to tile(2,2)
        .data_in_s(tile_22_n_data),
        .valid_in_s(tile_22_n_valid),
        .ready_out_s(tile_12_s_ready),
        .data_out_s(tile_12_s_data),
        .valid_out_s(tile_12_s_valid),
        .ready_in_s(tile_22_n_ready),
        // West - to tile(1,1)
        .data_in_w(tile_11_e_data),
        .valid_in_w(tile_11_e_valid),
        .ready_out_w(tile_12_w_ready),
        .data_out_w(tile_12_w_data),
        .valid_out_w(tile_12_w_valid),
        .ready_in_w(tile_11_e_ready)
    );
    
    // Tile (1,3) - Right edge
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(3),
        .Y_COORD(1),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_13 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_13),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_13),
        // North - to tile(0,3)
        .data_in_n(tile_03_s_data),
        .valid_in_n(tile_03_s_valid),
        .ready_out_n(tile_13_n_ready),
        .data_out_n(tile_13_n_data),
        .valid_out_n(tile_13_n_valid),
        .ready_in_n(tile_03_s_ready),
        // East - external edge
        .data_in_e(edge_data_in_e1),
        .valid_in_e(edge_valid_in_e1),
        .ready_out_e(tile_13_e_ready),
        .data_out_e(tile_13_e_data),
        .valid_out_e(tile_13_e_valid),
        .ready_in_e(1'b1),
        // South - to tile(2,3)
        .data_in_s(tile_23_n_data),
        .valid_in_s(tile_23_n_valid),
        .ready_out_s(tile_13_s_ready),
        .data_out_s(tile_13_s_data),
        .valid_out_s(tile_13_s_valid),
        .ready_in_s(tile_23_n_ready),
        // West - to tile(1,2)
        .data_in_w(tile_12_e_data),
        .valid_in_w(tile_12_e_valid),
        .ready_out_w(tile_13_w_ready),
        .data_out_w(tile_13_w_data),
        .valid_out_w(tile_13_w_valid),
        .ready_in_w(tile_12_e_ready)
    );

    // =========================================================================
    // Tile Instantiations - Row 2
    // =========================================================================
    
    // Tile (2,0) - Left edge
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(0),
        .Y_COORD(2),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_20 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_20),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_20),
        // North - to tile(1,0)
        .data_in_n(tile_10_s_data),
        .valid_in_n(tile_10_s_valid),
        .ready_out_n(tile_20_n_ready),
        .data_out_n(tile_20_n_data),
        .valid_out_n(tile_20_n_valid),
        .ready_in_n(tile_10_s_ready),
        // East - to tile(2,1)
        .data_in_e(tile_21_w_data),
        .valid_in_e(tile_21_w_valid),
        .ready_out_e(tile_20_e_ready),
        .data_out_e(tile_20_e_data),
        .valid_out_e(tile_20_e_valid),
        .ready_in_e(tile_21_w_ready),
        // South - to tile(3,0)
        .data_in_s(tile_30_n_data),
        .valid_in_s(tile_30_n_valid),
        .ready_out_s(tile_20_s_ready),
        .data_out_s(tile_20_s_data),
        .valid_out_s(tile_20_s_valid),
        .ready_in_s(tile_30_n_ready),
        // West - external edge
        .data_in_w(edge_data_in_w2),
        .valid_in_w(edge_valid_in_w2),
        .ready_out_w(tile_20_w_ready),
        .data_out_w(tile_20_w_data),
        .valid_out_w(tile_20_w_valid),
        .ready_in_w(1'b1)
    );
    
    // Tile (2,1) - Internal
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(1),
        .Y_COORD(2),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_21 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_21),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_21),
        // North - to tile(1,1)
        .data_in_n(tile_11_s_data),
        .valid_in_n(tile_11_s_valid),
        .ready_out_n(tile_21_n_ready),
        .data_out_n(tile_21_n_data),
        .valid_out_n(tile_21_n_valid),
        .ready_in_n(tile_11_s_ready),
        // East - to tile(2,2)
        .data_in_e(tile_22_w_data),
        .valid_in_e(tile_22_w_valid),
        .ready_out_e(tile_21_e_ready),
        .data_out_e(tile_21_e_data),
        .valid_out_e(tile_21_e_valid),
        .ready_in_e(tile_22_w_ready),
        // South - to tile(3,1)
        .data_in_s(tile_31_n_data),
        .valid_in_s(tile_31_n_valid),
        .ready_out_s(tile_21_s_ready),
        .data_out_s(tile_21_s_data),
        .valid_out_s(tile_21_s_valid),
        .ready_in_s(tile_31_n_ready),
        // West - to tile(2,0)
        .data_in_w(tile_20_e_data),
        .valid_in_w(tile_20_e_valid),
        .ready_out_w(tile_21_w_ready),
        .data_out_w(tile_21_w_data),
        .valid_out_w(tile_21_w_valid),
        .ready_in_w(tile_20_e_ready)
    );
    
    // Tile (2,2) - Internal
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(2),
        .Y_COORD(2),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_22 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_22),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_22),
        // North - to tile(1,2)
        .data_in_n(tile_12_s_data),
        .valid_in_n(tile_12_s_valid),
        .ready_out_n(tile_22_n_ready),
        .data_out_n(tile_22_n_data),
        .valid_out_n(tile_22_n_valid),
        .ready_in_n(tile_12_s_ready),
        // East - to tile(2,3)
        .data_in_e(tile_23_w_data),
        .valid_in_e(tile_23_w_valid),
        .ready_out_e(tile_22_e_ready),
        .data_out_e(tile_22_e_data),
        .valid_out_e(tile_22_e_valid),
        .ready_in_e(tile_23_w_ready),
        // South - to tile(3,2)
        .data_in_s(tile_32_n_data),
        .valid_in_s(tile_32_n_valid),
        .ready_out_s(tile_22_s_ready),
        .data_out_s(tile_22_s_data),
        .valid_out_s(tile_22_s_valid),
        .ready_in_s(tile_32_n_ready),
        // West - to tile(2,1)
        .data_in_w(tile_21_e_data),
        .valid_in_w(tile_21_e_valid),
        .ready_out_w(tile_22_w_ready),
        .data_out_w(tile_22_w_data),
        .valid_out_w(tile_22_w_valid),
        .ready_in_w(tile_21_e_ready)
    );
    
    // Tile (2,3) - Right edge
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(3),
        .Y_COORD(2),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_23 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_23),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_23),
        // North - to tile(1,3)
        .data_in_n(tile_13_s_data),
        .valid_in_n(tile_13_s_valid),
        .ready_out_n(tile_23_n_ready),
        .data_out_n(tile_23_n_data),
        .valid_out_n(tile_23_n_valid),
        .ready_in_n(tile_13_s_ready),
        // East - external edge
        .data_in_e(edge_data_in_e2),
        .valid_in_e(edge_valid_in_e2),
        .ready_out_e(tile_23_e_ready),
        .data_out_e(tile_23_e_data),
        .valid_out_e(tile_23_e_valid),
        .ready_in_e(1'b1),
        // South - to tile(3,3)
        .data_in_s(tile_33_n_data),
        .valid_in_s(tile_33_n_valid),
        .ready_out_s(tile_23_s_ready),
        .data_out_s(tile_23_s_data),
        .valid_out_s(tile_23_s_valid),
        .ready_in_s(tile_33_n_ready),
        // West - to tile(2,2)
        .data_in_w(tile_22_e_data),
        .valid_in_w(tile_22_e_valid),
        .ready_out_w(tile_23_w_ready),
        .data_out_w(tile_23_w_data),
        .valid_out_w(tile_23_w_valid),
        .ready_in_w(tile_22_e_ready)
    );

    // =========================================================================
    // Tile Instantiations - Row 3 (Bottom row)
    // =========================================================================
    
    // Tile (3,0) - Bottom-left corner
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(0),
        .Y_COORD(3),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_30 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_30),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_30),
        // North - to tile(2,0)
        .data_in_n(tile_20_s_data),
        .valid_in_n(tile_20_s_valid),
        .ready_out_n(tile_30_n_ready),
        .data_out_n(tile_30_n_data),
        .valid_out_n(tile_30_n_valid),
        .ready_in_n(tile_20_s_ready),
        // East - to tile(3,1)
        .data_in_e(tile_31_w_data),
        .valid_in_e(tile_31_w_valid),
        .ready_out_e(tile_30_e_ready),
        .data_out_e(tile_30_e_data),
        .valid_out_e(tile_30_e_valid),
        .ready_in_e(tile_31_w_ready),
        // South - external edge
        .data_in_s(edge_data_in_s0),
        .valid_in_s(edge_valid_in_s0),
        .ready_out_s(tile_30_s_ready),
        .data_out_s(tile_30_s_data),
        .valid_out_s(tile_30_s_valid),
        .ready_in_s(1'b1),
        // West - external edge
        .data_in_w(edge_data_in_w3),
        .valid_in_w(edge_valid_in_w3),
        .ready_out_w(tile_30_w_ready),
        .data_out_w(tile_30_w_data),
        .valid_out_w(tile_30_w_valid),
        .ready_in_w(1'b1)
    );
    
    // Tile (3,1) - Bottom edge
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(1),
        .Y_COORD(3),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_31 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_31),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_31),
        // North - to tile(2,1)
        .data_in_n(tile_21_s_data),
        .valid_in_n(tile_21_s_valid),
        .ready_out_n(tile_31_n_ready),
        .data_out_n(tile_31_n_data),
        .valid_out_n(tile_31_n_valid),
        .ready_in_n(tile_21_s_ready),
        // East - to tile(3,2)
        .data_in_e(tile_32_w_data),
        .valid_in_e(tile_32_w_valid),
        .ready_out_e(tile_31_e_ready),
        .data_out_e(tile_31_e_data),
        .valid_out_e(tile_31_e_valid),
        .ready_in_e(tile_32_w_ready),
        // South - external edge
        .data_in_s(edge_data_in_s1),
        .valid_in_s(edge_valid_in_s1),
        .ready_out_s(tile_31_s_ready),
        .data_out_s(tile_31_s_data),
        .valid_out_s(tile_31_s_valid),
        .ready_in_s(1'b1),
        // West - to tile(3,0)
        .data_in_w(tile_30_e_data),
        .valid_in_w(tile_30_e_valid),
        .ready_out_w(tile_31_w_ready),
        .data_out_w(tile_31_w_data),
        .valid_out_w(tile_31_w_valid),
        .ready_in_w(tile_30_e_ready)
    );
    
    // Tile (3,2) - Bottom edge
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(2),
        .Y_COORD(3),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_32 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_32),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_32),
        // North - to tile(2,2)
        .data_in_n(tile_22_s_data),
        .valid_in_n(tile_22_s_valid),
        .ready_out_n(tile_32_n_ready),
        .data_out_n(tile_32_n_data),
        .valid_out_n(tile_32_n_valid),
        .ready_in_n(tile_22_s_ready),
        // East - to tile(3,3)
        .data_in_e(tile_33_w_data),
        .valid_in_e(tile_33_w_valid),
        .ready_out_e(tile_32_e_ready),
        .data_out_e(tile_32_e_data),
        .valid_out_e(tile_32_e_valid),
        .ready_in_e(tile_33_w_ready),
        // South - external edge
        .data_in_s(edge_data_in_s2),
        .valid_in_s(edge_valid_in_s2),
        .ready_out_s(tile_32_s_ready),
        .data_out_s(tile_32_s_data),
        .valid_out_s(tile_32_s_valid),
        .ready_in_s(1'b1),
        // West - to tile(3,1)
        .data_in_w(tile_31_e_data),
        .valid_in_w(tile_31_e_valid),
        .ready_out_w(tile_32_w_ready),
        .data_out_w(tile_32_w_data),
        .valid_out_w(tile_32_w_valid),
        .ready_in_w(tile_31_e_ready)
    );
    
    // Tile (3,3) - Bottom-right corner
    cgra_tile #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .X_COORD(3),
        .Y_COORD(3),
        .CONTEXT_DEPTH(CONTEXT_DEPTH),
        .PC_WIDTH(PC_WIDTH)
    ) u_tile_33 (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame_33),
        .config_valid(config_valid),
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en_33),
        // North - to tile(2,3)
        .data_in_n(tile_23_s_data),
        .valid_in_n(tile_23_s_valid),
        .ready_out_n(tile_33_n_ready),
        .data_out_n(tile_33_n_data),
        .valid_out_n(tile_33_n_valid),
        .ready_in_n(tile_23_s_ready),
        // East - external edge
        .data_in_e(edge_data_in_e3),
        .valid_in_e(edge_valid_in_e3),
        .ready_out_e(tile_33_e_ready),
        .data_out_e(tile_33_e_data),
        .valid_out_e(tile_33_e_valid),
        .ready_in_e(1'b1),
        // South - external edge
        .data_in_s(edge_data_in_s3),
        .valid_in_s(edge_valid_in_s3),
        .ready_out_s(tile_33_s_ready),
        .data_out_s(tile_33_s_data),
        .valid_out_s(tile_33_s_valid),
        .ready_in_s(1'b1),
        // West - to tile(3,2)
        .data_in_w(tile_32_e_data),
        .valid_in_w(tile_32_e_valid),
        .ready_out_w(tile_33_w_ready),
        .data_out_w(tile_33_w_data),
        .valid_out_w(tile_33_w_valid),
        .ready_in_w(tile_32_e_ready)
    );

    // =========================================================================
    // Edge Output Assignments
    // =========================================================================
    
    // North edge outputs (from row 0 tiles going north)
    assign edge_data_out_n0  = tile_00_n_data;
    assign edge_valid_out_n0 = tile_00_n_valid;
    assign edge_data_out_n1  = tile_01_n_data;
    assign edge_valid_out_n1 = tile_01_n_valid;
    assign edge_data_out_n2  = tile_02_n_data;
    assign edge_valid_out_n2 = tile_02_n_valid;
    assign edge_data_out_n3  = tile_03_n_data;
    assign edge_valid_out_n3 = tile_03_n_valid;
    
    // South edge outputs (from row 3 tiles going south)
    assign edge_data_out_s0  = tile_30_s_data;
    assign edge_valid_out_s0 = tile_30_s_valid;
    assign edge_data_out_s1  = tile_31_s_data;
    assign edge_valid_out_s1 = tile_31_s_valid;
    assign edge_data_out_s2  = tile_32_s_data;
    assign edge_valid_out_s2 = tile_32_s_valid;
    assign edge_data_out_s3  = tile_33_s_data;
    assign edge_valid_out_s3 = tile_33_s_valid;
    
    // East edge outputs (from column 3 tiles going east)
    assign edge_data_out_e0  = tile_03_e_data;
    assign edge_valid_out_e0 = tile_03_e_valid;
    assign edge_data_out_e1  = tile_13_e_data;
    assign edge_valid_out_e1 = tile_13_e_valid;
    assign edge_data_out_e2  = tile_23_e_data;
    assign edge_valid_out_e2 = tile_23_e_valid;
    assign edge_data_out_e3  = tile_33_e_data;
    assign edge_valid_out_e3 = tile_33_e_valid;
    
    // West edge outputs (from column 0 tiles going west)
    assign edge_data_out_w0  = tile_00_w_data;
    assign edge_valid_out_w0 = tile_00_w_valid;
    assign edge_data_out_w1  = tile_10_w_data;
    assign edge_valid_out_w1 = tile_10_w_valid;
    assign edge_data_out_w2  = tile_20_w_data;
    assign edge_valid_out_w2 = tile_20_w_valid;
    assign edge_data_out_w3  = tile_30_w_data;
    assign edge_valid_out_w3 = tile_30_w_valid;

endmodule
