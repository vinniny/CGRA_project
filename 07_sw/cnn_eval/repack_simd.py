#!/usr/bin/env python3
"""
repack_simd.py — Pack the existing v1/v2 FC weight blob into INT16x2 SIMD
                 layout for the Tier-2 kernel.

Reads:  mnist_weights_spm.bin   (one INT16 per 32-bit word, sign-extended)
        mnist_weights_scale.h   (for FC1/FC2 N_OUT, N_IN constants)

Writes: mnist_weights_spm_simd.bin

INT16x2 packing (per the RTL — see cgra_pe.sv:362-371):
    DATA_MODE_INT16X2 produces a 2-element dot product per cycle:
        acc += op0[lo16] * op1[lo16] + op0[hi16] * op1[hi16]

So we pack two consecutive INT16 weights per 32-bit word:
    word[i] = (w[2i+1] << 16) | (w[2i] & 0xFFFF)

The corresponding ACTIVATIONS must be packed the same way at runtime.
The tile DMA broadcast already handles 32-bit words, so the ARM side
just needs to pack act[2i], act[2i+1] into the same layout when writing
the tile DDR staging area.

Output layout — same neuron-major as v1, half the bytes per neuron:
    FC1: 64 neurons × ceil(400/2) = 200 SIMD words/neuron =  51 200 bytes
    FC2: 10 neurons × ceil( 64/2) =  32 SIMD words/neuron =   1 280 bytes
                                                       ----   52 480 B total
    (vs 104 960 B for the v1 blob)

If N_IN is odd, the trailing INT16 is paired with an explicit zero in the
upper half — equivalent to zero-pad input → no contribution to the MAC.

This is a STAGED tool. The matching kernel (cgra_kernels_cnn_simd.h) is
NOT yet written — Tier-2 is gated on v3 bitstream landing + the v2
fixed kernel showing what we get from the dual-port SPM path first.
"""

import struct
import sys
import re
from pathlib import Path

SCRIPT_DIR = Path(__file__).parent
IN_BIN     = SCRIPT_DIR / "mnist_weights_spm.bin"
OUT_BIN    = SCRIPT_DIR / "mnist_weights_spm_simd.bin"
SCALE_HDR  = SCRIPT_DIR / "mnist_weights_scale.h"


def read_scale_header() -> dict:
    """Parse FC{1,2}_N_IN / N_OUT from mnist_weights_scale.h."""
    if not SCALE_HDR.exists():
        raise FileNotFoundError(f"{SCALE_HDR} not found — run quantize_cgra.py first")
    text  = SCALE_HDR.read_text()
    grab  = lambda name: int(re.search(rf"#define\s+{name}\s+(\d+)", text).group(1))
    return {
        "fc1_n_in":  grab("MNIST_FC1_N_IN"),
        "fc1_n_out": grab("MNIST_FC1_N_OUT"),
        "fc2_n_in":  grab("MNIST_FC2_N_IN"),
        "fc2_n_out": grab("MNIST_FC2_N_OUT"),
    }


def read_v1_blob(consts: dict) -> tuple[list[list[int]], list[list[int]]]:
    """Return (fc1_weights[neuron][n_in], fc2_weights[neuron][n_in]) as INT16."""
    if not IN_BIN.exists():
        raise FileNotFoundError(f"{IN_BIN} not found — run quantize_cgra.py first")

    raw = IN_BIN.read_bytes()
    # Each word is 32 bits, low 16 = INT16 (sign-extended in v1 layout).
    words = struct.unpack(f"<{len(raw) // 4}I", raw)

    fc1_words = consts["fc1_n_in"] * consts["fc1_n_out"]
    fc2_words = consts["fc2_n_in"] * consts["fc2_n_out"]
    if len(words) < fc1_words + fc2_words:
        raise ValueError(
            f"blob too short: have {len(words)} words, need {fc1_words+fc2_words}")

    def to_int16(w):
        v = w & 0xFFFF
        return v - 0x10000 if v & 0x8000 else v

    fc1 = []
    idx = 0
    for n in range(consts["fc1_n_out"]):
        row = [to_int16(words[idx + i]) for i in range(consts["fc1_n_in"])]
        fc1.append(row)
        idx += consts["fc1_n_in"]

    fc2 = []
    for n in range(consts["fc2_n_out"]):
        row = [to_int16(words[idx + i]) for i in range(consts["fc2_n_in"])]
        fc2.append(row)
        idx += consts["fc2_n_in"]

    return fc1, fc2


def pack_simd(weights: list[int]) -> bytes:
    """Pack N INT16 weights → ceil(N/2) 32-bit words [hi=w[2i+1], lo=w[2i]]."""
    out = bytearray()
    n = len(weights)
    for i in range(0, n, 2):
        lo = weights[i] & 0xFFFF
        hi = (weights[i + 1] & 0xFFFF) if (i + 1) < n else 0
        out += struct.pack("<I", (hi << 16) | lo)
    return bytes(out)


def emit_blob(fc1: list[list[int]], fc2: list[list[int]], out: Path) -> dict:
    """Write the SIMD blob and return summary stats."""
    buf = bytearray()
    for layer, name in [(fc1, "fc1"), (fc2, "fc2")]:
        for neuron_weights in layer:
            buf += pack_simd(neuron_weights)

    out.write_bytes(buf)
    fc1_bytes = sum(len(pack_simd(n)) for n in fc1)
    fc2_bytes = sum(len(pack_simd(n)) for n in fc2)
    return {
        "fc1_bytes": fc1_bytes,
        "fc2_bytes": fc2_bytes,
        "total_bytes": len(buf),
        "fc1_words_per_neuron": len(pack_simd(fc1[0])) // 4,
        "fc2_words_per_neuron": len(pack_simd(fc2[0])) // 4,
    }


def main():
    consts = read_scale_header()
    print(f"FC1: {consts['fc1_n_in']} → {consts['fc1_n_out']}")
    print(f"FC2: {consts['fc2_n_in']} → {consts['fc2_n_out']}")

    fc1, fc2 = read_v1_blob(consts)
    stats = emit_blob(fc1, fc2, OUT_BIN)

    print(f"\nSIMD blob written: {OUT_BIN}")
    print(f"  FC1: {stats['fc1_words_per_neuron']} SIMD words/neuron"
          f" × {consts['fc1_n_out']} = {stats['fc1_bytes']:>6} bytes")
    print(f"  FC2: {stats['fc2_words_per_neuron']} SIMD words/neuron"
          f" × {consts['fc2_n_out']} = {stats['fc2_bytes']:>6} bytes")
    print(f"  Total: {stats['total_bytes']:>6} bytes"
          f" (vs {IN_BIN.stat().st_size} for the v1 blob → {100*stats['total_bytes']/IN_BIN.stat().st_size:.1f}%)")

    # Spot-check: first neuron of FC1, first 4 packed words
    print(f"\nFC1 neuron 0 spot-check (first 4 SIMD words):")
    head = pack_simd(fc1[0])[:16]
    for i in range(0, len(head), 4):
        w = struct.unpack("<I", head[i:i+4])[0]
        lo = w & 0xFFFF; hi = (w >> 16) & 0xFFFF
        lo_s = lo - 0x10000 if lo & 0x8000 else lo
        hi_s = hi - 0x10000 if hi & 0x8000 else hi
        print(f"  word[{i//4}] = 0x{w:08X}  -> [lo={lo_s:6d}, hi={hi_s:6d}]")
        print(f"               (matches fc1[0][{2*(i//4)}]={fc1[0][2*(i//4)]}, "
              f"fc1[0][{2*(i//4)+1}]={fc1[0][2*(i//4)+1]})")


if __name__ == "__main__":
    main()
