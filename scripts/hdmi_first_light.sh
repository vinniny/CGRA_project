#!/bin/sh
# hdmi_first_light.sh — devmem-only end-to-end HDMI bring-up for the
# PYNQ-base+CGRA bitstream. Replaces /usr/bin/hdmi-demo (which had
# DYNCLK_BASE=0x43C00000 hardcoded for the legacy build; in our build
# 0x43C00000 is audio_codec_ctrl_0 and dynclk lives at 0x43C10000).
#
# Steps:
#   1. SLCR: bump FCLK0 from 50 MHz (FSBL default) to 100 MHz so dynclk
#      MMCM can lock on its synth-time defaults at startup.
#   2. Reload bitstream (so dynclk IP boots fresh into WAIT_LOCKED with
#      FCLK0 already correct, otherwise its state machine stays stuck
#      and ignores all CTRL writes forever).
#   3. dynclk: program 25.175 MHz pixel clock and start MMCM.
#   4. Fill 640*480*3 byte framebuffer at 0x1F000000.
#   5. VTC: configure 640x480 timing, enable generator.
#   6. VDMA MM2S: reset, set frame buffer + sizes, start.

set -u

# === Address map (PYNQ-base + CGRA bolt-on) ===
DYNCLK=0x43C10000
VTC=0x43C20000
VDMA=0x43000000
FB=0x1F000000
FB_BYTES=$((640*480*3))     # 921600 bytes for 24-bit RGB

# Helper: write devmem in a way busybox accepts
w() { devmem "$1" 32 "$2" ; }
r() { devmem "$1" 32 ; }

echo "=========================================================="
echo " hdmi_first_light: PYNQ-base CGRA bitstream HDMI bring-up"
echo "=========================================================="

# ----------------------------------------------------------------
echo "[1/6] SLCR: set FCLK0 = 100 MHz"
# IO_PLL=1000 MHz. Want 100 MHz: DIVISOR0=10, DIVISOR1=1, SRCSEL=IO_PLL.
# Reg layout: 0x00100A00
w 0xF8000008 0xDF0D                 # SLCR_UNLOCK
w 0xF8000170 0x00100A00             # FPGA0_CLK_CTRL
w 0xF8000004 0x767B                 # SLCR_LOCK
echo "   FPGA0_CLK_CTRL=$(r 0xF8000170)  (expect 0x00100A00)"

# ----------------------------------------------------------------
echo "[2/6] Reload bitstream so dynclk IP starts fresh"
fpgautil -b /tmp/cgra_base.bin -f Full
state=$(cat /sys/class/fpga_manager/fpga0/state)
echo "   fpga_manager state = $state"
[ "$state" = "operating" ] || { echo "FATAL: fpga not operating"; exit 1; }

# Re-confirm FCLK0 (FSBL doesn't touch it on PL reload, but just in case)
case $(r 0xF8000170) in
  0x00100A00) ;;
  *) echo "   re-applying FCLK0=100 MHz"
     w 0xF8000008 0xDF0D ; w 0xF8000170 0x00100A00 ; w 0xF8000004 0x767B ;;
esac

sleep 1

# ----------------------------------------------------------------
echo "[3/6] dynclk: program 25.175 MHz (640x480), start MMCM"
# Values computed by ClkFindParams + ClkFindReg (REF=100 MHz, target=25.175 MHz)
# fbmult=34, clkdiv=9, maindiv=3 -> internal 125.926 MHz, PXL = 25.185 MHz
w "$DYNCLK"          0x00000000     # CTRL: stop
w $(printf '0x%X' $((DYNCLK + 0x08))) 0x00800105   # CLK_O_REG
w $(printf '0x%X' $((DYNCLK + 0x0C))) 0x00000451   # CLK_FB_REG
w $(printf '0x%X' $((DYNCLK + 0x10))) 0x00000000   # CLK_FRAC_REG (top bits)
w $(printf '0x%X' $((DYNCLK + 0x14))) 0x00002042   # CLK_DIV_REG
w $(printf '0x%X' $((DYNCLK + 0x18))) 0xD2CFA401   # CLK_LOCK_REG
w $(printf '0x%X' $((DYNCLK + 0x1C))) 0x006300FF   # CLK_FLTR_REG
w "$DYNCLK"          0x00000001     # CTRL: start

locked=0
for i in 1 2 3 4 5 6 7 8 9 10; do
  st=$(r $(printf '0x%X' $((DYNCLK + 0x04))))
  case $st in *1) locked=1 ; break;; esac
  usleep 200000
done
if [ $locked -eq 1 ]; then
  echo "   dynclk LOCKED (STATUS=$st)"
else
  echo "   FATAL: dynclk did not lock (STATUS=$st)"
  exit 1
fi

# ----------------------------------------------------------------
echo "[4/6] Skip framebuffer fill — use fb_paint instead."
# DO NOT dd to /dev/mem on this kernel. CONFIG_STRICT_DEVMEM=y means the
# write() path triggers arm_copy_from_user -> write_mem -> kernel BUG with
# "exited with irqs disabled", silently corrupting /dev/mem for the rest of
# the session (every subsequent devmem call SIGBUSes until reboot). Use the
# static musl-linked fb_paint binary (scripts/fb_paint.c) which mmap()s the
# region — that path the kernel allows. After this script finishes, run:
#   /tmp/fb_paint /tmp/fb_pattern.bin 0x1F000000
echo "   (run /tmp/fb_paint <pattern.bin> 0x1F000000 separately to fill FB)"

# ----------------------------------------------------------------
echo "[5/6] VTC: configure 640x480 timing, enable generator"
# 640x480@60: hps=656 hpe=752 hmax=799 hpol=0 vps=490 vpe=492 vmax=524 vpol=0
# Pre-computed register values:
w $(printf '0x%X' $((VTC + 0x60))) 0x01E00280   # GASIZE  (480<<16)|640
w $(printf '0x%X' $((VTC + 0x68))) 0x00000040   # GFENC   PROG
w $(printf '0x%X' $((VTC + 0x6C))) 0x00000010   # GPOL    AVP only
w $(printf '0x%X' $((VTC + 0x70))) 0x00000320   # GHSIZE  800
w $(printf '0x%X' $((VTC + 0x74))) 0x0000020D   # GVSIZE  525
w $(printf '0x%X' $((VTC + 0x78))) 0x02F00290   # GHSYNC  pack(656,752)
w $(printf '0x%X' $((VTC + 0x7C))) 0x031F0280   # GVBHOFF pack(640,799)
w $(printf '0x%X' $((VTC + 0x80))) 0x01EC01EA   # GVSYNC  pack(490,492)
w $(printf '0x%X' $((VTC + 0x84))) 0x02F00290   # GVSHOFF pack(656,752)
w $(printf '0x%X' $((VTC + 0x140))) 0x00000000  # GGD
w "$VTC"          0x0007FF03                    # CTL: ALLGENSRC|RU|SW
w "$VTC"          0x0007FF07                    # CTL: + GE (enable generator)

vtc_ctl=$(r $VTC)
vtc_st=$(r $(printf '0x%X' $((VTC + 0x04))))
echo "   VTC CTL=$vtc_ctl  STATUS=$vtc_st"

# ----------------------------------------------------------------
echo "[6/6] VDMA MM2S: reset, configure, start"
# CR @ +0x00, SR @ +0x04, FRMSTORE @ +0x18, PARKPTR @ +0x28
# MM2S frame regs at +0x50: VSIZE=+0x50, HSIZE=+0x54, STRD=+0x58, ADDR=+0x5C
w "$VDMA"                                  0x00000004   # CR RESET
usleep 5000
w $(printf '0x%X' $((VDMA + 0x18))) 0x00000001       # FRMSTORE = 1
w $(printf '0x%X' $((VDMA + 0x28))) 0x00000000       # PARKPTR  = 0 (read frame 0)
w "$VDMA"                                  0x00000001   # CR RUNSTOP
w $(printf '0x%X' $((VDMA + 0x5C))) "$FB"            # START_ADDR
w $(printf '0x%X' $((VDMA + 0x58))) 0x00000780       # STRD_FRMDLY = 1920 = 640*3
w $(printf '0x%X' $((VDMA + 0x54))) 0x00000780       # HSIZE       = 1920
w $(printf '0x%X' $((VDMA + 0x50))) 0x000001E0       # VSIZE       = 480 (write LAST)

usleep 10000
vdma_cr=$(r $VDMA)
vdma_sr=$(r $(printf '0x%X' $((VDMA + 0x04))))
echo "   VDMA MM2S CR=$vdma_cr  SR=$vdma_sr"
echo "   SR bit0=halted  bit1=idle  bits[11:4]=err"

# ----------------------------------------------------------------
echo
echo "=== final state ==="
echo "  fpga_manager  : $(cat /sys/class/fpga_manager/fpga0/state)"
echo "  FCLK0_CTRL    : $(r 0xF8000170)  (0x00100A00 = 100 MHz)"
echo "  dynclk STATUS : $(r $(printf '0x%X' $((DYNCLK + 0x04))))  (bit0=locked)"
echo "  VTC STATUS    : $(r $(printf '0x%X' $((VTC + 0x04))))"
echo "  VDMA MM2S SR  : $(r $(printf '0x%X' $((VDMA + 0x04))))"
echo "  uptime        : $(uptime)"
echo
echo "If a monitor is attached, you should see noise at 640x480@60Hz."
