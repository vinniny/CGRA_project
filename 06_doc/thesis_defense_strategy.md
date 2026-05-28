# Thesis defense strategy

Distilled from `senior_arch_review_2026-05-28.md`. Use this as the playbook
for the defense slide order, measurement methodology, and the answers to
anticipated examiner questions.

---

## Defense narrative — the one-paragraph thesis position

> We built a CGRA for spatial-reuse workloads (Conv with AI ≥ 14 ops/byte,
> stencil filters, NTT). On these workloads the architecture achieves the
> compute-roof on the Roofline plot. Memory-bound layers (FC with AI < 1)
> are explicitly offloaded to ARM-NEON — not because we couldn't put them
> on the CGRA, but because we modeled it and proved the data movement, not
> the compute, is the bottleneck. This heterogeneous posture mirrors how
> production accelerators (TPU MXU+VPU, Apple ANE, NVDLA) handle the same
> dichotomy. Forcing FC onto a spatial array is feature-creep that destroys
> the area/power/performance advantage the CGRA exists to deliver.

## Workload selection (the "why these three?")

State this *explicitly* at the start of the evaluation section:

| Workload | Stresses | What it proves |
|---|---|---|
| MNIST CNN | Compute array spatial reuse, 2D dataflows | Compute roof attainable |
| LPR INT8 OCR | Memory subsystem, irregular access | Memory bottleneck diagnosed |
| Kyber-512 Barrett | Functional unit flexibility, modular arithmetic | "General" in CGRA |

Three is the academic-paper magic number for architectural diversity.
They each stress a different subsystem — not just three different topologies
of the same workload class.

If asked "why MNIST, not ImageNet?": cite **MLPerf Tiny**. The relevant
benchmark suite for ultra-low-power edge devices uses visual wake words,
keyword spotting, anomaly detection — workloads the size of MNIST and LPR.
This CGRA targets the Deep Embedded Edge; ImageNet is a datacenter and
high-tier mobile benchmark with fundamentally different memory-hierarchy
assumptions.

---

## Measurement methodology — the four pillars

To make the cycle model bulletproof, all four must be measured on the
same bitstream and instrumented with the PMU:

1. **Microbenchmark anchor** — synthetic kernel (pure MAC with operands in
   PE registers, or pure DMA stream). Proves the architectural roof is
   real.
2. **Compute-bound layer** — one Conv layer in isolation. Proves the
   spatial array delivers high utilization when data reuse is present.
3. **Memory-bound layer** — one FC layer in isolation. Validates the
   diagnosis of the readout/orchestration bottleneck.
4. **End-to-end workload** — full inference. Proves the system-level
   orchestration story.

**Target precision**: cycle-model within **5-10% margin of error** against
silicon PMU on all four. If the model achieves that, it's defendable. If
it doesn't, you don't have a model — you have a guess.

## The two-pass PMU method (defeats the observer effect)

PL310 register reads cost dozens of CPU cycles over APB, so per-layer
sampling perturbs the very memory/compute overlap you're trying to measure.
Production methodology:

1. **Clean pass**: PMU read only at start + end of full inference. Gives
   unperturbed absolute latency.
2. **Instrumented pass**: PMU reads between every layer. Total time is
   inflated by the APB read overheads.
3. **Synthesis**: Use the instrumented pass for **proportional breakdown
   only** (e.g., "Layer 1 was 20%"). Apply those percentages to the *clean*
   pass's absolute time.

**Cite this in the methodology section verbatim.** Examiners love
acknowledging the observer effect — most students don't realize it exists.

## Bottom-up presentation order

Never lead with the end-to-end number. Lead with primitives and let the
end-to-end number become an inevitable conclusion:

1. *"Microbenchmark: 100% MAC utilization, matches simulator."* (trust)
2. *"DMA stream: 80% of theoretical AXI bandwidth."* (platform limits)
3. *"Conv layer hits compute roof; FC layer hits memory roof."* (diagnosis)
4. *"End-to-end: behaves exactly as the primitives predicted."* (result)

By the time the headline number appears, it's not a claim to defend —
it's the mathematical conclusion of the previous four slides.

---

## Roofline plot — the canonical setup

### Y-axis: GOPS (with explicit definition)

Label: `Performance (GOPS)`. In the caption: *"Peak compute is 800 MMAC/s
(16 PEs × 50 MHz). Using the ML-industry standard convention of
1 MAC = 2 Operations, this yields 1.6 GOPS."*

### Two ceilings, not one

- **Theoretical roof**: 4.8 GB/s memory bandwidth × ... GOPS compute peak.
  Cite Xilinx Zynq-7000 TRM for the BW number.
- **Empirical/achievable roof**: 60-80% of theoretical, measured via a
  **pure-streaming DMA microbenchmark** (NOT the ML workload — that's
  circular). The microbenchmark must saturate AXI with max-burst-length
  reads/writes.

### Plot the workloads as points (NOT as the roof)

The architectural peak is the roof; the workload's actual performance is
the dot under the roof. **Never lower the roof to make the dot look
closer** — committees recognize this as cooking the books.

The gap between the dot and the roof IS the bottleneck story. Point at the
vertical gap on the FC point and say: *"This represents our 87% idle time.
It is driven by readout overhead and column-serial AXI drain."*

---

## NEON baseline — give the CPU every advantage

Compile flags: **-O3 + LTO + NEON intrinsics**. Isolate the NEON kernel
into its own compilation unit so the -O1 baremetal codebase doesn't break
linking. Use explicit `vmlal_s16` (or `smlal` if writing inline asm), not
the auto-vectorizer.

Presentation line: *"We benchmarked against a heavily optimized, -O3
compiled NEON baseline using explicit vector intrinsics to ensure our
hardware comparison was rigorously fair."*

This single sentence shields you from the most common attack in
accelerator defenses (the "you compared against unoptimized software"
strawman).

---

## Hetero pipeline visualization — show both

| Slide | Title | What it shows |
|---|---|---|
| 1 | Measured Execution | Serial waterfall: CGRA-conv → sync → NEON-FC. PMU-anchored. |
| 2 | System-Level Scaling Opportunity | Parallel timeline: CGRA-conv (frame N+1) overlapped with NEON-FC (frame N). Macro-pipelining. |

The order matters: validation first, then projection. Never present an
unvalidated pipeline as the primary result.

---

## Anticipated examiner questions & pre-built answers

| Question | Answer (short form) |
|---|---|
| "Shouldn't a CGRA at least try to do FC?" | "I did try — modeled the 16-PE FC v2 wide-compute variant. Readout overhead scaled proportionally; no net win. Feature-creep destroys the area/power advantage." |
| "Why only MNIST?" | "MLPerf Tiny — target domain is Deep Embedded Edge. ImageNet violates the area/power constraints by design." |
| "Why three workloads?" | "Architectural diversity: MNIST stresses spatial reuse, LPR stresses memory subsystem, Kyber stresses functional unit flexibility." |
| "Your CGRA only delivers 13% on FC. That's bad." | "Yes — and that vertical gap on the Roofline plot is exactly the architectural diagnosis we're presenting. The CGRA is delivering 95%+ on the workloads it was designed for; the FC mismatch is what motivates the heterogeneous offload." |
| "How do you know your model is accurate?" | "Four-pillar validation: microbenchmark, compute-bound layer, memory-bound layer, end-to-end. Model predicts each within 5-10% of PMU-measured silicon." |
| "Is the NEON comparison fair?" | "-O3 + LTO + explicit NEON intrinsics. Isolated in its own compilation unit. Anything less would be a strawman." |

---

## Citations to seed the bibliography

| Topic | Citation |
|---|---|
| NEON INT16 GEMV | QNNPACK (Dukhan, Facebook 2018) |
| NEON low-precision MAC | gemmlowp design docs (Benoit Jacob, Google) |
| 16-bit NEON tutorial | Chris Shore, *Coding for Neon — Part 3: Matrix Multiplication* (ARM) |
| Edge benchmark legitimacy | MLPerf Tiny |
| Hetero TPU precedent | Jouppi et al., *In-Datacenter Performance Analysis of a TPU* (ISCA 2017) |
| ANN sparse-vs-dense split | Eyeriss (MIT), SCNN (NVIDIA), Cambricon-X (CAS) |
| Mesh-router upgrade path | HyCUBE — single-cycle multi-hop CGRA routing |

---

## What NOT to do in the defense

- ❌ Don't quote the all-CGRA 2.33 ms number as a headline (internally
  inconsistent — FC1 alone is 115 k cyc; emulator total can't be 116 k)
- ❌ Don't present hetero 0.47 ms as silicon-measured (it's a projection)
- ❌ Don't use the application-achievable curve as the roof
- ❌ Don't lead with end-to-end before primitives
- ❌ Don't compare against unoptimized ARM code
- ❌ Don't claim measurements were on Haoyue when current platform is PYNQ-Z2

---

## What WILL happen if all the above is executed

The defense becomes a *guided derivation* rather than a *claim to defend*.
Each measurement establishes a fact; each fact supports the next; the
final speedup number is the mathematical conclusion of the chain. The
heterogeneous architecture posture is the position, not the apology.
