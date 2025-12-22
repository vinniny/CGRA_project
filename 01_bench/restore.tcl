# ==============================================================================
# SimVision Waveform Restore Script for CGRA
# ==============================================================================
# Usage: xrun -gui -access +rwc -f flist -input restore.tcl
# ==============================================================================

# Open waveform database
database -open waves -shm

# Create waveform window
waveform new

# ==============================================================================
# Clock and Reset
# ==============================================================================
waveform add -signals tb_top.clk
waveform add -signals tb_top.rst_n

# ==============================================================================
# APB Interface (Host CPU to CGRA)
# ==============================================================================
waveform add -label "APB Interface" -comment
waveform add -signals tb_top.psel
waveform add -signals tb_top.penable
waveform add -signals tb_top.pwrite
waveform add -signals tb_top.paddr -radix hex
waveform add -signals tb_top.pwdata -radix hex
waveform add -signals tb_top.prdata -radix hex
waveform add -signals tb_top.pready
waveform add -signals tb_top.pslverr

# ==============================================================================
# DMA Engine Status
# ==============================================================================
waveform add -label "DMA Engine" -comment
waveform add -signals tb_top.u_dut.dma_start
waveform add -signals tb_top.u_dut.dma_busy
waveform add -signals tb_top.u_dut.dma_done
waveform add -signals tb_top.u_dut.dma_src -radix hex
waveform add -signals tb_top.u_dut.dma_dst -radix hex
waveform add -signals tb_top.u_dut.dma_size -radix unsigned

# ==============================================================================
# Control Unit
# ==============================================================================
waveform add -label "Control Unit" -comment
waveform add -signals tb_top.u_dut.cu_start
waveform add -signals tb_top.u_dut.cu_busy
waveform add -signals tb_top.u_dut.cu_done
waveform add -signals tb_top.u_dut.pe_enable
waveform add -signals tb_top.u_dut.u_cu.state
waveform add -signals tb_top.u_dut.u_cu.cycle_counter -radix unsigned
waveform add -signals tb_top.u_dut.context_pc -radix unsigned

# ==============================================================================
# AXI Master Interface (DMA to Memory)
# ==============================================================================
waveform add -label "AXI Interface" -comment
waveform add -signals tb_top.axi_arvalid
waveform add -signals tb_top.axi_arready
waveform add -signals tb_top.axi_araddr -radix hex
waveform add -signals tb_top.axi_rvalid
waveform add -signals tb_top.axi_rready
waveform add -signals tb_top.axi_rdata -radix hex
waveform add -signals tb_top.axi_awvalid
waveform add -signals tb_top.axi_awready
waveform add -signals tb_top.axi_awaddr -radix hex
waveform add -signals tb_top.axi_wvalid
waveform add -signals tb_top.axi_wready
waveform add -signals tb_top.axi_wdata -radix hex

# ==============================================================================
# PE Array (Sample: PE[0,0])
# ==============================================================================
waveform add -label "PE[0,0]" -comment
waveform add -signals tb_top.u_dut.u_array.u_tile_00.u_pe.enable
waveform add -signals tb_top.u_dut.u_array.u_tile_00.u_pe.op_code -radix unsigned
waveform add -signals tb_top.u_dut.u_array.u_tile_00.u_pe.operand0 -radix hex
waveform add -signals tb_top.u_dut.u_array.u_tile_00.u_pe.operand1 -radix hex
waveform add -signals tb_top.u_dut.u_array.u_tile_00.u_pe.alu_result -radix hex
waveform add -signals tb_top.u_dut.u_array.u_tile_00.u_pe.output_valid

# ==============================================================================
# Tile Memory Banks
# ==============================================================================
waveform add -label "Tile Memory" -comment
waveform add -signals tb_top.u_dut.u_tile_mem.ext_write
waveform add -signals tb_top.u_dut.u_tile_mem.ext_bank_sel -radix unsigned
waveform add -signals tb_top.u_dut.u_tile_mem.ext_addr -radix hex
waveform add -signals tb_top.u_dut.u_tile_mem.ext_wdata -radix hex

# ==============================================================================
# Zoom to fit all
# ==============================================================================
waveform zoom -fit

# Save probe database
probe -create tb_top -depth all -shm -waveform
