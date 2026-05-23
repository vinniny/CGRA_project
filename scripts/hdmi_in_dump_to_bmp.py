#!/usr/bin/env python3
"""
hdmi_in_dump_to_bmp.py — Convert a raw HDMI-in frame dump to a BMP.

Usage:
    python3 scripts/hdmi_in_dump_to_bmp.py <input.bin> [-o <output.bmp>]
                                            [-w WIDTH] [-h HEIGHT]
                                            [--rgb-order BGR|RGB|XRGB|BGRX]

The bare-metal HDMI-in VDMA writes 640x480x3 = 921 600 bytes of BGR pixels
starting at DDR 0x1F80_0000. To capture one frame:

    xsdb> mrd -value -size b 0x1F800000 921600 > frame_raw.bin

(or use `mrd -bin -file frame_raw.bin 0x1F800000 921600` on newer XSDB
which writes binary directly).

Then on the host:

    python3 scripts/hdmi_in_dump_to_bmp.py frame_raw.bin -o frame.bmp
    xdg-open frame.bmp

Bring-up checklist item 6 (06_doc/hdmi_in_plan.md): "host program saves one
HDMI-in frame to a BMP for visual sanity check."

No external deps (pure stdlib). Avoids Pillow so it works on the bare WSL2
install with no extra apt installs.
"""

import argparse
import struct
import sys
from pathlib import Path


def bmp_24bit(pixels_bgr_bottom_up: bytes, width: int, height: int) -> bytes:
    """Build a 24-bit uncompressed BMP file body.

    pixels_bgr_bottom_up must already be in BGR order, padded to multiples
    of 4 bytes per row, ordered bottom-to-top (BMP convention).
    """
    row_size = (width * 3 + 3) & ~3
    pixel_data_size = row_size * height
    file_size = 14 + 40 + pixel_data_size
    # File header (14 bytes)
    file_hdr = struct.pack("<2sIHHI", b"BM", file_size, 0, 0, 14 + 40)
    # DIB header BITMAPINFOHEADER (40 bytes)
    dib = struct.pack(
        "<IiiHHIIiiII",
        40,             # header size
        width,
        height,         # positive → bottom-up rows
        1,              # planes
        24,             # bits/pixel
        0,              # BI_RGB
        pixel_data_size,
        2835, 2835,     # X/Y pixels per meter (~72 DPI)
        0, 0,
    )
    return file_hdr + dib + pixels_bgr_bottom_up


def reorder(buf: bytes, w: int, h: int, order: str) -> bytes:
    """Convert raw frame buffer into top-down BGR (one byte per channel)."""
    if order == "BGR":
        bpp = 3
        pick = lambda px: px[0:3]
    elif order == "RGB":
        bpp = 3
        pick = lambda px: bytes((px[2], px[1], px[0]))
    elif order == "XRGB":
        # 32-bit XRGB → take bytes 1..3 (X drops), swap to BGR
        bpp = 4
        pick = lambda px: bytes((px[3], px[2], px[1]))
    elif order == "BGRX":
        # 32-bit BGRX → take bytes 0..2 (X drops)
        bpp = 4
        pick = lambda px: px[0:3]
    else:
        raise ValueError(f"unknown --rgb-order {order!r}")

    expected = w * h * bpp
    if len(buf) < expected:
        raise SystemExit(
            f"Input is {len(buf)} bytes; need at least {expected} for "
            f"{w}x{h} @ {order} ({bpp} bpp). "
            f"Truncated dump or wrong --rgb-order?"
        )
    out = bytearray(w * h * 3)
    for i in range(w * h):
        px = buf[i * bpp:(i + 1) * bpp]
        out[i * 3:(i + 1) * 3] = pick(px)
    return bytes(out)


def to_bmp_bytes(top_down_bgr: bytes, w: int, h: int) -> bytes:
    """Flip top-down BGR to bottom-up + pad rows for the BMP container."""
    row_in = w * 3
    row_out = (w * 3 + 3) & ~3
    out = bytearray(row_out * h)
    for y in range(h):
        src_y = h - 1 - y  # bottom-up
        src = top_down_bgr[src_y * row_in:(src_y + 1) * row_in]
        out[y * row_out:y * row_out + row_in] = src
    return bytes(out)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("input", help="raw frame dump (e.g. from xsdb mrd)")
    ap.add_argument("-o", "--output", default=None, help="output .bmp (default: <input>.bmp)")
    ap.add_argument("-w", "--width", type=int, default=640)
    ap.add_argument("--height", type=int, default=480)
    ap.add_argument("--rgb-order", default="BGR", choices=["BGR", "RGB", "XRGB", "BGRX"],
                    help="byte order of input pixels (default BGR — pixel_pack_in default)")
    args = ap.parse_args()

    src = Path(args.input)
    if not src.is_file():
        print(f"error: input file not found: {src}", file=sys.stderr)
        return 1

    raw = src.read_bytes()
    print(f"input: {src} ({len(raw)} bytes)")

    top_down_bgr = reorder(raw, args.width, args.height, args.rgb_order)
    bottom_up = to_bmp_bytes(top_down_bgr, args.width, args.height)
    bmp = bmp_24bit(bottom_up, args.width, args.height)

    out = Path(args.output) if args.output else src.with_suffix(".bmp")
    out.write_bytes(bmp)
    print(f"wrote: {out} ({len(bmp)} bytes, {args.width}x{args.height})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
