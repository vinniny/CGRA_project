// ==============================================================================
// CGRA APB CSR — Configuration and Status Registers
// ==============================================================================
// APB slave, zero wait states. 29 registers at 0x00-0x7C + 0x80.
//
// DMA:  DMA_CTRL(00 RW), DMA_STATUS(04 RO), DMA_SRC(08), DMA_DST(0C),
//       DMA_SIZE(10), DMA_SRC_STRIDE(14), DMA_ROWS(18), DMA_COLS(1C),
//       DMA_ERROR(38 RO), DMA_DESC_HEAD(7C RW), DMA_DESC_STATUS(80 RO)
// CU:   CU_CTRL(20 RW), CU_STATUS(24 RO), CU_CYCLES(28 RO), CU_TIMEOUT(2C RW)
// IRQ:  IRQ_STATUS(30 W1C), IRQ_MASK(34 RW)
// Loop: LOOP_START(48), LOOP_END(4C), LOOP_COUNT(50),
//       LOOP2_START(68), LOOP2_END(6C), LOOP2_COUNT(70)
// Misc: RESULT_SKIP(54), TILE_BANK_SEL(74), TILE_AUTO_INC(78)
// ==============================================================================

module cgra_apb_csr #(
    parameter ADDR_WIDTH = 32,
    parameter DATA_WIDTH = 32
)(
    input  logic                  clk,
    input  logic                  rst_n,
    
    // =========================================================================
    // APB Slave Interface
    // =========================================================================
    input  logic                  psel,
    input  logic                  penable,
    input  logic                  pwrite,
    input  logic [ADDR_WIDTH-1:0] paddr,        // Only [7:0] used for register decode (ASSIGN-10)
    input  logic [DATA_WIDTH-1:0] pwdata,
    output logic [DATA_WIDTH-1:0] prdata,
    output logic                  pready,
    output logic                  pslverr,
    
    // =========================================================================
    // DMA Configuration Wires (Static Config)
    // =========================================================================
    output logic [31:0]           dma_src,
    output logic [31:0]           dma_dst,
    output logic [31:0]           dma_size,
    output logic [31:0]           dma_src_stride,   // 2D stride
    output logic [31:0]           dma_rows,          // 2D row count
    output logic [31:0]           dma_cols,           // 2D cols/row
    output logic                  dma_start,      // Auto-clearing pulse
    input  logic                  dma_busy_i,
    input  logic                  dma_done_i,
    input  logic [1:0]            dma_error_code_i,  // AXI BRESP/RRESP error code
    input  logic                  dma_error_valid_i,  // Pulse on error detection
    
    // =========================================================================
    // Control Unit Configuration Wires
    // =========================================================================
    output logic                  cu_start,       // Auto-clearing pulse
    output logic                  cu_soft_reset,
    output logic [31:0]           cu_max_cycles,  // Programmable timeout limit
    input  logic                  cu_busy_i,
    input  logic                  cu_done_i,
    input  logic [31:0]           cu_cycles_i,
    
    // =========================================================================
    // Interrupt Output
    // =========================================================================
    output logic                  irq,
    
    // =========================================================================
    // Hardware Loop Configuration (NEW - for LPR multi-tile execution)
    // =========================================================================
    output logic [15:0]           loop_start_pc,
    output logic [15:0]           loop_end_pc,
    output logic [15:0]           loop_count,

    // Nested Loop (Level 2) — B3
    output logic [15:0]           loop2_start_pc,
    output logic [15:0]           loop2_end_pc,
    output logic [15:0]           loop2_count,

    // Double-Buffering — C2
    output logic                  tile_bank_sel,

    // Tile Auto-Increment
    output logic                  tile_auto_inc_en,

    // Result FIFO
    output logic [3:0]            result_skip_count,    // warmup skip (default 13)

    // Scatter-Gather DMA
    output logic [31:0]           dma_desc_head,        // descriptor chain head pointer
    output logic                  dma_chain_start,      // pulse: start chain execution
    input  logic                  dma_chain_active_i,   // chain in progress
    input  logic [15:0]           dma_desc_completed_i  // descriptors completed
);

    // =========================================================================
    // Address Map - Register Definitions
    // =========================================================================
    // DMA Region
    localparam ADDR_DMA_CTRL   = 8'h00;  // RW: [0] Start, [1] Chain start (both auto-clear)
    localparam ADDR_DMA_STATUS = 8'h04;  // RO: [0] Busy, [1] Done

    // DMA_CTRL bit definitions
    localparam DMA_CTRL_START       = 0;   // [0] Legacy single-shot start (auto-clear)
    localparam DMA_CTRL_CHAIN_START = 1;   // [1] Scatter-gather chain start (auto-clear)
    localparam ADDR_DMA_SRC    = 8'h08;  // RW: Source address
    localparam ADDR_DMA_DST    = 8'h0C;  // RW: Dest address
    localparam ADDR_DMA_SIZE   = 8'h10;  // RW: Transfer size (bytes)
    localparam ADDR_DMA_SRC_STRIDE = 8'h14; // RW: 2D source row stride (bytes)
    localparam ADDR_DMA_ROWS       = 8'h18; // RW: 2D number of rows (0=1D mode)
    localparam ADDR_DMA_COLS       = 8'h1C; // RW: 2D columns per row (bytes)

    // Control Unit Region
    localparam ADDR_CU_CTRL    = 8'h20;  // RW: [0] Start, [1] Soft Reset
    localparam ADDR_CU_STATUS  = 8'h24;  // RO: [0] Busy, [1] Done
    localparam ADDR_CU_CYCLES  = 8'h28;  // RO: Cycle counter
    localparam ADDR_CU_TIMEOUT = 8'h2C;  // RW: Max cycles (0 = no limit)
    
    // IRQ Region
    localparam ADDR_IRQ_STATUS = 8'h30;  // W1C: [0] DMA Done, [1] CU Done, [2] DMA Error
    localparam ADDR_IRQ_MASK   = 8'h34;  // RW: IRQ enable mask
    localparam ADDR_DMA_ERROR  = 8'h38;  // RO: [0] Error flag, [2:1] Error code (BRESP/RRESP)
    
    // Hardware Loop Region (NEW - LPR)
    localparam ADDR_LOOP_START = 8'h48;  // RW: Loop start PC
    localparam ADDR_LOOP_END   = 8'h4C;  // RW: Loop end PC
    localparam ADDR_LOOP_COUNT = 8'h50;  // RW: Loop iteration count

    // Nested Loop (Level 2) Region — B3
    localparam ADDR_LOOP2_START = 8'h68; // RW: Outer loop start PC
    localparam ADDR_LOOP2_END   = 8'h6C; // RW: Outer loop end PC
    localparam ADDR_LOOP2_COUNT = 8'h70; // RW: Outer loop iterations (0=disabled)

    // Double-Buffering — C2
    localparam ADDR_TILE_BANK_SEL = 8'h74; // RW: PE buffer selector (bit[0])

    // Result FIFO
    localparam ADDR_RESULT_SKIP   = 8'h54; // RW: [3:0] warmup skip count (default 11)

    // Tile Auto-Increment
    localparam ADDR_TILE_AUTO_INC = 8'h78; // RW: bit[0] = enable tile addr auto-inc on loop wrap

    // Scatter-Gather DMA
    localparam ADDR_DMA_DESC_HEAD   = 8'h7C; // RW: descriptor chain head pointer (DDR addr)
    localparam ADDR_DMA_DESC_STATUS = 8'h80; // RO: [0] chain_active, [15:8] desc_completed

    // =========================================================================
    // Internal Registers
    // =========================================================================
    logic [31:0] reg_dma_ctrl;
    logic [31:0] reg_dma_src;
    logic [31:0] reg_dma_dst;
    logic [31:0] reg_dma_size;
    logic [31:0] reg_dma_src_stride;  // 2D stride
    logic [31:0] reg_dma_rows;        // 2D row count (0=1D)
    logic [31:0] reg_dma_cols;        // 2D cols per row (bytes)

    logic [31:0] reg_cu_ctrl;
    logic [31:0] reg_cu_timeout;  // Programmable timeout limit
    
    logic [31:0] reg_irq_mask;
    
    // Hardware Loop registers (NEW - LPR)
    logic [31:0] reg_loop_start;
    logic [31:0] reg_loop_end;
    logic [31:0] reg_loop_count;

    // Nested Loop (Level 2) registers — B3
    logic [31:0] reg_loop2_start;
    logic [31:0] reg_loop2_end;
    logic [31:0] reg_loop2_count;
    logic [31:0] reg_tile_bank_sel;
    logic [31:0] reg_tile_auto_inc;
    logic [31:0] reg_result_skip;
    logic [31:0] reg_dma_desc_head;

    logic        dma_done_latch;
    logic        cu_done_latch;
    logic        dma_error_latch;
    logic [1:0]  dma_error_code_latch;
    logic        dma_error_valid_prev;  // dma_error_valid_i is a level; edge-detect to allow W1C

    assign pready  = 1'b1;
    assign pslverr = 1'b0;

    // APB write decode helpers
    wire apb_write = psel && penable && pwrite;
    wire apb_w_irq_status = apb_write && (paddr[7:0] == ADDR_IRQ_STATUS);
    wire apb_w_dma_ctrl   = apb_write && (paddr[7:0] == ADDR_DMA_CTRL);
    wire apb_w_cu_ctrl    = apb_write && (paddr[7:0] == ADDR_CU_CTRL);

    // Sticky done/error latches. Start-write clears done; engine pulse sets it;
    // software W1C via IRQ_STATUS clears. Engine sets win over W1C clears.
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            dma_done_latch       <= 1'b0;
            cu_done_latch        <= 1'b0;
            dma_error_latch      <= 1'b0;
            dma_error_code_latch <= 2'b00;
            dma_error_valid_prev <= 1'b0;
        end else begin
            dma_error_valid_prev <= dma_error_valid_i;

            // DMA done: immediate start-write (same cycle as DMA_CTRL[0/1]) clears
            // the latch before wait_dma_done can read it.
            if ((apb_w_dma_ctrl && (pwdata[DMA_CTRL_START] || pwdata[DMA_CTRL_CHAIN_START]))
                || dma_start || dma_chain_start || reg_cu_ctrl[1])
                dma_done_latch <= 1'b0;
            else if (dma_done_i)
                dma_done_latch <= 1'b1;
            else if (apb_w_irq_status && pwdata[0])
                dma_done_latch <= 1'b0;

            // CU done: done-set wins over W1C-clear
            if (apb_w_irq_status && pwdata[1]) cu_done_latch <= 1'b0;
            if (cu_done_i)                     cu_done_latch <= 1'b1;
            if (cu_start)                      cu_done_latch <= 1'b0;

            // DMA error: rising-edge latch (error_valid is level-sticky)
            if (apb_w_irq_status && pwdata[2]) dma_error_latch <= 1'b0;
            if (dma_error_valid_i && !dma_error_valid_prev) begin
                dma_error_latch      <= 1'b1;
                dma_error_code_latch <= dma_error_code_i;
            end
            if (dma_start) begin
                dma_error_latch      <= 1'b0;
                dma_error_code_latch <= 2'b00;
            end
        end
    end
    
    logic [31:0] reg_dma_status;
    logic [31:0] reg_cu_status;
    logic [31:0] reg_irq_status;

    assign reg_dma_status = {30'd0, dma_done_latch, dma_busy_i};
    assign reg_cu_status  = {30'd0, cu_done_latch, cu_busy_i};
    assign reg_irq_status = {29'd0, dma_error_latch, cu_done_latch, dma_done_latch};

    // Config writes are rejected while the relevant engine is busy to prevent
    // mid-transaction corruption.
    wire dma_wr_ok  = !dma_busy_i;
    wire cu_wr_ok   = !cu_busy_i;
    wire tile_wr_ok = !dma_busy_i && !cu_busy_i;

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            reg_dma_ctrl       <= 32'd0;
            reg_dma_src        <= 32'd0;
            reg_dma_dst        <= 32'd0;
            reg_dma_size       <= 32'd0;
            reg_dma_src_stride <= 32'd0;
            reg_dma_rows       <= 32'd0;
            reg_dma_cols       <= 32'd0;
            reg_cu_ctrl        <= 32'd0;
            reg_cu_timeout     <= 32'd0;
            reg_irq_mask       <= 32'd0;
            reg_loop_start     <= 32'd0;
            reg_loop_end       <= 32'd15;
            reg_loop_count     <= 32'd0;
            reg_loop2_start    <= 32'd0;
            reg_loop2_end      <= 32'd15;
            reg_loop2_count    <= 32'd0;
            reg_tile_bank_sel  <= 32'd0;
            reg_tile_auto_inc  <= 32'd0;
            reg_result_skip    <= 32'd13;  // 3-stage PE x 3 hops + router pipeline warmup
            reg_dma_desc_head  <= 32'd0;
        end else begin
            if (apb_write) begin
                case (paddr[7:0])
                    ADDR_DMA_CTRL:       reg_dma_ctrl       <= pwdata;
                    ADDR_DMA_SRC:        if (dma_wr_ok)  reg_dma_src        <= pwdata;
                    ADDR_DMA_DST:        if (dma_wr_ok)  reg_dma_dst        <= pwdata;
                    ADDR_DMA_SIZE:       if (dma_wr_ok)  reg_dma_size       <= pwdata;
                    ADDR_DMA_SRC_STRIDE: if (dma_wr_ok)  reg_dma_src_stride <= pwdata;
                    ADDR_DMA_ROWS:       if (dma_wr_ok)  reg_dma_rows       <= pwdata;
                    ADDR_DMA_COLS:       if (dma_wr_ok)  reg_dma_cols       <= pwdata;
                    ADDR_CU_CTRL:        reg_cu_ctrl        <= pwdata;
                    ADDR_CU_TIMEOUT:     if (cu_wr_ok)   reg_cu_timeout     <= pwdata;
                    ADDR_IRQ_MASK:       reg_irq_mask       <= pwdata;
                    ADDR_LOOP_START:     if (cu_wr_ok)   reg_loop_start     <= pwdata;
                    ADDR_LOOP_END:       if (cu_wr_ok)   reg_loop_end       <= pwdata;
                    ADDR_LOOP_COUNT:     if (cu_wr_ok)   reg_loop_count     <= pwdata;
                    ADDR_LOOP2_START:    if (cu_wr_ok)   reg_loop2_start    <= pwdata;
                    ADDR_LOOP2_END:      if (cu_wr_ok)   reg_loop2_end      <= pwdata;
                    ADDR_LOOP2_COUNT:    if (cu_wr_ok)   reg_loop2_count    <= pwdata;
                    ADDR_TILE_BANK_SEL:  if (tile_wr_ok) reg_tile_bank_sel  <= pwdata;
                    ADDR_TILE_AUTO_INC:  if (cu_wr_ok)   reg_tile_auto_inc  <= pwdata;
                    ADDR_RESULT_SKIP:    if (cu_wr_ok)   reg_result_skip    <= pwdata;
                    ADDR_DMA_DESC_HEAD:  if (dma_wr_ok)  reg_dma_desc_head  <= pwdata;
                    default: ;
                endcase
            end

            // Auto-clear start-pulse bits one cycle after assertion
            if (reg_dma_ctrl[0] && !apb_w_dma_ctrl) reg_dma_ctrl[0] <= 1'b0;
            if (reg_dma_ctrl[1] && !apb_w_dma_ctrl) reg_dma_ctrl[1] <= 1'b0;
            if (reg_cu_ctrl[0]  && !apb_w_cu_ctrl)  reg_cu_ctrl[0]  <= 1'b0;

        end
    end
    
    // =========================================================================
    // Read Logic - Register Mux
    // =========================================================================
    always_comb begin
        case (paddr[7:0])
            ADDR_DMA_CTRL:   prdata = reg_dma_ctrl;
            ADDR_DMA_STATUS: prdata = reg_dma_status;
            ADDR_DMA_SRC:    prdata = reg_dma_src;
            ADDR_DMA_DST:    prdata = reg_dma_dst;
            ADDR_DMA_SIZE:       prdata = reg_dma_size;
            ADDR_DMA_SRC_STRIDE: prdata = reg_dma_src_stride;
            ADDR_DMA_ROWS:       prdata = reg_dma_rows;
            ADDR_DMA_COLS:       prdata = reg_dma_cols;
            ADDR_CU_CTRL:    prdata = reg_cu_ctrl;
            ADDR_CU_STATUS:  prdata = reg_cu_status;
            ADDR_CU_CYCLES:  prdata = cu_cycles_i;
            ADDR_CU_TIMEOUT: prdata = reg_cu_timeout;
            ADDR_IRQ_STATUS: prdata = reg_irq_status;
            ADDR_IRQ_MASK:   prdata = reg_irq_mask;
            ADDR_DMA_ERROR:  prdata = {29'd0, dma_error_latch, dma_error_code_latch};
            ADDR_LOOP_START: prdata = reg_loop_start;
            ADDR_LOOP_END:   prdata = reg_loop_end;
            ADDR_LOOP_COUNT:  prdata = reg_loop_count;
            ADDR_LOOP2_START: prdata = reg_loop2_start;
            ADDR_LOOP2_END:   prdata = reg_loop2_end;
            ADDR_LOOP2_COUNT:    prdata = reg_loop2_count;
            ADDR_RESULT_SKIP:     prdata = reg_result_skip;
            ADDR_TILE_BANK_SEL:  prdata = reg_tile_bank_sel;
            ADDR_TILE_AUTO_INC:  prdata = reg_tile_auto_inc;
            ADDR_DMA_DESC_HEAD:  prdata = reg_dma_desc_head;
            ADDR_DMA_DESC_STATUS: prdata = {16'b0, dma_desc_completed_i,
                                            7'b0, dma_chain_active_i};
            default:         prdata = 32'h0;           // Undefined address → zero
        endcase
    end
    
    // =========================================================================
    // Output Wire Assignments
    // =========================================================================
    assign dma_src  = reg_dma_src;
    assign dma_dst  = reg_dma_dst;
    assign dma_size       = reg_dma_size;
    assign dma_src_stride = reg_dma_src_stride;
    assign dma_rows       = reg_dma_rows;
    assign dma_cols       = reg_dma_cols;
    assign dma_start = reg_dma_ctrl[0];
    
    assign cu_start         = reg_cu_ctrl[0];
    assign cu_soft_reset    = reg_cu_ctrl[1];
    assign cu_max_cycles    = reg_cu_timeout;

    assign loop_start_pc    = reg_loop_start[15:0];
    assign loop_end_pc      = reg_loop_end[15:0];
    assign loop_count       = reg_loop_count[15:0];
    assign loop2_start_pc   = reg_loop2_start[15:0];
    assign loop2_end_pc     = reg_loop2_end[15:0];
    assign loop2_count      = reg_loop2_count[15:0];
    assign tile_bank_sel    = reg_tile_bank_sel[0];
    assign tile_auto_inc_en = reg_tile_auto_inc[0];
    assign result_skip_count = reg_result_skip[3:0];
    assign dma_desc_head    = reg_dma_desc_head;
    assign dma_chain_start  = reg_dma_ctrl[1];

    always_ff @(posedge clk) begin
        if (!rst_n) irq <= 1'b0;
        else        irq <= |(reg_irq_status & reg_irq_mask);
    end

endmodule
