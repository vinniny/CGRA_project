#!/bin/sh
# hdmi_paint.sh — second-stage HDMI bring-up for the PYNQ-base+CGRA bitstream.
#
# Run AFTER hdmi_first_light.sh has succeeded (dynclk locked, VTC+VDMA
# running). hdmi_first_light leaves the monitor receiving valid 640x480@60
# sync but the screen is solid black, because the two PYNQ HLS IPs in the
# AXIS path between VDMA and rgb2dvi default to a non-functional state:
#
#   * color_convert @ 0x43C60000 — default coefficient matrix is ALL ZEROS,
#     so every pixel becomes (bias, bias, bias) = black.
#   * pixel_unpack  @ 0x43C70000 — default mode = 0 (V_24, 24-bit packed
#     RGB, 3 bytes/pixel in DDR) which already matches our 1920-byte stride.
#
# This script writes:
#   1. color_convert: identity matrix in ap_fixed<10,2> format (1.0 = 0x100).
#   2. pixel_unpack:  mode = 0 explicitly (no-op if first run, idempotent).
#
# After this, the FB at 0x1F000000 drives the screen. To paint a custom test
# pattern requires a userspace mmap() — kernel STRICT_DEVMEM blocks dd/cp
# writes to /dev/mem so a glibc-linked ARM binary is the only option.

set -u

CCV=0x43C60000   # video/hdmi_out/color_convert
PUP=0x43C70000   # video/hdmi_out/pixel_unpack
FB=0x1F000000

w() { devmem "$1" 32 "$2" ; }
r() { devmem "$1" 32 ; }

echo "=========================================================="
echo " hdmi_paint: configure HLS IPs in HDMI OUT AXIS path"
echo "=========================================================="

# --------- 1. color_convert identity -----------------------------
echo "[1/2] color_convert @ $CCV: identity matrix (1.0 = 0x100)"
w $(printf '0x%X' $((CCV + 0x10))) 0x100   # c1_c1
w $(printf '0x%X' $((CCV + 0x18))) 0x000   # c1_c2
w $(printf '0x%X' $((CCV + 0x20))) 0x000   # c1_c3
w $(printf '0x%X' $((CCV + 0x28))) 0x000   # c2_c1
w $(printf '0x%X' $((CCV + 0x30))) 0x100   # c2_c2
w $(printf '0x%X' $((CCV + 0x38))) 0x000   # c2_c3
w $(printf '0x%X' $((CCV + 0x40))) 0x000   # c3_c1
w $(printf '0x%X' $((CCV + 0x48))) 0x000   # c3_c2
w $(printf '0x%X' $((CCV + 0x50))) 0x100   # c3_c3
w $(printf '0x%X' $((CCV + 0x58))) 0x000   # bias_c1
w $(printf '0x%X' $((CCV + 0x60))) 0x000   # bias_c2
w $(printf '0x%X' $((CCV + 0x68))) 0x000   # bias_c3
echo "   c1_c1=$(r $(printf '0x%X' $((CCV + 0x10))))  (expect 0x100)"
echo "   c2_c2=$(r $(printf '0x%X' $((CCV + 0x30))))  (expect 0x100)"
echo "   c3_c3=$(r $(printf '0x%X' $((CCV + 0x50))))  (expect 0x100)"

# --------- 2. pixel_unpack mode --------------------------------
echo "[2/2] pixel_unpack @ $PUP: mode = 0 (V_24, 3 bytes/pixel BGR-in-memory)"
w $(printf '0x%X' $((PUP + 0x10))) 0x0
echo "   mode=$(r $(printf '0x%X' $((PUP + 0x10))))  (expect 0x0)"

echo
echo "=== final state ==="
echo "  VDMA MM2S CR : $(r 0x43000000)"
echo "  VDMA MM2S SR : $(r 0x43000004)"
echo "  dynclk STATUS: $(r 0x43C10004)"
echo "  VTC STATUS   : $(r 0x43C20004)"
echo
echo "Monitor should now show whatever bytes are in DDR at 0x1F000000."
echo "(Likely a residual test pattern from kernel/boot.) To paint a"
echo "specific image, build a glibc-linked ARM binary that mmap()s /dev/mem"
echo "— STRICT_DEVMEM blocks dd/cp to /dev/mem so no shell-only painter"
echo "will work."
