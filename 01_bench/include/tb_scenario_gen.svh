`ifndef TB_SCENARIO_GEN_SVH
`define TB_SCENARIO_GEN_SVH
// ==============================================================================
// tb_scenario_gen.svh — Constrained-Random Stimulus Generation
// ==============================================================================
// Provides:
//   1. Scenario mode control (NORMAL/STRESS/CORNER)
//   2. Manual coverage counters (backward-compatible)
//   3. Legacy random generator functions
//   4. SystemVerilog `rand` class for constrained-random DMA/PE stimuli
// ==============================================================================

// ============================================================================
// 1. SCENARIO MODES
// ============================================================================
typedef enum logic [1:0] {
    MODE_NORMAL = 2'b00,
    MODE_STRESS = 2'b01,
    MODE_CORNER = 2'b10
} scenario_mode_t;

scenario_mode_t current_scenario = MODE_NORMAL;

// ============================================================================
// 2. COVERAGE COUNTERS (backward-compatible, also used by covergroups)
// ============================================================================
int cov_single_beat   = 0;
int cov_multi_beat    = 0;
int cov_max_burst     = 0;
int cov_4kb_boundary  = 0;
int cov_stress_cycles = 0;
int cov_reset_tests   = 0;

// ============================================================================
// 3. LEGACY RANDOM GENERATORS (used by existing test suites)
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
// 4. CONSTRAINED-RANDOM STIMULUS CLASS: DMA Transfers
// ============================================================================
// Use: cgra_dma_stim stim = new; stim.randomize(); dma_transfer(stim.src, ...);
class cgra_dma_stim;
    rand logic [31:0] src;
    rand logic [31:0] dst;
    rand logic [31:0] size;
    rand logic [1:0]  dir;   // 0=DDR→DDR, 1=DDR→tile, 2=tile→DDR

    // Addresses must be word-aligned
    constraint c_align {
        src[1:0] == 2'b00;
        dst[1:0] == 2'b00;
        size[1:0] == 2'b00;
    }

    // Size: 4–4096 bytes (1–1024 words)
    constraint c_size {
        size >= 4;
        size <= 4096;
    }

    // Source address in AXI range (prefix 0x0), within TB_MEM_SIZE
    constraint c_src_axi {
        src[31:28] == 4'h0;
        src[21:0] < (22'h3F_FFFF - size);  // Don't overflow 4MB model
    }

    // Direction-dependent dst prefix
    constraint c_dst_prefix {
        (dir == 0) -> dst[31:28] == 4'h0;  // DDR→DDR
        (dir == 1) -> dst[31:28] == 4'h1;  // DDR→tile
        (dir == 2) -> dst[31:28] == 4'h0;  // tile→DDR (src becomes tile)
    }

    // DDR dst must also be within model
    constraint c_dst_axi {
        (dst[31:28] == 4'h0) -> dst[21:0] < (22'h3F_FFFF - size);
    }

    // Weight distribution: prefer small and medium transfers
    constraint c_size_dist {
        size dist {
            [4:32]      := 40,
            [36:256]    := 40,
            [260:1024]  := 15,
            [1028:4096] := 5
        };
    }
endclass

// ============================================================================
// 5. CONSTRAINED-RANDOM STIMULUS CLASS: PE Configuration
// ============================================================================
class cgra_pe_stim;
    rand logic [5:0]  opcode;
    rand logic [3:0]  src0;
    rand logic [3:0]  src1;
    rand logic [3:0]  dst;
    rand logic [3:0]  route;
    rand logic [15:0] imm;
    rand logic [3:0]  pe_id;

    // Valid opcodes only (0-20)
    constraint c_opcode { opcode <= 6'd20; }

    // Valid source selects (0-6)
    constraint c_src {
        src0 <= 4'd6;
        src1 <= 4'd6;
    }

    // PE ID (0-15)
    constraint c_pe_id { pe_id <= 4'd15; }

    // Dst register (0-15)
    constraint c_dst { dst <= 4'd15; }

    // Route mask: bias toward common patterns
    constraint c_route {
        route dist {
            4'b0000 := 40,   // NONE
            4'b0100 := 20,   // EAST
            4'b0010 := 10,   // SOUTH
            4'b1000 := 10,   // NORTH
            4'b0001 := 10,   // WEST
            4'b1111 := 10    // ALL
        };
    }

    // Arithmetic ops should prefer WEST+IMM sources (tile data + immediate)
    constraint c_arith_src {
        (opcode inside {[1:4]}) -> (src0 == 4'd4);  // SRC_WEST for ADD/SUB/MUL/MAC
        (opcode inside {[1:4]}) -> (src1 == 4'd6);  // SRC_IMM
    }
endclass

// ============================================================================
// 6. CONSTRAINED-RANDOM STIMULUS CLASS: APB Register Access
// ============================================================================
class cgra_apb_stim;
    rand logic [31:0] addr;
    rand logic [31:0] data;
    rand logic        is_write;

    // Only valid register offsets
    constraint c_addr {
        addr inside {
            32'h00, 32'h04, 32'h08, 32'h0C, 32'h10, 32'h14, 32'h18, 32'h1C,
            32'h20, 32'h24, 32'h28, 32'h2C, 32'h30, 32'h34,
            32'h40, 32'h44, 32'h48, 32'h4C, 32'h50,
            32'h58, 32'h5C, 32'h60, 32'h64,
            32'h68, 32'h6C, 32'h70, 32'h74
        };
    }

    // RO registers should only be read
    constraint c_ro_read_only {
        (addr inside {32'h04, 32'h24, 32'h28, 32'h40, 32'h44,
                      32'h58, 32'h5C, 32'h60, 32'h64}) -> (is_write == 0);
    }
endclass

// ============================================================================
// 7. SCENARIO CONTROL
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
// 8. SEQUENCE BASE CLASSES (Phase E — UVM-inspired)
// ============================================================================
// Virtual base class for reusable test sequences. Subclasses override body()
// to implement specific test flows using driver APIs.
virtual class cgra_sequence;
    cgra_tb_config cfg;
    string name;
    
    function new(cgra_tb_config c, string n = "cgra_seq");
        cfg  = c;
        name = n;
    endfunction
    
    // Override in subclasses to implement sequence behavior
    virtual task body(apb_driver apb_drv);
        $display("[SEQ] Base sequence body() - override in subclass");
    endtask
endclass

// Example: DMA stress sequence (random DMA transfers)
class dma_stress_sequence extends cgra_sequence;
    int num_iters;
    
    function new(cgra_tb_config c, int iters = 10);
        super.new(c, "dma_stress_seq");
        num_iters = iters;
    endfunction
    
    virtual task body(apb_driver apb_drv);
        for (int i = 0; i < num_iters; i++) begin
            logic [31:0] src = rand_src_addr();
            logic [31:0] dst = rand_dst_addr();
            logic [31:0] size = rand_size();
            
            if (cfg.verbosity >= 2)
                $display("[SEQ] %0t %s: DMA iter %0d/%0d src=0x%h dst=0x%h size=%0d",
                         $time, name, i+1, num_iters, src, dst, size);
            
            // Use existing DMA task infrastructure
            apb_drv.write(ADDR_DMA_SRC, src);
            apb_drv.write(ADDR_DMA_DST, dst);
            apb_drv.write(ADDR_DMA_SIZE, size);
            apb_drv.write(ADDR_DMA_CTRL, 32'h1);  // Start DMA

            // Wait for completion via shared task (avoids invalid event control).
            wait_dma_done(TB_TIMEOUT);
        end
        $display("[SEQ] %0t %s complete: %0d DMA transfers", $time, name, num_iters);
    endtask
endclass

// Example: PE random sequence (random PE configs)
class pe_random_sequence extends cgra_sequence;
    int num_ops;
    
    function new(cgra_tb_config c, int ops = 5);
        super.new(c, "pe_random_seq");
        num_ops = ops;
    endfunction
    
    virtual task body(apb_driver apb_drv);
        for (int i = 0; i < num_ops; i++) begin
            logic [3:0] pe_id = $urandom_range(0, 15);
            logic [5:0] op = $urandom_range(0, 20);
            
            if (cfg.verbosity >= 2)
                $display("[SEQ] %0t %s: Configure PE %0d op=%0d", $time, name, pe_id, op);
            
            // Use existing config task (would need pe_config_driver integration)
            // Simplified for now
        end
        $display("[SEQ] %0t %s complete: %0d PE configs", $time, name, num_ops);
    endtask
endclass

// ============================================================================
// 9. COVERAGE REPORTING (legacy counters)
// ============================================================================
task automatic print_coverage_report();
    $display("");
    $display("  COVERAGE REPORT (Scenario Counters)");
    $display("  ----------------------------------------------------------------");
    $display("    Single-beat (4-16B):     %6d hits", cov_single_beat);
    $display("    Multi-beat (20-512B):    %6d hits", cov_multi_beat);
    $display("    Max-burst (516-1024B):   %6d hits", cov_max_burst);
    $display("    4KB Boundary Tests:      %6d hits", cov_4kb_boundary);
    $display("    Stress Cycles:           %6d hits", cov_stress_cycles);
    $display("    Reset Recovery Tests:    %6d hits", cov_reset_tests);
    $display("");
endtask

`endif
