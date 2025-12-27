// ==============================================================================
// dma_protocol_checker.sv - High-Precision DMA Protocol Monitor
// ==============================================================================
// Purpose: Real-time assertion-based verification of DMA engine behavior
// This module enforces AXI protocol compliance and FIFO integrity at every cycle.
// If any rule is violated, the simulation will immediately stop with a fatal error.
//
// Usage: Bind this to the DMA engine in your testbench:
//   bind cgra_dma_engine dma_protocol_checker u_checker (.*);
//
// Or instantiate directly with signal connections in tb_top.sv
// ==============================================================================

module dma_protocol_checker (
    input logic        clk,
    input logic        rst_n,
    
    // FSM States
    input logic [1:0]  r_state,       // Read FSM state
    input logic [2:0]  w_state,       // Write FSM state
    
    // FIFO Status
    input logic [4:0]  count,         // FIFO count (0-16)
    input logic        fifo_full,
    input logic        fifo_empty,
    input logic        fifo_push,
    input logic        fifo_pop,
    
    // AXI Read Address Channel
    input logic        m_axi_arvalid,
    input logic        m_axi_arready,
    input logic [31:0] m_axi_araddr,
    input logic [7:0]  m_axi_arlen,
    
    // AXI Read Data Channel
    input logic        m_axi_rvalid,
    input logic        m_axi_rready,
    input logic        m_axi_rlast,
    
    // AXI Write Address Channel
    input logic        m_axi_awvalid,
    input logic        m_axi_awready,
    
    // AXI Write Data Channel
    input logic        m_axi_wvalid,
    input logic        m_axi_wready
);

    // =========================================================================
    // LAYER 1: AXI Protocol Safety (Prevents Handshake Bugs)
    // =========================================================================
    // Rule: Once VALID is asserted, it MUST stay HIGH until READY is received.
    // Prevents: Signal "glitching" that confuses the Interconnect.
    
    // AR Channel: ARVALID must stay high until ARREADY
    property p_axi_arvalid_stable;
        @(posedge clk) disable iff (!rst_n)
        (m_axi_arvalid && !m_axi_arready) |=> m_axi_arvalid;
    endproperty
    assert property (p_axi_arvalid_stable) 
        else $fatal(1, "[AXI VIOLATION] ARVALID dropped before ARREADY!");
    
    // AW Channel: AWVALID must stay high until AWREADY
    property p_axi_awvalid_stable;
        @(posedge clk) disable iff (!rst_n)
        (m_axi_awvalid && !m_axi_awready) |=> m_axi_awvalid;
    endproperty
    assert property (p_axi_awvalid_stable) 
        else $fatal(1, "[AXI VIOLATION] AWVALID dropped before AWREADY!");
    
    // W Channel: WVALID must stay high until WREADY
    property p_axi_wvalid_stable;
        @(posedge clk) disable iff (!rst_n)
        (m_axi_wvalid && !m_axi_wready) |=> m_axi_wvalid;
    endproperty
    assert property (p_axi_wvalid_stable) 
        else $fatal(1, "[AXI VIOLATION] WVALID dropped before WREADY!");

    // =========================================================================
    // LAYER 2: 4KB Boundary Protection (Prevents X01 Hangs)
    // =========================================================================
    // Rule: A burst (Start Addr + Length) MUST NOT cross a 4KB boundary.
    // Calculation: (Start & 0xFFF) + (Len+1)*4 must be <= 0x1000
    
    wire [12:0] burst_end_offset = m_axi_araddr[11:0] + ((m_axi_arlen + 1) << 2);
    
    property p_no_4kb_crossing;
        @(posedge clk) disable iff (!rst_n)
        (m_axi_arvalid && m_axi_arready) |-> (burst_end_offset <= 13'h1000);
    endproperty
    assert property (p_no_4kb_crossing) 
        else $fatal(1, "[AXI VIOLATION] Burst crosses 4KB Boundary! Addr: %h, Len: %h, End Offset: %h", 
                   m_axi_araddr, m_axi_arlen, burst_end_offset);

    // =========================================================================
    // LAYER 3: FIFO Integrity (Prevents Overflow/Underflow)
    // =========================================================================
    
    // Rule 1: Never push to a full FIFO
    property p_no_fifo_overflow;
        @(posedge clk) disable iff (!rst_n)
        fifo_full |-> !fifo_push;
    endproperty
    assert property (p_no_fifo_overflow) 
        else $fatal(1, "[FIFO VIOLATION] Attempted push to full FIFO!");
    
    // Rule 2: Never pop from an empty FIFO
    property p_no_fifo_underflow;
        @(posedge clk) disable iff (!rst_n)
        fifo_empty |-> !fifo_pop;
    endproperty
    assert property (p_no_fifo_underflow) 
        else $fatal(1, "[FIFO VIOLATION] Attempted pop from empty FIFO!");
    
    // Rule 3: FIFO count must be in valid range
    property p_fifo_count_valid;
        @(posedge clk) disable iff (!rst_n)
        1'b1 |-> (count <= 5'd16);
    endproperty
    assert property (p_fifo_count_valid) 
        else $fatal(1, "[FIFO VIOLATION] Count exceeded FIFO depth: %d", count);

    // =========================================================================
    // LAYER 4: Burst Handshake Integrity
    // =========================================================================
    
    // Track ongoing burst
    logic [7:0] expected_beats;
    logic [7:0] received_beats;
    logic in_burst;
    
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            expected_beats <= 0;
            received_beats <= 0;
            in_burst <= 0;
        end else begin
            // Start of new burst
            if (m_axi_arvalid && m_axi_arready) begin
                expected_beats <= m_axi_arlen + 1;
                received_beats <= 0;
                in_burst <= 1;
            end
            
            // Beat received
            if (in_burst && m_axi_rvalid && m_axi_rready) begin
                received_beats <= received_beats + 1;
                
                // Check RLAST on final beat
                if (received_beats == expected_beats - 1) begin
                    if (!m_axi_rlast) begin
                        $fatal(1, "[BURST VIOLATION] RLAST not asserted on final beat! Beat %d of %d", 
                               received_beats + 1, expected_beats);
                    end
                    in_burst <= 0;
                end else begin
                    // Premature RLAST
                    if (m_axi_rlast) begin
                        $fatal(1, "[BURST VIOLATION] RLAST asserted too early! Beat %d of %d", 
                               received_beats + 1, expected_beats);
                    end
                end
            end
        end
    end

    // =========================================================================
    // Coverage Points (Optional - for coverage analysis)
    // =========================================================================
    
    // Cover: Single-beat burst (ARLEN=0)
    covergroup cg_burst_types @(posedge clk);
        option.per_instance = 1;
        cp_single_beat: coverpoint (m_axi_arvalid && m_axi_arready && m_axi_arlen == 0);
        cp_multi_beat:  coverpoint (m_axi_arvalid && m_axi_arready && m_axi_arlen > 0);
        cp_max_burst:   coverpoint (m_axi_arvalid && m_axi_arready && m_axi_arlen == 15);
    endgroup
    
    cg_burst_types cg_inst = new();
    
    // =========================================================================
    // Debug Display (when assertions pass)
    // =========================================================================
    
    // Uncomment for verbose monitoring:
    // always @(posedge clk) begin
    //     if (m_axi_arvalid && m_axi_arready)
    //         $display("[PROTOCOL] AR Handshake: Addr=%h, Len=%d", m_axi_araddr, m_axi_arlen+1);
    //     if (m_axi_rvalid && m_axi_rready && m_axi_rlast)
    //         $display("[PROTOCOL] Burst Complete: %d beats received", received_beats+1);
    // end

endmodule
