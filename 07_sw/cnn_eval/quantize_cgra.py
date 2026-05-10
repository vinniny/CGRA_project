#!/usr/bin/env python3
"""
quantize_cgra.py — Export MnistCGRA weights to CGRA binary layouts.

Reads: mnist_cgra.pt  (float32 state dict from train_mnist.py)

Emits three files in this directory:
  mnist_weights_conv.bin    — INT16 conv weights (tile-bank layout)
  mnist_weights_spm.bin     — INT16 FC weights   (SPM per-PE layout, v2-compatible)
  mnist_weights_scale.h     — C header: scale/shift constants + weight counts
  mnist_golden_test.bin     — 1000 test images (INT16, 28×28 each) + labels

INT16 quantization (per-tensor symmetric, matches LPR scheme):
  scale  = max(|w_float|) / 32767
  w_int16 = round(w_float / scale)

Bias quantization (same scale as weights, stored as INT32 bias-scale units):
  b_int32 = round(b_float / scale)

Conv weight layout (tile-bank):
  conv1_w[out_ch=8][ky=3][kx=3][in_ch=1]  × 2 bytes = 144 bytes
  conv1_b[out_ch=8]                          × 4 bytes (INT32) = 32 bytes
  conv2_w[out_ch=16][ky=3][kx=3][in_ch=8]  × 2 bytes = 2304 bytes
  conv2_b[out_ch=16]                         × 4 bytes = 64 bytes
  Total: 2544 bytes

FC weight layout (SPM, one file per PE within the blob):
  Arranged for FC1 (400→64) and FC2 (64→10) using the v2 SPM scheme.
  FC1: 64 neurons. SPM stride = ceiling(400/2) = 200 INT16x2 words per neuron,
       packed as INT16x2 (two INT16 weights per 32-bit word).
       FC1 layout: [w[0..199] for neuron 0] [w[0..199] for neuron 1] ... × 64 = 12800 words
  FC2: 10 neurons × 32 words (ceiling(64/2)=32) = 320 words
  Total FC SPM: (12800 + 320) × 4 bytes = 52,480 bytes

Usage:
    python3 quantize_cgra.py [--checkpoint mnist_cgra.pt]
"""

import argparse
import struct
import numpy as np
import torch
from pathlib import Path
from torchvision import datasets, transforms

SCRIPT_DIR = Path(__file__).parent
INT16_MAX  = 32767
INT32_MAX  = 2147483647


def load_model():
    from train_mnist import MnistCGRA
    model = MnistCGRA()
    ckpt  = SCRIPT_DIR / "mnist_cgra.pt"
    if not ckpt.exists():
        raise FileNotFoundError(f"{ckpt} not found — run train_mnist.py first")
    model.load_state_dict(torch.load(ckpt, map_location="cpu"))
    model.eval()
    return model


def quantize_symmetric(arr: np.ndarray) -> tuple[np.ndarray, float]:
    """Return (int16_array, scale) for symmetric per-tensor quantization."""
    scale = float(np.max(np.abs(arr))) / INT16_MAX
    if scale == 0:
        scale = 1.0
    q = np.round(arr / scale).astype(np.int16)
    q = np.clip(q, -INT16_MAX, INT16_MAX).astype(np.int16)
    return q, scale


def conv_weight_hwc(module: torch.nn.Conv2d) -> np.ndarray:
    """Return weight as [out_ch, kH, kW, in_ch] numpy float32."""
    w = module.weight.detach().numpy()   # [out, in, kH, kW]
    return w.transpose(0, 2, 3, 1)      # → [out, kH, kW, in]


def emit_conv_bin(model, out_path: Path) -> dict:
    """Write conv1 + conv2 weights/biases (INT16/INT32) to binary file.

    Returns scale dict for the C header.
    """
    scales = {}

    with open(out_path, "wb") as f:
        for layer_name, module in [("conv1", model.conv1), ("conv2", model.conv2)]:
            w_hwc = conv_weight_hwc(module)
            b_f   = module.bias.detach().numpy()

            w_q, scale_w = quantize_symmetric(w_hwc)
            # Bias quantised at same scale so MAC accumulator units match:
            #   out_acc_int32 = sum(input_int16 * weight_int16)
            #   out_float     = out_acc_int32 * scale_w^2   (for input normalised to [-1,1]→INT16)
            # For the CGRA we store bias as int32 in accumulator units:
            #   b_acc = b_float / scale_w
            b_acc = np.round(b_f / scale_w).astype(np.int32)
            b_acc = np.clip(b_acc, -INT32_MAX, INT32_MAX).astype(np.int32)

            scales[f"{layer_name}_scale_w"] = scale_w

            # Write weights flat: [out, kH, kW, in] row-major
            f.write(w_q.tobytes())
            # Write biases as INT32
            f.write(b_acc.tobytes())

            total_weights = int(np.prod(w_q.shape))
            print(f"  {layer_name}: weights={total_weights} INT16, bias={len(b_acc)} INT32, "
                  f"scale_w={scale_w:.6f}")

    print(f"  → {out_path} ({out_path.stat().st_size} bytes)")
    return scales


def emit_spm_fc_bin(model, out_path: Path) -> dict:
    """Write FC1 + FC2 weights in v2 SPM layout (one blob).

    SPM layout (matches cgra_kernels_lpr SPM v2 scheme, LPR_FC_SPM_BYTES_PER_NEURON):
      For FC(n_in, n_out):
        n_words_per_neuron = n_in  (one INT16 in lower 16 bits of each 32-bit word)
        blob = [neuron_0_weights..., neuron_1_weights..., ..., neuron_{n_out-1}_weights]

    FC1: n_in=400, n_words=400, n_out=64  → 400×64 = 25600 words (102400 bytes)
    FC2: n_in=64,  n_words=64,  n_out=10  → 64×10  =   640 words  (2560 bytes)
    Total: 104960 bytes
    """
    scales = {}
    buf = bytearray()

    for layer_name in ["fc1", "fc2"]:
        module = getattr(model, layer_name)
        w_f = module.weight.detach().numpy()  # [n_out, n_in]
        b_f = module.bias.detach().numpy()

        n_out, n_in = w_f.shape
        n_words = n_in   # one INT16 per 32-bit word (LPR v2 format)

        w_q, scale_w = quantize_symmetric(w_f)
        b_acc = np.round(b_f / scale_w).astype(np.int32)
        b_acc = np.clip(b_acc, -INT32_MAX, INT32_MAX).astype(np.int32)

        scales[f"{layer_name}_scale_w"] = scale_w
        scales[f"{layer_name}_n_in"]    = n_in
        scales[f"{layer_name}_n_out"]   = n_out
        scales[f"{layer_name}_n_words"] = n_words

        for neuron in range(n_out):
            row = w_q[neuron]  # [n_in] int16
            # Sign-extend INT16 to INT32 (matches LPR: fc_wq.astype(np.int32))
            # Negative weights need 0xFFFFFF.. upper bytes for correct MAC arithmetic
            for w in row:
                buf += struct.pack("<I", int(w) & 0xFFFFFFFF)

        print(f"  {layer_name}: n_in={n_in}, n_out={n_out}, "
              f"n_words/neuron={n_words}, scale_w={scale_w:.6f}")

    with open(out_path, "wb") as f:
        f.write(buf)
    print(f"  → {out_path} ({len(buf)} bytes)")

    scales["fc1_b"] = model.fc1.bias.detach().numpy().tolist()
    scales["fc2_b"] = model.fc2.bias.detach().numpy().tolist()
    scales["fc1_b_q"] = np.round(model.fc1.bias.detach().numpy() / scales["fc1_scale_w"]).astype(np.int32).tolist()
    scales["fc2_b_q"] = np.round(model.fc2.bias.detach().numpy() / scales["fc2_scale_w"]).astype(np.int32).tolist()
    return scales


def emit_scale_header(conv_scales: dict, fc_scales: dict, out_path: Path):
    """Write C header with all scale/shift constants."""
    # Compute right-shift amounts to bring INT32 accumulator back to INT16 range.
    # For conv layer: acc = sum(input_int16 * weight_int16)
    #   input_int16  ~ input_float / scale_input  (scale_input ≈ 1.0 for normalized MNIST)
    #   weight_int16 ~ weight_float / scale_w
    #   acc_float    = acc_int32 * scale_input * scale_w
    #   output_int16 = acc_float / scale_output ≈ acc_int32 * (scale_input * scale_w / scale_output)
    # For simplicity, use fixed shift so output ≈ INT16 range.
    import math

    def right_shift_for(scale, input_scale=1.0/32767.0, out_scale=1.0/32767.0):
        combined = input_scale * scale / out_scale
        if combined <= 0:
            return 0
        # We want 2^(-shift) ≈ combined → shift = -log2(combined)
        shift = max(0, int(math.floor(-math.log2(combined))))
        return min(shift, 31)

    with open(out_path, "w") as f:
        f.write("#pragma once\n")
        f.write("/* Auto-generated by quantize_cgra.py — do not edit */\n\n")
        f.write("#include <stdint.h>\n\n")

        f.write("/* ---- Conv1 ---- */\n")
        sc1 = conv_scales.get("conv1_scale_w", 1.0)
        f.write(f"#define MNIST_CONV1_SCALE_W_F   {sc1:.8f}f\n")
        f.write(f"#define MNIST_CONV1_N_OUT        8\n")
        f.write(f"#define MNIST_CONV1_N_IN         1\n")
        f.write(f"#define MNIST_CONV1_K            3\n")

        f.write("\n/* ---- Conv2 ---- */\n")
        sc2 = conv_scales.get("conv2_scale_w", 1.0)
        f.write(f"#define MNIST_CONV2_SCALE_W_F   {sc2:.8f}f\n")
        f.write(f"#define MNIST_CONV2_N_OUT       16\n")
        f.write(f"#define MNIST_CONV2_N_IN         8\n")
        f.write(f"#define MNIST_CONV2_K            3\n")

        f.write("\n/* ---- FC1 (400→64) ---- */\n")
        sfc1 = fc_scales.get("fc1_scale_w", 1.0)
        f.write(f"#define MNIST_FC1_SCALE_W_F     {sfc1:.8f}f\n")
        f.write(f"#define MNIST_FC1_N_IN         400\n")
        f.write(f"#define MNIST_FC1_N_OUT         64\n")
        f.write(f"#define MNIST_FC1_N_WORDS       {fc_scales.get('fc1_n_words', 200)}\n")

        f.write("\n/* ---- FC2 (64→10) ---- */\n")
        sfc2 = fc_scales.get("fc2_scale_w", 1.0)
        f.write(f"#define MNIST_FC2_SCALE_W_F     {sfc2:.8f}f\n")
        f.write(f"#define MNIST_FC2_N_IN          64\n")
        f.write(f"#define MNIST_FC2_N_OUT         10\n")
        f.write(f"#define MNIST_FC2_N_WORDS       {fc_scales.get('fc2_n_words', 32)}\n")

        f.write("\n/* ---- Bias arrays (INT32, accumulator units) ---- */\n")
        for fc_name, key in [("FC1", "fc1_b_q"), ("FC2", "fc2_b_q")]:
            vals = fc_scales.get(key, [])
            f.write(f"static const int32_t mnist_{fc_name.lower()}_bias_q[{len(vals)}] = {{\n    ")
            f.write(", ".join(str(int(v)) for v in vals))
            f.write("\n};\n")

    print(f"  → {out_path}")


def emit_test_images(n_images: int, out_path: Path):
    """Write N test images as int16 (28×28 normalized × 32767) + int8 labels."""
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,)),
    ])
    test_ds = datasets.MNIST(SCRIPT_DIR / "data", train=False, download=True, transform=transform)
    buf = bytearray()
    labels = bytearray()
    for i in range(min(n_images, len(test_ds))):
        img, label = test_ds[i]
        # img: [1, 28, 28] float32 in roughly [-1, +1]
        img_int16 = (img.numpy()[0] * 32767).round().clip(-32767, 32767).astype(np.int16)
        buf += img_int16.tobytes()
        labels += bytes([label])
    # Pack: [images block] then [labels block]
    full = struct.pack("<I", n_images) + bytes(buf) + bytes(labels)
    with open(out_path, "wb") as f:
        f.write(full)
    print(f"  → {out_path} ({len(full)} bytes, {n_images} images)")


def main(args):
    model = load_model()

    print("Emitting conv weight binary...")
    conv_out  = SCRIPT_DIR / "mnist_weights_conv.bin"
    conv_scales = emit_conv_bin(model, conv_out)

    print("Emitting SPM FC weight binary...")
    spm_out   = SCRIPT_DIR / "mnist_weights_spm.bin"
    fc_scales = emit_spm_fc_bin(model, spm_out)

    print("Emitting C scale header...")
    emit_scale_header(conv_scales, fc_scales, SCRIPT_DIR / "mnist_weights_scale.h")

    print(f"Emitting {args.test_images} test images...")
    emit_test_images(args.test_images, SCRIPT_DIR / "mnist_golden_test.bin")

    print("\nDone. Files written to", SCRIPT_DIR)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--checkpoint",   default="mnist_cgra.pt")
    parser.add_argument("--test-images",  type=int, default=10000)
    args = parser.parse_args()
    main(args)
