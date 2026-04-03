`ifndef TB_MONITORS_SVH
`define TB_MONITORS_SVH

// =============================================================================
// tb_monitors.svh — Passive Transaction-Level Monitors
// =============================================================================
// Monitor classes observe DUT signals passively and reconstruct transaction
// objects. They run alongside existing protocol checkers without interference.
// Burst transactions (AXI) require multi-cycle state tracking.
// =============================================================================

// ============================================================================
// APB Monitor
// ============================================================================
// Note: Xcelium doesn't support 'const ref' in class members (only in task args).
// Solution: Pass signals as task ref arguments, not class members.
class apb_monitor;
    cgra_tb_config cfg;
    mailbox #(apb_txn) txn_out;

    function new(cgra_tb_config c, mailbox #(apb_txn) mbox);
        cfg     = c;
        txn_out = mbox;
    endfunction

    // APB transaction capture: SETUP (psel && !penable) → ACCESS (penable && pready)
    // Signal references passed as task arguments (Xcelium-compliant)
    task run(ref logic clk, ref logic psel, ref logic penable,
             ref logic pwrite, ref logic [31:0] paddr,
             ref logic [31:0] pwdata, ref logic [31:0] prdata,
             ref logic pready, ref logic pslverr);
        apb_txn t;
        forever begin
            @(posedge clk);
            // Detect ACCESS phase completion (handshake)
            if (psel && penable && pready) begin
                t = new();
                t.addr     = paddr;
                t.is_write = pwrite;
                t.data     = pwrite ? pwdata : prdata;
                t.response_data = prdata;
                t.slverr   = pslverr;
                t.timestamp = $time;
                if (txn_out != null) txn_out.put(t);
                if (cfg.verbosity >= 3)
                    $display("[MON_APB] %0t %s", $time, t.to_string());
            end
        end
    endtask
endclass

// ============================================================================
// AXI Read Monitor
// ============================================================================
class axi_read_monitor;
    cgra_tb_config cfg;
    mailbox #(axi_read_txn) txn_out;

    // State for burst reconstruction
    axi_read_txn active_txn;
    logic        txn_pending;

    function new(cgra_tb_config c, mailbox #(axi_read_txn) mbox);
        cfg         = c;
        txn_out     = mbox;
        txn_pending = 0;
    endfunction

    task run(ref logic clk,
             ref logic [3:0]  axi_arid,
             ref logic [31:0] axi_araddr,
             ref logic [7:0]  axi_arlen,
             ref logic [2:0]  axi_arsize,
             ref logic [1:0]  axi_arburst,
             ref logic        axi_arvalid,
             ref logic        axi_arready,
             ref logic [3:0]  axi_rid,
             ref logic [31:0] axi_rdata,
             ref logic [1:0]  axi_rresp,
             ref logic        axi_rlast,
             ref logic        axi_rvalid,
             ref logic        axi_rready);
        forever begin
            @(posedge clk);
            
            // AR channel: Capture read request metadata
            if (axi_arvalid && axi_arready) begin
                active_txn = new();
                active_txn.addr  = axi_araddr;
                active_txn.len   = axi_arlen;
                active_txn.size  = axi_arsize;
                active_txn.burst = axi_arburst;
                active_txn.id    = axi_arid;
                txn_pending = 1;
                if (cfg.verbosity >= 3)
                    $display("[MON_AXI_AR] %0t AR addr=0x%08h len=%0d id=%0d",
                             $time, axi_araddr, axi_arlen, axi_arid);
            end
            
            // R channel: Accumulate data beats
            if (axi_rvalid && axi_rready && txn_pending) begin
                active_txn.data_beats.push_back(axi_rdata);
                if (cfg.verbosity >= 3)
                    $display("[MON_AXI_R] %0t R data=0x%08h last=%0d beat=%0d/%0d",
                             $time, axi_rdata, axi_rlast,
                             active_txn.data_beats.size(), active_txn.len + 1);
                
                // On RLAST, capture response and emit transaction
                if (axi_rlast) begin
                    active_txn.resp = axi_rresp;
                    active_txn.timestamp = $time;
                    if (txn_out != null) txn_out.put(active_txn);
                    if (cfg.verbosity >= 2)
                        $display("[MON_AXI_RD] %0t %s", $time, active_txn.to_string());
                    txn_pending = 0;
                end
            end
        end
    endtask
endclass

// ============================================================================
// AXI Write Monitor
// ============================================================================
class axi_write_monitor;
    cgra_tb_config cfg;
    mailbox #(axi_write_txn) txn_out;

    // State for burst reconstruction (AW and W can arrive out-of-order)
    axi_write_txn aw_txn;    // Metadata from AW channel
    logic         aw_pending;
    logic         w_complete;

    function new(cgra_tb_config c, mailbox #(axi_write_txn) mbox);
        cfg         = c;
        txn_out     = mbox;
        aw_pending  = 0;
        w_complete  = 0;
    endfunction

    task run(ref logic clk,
             ref logic [3:0]  axi_awid,
             ref logic [31:0] axi_awaddr,
             ref logic [7:0]  axi_awlen,
             ref logic [2:0]  axi_awsize,
             ref logic [1:0]  axi_awburst,
             ref logic        axi_awvalid,
             ref logic        axi_awready,
             ref logic [31:0] axi_wdata,
             ref logic [3:0]  axi_wstrb,
             ref logic        axi_wlast,
             ref logic        axi_wvalid,
             ref logic        axi_wready,
             ref logic [3:0]  axi_bid,
             ref logic [1:0]  axi_bresp,
             ref logic        axi_bvalid,
             ref logic        axi_bready);
        forever begin
            @(posedge clk);
            
            // AW channel: Capture write request metadata
            if (axi_awvalid && axi_awready) begin
                aw_txn = new();
                aw_txn.addr  = axi_awaddr;
                aw_txn.len   = axi_awlen;
                aw_txn.size  = axi_awsize;
                aw_txn.burst = axi_awburst;
                aw_txn.id    = axi_awid;
                aw_pending = 1;
                w_complete = 0;
                if (cfg.verbosity >= 3)
                    $display("[MON_AXI_AW] %0t AW addr=0x%08h len=%0d id=%0d",
                             $time, axi_awaddr, axi_awlen, axi_awid);
            end
            
            // W channel: Accumulate write data beats
            if (axi_wvalid && axi_wready && aw_pending) begin
                aw_txn.data_beats.push_back(axi_wdata);
                aw_txn.strb_beats.push_back(axi_wstrb);
                if (cfg.verbosity >= 3)
                    $display("[MON_AXI_W] %0t W data=0x%08h strb=0x%01h last=%0d beat=%0d/%0d",
                             $time, axi_wdata, axi_wstrb, axi_wlast,
                             aw_txn.data_beats.size(), aw_txn.len + 1);
                
                // On WLAST, mark W phase complete but wait for B response
                if (axi_wlast) begin
                    w_complete = 1;
                end
            end
            
            // B channel: Capture write response (completes transaction)
            if (axi_bvalid && axi_bready && aw_pending && w_complete) begin
                aw_txn.resp = axi_bresp;
                aw_txn.timestamp = $time;
                if (txn_out != null) txn_out.put(aw_txn);
                if (cfg.verbosity >= 2)
                    $display("[MON_AXI_WR] %0t %s", $time, aw_txn.to_string());
                aw_pending = 0;
                w_complete = 0;
            end
        end
    endtask
endclass

`endif
