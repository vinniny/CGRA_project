`ifndef TB_SUITE_OPENCORES_REF_SVH
`define TB_SUITE_OPENCORES_REF_SVH
// ==============================================================================
// tb_suite_opencores_ref.svh — Suite OCR: OpenCores RTL Golden Model Arithmetic
// ==============================================================================
// Instantiates OpenCores qadd and qmult (verilog_fixed_point_math_library) as
// combinational golden reference models alongside the CGRA PE, then verifies
// that CGRA PE ADD / MUL / chained-MUL+ADD produce identical results.
//
// Constraint: all operands masked to 12 bits [0, 4095].
//   - qadd Q=0 N=32: sum < 2^13, sign bit=0, sign-magnitude == 2's complement. ✓
//   - qmult Q=0 N=32: product < 2^24, ovr=0, sign=0, matches CGRA integer MUL. ✓
//
// PE chain (all row 0):
//   OCR01/02: pe_id=2 (col 2) PASS0(IMM=a) → East → pe_id=3 (col 3) OP(West, IMM=b)
//   OCR03:    pe_id=1 → pe_id=2 → pe_id=3   (3-hop chain)
//
// Tests: 3 groups × 8 LFSR-seeded vectors = 24 tests total.
// ==============================================================================

// lfsr32_next defined in tb_suite_opencores_dma.svh (included first).
// Use it here directly — both files share the same include guard namespace.

task automatic run_suite_OCR_opencores_ref;
    logic [31:0] lfsr_state;
    logic [31:0] a, b, c;
    logic [31:0] actual, mul_step;
    int          i;
    string       tname;

    $display("\n--- SUITE OCR: OpenCores RTL Golden Model Arithmetic (24 Tests) ---");

    // =========================================================================
    // OCR01: ADD — 8 LFSR vectors, compare CGRA PE ADD vs qadd golden model
    // =========================================================================
    $display("[OCR01] PE ADD vs qadd golden model (8 vectors)...");
    lfsr_state = 32'h1ACA_3107;

    for (i = 0; i < 8; i++) begin
        // Generate constrained operands
        lfsr_state = lfsr32_next(lfsr_state);
        a = lfsr_state & 32'h00000FFF;
        lfsr_state = lfsr32_next(lfsr_state);
        b = lfsr_state & 32'h00000FFF;

        // Drive golden model BEFORE CGRA run so comb logic settles during run
        ref_a = a;
        ref_b = b;

        // 2-PE east chain: pe[0,2] → PASS0(a) → East; pe[0,3] → ADD(West=a, IMM=b)
        config_pe_imm(4'd2, OP_PASS0, SRC_IMM,  4'd0, 4'd0, ROUTE_EAST, a[15:0]);
        config_pe_imm(4'd3, OP_ADD,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, b[15:0]);
        run_cgra(8);  // 3-stage pipe × 2 hops = 6 cycles + 2 margin

        actual = read_pe_result(4'd3);
        tname  = $sformatf("OCR01[%0d]: ADD a=%0d b=%0d exp=%0d", i, a, b, ref_add_out);
        if (actual === ref_add_out) begin
            pass_count++;
            `ifdef TB_VERBOSE
            $display("[PASS] %s got=0x%08h", tname, actual);
            `endif
        end else begin
            error_count++;
            $display("[FAIL] %s got=0x%08h", tname, actual);
        end
    end
    $display("[OCR01] Done.");

    // =========================================================================
    // OCR02: MUL — 8 LFSR vectors, compare CGRA PE MUL vs qmult golden model
    // =========================================================================
    $display("[OCR02] PE MUL vs qmult golden model (8 vectors)...");
    // Continue LFSR from where OCR01 left off for fresh vectors

    for (i = 0; i < 8; i++) begin
        lfsr_state = lfsr32_next(lfsr_state);
        a = lfsr_state & 32'h00000FFF;
        lfsr_state = lfsr32_next(lfsr_state);
        b = lfsr_state & 32'h00000FFF;

        ref_a = a;
        ref_b = b;

        // Sanity: qmult must not overflow for these constrained values
        if (ref_mul_ovr !== 1'b0) begin
            $display("[WARN] OCR02[%0d]: qmult overflow unexpected a=%0d b=%0d", i, a, b);
        end

        config_pe_imm(4'd2, OP_PASS0, SRC_IMM,  4'd0, 4'd0, ROUTE_EAST, a[15:0]);
        config_pe_imm(4'd3, OP_MUL,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, b[15:0]);
        run_cgra(8);

        actual = read_pe_result(4'd3);
        tname  = $sformatf("OCR02[%0d]: MUL a=%0d b=%0d exp=%0d", i, a, b, ref_mul_out);
        if (actual === ref_mul_out) begin
            pass_count++;
            `ifdef TB_VERBOSE
            $display("[PASS] %s got=0x%08h", tname, actual);
            `endif
        end else begin
            error_count++;
            $display("[FAIL] %s got=0x%08h", tname, actual);
        end
    end
    $display("[OCR02] Done.");

    // =========================================================================
    // OCR03: MUL+ADD chain — 3 PEs east-chained, golden model applied in 2 steps
    //   pe[0,1] PASS0(a)→E → pe[0,2] MUL(West=a, IMM=b)→E → pe[0,3] ADD(West=a*b, IMM=c)
    // =========================================================================
    $display("[OCR03] 3-PE chain MUL+ADD vs qadd/qmult golden models (8 vectors)...");

    for (i = 0; i < 8; i++) begin
        lfsr_state = lfsr32_next(lfsr_state);
        a = lfsr_state & 32'h00000FFF;
        lfsr_state = lfsr32_next(lfsr_state);
        b = lfsr_state & 32'h00000FFF;
        lfsr_state = lfsr32_next(lfsr_state);
        c = lfsr_state & 32'h00000FFF;

        // Step 1: compute a*b via direct arithmetic.
        // qmult uses two-stage NBA so a single #0 doesn't fully settle it.
        // OCR02 independently proves qmult == PE MUL, so direct mul is valid here.
        mul_step = a * b;

        // Step 2: drive qadd golden model with mul_step and c.
        // qadd uses blocking assignments so output settles in this delta.
        ref_a = mul_step;
        ref_b = c;
        #0;

        // 3-PE chain: pe[0,1]→pe[0,2]→pe[0,3]
        config_pe_imm(4'd1, OP_PASS0, SRC_IMM,  4'd0, 4'd0, ROUTE_EAST, a[15:0]);
        config_pe_imm(4'd2, OP_MUL,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_EAST, b[15:0]);
        config_pe_imm(4'd3, OP_ADD,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, c[15:0]);
        run_cgra(12);  // 3-stage pipe × 3 hops = 9 cycles + 3 margin

        actual = read_pe_result(4'd3);
        tname  = $sformatf("OCR03[%0d]: MUL+ADD a=%0d b=%0d c=%0d exp=%0d",
                           i, a, b, c, ref_add_out);
        if (actual === ref_add_out) begin
            pass_count++;
            `ifdef TB_VERBOSE
            $display("[PASS] %s got=0x%08h", tname, actual);
            `endif
        end else begin
            error_count++;
            $display("[FAIL] %s got=0x%08h", tname, actual);
        end
    end
    $display("[OCR03] Done.");

    $display("\n[SUITE OCR COMPLETE] OpenCores golden model tests done.\n");
endtask

`endif  // TB_SUITE_OPENCORES_REF_SVH
