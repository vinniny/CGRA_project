"""
Analyze lprnet.onnx for CGRA feasibility and run an x86_64 baseline.

Outputs a per-layer breakdown:
  - Op type, input/output shape, kernel size
  - MAC count (multiply-accumulates) for the layer
  - Weight size in bytes (INT8 assumption)
  - Whether the op maps to the CGRA's 21-op ISA
  - Whether the activation tensor fits in 64 KB tile memory (or how it
    must be chunked)

And then runs 100 inferences through ONNX Runtime on synthetic input to
give a wall-time baseline.

Runs on the WSL2 x86_64 dev host — no hardware touched.
"""
import time
import numpy as np
import onnx
import onnxruntime as ort

MODEL_PATH = "lprnet.onnx"
TILE_MEM_BYTES = 64 * 1024          # 4 banks x 4096 x 32-bit = 64 KB
CGRA_SUPPORTED_OPS = {
    # Ops the 21-op ISA can express (Conv = chunked MAC via im2col,
    # MaxPool = OP_MAX sweep, Relu = OP_RELU, FC/Gemm = chunked MAC):
    "Conv", "Relu", "MaxPool", "Gemm", "MatMul", "Add", "Mul", "Sub",
    # Reshape/transpose are free (just pointer math in the DMA):
    "Reshape", "Transpose", "Flatten",
    # BatchNorm folds into the preceding conv at quantization time:
    "BatchNormalization",
}
CGRA_UNSUPPORTED_OPS = {
    # Softmax needs exp + division, which we don't have
    "Softmax", "LogSoftmax",
    # Transformer primitives
    "LayerNormalization", "Attention",
    # Depthwise conv — doesn't vectorize on our 16-PE mesh
    "ConvTranspose",
    # Division / power / non-linear
    "Div", "Pow", "Exp", "Log", "Sigmoid", "Tanh", "Gelu",
}


def shape_from_proto(proto):
    """Pull a list of ints out of a ValueInfoProto shape."""
    if not proto.type.tensor_type.HasField("shape"):
        return None
    return [d.dim_value if d.dim_value > 0 else -1
            for d in proto.type.tensor_type.shape.dim]


def collect_shapes(model):
    """Return {tensor_name: shape} for all value_info after shape inference."""
    shapes = {}
    for v in list(model.graph.input) + list(model.graph.output) + list(model.graph.value_info):
        shapes[v.name] = shape_from_proto(v)
    # Initializers (weights) are tensors themselves — use their dims
    for init in model.graph.initializer:
        shapes[init.name] = list(init.dims)
    return shapes


def get_attr(node, name, default=None):
    for a in node.attribute:
        if a.name == name:
            if a.type == onnx.AttributeProto.INT:
                return a.i
            if a.type == onnx.AttributeProto.INTS:
                return list(a.ints)
            if a.type == onnx.AttributeProto.FLOAT:
                return a.f
    return default


def mac_count(node, shapes):
    """
    MAC count for common ops. Returns 0 for ops that have no multiplies.
    """
    if node.op_type == "Conv":
        out_shape = shapes.get(node.output[0])
        w_shape   = shapes.get(node.input[1])
        if out_shape is None or w_shape is None:
            return 0
        # out_shape = [N, out_c, H, W]
        # w_shape   = [out_c, in_c, kh, kw]
        n, oc, oh, ow = out_shape
        ocw, icw, kh, kw = w_shape
        return n * oc * oh * ow * icw * kh * kw
    if node.op_type in ("Gemm", "MatMul"):
        a_shape = shapes.get(node.input[0])
        b_shape = shapes.get(node.input[1])
        if a_shape is None or b_shape is None:
            return 0
        # Rough: M*K*N
        return int(np.prod(a_shape[:-1])) * a_shape[-1] * b_shape[-1]
    return 0


def weight_bytes(node, shapes, bytes_per_elem):
    if node.op_type == "Conv":
        w_shape = shapes.get(node.input[1])
        if not w_shape:
            return 0
        return int(np.prod(w_shape)) * bytes_per_elem
    if node.op_type in ("Gemm", "MatMul"):
        b_shape = shapes.get(node.input[1])
        if not b_shape:
            return 0
        return int(np.prod(b_shape)) * bytes_per_elem
    return 0


def activation_bytes(tensor_name, shapes, bytes_per_elem):
    sh = shapes.get(tensor_name)
    if not sh:
        return 0
    return int(np.prod([d if d > 0 else 1 for d in sh])) * bytes_per_elem


def fmt_int(n):
    for unit in ("", "K", "M", "G"):
        if abs(n) < 1000:
            return f"{n:6.1f}{unit}"
        n /= 1000.0
    return f"{n:6.1f}T"


def fmt_bytes(n):
    for unit, div in (("B", 1), ("KB", 1024), ("MB", 1024**2)):
        if n < div * 1024 or unit == "MB":
            return f"{n/div:6.1f} {unit}"
    return f"{n} B"


def fmt_shape(sh):
    if sh is None:
        return "?"
    return "x".join(str(d) if d > 0 else "?" for d in sh)


def main():
    print(f"\n=== LPRNet ONNX analysis: {MODEL_PATH} ===\n")
    model = onnx.load(MODEL_PATH)
    model = onnx.shape_inference.infer_shapes(model)
    shapes = collect_shapes(model)

    print(f"{'#':>3}  {'Op':<16} {'Input shape':<20} {'Output shape':<20} {'K':<6} "
          f"{'MACs':>10} {'INT8 weights':>14} {'INT8 activ':>14} {'CGRA?':<6}")
    print("-" * 120)

    total_macs = 0
    total_weight_bytes_int8 = 0
    total_weight_bytes_fp32 = 0
    max_activation_int8 = 0
    unsupported_ops = []

    for i, node in enumerate(model.graph.nodes if False else model.graph.node):
        in_shape  = shapes.get(node.input[0]) if node.input else None
        out_shape = shapes.get(node.output[0]) if node.output else None

        kstr = ""
        if node.op_type in ("Conv", "MaxPool"):
            ks = get_attr(node, "kernel_shape")
            if ks:
                kstr = "x".join(str(k) for k in ks)

        m = mac_count(node, shapes)
        wb_int8 = weight_bytes(node, shapes, 1)
        wb_fp32 = weight_bytes(node, shapes, 4)
        ab_int8 = activation_bytes(node.output[0], shapes, 1) if node.output else 0

        total_macs += m
        total_weight_bytes_int8 += wb_int8
        total_weight_bytes_fp32 += wb_fp32
        max_activation_int8 = max(max_activation_int8, ab_int8)

        if node.op_type in CGRA_SUPPORTED_OPS:
            fit = "YES"
        elif node.op_type in CGRA_UNSUPPORTED_OPS:
            fit = "NO"
            unsupported_ops.append(node.op_type)
        else:
            fit = "?"

        print(f"{i:>3}  {node.op_type:<16} {fmt_shape(in_shape):<20} "
              f"{fmt_shape(out_shape):<20} {kstr:<6} {fmt_int(m):>10} "
              f"{fmt_bytes(wb_int8):>14} {fmt_bytes(ab_int8):>14} {fit:<6}")

    print("-" * 120)
    print(f"Total nodes              : {len(model.graph.node)}")
    print(f"Total MACs               : {fmt_int(total_macs)} ({total_macs:,})")
    print(f"Total weights (INT8)     : {fmt_bytes(total_weight_bytes_int8)}")
    print(f"Total weights (FP32)     : {fmt_bytes(total_weight_bytes_fp32)}")
    print(f"Largest activation (INT8): {fmt_bytes(max_activation_int8)}  "
          f"[tile memory = {fmt_bytes(TILE_MEM_BYTES)}]")
    if max_activation_int8 > TILE_MEM_BYTES:
        print(f"   ⚠  Activation exceeds tile memory — "
              f"must be chunked (ratio {max_activation_int8 / TILE_MEM_BYTES:.1f}x)")
    else:
        print(f"   ✓  Fits in tile memory without chunking")

    if unsupported_ops:
        print(f"\n⚠  Unsupported ops found: {set(unsupported_ops)}")
    else:
        print(f"\n✓  All ops map onto the CGRA 21-op ISA "
              f"(Conv = chunked MAC via im2col, MaxPool = OP_MAX sweep)")

    # ── x86_64 baseline ────────────────────────────────────────────
    print(f"\n=== x86_64 ONNX Runtime baseline ===\n")
    opts = ort.SessionOptions()
    opts.graph_optimization_level = ort.GraphOptimizationLevel.ORT_ENABLE_ALL
    sess = ort.InferenceSession(MODEL_PATH, sess_options=opts,
                                providers=["CPUExecutionProvider"])
    input_name = sess.get_inputs()[0].name
    dummy = np.random.randn(1, 3, 24, 94).astype(np.float32)

    # warmup
    for _ in range(5):
        sess.run(None, {input_name: dummy})

    # time 100 iterations
    t0 = time.perf_counter()
    for _ in range(100):
        sess.run(None, {input_name: dummy})
    t1 = time.perf_counter()
    total_ms = (t1 - t0) * 1000
    per_ms = total_ms / 100
    print(f"100 inferences in {total_ms:.1f} ms  ->  {per_ms:.2f} ms / inference")
    print(f"Throughput: {1000/per_ms:.1f} FPS on x86_64 FP32")

    # Return the critical numbers for the extrapolation step
    return {
        "total_macs": total_macs,
        "weight_bytes_int8": total_weight_bytes_int8,
        "max_activation_int8": max_activation_int8,
        "x86_ms_per_inference": per_ms,
    }


if __name__ == "__main__":
    main()
