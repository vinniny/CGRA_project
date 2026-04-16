// ==============================================================================
// CGRA Top-Level Integration
// ==============================================================================
// 4×4 CGRA accelerator with APB control, AXI4 DMA, and neuromorphic support.
//
// COMPONENTS:
//   - APB CSR (cgra_apb_csr)       — 29 registers (0x00-0x78)
//   - Config Broadcaster            — slot-0 replay to slots 1-15
//   - DMA Subsystem (engine + SG)   — AXI4 burst master, 32-word FIFO
//   - Control Unit                  — nested HW loops, dynamic branch, timeout
//   - Tile Memory (4 banks × 4KB)   — double-buffered, DMA-writable
//   - 4×4 PE Array (mesh broadcast) — 21-op ISA, 40-bit MAC
//   - Result FIFO (256-entry × 4)   — east-edge capture, pop-on-write
// ==============================================================================

module cgra_top #(
    parameter DATA_WIDTH = 32,
    parameter COORD_WIDTH = 4,
    parameter ADDR_WIDTH = 32,
    parameter AXI_ID_WIDTH = 4,
    parameter SPM_DEPTH = 256,
    parameter RF_DEPTH = 16,
    parameter CONFIG_WIDTH = 64,
    parameter NUM_PES = 16
)(
    input  logic clk,
    input  logic rst_n,
    
    // =========================================================================
    // APB Slave Interface (from CPU/Testbench)
    // =========================================================================
    input  logic                  psel,
    input  logic                  penable,
    input  logic                  pwrite,
    input  logic [ADDR_WIDTH-1:0] paddr,
    input  logic [31:0]           pwdata,
    output logic [31:0]           prdata,
    output logic                  pready,
    output logic                  pslverr,
    
    // =========================================================================
    // AXI4 Master Interface (DMA to External RAM with Burst Support)
    // =========================================================================
    // Write Address Channel
    output logic [AXI_ID_WIDTH-1:0] m_axi_awid,
    output logic [ADDR_WIDTH-1:0] m_axi_awaddr,
    output logic [7:0]            m_axi_awlen,     // Burst length
    output logic [2:0]            m_axi_awsize,    // Beat size
    output logic [1:0]            m_axi_awburst,   // Burst type
    output logic                  m_axi_awvalid,
    input  logic                  m_axi_awready,

    // Write Data Channel
    output logic [31:0]           m_axi_wdata,
    output logic [3:0]            m_axi_wstrb,
    output logic                  m_axi_wlast,     // Last beat in burst
    output logic                  m_axi_wvalid,
    input  logic                  m_axi_wready,

    // Write Response Channel
    input  logic [AXI_ID_WIDTH-1:0] m_axi_bid,
    input  logic [1:0]            m_axi_bresp,
    input  logic                  m_axi_bvalid,
    output logic                  m_axi_bready,

    // Read Address Channel
    output logic [AXI_ID_WIDTH-1:0] m_axi_arid,
    output logic [ADDR_WIDTH-1:0] m_axi_araddr,
    output logic [7:0]            m_axi_arlen,     // Burst length
    output logic [2:0]            m_axi_arsize,    // Beat size
    output logic [1:0]            m_axi_arburst,   // Burst type
    output logic                  m_axi_arvalid,
    input  logic                  m_axi_arready,

    // Read Data Channel
    input  logic [AXI_ID_WIDTH-1:0] m_axi_rid,
    input  logic [1:0]            m_axi_rresp,
    input  logic [31:0]           m_axi_rdata,
    input  logic                  m_axi_rlast,     // Last beat in burst
    input  logic                  m_axi_rvalid,
    output logic                  m_axi_rready,
    
    // =========================================================================
    // Interrupt Output
    // =========================================================================
    output logic                  irq,
    
    // =========================================================================
    // Synthesis Keeper (Prevents optimizer from removing unused logic)
    // =========================================================================
    output logic                  synthesis_keep,
    
    // =========================================================================
    // Debug Ports (For ILA/Chipscope probing)
    // =========================================================================
    output logic                  dbg_dma_busy,
    output logic [2:0]            dbg_dma_read_state,
    output logic [2:0]            dbg_dma_write_state,
    output logic                  dbg_dma_fifo_full,
    output logic                  dbg_dma_fifo_empty,
    output logic [31:0]           dbg_dma_write_words_remaining  // ILA probe
);

    // =========================================================================
    // Derived Constants
    // =========================================================================
    localparam CONTEXT_DEPTH = 16;

    // =========================================================================
    // Internal Wires: APB CSR Multiplexing
    // =========================================================================
    logic [31:0] csr_prdata;  // Internal prdata from u_csr module
    
    // =========================================================================
    // Internal Wires: CSR → DMA
    // =========================================================================
    logic [31:0] dma_src;
    logic [31:0] dma_dst;
    logic [31:0] dma_size;
    logic [31:0] dma_src_stride;
    logic [31:0] dma_rows;
    logic [31:0] dma_cols;
    logic        dma_start;
    logic        dma_busy;
    logic        dma_done;
    logic [1:0]  dma_error_code;
    logic        dma_error_valid;
    
    // =========================================================================
    // Internal Wires: CSR → Control Unit
    // =========================================================================
    logic        cu_start;
    logic        cu_soft_reset;
    logic [31:0] cu_max_cycles;  // Programmable timeout (CSR @ 0x2C)
    logic        cu_busy;
    logic        cu_done;
    logic        cu_loops_done;  // All internal loop counters exhausted
    logic [31:0] cu_cycles;
    
    // Hardware Loop Configuration (from CSR)
    logic [15:0] cu_loop_start_pc;
    logic [15:0] cu_loop_end_pc;
    logic [15:0] cu_loop_count;
    logic [15:0] cu_loop2_start_pc;
    logic [15:0] cu_loop2_end_pc;
    logic [15:0] cu_loop2_count;
    logic        tile_bank_sel_csr;
    logic        tile_auto_inc_en;
    logic [7:0]  cu_next_tile_offset;
    // DMA subsystem CSR/status signals
    logic [31:0] dma_desc_head;
    logic        dma_chain_start;
    logic        dma_chain_active;
    logic [15:0] dma_desc_completed;
    logic [3:0]  array_branch_target;
    logic        array_branch_taken;
    logic        array_branch_taken_r;  // Registered: breaks LUTLP-1 comb loop
    
    // East-edge result FIFO (replaces single-latch result_row)
    logic [DATA_WIDTH-1:0] result_fifo_pop_data [0:3];
    logic                  result_fifo_pop_valid;
    logic                  result_fifo_pop_read;
    logic                  result_fifo_full;
    logic [8:0]            result_fifo_count;
    logic                  result_fifo_overflow;
    logic                  result_fifo_underflow;
    logic                  result_fifo_clear;
    logic [3:0]            result_skip_count;
    
    // =========================================================================
    // Internal Wires: Control Unit → Array
    // =========================================================================
    logic        pe_enable;
    logic        pe_reset_n;
    logic        array_done;
    
    // =========================================================================
    // Internal Wires: DMA → Tile Memory (Data Fridge)
    // =========================================================================
    logic [11:0] dma_tile_addr;
    logic [1:0]  dma_tile_bank_sel;
    logic        dma_tile_we;
    logic [31:0] dma_tile_wdata;
    logic        dma_tile_re;     // DMA tile read enable (for tile-to-DDR read-back)
    logic [31:0] dma_tile_rdata;  // Read data from tile memory (1-cycle latent)
    logic        dma_tile_valid;  // Read data valid from tile memory
    
    // Row data from tile memory (1-cycle SRAM latency)
    logic [31:0] row_data [0:3];
    logic        row_valid [0:3];

    // =========================================================================
    // Internal Wires: DMA → Config Bus (Recipe Book)
    // =========================================================================
    logic [31:0] dma_cfg_addr;
    logic        dma_cfg_we;
    logic [31:0] dma_cfg_wdata;
    logic [3:0]  dma_cfg_pe_sel;  // Which PE to configure (0-15)
    
    // Double-pump 64-bit config loader: DMA writes HI (addr[2]=0) then LO
    // (addr[2]=1). The LO write commits the full 64-bit word to the config
    // bus. config_high_loaded guards against a stray LO write before HI.
    logic [31:0] config_high_reg;
    logic [63:0] config_full_word;
    logic        config_commit_en;
    logic        config_high_loaded;

    always_ff @(posedge clk) begin
        if (!rst_n || cu_soft_reset) begin
            config_high_reg    <= 32'd0;
            config_high_loaded <= 1'b0;
        end else if (dma_cfg_we && !dma_cfg_addr[2]) begin
            config_high_reg    <= dma_cfg_wdata;
            config_high_loaded <= 1'b1;
        end else if (config_commit_en) begin
            config_high_loaded <= 1'b0;
        end
    end

    assign config_commit_en = dma_cfg_we && dma_cfg_addr[2] && config_high_loaded;
    assign config_full_word = {config_high_reg, dma_cfg_wdata};

    logic csr_pready;
    logic csr_pslverr;
    
    // Config path: DMA → cgra_config_broadcaster → PE-internal BRAM.
    // PEs read their config from internal BSG SRAM during execution; the
    // broadcaster replays slot-0 writes to slots 1-15 so single-kernel
    // programs only need to write one slot.
    logic [3:0]  cfg_wr_addr_mux;
    logic [63:0] cfg_wr_data_mux;
    logic [3:0]  cfg_wr_pe_sel_mux;
    logic        cfg_wr_en_mux;

    cgra_config_broadcaster u_bcast (
        .clk        (clk),
        .rst_n      (rst_n),
        .in_addr    (dma_cfg_addr[6:3]),
        .in_data    (config_full_word),
        .in_pe_sel  (dma_cfg_pe_sel),
        .in_we      (config_commit_en),
        .out_addr   (cfg_wr_addr_mux),
        .out_data   (cfg_wr_data_mux),
        .out_pe_sel (cfg_wr_pe_sel_mux),
        .out_we     (cfg_wr_en_mux)
    );

    // =========================================================================
    // Internal Wires: Control Unit → Flow Control
    // =========================================================================
    logic [3:0]  context_pc;       // 4-bit PC counter (0-15) from Control Unit
    logic [3:0]  next_context_pc;  // Next PC (for tile prefetch, accounts for HW loops)
    logic        global_stall;      // Stall signal (combinatorial from CU)
    logic        global_stall_r;   // Registered: reduces 5610-fanout to 1 net + FF tree

    // =========================================================================
    // Internal Wires: Hybrid I/O - Result Collection from Array
    // =========================================================================
    // Capture computation result from last PE (PE 3,3 = tile 15)
    // Using East edge output as it's typically the final output direction
    logic [31:0] global_result;

    // Config Write Logic: Populate config_frames when DMA commits
    // Slot-0 broadcast: writing to slot 0 fills ALL 16 context slots of the PE.
    //   This preserves backward compatibility — single-config tests write slot 0
    //   and expect the same instruction to execute on every context_pc cycle.
    // Addressed write: writing to slot 1-15 updates only that specific slot.
    //   Multi-context drivers (e.g. FC layer) write slot 0 first (broadcast),
    //   then overwrite slots 1-15 with per-context configs.
    // Config writes now go directly to PE-internal BRAM via cfg_wr_* bus.
    // The old config_frames[16][16] register array has been removed (A2).
    // Broadcast (slot-0) is handled by the broadcast FSM above.

    // Config address within 2048-byte block: [2]=HI/LO, [6:3]=slot, [10:7]=PE
    assign dma_cfg_pe_sel = dma_cfg_addr[10:7];

    // =========================================================================
    // 1. APB CSR Module
    // =========================================================================
    cgra_apb_csr #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .DATA_WIDTH(32)
    ) u_csr (
        .clk(clk),
        .rst_n(rst_n),
        
        // APB Interface - use internal wires for muxing
        .psel(psel),
        .penable(penable),
        .pwrite(pwrite),
        .paddr(paddr),
        .pwdata(pwdata),
        .prdata(csr_prdata),   // Internal wire for multiplexing
        .pready(csr_pready),   // Internal wire for multiplexing
        .pslverr(csr_pslverr),
        
        // DMA Config Wires
        .dma_src(dma_src),
        .dma_dst(dma_dst),
        .dma_size(dma_size),
        .dma_src_stride(dma_src_stride),
        .dma_rows(dma_rows),
        .dma_cols(dma_cols),
        .dma_start(dma_start),
        .dma_busy_i(dma_busy),
        .dma_done_i(dma_done),
        .dma_error_code_i(dma_error_code),
        .dma_error_valid_i(dma_error_valid),

        // Control Unit Config Wires
        .cu_start(cu_start),
        .cu_soft_reset(cu_soft_reset),
        .cu_max_cycles(cu_max_cycles),  // Programmable timeout
        .cu_busy_i(cu_busy),
        .cu_done_i(cu_done),
        .cu_cycles_i(cu_cycles),
        
        // IRQ
        .irq(irq),
        
        // Hardware Loop (NEW - LPR: programmable via CSR 0x48-0x50)
        .loop_start_pc(cu_loop_start_pc),
        .loop_end_pc(cu_loop_end_pc),
        .loop_count(cu_loop_count),
        .loop2_start_pc(cu_loop2_start_pc),
        .loop2_end_pc(cu_loop2_end_pc),
        .loop2_count(cu_loop2_count),
        .tile_bank_sel(tile_bank_sel_csr),
        .tile_auto_inc_en(tile_auto_inc_en),
        .result_skip_count(result_skip_count),
        .dma_desc_head(dma_desc_head),
        .dma_chain_start(dma_chain_start),
        .dma_chain_active_i(dma_chain_active),
        .dma_desc_completed_i(dma_desc_completed)
    );
    
    // =========================================================================
    // 2. DMA Subsystem (engine + SG chain controller + muxes)
    // =========================================================================
    cgra_dma_subsystem #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(ADDR_WIDTH),
        .AXI_ID_WIDTH(AXI_ID_WIDTH),
        .FIFO_DEPTH(32)
    ) u_dma (
        .clk(clk),
        .rst_n(rst_n),

        .cfg_src(dma_src),
        .cfg_dst(dma_dst),
        .cfg_size(dma_size),
        .cfg_src_stride(dma_src_stride),
        .cfg_rows(dma_rows),
        .cfg_cols(dma_cols),
        .cfg_start(dma_start),
        .cfg_abort(cu_soft_reset),
        .cfg_desc_head(dma_desc_head),
        .cfg_chain_start(dma_chain_start),

        .status_busy(dma_busy),
        .status_done(dma_done),
        .chain_active(dma_chain_active),
        .desc_completed(dma_desc_completed),
        .error_code(dma_error_code),
        .error_valid(dma_error_valid),

        .m_axi_awid(m_axi_awid),
        .m_axi_awaddr(m_axi_awaddr),
        .m_axi_awlen(m_axi_awlen),
        .m_axi_awsize(m_axi_awsize),
        .m_axi_awburst(m_axi_awburst),
        .m_axi_awvalid(m_axi_awvalid),
        .m_axi_awready(m_axi_awready),
        .m_axi_wdata(m_axi_wdata),
        .m_axi_wstrb(m_axi_wstrb),
        .m_axi_wlast(m_axi_wlast),
        .m_axi_wvalid(m_axi_wvalid),
        .m_axi_wready(m_axi_wready),
        .m_axi_bid(m_axi_bid),
        .m_axi_bresp(m_axi_bresp),
        .m_axi_bvalid(m_axi_bvalid),
        .m_axi_bready(m_axi_bready),
        .m_axi_arid(m_axi_arid),
        .m_axi_araddr(m_axi_araddr),
        .m_axi_arlen(m_axi_arlen),
        .m_axi_arsize(m_axi_arsize),
        .m_axi_arburst(m_axi_arburst),
        .m_axi_arvalid(m_axi_arvalid),
        .m_axi_arready(m_axi_arready),
        .m_axi_rdata(m_axi_rdata),
        .m_axi_rlast(m_axi_rlast),
        .m_axi_rvalid(m_axi_rvalid),
        .m_axi_rid(m_axi_rid),
        .m_axi_rresp(m_axi_rresp),
        .m_axi_rready(m_axi_rready),

        .tile_addr_o(dma_tile_addr),
        .tile_bank_sel_o(dma_tile_bank_sel),
        .tile_we_o(dma_tile_we),
        .tile_wdata_o(dma_tile_wdata),
        .tile_re_o(dma_tile_re),
        .tile_rdata_i(dma_tile_rdata),
        .tile_rvalid_i(dma_tile_valid),

        .config_addr_o(dma_cfg_addr),
        .config_we_o(dma_cfg_we),
        .config_wdata_o(dma_cfg_wdata),

        .dbg_status_busy(dbg_dma_busy),
        .dbg_read_fsm_state(dbg_dma_read_state),
        .dbg_write_fsm_state(dbg_dma_write_state),
        .dbg_fifo_full(dbg_dma_fifo_full),
        .dbg_fifo_empty(dbg_dma_fifo_empty),
        .dbg_write_words_remaining(dbg_dma_write_words_remaining)
    );

    // =========================================================================
    // 3. Control Unit
    // =========================================================================
    cgra_control_unit #(
        .CONTEXT_DEPTH(16),
        .PC_WIDTH(4)
    ) u_cu (
        .clk(clk),
        .rst_n(rst_n),
        
        // CSR Interface
        .start_i(cu_start),
        .soft_reset_i(cu_soft_reset),
        .busy_o(cu_busy),
        .done_o(cu_done),
        .cycle_count_o(cu_cycles),
        
        // Array Interface
        .pe_enable(pe_enable),
        .pe_reset_n(pe_reset_n),
        .array_done_i(array_done),
        
        // Multi-Context Flow Control
        .context_pc_o(context_pc),
        .next_context_pc_o(next_context_pc),
        .global_stall_o(global_stall),
        .dma_busy_i(dma_busy || result_fifo_full),  // FIFO full also stalls CU
        
        // Configuration
        .max_cycles_i(cu_max_cycles),  // Programmable timeout from CSR @ 0x2C
        
        // Hardware Loop Configuration
        .loop_start_pc_i(cu_loop_start_pc),
        .loop_end_pc_i(cu_loop_end_pc),
        .loop_count_i(cu_loop_count),
        .loop2_start_pc_i(cu_loop2_start_pc),
        .loop2_end_pc_i(cu_loop2_end_pc),
        .loop2_count_i(cu_loop2_count),
        .branch_target_i(array_branch_target),
        .branch_taken_i(array_branch_taken_r),  // Registered: 1-cycle delay slot
        .loops_done_o(cu_loops_done),
        .tile_auto_inc_en_i(tile_auto_inc_en),
        .tile_base_offset_o(),                      // registered (unused at top level)
        .next_tile_base_offset_o(cu_next_tile_offset) // combinational for prefetch
    );
    
    // Tile memory: 4 banks × 4096 words, DMA writes ext_*, array reads bank*_rdata.
    // Pre-fetch with next_context_pc so the sync-read registered data arrives
    // aligned with the PE executing at that PC (also handles loop back-jumps).
    cgra_tile_memory #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(12),
        .BANK_DEPTH(4096),   // C1: 4× larger tile memory (64KB total)
        .NUM_BANKS(4)
    ) u_tile_mem (
        .clk(clk),
        .rst_n(rst_n),
        // When tile auto-increment is active, offset[7] drives bank_sel_i
        // Auto-inc mode steers offset[7] to bank_sel_i (upper/lower half),
        // with offset[6:0] forming the high bits of the per-bank address.
        .bank_sel_i(tile_auto_inc_en ? cu_next_tile_offset[7] : tile_bank_sel_csr),

        // Bank addresses: auto-inc concatenates {offset[6:0], pc[3:0]};
        // legacy mode uses only the low 4 bits (16-word stream).
        .bank0_addr(tile_auto_inc_en ? {1'b0, cu_next_tile_offset[6:0], next_context_pc}
                                     : {8'd0, next_context_pc}),
        .bank0_read(!dma_tile_re),       // Suppress during DMA tile read (PEs stalled anyway)
        .bank0_write(1'b0),              // Array doesn't write
        .bank0_wdata(32'd0),
        .bank0_rdata(row_data[0]),
        .bank0_valid(row_valid[0]),

        // Bank 1 (Row 1) - Read port to array
        .bank1_addr(tile_auto_inc_en ? {1'b0, cu_next_tile_offset[6:0], next_context_pc}
                                     : {8'd0, next_context_pc}),
        .bank1_read(!dma_tile_re),       // Suppress during DMA tile read
        .bank1_write(1'b0),
        .bank1_wdata(32'd0),
        .bank1_rdata(row_data[1]),
        .bank1_valid(row_valid[1]),

        // Bank 2 (Row 2) - Read port to array
        .bank2_addr(tile_auto_inc_en ? {1'b0, cu_next_tile_offset[6:0], next_context_pc}
                                     : {8'd0, next_context_pc}),
        .bank2_read(!dma_tile_re),       // Suppress during DMA tile read
        .bank2_write(1'b0),
        .bank2_wdata(32'd0),
        .bank2_rdata(row_data[2]),
        .bank2_valid(row_valid[2]),

        // Bank 3 (Row 3) - Read port to array
        .bank3_addr(tile_auto_inc_en ? {1'b0, cu_next_tile_offset[6:0], next_context_pc}
                                     : {8'd0, next_context_pc}),
        .bank3_read(!dma_tile_re),       // Suppress during DMA tile read
        .bank3_write(1'b0),
        .bank3_wdata(32'd0),
        .bank3_rdata(row_data[3]),
        .bank3_valid(row_valid[3]),
        
        // External/DMA port - Write access
        .ext_addr({2'b00, dma_tile_addr[11:2]}),  // Convert byte addr to 12-bit word index
        .ext_bank_sel(dma_tile_bank_sel),
        .ext_read(dma_tile_re),      // DMA tile read-back path (was 1'b0)
        .ext_write(dma_tile_we),
        .ext_wdata(dma_tile_wdata),
        .ext_rdata(dma_tile_rdata),
        .ext_valid(dma_tile_valid)
    );

    // synopsys translate_off
    always @(posedge clk) begin
        if (rst_n && dma_tile_we && (dma_tile_addr[1:0] != 2'b00))
            $error("[CGRA_TOP] DMA tile WRITE address 0x%08h is not word-aligned", dma_tile_addr);
        if (rst_n && dma_tile_re && (dma_tile_addr[1:0] != 2'b00))
            $error("[CGRA_TOP] DMA tile READ address 0x%08h is not word-aligned", dma_tile_addr);
    end
    // synopsys translate_on

    // Auto-stop: asserts array_done once the PE program has walked past the
    // final slot with all nested loop counters exhausted.
    //
    // With loops active, the CU's PC jumps back on loop boundaries, so
    // context_pc only reaches slot 15 after all loops finish. This is
    // detected via cu_loops_done from the CU's internal loop counters.
    //
    // Without loops (loop_count=0): cu_loops_done=1 from start, so
    // array_done fires after the first sweep (0-15), same as before.
    //
    // Timing: array_done fires on the same cycle context_pc==15 is
    // executed. The _r pipeline latency is absorbed by the BRAM
    // prefetch latency (both are 1-cycle).

    // Register array_branch_taken to break the combinatorial feedback loop:
    //   branch_taken_o → array_branch_taken → array_done → global_stall_o
    //   → stall → branch_taken_o  (LUTLP-1 violation in Vivado)
    // 1-cycle branch delay slot: PC redirects at N+1 instead of N.
    // Microcode must account for this (instruction after branch still executes).
    always_ff @(posedge clk) begin
        if (!rst_n || cu_soft_reset)
            array_branch_taken_r <= 1'b0;
        else
            array_branch_taken_r <= array_branch_taken;
    end

    // Pipeline register for global_stall: breaks the 5610-fanout from CU
    // output directly into PE register enables. One extra cycle of stall
    // latency is acceptable because stall assertion is already conservative
    // (triggered by DMA start, which happens between inference frames).
    always_ff @(posedge clk) begin
        if (!rst_n)
            global_stall_r <= 1'b1;  // Hold stall during reset
        else
            global_stall_r <= global_stall;
    end

    logic auto_stop_armed;

    always_ff @(posedge clk) begin
        if (!rst_n) begin
            auto_stop_armed <= 1'b0;
        end else if (cu_soft_reset) begin
            auto_stop_armed <= 1'b0;
        end else if (cu_start && !cu_busy && !cu_soft_reset) begin
            auto_stop_armed <= 1'b1;
        end else if (array_done) begin
            // Disarm after firing to prevent re-triggering if PE lingers
            auto_stop_armed <= 1'b0;
        end
    end

    // array_done: program has completed when the PC reaches the last context
    // slot AND all loop iterations are exhausted AND no dynamic branch is
    // redirecting execution elsewhere. Without the branch guard, a branch
    // at context_pc=15 would be killed by premature array_done assertion.
    //
    assign array_done = auto_stop_armed
                     && cu_loops_done
                     && (context_pc == 4'(CONTEXT_DEPTH - 1))
                     && !array_branch_taken_r;
    
    // =========================================================================
    // Edge Output Wires for Synthesis Keeper
    // =========================================================================
    // Edge output arrays (parameterized)
    localparam ROWS = 4;
    localparam COLS = 4;

    logic [DATA_WIDTH-1:0] edge_out_n [0:COLS-1];
    logic [DATA_WIDTH-1:0] edge_out_s [0:COLS-1];
    logic [DATA_WIDTH-1:0] edge_out_e [0:ROWS-1];
    logic [DATA_WIDTH-1:0] edge_out_w [0:ROWS-1];
    // Tie-off array for unused edge data inputs
    logic [DATA_WIDTH-1:0] edge_zero_data [0:3];
    assign edge_zero_data  = '{default: '0};

    cgra_array #(
        .ROWS(ROWS),
        .COLS(COLS),
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .ADDR_WIDTH(4),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .CONTEXT_DEPTH(16),
        .PC_WIDTH(4)
    ) u_array (
        .clk(clk),
        .rst_n(rst_n & pe_reset_n),

        // PEs use BRAM for programming; config_frame port tied to zeros
        .config_frame('{default: 64'd0}),
        .config_valid(1'b0),

        // Multi-context + config write
        .context_pc(next_context_pc),
        .global_stall(global_stall_r),    // Registered: avoids 5610-fanout on raw CU output
        .cfg_wr_addr(cfg_wr_addr_mux),
        .cfg_wr_data(cfg_wr_data_mux),
        .cfg_wr_pe_sel(cfg_wr_pe_sel_mux),
        .cfg_wr_en(cfg_wr_en_mux),

        // North/South/East edge inputs — tied off
        .edge_data_in_n(edge_zero_data[0:COLS-1]),
        .edge_data_in_s(edge_zero_data[0:COLS-1]),
        .edge_data_in_e(edge_zero_data[0:ROWS-1]),

        // West edge inputs — from Tile Memory
        .edge_data_in_w(row_data),

        // Edge data outputs (valid outputs not consumed at top level)
        .edge_data_out_n(edge_out_n),
        .edge_valid_out_n(),
        .edge_data_out_s(edge_out_s),
        .edge_valid_out_s(),
        .edge_data_out_e(edge_out_e),
        .edge_valid_out_e(),
        .edge_data_out_w(edge_out_w),
        .edge_valid_out_w(),

        // B4: Branch from PE[0][0]
        .branch_target_o(array_branch_target),
        .branch_taken_o(array_branch_taken)
    );

    // Synthesis keeper: prevents synth from optimizing the mesh away when the
    // edge outputs aren't pad-connected. OR-reduce across all 16 edge words.
    assign synthesis_keep = (|edge_out_n[0]) | (|edge_out_n[1]) | (|edge_out_n[2]) | (|edge_out_n[3]) |
                            (|edge_out_s[0]) | (|edge_out_s[1]) | (|edge_out_s[2]) | (|edge_out_s[3]) |
                            (|edge_out_e[0]) | (|edge_out_e[1]) | (|edge_out_e[2]) | (|edge_out_e[3]) |
                            (|edge_out_w[0]) | (|edge_out_w[1]) | (|edge_out_w[2]) | (|edge_out_w[3]);
    
    // Capture PE[3][3] east-edge output on cu_done so APB returns stable value.
    logic [DATA_WIDTH-1:0] global_result_reg;
    always_ff @(posedge clk) begin
        if (!rst_n)
            global_result_reg <= '0;
        else if (cu_done && !cu_soft_reset)
            global_result_reg <= edge_out_e[3];
    end
    assign global_result = global_result_reg;
    
    // =========================================================================
    // Result FIFO: Captures ALL east-edge outputs every valid cycle
    // =========================================================================
    // Replaces the old cu_done-only latch. Pushes 4 × 32-bit per cycle
    // during CU execution. ARM pops via APB reads at 0x58-0x64.

    // Push valid: PE output is valid when CU is running and not stalled
    logic result_push_valid;
    assign result_push_valid = pe_enable && !global_stall && !cu_soft_reset
                               && cu_busy;  // cu_busy is high during STATE_RUN

    // FIFO clear: on CU start or soft-reset
    assign result_fifo_clear = cu_start || cu_soft_reset;

    logic [DATA_WIDTH-1:0] result_push_data [0:3];
    assign result_push_data = edge_out_e;

    cgra_result_fifo #(
        .DATA_WIDTH(DATA_WIDTH),
        .DEPTH(256),
        .ROWS(4)
    ) u_result_fifo (
        .clk(clk),
        .rst_n(rst_n),
        .push_data(result_push_data),
        .push_valid(result_push_valid),
        .fifo_full(result_fifo_full),
        .pop_data(result_fifo_pop_data),
        .pop_valid(result_fifo_pop_valid),
        .pop_read(result_fifo_pop_read),
        .fifo_clear(result_fifo_clear),
        .skip_count(result_skip_count),
        .count(result_fifo_count),
        .empty(),
        .overflow_pulse(result_fifo_overflow),
        .underflow_pulse(result_fifo_underflow)
    );
    
    // APB read path mux: 0x40/0x44/0x58-0x64 go to Result FIFO / status;
    // every other address falls through to the CSR module.
    logic [31:0] apb_prdata;
    logic        apb_pready;
    
    // FIFO pop trigger: WRITING to RESULT_STATUS (0x44) pops one FIFO entry.
    // This decouples pop from read — software reads ROW0-3 (non-destructive),
    // then writes to 0x44 to advance. This ensures all 4 rows see the same
    // pre-fetched data before the pop advances to the next entry.
    // (Note: writing to 0x44 also handles W1C for overflow/underflow bits.)
    logic result_fifo_pop_trigger;
    assign result_fifo_pop_trigger = psel && penable && pwrite && (paddr[7:0] == 8'h44);
    assign result_fifo_pop_read = result_fifo_pop_trigger;

    always_comb begin
        // Data multiplexer: result FIFO + status vs CSR module
        case (paddr[7:0])
            8'h40: apb_prdata = global_result;
            8'h44: apb_prdata = {21'b0, result_fifo_underflow, result_fifo_overflow,
                                 result_fifo_count[7:0], result_fifo_pop_valid};
            8'h54: apb_prdata = {28'b0, result_skip_count};
            8'h58: apb_prdata = result_fifo_pop_data[0];
            8'h5C: apb_prdata = result_fifo_pop_data[1];
            8'h60: apb_prdata = result_fifo_pop_data[2];
            8'h64: apb_prdata = result_fifo_pop_data[3];
            default: apb_prdata = csr_prdata;
        endcase
        
        // Ready signal multiplexer: result registers always ready, CSR module for others
        case (paddr[7:0])
            8'h40, 8'h44, 8'h58, 8'h5C, 8'h60, 8'h64: apb_pready = 1'b1;
            default: apb_pready = csr_pready;                // CSR addresses: use CSR ready
        endcase
    end
    
    // Output assignments (replace CSR direct connections)
    assign prdata = apb_prdata;
    assign pready = apb_pready;
    assign pslverr = csr_pslverr;  // Slave error only from CSR (result regs don't error)

endmodule
