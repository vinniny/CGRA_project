# Defense Slide Outline — 20-minute presentation

Target: 30 minutes total (20-min presentation + 10-min Q&A). Each
slide labelled with [time], speaker note (italics), and the **one
number** that anchors it.

Slide deck assets: `06_doc/silicon_vtpg_smpte_bars.bmp`,
`06_doc/silicon_vtpg_ila_capture.csv`, `06_doc/impl_power.rpt`,
`bitstreams/cgra_top.bit` post-route screenshot (pull from Vivado HW
Manager device-image view).

---

## Slide 1. Title  [0:30]

> **A CGRA-Based Accelerator with Multicast Routing for Edge CNN
> Inference on Zynq-7000**
>
> Huynh Pham Anh Duy · Trieu Thanh Vinh
> Supervisor: Assoc. Prof. PhD. Truong Quang Vinh
> Senior Design Project — May 2026

*"Today I'm presenting our 4×4 CGRA accelerator on the Zynq-7000,
which we measured at 3.81× FC-stage speedup over a tuned ARM
baseline on MNIST."*

---

## Slide 2. The problem  [1:30]

> **Edge CNN inference: FC stage dominates**
>
> - 2-layer FC (400→64→10) = **80.6 %** of MNIST cycles on ARM-INT
> - Matrix-vector workload = low cache reuse → ARM cache-bound
> - GPU/NPU IPs hide their interconnect; we want to *study it*

[Number: **80.6 %**]

*"This isn't a build-a-better-accelerator pitch — it's a *study of
spatially-distributed reconfigurable compute* applied to the bottleneck
of edge inference."*

---

## Slide 3. Architectural pitch  [1:30]

> **4×4 mesh of identical PEs, 16 PEs total**
>
> Per PE: 3-stage pipeline, 21-opcode ISA, **40-bit saturating MAC**,
> 16-entry RF, 1024-word SPM, 16-slot context BRAM.
>
> Inter-PE: **multicast** routing (5-bit mask) — single-cycle broadcast
> to any N/E/S/W combination.
>
> [Diagram: 4×4 mesh with N/E/S/W arrows; one PE expanded]

[Number: **21** opcodes]

*"Three features beyond textbook CGRA: 40-bit MAC, multicast routing,
two-level loops with zero-overhead branching."*

---

## Slide 4. Three "Configurations" — different time-scales  [2:00]

> 1. **CSR program** (ARM ↔ APB, ms-scale): sets DMA params, loop bounds
> 2. **Context load** (DMA → BRAM, μs-scale): 64-bit word per slot,
>    broadcaster gives 15× DDR bandwidth saving on single-kernel kernels
> 3. **Per-cycle PC** (CU ↔ PE config BRAM, ns-scale): each cycle picks
>    one of 16 contexts

[Number: **15×** broadcast saving]

*"This is the key insight: 'reconfigurable' means three different things
at three different time-scales."*

---

## Slide 5. ISA + multicast routing example  [1:30]

> [Code block: `cnn_fc1_run_group` — 4 PEs MACing in parallel via
>  broadcast]
>
> One DMA, one CSR setup, then the 4×4 array runs for 400 outer
> iterations × 16 inner slots = 6 400 MAC ops in 6 419 cycles =
> **99.7 %** slot efficiency (Suite MTP, measured).

[Number: **99.7 %** MAC slot efficiency]

*"This was a real surprise during bring-up — the project's CLAUDE.md had
documented 'only ~1/3 of MACs contribute' as a quirk. We measured 99.7%
in steady state and updated the docs."*

---

## Slide 6. System diagram  [1:30]

> [Diagram: PS7 ARM-A9 ── APB ── CGRA APB CSR
>           PS7 ARM-A9 ── HP0/HP1 ── AXI ── CGRA DMA
>                                          ↓
>                              CGRA control unit / 4×4 array
>                                          ↓
>                              Tile memory ↔ per-PE SPM ↔ PE]

Bare-metal cgra_test.elf drives all of it via APB writes; AXI HP1 for
DMA bursts; GIC IRQ for DMA-done + CU-done.

*"50 MHz CGRA-side, 666 MHz ARM-side, AXI bridges between."*

---

## Slide 7. Verification rigour  [2:00]

> **Pre-silicon (Cadence Xcelium 20.09)**
> - 9 159 tests · 0 failures · 0 protocol errors
> - **21/21 ISA opcodes hit** (100 % opcode coverage)
> - 402 DMA writes, 40 distinct multi-beat bursts, 6 4 KB-cross
>
> **Post-silicon (PYNQ-Z2)**
> - 96 bare-metal checks across 25 groups (`cgra_test.elf`)
> - 5 distinct GIC interrupt scenarios validated, LED4 pulses visually
>
> **System-level**
> - System ILA confirms TVALID/TREADY ≥ 97 % on every AXIS link
> - 8 SMPTE bars verified post-conversion, within ±3 RGB tolerance

[Number: **9 159 / 0 / 0**]

---

## Slide 8. Silicon numbers  [2:00]

> **Resource (XC7Z020, post-route)**
>
> | Resource | Used | Total | % |
> |---|---|---|---|
> | LUTs | 40 330 | 53 200 | **75.81 %** |
> | Registers | 31 363 | 106 400 | 29.48 % |
> | BRAM | 44 | 140 | 31.43 % |
> | DSPs | 165 | 220 | **75.00 %** |
> | Total power | — | — | **2.456 W** |
>
> WNS = +0.344 ns at 50 MHz · all timing constraints met.

[Number: **2.456 W**, headline efficiency vs comparable CGRAs]

*"This is the silicon-validated production bitstream. We have three
additional variants — Procedure A/B/D — that demonstrate the build
flow."*

---

## Slide 9. Headline result — MNIST FC speedup  [2:00]

> | Path | Latency / image | Throughput |
> |---|---|---|
> | ARM-INT FC | 5.52 ms | 180 FPS |
> | ARM-VFP FC | 4.26 ms | 235 FPS |
> | **CGRA-FC** | **1.45 ms** | **665 FPS** |
>
> Top-1 accuracy on 2 745-frame live test:
> CGRA-FC **97.0 %** · ARM-INT 96.9 % · ARM-VFP 100 %

[Number: **3.81×** speedup (CGRA-FC vs ARM-INT-FC)]

*"3.81× speedup with no accuracy penalty against the matched-precision
ARM-INT baseline. The 3.1% gap to ARM-VFP is the quantisation cost,
not the CGRA cost."*

---

## Slide 10. Bitstream-build reproducibility  [1:30]

> **One `base.tcl` source → three additive bitstreams**
>
> | Procedure | Adds | WNS |
> |---|---|---|
> | A | nothing (reproduce baseline) | **+0.344 ns** |
> | B | v_tpg + axis_switch | +0.232 ns |
> | D | + System ILA | +0.309 ns |
>
> [Number: **0** Tcl errors after 6 documented bug fixes — listed in
>  `chapter5_silicon_results.md` §5.1.2]

*"The defense-relevant thing here: anyone with Vivado 2025.1 + the IP
repos can regenerate the production bitstream from `base.tcl`. We have
the receipts."*

---

## Slide 11. Live silicon demo — pre-recorded video (or live)  [3:00]

> **Demo agenda** (90 s)
> 1. Show `make vtpg_test` running — programs FPGA, runs ELF, captures
>    ILA, dumps + verifies 8 SMPTE bars
> 2. Open `06_doc/silicon_vtpg_smpte_bars.bmp` on the projector — the
>    captured frame
> 3. Show UART output of `demo_mnist_hdmi_bm.elf` with 3-panel
>    comparison: CGRA-FC vs ARM-INT vs ARM-VFP
> 4. (Optional) Demonstrate `rst -dap` recovery from a hung DAP state

*"Everything in this demo is reproducible from a clean clone of the
repo. The bitstream, the ELF, the verification script."*

---

## Slide 12. Limitations (honest)  [1:30]

> - Conv stays on ARM (CGRA does FC only) — Q&A L1
> - INT16 weights, not INT8 — Q&A L2
> - 50 MHz target (justified — Q&A Q8)
> - HDMI source not yet validated (HDMI splitter pending)

*"None of these are surprises — each has a defensible reason."*

---

## Slide 13. Future work  [1:00]

1. **Conv on CGRA** — input broadcast + per-PE weight stream
2. **INT8 quantization** — halves BRAM
3. **AXIS-slave port on DMA** — streams directly to tile memory
4. **Spiking-NN flow** — `LIF` opcode already in ISA

---

## Slide 14. Acknowledgements + Q&A  [0:30]

> **Supervisor**: Assoc. Prof. PhD. Truong Quang Vinh
> **Tools**: Cadence Xcelium 20.09, Vivado 2025.1, Vitis 2025.1
> **References**: MorphoSys (UCI, 2000), ADRES (IMEC, 2003),
> OpenEdgeCGRA (EPFL, 2023), CGRA4ML (UCLA, 2024)

*"Questions?"*

---

## Demo script — `scripts/silicon_vtpg_test.sh` in real time

If running the demo live:

```bash
# (set up beforehand: ssh into WSL with the board attached via usbipd)

# Show clean repo state
$ git log --oneline -5

# One-shot test: ~30 seconds
$ make vtpg_test
[1/4] make run_elf -- programs PL, runs ps7_init, loads + starts ELF
  Connected.
  Programming PL...
  PL programmed.
  Initializing PS...
  PS initialized.
  Loading ELF: 07_sw/baremetal/demo_vtpg.elf
  ELF loaded.
  Starting execution...
[2/4] Vivado HW Manager ILA capture (256 samples × 3 AXIS slots)
    captured: /tmp/ila_capture_vtpg.csv  (+ .vcd)
[3/4] Dump FB0 from DDR @ 0x1100_0000 (921 600 B = 230 400 words)
    dumped: /tmp/silicon_vtpg_fb.bin (921600 bytes)
[4/4] Render BMP + verify SMPTE bars
    OK   bar 0 (white  )  got (255, 255, 255)  want (255, 255, 255)
    OK   bar 1 (yellow )  got (254, 254, 0)    want (254, 254, 0)
    OK   bar 2 (cyan   )  got (0, 255, 252)    want (0, 255, 252)
    ...
    ALL 8 BARS VERIFIED ✓

SUCCESS — v_tpg AXIS chain end-to-end silicon-validated
         BMP: 06_doc/silicon_vtpg_smpte_bars.bmp
```

Open `06_doc/silicon_vtpg_smpte_bars.bmp` in the projector image
viewer. The colour bars are the captured silicon output, not a
simulated render.

## Q&A handoff strategies

- **Hostile examiner questions** (e.g. "why CGRA not GPU"): cite
  `defense_qa.md` Q1 — the *study* framing.
- **Implementation-detail probes** (e.g. "show me how routing works"):
  open `cgra_pe.sv` at the `route_mask` block. Read the comment.
- **"How did you test it?"**: open `cov_report.txt` — point at the
  21/21 line.
- **Honest "what didn't work?"**: tell the v_tpg-YCbCr story
  (`defense_qa.md` G1). It's a positive arc.
