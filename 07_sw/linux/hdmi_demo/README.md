# hdmi-demo — userspace HDMI driver (PetaLinux backup path)

## Provenance

Verbatim copy of the working hdmi-demo recipe used on the Embedfire/Haoyue
Zynq-7020 board (project at `cgra_SoC_main.bd`). Source archive:
`/mnt/c/Users/thanh/Desktop/petalinux files/Driver (For petalinux)/hdmi-demo/`.
Silicon-validated on Haoyue 2026-04 (CGRA + HDMI co-resident on the same PS7,
HP0 + HP1 with two `smartconnect:1.0` blocks).

This is staged here as the **PetaLinux backup path** for HDMI on PYNQ-Z2 in
case the Vivado-2024.1 / `build_cgra_hdmi_pynqz2_clean.tcl` rebuild stalls.

## Layout

- `files/` — userspace C app sources (compile to `/usr/bin/hdmi-demo` on target)
  - `hdmi-demo.c`, `mmio_util.[ch]`, `dynclk.[ch]`, `vtc.[ch]`, `vdma.[ch]`,
    `lcd_modes.h`, `platform_config.h`, `Makefile`
- `petalinux/` — PetaLinux Yocto recipe
  - `hdmi-demo.bb` — BitBake recipe (drop into
    `project-spec/meta-user/recipes-apps/hdmi-demo/hdmi-demo.bb`)
  - `README.txt` — original Digilent README (UIO/dmesg checks)
- See also `07_sw/dts/petalinux_haoyue/` for the matching device tree
  (`pl.dtsi`, `pcw.dtsi`, `system-top.dts`, `system-user.dtsi`) and the Haoyue
  XDC (`cgra_ps_haoyue.xdc`).

## How it works

1. `system-user.dtsi` reserves an 8 MiB framebuffer at `0x1F000000`
   (`hdmi_fb0`), sets `cgra_main_0` to `generic-uio`, and leaves `axi_dynclk`,
   `axi_vdma_0`, and `v_tc_0` with their stock Xilinx compatibles — no
   in-kernel driver binds them, so userspace owns them via `/dev/mem`.
2. `hdmi-demo.c` `mmap`s DYNCLK/VTC/VDMA/framebuffer, fills the FB with an
   RGB color bar, programs the Digilent dynamic pixel clock (640×480@60 by
   default; 800×600/1024×600/1024×768/1280×720 also available in `lcd_modes.h`),
   configures the Xilinx VTC generator, and starts VDMA MM2S in direct
   register mode (no SG-DMA descriptors).
3. CGRA is reachable via `/dev/uio*` (whichever name binds to `cgra_main_0`).

## PYNQ-Z2 deltas (vs the Haoyue source)

The recipe is portable; the only changes on PYNQ-Z2 are at the BD/XDC layer
and (possibly) at the address map. Concretely:

| Item | Haoyue | PYNQ-Z2 |
|---|---|---|
| HDMI TX TMDS pins | V20 / W14 / Y16 / Y18 (cgra_ps.xdc) | L16/L17, K17/K18, K19/J19, J18/H18 (`01_bench/constrs_pynq_z2.xdc`) |
| HDMI TX port names | `hdmi_tmds_0_tmds_clk_p/n`, `hdmi_tmds_0_tmds_data_p/n[2:0]` | `hdmi_tx_clk_p/n`, `hdmi_tx_d_p/n[2:0]` |
| Board preset | Embedfire ZYNQ (`xlnx,zynq-khoi`) | TUL PYNQ-Z2 |
| HDMI TX IP (custom RTL) | `hdmi_transmitter` (Embedfire, in `XSA create/ip_repo/`) — pure portable RTL: OBUFDS TMDS_33 + DVI 1.0 encoder + 10:1 OSERDESE2 | Same custom RTL **works as-is** (TMDS_33 is bank-IO standard, not board-specific). Only the wrapper port names + LOC constraints change. |
| AXI VDMA addr | 0x4300_0000 | 0x4300_0000 (keep) |
| AXI VDMA addr (8-bit) | 0x4301_0000 | not needed for first-light |
| DynClk addr | 0x43C0_0000 | 0x43C0_0000 (keep) |
| CGRA APB addr | 0x43C1_0000 | **0x43C8_0000** if combined with `bootstrap_pynq_base_cgra.tcl` (PYNQ base BD assigned the next free slot above `hdmi_in/color_convert`); 0x43C1_0000 if rebuilt in a clean BD. |
| VTC addr | 0x43C2_0000 | 0x43C2_0000 (keep) |
| Framebuffer reservation | 8 MiB @ 0x1F00_0000 | 8 MiB @ 0x1F00_0000 (keep — well below 512 MiB DDR limit) |

If CGRA APB lands at `0x43C8_0000` (PYNQ-base bolt-on path), update
`pl.dtsi` `cgra_main_0` `reg = <0x43c80000 0x10000>;` and rebuild
`07_sw/baremetal/cgra.h` / `07_sw/driver/cgra_driver.h` with
`-DBOARD_PYNQ_BASE` (already supported per
`memory/project_pynq_base_bolt_on.md`).

`platform_config.h` does not need changes for first-light because it pins the
HDMI IP base addresses, which we keep identical between Haoyue and PYNQ-Z2.

## Build & flash

See `06_doc/petalinux_hdmi_backup.md` for the full PetaLinux-2023.1 sequence
(petalinux-create → --get-hw-description → DTS edit → rootfs config →
petalinux-build → BOOT.BIN packaging → SD-card layout). The proven recipe is
in the .docx at
`/mnt/c/Users/thanh/Desktop/petalinux files/Petalinux setup flow & Jupyter Notebook.docx`.
