// ==============================================================================
// CGRA Protocol Monitor - AXI4-Lite Compliance Checker
// ==============================================================================
// Instantiate in testbench to catch protocol violations:
// - VALID must not drop before READY
// - Address/Data must remain stable during stall
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
    input  logic        rready
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
            ar_count <= 0;
            r_count <= 0;
        end else begin
            if (awvalid && awready) aw_count <= aw_count + 1;
            if (wvalid && wready)   w_count <= w_count + 1;
            if (arvalid && arready) ar_count <= ar_count + 1;
            if (rvalid && rready)   r_count <= r_count + 1;
        end
    end

endmodule
