// ==============================================================================
// tb_defs.svh - CGRA Testbench Definitions (Xcelium / Verilator)
// ==============================================================================
// Layered Architecture:
//   - Assertion macros with protocol_check_enable guard
//   - Verbosity control for clean/debug log modes
//   - Centralized test result tracking (log_test_result pattern)
//   - Address map constants
// ==============================================================================

`ifndef TB_DEFS_SVH
`define TB_DEFS_SVH

// ============================================================================
// VERBOSITY CONTROL
// ============================================================================
// Set TB_VERBOSE to gate debug output. Default OFF for clean logs.
// Override: +define+TB_VERBOSE on the compile command line.
`ifndef TB_VERBOSE
    `define TB_QUIET
`endif

// ============================================================================
// ASSERTION MACROS (Protocol-check aware)
// ============================================================================
// All macros respect protocol_check_enable and rst_n.
// ASSERT_TRUE: Non-fatal — increments assertion_errors
// ASSERT_FATAL: Fatal — stops simulation immediately

`define ASSERT_TRUE(cond, msg) \
    assert (!(protocol_check_enable && rst_n) || (cond)) \
    else begin \
        $error("[ASSERT] %s @ %0t", msg, $time); \
        assertion_errors = assertion_errors + 1; \
    end

`define ASSERT_FATAL(cond, msg) \
    assert (!(protocol_check_enable && rst_n) || (cond)) \
    else begin $error("[FATAL] %s @ %0t", msg, $time); $finish; end

// Simple assertion - stops on failure
`define ASSERT(cond, msg) \
    assert(cond) else $error("[ASSERT] %s at time %0t", msg, $time)

// Assertion with error counter (for non-fatal checks)
`define CHECK(cond, msg) \
    if (!(cond)) begin \
        $error("[CHECK FAIL] %s at time %0t", msg, $time); \
        assertion_errors++; \
    end

// Value comparison with expected
`define CHECK_EQ(actual, expected, msg) \
    if ((actual) !== (expected)) begin \
        $error("[CHECK_EQ FAIL] %s: expected=0x%h, got=0x%h at time %0t", \
               msg, (expected), (actual), $time); \
        assertion_errors++; \
    end

// Non-zero check
`define CHECK_NZ(value, msg) \
    if ((value) == 0) begin \
        $error("[CHECK_NZ FAIL] %s: expected non-zero at time %0t", msg, $time); \
        assertion_errors++; \
    end

// Bit check
`define CHECK_BIT(value, bit, expected, msg) \
    if ((value)[(bit)] !== (expected)) begin \
        $error("[CHECK_BIT FAIL] %s: bit[%0d] expected=%b, got=%b at time %0t", \
               msg, (bit), (expected), (value)[(bit)], $time); \
        assertion_errors++; \
    end

// ============================================================================
// WATCHDOG TIMEOUT
// ============================================================================
`ifndef TB_WATCHDOG_NS
    `define TB_WATCHDOG_NS 100_000_000
`endif

// ============================================================================
// TESTBENCH PARAMETERS
// ============================================================================
localparam int TB_MEM_SIZE    = 128 * 1024 + 4;  // 128KB + 4B guard for byte-lane OOB (addr[16:0]+3)
localparam int TB_TIMEOUT     = 10000;       // Default timeout cycles
localparam int TB_CLK_PERIOD  = 10;          // 10ns = 100MHz

// ============================================================================
// ADDRESS MAP CONSTANTS - DMA Engine
// ============================================================================
localparam logic [31:0] ADDR_DMA_CTRL   = 32'h00;
localparam logic [31:0] ADDR_DMA_STATUS = 32'h04;
localparam logic [31:0] ADDR_DMA_SRC    = 32'h08;
localparam logic [31:0] ADDR_DMA_DST    = 32'h0C;
localparam logic [31:0] ADDR_DMA_SIZE   = 32'h10;

// ============================================================================
// ADDRESS MAP CONSTANTS - Control Unit
// ============================================================================
localparam logic [31:0] ADDR_CU_CTRL    = 32'h20;
localparam logic [31:0] ADDR_CU_STATUS  = 32'h24;
localparam logic [31:0] ADDR_CU_CYCLES  = 32'h28;

// ============================================================================
// ADDRESS MAP CONSTANTS - IRQ
// ============================================================================
localparam logic [31:0] ADDR_IRQ_STATUS = 32'h30;
localparam logic [31:0] ADDR_IRQ_MASK   = 32'h34;

// ============================================================================
// ADDRESS MAP CONSTANTS - Hybrid I/O Result Registers
// ============================================================================
localparam logic [31:0] ADDR_RESULT_DATA   = 32'h40;  // RO: PE[15] output (global_result)
localparam logic [31:0] ADDR_RESULT_STATUS = 32'h44;  // RO: [0] result_valid (cu_done)

// ============================================================================
// ADDRESS MAP CONSTANTS - Hardware Loop (NEW - LPR)
// ============================================================================
localparam logic [31:0] ADDR_LOOP_START  = 32'h48;  // RW: Loop start PC
localparam logic [31:0] ADDR_LOOP_END    = 32'h4C;  // RW: Loop end PC
localparam logic [31:0] ADDR_LOOP_COUNT  = 32'h50;  // RW: Loop iteration count

// ============================================================================
// ADDRESS MAP CONSTANTS - LPR Row Results (NEW)
// ============================================================================
localparam logic [31:0] ADDR_RESULT_ROW0 = 32'h58;  // RO: East-edge row 0 (PE 0,3)
localparam logic [31:0] ADDR_RESULT_ROW1 = 32'h5C;  // RO: East-edge row 1 (PE 1,3)
localparam logic [31:0] ADDR_RESULT_ROW2 = 32'h60;  // RO: East-edge row 2 (PE 2,3)
localparam logic [31:0] ADDR_RESULT_ROW3 = 32'h64;  // RO: East-edge row 3 (PE 3,3)

// ============================================================================
// ADDRESS MAP CONSTANTS - Other
// ============================================================================
// FIX: 0x100 had paddr[7:0]=0x00 aliasing DMA_CTRL; 0x80 hits CSR default (DEAD_BEEF)
localparam logic [31:0] ADDR_UNMAPPED   = 32'h80;

// ============================================================================
// TILE/CONFIG BASE ADDRESSES
// ============================================================================
localparam logic [31:0] BASE_AXI    = 32'h0000_0000;
localparam logic [31:0] BASE_TILE   = 32'h1000_0000;
localparam logic [31:0] BASE_CONFIG = 32'h2000_0000;

// ============================================================================
// PE OPCODE CONSTANTS (19-Op ISA)
// ============================================================================
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
localparam logic [5:0] OP_RELU      = 6'd19;  // NEW: ReLU for ANN/LPR
localparam logic [5:0] OP_MAX       = 6'd20;  // NEW: Max for pooling

// ============================================================================
// PE SOURCE SELECT CONSTANTS
// ============================================================================
localparam logic [3:0] SRC_RF       = 4'd0;   // Register File
localparam logic [3:0] SRC_NORTH    = 4'd1;   // North neighbor
localparam logic [3:0] SRC_EAST     = 4'd2;   // East neighbor
localparam logic [3:0] SRC_SOUTH    = 4'd3;   // South neighbor
localparam logic [3:0] SRC_WEST     = 4'd4;   // West neighbor (Tile Memory)
localparam logic [3:0] SRC_SPM      = 4'd5;   // Scratchpad Memory
localparam logic [3:0] SRC_IMM      = 4'd6;   // Immediate

// ============================================================================
// PE ROUTE DIRECTION CONSTANTS
// ============================================================================
// PE route_mask mapping: {local(4), N(3), E(2), S(1), W(0)}
// build_pe_config packs route[3:0] into config[21:18], then PE decodes:
//   valid_out_n = route_mask[3], valid_out_e = route_mask[2],
//   valid_out_s = route_mask[1], valid_out_w = route_mask[0]
localparam logic [3:0] ROUTE_NONE   = 4'b0000;  // No routing
localparam logic [3:0] ROUTE_WEST   = 4'b0001;  // bit 0 → valid_out_w
localparam logic [3:0] ROUTE_SOUTH  = 4'b0010;  // bit 1 → valid_out_s
localparam logic [3:0] ROUTE_EAST   = 4'b0100;  // bit 2 → valid_out_e
localparam logic [3:0] ROUTE_NORTH  = 4'b1000;  // bit 3 → valid_out_n
localparam logic [3:0] ROUTE_ALL    = 4'b1111;  // Broadcast all directions

`endif // TB_DEFS_SVH
