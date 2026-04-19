#!/usr/bin/env python3
"""
uart_monitor.py — Read UART output from Zynq board over CH340 UART

Usage:
    python3 uart_monitor.py [port] [baud] [idle_timeout_s]
    python3 uart_monitor.py /dev/ttyUSB0 115200 120
"""
import serial
import sys
import time

port = sys.argv[1] if len(sys.argv) > 1 else "/dev/ttyUSB0"
baud = int(sys.argv[2]) if len(sys.argv) > 2 else 115200
idle_timeout = int(sys.argv[3]) if len(sys.argv) > 3 else 60

print(f"[UART] Opening {port} @ {baud} baud...")

try:
    ser = serial.Serial(port, baud, timeout=1,
                        bytesize=serial.EIGHTBITS,
                        parity=serial.PARITY_NONE,
                        stopbits=serial.STOPBITS_ONE)
except serial.SerialException as e:
    print(f"[UART] ERROR: {e}")
    sys.exit(1)
last_activity = time.time()

print(f"[UART] Listening... (Ctrl+C to stop, idle timeout {idle_timeout}s)")

try:
    while True:
        line = ser.readline()
        if line:
            last_activity = time.time()
            text = line.decode('ascii', errors='replace').rstrip('\r\n')
            print(f"  > {text}")
            sys.stdout.flush()
            # Exit on final result lines (regression test or benchmark summary)
            if ("failed" in text and "passed" in text) or \
               "[BENCH COMPLETE]" in text:
                time.sleep(0.5)
                break
        else:
            if time.time() - last_activity > idle_timeout:
                print("[UART] Idle timeout.")
                break
except KeyboardInterrupt:
    print("\n[UART] Interrupted.")
finally:
    ser.close()

print("[UART] Done.")
