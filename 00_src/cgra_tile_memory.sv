// ==============================================================================
// CGRA Tile Memory - Row-Banked Memory Architecture
// ==============================================================================
// Provides banked memory organization for 4×4 PE array
// Features:
// - 4 independent banks (one per PE row)
// - Parallel access to different rows
// - Configurable depth per bank
// - Support for both PE local access and DMA transfers

module cgra_tile_memory #(
    parameter DATA_WIDTH = 16,
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
    logic                  bank0_valid_reg;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            bank0_valid_reg <= 1'b0;
        end else begin
            if (bank0_write || (ext_write && ext_bank_sel == 2'd0)) begin
                if (ext_write && ext_bank_sel == 2'd0) begin
                    bank0_mem[ext_addr] <= ext_wdata;
                end else begin
                    bank0_mem[bank0_addr] <= bank0_wdata;
                end
            end
            
            if (bank0_read || (ext_read && ext_bank_sel == 2'd0)) begin
                if (ext_read && ext_bank_sel == 2'd0) begin
                    bank0_rdata <= bank0_mem[ext_addr];
                end else begin
                    bank0_rdata <= bank0_mem[bank0_addr];
                end
                bank0_valid_reg <= 1'b1;
            end else begin
                bank0_valid_reg <= 1'b0;
            end
        end
    end
    
    always_comb begin
        bank0_valid = bank0_valid_reg;
    end
    
    // =========================================================================
    // Bank 1 Memory Array
    // =========================================================================
    logic [DATA_WIDTH-1:0] bank1_mem [0:BANK_DEPTH-1];
    logic                  bank1_valid_reg;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            bank1_valid_reg <= 1'b0;
        end else begin
            if (bank1_write || (ext_write && ext_bank_sel == 2'd1)) begin
                if (ext_write && ext_bank_sel == 2'd1) begin
                    bank1_mem[ext_addr] <= ext_wdata;
                end else begin
                    bank1_mem[bank1_addr] <= bank1_wdata;
                end
            end
            
            if (bank1_read || (ext_read && ext_bank_sel == 2'd1)) begin
                if (ext_read && ext_bank_sel == 2'd1) begin
                    bank1_rdata <= bank1_mem[ext_addr];
                end else begin
                    bank1_rdata <= bank1_mem[bank1_addr];
                end
                bank1_valid_reg <= 1'b1;
            end else begin
                bank1_valid_reg <= 1'b0;
            end
        end
    end
    
    always_comb begin
        bank1_valid = bank1_valid_reg;
    end
    
    // =========================================================================
    // Bank 2 Memory Array
    // =========================================================================
    logic [DATA_WIDTH-1:0] bank2_mem [0:BANK_DEPTH-1];
    logic                  bank2_valid_reg;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            bank2_valid_reg <= 1'b0;
        end else begin
            if (bank2_write || (ext_write && ext_bank_sel == 2'd2)) begin
                if (ext_write && ext_bank_sel == 2'd2) begin
                    bank2_mem[ext_addr] <= ext_wdata;
                end else begin
                    bank2_mem[bank2_addr] <= bank2_wdata;
                end
            end
            
            if (bank2_read || (ext_read && ext_bank_sel == 2'd2)) begin
                if (ext_read && ext_bank_sel == 2'd2) begin
                    bank2_rdata <= bank2_mem[ext_addr];
                end else begin
                    bank2_rdata <= bank2_mem[bank2_addr];
                end
                bank2_valid_reg <= 1'b1;
            end else begin
                bank2_valid_reg <= 1'b0;
            end
        end
    end
    
    always_comb begin
        bank2_valid = bank2_valid_reg;
    end
    
    // =========================================================================
    // Bank 3 Memory Array
    // =========================================================================
    logic [DATA_WIDTH-1:0] bank3_mem [0:BANK_DEPTH-1];
    logic                  bank3_valid_reg;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            bank3_valid_reg <= 1'b0;
        end else begin
            if (bank3_write || (ext_write && ext_bank_sel == 2'd3)) begin
                if (ext_write && ext_bank_sel == 2'd3) begin
                    bank3_mem[ext_addr] <= ext_wdata;
                end else begin
                    bank3_mem[bank3_addr] <= bank3_wdata;
                end
            end
            
            if (bank3_read || (ext_read && ext_bank_sel == 2'd3)) begin
                if (ext_read && ext_bank_sel == 2'd3) begin
                    bank3_rdata <= bank3_mem[ext_addr];
                end else begin
                    bank3_rdata <= bank3_mem[bank3_addr];
                end
                bank3_valid_reg <= 1'b1;
            end else begin
                bank3_valid_reg <= 1'b0;
            end
        end
    end
    
    always_comb begin
        bank3_valid = bank3_valid_reg;
    end
    
    // =========================================================================
    // External Access Multiplexing
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            ext_rdata <= 16'd0;
            ext_valid <= 1'b0;
        end else begin
            if (ext_read) begin
                case (ext_bank_sel)
                    2'd0: begin
                        ext_rdata <= bank0_mem[ext_addr];
                        ext_valid <= 1'b1;
                    end
                    2'd1: begin
                        ext_rdata <= bank1_mem[ext_addr];
                        ext_valid <= 1'b1;
                    end
                    2'd2: begin
                        ext_rdata <= bank2_mem[ext_addr];
                        ext_valid <= 1'b1;
                    end
                    2'd3: begin
                        ext_rdata <= bank3_mem[ext_addr];
                        ext_valid <= 1'b1;
                    end
                    default: begin
                        ext_rdata <= 16'd0;
                        ext_valid <= 1'b0;
                    end
                endcase
            end else begin
                ext_valid <= 1'b0;
            end
        end
    end

endmodule
