#!/usr/bin/env python3
"""
eval_golden_accuracy.py — Evaluate golden_weights.bin on the held-out test set
using the golden C model as the inference engine.

Two evaluation modes:
  1. Python-only (--mode python): Run VNCharNet in pure Python/numpy using
     float32 arithmetic, exactly matching golden_infer() in lpr_golden.c.
  2. Binary (--mode binary): Write each test image as a raw INT32 binary and
     call the compiled lpr_golden_test executable (build/lpr_golden_test).

Usage:
  python3 eval_golden_accuracy.py [--mode python] [--weights golden_weights.bin]
  python3 eval_golden_accuracy.py --mode binary  --exe ../build/lpr_golden_test
"""

import argparse
import subprocess
import struct
import tempfile
import os
import sys
from pathlib import Path

import numpy as np
import torch

VN_CHAR_MAP = ['1','2','3','4','5','6','7','8','9',
               'A','B','C','D','E','F','G','H','K','L','M',
               'N','P','S','T','U','V','X','Y','Z','0']
assert len(VN_CHAR_MAP) == 30


# ---------------------------------------------------------------------------
# Python inference engine — mirrors golden_infer() in lpr_golden.c
# Weights and activations are float32; input pixels are [0, 255] float32.
# ---------------------------------------------------------------------------

def load_golden_weights_bin(path):
    """Load raw GoldenWeights struct (float32) and reshape into layer arrays."""
    with open(path, 'rb') as f:
        data = np.frombuffer(f.read(), dtype='<f4')
    assert len(data) == 24798, f"Expected 24798 float32, got {len(data)}"

    idx = 0
    def take(n):
        nonlocal idx
        s = data[idx:idx+n].copy()
        idx += n
        return s

    conv1_w = take(8*3*3*1).reshape(8, 3, 3, 1)    # [C_out][KH][KW][C_in]
    conv1_b = take(8)
    conv2_w = take(16*3*3*8).reshape(16, 3, 3, 8)
    conv2_b = take(16)
    fc_w    = take(784*30).reshape(784, 30)          # [in][out]
    fc_b    = take(30)
    assert idx == 24798
    return conv1_w, conv1_b, conv2_w, conv2_b, fc_w, fc_b


def conv2d_relu_hwc(inp, w, b, pad=1):
    """
    inp: [H,W,C_in]  float32   (HWC layout, pixel values in [0,255])
    w:   [C_out,KH,KW,C_in]  float32
    b:   [C_out]  float32
    Returns [H,W,C_out] float32  (same-spatial with pad=1, 3×3 kernel)
    Mirrors golden_conv2d_relu() — vectorized im2col for speed.
    """
    H, W, C_in = inp.shape
    C_out, KH, KW, _ = w.shape
    out_h = H + 2*pad - KH + 1
    out_w = W + 2*pad - KW + 1
    padded = np.pad(inp.astype(np.float32),
                    ((pad,pad),(pad,pad),(0,0)), mode='constant')
    # Build patch matrix [out_h*out_w, KH*KW*C_in] via stride tricks
    s = padded.strides
    patches = np.lib.stride_tricks.as_strided(
        padded,
        shape=(out_h, out_w, KH, KW, C_in),
        strides=(s[0], s[1], s[0], s[1], s[2])
    ).reshape(out_h * out_w, KH * KW * C_in)
    kern_mat = w.reshape(C_out, KH * KW * C_in)       # [C_out, KHKWCin]
    out = (patches @ kern_mat.T + b).astype(np.float32)  # [N, C_out]
    return np.maximum(out, 0).reshape(out_h, out_w, C_out)


def maxpool_2x2_hwc(inp):
    """inp: [H,W,C] float32 -> [H//2,W//2,C] float32  (vectorized)"""
    H, W, C = inp.shape
    return inp.reshape(H//2, 2, W//2, 2, C).max(axis=(1,3))


def fc_hwc(inp, w, b):
    """inp: [D] float32  w: [D,out] float32  b: [out] float32 -> [out] float32"""
    return (b + inp @ w).astype(np.float32)


def golden_infer_python(image_hwc_uint8, conv1_w, conv1_b, conv2_w, conv2_b, fc_w, fc_b):
    """
    image_hwc_uint8: [28,28,1] uint8 in [0,255]
    Returns predicted class index.
    Mirrors golden_infer() exactly (float32 arithmetic, HWC layout).
    """
    inp = image_hwc_uint8.astype(np.float32)          # [28,28,1] float32 [0,255]
    x = conv2d_relu_hwc(inp, conv1_w, conv1_b, pad=1)  # [28,28,8]
    x = maxpool_2x2_hwc(x)                             # [14,14,8]
    x = conv2d_relu_hwc(x, conv2_w, conv2_b, pad=1)    # [14,14,16]
    x = maxpool_2x2_hwc(x)                             # [7,7,16]
    flat = x.flatten()                                  # [784]
    logits = fc_hwc(flat, fc_w, fc_b)                  # [30]
    return int(np.argmax(logits))


def eval_python_mode(weights_path, data_dir):
    """Python-mode evaluation using the above golden inference engine."""
    print(f"[eval] Loading weights: {weights_path}")
    conv1_w, conv1_b, conv2_w, conv2_b, fc_w, fc_b = load_golden_weights_bin(weights_path)

    split_path = Path(data_dir) / 'test.pt'
    if not split_path.exists():
        raise FileNotFoundError(f"Test split not found: {split_path}\nRun preprocess.py first.")

    d = torch.load(split_path, weights_only=True)
    X = d['X'].numpy()  # [N,1,H,W] float32 in [0,255]
    y = d['y'].numpy()  # [N]

    print(f"[eval] Test set: {len(X)} images")

    correct = 0
    confusion = np.zeros((30, 30), dtype=np.int32)

    for i in range(len(X)):
        img_uint8 = X[i, 0].round().clip(0, 255).astype(np.uint8)
        img_hwc = img_uint8[:, :, np.newaxis]  # [28,28,1]

        pred = golden_infer_python(img_hwc, conv1_w, conv1_b, conv2_w, conv2_b, fc_w, fc_b)
        gt   = int(y[i])
        if pred == gt:
            correct += 1
        confusion[gt, pred] += 1

        if (i + 1) % 500 == 0:
            print(f"[eval]   {i+1}/{len(X)}  running_acc={correct/(i+1):.2%}")

    acc = correct / len(X)
    return acc, confusion


def eval_binary_mode(weights_path, data_dir, exe_path):
    """Binary mode: pipe each image through lpr_golden_test executable."""
    split_path = Path(data_dir) / 'test.pt'
    d = torch.load(split_path, weights_only=True)
    X = d['X'].numpy()
    y = d['y'].numpy()
    print(f"[eval] Binary mode: {len(X)} images via {exe_path}")

    correct = 0
    confusion = np.zeros((30, 30), dtype=np.int32)

    with tempfile.TemporaryDirectory() as tmpdir:
        img_path = os.path.join(tmpdir, 'img.bin')
        for i in range(len(X)):
            img_uint8 = X[i, 0].round().clip(0, 255).astype(np.uint8)
            img_int32 = img_uint8.astype(np.int32).flatten()
            with open(img_path, 'wb') as f:
                f.write(struct.pack(f'<{len(img_int32)}i', *img_int32))

            result = subprocess.run(
                [exe_path, weights_path, img_path],
                capture_output=True, text=True, timeout=10
            )
            pred = -1
            for line in result.stdout.splitlines():
                if 'class=' in line.lower():
                    try:
                        pred = int(line.split('class=')[1].split()[0])
                    except (ValueError, IndexError):
                        pass
            gt = int(y[i])
            if pred == gt:
                correct += 1
            confusion[gt, pred] += 1

    acc = correct / len(X)
    return acc, confusion


def print_report(acc, confusion, out_path=None):
    lines = []
    lines.append("=" * 60)
    lines.append(f"  Top-1 Accuracy: {acc:.2%}  ({acc*100:.2f}%)")
    if acc >= 0.89:
        lines.append("  RESULT: PASS (>= 89% target)")
    else:
        lines.append("  RESULT: FAIL (< 89% target)")
    lines.append("=" * 60)
    lines.append("")
    lines.append("Per-class accuracy:")
    lines.append(f"  {'Char':<6} {'Correct':>8} {'Total':>8} {'Acc':>8}")
    lines.append(f"  {'-'*6} {'-'*8} {'-'*8} {'-'*8}")
    for i, ch in enumerate(VN_CHAR_MAP):
        total = int(confusion[i].sum())
        corr  = int(confusion[i, i])
        cls_acc = corr / total if total > 0 else 0.0
        lines.append(f"  {ch:<6} {corr:>8} {total:>8} {cls_acc:>7.1%}")
    lines.append("")

    report = '\n'.join(lines)
    print(report)
    if out_path:
        with open(out_path, 'w') as f:
            f.write(report)
        print(f"[eval] Report saved to {out_path}")

    if out_path:
        cm_path = str(out_path).replace('.txt', '_confusion.npy')
        np.save(cm_path, confusion)
        print(f"[eval] Confusion matrix saved to {cm_path}")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--mode',     choices=['python','binary'], default='python')
    parser.add_argument('--weights',  default='golden_weights.bin')
    parser.add_argument('--data_dir', default='datasets/processed')
    parser.add_argument('--exe',      default='../build/lpr_golden_test',
                        help='Path to lpr_golden_test binary (--mode binary only)')
    parser.add_argument('--out',      default='eval_report.txt',
                        help='Output report file')
    args = parser.parse_args()

    if not Path(args.weights).exists():
        print(f"[eval] ERROR: weights file not found: {args.weights}")
        sys.exit(1)

    if args.mode == 'python':
        acc, confusion = eval_python_mode(args.weights, args.data_dir)
    else:
        if not Path(args.exe).exists():
            print(f"[eval] ERROR: exe not found: {args.exe}. Build with: cd 07_sw && make test")
            sys.exit(1)
        acc, confusion = eval_binary_mode(args.weights, args.data_dir, args.exe)

    print_report(acc, confusion, args.out)


if __name__ == '__main__':
    main()
