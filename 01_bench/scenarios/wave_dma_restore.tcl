# wave_dma_restore.tcl — SimVision restore for the DMA-burst SHM.
# Shows only signals that toggle in this scenario.
#
# Usage:
#   simvision wave_dma.shm/wave_dma.trn -input wave_dma_restore.tcl

database -open waves -shm
waveform new

# Clock + reset
waveform add -signals tb_wave_scenarios.clk
waveform add -signals tb_wave_scenarios.rst_n

# APB DMA programming (4 writes: SRC, DST, SIZE, CTRL)
waveform add -signals tb_wave_scenarios.psel
waveform add -signals tb_wave_scenarios.pwrite
waveform add -signals tb_wave_scenarios.paddr
waveform add -signals tb_wave_scenarios.pwdata

# AXI4 read channel — the heart of the DMA waveform
waveform add -signals tb_wave_scenarios.axi_arvalid
waveform add -signals tb_wave_scenarios.axi_arready
waveform add -signals tb_wave_scenarios.axi_araddr
waveform add -signals tb_wave_scenarios.axi_arlen
waveform add -signals tb_wave_scenarios.axi_rvalid
waveform add -signals tb_wave_scenarios.axi_rdata
waveform add -signals tb_wave_scenarios.axi_rlast

# CGRA-internal DMA busy
waveform add -signals tb_wave_scenarios.dbg_dma_busy

waveform xview limits 0ns 1000ns
