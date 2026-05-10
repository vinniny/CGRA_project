#!/bin/sh
# =============================================================================
# hdmi_boot_snapshot.sh — Capture HDMI / DRM / clock / v_tc state for diff.
#
# Run on the board once per boot (one with stock bit, one with merged bit):
#   ./hdmi_boot_snapshot.sh > /tmp/hdmi_stock.txt    # after stock-bit boot
#   ./hdmi_boot_snapshot.sh > /tmp/hdmi_merged.txt   # after merged-bit boot
#
# Then diff side-by-side from the host:
#   scp haoyue:/tmp/hdmi_*.txt . && diff -u hdmi_stock.txt hdmi_merged.txt
# =============================================================================

echo "=== uname / boot bit ==="
uname -a
md5sum /boot/bit/zynq7020.bit /boot/bit/zynq7020.bit.orig /boot/bit/zynq7020.bit.merged 2>/dev/null

echo
echo "=== dmesg: drm / hdmi / i2c / v_tc / frmbuf / dynclk ==="
dmesg | grep -iE "drm|hdmi|i2c|v_tc|frmbuf|dynclk|xlnx" | head -40

echo
echo "=== /dev/fb* ==="
ls -la /dev/fb* 2>&1

echo
echo "=== /sys/class/drm/card0/* ==="
for f in /sys/class/drm/card0-HDMI*/status \
         /sys/class/drm/card0-HDMI*/modes  \
         /sys/class/drm/card0-HDMI*/enabled \
         /sys/class/drm/card0-HDMI*/dpms; do
    [ -f "$f" ] && echo "--- $f"; cat "$f" 2>&1
done
echo "--- card0-HDMI-A-1/edid (hex, first 256 bytes) ---"
hexdump -C /sys/class/drm/card0-HDMI*/edid 2>/dev/null | head -16

echo
echo "=== /sys/class/graphics/fb0/* ==="
for f in /sys/class/graphics/fb0/virtual_size \
         /sys/class/graphics/fb0/bits_per_pixel \
         /sys/class/graphics/fb0/blank \
         /sys/class/graphics/fb0/state; do
    [ -f "$f" ] && echo "$f = $(cat $f 2>&1)"
done

echo
echo "=== v_tc_1 @ 0x43C80000 (HDMI video timing controller) ==="
# devmem from busybox is one-shot; read the version + a few status regs
# 0x000 ctrl, 0x004 status, 0x010 version, 0x060 generator timing
busybox devmem 0x43C80010 32 2>/dev/null && echo "  version (0x010)"
busybox devmem 0x43C80000 32 2>/dev/null && echo "  ctrl    (0x000)"
busybox devmem 0x43C80004 32 2>/dev/null && echo "  status  (0x004)"

echo
echo "=== axi_dynclk @ 0x43C20000 (HDMI pixel clock generator) ==="
busybox devmem 0x43C20000 32 2>/dev/null && echo "  ctrl/status"

echo
echo "=== v_frmbuf_rd_0 @ 0x43C70000 (HDMI frame buffer reader) ==="
busybox devmem 0x43C70000 32 2>/dev/null && echo "  ctrl"

echo
echo "=== axi_iic_0 (HDMI EDID I2C) ==="
# Wildfire's IIC for HDMI EDID lives somewhere — find via /proc/iomem
grep -i iic /proc/iomem 2>/dev/null

echo
echo "=== /proc/interrupts (HDMI hot-plug detect) ==="
grep -iE "hdmi|drm" /proc/interrupts 2>&1 | head -5

echo
echo "=== SLCR clock dividers (FCLK_CLKx_CTRL) ==="
echo "FPGA0_CLK_CTRL @ 0xF8000170:"; busybox devmem 0xF8000170 32
echo "FPGA1_CLK_CTRL @ 0xF8000180:"; busybox devmem 0xF8000180 32
echo "FPGA2_CLK_CTRL @ 0xF8000190:"; busybox devmem 0xF8000190 32
echo "FPGA3_CLK_CTRL @ 0xF80001A0:"; busybox devmem 0xF80001A0 32

echo
echo "=== /proc/iomem (PL address regions) ==="
grep -E "amba_pl|43c|43d" /proc/iomem 2>&1 | head -20
