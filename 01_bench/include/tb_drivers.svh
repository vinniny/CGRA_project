`ifndef TB_DRIVERS_SVH
`define TB_DRIVERS_SVH

// =============================================================================
// tb_drivers.svh — Transaction-Level Driver Classes
// =============================================================================
// Each driver wraps existing procedural tasks (tb_tasks.svh) and emits
// transaction objects to mailboxes for monitors/scoreboards.
// Existing test suites continue calling tasks directly — zero breakage.
// =============================================================================

// ============================================================================
// APB Driver
// ============================================================================
class apb_driver;
    cgra_tb_config cfg;
    mailbox #(apb_txn) txn_out;

    function new(cgra_tb_config c, mailbox #(apb_txn) mbox);
        cfg     = c;
        txn_out = mbox;
    endfunction

    task write(input logic [31:0] addr, input logic [31:0] data);
        apb_txn t = new();
        t.addr     = addr;
        t.data     = data;
        t.is_write = 1;
        apb_write(addr, data);  // Delegate to existing procedural task
        t.timestamp = $time;
        if (txn_out != null) txn_out.put(t);
    endtask

    task read(input logic [31:0] addr, output logic [31:0] data);
        apb_txn t = new();
        t.addr     = addr;
        t.is_write = 0;
        apb_read(addr, data);   // Delegate to existing procedural task
        t.response_data = data;
        t.data          = data;
        t.timestamp     = $time;
        if (txn_out != null) txn_out.put(t);
    endtask

    task check(input logic [31:0] addr, input logic [31:0] expected, input string msg);
        logic [31:0] rd;
        read(addr, rd);
        if (rd === expected) pass(msg);
        else fail(msg, $sformatf("exp=0x%08h got=0x%08h", expected, rd));
    endtask
endclass

// ============================================================================
// DMA Driver
// ============================================================================
class dma_driver;
    cgra_tb_config cfg;
    apb_driver     apb_drv;
    mailbox #(dma_txn) txn_out;

    function new(cgra_tb_config c, apb_driver a, mailbox #(dma_txn) mbox);
        cfg     = c;
        apb_drv = a;
        txn_out = mbox;
    endfunction

    task xfer(input logic [31:0] src, input logic [31:0] dst,
              input logic [31:0] size, input int timeout);
        dma_txn t = new();
        t.src  = src;
        t.dst  = dst;
        t.size = size;
        t.set_direction();
        dma_transfer(src, dst, size, timeout);  // Delegate to existing task
        t.completed = 1;
        t.timestamp = $time;
        if (txn_out != null) txn_out.put(t);
    endtask
endclass

// ============================================================================
// PE Configuration Driver
// ============================================================================
class pe_config_driver;
    cgra_tb_config cfg;
    mailbox #(pe_config_txn) txn_out;

    function new(cgra_tb_config c, mailbox #(pe_config_txn) mbox);
        cfg     = c;
        txn_out = mbox;
    endfunction

    task config_safe(input logic [3:0] pe_id, input logic [5:0] opcode,
                     input logic [3:0] src0, input logic [3:0] src1,
                     input logic [3:0] dst, input logic [3:0] route);
        pe_config_txn t = new();
        t.pe_id = pe_id;
        t.slot  = 4'd0;
        t.config_word = build_pe_config(opcode, src0, src1, dst, route, 16'd0);
        config_pe_safe(pe_id, opcode, src0, src1, dst, route);  // Delegate
        t.timestamp = $time;
        if (txn_out != null) txn_out.put(t);
    endtask

    task config_imm(input logic [3:0] pe_id, input logic [5:0] opcode,
                    input logic [3:0] src0, input logic [3:0] src1,
                    input logic [3:0] dst, input logic [3:0] route,
                    input logic [15:0] imm);
        pe_config_txn t = new();
        t.pe_id = pe_id;
        t.slot  = 4'd0;
        t.config_word = build_pe_config(opcode, src0, src1, dst, route, imm);
        config_pe_imm(pe_id, opcode, src0, src1, dst, route, imm);  // Delegate
        t.timestamp = $time;
        if (txn_out != null) txn_out.put(t);
    endtask
endclass

// ============================================================================
// CU Control Driver
// ============================================================================
class cu_driver;
    cgra_tb_config cfg;
    apb_driver     apb_drv;
    mailbox #(cu_txn) txn_out;

    function new(cgra_tb_config c, apb_driver a, mailbox #(cu_txn) mbox);
        cfg     = c;
        apb_drv = a;
        txn_out = mbox;
    endfunction

    task run(input int cycles);
        cu_txn t = new();
        t.start = 1;
        run_cgra(cycles);  // Delegate to existing task
        // Read results
        t.results[0] = read_pe_result(4'd0);
        t.execution_cycles = cycles;
        t.exit_reason = 2;  // soft_reset (run_cgra uses soft_reset to stop)
        t.timestamp = $time;
        if (txn_out != null) txn_out.put(t);
    endtask

    task set_loop(input logic [15:0] start_pc, end_pc, count);
        apb_drv.write(ADDR_LOOP_START, {16'd0, start_pc});
        apb_drv.write(ADDR_LOOP_END,   {16'd0, end_pc});
        apb_drv.write(ADDR_LOOP_COUNT, {16'd0, count});
    endtask
endclass

`endif
