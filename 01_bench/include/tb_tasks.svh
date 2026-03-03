`ifndef TB_TASKS_SVH
`define TB_TASKS_SVH
// ==============================================================================
// tb_tasks.svh - Verilator-Native Driver Layer
// ==============================================================================
// Reusable tasks for CGRA verification using Verilator 5.x --timing mode.
// All tasks use blocking assignments (=) which is correct for testbench code.
// ==============================================================================

// ============================================================================
// PROTOCOL CHECKER CONTROL
// ============================================================================
logic protocol_check_enable = 1'b1;

// ============================================================================
// RESET TASK (disables protocol checker during reset)
// ============================================================================
task automatic reset_dut(input int cycles);
    protocol_check_enable = 1'b0;
    rst_n = 1'b0;
    repeat(cycles) @(posedge clk);
    rst_n = 1'b1;
    repeat(5) @(posedge clk);
    protocol_check_enable = 1'b1;
    init_memory();
    cov_reset_tests++;
endtask

// ============================================================================
// UTILITY TASKS
// ============================================================================
task automatic wait_cycles(input int n);
    repeat(n) @(posedge clk);
endtask

task automatic random_delay(input int min_cycles, input int max_cycles);
    int delay, range;
    // FIX: Guard against divide-by-zero when max < min
    range = max_cycles - min_cycles + 1;
    if (range <= 0) range = 1;
    delay = min_cycles + ($urandom % range);
    repeat(delay) @(posedge clk);
endtask

// ============================================================================
// APB WRITE TASK
// ============================================================================
task automatic apb_write(input logic [31:0] addr, input logic [31:0] data);
    @(posedge clk);
    paddr = addr;
    pwdata = data;
    pwrite = 1'b1;
    psel = 1'b1;
    penable = 1'b0;
    
    @(posedge clk);
    penable = 1'b1;
    
    @(posedge clk);
    while (!pready) @(posedge clk); // FIX: Wait for pready (costs nothing when always 1)
    
    if (pslverr) $warning("[APB] Write to 0x%08h returned PSLVERR", addr);
    
    psel = 1'b0;
    penable = 1'b0;
    pwrite = 1'b0;
endtask

// ============================================================================
// APB READ TASK
// ============================================================================
task automatic apb_read(input logic [31:0] addr, output logic [31:0] data);
    @(posedge clk);
    paddr = addr;
    pwrite = 1'b0;
    psel = 1'b1;
    penable = 1'b0;
    
    @(posedge clk);
    penable = 1'b1;
    
    @(posedge clk);
    while (!pready) @(posedge clk); // FIX: Wait for pready (costs nothing when always 1)
    
    if (pslverr) $warning("[APB] Read from 0x%08h returned PSLVERR", addr);
    
    data = prdata;      // FIX: Sample BEFORE deasserting psel/penable
    
    psel = 1'b0;
    penable = 1'b0;
endtask

// ============================================================================
// APB CHECK TASK (Read and Verify)
// ============================================================================
task automatic apb_check(input logic [31:0] addr, input logic [31:0] exp, input string msg);
    logic [31:0] rd;
    apb_read(addr, rd);
    if (rd !== exp) begin
        $display("  [FAIL] %s | Addr: 0x%h | Exp: 0x%h | Got: 0x%h", msg, addr, exp, rd);
        error_count++;
    end else begin
        $display("  [PASS] %s", msg);
        pass_count++;
    end
endtask

// ============================================================================
// APB CHECK NONZERO
// ============================================================================
task automatic apb_check_nonzero(input logic [31:0] addr, input string msg);
    logic [31:0] rd;
    apb_read(addr, rd);
    if (rd > 0) begin
        $display("  [PASS] %s (value=%0d)", msg, rd);
        pass_count++;
    end else begin
        $display("  [FAIL] %s | Expected nonzero, got 0", msg);
        error_count++;
    end
endtask

// ============================================================================
// APB CHECK BIT
// ============================================================================
task automatic apb_check_bit(input logic [31:0] addr, input int bit_pos, 
                             input logic exp_val, input string msg);
    logic [31:0] rd;
    apb_read(addr, rd);
    if (rd[bit_pos] === exp_val) begin
        $display("  [PASS] %s", msg);
        pass_count++;
    end else begin
        $display("  [FAIL] %s | Bit[%0d]: Exp=%b Got=%b", msg, bit_pos, exp_val, rd[bit_pos]);
        error_count++;
    end
endtask

// ============================================================================
// BACKDOOR RAM ACCESS
// ============================================================================
task automatic ram_write(input logic [31:0] addr, input logic [31:0] data);
    mem[addr[16:0] + 0] = data[7:0];
    mem[addr[16:0] + 1] = data[15:8];
    mem[addr[16:0] + 2] = data[23:16];
    mem[addr[16:0] + 3] = data[31:24];
endtask

function automatic logic [31:0] ram_read(input logic [31:0] addr);
    return {mem[addr[16:0] + 3],
            mem[addr[16:0] + 2],
            mem[addr[16:0] + 1],
            mem[addr[16:0] + 0]};
endfunction

// ============================================================================
// INITIALIZE MEMORY WITH TEST PATTERN
// ============================================================================
task automatic init_memory();
    for (int i = 0; i < MEM_SIZE; i++) mem[i] = 8'h00;
    for (int i = 0; i < 65536; i++) mem[32'h1000 + i] = i[7:0];
endtask

// ============================================================================
// DMA OPERATIONS
// ============================================================================
task automatic wait_dma_done(input int timeout);
    logic [31:0] status;
    for (int i = 0; i < timeout; i++) begin
        apb_read(ADDR_DMA_STATUS, status);
        if (status[1]) return;
        wait_cycles(1);
    end
    $warning("[DMA] Timeout after %0d cycles", timeout);
endtask

task automatic dma_transfer(input logic [31:0] src, input logic [31:0] dst, 
                            input logic [31:0] size, input int timeout);
    apb_write(ADDR_DMA_SRC, src);
    apb_write(ADDR_DMA_DST, dst);
    apb_write(ADDR_DMA_SIZE, size);
    apb_write(ADDR_DMA_CTRL, 32'h1);
    wait_dma_done(timeout);
endtask

task automatic check_data(input logic [31:0] src, input logic [31:0] dst, 
                          input logic [31:0] size, output logic ok);
    ok = 1'b1;

    // FIX: OOB guard — prevent array access beyond MEM_SIZE
    if ((32'(src[16:0]) + size) > TB_MEM_SIZE || (32'(dst[16:0]) + size) > TB_MEM_SIZE) begin
        $error("[check_data] OOB: src[16:0]=0x%05h dst[16:0]=0x%05h size=%0d exceeds MEM_SIZE=%0d",
               src[16:0], dst[16:0], size, TB_MEM_SIZE);
        ok = 1'b0;
        return;
    end

    for (int i = 0; i < size; i++) begin
        if (mem[{15'd0, dst[16:0]} + 32'(i)] !== mem[{15'd0, src[16:0]} + 32'(i)]) ok = 1'b0;
    end
endtask

// Convenience wrapper: check_data with built-in pass/fail reporting
task automatic check_data_report(input logic [31:0] src, input logic [31:0] dst, 
                          input logic [31:0] size, input string test_name);
    logic ok;

    // OOB guard
    if ((32'(src[16:0]) + size) > TB_MEM_SIZE || (32'(dst[16:0]) + size) > TB_MEM_SIZE) begin
        fail(test_name, $sformatf("OOB: src[16:0]=0x%05h dst[16:0]=0x%05h size=%0d exceeds MEM_SIZE=%0d",
             src[16:0], dst[16:0], size, TB_MEM_SIZE));
        return;
    end

    ok = 1'b1;
    for (int i = 0; i < size; i++) begin
        if (mem[{15'd0, dst[16:0]} + 32'(i)] !== mem[{15'd0, src[16:0]} + 32'(i)]) begin
            if (ok) begin  // Print first mismatch only
                $display("  [MISMATCH] offset=%0d: dst[0x%05h]=0x%02h, src[0x%05h]=0x%02h",
                         i, dst[16:0]+17'(i), mem[{15'd0, dst[16:0]} + 32'(i)],
                            src[16:0]+17'(i), mem[{15'd0, src[16:0]} + 32'(i)]);
            end
            ok = 1'b0;
        end
    end

    if (ok)
        pass(test_name);
    else
        fail(test_name, "Data mismatch between src and dst");
endtask

// ============================================================================
// RESULT REPORTING (Centralized — mirrors reference TB log_test_result)
// ============================================================================
task automatic log_test_result(input string test_name, input string result);
    case (result)
        "PASS": begin
            pass_count++;
            $display("  [PASS] %s", test_name);
        end
        "FAIL": begin
            error_count++;
            $error("  [FAIL] %s", test_name);
        end
        "SKIP": begin
            $display("  [SKIP] %s", test_name);
        end
        default: begin
            $warning("  [UNKNOWN] %s - invalid result: %s", test_name, result);
        end
    endcase
endtask

task automatic pass(input string msg);
    $display("  [PASS] %s", msg);
    pass_count++;
endtask

task automatic fail(input string msg, input string reason);
    $display("  [FAIL] %s - %s", msg, reason);
    error_count++;
endtask

// ============================================================================
// STRESS INJECTOR
// ============================================================================
task automatic enable_stress(input int prob);
    stress_enable = 1'b1;
    stress_probability = prob;
    cov_stress_cycles++;
endtask

task automatic disable_stress();
    stress_enable = 1'b0;
    stress_probability = 0;
endtask

// ============================================================================
// TILE MEMORY & PE CONFIGURATION
// ============================================================================
task automatic dma_load_tile_bank(input logic [1:0] bank, input logic [11:0] offset, 
                                  input logic [31:0] value);
    logic [31:0] tile_addr;
    tile_addr = BASE_TILE | ({18'd0, bank, 12'd0}) | {20'd0, offset};
    ram_write(32'h0000_1000, value);
    apb_write(ADDR_DMA_SRC, 32'h0000_1000);
    apb_write(ADDR_DMA_DST, tile_addr);
    apb_write(ADDR_DMA_SIZE, 32'd4);
    apb_write(ADDR_DMA_CTRL, 32'd1);
    wait_dma_done(100);
endtask

// Fill all 16 context slots (0-15) with the same value
// This ensures PE reads the same operand regardless of context_pc
task automatic tile_bank_fill_all(input logic [1:0] bank, input logic [31:0] value);
    for (int i = 0; i < 16; i++) begin
        dma_load_tile_bank(bank, i[11:0] * 4, value);  // Each slot is 4 bytes apart
    end
endtask

task automatic config_pe(input logic [3:0] pe_id, input logic [3:0] slot, 
                         input logic [63:0] config_data);
    logic [31:0] cfg_addr_base;
    logic [31:0] data_high, data_low;
    
    cfg_addr_base = BASE_CONFIG | (32'({24'd0, pe_id}) << 8) | (32'({28'd0, slot}) << 3);
    data_low  = config_data[31:0];
    data_high = config_data[63:32];
    
    ram_write(32'h0000_1004, data_high);
    apb_write(ADDR_DMA_SRC, 32'h0000_1004);
    apb_write(ADDR_DMA_DST, cfg_addr_base | 32'h4);
    apb_write(ADDR_DMA_SIZE, 32'd4);
    apb_write(ADDR_DMA_CTRL, 32'd1);
    wait_dma_done(100);
    
    ram_write(32'h0000_1004, data_low);
    apb_write(ADDR_DMA_SRC, 32'h0000_1004);
    apb_write(ADDR_DMA_DST, cfg_addr_base);
    apb_write(ADDR_DMA_SIZE, 32'd4);
    apb_write(ADDR_DMA_CTRL, 32'd1);
    wait_dma_done(100);
endtask

task automatic run_cgra(input int cycles);
    // FIX: Increase soft reset duration to ensure PE accumulator is cleared
    // The pe_reset_n signal is registered, so need extra cycles for reset to propagate
    apb_write(ADDR_CU_CTRL, 32'd2);  // Assert soft_reset
    wait_cycles(3);                   // Hold reset for 3 cycles (was 1)
    apb_write(ADDR_CU_CTRL, 32'd0);  // Release soft_reset
    wait_cycles(2);                   // Wait for reset to deassert (was 1)
    apb_write(ADDR_CU_CTRL, 32'd1);  // Start execution (auto-clears after 1 cycle)
    wait_cycles(cycles);
    apb_write(ADDR_CU_CTRL, 32'd2);  // Stop via soft_reset (triggers FSM FINISH)
    wait_cycles(1);                   // Wait for FSM to reach FINISH state
    apb_write(ADDR_CU_CTRL, 32'd0);  // Release soft_reset
endtask

// ============================================================================
// PE CONFIGURATION ABSTRACTION LAYER
// ============================================================================
// Packs opcode and operand selectors into 64-bit config format and writes
// using the proper double-pump protocol. Handles timing automatically.
//
// Config frame format:
//   [5:0]   = op_code
//   [9:6]   = src0_sel
//   [13:10] = src1_sel
//   [17:14] = dst_sel
//   [21:18] = route_mask
//   [22]    = pred_en
//   [23]    = pred_inv
//   [39:24] = immediate
//   [63:40] = extended (dest coords, multicast)
// ============================================================================

// Build 64-bit config word from components
function automatic logic [63:0] build_pe_config(
    input logic [5:0]  opcode,
    input logic [3:0]  src0,
    input logic [3:0]  src1,
    input logic [3:0]  dst,
    input logic [3:0]  route,
    input logic [15:0] imm
);
    return {24'd0, imm, 2'b00, route, dst, src1, src0, opcode};
endfunction

// Configure PE with opcode and sources (simplified interface)
task automatic config_pe_safe(
    input logic [3:0]  pe_id,      // PE 0-15
    input logic [5:0]  opcode,     // Operation (use OP_* constants)
    input logic [3:0]  src0,       // Source 0 (use SRC_* constants)
    input logic [3:0]  src1,       // Source 1
    input logic [3:0]  dst,        // Destination register
    input logic [3:0]  route       // Output routing mask
);
    logic [63:0] cfg;
    cfg = build_pe_config(opcode, src0, src1, dst, route, 16'd0);
    config_pe(pe_id, 4'd0, cfg);   // Write to slot 0
    wait_cycles(3);                 // Allow config RAM latency
endtask

// Configure PE with immediate value
task automatic config_pe_imm(
    input logic [3:0]  pe_id,
    input logic [5:0]  opcode,
    input logic [3:0]  src0,
    input logic [3:0]  src1,
    input logic [3:0]  dst,
    input logic [3:0]  route,
    input logic [15:0] imm
);
    logic [63:0] cfg;
    cfg = build_pe_config(opcode, src0, src1, dst, route, imm);
    config_pe(pe_id, 4'd0, cfg);
    wait_cycles(3);
endtask

// ============================================================================
// PE RESULT VERIFICATION (BLACK-BOX)
// ============================================================================
// Instead of probing internal alu_result, we:
// 1. Run the CGRA for a few cycles
// 2. Read back the PE's accumulator/result via the proper data path
//
// For now, we'll still use whitebox access but through a controlled
// function that can be replaced with proper readback when available.

function automatic logic [31:0] read_pe_result(input logic [3:0] pe_id);
    // Whitebox access - to be replaced with black-box DMA readback
    // This centralizes the access point for easier migration
    case (pe_id)
        4'd0:  return tb_top.u_dut.u_array.u_tile_00.u_pe.alu_result;
        4'd1:  return tb_top.u_dut.u_array.u_tile_01.u_pe.alu_result;
        4'd2:  return tb_top.u_dut.u_array.u_tile_02.u_pe.alu_result;
        4'd3:  return tb_top.u_dut.u_array.u_tile_03.u_pe.alu_result;
        4'd4:  return tb_top.u_dut.u_array.u_tile_10.u_pe.alu_result;
        4'd5:  return tb_top.u_dut.u_array.u_tile_11.u_pe.alu_result;
        4'd6:  return tb_top.u_dut.u_array.u_tile_12.u_pe.alu_result;
        4'd7:  return tb_top.u_dut.u_array.u_tile_13.u_pe.alu_result;
        4'd8:  return tb_top.u_dut.u_array.u_tile_20.u_pe.alu_result;
        4'd9:  return tb_top.u_dut.u_array.u_tile_21.u_pe.alu_result;
        4'd10: return tb_top.u_dut.u_array.u_tile_22.u_pe.alu_result;
        4'd11: return tb_top.u_dut.u_array.u_tile_23.u_pe.alu_result;
        4'd12: return tb_top.u_dut.u_array.u_tile_30.u_pe.alu_result;
        4'd13: return tb_top.u_dut.u_array.u_tile_31.u_pe.alu_result;
        4'd14: return tb_top.u_dut.u_array.u_tile_32.u_pe.alu_result;
        4'd15: return tb_top.u_dut.u_array.u_tile_33.u_pe.alu_result;
        default: return 32'hDEAD_BEEF;
    endcase
endfunction

// Check PE result against expected value
task automatic check_pe_result(
    input logic [3:0]  pe_id,
    input logic [31:0] expected,
    input string       test_name
);
    logic [31:0] actual;
    logic [31:0] pe0_alu;
    logic [31:0] pe0_op0, pe0_op1;
    logic [5:0]  pe0_opcode;
    logic signed [39:0] pe0_acc;
    
    // Debug: capture PE0 internals
    pe0_alu = tb_top.u_dut.u_array.u_tile_00.u_pe.alu_result;
    pe0_op0 = tb_top.u_dut.u_array.u_tile_00.u_pe.operand0;
    pe0_op1 = tb_top.u_dut.u_array.u_tile_00.u_pe.operand1;
    pe0_opcode = tb_top.u_dut.u_array.u_tile_00.u_pe.op_code;
    pe0_acc = tb_top.u_dut.u_array.u_tile_00.u_pe.accumulator;
    
    // Direct probe for PE 0 to avoid function issues
    if (pe_id == 4'd0)
        actual = pe0_alu;
    else
        actual = read_pe_result(pe_id);
    
    // Debug output gated by TB_VERBOSE (only print on mismatch in quiet mode)
    `ifndef TB_QUIET
    if (actual !== expected) begin
        $display("  [DEBUG-FAIL] pe_id=%0d, opcode=%0d, op0=0x%h, op1=0x%h, acc=0x%h", 
                 pe_id, pe0_opcode, pe0_op0, pe0_op1, pe0_acc);
        $display("  [DEBUG-FAIL] pe0_alu=0x%h, actual=0x%h, expected=0x%h", 
                 pe0_alu, actual, expected);
    end
    `else
    if (actual !== expected) begin
        $display("  [DEBUG-FAIL] pe_id=%0d, opcode=%0d, op0=0x%h, op1=0x%h, acc=0x%h", 
                 pe_id, pe0_opcode, pe0_op0, pe0_op1, pe0_acc);
    end
    `endif
    
    if (actual === expected) begin
        pass(test_name);
    end else begin
        fail(test_name, $sformatf("PE%0d Exp: 0x%h, Got: 0x%h", pe_id, expected, actual));
    end
endtask

// ============================================================================
// COMBINED TEST HELPER - Load data, configure, execute, verify
// ============================================================================
task automatic test_pe_operation(
    input logic [3:0]  pe_id,
    input logic [5:0]  opcode,
    input logic [31:0] operand_a,     // Loaded to tile bank 0
    input logic [31:0] operand_b,     // FIX: Now used via SRC_IMM (lower 16 bits, sign-extended by PE)
    input logic [31:0] expected,
    input string       test_name
);
    // 1. Load operand_a to tile memory (West input)
    dma_load_tile_bank(2'd0, 12'd0, operand_a);
    
    // 2. Configure PE: src0=WEST (operand_a), src1=IMM (operand_b[15:0])
    // NOTE: IMM is 16-bit. If operand_b exceeds 16-bit signed range, this
    //       will silently truncate. Callers must account for this.
    config_pe_imm(pe_id, opcode, SRC_WEST, SRC_IMM, 4'd0, 4'd0, operand_b[15:0]);
    
    // 3. Run CGRA
    run_cgra(5);
    
    // 4. Check result
    check_pe_result(pe_id, expected, test_name);
endtask

// =========================================================================
// DMA WRITE-BACK HELPERS (Suite AE)
// =========================================================================

// Round-trip transfer: DDR -> Local -> DDR
task automatic dma_round_trip(
    input logic [31:0] ddr_src,
    input logic [31:0] local_addr,
    input logic [31:0] ddr_dst,
    input logic [31:0] size,
    input int timeout
);
    // Phase 1: DMA Read (External -> Local)
    dma_transfer(ddr_src, local_addr, size, timeout);
    
    // Phase 2: DMA Write (Local -> External)
    dma_transfer(local_addr, ddr_dst, size, timeout);
endtask

// Check AXI write burst protocol (WLAST)
task automatic check_write_burst_protocol();
    int beat_count;
    beat_count = 0;
    // Wait for write transaction start
    while (!axi_wvalid) @(posedge clk);
    
    // Monitor burst
    while (!axi_wlast && beat_count < 256) begin
        if (axi_wvalid && axi_wready) beat_count++;
        @(posedge clk);
    end
    
    if (axi_wlast && axi_wvalid) pass("Write burst WLAST asserted");
    else fail("Write burst", "WLAST not asserted or timeout");
endtask


`endif
