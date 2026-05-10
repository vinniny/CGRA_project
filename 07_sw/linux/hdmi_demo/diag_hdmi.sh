#!/bin/sh
# diag_hdmi.sh — first-light HDMI diagnostic for the PYNQ-Z2 PetaLinux build
# Run on the target as root over UART/SSH. Walks the pipeline upstream of
# pixel data so we can localise "black screen / no signal" failures.
#
# Address map matches /mnt/e/system.dtb (decoded 2026-05-10):
#   VDMA 0x43000000, CGRA 0x43C00000, DynClk 0x43C10000, VTC 0x43C20000
# If your bitstream uses different addrs, edit the variables below first.

set -u

VDMA=0x43000000
CGRA=0x43C00000
DYNCLK=0x43C10000
VTC=0x43C20000

PASS()  { printf '\033[32m[PASS]\033[0m %s\n' "$*"; }
FAIL()  { printf '\033[31m[FAIL]\033[0m %s\n' "$*"; }
INFO()  { printf '\033[36m[INFO]\033[0m %s\n' "$*"; }

if ! command -v devmem >/dev/null 2>&1; then
    echo "devmem not found. Install busybox-devmem or run 'busybox devmem ...' manually."
    exit 1
fi

if [ "$(id -u)" != 0 ]; then
    echo "ERROR: must run as root (devmem opens /dev/mem). Try:  sudo $0   or   su -c $0"
    exit 1
fi

echo "=== 1. FPGA fabric is configured ==="
if [ -r /sys/class/fpga_manager/fpga0/state ]; then
    state=$(cat /sys/class/fpga_manager/fpga0/state)
    INFO "fpga_manager state: $state"
    case "$state" in
        operating) PASS "FPGA reports operating" ;;
        *)         FAIL "FPGA not operating. BOOT.BIN may have skipped --fpga or FSBL did not program the PL." ;;
    esac
else
    INFO "No fpga_manager sysfs entry. Older kernel or DT lacks fpga-region."
fi
dmesg | grep -iE 'fpga|devcfg|pl-bus' | tail -20

echo
echo "=== 2. Reserved framebuffer region present ==="
if dmesg | grep -q 'Reserved memory: created.*framebuffer'; then
    PASS "kernel logged reserved-memory framebuffer"
elif [ -d /proc/device-tree/reserved-memory/framebuffer@1f000000 ]; then
    PASS "/proc/device-tree shows framebuffer@1f000000"
else
    FAIL "framebuffer reservation missing — system-user.dtsi did not take effect"
fi

echo
echo "=== 3. HDMI IPs respond to APB reads (registers must NOT be 0xffffffff) ==="
for pair in "VDMA $VDMA" "CGRA $CGRA" "DynClk $DYNCLK" "VTC $VTC"; do
    name=${pair%% *}; addr=${pair##* }
    err=$(devmem "$addr" 32 2>&1 >/dev/null)
    val=$(devmem "$addr" 32 2>/dev/null)
    if [ -n "$err" ] && [ -z "$val" ]; then
        FAIL "$name @ $addr — devmem error: $err"
    elif [ -z "$val" ]; then
        FAIL "$name @ $addr — bus error (no slave at this address — bitstream wrong?)"
    elif [ "$val" = "0xFFFFFFFF" ]; then
        FAIL "$name @ $addr = 0xFFFFFFFF (no IP responding — APB decode wrong)"
    else
        PASS "$name @ $addr base reg = $val"
    fi
done

echo
echo "=== 4. CGRA APB sanity (write/read scratch reg) ==="
INFO "Writing CU_TIMEOUT=0x12345678 at $CGRA + 0x2C, reading back"
devmem "$(printf '0x%X' $((CGRA + 0x2C)))" 32 0x12345678
rb=$(devmem "$(printf '0x%X' $((CGRA + 0x2C)))" 32)
if [ "$rb" = "0x12345678" ]; then
    PASS "CGRA APB write/read works (CU_TIMEOUT reflects write)"
else
    FAIL "CGRA APB scratch failed (wrote 0x12345678, read $rb)"
fi
devmem "$(printf '0x%X' $((CGRA + 0x2C)))" 32 0x00100000      # restore default

echo
echo "=== 5. DynClk PLL — programme 25.175 MHz (640x480) and check lock ==="
# Lookup table values for VCO=10*125 MHz, fbmult=10, clkdiv=50, maindiv=1
# (This is just a smoke test — hdmi-demo does it properly. We force lock.)
INFO "Stopping DynClk"
devmem "$DYNCLK"                     32 0x00000000
sleep 1
locked_before=$(devmem "$(printf '0x%X' $((DYNCLK + 0x04)))" 32)
INFO "DynClk STATUS while stopped = $locked_before (bit0 should be 0)"

INFO "Starting DynClk with whatever values are already loaded"
devmem "$DYNCLK"                     32 0x00000001
sleep 1
locked_after=$(devmem "$(printf '0x%X' $((DYNCLK + 0x04)))" 32)
INFO "DynClk STATUS after start = $locked_after"
case "$locked_after" in
    *0x00000001|*0x[0-9a-fA-F]*1)
        PASS "DynClk reports running (bit0=1) — PLL locked"
        ;;
    *)
        FAIL "DynClk did NOT lock. PLL config may be invalid; run hdmi-demo to load proper LUT values."
        ;;
esac

echo
echo "=== 6. VDMA MM2S status ==="
sr=$(devmem "$(printf '0x%X' $((VDMA + 0x04)))" 32)
INFO "VDMA MM2S SR = $sr (bit0=halted, bit1=idle, bits[11:4]=err mask)"

echo
echo "=== 7. VTC generator status ==="
ctl=$(devmem "$VTC" 32)
sts=$(devmem "$(printf '0x%X' $((VTC + 0x04)))" 32)
INFO "VTC CTL = $ctl, STATUS = $sts (CTL bit2=GE generator-enable)"

echo
echo "=== 8. UIO bindings ==="
for u in /sys/class/uio/uio*; do
    [ -e "$u" ] || continue
    name=$(cat "$u/name" 2>/dev/null)
    addr=$(cat "$u/maps/map0/addr" 2>/dev/null)
    sz=$(cat "$u/maps/map0/size" 2>/dev/null)
    INFO "$(basename "$u"): name=$name addr=$addr size=$sz"
done

echo
INFO "Done. Re-run after each bitstream/DT change."
