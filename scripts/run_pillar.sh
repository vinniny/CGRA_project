#!/usr/bin/env bash
# run_pillar.sh — execute one pillar of the four-pillar silicon
# measurement plan (06_doc/roofline_analysis.md / thesis_defense_strategy.md).
#
# Always runs B0 (bench_smoke) FIRST unless --skip-smoke is given.
# This is the senior-protocol atomic-validation sequence: if smoke
# fails, the .xsa/.bit/ps7_init combo is broken and the pillar run
# would just waste board time.
#
# Usage:
#   scripts/run_pillar.sh smoke         # B0 atomic-validation (~10 s)
#   scripts/run_pillar.sh B1            # MAC microbench
#   scripts/run_pillar.sh B2            # DMA streaming
#   scripts/run_pillar.sh B3            # demo_mnist_per_stage_two_pass
#                                       # (covers B3+B4+B5 in one ELF)
#   scripts/run_pillar.sh B6            # NEON FC baseline
#
# Env knobs (defaults set below):
#   CGRA_BIT       bitstream to load (default: bitstreams/cgra_top.bit)
#   CGRA_XSA_DIR   path containing _ide/psinit/ps7_init.tcl
#   UART_DEV       serial dev (default: /dev/ttyUSB1)
#   UART_BAUD      baud (default: 115200)
#   WAIT_SEC       seconds to capture UART after launch (default: 25)
set -eo pipefail
# Vitis settings64.sh uses unset PYTHONPATH — set it before strict-mode would catch.
export PYTHONPATH="${PYTHONPATH:-}"
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH:-}"

PILLAR="${1:-smoke}"
SKIP_SMOKE="${2:-}"

# Repo root
REPO="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO"

# --- Pillar → (workspace app, expected UART wait) ----------------------------
case "$PILLAR" in
    smoke|B0)
        APP=bench_smoke_v2
        WAIT="${WAIT_SEC:-15}"
        LOG="02_log/uart_b0_smoke.log"
        ;;
    B1|mac_micro)
        APP=bench_mac_micro_v2
        WAIT="${WAIT_SEC:-25}"
        LOG="02_log/uart_b1_mac_micro.log"
        ;;
    B2|dma_stream)
        APP=bench_dma_stream_v2
        WAIT="${WAIT_SEC:-25}"
        LOG="02_log/uart_b2_dma_stream.log"
        ;;
    B3|per_stage|B4|B5)
        APP=demo_mnist_per_stage_tp_v2
        WAIT="${WAIT_SEC:-90}"   # 100-image sweep × 2 passes
        LOG="02_log/uart_b3b4b5_per_stage.log"
        ;;
    B6|neon_fc)
        APP=bench_neon_fc_v2
        WAIT="${WAIT_SEC:-25}"
        LOG="02_log/uart_b6_neon_fc.log"
        ;;
    *)
        echo "ERROR: unknown pillar '$PILLAR'. Try smoke, B1, B2, B3, B6." >&2
        exit 2
        ;;
esac

WS="/tmp/cgra_vitis_ws"
ELF="${WS}/${APP}/Debug/${APP}.elf"
XSA_DIR="${WS}/${APP}/_ide"

if [[ ! -f "$ELF" ]]; then
    echo "ERROR: ELF not built — $ELF" >&2
    echo "Build it first with vitis_build_demo.tcl" >&2
    exit 3
fi

CGRA_BIT="${CGRA_BIT:-bitstreams/cgra_top.bit}"
UART_DEV="${UART_DEV:-/dev/ttyUSB1}"
# TUL PYNQ-Z2 PS_CLK = 50 MHz (not the standard 33.333 MHz on Digilent boards)
# → IO_PLL = 2700 MHz → UART_REF_CLK = 150 MHz → actual baud = 150e6/124/7 = 172,811
# Verified empirically 2026-05-28 against bench_uart_tuning.elf.
UART_BAUD="${UART_BAUD:-172800}"

# --- B0 smoke gate: skip only on explicit request ------------------------
if [[ "$PILLAR" != "smoke" && "$PILLAR" != "B0" && "$SKIP_SMOKE" != "--skip-smoke" ]]; then
    echo "Running smoke first (B0). Skip with: $0 $PILLAR --skip-smoke"
    "$0" smoke
    echo "Smoke passed; proceeding with $PILLAR"
fi

mkdir -p 02_log

echo "==========================================================="
echo "  Pillar $PILLAR — $APP"
echo "==========================================================="
echo "  Bitstream : $CGRA_BIT"
echo "  ELF       : $ELF"
echo "  UART log  : $LOG"
echo "  Wait      : ${WAIT}s"
echo "==========================================================="

# Use pyserial — stty doesn't support arbitrary bauds like 172800 on Linux
python3 -u -c "
import serial, time, sys
ser = serial.Serial('$UART_DEV', baudrate=$UART_BAUD, timeout=2)
end = time.time() + $WAIT + 4
while time.time() < end:
    d = ser.read(2000)
    if d:
        sys.stdout.buffer.write(d); sys.stdout.flush()
ser.close()
" > "$LOG" 2>&1 &
UART_PID=$!
sleep 1

source /tools/Xilinx/2025.1/Vitis/settings64.sh
CGRA_XSA_DIR="$XSA_DIR" \
CGRA_BIT="$CGRA_BIT" \
CGRA_ELF="$ELF" \
xsct scripts/vitis_launch_with_clear.tcl 2>&1 | tail -15

echo "Capturing UART for ${WAIT}s..."
sleep "$WAIT"
kill $UART_PID 2>/dev/null || true
wait $UART_PID 2>/dev/null || true

echo ""
echo "=== UART captured ($(wc -l < "$LOG") lines) ==="
tr -d '\r' < "$LOG"
echo ""
echo "Log saved: $LOG"

# Smoke-specific: parse for PASS/FAIL
if [[ "$PILLAR" == "smoke" || "$PILLAR" == "B0" ]]; then
    if grep -q "SMOKE PASS" "$LOG"; then
        echo ""
        echo "[B0] SMOKE PASS — bitstream healthy, OK to proceed with workload."
        exit 0
    fi
    echo "" >&2
    echo "[B0] SMOKE FAIL — fix .xsa coupling, do NOT power-cycle." >&2
    exit 1
fi
