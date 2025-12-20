// ==============================================================================
// tb_tasks.svh - Driver Layer for CGRA Unified Testbench
// ==============================================================================
// Provides reusable tasks for:
// - APB read/write operations
// - Memory backdoor access
// - DMA transfer helpers
// - Stress injection
// - Result checking
// ==============================================================================

// =========================================================================
// APB WRITE TASK
// =========================================================================
task apb_write(input [31:0] addr, input [31:0] data);
    begin
        @(posedge clk);
        paddr <= addr;
        pwdata <= data;
        pwrite <= 1;
        psel <= 1;
        penable <= 0;
        @(posedge clk);
        penable <= 1;
        @(posedge clk);
        while (!pready) @(posedge clk);
        psel <= 0;
        penable <= 0;
        pwrite <= 0;
    end
endtask

// =========================================================================
// APB READ TASK
// =========================================================================
task apb_read(input [31:0] addr, output [31:0] data);
    begin
        @(posedge clk);
        paddr <= addr;
        pwrite <= 0;
        psel <= 1;
        penable <= 0;
        @(posedge clk);
        penable <= 1;
        @(posedge clk);
        while (!pready) @(posedge clk);
        data = prdata;
        psel <= 0;
        penable <= 0;
    end
endtask

// =========================================================================
// APB CHECK TASK (Read and Verify)
// =========================================================================
task apb_check(input [31:0] addr, input [31:0] exp, input string msg);
    reg [31:0] rd;
    begin
        apb_read(addr, rd);
        if (rd !== exp) begin
            $display("  [FAIL] %s | Addr: 0x%h | Exp: 0x%h | Got: 0x%h", msg, addr, exp, rd);
            error_count = error_count + 1;
        end else begin
            $display("  [PASS] %s", msg);
            pass_count = pass_count + 1;
        end
    end
endtask

// =========================================================================
// APB CHECK NONZERO (Verify value > 0)
// =========================================================================
task apb_check_nonzero(input [31:0] addr, input string msg);
    reg [31:0] rd;
    begin
        apb_read(addr, rd);
        if (rd > 0) begin
            $display("  [PASS] %s (value=%0d)", msg, rd);
            pass_count = pass_count + 1;
        end else begin
            $display("  [FAIL] %s | Expected nonzero, got 0", msg);
            error_count = error_count + 1;
        end
    end
endtask

// =========================================================================
// APB CHECK BIT (Verify specific bit)
// =========================================================================
task apb_check_bit(input [31:0] addr, input integer bit_pos, input logic exp_val, input string msg);
    reg [31:0] rd;
    begin
        apb_read(addr, rd);
        if (rd[bit_pos] === exp_val) begin
            $display("  [PASS] %s", msg);
            pass_count = pass_count + 1;
        end else begin
            $display("  [FAIL] %s | Bit[%0d]: Exp=%b Got=%b", msg, bit_pos, exp_val, rd[bit_pos]);
            error_count = error_count + 1;
        end
    end
endtask

// =========================================================================
// WAIT CYCLES
// =========================================================================
task wait_cycles(input integer n);
    repeat(n) @(posedge clk);
endtask

// =========================================================================
// BACKDOOR RAM WRITE (Word)
// =========================================================================
task ram_write(input [31:0] addr, input [31:0] data);
    begin
        mem[addr[16:0] + 0] = data[7:0];
        mem[addr[16:0] + 1] = data[15:8];
        mem[addr[16:0] + 2] = data[23:16];
        mem[addr[16:0] + 3] = data[31:24];
    end
endtask

// =========================================================================
// BACKDOOR RAM READ (Word)
// =========================================================================
function [31:0] ram_read(input [31:0] addr);
    begin
        ram_read = {mem[addr[16:0] + 3],
                    mem[addr[16:0] + 2],
                    mem[addr[16:0] + 1],
                    mem[addr[16:0] + 0]};
    end
endfunction

// =========================================================================
// INITIALIZE MEMORY WITH TEST PATTERN
// =========================================================================
task init_memory;
    integer i;
    begin
        // Clear all memory
        for (i = 0; i < MEM_SIZE; i = i + 1) mem[i] = 8'h00;
        
        // Load test pattern at 0x1000 (64KB sequential)
        for (i = 0; i < 65536; i = i + 1) begin
            mem[32'h1000 + i] = i[7:0];
        end
    end
endtask

// =========================================================================
// WAIT FOR DMA DONE
// =========================================================================
task wait_dma_done(input integer timeout);
    reg [31:0] status;
    integer i;
    begin
        for (i = 0; i < timeout; i = i + 1) begin
            apb_read(32'h04, status);  // DMA_STATUS
            if (status[1]) return;     // Done bit
            wait_cycles(1);
        end
        $display("  [WARN] DMA timeout after %0d cycles", timeout);
    end
endtask

// =========================================================================
// DMA TRANSFER (Convenience Wrapper)
// =========================================================================
task dma_transfer(input [31:0] src, input [31:0] dst, input [31:0] size, input integer timeout);
    begin
        apb_write(32'h08, src);   // DMA_SRC
        apb_write(32'h0C, dst);   // DMA_DST
        apb_write(32'h10, size);  // DMA_SIZE
        apb_write(32'h00, 32'h1); // DMA_CTRL = Start
        wait_dma_done(timeout);
    end
endtask

// =========================================================================
// CHECK DATA INTEGRITY
// =========================================================================
task check_data(input [31:0] src, input [31:0] dst, input [31:0] size, output logic ok);
    integer i;
    begin
        ok = 1;
        for (i = 0; i < size; i = i + 1) begin
            if (mem[dst[16:0] + i] !== mem[src[16:0] + i]) begin
                ok = 0;
            end
        end
    end
endtask

// =========================================================================
// RESULT REPORTING HELPERS
// =========================================================================
task pass(input string msg);
    begin
        $display("  [PASS] %s", msg);
        pass_count = pass_count + 1;
    end
endtask

task fail(input string msg, input string reason);
    begin
        $display("  [FAIL] %s - %s", msg, reason);
        error_count = error_count + 1;
    end
endtask

// =========================================================================
// STRESS INJECTOR
// =========================================================================
task enable_stress(input integer prob);
    begin
        stress_enable = 1;
        stress_probability = prob;
    end
endtask

task disable_stress;
    begin
        stress_enable = 0;
        stress_probability = 0;
    end
endtask
