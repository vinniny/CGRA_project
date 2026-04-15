// cgra_config_broadcaster.sv — slot-0 config write replay.
//
// When the DMA writes slot 0 of a PE's config RAM, this module replays the
// same payload to slots 1..15 over 15 additional cycles, so that every
// context slot holds the same program (common case for single-kernel
// workloads). DMA is idle during config loading so the extra cycles don't
// impact throughput.
//
// The module sits on the config write bus between the DMA config output and
// the PE array's cfg_wr_* port. While broadcasting, it takes priority over
// the DMA path (the DMA can't start a new write until the current double-pump
// commits, and this FSM's slot-0 detection runs in the same cycle as commit).

module cgra_config_broadcaster (
    input  logic        clk,
    input  logic        rst_n,

    // Upstream (from DMA config commit)
    input  logic [3:0]  in_addr,      // config slot (0..15)
    input  logic [63:0] in_data,
    input  logic [3:0]  in_pe_sel,
    input  logic        in_we,        // commit pulse

    // Downstream (to PE array cfg_wr_* ports)
    output logic [3:0]  out_addr,
    output logic [63:0] out_data,
    output logic [3:0]  out_pe_sel,
    output logic        out_we
);

    logic        active;
    logic [3:0]  slot;
    logic [3:0]  pe_sel_r;
    logic [63:0] data_r;

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            active   <= 1'b0;
            slot     <= 4'd0;
            pe_sel_r <= 4'd0;
            data_r   <= 64'd0;
        end else if (in_we && in_addr == 4'd0 && !active) begin
            // Latch slot-0 payload and start replay to slots 1..15
            active   <= 1'b1;
            slot     <= 4'd1;
            pe_sel_r <= in_pe_sel;
            data_r   <= in_data;
        end else if (active) begin
            if (slot == 4'd15) active <= 1'b0;
            else               slot   <= slot + 4'd1;
        end
    end

    always_comb begin
        if (active) begin
            out_addr   = slot;
            out_data   = data_r;
            out_pe_sel = pe_sel_r;
            out_we     = 1'b1;
        end else begin
            out_addr   = in_addr;
            out_data   = in_data;
            out_pe_sel = in_pe_sel;
            out_we     = in_we;
        end
    end

endmodule
