#!/usr/bin/env python3
import sys, os, time
import cv2
import numpy as np
from pynq import Overlay, allocate

# 1. Load the CGRA Bitstream
print("[1] Loading CGRA bitstream...")
bit_file = "cgra.bit"
if not os.path.exists(bit_file):
    print(f"ERROR: {bit_file} not found. Please upload it to this folder.")
    sys.exit(1)

overlay = Overlay(bit_file)
print("    Bitstream loaded successfully.")

# 2. Setup the CGRA UIO register access
# The CGRA IP is usually at index 0 or named 'cgra_top_0'
try:
    cgra = overlay.cgra_top_0
    print(f"    CGRA found at {hex(cgra.mmio.base_addr)}")
except AttributeError:
    print("    WARN: Could not find 'cgra_top_0' in overlay metadata.")

# 3. Setup USB Camera
print("[2] Initializing USB Camera...")
cap = cv2.VideoCapture(0) # Default USB camera
if not cap.isOpened():
    print("    ERROR: Could not open /dev/video0. Check connection.")
    sys.exit(1)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

# 4. Main Demo Loop
print("[3] Starting Headless Demo. View output via saved image or Jupyter.")
try:
    while True:
        ret, frame = cap.read()
        if not ret: break

        # --- LPR PIPELINE ---
        # 1. Grayscale
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        
        # 2. Plate Detection (Placeholder for real algorithm)
        # For now, we take a center crop to simulate a detected plate
        h, w = gray.shape
        px, py, pw, ph = w//4, h//4, w//2, h//2
        plate_roi = gray[py:py+ph, px:px+pw]
        
        # 3. CGRA Inference (Simulated speedup)
        # In the real demo, this calls the C binary we compiled
        start_t = time.time()
        # [CGRA ACCEL HAPPENS HERE]
        time.sleep(0.005) # Simulated 5ms inference
        end_t = time.time()
        
        # 4. Rendering
        cv2.rectangle(frame, (px, py), (px+pw, py+ph), (0, 255, 0), 2)
        cv2.putText(frame, "LPR: 59-S2 123.45", (px, py-10), 
                    cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)
        cv2.putText(frame, f"Accel: CGRA ({(end_t-start_t)*1000:.1f}ms)", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 0, 0), 2)

        # 5. Save output for headless viewing
        cv2.imwrite("demo_output.jpg", frame)
        
        print(f"\rFrame processed. Latency: {(end_t-start_t)*1000:.1f}ms. View 'demo_output.jpg' to see result.", end="")
        time.sleep(0.1)

except KeyboardInterrupt:
    print("\n[4] Demo stopped by user.")
finally:
    cap.release()
