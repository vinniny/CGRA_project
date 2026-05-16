#!/bin/bash
set -euo pipefail
# =============================================================================
# deploy_cgra_bitstream.sh — Push the new CGRA+HDMI bitstream + CGRA DT overlay
# to the Haoyue board, then reboot and run the smoke test.
#
# Usage:
#   ./scripts/deploy_cgra_bitstream.sh [path/to/bitstream.bit]
# Default: /mnt/c/Users/thanh/Desktop/FPGA_CGRA/cgra_ip.runs/impl_1/design_1_wrapper.bit
# =============================================================================
set -euo pipefail

BIT="${1:-/mnt/c/Users/thanh/Desktop/zynq7020_2022/zynq7020/zynq7020.runs/impl_1/zynq_wrapper.bit}"
[ -f "$BIT" ] || { echo "ERROR: bitstream not found: $BIT"; exit 1; }

BOARD="haoyue"

echo "[1] Backup current SD bitstream + uEnv.txt..."
ssh $BOARD "cp -n /boot/bit/zynq7020.bit /boot/bit/zynq7020.bit.orig 2>/dev/null; \
            cp -n /boot/uEnv.txt /boot/uEnv.txt.orig 2>/dev/null; \
            ls -la /boot/bit/zynq7020.bit*"

echo "[2] Pushing new bitstream ($(du -h \"$BIT\" | cut -f1))..."
scp -q "$BIT" $BOARD:/boot/bit/zynq7020.bit
ssh $BOARD "ls -la /boot/bit/zynq7020.bit; sync"

echo "[3] Compile + install CGRA DT overlay..."
ssh $BOARD '
cd /home/root/cgra/dts
dtc -@ -I dts -O dtb -o zynq-ebf-cgra-overlay.dtbo zynq-ebf-cgra-overlay.dts 2>&1 | tail -3
cp zynq-ebf-cgra-overlay.dtbo /boot/dtb/overlay/
ls -la /boot/dtb/overlay/zynq-ebf-cgra-overlay.dtbo
'

echo "[4] Add overlay to uEnv.txt (idempotent)..."
ssh $BOARD '
grep -q "zynq-ebf-cgra-overlay" /boot/uEnv.txt || \
    echo "dtoverlay=/dtb/overlay/zynq-ebf-cgra-overlay.dtbo" >> /boot/uEnv.txt
grep -E "dtoverlay" /boot/uEnv.txt | tail -3
'

echo "[5] Reboot board..."
ssh $BOARD "sync; /sbin/reboot" || true
sleep 5
echo "    waiting for board to come back..."
until ping -c 1 -W 2 192.168.0.74 >/dev/null 2>&1; do sleep 2; done
echo "    pinged. Waiting for SSH..."
until ssh -o ConnectTimeout=2 -o BatchMode=yes $BOARD "echo up" 2>/dev/null; do sleep 2; done

echo "[6] Verify CGRA UIO + run smoke test..."
ssh $BOARD '
echo "=== /dev/uio* ==="
ls /dev/uio* 2>&1
echo "=== /sys/class/uio/uio0/ ==="
ls /sys/class/uio/uio0/ 2>&1 | head
cat /sys/class/uio/uio0/name /sys/class/uio/uio0/maps/map0/addr /sys/class/uio/uio0/maps/map0/size 2>&1
echo "=== running cgra_smoke ==="
/home/root/cgra/cgra_smoke 2>&1 | head -60
'
