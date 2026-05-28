#!/usr/bin/env python3
"""
analyze_two_pass.py — Phase C1 silicon-data analyzer.

Consumes a UART log from `demo_mnist_per_stage_two_pass.elf` (built with
-DTWO_PASS_PMU=1) and produces the per-layer silicon-anchored cycle
table for the thesis Roofline + emulator-calibration work.

Implements the senior-engineer "two-pass method" per
06_doc/senior_arch_review_2026-05-28.md §29:

  silicon_layer_time = clean_pass_absolute × (instrumented_layer_avg /
                                               instrumented_total)

The clean pass has no per-stage CCNT reads, so its outer-bracket total
is the unperturbed absolute latency. The instrumented pass has CCNT
between every stage; its total is inflated by the observer-effect
overhead, but the *proportional* breakdown of which stage took what
fraction is meaningful. Multiplying the proportions against the clean
total decouples the per-stage decomposition from the instrumentation
overhead.

Usage:
    python3 analyze_two_pass.py UART_LOG_PATH [--clock-mhz 666.67]
"""

import argparse
import re
import sys
from pathlib import Path
from typing import Dict, Optional


# Regex patterns matching demo_mnist_per_stage.c's output format.
# Clean-pass markers come from the #ifdef TWO_PASS_PMU block;
# instrumented-pass markers are the existing put_hex_field lines.

CLEAN_HW_RX = re.compile(r"CLEAN HW \(VFP\+CGRA\):\s*0x([0-9A-Fa-f]+)")
CLEAN_SW_RX = re.compile(r"CLEAN SW \(INT\+INT\)\s*:\s*0x([0-9A-Fa-f]+)")

# Instrumented per-stage lines.  Match the put_hex_field label, then the
# hex cycle count.  Label-to-key mapping below.
INSTR_LINE_RX = re.compile(
    r"(Conv1\+ReLU \(VFP\)|Pool1\s+\(VFP\)|Conv2\+ReLU \(VFP\)|"
    r"Pool2\s+\(VFP\)|Quantize HWC->CHW|CNN-INT Conv\+Pool|"
    r"ARM-INT FC1|ARM-INT FC1-post|ARM-INT FC2|ARM-INT argmax|"
    r"CGRA   FC1|CGRA   FC1-post|CGRA   FC2|CGRA   argmax)\s*:\s*"
    r"0x([0-9A-Fa-f]+)"
)


def parse_log(text: str) -> Dict[str, int]:
    """Return {stage_key: cycles_avg} parsed from the UART log."""
    out: Dict[str, int] = {}
    m = CLEAN_HW_RX.search(text)
    if m:
        out["__clean_hw__"] = int(m.group(1), 16)
    m = CLEAN_SW_RX.search(text)
    if m:
        out["__clean_sw__"] = int(m.group(1), 16)
    for m in INSTR_LINE_RX.finditer(text):
        # Collapse all whitespace runs to a single space so the label
        # key matches the cleaner form used in the `groups` table below
        # (the C-side put_hex_field pads labels with multiple spaces).
        label = " ".join(m.group(1).split())
        cycles = int(m.group(2), 16)
        out[label] = cycles
    return out


def fmt_us(cycles: int, mhz: float) -> str:
    us = cycles / mhz
    return f"{us:>8.1f} us"


def fmt_ms(cycles: int, mhz: float) -> str:
    return f"{cycles / mhz / 1000:>6.3f} ms"


# Stage membership per pipeline. ARM-INT and CGRA paths share the same
# Conv+Pool+Quant front-end but split at FC, so we need to apply the
# two-pass scaling per pipeline (otherwise the clean-pass HW anchor gets
# diluted by the ARM-INT-only stages running in the same instrumented loop).
HW_PIPELINE_KEYS = [
    "Conv1+ReLU (VFP)", "Pool1 (VFP)",
    "Conv2+ReLU (VFP)", "Pool2 (VFP)",
    "Quantize HWC->CHW",
    "CGRA FC1", "CGRA FC1-post", "CGRA FC2", "CGRA argmax",
]
SW_PIPELINE_KEYS = [
    "CNN-INT Conv+Pool",
    "ARM-INT FC1", "ARM-INT FC1-post", "ARM-INT FC2", "ARM-INT argmax",
]


def proportional_breakdown(stages: Dict[str, int],
                            clean_hw: Optional[int],
                            clean_sw: Optional[int]) -> Dict[str, int]:
    """Apply the two-pass method per pipeline:
       silicon_stage = clean_pipeline_total × (stage_cyc / pipeline_total)."""
    out: Dict[str, int] = {}

    if clean_hw is not None:
        hw_instr_total = sum(stages.get(k, 0) for k in HW_PIPELINE_KEYS)
        if hw_instr_total > 0:
            for k in HW_PIPELINE_KEYS:
                if k in stages:
                    out[k] = int(round(stages[k] * clean_hw / hw_instr_total))

    if clean_sw is not None:
        sw_instr_total = sum(stages.get(k, 0) for k in SW_PIPELINE_KEYS)
        if sw_instr_total > 0:
            for k in SW_PIPELINE_KEYS:
                if k in stages:
                    out[k] = int(round(stages[k] * clean_sw / sw_instr_total))

    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("log", help="UART log from per-stage two-pass ELF")
    ap.add_argument("--clock-mhz", type=float, default=666.666667,
                    help="ARM CCNT clock (default 666.67 MHz @ Zynq-7020)")
    ap.add_argument("--csv", help="Optional CSV output path")
    args = ap.parse_args()

    text = Path(args.log).read_text(errors="replace")
    stages = parse_log(text)
    if not stages:
        print(f"ERROR: no recognizable per-stage data in {args.log}",
              file=sys.stderr)
        return 1

    clean_hw = stages.get("__clean_hw__")
    clean_sw = stages.get("__clean_sw__")

    mhz = args.clock_mhz
    print("=" * 68)
    print(f"  Two-pass silicon analysis: {args.log}")
    print(f"  ARM CCNT clock = {mhz:.2f} MHz")
    print("=" * 68)

    # ---- Clean-pass absolute times ----
    if clean_hw is not None:
        print(f"\nClean pass HW (VFP-Conv + CGRA-FC) : "
              f"0x{clean_hw:08X} = {clean_hw:>9d} cyc = {fmt_ms(clean_hw, mhz)}")
    if clean_sw is not None:
        print(f"Clean pass SW (INT-Conv + INT-FC)  : "
              f"0x{clean_sw:08X} = {clean_sw:>9d} cyc = {fmt_ms(clean_sw, mhz)}")
        if clean_hw is not None:
            speedup = clean_sw / clean_hw if clean_hw else 0
            print(f"\n  Speedup (SW / HW) = {speedup:>5.2f}×")

    # ---- Instrumented pass per-stage breakdown ----
    print("\n" + "-" * 68)
    print(f"{'Stage':<28s}  {'instr cyc':>12s}  {'%':>6s}  {'silicon':>10s}")
    print("-" * 68)

    instrumented_total = sum(v for k, v in stages.items()
                             if not k.startswith("__"))
    proportions = proportional_breakdown(stages, clean_hw, clean_sw)

    # Group output by category for readability
    groups = [
        ("Conv front-end (ARM-VFP)", [
            "Conv1+ReLU (VFP)", "Pool1 (VFP)",
            "Conv2+ReLU (VFP)", "Pool2 (VFP)",
            "Quantize HWC->CHW",
        ]),
        ("ARM-INT full pipeline (baseline)", [
            "CNN-INT Conv+Pool",
            "ARM-INT FC1", "ARM-INT FC1-post",
            "ARM-INT FC2", "ARM-INT argmax",
        ]),
        ("CGRA-FC (hetero pipeline)", [
            "CGRA FC1", "CGRA FC1-post",
            "CGRA FC2", "CGRA argmax",
        ]),
    ]

    rows = []
    for header, keys in groups:
        print(f"\n  [{header}]")
        for k in keys:
            if k not in stages:
                continue
            cyc = stages[k]
            pct = (100.0 * cyc / instrumented_total) if instrumented_total else 0
            sil = proportions.get(k, 0)
            print(f"  {k:<28s}  {cyc:>12d}  {pct:>5.1f}%  {fmt_us(sil, mhz)}")
            rows.append((header, k, cyc, pct, sil, sil / mhz))

    # ---- Headline summary ----
    print("\n" + "=" * 68)
    print("  HEADLINE — silicon-anchored per-stage breakdown")
    print("=" * 68)
    # Aggregate into the four canonical buckets for Roofline + thesis Table 5.x
    def sum_keys(ks):
        return sum(proportions.get(k, 0) for k in ks)

    conv1_total = sum_keys(["Conv1+ReLU (VFP)", "Pool1 (VFP)"])
    conv2_total = sum_keys(["Conv2+ReLU (VFP)", "Pool2 (VFP)"])
    quant_total = proportions.get("Quantize HWC->CHW", 0)
    fc1_cgra    = sum_keys(["CGRA FC1", "CGRA FC1-post"])
    fc2_cgra    = proportions.get("CGRA FC2", 0)
    argmax      = proportions.get("CGRA argmax", 0)
    e2e_hw      = clean_hw or sum_keys([k for _, _, k, _, _, _ in rows])

    print(f"  Conv1+Pool1 (VFP)         : {fmt_ms(conv1_total, mhz)}  "
          f"({100*conv1_total/e2e_hw:>4.1f}%)")
    print(f"  Conv2+Pool2 (VFP)         : {fmt_ms(conv2_total, mhz)}  "
          f"({100*conv2_total/e2e_hw:>4.1f}%)")
    print(f"  Quantize HWC->CHW         : {fmt_ms(quant_total, mhz)}  "
          f"({100*quant_total/e2e_hw:>4.1f}%)")
    print(f"  FC1 (CGRA, incl post)     : {fmt_ms(fc1_cgra,    mhz)}  "
          f"({100*fc1_cgra/e2e_hw:>4.1f}%)")
    print(f"  FC2 (CGRA)                : {fmt_ms(fc2_cgra,    mhz)}  "
          f"({100*fc2_cgra/e2e_hw:>4.1f}%)")
    print(f"  argmax (CGRA bias-add)    : {fmt_ms(argmax,      mhz)}  "
          f"({100*argmax/e2e_hw:>4.1f}%)")
    print(f"  {'─' * 60}")
    print(f"  Total (clean-pass anchor) : {fmt_ms(e2e_hw,      mhz)}")

    if args.csv:
        with open(args.csv, "w") as f:
            f.write("category,stage,instrumented_cycles,instrumented_pct,"
                    "silicon_cycles,silicon_us\n")
            for cat, k, c, p, s, us in rows:
                f.write(f'"{cat}","{k}",{c},{p:.2f},{s},{us:.2f}\n')
        print(f"\nCSV written to {args.csv}")

    print()
    return 0


if __name__ == "__main__":
    sys.exit(main())
