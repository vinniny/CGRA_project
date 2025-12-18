// ==============================================================================
// CGRA Tile (Router + PE)
// ==============================================================================
// Wraps a router and a PE so all traffic flows through the NoC.
// Router local port connects to the PE's local interface.

module cgra_tile #(
    parameter DATA_WIDTH   = 32,
    parameter COORD_WIDTH  = 4,
    parameter PAYLOAD_WIDTH = 16,
    parameter ADDR_WIDTH   = 8,
    parameter SPM_DEPTH    = 256,
    parameter RF_DEPTH     = 16,
    parameter X_COORD      = 0,
    parameter Y_COORD      = 0
)(
    input  logic                   clk,
    input  logic                   rst_n,
    input  logic [63:0]            config_frame,
    input  logic                   config_valid,

    // Network Ports (N/S/E/W)
    input  logic [DATA_WIDTH-1:0]  data_in_n,
    input  logic [DATA_WIDTH-1:0]  data_in_e,
    input  logic [DATA_WIDTH-1:0]  data_in_s,
    input  logic [DATA_WIDTH-1:0]  data_in_w,
    input  logic                   valid_in_n,
    input  logic                   valid_in_e,
    input  logic                   valid_in_s,
    input  logic                   valid_in_w,
    output logic                   ready_out_n,
    output logic                   ready_out_e,
    output logic                   ready_out_s,
    output logic                   ready_out_w,

    output logic [DATA_WIDTH-1:0]  data_out_n,
    output logic [DATA_WIDTH-1:0]  data_out_e,
    output logic [DATA_WIDTH-1:0]  data_out_s,
    output logic [DATA_WIDTH-1:0]  data_out_w,
    output logic                   valid_out_n,
    output logic                   valid_out_e,
    output logic                   valid_out_s,
    output logic                   valid_out_w,
    input  logic                   ready_in_n,
    input  logic                   ready_in_e,
    input  logic                   ready_in_s,
    input  logic                   ready_in_w
);

    // Internal PE <-> Router links
    logic [DATA_WIDTH-1:0] pe_to_router_data;
    logic                  pe_to_router_valid;
    logic                  router_to_pe_ready;

    logic [DATA_WIDTH-1:0] router_to_pe_data;
    logic                  router_to_pe_valid;
    logic                  pe_to_router_ready;

    // -------------------------------------------------------------------------
    // Router Instance
    // -------------------------------------------------------------------------
    cgra_router #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .X_COORD(X_COORD),
        .Y_COORD(Y_COORD)
    ) u_router (
        .clk(clk),
        .rst_n(rst_n),

        .data_in_n(data_in_n),
        .valid_in_n(valid_in_n),
        .ready_out_n(ready_out_n),
        .data_out_n(data_out_n),
        .valid_out_n(valid_out_n),
        .ready_in_n(ready_in_n),

        .data_in_e(data_in_e),
        .valid_in_e(valid_in_e),
        .ready_out_e(ready_out_e),
        .data_out_e(data_out_e),
        .valid_out_e(valid_out_e),
        .ready_in_e(ready_in_e),

        .data_in_s(data_in_s),
        .valid_in_s(valid_in_s),
        .ready_out_s(ready_out_s),
        .data_out_s(data_out_s),
        .valid_out_s(valid_out_s),
        .ready_in_s(ready_in_s),

        .data_in_w(data_in_w),
        .valid_in_w(valid_in_w),
        .ready_out_w(ready_out_w),
        .data_out_w(data_out_w),
        .valid_out_w(valid_out_w),
        .ready_in_w(ready_in_w),

        .data_in_local(pe_to_router_data),
        .valid_in_local(pe_to_router_valid),
        .ready_out_local(router_to_pe_ready),
        .data_out_local(router_to_pe_data),
        .valid_out_local(router_to_pe_valid),
        .ready_in_local(pe_to_router_ready)
    );

    // -------------------------------------------------------------------------
    // PE Instance
    // -------------------------------------------------------------------------
    cgra_pe #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH)
    ) u_pe (
        .clk(clk),
        .rst_n(rst_n),
        .config_frame(config_frame),
        .config_valid(config_valid),

        .data_in_n(router_to_pe_data),
        .data_in_e(router_to_pe_data),
        .data_in_s(router_to_pe_data),
        .data_in_w(router_to_pe_data),
        .valid_in_n(router_to_pe_valid),
        .valid_in_e(router_to_pe_valid),
        .valid_in_s(router_to_pe_valid),
        .valid_in_w(router_to_pe_valid),

        .data_out_n(),
        .data_out_e(),
        .data_out_s(),
        .data_out_w(),
        .valid_out_n(),
        .valid_out_e(),
        .valid_out_s(),
        .valid_out_w(),

        .data_out_local(pe_to_router_data),
        .valid_out_local(pe_to_router_valid),
        .ready_in(router_to_pe_ready),
        .ready_out(pe_to_router_ready)
    );

endmodule
