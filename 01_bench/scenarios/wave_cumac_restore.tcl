# wave_cumac_restore.tcl — SimVision restore for the CU MAC-loop SHM.
# Focus: CU kick + LOOP/AUTO_INC registers + cu_status during 1 iteration.
#
# Usage:
#   simvision wave_cumac.shm/wave_cumac.trn -input wave_cumac_restore.tcl

database -open waves -shm
waveform new

# Clock + reset
waveform add -signals tb_wave_scenarios.clk
waveform add -signals tb_wave_scenarios.rst_n

# APB DMA preload + CU configuration writes
waveform add -signals tb_wave_scenarios.psel
waveform add -signals tb_wave_scenarios.pwrite
waveform add -signals tb_wave_scenarios.paddr
waveform add -signals tb_wave_scenarios.pwdata

# AXI4 read channel — the DMA preload phase fills tile bank 0 with
# DEADBEEF / CAFEBABE / FEEDFACE / BAADF00D before the CU runs.
waveform add -signals tb_wave_scenarios.axi_arvalid
waveform add -signals tb_wave_scenarios.axi_araddr
waveform add -signals tb_wave_scenarios.axi_rvalid
waveform add -signals tb_wave_scenarios.axi_rdata
waveform add -signals tb_wave_scenarios.axi_rlast
waveform add -signals tb_wave_scenarios.dbg_dma_busy

# CU + loop control / auto-inc registers (paths verified against cgra_apb_csr.sv)
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_cu_status
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_cu_ctrl
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_cu_pc_end
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_loop_end
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_loop_count
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_tile_auto_inc
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_spm_auto_inc

# CU busy/done from the control unit upstream of the CSR latch
waveform add -signals tb_wave_scenarios.u_dut.u_csr.cu_busy_i
waveform add -signals tb_wave_scenarios.u_dut.u_csr.cu_done_i

waveform xview limits 0ns 1600ns
