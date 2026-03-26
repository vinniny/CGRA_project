# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

4×4 CGRA (Coarse-Grained Reconfigurable Array) accelerator IP for Sparse Spiking Neural Networks (SNN) and License Plate Recognition (LPR) inference. Silicon-ready at 213.72 MHz on Xilinx Zynq UltraScale+ (XCZU4EV). All RTL is SystemVerilog. Simulation uses Cadence Xcelium.

## Build & Simulation Commands

```bash
make sim                # Full simulation flow (compile + elaborate + run, 6163 tests)
make compile            # xmvlog compilation only
make build              # xmelab elaboration only
make run                # xmsim simulation only
make gui                # Interactive SimVision waveform debugging
make lint               # Xcelium lint checks
make lab_test           # Sanity + Advanced + Benchmark + Stress test suites
SEED=12345 make test    # Run with custom random seed
make syn                # Genus synthesis (scripts/genus_syn.tcl)
make lec                # Conformal LEC (scripts/conformal_lec.tcl)
make full               # Complete flow: sim + syn + lec
make clean              # Remove simulation/synthesis artifacts
```

Software (07_sw/):
```bash
cd 07_sw && make all                              # Native build
cd 07_sw && make CROSS=arm-linux-gnueabihf- all   # ARM cross-compile for PYNQ-Z2
cd 07_sw && make test                             # Tiler unit tests
```

## Directory Layout

- **00_src/** — RTL sources (SystemVerilog). Core modules: cgra_top, cgra_pe, cgra_router, cgra_array_4x4, cgra_dma_engine, cgra_control_unit, cgra_apb_csr, cgra_tile_memory, cgra_tile. Uses BSG memory library (bsg_mem/).
- **01_bench/** — Testbench. tb_top.sv is the top-level. `include/` has layered components: tb_defs.svh (macros, address map, opcodes), tb_tasks.svh (APB/AXI/DMA driver tasks), tb_scenario_gen.svh (random generators), tb_protocol_checkers.svh (AXI4/APB monitors), tb_test_suites.svh (32 test suites). Specialized suites: tb_isa_regression.svh, tb_suite_dma_writeback.svh, tb_suite_fabric.svh, tb_suite_robustness.svh, tb_suite_lpr.svh.
- **02_log/** — Simulation logs (compile.log, elaborate.log, sim.log)
- **03_sim/** — Xcelium working directory (generated)
- **04_syn/** — Synthesis outputs (Genus)
- **05_lec/** — Logical equivalence check outputs (Conformal)
- **06_doc/** — Thesis documentation (LaTeX)
- **07_sw/** — C software: driver/ (UIO+CMA Linux driver), lib/ (cgra_tiler for im2col/convolution tiling), app/ (lpr_demo, test_tiler)
- **scripts/** — TCL scripts for synthesis and LEC

## Architecture

```
Host CPU (APB) → APB CSR (20 regs) → Control Unit (IDLE→RUN→FINISH FSM)
                                    → DMA Engine (AXI4 master, 8-word FIFO) ↔ AXI RAM
                                    → Tile Memory (4 banks × 1024 × 32b, one per row)
                                    → 4×4 PE Array (mesh with broadcast routing)
```

Each PE contains: Config RAM (16×64b multi-context), Register File (16×32b), Scratchpad (256×32b SRAM), ALU/MAC (40-bit saturating accumulator), 5-port Router (N/E/S/W/Local, unicast/multicast).

**ISA (21 ops):** ADD, SUB, MUL, MAC, AND, OR, XOR, SHL, SHR, CMP_GT, CMP_LT, CMP_EQ, LOAD_SPM, STORE_SPM, ACC_CLR, PASS0, PASS1, NOP, LIF (neuromorphic), RELU, MAX.

**Key parameters:** DATA_WIDTH=32, CONFIG_WIDTH=64, CONTEXT_DEPTH=16, NUM_PES=16 (4×4).

## Testbench Conventions

- Assertion macros defined in tb_defs.svh: `ASSERT_TRUE`, `ASSERT_FATAL`, `CHECK`, `CHECK_EQ`, etc.
- APB register addresses defined as constants in tb_defs.svh (e.g., `ADDR_DMA_CTRL`, `ADDR_CU_CTRL`).
- PE opcodes defined as constants (e.g., `OP_ADD`, `OP_LIF`, `OP_RELU`).
- All test tasks use `log_test_result` for uniform pass/fail tracking.
- Protocol checkers guarded by `protocol_check_enable` flag.
- Watchdog timer (100ms default) prevents infinite simulation hangs.
- Verbosity: compile with `+define+TB_VERBOSE` for detailed output.

## Makefile Variables

- `SEED` — Random seed for simulation (default: auto-generated)
- `TEST_ITERS` — Number of test iterations
- `CYCLES` — Simulation cycle limit
- `CORE` — Parallel compilation jobs
