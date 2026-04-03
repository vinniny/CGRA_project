// ==============================================================================
// tb_defs.svh — CGRA 4×4 Testbench Definitions
// ==============================================================================
// Central definition file for the CGRA verification environment.
// Contains: assertion macros, address map, opcode ISA, source/route constants.
//
// USAGE:
//   Included as Layer 1 of the 5-layer testbench architecture.
//   Must be included before all other TB layers (tasks, checkers, suites).
//
// COMPILE FLAGS:
//   +define+TB_VERBOSE   — Enable transaction-level debug logging
//   +define+MAX_ERRORS=N — Override error threshold (default: 50)
// ==============================================================================

`ifndef TB_DEFS_SVH
`define TB_DEFS_SVH

// ============================================================================
// 1. VERBOSITY CONTROL
// ============================================================================
// TB_VERBOSE gates [INFO] transaction logs in driver tasks (DMA, APB, CU).
// Default: OFF (clean output). Override: compile with +define+TB_VERBOSE.
`ifndef TB_VERBOSE
    `define TB_QUIET
`endif

// ============================================================================
// 2. ERROR THRESHOLD
// ============================================================================
// Simulation halts with $fatal after MAX_ERRORS assertion/test failures.
// Prevents runaway log files on catastrophic design failures.
// Override: compile with +define+MAX_ERRORS=100 (or any integer).
`ifndef MAX_ERRORS
    `define MAX_ERRORS 50
`endif

// ============================================================================
// 3. ASSERTION MACROS
// ============================================================================
// All macros:
//   - Use standardized severity: [ERROR], [FATAL]
//   - Include simulation time: [ERROR] [%0t] message
//   - Respect protocol_check_enable && rst_n guard
//   - Increment global assertion_errors counter
//   - Check MAX_ERRORS threshold (except CHECK_NZ, CHECK_BIT)
//
// ASSERT_TRUE(cond, msg)         — Non-fatal; increments assertion_errors
// ASSERT_FATAL(cond, msg)        — Fatal; stops simulation immediately
// ASSERT(cond, msg)              — Non-fatal; shorthand for ASSERT_TRUE
// CHECK(cond, msg)               — Procedural condition check
// CHECK_EQ(actual, expected, msg)— 4-state comparison with mismatch detail
// CHECK_NZ(value, msg)           — Verify value is non-zero
// CHECK_BIT(value, bit, exp, msg)— Verify single bit value

`define ASSERT_TRUE(cond, msg) \
    assert (!(protocol_check_enable && rst_n) || (cond)) \
    else begin \
        $error("[ERROR] [%0t] [%m] %s", $time, msg); \
        assertion_errors = assertion_errors + 1; \
        if (assertion_errors >= `MAX_ERRORS) begin \
            $fatal(0, "[FATAL] [%0t] Error threshold reached (%0d errors). Stopping simulation.", $time, `MAX_ERRORS); \
        end \
    end

`define ASSERT_FATAL(cond, msg) \
    assert (!(protocol_check_enable && rst_n) || (cond)) \
    else begin $fatal(0, "[FATAL] [%0t] [%m] %s", $time, msg); end

`define ASSERT(cond, msg) \
    assert(cond) else begin \
        $error("[ERROR] [%0t] [%m] %s", $time, msg); \
        assertion_errors++; \
        if (assertion_errors >= `MAX_ERRORS) \
            $fatal(0, "[FATAL] [%0t] Error threshold reached (%0d)", $time, `MAX_ERRORS); \
    end

`define CHECK(cond, msg) \
    if (!(cond)) begin \
        $error("[ERROR] [%0t] [%m] %s", $time, msg); \
        assertion_errors++; \
        if (assertion_errors >= `MAX_ERRORS) \
            $fatal(0, "[FATAL] [%0t] Error threshold reached (%0d)", $time, `MAX_ERRORS); \
    end

`define CHECK_EQ(actual, expected, msg) \
    if ((actual) !== (expected)) begin \
        $error("[ERROR] [%0t] [%m] %s: Expected=0x%h, Actual=0x%h", \
               $time, msg, (expected), (actual)); \
        assertion_errors++; \
        if (assertion_errors >= `MAX_ERRORS) \
            $fatal(0, "[FATAL] [%0t] Error threshold reached (%0d)", $time, `MAX_ERRORS); \
    end

`define CHECK_NZ(value, msg) \
    if ((value) === 0) begin \
        $error("[ERROR] [%0t] [%m] %s: Expected non-zero, got 0", $time, msg); \
        assertion_errors++; \
    end

`define CHECK_BIT(value, bit, expected, msg) \
    if ((value)[(bit)] !== (expected)) begin \
        $error("[ERROR] [%0t] [%m] %s: bit[%0d] Expected=%b, Actual=%b", \
               $time, msg, (bit), (expected), (value)[(bit)]); \
        assertion_errors++; \
    end

// ============================================================================
// 4. WATCHDOG TIMEOUT
// ============================================================================
// Simulation terminates after TB_WATCHDOG_NS nanoseconds to prevent hangs.
// Default: 100ms of simulation time. Override with +define+TB_WATCHDOG_NS=N.
`ifndef TB_WATCHDOG_NS
    `define TB_WATCHDOG_NS 100_000_000
`endif

// ============================================================================
// 5. TESTBENCH PARAMETERS
// ============================================================================
localparam int TB_MEM_SIZE    = 4 * 1024 * 1024 + 4;  // 4MB + 4B (AXI RAM model size)
localparam int TB_TIMEOUT     = 10000;                 // Default DMA/CU poll timeout (cycles)
localparam int TB_CLK_PERIOD  = 10;                    // Clock period (ns): 10ns = 100MHz

// ============================================================================
// 6. APB REGISTER MAP — Complete Address Decode
// ============================================================================
// All registers are 32-bit wide, accessed via APB at the listed byte offsets.
// RW = read-write, RO = read-only, W1C = write-1-to-clear.
//
// ┌──────────────────────────────────────────────────────────────────────────┐
// │ Offset │ Name             │ R/W │ Bits    │ Description                 │
// ├────────┼──────────────────┼─────┼─────────┼─────────────────────────────┤
// │ 0x00   │ DMA_CTRL         │ RW  │ [0]     │ Start (auto-clear 1 cycle)  │
// │ 0x04   │ DMA_STATUS       │ RO  │ [0]=Busy│ [1]=Done (sticky)           │
// │ 0x08   │ DMA_SRC          │ RW  │ [31:0]  │ Source address (physical)   │
// │ 0x0C   │ DMA_DST          │ RW  │ [31:0]  │ Destination address         │
// │ 0x10   │ DMA_SIZE         │ RW  │ [31:0]  │ Transfer size (bytes)       │
// │ 0x14   │ DMA_SRC_STRIDE   │ RW  │ [31:0]  │ 2D: row stride (bytes)     │
// │ 0x18   │ DMA_ROWS         │ RW  │ [31:0]  │ 2D: number of rows (0=1D)  │
// │ 0x1C   │ DMA_COLS         │ RW  │ [31:0]  │ 2D: columns per row (bytes)│
// ├────────┼──────────────────┼─────┼─────────┼─────────────────────────────┤
// │ 0x20   │ CU_CTRL          │ RW  │ [0]=Start│[1]=Soft Reset              │
// │ 0x24   │ CU_STATUS        │ RO  │ [0]=Busy│ [1]=Done (sticky)           │
// │ 0x28   │ CU_CYCLES        │ RO  │ [31:0]  │ Execution cycle count       │
// │ 0x2C   │ CU_TIMEOUT       │ RW  │ [31:0]  │ Max cycles (0=no limit)     │
// ├────────┼──────────────────┼─────┼─────────┼─────────────────────────────┤
// │ 0x30   │ IRQ_STATUS       │ W1C │ [0]=DMA │ [1]=CU Done                 │
// │ 0x34   │ IRQ_MASK         │ RW  │ [1:0]   │ IRQ enable mask             │
// ├────────┼──────────────────┼─────┼─────────┼─────────────────────────────┤
// │ 0x40   │ RESULT_DATA      │ RO  │ [31:0]  │ PE[3,3] output              │
// │ 0x44   │ RESULT_STATUS    │ RO  │ [0]     │ result_valid (cu_done)       │
// ├────────┼──────────────────┼─────┼─────────┼─────────────────────────────┤
// │ 0x48   │ LOOP_START       │ RW  │ [15:0]  │ Inner loop start PC         │
// │ 0x4C   │ LOOP_END         │ RW  │ [15:0]  │ Inner loop end PC           │
// │ 0x50   │ LOOP_COUNT       │ RW  │ [15:0]  │ Inner loop iterations (0=off)│
// ├────────┼──────────────────┼─────┼─────────┼─────────────────────────────┤
// │ 0x58   │ RESULT_ROW0      │ RO  │ [31:0]  │ East-edge row 0 (PE 0,3)    │
// │ 0x5C   │ RESULT_ROW1      │ RO  │ [31:0]  │ East-edge row 1 (PE 1,3)    │
// │ 0x60   │ RESULT_ROW2      │ RO  │ [31:0]  │ East-edge row 2 (PE 2,3)    │
// │ 0x64   │ RESULT_ROW3      │ RO  │ [31:0]  │ East-edge row 3 (PE 3,3)    │
// ├────────┼──────────────────┼─────┼─────────┼─────────────────────────────┤
// │ 0x68   │ LOOP2_START      │ RW  │ [15:0]  │ Outer loop start PC         │
// │ 0x6C   │ LOOP2_END        │ RW  │ [15:0]  │ Outer loop end PC           │
// │ 0x70   │ LOOP2_COUNT      │ RW  │ [15:0]  │ Outer loop iterations (0=off)│
// │ 0x74   │ TILE_BANK_SEL    │ RW  │ [0]     │ Double-buffer select (0/1)  │
// └──────────────────────────────────────────────────────────────────────────┘

// --- DMA Engine Registers (0x00-0x1C) ---
localparam logic [31:0] ADDR_DMA_CTRL       = 32'h00;  // [0] Start (auto-clear)
localparam logic [31:0] ADDR_DMA_STATUS     = 32'h04;  // [0] Busy, [1] Done
localparam logic [31:0] ADDR_DMA_SRC        = 32'h08;  // Source address
localparam logic [31:0] ADDR_DMA_DST        = 32'h0C;  // Destination address
localparam logic [31:0] ADDR_DMA_SIZE       = 32'h10;  // Transfer size (bytes)
localparam logic [31:0] ADDR_DMA_SRC_STRIDE = 32'h14;  // 2D: source row stride
localparam logic [31:0] ADDR_DMA_ROWS       = 32'h18;  // 2D: row count (0=1D)
localparam logic [31:0] ADDR_DMA_COLS       = 32'h1C;  // 2D: cols per row (bytes)

// --- Control Unit Registers (0x20-0x2C) ---
localparam logic [31:0] ADDR_CU_CTRL        = 32'h20;  // [0] Start, [1] Soft Reset
localparam logic [31:0] ADDR_CU_STATUS      = 32'h24;  // [0] Busy, [1] Done
localparam logic [31:0] ADDR_CU_CYCLES      = 32'h28;  // Execution cycle count
localparam logic [31:0] ADDR_CU_TIMEOUT     = 32'h2C;  // Max cycles (0=no limit)

// --- IRQ Registers (0x30-0x38) ---
localparam logic [31:0] ADDR_IRQ_STATUS     = 32'h30;  // W1C: [0] DMA Done, [1] CU Done, [2] DMA Error
localparam logic [31:0] ADDR_IRQ_MASK       = 32'h34;  // [2:0] IRQ enable mask
localparam logic [31:0] ADDR_DMA_ERROR      = 32'h38;  // RO: [0] error flag, [2:1] error code

// --- Result Registers (0x40-0x44, muxed in cgra_top) ---
localparam logic [31:0] ADDR_RESULT_DATA    = 32'h40;  // PE[3,3] output
localparam logic [31:0] ADDR_RESULT_STATUS  = 32'h44;  // [0] result_valid

// --- Hardware Loop Level 1 (0x48-0x50) ---
localparam logic [31:0] ADDR_LOOP_START     = 32'h48;  // Inner loop start PC [15:0]
localparam logic [31:0] ADDR_LOOP_END       = 32'h4C;  // Inner loop end PC [15:0]
localparam logic [31:0] ADDR_LOOP_COUNT     = 32'h50;  // Inner loop iterations [15:0]

// --- East-Edge Row Results (0x58-0x64, muxed in cgra_top) ---
localparam logic [31:0] ADDR_RESULT_ROW0    = 32'h58;  // PE(0,3) east output
localparam logic [31:0] ADDR_RESULT_ROW1    = 32'h5C;  // PE(1,3) east output
localparam logic [31:0] ADDR_RESULT_ROW2    = 32'h60;  // PE(2,3) east output
localparam logic [31:0] ADDR_RESULT_ROW3    = 32'h64;  // PE(3,3) east output

// --- Hardware Loop Level 2 — Nested (0x68-0x70) ---
localparam logic [31:0] ADDR_LOOP2_START    = 32'h68;  // Outer loop start PC [15:0]
localparam logic [31:0] ADDR_LOOP2_END      = 32'h6C;  // Outer loop end PC [15:0]
localparam logic [31:0] ADDR_LOOP2_COUNT    = 32'h70;  // Outer loop iterations [15:0]

// --- Double-Buffer Control (0x74) ---
localparam logic [31:0] ADDR_TILE_BANK_SEL  = 32'h74;  // [0] PE buffer select (0/1)

// --- Unmapped address for negative testing ---
localparam logic [31:0] ADDR_UNMAPPED       = 32'h80;

// ============================================================================
// 7. DMA ADDRESS SPACE PREFIXES
// ============================================================================
// The DMA engine routes transfers based on bits [31:28] of dst/src address:
//   0x0XXX_XXXX → External DDR (AXI4 master)
//   0x1XXX_XXXX → Tile Memory (4 banks × 4096 words)
//   0x2XXX_XXXX → PE Config RAM (16 PEs × 16 contexts × 64-bit)
localparam logic [31:0] BASE_AXI    = 32'h0000_0000;
localparam logic [31:0] BASE_TILE   = 32'h1000_0000;
localparam logic [31:0] BASE_CONFIG = 32'h2000_0000;

// Physical DDR staging addresses (match cgra_driver.h for board alignment)
localparam logic [31:0] DDR_BASE    = 32'h1000_0000;
localparam logic [31:0] DDR_IMAGE   = 32'h1000_0000;  // Image/tile data staging
localparam logic [31:0] DDR_CONFIG  = 32'h1010_0000;  // PE config data staging
localparam logic [31:0] DDR_RESULT  = 32'h1020_0000;  // DMA write-back destination

// ============================================================================
// 8. PE ISA — 21 Operations (Opcodes 0-20)
// ============================================================================
// Each PE executes one opcode per context cycle. Opcodes are encoded in the
// config frame bits [5:0]. All operations use 32-bit signed operands unless
// data_mode (config bits [50:49]) selects INT16×2 or INT8×4 SIMD mode.
//
// ┌────┬────────────┬─────────────────────────────────────────────────────────┐
// │ Op │ Name       │ Operation                                              │
// ├────┼────────────┼─────────────────────────────────────────────────────────┤
// │  0 │ NOP        │ No operation (preserves alu_result)                     │
// │  1 │ ADD        │ A + B → saturate to INT32, update accumulator           │
// │  2 │ SUB        │ A - B → saturate to INT32, update accumulator           │
// │  3 │ MUL        │ A × B → lower 32 bits (SIMD: dot-product)              │
// │  4 │ MAC        │ Acc += A × B → saturating 40-bit (SIMD: dot-product)   │
// │  5 │ AND        │ A & B (bitwise)                                         │
// │  6 │ OR         │ A | B (bitwise)                                         │
// │  7 │ XOR        │ A ^ B (bitwise)                                         │
// │  8 │ SHL        │ A << B[4:0] (logical left shift, 0-31)                  │
// │  9 │ SHR        │ A >>> B[4:0] (arithmetic right shift, 0-31)             │
// │ 10 │ CMP_GT     │ (A > B) ? 1 : 0 (signed), sets predicate_flag          │
// │ 11 │ CMP_LT     │ (A < B) ? 1 : 0 (signed), sets predicate_flag          │
// │ 12 │ CMP_EQ     │ (A == B) ? 1 : 0, sets predicate_flag                  │
// │ 13 │ LOAD_SPM   │ Load from scratchpad[B[7:0]] → alu_result               │
// │ 14 │ STORE_SPM  │ Store A → scratchpad[B[7:0]]                            │
// │ 15 │ ACC_CLR    │ Clear accumulator and alu_result to 0                   │
// │ 16 │ PASS0      │ Pass operand A (routing helper)                         │
// │ 17 │ PASS1      │ Pass operand B (routing helper)                         │
// │ 18 │ LIF        │ Leaky Integrate-and-Fire neuron (spiking)               │
// │ 19 │ RELU       │ max(0, A) — ANN activation                              │
// │ 20 │ MAX        │ max(A, B) signed — pooling                              │
// └────┴────────────┴─────────────────────────────────────────────────────────┘

localparam logic [5:0] OP_NOP       = 6'd0;
localparam logic [5:0] OP_ADD       = 6'd1;
localparam logic [5:0] OP_SUB       = 6'd2;
localparam logic [5:0] OP_MUL       = 6'd3;
localparam logic [5:0] OP_MAC       = 6'd4;
localparam logic [5:0] OP_AND       = 6'd5;
localparam logic [5:0] OP_OR        = 6'd6;
localparam logic [5:0] OP_XOR       = 6'd7;
localparam logic [5:0] OP_SHL       = 6'd8;
localparam logic [5:0] OP_SHR       = 6'd9;
localparam logic [5:0] OP_CMP_GT    = 6'd10;
localparam logic [5:0] OP_CMP_LT    = 6'd11;
localparam logic [5:0] OP_CMP_EQ    = 6'd12;
localparam logic [5:0] OP_LOAD_SPM  = 6'd13;
localparam logic [5:0] OP_STORE_SPM = 6'd14;
localparam logic [5:0] OP_ACC_CLR   = 6'd15;
localparam logic [5:0] OP_PASS0     = 6'd16;
localparam logic [5:0] OP_PASS1     = 6'd17;
localparam logic [5:0] OP_LIF       = 6'd18;
localparam logic [5:0] OP_RELU      = 6'd19;
localparam logic [5:0] OP_MAX       = 6'd20;

// ============================================================================
// 9. PE OPERAND SOURCE SELECT (config bits [9:6] and [13:10])
// ============================================================================
// Selects which input feeds operand0 (src0_sel) and operand1 (src1_sel).
// Each PE has 7 possible operand sources.

localparam logic [3:0] SRC_RF       = 4'd0;   // Register File (16×32-bit)
localparam logic [3:0] SRC_NORTH    = 4'd1;   // North neighbor output
localparam logic [3:0] SRC_EAST     = 4'd2;   // East neighbor output
localparam logic [3:0] SRC_SOUTH    = 4'd3;   // South neighbor output
localparam logic [3:0] SRC_WEST     = 4'd4;   // West neighbor (Tile Memory input)
localparam logic [3:0] SRC_SPM      = 4'd5;   // Scratchpad Memory (256×32-bit)
localparam logic [3:0] SRC_IMM      = 4'd6;   // 16-bit immediate (sign-extended to 32)

// ============================================================================
// 10. PE ROUTE DIRECTION MASK (config bits [21:18])
// ============================================================================
// Controls which directions the PE broadcasts its alu_result to.
// Each bit enables one output direction. Multiple bits = multicast.
//
// Bit mapping in config frame:
//   config[21] → valid_out_n (North)
//   config[20] → valid_out_e (East)
//   config[19] → valid_out_s (South)
//   config[18] → valid_out_w (West)

localparam logic [3:0] ROUTE_NONE   = 4'b0000;  // No output routing
localparam logic [3:0] ROUTE_WEST   = 4'b0001;  // West only
localparam logic [3:0] ROUTE_SOUTH  = 4'b0010;  // South only
localparam logic [3:0] ROUTE_EAST   = 4'b0100;  // East only
localparam logic [3:0] ROUTE_NORTH  = 4'b1000;  // North only
localparam logic [3:0] ROUTE_ALL    = 4'b1111;  // Broadcast all 4 directions

// ============================================================================
// 11. PE CONFIG FRAME BIT MAP (64-bit)
// ============================================================================
// Each PE config entry is 64 bits. Decoded by cgra_pe.sv:
//
// ┌────────┬──────────────────────────────────────────────────────┐
// │ Bits   │ Field                                                │
// ├────────┼──────────────────────────────────────────────────────┤
// │ [5:0]  │ op_code — ALU operation (0-20, see ISA table above)  │
// │ [9:6]  │ src0_sel — Operand A source (0-6)                    │
// │ [13:10]│ src1_sel — Operand B source (0-6)                    │
// │ [17:14]│ dst_sel — RF write-back address (0-15)               │
// │ [21:18]│ route_mask — Output direction mask (NESW)            │
// │ [22]   │ pred_en — Predicate execution enable                 │
// │ [23]   │ pred_inv — Invert predicate condition                │
// │ [39:24]│ immediate — 16-bit signed immediate value            │
// │ [43:40]│ cfg_dest_x — XY routing X coordinate                 │
// │ [47:44]│ branch_target — Dynamic branch PC target (B4)        │
// │ [48]   │ branch_en — Enable dynamic branching (B4)            │
// │ [50:49]│ data_mode — 00=INT32, 01=INT16×2, 10=INT8×4 (B1)    │
// │ [63:51]│ reserved                                              │
// └────────┴──────────────────────────────────────────────────────┘

`endif // TB_DEFS_SVH
