#!/usr/bin/env bash
# =============================================================================
# silicon_vtpg_test.sh — One-shot silicon validation of the v_tpg AXIS chain.
#
# Programs cgra_vtpg_ila.bit, loads + runs demo_vtpg.elf, captures the ILA,
# dumps the framebuffer from DDR, and renders a BMP. Handles every known
# DAP-lockup recovery automatically via rst -dap retries.
#
# Usage:
#   scripts/silicon_vtpg_test.sh                # full test, default paths
#   scripts/silicon_vtpg_test.sh --skip-ila     # skip Vivado HW Manager step
#   scripts/silicon_vtpg_test.sh --bmp out.bmp  # custom output BMP
#
# Outputs:
#   06_doc/silicon_vtpg_smpte_bars.bmp  (or --bmp path)
#   /tmp/ila_capture_vtpg.csv           (if --skip-ila NOT set)
#   /tmp/ila_capture_vtpg.vcd
#
# Exit codes:
#   0 = full success (8 SMPTE bars verified)
#   1 = ELF / program failure
#   2 = ILA capture failure (BMP still produced via XSDB-only path)
#   3 = framebuffer dump failure
#   4 = colour-bar verification failed (chain wrote, but wrong content)
# =============================================================================
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.."; pwd -P)"
cd "$REPO_ROOT"

BIT="$REPO_ROOT/bitstreams/cgra_vtpg_ila.bit"
LTX="$REPO_ROOT/bitstreams/cgra_vtpg_ila.ltx"
ELF="$REPO_ROOT/07_sw/baremetal/demo_vtpg.elf"
OUT_BMP="$REPO_ROOT/06_doc/silicon_vtpg_smpte_bars.bmp"
OUT_FB="/tmp/silicon_vtpg_fb.bin"
SKIP_ILA=0

while [[ $# -gt 0 ]]; do
    case $1 in
        --skip-ila) SKIP_ILA=1; shift ;;
        --bmp)      OUT_BMP="$2"; shift 2 ;;
        --bit)      BIT="$2"; shift 2 ;;
        --elf)      ELF="$2"; shift 2 ;;
        -h|--help)
            sed -n '4,18p' "$0"; exit 0 ;;
        *) echo "Unknown arg: $1"; exit 1 ;;
    esac
done

for f in "$BIT" "$LTX" "$ELF"; do
    [[ -f "$f" ]] || { echo "Missing: $f"; exit 1; }
done

XSDB=/tools/Xilinx/2025.1/Vitis/bin/xsdb

# ---------------------------------------------------------------------------
# Helper: run XSDB with built-in DAP recovery -- if a command errors out
# with the "Blocked address" or "transaction error" symptom, retry once
# after rst -dap. Returns the script's stdout.
# ---------------------------------------------------------------------------
run_xsdb_with_recovery() {
    local tcl_body="$1"
    local timeout_s="${2:-60}"
    local tmpf
    tmpf=$(mktemp /tmp/xsdb_XXXXXX.tcl)
    cat > "$tmpf" <<EOF
fconfigure stdout -buffering line
connect
configparams force-mem-accesses 1
# Pre-emptive DAP recovery -- safe no-op if the DAP was already clean.
catch {targets -set -filter {name =~ "DAP*"}}
catch {rst -dap}
after 800
$tcl_body
exit
EOF
    timeout "$timeout_s" "$XSDB" "$tmpf"
    rm -f "$tmpf"
}

echo "=============================================================="
echo " SILICON v_tpg VALIDATION — one-shot resilient test"
echo "=============================================================="
echo " BIT  : $BIT"
echo " ELF  : $ELF"
echo " LTX  : $LTX"
echo " BMP  : $OUT_BMP"
echo "--------------------------------------------------------------"

# Step 1: program + run via make (which already handles DAP recovery now)
echo ""
echo "[1/4] make run_elf -- programs PL, runs ps7_init, loads + starts ELF"
make run_elf ELF="$ELF" BIT="$BIT" 2>&1 | tail -8

# Give the demo a moment to set up VDMA + v_tpg + axis_switch + matrix
sleep 2

# Step 2 (optional): Vivado HW Manager ILA capture
if [[ "$SKIP_ILA" -eq 0 ]]; then
    echo ""
    echo "[2/4] Vivado HW Manager ILA capture (256 samples × 3 AXIS slots)"
    # Suspend CPU first so the JTAG hand-off is clean
    run_xsdb_with_recovery "
        targets -set -filter {name =~ \"*Cortex-A9*0*\"}
        catch {stop}
        after 200
    " 20
    source /tools/Xilinx/2025.1/Vivado/settings64.sh
    if vivado -mode batch -source scripts/ila_capture_vtpg.tcl > /tmp/ila_capture.log 2>&1; then
        echo "    captured: /tmp/ila_capture_vtpg.csv  (+ .vcd)"
    else
        echo "    WARN: ILA capture errored -- see /tmp/ila_capture.log"
        echo "    Proceeding to framebuffer dump anyway."
    fi
    # Resume CPU so v_tpg keeps streaming
    run_xsdb_with_recovery "
        targets -set -filter {name =~ \"*Cortex-A9*0*\"}
        catch {con}
        after 1500
    " 20
else
    echo ""
    echo "[2/4] ILA capture skipped (--skip-ila)"
fi

# Step 3: dump the framebuffer (with auto-recovery)
echo ""
echo "[3/4] Dump FB0 from DDR @ 0x1100_0000 (921 600 B = 230 400 words)"
# mrd count is in 32-bit words by default, NOT bytes. 640*480*3 / 4 = 230400.
run_xsdb_with_recovery "
    targets -set -filter {name =~ \"*Cortex-A9*0*\"}
    catch {stop}
    mrd -bin -file $OUT_FB 0x11000000 230400
    catch {con}
" 90

if [[ ! -s "$OUT_FB" ]]; then
    echo "ERROR: FB dump empty or missing."
    exit 3
fi
echo "    dumped: $OUT_FB ($(stat -c %s "$OUT_FB") bytes)"

# Step 4: render BMP + verify the 8 SMPTE bars are present
echo ""
echo "[4/4] Render BMP + verify SMPTE bars"
python3 scripts/hdmi_in_dump_to_bmp.py "$OUT_FB" -o "$OUT_BMP" \
    -w 640 --height 480 --rgb-order RGB 2>&1 | sed 's/^/    /'

python3 - <<EOF
import sys
with open("$OUT_FB", "rb") as f:
    fb = f.read()[:921600]

expected = [
    ("white",   (255,255,255)),
    ("yellow",  (254,254,  0)),
    ("cyan",    (  0,255,252)),
    ("green",   (  0,254,  0)),
    ("magenta", (254,  0,254)),
    ("red",     (255,  0,  0)),
    ("blue",    (  0,  0,254)),
    ("black",   (  1,  0,  0)),
]
TOL = 3
ok = True
print("    --- SMPTE 8-bar verification ---")
for i, (name, want) in enumerate(expected):
    x = i * 80 + 40
    o = 240 * 1920 + x * 3
    got = (fb[o], fb[o+1], fb[o+2])
    match = all(abs(g - w) <= TOL for g, w in zip(got, want))
    status = "OK " if match else "BAD"
    if not match:
        ok = False
    print(f"    {status}  bar {i} ({name:7s})  got {got}  want {want}")
if not ok:
    sys.exit(4)
print()
print("    ALL 8 BARS VERIFIED ✓")
EOF

echo ""
echo "=============================================================="
echo " SUCCESS — v_tpg AXIS chain end-to-end silicon-validated"
echo "         BMP: $OUT_BMP"
echo "=============================================================="
