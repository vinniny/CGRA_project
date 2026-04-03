`ifndef TB_CONFIG_SVH
`define TB_CONFIG_SVH

// =============================================================================
// tb_config.svh — Testbench Configuration Object
// =============================================================================
// Wraps TB parameters in a class for passing to verification components.
// Coexists with existing localparam constants for backward compatibility.
// =============================================================================

class cgra_tb_config;
    // Memory model
    int unsigned mem_size       = 4 * 1024 * 1024 + 4;

    // Timeouts
    int unsigned dma_timeout    = 10000;
    int unsigned cu_timeout     = 1000000;
    int unsigned watchdog_ns    = 100_000_000;

    // Clock
    int unsigned clk_period_ns  = 10;

    // Error handling
    int unsigned max_errors     = 50;

    // Verbosity: 0=quiet, 1=normal, 2=verbose, 3=debug
    int unsigned verbosity      = 1;

    // Stress injection
    bit          stress_enable  = 0;
    int unsigned stress_prob    = 0;

    // Protocol checking
    bit          protocol_check = 1;

    // Random seed (from +SEED plusarg)
    int unsigned sim_seed       = 42;

    // Array dimensions (for parameterized tests)
    int unsigned array_rows     = 4;
    int unsigned array_cols     = 4;
    int unsigned num_pes        = 16;
    int unsigned context_depth  = 16;

    function void display();
        $display("[CONFIG] mem_size=%0d timeout=%0d stress=%0d verb=%0d seed=%0d array=%0dx%0d",
                 mem_size, dma_timeout, stress_enable, verbosity,
                 sim_seed, array_rows, array_cols);
    endfunction
endclass

`endif
