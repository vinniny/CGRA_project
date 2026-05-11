#!/usr/bin/env python3
"""
emit_sweep_fixture.py — Generate C header with N-image MNIST sweep data.

For each test image (i = 0..N-1), pre-computes:
  - act400[400] : INT32 activations after Conv1+ReLU+MaxPool+Conv2+ReLU+MaxPool
                  + per-image quantization (max|x|/32767 → INT16, sign-extended).
  - act64[64]   : INT32 activations after FC1 + bias + ReLU + per-image requant.
                  These would be produced by ARM between FC1 and FC2 in a true
                  end-to-end demo. For the sweep we feed them directly so HW
                  FC1 errors don't compound into FC2 (each layer is graded
                  against its own analytic-golden input).
  - label       : ground truth class (uint8).
  - golden_pred : Python-int-MAC-then-float-dequant argmax (uint8).

The hardware ELF runs FC1(act400) and FC2(act64) per image, then takes the
argmax of FC2's INT32 result. Three accuracies are reported:
  HW_vs_label   : how often HW argmax matches ground truth
  Golden_vs_label : reference (Python pure-int MAC, same sweep)
  HW_vs_golden  : how often HW agrees with the analytic golden

Output: 07_sw/baremetal/mnist_sweep_fixture.h
"""

import argparse
import re
import struct
import numpy as np
import torch
import torch.nn.functional as F
from pathlib import Path

SCRIPT_DIR = Path(__file__).parent


def load_weights():
    conv_path = SCRIPT_DIR / "mnist_weights_conv.bin"
    spm_path  = SCRIPT_DIR / "mnist_weights_spm.bin"
    scale_h   = SCRIPT_DIR / "mnist_weights_scale.h"

    header = scale_h.read_text()
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

    with open(spm_path, "rb") as f:
        data = np.frombuffer(f.read(), dtype=np.uint32)

    def unpack_spm(words_flat, n_out, n_in):
        out = np.zeros((n_out, n_in), dtype=np.int16)
        for i in range(n_out):
            row_words = words_flat[i * n_in:(i + 1) * n_in]
            for j, word in enumerate(row_words):
                out[i, j] = np.int16(word & 0xFFFF)
        return out

    fc1_w_q = unpack_spm(data,             64, 400)
    fc2_w_q = unpack_spm(data[64 * 400:],  10,  64)

    def parse_bias(name):
        m = re.search(rf'mnist_{name}_bias_q\[[\d]+\]\s*=\s*\{{([^}}]+)\}}', header, re.DOTALL)
        if m:
            return np.array([int(x.strip()) for x in m.group(1).split(",")], dtype=np.int32)
        return np.zeros(1, dtype=np.int32)

    return dict(
        conv1_w_q=conv1_w_q, conv1_b_q=conv1_b_q, sc1=sc1,
        conv2_w_q=conv2_w_q, conv2_b_q=conv2_b_q, sc2=sc2,
        fc1_w_q=fc1_w_q, fc1_b_q=parse_bias("fc1"), sf1=sf1,
        fc2_w_q=fc2_w_q, fc2_b_q=parse_bias("fc2"), sf2=sf2,
    )


def run_image(img_t, w):
    """Returns (act400_i32, act64_i32, golden_pred).

    The conv weights are stored in [out, kH, kW, in] order in the binary
    (per load_weights's frombuffer().reshape). PyTorch conv2d expects
    [out, in, kH, kW], so we MUST transpose (not reshape, which preserves
    memory layout and corrupts the channel axis for conv2 with in=8).
    Matches golden_sim.py's infer_one path.
    """
    c1_w = torch.tensor(w["conv1_w_q"].astype(np.float32) * w["sc1"]).permute(0, 3, 1, 2).contiguous()
    c1_b = torch.tensor(w["conv1_b_q"].astype(np.float32) * w["sc1"])
    x = F.conv2d(img_t.unsqueeze(0), c1_w, c1_b)
    x = F.relu(x); x = F.max_pool2d(x, 2)

    c2_w = torch.tensor(w["conv2_w_q"].astype(np.float32) * w["sc2"]).permute(0, 3, 1, 2).contiguous()
    c2_b = torch.tensor(w["conv2_b_q"].astype(np.float32) * w["sc2"])
    x = F.conv2d(x, c2_w, c2_b)
    x = F.relu(x); x = F.max_pool2d(x, 2)
    act400_f = x.reshape(-1).detach().numpy()

    act_scale = float(np.max(np.abs(act400_f))) / 32767.0 or 1.0
    act400_i32 = np.round(act400_f / act_scale).astype(np.int16).astype(np.int32)

    fc1_w_i32 = w["fc1_w_q"].astype(np.int32)
    fc1_acc = np.zeros(64, dtype=np.int64)
    for n in range(64):
        fc1_acc[n] = np.sum(act400_i32.astype(np.int64) * fc1_w_i32[n].astype(np.int64))
    fc1_acc_i32 = np.clip(fc1_acc, -2**31, 2**31 - 1).astype(np.int32)

    fc1_float = fc1_acc_i32.astype(np.float32) * (act_scale * w["sf1"])
    fc1_float += w["fc1_b_q"].astype(np.float32) * w["sf1"]
    fc1_relu  = np.maximum(0.0, fc1_float)

    act64_scale = float(np.max(np.abs(fc1_relu))) / 32767.0 or 1.0
    act64_i32 = np.round(fc1_relu / act64_scale).astype(np.int16).astype(np.int32)

    fc2_w_i32 = w["fc2_w_q"].astype(np.int32)
    fc2_acc = np.zeros(10, dtype=np.int64)
    for n in range(10):
        fc2_acc[n] = np.sum(act64_i32.astype(np.int64) * fc2_w_i32[n].astype(np.int64))
    fc2_acc_i32 = np.clip(fc2_acc, -2**31, 2**31 - 1).astype(np.int32)

    fc2_float = fc2_acc_i32.astype(np.float32) * (act64_scale * w["sf2"])
    fc2_float += w["fc2_b_q"].astype(np.float32) * w["sf2"]
    return act400_i32, act64_i32, int(np.argmax(fc2_float))


def main(args):
    from torchvision import datasets, transforms
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,)),
    ])
    test_ds = datasets.MNIST(SCRIPT_DIR / "data", train=False, download=False,
                             transform=transform)
    w = load_weights()
    n = min(args.images, len(test_ds))

    act400_all = np.zeros((n, 400), dtype=np.int32)
    act64_all  = np.zeros((n,  64), dtype=np.int32)
    input28_all = np.zeros((n, 784), dtype=np.uint8)
    labels     = np.zeros(n, dtype=np.uint8)
    golden     = np.zeros(n, dtype=np.uint8)

    # The torchvision MNIST dataset stores raw uint8 pixels in `test_ds.data`
    # (28x28 tensor per image). We snapshot these before any transforms so the
    # HDMI demo can render the actual handwritten digit.
    raw_pixels = test_ds.data.numpy().astype(np.uint8)  # [N, 28, 28]

    correct = 0
    for i in range(n):
        img, label = test_ds[i]
        a400, a64, pred = run_image(torch.tensor(img.numpy()), w)
        act400_all[i] = a400; act64_all[i] = a64
        input28_all[i] = raw_pixels[i].reshape(784)
        labels[i] = label;    golden[i] = pred
        correct += (pred == label)

    print(f"Golden int-MAC accuracy: {correct}/{n} = {100*correct/n:.2f}%")

    out = Path(args.out)
    lines = [
        "/* Auto-generated by emit_sweep_fixture.py — do not edit */",
        "#pragma once",
        "#include <stdint.h>",
        "",
        f"#define SWEEP_N_IMAGES {n}",
        "",
        f"#define SWEEP_RODATA __attribute__((section(\".cnn_sweep\")))",
        "",
        f"static const int32_t SWEEP_RODATA sweep_act400[{n}][400] = {{",
    ]
    for i in range(n):
        row = ", ".join(str(int(v)) for v in act400_all[i])
        lines.append(f"  {{ {row} }},")
    lines += ["};", "",
              f"static const int32_t SWEEP_RODATA sweep_act64[{n}][64] = {{"]
    for i in range(n):
        row = ", ".join(str(int(v)) for v in act64_all[i])
        lines.append(f"  {{ {row} }},")
    lines += ["};", "",
              f"/* Raw 28x28 grayscale input pixels (uint8 0..255) for HDMI demo */",
              f"static const uint8_t SWEEP_RODATA sweep_input28[{n}][784] = {{"]
    for i in range(n):
        row = ", ".join(str(int(v)) for v in input28_all[i])
        lines.append(f"  {{ {row} }},")
    lines += ["};", "",
              f"static const uint8_t SWEEP_RODATA sweep_labels[{n}] = {{ "
              + ", ".join(str(int(v)) for v in labels) + " };", "",
              f"static const uint8_t SWEEP_RODATA sweep_golden[{n}] = {{ "
              + ", ".join(str(int(v)) for v in golden) + " };", ""]

    out.write_text("\n".join(lines))
    print(f"→ {out}  ({out.stat().st_size//1024} KB)")


if __name__ == "__main__":
    p = argparse.ArgumentParser()
    p.add_argument("--images", type=int, default=100)
    p.add_argument("--out", type=str,
                   default=str(SCRIPT_DIR.parent / "baremetal" / "mnist_sweep_fixture.h"))
    main(p.parse_args())
