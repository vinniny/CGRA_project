`ifndef TB_ENV_SVH
`define TB_ENV_SVH

// =============================================================================
// tb_env.svh — Top-Level Verification Environment
// =============================================================================
// The environment instantiates all agents, scoreboards, and starts background
// processes (monitors, scoreboards). It provides a unified run() and report()
// interface for the testbench.
//
// USAGE:
//   1. Instantiate cgra_env in tb_top
//   2. Call env.build() to create agents
//   3. Call env.run() via fork to start monitors/scoreboards
//   4. Call env.report() at end of simulation to display stats
// =============================================================================

class cgra_env;
    // Configuration
    cgra_tb_config cfg;
    
    // Agents
    apb_agent apb_agt;
    axi_agent axi_agt;
    dma_agent dma_agt;
    
    // Scoreboards
    dma_scoreboard dma_scbd;
    pe_scoreboard  pe_scbd;
    
    // Mailboxes for inter-component communication
    mailbox #(dma_txn) dma_txn_mbox;
    
    // Control flags
    bit monitors_started;
    bit scoreboards_started;
    
    function new();
        cfg = new();
        monitors_started = 0;
        scoreboards_started = 0;
    endfunction
    
    // Build phase: Create all agents and scoreboards
    function void build();
        $display("[ENV] Building verification environment...");
        
        // Create agents
        apb_agt = new(cfg);
        axi_agt = new(cfg);
        dma_agt = new(cfg, apb_agt.drv);
        
        // Create DMA scoreboard mailbox (shared between driver and scoreboard)
        dma_txn_mbox = new();
        dma_agt.txn_mbox = dma_txn_mbox;
        
        // Create scoreboards
        dma_scbd = new(cfg, dma_txn_mbox);
        pe_scbd  = new(cfg);
        
        $display("[ENV] Build complete: APB agent, AXI agent, DMA agent, 2 scoreboards");
    endfunction
    
    // Report phase: Display scoreboard statistics
    function void report();
        $display("");
        $display("═══════════════════════════════════════════════════════════════");
        $display("  VERIFICATION ENVIRONMENT REPORT");
        $display("═══════════════════════════════════════════════════════════════");
        $display("");
        dma_scbd.report();
        $display("");
        pe_scbd.report();
        $display("");
        $display("═══════════════════════════════════════════════════════════════");
    endfunction
endclass

`endif
