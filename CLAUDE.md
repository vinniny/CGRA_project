# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

4x4 CGRA (Coarse-Grained Reconfigurable Array) accelerator IP for Sparse Spiking Neural Networks (SNN) and License Plate Recognition (LPR) inference. Targets Xilinx Zynq-7000 (XC7Z020) at 50 MHz with PetaLinux 2022.2 deployment. All RTL is SystemVerilog. Simulation uses Cadence Xcelium 20.09.

## Build & Simulation Commands

```bash
make sim                # Full simulation flow (compile + elaborate + run, 8915 tests)
make compile            # xmvlog compilation only
make build              # xmelab elaboration only
make run                # xmsim simulation only
make gui                # Interactive SimVision waveform debugging
make lint               # Xcelium lint checks
SEED=12345 make sim     # Run with custom random seed
make cov                # Simulate with coverage collection (COV=1)
make cov_report         # Generate text coverage summary
make cov_gui            # Open SimVision with coverage database
make syn                # Genus synthesis (scripts/genus_syn.tcl)
make lec                # Conformal LEC (scripts/conformal_lec.tcl)
make full               # Complete flow: sim + syn + lec
make clean              # Remove simulation/synthesis artifacts
```

Software (07_sw/):
```bash
cd 07_sw && make all                              # Native build
cd 07_sw && make CROSS=arm-linux-gnueabihf- all   # ARM cross-compile for Zynq
cd 07_sw && make test                             # Golden model tests
cd 07_sw && make dump_hex                         # Generate .mem files for Suite RAP
```

## Directory Layout

- **00_src/** — RTL sources (SystemVerilog). Core modules: cgra_top, cgra_pe, cgra_router, cgra_array (parameterized N*M), cgra_dma_engine, cgra_control_unit, cgra_apb_csr, cgra_tile_memory, cgra_tile. Uses BSG memory library (bsg_mem/).
- **01_bench/** — Testbench. tb_top.sv is the top-level. `include/` has layered components: tb_defs.svh (macros, address map, opcodes), tb_tasks.svh (APB/AXI/DMA driver tasks + clocking-block variants), tb_scenario_gen.svh (constrained-random classes + generators), tb_coverage.svh (4 covergroups + manual counters), tb_protocol_checkers.svh (AXI4/APB monitors), and 20+ test suite files (tb_suite_*.svh, tb_isa_regression.svh, tb_test_suites.svh).
- **02_log/** — Simulation logs (compile.log, elaborate.log, sim.log)
- **03_sim/** — Xcelium working directory (generated)
- **04_syn/** — Synthesis outputs (Genus)
- **05_lec/** — Logical equivalence check outputs (Conformal)
- **06_doc/** — Thesis documentation (LaTeX)
- **07_sw/** — C software: driver/ (UIO+CMA+devmem Linux driver), lib/ (cgra_tiler for im2col/convolution tiling, lpr_golden model), app/ (lpr_demo, lpr_cgra_accel, lpr_live_demo, test_tiler, dump_cgra_hex)
- **scripts/** — TCL scripts for synthesis and LEC

## Architecture

```
Host CPU (APB) -> APB CSR (28 regs) -> Control Unit (IDLE->RUN->FINISH FSM, nested loops, timeout)
                                     -> DMA Engine (AXI4 master, 32-word FIFO, 2D strided) <-> AXI RAM
                                     -> Tile Memory (4 banks * 4096 * 32b, double-buffered)
                                     -> 4x4 PE Array (parameterized mesh, broadcast routing)
```

Each PE contains: Config RAM (16x64b multi-context BSG SRAM), Register File (16x32b), Scratchpad (256x32b SRAM), ALU/MAC (40-bit saturating accumulator, 3-stage pipeline: decode→_r→_r2), 5-port Router (N/E/S/W/Local, unicast/multicast).

**ISA (21 ops):** ADD, SUB, MUL, MAC, AND, OR, XOR, SHL, SHR, CMP_GT, CMP_LT, CMP_EQ, LOAD_SPM, STORE_SPM, ACC_CLR, PASS0, PASS1, NOP, LIF (neuromorphic), RELU, MAX.

**Extensions:** Mixed-precision INT8x4 / INT16x2 SIMD (config bits [50:49]), dynamic branching from PE predicate to CU PC (config bits [48:44]), nested hardware loops (2 levels).

**Key parameters:** DATA_WIDTH=32, CONFIG_WIDTH=64, CONTEXT_DEPTH=16, NUM_PES=16 (4x4), FIFO_DEPTH=32, BANK_DEPTH=4096.

## APB Register Map (28 registers, 0x00-0x74)

DMA: DMA_CTRL(0x00 RW), DMA_STATUS(0x04 RO), DMA_SRC(0x08 RW), DMA_DST(0x0C RW), DMA_SIZE(0x10 RW), DMA_SRC_STRIDE(0x14 RW), DMA_ROWS(0x18 RW), DMA_COLS(0x1C RW).
CU: CU_CTRL(0x20 RW), CU_STATUS(0x24 RO), CU_CYCLES(0x28 RO), CU_TIMEOUT(0x2C RW).
IRQ: IRQ_STATUS(0x30 W1C — [0] DMA Done, [1] CU Done, [2] DMA Error), IRQ_MASK(0x34 RW).
Result: RESULT_DATA(0x40 RO), RESULT_STATUS(0x44 RO).
Loop L1: LOOP_START(0x48 RW), LOOP_END(0x4C RW), LOOP_COUNT(0x50 RW).
Row Results: RESULT_ROW0-3(0x58-0x64 RO).
Loop L2: LOOP2_START(0x68 RW), LOOP2_END(0x6C RW), LOOP2_COUNT(0x70 RW).
Double-Buffer: TILE_BANK_SEL(0x74 RW).

Error: DMA_ERROR(0x38 RO) — [0] error_flag, [2:1] error_code (W1C via IRQ_STATUS[2]).

Protected registers: DMA_SRC/DST/SIZE/STRIDE/ROWS/COLS rejected while DMA busy. CU_TIMEOUT/LOOP*/LOOP2* rejected while CU busy. TILE_BANK_SEL rejected while DMA or CU busy. DMA_CTRL[0] and CU_CTRL[0] auto-clear after 1 cycle.

## Testbench Architecture

5-layer modular TB with 25 test suites, 8915 tests + UVM-inspired transaction layer:
- Layer 1: tb_defs.svh — macros, constants, assertion helpers (CHECK_EQ, ASSERT_TRUE, etc.)
- Layer 2: tb_scenario_gen.svh — constrained-random classes (cgra_dma_stim, cgra_pe_stim, cgra_apb_stim) + sequence base classes
- Layer 3: tb_tasks.svh — APB/DMA/PE driver tasks + clocking-block variants (apb_cb_write/read)
- Layer 4: tb_coverage.svh — 4 covergroups (DMA xfer, PE ISA, CU flow, APB regs) + manual counters
- Layer 5: Protocol checkers + 24 test suites
- Layer 6 (UVM-inspired): tb_transactions.svh, tb_config.svh, tb_drivers.svh, tb_monitors.svh, tb_scoreboard.svh, tb_agents.svh, tb_env.svh — class-based verification infrastructure with APB/AXI monitors, DMA/PE scoreboards (21-opcode golden ALU + SIMD), mailbox-connected agents

Clocking blocks: `apb_cb` (drive #1, sample #1step), `axi_cb` (sample-only). Watchdog: TB_WATCHDOG_NS (100ms default). Error threshold: MAX_ERRORS (50 default). Verbosity: +define+TB_VERBOSE or +VERBOSITY=N plusarg.

## Makefile Variables

- `SEED` — Random seed for simulation (default: auto-generated)
- `TEST_ITERS` — Number of test iterations
- `CYCLES` — Simulation cycle limit
- `CORE` — Parallel compilation jobs
- `COV` — Enable coverage (COV=1)
- `COV_TEST` — Coverage test name (default: full_sim)
