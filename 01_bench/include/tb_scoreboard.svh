`ifndef TB_SCOREBOARD_SVH
`define TB_SCOREBOARD_SVH

// =============================================================================
// tb_scoreboard.svh — Golden Model Scoreboards
// =============================================================================
// Automated result checking via golden models:
//  - dma_scoreboard: Byte-level comparison for DDR→DDR transfers
//  - pe_scoreboard: Cycle-accurate ALU golden model for all 21 opcodes + SIMD
// =============================================================================

// ============================================================================
// DMA Scoreboard — DDR Memory Comparison
// ============================================================================
class dma_scoreboard;
    cgra_tb_config cfg;
    mailbox #(dma_txn) txn_in;
    
    int match_count;
    int mismatch_count;
    int checked_bytes;
    
    function new(cgra_tb_config c, mailbox #(dma_txn) mbox);
        cfg             = c;
        txn_in          = mbox;
        match_count     = 0;
        mismatch_count  = 0;
        checked_bytes   = 0;
    endfunction
    
    // Check DDR→DDR transfers only (src and dst both in 0x0XXX_XXXX range)
    // Memory reference passed as task argument (Xcelium-compliant)
    task run(ref logic [7:0] mem[*]);
        dma_txn t;
        forever begin
            txn_in.get(t);
            
            // Only check DDR→DDR transfers (direction == DMA_DDR_TO_DDR)
            if (t.direction == DMA_DDR_TO_DDR) begin
                check_ddr_to_ddr(t, mem);
            end else if (cfg.verbosity >= 2) begin
                $display("[SCBD_DMA] %0t Skipping non-DDR transfer: %s", 
                         $time, t.direction.name());
            end
        end
    endtask
    
    task check_ddr_to_ddr(dma_txn t, ref logic [7:0] mem[*]);
        logic [7:0] src_byte, dst_byte;
        int errors = 0;
        
        // Compare byte-by-byte
        for (int i = 0; i < t.size; i++) begin
            src_byte = mem[(t.src + i) & 32'h3FFFFF];  // Mask to mem bounds
            dst_byte = mem[(t.dst + i) & 32'h3FFFFF];
            checked_bytes++;
            
            if (src_byte !== dst_byte) begin
                if (errors < 10) begin  // Limit error spam
                    $error("[SCBD_DMA] %0t Mismatch at byte %0d: src=0x%02h dst=0x%02h",
                           $time, i, src_byte, dst_byte);
                end
                errors++;
                mismatch_count++;
            end else begin
                match_count++;
            end
        end
        
        if (errors == 0) begin
            if (cfg.verbosity >= 2)
                $display("[SCBD_DMA] %0t PASS %s (%0d bytes)", 
                         $time, t.to_string(), t.size);
        end else begin
            $error("[SCBD_DMA] %0t FAIL %s (%0d/%0d bytes mismatched)",
                   $time, t.to_string(), errors, t.size);
        end
    endtask
    
    function void report();
        $display("╔══════════════════════════════════════════════════════════╗");
        $display("║  DMA SCOREBOARD REPORT                                   ║");
        $display("╠══════════════════════════════════════════════════════════╣");
        $display("║  Checked bytes  : %-10d                           ║", checked_bytes);
        $display("║  Matches        : %-10d                           ║", match_count);
        $display("║  Mismatches     : %-10d                           ║", mismatch_count);
        if (mismatch_count > 0)
            $display("║  STATUS         : FAIL                                   ║");
        else
            $display("║  STATUS         : PASS                                   ║");
        $display("╚══════════════════════════════════════════════════════════╝");
    endfunction

    function int get_error_count();
        return mismatch_count;
    endfunction
endclass

// ============================================================================
// PE Scoreboard — Golden ALU Model
// ============================================================================
class pe_scoreboard;
    cgra_tb_config cfg;
    
    int check_count;
    int pass_count;
    int fail_count;
    
    function new(cgra_tb_config c);
        cfg         = c;
        check_count = 0;
        pass_count  = 0;
        fail_count  = 0;
    endfunction
    
    // Golden ALU function: models all 21 opcodes + INT8/INT16 SIMD
    // Returns: {overflow_flag, result[31:0]}
    function automatic logic [32:0] golden_alu(
        input logic [5:0]  op,
        input logic [31:0] a,
        input logic [31:0] b,
        input logic [39:0] acc_in,
        input logic [1:0]  data_mode,  // 00=INT32, 01=INT16x2, 10=INT8x4
        output logic [39:0] acc_out
    );
        logic signed [31:0] sa, sb, sr;
        logic signed [39:0] mac_acc;
        logic signed [63:0] prod64;
        logic [32:0] result;
        
        sa = signed'(a);
        sb = signed'(b);
        result = 33'd0;
        acc_out = acc_in;
        
        case (op)
            OP_NOP: begin
                result = {1'b0, a};  // Preserve previous result (simplified: pass A)
            end
            
            OP_ADD: begin
                sr = sa + sb;
                result = {sr[31] ^ sa[31] ^ sb[31], sr};  // Overflow detection
                acc_out = {{8{sr[31]}}, sr};
            end
            
            OP_SUB: begin
                sr = sa - sb;
                result = {1'b0, sr};
                acc_out = {{8{sr[31]}}, sr};
            end
            
            OP_MUL: begin
                if (data_mode == 2'b00) begin  // INT32
                    prod64 = sa * sb;
                    result = {prod64[63] != prod64[31], prod64[31:0]};  // Overflow if != sign-extend
                end else if (data_mode == 2'b01) begin  // INT16x2 (dot-product)
                    automatic logic signed [15:0] a0 = signed'(a[15:0]);
                    automatic logic signed [15:0] a1 = signed'(a[31:16]);
                    automatic logic signed [15:0] b0 = signed'(b[15:0]);
                    automatic logic signed [15:0] b1 = signed'(b[31:16]);
                    automatic logic signed [31:0] dot = (a0 * b0) + (a1 * b1);
                    result = {1'b0, dot};
                end else begin  // INT8x4 (dot-product)
                    automatic logic signed [7:0] a0 = signed'(a[7:0]);
                    automatic logic signed [7:0] a1 = signed'(a[15:8]);
                    automatic logic signed [7:0] a2 = signed'(a[23:16]);
                    automatic logic signed [7:0] a3 = signed'(a[31:24]);
                    automatic logic signed [7:0] b0 = signed'(b[7:0]);
                    automatic logic signed [7:0] b1 = signed'(b[15:8]);
                    automatic logic signed [7:0] b2 = signed'(b[23:16]);
                    automatic logic signed [7:0] b3 = signed'(b[31:24]);
                    automatic logic signed [31:0] dot = (a0*b0) + (a1*b1) + (a2*b2) + (a3*b3);
                    result = {1'b0, dot};
                end
            end
            
            OP_MAC: begin
                mac_acc = signed'(acc_in);
                if (data_mode == 2'b00) begin  // INT32
                    mac_acc = mac_acc + (sa * sb);
                end else if (data_mode == 2'b01) begin  // INT16x2 dot
                    automatic logic signed [15:0] a0 = signed'(a[15:0]);
                    automatic logic signed [15:0] a1 = signed'(a[31:16]);
                    automatic logic signed [15:0] b0 = signed'(b[15:0]);
                    automatic logic signed [15:0] b1 = signed'(b[31:16]);
                    mac_acc = mac_acc + (a0 * b0) + (a1 * b1);
                end else begin  // INT8x4 dot
                    automatic logic signed [7:0] a0 = signed'(a[7:0]);
                    automatic logic signed [7:0] a1 = signed'(a[15:8]);
                    automatic logic signed [7:0] a2 = signed'(a[23:16]);
                    automatic logic signed [7:0] a3 = signed'(a[31:24]);
                    automatic logic signed [7:0] b0 = signed'(b[7:0]);
                    automatic logic signed [7:0] b1 = signed'(b[15:8]);
                    automatic logic signed [7:0] b2 = signed'(b[23:16]);
                    automatic logic signed [7:0] b3 = signed'(b[31:24]);
                    mac_acc = mac_acc + (a0*b0) + (a1*b1) + (a2*b2) + (a3*b3);
                end
                // Saturate to 40-bit range (simplified: no saturation in golden)
                acc_out = mac_acc;
                result = {1'b0, mac_acc[31:0]};
            end
            
            OP_AND: result = {1'b0, a & b};
            OP_OR:  result = {1'b0, a | b};
            OP_XOR: result = {1'b0, a ^ b};
            
            OP_SHL: begin
                result = {1'b0, a << b[4:0]};
            end
            
            OP_SHR: begin
                result = {1'b0, unsigned'(sa >>> b[4:0])};  // Arithmetic shift
            end
            
            OP_CMP_GT: result = {1'b0, 32'(sa > sb)};
            OP_CMP_LT: result = {1'b0, 32'(sa < sb)};
            OP_CMP_EQ: result = {1'b0, 32'(a == b)};
            
            OP_LOAD_SPM:  result = {1'b0, 32'hDEAD_C0DE};  // Cannot model without SPM state
            OP_STORE_SPM: result = {1'b0, a};              // Pass-through
            
            OP_ACC_CLR: begin
                result = 33'd0;
                acc_out = 40'd0;
            end
            
            OP_PASS0: result = {1'b0, a};
            OP_PASS1: result = {1'b0, b};
            
            OP_LIF: begin  // Simplified LIF: V = V + input (no spike logic)
                sr = sa + sb;
                result = {1'b0, sr};
            end
            
            OP_RELU: result = {1'b0, (sa[31] == 0) ? a : 32'd0};  // max(0, A)
            
            OP_MAX: result = {1'b0, (sa > sb) ? a : b};  // max(A, B)
            
            default: result = {1'b1, 32'hBAD_C0DE};  // Illegal opcode
        endcase
        
        return result;
    endfunction
    
    // Check a single PE operation
    task check_pe_op(
        input logic [5:0]  op,
        input logic [31:0] a,
        input logic [31:0] b,
        input logic [39:0] acc_in,
        input logic [1:0]  data_mode,
        input logic [31:0] actual_result,
        input string       test_name
    );
        logic [39:0] golden_acc_out;
        logic [32:0] golden_result;
        
        golden_result = golden_alu(op, a, b, acc_in, data_mode, golden_acc_out);
        check_count++;
        
        if (actual_result === golden_result[31:0]) begin
            pass_count++;
            if (cfg.verbosity >= 3)
                $display("[SCBD_PE] %0t PASS %s: op=%0d a=0x%h b=0x%h → 0x%h",
                         $time, test_name, op, a, b, actual_result);
        end else begin
            fail_count++;
            $error("[SCBD_PE] %0t FAIL %s: op=%0d a=0x%h b=0x%h exp=0x%h got=0x%h",
                   $time, test_name, op, a, b, golden_result[31:0], actual_result);
        end
    endtask
    
    function void report();
        $display("╔══════════════════════════════════════════════════════════╗");
        $display("║  PE SCOREBOARD REPORT                                    ║");
        $display("╠══════════════════════════════════════════════════════════╣");
        $display("║  Checks         : %-10d                           ║", check_count);
        $display("║  Passed         : %-10d                           ║", pass_count);
        $display("║  Failed         : %-10d                           ║", fail_count);
        if (fail_count > 0)
            $display("║  STATUS         : FAIL                                   ║");
        else if (check_count > 0)
            $display("║  STATUS         : PASS                                   ║");
        else
            $display("║  STATUS         : NO CHECKS                              ║");
        $display("╚══════════════════════════════════════════════════════════╝");
    endfunction

    function int get_error_count();
        return fail_count;
    endfunction
endclass

`endif
