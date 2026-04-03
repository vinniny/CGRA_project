`ifndef TB_AGENTS_SVH
`define TB_AGENTS_SVH

// =============================================================================
// tb_agents.svh — Verification Agents (Driver + Monitor Bundles)
// =============================================================================
// Each agent encapsulates a driver and/or monitor for a specific interface.
// Agents simplify instantiation and wiring in the environment.
// =============================================================================

// ============================================================================
// APB Agent — Master Agent (Driver + Monitor)
// ============================================================================
class apb_agent;
    cgra_tb_config      cfg;
    apb_driver          drv;
    apb_monitor         mon;
    mailbox #(apb_txn)  mon_mbox;

    function new(cgra_tb_config c);
        cfg      = c;
        mon_mbox = new();
        drv      = new(cfg, null);  // Driver doesn't emit to mailbox (tasks do)
        mon      = new(cfg, mon_mbox);
    endfunction

    // Start monitor (called from environment via fork)
    task run_monitor(ref logic clk, ref logic psel, ref logic penable,
                     ref logic pwrite, ref logic [31:0] paddr,
                     ref logic [31:0] pwdata, ref logic [31:0] prdata,
                     ref logic pready, ref logic pslverr);
        mon.run(clk, psel, penable, pwrite, paddr, pwdata, prdata, pready, pslverr);
    endtask
endclass

// ============================================================================
// AXI Agent — Passive Monitor Agent (no driver, DUT is master)
// ============================================================================
class axi_agent;
    cgra_tb_config          cfg;
    axi_read_monitor        rd_mon;
    axi_write_monitor       wr_mon;
    mailbox #(axi_read_txn)  rd_mbox;
    mailbox #(axi_write_txn) wr_mbox;

    function new(cgra_tb_config c);
        cfg     = c;
        rd_mbox = new();
        wr_mbox = new();
        rd_mon  = new(cfg, rd_mbox);
        wr_mon  = new(cfg, wr_mbox);
    endfunction

    // Start read monitor
    task run_read_monitor(ref logic clk,
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
        rd_mon.run(clk, axi_arid, axi_araddr, axi_arlen, axi_arsize, axi_arburst,
                   axi_arvalid, axi_arready, axi_rid, axi_rdata, axi_rresp,
                   axi_rlast, axi_rvalid, axi_rready);
    endtask

    // Start write monitor
    task run_write_monitor(ref logic clk,
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
        wr_mon.run(clk, axi_awid, axi_awaddr, axi_awlen, axi_awsize, axi_awburst,
                   axi_awvalid, axi_awready, axi_wdata, axi_wstrb, axi_wlast,
                   axi_wvalid, axi_wready, axi_bid, axi_bresp, axi_bvalid, axi_bready);
    endtask
endclass

// ============================================================================
// DMA Agent — Transaction-Level DMA Agent
// ============================================================================
class dma_agent;
    cgra_tb_config      cfg;
    dma_driver          drv;
    mailbox #(dma_txn)  txn_mbox;

    function new(cgra_tb_config c, apb_driver apb_drv);
        cfg      = c;
        txn_mbox = new();
        drv      = new(cfg, apb_drv, txn_mbox);
    endfunction
endclass

`endif
