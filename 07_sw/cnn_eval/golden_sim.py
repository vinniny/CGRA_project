#!/usr/bin/env python3
"""
golden_sim.py — Reference simulator for MnistCGRA with quantized weights.

Validates that INT16 weight quantization does not significantly degrade accuracy.
Uses dequantized (float) arithmetic — same result as the CGRA chain once
accumulator values are scaled back to float by the ARM.

Matching the bare-metal inference flow:
  1. Input: float32 (MNIST normalised: mean=0.1307, std=0.3081)
  2. Conv: float dot-product using DEQUANTIZED int16 weights (w_float = w_int16 × scale_w)
  3. ReLU + MaxPool: float
  4. FC: float dot-product using DEQUANTIZED int16 weights

For the actual bare-metal ELF:
  - ARM computes conv+relu+pool in float (or INT16 scaled)
  - CGRA computes FC in INT16 MAC; ARM reads RESULT_ROW and multiplies by (scale_w × scale_act)
  - For demo validity, this golden sim uses the same quantised weights

Usage:
    python3 golden_sim.py [--images N] [--verbose]

Output:
    golden_sim_results.bin   — predicted class (uint8) per test image
    Prints overall accuracy vs float model baseline.
"""

import argparse
import struct
import numpy as np
import torch
import torch.nn.functional as F
from pathlib import Path
from torchvision import datasets, transforms

SCRIPT_DIR = Path(__file__).parent


def load_weights_float():
    """Load INT16-quantised weights, dequantise back to float32."""
    conv_path = SCRIPT_DIR / "mnist_weights_conv.bin"
    spm_path  = SCRIPT_DIR / "mnist_weights_spm.bin"
    scale_h   = SCRIPT_DIR / "mnist_weights_scale.h"

    if not conv_path.exists() or not spm_path.exists():
        raise FileNotFoundError("Run quantize_cgra.py first")

    header = scale_h.read_text()
    import re
    def get_f(name):
        m = re.search(rf'#define\s+{name}\s+([\d.e+\-]+)f?', header)
        return float(m.group(1)) if m else 1.0

    sc1 = get_f("MNIST_CONV1_SCALE_W_F")
    sc2 = get_f("MNIST_CONV2_SCALE_W_F")
    sf1 = get_f("MNIST_FC1_SCALE_W_F")
    sf2 = get_f("MNIST_FC2_SCALE_W_F")

    with open(conv_path, "rb") as f:
        conv1_w_q = np.frombuffer(f.read(72 * 2),   dtype=np.int16).reshape(8, 3, 3, 1)
        conv1_b_q = np.frombuffer(f.read(8 * 4),    dtype=np.int32)
        conv2_w_q = np.frombuffer(f.read(1152 * 2), dtype=np.int16).reshape(16, 3, 3, 8)
        conv2_b_q = np.frombuffer(f.read(16 * 4),   dtype=np.int32)

    conv1_w = conv1_w_q.astype(np.float32) * sc1  # [8,3,3,1]
    conv1_b = conv1_b_q.astype(np.float32) * sc1  # [8]   (bias in weight-scale units → float)
    conv2_w = conv2_w_q.astype(np.float32) * sc2  # [16,3,3,8]
    conv2_b = conv2_b_q.astype(np.float32) * sc2  # [16]

    # FC weights from SPM binary
    with open(spm_path, "rb") as f:
        data = np.frombuffer(f.read(), dtype=np.uint32)

    def unpack_spm(words_flat, n_out, n_in):
        # LPR v2 format: one INT16 in lower 16 bits of each 32-bit word
        out = np.zeros((n_out, n_in), dtype=np.int16)
        for i in range(n_out):
            row_words = words_flat[i * n_in:(i + 1) * n_in]
            for j, word in enumerate(row_words):
                out[i, j] = np.int16(word & 0xFFFF)
        return out

    fc1_w_q = unpack_spm(data,              64, 400)   # [64,400] int16
    fc2_w_q = unpack_spm(data[64 * 400:],   10,  64)   # [10,64]  int16
    fc1_w = fc1_w_q.astype(np.float32) * sf1
    fc2_w = fc2_w_q.astype(np.float32) * sf2

    # Parse bias arrays from header
    def parse_bias(name):
        m = re.search(rf'mnist_{name}_bias_q\[[\d]+\]\s*=\s*\{{([^}}]+)\}}', header, re.DOTALL)
        if m:
            vals = [int(x.strip()) for x in m.group(1).split(",")]
            return np.array(vals, dtype=np.float32)
        return np.zeros(1, dtype=np.float32)

    fc1_b_q = parse_bias("fc1")
    fc2_b_q = parse_bias("fc2")
    fc1_b = fc1_b_q * sf1
    fc2_b = fc2_b_q * sf2

    return dict(
        conv1_w=conv1_w, conv1_b=conv1_b,
        conv2_w=conv2_w, conv2_b=conv2_b,
        fc1_w=fc1_w, fc1_b=fc1_b,
        fc2_w=fc2_w, fc2_b=fc2_b,
    )


def infer_one(img_np: np.ndarray, w: dict) -> int:
    """Float inference using dequantized weights. img_np: [1,28,28] float32."""
    # Conv1 + ReLU + MaxPool  (no padding, HWC layout for conv)
    x = torch.tensor(img_np)  # [1,28,28]
    # Weights in [out,kH,kW,in] → PyTorch needs [out,in,kH,kW]
    c1_w = torch.tensor(w["conv1_w"].transpose(0, 3, 1, 2))  # [8,1,3,3]
    c1_b = torch.tensor(w["conv1_b"])                          # [8]
    x = F.conv2d(x.unsqueeze(0), c1_w, c1_b)                  # [1,8,26,26]
    x = F.relu(x)
    x = F.max_pool2d(x, 2)                                     # [1,8,13,13]

    c2_w = torch.tensor(w["conv2_w"].transpose(0, 3, 1, 2))  # [16,8,3,3]
    c2_b = torch.tensor(w["conv2_b"])                          # [16]
    x = F.conv2d(x, c2_w, c2_b)                               # [1,16,11,11]
    x = F.relu(x)
    x = F.max_pool2d(x, 2)                                     # [1,16,5,5]

    x = x.reshape(-1)                                          # [400]
    # FC1
    fc1_w = torch.tensor(w["fc1_w"])  # [64,400]
    fc1_b = torch.tensor(w["fc1_b"])
    x = F.relu(fc1_w @ x + fc1_b)    # [64]
    # FC2
    fc2_w = torch.tensor(w["fc2_w"])  # [10,64]
    fc2_b = torch.tensor(w["fc2_b"])
    logits = fc2_w @ x + fc2_b        # [10]

    return int(torch.argmax(logits).item())


def main(args):
    w = load_weights_float()

    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,)),
    ])
    test_ds = datasets.MNIST(SCRIPT_DIR / "data", train=False, download=True, transform=transform)
    n = min(args.images, len(test_ds))

    predictions = []
    correct = 0
    for i in range(n):
        img, label = test_ds[i]
        pred = infer_one(img.numpy(), w)
        predictions.append(pred)
        if pred == label:
            correct += 1
        if args.verbose and i < 30:
            mark = "OK" if pred == label else "ERR"
            print(f"  [{i:4d}] gt={label} pred={pred} {mark}")

    acc = 100.0 * correct / n
    print(f"\nGolden-sim (INT16-quantised weights, float arith): {correct}/{n} = {acc:.2f}%")
    if acc < 98.0:
        print("WARNING: quantization degraded accuracy below 98% — check scales")
    else:
        print("PASS — quantization accuracy OK")

    out_path = SCRIPT_DIR / "golden_sim_results.bin"
    with open(out_path, "wb") as f:
        f.write(bytes(predictions))
    print(f"Saved {n} predictions → {out_path}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--images",  type=int, default=1000)
    parser.add_argument("--verbose", action="store_true")
    args = parser.parse_args()
    main(args)
