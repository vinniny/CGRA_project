`timescale 1ns/1ps

// Ensure definitions are loaded. 
// Ideally, compile bsg_defines.sv BEFORE this file, but this include is a safety net.
`include "bsg_defines.sv"

module cgra_config_mem_bsg #(
    parameter DATA_WIDTH = 64,
    parameter ADDR_WIDTH = 32, // Byte Address Width (e.g. 32-bit address space)
    parameter DEPTH      = 1024
)(
    input  wire                  clk,
    input  wire                  rst_n,

    // --------------------------------------------------------
    // Port A: Read Interface (Connect to CGRA DUT)
    // --------------------------------------------------------
    input  wire [ADDR_WIDTH-1:0] cfg_addr,
    input  wire                  cfg_ren,
    output wire [DATA_WIDTH-1:0] cfg_rdata,
    output reg                   cfg_valid,

    // --------------------------------------------------------
    // Port B: Write Interface (Connect to Testbench)
    // --------------------------------------------------------
    input  wire                  tb_we,
    input  wire [ADDR_WIDTH-1:0] tb_waddr,
    input  wire [DATA_WIDTH-1:0] tb_wdata
);

    // ------------------------------------------------
    // Address Calculation
    // ------------------------------------------------
    // Convert Byte Address (0, 8, 16...) to Word Index (0, 1, 2...)
    // for 64-bit words (8 bytes), we shift right by 3 bits.
    localparam IDX_WIDTH = $clog2(DEPTH);
    
    wire [IDX_WIDTH-1:0] read_idx;
    wire [IDX_WIDTH-1:0] write_idx;

    assign read_idx  = cfg_addr[2 + IDX_WIDTH : 3]; 
    assign write_idx = tb_waddr[2 + IDX_WIDTH : 3];

    // ------------------------------------------------
    // Instantiate BaseJump STL Memory
    // ------------------------------------------------
    // Note: BSG modules use specific suffixes like _i and _o
    bsg_mem_1r1w_sync #(
        .width_p(DATA_WIDTH),
        .els_p(DEPTH)
    ) mem_inst (
        .clk_i(clk),
        .reset_i(~rst_n), // BSG usually expects Active High reset
        
        // Read Port (CGRA)
        .r_v_i(cfg_ren),
        .r_addr_i(read_idx),
        .r_data_o(cfg_rdata),
        
        // Write Port (Testbench)
        .w_v_i(tb_we),
        .w_addr_i(write_idx),
        .w_data_i(tb_wdata)
    );

    // ------------------------------------------------
    // Generate Valid Signal
    // ------------------------------------------------
    // bsg_mem_1r1w_sync is a synchronous RAM with 1-cycle read latency.
    // So, if Read Enable (ren) is high at T0, Valid Data is ready at T1.
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cfg_valid <= 1'b0;
        end else begin
            cfg_valid <= cfg_ren;
        end
    end

endmodule