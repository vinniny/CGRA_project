# Session paused — 2026-05-28 ~20:10

## Where we left off

Silicon path debugging on PYNQ-Z2 hit a DDR-controller misconfig after
the crystal=50 BD fix (commit `fb94e59`). The new ps7_init programs the
DDR controller with timing parameters that don't match the canonical
PYNQ-Z2 chip (MT41K256M16 RE-125 at 533 MHz), so DDR3 silently drops
writes (`mwr 0x100000 0xDEADBEEF` → reads back 0).

## Current artifacts

- `bitstreams/cgra_top.xsa` — **broken** (MD5 `f34ca0f6…`, crystal-fix
  but DDR dead). Smoke S0+S1 pass; B1 mac_micro hangs because
  `cgra_config_pe` DMAs from DDR which is broken.
- `bitstreams/cgra_top.bit` — backup, MD5 `1c26853b…`.
- `bench_mac_micro.elf` — DDR_STAGE reverted to `0x00100000` (DDR-side).
  Hangs until DDR is fixed.

## Diagnosis chain (confirmed)

1. Smoke ELF S0 → reads `ARM_PLL_CTRL = 0x0001B008` → FBDIV = 27 →
   ARM PLL = 50 × 27 = 1350 MHz ✅ (crystal fix landed correctly).
2. Smoke ELF S1 → CGRA APB ping-pong (DEADBEEF/CAFEBABE) passes ✅.
3. Direct PS-side mwr to `0x100000+` reads back 0 ❌ — DDR broken.
4. `cgra_config_pe` uses DMA from DDR staging → hangs (`CU_STATUS=0x1`
   forever, `CU_CYCLES=1.84B`).
5. Manual xsct test: OCM-source DMA `0x20000 → 0x20000000` succeeds
   (`status=2`, `error=0`, 65 ms). CGRA fabric itself is fine.
6. v8b: PYNQ-Z2 board_part found at
   `/mnt/d/Programs/Xilinx/2025.1/Vivado/data/boards/board_files/`
   but applying it locks the PS-7 IP (project `xc7z020clg400-1`
   vs board file `xc7z020clg400-2`).

## Pending Vivado fix (to resume)

`scripts/vivado_diagnostics/bd_apply_pynqz2_ddr_only.tcl` (v8c) +
`scripts/vivado_diagnostics/pynqz2_ddr_settings.tcl` (74 DDR settings
extracted from PYNQ-Z2 preset.xml):

```bash
cd /home/vinniny/centos_vm/projects/CGRA_project
source /tools/Xilinx/2025.1/Vivado/settings64.sh
vivado -mode batch -source scripts/vivado_diagnostics/bd_apply_pynqz2_ddr_only.tcl \
       -log /tmp/vivado_v8c_ddr_only.log -journal /tmp/vivado_v8c.jou
```

Approach:
- Skips `set_property board_part` to avoid IP lock.
- Applies 74 `PCW_UIPARAM_DDR_*` + `PCW_DDR_RAM_*` settings directly
  via `set_property -dict` on the PS-7.
- Keeps everything else (FCLK0=50 MHz, CGRA wiring) untouched.
- ETA ~30-40 min for full impl + .xsa export.

After v8c completes, the validation sequence is:
1. Power-cycle the PYNQ-Z2 board.
2. Re-test direct DDR write via xsct (`mwr 0x100000 0xDEADBEEF` →
   should read back `0xDEADBEEF`).
3. Run bench_smoke.elf → expect S0+S1 still pass.
4. Run bench_mac_micro.elf → expect MTP01/02/03 actual results
   (not TIMEOUT).
5. Proceed B1-B6 pillar sweep.

## Background-task hygiene

All processes terminated at session end:
- `bnum5witl` (v8c Vivado) — stopped via TaskStop.
- 3 zombie watcher shells killed (`b4zhiwdug`, `blonaidz8`, `bc7f42t6u`).
- UART monitor not running.

## Key files modified but uncommitted

- `06_doc/ddr_broken_post_crystal_fix.md` (created)
- `scripts/vivado_diagnostics/bd_fix_crystal.tcl` (older, may stay)
- `scripts/vivado_diagnostics/bd_apply_pynqz2_board_preset.tcl` (v8/v8b)
- `scripts/vivado_diagnostics/bd_apply_pynqz2_ddr_only.tcl` (v8c, next)
- `scripts/vivado_diagnostics/pynqz2_ddr_settings.tcl` (auto-gen)
- `06_doc/session_state_2026-05-28_paused.md` (this file)
- `02_log/uart_pillar_B1_mac_micro.log`, `02_log/uart_pillar_B1_ocm.log`,
  `02_log/uart_smoke_postfix.log` (probe data, may be useful)
- `07_sw/baremetal/bench_mac_micro.c` — reverted to DDR_STAGE=0x00100000
  (was temporarily 0x00030000 during OCM diagnostic).
