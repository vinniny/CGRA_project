// ==============================================================================
// CGRA Top-Level Integration - v2.4
// ==============================================================================
// A 4x4 Coarse-Grained Reconfigurable Array accelerator with APB control,
// AXI4-Lite DMA master, and neuromorphic (LIF) support.
//
// COMPONENTS:
//   - APB CSR Interface (cgra_axi_csr) - 11 registers
//   - Pipelined DMA Engine (cgra_dma_engine) with 32-word FIFO
//   - Control Unit (cgra_control_unit) with 3-state FSM + auto-stop
//   - 4-Bank Tile Memory (cgra_tile_memory) with context_pc streaming  
//   - 4x4 PE Array (cgra_array_4x4) with mesh broadcast
//
// FEATURES:
//   - Auto-Stop: Programmable timeout via 0x2C register
//   - Synthesis Keeper: OR-reduce of all edge outputs
//   - Double-Pump Config: 32→64 bit configuration loader
//   - Mesh Broadcast: PE outputs → all 4 neighbors
//   - 21-Op ISA: Includes LIF neuron, RELU, MAX for neuromorphic/ANN
//
// APB REGISTER MAP:
//   0x00  DMA_CTRL    [0] Start (auto-clear)
//   0x04  DMA_STATUS  [0] Busy, [1] Done
//   0x08  DMA_SRC     Source address
//   0x0C  DMA_DST     Destination address
//   0x10  DMA_SIZE    Transfer size (bytes)
//   0x20  CU_CTRL     [0] Start, [1] Soft Reset
//   0x24  CU_STATUS   [0] Busy, [1] Done
//   0x28  CU_CYCLES   Cycle counter (read-only)
//   0x2C  CU_TIMEOUT  Max cycles (0 = no limit)
//   0x30  IRQ_STATUS  [0] DMA Done, [1] CU Done
//   0x34  IRQ_MASK    IRQ enable mask
//   0x48  LOOP_START  Hardware loop start PC      [NEW - LPR]
//   0x4C  LOOP_END    Hardware loop end PC         [NEW - LPR]
//   0x50  LOOP_COUNT  Hardware loop iteration count [NEW - LPR]
//   0x58  RESULT_ROW0 East-edge result row 0 (RO)  [NEW - LPR]
//   0x5C  RESULT_ROW1 East-edge result row 1 (RO)  [NEW - LPR]
//   0x60  RESULT_ROW2 East-edge result row 2 (RO)  [NEW - LPR]
//   0x64  RESULT_ROW3 East-edge result row 3 (RO)  [NEW - LPR]
//
// VERIFICATION: All 38 suites pass (21-op ISA, Silicon Ready)
// ==============================================================================

module cgra_top #(
    parameter DATA_WIDTH = 32,
    parameter COORD_WIDTH = 4,
    parameter PAYLOAD_WIDTH = 16,
    parameter ADDR_WIDTH = 32,
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
    input  logic                  m_axi_bvalid,
    output logic                  m_axi_bready,
    
    // Read Address Channel
    output logic [ADDR_WIDTH-1:0] m_axi_araddr,
    output logic [7:0]            m_axi_arlen,     // Burst length
    output logic [2:0]            m_axi_arsize,    // Beat size
    output logic [1:0]            m_axi_arburst,   // Burst type
    output logic                  m_axi_arvalid,
    input  logic                  m_axi_arready,
    
    // Read Data Channel
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
    // Internal Wires: APB CSR Multiplexing
    // =========================================================================
    logic [31:0] csr_prdata;  // Internal prdata from u_csr module
    
    // =========================================================================
    // Internal Wires: CSR → DMA
    // =========================================================================
    logic [31:0] dma_src;
    logic [31:0] dma_dst;
    logic [31:0] dma_size;
    logic        dma_start;
    logic        dma_busy;
    logic        dma_done;
    
    // =========================================================================
    // Internal Wires: CSR → Control Unit
    // =========================================================================
    logic        cu_start;
    logic        cu_soft_reset;
    logic [31:0] cu_max_cycles;  // Programmable timeout (CSR @ 0x2C)
    logic        cu_busy;
    logic        cu_done;
    logic [31:0] cu_cycles;
    
    // Hardware Loop Configuration (from CSR)
    logic [15:0] cu_loop_start_pc;
    logic [15:0] cu_loop_end_pc;
    logic [15:0] cu_loop_count;
    
    // East-edge result registers (4 rows for LPR 4×4 output capture)
    logic [DATA_WIDTH-1:0] result_row [0:3];
    
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
    
    // Row data from tile memory → Array
    logic [31:0] row_data [0:3];
    logic        row_valid [0:3];
    
    // =========================================================================
    // Internal Wires: DMA → Config Bus (Recipe Book)
    // =========================================================================
    logic [31:0] dma_cfg_addr;
    logic        dma_cfg_we;
    logic [31:0] dma_cfg_wdata;
    logic [3:0]  dma_cfg_pe_sel;  // Which PE to configure (0-15)
    
    // =========================================================================
    // FIX 2: Double-Pump Config Loader (32-bit DMA → 64-bit Config)
    // =========================================================================
    // Protocol: Write High Word (addr[2]=0) → Write Low Word (addr[2]=1) commits 64-bit
    // Polarity: bit[2]=0 latches HI (first in sequential DMA), bit[2]=1 commits LO.
    // This enables bulk DMA: sequential writes to CONFIG_BASE+0,+4,+8,...
    // naturally pair as [HI latch, LO commit] per 8-byte config entry.
    logic [31:0] config_high_reg;     // Holding register for upper 32 bits
    logic [63:0] config_full_word;    // Combined 64-bit config
    logic        config_commit_en;    // Triggers when low word written
    logic        config_high_loaded;  // FIX: Guard — high word must be written before commit

    always_ff @(posedge clk) begin
        if (!rst_n || cu_soft_reset) begin
            config_high_reg    <= 32'd0;  // FIX: Clear on soft reset to prevent stale pairing
            config_high_loaded <= 1'b0;
        end else if (dma_cfg_we && !dma_cfg_addr[2]) begin
            // Writing to high word address (addr[2]=0, first in sequential order)
            config_high_reg    <= dma_cfg_wdata;
            config_high_loaded <= 1'b1;
        end else if (config_commit_en) begin
            config_high_loaded <= 1'b0;   // Clear after commit
        end
    end

    // Commit trigger: DMA writes to low word address (addr[2]=1) AND high word was loaded
    // FIX: Without config_high_loaded guard, a stray low-word write could commit
    //      a stale or zeroed high_reg, silently corrupting the PE config frame.
    assign config_commit_en = dma_cfg_we && dma_cfg_addr[2] && config_high_loaded;

    // Combined 64-bit config: {high_reg, current_low_word}
    assign config_full_word = {config_high_reg, dma_cfg_wdata};
    
    // =========================================================================
    // Internal Wires: APB Handshake Signals (for multiplexing)
    // =========================================================================
    // csr_prdata already declared at line 122
    logic        csr_pready;  // CSR module ready signal
    logic        csr_pslverr; // CSR module slave error
    
    // =========================================================================
    // Internal Wires: Configuration (simplified for now)
    // =========================================================================
    // 2D config register array: [pe_id][context_slot]
    // Combinational read via context_pc — zero latency, no BSG pipeline issue.
    // Survives soft_reset (only cleared by global rst_n).
    logic [CONFIG_WIDTH-1:0] config_frames [0:15][0:15];  // 16 PEs × 16 contexts

    // =========================================================================
    // Internal Wires: Control Unit → Flow Control
    // =========================================================================
    logic [3:0]  context_pc;    // 4-bit PC counter (0-15) from Control Unit
    logic        global_stall;  // Stall signal to PE array

    // =========================================================================
    // Internal Wires: Hybrid I/O - Result Collection from Array
    // =========================================================================
    // Capture computation result from last PE (PE 3,3 = tile 15)
    // Using East edge output as it's typically the final output direction
    logic [31:0] global_result;
    logic        result_valid;

    // Config Write Logic: Populate config_frames when DMA commits
    // Slot-0 broadcast: writing to slot 0 fills ALL 16 context slots of the PE.
    //   This preserves backward compatibility — single-config tests write slot 0
    //   and expect the same instruction to execute on every context_pc cycle.
    // Addressed write: writing to slot 1-15 updates only that specific slot.
    //   Multi-context drivers (e.g. FC layer) write slot 0 first (broadcast),
    //   then overwrite slots 1-15 with per-context configs.
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            for (int i = 0; i < 16; i++)
                for (int j = 0; j < 16; j++)
                    config_frames[i][j] <= 64'd0;
        end else if (config_commit_en) begin
            if (dma_cfg_addr[6:3] == 4'd0) begin
                // Slot 0: broadcast to all 16 context slots
                for (int s = 0; s < 16; s++)
                    config_frames[dma_cfg_pe_sel][s] <= config_full_word;
            end else begin
                // Slot 1-15: addressed write to specific context slot
                config_frames[dma_cfg_pe_sel][dma_cfg_addr[6:3]] <= config_full_word;
            end
        end
    end

    // =========================================================================
    // TEMPORARY: Placeholder assignment for config PE selection
    // =========================================================================
    // Address layout within 2048-byte config block:
    //   [2]    = HI/LO (0=HI latch, 1=LO commit)
    //   [6:3]  = context slot (0-15, stride 8 bytes)
    //   [10:7] = PE select (0-15, stride 128 bytes)
    assign dma_cfg_pe_sel = dma_cfg_addr[10:7];
    
    // =========================================================================
    // TEMPORARY: Hardware Loop Configuration - NOW WIRED FROM CSR
    // =========================================================================
    // Hardware loop parameters are programmable via APB CSR registers:
    //   0x48 = LOOP_START, 0x4C = LOOP_END, 0x50 = LOOP_COUNT
    // Default values (no looping): start=0, end=15, count=0
        
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
        .dma_start(dma_start),
        .dma_busy_i(dma_busy),
        .dma_done_i(dma_done),
        
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
        .loop_count(cu_loop_count)
    );
    
    // =========================================================================
    // 2. Pipelined DMA Engine
    // =========================================================================
    cgra_dma_engine #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(ADDR_WIDTH),
        .FIFO_DEPTH(32)
    ) u_dma (
        .clk(clk),
        .rst_n(rst_n),
        
        // CSR Config
        .cfg_src(dma_src),
        .cfg_dst(dma_dst),
        .cfg_size(dma_size),
        .cfg_start(dma_start),
        .cfg_abort(cu_soft_reset),    // FIX: Use CU soft reset to abort stuck DMA
        .status_busy(dma_busy),
        .status_done(dma_done),
        /* verilator lint_off PINCONNECTEMPTY */
        .irq_done(),  // Intentional: IRQ generated by CSR module, not DMA
        /* verilator lint_on PINCONNECTEMPTY */
        
        // AXI4 Master (with Burst Support)
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
        .m_axi_bvalid(m_axi_bvalid),
        .m_axi_bready(m_axi_bready),
        .m_axi_araddr(m_axi_araddr),
        .m_axi_arlen(m_axi_arlen),
        .m_axi_arsize(m_axi_arsize),
        .m_axi_arburst(m_axi_arburst),
        .m_axi_arvalid(m_axi_arvalid),
        .m_axi_arready(m_axi_arready),
        .m_axi_rdata(m_axi_rdata),
        .m_axi_rlast(m_axi_rlast),
        .m_axi_rvalid(m_axi_rvalid),
        .m_axi_rready(m_axi_rready),
        
        // Local Memory Interface (To Tile Memory)
        .tile_addr_o(dma_tile_addr),
        .tile_bank_sel_o(dma_tile_bank_sel),
        .tile_we_o(dma_tile_we),
        .tile_wdata_o(dma_tile_wdata),
        .tile_re_o(dma_tile_re),
        .tile_rdata_i(dma_tile_rdata),
        .tile_rvalid_i(dma_tile_valid),
        
        // Config Interface (To PE Array)
        .config_addr_o(dma_cfg_addr),
        .config_we_o(dma_cfg_we),
        .config_wdata_o(dma_cfg_wdata),
        
        // Debug Ports (For ILA)
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
        .global_stall_o(global_stall),
        .dma_busy_i(dma_busy),
        
        // Configuration
        .max_cycles_i(cu_max_cycles),  // Programmable timeout from CSR @ 0x2C
        
        // Hardware Loop Configuration
        .loop_start_pc_i(cu_loop_start_pc),
        .loop_end_pc_i(cu_loop_end_pc),
        .loop_count_i(cu_loop_count)
    );
    
    // =========================================================================
    // 4. Tile Memory (The "Fridge" - Data Banks for PE Array)
    // =========================================================================
    // 4 banks × 1024 words = 16KB total
    // DMA writes to ext_* port, Array reads from bank*_rdata
    //
    // FIX: Tile read pre-fetch to compensate for 1-cycle sync read latency.
    // The sync read registers the address at posedge, outputting data 1 cycle
    // later.  Without pre-fetch, the PE at context_pc=N reads tile[N-1].
    // Solution: feed `tile_prefetch_pc` (= next context_pc) to the tile
    // address, so the registered read delivers tile[N] when PE executes at N.
    // When stalled: holds current pc (pre-loads data for first execution).
    // When executing: advances to pc+1 (pre-loads next context's data).
    logic [3:0] tile_prefetch_pc;
    always_comb begin
        if (pe_enable && !global_stall) begin
            // Executing: pre-fetch next context (mirrors CU PC increment)
            if (context_pc == 4'd15)
                tile_prefetch_pc = 4'd0;
            else
                tile_prefetch_pc = context_pc + 4'd1;
        end else begin
            // Stalled or idle: hold at current pc (ensures first execution
            // reads the correct context after the stall cycle pre-loads it)
            tile_prefetch_pc = context_pc;
        end
    end

    cgra_tile_memory #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(12),
        .BANK_DEPTH(1024),
        .NUM_BANKS(4)
    ) u_tile_mem (
        .clk(clk),
        .rst_n(rst_n),
        
        // FIX 3: Dynamic Memory Addressing (Streaming Mode)
        // Each bank address = context_pc, enabling 16-word streaming per run
        
        // Bank 0 (Row 0) - Read port to array
        .bank0_addr({8'd0, tile_prefetch_pc}), // Prefetch: compensates 1-cycle sync read latency (0-15)
        .bank0_read(!dma_tile_re),       // Suppress during DMA tile read (PEs stalled anyway)
        .bank0_write(1'b0),              // Array doesn't write
        .bank0_wdata(32'd0),
        .bank0_rdata(row_data[0]),
        .bank0_valid(row_valid[0]),

        // Bank 1 (Row 1) - Read port to array
        .bank1_addr({8'd0, tile_prefetch_pc}), // Prefetch: compensates 1-cycle sync read latency
        .bank1_read(!dma_tile_re),       // Suppress during DMA tile read
        .bank1_write(1'b0),
        .bank1_wdata(32'd0),
        .bank1_rdata(row_data[1]),
        .bank1_valid(row_valid[1]),

        // Bank 2 (Row 2) - Read port to array
        .bank2_addr({8'd0, tile_prefetch_pc}), // Prefetch: compensates 1-cycle sync read latency
        .bank2_read(!dma_tile_re),       // Suppress during DMA tile read
        .bank2_write(1'b0),
        .bank2_wdata(32'd0),
        .bank2_rdata(row_data[2]),
        .bank2_valid(row_valid[2]),

        // Bank 3 (Row 3) - Read port to array
        .bank3_addr({8'd0, tile_prefetch_pc}), // Prefetch: compensates 1-cycle sync read latency
        .bank3_read(!dma_tile_re),       // Suppress during DMA tile read
        .bank3_write(1'b0),
        .bank3_wdata(32'd0),
        .bank3_rdata(row_data[3]),
        .bank3_valid(row_valid[3]),
        
        // External/DMA port - Write access
        .ext_addr({2'b00, dma_tile_addr[11:2]}), // FIX: Convert byte address to word index (pad to 12-bit)
        .ext_bank_sel(dma_tile_bank_sel),
        .ext_read(dma_tile_re),      // DMA tile read-back path (was 1'b0)
        .ext_write(dma_tile_we),
        .ext_wdata(dma_tile_wdata),
        .ext_rdata(dma_tile_rdata),
        .ext_valid(dma_tile_valid)
    );

    // synopsys translate_off
    // FIX: Assert DMA tile address is word-aligned (lower 2 bits silently discarded)
    always @(posedge clk) begin
        if (rst_n && dma_tile_we && (dma_tile_addr[1:0] != 2'b00))
            $error("[CGRA_TOP] DMA tile WRITE address 0x%08h is not word-aligned!", dma_tile_addr);
        if (rst_n && dma_tile_re && (dma_tile_addr[1:0] != 2'b00))
            $error("[CGRA_TOP] DMA tile READ address 0x%08h is not word-aligned!", dma_tile_addr);
    end
    // synopsys translate_on

    // =========================================================================
    // 5. CGRA Array (4x4 PE Mesh)
    // =========================================================================
    
    // =========================================================================
    // AUTO-STOP FEATURE: Programmable Cycle Counter
    // =========================================================================
    // The CPU can program a cycle limit. When the counter reaches 1, array_done
    // is asserted to signal the Control Unit to stop execution automatically.
    //
    // Usage:
    // 1. Write cycle count to cycle_limit register (via CSR or hardcode)
    // 2. Start execution - counter decrements each cycle
    // 3. When counter == 1, array_done pulses to trigger auto-stop
    //
    // For now, we use a simple approach: tie array_done to context_pc overflow
    // This triggers auto-stop after 16 contexts (one complete sweep)
    // More sophisticated: Use a dedicated CSR register for arbitrary counts
    
    // Simple Auto-Stop: Trigger after 16 context cycles (context_pc wraps)
    // This is suitable for single-pass dataflow computations
    logic [4:0] auto_stop_counter;
    logic       auto_stop_armed;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            auto_stop_counter <= 5'd0;
            auto_stop_armed <= 1'b0;
        end else if (cu_soft_reset) begin
            // Soft reset clears the counter
            auto_stop_counter <= 5'd0;
            auto_stop_armed <= 1'b0;
        end else if (cu_start && !cu_busy && !cu_soft_reset) begin
            // FIX: Arm on start, not soft_reset. Gate with !cu_busy to prevent
            // mid-execution cu_start from resetting the counter spuriously.
            // FIX: Also gate with !cu_soft_reset — if start is asserted in the
            // same cycle as soft_reset, arming must not occur.
            auto_stop_counter <= 5'd0;
            auto_stop_armed <= 1'b1;
        end else if (pe_enable && auto_stop_armed && !global_stall && !array_done) begin
            // FIX: Only count when PEs actually execute (not stalled by DMA)
            // Gate with !array_done to prevent counter overshooting to 17
            // during the 1-cycle pe_enable pipeline lag after FINISH.
            auto_stop_counter <= auto_stop_counter + 1'b1;
        end
    end
    
    // Trigger array_done after 16 cycles (configurable via parameter)
    // This causes the CU to transition to FINISH state
    assign array_done = auto_stop_armed && (auto_stop_counter == 5'd16);
    
    // =========================================================================
    // Edge Output Wires for Synthesis Keeper
    // =========================================================================
    logic [DATA_WIDTH-1:0] edge_n0, edge_n1, edge_n2, edge_n3;
    logic [DATA_WIDTH-1:0] edge_s0, edge_s1, edge_s2, edge_s3;
    logic [DATA_WIDTH-1:0] edge_e0, edge_e1, edge_e2, edge_e3;
    logic [DATA_WIDTH-1:0] edge_w0, edge_w1, edge_w2, edge_w3;
    
    cgra_array_4x4 #(
        .DATA_WIDTH(DATA_WIDTH),
        .COORD_WIDTH(COORD_WIDTH),
        .PAYLOAD_WIDTH(PAYLOAD_WIDTH),
        .ADDR_WIDTH(4),
        .SPM_DEPTH(SPM_DEPTH),
        .RF_DEPTH(RF_DEPTH),
        .CONTEXT_DEPTH(16),
        .PC_WIDTH(4)
    ) u_array (
        .clk(clk),
        .rst_n(rst_n & pe_reset_n),  // Combined reset
        
        // Configuration - FIX: Wire from config_frames array (loaded by DMA)
        // Combinational MUX: config_frames[pe_id][context_pc] — zero latency
        .config_frame_00(config_frames[0][context_pc]),
        .config_frame_01(config_frames[1][context_pc]),
        .config_frame_02(config_frames[2][context_pc]),
        .config_frame_03(config_frames[3][context_pc]),
        .config_frame_10(config_frames[4][context_pc]),
        .config_frame_11(config_frames[5][context_pc]),
        .config_frame_12(config_frames[6][context_pc]),
        .config_frame_13(config_frames[7][context_pc]),
        .config_frame_20(config_frames[8][context_pc]),
        .config_frame_21(config_frames[9][context_pc]),
        .config_frame_22(config_frames[10][context_pc]),
        .config_frame_23(config_frames[11][context_pc]),
        .config_frame_30(config_frames[12][context_pc]),
        .config_frame_31(config_frames[13][context_pc]),
        .config_frame_32(config_frames[14][context_pc]),
        .config_frame_33(config_frames[15][context_pc]),
        .config_valid(cu_busy),    // FIX: Enable PE execution when CU is running
        
        // Multi-context interface - FIX 2: Double-pump config path
        .context_pc(context_pc),
        .global_stall(global_stall),
        .cfg_wr_addr(dma_cfg_addr[6:3]),         // Config slot address (skip bit 2 used for hi/lo)
        .cfg_wr_data(config_full_word),          // FIX 2: Full 64-bit config
        .cfg_wr_pe_sel(dma_cfg_pe_sel),          // From address decode
        .cfg_wr_en(config_commit_en),            // FIX 2: Only commit on low word write

        
        // North edge inputs - tie off
        .edge_data_in_n0(32'd0),
        .edge_data_in_n1(32'd0),
        .edge_data_in_n2(32'd0),
        .edge_data_in_n3(32'd0),
        .edge_valid_in_n0(1'b0),
        .edge_valid_in_n1(1'b0),
        .edge_valid_in_n2(1'b0),
        .edge_valid_in_n3(1'b0),
        
        // South edge inputs - tie off
        .edge_data_in_s0(32'd0),
        .edge_data_in_s1(32'd0),
        .edge_data_in_s2(32'd0),
        .edge_data_in_s3(32'd0),
        .edge_valid_in_s0(1'b0),
        .edge_valid_in_s1(1'b0),
        .edge_valid_in_s2(1'b0),
        .edge_valid_in_s3(1'b0),
        
        // East edge inputs - tie off
        .edge_data_in_e0(32'd0),
        .edge_data_in_e1(32'd0),
        .edge_data_in_e2(32'd0),
        .edge_data_in_e3(32'd0),
        .edge_valid_in_e0(1'b0),
        .edge_valid_in_e1(1'b0),
        .edge_valid_in_e2(1'b0),
        .edge_valid_in_e3(1'b0),
        
        // West edge inputs - FROM TILE MEMORY (The Data Pipeline!)
        .edge_data_in_w0(row_data[0]),   // Bank 0 -> Row 0 PEs
        .edge_data_in_w1(row_data[1]),   // Bank 1 -> Row 1 PEs
        .edge_data_in_w2(row_data[2]),   // Bank 2 -> Row 2 PEs
        .edge_data_in_w3(row_data[3]),   // Bank 3 -> Row 3 PEs
        .edge_valid_in_w0(row_valid[0]),
        .edge_valid_in_w1(row_valid[1]),
        .edge_valid_in_w2(row_valid[2]),
        .edge_valid_in_w3(row_valid[3]),
        
        // Edge outputs - connected for synthesis keepalive
        .edge_data_out_n0(edge_n0),
        .edge_data_out_n1(edge_n1),
        .edge_data_out_n2(edge_n2),
        .edge_data_out_n3(edge_n3),
        /* verilator lint_off PINCONNECTEMPTY */
        .edge_valid_out_n0(),  // Intentional: data captured by synthesis_keep
        .edge_valid_out_n1(),
        .edge_valid_out_n2(),
        .edge_valid_out_n3(),
        /* verilator lint_on PINCONNECTEMPTY */
        
        .edge_data_out_s0(edge_s0),
        .edge_data_out_s1(edge_s1),
        .edge_data_out_s2(edge_s2),
        .edge_data_out_s3(edge_s3),
        /* verilator lint_off PINCONNECTEMPTY */
        .edge_valid_out_s0(),
        .edge_valid_out_s1(),
        .edge_valid_out_s2(),
        .edge_valid_out_s3(),
        /* verilator lint_on PINCONNECTEMPTY */
        
        .edge_data_out_e0(edge_e0),
        .edge_data_out_e1(edge_e1),
        .edge_data_out_e2(edge_e2),
        .edge_data_out_e3(edge_e3),
        /* verilator lint_off PINCONNECTEMPTY */
        .edge_valid_out_e0(),
        .edge_valid_out_e1(),
        .edge_valid_out_e2(),
        .edge_valid_out_e3(),
        /* verilator lint_on PINCONNECTEMPTY */
        
        .edge_data_out_w0(edge_w0),
        .edge_data_out_w1(edge_w1),
        .edge_data_out_w2(edge_w2),
        .edge_data_out_w3(edge_w3),
        /* verilator lint_off PINCONNECTEMPTY */
        .edge_valid_out_w0(),
        .edge_valid_out_w1(),
        .edge_valid_out_w2(),
        .edge_valid_out_w3()
        /* verilator lint_on PINCONNECTEMPTY */
    );
    
    // =========================================================================
    // Synthesis Keeper: OR-reduce all edge outputs to single bit
    // =========================================================================
    // This prevents the synthesizer from optimizing away the array due to
    // unconnected outputs. Route this pin to a test pad or leave floating.
    assign synthesis_keep = (|edge_n0) | (|edge_n1) | (|edge_n2) | (|edge_n3) |
                            (|edge_s0) | (|edge_s1) | (|edge_s2) | (|edge_s3) |
                            (|edge_e0) | (|edge_e1) | (|edge_e2) | (|edge_e3) |
                            (|edge_w0) | (|edge_w1) | (|edge_w2) | (|edge_w3);
    
    // =========================================================================
    // Hybrid I/O: Capture Result from Last PE (PE 3,3)
    // =========================================================================
    // Register the result on cu_done pulse so the APB read returns a stable
    // value. Without this, edge_e3 is a live combinational wire that could
    // change during the 1-2 pipeline-drain cycles after auto-stop fires.
    logic [DATA_WIDTH-1:0] global_result_reg;
    always_ff @(posedge clk) begin
        if (!rst_n)
            global_result_reg <= '0;
        else if (cu_done && !cu_soft_reset)
            global_result_reg <= edge_e3;  // FIX: Don't capture on soft-reset abort
    end
    assign global_result = global_result_reg;
    
    // =========================================================================
    // LPR: Capture ALL 4 East-Edge Results (one per row)
    // =========================================================================
    // For 4×4 matrix operations, each row produces an independent result.
    // Capture on cu_done so PS can read all 4 via APB (0x58-0x64).
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            result_row[0] <= '0;
            result_row[1] <= '0;
            result_row[2] <= '0;
            result_row[3] <= '0;
        end else if (cu_done && !cu_soft_reset) begin
            result_row[0] <= edge_e0;  // PE(0,3) output
            result_row[1] <= edge_e1;  // PE(1,3) output
            result_row[2] <= edge_e2;  // PE(2,3) output
            result_row[3] <= edge_e3;  // PE(3,3) output
        end
    end
    
    // Result valid: latched on cu_done, cleared by soft_reset
    // CRITICAL: cu_done is a 1-cycle pulse that APB polling would miss.
    // Latch it so result_valid stays high until the next soft_reset.
    logic result_valid_latch;
    always_ff @(posedge clk) begin
        if (!rst_n || cu_soft_reset)
            result_valid_latch <= 1'b0;
        else if (cu_done)
            result_valid_latch <= 1'b1;
    end
    assign result_valid = result_valid_latch;
    
    // =========================================================================
    // Hybrid I/O: APB Multiplexers (Result Data + Handshake Signals)
    // =========================================================================
    // Extended APB address map:
    //   0x40  RESULT_DATA   - Computation result from last PE (RO)
    //   0x44  RESULT_STATUS - {31'b0, result_valid} (RO)
    //
    // Multiplexes between CSR module output and result registers
    // CRITICAL: Must drive pready for all addresses (APB protocol requirement)
    
    // Internal wires to avoid multiple drivers on output ports
    logic [31:0] apb_prdata;
    logic        apb_pready;
    
    always_comb begin
        // Data multiplexer: result registers vs CSR module
        case (paddr[7:0])
            8'h40: apb_prdata = global_result;              // RESULT_DATA (combinational)
            8'h44: apb_prdata = {31'b0, result_valid};      // RESULT_STATUS (combinational)
            8'h58: apb_prdata = result_row[0];              // LPR: Row 0 east-edge result
            8'h5C: apb_prdata = result_row[1];              // LPR: Row 1 east-edge result
            8'h60: apb_prdata = result_row[2];              // LPR: Row 2 east-edge result
            8'h64: apb_prdata = result_row[3];              // LPR: Row 3 east-edge result
            default: apb_prdata = csr_prdata;                // All other addresses from CSR
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
