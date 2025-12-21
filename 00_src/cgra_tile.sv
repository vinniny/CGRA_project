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
    parameter Y_COORD      = 0,
    parameter CONTEXT_DEPTH = 16,
    parameter PC_WIDTH     = 4
)(
    input  logic                   clk,
    input  logic                   rst_n,
    input  logic [63:0]            config_frame,
    input  logic                   config_valid,

    // Multi-context interface
    input  logic [PC_WIDTH-1:0]    context_pc,
    input  logic                   global_stall,
    
    // Config write interface (from DMA/TB)
    input  logic [PC_WIDTH-1:0]    cfg_wr_addr,
    input  logic [63:0]            cfg_wr_data,
    input  logic                   cfg_wr_en,

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
    // FIX #4: Router outputs go to internal wires (unused for now)
    // PE broadcast overrides tile output ports below
    logic [DATA_WIDTH-1:0] router_out_n, router_out_e, router_out_s, router_out_w;
    logic router_valid_n, router_valid_e, router_valid_s, router_valid_w;
    
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
        .data_out_n(router_out_n),       // FIX #4: to internal wire
        .valid_out_n(router_valid_n),    // FIX #4: to internal wire
        .ready_in_n(ready_in_n),

        .data_in_e(data_in_e),
        .valid_in_e(valid_in_e),
        .ready_out_e(ready_out_e),
        .data_out_e(router_out_e),       // FIX #4: to internal wire
        .valid_out_e(router_valid_e),    // FIX #4: to internal wire
        .ready_in_e(ready_in_e),

        .data_in_s(data_in_s),
        .valid_in_s(valid_in_s),
        .ready_out_s(ready_out_s),
        .data_out_s(router_out_s),       // FIX #4: to internal wire
        .valid_out_s(router_valid_s),    // FIX #4: to internal wire
        .ready_in_s(ready_in_s),

        .data_in_w(data_in_w),
        .valid_in_w(valid_in_w),
        .ready_out_w(ready_out_w),
        .data_out_w(router_out_w),       // FIX #4: to internal wire
        .valid_out_w(router_valid_w),    // FIX #4: to internal wire
        .ready_in_w(ready_in_w),

        .data_in_local(pe_to_router_data),
        .valid_in_local(pe_to_router_valid),
        .ready_out_local(router_to_pe_ready),
        .data_out_local(router_to_pe_data),
        .valid_out_local(router_to_pe_valid),
        .ready_in_local(pe_to_router_ready)
    );

    // PE Instance
    // -------------------------------------------------------------------------
    
    // FIX #4: Capture PE result for mesh broadcast
    logic [DATA_WIDTH-1:0] pe_result;
    logic                  pe_result_valid;
    
    cgra_pe #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
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
        
        // Multi-context
        .context_pc(context_pc),
        .global_stall(global_stall),
        
        // Config write
        .cfg_wr_addr(cfg_wr_addr),
        .cfg_wr_data(cfg_wr_data),
        .cfg_wr_en(cfg_wr_en),

        .data_in_n(data_in_n),          // FIX 1: Direct from tile port (not router)
        .data_in_e(data_in_e),          // FIX 1: Direct from tile port
        .data_in_s(data_in_s),          // FIX 1: Direct from tile port  
        .data_in_w(data_in_w),          // FIX 1: Direct from tile port (Tile Memory path!)
        .valid_in_n(valid_in_n),        // FIX 1: Direct valid
        .valid_in_e(valid_in_e),        // FIX 1: Direct valid
        .valid_in_s(valid_in_s),        // FIX 1: Direct valid
        .valid_in_w(valid_in_w),        // FIX 1: Direct valid (Tile Memory!)

        // FIX #4: Capture PE directional outputs (all carry same result)
        .data_out_n(pe_result),         // Capture result
        .data_out_e(),                  // Same data, unused
        .data_out_s(),                  // Same data, unused
        .data_out_w(),                  // Same data, unused
        .valid_out_n(pe_result_valid),  // Capture valid
        .valid_out_e(),
        .valid_out_s(),
        .valid_out_w(),

        .data_out_local(pe_to_router_data),
        .valid_out_local(pe_to_router_valid),
        .ready_in(router_to_pe_ready),
        .ready_out(pe_to_router_ready)
    );
    
    // =========================================================================
    // FIX #4: BROADCAST PE RESULT TO ALL NEIGHBORS
    // =========================================================================
    // Override router outputs - PE result goes directly to all neighbors
    assign data_out_n = pe_result;
    assign data_out_e = pe_result;
    assign data_out_s = pe_result;
    assign data_out_w = pe_result;
    
    assign valid_out_n = pe_result_valid;
    assign valid_out_e = pe_result_valid;
    assign valid_out_s = pe_result_valid;
    assign valid_out_w = pe_result_valid;

endmodule
