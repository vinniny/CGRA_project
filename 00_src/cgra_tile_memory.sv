// ==============================================================================
// CGRA Tile Memory - Row-Banked Memory Architecture
// ==============================================================================
// Provides banked memory for 4×4 PE array input data streaming.
//
// ARCHITECTURE:
//   - 4 independent banks (one per PE row)
//   - 1024 words × 32-bit per bank = 16KB total
//   - Context PC streaming: bank_addr = context_pc (0-15)
//   - DMA write via external port (ext_addr, ext_bank_sel)
//
// DATA FLOW:
//   DMA → Tile Memory (bank 0-3) → West edge of PE array
//   Bank 0 → Row 0 (PE00, PE01, PE02, PE03)
//   Bank 1 → Row 1 (PE10, PE11, PE12, PE13)
//   Bank 2 → Row 2 (PE20, PE21, PE22, PE23)
//   Bank 3 → Row 3 (PE30, PE31, PE32, PE33)
// ==============================================================================

module cgra_tile_memory #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 12,      // Address within each bank
    parameter BANK_DEPTH = 1024,    // Entries per bank
    parameter NUM_BANKS = 4         // One bank per row
)(
    input  logic clk,
    input  logic rst_n,
    
    // Bank 0 (Row 0: PE 0,0 - PE 0,3) interface
    input  logic [ADDR_WIDTH-1:0] bank0_addr,
    input  logic                  bank0_read,
    input  logic                  bank0_write,
    input  logic [DATA_WIDTH-1:0] bank0_wdata,
    output logic [DATA_WIDTH-1:0] bank0_rdata,
    output logic                  bank0_valid,
    
    // Bank 1 (Row 1: PE 1,0 - PE 1,3) interface
    input  logic [ADDR_WIDTH-1:0] bank1_addr,
    input  logic                  bank1_read,
    input  logic                  bank1_write,
    input  logic [DATA_WIDTH-1:0] bank1_wdata,
    output logic [DATA_WIDTH-1:0] bank1_rdata,
    output logic                  bank1_valid,
    
    // Bank 2 (Row 2: PE 2,0 - PE 2,3) interface
    input  logic [ADDR_WIDTH-1:0] bank2_addr,
    input  logic                  bank2_read,
    input  logic                  bank2_write,
    input  logic [DATA_WIDTH-1:0] bank2_wdata,
    output logic [DATA_WIDTH-1:0] bank2_rdata,
    output logic                  bank2_valid,
    
    // Bank 3 (Row 3: PE 3,0 - PE 3,3) interface
    input  logic [ADDR_WIDTH-1:0] bank3_addr,
    input  logic                  bank3_read,
    input  logic                  bank3_write,
    input  logic [DATA_WIDTH-1:0] bank3_wdata,
    output logic [DATA_WIDTH-1:0] bank3_rdata,
    output logic                  bank3_valid,
    
    // DMA/External access port (arbitrated)
    input  logic [ADDR_WIDTH-1:0] ext_addr,
    input  logic [1:0]            ext_bank_sel,  // Which bank to access
    input  logic                  ext_read,
    input  logic                  ext_write,
    input  logic [DATA_WIDTH-1:0] ext_wdata,
    output logic [DATA_WIDTH-1:0] ext_rdata,
    output logic                  ext_valid
);

    // =========================================================================
    // Bank 0 Memory Array
    // =========================================================================
    logic [DATA_WIDTH-1:0] bank0_mem [0:BANK_DEPTH-1];
    logic                  bank0_read_reg;  // Registered read request for valid
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            bank0_read_reg <= 1'b0;
        end else begin
            // Register the read request - valid follows read with 1-cycle delay
            bank0_read_reg <= bank0_read || (ext_read && ext_bank_sel == 2'd0);
            
            /* verilator lint_off WIDTHTRUNC */
            if (bank0_write || (ext_write && ext_bank_sel == 2'd0)) begin
                if (ext_write && ext_bank_sel == 2'd0) begin
                    bank0_mem[ext_addr[9:0]] <= ext_wdata;
                end else begin
                    bank0_mem[bank0_addr[9:0]] <= bank0_wdata;
                end
            end
            
            if (bank0_read || (ext_read && ext_bank_sel == 2'd0)) begin
                if (ext_read && ext_bank_sel == 2'd0) begin
                    bank0_rdata <= bank0_mem[ext_addr[9:0]];
                end else begin
                    bank0_rdata <= bank0_mem[bank0_addr[9:0]];
                end
            end
            /* verilator lint_on WIDTHTRUNC */
        end
    end
    
    // Valid output: asserted when we had a read request last cycle
    assign bank0_valid = bank0_read_reg;
    
    // =========================================================================
    // Bank 1 Memory Array
    // =========================================================================
    logic [DATA_WIDTH-1:0] bank1_mem [0:BANK_DEPTH-1];
    logic                  bank1_read_reg;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            bank1_read_reg <= 1'b0;
        end else begin
            bank1_read_reg <= bank1_read || (ext_read && ext_bank_sel == 2'd1);
            
            /* verilator lint_off WIDTHTRUNC */
            if (bank1_write || (ext_write && ext_bank_sel == 2'd1)) begin
                if (ext_write && ext_bank_sel == 2'd1) begin
                    bank1_mem[ext_addr[9:0]] <= ext_wdata;
                end else begin
                    bank1_mem[bank1_addr[9:0]] <= bank1_wdata;
                end
            end
            
            if (bank1_read || (ext_read && ext_bank_sel == 2'd1)) begin
                if (ext_read && ext_bank_sel == 2'd1) begin
                    bank1_rdata <= bank1_mem[ext_addr[9:0]];
                end else begin
                    bank1_rdata <= bank1_mem[bank1_addr[9:0]];
                end
            end
            /* verilator lint_on WIDTHTRUNC */
        end
    end
    
    assign bank1_valid = bank1_read_reg;
    
    // =========================================================================
    // Bank 2 Memory Array
    // =========================================================================
    logic [DATA_WIDTH-1:0] bank2_mem [0:BANK_DEPTH-1];
    logic                  bank2_read_reg;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            bank2_read_reg <= 1'b0;
        end else begin
            bank2_read_reg <= bank2_read || (ext_read && ext_bank_sel == 2'd2);
            
            /* verilator lint_off WIDTHTRUNC */
            if (bank2_write || (ext_write && ext_bank_sel == 2'd2)) begin
                if (ext_write && ext_bank_sel == 2'd2) begin
                    bank2_mem[ext_addr[9:0]] <= ext_wdata;
                end else begin
                    bank2_mem[bank2_addr[9:0]] <= bank2_wdata;
                end
            end
            
            if (bank2_read || (ext_read && ext_bank_sel == 2'd2)) begin
                if (ext_read && ext_bank_sel == 2'd2) begin
                    bank2_rdata <= bank2_mem[ext_addr[9:0]];
                end else begin
                    bank2_rdata <= bank2_mem[bank2_addr[9:0]];
                end
            end
            /* verilator lint_on WIDTHTRUNC */
        end
    end
    
    assign bank2_valid = bank2_read_reg;
    
    // =========================================================================
    // Bank 3 Memory Array
    // =========================================================================
    logic [DATA_WIDTH-1:0] bank3_mem [0:BANK_DEPTH-1];
    logic                  bank3_read_reg;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            bank3_read_reg <= 1'b0;
        end else begin
            bank3_read_reg <= bank3_read || (ext_read && ext_bank_sel == 2'd3);
            
            /* verilator lint_off WIDTHTRUNC */
            if (bank3_write || (ext_write && ext_bank_sel == 2'd3)) begin
                if (ext_write && ext_bank_sel == 2'd3) begin
                    bank3_mem[ext_addr[9:0]] <= ext_wdata;
                end else begin
                    bank3_mem[bank3_addr[9:0]] <= bank3_wdata;
                end
            end
            
            if (bank3_read || (ext_read && ext_bank_sel == 2'd3)) begin
                if (ext_read && ext_bank_sel == 2'd3) begin
                    bank3_rdata <= bank3_mem[ext_addr[9:0]];
                end else begin
                    bank3_rdata <= bank3_mem[bank3_addr[9:0]];
                end
            end
            /* verilator lint_on WIDTHTRUNC */
        end
    end
    
    assign bank3_valid = bank3_read_reg;
    
    // =========================================================================
    // External Access Multiplexing
    // =========================================================================
    logic ext_read_reg;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            ext_rdata <= {DATA_WIDTH{1'b0}};
            ext_read_reg <= 1'b0;
        end else begin
            // Register ext_read for valid timing
            ext_read_reg <= ext_read;
            
            /* verilator lint_off WIDTHTRUNC */
            if (ext_read) begin
                unique case (ext_bank_sel)
                    2'd0: ext_rdata <= bank0_mem[ext_addr[9:0]];
                    2'd1: ext_rdata <= bank1_mem[ext_addr[9:0]];
                    2'd2: ext_rdata <= bank2_mem[ext_addr[9:0]];
                    2'd3: ext_rdata <= bank3_mem[ext_addr[9:0]];
                    default: ext_rdata <= {DATA_WIDTH{1'b0}};
                endcase
            end
            /* verilator lint_on WIDTHTRUNC */
        end
    end
    
    assign ext_valid = ext_read_reg;

endmodule
