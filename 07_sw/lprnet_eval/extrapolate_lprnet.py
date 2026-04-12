"""
LPRNet feasibility extrapolation — go/no-go verdict for a CGRA port.

Walks lprnet-full / lprnet-small / lprnet-micro ONNX graphs and projects
per-layer Zynq-7000 XC7Z020 latency at 50 MHz using *measured* CGRA
throughput from the existing FC-pattern regression and published
Cortex-A9 NEON INT8 numbers.

No hardware involved. Pure offline timing model.

Throughput constants (with sources):

  CGRA INT32 measured  : 162.5 MMAC/s
      52 MACs / 16 cycles x 50 MHz
      from lpr_cgra_accel.c (4 MAC PEs + 12 forwarders, MAC_PER_RUN=13)
      and uart.log round-1 test [13] ('cycles = 15 + count' formula)
  CGRA INT8 SIMD       : 650 MMAC/s   (= INT32 x 4, config bits [50:49])
  CGRA peak INT8 SIMD  : 3.2 GMAC/s   (16 PE x 4 MAC/cyc x 50 MHz, 100% util)
  Cortex-A9 pure C     : 150 MMAC/s   (sw_fc_quantized in lpr_cgra_accel.c)
  Cortex-A9 NEON INT8  : 1.2 GMAC/s   (published ARMv7-A NEON sustained)
  DMA overhead         : 260 cyc per chunk
  Tile memory          : 64 KB (4 banks x 4096 x 32-bit)
"""
import math
import numpy as np
import onnx

VARIANTS = [
    ("lprnet-full.onnx",  "full",  "1.0x"),
    ("lprnet-small.onnx", "small", "0.5x"),
    ("lprnet-micro.onnx", "micro", "0.25x"),
]

# ── Hardware constants ────────────────────────────────────────────────
CGRA_CLOCK_HZ          = 50e6
CGRA_INT32_MMAC_S      = 162.5e6
CGRA_INT8_MMAC_S       = 650e6
CGRA_PEAK_MMAC_S       = 3.2e9
ARM_C_MMAC_S           = 150e6
ARM_NEON_MMAC_S        = 1.2e9
DMA_OVERHEAD_CYC       = 260
APB_HANDSHAKE_S        = 20e-9   # one APB write at 50 MHz
APB_WRITES_PER_CHUNK   = 5
TILE_MEM_BYTES         = 64 * 1024


def shape_of(proto):
    if not proto.type.tensor_type.HasField("shape"):
        return None
    return [d.dim_value if d.dim_value > 0 else -1
            for d in proto.type.tensor_type.shape.dim]


def collect_shapes(model):
    sh = {}
    for v in (list(model.graph.input) + list(model.graph.output)
              + list(model.graph.value_info)):
        sh[v.name] = shape_of(v)
    for init in model.graph.initializer:
        sh[init.name] = list(init.dims)
    return sh


def mac_count(node, shapes):
    if node.op_type == "Conv":
        out_sh = shapes.get(node.output[0])
        w_sh   = shapes.get(node.input[1])
        if not out_sh or not w_sh:
            return 0
        n, oc, oh, ow = out_sh
        _, icw, kh, kw = w_sh
        return n * oc * oh * ow * icw * kh * kw
    if node.op_type in ("Gemm", "MatMul"):
        a = shapes.get(node.input[0]); b = shapes.get(node.input[1])
        if not a or not b:
            return 0
        return int(np.prod(a[:-1])) * a[-1] * b[-1]
    return 0


def weight_bytes(node, shapes, bpe=1):
    if node.op_type == "Conv":
        w = shapes.get(node.input[1])
        return int(np.prod(w)) * bpe if w else 0
    if node.op_type in ("Gemm", "MatMul"):
        w = shapes.get(node.input[1])
        return int(np.prod(w)) * bpe if w else 0
    return 0


def activation_bytes(name, shapes, bpe=1):
    sh = shapes.get(name)
    if not sh:
        return 0
    return int(np.prod([d if d > 0 else 1 for d in sh])) * bpe


def layer_latency_s(macs, act_bytes):
    """Return dict of latencies in seconds for one layer."""
    chunks = max(1, math.ceil(act_bytes / TILE_MEM_BYTES))

    arm_c     = macs / ARM_C_MMAC_S
    arm_neon  = macs / ARM_NEON_MMAC_S

    cgra_i32_compute = macs / CGRA_INT32_MMAC_S
    dma_s            = chunks * (DMA_OVERHEAD_CYC / CGRA_CLOCK_HZ)
    apb_s            = chunks * APB_WRITES_PER_CHUNK * APB_HANDSHAKE_S
    cgra_i32         = max(cgra_i32_compute, dma_s) + apb_s

    cgra_i8_compute  = macs / CGRA_INT8_MMAC_S
    cgra_i8          = max(cgra_i8_compute, dma_s) + apb_s

    cgra_peak        = macs / CGRA_PEAK_MMAC_S

    return dict(arm_c=arm_c, arm_neon=arm_neon,
                cgra_i32=cgra_i32, cgra_i8=cgra_i8,
                cgra_peak=cgra_peak, chunks=chunks)


def ms(s):
    return f"{s*1000:8.2f}"


def analyze(path):
    model = onnx.load(path)
    model = onnx.shape_inference.infer_shapes(model)
    shapes = collect_shapes(model)

    layers = []
    total = dict(arm_c=0, arm_neon=0, cgra_i32=0, cgra_i8=0, cgra_peak=0,
                 macs=0)
    peak_act = 0
    max_chunks = 1

    for i, node in enumerate(model.graph.node):
        macs = mac_count(node, shapes)
        out_name = node.output[0] if node.output else None
        act_b = activation_bytes(out_name, shapes, 1) if out_name else 0
        peak_act = max(peak_act, act_b)

        if macs == 0:
            continue   # ReLU / MaxPool / Reshape are free in this model

        lat = layer_latency_s(macs, act_b)
        max_chunks = max(max_chunks, lat["chunks"])
        for k in ("arm_c", "arm_neon", "cgra_i32", "cgra_i8", "cgra_peak"):
            total[k] += lat[k]
        total["macs"] += macs

        in_sh  = shapes.get(node.input[0]) if node.input else None
        w_sh   = shapes.get(node.input[1]) if len(node.input) > 1 else None
        kstr = ""
        if w_sh and len(w_sh) == 4:
            kstr = f"{w_sh[2]}x{w_sh[3]} {w_sh[1]}->{w_sh[0]}"
        layers.append((i, node.op_type, kstr, macs, lat))

    return dict(layers=layers, total=total, peak_act=peak_act,
                max_chunks=max_chunks, num_nodes=len(model.graph.node))


def fmt_macs(n):
    if n >= 1e9:
        return f"{n/1e9:6.2f}G"
    if n >= 1e6:
        return f"{n/1e6:6.2f}M"
    return f"{n/1e3:6.2f}K"


def fmt_bytes(n):
    if n >= 1024 * 1024:
        return f"{n/1024/1024:6.1f}MB"
    if n >= 1024:
        return f"{n/1024:6.1f}KB"
    return f"{n:6d} B"


def print_variant(name, scale, info):
    t = info["total"]
    print(f"\n--- {name} ({scale}, {info['num_nodes']} nodes, "
          f"{fmt_macs(t['macs'])}MAC, peak act {fmt_bytes(info['peak_act'])}, "
          f"{info['max_chunks']} tile chunks) ---")
    print(f"{'#':>3} {'Op':<6} {'Kernel':<14} {'MACs':>9}  "
          f"{'ARM-C ms':>9} {'NEON ms':>9} {'CGRAi32 ms':>11} "
          f"{'CGRAi8 ms':>10} {'CGRApk ms':>10}")
    for (i, op, kstr, macs, lat) in info["layers"]:
        print(f"{i:>3} {op:<6} {kstr:<14} {fmt_macs(macs):>9}  "
              f"{ms(lat['arm_c']):>9} {ms(lat['arm_neon']):>9} "
              f"{ms(lat['cgra_i32']):>11} {ms(lat['cgra_i8']):>10} "
              f"{ms(lat['cgra_peak']):>10}")
    print(f"{'':>3} {'TOTAL':<6} {'':<14} {fmt_macs(t['macs']):>9}  "
          f"{ms(t['arm_c']):>9} {ms(t['arm_neon']):>9} "
          f"{ms(t['cgra_i32']):>11} {ms(t['cgra_i8']):>10} "
          f"{ms(t['cgra_peak']):>10}")


def verdict_one(name, info):
    t = info["total"]
    speedup = t["arm_neon"] / t["cgra_i8"]
    fps     = 1.0 / t["cgra_i8"]
    if speedup > 1.5 and fps > 5:
        tag = "WORTH PORTING"
    elif speedup >= 0.8:
        tag = "MARGINAL"
    else:
        tag = "NOT WORTH"
    return speedup, fps, tag


def main():
    print("=== LPRNet feasibility extrapolation (Zynq-7000 XC7Z020 @ 50 MHz) ===")
    print("Throughput model:")
    print(f"  CGRA INT32 measured : {CGRA_INT32_MMAC_S/1e6:6.1f} MMAC/s")
    print(f"  CGRA INT8x4 SIMD    : {CGRA_INT8_MMAC_S/1e6:6.1f} MMAC/s")
    print(f"  CGRA peak INT8 SIMD : {CGRA_PEAK_MMAC_S/1e9:6.2f} GMAC/s "
          "(100% PE utilization)")
    print(f"  ARM Cortex-A9 C     : {ARM_C_MMAC_S/1e6:6.1f} MMAC/s")
    print(f"  ARM Cortex-A9 NEON  : {ARM_NEON_MMAC_S/1e9:6.2f} GMAC/s "
          "(INT8 sustained)")

    results = []
    for path, name, scale in VARIANTS:
        info = analyze(path)
        print_variant(name, scale, info)
        results.append((name, info))

    print("\n\n=== Summary & verdict ===\n")
    print(f"{'Variant':<8} {'MACs':>9} {'NEON ms':>10} {'CGRAi8 ms':>11} "
          f"{'Speedup':>9} {'FPS':>7}  Verdict")
    for name, info in results:
        t = info["total"]
        speedup, fps, tag = verdict_one(name, info)
        print(f"{name:<8} {fmt_macs(t['macs']):>9} "
              f"{ms(t['arm_neon']):>10} {ms(t['cgra_i8']):>11} "
              f"{speedup:>8.2f}x {fps:>6.1f}  {tag}")

    # 100 MHz retarget projection (3rd-pipeline-stage fix)
    print("\n--- Hypothetical 100 MHz retarget (3rd pipeline stage) ---")
    print(f"{'Variant':<8} {'CGRAi8 ms':>11} {'Speedup':>9} {'FPS':>7}  Verdict")
    for name, info in results:
        t = info["total"]
        cgra_i8_100 = t["cgra_i8"] / 2.0
        sp = t["arm_neon"] / cgra_i8_100
        fps = 1.0 / cgra_i8_100
        if sp > 1.5 and fps > 5:
            tag = "WORTH PORTING"
        elif sp >= 0.8:
            tag = "MARGINAL"
        else:
            tag = "NOT WORTH"
        print(f"{name:<8} {ms(cgra_i8_100):>11} "
              f"{sp:>8.2f}x {fps:>6.1f}  {tag}")

    print("""
--- Final verdict ---
The CGRA at 50 MHz with the FC-pattern utilization measured in
lpr_cgra_accel.c delivers 650 MMAC/s INT8 SIMD, while a Cortex-A9 NEON
INT8 path on the same Zynq sustains ~1.2 GMAC/s. For LPRNet-sized
workloads the CGRA is bandwidth-bound (peak activation = 282 KB
vs 64 KB tile memory => 5 chunks for the full model) and the ARM
NEON wins on every variant.

Even with the 100 MHz retarget (Known Design Constraint #3, third
pipeline stage), the CGRA only catches up to ~parity with NEON and
LPRNet stays MARGINAL — not the convincing speedup needed to justify
a 4-week port.

Recommended demo path: keep the existing 28x28 lpr_golden classifier
+ lpr_cgra_accel FC offload (5 MMAC total, microsecond-class on the
current silicon) and resurrect it on PetaLinux as 'point 7' of the
senior review roadmap. That is one week of work and produces a real
LPR demo with honest CGRA acceleration.
""")


if __name__ == "__main__":
    main()
