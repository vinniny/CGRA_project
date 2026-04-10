#!/usr/bin/env python3
"""
uart_monitor.py — Read UART output from Zynq board over /dev/ttyUSB1

Usage:
    python3 uart_monitor.py [port] [baud]
    python3 uart_monitor.py /dev/ttyUSB1 115200
"""
import serial
import sys
import time

port = sys.argv[1] if len(sys.argv) > 1 else "/dev/ttyUSB1"
baud = int(sys.argv[2]) if len(sys.argv) > 2 else 115200

print(f"[UART] Opening {port} @ {baud} baud...")

try:
    ser = serial.Serial(port, baud, timeout=1,
                        bytesize=serial.EIGHTBITS,
                        parity=serial.PARITY_NONE,
                        stopbits=serial.STOPBITS_ONE)
except serial.SerialException as e:
    print(f"[UART] ERROR: {e}")
    sys.exit(1)

print(f"[UART] Listening... (Ctrl+C to stop, idle timeout 10s)")

last_activity = time.time()
idle_timeout = 60  # seconds to wait after last output before giving up

try:
    while True:
        line = ser.readline()
        if line:
            last_activity = time.time()
            text = line.decode('ascii', errors='replace').rstrip('\r\n')
            print(f"  > {text}")
            sys.stdout.flush()
            # If we see the final result line, give it a moment then exit
            if "failed" in text and "passed" in text:
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
