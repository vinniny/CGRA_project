# wave_fcgroup_restore.tcl — SimVision restore for the east-readout SHM.
# Focus: brief CU pulse + the result FIFO populating row outputs.
#
# Usage:
#   simvision wave_fcgroup.shm/wave_fcgroup.trn -input wave_fcgroup_restore.tcl

database -open waves -shm
waveform new

# Clock + reset
waveform add -signals tb_wave_scenarios.clk
waveform add -signals tb_wave_scenarios.rst_n

# APB writes — DMA preload + MAC kick + readout pulse
waveform add -signals tb_wave_scenarios.psel
waveform add -signals tb_wave_scenarios.pwrite
waveform add -signals tb_wave_scenarios.paddr
waveform add -signals tb_wave_scenarios.pwdata

# AXI4 read channel — the DMA preload phase fills tile bank 0 with
# DEADBEEF / CAFEBABE / FEEDFACE / BAADF00D before the MAC runs.
waveform add -signals tb_wave_scenarios.axi_arvalid
waveform add -signals tb_wave_scenarios.axi_araddr
waveform add -signals tb_wave_scenarios.axi_rvalid
waveform add -signals tb_wave_scenarios.axi_rdata
waveform add -signals tb_wave_scenarios.axi_rlast
waveform add -signals tb_wave_scenarios.dbg_dma_busy

# CU status + ctrl during the pulse
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_cu_status
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_cu_ctrl
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_cu_pc_end
waveform add -signals tb_wave_scenarios.u_dut.u_csr.cu_busy_i
waveform add -signals tb_wave_scenarios.u_dut.u_csr.cu_done_i

# East-edge result FIFO — four row outputs, mirrored from the unpacked
# array u_dut.result_fifo_pop_data[0..3] into TB-level packed wires so
# they probe cleanly under $shm_probe("AS") with no bracket gymnastics.
waveform add -signals tb_wave_scenarios.wave_result_row0
waveform add -signals tb_wave_scenarios.wave_result_row1
waveform add -signals tb_wave_scenarios.wave_result_row2
waveform add -signals tb_wave_scenarios.wave_result_row3
waveform add -signals tb_wave_scenarios.u_dut.result_fifo_pop_valid
waveform add -signals tb_wave_scenarios.u_dut.result_fifo_count

waveform xview limits 0ns 1800ns
