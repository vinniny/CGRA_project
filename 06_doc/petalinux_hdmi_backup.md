# PetaLinux HDMI backup path (PYNQ-Z2)

Backup plan for HDMI on PYNQ-Z2 in case the Vivado-2024.1 clean rebuild via
`scripts/build_cgra_hdmi_pynqz2_clean.tcl` stalls. Builds on a known-working
artifact: the Embedfire/Haoyue Zynq-7020 PetaLinux 2023.1 image whose XSA,
device tree, and userspace `hdmi-demo` produced live HDMI + CGRA on the same
PS7 (proven 2026-04). Companion to `06_doc/board_petalinux_guide.md`.

## Why this path is plausible

1. **Same silicon.** Both boards use XC7Z020 — only PS clock (Haoyue 33.333 MHz
   vs PYNQ-Z2 50 MHz) and DDR part differ. The HDMI BD itself is purely PL.
2. **Custom HDMI TX IP is portable RTL.** `XSA create/ip_repo/hdmi_transmitter`
   is just `OBUFDS TMDS_33` + DVI 1.0 encoder + 10:1 OSERDESE2 serializer —
   no board-specific logic. The same Verilog elaborates fine on PYNQ-Z2 once
   pin LOCs and port names are remapped (see deltas table below).
3. **Userspace driver, no DRM/KMS.** `hdmi-demo` mmaps DYNCLK/VTC/VDMA via
   `/dev/mem`. Linux never binds those IPs, so no kernel-side breakage from
   compat strings or version drift.
4. **CGRA accessed via UIO.** `cgra_main_0` uses `compatible = "generic-uio"`,
   which is the path our driver code (`07_sw/driver/cgra_driver.c`) already
   targets.

## Staged artifacts in this repo

- `07_sw/dts/petalinux_haoyue/` — proven device tree (`pl.dtsi`,
  `pcw.dtsi`, `system-top.dts`, `system-user.dtsi`) + Haoyue XDC
  (`cgra_ps_haoyue.xdc`) for reference. README.md lists per-file deltas.
- `07_sw/linux/hdmi_demo/files/` — userspace driver (≈600 LOC: hdmi-demo.c,
  mmio_util, dynclk, vtc, vdma + headers + Makefile)
- `07_sw/linux/hdmi_demo/petalinux/hdmi-demo.bb` — Yocto recipe
- Original archive (Windows host): `/mnt/c/Users/thanh/Desktop/petalinux files/`

## Address map — Haoyue vs current PYNQ-Z2 SD card

⚠️ **DynClk and CGRA are swapped between the two BDs.** Always re-derive from
the actual XSA. The on-card DTS (saved as
`07_sw/dts/petalinux_haoyue/sdcard_system_2026_05_10.dts`, decoded from
`/mnt/e/system.dtb`) is authoritative for the current PYNQ-Z2 build:

| Block | Haoyue (XSA proven 2026-04) | PYNQ-Z2 (`/mnt/e/system.dtb`, 2026-05-10) | IRQ | Notes |
|---|---|---|---|---|
| axi_vdma_0 | 0x4300_0000 | 0x4300_0000 | SPI 29 | 24-bit RGB MM2S; PYNQ build has `xlnx,num-fstores = <3>` (Haoyue: 1) |
| axi_dynclk_0 | 0x43C0_0000 | **0x43C1_0000** | — | Digilent dynamic pixel clock |
| cgra_top | 0x43C1_0000 | **0x43C0_0000** | SPI 31 (Haoyue) / **none on PYNQ-Z2 DT** | CGRA APB |
| v_tc_0 | 0x43C2_0000 | 0x43C2_0000 | SPI 30 | Xilinx Video Timing Controller (generator) |
| Framebuffer | 0x1F00_0000, 8 MiB | 0x1F00_0000, 8 MiB | — | Reserved via `system-user.dtsi`; correct on both |

`07_sw/linux/hdmi_demo/files/platform_config.h` now selects between the
two via `-DBOARD_HAOYUE` / `-DBOARD_PYNQ_Z2` (defaults to PYNQ-Z2).

## Pin / port deltas (Haoyue → PYNQ-Z2)

| Signal | Haoyue (cgra_ps_haoyue.xdc) | PYNQ-Z2 (constrs_pynq_z2.xdc) |
|---|---|---|
| `tmds_clk_p` | V20 | L16 |
| `tmds_clk_n` | (auto-pair) | L17 |
| `tmds_data_p[0]` | W14 | K17 |
| `tmds_data_p[1]` | Y16 | K19 |
| `tmds_data_p[2]` | Y18 | J18 |
| TMDS IOSTANDARD | TMDS_33 | TMDS_33 (same) |
| Port name in BD wrapper | `hdmi_tmds_0_tmds_*` | `hdmi_tx_*` |

**Action in Vivado:** Source the existing Haoyue BD verbatim
(`cgra_SoC_main`), then in the BD top-level rename the HDMI TX TMDS ports to
`hdmi_tx_clk_p/n` and `hdmi_tx_d_p/n[2:0]` so they pair with our existing
`01_bench/constrs_pynq_z2.xdc`. Add the Haoyue `cgra_ps_haoyue.xdc` content
**only** as a reference; the canonical XDC is the PYNQ-Z2 one.

## Build sequence (PetaLinux 2023.1)

Source: extracted from
`/mnt/c/Users/thanh/Desktop/petalinux files/Petalinux setup flow & Jupyter Notebook.docx`,
condensed and PYNQ-Z2-adjusted.

### One-time host setup

```bash
# Install PetaLinux 2023.1 (downloaded from xilinx.com archive)
sudo mkdir -p /opt/petalinux-tools && sudo chown -R $USER /opt/petalinux-tools
chmod +x petalinux-v2023.1-05012318-installer.run
./petalinux-v2023.1-05012318-installer.run --dir /opt/petalinux-tools/   # Accept EULA: ENTER q y q y
sudo apt install libtinfo5
sudo dpkg-reconfigure dash      # choose "No" (use bash, not dash)
echo "source /opt/petalinux-tools/settings.sh" >> ~/.bashrc

# Optional: pre-fetched offline caches (~10x faster build)
mkdir ~/petalinux_offline
tar -xzf sstate_arm_2023.1_05010539.tar.gz   -C ~/petalinux_offline
tar -xzf download_2023.1_05010539.tar.z      -C ~/petalinux_offline
```

### Per-XSA build

```bash
mkdir -p ~/workspace/plnx_prj && cd ~/workspace/plnx_prj
petalinux-create -t project --template zynq -n cgra_pynqz2
cd cgra_pynqz2

# Import the PYNQ-Z2 XSA (output of write_hw_platform after the BD bitstream)
petalinux-config --get-hw-description ~/CGRA_PYNQ/cgra_pynqz2.xsa
# In the menu:
#   Subsystem AUTO Hardware Settings -> Ethernet Settings -> [*] Obtain IP automatically (or set static)
#   Image Packaging Configuration    -> Root filesystem type -> EXT4 (SD/eMMC/SATA/USB)
#   Yocto Settings -> Add pre-mirror url: file:///home/$USER/petalinux_offline/downloads
#                  -> Local sstate feeds settings: /home/$USER/petalinux_offline/arm
#                  -> [*] Enable Network sstate feeds  (leave on; fills gaps)

# Edit device tree
petalinux-config -c device-tree     # opens menuconfig; just save+exit to materialize files
cp $CGRA_ROOT/07_sw/dts/petalinux_haoyue/system-user.dtsi project-spec/meta-user/recipes-bsp/device-tree/files/
# Adjust system-user.dtsi if the PYNQ-Z2 BD landed CGRA at 0x43C80000:
#   &cgra_main_0 { reg = <0x43c80000 0x10000>; };
# (override on top of pl.dtsi, do NOT modify the auto-generated pl.dtsi)

# Drop in the hdmi-demo recipe
mkdir -p project-spec/meta-user/recipes-apps/hdmi-demo/files
cp $CGRA_ROOT/07_sw/linux/hdmi_demo/petalinux/hdmi-demo.bb project-spec/meta-user/recipes-apps/hdmi-demo/
cp $CGRA_ROOT/07_sw/linux/hdmi_demo/files/* project-spec/meta-user/recipes-apps/hdmi-demo/files/

# Enable the recipe in rootfs config
petalinux-config -c rootfs
#   apps -> [*] hdmi-demo
#   (optional: Filesystem Packages -> Image Features -> [*] debug-tweaks for root login)

petalinux-build                                              # ~30 min cold, ~5 min with sstate
petalinux-package --boot --fsbl --fpga --u-boot --force      # produces images/linux/BOOT.BIN
```

### SD card layout (pulled together by hand — petalinux-package does not do this)

```bash
# Two partitions: sdb1 = FAT32 1 GiB labeled "boot", sdb2 = ext4 rest labeled "rootfs"
sudo umount /dev/sdb*
sudo wipefs -a /dev/sdb
sudo fdisk /dev/sdb            # n p 1 +1G ; n p 2 default ; t 1 c ; w
sudo mkfs.fat -F 32 -n boot   /dev/sdb1
sudo mkfs.ext4         -L rootfs /dev/sdb2

# Mount, copy, unmount
sudo mkdir -p /media/$USER/boot /media/$USER/rootfs
sudo mount /dev/sdb1 /media/$USER/boot
sudo mount /dev/sdb2 /media/$USER/rootfs

cp images/linux/BOOT.BIN              /media/$USER/boot/
cp images/linux/boot.scr              /media/$USER/boot/
cp images/linux/image.ub              /media/$USER/boot/        # alternative to zImage+dtb path
# OR (the Haoyue flow used split files):
mkdir -p /media/$USER/boot/{kernel,dtb}
cp images/linux/zImage                /media/$USER/boot/kernel/
cp images/linux/system.dtb            /media/$USER/boot/dtb/system-top.dtb

# uEnv.txt (lives in FAT partition, read by U-Boot's distro_bootcmd)
cat > /tmp/uEnv.txt <<'EOF'
bootargs=console=ttyPS0,115200 root=/dev/mmcblk0p2 rw rootwait ip=dhcp uio_pdrv_genirq.of_id=generic-uio
uenvcmd=run set_bootargs
set_bootargs=setenv bootargs ${bootargs}
EOF
sudo cp /tmp/uEnv.txt /media/$USER/boot/

sudo tar -xzf images/linux/rootfs.tar.gz -C /media/$USER/rootfs/
sync
sudo umount /media/$USER/boot /media/$USER/rootfs
```

## Runtime checklist on PYNQ-Z2

After SD boot:

```bash
# Hardware sanity
ls /sys/class/uio/uio*/name           # expect at least cgra (uio0 typically)
dmesg | grep -i uio                   # look for "uio_pdrv_genirq" probe
cat /proc/device-tree/reserved-memory/framebuffer@1f000000/reg | xxd | head -1
                                       # confirm 0x1f000000, 0x800000

# HDMI bring-up
hdmi-demo                              # writes color bars, returns 0 on success
echo $?                                # must be 0; non-zero means dump_regs() printed before exit
```

If `hdmi-demo` fails, check `dump_regs` output for which stage tripped:
- `dynclk status` LSB clear → DynClk PLL didn't lock; verify FCLK1 is enabled
  (`fclk-enable = <0x3>` in `pcw.dtsi`) and clock-frequency for `misc_clk_0`
  in `pl.dtsi` matches your design.
- `vtc status` zero → VTC RU/SW bits not latched; check the BD wired
  `s_axi_aclk` to FCLK0.
- `vdma sr` ERR_ALL bits set → VDMA can't read FB; confirm framebuffer
  reserved-memory region didn't get carved up by other reservations.

## Boot-time autostart

`/etc/init.d/hdmi-demo-init` (sysVinit-style; PetaLinux uses sysvinit by
default):

```sh
#!/bin/sh
### BEGIN INIT INFO
# Provides:          hdmi-demo-init
# Required-Start:    $local_fs
# Default-Start:     5
### END INIT INFO
case "$1" in
    start|restart)
        sleep 2
        /usr/bin/hdmi-demo >> /var/log/hdmi-demo.log 2>&1
        ;;
esac
exit 0
```

Then on the target:
```bash
chmod +x /etc/init.d/hdmi-demo-init
ln -sf ../init.d/hdmi-demo-init /etc/rc5.d/S99hdmi-demo-init
```

## Current SD card state (`/mnt/e`, snapshot 2026-05-10 14:33)

The FAT boot partition is mounted at `/mnt/e` (the ext4 rootfs is not
mounted in WSL2). Files present:

```
BOOT.BIN     5,227,956 B   2026-05-10 14:33  (FSBL + bitstream + U-Boot)
boot.scr     3,830 B       2026-05-09 10:53  (legacy uImage script wrapper)
system.dtb   20,978 B      2026-05-10 14:33  (compiled today)
uImage       5,039,528 B   2026-05-09 10:53  (Linux 6.12.10-xilinx, built 2025-05-17)
```

`system.dtb` decodes as `compatible = "tul,pynq-z2","xlnx,zynq-7000"` /
`model = "PYNQ-Z2 + CGRA + HDMI"` — the PYNQ-Z2 build, not Haoyue. Key
runtime properties:

- HDMI IPs (vdma, dynclk, vtc) all `status = "disabled"` — intentional, so
  the in-tree Xilinx drivers do not bind. Userspace `/dev/mem` access is
  unaffected by status="disabled".
- `cgra_top@43c00000` is `compatible = "generic-uio"`, `status = "okay"`,
  but **no `interrupts` property** — IRQ delivery to userspace is not wired.
  Compare Haoyue: `interrupts = <0 31 4>`. If you need the CGRA IRQ on
  PYNQ-Z2 you must add it to `system-user.dtsi`.
- bootargs: `console=ttyPS0,115200 earlycon earlyprintk root=/dev/mmcblk0p2 rw rootwait uio_pdrv_genirq.of_id=generic-uio clk_ignore_unused`
  — `clk_ignore_unused` is on (was tried in V165). Keep this.
- DDR memory: `reg = <0x0 0x20000000>` = 512 MiB. PYNQ-Z2 correct.
- Kernel 6.12.10 implies this image is **not** PetaLinux 2023.1 (which
  ships 5.15) — likely 2024.2 or 2025.1. The setup .docx commands are
  version-compatible at the petalinux-* level but Yocto layer paths and
  default rootfs may differ.

The decoded DTS is preserved at
`07_sw/dts/petalinux_haoyue/sdcard_system_2026_05_10.dts`.

### Live test 2026-05-10 18:10 — bitstream has the V162-V169 AXI hang

SSH login as `petalinux@10.39.20.228` succeeded. FPGA fabric reports
operating, `/proc/device-tree/reserved-memory/framebuffer@1f000000` is
present, uio0 binds to `cgra_top@43c00000` at probe (metadata only).

**`sudo /tmp/diag_hdmi.sh` froze the kernel at the first `devmem` read of
0x43000000 (VDMA APB).** Hard power-cycle required.

This is the same signature as V162-V169: PL configures, UIO probes
succeed, but any userspace AXI access via `/dev/mem` deadlocks the
GP0→PL fabric. Cause is on the **bitstream** side (unbacked AXI slave or
stale `axi_interconnect:2.1` AxPROT cache), **not** on the PetaLinux
side. The PetaLinux build is correct; the BD packaged into this BOOT.BIN
is not.

**Until a fresh XSA from `build_cgra_hdmi_pynqz2_clean.tcl` (Vivado
2024.1, smartconnect:1.0 on HP) is available, do not run any /dev/mem
probes on this SD card** — every probe attempt costs a power-cycle and
gives zero new information.

## Decision matrix — when to switch to this path

Switch from the Vivado-2024.1 clean-rebuild path to this PetaLinux path if any
of these holds after a sensible amount of effort on the primary path:

- `build_cgra_hdmi_pynqz2_clean.tcl` synthesizes but `hdmi_tx_*` ports
  remain unconnected post-validate (port-naming dance fails again).
- `axi_vdma` or `v_tc` Linux drivers refuse to bind on PYNQ-Z2 PetaLinux
  build (compat-string version drift in 2023.1 vs whatever Vivado 2024.1
  emits).
- The combined LUT count for `cgra_top + axi_vdma + axi_dynclk +
  hdmi_transmitter + v_tc` plus PYNQ base IOPs busts the XC7Z020 53,200-LUT
  budget after `strip_pynq_iops.tcl` (then we abandon "PYNQ base + bolt-on"
  and rebuild a minimal BD using the Haoyue recipe).

In all three cases the staged artifacts here let us rebuild from the
silicon-proven recipe rather than restarting from zero.
