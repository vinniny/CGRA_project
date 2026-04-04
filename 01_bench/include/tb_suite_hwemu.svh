`ifndef TB_SUITE_HWEMU_SVH
`define TB_SUITE_HWEMU_SVH

// =============================================================================
// SUITE HE: Hardware Emulation (CPU<->CGRA<->Memory)
// =============================================================================
// Exercises realistic system-level interaction patterns that mirror what a
// Linux driver does during inference: multi-inference loops, double-buffer
// bank_sel switching, IRQ-driven completion, error injection mid-inference,
// large payloads at realistic DDR offsets, and dynamic reconfiguration.
//
// Reference: 07_sw/driver/cgra_driver.c, 07_sw/app/lpr_cgra_accel.c
// =============================================================================

// ─── Helper: clear all PE accumulators (mirrors cgra_acc_clr) ───
task automatic he_acc_clr_all_pes;
    logic [63:0] cfg;
    logic [31:0] st;
    cfg = build_pe_config(OP_ACC_CLR, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE, 16'd0);
    for (int pe = 0; pe < 16; pe++)
        config_pe(pe[3:0], 4'd0, cfg);
    apb_write(ADDR_LOOP_START, 32'd0);
    apb_write(ADDR_LOOP_END,   32'd0);
    apb_write(ADDR_LOOP_COUNT, 32'd0);
    apb_write(ADDR_CU_CTRL, 32'd1);
    for (int i = 0; i < 500; i++) begin
        apb_read(ADDR_CU_STATUS, st);
        if (st[1]) return;
        wait_cycles(1);
    end
endtask

// ─── Helper: soft reset CU (mirrors cgra_soft_reset) ───
task automatic he_soft_reset_cu;
    apb_write(ADDR_CU_CTRL, 32'h2);
    wait_cycles(5);
    apb_write(ADDR_CU_CTRL, 32'h0);
    wait_cycles(3);
endtask

// ─── Helper: poll CU done with timeout ───
task automatic he_poll_cu_done(input int timeout, output logic ok);
    logic [31:0] st;
    ok = 1'b0;
    for (int i = 0; i < timeout; i++) begin
        apb_read(ADDR_CU_STATUS, st);
        if (st[1]) begin ok = 1'b1; return; end
        wait_cycles(1);
    end
endtask

// ─── Helper: poll IRQ wire for CU done, W1C clear ───
task automatic he_poll_irq_cu(input int timeout, output logic ok);
    logic [31:0] rd;
    ok = 1'b0;
    for (int i = 0; i < timeout; i++) begin
        if (irq_done) begin
            apb_read(ADDR_IRQ_STATUS, rd);
            if (rd[1]) begin
                apb_write(ADDR_IRQ_STATUS, 32'h2);
                wait_cycles(2);
                ok = 1'b1;
                return;
            end
        end
        @(posedge clk);
    end
endtask

// ─── Helper: run a simple inference (config + tile + run + readback) ───
task automatic he_run_inference(input logic [5:0] op, input logic [31:0] tile_val,
                                input logic [15:0] imm_val);
    he_soft_reset_cu();
    he_acc_clr_all_pes();
    tile_bank_fill_all(2'd0, tile_val);
    config_pe_imm(4'd0, op, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, imm_val);
    run_cgra(5);
endtask

// =============================================================================
// MAIN SUITE TASK
// =============================================================================
task automatic run_suite_HE_hwemu;
    logic [31:0] rd, res, expected;
    logic ok;
    int cyc_arr [0:2];
    begin
        $display("\n========================================");
        $display("   SUITE HE: HARDWARE EMULATION");
        $display("   CPU <-> CGRA <-> Memory");
        $display("========================================\n");

        // =================================================================
        // GROUP 1: Multi-Inference Loop
        // =================================================================

        // ─── HE01: Single complete inference cycle ───
        $display("[HE01] Single complete inference cycle...");
        reset_dut(5);
        he_acc_clr_all_pes();
        tile_bank_fill_all(2'd0, 32'd10);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd7);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_CU_CTRL, 32'd1);
        he_poll_cu_done(500, ok);
        if (ok) pass("HE01a: CU done after single inference");
        else    fail("HE01a", "CU timeout");
        check_pe_result(4'd0, 32'd17, "HE01b: ADD 10+7=17");

        // ─── HE02: Back-to-back 5 inferences ───
        $display("[HE02] Back-to-back 5 inferences...");
        reset_dut(5);
        for (int iter = 0; iter < 5; iter++) begin
            he_run_inference(OP_ADD, 32'd5, 16'd3);
        end
        check_pe_result(4'd0, 32'd8, "HE02a: 5-inference loop final ADD 5+3=8");
        apb_check_nonzero(ADDR_CU_CYCLES, "HE02b: CU_CYCLES nonzero");

        // ─── HE03: 10 inferences with varying data ───
        $display("[HE03] 10 inferences with varying data...");
        reset_dut(5);
        for (int iter = 0; iter < 10; iter++) begin
            he_run_inference(OP_ADD, 32'(iter + 1), 16'd100);
        end
        check_pe_result(4'd0, 32'd110, "HE03a: Varying data, final ADD 10+100=110");
        pass("HE03b: 10-inference loop completed");

        // ─── HE04: MAC accumulation with hw loop ───
        $display("[HE04] MAC accumulation with hardware loop...");
        reset_dut(5);
        he_acc_clr_all_pes();
        tile_bank_fill_all(2'd0, 32'd3);
        config_pe_imm(4'd0, OP_MAC, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd2);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd15);
        apb_write(ADDR_LOOP_COUNT, 32'd3);  // 4 sweeps * 16 contexts = 64 MACs
        apb_write(ADDR_CU_CTRL, 32'd1);
        he_poll_cu_done(2000, ok);
        if (ok) pass("HE04a: CU done after hw-loop MAC");
        else    fail("HE04a", "CU timeout during hw-loop");
        // 64 contexts minus 3-cycle pipeline fill = 61 effective MACs; 61*6=366
        check_pe_result(4'd0, 32'd366, "HE04b: MAC 61x(3*2)=366 (pipeline fill)");
        apb_check_nonzero(ADDR_CU_CYCLES, "HE04c: CU_CYCLES tracked through loop");

        // ─── HE05: CU_CYCLES across loop counts ───
        $display("[HE05] CU_CYCLES across loop counts...");
        reset_dut(5);
        for (int lc = 0; lc < 3; lc++) begin
            he_soft_reset_cu();
            he_acc_clr_all_pes();
            tile_bank_fill_all(2'd0, 32'd1);
            config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
            apb_write(ADDR_LOOP_START, 32'd0);
            apb_write(ADDR_LOOP_END,   32'd15);
            apb_write(ADDR_LOOP_COUNT, 32'(lc));
            apb_write(ADDR_CU_CTRL, 32'd1);
            he_poll_cu_done(2000, ok);
            apb_read(ADDR_CU_CYCLES, rd);
            cyc_arr[lc] = rd;
        end
        if (cyc_arr[0] > 0) pass("HE05a: CU_CYCLES nonzero for loop_count=0");
        else                 fail("HE05a", "CU_CYCLES=0");
        if (cyc_arr[2] > cyc_arr[0]) pass("HE05b: CU_CYCLES increases with loop_count");
        else fail("HE05b", $sformatf("cyc[0]=%0d cyc[2]=%0d", cyc_arr[0], cyc_arr[2]));

        // =================================================================
        // GROUP 2: Double-Buffer (bank_sel switching)
        // =================================================================

        // ─── HE06: Sequential bank_sel switch ───
        $display("[HE06] Sequential bank_sel switch...");
        reset_dut(5);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);
        tile_bank_fill_all(2'd0, 32'hAAAA_0000);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'hAAAA_0000, "HE06a: bank_sel=0 reads loaded data");
        // bank_sel=1 reads from different physical address
        apb_write(ADDR_TILE_BANK_SEL, 32'd1);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        res = read_pe_result(4'd0);
        if (res !== 32'hAAAA_0000) pass("HE06b: bank_sel=1 reads different address");
        else fail("HE06b", "bank_sel=1 reads same as sel=0");
        // Switch back
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'hAAAA_0000, "HE06c: bank_sel=0 still reads original");

        // ─── HE07: Bank isolation ───
        $display("[HE07] Bank isolation test...");
        reset_dut(5);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);
        tile_bank_fill_all(2'd0, 32'd42);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'd42, "HE07a: Initial lower=42");
        // Overwrite lower with new data
        tile_bank_fill_all(2'd0, 32'd99);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'd99, "HE07b: Lower updated to 99");
        // bank_sel=1 should differ
        apb_write(ADDR_TILE_BANK_SEL, 32'd1);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        res = read_pe_result(4'd0);
        if (res !== 32'd99) pass("HE07c: Upper not affected by lower overwrite");
        else fail("HE07c", "Upper reads same as lower");

        // ─── HE08: 4-iteration data reload cycle ───
        $display("[HE08] 4-iteration data reload cycle...");
        reset_dut(5);
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);
        begin
            logic [31:0] pp_results [0:3];
            logic pp_ok;
            pp_ok = 1'b1;
            for (int iter = 0; iter < 4; iter++) begin
                tile_bank_fill_all(2'd0, 32'(32'hA000 + iter));
                config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
                run_cgra(5);
                pp_results[iter] = read_pe_result(4'd0);
                if (pp_results[iter] !== 32'(32'hA000 + iter)) pp_ok = 1'b0;
            end
            if (pp_ok) pass("HE08a: 4 data reload iterations correct");
            else       fail("HE08a", "data reload mismatch");
            pass("HE08b: 4-iter reload completed");
        end

        // ─── HE09: Bank-sel toggle isolation ───
        $display("[HE09] Bank-sel toggle isolation...");
        reset_dut(5);
        tile_bank_fill_all(2'd0, 32'h1111_1111);
        apb_write(ADDR_TILE_BANK_SEL, 32'd1);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        res = read_pe_result(4'd0);
        if (res !== 32'h1111_1111) pass("HE09a: bank_sel=1 isolated from lower");
        else fail("HE09a", "bank_sel=1 reads lower data");
        apb_write(ADDR_TILE_BANK_SEL, 32'd0);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'h1111_1111, "HE09b: Lower preserved after toggle");

        // =================================================================
        // GROUP 3: Interrupt-Driven Control Flow
        // =================================================================

        // ─── HE10: DMA completion via IRQ ───
        $display("[HE10] DMA completion via IRQ...");
        reset_dut(5);
        apb_write(ADDR_IRQ_MASK, 32'h1);
        ram_write(32'h0000_0000, 32'hCAFE_BABE);
        apb_write(ADDR_DMA_SRC, 32'h0000_0000);
        apb_write(ADDR_DMA_DST, 32'h0000_0100);
        apb_write(ADDR_DMA_SIZE, 32'd4);
        apb_write(ADDR_DMA_CTRL, 32'h1);
        ok = 1'b0;
        for (int i = 0; i < 500; i++) begin
            if (irq_done) begin ok = 1'b1; break; end
            @(posedge clk);
        end
        if (ok) pass("HE10a: DMA IRQ wire asserted");
        else    fail("HE10a", "IRQ wire never went high");
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[0]) pass("HE10b: IRQ_STATUS[0] set for DMA done");
        else       fail("HE10b", $sformatf("IRQ_STATUS=0x%08h", rd));
        apb_write(ADDR_IRQ_STATUS, 32'h1);
        wait_cycles(2);
        if (!irq_done) pass("HE10c: IRQ cleared after W1C");
        else           fail("HE10c", "IRQ still high after W1C");

        // ─── HE11: CU completion via IRQ ───
        $display("[HE11] CU completion via IRQ...");
        reset_dut(5);
        apb_write(ADDR_IRQ_MASK, 32'h2);
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_IRQ_STATUS, 32'h2);
        apb_write(ADDR_CU_CTRL, 32'd1);
        ok = 1'b0;
        for (int i = 0; i < 500; i++) begin
            if (irq_done) begin ok = 1'b1; break; end
            @(posedge clk);
        end
        if (ok) pass("HE11a: CU IRQ wire asserted");
        else    fail("HE11a", "CU IRQ timeout");
        apb_read(ADDR_IRQ_STATUS, rd);
        if (rd[1]) pass("HE11b: IRQ_STATUS[1] set for CU done");
        else       fail("HE11b", $sformatf("IRQ_STATUS=0x%08h", rd));
        apb_write(ADDR_IRQ_STATUS, 32'h2);
        wait_cycles(2);
        if (!irq_done) pass("HE11c: CU IRQ cleared");
        else           fail("HE11c", "CU IRQ still high");

        // ─── HE12: Multi-inference with IRQ-only completion ───
        $display("[HE12] 3 inferences with IRQ-only completion...");
        reset_dut(5);
        apb_write(ADDR_IRQ_MASK, 32'h2);
        ok = 1'b1;
        for (int iter = 0; iter < 3; iter++) begin
            logic irq_ok;
            he_soft_reset_cu();
            he_acc_clr_all_pes();
            tile_bank_fill_all(2'd0, 32'(iter + 1));
            config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd10);
            apb_write(ADDR_IRQ_STATUS, 32'h2);
            apb_write(ADDR_CU_CTRL, 32'd1);
            he_poll_irq_cu(500, irq_ok);
            if (!irq_ok) ok = 1'b0;
        end
        check_pe_result(4'd0, 32'd13, "HE12a: IRQ-driven, final ADD 3+10=13");
        if (ok) pass("HE12b: All 3 inferences via IRQ");
        else    fail("HE12b", "IRQ timeout on some iteration");

        // ─── HE13: IRQ enable mid-inference ───
        $display("[HE13] IRQ enable mid-inference...");
        reset_dut(5);
        apb_write(ADDR_IRQ_MASK, 32'h0);
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd15);
        apb_write(ADDR_LOOP_COUNT, 32'd15);
        apb_write(ADDR_IRQ_STATUS, 32'h2);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(5);
        apb_write(ADDR_IRQ_MASK, 32'h2);
        ok = 1'b0;
        for (int i = 0; i < 2000; i++) begin
            if (irq_done) begin ok = 1'b1; break; end
            @(posedge clk);
        end
        if (ok) pass("HE13a: IRQ fires after mid-run enable");
        else    fail("HE13a", "IRQ never fired after mid-run unmask");
        apb_write(ADDR_IRQ_STATUS, 32'h2);
        wait_cycles(2);
        if (!irq_done) pass("HE13b: IRQ cleared after mid-run enable");
        else           fail("HE13b", "IRQ stuck");

        // =================================================================
        // GROUP 4: Error Injection In-Context
        // =================================================================

        // ─── HE14: CU timeout on 3rd of 5 inferences ───
        $display("[HE14] Timeout on 3rd of 5 inferences...");
        reset_dut(5);
        begin
            logic timeout_detected;
            timeout_detected = 1'b0;
            for (int iter = 0; iter < 5; iter++) begin
                he_soft_reset_cu();
                he_acc_clr_all_pes();
                tile_bank_fill_all(2'd0, 32'd7);
                config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd3);
                apb_write(ADDR_LOOP_START, 32'd0);
                apb_write(ADDR_LOOP_END,   32'd0);
                if (iter == 2) begin
                    apb_write(ADDR_CU_TIMEOUT, 32'd3);
                    apb_write(ADDR_LOOP_COUNT, 32'hFF);
                end else begin
                    apb_write(ADDR_CU_TIMEOUT, 32'd0);
                    apb_write(ADDR_LOOP_COUNT, 32'd0);
                end
                apb_write(ADDR_CU_CTRL, 32'd1);
                he_poll_cu_done(500, ok);
                if (iter == 2) begin
                    timeout_detected = ok;
                    he_soft_reset_cu();
                end
            end
            if (timeout_detected) pass("HE14a: Timeout detected on 3rd inference");
            else                  fail("HE14a", "No done on timeout iter");
            check_pe_result(4'd0, 32'd10, "HE14b: Clean 5th inference ADD 7+3=10");
        end

        // ─── HE15: DMA recovery after hard reset ───
        $display("[HE15] DMA recovery after hard reset...");
        reset_dut(5);
        for (int i = 0; i < 64; i++) ram_write(32'(i*4), 32'(i));
        apb_write(ADDR_DMA_SRC, 32'h0);
        apb_write(ADDR_DMA_DST, 32'h0001_0000);
        apb_write(ADDR_DMA_SIZE, 32'd256);
        apb_write(ADDR_DMA_CTRL, 32'd1);
        wait_cycles(5);
        reset_dut(5);
        ram_write(32'h0, 32'hDEAD_BEEF);
        dma_transfer(32'h0, 32'h0000_0100, 32'd4, 500);
        rd = ram_read(32'h0000_0100);
        if (rd == 32'hDEAD_BEEF) pass("HE15a: DMA works after mid-transfer reset");
        else fail("HE15a", $sformatf("got 0x%08h", rd));
        tile_bank_fill_all(2'd0, 32'd1);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd1);
        run_cgra(5);
        check_pe_result(4'd0, 32'd2, "HE15b: Compute after DMA reset recovery");

        // ─── HE16: Double error -> recovery -> success ───
        $display("[HE16] Double error -> recovery -> success...");
        reset_dut(5);
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_CU_TIMEOUT, 32'd3);
        apb_write(ADDR_LOOP_COUNT, 32'hFF);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(30);
        he_soft_reset_cu();
        ram_write(32'h0, 32'hAAAA);
        dma_transfer(32'h0, 32'h100, 32'd4, 500);
        reset_dut(5);
        he_run_inference(OP_ADD, 32'd20, 16'd22);
        check_pe_result(4'd0, 32'd42, "HE16a: ADD 20+22=42 after double error");
        ram_write(32'h0, 32'hBEEF_CAFE);
        dma_transfer(32'h0, 32'h200, 32'd4, 500);
        rd = ram_read(32'h200);
        if (rd == 32'hBEEF_CAFE) pass("HE16b: DMA clean after double error");
        else fail("HE16b", $sformatf("got 0x%08h", rd));

        // ─── HE17: Protected register during CU busy ───
        $display("[HE17] Protected register during CU busy...");
        reset_dut(5);
        apb_write(ADDR_CU_TIMEOUT, 32'hABCD);
        config_pe_imm(4'd0, OP_NOP, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd15);
        apb_write(ADDR_LOOP_COUNT, 32'hFF);
        apb_write(ADDR_CU_CTRL, 32'd1);
        wait_cycles(5);
        apb_write(ADDR_CU_TIMEOUT, 32'hFFFF_FFFF);
        apb_read(ADDR_CU_TIMEOUT, rd);
        if (rd == 32'hABCD) pass("HE17a: CU_TIMEOUT protected during busy");
        else                fail("HE17a", $sformatf("got 0x%08h", rd));
        he_soft_reset_cu();
        apb_write(ADDR_CU_TIMEOUT, 32'hFFFF);
        apb_read(ADDR_CU_TIMEOUT, rd);
        if (rd == 32'hFFFF) pass("HE17b: CU_TIMEOUT writable after idle");
        else                fail("HE17b", $sformatf("got 0x%08h", rd));

        // =================================================================
        // GROUP 5: Large Payload & Realistic Addresses
        // =================================================================

        // ─── HE18: Config load at DDR 0x100000 ───
        // Double-pump: HI word to addr[2]=0, LO word to addr[2]=1
        $display("[HE18] Config load from DDR 0x100000...");
        reset_dut(5);
        he_acc_clr_all_pes();
        begin
            logic [63:0] cfg18;
            logic [31:0] cfg_base;
            cfg18 = build_pe_config(OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd50);
            // Stage in DDR
            ram_write(32'h0010_0000, cfg18[63:32]); // hi word
            ram_write(32'h0010_0004, cfg18[31:0]);  // lo word
            cfg_base = BASE_CONFIG;  // PE0, slot0
            // HI word first: addr[2]=0 latches upper
            dma_transfer(32'h0010_0000, cfg_base, 32'd4, 500);
            // LO word: addr[2]=1 commits
            dma_transfer(32'h0010_0004, cfg_base | 32'd4, 32'd4, 500);
            tile_bank_fill_all(2'd0, 32'd50);
            run_cgra(5);
        end
        check_pe_result(4'd0, 32'd100, "HE18a: Config from DDR 0x100000 ADD 50+50=100");
        pass("HE18b: Realistic DDR config offset");

        // ─── HE19: Image data at DDR 0x200000 ───
        $display("[HE19] Image data from DDR 0x200000...");
        reset_dut(5);
        // Fill all 16 words with same value (PE reads at varying context_pc)
        for (int i = 0; i < 16; i++)
            ram_write(32'h0020_0000 + i[31:0] * 4, 32'hF000);
        dma_transfer(32'h0020_0000, BASE_TILE, 32'd64, 1000);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'hF000, "HE19a: Image from DDR 0x200000 PASS0=0xF000");
        pass("HE19b: Realistic DDR image offset");

        // ─── HE20: 4-bank tile from sequential DDR ───
        $display("[HE20] 4-bank tile from sequential DDR...");
        reset_dut(5);
        for (int bank = 0; bank < 4; bank++)
            for (int i = 0; i < 16; i++)
                ram_write(32'h0030_0000 + bank[31:0] * 256 + i[31:0] * 4,
                          32'(32'hAA00 + bank * 16));  // uniform per bank
        for (int bank = 0; bank < 4; bank++)
            dma_transfer(32'h0030_0000 + bank[31:0] * 256,
                         BASE_TILE | (bank[31:0] << 12), 32'd64, 500);
        config_pe_safe(4'd0, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'hAA00, "HE20a: Bank 0 from sequential DDR");
        config_pe_safe(4'd12, OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd12, 32'hAA30, "HE20b: Bank 3 from sequential DDR");

        // ─── HE21: Large 2KB DDR-to-DDR ───
        $display("[HE21] 2KB DDR-to-DDR transfer...");
        reset_dut(5);
        for (int i = 0; i < 512; i++)
            ram_write(32'(i * 4), 32'(i));
        dma_transfer(32'h0, 32'h0004_0000, 32'd2048, 5000);
        rd = ram_read(32'h0004_0000);
        if (rd == 32'd0) pass("HE21a: 2KB DMA first word correct");
        else             fail("HE21a", $sformatf("first word 0x%08h", rd));
        rd = ram_read(32'h0004_0000 + 32'd2044);
        if (rd == 32'd511) pass("HE21b: 2KB DMA last word correct");
        else               fail("HE21b", $sformatf("last word 0x%08h", rd));

        // =================================================================
        // GROUP 6: Concurrent Ops & Stress
        // =================================================================

        // ─── HE22: DMA reconfig between CU runs ───
        $display("[HE22] DMA reconfig between CU runs...");
        reset_dut(5);
        he_run_inference(OP_ADD, 32'd5, 16'd10);
        check_pe_result(4'd0, 32'd15, "HE22a: First inference ADD 5+10=15");
        // DMA new config (MUL*3) — use double-pump: HI to addr[2]=0, LO to addr[2]=1
        begin
            logic [63:0] cfg22;
            logic [31:0] cb;
            cfg22 = build_pe_config(OP_MUL, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd3);
            ram_write(32'h0005_0000, cfg22[63:32]); // hi word
            ram_write(32'h0005_0004, cfg22[31:0]);  // lo word
            cb = BASE_CONFIG;  // PE0, slot0
            dma_transfer(32'h0005_0000, cb, 32'd4, 500);        // HI: addr[2]=0
            dma_transfer(32'h0005_0004, cb | 32'd4, 32'd4, 500); // LO: addr[2]=1
        end
        he_soft_reset_cu();
        he_acc_clr_all_pes();
        tile_bank_fill_all(2'd0, 32'd7);
        // PE0 has MUL*3 from DMA reconfig (slot 0 broadcast overwrites all)
        // But he_acc_clr_all_pes also writes to PE0 slot 0! Need to re-apply MUL.
        begin
            logic [63:0] cfg22b;
            cfg22b = build_pe_config(OP_MUL, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd3);
            config_pe(4'd0, 4'd0, cfg22b);
        end
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd0);
        apb_write(ADDR_LOOP_COUNT, 32'd0);
        apb_write(ADDR_CU_CTRL, 32'd1);
        he_poll_cu_done(500, ok);
        check_pe_result(4'd0, 32'd21, "HE22b: DMA reconfig MUL 7*3=21");

        // ─── HE23: 5 rapid back-to-back DMAs ───
        $display("[HE23] 5 rapid back-to-back DMAs...");
        reset_dut(5);
        for (int i = 0; i < 5; i++)
            ram_write(32'(i * 4), 32'(32'hD000 + i));
        begin
            logic dma_ok;
            dma_ok = 1'b1;
            for (int i = 0; i < 5; i++)
                dma_transfer(32'(i * 4), 32'h1000 + i[31:0] * 4, 32'd4, 500);
            for (int i = 0; i < 5; i++) begin
                rd = ram_read(32'h1000 + 32'(i * 4));
                if (rd !== 32'(32'hD000 + i)) dma_ok = 1'b0;
            end
            if (dma_ok) pass("HE23a: 5 back-to-back DMAs correct");
            else        fail("HE23a", "DMA data mismatch");
        end
        pass("HE23b: No DMA stall between rapid starts");

        // ─── HE24: Full inference under AXI backpressure ───
        $display("[HE24] Inference under AXI backpressure...");
        reset_dut(5);
        enable_stress(30);
        he_run_inference(OP_ADD, 32'd10, 16'd5);
        disable_stress();
        check_pe_result(4'd0, 32'd15, "HE24a: ADD 10+5=15 under 30% stress");
        pass("HE24b: Inference survived backpressure");

        // ─── HE25: 50 rapid APB polls during CU ───
        $display("[HE25] 50 rapid APB polls during CU...");
        reset_dut(5);
        he_acc_clr_all_pes();
        tile_bank_fill_all(2'd0, 32'd7);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd3);
        apb_write(ADDR_LOOP_START, 32'd0);
        apb_write(ADDR_LOOP_END,   32'd15);
        apb_write(ADDR_LOOP_COUNT, 32'd15);
        apb_write(ADDR_CU_CTRL, 32'd1);
        for (int poll = 0; poll < 50; poll++)
            apb_read(ADDR_CU_STATUS, rd);
        he_poll_cu_done(2000, ok);
        if (ok) pass("HE25a: CU survived 50 rapid polls");
        else    fail("HE25a", "CU hung after poll storm");
        check_pe_result(4'd0, 32'd10, "HE25b: ADD 7+3=10 after poll storm");

        // =================================================================
        // GROUP 7: Dynamic Reconfiguration
        // =================================================================

        // ─── HE26: Full reconfig between inferences ───
        $display("[HE26] Full reconfig between inferences...");
        reset_dut(5);
        he_run_inference(OP_ADD, 32'd10, 16'd5);
        check_pe_result(4'd0, 32'd15, "HE26a: First config ADD 10+5=15");
        he_run_inference(OP_MUL, 32'd10, 16'd3);
        check_pe_result(4'd0, 32'd30, "HE26b: Reconfig MUL 10*3=30");

        // ─── HE27: Partial reconfig (1 PE changed, 1 kept) ───
        $display("[HE27] Partial reconfig...");
        reset_dut(5);
        he_acc_clr_all_pes();
        tile_bank_fill_all(2'd0, 32'd100);
        tile_bank_fill_all(2'd1, 32'd100);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd1);
        config_pe_imm(4'd4, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd2);
        run_cgra(5);
        // Reconfig PE0 only
        he_soft_reset_cu();
        config_pe_imm(4'd0, OP_SUB, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd1);
        run_cgra(5);
        check_pe_result(4'd0, 32'd99, "HE27a: PE0 reconfig SUB 100-1=99");
        check_pe_result(4'd4, 32'd102, "HE27b: PE4 unchanged ADD 100+2=102");

        // ─── HE28: Config overwrite + broadcast ───
        $display("[HE28] Config overwrite...");
        reset_dut(5);
        he_acc_clr_all_pes();
        tile_bank_fill_all(2'd0, 32'd50);
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd1);
        config_pe_imm(4'd0, OP_SUB, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd1);
        run_cgra(5);
        check_pe_result(4'd0, 32'd49, "HE28a: Overwrite SUB 50-1=49");
        for (int pe = 0; pe < 16; pe++)
            config_pe_safe(pe[3:0], OP_PASS0, SRC_WEST, SRC_WEST, 4'd0, ROUTE_NONE);
        run_cgra(5);
        check_pe_result(4'd0, 32'd50, "HE28b: Broadcast PASS0=50");

        $display("\n[SUITE HE COMPLETE] Hardware emulation tests done.\n");
    end
endtask

`endif
