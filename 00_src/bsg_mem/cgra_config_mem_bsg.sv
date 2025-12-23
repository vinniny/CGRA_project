`timescale 1ns/1ps

// ==============================================================================
// cgra_config_mem_bsg.sv - PE Configuration RAM using BSG Memory
// ==============================================================================
// Wraps bsg_mem_1r1w_sync to provide:
//   - Write port: for DMA/testbench to load configuration
//   - Read port: for PE to fetch active config by context_pc
// 
// Integration: Instantiated inside cgra_pe.sv to replace simple logic array
// Memory: 16 slots × 64-bit = 128 bytes per PE (16KB total for 4x4 array)
//
// TIMING:
//   - Write: Synchronous, 1-cycle latency
//   - Read: Synchronous, 1-cycle latency (rd_valid delayed from rd_en)
// ==============================================================================

`include "bsg_defines.sv"

module cgra_config_mem_bsg #(
    parameter DATA_WIDTH = 64,
    parameter DEPTH      = 16,     // Number of config slots (context depth)
    parameter ADDR_WIDTH = 4       // $clog2(DEPTH)
)(
    input  wire                   clk,
    input  wire                   rst_n,

    // --------------------------------------------------------
    // Write Port (from DMA/Testbench)
    // --------------------------------------------------------
    input  wire [ADDR_WIDTH-1:0]  wr_addr,    // Config slot to write
    input  wire [DATA_WIDTH-1:0]  wr_data,    // 64-bit config frame
    input  wire                   wr_en,      // Write enable

    // --------------------------------------------------------
    // Read Port (from PE - indexed by context_pc)
    // --------------------------------------------------------
    input  wire [ADDR_WIDTH-1:0]  rd_addr,    // context_pc
    input  wire                   rd_en,      // Read enable
    output wire [DATA_WIDTH-1:0]  rd_data,    // Config data out
    output logic                  rd_valid    // Data valid (1-cycle delayed)
);

    // ------------------------------------------------
    // Instantiate BaseJump STL Memory
    // ------------------------------------------------
    // read_write_same_addr_p=1: Allows read and write to same address
    // (write data is forwarded to read port on same cycle)
    bsg_mem_1r1w_sync #(
        .width_p(DATA_WIDTH),
        .els_p(DEPTH),
        .read_write_same_addr_p(1)  // Enable write-through to prevent X on hazard
    ) mem_inst (
        .clk_i   (clk),
        .reset_i (~rst_n),        // BSG uses active-high reset
        
        // Read Port
        .r_v_i   (rd_en),
        .r_addr_i(rd_addr),
        .r_data_o(rd_data),
        
        // Write Port
        .w_v_i   (wr_en),
        .w_addr_i(wr_addr),
        .w_data_i(wr_data)
    );

    // ------------------------------------------------
    // Read Valid Signal (1-cycle latency)
    // ------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rd_valid <= 1'b0;
        end else begin
            rd_valid <= rd_en;
        end
    end

endmodule