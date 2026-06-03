# Windows Defense-Day Workflow

**Target audience.** The user on defense day, opening Vivado 2025.1 +
Vitis 2025.1 on Windows, with the PYNQ-Z2 board attached via USB-JTAG.

**Premise.** All the Tcl-side gotchas (six of them, listed in
`chapter5_silicon_results.md` §5.1.2) have already been fixed in the
WSL rehearsal. Tonight's WSL work guarantees the Windows-side flow is
bug-free if you follow the steps below.

---

## End-to-end flow (one diagram)

```
Vivado 2025.1 (GUI or Tcl)              Vitis 2025.1                   PYNQ-Z2 board
─────────────────────────               ──────────────────             ──────────────
source <build_procedure>.tcl   ───►     Platform Project              JTAG / UART
                                        from <.xsa>           ───►    Launch on
write_bitstream                            │                          Hardware
                                           ▼
write_hw_platform -include_bit  ───►   Application Project
   produces .xsa                       (drop in .c + .ld)
                                           │
                                           ▼
                                       Build → .elf
```

The **.xsa** is the load-bearing artefact between Vivado and Vitis. It's
a zip that contains:
- The `.bit` file
- The auto-generated `ps7_init.{tcl,c,h}` (PS clocks, DDR, MIO)
- The `.hwh` hardware description
- DRC / util / power / timing reports
- Block-design topology

The three orchestrator Tcl scripts now emit a `.xsa` automatically via
`write_hw_platform -fixed -include_bit -force`.

---

## Step 1 — Stage the WSL repo on Windows

You have two choices:

**(A) Access WSL files directly via UNC path.** No copy needed. Open
Windows Explorer and type:
```
\\wsl$\Ubuntu\home\vinniny\centos_vm\projects\CGRA_project
```
(replace `Ubuntu` with your WSL distro name if different).

**(B) Clone to a Windows-native path.** From a WSL prompt:
```bash
cp -r /home/vinniny/centos_vm/projects/CGRA_project /mnt/c/Users/thanh/Desktop/CGRA_project
```
Or `git clone <url>` if you push to GitHub first.

**Fast path — skip Vitis IDE clicks entirely.** A reusable xsct batch
script `scripts/vitis_build_demo.tcl` does platform + app create + source
import + build in one command:

```cmd
:: From Windows cmd, with Vitis 2025.1 on PATH (or use xsct.bat full path):
xsct C:\Users\thanh\Desktop\CGRA_project\scripts\vitis_build_demo.tcl
```

Environment overrides:
```cmd
set CGRA_XSA=C:\path\to\cgra_rebuilt_from_base.xsa
set CGRA_DEMO=cgra_test
set CGRA_DEMO_SRCS=start.s main.c gic.c gic.h cgra.h uart.h linker.ld
xsct scripts\vitis_build_demo.tcl
```

Validated on WSL Vitis 2025.1 (2026-05-25): builds demo_vtpg.elf at
45 328 bytes from `bitstreams/cgra_vtpg_ila.xsa`. Same tool / Tcl on
Windows.

Path used in the rest of this doc (substitute as needed):
```
C:\Users\thanh\Desktop\CGRA_project\
```

---

## Step 2 — Open Vivado 2025.1 and produce a `.xsa`

Three procedures available. Pick whichever fits the demo you want.

### Procedure A — clean rebuild of the working bitstream (~50 min)

1. Launch Vivado 2025.1.
2. In the Tcl console:
   ```tcl
   source C:/Users/thanh/Desktop/CGRA_project/scripts/rebuild_bitstream_from_base.tcl
   ```
3. The script runs: project create → BD recreate from `base.tcl` →
   constraints → synth → impl → bitstream → `write_hw_platform`.
4. When it finishes the Tcl console prints:
   ```
   Bitstream : .../cgra_rebuild.runs/impl_1/base_wrapper.bit
   XSA       : .../cgra_rebuild.runs/impl_1/base_wrapper.xsa
   ```
5. Copy `base_wrapper.xsa` to a convenient location, e.g.
   `C:\Users\thanh\Desktop\cgra_xsa\cgra_rebuilt.xsa`.

### Procedure B — + v_tpg test pattern (~50 min)

```tcl
source C:/Users/thanh/Desktop/CGRA_project/scripts/build_v_tpg_test_bitstream.tcl
```
Output: `cgra_vtpg.runs/impl_1/base_wrapper.{bit,xsa}`.

### Procedure D — + System ILA (~60 min)

```tcl
source C:/Users/thanh/Desktop/CGRA_project/scripts/build_vtpg_ila_bitstream.tcl
```
Output: `cgra_vtpg_ila.runs/impl_1/base_wrapper.{bit,ltx,xsa}`.

### Or skip rebuild — use pre-built .xsa

If you don't need to demo the build, the pre-built bitstreams are
already in the repo:
- `bitstreams/cgra_top.bit` — production (silicon-validated 50 MHz)
- `bitstreams/cgra_rebuilt_from_base.bit` — Procedure A output
- `bitstreams/cgra_vtpg_test.bit` — Procedure B output
- `bitstreams/cgra_vtpg_ila.bit` + `.ltx` — Procedure D output

For the production `cgra_top.bit`, the `.xsa` is in the original
Windows project at:
```
C:\Users\thanh\Desktop\CGRA_PYNQ_clean\cgra_vitis\platform\hw\<bd>.xsa
```
(or re-export from the existing Vivado project via File → Export →
Export Hardware → Include bitstream).

---

## Step 3 — Create a Vitis platform from the .xsa

1. Launch Vitis 2025.1 (Vitis Unified IDE).
2. File → New → **Platform Component**.
3. **Name**: `cgra_pynq_base_platform` (or whatever you prefer).
4. **Hardware Specification**: browse to your `.xsa` from Step 2.
5. **Operating System**: `standalone` (bare-metal).
6. **Processor**: `ps7_cortexa9_0`.
7. **Generate boot artefacts**: leave default (no).
8. Click **Finish**.

The platform project appears. Right-click it → **Build**. This compiles:
- The BSP (Board Support Package) — `xparameters.h`, `xil_io.h`, GIC driver, etc.
- `ps7_init.c` from the auto-generated source in the `.xsa`

When the build finishes you have a working bare-metal target template.

---

## Step 4 — Create the application project

1. File → New → **Application Component**.
2. **Name**: `demo_vtpg` (or `cgra_test` for the 96-check regression,
   `demo_mnist_hdmi_bm` for the 3-panel demo, etc.).
3. **Platform**: select the one you just built.
4. **Domain**: standalone, `ps7_cortexa9_0`.
5. **Template**: **Empty Application (C)**.
6. Finish.

### Drop in the source files

Copy from `C:\Users\thanh\Desktop\CGRA_project\07_sw\baremetal\` into the
app's `src/` directory:

| Demo target | Files to copy |
|---|---|
| `demo_vtpg` | `start.s`, `demo_vtpg.c`, `hdmi_in_bm.c`, `hdmi_in_bm.h`, `vtpg.h`, `gic.c`, `gic.h`, `uart.h`, `linker.ld` |
| `cgra_test` (full regression) | `start.s`, `main.c`, `gic.c`, `gic.h`, `cgra.h`, `uart.h`, `linker.ld` |
| `demo_mnist_hdmi_bm` (3-panel MNIST) | `start.s`, `demo_mnist_hdmi_bm.c`, `cgra_kernels_cnn.h`, `mnist_*.h`, `gic.c`, `uart.h`, `linker.ld` |

### Configure the project

- **Linker script**: right-click app → Properties → C/C++ Build →
  Settings → ARM v7 gcc linker → General → **Linker Script**: point at
  the imported `linker.ld`.
- **Symbols**: same Properties dialog → ARM v7 gcc compiler → Symbols:
  add `BOARD_CGRA_ONLY` (or `BOARD_PYNQ_BASE` if using the PYNQ-base BD).
- **Float ABI**: ARM v7 gcc compiler → Miscellaneous: confirm
  `-mfpu=vfpv3 -mfloat-abi=hard` is present (Vitis usually defaults
  to soft-float).

### Build

Right-click app → **Build**. ELF appears at `<app>/Debug/<app>.elf`.

**Two Vitis 2025.1 gotchas** validated on 2026-05-25 (only relevant if
doing the GUI flow — the batch script handles them):

1. The Empty C template name is `"Empty Application(C)"` (no space
   before the paren). Older Vitis versions used `"Empty Application
   (C)"` — the space breaks 2025.1.
2. `start.s` will fail to assemble with "selected processor does not
   support `isb`/`vmsr`/`wfi`" because Vitis 2025.1's auto-makefile
   invokes the assembler without inheriting `-mcpu=cortex-a9`. Fix
   in Properties → C/C++ Build → Settings → ARM v7 gcc assembler →
   General → Assembler Flags: add `-mcpu=cortex-a9 -mfpu=vfpv3
   -mfloat-abi=hard`.

---

## Step 5 — Launch on Hardware (defense-day moment)

This is the step that previous incorrect WSL guidance skipped over.

1. Make sure the board is powered on and the USB-JTAG cable is plugged
   in.
2. Vitis: Run → **Run Configurations**.
3. Right-click "Single Application Debug (GDB)" → **New Configuration**.
4. Target: select the auto-discovered Hardware Server (or "Local"
   pointing at `localhost:3121`).
5. **Application** tab: confirm the ELF path.
6. **Target Setup** tab:
   - **Initialization file**: should auto-populate from the platform's
     `ps7_init.tcl`. If not, browse to it (inside the platform
     project's `hw/` folder).
   - **Reset entire system**: yes.
   - **Program FPGA**: yes (this is where the .bit gets loaded).
   - **Run ps7_init**: yes (default).
   - **Run ps7_post_config**: yes (default).
7. Click **Apply** → **Run**.

Vitis now does, in order:
- `connect` to hw_server
- `fpga -file <bit-from-xsa>`
- `targets -set <Cortex-A9-0>`
- `stop`
- `source ps7_init.tcl; ps7_init; ps7_post_config`
- `dow <app>.elf`
- `con`

**No DAP lockup, no manual `rst -dap` needed.** This is the safe path.

---

## Step 6 — UART output

Vitis has a built-in serial monitor:
1. Window → Show View → **Vitis Serial Monitor**.
2. Click "Connect".
3. Port: the COM port for the USB-UART (check Device Manager — typically
   COMx where x = whatever Windows assigned).
4. Baud: **115200**, 8N1.
5. Demo output appears live.

---

## Step 7 — Optional ILA capture (Procedure-D bitstream only)

For the visual wow-factor:

1. After Step 5 has programmed the board and the ELF is running, open
   **Vivado 2025.1** alongside Vitis.
2. Flow → **Open Hardware Manager**.
3. Open Target → **Auto Connect**.
4. Right-click the device → **Refresh Device**.
5. Right-click → **Specify Probes file** if the `.ltx` doesn't
   auto-load — browse to your build's `debug_nets.ltx`.
6. The ILA core(s) appear in the Hardware tab.
7. Right-click `hw_ila_1` → **Run Trigger Immediate**.
8. The waveform window opens — TVALID, TREADY, TDATA on each AXIS link.

Don't touch "Program Device" in Vivado HW Manager. The board is already
programmed by Vitis; HW Manager is read-only at this point.

---

## Step 8 — Frame capture / BMP render (Procedure-B or D)

If demonstrating the v_tpg colour bars (Step 5 with `demo_vtpg.elf`):

1. In the **XSDB** console (Vivado → Window → Xilinx → XSCT, or open
   xsdb.bat from the Vivado install):
   ```tcl
   connect -host localhost -port 3121
   targets -set -filter {name =~ "*Cortex-A9*0*"}
   stop
   mrd -bin -file C:/Users/thanh/Desktop/fb.bin 0x11000000 230400
   con
   ```
2. Then in a Windows command prompt (with Python installed):
   ```cmd
   python C:\Users\thanh\Desktop\CGRA_project\scripts\hdmi_in_dump_to_bmp.py ^
          C:\Users\thanh\Desktop\fb.bin ^
          -o C:\Users\thanh\Desktop\fb.bmp ^
          -w 640 --height 480 --rgb-order RGB
   ```
3. Open `fb.bmp` — the 8 SMPTE bars appear.

(Or use the already-captured `06_doc/silicon_vtpg_smpte_bars.bmp` from
the WSL repo as a fall-back if the live capture fails during demo.)

---

## Step 9 — 3-panel MNIST demo on HDMI-out

For the headline thesis demo (3.81× speedup):

1. In Vitis create / launch `demo_mnist_hdmi_bm` per Steps 4–5 with
   `cgra_top.bit` (the production bitstream).
2. Plug an HDMI monitor into the PYNQ-Z2's **J11** (HDMI-out)
   connector.
3. The three-panel display appears: CGRA-FC | ARM-INT-FC | ARM-VFP-FC
   side by side with per-image cycle counts.
4. UART log also dumps the cycle counters image-by-image; let it run
   over 2 745 images for the live accuracy result.

---

## What to do if something goes wrong

| Symptom | Fix |
|---|---|
| Vivado Tcl script errors during `apply_bd_automation` | Re-check `CGRA_PYNQ_REPO` env var points at `C:/Users/thanh/Desktop/PYNQ_repo/boards/ip` |
| Vitis "platform build failed" | The .xsa likely doesn't have `-include_bit`. Re-run the orchestrator or `write_hw_platform -fixed -include_bit -force` in the Vivado project |
| Vitis "Launch on Hardware" hangs at "Initialising target" | hw_server isn't running. Open xsdb.bat → `connect` — if that fails, Device Manager → check USB-JTAG drivers |
| Cortex-A9 missing from targets | Use XSDB: `targets -set 1; rst -dap; after 1500; targets` |
| `mrd` says "Blocked address" | XSDB: `configparams force-mem-accesses 1` |
| Bitstream programs but PS dead | Vitis Run Configuration → confirm **Run ps7_init = YES** |
| `app create` error: "is not valid application template name" | Template name in 2025.1 is `"Empty Application(C)"` (no space). |
| `start.s` build fails with "isb / vmsr / wfi not supported in ARM mode" | Add `-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard` to assembler-flags (the batch script does this automatically). |

---

## Reference

| Doc | Purpose |
|---|---|
| `06_doc/build/vivado_bitstream_build_procedure.md` | Vivado-side details, Procedure A/B/C |
| `06_doc/silicon/silicon_validation_protocol.md` | WSL-side bash equivalents of the steps above |
| `06_doc/build/zynq_dap_recovery.md` | When the DAP locks up despite everything |
| `06_doc/thesis/chapter5_silicon_results.md` | The measured numbers for the slides |
| `06_doc/defense/defense_qa.md` | Q&A for the examiners |
| `06_doc/defense/defense_slide_outline.md` | 14-slide deck outline |
