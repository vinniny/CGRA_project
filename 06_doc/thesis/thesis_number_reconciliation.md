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
