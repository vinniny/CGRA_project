# CGRA_opencores — OpenCores Integration Notes

11 archives from OpenCores. Extracted to `extracted/`. One module integrated into the
testbench; the rest are RTL reference material.

## Integrated into testbench

| Archive | Module | Where used |
|---|---|---|
| `myhdl_lfsr_latest.tar.gz` | `lfsr_32.v` (sample_modules/verilog/) | `01_bench/lfsr_32.v` — 3 instances replace `$urandom_range` in AXI BFM ARREADY/AWREADY/WREADY. Seeds: AR=0x1ACA3107, AW=0xDEADBEEF, W=0xC0FFEE42. Backpressure patterns are now deterministic (SEED-independent). |

New test suite: `01_bench/include/tb_suite_opencores_dma.svh` — 3 DMA integrity tests under backpressure (OC01: no stress, OC02: 50%, OC03: 75% 2D).

## RTL reference (extracted, not compiled)

| Archive | Language | What it is |
|---|---|---|
| `adder_tree_latest.tar.gz` | Verilog/SV | Parameterizable tree adder — reference for PE MAC adder design |
| `ddr3_synthesizable_bfm_latest.tar.gz` | Verilog | DDR3 synthesizable BFM — reference; AXI abstraction is correct level for this TB |
| `fixed_point_arithmetic_parameterized_latest.tar.gz` | Verilog | Q,N fixed-point (add/mul/div) — reference for PE ops |
| `verilog_fixed_point_math_library_latest.tar.gz` | Verilog | Parameterized fixed-point math — reference for PE |
| `pipelined_fixed_point_elementary_functions_latest.tar.gz` | SV | Pipelined sin/cos/exp/sqrt — reference for PE |
| `uart_fifo_cpu_if_sv_testbench_latest.tar.gz` | VHDL RTL + SV TB | UART SV testbench pattern reference; UART not simulated in CGRA TB |
| `multiply-accumulate_latest.tar.gz` | VHDL | MAC unit — VHDL only |
| `rng_lib_latest.tar.gz` | VHDL | RNG library — VHDL only |
| `simu_mem_latest.tar.gz` | VHDL + Verilog | SRAM/ZBT models — wrong interface level for this TB |
| `hls_dma_latest.tar.gz` | VHDL + C++ HLS | HLS DMA — requires Vivado HLS toolchain |
