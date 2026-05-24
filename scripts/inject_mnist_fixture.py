#!/usr/bin/env python3
"""
inject_mnist_fixture.py — render one MNIST sweep_input28[] image as a 640×480
BGR raw frame ready for XSDB to load into the HDMI-in framebuffer at
0x11000000.

This is Phase C of the no-HDMI bring-up: prove the bare-metal capture+
inference chain on a known input WITHOUT a real HDMI source. Steps:

  1. Parse `07_sw/baremetal/mnist_sweep_fixture.h` for sweep_input28[N][784]
     and sweep_labels[N].
  2. Pick one image (default: index 0). Upscale 28×28 → 280×280 (10× nearest).
  3. Invert (MNIST white-on-black → Paint black-on-white) because
     `frame_to_mnist.c` re-inverts on the way back.
  4. Embed the 280×280 block at (x=180, y=100) inside a 640×480 white
     background. Matches HDMI_ROI_DEFAULT in frame_to_mnist.h.
  5. Write 640×480×3 BGR bytes (1920×480 = 921,600 B) to <out>.

Usage:
    python3 scripts/inject_mnist_fixture.py [--index N] [--output PATH]
"""

import argparse
import re
import struct
from pathlib import Path

FIXTURE = Path(__file__).resolve().parent.parent / "07_sw/baremetal/mnist_sweep_fixture.h"
ROI_X, ROI_Y, ROI_W, ROI_H = 180, 100, 280, 280
FB_W, FB_H = 640, 480


def parse_fixture(path: Path):
    """Read sweep_input28[N][784] + sweep_labels[N] from the C header."""
    text = path.read_text()

    m = re.search(r"sweep_input28\[(\d+)\]\[784\]\s*=\s*\{(.*?)\};",
                  text, re.DOTALL)
    if not m:
        raise SystemExit("sweep_input28 not found in fixture")
    n_images = int(m.group(1))
    body = m.group(2)
    # Body is N nested {a,b,c,...} blocks
    blocks = re.findall(r"\{([^{}]*)\}", body)
    images = []
    for blk in blocks:
        vals = [int(v.strip()) for v in blk.split(",") if v.strip()]
        if len(vals) == 784:
            images.append(vals)
    assert len(images) == n_images, f"got {len(images)} expected {n_images}"

    m = re.search(r"sweep_labels\[\d+\]\s*=\s*\{([^}]+)\}", text)
    labels = [int(v.strip()) for v in m.group(1).split(",") if v.strip()]
    return images, labels


def render(image28: list, fb_w: int, fb_h: int,
           roi_x: int, roi_y: int, roi_w: int, roi_h: int) -> bytes:
    """Build a 640×480 BGR byte buffer with the upscaled digit in the ROI."""
    # 1. Upscale 28×28 → 280×280 nearest-neighbour.
    scale = roi_w // 28
    upscaled = bytearray(roi_w * roi_h)
    for ry in range(roi_h):
        sy = ry // scale
        for rx in range(roi_w):
            sx = rx // scale
            upscaled[ry * roi_w + rx] = image28[sy * 28 + sx]

    # 2. Build 640×480 BGR frame: white background, digit ROI inverted.
    #    MNIST: 255 = digit, 0 = background.
    #    Paint convention (what HDMI source sends): black digit on white.
    #    So we INVERT the 28×28 inside the ROI: Y = 255 - upscaled.
    #    Outside the ROI: white (255).
    fb = bytearray(fb_w * fb_h * 3)
    # Fill all-white first
    for i in range(0, len(fb), 3):
        fb[i + 0] = 255  # B
        fb[i + 1] = 255  # G
        fb[i + 2] = 255  # R
    # Stamp the inverted upscaled digit
    for ry in range(roi_h):
        for rx in range(roi_w):
            y = 255 - upscaled[ry * roi_w + rx]
            fx = roi_x + rx
            fy = roi_y + ry
            idx = (fy * fb_w + fx) * 3
            fb[idx + 0] = y
            fb[idx + 1] = y
            fb[idx + 2] = y
    return bytes(fb)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--index", type=int, default=0,
                    help="sweep_input28 index (default: 0)")
    ap.add_argument("--output", default="/tmp/mnist_fb0.bin",
                    help="output raw BGR file (default: /tmp/mnist_fb0.bin)")
    ap.add_argument("--bmp", help="optional BMP rendering for visual verification")
    args = ap.parse_args()

    images, labels = parse_fixture(FIXTURE)
    if args.index >= len(images):
        raise SystemExit(f"index {args.index} >= N_IMAGES={len(images)}")

    img = images[args.index]
    lbl = labels[args.index]
    print(f"Rendering sweep image {args.index} (label = {lbl}) → 640×480 BGR raw")

    raw = render(img, FB_W, FB_H, ROI_X, ROI_Y, ROI_W, ROI_H)
    Path(args.output).write_bytes(raw)
    print(f"Wrote {len(raw)} bytes to {args.output}")
    print(f"  XSDB load command:")
    print(f"    mwr -bin -file {args.output} -size b 0x11000000 {len(raw)}")
    print(f"  Then run demo_mnist_hdmi_bm.elf (LIVE_INPUT=1) and watch UART")
    print(f"  Expected prediction: {lbl}")

    if args.bmp:
        # Reuse hdmi_in_dump_to_bmp's helpers indirectly via a quick inline BMP writer
        from hdmi_in_dump_to_bmp import bmp_24bit, to_bmp_bytes  # type: ignore
        bottom_up = to_bmp_bytes(raw, FB_W, FB_H)
        Path(args.bmp).write_bytes(bmp_24bit(bottom_up, FB_W, FB_H))
        print(f"Wrote BMP {args.bmp} for visual sanity check")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
