// ==============================================================================
// Testbench for CGRA Configuration Loader
// ==============================================================================

`timescale 1ns/1ps

module tb_cgra_config_loader;

    // Parameters
    localparam CONFIG_WIDTH = 64;
    localparam ADDR_WIDTH = 32;
    localparam CLK_PERIOD = 10;
    
    // DUT signals
    logic clk;
    logic rst_n;
    logic                  start_load;
    logic [ADDR_WIDTH-1:0] bitstream_addr;
    logic [15:0]           bitstream_size;
    logic                  load_done;
    logic                  load_error;
    logic                  swap_context;
    logic                  active_buffer;
    logic [ADDR_WIDTH-1:0] mem_addr;
    logic                  mem_read;
    logic [CONFIG_WIDTH-1:0] mem_rdata;
    logic                  mem_valid;
    
    logic [CONFIG_WIDTH-1:0] config_frame_00, config_frame_01, config_frame_02, config_frame_03;
    logic [CONFIG_WIDTH-1:0] config_frame_10, config_frame_11, config_frame_12, config_frame_13;
    logic [CONFIG_WIDTH-1:0] config_frame_20, config_frame_21, config_frame_22, config_frame_23;
    logic [CONFIG_WIDTH-1:0] config_frame_30, config_frame_31, config_frame_32, config_frame_33;
    logic                   config_valid;
    
    // Memory model
    logic [CONFIG_WIDTH-1:0] mem_array [0:1023];
    
    // DUT instantiation
    cgra_config_loader #(
        .NUM_PES(16),
        .CONFIG_WIDTH(CONFIG_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .MAX_FRAMES(1024)
    ) dut (
        .clk(clk),
        .rst_n(rst_n),
        .start_load(start_load),
        .bitstream_addr(bitstream_addr),
        .bitstream_size(bitstream_size),
        .load_done(load_done),
        .load_error(load_error),
        .swap_context(swap_context),
        .active_buffer(active_buffer),
        .mem_addr(mem_addr),
        .mem_read(mem_read),
        .mem_rdata(mem_rdata),
        .mem_valid(mem_valid),
        .config_frame_00(config_frame_00),
        .config_frame_01(config_frame_01),
        .config_frame_02(config_frame_02),
        .config_frame_03(config_frame_03),
        .config_frame_10(config_frame_10),
        .config_frame_11(config_frame_11),
        .config_frame_12(config_frame_12),
        .config_frame_13(config_frame_13),
        .config_frame_20(config_frame_20),
        .config_frame_21(config_frame_21),
        .config_frame_22(config_frame_22),
        .config_frame_23(config_frame_23),
        .config_frame_30(config_frame_30),
        .config_frame_31(config_frame_31),
        .config_frame_32(config_frame_32),
        .config_frame_33(config_frame_33),
        .config_valid(config_valid)
    );
    
    // Clock generation
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end
    
    // Memory model - responds to read requests
    always_ff @(posedge clk) begin
        if (mem_read) begin
            mem_rdata <= mem_array[mem_addr];
            mem_valid <= 1'b1;
        end else begin
            mem_valid <= 1'b0;
        end
    end
    
    // Test stimulus
    initial begin
        $display("======================================");
        $display("  Config Loader Testbench Started");
        $display("======================================");
        
        // Initialize memory with test patterns
        mem_array[0] = 64'hAAAA_AAAA_AAAA_0000;
        mem_array[1] = 64'hAAAA_AAAA_AAAA_0001;
        mem_array[2] = 64'hAAAA_AAAA_AAAA_0002;
        mem_array[3] = 64'hAAAA_AAAA_AAAA_0003;
        mem_array[4] = 64'hAAAA_AAAA_AAAA_0010;
        mem_array[5] = 64'hAAAA_AAAA_AAAA_0011;
        mem_array[6] = 64'hAAAA_AAAA_AAAA_0012;
        mem_array[7] = 64'hAAAA_AAAA_AAAA_0013;
        mem_array[8] = 64'hAAAA_AAAA_AAAA_0020;
        mem_array[9] = 64'hAAAA_AAAA_AAAA_0021;
        mem_array[10] = 64'hAAAA_AAAA_AAAA_0022;
        mem_array[11] = 64'hAAAA_AAAA_AAAA_0023;
        mem_array[12] = 64'hAAAA_AAAA_AAAA_0030;
        mem_array[13] = 64'hAAAA_AAAA_AAAA_0031;
        mem_array[14] = 64'hAAAA_AAAA_AAAA_0032;
        mem_array[15] = 64'hAAAA_AAAA_AAAA_0033;
        
        // Second configuration for context swap test
        mem_array[100] = 64'hBBBB_BBBB_BBBB_0000;
        mem_array[101] = 64'hBBBB_BBBB_BBBB_0001;
        mem_array[102] = 64'hBBBB_BBBB_BBBB_0002;
        mem_array[103] = 64'hBBBB_BBBB_BBBB_0003;
        mem_array[104] = 64'hBBBB_BBBB_BBBB_0010;
        mem_array[105] = 64'hBBBB_BBBB_BBBB_0011;
        mem_array[106] = 64'hBBBB_BBBB_BBBB_0012;
        mem_array[107] = 64'hBBBB_BBBB_BBBB_0013;
        mem_array[108] = 64'hBBBB_BBBB_BBBB_0020;
        mem_array[109] = 64'hBBBB_BBBB_BBBB_0021;
        mem_array[110] = 64'hBBBB_BBBB_BBBB_0022;
        mem_array[111] = 64'hBBBB_BBBB_BBBB_0023;
        mem_array[112] = 64'hBBBB_BBBB_BBBB_0030;
        mem_array[113] = 64'hBBBB_BBBB_BBBB_0031;
        mem_array[114] = 64'hBBBB_BBBB_BBBB_0032;
        mem_array[115] = 64'hBBBB_BBBB_BBBB_0033;
        
        // Initialize
        rst_n = 0;
        start_load = 0;
        bitstream_addr = 0;
        bitstream_size = 0;
        swap_context = 0;
        
        #(CLK_PERIOD*5);
        rst_n = 1;
        #(CLK_PERIOD*2);
        
        // Test 1: Load first configuration
        $display("\n[TEST 1] Load first configuration");
        bitstream_addr = 32'd0;
        bitstream_size = 16'd16;
        start_load = 1;
        #(CLK_PERIOD);
        start_load = 0;
        
        // Wait for load to complete
        wait(load_done);
        $display("  Load complete!");
        $display("  Active buffer = %0d", active_buffer);
        $display("  Config_frame_00 = 0x%016h", config_frame_00);
        $display("  Config_frame_15 = 0x%016h", config_frame_33);
        #(CLK_PERIOD*5);
        
        // Test 2: Context swap
        $display("\n[TEST 2] Context swap test");
        $display("  Before swap - Active buffer = %0d", active_buffer);
        swap_context = 1;
        #(CLK_PERIOD);
        swap_context = 0;
        #(CLK_PERIOD);
        $display("  After swap - Active buffer = %0d", active_buffer);
        #(CLK_PERIOD*5);
        
        // Test 3: Load second configuration to other buffer
        $display("\n[TEST 3] Load second configuration");
        bitstream_addr = 32'd100;
        bitstream_size = 16'd16;
        start_load = 1;
        #(CLK_PERIOD);
        start_load = 0;
        
        wait(load_done);
        $display("  Second config loaded!");
        $display("  Active buffer still = %0d", active_buffer);
        #(CLK_PERIOD*5);
        
        // Test 4: Swap to new configuration
        $display("\n[TEST 4] Swap to new configuration");
        swap_context = 1;
        #(CLK_PERIOD);
        swap_context = 0;
        #(CLK_PERIOD);
        $display("  Swapped! Active buffer = %0d", active_buffer);
        $display("  Config_frame_00 = 0x%016h", config_frame_00);
        #(CLK_PERIOD*5);
        
        #(CLK_PERIOD*10);
        $display("\n======================================");
        $display("  Config Loader Testbench Completed");
        $display("======================================\n");
        $finish;
    end
    
    // Monitor
    initial begin
        $monitor("Time=%0t | State=%0d | Load_done=%b | Active_buf=%0d | Config_valid=%b",
                 $time, dut.state, load_done, active_buffer, config_valid);
    end

endmodule
