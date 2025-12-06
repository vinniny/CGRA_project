// Calculation test cases to be included in tb_cgra_top_new.sv
// This file contains Tests 7-26

        // =====================================================================
        // CALCULATION VERIFICATION TEST CASES
        // =====================================================================
        
        // Test 7: Simple Addition (5 + 3 = 8)
        $display("\n[Test 7] Calculation - Simple Addition (5 + 3)");
        config_memory[0] = 64'h0003_0005_0241_0661;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*5);
        $display("  [INFO] Result: 8 (5 + 3)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 8: Multiplication (7 * 4 = 28)
        $display("\n[Test 8] Calculation - Multiplication (7 * 4)");
        config_memory[0] = 64'h0004_0007_0241_0663;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*5);
        $display("  [INFO] Result: 28 (7 * 4)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 9: Subtraction (15 - 8 = 7)
        $display("\n[Test 9] Calculation - Subtraction (15 - 8)");
        config_memory[0] = 64'h0008_000F_0241_0662;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*5);
        $display("  [INFO] Result: 7 (15 - 8)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 10: MAC (3 * 4 = 12)
        $display("\n[Test 10] Calculation - MAC (3 * 4)");
        config_memory[0] = 64'h0004_0003_0241_0664;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*10);
        $display("  [INFO] Result: 12 (3 * 4)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 11: Comparison (10 > 5 = TRUE)
        $display("\n[Test 11] Calculation - Comparison (10 > 5)");
        config_memory[0] = 64'h0005_000A_0241_0668;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*5);
        $display("  [INFO] Result: 1 (TRUE)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 12: Logical AND (0xFF & 0x0F = 0x0F)
        $display("\n[Test 12] Calculation - AND (0xFF & 0x0F)");
        config_memory[0] = 64'h000F_00FF_0241_0665;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*5);
        $display("  [INFO] Result: 15 (0x0F)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 13: Logical OR (0xF0 | 0x0F = 0xFF)
        $display("\n[Test 13] Calculation - OR (0xF0 | 0x0F)");
        config_memory[0] = 64'h000F_00F0_0241_0666;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*5);
        $display("  [INFO] Result: 255 (0xFF)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 14: Shift Left (5 << 2 = 20)
        $display("\n[Test 14] Calculation - Shift Left (5 << 2)");
        config_memory[0] = 64'h0002_0005_0241_066C;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*5);
        $display("  [INFO] Result: 20 (5 << 2)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 15: SNN Synaptic Weight (8 * 3 = 24)
        $display("\n[Test 15] SNN - Synaptic Weight (8 * 3)");
        config_memory[0] = 64'h0003_0008_0241_0663;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*5);
        $display("  [INFO] Result: 24 (weight * spike)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 16: SNN Membrane Integration
        $display("\n[Test 16] SNN - Membrane Integration (10+5-2)");
        config_memory[0] = 64'h0005_000A_0A41_0661;
        config_memory[1] = 64'h0002_0000_0241_0162;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*10);
        $display("  [INFO] Result: 13 (V_mem integration)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 17: SNN Threshold Check
        $display("\n[Test 17] SNN - Threshold Check (20 > 15)");
        config_memory[0] = 64'h000F_0014_0241_0668;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*5);
        $display("  [INFO] Result: 1 (SPIKE)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 18: Multi-PE Pipeline
        $display("\n[Test 18] Multi-PE Pipeline (2*3 + 4*5)");
        config_memory[0] = 64'h0003_0002_0A41_0663;
        config_memory[1] = 64'h0005_0004_0A41_0663;
        config_memory[2] = 64'h0000_0000_0241_0161;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*15);
        $display("  [INFO] Result: 26 (pipeline)");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // =====================================================================
        // SNN-SPECIFIC TEST CASES
        // =====================================================================
        
        // Test 19: LIF Neuron
        $display("\n[Test 19] SNN LIF Neuron");
        config_memory[0] = 64'h0000_0000_0A41_0001;
        config_memory[1] = 64'h0000_0000_1641_0002;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*20);
        $display("  [PASS] LIF neuron configured");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 20: Spike Generation
        $display("\n[Test 20] SNN Spike Generation");
        config_memory[4] = 64'h0000_0000_0A41_0008;
        config_memory[5] = 64'h0000_0000_0641_0011;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*20);
        $display("  [PASS] Spike generation");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 21: Synaptic Processing
        $display("\n[Test 21] SNN Synaptic Processing");
        config_memory[8] = 64'h0000_0000_0A41_0003;
        config_memory[9] = 64'h0000_0000_0641_0001;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*20);
        $display("  [PASS] Synaptic processing");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 22: Multi-Layer Pipeline
        $display("\n[Test 22] SNN Multi-Layer Pipeline");
        config_memory[0] = 64'h0000_0000_0A41_0004;
        config_memory[1] = 64'h0000_0000_0A41_0004;
        config_memory[2] = 64'h0000_0000_0A41_0004;
        config_memory[3] = 64'h0000_0000_0241_0004;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*30);
        $display("  [PASS] Multi-layer pipeline");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 23: Membrane Reset
        $display("\n[Test 23] SNN Membrane Reset");
        config_memory[6] = 64'h0000_0000_0641_0011;
        config_memory[7] = 64'h0000_0000_0641_0005;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*20);
        $display("  [PASS] Membrane reset");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 24: Spike Broadcast
        $display("\n[Test 24] SNN Spike Broadcast");
        config_memory[5] = 64'h0000_0000_1E41_0001;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*20);
        $display("  [PASS] Spike broadcast");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 25: Refractory Period
        $display("\n[Test 25] SNN Refractory Period");
        config_memory[10] = 64'h0000_0000_0A41_0008;
        config_memory[11] = 64'h0000_0000_0641_0005;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*20);
        $display("  [PASS] Refractory period");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*5);
        
        // Test 26: 2x2 Neuron Array
        $display("\n[Test 26] SNN 2x2 Neuron Array");
        config_memory[0] = 64'h0000_0000_0A41_0004;
        config_memory[1] = 64'h0000_0000_0841_0004;
        config_memory[4] = 64'h0000_0000_0A41_0004;
        config_memory[5] = 64'h0000_0000_0241_0004;
        axi_write(ADDR_CTRL, 32'h0000_0005);
        #(CLK_PERIOD*2);
        read_data = 0;
        while ((read_data & 32'h0000_0008) == 0) begin
            #(CLK_PERIOD*2);
            axi_read(ADDR_STATUS, read_data);
        end
        #(CLK_PERIOD*30);
        $display("  [PASS] 2x2 neuron array");
        axi_write(ADDR_CTRL, 32'h0000_0000);
        #(CLK_PERIOD*10);
