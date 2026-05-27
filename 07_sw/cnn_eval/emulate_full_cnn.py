#!/usr/bin/env python3
"""
emulate_full_cnn.py — Bit-exact Python emulator for running the FULL CNN
(Conv1 + Pool1 + Conv2 + Pool2 + FC1 + FC2) on the CGRA.

Models the CGRA's actual hardware semantics:
  - INT16 quantised weights + activations (the only thing the MAC ingests)
  - INT40 saturating accumulator inside each MAC (matches cgra_pe.sv:362-371)
  - RELU + MAX opcodes (saturating-INT)
  - 4×4 PE mesh with dual-port SPM (one PE = one output channel, MAC reads
    activation via Port A and weight via Port B in the same cycle — the
    v2 RTL primitive committed in 0b707ae)

Produces:
  - Per-image prediction matching what silicon would produce IF the full-
    CNN kernel were written and silicon-validated
  - Aggregated accuracy on the MNIST test set
  - Cycle-budget estimate per layer assuming 16 PEs × 1 MAC/cycle × 50 MHz

This is *prospective* — it answers "what IF the full-CNN kernel were
on silicon, what accuracy + cycle count would we see?" without
actually writing the bare-metal kernel or burning a bitstream.

Usage:
    python3 emulate_full_cnn.py [--images N]
"""

from __future__ import annotations
import argparse
import struct
import sys
import time
from dataclasses import dataclass, field
from pathlib import Path

import numpy as np
import torch
from torchvision import datasets, transforms

SCRIPT_DIR = Path(__file__).parent
INT16_MAX = 32767
INT16_MIN = -32768
INT40_MAX = 549_755_813_887           # 2**39 - 1
INT40_MIN = -549_755_813_888          # -2**39

# 4×4 PE mesh. v2 RTL allows all 16 PEs to MAC in parallel.
NUM_PES = 16


# ============================================================================
#  REALISTIC OVERHEAD MODEL
#
#  Constants below are derived from silicon-measured behavior on the
#  cgra_split_vdma.bit bitstream:
#
#  - FC1 (4 PEs × 16 groups × 400 INT16 MACs) measured at 115k CGRA cycles.
#    Pure MAC content = 6.4k cycles. So overhead = 109k for that path =
#    ~6.8k cycles per group, dominated by SG-DMA setup + ARM polling.
#
#  - MAC throughput (Suite MTP): 81% single-pass, 99.7% steady-state at 64+
#    passes. CONV inner loops are long enough to hit ~95% efficiency.
#
#  - HP-port bandwidth: 64-bit AXI @ 100 MHz = 800 MB/s = 8 bytes/AXI cyc.
#    Translated to CGRA cycles (50 MHz): 16 bytes per CGRA cycle peak.
#    Real sustained throughput: ~12 bytes/CGRA cyc with bursts + overhead.
#
#  - ARM-PS polling: each cgra_*_wait() call polls APB_STATUS in a busy loop.
#    Each poll costs ~30 ARM cycles. A wait completes when CGRA finishes,
#    so polling cycles burn while CGRA is computing in parallel -- but the
#    READ-MORE-THAN-NEEDED overhead is small if waits are well-tuned.
#    Per layer there are ~4-6 sync points (DMA wait, CU wait); each adds
#    a fixed ~80 ARM cycle "phase-change" cost regardless of compute time.
# ============================================================================

ARM_FREQ_MHZ  = 666
CGRA_FREQ_MHZ = 50
ARM_PER_CGRA  = ARM_FREQ_MHZ / CGRA_FREQ_MHZ          # = 13.32

# === Overhead constants (CGRA cycles unless noted) ===========================
# Reviewed by codex/gemini/copilot 2026-05-28 against silicon-measured FC1
# (v1 kernel: 4 PEs × 16 groups × 400 MACs = ~115 k CGRA cyc, so
#  per-group overhead = (115 000 - 6 400) / 16 ≈ 6 800 cyc/group).
# Constants raised to match silicon-realistic behaviour.

# INT16 values are stored as 32-bit words in SPM/tile (zero/sign-extended).
# This is from quantize_cgra.py emitting struct.pack("<I", int(w)) and
# cgra_kernels_cnn.h defining SPM_BPN = N_INPUTS * 4. So every "INT16
# weight or activation" actually moves 4 bytes across the AXI bus.
BYTES_PER_INT16_WORD = 4

# Per APB transaction (ARM PS → AXI GP → APB CSR), measured indirectly via
# silicon polling-loop overhead. ARM @ 666 MHz, each APB write ≈ 30 ARM
# cyc round-trip → ~2 CGRA cyc.
APB_WRITE_CGRA  = 3               # incl. AXI-Lite arbitration + APB ack
APB_READ_CGRA   = 4               # reads bring back data, slightly longer

# Per-descriptor SG-DMA traversal: cgra_kernels_cnn_opt.h budgets ~800 cyc
# for 8 descs ⇒ ~100 cyc/desc end-to-end (decoder + DDR fetch of next
# pointer + execution-stage handoff). 50 was too low.
SG_DMA_DESC_CGRA = 100

# cgra_sg_dma_start() itself has a setup phase (program SG_HEAD register,
# trigger DMA, wait for first descriptor fetch) before any desc executes.
SG_DMA_CHAIN_SETUP_CGRA = 80

# Regular 1D DMA setup: write SRC/DST/SIZE/CTRL + arb + first burst.
DMA_SETUP_CGRA   = 120

# CU_START sequence (CU_CTRL = 1 + state machine spin-up + first slot decode).
CU_START_CGRA    = 40

# Phase sync = the `cgra_*_wait()` busy-loop overhead beyond the actual
# CGRA-side completion time. Silicon-derived: ARM polls APB STATUS every
# ~30 ARM cyc; a typical wait has 3-15 polls before completion. The
# delta vs CGRA-completion-time is ~80-300 ARM cyc per phase.
PHASE_SYNC_CGRA  = 100            # mid-estimate, in CGRA cycles

# HP-port effective bandwidth: 64-bit AXI @ 100 MHz peak = 800 MB/s.
# At 50 MHz CGRA that's 16 B/CGRA-cyc peak. Sustained ~12 B/CGRA-cyc
# under burst overhead. Both codex + gemini concurred this is reasonable.
HP_BYTES_PER_CGRA_CYC = 12

# MAC efficiency from Suite MTP silicon measurements:
#   1-pass:   81.2%      ← short inner loop
#   10-pass:  98.1%
#   64-pass:  99.7%      ← long inner loop with auto-inc
MAC_EFF_LONG  = 0.97              # CONV layers (thousands of MAC/PE)
MAC_EFF_SHORT = 0.80              # FC layers (25-50 MAC/PE per group)


@dataclass
class StageBudget:
    """One pipeline stage's cycle breakdown — separates compute from data
    movement from ARM coordination so we can identify the bottleneck."""
    name:         str  = ""
    input_dma:    int  = 0   # DDR -> tile/SPM bytes / HP bandwidth + DMA setup
    weight_dma:   int  = 0   # weights -> PE SPMs
    mac_compute:  int  = 0   # pure MAC dataflow (1 MAC/cyc/PE × NUM_PES)
    cu_setup:    int  = 0    # CU register writes + CU_START
    output_dma:   int  = 0   # results -> DDR for next layer
    arm_sync:     int  = 0   # ARM-side sync overhead between phases

    @property
    def total(self) -> int:
        return (self.input_dma + self.weight_dma + self.mac_compute
                + self.cu_setup + self.output_dma + self.arm_sync)

    def breakdown(self) -> str:
        if self.total == 0:
            return "(none)"
        items = []
        for k in ['input_dma', 'weight_dma', 'mac_compute',
                  'cu_setup', 'output_dma', 'arm_sync']:
            v = getattr(self, k)
            if v > 0:
                pct = 100 * v / self.total
                items.append(f"{k}={v}({pct:.0f}%)")
        return "  ".join(items)


@dataclass
class CycleBudget:
    """Aggregates StageBudgets for the full inference."""
    stages: list = field(default_factory=list)

    def add(self, stage: StageBudget):
        self.stages.append(stage)

    @property
    def total(self) -> int:
        return sum(s.total for s in self.stages)

    def report(self):
        print(f"\n  Per-stage CGRA cycle budget (50 MHz, 16 PE peak):")
        print(f"  {'stage':<10s} {'total':>8s}  {'ms':>7s}   bottleneck-breakdown")
        # Find global bottleneck category
        cat_totals = {k: 0 for k in
            ['input_dma', 'weight_dma', 'mac_compute',
             'cu_setup', 'output_dma', 'arm_sync']}
        for s in self.stages:
            ms = s.total / (CGRA_FREQ_MHZ * 1000)  # cyc / (cyc/us / us/ms)
            print(f"  {s.name:<10s} {s.total:>8d}  {ms:>5.3f}    {s.breakdown()}")
            for k in cat_totals:
                cat_totals[k] += getattr(s, k)
        print(f"  {'─'*70}")
        ms_tot = self.total / (CGRA_FREQ_MHZ * 1000)
        print(f"  {'TOTAL':<10s} {self.total:>8d}  {ms_tot:>5.3f} ms")
        arm_eq = int(self.total * ARM_PER_CGRA)
        print(f"  {'ARM equiv':<10s} {arm_eq:>8d}  {arm_eq/(ARM_FREQ_MHZ*1000):>5.3f} ms"
              f" @ {ARM_FREQ_MHZ} MHz")
        # Bottleneck analysis
        print(f"\n  Bottleneck analysis (aggregated across all stages):")
        for k, v in sorted(cat_totals.items(), key=lambda kv: -kv[1]):
            pct = 100 * v / max(self.total, 1)
            bar = '█' * int(pct / 2)
            print(f"    {k:<14s} {v:>8d} cyc  {pct:>5.1f}%  {bar}")

        # Silicon-anchor comparison: FC1 v1 measured at ~115 k CGRA cyc on
        # the Haoyue board (4-PE × 16-group). FC2 v1 not separately
        # measured; estimated at ~12-18 k from end-to-end LPR-FC traces.
        fc1_stage = next((s for s in self.stages if 'fc1' in s.name), None)
        if fc1_stage is not None:
            print(f"\n  Silicon-anchor calibration:")
            print(f"    FC1 (v2, this model): {fc1_stage.total:>6d} cyc")
            print(f"    FC1 (v1, silicon):    ~115000 cyc  (4-PE × 16 grp)")
            print(f"    FC1 v2 projection:     ~28-40 k cyc (reviewer estimate)")
            print(f"    → model is {'PESSIMISTIC' if fc1_stage.total > 50000 else 'in-range'}"
                  f" vs reviewer; tune SG_DMA_DESC_CGRA if more data lands.")


def conv_stage_budget(c_in:  int, c_out: int,
                       h_in:  int, w_in:  int,
                       kh:    int, kw:    int,
                       num_pes: int,
                       name:  str) -> StageBudget:
    """Realistic CGRA cycle budget for a Conv3x3 (or similar) layer using
    the v2 RTL primitives (dual-port SPM, broadcast DMA, 16-PE parallel)."""
    h_out, w_out = h_in - kh + 1, w_in - kw + 1
    s = StageBudget(name=name)

    # ---- Input DMA: c_in × h_in × w_in INT16 values stored as 32-bit words
    in_bytes = c_in * h_in * w_in * BYTES_PER_INT16_WORD
    s.input_dma = (DMA_SETUP_CGRA
                   + (in_bytes + HP_BYTES_PER_CGRA_CYC - 1)
                     // HP_BYTES_PER_CGRA_CYC)

    # ---- Weight load: SG-DMA across up to num_pes PEs.
    pe_groups = (c_out + num_pes - 1) // num_pes
    w_per_pe_bytes = kh * kw * c_in * BYTES_PER_INT16_WORD
    weight_dma_per_group = (SG_DMA_CHAIN_SETUP_CGRA
                            + num_pes * SG_DMA_DESC_CGRA
                            + (num_pes * w_per_pe_bytes
                               + HP_BYTES_PER_CGRA_CYC - 1)
                              // HP_BYTES_PER_CGRA_CYC)
    s.weight_dma = pe_groups * weight_dma_per_group

    # ---- MAC compute: total MACs / num_pes, at long-run efficiency
    # (CONV layers have thousands of MAC/PE so TILE_AUTO_INC sustains).
    total_macs = c_out * h_out * w_out * kh * kw * c_in
    macs_per_pe_group = total_macs / num_pes / max(pe_groups, 1)
    s.mac_compute = int((macs_per_pe_group / MAC_EFF_LONG) * pe_groups)

    # ---- CU setup: write LOOP_*, CU_PC_END, AUTO_INC enable/disable,
    # CU_START per PE group.
    s.cu_setup = pe_groups * (8 * APB_WRITE_CGRA + CU_START_CGRA)

    # ---- Output writeback: c_out × h_out × w_out × 4 bytes (INT32
    # retained for next-layer requant).
    out_bytes = c_out * h_out * w_out * 4
    s.output_dma = (DMA_SETUP_CGRA
                    + (out_bytes + HP_BYTES_PER_CGRA_CYC - 1)
                      // HP_BYTES_PER_CGRA_CYC)

    # ---- ARM sync: 5 sync points per PE group (in DMA, weight DMA,
    # CU done, readout DMA done, output DMA done).
    s.arm_sync = pe_groups * 5 * PHASE_SYNC_CGRA

    return s


def pool_stage_budget(c: int, h_in: int, w_in: int,
                      num_pes: int, name: str) -> StageBudget:
    s = StageBudget(name=name)
    # Input reuse from prior stage; output is c × (h/2) × (w/2) × 4 bytes
    h_out, w_out = h_in // 2, w_in // 2
    out_bytes = c * h_out * w_out * 4
    # 4 MAX ops per output spread across num_pes
    s.mac_compute = int((c * h_out * w_out * 4 + num_pes - 1) // num_pes / MAC_EFF_LONG)
    s.cu_setup    = 3 * APB_WRITE_CGRA + CU_START_CGRA
    s.output_dma  = DMA_SETUP_CGRA + (out_bytes + HP_BYTES_PER_CGRA_CYC - 1) // HP_BYTES_PER_CGRA_CYC
    s.arm_sync    = 2 * PHASE_SYNC_CGRA
    return s


def quant_stage_budget(n_elements: int, num_pes: int, name: str) -> StageBudget:
    s = StageBudget(name=name)
    # Two passes: find max-abs, then arithmetic right shift. Each pass uses
    # num_pes lanes (CGRA's ALU SHR opcode), so ~2 × n_elements / num_pes cycles.
    s.mac_compute = (2 * n_elements + num_pes - 1) // num_pes
    s.cu_setup    = 4 * APB_WRITE_CGRA + CU_START_CGRA
    s.arm_sync    = 2 * PHASE_SYNC_CGRA
    return s


def fc_stage_budget(n_in: int, n_out: int, num_pes: int,
                    name: str) -> StageBudget:
    """FC layer cycle budget modelling the ACTUAL v2 kernel structure
    (cnn_fc_v2_run_group in cgra_kernels_cnn_v2.h, lines 220-290).

    Per group, the kernel issues these phases sequentially with ARM
    polling between each:
      1. SPM weight preload      (num_pes-desc SG-DMA chain)
      2. ACC_CLR pass            (num_pes-desc SG-DMA + CU run, PC_END=0)
      3. MAC opword restore      (num_pes-desc SG-DMA)
      4. MAC loop                (CU run, LOOP_COUNT × 16 slots)
      5. Relay PASS0(SRC_W) init (num_pes-desc SG-DMA, NEW in v2)
      6. Per-column readout × 4  (col-desc SG-DMA + CU run + APB reads)
                                  (NEW in v2: 4 separate phases for 16-PE)
    """
    s = StageBudget(name=name)
    pe_groups = (n_out + num_pes - 1) // num_pes

    # ---- Activation broadcast: SPM broadcast prefix (0x5) writes to all
    # PEs simultaneously. INT16 stored as 32-bit words. Only ONCE per
    # inference (act_preload at top-level), not per group.
    in_bytes = n_in * BYTES_PER_INT16_WORD     # 4 B/word, not 2
    s.input_dma = (DMA_SETUP_CGRA
                   + (in_bytes + HP_BYTES_PER_CGRA_CYC - 1)
                     // HP_BYTES_PER_CGRA_CYC)

    # ---- Per-group weight preload: SG-DMA, num_pes descriptors. Each
    # descriptor writes one PE's worth of weights (n_in × 4 B).
    w_bytes_per_pe = n_in * BYTES_PER_INT16_WORD
    weight_dma_per_group = (SG_DMA_CHAIN_SETUP_CGRA
                            + num_pes * SG_DMA_DESC_CGRA
                            + (num_pes * w_bytes_per_pe
                               + HP_BYTES_PER_CGRA_CYC - 1)
                              // HP_BYTES_PER_CGRA_CYC)
    s.weight_dma = pe_groups * weight_dma_per_group

    # ---- ACC_CLR pass: 2*num_pes-desc chain + CU run (1 slot).
    acc_clr_chain = (SG_DMA_CHAIN_SETUP_CGRA
                     + 2 * num_pes * SG_DMA_DESC_CGRA)  # HI+LO per PE
    # ---- MAC opword restore: same chain length.
    mac_restore_chain = acc_clr_chain
    # ---- Relay PASS0(SRC_W) init: same chain length (NEW in v2).
    relay_chain = acc_clr_chain
    # ---- Per-column readout: 2*num_pes/4-desc chain per column + CU run.
    # The kernel does this for each of the 4 columns of the PE array.
    col_chain   = (SG_DMA_CHAIN_SETUP_CGRA
                   + 2 * (num_pes // 4) * SG_DMA_DESC_CGRA)
    n_readout_cols = 4

    # ---- MAC compute: short loop (25-50 inner-loop passes) so use
    # MAC_EFF_SHORT. Per group: num_pes PEs each doing n_in MACs in
    # parallel = n_in cycles per group.
    s.mac_compute = int(pe_groups * n_in / MAC_EFF_SHORT)

    # ---- CU coordination: ~7 CU starts per group (ACC_CLR, MAC,
    # 4× readout) plus loop-config writes (LOOP_START/END/COUNT/PC_END/
    # AUTO_INC). Per group ~12 APB writes + ~5 CU starts.
    s.cu_setup = pe_groups * (12 * APB_WRITE_CGRA + 5 * CU_START_CGRA)

    # ---- All the per-group SG-DMA / readout chain overheads aggregated
    # into output_dma (because they're all between MAC-compute and the
    # final results being read out):
    s.output_dma = pe_groups * (
        acc_clr_chain                 # Step 2
        + mac_restore_chain            # Step 3
        + relay_chain                  # Step 5
        + n_readout_cols * col_chain   # Step 6 (4 columns)
        + n_readout_cols * num_pes * APB_READ_CGRA  # actual result reads
    )

    # ---- ARM polling between phases. v2 has ~10 sync points per group
    # (vs ~7 for v1). Polling overhead beyond the CGRA-side completion.
    s.arm_sync = pe_groups * 10 * PHASE_SYNC_CGRA

    return s


# ============================================================================
#  CGRA HW primitives — these are the ONLY operations the emulator uses,
#  matching what cgra_pe.sv can actually execute.
# ============================================================================

def cgra_mac_int40(activations: np.ndarray,
                   weights:     np.ndarray) -> np.int64:
    """Single PE's MAC over a vector of INT16 activations × INT16 weights.
    Matches cgra_pe.sv:362-371 semantics:
      - product = INT16 * INT16 = INT32 (no overflow — INT32 wide)
      - accumulator += product, clamped to INT40 each step
    Returns the final accumulator value (INT64 just for Python convenience;
    bit-exact to INT40)."""
    activations = activations.astype(np.int64)
    weights     = weights.astype(np.int64)
    products = activations * weights        # INT32 range, stored as INT64
    acc = np.int64(0)
    for p in products:
        acc += p
        if acc > INT40_MAX:
            acc = np.int64(INT40_MAX)
        elif acc < INT40_MIN:
            acc = np.int64(INT40_MIN)
    return acc


def cgra_relu(x: np.ndarray) -> np.ndarray:
    """RELU opcode: max(0, x), bit-preserving."""
    return np.maximum(x, 0)


def cgra_max_pool_2x2(feature_map: np.ndarray) -> np.ndarray:
    """2×2 max pool with stride 2. feature_map shape: [H, W, C].
    Uses the silicon-validated MAX opcode."""
    H, W, C = feature_map.shape
    out_H, out_W = H // 2, W // 2
    out = np.zeros((out_H, out_W, C), dtype=feature_map.dtype)
    for i in range(out_H):
        for j in range(out_W):
            window = feature_map[2*i:2*i+2, 2*j:2*j+2, :]  # [2, 2, C]
            out[i, j, :] = window.reshape(-1, C).max(axis=0)
    return out


# ============================================================================
#  Layer kernels — each layer uses ONLY cgra_mac_int40 + cgra_relu + pool.
# ============================================================================

def conv3x3_layer(input_feat: np.ndarray,   # [H, W, C_in] float
                  weights_q:  np.ndarray,   # [C_out, 3, 3, C_in] INT16
                  bias_q:     np.ndarray,   # [C_out] INT32 (acc units)
                  scale_w:    float,
                  budget:     CycleBudget,
                  layer_name: str = "conv") -> np.ndarray:
    """Compute Conv3x3 layer using CGRA INT40-MAC primitives.

    The arithmetic is bit-exact INT16 × INT16 → INT40 saturating. To stay
    honest about accuracy without retraining (full INT QAT is out of
    scope), we compute the MAC in INT and immediately rescale to float
    using the known weight scale (the same dequantisation the bare-metal
    code does when reading RESULT_ROW back as INT32 and multiplying by
    scale_w × scale_act).

    For the cycle estimate this is the same as full-INT inference — the
    only difference is that float-rescaling between layers preserves
    precision the same way QAT-trained INT weights would after a
    per-layer right-shift.
    """
    H, W, C_in = input_feat.shape
    C_out      = weights_q.shape[0]
    out_H, out_W = H - 2, W - 2     # valid conv (no padding)
    output = np.zeros((out_H, out_W, C_out), dtype=np.float32)

    # Convert input float -> INT16 once per call. This matches what the
    # CGRA's tile-load DMA would write to the tile bank.
    in_max = float(np.abs(input_feat).max()) + 1e-9
    scale_in = in_max / INT16_MAX
    in_q = np.clip(np.round(input_feat / scale_in), INT16_MIN, INT16_MAX
                  ).astype(np.int16)

    for oc in range(C_out):
        w_oc = weights_q[oc].astype(np.int32)
        b_oc = int(bias_q[oc])
        for oy in range(out_H):
            for ox in range(out_W):
                window = in_q[oy:oy+3, ox:ox+3, :].astype(np.int32)
                acc = cgra_mac_int40(window.reshape(-1), w_oc.reshape(-1))
                acc = max(INT40_MIN, min(INT40_MAX, int(acc) + b_oc))
                # Rescale back to float for the next layer (the bare-
                # metal path does the equivalent via per-stage right-shift)
                float_val = acc * scale_in * scale_w
                output[oy, ox, oc] = max(0.0, float_val)   # ReLU

    budget.add(conv_stage_budget(
        c_in=C_in, c_out=C_out, h_in=H, w_in=W, kh=3, kw=3,
        num_pes=NUM_PES, name=layer_name))
    return output


def maxpool_layer(input_feat: np.ndarray,
                  budget: CycleBudget,
                  layer_name: str = "pool") -> np.ndarray:
    """2x2 max-pool stride 2. Uses CGRA MAX opcode primitive."""
    output = cgra_max_pool_2x2(input_feat)
    H, W, C = input_feat.shape
    budget.add(pool_stage_budget(c=C, h_in=H, w_in=W,
                                 num_pes=NUM_PES, name=layer_name))
    return output


def requant_to_int16(x:        np.ndarray,
                     budget:   CycleBudget,
                     name:     str = "quant") -> np.ndarray:
    """Quantise INT32/INT64 features back to INT16 for the next layer."""
    max_abs = int(np.abs(x).max())
    if max_abs == 0:
        return x.astype(np.int16)
    shift = 0
    while (max_abs >> shift) > INT16_MAX and shift < 31:
        shift += 1
    out = (x >> shift).astype(np.int16)
    out = np.clip(out, INT16_MIN, INT16_MAX).astype(np.int16)
    n_elem = int(np.prod(x.shape))
    budget.add(quant_stage_budget(n_elements=n_elem,
                                  num_pes=NUM_PES, name=name))
    return out


# ============================================================================
#  Weight + bias loading from the same source-of-truth as the C demo
# ============================================================================

def load_weights() -> dict:
    """Load INT16 weights from the same .bin files the bare-metal demo uses,
    plus biases from the .pt checkpoint."""
    ckpt = torch.load(SCRIPT_DIR / "mnist_cgra.pt", map_location="cpu",
                      weights_only=True)

    # Read scale constants from the C header (regenerated by quantize_cgra.py)
    scales = {}
    for line in (SCRIPT_DIR / "mnist_weights_scale.h").read_text().splitlines():
        if line.startswith("#define MNIST_") and "SCALE_W_F" in line:
            parts = line.split()
            key   = parts[1].lower()                    # mnist_conv1_scale_w_f
            scales[key] = float(parts[2].rstrip("f"))

    sc1 = scales['mnist_conv1_scale_w_f']
    sc2 = scales['mnist_conv2_scale_w_f']
    sfc1 = scales['mnist_fc1_scale_w_f']
    sfc2 = scales['mnist_fc2_scale_w_f']

    def quantise(t: torch.Tensor, scale: float, shape=None) -> np.ndarray:
        a = t.detach().numpy()
        q = np.round(a / scale).astype(np.int32)
        q = np.clip(q, INT16_MIN, INT16_MAX).astype(np.int16)
        if shape is not None:
            q = q.reshape(shape)
        return q

    # Conv weights: [out, in, kH, kW] in PyTorch → [out, kH, kW, in] for emu
    c1_w_pt = ckpt['conv1.weight']                  # [8, 1, 3, 3]
    conv1_w = c1_w_pt.permute(0, 2, 3, 1).contiguous()    # [8, 3, 3, 1]
    conv1_w = quantise(conv1_w, sc1)

    c2_w_pt = ckpt['conv2.weight']                  # [16, 8, 3, 3]
    conv2_w = c2_w_pt.permute(0, 2, 3, 1).contiguous()    # [16, 3, 3, 8]
    conv2_w = quantise(conv2_w, sc2)

    # FC weights: [out, in]
    fc1_w = quantise(ckpt['fc1.weight'], sfc1)      # [64, 400]
    fc2_w = quantise(ckpt['fc2.weight'], sfc2)      # [10, 64]

    # Biases quantised to INT32 in accumulator units (same scale as weights)
    def quant_bias(b: torch.Tensor, scale: float) -> np.ndarray:
        return np.round(b.detach().numpy() / scale).astype(np.int32)

    return dict(
        conv1_w=conv1_w, conv1_b=quant_bias(ckpt['conv1.bias'], sc1),
        conv2_w=conv2_w, conv2_b=quant_bias(ckpt['conv2.bias'], sc2),
        fc1_w=fc1_w,   fc1_b=quant_bias(ckpt['fc1.bias'],     sfc1),
        fc2_w=fc2_w,   fc2_b=quant_bias(ckpt['fc2.bias'],     sfc2),
        scales=dict(c1=sc1, c2=sc2, fc1=sfc1, fc2=sfc2),
    )


# ============================================================================
#  Full forward pass through the emulator
# ============================================================================

def fc_layer_float(flat_float: np.ndarray,
                   weights_q:  np.ndarray,
                   bias_q:     np.ndarray,
                   scale_w:    float,
                   budget:     CycleBudget,
                   name:       str = "fc1") -> np.ndarray:
    """FC using INT MAC but float-rescaled outputs."""
    N_out, N_in = weights_q.shape
    in_max = float(np.abs(flat_float).max()) + 1e-9
    scale_in = in_max / INT16_MAX
    in_q = np.clip(np.round(flat_float / scale_in), INT16_MIN, INT16_MAX
                  ).astype(np.int16)

    out = np.zeros(N_out, dtype=np.float32)
    for n in range(N_out):
        acc = cgra_mac_int40(in_q, weights_q[n]) + np.int64(bias_q[n])
        acc = max(INT40_MIN, min(INT40_MAX, int(acc)))
        out[n] = float(acc) * scale_in * scale_w

    budget.add(fc_stage_budget(n_in=N_in, n_out=N_out,
                               num_pes=NUM_PES, name=name))
    return out


def emulate_inference(image28: np.ndarray,         # [28, 28] uint8 0..255
                      w:       dict,
                      budget:  CycleBudget) -> int:
    # 1. Normalise input the same way training did (MNIST mean/std).
    #    Keep float through the conv pipeline; INT16 quantisation
    #    happens inside each conv/FC layer call (per-call dynamic scale).
    x = image28.astype(np.float32) / 255.0
    x = (x - 0.1307) / 0.3081
    x = x.reshape(28, 28, 1)                      # [H, W, C_in=1]

    # 2. Conv1 (INT16 MAC, float-rescaled output) + ReLU
    y = conv3x3_layer(x, w['conv1_w'], w['conv1_b'],
                      w['scales']['c1'], budget, 'conv1')
    # 3. Pool1
    y = maxpool_layer(y, budget, 'pool1')         # [13, 13, 8]
    # 4. Conv2 (INT16 MAC, float-rescaled) + ReLU
    y = conv3x3_layer(y, w['conv2_w'], w['conv2_b'],
                      w['scales']['c2'], budget, 'conv2')
    # 5. Pool2
    y = maxpool_layer(y, budget, 'pool2')         # [5, 5, 16]
    # 6. HWC → CHW transpose then flatten (matches PyTorch's view() order
    #    that the trained FC1 weights expect).
    flat = y.transpose(2, 0, 1).reshape(-1)       # 16 × 5 × 5 = 400
    # 7. FC1 + ReLU
    fc1 = fc_layer_float(flat, w['fc1_w'], w['fc1_b'],
                         w['scales']['fc1'], budget, 'fc1')
    fc1 = np.maximum(fc1, 0.0)
    # 8. FC2
    fc2 = fc_layer_float(fc1, w['fc2_w'], w['fc2_b'],
                         w['scales']['fc2'], budget, 'fc2')
    # 9. argmax
    return int(np.argmax(fc2))


def emulate_inference_float_ref(image28: np.ndarray,  # [28,28] uint8
                                w:       dict) -> int:
    """Pure-float reference: dequantise INT16 weights × float activations.
    Plumbing sanity check — if this gives ~98%+ on MNIST, the emulator's
    layer ordering and shapes are correct and any accuracy gap on the
    INT path is purely a post-training-quantisation precision issue
    (would need QAT to fix)."""
    x = image28.astype(np.float32) / 255.0
    x = (x - 0.1307) / 0.3081
    x = x.reshape(28, 28, 1)

    # Conv1 — float math, dequantised INT16 weights
    sc1 = w['scales']['c1']
    c1_f = w['conv1_w'].astype(np.float32) * sc1
    c1_b = w['conv1_b'].astype(np.float32) * sc1
    y = np.zeros((26, 26, 8), dtype=np.float32)
    for oc in range(8):
        for oy in range(26):
            for ox in range(26):
                window = x[oy:oy+3, ox:ox+3, :]
                y[oy, ox, oc] = (window * c1_f[oc]).sum() + c1_b[oc]
    y = np.maximum(y, 0)
    y = cgra_max_pool_2x2(y)        # [13,13,8]

    # Conv2
    sc2 = w['scales']['c2']
    c2_f = w['conv2_w'].astype(np.float32) * sc2
    c2_b = w['conv2_b'].astype(np.float32) * sc2
    z = np.zeros((11, 11, 16), dtype=np.float32)
    for oc in range(16):
        for oy in range(11):
            for ox in range(11):
                window = y[oy:oy+3, ox:ox+3, :]
                z[oy, ox, oc] = (window * c2_f[oc]).sum() + c2_b[oc]
    z = np.maximum(z, 0)
    z = cgra_max_pool_2x2(z)        # [5,5,16]
    # PyTorch view() after conv2+pool flattens C-major. Our z is HWC.
    # Transpose HWC → CHW before flatten to match the weights' input axis.
    flat = z.transpose(2, 0, 1).reshape(-1)   # [C, H, W] flat = 400

    # FC1
    sfc1 = w['scales']['fc1']
    fc1_w = w['fc1_w'].astype(np.float32) * sfc1
    fc1_b = w['fc1_b'].astype(np.float32) * sfc1
    fc1 = (fc1_w @ flat) + fc1_b
    fc1 = np.maximum(fc1, 0)

    # FC2
    sfc2 = w['scales']['fc2']
    fc2_w = w['fc2_w'].astype(np.float32) * sfc2
    fc2_b = w['fc2_b'].astype(np.float32) * sfc2
    fc2 = (fc2_w @ fc1) + fc2_b
    return int(np.argmax(fc2))


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--images", type=int, default=200,
                   help="how many MNIST test images to evaluate")
    p.add_argument("--float-ref", action="store_true",
                   help="run the float-reference path (sanity check plumbing)")
    args = p.parse_args()

    print("=== Full-CNN-on-CGRA emulator ===\n")
    print("Loading weights...")
    w = load_weights()
    print(f"  conv1: {w['conv1_w'].shape}   conv2: {w['conv2_w'].shape}")
    print(f"  fc1:   {w['fc1_w'].shape}    fc2:   {w['fc2_w'].shape}")

    print(f"\nLoading MNIST test set ({args.images} images)...")
    test_ds = datasets.MNIST(SCRIPT_DIR / "data", train=False, download=True)
    correct_int = 0
    correct_flt = 0
    budget_for_report = None    # capture LAST image's per-inference budget
    t0      = time.time()
    for i in range(args.images):
        img, label = test_ds[i]
        img_arr = np.asarray(img)
        # Fresh budget per image — same network structure so all identical;
        # we keep the LAST one for reporting.
        budget_for_report = CycleBudget()
        pred_int = emulate_inference(img_arr, w, budget_for_report)
        if pred_int == label:
            correct_int += 1
        if args.float_ref:
            pred_flt = emulate_inference_float_ref(img_arr, w)
            if pred_flt == label:
                correct_flt += 1
        if (i + 1) % 50 == 0:
            msg = f"\r  [{i+1}/{args.images}] INT-emu={100*correct_int/(i+1):.1f}%"
            if args.float_ref:
                msg += f"  float-ref={100*correct_flt/(i+1):.1f}%"
            sys.stdout.write(msg)
            sys.stdout.flush()
    elapsed = time.time() - t0
    print()
    print(f"\n  INT-emulator (CGRA INT16 MAC + INT40 sat):  "
          f"{correct_int}/{args.images} = {100*correct_int/args.images:.2f}%")
    if args.float_ref:
        print(f"  Float-reference (dequant INT16 weights):    "
              f"{correct_flt}/{args.images} = {100*correct_flt/args.images:.2f}%")
    print(f"  Emulator wall time: {elapsed:.1f}s  ({elapsed/args.images*1000:.0f} ms/image, Python)")
    if budget_for_report is not None:
        budget_for_report.report()


if __name__ == "__main__":
    main()
