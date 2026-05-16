#!/bin/bash
set -euo pipefail
# =============================================================================
# deploy_path_a.sh — Deploy Vivado-2022.2 merged HDMI+CGRA bitstream to Haoyue
# and verify both subsystems live in a single boot.
#
# Path A of inherited-enchanting-matsumoto.md plan: replace the boot bit with
# the 2022.2-rebuilt merged bit (NO DT overlay, NO UIO — uses /dev/mem and
# stock kernel/DTB unchanged).
#
# Usage:
#   ./scripts/deploy_path_a.sh [path/to/bitstream.bit]
# Default Vivado output:
#   /mnt/c/Users/thanh/Desktop/zynq7020_clean/zynq7020/zynq7020.runs/impl_1/zynq_wrapper.bit
# =============================================================================
set -euo pipefail

BIT="${1:-/mnt/c/Users/thanh/Desktop/zynq7020_clean/zynq7020/zynq7020.runs/impl_1/zynq_wrapper.bit}"
BOARD="${BOARD:-haoyue}"

[ -f "$BIT" ] || { echo "ERROR: bitstream not found: $BIT"; exit 1; }
echo "[*] Bitstream: $BIT ($(du -h "$BIT" | cut -f1))"

echo "[1] Backup current boot bit (one-shot — won't overwrite existing .orig)..."
ssh $BOARD '
  cp -n /boot/bit/zynq7020.bit /boot/bit/zynq7020.bit.orig 2>/dev/null || true
  ls -la /boot/bit/zynq7020.bit*'

echo "[2] Push new bitstream to /boot/bit/zynq7020.bit..."
scp -q "$BIT" $BOARD:/boot/bit/zynq7020.bit
ssh $BOARD 'sync; ls -la /boot/bit/zynq7020.bit'

echo "[3] Verify NO UIO/DT overlay is active (Path A = stock kernel only)..."
ssh $BOARD '
  if grep -q "^dtoverlay=.*cgra" /boot/uEnv.txt 2>/dev/null; then
    echo "  WARNING: cgra dtoverlay still in uEnv.txt — commenting out (it hangs boot)"
    sed -i "/^dtoverlay=.*cgra/s/^/#/" /boot/uEnv.txt
  fi
  echo "  uEnv.txt overlay lines:"
  grep -E "^[^#]*dtoverlay" /boot/uEnv.txt 2>/dev/null || echo "    (none)"'

echo "[4] Reboot..."
ssh $BOARD 'sync; /sbin/reboot' || true
sleep 8
echo "    waiting for ping..."
until ping -c 1 -W 2 ${BOARD_IP:-192.168.0.74} >/dev/null 2>&1; do sleep 2; done
echo "    waiting for SSH..."
until ssh -o ConnectTimeout=2 -o BatchMode=yes $BOARD 'echo up' 2>/dev/null; do sleep 2; done
sleep 3

echo ""
echo "==========================================================="
echo " HDMI + CGRA verification"
echo "==========================================================="
ssh $BOARD '
echo "── /dev/fb0 (HDMI framebuffer) ──"
ls -la /dev/fb0 2>&1 || echo "  MISSING — HDMI dead"

echo ""
echo "── DRM HDMI status ──"
cat /sys/class/drm/card0-HDMI-A-1/status 2>&1 || echo "  no card0-HDMI-A-1"

echo ""
echo "── v_tc_1 ctrl register (expect 0x0007EF06 once HDMI is up) ──"
busybox devmem 0x43C80000 32 2>&1 || echo "  devmem failed"

echo ""
echo "── CGRA APB reachable @ 0x43CD0000 ──"
busybox devmem 0x43CD0000 32 2>&1 || echo "  CGRA APB unreachable"

echo ""
echo "── FCLK_CLK1 (CGRA clock) is already 50MHz from Vivado ──"
if [ -x /home/root/cgra/cgra_smoke ]; then
    /home/root/cgra/cgra_smoke 2>&1 | tail -20
else
    echo "  cgra_smoke binary missing — scp it first"
fi

echo ""
echo "── DRM connector list ──"
for c in /sys/class/drm/card0-*/status; do
    [ -f "$c" ] && echo "  $(dirname "$c" | xargs basename): $(cat "$c")"
done
'

echo ""
echo "==========================================================="
echo " Done. If both /dev/fb0 exists AND cgra_smoke passes 5/5,"
echo " Path A succeeded. Run lpr_eval_cgra -c next for accuracy."
echo "==========================================================="
