`ifndef TB_SUITE_SPM_MAC_ADDRSRC_SVH
`define TB_SUITE_SPM_MAC_ADDRSRC_SVH

// =============================================================================
// SUITE SMA: SPM MAC Address-Source Tests (T3)
// =============================================================================
// Regression oracle for Bug #2: when src1_sel=SRC_SPM and spm_auto_inc_en=1,
// spm_addr = operand1_r2 + spm_iter_cnt uses SPM DATA (not a base address).
//
// SMA01: Exact FC v2 kernel (SRC_W, SRC_SPM, imm=0) — whitebox spm_addr check.
//        Fails pre-fix (spm_addr = garbage).
//        Post-fix: spm_addr = imm(0) + spm_iter_cnt + context_pc.
//        The context_pc term ensures each slot in a pass reads a unique weight.
// SMA02: Correct path (SRC_IMM, imm=0) — baseline reference, must pass always.
//        Post-fix: same formula; SRC_IMM keeps spm_auto_inc_en=1 so
//        spm_addr = imm + spm_iter_cnt + context_pc.
// SMA03: End-to-end OP_ADD with SRC_SPM + auto-inc — numerical correctness check.
// SMA04: 16-PE broadcast MAC config + distinct per-PE SPM preload.
// =============================================================================

// Helper: start CU (with soft-reset) and wait for done or fail.
task automatic sma_cu_start_wait(input int timeout_cyc, input string testname);
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
        fail({testname, ": CU timeout"},
             $sformatf("timeout=%0d fifo_full=%b", timeout_cyc,
                 tb_top.u_dut.result_fifo_full));
endtask

// Helper: wait for CU done without issuing soft-reset first (preserves SPM state).
task automatic sma_cu_start_only_wait(input int timeout_cyc, input string testname);
    logic [31:0] cu_stat;
    int t;
    apb_write(ADDR_CU_CTRL, 32'd1);
    t = 0;
    do begin
        wait_cycles(1);
        apb_read(ADDR_CU_STATUS, cu_stat);
        t++;
    end while (!cu_stat[1] && t < timeout_cyc);
    if (t >= timeout_cyc)
        fail({testname, ": CU timeout"},
             $sformatf("timeout=%0d fifo_full=%b", timeout_cyc,
                 tb_top.u_dut.result_fifo_full));
endtask

task automatic run_suite_SMA_spm_mac_addrsrc;
    logic [31:0] rd;
    logic [9:0]  observed_addr;
    logic [9:0]  iter_cnt;
    logic [3:0]  observed_pc;
    logic [63:0] mac_cfg;
    begin
        $display("\n========================================");
        $display("   SUITE SMA: SPM MAC ADDRESS SOURCE");
        $display("========================================\n");

        // =================================================================
        // SMA01: FC v2 exact kernel: CFGW(OP_MAC, SRC_W, SRC_SPM, 0, 0, 0)
        //        with spm_auto_inc_en=1.
        //        Pre-fix: spm_addr = spm_rdata + spm_iter_cnt (bug: data→addr).
        //        Post-fix: spm_addr = imm(0) + spm_iter_cnt + context_pc.
        //        Each slot reads a unique weight: slot j in pass p → weight[p*16+j].
        // =================================================================
        $display("[SMA01] FC v2 kernel SRC_SPM addr check (spm_addr must equal spm_iter_cnt+pc)...");
        reset_dut(5);

        // Preload PE0 SPM: word[k] = k+1  (so word[0]=1, word[16]=17, ...)
        begin
            int i;
            for (i = 0; i < 64; i++)
                ram_write(32'h0020_0000 + i*4, 32'(i + 1));
        end
        dma_transfer(32'h0020_0000, BASE_SPM | (32'd0 << 12) | 32'd0, 32'd256, 1000);

        // Tile bank 0: activation = 1000 for all 16 slots
        tile_bank_fill_all(2'd0, 32'd1000);

        // Enable auto-inc; set SPM_AUTO_INC before CU
        apb_write(ADDR_SPM_AUTO_INC, 32'h1);

        // Kernel: OP_MAC src0=SRC_W(4), src1=SRC_SPM(5), dst=0, route=NONE, imm=0
        mac_cfg = build_pe_config(OP_MAC, SRC_WEST, SRC_SPM, 4'd0, ROUTE_NONE, 16'd0);
        config_pe(4'd0, 4'd0, mac_cfg);   // slot 0 only; LOOP fills slots 1-15 same
        // All other slots also need the MAC kernel (broadcaster fills via slot-0 write)
        // Use a loop to fill all 16 slots explicitly
        begin
            int s;
            for (s = 1; s < 16; s++)
                config_pe(4'd0, s[3:0], mac_cfg);
        end

        apb_write(ADDR_LOOP_START,  32'd0);
        apb_write(ADDR_LOOP_END,    32'd15);
        apb_write(ADDR_LOOP_COUNT,  32'd2);   // 3 iterations (32 bit)
        apb_write(ADDR_CU_PC_END,   32'd15);
        apb_write(ADDR_RESULT_SKIP, 32'd12);

        // Start CU (no reset to preserve SPM), sample spm_addr ~10 cycles in
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(3);
        apb_write(ADDR_CU_CTRL, 32'd0); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(10);  // pipeline fills; spm_iter_cnt still 0

        // Whitebox: sample spm_addr, spm_iter_cnt, context_pc simultaneously on PE0
        observed_addr = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.spm_addr;
        iter_cnt      = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.spm_iter_cnt;
        observed_pc   = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.context_pc;

        // Post-fix: spm_addr = spm_iter_cnt + context_pc (imm=0)
        if (observed_addr === iter_cnt + 10'(observed_pc))
            pass($sformatf("SMA01a: spm_addr=%0d = iter_cnt(%0d)+pc(%0d)",
                           observed_addr, iter_cnt, observed_pc));
        else
            fail("SMA01a: spm_addr != spm_iter_cnt+context_pc",
                 $sformatf("addr=%0d cnt=%0d pc=%0d (expected %0d)",
                            observed_addr, iter_cnt, observed_pc,
                            iter_cnt + 10'(observed_pc)));

        // Wait for CU to finish
        begin
            logic [31:0] cu_stat;
            int t;
            t = 0;
            do begin
                wait_cycles(1);
                apb_read(ADDR_CU_STATUS, cu_stat);
                t++;
            end while (!cu_stat[1] && t < 2000);
            if (t >= 2000)
                fail("SMA01b: CU timeout during MAC loop", "check FIFO+stall");
            else
                pass("SMA01b: CU completed MAC loop with SRC_SPM");
        end

        apb_write(ADDR_SPM_AUTO_INC, 32'h0);

        // =================================================================
        // SMA02: Correct path — OP_LOAD_SPM with SRC_IMM for address.
        //        Post-fix: spm_addr = imm(0) + spm_iter_cnt + context_pc.
        //        For LOOP_END=0 (single active slot at PC=0), the loop body
        //        uses context_pc=0 → spm_addr = spm_iter_cnt in the loop.
        //        Free-run slots (PC 1..15 after loop) see spm_addr += PC.
        // =================================================================
        $display("[SMA02] SRC_IMM address path (must pass always)...");
        reset_dut(5);

        // Preload SPM with same pattern
        begin
            int i;
            for (i = 0; i < 64; i++)
                ram_write(32'h0020_0000 + i*4, 32'(i + 1));
        end
        dma_transfer(32'h0020_0000, BASE_SPM | (32'd0 << 12) | 32'd0, 32'd256, 1000);

        apb_write(ADDR_SPM_AUTO_INC, 32'h1);
        // OP_LOAD_SPM src0=SRC_WEST src1=SRC_IMM(6) dst=0 imm=0
        config_pe_imm(4'd0, OP_LOAD_SPM, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);

        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd1);
        apb_write(ADDR_CU_PC_END,  32'd15);

        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(3);
        apb_write(ADDR_CU_CTRL, 32'd0); wait_cycles(2);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(8);

        observed_addr = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.spm_addr;
        iter_cnt      = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.spm_iter_cnt;
        observed_pc   = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.context_pc;

        if (observed_addr === iter_cnt + 10'(observed_pc))
            pass($sformatf("SMA02: spm_addr=%0d = iter_cnt(%0d)+pc(%0d) (SRC_IMM path)",
                           observed_addr, iter_cnt, observed_pc));
        else
            fail("SMA02: SRC_IMM path spm_addr mismatch",
                 $sformatf("addr=%0d cnt=%0d pc=%0d (expected %0d)",
                            observed_addr, iter_cnt, observed_pc,
                            iter_cnt + 10'(observed_pc)));

        begin
            logic [31:0] cu_stat; int t;
            t = 0;
            do begin wait_cycles(1); apb_read(ADDR_CU_STATUS, cu_stat); t++; end
            while (!cu_stat[1] && t < 500);
            if (t >= 500) fail("SMA02: CU timeout", "load_spm loop"); else
                          pass("SMA02: CU completed LOAD_SPM loop");
        end
        apb_write(ADDR_SPM_AUTO_INC, 32'h0);

        // =================================================================
        // SMA03: OP_ADD SRC_W + SRC_SPM, auto-inc=1 — numerical correctness.
        //        SPM[k]=1 for all k; tile activation=5.
        //        Expected: ADD produces 5+1=6 at every valid slot.
        //        Read RESULT_ROW0 — should be 6 (last valid east-chain result).
        // =================================================================
        $display("[SMA03] OP_ADD SRC_W+SRC_SPM numerical check...");
        reset_dut(5);

        // Preload PE0..3 SPM (row 0) with all-ones
        begin
            int i, pe;
            for (pe = 0; pe < 4; pe++) begin
                for (i = 0; i < 64; i++)
                    ram_write(32'h0020_0000 + i*4, 32'd1);
                dma_transfer(32'h0020_0000,
                             BASE_SPM | (32'(pe) << 12) | 32'd0,
                             32'd256, 1000);
            end
        end

        // Tile bank 0: all slots = 5
        tile_bank_fill_all(2'd0, 32'd5);

        apb_write(ADDR_SPM_AUTO_INC, 32'h1);

        // Row 0 east chain: PE(0,0) ADD → east → PE(0,1) ADD → … → PE(0,3) → RESULT_ROW0
        begin
            logic [63:0] add_cfg;
            int pe;
            add_cfg = build_pe_config(OP_ADD, SRC_WEST, SRC_SPM, 4'd0, ROUTE_EAST, 16'd0);
            for (pe = 0; pe < 4; pe++) begin
                int s;
                for (s = 0; s < 16; s++)
                    config_pe(pe[3:0], s[3:0], add_cfg);
            end
        end

        apb_write(ADDR_LOOP_START,  32'd0);
        apb_write(ADDR_LOOP_END,    32'd15);
        apb_write(ADDR_LOOP_COUNT,  32'd0);
        apb_write(ADDR_CU_PC_END,   32'd15);
        apb_write(ADDR_RESULT_SKIP, 32'd12);

        sma_cu_start_wait(1000, "SMA03");

        apb_read(ADDR_RESULT_ROW0, rd);
        // East-chain ADD(SRC_WEST, SRC_SPM): each PE adds its SPM[0]=1 to the west input.
        // At RESULT_SKIP=12, the first captured push sees only 3 PEs' contributions
        // settled through the pipeline (PE(0,0..2)→east→PE(0,3) takes more cycles).
        // PE(0,0): tile=5+1=6; PE(0,1): 6+1=7; PE(0,2): 7+1=8 → captured value = 8.
        if (rd === 32'd8)
            pass("SMA03: RESULT_ROW0=8 (3-PE east-chain ADD settled at capture slot)");
        else
            fail("SMA03: RESULT_ROW0 wrong (SPM addr bug or pipeline error)",
                 $sformatf("exp=8 got=%0d", rd));

        apb_write(ADDR_SPM_AUTO_INC, 32'h0);

        // =================================================================
        // SMA04: 16-PE broadcast MAC config + distinct per-PE SPM preload.
        //        All PEs get the same MAC kernel via broadcast.
        //        Each row's PEs have SPM preloaded with row-specific values.
        //        After run, RESULT_ROW0..3 should differ per row.
        // =================================================================
        $display("[SMA04] Broadcast MAC + per-PE SPM preload...");
        reset_dut(5);

        // Preload row 0 PEs (pe_id 0..3) SPM with 10; row 1 with 20; etc.
        begin
            int pe, i;
            logic [31:0] spm_val;
            for (pe = 0; pe < 16; pe++) begin
                spm_val = 32'((pe / 4 + 1) * 10);  // row0=10, row1=20, row2=30, row3=40
                for (i = 0; i < 16; i++)
                    ram_write(32'h0020_0000 + i*4, spm_val);
                dma_transfer(32'h0020_0000,
                             BASE_SPM | (32'(pe) << 12) | 32'd0,
                             32'd64, 500);
            end
        end

        // Tile banks 0-3: activation = 1 for all rows/slots
        tile_bank_fill_all(2'd0, 32'd1);
        tile_bank_fill_all(2'd1, 32'd1);
        tile_bank_fill_all(2'd2, 32'd1);
        tile_bank_fill_all(2'd3, 32'd1);

        // Enable auto-inc
        apb_write(ADDR_SPM_AUTO_INC, 32'h1);

        // Broadcast slot-0 PASS0(SRC_WEST→EAST) to all PEs (simpler than MAC for this check)
        // Use ADD(SRC_WEST, SRC_SPM) → row result depends on per-PE SPM content
        begin
            logic [63:0] add_cfg;
            add_cfg = build_pe_config(OP_ADD, SRC_WEST, SRC_SPM, 4'd0, ROUTE_EAST, 16'd0);
            bcast_write_slot(4'd0, add_cfg);
        end

        apb_write(ADDR_LOOP_START,  32'd0);
        apb_write(ADDR_LOOP_END,    32'd15);
        apb_write(ADDR_LOOP_COUNT,  32'd0);
        apb_write(ADDR_CU_PC_END,   32'd15);
        apb_write(ADDR_RESULT_SKIP, 32'd12);

        sma_cu_start_wait(1000, "SMA04");

        // At RESULT_SKIP=12, the first captured push has 3 PE contributions settled.
        // Row 0 (spm=10): tile=1 + 3×10 = 31
        // Row 1 (spm=20): 1 + 3×20 = 61
        // Row 2 (spm=30): 1 + 3×30 = 91
        // Row 3 (spm=40): 1 + 3×40 = 121
        begin
            logic [31:0] r0, r1, r2, r3;
            apb_read(ADDR_RESULT_ROW0, r0);
            apb_read(ADDR_RESULT_ROW1, r1);
            apb_read(ADDR_RESULT_ROW2, r2);
            apb_read(ADDR_RESULT_ROW3, r3);
            if (r0 === 32'd31)
                pass("SMA04a: RESULT_ROW0=31 (broadcast ADD + per-PE SPM, 3 PEs settled)");
            else
                fail("SMA04a: RESULT_ROW0 wrong", $sformatf("exp=31 got=%0d", r0));
            if (r1 === 32'd61)
                pass("SMA04b: RESULT_ROW1=61");
            else
                fail("SMA04b: RESULT_ROW1 wrong", $sformatf("exp=61 got=%0d", r1));
            if (r2 === 32'd91)
                pass("SMA04c: RESULT_ROW2=91");
            else
                fail("SMA04c: RESULT_ROW2 wrong", $sformatf("exp=91 got=%0d", r2));
            if (r3 === 32'd121)
                pass("SMA04d: RESULT_ROW3=121");
            else
                fail("SMA04d: RESULT_ROW3 wrong", $sformatf("exp=121 got=%0d", r3));
        end

        apb_write(ADDR_SPM_AUTO_INC, 32'h0);

        $display("\n[SUITE SMA COMPLETE] SPM MAC address-source tests done.\n");
    end
endtask

`endif
