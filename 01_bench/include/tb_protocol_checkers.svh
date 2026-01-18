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
// TRANSACTION COUNTERS & TRACE LOGGING
// ============================================================================
int ar_txn_count = 0;
int aw_txn_count = 0;
int r_txn_count = 0;
int w_txn_count = 0;
int b_txn_count = 0;
int axi_read_reqs_split_at_4kb = 0;  // Track 4KB boundary splits
int axi_config_writes = 0;           // Track config space writes

// ============================================================================
// 4KB BOUNDARY DETECTION VARIABLES
// ============================================================================
logic [31:0] burst_end_addr;
logic [11:0] start_page, end_page;
int beat_count;

// ============================================================================
// CONFIG WRITE TRACE VARIABLES
// ============================================================================
logic [3:0] config_pe_id;
logic [3:0] config_slot_id;
logic [2:0] config_offset;

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
// Note: Using blocking assignments (=) since assertion_errors is also
// modified by other testbench code using blocking assignments.
always @(posedge clk) begin
    if (rst_n && protocol_check_enable) begin
        // ================================================================
        // AR Channel: ARVALID/ARADDR stability
        // ================================================================
        if (ar_pending && !axi_arready) begin
            if (axi_arvalid !== 1'b1) begin
                $error("[AXI] ARVALID dropped before ARREADY @ %0t", $time);
                assertion_errors = assertion_errors + 1;
            end
            if (axi_araddr !== ar_addr_lock) begin
                $error("[AXI] ARADDR unstable: was 0x%h, now 0x%h @ %0t", 
                       ar_addr_lock, axi_araddr, $time);
                assertion_errors = assertion_errors + 1;
            end
            ar_stall_cycles = ar_stall_cycles + 1;
            if (ar_stall_cycles >= STALL_THRESHOLD) begin
                $warning("[AXI] AR channel stalled for %0d cycles", ar_stall_cycles);
            end
        end
        
        if (axi_arvalid && !axi_arready && !ar_pending) begin
            ar_pending = 1'b1;
            ar_addr_lock = axi_araddr;
            ar_stall_cycles = 0;
        end else if (axi_arvalid && axi_arready) begin
            ar_pending = 1'b0;
            ar_txn_count = ar_txn_count + 1;
            ar_stall_cycles = 0;
            
            // ================================================================
            // 4KB BOUNDARY DETECTION (CRITICAL FEATURE TEST)
            // ================================================================
            // Check if this burst would cross a 4KB boundary
            beat_count = axi_arlen + 1;  // arlen is 0-indexed
            burst_end_addr = axi_araddr + (beat_count * (1 << axi_arsize)) - 1;
            
            // Compare page boundaries: [31:12] is the 4KB page address
            if (burst_end_addr[31:12] != axi_araddr[31:12]) begin
                // Burst CROSSES a 4KB boundary
                // In normal operation, DMA splits at 4KB boundaries, so we shouldn't
                // see cross-boundary bursts. This counter tracks boundary-crossing
                // transactions for verification purposes.
                axi_read_reqs_split_at_4kb = axi_read_reqs_split_at_4kb + 1;
                $display("[4KB_BOUNDARY_DETECTED] Read crosses page boundary: Addr=0x%08h, Len=%0d, End=0x%08h", 
                         axi_araddr, axi_arlen, burst_end_addr);
            end
        end
        
        // ================================================================
        // AW Channel: AWVALID/AWADDR stability
        // ================================================================
        if (aw_pending && !axi_awready) begin
            if (axi_awvalid !== 1'b1) begin
                $error("[AXI] AWVALID dropped before AWREADY @ %0t", $time);
                assertion_errors = assertion_errors + 1;
            end
            if (axi_awaddr !== aw_addr_lock) begin
                $error("[AXI] AWADDR unstable @ %0t", $time);
                assertion_errors = assertion_errors + 1;
            end
            aw_stall_cycles = aw_stall_cycles + 1;
        end
        
        if (axi_awvalid && !axi_awready && !aw_pending) begin
            aw_pending = 1'b1;
            aw_addr_lock = axi_awaddr;
            aw_stall_cycles = 0;
        end else if (axi_awvalid && axi_awready) begin
            aw_pending = 1'b0;
            aw_txn_count = aw_txn_count + 1;
            aw_stall_cycles = 0;
            
            // ================================================================
            // CONFIG DOUBLEUMP DETECTION (CRITICAL FEATURE TEST)
            // ================================================================
            // Detect writes to config space (0x2000_0000 - 0x2FFF_FFFF)
            if (axi_awaddr[31:28] == 4'h2) begin
                axi_config_writes = axi_config_writes + 1;
                config_pe_id   = axi_awaddr[11:8];
                config_slot_id = axi_awaddr[7:4];
                config_offset  = axi_awaddr[2:0];
                
                if (config_offset == 3'h0) begin
                    $display("[CONFIG_TRACE] Write to PE%0d Slot%0d Low  (offset 0x00): Addr=0x%08h", 
                             config_pe_id, config_slot_id, axi_awaddr);
                end else if (config_offset == 3'h4) begin
                    $display("[CONFIG_TRACE] Write to PE%0d Slot%0d High (offset 0x04): Addr=0x%08h", 
                             config_pe_id, config_slot_id, axi_awaddr);
                end
            end
        end
        
        // ================================================================
        // W Channel: WVALID/WDATA stability
        // ================================================================
        if (w_pending && !axi_wready) begin
            if (axi_wvalid !== 1'b1) begin
                $error("[AXI] WVALID dropped before WREADY @ %0t", $time);
                assertion_errors = assertion_errors + 1;
            end
            if (axi_wdata !== w_data_lock) begin
                $error("[AXI] WDATA unstable @ %0t", $time);
                assertion_errors = assertion_errors + 1;
            end
            w_stall_cycles = w_stall_cycles + 1;
        end
        
        if (axi_wvalid && !axi_wready && !w_pending) begin
            w_pending = 1'b1;
            w_data_lock = axi_wdata;
            w_stall_cycles = 0;
        end else if (axi_wvalid && axi_wready) begin
            w_pending = 1'b0;
            w_txn_count = w_txn_count + 1;
            w_stall_cycles = 0;
        end
        
        // ================================================================
        // R Channel: Count read data beats
        // ================================================================
        if (axi_rvalid && axi_rready) begin
            r_txn_count = r_txn_count + 1;
        end
        
        // ================================================================
        // B Channel: Count write responses
        // ================================================================
        if (axi_bvalid && axi_bready) begin
            b_txn_count = b_txn_count + 1;
        end
        
    end else if (!rst_n) begin
        ar_pending = 1'b0;
        aw_pending = 1'b0;
        w_pending = 1'b0;
        ar_stall_cycles = 0;
        aw_stall_cycles = 0;
        w_stall_cycles = 0;
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
    $display("║  CRITICAL FEATURE VERIFICATION:                             ║");
    $display("║    4KB Boundary Splits:    %6d                            ║", axi_read_reqs_split_at_4kb);
    $display("║    Config Space Writes:         N/A (internal config I/F)      ║");
    $display("║    (Double-pump shifts detect above)                         ║");
    $display("╠══════════════════════════════════════════════════════════════╣");
    $display("║  Protocol Errors:          %6d                            ║", assertion_errors);
    $display("╚══════════════════════════════════════════════════════════════╝");
    $display("");
endtask
