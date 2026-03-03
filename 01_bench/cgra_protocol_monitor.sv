// ==============================================================================
// CGRA Protocol Monitor - AXI4-Lite Compliance Checker + Hybrid I/O Verifier
// ==============================================================================
// Instantiate in testbench to catch protocol violations:
// - VALID must not drop before READY
// - Address/Data must remain stable during stall
// - Hybrid I/O APB result registers return correct values
// ==============================================================================

module cgra_protocol_monitor (
    input  logic        clk,
    input  logic        rst_n,
    
    // =========================================================================
    // AXI Write Address Channel
    // =========================================================================
    input  logic [31:0] awaddr,
    input  logic        awvalid,
    input  logic        awready,
    
    // =========================================================================
    // AXI Write Data Channel
    // =========================================================================
    input  logic [31:0] wdata,
    input  logic [3:0]  wstrb,
    input  logic        wvalid,
    input  logic        wready,
    input  logic        wlast,
    
    // =========================================================================
    // AXI Write Response Channel
    // =========================================================================
    input  logic        bvalid,
    input  logic        bready,
    
    // =========================================================================
    // AXI Read Address Channel
    // =========================================================================
    input  logic [31:0] araddr,
    input  logic        arvalid,
    input  logic        arready,
    
    // =========================================================================
    // AXI Read Data Channel
    // =========================================================================
    input  logic [31:0] rdata,
    input  logic        rvalid,
    input  logic        rready,
    
    // =========================================================================
    // APB Slave Interface (for Hybrid I/O verification)
    // =========================================================================
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] paddr,
    input  logic [31:0] prdata
);

    // =========================================================================
    // Write Address Channel Monitoring
    // =========================================================================
    logic        aw_active;
    logic [31:0] aw_addr_lock;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            aw_active <= 1'b0;
            aw_addr_lock <= 32'd0;
        end else begin
            if (awvalid && !awready) begin
                // Stall condition - check stability
                if (!aw_active) begin
                    // First cycle of stall - lock values
                    aw_active <= 1'b1;
                    aw_addr_lock <= awaddr;
                end else begin
                    // Subsequent cycles - check stability
                    if (awaddr !== aw_addr_lock) begin
                        $error("[PROTOCOL MONITOR] AXI VIOLATION: AWADDR changed during stall! Locked=0x%08h, Current=0x%08h", 
                               aw_addr_lock, awaddr);
                    end
                end
            end else if (awvalid && awready) begin
                // Handshake complete
                aw_active <= 1'b0;
            end else if (!awvalid && aw_active) begin
                // VALID dropped before READY - violation!
                $error("[PROTOCOL MONITOR] AXI VIOLATION: AWVALID dropped before AWREADY!");
                aw_active <= 1'b0;
            end else begin
                aw_active <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // Write Data Channel Monitoring
    // =========================================================================
    logic        w_active;
    logic [31:0] w_data_lock;
    logic [3:0]  w_strb_lock;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            w_active <= 1'b0;
            w_data_lock <= 32'd0;
            w_strb_lock <= 4'd0;
        end else begin
            if (wvalid && !wready) begin
                if (!w_active) begin
                    w_active <= 1'b1;
                    w_data_lock <= wdata;
                    w_strb_lock <= wstrb;
                end else begin
                    if (wdata !== w_data_lock) begin
                        $error("[PROTOCOL MONITOR] AXI VIOLATION: WDATA changed during stall!");
                    end
                    if (wstrb !== w_strb_lock) begin
                        $error("[PROTOCOL MONITOR] AXI VIOLATION: WSTRB changed during stall!");
                    end
                end
            end else if (wvalid && wready) begin
                w_active <= 1'b0;
            end else if (!wvalid && w_active) begin
                $error("[PROTOCOL MONITOR] AXI VIOLATION: WVALID dropped before WREADY!");
                w_active <= 1'b0;
            end else begin
                w_active <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // Read Address Channel Monitoring
    // =========================================================================
    logic        ar_active;
    logic [31:0] ar_addr_lock;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            ar_active <= 1'b0;
            ar_addr_lock <= 32'd0;
        end else begin
            if (arvalid && !arready) begin
                if (!ar_active) begin
                    ar_active <= 1'b1;
                    ar_addr_lock <= araddr;
                end else begin
                    if (araddr !== ar_addr_lock) begin
                        $error("[PROTOCOL MONITOR] AXI VIOLATION: ARADDR changed during stall! Locked=0x%08h, Current=0x%08h",
                               ar_addr_lock, araddr);
                    end
                end
            end else if (arvalid && arready) begin
                ar_active <= 1'b0;
            end else if (!arvalid && ar_active) begin
                $error("[PROTOCOL MONITOR] AXI VIOLATION: ARVALID dropped before ARREADY!");
                ar_active <= 1'b0;
            end else begin
                ar_active <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // Read Data Channel Monitoring
    // =========================================================================
    logic        r_active;
    logic [31:0] r_data_lock;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            r_active <= 1'b0;
            r_data_lock <= 32'd0;
        end else begin
            if (rvalid && !rready) begin
                if (!r_active) begin
                    r_active <= 1'b1;
                    r_data_lock <= rdata;
                end else begin
                    if (rdata !== r_data_lock) begin
                        $error("[PROTOCOL MONITOR] AXI VIOLATION: RDATA changed during stall!");
                    end
                end
            end else if (rvalid && rready) begin
                r_active <= 1'b0;
            end else if (!rvalid && r_active) begin
                $error("[PROTOCOL MONITOR] AXI VIOLATION: RVALID dropped before RREADY!");
                r_active <= 1'b0;
            end else begin
                r_active <= 1'b0;
            end
        end
    end
    
    // =========================================================================
    // Transaction Counters (for debugging)
    // =========================================================================
    integer aw_count, w_count, b_count, ar_count, r_count;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            aw_count <= 0;
            w_count <= 0;
            b_count <= 0;
            ar_count <= 0;
            r_count <= 0;
        end else begin
            if (awvalid && awready) aw_count <= aw_count + 1;
            if (wvalid && wready)   w_count <= w_count + 1;
            if (bvalid && bready)   b_count <= b_count + 1;
            if (arvalid && arready) ar_count <= ar_count + 1;
            if (rvalid && rready)   r_count <= r_count + 1;
        end
    end
    
    // =========================================================================
    // AXI4 Write Channel: SVA Property Definitions
    // =========================================================================
    // Peek into DUT's internal DMA signals for burst verification
    wire [7:0] mon_write_beat_counter = tb_top.u_dut.u_dma.write_beat_counter;
    wire [7:0] mon_write_burst_len    = tb_top.u_dut.u_dma.write_burst_len;
    
    // -------------------------------------------------------------------------
    // Property: AWVALID must not drop before AWREADY
    // AXI4 spec: Once VALID is asserted, it must remain asserted until READY
    // -------------------------------------------------------------------------
    property p_sticky_awvalid;
        @(posedge clk) disable iff (!rst_n)
            (awvalid && !awready) |=> awvalid;
    endproperty
    
    assert property (p_sticky_awvalid)
        else $error("[PROTOCOL MONITOR] AXI VIOLATION: AWVALID dropped before AWREADY!");
    
    cover property (p_sticky_awvalid)
        $display("[PROTOCOL MONITOR] ✓ AWVALID sticky behavior verified");
    
    // -------------------------------------------------------------------------
    // Property: WVALID must not drop before WREADY
    // AXI4 spec: Once VALID is asserted, it must remain asserted until READY
    // -------------------------------------------------------------------------
    property p_sticky_wvalid;
        @(posedge clk) disable iff (!rst_n)
            (wvalid && !wready) |=> wvalid;
    endproperty
    
    assert property (p_sticky_wvalid)
        else $error("[PROTOCOL MONITOR] AXI VIOLATION: WVALID dropped before WREADY!");
    
    cover property (p_sticky_wvalid)
        $display("[PROTOCOL MONITOR] ✓ WVALID sticky behavior verified");
    
    // -------------------------------------------------------------------------
    // Property: WLAST must be HIGH only on final beat of burst
    // Checks that wlast assertion matches internal DMA burst counter
    // -------------------------------------------------------------------------
    property p_wlast_final_beat;
        @(posedge clk) disable iff (!rst_n)
            (wvalid && wready && wlast) |-> (mon_write_beat_counter == mon_write_burst_len);
    endproperty
    
    assert property (p_wlast_final_beat)
        else $error("[PROTOCOL MONITOR] AXI VIOLATION: WLAST asserted but beat_counter(%0d) != burst_len(%0d)!",
                    mon_write_beat_counter, mon_write_burst_len);
    
    cover property (p_wlast_final_beat)
        $display("[PROTOCOL MONITOR] ✓ WLAST correctly asserted on final beat");
    
    // -------------------------------------------------------------------------
    // Property: WLAST must NOT be HIGH before final beat
    // -------------------------------------------------------------------------
    property p_wlast_not_early;
        @(posedge clk) disable iff (!rst_n)
            (wvalid && wready && !wlast) |-> (mon_write_beat_counter != mon_write_burst_len);
    endproperty
    
    assert property (p_wlast_not_early)
        else $error("[PROTOCOL MONITOR] AXI VIOLATION: WLAST not asserted but beat_counter(%0d) == burst_len(%0d)!",
                    mon_write_beat_counter, mon_write_burst_len);
    
    // -------------------------------------------------------------------------
    // Property: Deadlock Prevention - BREADY must follow WLAST handshake
    // After wvalid & wready & wlast handshake, bready must assert within N cycles
    // -------------------------------------------------------------------------
    localparam int BREADY_TIMEOUT = 16;  // Maximum cycles to assert bready
    
    property p_bready_after_wlast;
        @(posedge clk) disable iff (!rst_n)
            (wvalid && wready && wlast) |-> ##[1:BREADY_TIMEOUT] bready;
    endproperty
    
    assert property (p_bready_after_wlast)
        else $error("[PROTOCOL MONITOR] AXI DEADLOCK: BREADY not asserted within %0d cycles after WLAST!",
                    BREADY_TIMEOUT);
    
    cover property (p_bready_after_wlast)
        $display("[PROTOCOL MONITOR] ✓ BREADY asserted after WLAST handshake");
    
    // -------------------------------------------------------------------------
    // Property: BVALID/BREADY handshake must complete after WLAST
    // -------------------------------------------------------------------------
    property p_write_response_complete;
        @(posedge clk) disable iff (!rst_n)
            (wvalid && wready && wlast) |-> ##[1:BREADY_TIMEOUT*2] (bvalid && bready);
    endproperty
    
    assert property (p_write_response_complete)
        else $error("[PROTOCOL MONITOR] AXI DEADLOCK: Write response handshake not completed after WLAST!");
    
    // =========================================================================
    // Hybrid I/O: Signal Aliases via XMR (Cross-Module Reference)
    // =========================================================================
    // Peek into DUT's internal result signals for verification
    wire [31:0] mon_global_result = tb_top.u_dut.global_result;
    wire        mon_result_valid  = tb_top.u_dut.result_valid;
    
    // =========================================================================
    // Hybrid I/O: APB Assertion 1 - Data Integrity (0x40 Read)
    // =========================================================================
    // Verify: When CPU reads address 0x40 (RESULT_DATA), the returned prdata
    // matches the internal global_result value.
    //
    // Property: APB read of 0x40 → prdata == global_result
    property apb_result_data_integrity;
        @(posedge clk) disable iff (!rst_n)
            (psel && penable && !pwrite && (paddr[7:0] == 8'h40))
            |-> (prdata == mon_global_result);
    endproperty
    
    assert property (apb_result_data_integrity)
        else $error("[HYBRID_IO] DATA INTEGRITY VIOLATION: APB read 0x40 returned 0x%08h, expected 0x%08h",
                    prdata, mon_global_result);
    
    cover property (apb_result_data_integrity)
        $display("[HYBRID_IO] ✓ APB RESULT_DATA (0x40) read verified: prdata=0x%08h", prdata);
    
    // =========================================================================
    // Hybrid I/O: APB Assertion 2 - Valid Flag Correctness (0x44 Read)
    // =========================================================================
    // Verify: When CPU reads address 0x44 (RESULT_STATUS), bit [0] matches
    // the internal result_valid flag, and bits [31:1] are zero (reserved).
    //
    // Property: APB read of 0x44 → prdata[0] == result_valid && prdata[31:1] == 0
    property apb_result_status_valid_flag;
        @(posedge clk) disable iff (!rst_n)
            (psel && penable && !pwrite && (paddr[7:0] == 8'h44))
            |-> (prdata[0] == mon_result_valid && prdata[31:1] == 31'b0);
    endproperty
    
    assert property (apb_result_status_valid_flag)
        else $error("[HYBRID_IO] VALID FLAG VIOLATION: APB read 0x44 returned 0x%08h, expected {31'b0, %0b}",
                    prdata, mon_result_valid);
    
    cover property (apb_result_status_valid_flag)
        $display("[HYBRID_IO] ✓ APB RESULT_STATUS (0x44) valid flag verified: prdata[0]=%0b", prdata[0]);

endmodule
