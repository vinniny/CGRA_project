#!/usr/bin/env python3
"""
emit_smoke_fixture.py — Generate C header with test fixture for demo_mnist_smoke.c.

Runs integer-exact MAC simulation (same arithmetic as CGRA) for image 0 and
emits expected intermediate values that the bare-metal smoke ELF can compare.

Outputs:
    mnist_smoke_fixture.h — C header with pre-computed activations + expected MACs
"""

import struct
import numpy as np
import torch
import torch.nn.functional as F
import re
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

    sc1  = get_f("MNIST_CONV1_SCALE_W_F")
    sc2  = get_f("MNIST_CONV2_SCALE_W_F")
    sf1  = get_f("MNIST_FC1_SCALE_W_F")
    sf2  = get_f("MNIST_FC2_SCALE_W_F")

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


def run_image_0():
    """Full inference for image 0, returning intermediate values."""
    from torchvision import datasets, transforms

    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,)),
    ])
    test_ds = datasets.MNIST(SCRIPT_DIR / "data", train=False, download=False,
                             transform=transform)
    img, label = test_ds[0]   # [1,28,28] float32
    w = load_weights()

    # ---- ARM float conv/pool path ----
    x = torch.tensor(img)
    c1_w = torch.tensor(w["conv1_w_q"].astype(np.float32) * w["sc1"]).reshape(8, 1, 3, 3)
    c1_b = torch.tensor(w["conv1_b_q"].astype(np.float32) * w["sc1"])
    x = F.conv2d(x.unsqueeze(0), c1_w, c1_b)
    x = F.relu(x)
    x = F.max_pool2d(x, 2)   # [1,8,13,13]

    c2_w = torch.tensor(w["conv2_w_q"].astype(np.float32) * w["sc2"]).reshape(16, 8, 3, 3)
    c2_b = torch.tensor(w["conv2_b_q"].astype(np.float32) * w["sc2"])
    x = F.conv2d(x, c2_w, c2_b)
    x = F.relu(x)
    x = F.max_pool2d(x, 2)   # [1,16,5,5]

    act400_f = x.reshape(-1).detach().numpy()   # [400] float32, ≥0

    # Quantize activations to int16 then store as int32 (sign-extended, but ≥0 so same)
    act_scale = float(np.max(np.abs(act400_f))) / 32767.0
    if act_scale == 0.0:
        act_scale = 1.0
    act400_i16 = np.round(act400_f / act_scale).astype(np.int16)
    act400_i32 = act400_i16.astype(np.int32)   # sign-extended, stored in tile memory

    # ---- CGRA integer MAC for FC1 ----
    # acc[n] = sum_i( act_i32[i] * fc1_w_i32[n,i] )
    # Note: CGRA computes 32×32→32 product (INT32 mode), then accumulates 40-bit
    fc1_w_i32 = w["fc1_w_q"].astype(np.int32)   # [64,400] sign-extended
    fc1_acc = np.zeros(64, dtype=np.int64)
    for n in range(64):
        for i in range(400):
            fc1_acc[n] += int(act400_i32[i]) * int(fc1_w_i32[n, i])
    # Clamp to INT32 range (matches CGRA RESULT_ROW which is 32-bit)
    fc1_acc_i32 = np.clip(fc1_acc, -2**31, 2**31 - 1).astype(np.int32)

    # ---- ARM: dequantize, add bias, ReLU, requantize for FC2 ----
    fc1_float = fc1_acc_i32.astype(np.float32) * (act_scale * w["sf1"])
    fc1_float += w["fc1_b_q"].astype(np.float32) * w["sf1"]
    fc1_relu  = np.maximum(0.0, fc1_float)

    act64_scale = float(np.max(np.abs(fc1_relu))) / 32767.0
    if act64_scale == 0.0:
        act64_scale = 1.0
    act64_i16 = np.round(fc1_relu / act64_scale).astype(np.int16)
    act64_i32 = act64_i16.astype(np.int32)

    # ---- CGRA integer MAC for FC2 ----
    fc2_w_i32 = w["fc2_w_q"].astype(np.int32)   # [10,64]
    fc2_acc = np.zeros(10, dtype=np.int64)
    for n in range(10):
        for i in range(64):
            fc2_acc[n] += int(act64_i32[i]) * int(fc2_w_i32[n, i])
    fc2_acc_i32 = np.clip(fc2_acc, -2**31, 2**31 - 1).astype(np.int32)

    # ---- Argmax on dequantized FC2 + bias ----
    fc2_float = fc2_acc_i32.astype(np.float32) * (act64_scale * w["sf2"])
    fc2_float += w["fc2_b_q"].astype(np.float32) * w["sf2"]
    pred = int(np.argmax(fc2_float))

    print(f"Image 0: label={label}, pred={pred}, {'PASS' if pred == label else 'FAIL'}")
    print(f"act400 scale={act_scale:.6f}, act64 scale={act64_scale:.6f}")
    print(f"FC1 acc range: [{fc1_acc_i32.min()}, {fc1_acc_i32.max()}]")
    print(f"FC2 acc range: [{fc2_acc_i32.min()}, {fc2_acc_i32.max()}]")

    return dict(
        label=label,
        pred=pred,
        act400_i32=act400_i32,
        act_scale=act_scale,
        fc1_acc_i32=fc1_acc_i32,
        act64_i32=act64_i32,
        act64_scale=act64_scale,
        fc2_acc_i32=fc2_acc_i32,
    )


def emit_header(vals: dict, out_path: Path):
    w = load_weights()
    lines = [
        "/* Auto-generated by emit_smoke_fixture.py — do not edit */",
        "#pragma once",
        "#include <stdint.h>",
        "",
        f"#define SMOKE_LABEL          {vals['label']}",
        f"#define SMOKE_PRED           {vals['pred']}",
        f"/* act_scale = max|pool2_out| / 32767 */",
        f"#define SMOKE_ACT_SCALE_Q23  {int(round(vals['act_scale'] * (1 << 23)))}u  /* Q23 fixed-point */",
        f"/* act64_scale = max|fc1_relu| / 32767 */",
        f"#define SMOKE_ACT64_SCALE_Q23 {int(round(vals['act64_scale'] * (1 << 23)))}u",
        "",
    ]

    def fmt_i32_array(name, arr):
        vals_str = ", ".join(str(int(v)) for v in arr)
        return [f"static const int32_t {name}[{len(arr)}] = {{", f"    {vals_str}", "};"]

    lines += fmt_i32_array("smoke_act400", vals["act400_i32"])
    lines += [""]
    lines += fmt_i32_array("smoke_fc1_acc", vals["fc1_acc_i32"])
    lines += [""]
    lines += fmt_i32_array("smoke_act64", vals["act64_i32"])
    lines += [""]
    lines += fmt_i32_array("smoke_fc2_acc", vals["fc2_acc_i32"])
    lines += [""]

    # Also embed FC1 and FC2 scale factors for dequantization in C
    lines += [
        f"#define SMOKE_FC1_SCALE_W_Q23  {int(round(w['sf1'] * (1 << 23)))}u",
        f"#define SMOKE_FC2_SCALE_W_Q23  {int(round(w['sf2'] * (1 << 23)))}u",
    ]

    out_path.write_text("\n".join(lines) + "\n")
    print(f"→ {out_path}")


if __name__ == "__main__":
    vals = run_image_0()
    emit_header(vals, SCRIPT_DIR / "mnist_smoke_fixture.h")
    emit_header(vals, Path(__file__).parent.parent / "baremetal" / "mnist_smoke_fixture.h")
