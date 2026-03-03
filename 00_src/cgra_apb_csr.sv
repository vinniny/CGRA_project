// ==============================================================================
// CGRA APB CSR - Centralized Configuration and Status Registers
// ==============================================================================
// APB Slave interface (zero wait states) for CPU configuration.
// Provides config wires to DMA Engine and Control Unit.
//
// REGISTER MAP (11 registers):
//   0x00  DMA_CTRL    RW  [0] Start (auto-clear)
//   0x04  DMA_STATUS  RO  [0] Busy, [1] Done (sticky)
//   0x08  DMA_SRC     RW  Source address
//   0x0C  DMA_DST     RW  Destination address
//   0x10  DMA_SIZE    RW  Transfer size (bytes)
//   0x20  CU_CTRL     RW  [0] Start, [1] Soft Reset
//   0x24  CU_STATUS   RO  [0] Busy, [1] Done (sticky)
//   0x28  CU_CYCLES   RO  Cycle counter
//   0x2C  CU_TIMEOUT  RW  Max cycles (0 = no limit)  [NEW]
//   0x30  IRQ_STATUS  W1C [0] DMA Done, [1] CU Done
//   0x34  IRQ_MASK    RW  IRQ enable mask
//   0x48  LOOP_START  RW  Hardware loop start PC  [NEW - LPR]
//   0x4C  LOOP_END    RW  Hardware loop end PC    [NEW - LPR]
//   0x50  LOOP_COUNT  RW  Hardware loop count     [NEW - LPR]
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
    output logic                  dma_start,      // Auto-clearing pulse
    input  logic                  dma_busy_i,
    input  logic                  dma_done_i,
    
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
    output logic [15:0]           loop_count
);

    // =========================================================================
    // Address Map - Register Definitions
    // =========================================================================
    // DMA Region
    localparam ADDR_DMA_CTRL   = 8'h00;  // RW: [0] Start (auto-clear)
    localparam ADDR_DMA_STATUS = 8'h04;  // RO: [0] Busy, [1] Done
    localparam ADDR_DMA_SRC    = 8'h08;  // RW: Source address
    localparam ADDR_DMA_DST    = 8'h0C;  // RW: Dest address
    localparam ADDR_DMA_SIZE   = 8'h10;  // RW: Transfer size (bytes)
    
    // Control Unit Region
    localparam ADDR_CU_CTRL    = 8'h20;  // RW: [0] Start, [1] Soft Reset
    localparam ADDR_CU_STATUS  = 8'h24;  // RO: [0] Busy, [1] Done
    localparam ADDR_CU_CYCLES  = 8'h28;  // RO: Cycle counter
    localparam ADDR_CU_TIMEOUT = 8'h2C;  // RW: Max cycles (0 = no limit)
    
    // IRQ Region
    localparam ADDR_IRQ_STATUS = 8'h30;  // W1C: [0] DMA Done, [1] CU Done
    localparam ADDR_IRQ_MASK   = 8'h34;  // RW: IRQ enable mask
    
    // Hardware Loop Region (NEW - LPR)
    localparam ADDR_LOOP_START = 8'h48;  // RW: Loop start PC
    localparam ADDR_LOOP_END   = 8'h4C;  // RW: Loop end PC
    localparam ADDR_LOOP_COUNT = 8'h50;  // RW: Loop iteration count
    
    // =========================================================================
    // Internal Registers
    // =========================================================================
    logic [31:0] reg_dma_ctrl;
    logic [31:0] reg_dma_src;
    logic [31:0] reg_dma_dst;
    logic [31:0] reg_dma_size;
    
    logic [31:0] reg_cu_ctrl;
    logic [31:0] reg_cu_timeout;  // Programmable timeout limit
    
    logic [31:0] reg_irq_mask;
    
    // Hardware Loop registers (NEW - LPR)
    logic [31:0] reg_loop_start;
    logic [31:0] reg_loop_end;
    logic [31:0] reg_loop_count;
    
    // Status registers - latched (done bits are sticky)
    logic        dma_done_latch;
    logic        cu_done_latch;
    
    // =========================================================================
    // APB Interface - Zero Wait States
    // =========================================================================
    assign pready = 1'b1;
    assign pslverr = 1'b0;
    
    // =========================================================================
    // Done Bit Latching - Sticky until next start
    // =========================================================================
    // W1C wire: APB write to IRQ_STATUS clears individual done latches
    wire irq_w1c = psel && penable && pwrite && (paddr[7:0] == ADDR_IRQ_STATUS);

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            dma_done_latch <= 1'b0;
            cu_done_latch <= 1'b0;
        end else begin
            // DMA done latch: start-clear wins to prevent stale done on back-to-back ops
            // Priority: start-clear > W1C-clear > done-set  (last assignment wins)
            if (dma_done_i)
                dma_done_latch <= 1'b1;          // done sets
            if (irq_w1c && pwdata[0])
                dma_done_latch <= 1'b0;          // W1C clears
            if (dma_start)
                dma_done_latch <= 1'b0;          // start clears (wins)
            
            // CU done latch: start-clear wins
            if (cu_done_i)
                cu_done_latch <= 1'b1;
            if (irq_w1c && pwdata[1])
                cu_done_latch <= 1'b0;
            if (cu_start)
                cu_done_latch <= 1'b0;
        end
    end
    
    // =========================================================================
    // Status Register Construction
    // =========================================================================
    logic [31:0] reg_dma_status;
    logic [31:0] reg_cu_status;
    logic [31:0] reg_irq_status;
    
    always_comb begin
        reg_dma_status = {30'd0, dma_done_latch, dma_busy_i};
        reg_cu_status  = {30'd0, cu_done_latch, cu_busy_i};
        reg_irq_status = {30'd0, cu_done_latch, dma_done_latch};
    end
    
    // =========================================================================
    // Write Logic - Register Updates
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            reg_dma_ctrl <= 32'd0;
            reg_dma_src  <= 32'd0;
            reg_dma_dst  <= 32'd0;
            reg_dma_size <= 32'd0;
            reg_cu_ctrl  <= 32'd0;
            reg_cu_timeout <= 32'd0;  // Default: no timeout
            reg_irq_mask <= 32'd0;
            reg_loop_start <= 32'd0;       // Default: PC 0
            reg_loop_end   <= 32'd15;      // Default: PC 15 (full range)
            reg_loop_count <= 32'd0;       // Default: no looping
        end else begin
            // APB Write Phase
            if (psel && penable && pwrite) begin
                case (paddr[7:0])
                    ADDR_DMA_CTRL:   reg_dma_ctrl <= pwdata;
                    ADDR_DMA_SRC:    reg_dma_src  <= pwdata;
                    ADDR_DMA_DST:    reg_dma_dst  <= pwdata;
                    ADDR_DMA_SIZE:   reg_dma_size <= pwdata;
                    ADDR_CU_CTRL:    reg_cu_ctrl  <= pwdata;
                    ADDR_CU_TIMEOUT: reg_cu_timeout <= pwdata;
                    ADDR_IRQ_MASK:   reg_irq_mask <= pwdata;
                    ADDR_LOOP_START: reg_loop_start <= pwdata;
                    ADDR_LOOP_END:   reg_loop_end   <= pwdata;
                    ADDR_LOOP_COUNT: reg_loop_count <= pwdata;
                    // Read-only registers: ignore writes
                    default: ;
                endcase
            end
            
            // FIX: Auto-clear start bits unconditionally (moved out of else branch)
            // Prevents multi-cycle pulse during back-to-back APB writes to other regs
            if (reg_dma_ctrl[0] && !(psel && penable && pwrite && paddr[7:0] == ADDR_DMA_CTRL))
                reg_dma_ctrl[0] <= 1'b0;
            if (reg_cu_ctrl[0] && !(psel && penable && pwrite && paddr[7:0] == ADDR_CU_CTRL))
                reg_cu_ctrl[0] <= 1'b0;
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
            ADDR_DMA_SIZE:   prdata = reg_dma_size;
            ADDR_CU_CTRL:    prdata = reg_cu_ctrl;
            ADDR_CU_STATUS:  prdata = reg_cu_status;
            ADDR_CU_CYCLES:  prdata = cu_cycles_i;
            ADDR_CU_TIMEOUT: prdata = reg_cu_timeout;
            ADDR_IRQ_STATUS: prdata = reg_irq_status;
            ADDR_IRQ_MASK:   prdata = reg_irq_mask;
            ADDR_LOOP_START: prdata = reg_loop_start;
            ADDR_LOOP_END:   prdata = reg_loop_end;
            ADDR_LOOP_COUNT: prdata = reg_loop_count;
            default:         prdata = 32'hDEAD_BEEF;  // Undefined address
        endcase
    end
    
    // =========================================================================
    // Output Wire Assignments
    // =========================================================================
    assign dma_src  = reg_dma_src;
    assign dma_dst  = reg_dma_dst;
    assign dma_size = reg_dma_size;
    assign dma_start = reg_dma_ctrl[0];
    
    assign cu_start = reg_cu_ctrl[0];
    assign cu_soft_reset = reg_cu_ctrl[1];
    assign cu_max_cycles = reg_cu_timeout;  // Programmable timeout
    
    // Hardware Loop outputs
    assign loop_start_pc = reg_loop_start[15:0];
    assign loop_end_pc   = reg_loop_end[15:0];
    assign loop_count    = reg_loop_count[15:0];
    
    // =========================================================================
    // IRQ Generation
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            irq <= 1'b0;
        end else begin
            // IRQ = (Status & Mask) != 0
            irq <= |(reg_irq_status & reg_irq_mask);
        end
    end

endmodule
