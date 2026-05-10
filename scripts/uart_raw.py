#!/usr/bin/env python3
"""uart_raw.py — read raw bytes from UART (no line-buffering).

Use when the board sits at a u-boot prompt (no LF after `zynq-uboot>`),
or to send a few keystrokes to interrupt autoboot.

Usage:
    python3 uart_raw.py [port] [baud] [seconds] [send_chars]
    python3 uart_raw.py /dev/ttyUSB2 115200 30
    python3 uart_raw.py /dev/ttyUSB2 115200 30 "\\n\\n"   # send 2 newlines
"""
import serial, sys, time

port = sys.argv[1] if len(sys.argv) > 1 else "/dev/ttyUSB2"
baud = int(sys.argv[2]) if len(sys.argv) > 2 else 115200
secs = int(sys.argv[3]) if len(sys.argv) > 3 else 30
send = sys.argv[4].encode().decode("unicode_escape").encode() if len(sys.argv) > 4 else b""

print(f"[UART] {port} @ {baud}, capturing {secs}s, send={send!r}", flush=True)
ser = serial.Serial(port, baud, timeout=0.2,
                    bytesize=serial.EIGHTBITS,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE)
if send:
    ser.write(send)
    ser.flush()
end = time.time() + secs
buf = b""
while time.time() < end:
    chunk = ser.read(256)
    if chunk:
        buf += chunk
        sys.stdout.write(chunk.decode("ascii", errors="replace"))
        sys.stdout.flush()
print(f"\n[UART] captured {len(buf)} bytes total", flush=True)
ser.close()
