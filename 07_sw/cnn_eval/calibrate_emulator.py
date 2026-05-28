#!/usr/bin/env python3
"""
calibrate_emulator.py — Phase C2 prep.

Given silicon per-layer cycle measurements (from analyze_two_pass.py's
CSV output, or hand-entered), this script:

  1. Runs the current emulate_full_cnn.py and parses its per-layer
     predictions.
  2. Computes the relative error per layer (silicon vs emulator).
  3. If error exceeds ±10% on any pillar, proposes which constants in
     emulate_full_cnn.py to adjust and by how much — using a simple
     linear sensitivity model:
        * MAC-compute layers (Conv) overrun → MAC_EFF_SHORT too high
        * Memory-bound layers (FC) overrun → SG_DMA_DESC_CGRA /
          SG_DMA_CHAIN_SETUP_CGRA / PHASE_SYNC_CGRA too low
  4. Optionally applies the corrections (--apply) and re-runs to confirm.

Per senior review §19: target ±5-10% on all four pillars to call the
emulator "reviewer-grade".

Usage:
    # Inspect current error
    python3 calibrate_emulator.py --silicon path/to/roofline_data.csv

    # Apply automatic adjustments (writes emulate_full_cnn.py in place)
    python3 calibrate_emulator.py --silicon ... --apply

Inputs:
  - --silicon: CSV path with columns:
        layer,ai_mac_per_byte,silicon_ms,silicon_gops,...
    Emit this with analyze_two_pass.py --csv after the per-stage two-pass
    silicon run.
"""

import argparse
import csv
import re
import subprocess
import sys
from pathlib import Path


CGRA_FREQ_MHZ = 50.0
ARM_FREQ_MHZ  = 666.666667


# Constants in emulate_full_cnn.py that affect each pillar.
# Format: (regex pattern, current default, "lower error if increase" direction)
TUNABLES = {
    # Constant name              regex to find it in source
    "MAC_EFF_SHORT":           r"^MAC_EFF_SHORT\s*=\s*([\d.]+)",
    "MAC_EFF_LONG":            r"^MAC_EFF_LONG\s*=\s*([\d.]+)",
    "SG_DMA_DESC_CGRA":        r"^SG_DMA_DESC_CGRA\s*=\s*(\d+)",
    "SG_DMA_CHAIN_SETUP_CGRA": r"^SG_DMA_CHAIN_SETUP_CGRA\s*=\s*(\d+)",
    "PHASE_SYNC_CGRA":         r"^PHASE_SYNC_CGRA\s*=\s*(\d+)",
    "APB_WRITE_CGRA":          r"^APB_WRITE_CGRA\s*=\s*(\d+)",
    "DMA_SETUP_CGRA":          r"^DMA_SETUP_CGRA\s*=\s*(\d+)",
    "HP_BYTES_PER_CGRA_CYC":   r"^HP_BYTES_PER_CGRA_CYC\s*=\s*(\d+)",
}


def read_silicon_csv(path: Path) -> dict[str, float]:
    """Return {layer: silicon_ms} from the roofline CSV."""
    out: dict[str, float] = {}
    with open(path) as f:
        # Skip leading commented lines
        rows = [r for r in csv.DictReader(
            (line for line in f if not line.startswith("#"))
        )]
    for r in rows:
        layer = r.get("layer", "").strip()
        sms = r.get("silicon_ms", "").strip()
        if not layer or sms.lower() in ("", "pending", "n/a"):
            continue
        try:
            out[layer] = float(sms)
        except ValueError:
            continue
    return out


def run_emulator() -> str:
    """Run emulate_full_cnn.py and capture its stdout."""
    here = Path(__file__).parent
    result = subprocess.run(
        [sys.executable, str(here / "emulate_full_cnn.py"),
         "--images", "10", "--float-ref"],
        capture_output=True, text=True
    )
    if result.returncode != 0:
        print(f"emulate_full_cnn.py failed:\n{result.stderr}", file=sys.stderr)
        sys.exit(1)
    return result.stdout


def parse_emulator_output(out: str) -> dict[str, int]:
    """Return {layer_name: cgra_cycles} from emulator's per-stage table."""
    cycles: dict[str, int] = {}
    # The emulator prints lines like:  "  conv1          7733  0.155 ..."
    for m in re.finditer(
        r"^\s+(conv1|conv2|pool1|pool2|fc1|fc2)\s+(\d+)\s+",
        out, re.MULTILINE
    ):
        cycles[m.group(1)] = int(m.group(2))
    return cycles


def cycles_to_ms(cycles: int) -> float:
    """Convert CGRA cycles → ms at 50 MHz."""
    return cycles / (CGRA_FREQ_MHZ * 1000.0)


def read_emulator_constants(path: Path) -> dict[str, float]:
    """Extract current tunable values from emulate_full_cnn.py."""
    text = path.read_text()
    consts: dict[str, float] = {}
    for name, pattern in TUNABLES.items():
        m = re.search(pattern, text, re.MULTILINE)
        if m:
            try:
                consts[name] = float(m.group(1))
            except ValueError:
                pass
    return consts


def propose_adjustments(errors: dict[str, float],
                        consts: dict[str, float]) -> list[tuple[str, float, str]]:
    """Given per-layer relative errors, propose constant changes.

    Returns list of (constant_name, new_value, rationale).
    """
    proposals: list[tuple[str, float, str]] = []

    # Conv layers — MAC efficiency
    conv_err = max(
        (abs(errors.get(l, 0)) for l in ("conv1", "conv2")),
        default=0,
    )
    if conv_err > 0.10:
        # Conv emulator-overshoots → MAC_EFF_LONG is too generous
        signed = (errors.get("conv1", 0) + errors.get("conv2", 0)) / 2
        adj = consts.get("MAC_EFF_LONG", 0.97) * (1 - signed)
        adj = max(0.5, min(0.999, adj))
        proposals.append(("MAC_EFF_LONG", adj,
            f"conv layers off by {conv_err*100:.1f}%; adjust MAC efficiency"))

    # FC1 — multiple knobs, propose the dominant one
    fc1_err = errors.get("fc1", 0)
    if abs(fc1_err) > 0.10:
        # FC1 overshoots → orchestration overhead is overestimated
        # → reduce SG_DMA_DESC_CGRA or PHASE_SYNC_CGRA
        # FC1 undershoots → orchestration overhead is underestimated
        # → increase those constants
        cur = consts.get("SG_DMA_DESC_CGRA", 100)
        adj = cur * (1 - fc1_err)   # signed: positive err → decrease
        proposals.append(("SG_DMA_DESC_CGRA", int(round(adj)),
            f"fc1 off by {fc1_err*100:+.1f}%; tune SG-DMA per-desc cost"))

    # FC2 — usually small, use PHASE_SYNC_CGRA as secondary knob
    fc2_err = errors.get("fc2", 0)
    if abs(fc2_err) > 0.10:
        cur = consts.get("PHASE_SYNC_CGRA", 100)
        adj = cur * (1 - fc2_err)
        proposals.append(("PHASE_SYNC_CGRA", int(round(adj)),
            f"fc2 off by {fc2_err*100:+.1f}%; tune phase-sync overhead"))

    return proposals


def apply_proposals(path: Path,
                    proposals: list[tuple[str, float, str]]) -> None:
    """Edit emulate_full_cnn.py in place to apply each proposal."""
    text = path.read_text()
    for name, new_val, _ in proposals:
        pattern = TUNABLES[name]
        # Re-form the line preserving formatting style of the integer/float
        if isinstance(new_val, int):
            repl_val = str(new_val)
        else:
            repl_val = f"{new_val:.3f}".rstrip("0").rstrip(".")
        new_text, n = re.subn(
            pattern,
            lambda m: m.group(0).replace(m.group(1), repl_val),
            text, count=1, flags=re.MULTILINE
        )
        if n == 1:
            text = new_text
            print(f"  ✓ {name} = {repl_val}")
        else:
            print(f"  ✗ {name}: pattern not found in source")
    path.write_text(text)


def main() -> int:
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter
    )
    ap.add_argument("--silicon",
        default=str(Path(__file__).parent.parent.parent /
                    "06_doc/roofline_data.csv"),
        help="silicon measurement CSV (from analyze_two_pass.py)")
    ap.add_argument("--apply", action="store_true",
        help="apply proposals to emulate_full_cnn.py in place")
    ap.add_argument("--threshold", type=float, default=0.10,
        help="acceptable relative error (default 0.10 = ±10%%)")
    args = ap.parse_args()

    here = Path(__file__).parent
    emu_path = here / "emulate_full_cnn.py"

    silicon = read_silicon_csv(Path(args.silicon))
    if not silicon:
        print(f"ERROR: no silicon data in {args.silicon}", file=sys.stderr)
        print("Run analyze_two_pass.py --csv first.", file=sys.stderr)
        return 1

    emu_out = run_emulator()
    emu_cycles = parse_emulator_output(emu_out)
    consts = read_emulator_constants(emu_path)

    # Compute per-layer relative errors (signed: positive = emulator OVER)
    print("=" * 64)
    print("  Emulator vs silicon")
    print("=" * 64)
    print(f"  {'layer':<8s} {'silicon (ms)':>14s} {'emulator (ms)':>14s}  "
          f"{'err':>8s}  {'flag':>6s}")
    print("-" * 64)
    errors: dict[str, float] = {}
    n_fail = 0
    for layer in ("conv1", "conv2", "fc1", "fc2"):
        sms = silicon.get(layer)
        ec = emu_cycles.get(layer, 0)
        ems = cycles_to_ms(ec) if ec else 0
        if sms is None or sms == 0:
            print(f"  {layer:<8s} {'pending':>14s} {ems:>14.3f}    "
                  f"{'—':>8s}  {'skip':>6s}")
            continue
        err = (ems - sms) / sms
        errors[layer] = err
        flag = "OK" if abs(err) <= args.threshold else "**FAIL**"
        if flag == "**FAIL**":
            n_fail += 1
        print(f"  {layer:<8s} {sms:>14.3f} {ems:>14.3f}  "
              f"{err*100:>+7.1f}%  {flag:>6s}")

    if not errors:
        print("\nAll silicon values are still pending; nothing to calibrate.")
        return 0

    print()
    if n_fail == 0:
        print(f"✅ All layers within ±{args.threshold*100:.0f}% — "
              f"emulator is reviewer-grade.")
        return 0

    print(f"❌ {n_fail} layers exceed ±{args.threshold*100:.0f}%; "
          f"proposing constant adjustments...")
    print()
    proposals = propose_adjustments(errors, consts)
    if not proposals:
        print("  (no specific proposals; consider deeper inspection)")
        return 2

    print("Proposals:")
    for name, val, why in proposals:
        cur = consts.get(name, "?")
        print(f"  - {name}: {cur} → {val}")
        print(f"      reason: {why}")

    if args.apply:
        print("\nApplying changes to emulate_full_cnn.py:")
        apply_proposals(emu_path, proposals)
        print("\nRe-run with `python3 calibrate_emulator.py --silicon ...` "
              "to verify (iterate until all OK).")
    else:
        print("\nDry run. Re-run with --apply to commit changes.")

    return 0 if args.apply else 3


if __name__ == "__main__":
    sys.exit(main())
