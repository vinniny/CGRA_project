`ifndef TB_SUITE_SPM_DMA_SVH
`define TB_SUITE_SPM_DMA_SVH

// =============================================================================
// SUITE SPM_DMA: DMA → SPM Write Path Verification
// =============================================================================
// Verifies the R1 RTL feature: DMA→SPM write path (CGRA_PFX_SPM = 0x40000000).
// Address encoding: bits[31:28]=0x4 → DST_SPM, bits[15:12]=PE id, bits[11:2]=word.
//
// Tests:
//   SPM01: DMA 16 words to PE 0 SPM; read back word 0 via LOAD_SPM
//   SPM02: DMA to PE 7 SPM (non-zero PE id); whitebox check data integrity
//   SPM03: Non-zero word offset; verify word 5 is correct after DMA
//   SPM04: DMA→SPM does not corrupt existing PE config (config survives preload)
// =============================================================================

localparam logic [31:0] BASE_SPM = 32'h4000_0000;

// Whitebox SPM read helper: reads spm_mem[word] for a given PE via hierarchy.
function automatic logic [31:0] spm_read_wb(input int pe_id, input int word);
    case (pe_id)
        0:  return tb_top.u_dut.u_array.row[0].col[0].u_tile.u_pe.spm_mem[word];
        1:  return tb_top.u_dut.u_array.row[0].col[1].u_tile.u_pe.spm_mem[word];
        2:  return tb_top.u_dut.u_array.row[0].col[2].u_tile.u_pe.spm_mem[word];
        3:  return tb_top.u_dut.u_array.row[0].col[3].u_tile.u_pe.spm_mem[word];
        4:  return tb_top.u_dut.u_array.row[1].col[0].u_tile.u_pe.spm_mem[word];
        5:  return tb_top.u_dut.u_array.row[1].col[1].u_tile.u_pe.spm_mem[word];
        6:  return tb_top.u_dut.u_array.row[1].col[2].u_tile.u_pe.spm_mem[word];
        7:  return tb_top.u_dut.u_array.row[1].col[3].u_tile.u_pe.spm_mem[word];
        8:  return tb_top.u_dut.u_array.row[2].col[0].u_tile.u_pe.spm_mem[word];
        9:  return tb_top.u_dut.u_array.row[2].col[1].u_tile.u_pe.spm_mem[word];
        10: return tb_top.u_dut.u_array.row[2].col[2].u_tile.u_pe.spm_mem[word];
        11: return tb_top.u_dut.u_array.row[2].col[3].u_tile.u_pe.spm_mem[word];
        12: return tb_top.u_dut.u_array.row[3].col[0].u_tile.u_pe.spm_mem[word];
        13: return tb_top.u_dut.u_array.row[3].col[1].u_tile.u_pe.spm_mem[word];
        14: return tb_top.u_dut.u_array.row[3].col[2].u_tile.u_pe.spm_mem[word];
        15: return tb_top.u_dut.u_array.row[3].col[3].u_tile.u_pe.spm_mem[word];
        default: return 32'hDEAD_BEEF;
    endcase
endfunction

task automatic run_suite_SPM_dma;
    logic [31:0] rd;
    logic ok;
    begin
        $display("\n========================================");
        $display("   SUITE SPM_DMA: DMA->SPM PATH");
        $display("========================================\n");

        reset_dut(5);

        // =================================================================
        // SPM01: DMA 16 words DDR → PE 0 SPM[0..15]; read back via LOAD_SPM
        // =================================================================
        $display("[SPM01] DMA 16 words → PE0 SPM, LOAD_SPM readback...");
        // Write pattern to DDR at 0x0001_0000
        for (int i = 0; i < 16; i++)
            ram_write(32'h0001_0000 + i*4, 32'h5A00_0000 | i);
        // DMA DDR → PE 0 SPM starting at word 0
        dma_transfer(32'h0001_0000, BASE_SPM | (32'd0 << 12) | 32'd0, 32'd64, 1000);
        // Whitebox verify word 0 and word 15
        rd = spm_read_wb(0, 0);
        if (rd === 32'h5A00_0000)
            pass("SPM01a: PE0 SPM[0] = 0x5A000000 after DMA");
        else
            fail("SPM01a: PE0 SPM[0] after DMA", $sformatf("exp=0x5A000000 got=0x%08h", rd));
        rd = spm_read_wb(0, 15);
        if (rd === 32'h5A00_000F)
            pass("SPM01b: PE0 SPM[15] = 0x5A00000F after DMA");
        else
            fail("SPM01b: PE0 SPM[15] after DMA", $sformatf("exp=0x5A00000F got=0x%08h", rd));

        // Verify via LOAD_SPM instruction: configure PE0 to load SPM[0]
        config_pe_imm(4'd0, OP_LOAD_SPM, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd0);
        run_cgra(5);
        rd = read_pe_result(4'd0);
        if (rd === 32'h5A00_0000)
            pass("SPM01c: LOAD_SPM PE0[0] = 0x5A000000");
        else
            fail("SPM01c: LOAD_SPM PE0[0]", $sformatf("exp=0x5A000000 got=0x%08h", rd));

        // =================================================================
        // SPM02: DMA to PE 7 SPM; verify per-PE enable selectivity
        // =================================================================
        $display("[SPM02] DMA → PE7 SPM, verify PE0 not affected...");
        reset_dut(5);
        // Pre-fill PE0 SPM[0] with a sentinel
        for (int i = 0; i < 4; i++)
            ram_write(32'h0002_0000 + i*4, 32'hAA55_0000 | i);
        dma_transfer(32'h0002_0000, BASE_SPM | (32'd0 << 12) | 32'd0, 32'd16, 500);
        // Now DMA a different pattern to PE7 SPM[0..3]
        for (int i = 0; i < 4; i++)
            ram_write(32'h0003_0000 + i*4, 32'hBEEF_0000 | i);
        dma_transfer(32'h0003_0000, BASE_SPM | (32'd7 << 12) | 32'd0, 32'd16, 500);
        // PE7 SPM[0] must have new pattern
        rd = spm_read_wb(7, 0);
        if (rd === 32'hBEEF_0000)
            pass("SPM02a: PE7 SPM[0] = 0xBEEF0000");
        else
            fail("SPM02a: PE7 SPM[0]", $sformatf("exp=0xBEEF0000 got=0x%08h", rd));
        // PE0 SPM[0] must be unchanged (sentinel)
        rd = spm_read_wb(0, 0);
        if (rd === 32'hAA55_0000)
            pass("SPM02b: PE0 SPM[0] unchanged = 0xAA550000 (per-PE selectivity OK)");
        else
            fail("SPM02b: PE0 SPM[0] selectivity", $sformatf("exp=0xAA550000 got=0x%08h", rd));

        // =================================================================
        // SPM03: Non-zero word offset — DMA 4 words starting at word 5
        // =================================================================
        $display("[SPM03] DMA → PE0 SPM starting at word 5...");
        reset_dut(5);
        // Pre-load a sentinel into word 4 so we can verify it is NOT overwritten
        ram_write(32'h0004_0000, 32'hDEAD_0004);
        dma_transfer(32'h0004_0000, BASE_SPM | (32'd0 << 12) | (32'd4 << 2), 32'd4, 500);
        // Now DMA 4 words starting at word 5
        for (int i = 0; i < 4; i++)
            ram_write(32'h0004_0010 + i*4, 32'hC0DE_0000 | (5 + i));
        // DST = BASE_SPM | (pe=0 << 12) | (word=5 << 2) = 0x40000014
        dma_transfer(32'h0004_0010, BASE_SPM | (32'd0 << 12) | (32'd5 << 2), 32'd16, 500);
        rd = spm_read_wb(0, 5);
        if (rd === 32'hC0DE_0005)
            pass("SPM03a: PE0 SPM[5] = 0xC0DE0005 (word-offset DMA)");
        else
            fail("SPM03a: PE0 SPM[5]", $sformatf("exp=0xC0DE0005 got=0x%08h", rd));
        rd = spm_read_wb(0, 8);
        if (rd === 32'hC0DE_0008)
            pass("SPM03b: PE0 SPM[8] = 0xC0DE0008");
        else
            fail("SPM03b: PE0 SPM[8]", $sformatf("exp=0xC0DE0008 got=0x%08h", rd));
        // Word 4 must retain the sentinel — not overwritten by the word-5 DMA
        rd = spm_read_wb(0, 4);
        if (rd === 32'hDEAD_0004)
            pass("SPM03c: PE0 SPM[4] = 0xDEAD0004 (not overwritten by word-5 DMA)");
        else
            fail("SPM03c: PE0 SPM[4] untouched", $sformatf("exp=0xDEAD0004 got=0x%08h", rd));

        // =================================================================
        // SPM04: DMA→SPM does not corrupt PE config RAM
        // =================================================================
        $display("[SPM04] PE config survives DMA→SPM preload...");
        reset_dut(5);
        // Configure PE0: ADD, WEST + IMM=42
        config_pe_imm(4'd0, OP_ADD, SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, 16'd42);
        // Load tile bank 0 with 7, run once and verify result = 49
        tile_bank_fill_all(2'd0, 32'd7);
        run_cgra(5);
        rd = read_pe_result(4'd0);
        if (rd === 32'd49)
            pass("SPM04a: ADD 7+42=49 before SPM preload");
        else
            fail("SPM04a: pre-preload result", $sformatf("exp=49 got=%0d", rd));
        // Now DMA 64 words to PE0 SPM (simulates weight preload)
        for (int i = 0; i < 64; i++)
            ram_write(32'h0005_0000 + i*4, 32'(i));
        dma_transfer(32'h0005_0000, BASE_SPM | (32'd0 << 12) | 32'd0, 32'd256, 1000);
        // Run again with the same config — result must still be 49
        tile_bank_fill_all(2'd0, 32'd7);
        run_cgra(5);
        rd = read_pe_result(4'd0);
        if (rd === 32'd49)
            pass("SPM04b: ADD 7+42=49 after SPM preload (config intact)");
        else
            fail("SPM04b: config integrity after SPM preload", $sformatf("exp=49 got=%0d", rd));

        $display("\n[SUITE SPM_DMA COMPLETE] DMA->SPM path verified.\n");
    end
endtask

`endif
