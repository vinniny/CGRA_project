`ifndef TB_STALL_OBSERVER_SVH
`define TB_STALL_OBSERVER_SVH

// =============================================================================
// Stall Observer (T1) — background monitor for FIFO-overflow-induced CU hangs.
//
// Fires fail() when global_stall_r is asserted for > STALL_FATAL_CYCS
// consecutive cycles while cu_busy is high.  Set stall_observer_en=0 to
// suppress for tests that intentionally create long stalls (e.g. FRS03).
// =============================================================================

localparam int STALL_FATAL_CYCS = 200;

int  stall_observer_en          = 1;
int  stall_consec_cycs          = 0;
int  stall_obs_overflow_total   = 0;   // running count of overflow pulses seen

always @(posedge clk) begin
    // Track overflow events globally for suite use
    if (tb_top.u_dut.result_fifo_overflow)
        stall_obs_overflow_total = stall_obs_overflow_total + 1;

    if (!rst_n) begin
        stall_consec_cycs = 0;
    end else if (stall_observer_en &&
                 tb_top.u_dut.cu_busy &&
                 tb_top.u_dut.global_stall_r) begin
        stall_consec_cycs = stall_consec_cycs + 1;
        if (stall_consec_cycs == STALL_FATAL_CYCS) begin
            fail("STALL_OBS: global_stall held for 200 cycles while CU busy",
                 $sformatf("fifo_full=%b fifo_count=%0d dma_conflict=%b",
                     tb_top.u_dut.result_fifo_full,
                     tb_top.u_dut.result_fifo_count,
                     tb_top.u_dut.dma_bank_conflict));
            // Reset counter so we don't re-fire every cycle after threshold
            stall_consec_cycs = 0;
        end
    end else begin
        stall_consec_cycs = 0;
    end
end

`endif
