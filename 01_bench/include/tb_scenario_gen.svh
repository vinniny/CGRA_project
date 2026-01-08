// ==============================================================================
// tb_scenario_gen.svh - Verilator-Native Stimulus Generator
// ==============================================================================
// Constrained-random generation and coverage tracking for Verilator 5.x.
// Uses SystemVerilog 2017 constructs: int, logic, automatic functions.
// ==============================================================================

// ============================================================================
// SCENARIO MODES
// ============================================================================
typedef enum logic [1:0] {
    MODE_NORMAL = 2'b00,
    MODE_STRESS = 2'b01,
    MODE_CORNER = 2'b10
} scenario_mode_t;

scenario_mode_t current_scenario = MODE_NORMAL;

// ============================================================================
// COVERAGE COUNTERS
// ============================================================================
int cov_single_beat   = 0;
int cov_multi_beat    = 0;
int cov_max_burst     = 0;
int cov_4kb_boundary  = 0;
int cov_stress_cycles = 0;
int cov_reset_tests   = 0;
int cov_overlap_txn   = 0;

// ============================================================================
// RANDOM ADDRESS GENERATORS
// ============================================================================
function automatic logic [31:0] rand_src_addr();
    return 32'h1000 + (($urandom % (32'h6000 / 4)) * 4);
endfunction

function automatic logic [31:0] rand_dst_addr();
    return 32'h8000 + (($urandom % (32'h7000 / 4)) * 4);
endfunction

function automatic logic [31:0] rand_size();
    int r = $urandom % 100;
    if (r < 20) begin
        cov_single_beat++;
        return 4 + (($urandom % 4) * 4);
    end else if (r < 80) begin
        cov_multi_beat++;
        return 20 + (($urandom % 124) * 4);
    end else begin
        cov_max_burst++;
        return 516 + (($urandom % 128) * 4);
    end
endfunction

function automatic int rand_stress();
    int r = $urandom % 100;
    if (r < 70)      return 0;
    else if (r < 90) return 1 + ($urandom % 30);
    else             return 31 + ($urandom % 50);
endfunction

// ============================================================================
// SCENARIO CONTROL
// ============================================================================
task automatic set_scenario(input scenario_mode_t mode);
    current_scenario = mode;
    case (mode)
        MODE_NORMAL: $display("[SCENARIO] Switched to NORMAL mode");
        MODE_STRESS: $display("[SCENARIO] Switched to STRESS mode");
        MODE_CORNER: $display("[SCENARIO] Switched to CORNER_CASE mode");
    endcase
endtask

// ============================================================================
// COVERAGE REPORTING
// ============================================================================
task automatic print_coverage_report();
    $display("");
    $display("╔══════════════════════════════════════════════════════════════╗");
    $display("║                    COVERAGE REPORT                           ║");
    $display("╠══════════════════════════════════════════════════════════════╣");
    $display("║  Transfer Types:                                             ║");
    $display("║    Single-beat (4-16B):     %6d hits                      ║", cov_single_beat);
    $display("║    Multi-beat (20-512B):    %6d hits                      ║", cov_multi_beat);
    $display("║    Max-burst (516-1024B):   %6d hits                      ║", cov_max_burst);
    $display("╠══════════════════════════════════════════════════════════════╣");
    $display("║  Stress & Corner Cases:                                      ║");
    $display("║    4KB Boundary Tests:      %6d hits                      ║", cov_4kb_boundary);
    $display("║    Stress Cycles:           %6d hits                      ║", cov_stress_cycles);
    $display("║    Reset Recovery Tests:    %6d hits                      ║", cov_reset_tests);
    $display("║    Overlap Transactions:    %6d hits                      ║", cov_overlap_txn);
    $display("╚══════════════════════════════════════════════════════════════╝");
    $display("");
endtask
