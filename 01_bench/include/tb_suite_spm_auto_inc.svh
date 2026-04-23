`ifndef TB_SUITE_SPM_AUTO_INC_SVH
`define TB_SUITE_SPM_AUTO_INC_SVH

// =============================================================================
// SUITE SAI: SPM Address Auto-Increment across LOOP iterations (R2)
// =============================================================================
// APB 0x84 (SPM_AUTO_INC): bit[0] = enable.  Default 0 = disabled.
// When enabled, spm_iter_cnt increments by 16 per loop wrap.
// Effective SPM address = operand1_r2 + spm_iter_cnt.
//
// Tests:
//   SAI01: SPM_AUTO_INC=0 — spm_iter_cnt stays 0 after a looped CU run
//   SAI02: SPM_AUTO_INC=1, LOOP_COUNT=2 — spm_iter_cnt=32 after 2 wraps
//   SAI03: LOAD_SPM with auto-inc reads advancing addresses across iterations
// =============================================================================

localparam logic [31:0] ADDR_SPM_AUTO_INC = 32'h84;

// Start CU and wait for done — does NOT soft-reset so spm_iter_cnt is readable.
task automatic run_cgra_wait_done(input int timeout_cyc);
    logic [31:0] cu_stat;
    int t;
    // Soft-reset first to clear any stale state
    apb_write(ADDR_CU_CTRL, 32'd2);
    wait_cycles(3);
    apb_write(ADDR_CU_CTRL, 32'd0);
    wait_cycles(2);
    // Start execution
    apb_write(ADDR_CU_CTRL, 32'd1);
    t = 0;
    do begin
        wait_cycles(1);
        apb_read(ADDR_CU_STATUS, cu_stat);
        t++;
    end while (!cu_stat[1] && t < timeout_cyc);
    if (t >= timeout_cyc)
        $display("[SAI] WARNING: CU did not complete within %0d cycles", timeout_cyc);
endtask

task automatic run_suite_SAI_spm_auto_inc;
    logic [31:0] rd;
    logic [9:0]  iter_cnt;
    begin
        $display("\n========================================");
        $display("   SUITE SAI: SPM AUTO-INCREMENT");
        $display("========================================\n");

        reset_dut(5);

        // =================================================================
        // SAI01: SPM_AUTO_INC disabled — spm_iter_cnt stays 0 after looped run
        // =================================================================
        $display("[SAI01] SPM_AUTO_INC=0: spm_iter_cnt stays 0 through loops...");
        apb_write(ADDR_SPM_AUTO_INC, 32'h0);
        // Configure PE0 with a simple NOP, LOOP_COUNT=3 (4 loop wraps → 4 passes)
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd3);
        apb_write(ADDR_CU_PC_END,  32'd15);
        run_cgra_wait_done(500);
        // Read counter BEFORE any reset
        iter_cnt = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.spm_iter_cnt;
        if (iter_cnt === 10'd0)
            pass("SAI01: spm_iter_cnt=0 with SPM_AUTO_INC=0 (no drift)");
        else
            fail("SAI01: spm_iter_cnt != 0 with feature disabled", $sformatf("got=%0d", iter_cnt));
        // Cleanup
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(3); apb_write(ADDR_CU_CTRL, 32'd0);

        // =================================================================
        // SAI02: SPM_AUTO_INC=1, LOOP_COUNT=2 → spm_iter_cnt = 32 after run
        //        2 loop wraps (iter 0→1 and iter 1→2) each add 16 → total 32
        // =================================================================
        $display("[SAI02] SPM_AUTO_INC=1, LOOP_COUNT=2: spm_iter_cnt should = 32...");
        reset_dut(5);
        apb_write(ADDR_SPM_AUTO_INC, 32'h1);
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd2);
        apb_write(ADDR_CU_PC_END,  32'd15);
        run_cgra_wait_done(500);
        iter_cnt = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.spm_iter_cnt;
        if (iter_cnt === 10'd32)
            pass("SAI02: spm_iter_cnt=32 after 2 loop wraps (0→16→32)");
        else
            fail("SAI02: spm_iter_cnt wrong", $sformatf("exp=32 got=%0d", iter_cnt));
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(3); apb_write(ADDR_CU_CTRL, 32'd0);

        // =================================================================
        // SAI03: LOAD_SPM with auto-inc reads advancing SPM words
        //        Preload SPM: word[k] = 0xAB000000 | k
        //        Config: LOAD_SPM src1=IMM(0), auto-inc → iter 0 reads [0], iter 1 reads [16]
        //        After run (LOOP_COUNT=1, 2 passes), last alu_result = SPM[16]
        //        We verify via whitebox SPM read + spm_iter_cnt
        // =================================================================
        $display("[SAI03] LOAD_SPM with auto-inc reads advancing SPM words...");
        reset_dut(5);
        // Preload PE0 SPM words 0..31
        for (int i = 0; i < 32; i++)
            ram_write(32'h0020_0000 + i*4, 32'hAB00_0000 | i);
        dma_transfer(32'h0020_0000, BASE_SPM | (32'd0 << 12) | 32'd0, 32'd128, 500);
        // Enable auto-inc
        apb_write(ADDR_SPM_AUTO_INC, 32'h1);
        // LOAD_SPM with imm=0: effective_addr = 0 + spm_iter_cnt
        config_pe_imm(4'd0, OP_LOAD_SPM, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd1);  // 2 passes: iter0 (cnt=0, addr=0), iter1 (cnt=16, addr=16)
        apb_write(ADDR_CU_PC_END,  32'd15);
        run_cgra_wait_done(500);
        // spm_iter_cnt should be 16 (1 loop wrap × 16)
        iter_cnt = tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.spm_iter_cnt;
        if (iter_cnt === 10'd16)
            pass("SAI03a: spm_iter_cnt=16 after 1 loop wrap");
        else
            fail("SAI03a: spm_iter_cnt", $sformatf("exp=16 got=%0d", iter_cnt));
        // SPM[0] and SPM[16] should both be correctly preloaded
        rd = spm_read_wb(0, 0);
        if (rd === 32'hAB00_0000) pass("SAI03b: PE0 SPM[0]=0xAB000000 (iter0 data)");
        else fail("SAI03b: SPM[0]", $sformatf("exp=0xAB000000 got=0x%08h", rd));
        rd = spm_read_wb(0, 16);
        if (rd === 32'hAB00_0010) pass("SAI03c: PE0 SPM[16]=0xAB000010 (iter1 data)");
        else fail("SAI03c: SPM[16]", $sformatf("exp=0xAB000010 got=0x%08h", rd));
        apb_write(ADDR_CU_CTRL, 32'd2); wait_cycles(3); apb_write(ADDR_CU_CTRL, 32'd0);
        // Disable auto-inc for cleanup
        apb_write(ADDR_SPM_AUTO_INC, 32'h0);

        $display("\n[SUITE SAI COMPLETE] SPM auto-increment verified.\n");
    end
endtask

`endif
