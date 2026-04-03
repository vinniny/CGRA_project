`ifndef TB_TRANSACTIONS_SVH
`define TB_TRANSACTIONS_SVH

// =============================================================================
// tb_transactions.svh — Transaction Classes (UVM-Inspired)
// =============================================================================
// Class-based containers for all DUT interactions. Used by drivers, monitors,
// and scoreboards for transaction-level verification.
// =============================================================================

// ============================================================================
// Base Transaction
// ============================================================================
class cgra_txn_base;
    static int unsigned txn_id_counter = 0;
    int unsigned txn_id;
    time         timestamp;

    function new();
        txn_id    = txn_id_counter++;
        timestamp = $time;
    endfunction

    virtual function string to_string();
        return $sformatf("[TXN#%0d @%0t]", txn_id, timestamp);
    endfunction
endclass

// ============================================================================
// APB Transaction
// ============================================================================
class apb_txn extends cgra_txn_base;
    logic [31:0] addr;
    logic [31:0] data;
    logic        is_write;
    logic        slverr;
    logic [31:0] response_data;

    function new();
        super.new();
    endfunction

    virtual function string to_string();
        if (is_write)
            return $sformatf("%s APB WR addr=0x%08h data=0x%08h",
                             super.to_string(), addr, data);
        else
            return $sformatf("%s APB RD addr=0x%08h resp=0x%08h",
                             super.to_string(), addr, response_data);
    endfunction
endclass

// ============================================================================
// DMA Transaction
// ============================================================================
typedef enum logic [1:0] {
    DMA_DDR_TO_DDR    = 2'd0,
    DMA_DDR_TO_TILE   = 2'd1,
    DMA_DDR_TO_CONFIG = 2'd2,
    DMA_TILE_TO_DDR   = 2'd3
} dma_dir_t;

class dma_txn extends cgra_txn_base;
    logic [31:0] src;
    logic [31:0] dst;
    logic [31:0] size;
    logic [31:0] src_stride;
    logic [31:0] rows;
    logic [31:0] cols;
    dma_dir_t    direction;
    logic        completed;
    logic [2:0]  error_code;
    int          cycle_count;

    function new();
        super.new();
        completed = 0;
    endfunction

    // Auto-detect direction from address prefixes
    function void set_direction();
        case ({src[31:28], dst[31:28]})
            {4'h0, 4'h0}: direction = DMA_DDR_TO_DDR;
            {4'h0, 4'h1}: direction = DMA_DDR_TO_TILE;
            {4'h0, 4'h2}: direction = DMA_DDR_TO_CONFIG;
            {4'h1, 4'h0}: direction = DMA_TILE_TO_DDR;
            default:       direction = DMA_DDR_TO_DDR;
        endcase
    endfunction

    virtual function string to_string();
        return $sformatf("%s DMA %s src=0x%08h dst=0x%08h size=%0d %s",
                         super.to_string(), direction.name(),
                         src, dst, size,
                         completed ? "DONE" : "PENDING");
    endfunction
endclass

// ============================================================================
// PE Configuration Transaction
// ============================================================================
class pe_config_txn extends cgra_txn_base;
    logic [3:0]  pe_id;
    logic [3:0]  slot;
    logic [63:0] config_word;

    function new();
        super.new();
    endfunction

    // Config frame field accessors
    function logic [5:0]  opcode();    return config_word[5:0];     endfunction
    function logic [3:0]  src0();      return config_word[9:6];     endfunction
    function logic [3:0]  src1();      return config_word[13:10];   endfunction
    function logic [3:0]  dst();       return config_word[17:14];   endfunction
    function logic [3:0]  route();     return config_word[21:18];   endfunction
    function logic [15:0] imm();       return config_word[39:24];   endfunction
    function logic [1:0]  data_mode(); return config_word[50:49];   endfunction

    virtual function string to_string();
        return $sformatf("%s PE_CFG pe=%0d slot=%0d op=%0d src0=%0d src1=%0d imm=%0d mode=%0d",
                         super.to_string(), pe_id, slot,
                         opcode(), src0(), src1(), imm(), data_mode());
    endfunction
endclass

// ============================================================================
// CU Control Transaction
// ============================================================================
class cu_txn extends cgra_txn_base;
    // Input fields (programmed before run)
    logic        start;
    logic        soft_reset;
    logic [31:0] timeout;
    logic [15:0] loop_start;
    logic [15:0] loop_end;
    logic [15:0] loop_count;
    logic [15:0] loop2_start;
    logic [15:0] loop2_end;
    logic [15:0] loop2_count;

    // Output fields (filled after completion)
    logic [1:0]  exit_reason;   // 0=auto-stop, 1=timeout, 2=soft_reset
    int          execution_cycles;
    logic [31:0] results [0:3]; // East-edge row outputs

    function new();
        super.new();
        start = 0;
        soft_reset = 0;
    endfunction

    virtual function string to_string();
        return $sformatf("%s CU_RUN cycles=%0d exit=%0d loop=%0d/%0d/%0d",
                         super.to_string(), execution_cycles, exit_reason,
                         loop_start, loop_end, loop_count);
    endfunction
endclass

// ============================================================================
// AXI Read Transaction (burst-level, captured by monitor)
// ============================================================================
class axi_read_txn extends cgra_txn_base;
    logic [31:0] addr;
    logic [7:0]  len;       // ARLEN (0 = 1 beat)
    logic [2:0]  size;      // ARSIZE
    logic [1:0]  burst;     // ARBURST
    logic [3:0]  id;        // ARID
    logic [31:0] data_beats[$];
    logic [1:0]  resp;      // RRESP (from last beat)

    function new();
        super.new();
    endfunction

    virtual function string to_string();
        return $sformatf("%s AXI_RD addr=0x%08h len=%0d beats=%0d resp=%0d",
                         super.to_string(), addr, len, data_beats.size(), resp);
    endfunction
endclass

// ============================================================================
// AXI Write Transaction (burst-level, captured by monitor)
// ============================================================================
class axi_write_txn extends cgra_txn_base;
    logic [31:0] addr;
    logic [7:0]  len;       // AWLEN
    logic [2:0]  size;      // AWSIZE
    logic [1:0]  burst;     // AWBURST
    logic [3:0]  id;        // AWID
    logic [31:0] data_beats[$];
    logic [3:0]  strb_beats[$];
    logic [1:0]  resp;      // BRESP

    function new();
        super.new();
    endfunction

    virtual function string to_string();
        return $sformatf("%s AXI_WR addr=0x%08h len=%0d beats=%0d resp=%0d",
                         super.to_string(), addr, len, data_beats.size(), resp);
    endfunction
endclass

`endif
