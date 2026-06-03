# HDMI-IN Live-Capture — Board-Test Checklist (next session)

Everything below is build-verified; only the hardware test remains. The
`.xsa` is timing-met (WNS +0.112 / WHS +0.052) and OUT-safe (crystal=50,
OUT address map intact — flashing it does NOT regress the working HDMI-OUT demo).

## 0. Hardware setup
- Laptop HDMI-out → **J10 (HDMI-IN)** on the PYNQ-Z2.
- Monitor → **J11 (HDMI-OUT)**.
- Laptop second display: **1920×1080 60 Hz** (no-EDID default; desktop native 1080p ideal).
- WSL USB: `usbipd attach --wsl --busid <X>` from Windows if `/dev/ttyUSB1` missing.

## 1. (Re)build the LIVE ELF  — only if /tmp was cleared
```
cd /home/vinniny/centos_vm/projects/CGRA_project
source /tools/Xilinx/2025.1/Vitis/settings64.sh
CGRA_WS=/tmp/cgra_vitis_live CGRA_LIVE=1 xsct scripts/vitis_build_hdmi_demo.tcl
```
Expect: `LIVE_INPUT enabled` + `DEMO ELF: .../hdmi_demo.elf (~492 KB)`.

## 2. Program + run (fresh full program — NOT a soft reload; genlock needs it)
```
CGRA_XSA_DIR=/tmp/cgra_vitis_live/hdmi_demo/_ide \
CGRA_BIT=/tmp/cgra_vitis_live/hdmi_demo/_ide/bitstream/cgra_hdmi_dual.bit \
CGRA_ELF=/tmp/cgra_vitis_live/hdmi_demo/Debug/hdmi_demo.elf \
xsct scripts/vitis_launch_autohw.tcl
```
If `ps7_init: Cannot halt` → A9 wedged from a prior run → **power-cycle**, retry.

## 3. Smoke (read UART @115200, open serial BEFORE launch to catch the banner)
Expect the init sequence (HDMI-OUT first):
```
=== B6 MNIST HDMI demo ... ===
  hdmi: dynclk @0x43C00000 ... vtc 640x480 ... vdma mm2s ... out path up
HDMI ready ...
 [init.S1] HDMI-IN VDMA halt+reset
 [init.S2] (lean BD: no color_convert/pixel_pack)
 [init.S5] S2MM config ... [init.S6] FB pointers + done
HDMI-in initialised, waiting for laptop signal on J10...
```
→ Monitor (J11) should show the MNIST UI (yellow headers, panels). If "no signal":
power-cycle + fresh program (soft reloads break OUT genlock).

## 4. The capture test — draw a BIG digit centre-screen on the laptop
Read UART and watch the per-frame `IN inSR=... store=... px@roi=... ds28sum=...`:
- **PASS**: `store` advances (0→1→2→0…) and `px@roi` / `ds28sum` **change as you draw**
  (and `cgra=`/`int=`/`vfp=` predictions start tracking the drawn digit).
- If `store` stays 0 + values frozen: capture still not completing — re-check the
  laptop is truly sending 1080p to J10 and dvi2rgb is locking (read its ILAs:
  hw_ila_1/2 dbg_rMMCM_Locked / pVld via Vivado hw_manager headless).
- If image captures but **colors look swapped** (e.g. R↔B): add a color_swap on
  dvi2rgb→v_vid_in (PYNQ reference has one) OR swap bytes in frame_to_mnist read.

## Key fix this build carries (vs the frozen-capture build)
Capture AXIS (v_vid_in/aclk + subset + vdma_1 s_axis) reclocked FCLK0=50 →
**FCLK2=200 MHz** (> 148.5 MHz 1080p pixel rate → async FIFO drains, no overrun).
vid_io_in stays on dvi2rgb PixelClk. See memory `project_hdmi_in_recipe`.

## Diagnostics already in the ELF
- `hdmi_in_dmasr()` / `hdmi_in_cur_store()` — VDMA S2MM status + frame-store index.
- per-frame `px@roi` (raw bytes at frame centre 960,540) + `ds28sum` (28×28 sum).
- ROI = {x576,y156,768×768} centred — draw the digit in the MIDDLE of the screen.
