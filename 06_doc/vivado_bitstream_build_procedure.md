# Vivado Bitstream Build Procedure

**Thesis Chapter 5 — supporting material for the silicon-results section.**

This document is the *demonstrable Vivado-only workflow* for re-creating
the working `cgra_pynq_base` bitstream and extending it with a synthetic
test-pattern source for HDMI-in path validation.

## Sources of truth

| Asset | Path |
|---|---|
| BD recipe | `/mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/base.tcl` |
| CGRA IP repo | `/mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/cgra_ip_repo` |
| PYNQ-Z2 board IP repo | `/mnt/c/Users/thanh/Desktop/PYNQ_repo/boards/ip` |
| Working bitstream | `/mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/cgra_pynq_base.runs/impl_1/base_wrapper.bit` |
| Working ps7_init | `/mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/cgra_vitis/platform/hw/sdt/ps7_init.tcl` |

`base.tcl` is a `write_bd_tcl -force` export of the working BD —
reproducing it in a fresh project gives an *identical* bitstream
(modulo placer randomness). That's the foundation of the procedure.

## Procedure A — Re-create the working bitstream (proof of build flow)

```bash
# 1. Open Vivado 2024.1 (or patch base.tcl's version string for 2025.1 —
#    base.tcl has a hard `set scripts_vivado_version 2024.1` check).
vivado &

# 2. In the Vivado Tcl console:
create_project -force cgra_rebuild ~/vivado_projects/cgra_rebuild -part xc7z020clg400-1
set_property ip_repo_paths {
    /mnt/c/Users/thanh/Desktop/PYNQ_repo/boards/ip
    /mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/cgra_ip_repo
} [current_project]
update_ip_catalog

# 3. Source the BD recipe.
source /mnt/c/Users/thanh/Desktop/CGRA_PYNQ_clean/base.tcl

# 4. Generate wrapper.
make_wrapper -files [get_files base.bd] -top -import
set_property top base_wrapper [current_fileset]

# 5. Add constraints (J11 HDMI-out + J10 HDMI-in pin LOCs).
add_files -fileset constrs_1 -norecurse 01_bench/constrs_pynq_z2.xdc

# 6. Synth + impl + bitstream (~50 min total).
launch_runs synth_1 -jobs 2
wait_on_run synth_1
launch_runs impl_1 -to_step write_bitstream -jobs 2
wait_on_run impl_1

# 7. Output is at:
#   ~/vivado_projects/cgra_rebuild/cgra_rebuild.runs/impl_1/base_wrapper.bit
#
# Compare to /mnt/c/.../impl_1/base_wrapper.bit — should be bit-equivalent
# (LUT placement may differ slightly between runs, but utilisation /
# timing / DRC reports match).

# 8. Export hardware platform (.xsa) — load-bearing handoff to Vitis.
#    -include_bit packages the .bit + ps7_init.{tcl,c,h} in the .xsa zip.
write_hw_platform -fixed -include_bit -force \
    -file ~/vivado_projects/cgra_rebuild/cgra_rebuild.runs/impl_1/base_wrapper.xsa
```

**Note** (2026-05-25): the `scripts/rebuild_bitstream_from_base.tcl`,
`scripts/build_v_tpg_test_bitstream.tcl`, and
`scripts/build_vtpg_ila_bitstream.tcl` orchestrators now invoke
`write_hw_platform` automatically as their final step. You only need to
do it manually if you're walking the procedure in the GUI. The `.xsa`
is what Vitis "New Platform Project" consumes for the Windows
defense-day flow (see `06_doc/windows_defense_day_workflow.md`).

This rebuild is **the thesis demonstration** — *anyone with Vivado 2024.1
+ the IP repos can reproduce the silicon-validated bitstream from one
file (`base.tcl`)*. The CGRA RTL ships in the repo as
`xilinx.com:user:cgra_top:1.0` via `package_cgra_ip.tcl`.

## Procedure B — Extend the BD with a v_tpg test-pattern source

For HDMI-in pipeline validation without a real HDMI source, insert a
**v_tpg + axis_switch** pair between `dvi2rgb_0` and `color_convert_in`:

```
J10 (TMDS)   →  dvi2rgb_0  ─────────────.
                                          │
                                          ├──→  axis_switch_in.S00_AXIS
v_tpg_test_0 (color bars)  ───────────────┘                 ↓
                                                          M00_AXIS
                                                            ↓
                                              video/hdmi_in/color_convert
                                                            ↓
                                              video/hdmi_in/pixel_pack
                                                            ↓
                                              video/axi_vdma (S2MM)
                                                            ↓
                                              DDR @ 0x1100_0000
```

`axis_switch_in` selects between live HDMI (S00) and the synthetic test
pattern (S01) via an AXI-Lite control register.

### Step-by-step in the Vivado IP Integrator GUI

1. **Open the BD** (Procedure A step 3 done first).
2. **Add `v_tpg`** (Add IP → search "Video Test Pattern Generator"):
   - `Has AXI4-Lite`: ✓ (need SW control)
   - `Max columns / rows`: 640 / 480
   - `Samples per clock`: 1
   - `Max data width`: 8
3. **Add `axis_switch`**:
   - `Routing mode`: 0 (round-robin disabled; SW-controlled)
   - `NUM_SI`: 2 (slaves)
   - `NUM_MI`: 1 (master)
   - Match TDATA / TUSER / TLAST widths to the existing dvi2rgb output
     AXIS (24-bit TDATA, 1-bit TUSER, has TLAST).
4. **Disconnect** the existing AXIS net feeding `video/hdmi_in/color_convert/stream_in_24`.
5. **Re-connect**:
   - dvi2rgb frontend AXIS output → `axis_switch_in/S00_AXIS`
   - `v_tpg_test_0/m_axis_video` → `axis_switch_in/S01_AXIS`
   - `axis_switch_in/M00_AXIS` → `video/hdmi_in/color_convert/stream_in_24`
6. **Clock + reset hookup** (both new IPs to FCLK0 / 100 MHz domain):
   - `v_tpg_test_0/ap_clk`         → `ps7_0/FCLK_CLK0`
   - `v_tpg_test_0/ap_rst_n`       → existing `periph_resetn_clk100M`
   - `axis_switch_in/aclk`         → `ps7_0/FCLK_CLK0`
   - `axis_switch_in/aresetn`      → `periph_resetn_clk100M`
   - `axis_switch_in/s_axi_ctrl_aclk` and `s_axi_ctrl_aresetn` → same
7. **AXI-Lite control**: connect both new IPs to the control SmartConnect
   (`ps7_0_axi_periph` — increase NUM_MI by 2). Assign addresses in the
   free hole above 0x43Cx_x — recommended:
   - `v_tpg_test_0` AXI-Lite @ `0x43CC_0000`
   - `axis_switch_in` AXI-Lite @ `0x43CD_0000`
8. **Validate** (`F6` or Tools → Validate Design). Must pass.
9. **Re-generate wrapper** (right-click BD → Create HDL Wrapper → "let
   Vivado manage", overwrite).
10. **Launch runs** → synth_1 → impl_1 → bitstream.

### SW control of the new IPs

```c
/* v_tpg AP_CTRL + size + pattern, then go. AP_CTRL is at offset 0. */
#define VTPG_BASE       0x43CC0000UL
#define VTPG_AP_CTRL    0x00
#define VTPG_COLS       0x10
#define VTPG_ROWS       0x18
#define VTPG_FORMAT     0x20    /* 2 = RGB */
#define VTPG_PATTERN    0x30    /* 1 = colour bars; 9 = checkerboard; etc */
#define VTPG_AP_START   0x01
#define VTPG_AUTORESTART 0x80   /* OR with AP_START for free-run */

mmio_w(VTPG_BASE + VTPG_COLS,    640);
mmio_w(VTPG_BASE + VTPG_ROWS,    480);
mmio_w(VTPG_BASE + VTPG_FORMAT,  2);
mmio_w(VTPG_BASE + VTPG_PATTERN, 1);   /* colour bars */
mmio_w(VTPG_BASE + VTPG_AP_CTRL, VTPG_AP_START | VTPG_AUTORESTART);

/* axis_switch routing: write the destination master ID to MI_MUX. The
 * v1.1 axis_switch has one MI control register per master at offset
 * 0x40 + 4·M. Writing 0x80000000 disables; bits[1:0] select the source. */
#define AXIS_SWITCH_BASE 0x43CD0000UL
#define AXIS_SWITCH_MUX0 0x40
mmio_w(AXIS_SWITCH_BASE + AXIS_SWITCH_MUX0, 0x00000001);  /* S01 = v_tpg */
/* register update commit */
mmio_w(AXIS_SWITCH_BASE + 0x00, 0x02);
```

After the SW sequence runs:
- v_tpg streams 640×480 colour bars at the pixel rate
- axis_switch routes those into color_convert → pixel_pack → VDMA
- VDMA captures frames at `0x1100_0000` (FB0)
- XSDB `mrd -bin -file fb0.bin 0x11000000 230400` + the BMP host tool
  shows the colour-bar pattern → AXIS path is end-to-end validated

## Procedure C — Switch back to live HDMI

After verifying with v_tpg:

```c
mmio_w(AXIS_SWITCH_BASE + AXIS_SWITCH_MUX0, 0x00000000);  /* S00 = dvi2rgb */
mmio_w(AXIS_SWITCH_BASE + 0x00, 0x02);                    /* commit */
hdmi_in_enable_vtc();   /* now safe — pixel clock from dvi2rgb */
```

Same bitstream, two paths. v_tpg validates the AXIS infrastructure;
dvi2rgb path activates once a real HDMI source is plugged into J10.

## Repo artefacts supporting this procedure

| File | Purpose |
|---|---|
| `scripts/build_v_tpg_test_bitstream.tcl` | Linux-side orchestrator (sources base.tcl, applies patch, runs synth+impl). Version-patches base.tcl's 2024.1 string for 2025.1 compatibility |
| `scripts/add_v_tpg_test_pattern.tcl` | Additive BD patch (v_tpg + axis_switch + AXI-Lite + address map) |
| `bitstreams/cgra_pynq_base_working.bit` | Staged copy of the silicon-validated bitstream |
| `scripts/ps7_init.tcl` | Vitis-exported PS init from the working project |
| `06_doc/vivado_bitstream_build_procedure.md` | This document |

## Build resource cost (Linux Vivado 2025.1 on WSL2 8 GiB)

| Stage | Time | Peak RAM |
|---|---|---|
| Project create + IP repo load | <1 min | ~1.5 GiB |
| BD recreate (source base.tcl) | ~2 min | ~1.8 GiB |
| Wrapper + constraints | <1 min | ~2 GiB |
| Synth (-jobs 2) | ~20 min | ~3 GiB |
| Impl + bitstream | ~30 min | ~5 GiB |
| **Total walk-away** | **~55 min** | **5 GiB peak** |
| Power report (optional) | +5 min | ~3 GiB |

Cold-start memory budget for WSL2: at least 6 GiB free recommended. If
WSL has only 8 GiB total and Vivado climbs past ~5.5 GiB, swap thrashing
slows impl significantly.
