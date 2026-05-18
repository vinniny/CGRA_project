# Chapter 5 — Results and Evaluation (LaTeX)

Standalone LaTeX project that builds the Results and Evaluation
chapter of the graduation thesis. Same package set and style as
Chapter 4; placeholders (`[XX]%`, `[X.XX] ms`, etc.) mark numerical
values to be filled in from the user's Vivado reports and silicon
measurements.

## Files

| File | Role |
|---|---|
| `main.tex` | Standalone wrapper. `\maketitle`, ToC, then `\input{chapter5}`. Renumbers counters to 5.1, 5.2, … |
| `preamble.tex` | All package loads, TikZ styles, listings style, palette. Same as Chapter 4. |
| `chapter5.tex` | The chapter: §5.1 RTL Verification (with sample-waveform placeholders), §5.2 Vivado Implementation Results (resource / timing / power tables), §5.3 Software and System-Level Results (accuracy, performance comparison, discussion). |
| `Makefile` | `latexmk` wrapper. `make`, `make watch`, `make clean`, `make distclean`. |
| `figures/` | Reserved for waveform screenshots (currently 3 inline placeholders in §5.1). |
| `listings/` | Reserved for any external code listings (currently unused). |

## Build

```bash
cd 06_doc/thesis_ch5
make                  # produces main.pdf (latex only — no Xcelium dependency)
make watch            # auto-rebuild on edit
make sample_waveforms # invoke Xcelium → produce three SHM files (see below)
make wave_clean       # delete the three SHM directories under 03_sim/scenarios/
make clean            # drop LaTeX intermediates
make distclean        # drop main.pdf + intermediates
```

### Sample waveforms (Figures 5.1–5.3)

The three sample-waveform figures in §5.1.5 reference SHM databases
that the user captures in SimVision. The `sample_waveforms` Makefile
target invokes Cadence Xcelium to run a dedicated scenario testbench
that produces those databases.

**Pipeline**

```
01_bench/scenarios/run_scenarios.sh        ← driver (called by `make sample_waveforms`)
        │
        ├─ xmvlog -sv -f flist_wave         (compile RTL + tb_wave_scenarios.sv)
        ├─ xmelab worklib.tb_wave_scenarios (one snapshot — `snap_wave`)
        └─ xmsim snap_wave +SCENARIO=X      (three times, X ∈ {DMA, CUMAC, FCGROUP})
                                            │
                                            └─ writes 03_sim/scenarios/wave_<x>.shm
```

| Figure | SHM database | Plusarg | Scenario |
|---|---|---|---|
| **5.1** | `03_sim/scenarios/wave_dma.shm`     | `+SCENARIO=DMA`     | 16-beat 1-D AXI4 DMA read into tile bank 0 |
| **5.2** | `03_sim/scenarios/wave_cumac.shm`   | `+SCENARIO=CUMAC`   | CU MAC loop with `TILE_AUTO_INC` + `SPM_AUTO_INC` (3 iterations) |
| **5.3** | `03_sim/scenarios/wave_fcgroup.shm` | `+SCENARIO=FCGROUP` | East-readout pass driving `RESULT_ROW0..3` |

Source files for the testbench live under `01_bench/scenarios/`:

| File | Role |
|---|---|
| `tb_wave_scenarios.sv` | Standalone scenario testbench. Instantiates real `cgra_top` from `00_src/`, drives APB stimulus + minimal AXI4 memory model, dispatches on `+SCENARIO=` plusarg, opens a uniquely-named `.shm` via `$shm_open` / `$shm_probe("AS")`. |
| `run_scenarios.sh`     | Bash driver that invokes the three Xcelium tools in sequence. Fails fast (exit 2) if `xmvlog`/`xmelab`/`xmsim` are not on PATH. |
| `wave_restore.tcl`     | SimVision setup — `database -open waves -shm`, then `waveform add -signals tb_wave_scenarios.*` for clock, reset, APB, AXI, and CGRA debug signals. |

**Prerequisite — source Xcelium environment first**

Cadence's tools must be on PATH before running `make sample_waveforms`. Typically:

```bash
source /path/to/xcelium/installs/Xcelium-XX.XX/bin/setup.csh    # csh-style
# or equivalent bash setup that adds xmvlog/xmelab/xmsim to PATH
make sample_waveforms
```

The driver script verifies tool presence and exits with a clear error if any of the three executables are missing.

**Viewing in SimVision**

```bash
cd 03_sim/scenarios
simvision wave_dma.shm/wave_dma.trn -input ../../01_bench/scenarios/wave_restore.tcl
```

Repeat for `wave_cumac.shm` and `wave_fcgroup.shm`. Capture the three screenshots, save them as PDF/PNG, drop them into `06_doc/thesis_ch5/figures/`, and replace the placeholder `\fbox{...}` blocks in §5.1.5 with `\includegraphics[width=0.95\textwidth]{figures/<name>}` to embed the real waveforms in the chapter.

## Numerical placeholders

The chapter is deliberately populated with bracketed placeholders
that the user replaces with their own Vivado / silicon outputs:

| Placeholder family | Source |
|---|---|
| `[9,148]`, `[X,XXX]` tests | `02_log/sim.log` regression summary |
| `[XX]` minutes runtime | `02_log/sim.log` end-to-end time |
| `[XX.X]%` coverage | `xrun -coverage report` |
| `[XX,XXX]` LUTs / FFs, `[XX]` BRAM / DSP, `[XX.X]%` | Vivado `utilization_post_implementation.rpt` |
| `[XX] MHz`, `[+X.XXX] ns` WNS | Vivado `timing_summary_post_implementation.rpt` |
| `[X.XXX] W` power | Vivado `power_post_implementation.rpt` |
| `[201]`, `[195/201]`, `[97]%`, `[X.XX] ms`, `[3.74]×` | `/tmp/uart_demo*.log` from silicon runs of `demo_mnist_hdmi_bm.elf` |

## Integrating into a larger thesis

If the larger thesis uses `\documentclass{book}` or `report`:

1. Remove the standalone counter renumbering at the top of
   `chapter5.tex` — `\chapter{Results and Evaluation}` in the
   master document will provide it.
2. Master preamble must load: `listings`, `xcolor`, `tikz`,
   `booktabs`, `tabularx`, `cleveref`, `enumitem`.
3. `\input{chapter5}` from the master file.
