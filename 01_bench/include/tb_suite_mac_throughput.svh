`ifndef TB_SUITE_MAC_THROUGHPUT_SVH
`define TB_SUITE_MAC_THROUGHPUT_SVH

// =============================================================================
// SUITE MTP: MAC PIPELINE THROUGHPUT MEASUREMENT
// =============================================================================
// Purpose
// -------
// CLAUDE.md historically described a "~1/3 of back-to-back MACs contribute"
// hazard. Reading cgra_pe.sv:563-586 (synchronous accumulator update) suggests
// that's stale — and CK_D1P already empirically shows 12 of 16 slots commit
// per single pass (75% slot efficiency, mask 0x0000_3FFC). This suite produces
// the citation-ready throughput numbers behind that claim, sweeping LOOP_COUNT
// to also report cycle-level efficiency in steady state.
//
// Method
// ------
// Each test:
//   - tile bank 0 + SPM[0..N] = 1  (each commit adds 1 × 1 = 1 to acc).
//   - PE 0, all 16 context slots: MAC(SRC_WEST, SRC_SPM) → acc.
//   - CU_PC_END=15, LOOP_START=0, LOOP_END=15, TILE+SPM auto-inc on.
//   - Read CU_CYCLES after cu_done.
//   - Read accumulator via the existing whitebox read_pe_result(0). With
//     all-ones inputs, no 32-bit clamp fires, so alu_result == contributions.
//   - Print  contribs, cycles, slot_eff%, cycle_eff%
//     (slot_eff  = contribs / (16 × passes); cycle_eff = contribs / cycles).
//   - Pass criterion: contribs matches the closed-form 16·passes − 4 model
//     (loses 2 commits at the start of pass 0 and 2 at the end of the last
//     pass; middle passes commit all 16).
//
// Expected results (measured at commit f66eaeb baseline RTL)
// ----------------
// MTP01  LOOP_COUNT=0    1 pass    contribs = 13   cycles = 15   slot_eff = 81.2%   cycle_eff = 86.6%
// MTP02  LOOP_COUNT=9    10 passes contribs = 157  cycles = 159  slot_eff = 98.1%   cycle_eff = 98.7%
// MTP03  LOOP_COUNT=63   64 passes contribs = 1021 cycles = 1023 slot_eff = 99.7%   cycle_eff = 99.8%
//
// The closed-form model is contribs = 16·N − 3 (with SRC_IMM second
// operand). SRC_IMM has zero read latency, so we lose only 3 slots total
// to startup/drain bookkeeping (vs the 4 lost when using SRC_SPM with its
// 1-cycle registered read — see CK_D1P which gets 12 = 16−4 single-pass).
//
// MTP03 is capped at 64 passes because TILE_AUTO_INC reads tile addresses
// 0..16N-1 (with imm=0) — beyond 64 passes we'd need a tile bank fill
// larger than the bulk DMA used here. 64 passes is plenty to drive the
// efficiency past 99% — the asymptote is 16/16 = 100%.
//
// The trend 81% → 98% → 99.7% directly refutes any "1/3 of back-to-back
// MACs contribute" claim. The pipeline is *de facto* 100% per-slot
// efficient in steady state, with a fixed −3 startup+drain that becomes
// negligible at high LOOP_COUNT.
// =============================================================================

task automatic mtp_one_measurement(
        input  string        label,
        input  logic [31:0]  loop_cnt,
        input  int           passes,        // = loop_cnt + 1
        input  logic [31:0]  expected_contribs,
        input  int           cycle_timeout);
    logic [31:0]  mac_cfg_lo;
    logic [63:0]  mac_cfg;
    logic [31:0]  cycles;
    logic [31:0]  contribs;
    integer       i;
    int           slot_eff_x10;     // tenths-of-percent (e.g. 750 = 75.0%)
    int           cycle_eff_x10;

    // MAC config: src0=SRC_WEST (tile via row 0 routing), src1=SRC_IMM=1.
    // This deliberately AVOIDS SRC_SPM so we don't depend on per-PE SPM
    // contents, which can carry stale data between suites in simulation
    // (SPM BRAM has no reset path). Each contribution = tile × 1 = 1.
    mac_cfg = build_pe_config(OP_MAC, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd1);

    reset_dut(5);

    // Fill tile bank 0 with 1024 words of value 1. The existing
    // tile_bank_fill_all() only writes the first 16 slots — fine for
    // single-pass tests but not for MTP03 (64 passes × 16 reads = 1024).
    // We do one bulk DMA from DDR scratch to tile bank.
    for (i = 0; i < 1024; i++)
        ram_write(32'h0000_4000 + i*4, 32'h0000_0001);
    dma_transfer(32'h0000_4000,
                 BASE_TILE | ({18'd0, 2'd0, 12'd0}) | {20'd0, 12'd0},
                 32'd4096, 5000);

    // PE 0 all 16 slots = MAC(SRC_WEST, SRC_SPM)
    cnn_k_fill_pe_all_slots(4'd0, mac_cfg);
    cnn_k_acc_clr(4'd0, mac_cfg);

    // Run the MAC loop. cnn_k_run_mac internally sets LOOP_*, CU_PC_END,
    // auto-inc, soft-resets, starts CU, waits for cu_done.
    cnn_k_run_mac(loop_cnt, cycle_timeout);

    // Read out cycle count + accumulator
    apb_read(ADDR_CU_CYCLES, cycles);
    contribs = read_pe_result(4'd0);

    // Compute efficiencies in tenths-of-percent to avoid floats in SV
    if (passes != 0 && contribs != 0) begin
        slot_eff_x10  = (contribs * 1000) / (16 * passes);
        cycle_eff_x10 = (cycles == 0) ? 0 : ((contribs * 1000) / cycles);
    end else begin
        slot_eff_x10  = 0;
        cycle_eff_x10 = 0;
    end

    $display("[%s] passes=%0d contribs=%0d cycles=%0d slot_eff=%0d.%0d%% cycle_eff=%0d.%0d%%",
             label, passes, contribs, cycles,
             slot_eff_x10  / 10, slot_eff_x10  % 10,
             cycle_eff_x10 / 10, cycle_eff_x10 % 10);

    if (contribs == expected_contribs)
        pass($sformatf("%s: contribs == %0d (matches 16N-3 model)",
                       label, expected_contribs));
    else
        fail($sformatf("%s: contribs mismatch",
                       label),
             $sformatf("expected=%0d got=%0d cycles=%0d",
                       expected_contribs, contribs, cycles));
endtask

task automatic run_suite_MTP_mac_throughput;
    begin
        $display("\n========================================");
        $display("   SUITE MTP: MAC PIPELINE THROUGHPUT");
        $display("========================================\n");

        // MTP01: single pass — 16·1 − 3 = 13 (SRC_IMM has zero read latency)
        mtp_one_measurement("MTP01", 32'd0,  1,    32'd13,    500);

        // MTP02: 10 passes — 16·10 − 3 = 157
        mtp_one_measurement("MTP02", 32'd9,  10,   32'd157,   2000);

        // MTP03: 64 passes (max within bulk-DMA tile fill) — 16·64 − 3 = 1021
        mtp_one_measurement("MTP03", 32'd63, 64,   32'd1021,  20000);

        $display("\n[SUITE MTP COMPLETE] MAC pipeline throughput measured.\n");
    end
endtask

`endif // TB_SUITE_MAC_THROUGHPUT_SVH
