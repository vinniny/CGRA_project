// ==============================================================================
// CGRA 4x4 Array (Router-Connected Tiles)
// ==============================================================================
// Instantiates 16 tiles in a 4x4 mesh topology. Each tile wraps a router and PE.
// Edge interfaces expose data/valid only; edge ready signals are tied high.

module cgra_array_4x4 #(
    parameter DATA_WIDTH = 32,
    parameter COORD_WIDTH = 4,
    parameter PAYLOAD_WIDTH = 16,
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

    localparam int ROWS = 4;
    localparam int COLS = 4;

    // -------------------------------------------------------------------------
    // Configuration frame matrix
    // -------------------------------------------------------------------------
    logic [63:0] cfg_frames [0:ROWS-1][0:COLS-1];

    assign cfg_frames[0][0] = config_frame_00;
    assign cfg_frames[0][1] = config_frame_01;
    assign cfg_frames[0][2] = config_frame_02;
    assign cfg_frames[0][3] = config_frame_03;
    assign cfg_frames[1][0] = config_frame_10;
    assign cfg_frames[1][1] = config_frame_11;
    assign cfg_frames[1][2] = config_frame_12;
    assign cfg_frames[1][3] = config_frame_13;
    assign cfg_frames[2][0] = config_frame_20;
    assign cfg_frames[2][1] = config_frame_21;
    assign cfg_frames[2][2] = config_frame_22;
    assign cfg_frames[2][3] = config_frame_23;
    assign cfg_frames[3][0] = config_frame_30;
    assign cfg_frames[3][1] = config_frame_31;
    assign cfg_frames[3][2] = config_frame_32;
    assign cfg_frames[3][3] = config_frame_33;

    // -------------------------------------------------------------------------
    // Mesh links
    // -------------------------------------------------------------------------
    // Horizontal: data moving right/left
    logic [DATA_WIDTH-1:0] h_link_data_right [ROWS][COLS+1];
    logic                  h_link_valid_right [ROWS][COLS+1];
    logic                  h_link_ready_right [ROWS][COLS+1];

    logic [DATA_WIDTH-1:0] h_link_data_left [ROWS][COLS+1];
    logic                  h_link_valid_left [ROWS][COLS+1];
    logic                  h_link_ready_left [ROWS][COLS+1];

    // Vertical: data moving down/up
    logic [DATA_WIDTH-1:0] v_link_data_down [ROWS+1][COLS];
    logic                  v_link_valid_down [ROWS+1][COLS];
    logic                  v_link_ready_down [ROWS+1][COLS];

    logic [DATA_WIDTH-1:0] v_link_data_up [ROWS+1][COLS];
    logic                  v_link_valid_up [ROWS+1][COLS];
    logic                  v_link_ready_up [ROWS+1][COLS];

    // -------------------------------------------------------------------------
    // Connect edge inputs to mesh links
    // -------------------------------------------------------------------------
    assign v_link_data_down[0][0] = edge_data_in_n0;
    assign v_link_valid_down[0][0] = edge_valid_in_n0;
    assign v_link_data_down[0][1] = edge_data_in_n1;
    assign v_link_valid_down[0][1] = edge_valid_in_n1;
    assign v_link_data_down[0][2] = edge_data_in_n2;
    assign v_link_valid_down[0][2] = edge_valid_in_n2;
    assign v_link_data_down[0][3] = edge_data_in_n3;
    assign v_link_valid_down[0][3] = edge_valid_in_n3;

    assign v_link_data_up[ROWS][0] = edge_data_in_s0;
    assign v_link_valid_up[ROWS][0] = edge_valid_in_s0;
    assign v_link_data_up[ROWS][1] = edge_data_in_s1;
    assign v_link_valid_up[ROWS][1] = edge_valid_in_s1;
    assign v_link_data_up[ROWS][2] = edge_data_in_s2;
    assign v_link_valid_up[ROWS][2] = edge_valid_in_s2;
    assign v_link_data_up[ROWS][3] = edge_data_in_s3;
    assign v_link_valid_up[ROWS][3] = edge_valid_in_s3;

    assign h_link_data_right[0][0] = edge_data_in_w0;
    assign h_link_valid_right[0][0] = edge_valid_in_w0;
    assign h_link_data_right[1][0] = edge_data_in_w1;
    assign h_link_valid_right[1][0] = edge_valid_in_w1;
    assign h_link_data_right[2][0] = edge_data_in_w2;
    assign h_link_valid_right[2][0] = edge_valid_in_w2;
    assign h_link_data_right[3][0] = edge_data_in_w3;
    assign h_link_valid_right[3][0] = edge_valid_in_w3;

    assign h_link_data_left[0][COLS] = edge_data_in_e0;
    assign h_link_valid_left[0][COLS] = edge_valid_in_e0;
    assign h_link_data_left[1][COLS] = edge_data_in_e1;
    assign h_link_valid_left[1][COLS] = edge_valid_in_e1;
    assign h_link_data_left[2][COLS] = edge_data_in_e2;
    assign h_link_valid_left[2][COLS] = edge_valid_in_e2;
    assign h_link_data_left[3][COLS] = edge_data_in_e3;
    assign h_link_valid_left[3][COLS] = edge_valid_in_e3;

    // -------------------------------------------------------------------------
    // Ready tie-offs for boundary outputs (external always ready)
    // -------------------------------------------------------------------------
    genvar xi, yi;
    generate
        for (xi = 0; xi < COLS; xi++) begin : V_READY_BOUND
            assign v_link_ready_down[ROWS][xi] = 1'b1; // South boundary
            assign v_link_ready_up[0][xi] = 1'b1;      // North boundary
        end
        for (yi = 0; yi < ROWS; yi++) begin : H_READY_BOUND
            assign h_link_ready_right[yi][COLS] = 1'b1; // East boundary
            assign h_link_ready_left[yi][0] = 1'b1;     // West boundary
        end
    endgenerate

    // -------------------------------------------------------------------------
    // Connect edge outputs from mesh links
    // -------------------------------------------------------------------------
    assign edge_data_out_n0 = v_link_data_up[0][0];
    assign edge_valid_out_n0 = v_link_valid_up[0][0];
    assign edge_data_out_n1 = v_link_data_up[0][1];
    assign edge_valid_out_n1 = v_link_valid_up[0][1];
    assign edge_data_out_n2 = v_link_data_up[0][2];
    assign edge_valid_out_n2 = v_link_valid_up[0][2];
    assign edge_data_out_n3 = v_link_data_up[0][3];
    assign edge_valid_out_n3 = v_link_valid_up[0][3];

    assign edge_data_out_s0 = v_link_data_down[ROWS][0];
    assign edge_valid_out_s0 = v_link_valid_down[ROWS][0];
    assign edge_data_out_s1 = v_link_data_down[ROWS][1];
    assign edge_valid_out_s1 = v_link_valid_down[ROWS][1];
    assign edge_data_out_s2 = v_link_data_down[ROWS][2];
    assign edge_valid_out_s2 = v_link_valid_down[ROWS][2];
    assign edge_data_out_s3 = v_link_data_down[ROWS][3];
    assign edge_valid_out_s3 = v_link_valid_down[ROWS][3];

    assign edge_data_out_e0 = h_link_data_right[0][COLS];
    assign edge_valid_out_e0 = h_link_valid_right[0][COLS];
    assign edge_data_out_e1 = h_link_data_right[1][COLS];
    assign edge_valid_out_e1 = h_link_valid_right[1][COLS];
    assign edge_data_out_e2 = h_link_data_right[2][COLS];
    assign edge_valid_out_e2 = h_link_valid_right[2][COLS];
    assign edge_data_out_e3 = h_link_data_right[3][COLS];
    assign edge_valid_out_e3 = h_link_valid_right[3][COLS];

    assign edge_data_out_w0 = h_link_data_left[0][0];
    assign edge_valid_out_w0 = h_link_valid_left[0][0];
    assign edge_data_out_w1 = h_link_data_left[1][0];
    assign edge_valid_out_w1 = h_link_valid_left[1][0];
    assign edge_data_out_w2 = h_link_data_left[2][0];
    assign edge_valid_out_w2 = h_link_valid_left[2][0];
    assign edge_data_out_w3 = h_link_data_left[3][0];
    assign edge_valid_out_w3 = h_link_valid_left[3][0];

    // -------------------------------------------------------------------------
    // Tile generation
    // -------------------------------------------------------------------------
    genvar x, y;
    generate
        for (y = 0; y < ROWS; y++) begin : ROW
            for (x = 0; x < COLS; x++) begin : COL
                cgra_tile #(
                    .DATA_WIDTH(DATA_WIDTH),
                    .COORD_WIDTH(COORD_WIDTH),
                    .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
                    .ADDR_WIDTH(ADDR_WIDTH),
                    .SPM_DEPTH(SPM_DEPTH),
                    .RF_DEPTH(RF_DEPTH),
                    .X_COORD(x),
                    .Y_COORD(y)
                ) u_tile (
                    .clk(clk),
                    .rst_n(rst_n),
                    .config_frame(cfg_frames[y][x]),
                    .config_valid(config_valid),

                    .data_in_n(v_link_data_down[y][x]),
                    .data_in_e(h_link_data_left[y][x+1]),
                    .data_in_s(v_link_data_up[y+1][x]),
                    .data_in_w(h_link_data_right[y][x]),
                    .valid_in_n(v_link_valid_down[y][x]),
                    .valid_in_e(h_link_valid_left[y][x+1]),
                    .valid_in_s(v_link_valid_up[y+1][x]),
                    .valid_in_w(h_link_valid_right[y][x]),
                    .ready_out_n(v_link_ready_down[y][x]),
                    .ready_out_e(h_link_ready_left[y][x+1]),
                    .ready_out_s(v_link_ready_up[y+1][x]),
                    .ready_out_w(h_link_ready_right[y][x]),

                    .data_out_n(v_link_data_up[y][x]),
                    .data_out_e(h_link_data_right[y][x+1]),
                    .data_out_s(v_link_data_down[y+1][x]),
                    .data_out_w(h_link_data_left[y][x]),
                    .valid_out_n(v_link_valid_up[y][x]),
                    .valid_out_e(h_link_valid_right[y][x+1]),
                    .valid_out_s(v_link_valid_down[y+1][x]),
                    .valid_out_w(h_link_valid_left[y][x]),
                    .ready_in_n(v_link_ready_up[y][x]),
                    .ready_in_e(h_link_ready_right[y][x+1]),
                    .ready_in_s(v_link_ready_down[y+1][x]),
                    .ready_in_w(h_link_ready_left[y][x])
                );
            end
        end
    endgenerate

endmodule
