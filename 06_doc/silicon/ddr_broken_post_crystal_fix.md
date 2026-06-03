# DDR controller broken after crystal=50 BD-FIX — OCM-staged workaround

**Date:** 2026-05-28
**Bitstream:** `bitstreams/cgra_top.xsa` (MD5 `f34ca0f6…`, contains `.bit` MD5 `1c26853b…`)

## Symptom

After the BD-FIX commit (`fb94e59`, set `PCW_CRYSTAL_PERIPHERAL_FREQMHZ=50`,
removed HDMI/video IPs), bare-metal ELFs that stage DMA buffers in DDR
(at `0x00100000+`) hang. Direct PS-side writes to DDR also silently fail:

```
mwr -force 0x00100000 0xDEADBEEF  ->  mrd reads back 0
mwr -force 0x00200000 0x12345678  ->  mrd reads back 0
```

Meanwhile OCM works (writes at `0x0`, `0x100`, `0x20000` all read back
correctly), and CGRA APB CSR access works (the smoke ELF's
`DEADBEEF`/`CAFEBABE` ping-pong on `CGRA_DMA_SRC` passes).

## Root cause hypothesis

The new `ps7_init.tcl` (extracted from the regenerated `.xsa`) programs
the DDR controller with **the same timing parameters as the old ps7_init**:

```
NEW: mask_write 0XF8006000 0x0001FFFF 0x00000080   (DDRC_CTRL bit-pattern)
OLD: mask_write 0XF8006000 0x0001FFFF 0x00000084
NEW: mask_write 0XF8006008 0x03FFFFFF 0x03C0780F   (same in both)
NEW: mask_write 0XF800600C 0x03FFFFFF 0x02001001   (same in both)
…
```

But the DDR PLL FBDIV field is also identical: `0x15000` in
`F8000104[18:12]` → FBDIV = 21. Under the OLD (broken) crystal=33.333
config, this gave **DDR PLL = 700 MHz** (DDR3-700, slow). Under the
NEW crystal=50 config, it now gives **DDR PLL = 1050 MHz**
(DDR3-1050, ≈ PYNQ-Z2 standard).

The DDR controller timing parameters at `0xF8006008+` are programmed
for the **old** target (700 MHz). With the PLL now at 1050 MHz, the
controller's timing assumptions are wrong by ~1.5× → DDR refuses to
train, all writes go to /dev/null.

## Path forward (chosen for now)

**Workaround**: stage DMA buffers in OCM low-alias (`0x0-0x3FFFF`).
- The bare-metal `linker.ld` already places `.text`/`.data`/stacks at
  `0x4000-0x1FFFF`.
- `0x20000-0x3FFFF` (128 KB) is unused → safe for DMA staging.
- The CGRA's `m_axi` master, routed through HP0 + the smartconnect,
  successfully reads OCM low-alias (verified by an xsct-driven manual
  DMA: `0x20000 → 0x20000000`, 8 bytes, completed in 65 ms, `status=2`,
  `error=0`).

For B1 (`bench_mac_micro`): change `DDR_STAGE` from `0x00100000` to
`0x00030000`. Other ELFs (B2-B6) will need the same change to their
staging-address constants.

## Real fix (deferred)

The proper fix is to **regenerate ps7_init.tcl with the correct DDR
target-frequency computation**:

1. In Vivado BD: open Customize IP on PS-7, navigate to "DDR
   Configuration", manually set `PCW_DDR_PERIPHERAL_FREQMHZ` to the
   board-rated `533.333` MHz (DDR3-1066, PYNQ-Z2 chip rating).
2. Validate BD, save, rerun synth+impl+bitgen.
3. The regenerated `ps7_init.tcl` will recompute DDRC_xx timing
   params for the new target frequency.

OR alternatively: set `PCW_CRYSTAL_PERIPHERAL_FREQMHZ` back to
33.333 (matching whatever the original BD assumed). The crystal-fix
that started this rabbit hole was based on UART baud math (we observed
real-board baud was 172800 not 115200) — but if everything was
self-consistent under the wrong assumption, "fixing" only crystal
introduced new mismatches. A holistic option is: keep `crystal=50`
**and** force Vivado to recompute the entire PS7 clock graph (close
the BD, re-open, re-validate, regen) so all FBDIVs and the DDR
target are mutually consistent.

## Affected files

- `07_sw/baremetal/bench_mac_micro.c`     — `DDR_STAGE 0x00100000 → 0x00030000`
- `07_sw/baremetal/bench_dma_stream.c`    — will need same patch for B2
- `07_sw/baremetal/demo_mnist_per_stage.c` — will need staging-address audit
  before running B3-B5 (CNN weight blob is too large for OCM low-alias;
  may require splitting layers into multiple OCM-resident chunks, or
  fixing DDR first)
- `07_sw/baremetal/arm_fc_neon_bm.c`       — pure ARM, unaffected; B6 OK as-is

## Verification commands

```bash
# Diagnostic dump script lives at scripts/vivado_diagnostics/probe_ddr.tcl
source /tools/Xilinx/2025.1/Vitis/settings64.sh
xsct scripts/vivado_diagnostics/probe_ddr.tcl
```

---

## UPDATE 2026-05-29 — ROOT CAUSE CONFIRMED + DDR FIX APPLIED TO BD

**Confirmed root cause:** the BD was built with `BoardPart=""`. Without the
PYNQ-Z2 board file, the PS-7 DDR PHY got **generic identical per-lane delays**.
Proven by diffing ps7_init DDR data-eye registers (0xF8006120-0x6138) vs a
board-aware reference build (`backups/.../cgra_rebuilt_from_base`):

| read-DQS delay reg | board-aware REF | broken (generic) |
|---|---|---|
| 0xF800612C lane0 | 0x00026C05 | 0x00028C00 |
| 0xF8006130 lane1 | 0x00026007 | 0x00028C00 |
| 0xF8006134 lane2 | 0x0001D800 | 0x00028C00 |
| 0xF8006138 lane3 | 0x0001E000 | 0x00028C00 |

Silicon symptom: DDR controller reaches op_mode=1 (NORMAL) + DCI done + PLL
locked + correct 525 MHz, **yet read/write data is corrupt** (data eye not
centered). OCM + CGRA-APB work fine; only DDR memory is dead.

**Fix applied (and SAVED in the BD):** the 45 PYNQ-Z2 board-trace-delay
UIPARAMs from the official board file preset.xml, applied directly to the
PS-7 (DQS_TO_CLK_DELAY_0=-0.051, BOARD_DELAY0=0.279, DQS/DQ/CLOCK lengths,
etc.). Crystal=50 and FCLK0=50 preserved. Verified persisted in design_1.bd.

**Remaining blocker (mechanical, GUI-easy):** an earlier `upgrade_ip`
experiment corrupted `smartconnect_0`'s internal `psr_aclk` proc_sys_reset
sub-core (`C_AUX_RESET_HIGH` elaboration error on full BD regen). This
blocks generating a fresh ps7_init / .xsa in batch. No BD backup exists to
revert. Best fixed in the Vivado GUI:

### GUI completion steps (Windows Vivado 2025.1, project cgra_ip.xpr)
1. **Tools ▸ Reports ▸ Report IP Status** → select `smartconnect_0`
   (and any other locked IP) → **Upgrade Selected**. The GUI migrates the
   internal proc_sys_reset correctly (batch upgrade_ip does not).
2. **Generate Output Products** (Sources ▸ design_1.bd ▸ right-click ▸
   Generate Output Products ▸ Global ▸ Generate).
3. **Generate Bitstream** (or Flow ▸ Run Implementation, then write_bitstream).
   Apply the DRC override if NSTD-1/UCIO-1 reappear on the floating
   tmds_*/ddc_* ports (set SEVERITY Warning).
4. **File ▸ Export ▸ Export Hardware** ▸ Include bitstream → overwrite
   `bitstreams/cgra_top.xsa`.
5. Re-test DDR on silicon: load .xsa via xsct, `mwr 0x100000 0xDEADBEEF`
   then `mrd 0x100000` → must read back 0xDEADBEEF. Then fire B1-B6.

The DDR board-trace delays are ALREADY in the BD, so the GUI build will
emit a ps7_init with the correct distinct per-lane DDR PHY values.
