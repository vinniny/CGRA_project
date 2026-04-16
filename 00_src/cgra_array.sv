// ==============================================================================
// CGRA Parameterized Array — Mesh Broadcast Topology
// ==============================================================================
// N×M tiles in a parameterized mesh. Each tile wraps PE + Router.
// PE outputs broadcast to all 4 neighbors (mesh broadcast architecture).
//
// Replaces the hardcoded cgra_array_4x4.sv with generate blocks.
// Default ROWS=4, COLS=4 produces identical behavior.
//
// WIRING CONVENTION:
//   Horizontal: tile(y,x).data_out_e → tile(y,x+1).data_in_w
//   Vertical:   tile(y,x).data_out_s → tile(y+1,x).data_in_n
// ==============================================================================

module cgra_array #(
    parameter ROWS          = 4,
    parameter COLS          = 4,
    parameter DATA_WIDTH    = 32,
    parameter COORD_WIDTH   = 4,
    parameter ADDR_WIDTH    = 4,
    parameter SPM_DEPTH     = 256,
    parameter RF_DEPTH      = 16,
    parameter CONTEXT_DEPTH = 16,
    parameter PC_WIDTH      = 4,
    parameter NUM_PES       = ROWS * COLS
)(
    input  logic clk,
    input  logic rst_n,

    // Configuration (unused in BRAM mode — PEs use internal config RAM)
    input  logic [63:0] config_frame [0:NUM_PES-1],
    input  logic        config_valid,

    // Multi-context interface (broadcast to all PEs)
    input  logic [PC_WIDTH-1:0] context_pc,
    input  logic                global_stall,

    // Config write interface (targeted per-PE)
    input  logic [PC_WIDTH-1:0]              cfg_wr_addr,
    input  logic [63:0]                      cfg_wr_data,
    input  logic [$clog2(NUM_PES)-1:0]       cfg_wr_pe_sel,
    input  logic                             cfg_wr_en,

    // Edge inputs — North/South/East (tied off at top level; West from Tile Memory)
    input  logic [DATA_WIDTH-1:0] edge_data_in_n  [0:COLS-1],
    input  logic [DATA_WIDTH-1:0] edge_data_in_s  [0:COLS-1],
    input  logic [DATA_WIDTH-1:0] edge_data_in_e  [0:ROWS-1],

    // Edge inputs — West (one per row, from Tile Memory)
    input  logic [DATA_WIDTH-1:0] edge_data_in_w  [0:ROWS-1],

    // Edge outputs — North (one per column)
    output logic [DATA_WIDTH-1:0] edge_data_out_n  [0:COLS-1],
    output logic                  edge_valid_out_n [0:COLS-1],

    // Edge outputs — South (one per column)
    output logic [DATA_WIDTH-1:0] edge_data_out_s  [0:COLS-1],
    output logic                  edge_valid_out_s [0:COLS-1],

    // Edge outputs — East (one per row)
    output logic [DATA_WIDTH-1:0] edge_data_out_e  [0:ROWS-1],
    output logic                  edge_valid_out_e [0:ROWS-1],

    // Edge outputs — West (one per row)
    output logic [DATA_WIDTH-1:0] edge_data_out_w  [0:ROWS-1],
    output logic                  edge_valid_out_w [0:ROWS-1],

    // B4: Branch output from PE[0][0] (designated branch source)
    output logic [PC_WIDTH-1:0]   branch_target_o,
    output logic                  branch_taken_o
);

    // =========================================================================
    // Internal Mesh Wiring — Per-Tile Outputs
    // =========================================================================
    // Each tile has 4 outputs (N/E/S/W data + valid)
    logic [DATA_WIDTH-1:0] tile_out_n_data  [0:ROWS-1][0:COLS-1];
    logic                  tile_out_n_valid [0:ROWS-1][0:COLS-1];
    logic [DATA_WIDTH-1:0] tile_out_e_data  [0:ROWS-1][0:COLS-1];
    logic                  tile_out_e_valid [0:ROWS-1][0:COLS-1];
    logic [DATA_WIDTH-1:0] tile_out_s_data  [0:ROWS-1][0:COLS-1];
    logic                  tile_out_s_valid [0:ROWS-1][0:COLS-1];
    logic [DATA_WIDTH-1:0] tile_out_w_data  [0:ROWS-1][0:COLS-1];
    logic                  tile_out_w_valid [0:ROWS-1][0:COLS-1];

    // B4: Per-tile branch outputs (only PE[0][0] used at array level)
    logic [PC_WIDTH-1:0]   tile_branch_target [0:ROWS-1][0:COLS-1];
    logic                  tile_branch_taken  [0:ROWS-1][0:COLS-1];

    // =========================================================================
    // Tile Instantiation (ROWS × COLS mesh)
    // =========================================================================
    generate
        for (genvar y = 0; y < ROWS; y++) begin : row
            for (genvar x = 0; x < COLS; x++) begin : col

                // Per-PE config write enable decode
                localparam int PE_ID = y * COLS + x;
                logic cfg_wr_en_tile;
                assign cfg_wr_en_tile = cfg_wr_en &&
                    (cfg_wr_pe_sel == PE_ID[$clog2(NUM_PES)-1:0]);

                // ── Determine input signals for each direction ──

                // North input: from tile(y-1,x) south output, or edge input
                wire [DATA_WIDTH-1:0] in_n_data = (y == 0) ? edge_data_in_n[x]
                                                            : tile_out_s_data[y-1][x];
                // South input: from tile(y+1,x) north output, or edge input
                wire [DATA_WIDTH-1:0] in_s_data = (y == ROWS-1) ? edge_data_in_s[x]
                                                                 : tile_out_n_data[y+1][x];
                // West input: from tile(y,x-1) east output, or edge input
                wire [DATA_WIDTH-1:0] in_w_data = (x == 0) ? edge_data_in_w[y]
                                                             : tile_out_e_data[y][x-1];
                // East input: from tile(y,x+1) west output, or edge input
                wire [DATA_WIDTH-1:0] in_e_data = (x == COLS-1) ? edge_data_in_e[y]
                                                                 : tile_out_w_data[y][x+1];

                cgra_tile #(
                    .DATA_WIDTH    (DATA_WIDTH),
                    .COORD_WIDTH   (COORD_WIDTH),
                    .ADDR_WIDTH    (ADDR_WIDTH > 4 ? ADDR_WIDTH : 8),
                    .SPM_DEPTH     (SPM_DEPTH),
                    .RF_DEPTH      (RF_DEPTH),
                    .X_COORD       (x),
                    .Y_COORD       (y),
                    .CONTEXT_DEPTH (CONTEXT_DEPTH),
                    .PC_WIDTH      (PC_WIDTH)
                ) u_tile (
                    .clk           (clk),
                    .rst_n         (rst_n),

                    .config_frame  (config_frame[PE_ID]),
                    .config_valid  (config_valid),
                    .context_pc    (context_pc),
                    .global_stall  (global_stall),

                    .cfg_wr_addr   (cfg_wr_addr),
                    .cfg_wr_data   (cfg_wr_data),
                    .cfg_wr_en     (cfg_wr_en_tile),

                    // North
                    .data_in_n     (in_n_data),
                    .data_out_n    (tile_out_n_data[y][x]),
                    .valid_out_n   (tile_out_n_valid[y][x]),

                    // South
                    .data_in_s     (in_s_data),
                    .data_out_s    (tile_out_s_data[y][x]),
                    .valid_out_s   (tile_out_s_valid[y][x]),

                    // East
                    .data_in_e     (in_e_data),
                    .data_out_e    (tile_out_e_data[y][x]),
                    .valid_out_e   (tile_out_e_valid[y][x]),

                    // West
                    .data_in_w     (in_w_data),
                    .data_out_w    (tile_out_w_data[y][x]),
                    .valid_out_w   (tile_out_w_valid[y][x]),

                    // B4: Branch
                    .branch_target_o(tile_branch_target[y][x]),
                    .branch_taken_o (tile_branch_taken[y][x])
                );

            end // col
        end // row
    endgenerate

    // =========================================================================
    // Edge Output Assignments
    // =========================================================================
    generate
        for (genvar x = 0; x < COLS; x++) begin : edge_out_ns
            assign edge_data_out_n[x]  = tile_out_n_data[0][x];
            assign edge_valid_out_n[x] = tile_out_n_valid[0][x];
            assign edge_data_out_s[x]  = tile_out_s_data[ROWS-1][x];
            assign edge_valid_out_s[x] = tile_out_s_valid[ROWS-1][x];
        end

        for (genvar y = 0; y < ROWS; y++) begin : edge_out_ew
            assign edge_data_out_e[y]  = tile_out_e_data[y][COLS-1];
            assign edge_valid_out_e[y] = tile_out_e_valid[y][COLS-1];
            assign edge_data_out_w[y]  = tile_out_w_data[y][0];
            assign edge_valid_out_w[y] = tile_out_w_valid[y][0];
        end
    endgenerate

    // =========================================================================
    // B4: Branch output from PE[0][0] (designated branch source)
    // =========================================================================
    assign branch_target_o = tile_branch_target[0][0];
    assign branch_taken_o  = tile_branch_taken[0][0];

endmodule
