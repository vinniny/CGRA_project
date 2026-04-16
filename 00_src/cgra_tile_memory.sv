// cgra_tile_memory.sv — 4 row-banked SRAMs for CGRA west-edge streaming.
// Bank b feeds row b (one bank per row). Each bank has a PE-facing read port
// and a shared external (DMA) port muxed by ext_bank_sel.
//
// Double-buffering: bank_sel_i selects upper vs lower half of each bank for
// the PE-facing port; the DMA-facing port always uses full-width address.

module cgra_tile_memory #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 12,
    parameter BANK_DEPTH = 1024,
    parameter NUM_BANKS  = 4
)(
    input  logic clk,
    input  logic rst_n,

    input  logic bank_sel_i,

    // Per-bank PE-facing ports (flat — kept for backward compatibility)
    input  logic [ADDR_WIDTH-1:0] bank0_addr, bank1_addr, bank2_addr, bank3_addr,
    input  logic                  bank0_read, bank1_read, bank2_read, bank3_read,
    input  logic                  bank0_write, bank1_write, bank2_write, bank3_write,
    input  logic [DATA_WIDTH-1:0] bank0_wdata, bank1_wdata, bank2_wdata, bank3_wdata,
    output logic [DATA_WIDTH-1:0] bank0_rdata, bank1_rdata, bank2_rdata, bank3_rdata,
    output logic                  bank0_valid, bank1_valid, bank2_valid, bank3_valid,

    // Shared DMA-facing port
    input  logic [ADDR_WIDTH-1:0] ext_addr,
    input  logic [1:0]            ext_bank_sel,
    input  logic                  ext_read,
    input  logic                  ext_write,
    input  logic [DATA_WIDTH-1:0] ext_wdata,
    output logic [DATA_WIDTH-1:0] ext_rdata,
    output logic                  ext_valid
);

    localparam BANK_ADDR_W = $clog2(BANK_DEPTH);

    // Pack the per-bank interface into arrays for the generate loop below.
    logic [ADDR_WIDTH-1:0] bank_addr  [0:NUM_BANKS-1];
    logic                  bank_read  [0:NUM_BANKS-1];
    logic                  bank_write [0:NUM_BANKS-1];
    logic [DATA_WIDTH-1:0] bank_wdata [0:NUM_BANKS-1];
    logic [DATA_WIDTH-1:0] bank_rdata [0:NUM_BANKS-1];
    logic                  bank_valid [0:NUM_BANKS-1];

    assign bank_addr  = '{bank0_addr,  bank1_addr,  bank2_addr,  bank3_addr};
    assign bank_read  = '{bank0_read,  bank1_read,  bank2_read,  bank3_read};
    assign bank_write = '{bank0_write, bank1_write, bank2_write, bank3_write};
    assign bank_wdata = '{bank0_wdata, bank1_wdata, bank2_wdata, bank3_wdata};
    assign bank0_rdata = bank_rdata[0];
    assign bank1_rdata = bank_rdata[1];
    assign bank2_rdata = bank_rdata[2];
    assign bank3_rdata = bank_rdata[3];
    assign bank0_valid = bank_valid[0];
    assign bank1_valid = bank_valid[1];
    assign bank2_valid = bank_valid[2];
    assign bank3_valid = bank_valid[3];

    // Bank storage shared across generate block
    logic [DATA_WIDTH-1:0] mem [0:NUM_BANKS-1][0:BANK_DEPTH-1];

    genvar b;
    generate
        for (b = 0; b < NUM_BANKS; b++) begin : g_bank
            logic read_reg;
            logic ext_hits;
            assign ext_hits = (ext_bank_sel == b[1:0]);

            always_ff @(posedge clk) begin
                if (!rst_n) begin
                    read_reg        <= 1'b0;
                    bank_rdata[b]   <= '0;
                end else begin
                    read_reg <= bank_read[b] || (ext_read && ext_hits);

                    /* verilator lint_off WIDTHTRUNC */
                    if (bank_write[b] || (ext_write && ext_hits)) begin
                        if (ext_write && ext_hits)
                            mem[b][ext_addr[BANK_ADDR_W-1:0]] <= ext_wdata;
                        else
                            mem[b][{bank_sel_i, bank_addr[b][BANK_ADDR_W-2:0]}] <= bank_wdata[b];
                    end

                    if (bank_read[b] || (ext_read && ext_hits)) begin
                        if (ext_read && ext_hits)
                            bank_rdata[b] <= mem[b][ext_addr[BANK_ADDR_W-1:0]];
                        else
                            bank_rdata[b] <= mem[b][{bank_sel_i, bank_addr[b][BANK_ADDR_W-2:0]}];
                    end
                    /* verilator lint_on WIDTHTRUNC */
                end
            end

            assign bank_valid[b] = read_reg;
        end
    endgenerate

    // External read port: mux across banks
    logic ext_read_reg;
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            ext_rdata    <= '0;
            ext_read_reg <= 1'b0;
        end else begin
            ext_read_reg <= ext_read;
            /* verilator lint_off WIDTHTRUNC */
            if (ext_read) begin
                unique case (ext_bank_sel)
                    2'd0: ext_rdata <= mem[0][ext_addr[BANK_ADDR_W-1:0]];
                    2'd1: ext_rdata <= mem[1][ext_addr[BANK_ADDR_W-1:0]];
                    2'd2: ext_rdata <= mem[2][ext_addr[BANK_ADDR_W-1:0]];
                    2'd3: ext_rdata <= mem[3][ext_addr[BANK_ADDR_W-1:0]];
                    default: ext_rdata <= '0;
                endcase
            end
            /* verilator lint_on WIDTHTRUNC */
        end
    end
    assign ext_valid = ext_read_reg;

    // synthesis translate_off
    // Bank + external concurrent write/read to the same bank causes undefined
    // behavior; the CU's global_stall gating should prevent this in practice.
    always_ff @(posedge clk) begin
        if (rst_n) begin
            if (bank_write[0] && ext_write && ext_bank_sel == 2'd0) $fatal(0, "[TILE_MEM] Simultaneous bank0_write + ext_write — data corruption");
            if (bank_read[0]  && ext_read  && ext_bank_sel == 2'd0) $error("[TILE_MEM] Simultaneous bank0_read + ext_read — bank gets ext data");
            if (bank_write[1] && ext_write && ext_bank_sel == 2'd1) $fatal(0, "[TILE_MEM] Simultaneous bank1_write + ext_write — data corruption");
            if (bank_read[1]  && ext_read  && ext_bank_sel == 2'd1) $error("[TILE_MEM] Simultaneous bank1_read + ext_read — bank gets ext data");
            if (bank_write[2] && ext_write && ext_bank_sel == 2'd2) $fatal(0, "[TILE_MEM] Simultaneous bank2_write + ext_write — data corruption");
            if (bank_read[2]  && ext_read  && ext_bank_sel == 2'd2) $error("[TILE_MEM] Simultaneous bank2_read + ext_read — bank gets ext data");
            if (bank_write[3] && ext_write && ext_bank_sel == 2'd3) $fatal(0, "[TILE_MEM] Simultaneous bank3_write + ext_write — data corruption");
            if (bank_read[3]  && ext_read  && ext_bank_sel == 2'd3) $error("[TILE_MEM] Simultaneous bank3_read + ext_read — bank gets ext data");
        end
    end
    // synthesis translate_on

endmodule
