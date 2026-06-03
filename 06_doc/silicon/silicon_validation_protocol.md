# Silicon-Validation Protocol — PYNQ-Z2

Operational checklist for validating any bitstream/ELF combo on the
Zynq-7020 / PYNQ-Z2 target. Captures the recovery, ordering, and probe
techniques learned during the v_tpg AXIS-chain bring-up.

## Pre-flight

```bash
# 1. FTDI cable visible on WSL?
lsusb | grep -E '0403:6010|FTDI'        # expect FT2232C/D/H Dual UART/FIFO IC
ls /dev/ttyUSB*                          # at least /dev/ttyUSB1 for the UART

# 2. hw_server alive on tcp::3121?
pgrep -af hw_server                      # if missing: make hw_server_start

# 3. Repo at a clean commit
git status --short                       # should be empty
```

If JTAG isn't visible from WSL: on Windows run `usbipd attach --wsl --busid 1-3`.

## Programming bitstream + ELF

The `make program` / `make run_elf` targets already do:
1. `connect` to hw_server
2. `configparams force-mem-accesses 1` (auto, since commit `156976d`)
3. `rst -dap` (auto — clears AHB/APB AP sticky errors if any)
4. `fpga -file <bit>`
5. `ps7_init`
6. `dow <elf>` + `con`

```bash
# All-in-one (programs + runs + monitors UART):
make run_elf ELF=07_sw/baremetal/<demo>.elf BIT=bitstreams/<bit>.bit

# Watch UART live (115200 8N1):
python3 scripts/uart_monitor.py /dev/ttyUSB1 115200 60
```

## v_tpg silicon validation (one-shot)

```bash
# Full ILA + capture + verify (Procedure D bitstream required):
make vtpg_test

# Quick path (skip Vivado HW Mgr ILA capture):
make vtpg_test_quick
```

Output:
- `06_doc/silicon_vtpg_smpte_bars.bmp` — 640×480 BMP
- `/tmp/ila_capture_vtpg.csv`, `.vcd` — ILA waveform (full path only)
- Stdout: per-bar PASS/FAIL with ±3 RGB tolerance

## DAP-lockup recovery (when things go wrong)

**Symptom**: `targets` shows only `DAP (AHB AP transaction error)`, `xc7z020`,
and `Legacy Debug Hub`. The ARM Cortex-A9 cores are missing.

**Software recovery (no SRST press)**:
```tcl
connect
targets -set -filter {name =~ "DAP*"}
rst -dap                              # clears the AHB/APB sticky-error bit
after 1500
targets                               # ARM cores reappear as "Suspended"
```

This is automatic in `xsdb_program.tcl` since commit `156976d`. Manual
recovery may still be needed if `rst -dap` doesn't restore the AXI slave
port map (symptom: subsequent `mwr 0x43Cx_xxxx` "Blocked address"). In
that case, also run `configparams force-mem-accesses 1`.

**When software recovery fails**: physical SRST button press. The PS PLLs
may have lost lock; `rst -dap` doesn't reset the PS clock generator.
Full background: `06_doc/build/zynq_dap_recovery.md`.

## ILA capture without Vivado HW Manager

Use case: headless capture from a script.

```bash
source /tools/Xilinx/2025.1/Vivado/settings64.sh
vivado -mode batch -source scripts/ila_capture_vtpg.tcl
# outputs: /tmp/ila_capture_vtpg.{csv,vcd}
```

The script attaches to a live device (does NOT re-program), loads the
`.ltx` probes file, sets `CAPTURE_MODE=ALWAYS` and `DATA_DEPTH=256`,
arms, waits for trigger, and dumps both CSV and VCD.

## Common probe sequences

### Read VDMA S2MM state

```tcl
mrd -value 0x43000030      ;# S2MM_DMACR  -- bit 0 RS, bit 1 CIRC_PARK
mrd -value 0x43000034      ;# S2MM_DMASR  -- bits[28:24] FrameStore
mrd -value 0x430000A0      ;# S2MM_VSIZE  -- should = 480
mrd -value 0x430000A4      ;# S2MM_HSIZE  -- should = 1920
mrd -value 0x430000AC      ;# S2MM_START1 -- FB0 base, e.g. 0x11000000
```

### Read v_tpg state (Procedure-B/D bitstream)

```tcl
mrd -value 0x43CC0000      ;# AP_CTRL    -- bit 0 ap_start, bit 7 auto_restart
mrd -value 0x43CC0010      ;# height
mrd -value 0x43CC0018      ;# width
mrd -value 0x43CC0020      ;# bckgndId   -- 9 = COLOR_BARS
mrd -value 0x43CC0040      ;# colorFormat (note: doesn't change YCbCr output)
```

### Read axis_switch routing

```tcl
mrd -value 0x43CD0000      ;# CTRL        -- bit 1 = commit register update
mrd -value 0x43CD0040      ;# MI_MUX0     -- bits[3:0]: 0=S00(HDMI) 1=S01(v_tpg), bit[31] disable
```

### Dump FB0 via XSDB

```tcl
# Count is in 32-bit WORDS, not bytes. 640*480*3 / 4 = 230400
mrd -bin -file /tmp/fb.bin 0x11000000 230400
```

Then on the host:
```bash
python3 scripts/hdmi_in_dump_to_bmp.py /tmp/fb.bin -o /tmp/fb.bmp \
        -w 640 --height 480 --rgb-order RGB
```

## Verifying YCbCr → RGB conversion

Pre-checks (before assuming v_tpg outputs RGB):
1. Set `BCKGND_ID = 7` (SOLID_BLACK)
2. Dump FB0
3. Sample any pixel — if bytes are `(0, 128, 128)` → YCbCr. If `(0, 0, 0)` → RGB.

If YCbCr (common, even with `colorFormat = 2`), program `color_convert`
with the BT.601 matrix:

```c
hdmi_in_color_convert_ycbcr2rgb();        /* BT.601 — for v_tpg, SD */
hdmi_in_color_convert_ycbcr2rgb_bt709();  /* BT.709 — for HD HDMI   */
```

## Windows defense-day workflow (Vitis-based)

This doc covers the WSL/bash flow used during tonight's rehearsal. For
the **Windows** defense-day flow (Vivado GUI → Vitis IDE → Launch on
Hardware) see `06_doc/build/windows_defense_day_workflow.md`. Key difference:
on Windows, Vitis "Launch on Hardware" handles PL programming + ps7_init
+ ELF load in one click — no manual `xsdb` scripting needed. The
`.xsa` file (auto-emitted by all three Vivado orchestrators) is the
load-bearing handoff between Vivado and Vitis.

## Reference artefacts

| Topic | Path |
|---|---|
| Bitstream build procedures | `06_doc/build/vivado_bitstream_build_procedure.md` |
| Windows defense-day flow | `06_doc/build/windows_defense_day_workflow.md` |
| DAP recovery deep-dive | `06_doc/build/zynq_dap_recovery.md` |
| Silicon results numbers | `06_doc/thesis/chapter5_silicon_results.md` |
| Defense Q&A | `06_doc/defense/defense_qa.md` |
| Slide outline | `06_doc/defense/defense_slide_outline.md` |
| Coverage snapshot | `06_doc/sim_cov_report_2026-05-25.txt` |
| Genus HAL lint snapshot | `06_doc/genus_hal_check_design_2026-05-25.rpt` |
| Captured SMPTE bars | `06_doc/silicon_vtpg_smpte_bars.bmp` |
| ILA waveform sample | `06_doc/silicon_vtpg_ila_capture.csv` |
