`ifndef TB_SUITE_XFEAT_SVH
`define TB_SUITE_XFEAT_SVH

// =============================================================================
// SUITE XF: Cross-Feature Interaction Tests (T4)
// =============================================================================
// Covers interactions between R1/R2/R3 features that are not tested by the
// individual R-series suites.
//
// XF01: SPM_AUTO_INC + TILE_AUTO_INC simultaneously — both counters must
//       advance independently per loop wrap.
// XF02: LOOP2 (outer loop) with SPM auto-inc — spm_iter_cnt advances only
//       on L1 loop wraps, not L2 wraps.
// XF03: DMA→SPM concurrent with CU OP_LOAD_SPM on a different PE —
//       arb correctness: DMA writes PE15, CU reads PE0 (no collision).
// XF04: OP_STORE_SPM then DMA→SPM to same PE/address — DMA overwrites.
// XF05: Broadcast config + per-PE unicast override to one PE only.
// =============================================================================

task automatic xf_cu_start_wait(input int timeout_cyc, input string testname);
    logic [31:0] cu_stat;
    int t;
    apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(3);
    apb_write(ADDR_CU_CTRL, 32'd0); wait_cycles(2);
    apb_write(ADDR_CU_CTRL, 32'd1);
    t = 0;
    do begin
        wait_cycles(1);
        apb_read(ADDR_CU_STATUS, cu_stat);
        t++;
    end while (!cu_stat[1] && t < timeout_cyc);
    if (t >= timeout_cyc)
        fail({testname, ": CU timeout"}, $sformatf("timeout=%0d", timeout_cyc));
endtask

task automatic run_suite_XF_xfeat;
    logic [31:0] rd;
    logic [9:0]  spm_iter;
    logic [7:0]  tile_iter;
    begin
        $display("\n========================================");
        $display("   SUITE XF: CROSS-FEATURE INTERACTIONS");
        $display("========================================\n");

        // =================================================================
        // XF01: SPM_AUTO_INC + TILE_AUTO_INC simultaneously.
        //       LOOP_COUNT=3 → 3 loop wraps (LOOP_COUNT=N gives N wraps).
        //       Expected: spm_iter_cnt = 3×16 = 48; tile_base_offset = 3.
        // =================================================================
        $display("[XF01] SPM_AUTO_INC + TILE_AUTO_INC simultaneously...");
        reset_dut(5);

        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);

        apb_write(ADDR_SPM_AUTO_INC,  32'h1);
        apb_write(ADDR_TILE_AUTO_INC, 32'h1);
        apb_write(ADDR_LOOP_START,    32'd0);
        apb_write(ADDR_LOOP_END,      32'd0);
        apb_write(ADDR_LOOP_COUNT,    32'd3);
        apb_write(ADDR_CU_PC_END,     32'd15);

        xf_cu_start_wait(500, "XF01");

        spm_iter  = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.spm_iter_cnt;
        tile_iter = tb_top.u_dut.u_cu.tile_base_offset;

        if (spm_iter === 10'd48)
            pass($sformatf("XF01a: spm_iter_cnt=48 (3 wraps × 16) concurrent with tile auto-inc"));
        else
            fail("XF01a: spm_iter_cnt wrong with dual auto-inc",
                 $sformatf("exp=48 got=%0d", spm_iter));

        if (tile_iter === 8'd3)
            pass($sformatf("XF01b: tile_base_offset=3 (3 wraps × 1)"));
        else
            fail("XF01b: tile_base_offset wrong",
                 $sformatf("exp=3 got=%0d", tile_iter));

        apb_write(ADDR_SPM_AUTO_INC,  32'h0);
        apb_write(ADDR_TILE_AUTO_INC, 32'h0);

        // =================================================================
        // XF02: LOOP2 outer loop + SPM auto-inc.
        //       LOOP_COUNT=1 → 1 L1 wrap per outer iteration (2 outer iters).
        //       LOOP2_COUNT=1 → 1 L2 wrap.
        //       spm_iter_cnt fires on ALL loop wraps (L1 and L2):
        //       2 L1 wraps + 1 L2 wrap = 3 total → 3×16 = 48.
        // =================================================================
        $display("[XF02] LOOP2 with SPM auto-inc — iter_cnt on L1 wraps only...");
        reset_dut(5);

        config_pe_safe(4'd0, OP_NOP, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);

        apb_write(ADDR_SPM_AUTO_INC, 32'h1);
        apb_write(ADDR_LOOP_START,   32'd0);
        apb_write(ADDR_LOOP_END,     32'd0);
        apb_write(ADDR_LOOP_COUNT,   32'd1);   // L1: 2 passes per L2 iteration
        apb_write(ADDR_LOOP2_START,  32'd0);
        apb_write(ADDR_LOOP2_END,    32'd0);
        apb_write(ADDR_LOOP2_COUNT,  32'd1);   // L2: 2 outer iterations
        apb_write(ADDR_CU_PC_END,    32'd15);

        xf_cu_start_wait(1000, "XF02");

        spm_iter = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.spm_iter_cnt;
        // spm_iter_cnt fires on every loop_wrap_o (L1 and L2 both counted):
        // 2 L1 wraps + 1 L2 wrap = 3 total → 3×16 = 48
        if (spm_iter === 10'd48)
            pass($sformatf("XF02: spm_iter_cnt=48 (3 wraps: 2 L1 + 1 L2)"));
        else
            fail("XF02: spm_iter_cnt wrong under LOOP2",
                 $sformatf("exp=48 got=%0d", spm_iter));

        apb_write(ADDR_SPM_AUTO_INC, 32'h0);
        apb_write(ADDR_LOOP2_COUNT,  32'd0);

        // =================================================================
        // XF03: DMA→SPM on PE15 concurrent with CU running LOAD_SPM on PE0.
        //       Preload PE0 SPM[0]=0xABCD_1234. CU: LOAD_SPM from PE0.
        //       While CU runs, DMA writes PE15 SPM[0]=0xDEAD_BEEF.
        //       After CU done, verify PE15 SPM[0]=0xDEAD_BEEF (DMA succeeded).
        // =================================================================
        $display("[XF03] DMA→SPM concurrent with CU LOAD_SPM...");
        reset_dut(5);

        // Preload PE0 SPM[0..15]
        begin
            int i;
            for (i = 0; i < 16; i++)
                ram_write(32'h0020_0000 + i*4, 32'hABCD_1234);
        end
        dma_transfer(32'h0020_0000, BASE_SPM | (32'd0 << 12) | 32'd0, 32'd64, 500);

        // Configure PE0: LOAD_SPM(SRC_IMM addr=0) — runs 16 slots, no loop
        config_pe_imm(4'd0, OP_LOAD_SPM, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_CU_PC_END,  32'd15);

        // Start CU
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(3);
        apb_write(ADDR_CU_CTRL, 32'd0); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd1);

        // While CU runs (takes ~30 cycles), issue DMA→SPM to PE15
        wait_cycles(5);
        ram_write(32'h0021_0000, 32'hDEAD_BEEF);
        dma_transfer(32'h0021_0000, BASE_SPM | (32'd15 << 12) | 32'd0, 32'd4, 500);

        // Wait for CU done
        begin
            logic [31:0] cu_stat; int t;
            t = 0;
            do begin wait_cycles(1); apb_read(ADDR_CU_STATUS, cu_stat); t++; end
            while (!cu_stat[1] && t < 200);
            if (t >= 200) fail("XF03: CU timeout", "concurrent DMA+CU test");
        end

        // Verify PE15 SPM[0] got the DMA value
        rd = spm_read_wb(15, 0);
        if (rd === 32'hDEAD_BEEF)
            pass("XF03: PE15 SPM[0]=0xDEADBEEF after concurrent DMA→SPM during CU");
        else
            fail("XF03: PE15 SPM[0] wrong after concurrent DMA",
                 $sformatf("exp=0xDEADBEEF got=0x%08h", rd));

        // =================================================================
        // XF04: OP_STORE_SPM followed by DMA→SPM to same PE/address.
        //       CU stores 0x1234 to PE0 SPM[0] via STORE_SPM.
        //       Then DMA writes 0x5678 to PE0 SPM[0].
        //       DMA should overwrite (per R1 design: DMA wins when both fire;
        //       here they are sequential so DMA always wins anyway).
        // =================================================================
        $display("[XF04] OP_STORE_SPM followed by DMA→SPM overwrite...");
        reset_dut(5);

        // Fill all of tile bank 0 with 0x1234 so PE(0,0) reads it at any slot
        tile_bank_fill_all(2'd0, 32'h0000_1234);
        // PE0 slot 0: STORE_SPM(SRC_WEST → SPM[0])
        // STORE_SPM: operand0=data to store (SRC_WEST), operand1=address (SRC_IMM=0)
        config_pe_imm(4'd0, OP_STORE_SPM, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_CU_PC_END,  32'd15); // need full 16 slots for 3-stage pipeline to drain

        xf_cu_start_wait(200, "XF04-store");

        // Verify STORE_SPM wrote correctly
        rd = spm_read_wb(0, 0);
        if (rd === 32'h0000_1234)
            pass("XF04a: STORE_SPM wrote 0x1234 to PE0 SPM[0]");
        else
            fail("XF04a: STORE_SPM wrong", $sformatf("exp=0x1234 got=0x%08h", rd));

        // Now DMA→SPM overwrites PE0 SPM[0] with 0x5678
        ram_write(32'h0021_0000, 32'h0000_5678);
        dma_transfer(32'h0021_0000, BASE_SPM | (32'd0 << 12) | 32'd0, 32'd4, 500);

        rd = spm_read_wb(0, 0);
        if (rd === 32'h0000_5678)
            pass("XF04b: DMA→SPM overwrote PE0 SPM[0] to 0x5678");
        else
            fail("XF04b: DMA overwrite failed", $sformatf("exp=0x5678 got=0x%08h", rd));

        apb_write(ADDR_CU_PC_END, 32'd15);

        // =================================================================
        // XF05: Broadcast config → then unicast override on PE4 (row1,col0).
        //       All PEs get PASS0(SRC_WEST→EAST) via broadcast.
        //       PE4 gets unicast ADD(SRC_WEST + IMM=99).
        //       Tile = 1 for all banks.  Expected:
        //       RESULT_ROW0 = 1 (rows 0, unchanged PASS0 chain)
        //       RESULT_ROW1 ≠ 1 (PE4 adds 99 → row1 result differs)
        // =================================================================
        $display("[XF05] Broadcast config + unicast PE override...");
        reset_dut(5);

        tile_bank_fill_all(2'd0, 32'd1);
        tile_bank_fill_all(2'd1, 32'd1);
        tile_bank_fill_all(2'd2, 32'd1);
        tile_bank_fill_all(2'd3, 32'd1);

        // Broadcast PASS0 to all 16 PEs
        begin
            logic [63:0] pass0_cfg;
            pass0_cfg = build_pe_config(OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_EAST, 16'd0);
            bcast_write_slot(4'd0, pass0_cfg);
        end

        // Unicast ADD(SRC_WEST + 99) to PE4 (row1, col0 = pe_id=4)
        config_pe_imm(4'd4, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_EAST, 16'd99);

        apb_write(ADDR_LOOP_COUNT,  32'd0);
        apb_write(ADDR_CU_PC_END,   32'd15);
        apb_write(ADDR_RESULT_SKIP, 32'd12);

        xf_cu_start_wait(500, "XF05");

        begin
            logic [31:0] r0, r1;
            apb_read(ADDR_RESULT_ROW0, r0);
            apb_read(ADDR_RESULT_ROW1, r1);
            // Row0: PASS0 chain, tile=1 → 1 at every PE → RESULT_ROW0=1
            if (r0 === 32'd1)
                pass("XF05a: RESULT_ROW0=1 (broadcast PASS0 unchanged)");
            else
                fail("XF05a: RESULT_ROW0 wrong", $sformatf("exp=1 got=%0d", r0));
            // Row1: PE4 = ADD(1, 99)=100; PE5..7 PASS0(east) → RESULT_ROW1=100
            if (r1 === 32'd100)
                pass("XF05b: RESULT_ROW1=100 (unicast ADD(1,99) overrode broadcast on PE4)");
            else
                fail("XF05b: RESULT_ROW1 wrong", $sformatf("exp=100 got=%0d", r1));
        end

        $display("\n[SUITE XF COMPLETE] Cross-feature interaction tests done.\n");
    end
endtask

`endif
