# Silicon characterization — PYNQ-Z2, 2026-05-29

First full silicon pillar sweep on the **DDR-fixed** platform
(v17 bitstream `eec56d1e` + board-aware REF ps7_init). DDR was dead for
the entire prior bring-up due to an incomplete PS-7 DDR config; root-caused
and fixed this session (see `06_doc/ddr_broken_post_crystal_fix.md` +
`memory/project_ddr_root_cause.md`). All ELFs run via
`scripts/vitis_launch_with_clear.tcl` with `CGRA_BIT=/tmp/cgra_working/cgra_top.bit`
and `CGRA_XSA_DIR` pointing at the working ps7_init.

## Pillar results

### B1 — Compute roof (`bench_mac_micro`)
PE[0,3] MAC(IMM,IMM), `LOOP_START=1` (ACC_CLR outside loop body):

| passes | cycles | MAC slots |
|---|---|---|
| 1  | 15  | 15  |
| 10 | 150 | 150 |
| 64 | 960 | 960 |

`cycles == MAC-slots` exactly → **1 MAC/cyc/PE, zero stall** →
**compute roof = 1.6 GOPS** (16 PE × 50 MHz × 2 ops/MAC).
(Note: `contribs` readout = 10 is a result-FIFO/RESULT_SKIP snapshot
artifact, not a compute error; cycle count is the valid metric.)

### B2 — Memory roof (`bench_dma_stream`)
DDR (0x100000) → CGRA tile broadcast, ARM-CCNT bracketed:

| burst | BW |
|---|---|
| 1 KB | 66 MB/s |
| 4 KB | 74 MB/s |
| 16 KB | 75 MB/s |
| 64 KB | 76 MB/s |
| 1 MB sustained | **76 MB/s** |

**Memory roof = 76 MB/s — DMA-engine-limited, not HP-bandwidth-limited**
(~6 % of the ~1200 MB/s HP-port ceiling; the 32-word FIFO engine moves
~0.38 words/cyc @ 50 MHz). Key Roofline point: the bottleneck is the DMA
engine, not the bus.

### B3/B4/B5 — Per-stage MNIST (`demo_mnist_per_stage_two_pass`, N=100, @666 MHz)

| stage | cycles | ms/inf |
|---|---|---|
| Conv1+ReLU (VFP) | 7,914,821 | 11.872 |
| Pool1 (VFP) | 169,574 | 0.254 |
| **Conv2+ReLU (VFP) [B3]** | 8,833,972 | **13.251** |
| Pool2 (VFP) | 49,816 | 0.075 |
| Quantize HWC→CHW | 75,404 | 0.113 |
| ARM-INT FC1 | 3,580,110 | 5.370 |
| ARM-INT FC2 | 89,721 | 0.135 |
| **CGRA FC1 [B4]** | 775,485 | **1.163** |
| CGRA FC2 | 63,996 | 0.096 |
| ROW FC total CGRA | 850,484 | **1.276** |
| ROW FC total ARM-INT | 3,680,731 | 5.521 |
| **Full HW VFP+CGRA (clean) [B5]** | 18,020,345 | **27.030** |
| Full SW VFP+INT | 20,724,319 | 31.086 |
| Full SW INT-only | 28,984,848 | 43.477 |

Accuracy: ARM-INT **94/100**, CGRA **87/100** (CGRA lower from the SPM
auto-inc slot-boundary quirk — argmax-correctness, not exact-match).

### B6 — NEON FC baseline (`bench_neon_fc`, per inference)

| kernel | µs/inf |
|---|---|
| **NEON (vmlal_s16)** | **1011.4** |
| scalar INT | 5520.6 |
| VFP | 4211.0 |

⚠️ NEON argmax pred=6 vs scalar/VFP pred=1 → the 4-accumulator NEON kernel
has a correctness bug (timing valid, result wrong). Needs a separate fix.

## Headline findings

1. **Conv dominates** end-to-end (Conv1 11.9 + Conv2 13.3 = 25 ms of 27 ms);
   conv runs in ARM-VFP float, NOT on the CGRA. The CGRA currently only
   accelerates FC.
2. **FC ranking:** NEON 1.01 ms < CGRA 1.28 ms < ARM-INT 5.52 ms < VFP… —
   the CGRA beats scalar/VFP on FC by 4.3×, but **NEON beats the CGRA** on FC
   (FC is readout-dominated on the CGRA → hetero pipeline should use NEON for FC).
3. **CGRA FC total = 1.276 ms silicon** vs thesis-cited **1.50 ms** — the
   emulator (calibrated to 1.50 ms) **over-predicts FC by ~18 %**; recalibrate
   constants to the 1.276 ms silicon anchor (Phase C2/C3).
4. **Memory roof is DMA-engine-bound** (76 MB/s), a stronger constraint than
   the HP bus — central to the Roofline narrative.

## Follow-ups
- Recalibrate `emulate_full_cnn.py` to silicon (FC 1.276 ms, per-stage table).
- Clean `.xsa` rebuild applying REF's complete DDR config (currently using
  v17 bit + REF ps7_init combo).
- Fix NEON FC 4-accumulator correctness bug.
- Fix `bench_mac_micro` contribs readout (result-FIFO semantics).
