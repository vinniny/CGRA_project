`ifndef TB_SUITE_OPENCORES_DIV_SVH
`define TB_SUITE_OPENCORES_DIV_SVH
// ==============================================================================
// tb_suite_opencores_div.svh — Suite OD: OpenCores Sequential Divider
//                              Cross-Verification (24 tests)
// ==============================================================================
// Instantiates the OpenCores qdiv (Q=0, N=32) sequential integer divider as a
// golden reference to verify CGRA arithmetic precision via mathematical inversion.
//
// qdiv instance:   u_ref_qdiv in tb_top.sv (Q=0, N=32)
// Control signals: dv_dividend, dv_divisor, dv_start, dv_quotient_out, dv_complete
// Latency:         32 clock cycles from start-pulse to complete=1
// Format:          Sign-magnitude (bit 31 = sign). Positive inputs only here.
//
// Three independent precision tests:
//
//   OD01 — MUL roundtrip: qdiv(CGRA_MUL(A,B), B) == A
//     Proves the CGRA MUL result has no lost bits.
//     A,B ≤ 10 bits → A×B < 2^20, fits in sign-magnitude range.
//
//   OD02 — SHR vs floor division: CGRA_SHR(A,K) == qdiv(A, 2^K)
//     Proves arithmetic right-shift is identical to floor division for positive A.
//     K cycles through {1,2,4,8}. A ≤ 16 bits.
//
//   OD03 — General floor division property: Q×B ≤ A < (Q+1)×B
//     qdiv(A,B) → Q; CGRA MUL(Q,B) → Q×B; verify floor division bounds.
//     A ≤ 16 bits, B ∈ [1,63] (6 bits, non-zero).
//
// Tests: 3 groups × 8 LFSR vectors = 24 tests total.
// ==============================================================================

// Drive the qdiv sequential divider and wait for it to complete.
// Caller must set dv_dividend and dv_divisor before calling.
// Uses 40 cycles total (32 computation + 8 margin) — safe for Q=0, N=32.
task automatic run_qdiv_wait;
    // Ensure we're at a safe point (qdiv starts on posedge when complete=1)
    wait_cycles(1);
    dv_start = 1'b1;
    wait_cycles(1);   // start seen on this posedge
    dv_start = 1'b0;
    wait_cycles(40);  // 32 cycles computation + 8 margin
endtask

task automatic run_suite_OD_opencores_div;
    logic [31:0] lfsr_state;
    logic [31:0] A, B, K;
    logic [31:0] cgra_result;
    logic [31:0] quotient;
    logic [31:0] qb;
    int          i;
    string       tname;

    // K rotation for OD02: shift amounts {1,2,4,8}
    logic [31:0] shift_tbl [0:3];

    $display("\n--- SUITE OD: OpenCores Sequential Divider Cross-Verification (24 Tests) ---");

    shift_tbl[0] = 32'd1;
    shift_tbl[1] = 32'd2;
    shift_tbl[2] = 32'd4;
    shift_tbl[3] = 32'd8;

    // =========================================================================
    // OD01: MUL roundtrip — qdiv(CGRA_MUL(A,B), B) == A
    //   Verifies that the CGRA integer MUL is bitwise exact (no truncation).
    //   A×B < 2^20 ensures no 32-bit overflow and fits in qdiv sign-magnitude.
    // =========================================================================
    $display("[OD01] MUL roundtrip via qdiv (8 vectors)...");
    lfsr_state = 32'hD3B2_7F4E;

    for (i = 0; i < 8; i++) begin
        lfsr_state = lfsr32_next(lfsr_state);
        A = lfsr_state & 32'h000003FF;  // 10-bit
        lfsr_state = lfsr32_next(lfsr_state);
        B = (lfsr_state & 32'h000003FE) | 32'h1;  // 10-bit, force odd ≥ 1 (avoid B=0)

        // CGRA: pe[0,2] PASS0(A) → East; pe[0,3] MUL(West=A, IMM=B)
        config_pe_imm(4'd2, OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, A[15:0]);
        config_pe_imm(4'd3, OP_MUL,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, B[15:0]);
        run_cgra(8);
        cgra_result = read_pe_result(4'd3);  // = A×B

        // qdiv(A×B, B) must recover A exactly
        dv_dividend = cgra_result;
        dv_divisor  = B;
        run_qdiv_wait();
        quotient = dv_quotient_out;

        tname = $sformatf("OD01[%0d]: MUL(%0d,%0d)=%0d qdiv->%0d exp=%0d",
                          i, A, B, cgra_result, quotient, A);
        if (cgra_result === (A*B) && quotient === A) begin
            pass_count++;
            `ifdef TB_VERBOSE
            $display("[PASS] %s", tname);
            `endif
        end else begin
            error_count++;
            $display("[FAIL] %s", tname);
        end
    end
    $display("[OD01] Done.");

    // =========================================================================
    // OD02: SHR vs qdiv(A, 2^K) floor division
    //   Verifies CGRA arithmetic right-shift equals floor division by 2^K.
    //   For positive A (bit 31 = 0), arithmetic shift == logical shift == floor div.
    //   K rotates through {1,2,4,8} across the 8 vectors.
    // =========================================================================
    $display("[OD02] SHR vs qdiv power-of-2 (8 vectors)...");

    for (i = 0; i < 8; i++) begin
        lfsr_state = lfsr32_next(lfsr_state);
        A = lfsr_state & 32'h00007FFF;  // 15-bit: keeps IMM[15:0] sign-bit 0 after PE extension
        K = shift_tbl[i % 4];

        // CGRA: pe[0,2] PASS0(A) → East; pe[0,3] SHR(West=A, IMM=K)
        config_pe_imm(4'd2, OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, A[15:0]);
        config_pe_imm(4'd3, OP_SHR,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, K[15:0]);
        run_cgra(8);
        cgra_result = read_pe_result(4'd3);  // = A >>> K

        // qdiv(A, 2^K) must equal A >> K
        dv_dividend = A;
        dv_divisor  = (32'd1 << K);
        run_qdiv_wait();
        quotient = dv_quotient_out;

        tname = $sformatf("OD02[%0d]: SHR(%0d,%0d)=%0d qdiv(%0d,%0d)=%0d",
                          i, A, K, cgra_result, A, (32'd1<<K), quotient);
        if (cgra_result === quotient) begin
            pass_count++;
            `ifdef TB_VERBOSE
            $display("[PASS] %s", tname);
            `endif
        end else begin
            error_count++;
            $display("[FAIL] %s", tname);
        end
    end
    $display("[OD02] Done.");

    // =========================================================================
    // OD03: General floor division property — Q×B ≤ A < (Q+1)×B
    //   For arbitrary A and B, qdiv(A,B) returns Q = floor(A/B).
    //   CGRA MUL(Q,B) independently computes Q×B.
    //   Three invariants of floor division must all hold simultaneously.
    // =========================================================================
    $display("[OD03] General floor division bounds via CGRA MUL (8 vectors)...");

    for (i = 0; i < 8; i++) begin
        lfsr_state = lfsr32_next(lfsr_state);
        A = lfsr_state & 32'h00007FFF;  // 15-bit: quotient ≤ A ≤ 32767 fits in IMM
        lfsr_state = lfsr32_next(lfsr_state);
        B = (lfsr_state & 32'h0000003F) | 32'h1;  // 6-bit, force ≥ 1

        // Step 1: compute Q = floor(A/B) using qdiv reference
        dv_dividend = A;
        dv_divisor  = B;
        run_qdiv_wait();
        quotient = dv_quotient_out;  // Q

        // Step 2: CGRA computes Q×B
        // Q ≤ A ≤ 65535 and B ≤ 63, so Q×B ≤ 65535 — fits in 16-bit IMM and MUL
        config_pe_imm(4'd2, OP_PASS0, SRC_IMM, 4'd0, 4'd0, ROUTE_EAST, quotient[15:0]);
        config_pe_imm(4'd3, OP_MUL,   SRC_WEST, SRC_IMM, 4'd0, ROUTE_NONE, B[15:0]);
        run_cgra(8);
        qb = read_pe_result(4'd3);  // = Q×B

        // Verify floor division property: Q×B ≤ A AND Q×B + B > A
        tname = $sformatf("OD03[%0d]: floor(%0d/%0d)=%0d Q*B=%0d",
                          i, A, B, quotient, qb);
        if (qb <= A && (qb + B) > A && (A - qb) < B) begin
            pass_count++;
            `ifdef TB_VERBOSE
            $display("[PASS] %s", tname);
            `endif
        end else begin
            error_count++;
            $display("[FAIL] %s qb=%0d A=%0d B=%0d lb=%0b ub=%0b rem=%0b",
                     tname, qb, A, B, (qb<=A), ((qb+B)>A), ((A-qb)<B));
        end
    end
    $display("[OD03] Done.");

    $display("\n[SUITE OD COMPLETE] OpenCores sequential divider tests done.\n");
endtask

`endif  // TB_SUITE_OPENCORES_DIV_SVH
