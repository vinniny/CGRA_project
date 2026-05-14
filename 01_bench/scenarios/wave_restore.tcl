# wave_restore.tcl — generic SimVision restore that works for any of the
# three SHM databases produced by tb_wave_scenarios.sv. For best
# thesis-quality screenshots, prefer the per-scenario restore scripts:
#   wave_dma_restore.tcl, wave_cumac_restore.tcl, wave_fcgroup_restore.tcl
#
# This generic script lists only the union of signals whose hierarchical
# paths have been verified to exist in cgra_top.sv (no placeholder
# entries). Signals that don't toggle in a given scenario are silently
# inactive.

database -open waves -shm
waveform new

# --- TB-level (always present) ---
waveform add -signals tb_wave_scenarios.clk
waveform add -signals tb_wave_scenarios.rst_n

# --- APB programming ---
waveform add -signals tb_wave_scenarios.psel
waveform add -signals tb_wave_scenarios.pwrite
waveform add -signals tb_wave_scenarios.paddr
waveform add -signals tb_wave_scenarios.pwdata

# --- AXI4 read channel (only the DMA scenario exercises this) ---
waveform add -signals tb_wave_scenarios.axi_arvalid
waveform add -signals tb_wave_scenarios.axi_arready
waveform add -signals tb_wave_scenarios.axi_araddr
waveform add -signals tb_wave_scenarios.axi_arlen
waveform add -signals tb_wave_scenarios.axi_rvalid
waveform add -signals tb_wave_scenarios.axi_rdata
waveform add -signals tb_wave_scenarios.axi_rlast

# --- CGRA DMA debug ---
waveform add -signals tb_wave_scenarios.dbg_dma_busy

# --- Verified CSR signal paths inside u_csr (cgra_apb_csr.sv) ---
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_cu_status
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_cu_ctrl
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_loop_count
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_tile_auto_inc
waveform add -signals tb_wave_scenarios.u_dut.u_csr.reg_spm_auto_inc
waveform add -signals tb_wave_scenarios.u_dut.u_csr.cu_busy_i
waveform add -signals tb_wave_scenarios.u_dut.u_csr.cu_done_i

# --- East-edge result FIFO (only FCGROUP scenario meaningfully toggles) ---
# Packed TB-level mirrors of the underlying unpacked array.
waveform add -signals tb_wave_scenarios.wave_result_row0
waveform add -signals tb_wave_scenarios.wave_result_row1
waveform add -signals tb_wave_scenarios.wave_result_row2
waveform add -signals tb_wave_scenarios.wave_result_row3
waveform add -signals tb_wave_scenarios.u_dut.result_fifo_pop_valid

waveform xview limits 0ns 1000ns
