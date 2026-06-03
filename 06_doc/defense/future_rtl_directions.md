# Future RTL directions (v3 chip)

Distilled from `senior_arch_review_2026-05-28.md`. The current 4×4 CGRA on
XC7Z020 is sound for an edge-CNN/SNN demonstrator; this doc captures the
specific changes for a v3 chip targeting late-2020s edge ML (Transformer
attention, ViT, small LLM inference) with hetero offload for non-spatial
workloads. **Not a v2 RTL plan — keep the current RTL frozen for the
thesis defense.** Use this as the lineage doc for any successor project.

---

## v3 chip — target workload

**Transformer attention (GEMM)**, not MNIST CNN. By the late-2020s, edge
inference is moving aggressively to ViTs and small LLMs (Llama-3-8B class,
MobileBERT). Optimize for matrix-matrix multiplication; use a secondary
fabric (or ARM NEON) for Softmax and LayerNorm.

- ❌ Standard CNNs — solved problem
- ❌ Post-Quantum Crypto NTT — too niche, build a dedicated co-processor
- ❌ SNN — academically interesting, commercially stalled
- ✅ **GEMM for attention layers** — commercial semiconductor industry is bleeding here

---

## Architectural decisions — confirmed (keep these)

| Decision | Keep because |
|---|---|
| 4×4 mesh router (N/E/S/W/Local) | Defining scalable characteristic of a CGRA; full crossbar scales O(N²) and destroys Fmax |
| 40-bit accumulator | Industry-standard sweet spot for INT16×INT16; 8 guard bits = 256 safe MACs |
| 4 KB SPM per PE | Right area/flexibility point for edge — shrink → memory-bound, grow → SRAM-array with ALUs bolted on |
| Software-programmable `CU_PC_END` | The 30-cycle APB tax is Amdahl-noise; hard-coding wastes config-RAM area |
| Per-PE bias *via DMA-mappable bank* (not APB regs, not opcode) | APB is too slow; opcode bloats decode; DMA-mappable keeps datapath pure |

## Architectural changes — recommended for v3

### 1. **Kill 16-deep config slots → use 4-deep**
Multi-context was a vestige of irregular-DSP-era CGRAs. For spatial AI
the inner loops are highly regular: you only need Prologue + Steady-State
+ Epilogue + one spare = **4 contexts**.

Impact: drastically smaller config RAM, less routing congestion, faster
MAC clock. This is the single biggest "free" area savings.

### 2. **Decoupled Access-Execute via per-PE result FIFOs**
Replace the current synchronous-drain readout architecture with per-PE
result FIFOs.

- **Depth**: `(compute burst) − (drain rate) + (max AXI backpressure)`.
  Empirically 16-32 is "free" via LUTRAM/SRL32 on FPGA.
- **Backpressure**: PE *must stall* on FIFO full. Silent corruption is
  fatal in ML — TPU/NVDLA both stall.
- **Drain arbiter**: **Burst-locked round-robin** (not priority — priority
  needs 16-way counter comparison every cycle, kills Fmax). Lock onto a
  FIFO for one full AXI burst (4-8 beats) or until empty.
- **Drain port**: Share through SmartConnect, not a dedicated HP port.
  The 5 ns first-beat arbitration is hidden by the FIFO depth.

Eliminates the 4-column readout serialization that currently dominates
FC layers (Section 4 of the current bottleneck analysis).

### 3. **Tile memory: 4 banks × 4096 → 8 banks × 2048**
Doubles the read/write ports into the fabric. Lets DMA fill banks 0-3
while compute reads banks 4-7 (true ping-pong with simultaneous Weights +
Activations + Partial Sums streams). Cost: wider memory-to-CGRA
interconnect crossbar. Payoff: significant utilization boost on GEMM-like
workloads.

### 4. **HyCUBE-style single-cycle multi-hop routing**
Keep the 5-port mesh topology, but add bypass multiplexers to the routers
so data can traverse multiple PEs in a single clock cycle without
stopping at intermediate registers. Crossbar-like flexibility at mesh-
like area cost.

### 5. **INT8 with INT32 accumulator (not INT16)**
For an edge inference chip, INT8 is the standardized format. INT16 is the
right call for *this* MSc-defensible chip (forgiving on quantization
error), but for v3 commit to INT8.

**Do not go FP16** unless the chip targets on-device training/fine-tuning
— FP16 MACs are 3-4× larger and more power-hungry than INT in 28 nm.

---

## ASIC migration deltas (when leaving FPGA)

Three things break on 28 nm standard-cell when porting from XC7Z020:

| FPGA artifact | ASIC problem | Mitigation |
|---|---|---|
| 16-deep config RAM per PE via LUTRAM | SRAM macros have minimum size; 16×32b is wildly inefficient | Use flip-flops (if going to 4-deep), OR consolidate per-column shared config SRAM with broadcast |
| 64-bit config word broadcast to 16 PEs | Massive routing web — FPGA has prefab tracks, ASIC must weave them | Serialize config loading, OR compress/encode instructions |
| Asynchronous resets + nested clock gating | Clock-tree synthesis fails to balance skew | Single global synchronous reset, clean clock-gating hierarchy |

### Power-domain strategy
- ✅ **Per-PE clock gating (ICG cells)** — mandatory, drops idle dynamic power 95%, near-zero routing cost
- ❌ **Fine-grained voltage scaling** — trap. Isolation cells + level shifters + multiple power grids destroys floorplan and tape-out schedule

Use a single voltage domain. Aggressive clock-gating only.

---

## Hetero-SoC topology (v3 chip-level)

**Two specialized fabrics + shared coherent SRAM**, not one universal
CGRA. The Apple Neural Engine, Google Edge TPU, and NVDLA all follow this
pattern.

```
                  ┌─────────────────────────┐
                  │  Shared SRAM (coherent) │
                  │  256 KB - 1 MB          │
                  └────────┬─────────┬──────┘
                           │         │
              ┌────────────▼──┐   ┌──▼──────────────┐
              │ CGRA (v3)     │   │ Vector / Scalar │
              │ 8×8 array     │   │ engine          │
              │ INT8 GEMM     │   │ Softmax,        │
              │ 4-ctx config  │   │ LayerNorm,      │
              │ HyCUBE router │   │ control flow    │
              └───────────────┘   └─────────────────┘
```

The CGRA does what it's best at (regular dataflow, compute-bound). The
vector engine handles activation functions, normalization, dynamic
sparsity. Coherent SRAM (not DDR round-trip) keeps the hetero handoff
under ~µs.

---

## Sub-block decisions cribbed verbatim

### Per-PE FIFO sizing rule
```
Depth = (Compute Burst Size) - (Guaranteed Drain Rate)
      + (Max Expected AXI Backpressure)
```
For our AXI interconnect (~10-15 cycle worst-case stall observed), depth
= 16-32 is sufficient and maps to SRL32 LUTRAM (free).

### ACP rate-limit sweet spot (when forced to use ACP)
- AXI bursts: **4 or 8 beats only** (32-64 B, aligns with 32 B cache line)
- Outstanding writes: **1 or 2** (`AWVALID` without `BVALID`)
- Insert artificial gap between bursts to let A9 NEON fetches slip into L2

### ACP usage policy
- ✅ Small latency-sensitive control structures (SG-DMA descriptors,
  parameter updates)
- ❌ Bulk ML tensors — use HP ports to DDR + manage cache in software

The SCU on Cortex-A9 *will* lock up if streamed bulk tensors. UG1046's
warning is not overcautious — it's a hard production reality.

---

## What this implies for the current v2 RTL

**Don't touch it.** The current 4×4 CGRA + v2 dual-port SPM is the right
demonstrator for the MSc defense. The future-directions above are for the
*next* project. Implementing any of them now would:

- Break the silicon-validated v5b bitstream
- Force a 2-4 week re-validation cycle
- Push the demo timeline past the defense window

If a v3 project ever materializes, this doc + `senior_arch_review_2026-05-28.md`
are the starting point. Until then: freeze the RTL.
