// ==============================================================================
// tb_protocol_checkers.svh - Verilator-Native Protocol Monitors
// ==============================================================================
// Uses Verilator's native assert() for protocol checking.
// Replaces SVA concurrent assertions with immediate assertions.
// ==============================================================================

// ============================================================================
// STATE TRACKING
// ============================================================================
logic        ar_pending = 1'b0;
logic [31:0] ar_addr_lock = '0;
logic        aw_pending = 1'b0;
logic [31:0] aw_addr_lock = '0;
logic        w_pending = 1'b0;
logic [31:0] w_data_lock = '0;

// ============================================================================
// TRANSACTION COUNTERS
// ============================================================================
int ar_txn_count = 0;
int aw_txn_count = 0;
int r_txn_count = 0;
int w_txn_count = 0;
int b_txn_count = 0;

// ============================================================================
// STARVATION DETECTION
// ============================================================================
int ar_stall_cycles = 0;
int aw_stall_cycles = 0;
int w_stall_cycles = 0;
localparam int STALL_THRESHOLD = 1000;

// ============================================================================
// AXI PROTOCOL MONITOR
// ============================================================================
always_ff @(posedge clk) begin
    if (rst_n && protocol_check_enable) begin
        // ================================================================
        // AR Channel: ARVALID/ARADDR stability
        // ================================================================
        if (ar_pending && !axi_arready) begin
            if (axi_arvalid !== 1'b1) begin
                $error("[AXI] ARVALID dropped before ARREADY @ %0t", $time);
                assertion_errors++;
            end
            if (axi_araddr !== ar_addr_lock) begin
                $error("[AXI] ARADDR unstable: was 0x%h, now 0x%h @ %0t", 
                       ar_addr_lock, axi_araddr, $time);
                assertion_errors++;
            end
            ar_stall_cycles <= ar_stall_cycles + 1;
            if (ar_stall_cycles >= STALL_THRESHOLD) begin
                $warning("[AXI] AR channel stalled for %0d cycles", ar_stall_cycles);
            end
        end
        
        if (axi_arvalid && !axi_arready && !ar_pending) begin
            ar_pending <= 1'b1;
            ar_addr_lock <= axi_araddr;
            ar_stall_cycles <= 0;
        end else if (axi_arvalid && axi_arready) begin
            ar_pending <= 1'b0;
            ar_txn_count <= ar_txn_count + 1;
            ar_stall_cycles <= 0;
        end
        
        // ================================================================
        // AW Channel: AWVALID/AWADDR stability
        // ================================================================
        if (aw_pending && !axi_awready) begin
            if (axi_awvalid !== 1'b1) begin
                $error("[AXI] AWVALID dropped before AWREADY @ %0t", $time);
                assertion_errors++;
            end
            if (axi_awaddr !== aw_addr_lock) begin
                $error("[AXI] AWADDR unstable @ %0t", $time);
                assertion_errors++;
            end
            aw_stall_cycles <= aw_stall_cycles + 1;
        end
        
        if (axi_awvalid && !axi_awready && !aw_pending) begin
            aw_pending <= 1'b1;
            aw_addr_lock <= axi_awaddr;
            aw_stall_cycles <= 0;
        end else if (axi_awvalid && axi_awready) begin
            aw_pending <= 1'b0;
            aw_txn_count <= aw_txn_count + 1;
            aw_stall_cycles <= 0;
        end
        
        // ================================================================
        // W Channel: WVALID/WDATA stability
        // ================================================================
        if (w_pending && !axi_wready) begin
            if (axi_wvalid !== 1'b1) begin
                $error("[AXI] WVALID dropped before WREADY @ %0t", $time);
                assertion_errors++;
            end
            if (axi_wdata !== w_data_lock) begin
                $error("[AXI] WDATA unstable @ %0t", $time);
                assertion_errors++;
            end
            w_stall_cycles <= w_stall_cycles + 1;
        end
        
        if (axi_wvalid && !axi_wready && !w_pending) begin
            w_pending <= 1'b1;
            w_data_lock <= axi_wdata;
            w_stall_cycles <= 0;
        end else if (axi_wvalid && axi_wready) begin
            w_pending <= 1'b0;
            w_txn_count <= w_txn_count + 1;
            w_stall_cycles <= 0;
        end
        
        // ================================================================
        // R Channel: Count read data beats
        // ================================================================
        if (axi_rvalid && axi_rready) begin
            r_txn_count <= r_txn_count + 1;
        end
        
        // ================================================================
        // B Channel: Count write responses
        // ================================================================
        if (axi_bvalid && axi_bready) begin
            b_txn_count <= b_txn_count + 1;
        end
        
    end else if (!rst_n) begin
        ar_pending <= 1'b0;
        aw_pending <= 1'b0;
        w_pending <= 1'b0;
        ar_stall_cycles <= 0;
        aw_stall_cycles <= 0;
        w_stall_cycles <= 0;
    end
end

// ============================================================================
// PROTOCOL STATISTICS REPORTING
// ============================================================================
task automatic print_protocol_stats();
    $display("");
    $display("╔══════════════════════════════════════════════════════════════╗");
    $display("║                   PROTOCOL STATISTICS                        ║");
    $display("╠══════════════════════════════════════════════════════════════╣");
    $display("║  AXI Transactions:                                           ║");
    $display("║    AR (Read Address):      %6d                            ║", ar_txn_count);
    $display("║    R  (Read Data):         %6d                            ║", r_txn_count);
    $display("║    AW (Write Address):     %6d                            ║", aw_txn_count);
    $display("║    W  (Write Data):        %6d                            ║", w_txn_count);
    $display("║    B  (Write Response):    %6d                            ║", b_txn_count);
    $display("╠══════════════════════════════════════════════════════════════╣");
    $display("║  Protocol Errors:          %6d                            ║", assertion_errors);
    $display("╚══════════════════════════════════════════════════════════════╝");
    $display("");
endtask
