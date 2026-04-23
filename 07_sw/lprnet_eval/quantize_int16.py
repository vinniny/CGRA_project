#!/usr/bin/env python3
"""
quantize_int16.py — Convert float GoldenWeights to INT16 for CGRA inference.

Reads vn_char_best.pt and emits:
  - golden_weights_int16.bin:  24,798 int16 values (49,596 bytes)
  - golden_weights_scale.h:    Per-layer scale + shift constants

Quantization scheme (per-tensor symmetric INT16):
  scale_w_L  = max(|w_f|) / 32767          per-layer weight scale
  w_q        = round(w_f / scale_w_L)       INT16 weight
  b_q        = round(b_f / scale_w_L)       INT16 bias in accumulator units

ARM inference flow per conv/pool output:
  1. CGRA MAC chain -> RESULT_ROW[y] = INT32 accumulator (40-bit saturated)
  2. ARM:  pre  = RESULT_ROW[y] + b_q[co]
  3. ARM:  out  = pre >> shift_L              (right-shift to INT16 range)
  4. ARM:  out  = max(0, out)                 (ReLU, conv layers only)
  5. Pass INT16 activation to next layer

FC output is NOT shifted (just argmax on raw INT32).

Binary layout mirrors GoldenWeights field order:
  conv1_w [72]    int16
  conv1_b [8]     int16
  conv2_w [1152]  int16
  conv2_b [16]    int16
  fc_w    [23520] int16
  fc_b    [30]    int16
  Total = 24,798 × 2 = 49,596 bytes
"""

import argparse
import math
import struct
import numpy as np
import torch
import torch.nn as nn
from pathlib import Path

# Must match lpr_golden.h VN_CHAR_MAP exactly
VN_CHAR_MAP = ['1','2','3','4','5','6','7','8','9',
               'A','B','C','D','E','F','G','H','K','L','M',
               'N','P','S','T','U','V','X','Y','Z','0']

INT16_MAX = 32767
INT16_MIN = -32768


class VNCharNet(nn.Module):
    def __init__(self, num_classes=30):
        super().__init__()
        self.conv1 = nn.Conv2d(1, 8,  3, padding=1, bias=True)
        self.conv2 = nn.Conv2d(8, 16, 3, padding=1, bias=True)
        self.pool  = nn.MaxPool2d(2, 2)
        self.relu  = nn.ReLU(inplace=True)
        self.fc    = nn.Linear(16 * 7 * 7, num_classes, bias=True)

    def forward(self, x):
        x = self.pool(self.relu(self.conv1(x)))
        x = self.pool(self.relu(self.conv2(x)))
        x = x.view(x.size(0), -1)
        return self.fc(x)


def extract_float_weights(model):
    """Extract float32 weights in GoldenWeights field order (mirrors quantize_to_int32.py)."""
    conv1_w = model.conv1.weight.detach().numpy().transpose(0, 2, 3, 1)  # [8,3,3,1]
    conv1_b = model.conv1.bias.detach().numpy()                           # [8]
    conv2_w = model.conv2.weight.detach().numpy().transpose(0, 2, 3, 1)  # [16,3,3,8]
    conv2_b = model.conv2.bias.detach().numpy()                           # [16]
    # PyTorch fc.weight [30,784] CHW-indexed; golden model uses HWC [784,30].
    fc_w_chw = model.fc.weight.detach().numpy().T      # [784, 30] CHW-indexed
    fc_w = fc_w_chw.reshape(16, 7, 7, 30).transpose(1, 2, 0, 3).reshape(784, 30)
    fc_b = model.fc.bias.detach().numpy()              # [30]
    return dict(conv1_w=conv1_w, conv1_b=conv1_b,
                conv2_w=conv2_w, conv2_b=conv2_b,
                fc_w=fc_w,       fc_b=fc_b)


def quant_layer(w_flat, b_flat, name):
    """
    Per-tensor symmetric INT16 quantization for one weight tensor + bias.
    Returns (w_q int16, b_q int16, scale_w float, shift int).
    """
    max_w = float(np.max(np.abs(w_flat)))
    if max_w == 0.0:
        raise ValueError(f"{name}: all-zero weight tensor")
    scale_w = max_w / INT16_MAX                         # float/int16 ratio

    w_q = np.round(w_flat / scale_w).astype(np.int32)
    w_clipped = np.clip(w_q, INT16_MIN, INT16_MAX)
    if not np.all(w_q == w_clipped):
        print(f"[quant] WARNING {name} weights: {np.sum(w_q != w_clipped)} values clipped")
    w_q = w_clipped.astype(np.int16)

    # Bias in accumulator units (same scale as weights for CGRA MAC output)
    b_q = np.round(b_flat / scale_w).astype(np.int32)
    b_clipped = np.clip(b_q, INT16_MIN, INT16_MAX)
    if not np.all(b_q == b_clipped):
        print(f"[quant] WARNING {name} bias: {np.sum(b_q != b_clipped)} values clipped to INT16")
        print(f"          max bias_q={np.max(np.abs(b_q)):.0f} — consider INT32 bias storage")
    b_q = b_clipped.astype(np.int16)

    return w_q, b_q, scale_w


def compute_shift(n_macs, max_act_int16, name):
    """
    Conservative per-layer right-shift so that:
      (n_macs * max_act * INT16_MAX) >> shift  <=  INT16_MAX

    This ensures the accumulated INT40 value, when right-shifted, fits in INT16.
    """
    max_acc = n_macs * max_act_int16 * INT16_MAX
    if max_acc == 0:
        return 0
    needed_bits = math.ceil(math.log2(max_acc + 1))
    shift = max(0, needed_bits - 15)
    max_out = max_acc >> shift
    print(f"[quant] {name}: n_macs={n_macs} max_act={max_act_int16} "
          f"max_acc={max_acc:.3e} shift={shift} max_out={max_out}")
    return shift


def write_int16_bin(fields, out_path):
    """Write all fields as little-endian int16, in GoldenWeights field order."""
    order = ['conv1_w', 'conv1_b', 'conv2_w', 'conv2_b', 'fc_w', 'fc_b']
    counts = {'conv1_w': 72, 'conv1_b': 8, 'conv2_w': 1152,
              'conv2_b': 16, 'fc_w': 23520, 'fc_b': 30}
    total = sum(counts.values())
    assert total == 24798

    with open(out_path, 'wb') as f:
        for key in order:
            arr = fields[key].flatten().astype('<i2')   # little-endian int16
            assert len(arr) == counts[key], f"{key}: expected {counts[key]} got {len(arr)}"
            f.write(arr.tobytes())

    size = Path(out_path).stat().st_size
    assert size == 24798 * 2, f"Size mismatch: {size} != {24798*2}"
    print(f"[quant] Written {out_path}  ({size} bytes = {size//2} int16)")


def write_scale_header(scales, out_path):
    """
    Write C header with per-layer scale constants and shift amounts.
    Consumed by lpr_golden.c CGRA variant and cgra_kernels_lpr.h builders.
    """
    lines = [
        "/* golden_weights_scale.h — auto-generated by quantize_int16.py */",
        "#pragma once",
        "",
        "#define LPR_WEIGHTS_ARE_INT16        1",
        "#define LPR_WEIGHTS_ARE_FLOAT32      0",
        "",
        "/* Per-layer weight scale factors (float = int16_val * SCALE_W_L) */",
    ]
    for name, sc in scales['w_scales'].items():
        cname = name.upper().replace('_', '_')
        lines.append(f"#define LPR_{cname}_SCALE_W    {sc:.10f}f")
    lines.append("")
    lines.append("/* Per-layer right-shift for accumulator -> INT16 activation */")
    for name, sh in scales['shifts'].items():
        cname = name.upper()
        lines.append(f"#define LPR_{cname}_SHIFT    {sh}")
    lines.append("")
    lines.append("/* Convenience: shift amounts as initializer for uint8_t array */")
    shifts = scales['shifts']
    lines.append(f"#define LPR_SHIFTS_INITIALIZER   {shifts['conv1']}, {shifts['conv2']}, 0  /* conv1, conv2, fc */")
    lines.append("")

    with open(out_path, 'w') as f:
        f.write('\n'.join(lines) + '\n')
    print(f"[quant] Written {out_path}")


def verify_int16_accuracy(model, q_fields, scales, data_dir, n_samples=4500):
    """Compare INT16 dequantized model argmax vs float model argmax."""
    try:
        d = torch.load(Path(data_dir) / 'test.pt', weights_only=True)
        X = d['X'][:n_samples].float()
        y = d['y'][:n_samples].numpy()
    except Exception as e:
        print(f"[quant] WARN: Could not load test split ({e}) — skipping accuracy check.")
        return None

    # Float model predictions
    model.eval()
    with torch.no_grad():
        logits_f = model(X)
        preds_f = logits_f.argmax(1).numpy()

    # INT16 dequantized forward pass (numpy reference for CGRA behaviour)
    # Input: pixel values [0,255] as INT16
    X_np = X.squeeze(1).numpy()  # [N, 28, 28]

    conv1_w_q = q_fields['conv1_w'].reshape(8, 3, 3, 1).astype(np.int32)  # [8,3,3,1]
    conv1_b_q = q_fields['conv1_b'].astype(np.int32)
    conv2_w_q = q_fields['conv2_w'].reshape(16, 3, 3, 8).astype(np.int32)
    conv2_b_q = q_fields['conv2_b'].astype(np.int32)
    fc_w_q    = q_fields['fc_w'].reshape(784, 30).astype(np.int32)
    fc_b_q    = q_fields['fc_b'].astype(np.int32)

    sh1 = scales['shifts']['conv1']
    sh2 = scales['shifts']['conv2']

    preds_q = np.zeros(len(y), dtype=np.int32)
    for i in range(len(y)):
        x = X_np[i].astype(np.int32)  # [28, 28]

        # Conv1: [28,28,1] -> [28,28,8]
        out1 = np.zeros((28, 28, 8), dtype=np.int64)
        for co in range(8):
            for kh in range(3):
                for kw in range(3):
                    dh = kh - 1; dw = kw - 1
                    for h in range(28):
                        for w in range(28):
                            ih = h + dh; iw = w + dw
                            if 0 <= ih < 28 and 0 <= iw < 28:
                                out1[h, w, co] += int(x[ih, iw]) * int(conv1_w_q[co, kh, kw, 0])
            out1[:, :, co] = (out1[:, :, co] + conv1_b_q[co]) >> sh1
        out1 = np.maximum(0, out1).astype(np.int16)  # ReLU

        # Pool1: 2x2 max -> [14,14,8]
        p1 = np.zeros((14, 14, 8), dtype=np.int16)
        for h in range(14):
            for w in range(14):
                p1[h, w] = np.maximum(np.maximum(out1[2*h,2*w], out1[2*h,2*w+1]),
                                       np.maximum(out1[2*h+1,2*w], out1[2*h+1,2*w+1]))

        # Conv2: [14,14,8] -> [14,14,16]
        out2 = np.zeros((14, 14, 16), dtype=np.int64)
        for co in range(16):
            for ci in range(8):
                for kh in range(3):
                    for kw in range(3):
                        dh = kh - 1; dw = kw - 1
                        for h in range(14):
                            for w in range(14):
                                ih = h + dh; iw = w + dw
                                if 0 <= ih < 14 and 0 <= iw < 14:
                                    out2[h, w, co] += int(p1[ih, iw, ci]) * int(conv2_w_q[co, kh, kw, ci])
            out2[:, :, co] = (out2[:, :, co] + conv2_b_q[co]) >> sh2
        out2 = np.maximum(0, out2).astype(np.int16)  # ReLU

        # Pool2: 2x2 max -> [7,7,16]
        p2 = np.zeros((7, 7, 16), dtype=np.int16)
        for h in range(7):
            for w in range(7):
                p2[h, w] = np.maximum(np.maximum(out2[2*h,2*w], out2[2*h,2*w+1]),
                                       np.maximum(out2[2*h+1,2*w], out2[2*h+1,2*w+1]))

        flat = p2.flatten().astype(np.int32)  # [784]

        # FC: [784] -> [30]
        logits_q = flat @ fc_w_q + fc_b_q  # [30] int64
        preds_q[i] = int(np.argmax(logits_q))

    match_float = np.sum(preds_q == preds_f)
    match_gt    = np.sum(preds_q == y)
    acc_gt      = match_gt / len(y)
    acc_f_gt    = np.sum(preds_f == y) / len(y)

    print(f"\n[quant] INT16 model accuracy:")
    print(f"  vs float model argmax:  {match_float}/{len(y)} = {match_float/len(y):.2%}")
    print(f"  vs ground truth:        {match_gt}/{len(y)} = {acc_gt:.2%}")
    print(f"  float model accuracy:   {acc_f_gt:.2%}")
    delta_pp = (acc_f_gt - acc_gt) * 100
    print(f"  accuracy drop:          {delta_pp:+.2f} pp")

    if delta_pp > 1.0:
        print("[quant] WARNING: >1 pp accuracy drop — consider tuning shift amounts.")
    elif delta_pp > 0.5:
        print("[quant] NOTE: >0.5 pp drop — within acceptable range but monitor.")
    else:
        print("[quant] OK: accuracy drop within 0.5 pp target.")

    return acc_gt


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--checkpoint',  default='vn_char_best.pt')
    parser.add_argument('--out_bin',     default='golden_weights_int16.bin')
    parser.add_argument('--out_scale',   default='golden_weights_scale.h')
    parser.add_argument('--out_spm',     default='golden_weights_spm.bin')
    parser.add_argument('--data_dir',    default='datasets/processed')
    parser.add_argument('--skip_verify', action='store_true')
    args = parser.parse_args()

    ckpt = torch.load(args.checkpoint, map_location='cpu', weights_only=True)
    model = VNCharNet(num_classes=30)
    model.load_state_dict(ckpt['model_state'])
    model.eval()
    print(f"[quant] Loaded checkpoint: {args.checkpoint}")
    print(f"[quant]   val_acc={ckpt.get('val_acc', 0.0):.2%}  epoch={ckpt.get('epoch', '?')}")

    w = extract_float_weights(model)

    # --- Quantize each layer ---
    print(f"\n[quant] Weight statistics and quantization:")
    print(f"{'Layer':<12} {'max|w|':<12} {'scale_w':<16} {'max|b|':<12} {'max|b_q|'}")

    conv1_wq, conv1_bq, sc_conv1 = quant_layer(w['conv1_w'].flatten(), w['conv1_b'], 'conv1')
    conv2_wq, conv2_bq, sc_conv2 = quant_layer(w['conv2_w'].flatten(), w['conv2_b'], 'conv2')
    fc_wq,    fc_bq,    sc_fc    = quant_layer(w['fc_w'].flatten(),    w['fc_b'],    'fc')

    for name, wf, wq, bf, bq, sc in [
        ('conv1', w['conv1_w'], conv1_wq, w['conv1_b'], conv1_bq, sc_conv1),
        ('conv2', w['conv2_w'], conv2_wq, w['conv2_b'], conv2_bq, sc_conv2),
        ('fc',    w['fc_w'],    fc_wq,    w['fc_b'],    fc_bq,    sc_fc),
    ]:
        print(f"  {name:<10} {np.max(np.abs(wf)):<12.4f} {sc:<16.6e} "
              f"{np.max(np.abs(bf)):<12.4f} {np.max(np.abs(bq.astype(np.int32)))}")

    # --- Compute per-layer shifts ---
    # Conv1: 9 MACs, input pixels in [0, 255] (treated as INT16)
    # Conv2: 72 MACs, input is INT16 output of Pool1 (max ≈ acc_max >> sh1)
    # FC: no shift needed (argmax on raw INT32)
    print(f"\n[quant] Shift computation:")
    sh1 = compute_shift(9, 255, 'conv1')
    max_after_conv1 = int((9 * 255 * INT16_MAX) >> sh1)
    sh2 = compute_shift(72, max_after_conv1, 'conv2')
    max_after_conv2 = int((72 * max_after_conv1 * INT16_MAX) >> sh2)
    max_fc_acc = 784 * max_after_conv2 * INT16_MAX
    print(f"[quant] fc: n_macs=784 max_act={max_after_conv2} "
          f"max_acc={max_fc_acc:.3e} shift=0 (no shift, argmax on raw)")
    if max_fc_acc > (1 << 39):
        print(f"[quant] WARNING: FC accumulator may overflow 40-bit! Consider reducing shifts.")

    # Reshape quantized weights back to field shapes for binary writing
    q_fields = {
        'conv1_w': conv1_wq.reshape(8, 3, 3, 1),
        'conv1_b': conv1_bq,
        'conv2_w': conv2_wq.reshape(16, 3, 3, 8),
        'conv2_b': conv2_bq,
        'fc_w':    fc_wq.reshape(784, 30),
        'fc_b':    fc_bq,
    }

    scales = {
        'w_scales': {'conv1_w': sc_conv1, 'conv2_w': sc_conv2, 'fc_w': sc_fc},
        'shifts':   {'conv1': sh1, 'conv2': sh2},
    }

    write_int16_bin(q_fields, args.out_bin)
    write_scale_header(scales, args.out_scale)

    # SPM-layout FC weights: fc_w_q transposed to [30, 784] and sign-extended
    # to int32 so each word is directly DMA-able to PE SPM.
    # Format: 30 neurons × 784 words × 4 bytes = 92,160 bytes.
    # neuron n's weights occupy byte range [n*784*4 .. (n+1)*784*4).
    fc_w_spm = fc_wq.reshape(784, 30).T.astype(np.int32)  # [30, 784]
    fc_w_spm.tofile(args.out_spm)
    print(f"\n[quant] SPM-layout FC weights written to {args.out_spm}")
    print(f"  Shape: {fc_w_spm.shape}  ({fc_w_spm.nbytes} bytes)")
    print(f"  Layout: fc_w_spm[neuron][input_idx] as int32 (30 × 784 × 4 B)")

    if not args.skip_verify:
        verify_int16_accuracy(model, q_fields, scales, args.data_dir)

    print(f"\n[quant] Done.")
    print(f"  INT16 weights: {args.out_bin}  (49,596 bytes)")
    print(f"  SPM weights:   {args.out_spm}  (92,160 bytes)")
    print(f"  Scale header:  {args.out_scale}")
    print(f"  CONV1_SHIFT={sh1}, CONV2_SHIFT={sh2}, FC_SHIFT=0")


if __name__ == '__main__':
    main()
