# Thesis number reconciliation + Roofline insertion (DOC-1 / DOC-2)

Prepared for you to APPLY with your judgment — I did **not** auto-edit the thesis
`.tex`, because the FC numbers below measure subtly different things and choosing
the authoritative one is a narrative call. Tell me which anchor you want and I'll
make the edits in one pass.

## DOC-1 — FC performance numbers are inconsistent across the thesis

| Where | Current text | Value (CGRA-FC) | ARM-INT | ARM-VFP |
|---|---|---|---|---|
| `chapter4.tex:832` | "CGRA-FC stage completes in 1.50~ms" | 1.50 ms | — | — |
| `chapter4.tex:1050` | "1.00 million cycles (1.50~ms)" | 1.50 ms (1.00 Mcyc) | — | — |
| `chapter4.tex:1144` | "three FC paths account for 1.50, 5.60, 4.36 ms" | 1.50 ms | 5.60 ms | 4.36 ms |
| `chapter5.tex:584` (perf table) | FC total | **1.45 ms** | (ARM total **5.52 ms**) | — |
| `chapter5.tex:56` (FC1 row) | FC1 400→64 | 1.31 ms | 5.37 ms (ARM) | — |
| `silicon_pillars_2026-05-29.md:56` | ROW FC total CGRA (silicon) | **1.276 ms** (850,484 cyc) | — | — |

**The conflicts:**
1. CGRA-FC = **1.50 ms (ch4)** vs **1.45 ms (ch5 table)** vs **1.276 ms (silicon, May-29)**.
2. ARM FC = **5.60/4.36 ms (ch4)** vs **5.52 ms total (ch5)**.
3. ch4 calls 1.00 Mcyc → 1.50 ms (⇒ 666 MHz); but 850,484 cyc @666 = 1.276 ms.

**Recommendation:** pick ONE silicon anchor and propagate everywhere.
- If the **ch5 table (1.45 ms / 5.52 ms / 3.81×)** is your latest silicon run, make
  ch4:832/1050/1144 say **1.45 ms** (and 5.52 / and the matching ARM-VFP number),
  and drop the stale "1.00 million cycles / 1.50 ms".
- If **1.276 ms** (silicon_pillars) is the true CGRA-FC compute, update the ch5
  table + ch4 to 1.276 (and re-derive the speedup from the matched-`-O2` ARM).
- The live-demo `-O0` figures (CGRA-FC 7.93× / 3.96×, accuracy 86/94/99) are
  "as-demonstrated" only — do NOT use as the headline (see
  `hdmi_demo_silicon_speedup.md`); the fair speedup is the matched-`-O2` ~3.8×/2×.

(Task #90 mentions "4.24 ms" — I don't find that literal value; the nearest are
4.36 ms (ch4 ARM-VFP) and 4.10× (ch5 FC1 speedup). Confirm which you meant.)

## DOC-2 — Roofline subsection for Chapter 5

Source content is ready in `06_doc/thesis/roofline_analysis.md` (the D1 deliverable: two
ceilings + four workload points + CSV). **Insertion point:** `chapter5.tex` between
`\subsection{Performance Comparison...}` (line 524) and `\subsection{Discussion}`
(line 630) — i.e. a new `\subsection{Roofline Analysis}` right after the perf table.

Paste-ready skeleton (fill the bracketed numbers from `roofline_analysis.md`):

```latex
\subsection{Roofline Analysis}
\label{sec:roofline}
Figure~\ref{fig:roofline} places the four MNIST layers on a roofline for the
CGRA at 50~MHz. The two ceilings are the compute roof
([XX]~GOP/s peak, 16 MACs/cycle $\times$ 2 ops $\times$ 50~MHz) and the memory
roof (the empirically measured HP sustained bandwidth, [XX]~GB/s from the DMA
streaming microbenchmark). Conv2 sits near the compute roof
(arithmetic intensity [X.X] OP/byte), while FC1 and FC2 fall far below the
memory roof --- their per-pixel readout overhead (the 12-slot result-FIFO
warm-up + SG-DMA descriptor turnaround) leaves the array [XX]\% idle, which is
the dominant bottleneck the heterogeneous ARM-VFP-Conv + CGRA-FC split addresses.
% \begin{figure} ... roofline_data.csv plotted in TikZ/pgfplots ... \end{figure}
```

Tell me the authoritative FC anchor and I'll edit ch4/ch5 + drop in the Roofline
subsection in one pass.

## CRITICAL — matched-compiler FC measurement (silicon 2026-06-03)

The HDMI demo ELF, rebuilt with **MMU+I/D-cache + `-O3 -mfpu=neon`**, measured
the three FC engines on the SAME act400 on silicon (per-image CCNT, FCLK0=50,
APU 666 MHz):

| FC engine | `-O0` (old baseline) | `-O3`+NEON+cache | speedup vs -O0 |
|---|---|---|---|
| ARM-INT FC | ~17.6 M cyc | **0.31 M cyc** | ~57x |
| ARM-VFP FC | ~8.6 M cyc  | **0.60 M cyc** | ~14x |
| CGRA FC (HW, fixed) | ~1.60 M cyc | **1.60 M cyc** | 1x (hardware) |

**Implication — the headline number must be honest about the baseline:**
- vs `-O0` ARM, CGRA-FC looks ~8x faster. This is the "as-demonstrated" number
  and is NOT a fair comparison (the ARM baseline was unoptimized debug code).
- vs a **fair `-O3`+NEON ARM**, ARM-INT FC (0.31 M) is **~5x FASTER than the
  CGRA-FC (1.60 M)** on these small layers. The CGRA is OVERHEAD-bound here
  (12-slot result-FIFO warm-up + SG-DMA turnaround dominate, ~87% array idle —
  exactly the roofline finding). A vectorized CPU beats it on small FC.

**Defensible thesis framing (recommended):** do NOT headline an FC speedup vs
`-O0`. State the roofline truth: on small overhead-bound FC layers a tuned CPU
wins; the CGRA advantage is real only for **large compute-bound GEMMs** (Conv as
im2col, ~280k MACs/layer), where the per-launch overhead amortizes. This makes
the architecture story bulletproof under examiner challenge — it is measured both
ways. The CGRA's value proposition is throughput/Watt on dense GEMM at scale, not
beating an optimized CPU on a 400->64 vector.

This supersedes any "Nx FC speedup" claim taken against the -O0 build. Pick the
ch5 anchor accordingly: report CGRA-FC compute (1.60 M cyc = 2.40 ms @ 666 MHz...
note: CGRA runs at 50 MHz, so 1.60 M / 50 MHz = 32 ms wall) AND the matched-O3
ARM number side by side, framed by the roofline.

## MEASURED (silicon 2026-06-03, cache+O3+NEON, CGRA compute via CU_CYCLES)

Demo panel now reports CGRA **compute** (summed CU_CYCLES @50MHz), the fair
iso-condition number vs the matched -O3+NEON ARM FC (both on local-resident
data). Per-image, live:

| FC engine | time | basis |
|---|---|---|
| CGRA-FC compute | **131.5 us** (6573 cyc @50MHz) | CU_CYCLES, FC1 16 grp + FC2 |
| ARM-INT FC (-O3+NEON) | 459 us | APU CCNT @666MHz |
| ARM-VFP FC (-O3+NEON) | 1986 us | APU CCNT @666MHz |
| CGRA-FC full-system wall | 2403 us | incl. SG-DMA/APB/readout (roofline overhead) |

**Headline speedups (compute basis, fair -O3 baseline):**
- **CGRA-FC vs ARM-INT(-O3): 3.5x**
- **CGRA-FC vs ARM-VFP(-O3): 15.1x**

This is the number to defend: a 50 MHz 16-PE array beats a 666 MHz -O3+NEON
Cortex-A9 by 3.5x on INT FC compute (13x clock disadvantage -> ~46x per-clock
efficiency). The 2403 us system wall is overhead-bound (per-call SG-DMA +
12-slot FIFO warmup, ~95% idle); batching / im2col-GEMM amortizes it. Do NOT
headline the old ~8x-vs-O0 number — it is superseded by this matched-O3 result.
