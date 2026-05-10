#!/usr/bin/env python3
"""bit2bin.py — convert a Vivado .bit file to a byte-swapped .bin for Zynq.

Strips the Xilinx ASCII header (fields a/b/c/d) and byte-swaps each 32-bit
word in the raw bitstream so the Zynq PCAP / fpga_manager driver finds the
SYNC word 0xAA995566 at the expected offset.

Usage: bit2bin.py input.bit output.bin
"""
import struct
import sys


def main(in_path: str, out_path: str) -> None:
    with open(in_path, 'rb') as f:
        d = f.read()

    i = 0
    # Field 1: 13-byte fixed header (length-prefixed magic).
    if d[:2] != b'\x00\x09':
        sys.exit(f"unexpected file magic at offset 0: {d[:2]!r}")
    i = 13

    # Fields a, b, c, d: 1-byte tag + 16-bit big-endian length + ASCII payload.
    for tag in (b'a', b'b', b'c', b'd'):
        if d[i:i+1] != tag:
            sys.exit(f"expected field '{tag.decode()}' at {i}, got {d[i:i+1]!r}")
        i += 1
        (ln,) = struct.unpack('>H', d[i:i+2])
        i += 2 + ln

    # Field e: 1-byte tag + 32-bit big-endian length + raw bitstream.
    if d[i:i+1] != b'e':
        sys.exit(f"expected field 'e' at {i}, got {d[i:i+1]!r}")
    i += 1
    (raw_len,) = struct.unpack('>I', d[i:i+4])
    i += 4
    raw = d[i:i+raw_len]
    if len(raw) != raw_len:
        sys.exit(f"truncated bitstream: header says {raw_len} bytes, got {len(raw)}")

    # Byte-swap each 32-bit word (MSB-first -> LSB-first per word).
    swapped = bytearray(len(raw))
    for j in range(0, len(raw), 4):
        swapped[j]   = raw[j+3]
        swapped[j+1] = raw[j+2]
        swapped[j+2] = raw[j+1]
        swapped[j+3] = raw[j]

    with open(out_path, 'wb') as f:
        f.write(swapped)

    # Sanity: in a Zynq .bin the SYNC word 0xAA995566 appears byte-reversed
    # as 0x665599AA in the file (matches what the kernel zynq-fpga driver scans
    # for). The .bit file has it as 0xAA995566 in raw bytes; after our per-word
    # byte-swap it becomes 0x665599AA in the .bin.
    sync_offset = swapped.find(b'\x66\x55\x99\xAA')
    print(f"raw bitstream     : {raw_len} bytes", file=sys.stderr)
    print(f"swapped .bin      : {len(swapped)} bytes -> {out_path}", file=sys.stderr)
    print(f"SYNC 0x665599AA at: {'0x%X' % sync_offset if sync_offset >= 0 else 'NOT FOUND'}",
          file=sys.stderr)
    if sync_offset < 0:
        sys.exit("SYNC word missing after swap — file is not a valid Zynq bitstream")


if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} input.bit output.bin")
    main(sys.argv[1], sys.argv[2])
