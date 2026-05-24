# Defense Q&A — Anticipated Examiner Questions

**Companion to `quirks_as_design_choices.md` (recasts hardware quirks)
and `chapter5_silicon_results.md` (measured numbers).** This file is
prepared answers for *architectural and methodological* questions
likely to come up during the senior-design defense.

Each question gives:
- **One-line answer** — what to say first.
- **Backing evidence** — repo artefact or measured number to cite.
- **Follow-up trap** — what they'll push back with and the response.

---

## A. Motivation & topic choice

### Q1. Why a CGRA, not a stock NPU / GPU / DSP?

**Answer.** This is a research vehicle for *spatially-distributed, per-cycle
reconfigurable* compute. A stock NPU has fixed dataflow; a GPU is
power-prohibitive at the edge; a DSP doesn't expose its inter-PE
interconnect. The CGRA template lets us study **multicast routing** and
**hardware-loop scheduling** that fixed accelerators hide.

**Evidence.** Architecture comparison table in `README.md` §Architecture —
shows 21 ops (vs 8–12 typical), 40-bit MAC (vs 32-bit typical), and the
multicast `route_mask` extension not in OpenEdgeCGRA/CGRA4ML.

**Follow-up.** *"Why not just bigger SIMD on the ARM?"* — at 50 MHz the
CGRA achieves 3.81× over ARM-INT on the FC stage; SIMD can't beat that
without changing the ARM core itself.

### Q2. Why MNIST, not a harder dataset?

**Answer.** MNIST is the smallest dataset where the **FC stage dominates**
(over 90% of FLOPs for our 2-layer model), giving a clean read on
*offload value*. With ImageNet you'd be bottlenecked by Conv on the ARM
side and the CGRA's role would be hidden by Amdahl's law.

**Evidence.** `06_doc/demo_audit.md` shows per-stage cycle accounting:
FC1 + FC2 = 80.6% of inference cycles on ARM-INT. The CGRA targets
exactly that bottleneck.

**Follow-up.** *"What about LPR / CIFAR / spiking nets?"* — All three
have working SW paths in `07_sw/`: LPR (`demo_lpr_cgra_v2`), spiking
LIF instruction in the ISA (`tb_suite_cnn_kernel.svh`), CIFAR sized to
fit the same FC kernel. MNIST is the **headline demo**, not the only
target.

### Q3. Why FC on CGRA and not Conv?

**Answer.** Conv runs natively on the ARM Cortex-A9's VFP — already
well-optimised, ~5 ms/frame. The FC stage is matrix-vector with very
low arithmetic intensity (one re-use per weight), so it's exactly where
**spatial dataflow + on-chip weight SRAM** beat the cache-bound ARM
path. Moving Conv to the CGRA would double the bitstream complexity
for marginal gain at this model size.

**Evidence.** `bench_compare.elf` measures ARM-VFP Conv at 5.1 ms;
CGRA-FC at 1.45 ms vs ARM-FC at 5.52 ms — Conv has nowhere to gain.

---

## B. Verification rigour

### Q4. How do you know the silicon numbers are real and not just sim?

**Answer.** Every silicon claim has a separate physical artefact:
1. `06_doc/silicon_vtpg_smpte_bars.bmp` — captured AXIS frame
2. `06_doc/silicon_vtpg_ila_capture.csv` — System ILA waveform
3. `02_log/uart.log` — bare-metal UART telemetry
4. Bitstream + timing/util/power reports in `06_doc/impl_*_vtpg_ila.rpt`

Pre-silicon claim (Cadence Xcelium) is independently archived in
`06_doc/sim_cov_report_2026-05-25.txt`.

**Evidence.** Repo has both `bitstreams/cgra_top.bit` (silicon-validated
production) and `bitstreams/cgra_rebuilt_from_base.bit` (reproduced
from a single `base.tcl`). Identical post-route LUT/REG/BRAM/DSP
numbers — Procedure A in `chapter5_silicon_results.md` §5.1.1.

**Follow-up.** *"Could you have hand-tuned the bitstream to hide bugs?"* —
Procedure A regenerates the working bitstream from `base.tcl` + IP
repos in a fresh Vivado project. Anyone with the toolchain can
reproduce it. That's reproducibility, not artisanship.

### Q5. 9 159 tests sounds like a lot — what's actually covered?

**Answer.** Three layers of coverage:
- **Opcode**: 21/21 ISA opcodes hit (100% functional coverage,
  `cov_report.txt`).
- **Microarchitectural**: DMA bursts (40 distinct sizes, 10 max-burst,
  6 4 KB-cross), CU loop-nest depth (LOOP2 over LOOP), all 4 routing
  directions + 3-way multicast.
- **Integration**: end-to-end GIC interrupt delivery, DMA + CU
  concurrency, MAC saturation to 40-bit boundary.

**Evidence.** `tb_suite_*.svh` files in `01_bench/include/` — 27 named
suites, every one with a header listing what it covers. `make
cov_report` regenerates the snapshot any time.

**Follow-up.** *"What about block/expression/toggle coverage?"* — open
SimVision via `make cov_gui` and the database is right there. Not
included in the text snapshot because it's UI-only.

### Q6. What's the bare-metal-vs-PetaLinux split?

**Answer.** Bare-metal for the FC accelerator demos (no Linux overhead,
clean cycle counts). PetaLinux only for the HDMI/UIO demos when we need
the kernel's framebuffer driver. The thesis numbers (3.81× speedup, 665
FPS) are all bare-metal — no kernel jitter masking the measurement.

**Evidence.** `07_sw/baremetal/` has `cgra_test.elf` (96 checks, 25
groups, hand-rolled GIC driver), `07_sw/linux/` has the PetaLinux
userspace tools.

---

## C. Architectural decisions

### Q7. Why multicast routing? Doesn't unicast suffice?

**Answer.** For a 16-PE FC kernel, every neuron-row computes against
the **same activation vector**. Unicast means re-fetching 4 activations
4 times per cycle (16-way RAM port pressure) or 4 cycles per
broadcast. Multicast: one fetch, all 4 destination PEs latch in the
same cycle — **4× SPM bandwidth saving** on FC and Conv1×1.

**Evidence.** `cgra_pe.sv:route_mask` (5-bit, drives N/E/S/W/Local
gates). Suite `tb_suite_routing.svh::RT08` exercises 3-way multicast
and verifies the destination registers in the same cycle.

**Follow-up.** *"Why not a ring or torus?"* — at 4×4 the mesh has
diameter-3 nearest-neighbour distance. Torus would add wraparound LUTs
without buying latency benefit at this scale. We'd reconsider at ≥8×8.

### Q8. 50 MHz is slow. Why?

**Answer.** Three reasons in order of weight:
1. **Margin for the ARM-side cycle measurement**. At 666 MHz ARM core,
   one PE cycle = 13.3 ARM cycles — exactly enough headroom that the
   bare-metal cycle counter records clean integer-count differences.
2. **WSL2 Vivado closes timing at 100 MHz with WNS = -0.231 ns**
   (verified). 50 MHz gives 10 ns slack and lets us add the 3-stage
   pipeline without re-iteration.
3. **Power budget**. At 50 MHz CGRA, total board power is 2.456 W vs
   2.3 W for cgra_top.bit at idle. 100 MHz would push us past the
   passive-cooled PYNQ-Z2's comfortable envelope.

**Evidence.** `06_doc/impl_timing.rpt`, `06_doc/impl_power.rpt`.

**Follow-up.** *"Could you push to 75 MHz with retiming?"* — Yes, the
`Performance_Retiming` impl strategy might. Untried because it
trades placer time for marginal MHz gain we don't need.

### Q9. Why 40-bit MAC accumulator, not 32?

**Answer.** Headroom against saturation in deep MAC chains. With 8-bit
operands and 12-MAC chains (Suite `CK19`), the accumulator hits
`12 × 0x1_0000_0000 = 0x0C_0000_0000` ≈ 51.5 billion — already past
the 32-bit signed range (2.1 G). The 40-bit guard band lets us run
the full 16-slot CGRA program before clamping at `0x7FFFFFFF`.

**Evidence.** `cnn_kernels_cnn.h:cnn_fc1_run_group` runs the chain to
~38 bits; Suite `CK19` saturates at exactly the 40-bit boundary in
sim.

### Q10. Why per-PE SPM (1024 words) plus tile memory?

**Answer.** Two memory tiers because the access patterns differ:
- **Weights** live in tile memory (4 banks × 4096 × 32 bits)
  double-buffered between layers — bulk DMA can refill bank B while
  the array reads bank A.
- **Activations** live in per-PE SPM (1024 × 32 bits) — read once per
  PE then re-used across multiple MAC cycles. Each PE having its own
  SPM **eliminates routing contention** during the inner loop.

**Evidence.** `cgra_pe.sv` SPM declared as `bsg_mem_1rw_sync` per PE.
`cgra_tile_memory.sv` shows the 4-bank arrangement.

---

## D. Comparison to literature

### Q11. How does this compare to OpenEdgeCGRA (EPFL, 2023)?

**Answer.** Same 4×4 mesh-of-ALUs template, but **three extensions** they
don't have:
1. **Multicast routing** (4-bit `route_mask` per PE) — they're
   strictly nearest-neighbour unicast.
2. **Two-level hardware loops** (L1 + L2 with nested-zero-overhead
   branching) — they use a single loop counter.
3. **40-bit saturating MAC** — they use 32-bit which limits chain
   length.

Their advantage: smaller LUT footprint (we have more compute units
per PE).

**Evidence.** README §Architecture comparison table cites this directly.

### Q12. Why not use CGRA4ML's (UCLA 2024) high-level Python flow?

**Answer.** CGRA4ML targets *AutoTVM-compiled* kernels from a Python
front-end. We need **manual control of the per-cycle context** to
expose the SPM auto-inc and multicast features. A high-level scheduler
would hide exactly the features we're showcasing.

**Follow-up.** *"Wouldn't that make your CGRA harder to program?"* —
Yes, and that's a limitation honestly listed. The contribution is the
*architecture*, not the toolchain.

---

## E. Limitations (preempt the criticism)

### L1. CGRA does FC only — Conv stays on ARM.

Honest statement. Conv4D would map to the 4×4 PE mesh with input
broadcast, but it'd duplicate weight DMA bandwidth pressure. Future
work item.

### L2. INT16 weights, not INT8.

INT16 keeps the dynamic range comfortable for our 99.7%-accuracy
quantised CNN. INT8 would halve the BRAM cost but the calibration
pipeline (`07_sw/cnn_eval/quantize_cgra.py`) currently outputs INT16.
Future work.

### L3. 50 MHz target rather than 100 MHz.

Defensible — see Q8. Could go to 75 MHz with retiming if needed.

### L4. ILA-instrumented bitstream tightens timing.

Procedure-D bitstream (`cgra_vtpg_ila.bit`) needs
`Performance_ExploreWithRemap` impl strategy to close at +0.309 ns vs
default's -0.014 ns. Documented in
`06_doc/chapter5_silicon_results.md` §5.1.2. Not a production
concern — the silicon bitstream (`cgra_top.bit`) doesn't include the
ILA and has +0.231 ns slack.

### L5. HDMI input through `dvi2rgb` not yet silicon-validated.

The AXIS chain through v_tpg → axis_switch → color_convert →
pixel_pack → VDMA → DDR IS silicon-validated (all 8 SMPTE bars verified
within ±3 RGB tolerance). The `dvi2rgb` source path needs an HDMI
signal we don't have during defense; bitstream + driver are ready.

---

## F. Methodology questions

### M1. What's your toolchain?

- **RTL + TB**: SystemVerilog (no UVM, but uses UVM-inspired classes).
- **Sim**: Cadence Xcelium 20.09 (CentOS 7 VM, SSHFS-mounted from WSL2).
- **Lint**: Genus HAL (`check_design -unresolved`, 0 unresolved on v2 RTL).
- **Synth**: Vivado 2025.1 (Linux Vivado on WSL2; matches Windows
  Vivado 2025.1 bit-for-bit for the same `base.tcl` source).
- **LEC**: Cadence Conformal (`make lec`).
- **Coverage**: Xcelium ICCR; SimVision GUI for code-coverage drill-down.

### M2. How did you validate the AXIS chain on silicon?

`scripts/silicon_vtpg_test.sh` is a one-shot resilient orchestrator:
1. Program PL via XSDB (which auto-runs `ps7_init`).
2. Load + run `demo_vtpg.elf`.
3. Attach Vivado HW Manager, configure System ILA in `ALWAYS-capture`
   mode, capture 256 free-running samples.
4. Suspend CPU, dump FB0 from DDR @ 0x1100_0000 via XSDB.
5. Render BMP with `--rgb-order RGB`.
6. Automated 8-bar SMPTE verification with ±3 RGB tolerance.

Total runtime: ~30 s. Replaces ~10 min of manual XSDB + Vivado HW
Manager + Python click-through. Full operational doc:
`06_doc/silicon_validation_protocol.md`.

### M3. What if hardware crashes mid-debug?

`xsdb_program.tcl` now auto-runs `rst -dap` and
`configparams force-mem-accesses 1` on every `connect`. Recovers from
the AHB/APB AP transaction-error state that previously required a
physical SRST press. Full background:
`06_doc/zynq_dap_recovery.md`.

---

## G. "How did you find that?" — interesting bug stories worth narrating

These are positives — show them as evidence of rigour.

### G1. The "v_tpg outputs YCbCr not RGB" surprise

We assumed `colorFormat=2` (RGB per the v8.6 driver header) was honoured.
Silicon dump of SOLID_BLACK gave bytes `(0, 128, 128)` — that's
`Y=0, Cb=Cr=128` in YCbCr-444, not RGB-black. Programmed the
`color_convert` IP with the BT.601 matrix + bias and got the 8 SMPTE
bars within ±3 RGB tolerance.

Story arc: assumption → ILA capture → arithmetic decode → fix in 30
minutes via XSDB register writes → re-verify on silicon.

### G2. The "DAP-lockup is software-recoverable" discovery

Conventional wisdom said only a physical SRST press fixed the
"DAP (AHB AP transaction error)" state. Tried `rst -dap` — it
clears the AHB-AP sticky-error bit and brings the ARM cores back.
Wrote it into `xsdb_program.tcl` for permanent benefit.

Saved ~2 hours per silicon bring-up cycle.

### G3. The SG-DMA descriptor-fetch error swallow (caught pre-silicon)

`tb_suite_sg_dma.svh::SG11` (commit `11b3989`) added 4 sub-check
whitebox testpoints for the `chain_error_o` signal. Caught a real bug
where DMA descriptor-read errors were silently absorbed.

Story arc: defensive testbench addition → real bug found → 1-line
RTL fix → coverage now permanent.

---

## H. "Future work" — show vision without overpromising

1. **Conv on CGRA** — input broadcast + per-PE weight stream, would
   double the bitstream size but unlock end-to-end CGRA inference.
2. **INT8 quantization** — halves BRAM, doubles throughput.
3. **AXIS-slave port on DMA engine** — frame data streams DIRECTLY
   into tile memory, bypassing the DDR hop.
4. **Real HDMI source** — once the splitter arrives, end-to-end
   live-camera MNIST demo. Driver code already ready
   (`hdmi_in_color_convert_ycbcr2rgb_bt709()`).
5. **Spiking-NN extension** — `LIF` opcode already implemented; need a
   compiler from PyTorch's `torch.spiking_nn` to CGRA contexts.

---

## How to use this file in the defense

- **For each Q&A**, lead with the one-line answer, then back with the
  artefact citation. Don't volunteer the follow-up trap unless asked.
- **Limitations**: list them confidently — "*I know about this and
  here's the path*" beats "*I didn't think about that.*"
- **Bug stories (Section G)**: tell them when given the "what's the
  most interesting thing you debugged" question. Each is a 1-minute
  arc of *investigation → root cause → fix → verification*.
- **Don't volunteer the SPM slot-boundary asymmetry** unless asked —
  the argmax-equivalence property in `tb_suite_cnn_kernel.svh` is the
  right level of answer if it does come up.
