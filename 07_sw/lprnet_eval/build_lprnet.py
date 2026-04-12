"""
Construct an LPRNet-style ONNX model from scratch using onnx.helper.

LPRNet (Zherzdev & Gruzdev, Intel AI 2018 — "LPRNet: License Plate
Recognition via Deep Neural Networks", https://arxiv.org/abs/1806.10447)
is an end-to-end CTC-decoded plate OCR network. Input 24x94 RGB, backbone
is a stack of Conv3x3 + BN + ReLU blocks, output is 18 timesteps x 37
character classes (greedy CTC on the host).

This script builds the *topology* (ops + shapes, random weights) so we
can feed it to ONNX Runtime for a latency baseline and walk the graph to
count MACs per layer. We don't need a trained model for feasibility
analysis — just the shapes.

Architecture follows the reference paper Table 1 with lightly tweaked
channel counts to keep everything divisible by 16 (matches the CGRA's
PE row width) for fair CGRA-friendliness.

Run:   python build_lprnet.py   →  lprnet.onnx
"""
import numpy as np
import onnx
from onnx import helper, TensorProto, numpy_helper


def make_init(name, shape, dtype=np.float32):
    """Random Gaussian initializer."""
    arr = np.random.randn(*shape).astype(dtype) * 0.05
    return numpy_helper.from_array(arr, name=name)


def make_bias(name, channels):
    arr = np.zeros((channels,), dtype=np.float32)
    return numpy_helper.from_array(arr, name=name)


def conv(input_name, out_name, in_c, out_c, kh, kw, sh=1, sw=1, pad_h=0, pad_w=0, bias=True):
    """Build a Conv node (+ optional bias add folded via ONNX Conv bias input)."""
    inits = []
    w = make_init(f"{out_name}_w", (out_c, in_c, kh, kw))
    inits.append(w)
    inputs = [input_name, w.name]
    if bias:
        b = make_bias(f"{out_name}_b", out_c)
        inits.append(b)
        inputs.append(b.name)
    node = helper.make_node(
        "Conv",
        inputs=inputs,
        outputs=[out_name],
        kernel_shape=[kh, kw],
        strides=[sh, sw],
        pads=[pad_h, pad_w, pad_h, pad_w],
    )
    return node, inits


def relu(input_name, out_name):
    return helper.make_node("Relu", [input_name], [out_name])


def maxpool(input_name, out_name, kh, kw, sh=None, sw=None, pad_h=0, pad_w=0):
    if sh is None: sh = kh
    if sw is None: sw = kw
    return helper.make_node(
        "MaxPool",
        inputs=[input_name],
        outputs=[out_name],
        kernel_shape=[kh, kw],
        strides=[sh, sw],
        pads=[pad_h, pad_w, pad_h, pad_w],
    )


def build(scale=1.0):
    nodes = []
    inits = []

    def s(c):
        # Scale a channel count, snap to a multiple of 16 (PE-row width),
        # never below 16.
        v = max(16, int(round(c * scale)))
        return ((v + 15) // 16) * 16

    c1 = s(64)
    c2 = s(128)
    c3 = s(256)
    c4 = s(64)
    c5 = s(256)
    num_classes = 37

    # Input: 1 x 3 x 24 x 94  (NCHW, batch 1, 3 channels, H=24, W=94)
    inp = helper.make_tensor_value_info("input", TensorProto.FLOAT, [1, 3, 24, 94])

    # ── Block 1: Conv3x3 stem, 3 → c1 channels ──────────────────────
    n, i = conv("input", "conv1",   3,  c1, 3, 3, pad_h=1, pad_w=1)
    nodes.append(n); inits.extend(i)
    nodes.append(relu("conv1", "relu1"))
    nodes.append(maxpool("relu1", "pool1", kh=3, kw=3, sh=1, sw=1, pad_h=1, pad_w=1))

    # ── Block 2: Conv3x3, c1 → c2 channels ──────────────────────────
    n, i = conv("pool1", "conv2", c1, c2, 3, 3, pad_h=1, pad_w=1)
    nodes.append(n); inits.extend(i)
    nodes.append(relu("conv2", "relu2"))
    nodes.append(maxpool("relu2", "pool2", kh=3, kw=3, sh=2, sw=1, pad_h=1, pad_w=1))

    # ── Block 3: Conv3x3, c2 → c3 channels ──────────────────────────
    n, i = conv("pool2", "conv3", c2, c3, 3, 3, pad_h=1, pad_w=1)
    nodes.append(n); inits.extend(i)
    nodes.append(relu("conv3", "relu3"))

    # ── Block 4: Conv3x3 compression, c3 → c4 channels ──────────────
    n, i = conv("relu3", "conv4", c3, c4, 3, 3, pad_h=1, pad_w=1)
    nodes.append(n); inits.extend(i)
    nodes.append(relu("conv4", "relu4"))
    nodes.append(maxpool("relu4", "pool4", kh=3, kw=3, sh=4, sw=1, pad_h=1, pad_w=1))

    # ── Head: Conv3x1 collapses the height dimension down to 1 ─────
    n, i = conv("pool4", "conv_head", c4, c5, 3, 1, pad_h=0, pad_w=0)
    nodes.append(n); inits.extend(i)
    nodes.append(relu("conv_head", "relu_head"))

    # ── Classifier: 1x13 conv to num_classes=37 (0-9, A-Z, blank) ───
    n, i = conv("relu_head", "logits", c5, num_classes, 1, 13, pad_h=0, pad_w=6)
    nodes.append(n); inits.extend(i)

    # Final output shape (walked forward by hand through all convs/pools):
    #   input   : 1 x   3 x 24 x 94
    #   conv1   : 1 x  64 x 24 x 94   (3x3, pad 1)
    #   pool1   : 1 x  64 x 24 x 94   (3x3, stride 1, pad 1)
    #   conv2   : 1 x 128 x 24 x 94
    #   pool2   : 1 x 128 x 12 x 94   (stride 2 on H)
    #   conv3   : 1 x 256 x 12 x 94
    #   conv4   : 1 x  64 x 12 x 94
    #   pool4   : 1 x  64 x  3 x 94   (stride 4 on H -> floor(11/4)+1 = 3)
    #   head    : 1 x 256 x  0 x 94   <-- BROKEN: 4x1 kernel needs H>=4
    # Fix: make head a 3x1 kernel (the paper uses the wider H here, but
    # for our characterization we just need a valid shape).
    out = helper.make_tensor_value_info("logits", TensorProto.FLOAT, [1, num_classes, 1, 94])

    graph = helper.make_graph(nodes, "LPRNet", [inp], [out], initializer=inits)
    model = helper.make_model(
        graph,
        opset_imports=[helper.make_opsetid("", 13)],
        producer_name="cgra-lprnet-eval",
    )
    model.ir_version = 8
    model = onnx.shape_inference.infer_shapes(model)
    onnx.checker.check_model(model)
    return model


if __name__ == "__main__":
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("--scale", type=float, default=1.0,
                    help="Channel scale factor (1.0 full, 0.5 small, 0.25 micro)")
    ap.add_argument("--out", default="lprnet.onnx", help="Output ONNX path")
    args = ap.parse_args()

    np.random.seed(0)
    model = build(scale=args.scale)
    onnx.save(model, args.out)
    print(f"Wrote {args.out} (scale={args.scale}, "
          f"{len(model.SerializeToString()) / 1024:.1f} KB)")
