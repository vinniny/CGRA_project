`ifndef TB_ISA_REGRESSION_SVH
`define TB_ISA_REGRESSION_SVH

// =============================================================================
// SUITE AD: RANDOMIZED ISA REGRESSION (500 Vectors/Opcode)
// =============================================================================
// Goal: Stress test ALU precision and corner cases with high volume random data.
// Coverage:
//   - Arithmetic: ADD, SUB, MUL, MAC (with Saturation checks)
//   - Logic: AND, OR, XOR
//   - Shift: SHL, SHR (include full 5-bit range)
//   - Compare: EQ, LT, GT
//   - Special: ACC_CLR, PASS0, PASS1, RELU, MAX
//   - Skipped (need special infra): NOP(0), LOAD_SPM(13), STORE_SPM(14), LIF(18)
// =============================================================================

task automatic run_suite_AD_isa_regression;
    integer i, op_idx;
    logic [31:0] a, b, res, expected;
    logic signed [63:0] temp_sum; // 64-bit signed for overflow check
    logic signed [31:0] a_s, b_s;
    string op_name;
    
    // Saturation constants
    localparam signed [31:0] MAX_POS = 32'h7FFF_FFFF;
    localparam signed [31:0] MIN_NEG = 32'h8000_0000;

    begin
        $display("\n   SUITE AD: RANDOMIZED ISA REGRESSION");
        $display("   Target: 500 Iterations per Opcode");
        $display("========================================");
        
        // Loop through all testable opcodes (1-12, 15-17, 19-20)
        // Skipped: 0=NOP (no output), 13=LOAD_SPM, 14=STORE_SPM, 18=LIF (need special infra)
        for (op_idx = 1; op_idx <= 20; op_idx++) begin

            // Skip opcodes that need special test infrastructure
            if (op_idx == 13 || op_idx == 14 || op_idx == 18) continue;

            case (op_idx)
                1:  op_name = "ADD";
                2:  op_name = "SUB";
                3:  op_name = "MUL";
                4:  op_name = "MAC";
                5:  op_name = "AND";
                6:  op_name = "OR";
                7:  op_name = "XOR";
                8:  op_name = "SHL";
                9:  op_name = "SHR";
                10: op_name = "CMP_GT";
                11: op_name = "CMP_LT";
                12: op_name = "CMP_EQ";
                15: op_name = "ACC_CLR";
                16: op_name = "PASS0";
                17: op_name = "PASS1";
                19: op_name = "RELU";
                20: op_name = "MAX";
                default: op_name = "UNKNOWN";
            endcase
            
            $display("[AD%02d] Testing %s (500 vectors)...", op_idx, op_name);
            
            for (i = 0; i < 500; i++) begin
                // 1. Generate Random Inputs
                a = $urandom();
                b = $urandom();
                
                // Corner case injection (10% chance)
                // FIX: Original code always set a=MIN_NEG because (i%10)==0 implies
                // (i%2)==0, so the ternary always took the false branch.
                // Now alternate MAX_POS and MIN_NEG across injection windows.
                if ((i % 10) == 0) begin
                    a = ((i % 20) != 0) ? MAX_POS : MIN_NEG;
                    b = ((i % 4) != 0) ? 32'd1 : 32'hFFFF_FFFF;
                end
                
                // FIX: Mask b to 16-bit BEFORE golden calculation, as we use IMM (16-bit)
                // FIX: Mask b to 16-bit and SIGN EXTEND to match RTL behavior
                if (op_idx != 8 && op_idx != 9) begin
                    b = {{16{b[15]}}, b[15:0]};
                end
                
                // 2. Compute Golden Result
                a_s = $signed(a);
                b_s = $signed(b);
                
                case (op_idx)
                    // ADD (Saturating)
                    1: begin
                        temp_sum = {{32{a_s[31]}}, a_s} + {{32{b_s[31]}}, b_s};
                        if (temp_sum > 64'(MAX_POS)) expected = MAX_POS;
                        else if (temp_sum < 64'(MIN_NEG)) expected = MIN_NEG;
                        else expected = temp_sum[31:0];
                    end
                    
                    // SUB (Saturating)
                    2: begin
                        temp_sum = {{32{a_s[31]}}, a_s} - {{32{b_s[31]}}, b_s};
                        if (temp_sum > 64'(MAX_POS)) expected = MAX_POS;
                        else if (temp_sum < 64'(MIN_NEG)) expected = MIN_NEG;
                        else expected = temp_sum[31:0];
                    end
                    
                    // MUL (Standard 32-bit truncation)
                    3: expected = a * b;
                    
                    // MAC (Saturating + Accumulate)
                    // For regression: Clear accumulator before each MAC test
                    // to verify the multiplication/saturation part primarily.
                    // NOTE: b is already sign-extended from 16-bit by the fix at line 65
                    //
                    // KNOWN LIMITATION (Session 9 audit):
                    // config_valid=cu_busy forces single-context mode, so
                    // the PE executes MAC on EVERY context_pc cycle during
                    // run_cgra(2), accumulating N × sat40(a*b) where N≈3-4.
                    // The golden below computes 1 × (a*b).
                    // This is masked by saturation: for random 32×16 signed
                    // products, |a*b| >> 2^31 in >99.99% of cases, so
                    // sat32(N × sat40(a*b)) == sat32(a*b).
                    // A mismatch can only occur when |a*b| < ~715M.
                    // True fix requires either single-cycle CU timeout
                    // or multi-context mode (config_valid decoupled from cu_busy).
                    4: begin
                        // MAC: Acc(0) + A * B (both signed, B is sign-extended 16-bit)
                        temp_sum = (a_s * b_s);
                        if (temp_sum > 64'(MAX_POS)) expected = MAX_POS;
                        else if (temp_sum < 64'(MIN_NEG)) expected = MIN_NEG;
                        else expected = temp_sum[31:0];
                    end
                    
                    // Logic
                    5: expected = a & b;
                    6: expected = a | b;
                    7: expected = a ^ b;
                    
                    // Shift (B is shift amount 0-31)
                    8: expected = a << b[4:0];
                    9: expected = $signed(a) >>> b[4:0]; // Arithmetic Right Shift
                    
                    // Compare (FIX: RTL now uses $signed comparison)
                    10: expected = ($signed(a) > $signed(b)) ? 1 : 0;
                    11: expected = ($signed(a) < $signed(b)) ? 1 : 0;
                    12: expected = (a == b) ? 1 : 0;

                    // ACC_CLR: Clears accumulator, result = 0
                    15: expected = 32'd0;

                    // PASS0: Passthrough operand0 (a from tile/west)
                    16: expected = a;

                    // PASS1: Passthrough operand1 (b = sign-extended 16-bit IMM)
                    17: expected = b;  // Already sign-extended at line 70

                    // RELU: max(a, 0) — signed comparison
                    19: expected = ($signed(a) < 0) ? 32'd0 : a;

                    // MAX: max(signed(a), signed(b))
                    20: expected = ($signed(a) > $signed(b)) ? a : b;

                    default: expected = 0;
                endcase
                
                // 3. Configure and Run

                // For MAC, clear accumulator first and set CU_TIMEOUT=1 so the
                // PE executes exactly 1 MAC cycle. Without this, run_cgra(2)
                // lets the PE accumulate ~3 times, and the golden model (1×product)
                // mismatches for small products that don't saturate.
                if (op_idx == 4) begin
                    config_pe_safe(4'd0, OP_ACC_CLR, SRC_WEST, SRC_WEST, 4'd0, 4'd0);
                    run_cgra(2);
                    apb_write(ADDR_CU_TIMEOUT, 32'd2);  // 2 wall-clock cycles: 1 to latch _r, 1 for ALU
                end

                // Data Setup
                tile_bank_fill_all(2'd0, a);

                // Op Setup (16-bit IMM for operand B)
                config_pe_imm(4'd0, op_idx[5:0], SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, b[15:0]);

                run_cgra(2);

                // Restore CU_TIMEOUT=0 (no limit) after MAC tests
                if (op_idx == 4) begin
                    apb_write(ADDR_CU_TIMEOUT, 32'd0);
                end
                
                // 4. Check
                check_pe_result(4'd0, expected, $sformatf("AD%02d_%03d: %s(0x%h, 0x%h)", op_idx, i, op_name, a, b));
            end
        end
        $display("\n[SUITE AD COMPLETE] 8500 Randomized tests finished (17 opcodes × 500 vectors).\n");
    end
endtask

`endif
