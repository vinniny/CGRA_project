# PetaLinux Preparation: PYNQ-Z2 vs Haoyue 7020

Both boards use the same XC7Z020 die, so the CGRA RTL bitstream is
**directly portable**. The differences are PS clock, DDR chip, and
board peripherals.

---

## Board Comparison

| Parameter | Haoyue (Wildfire 皓月) | PYNQ-Z2 |
|---|---|---|
| FPGA | XC7Z020-2CLG400I | XC7Z020-1CLG400C |
| PS Clock | **33.333 MHz** | **50 MHz** |
| DDR | 1 GB DDR3 × 2 (MT41K256M16TW-107) | 512 MB DDR3 (MT41K512M16HA-125) |
| DDR part (Vivado) | `MT41K256M16 RE-125` | `MT41K512M16 RE-125` |
| UART MIO | MIO14 (RX) / MIO15 (TX) @ 115200 | MIO14 (RX) / MIO15 (TX) @ 115200 |
| Boot mode | DIP switch MIO4/MIO5 | JP1 jumper |
| Ethernet PHY | 2× RTL8211E (1 PS, 1 PL) | 1× RTL8211E |
| USB | 4× HOST + 1× SLAVE + 1× USB-UART | 1× USB-UART (FTDI) |
| HDMI | Yes (1080p@60Hz) | Yes (in+out) |
| QSPI Flash | W25Q128JV (16 MB) | W25Q80BV (4 MB typical) |
| PS LEDs | MIO0, MIO9 | — |
| PS Buttons | MIO50, MIO51 | — |
| PL LEDs | K16/J16/K14/J14 | R14/P14/N16/M14 (from XDC) |
| Board files URL | — | http://www.tul.com.tw/download/pynq-z2.zip |

**Key CGRA project impact:** UART MIO assignments are **identical** on
both boards, so `uart.h` (baud divisors) only needs recalculation for
the different PS clock on PYNQ-Z2.

---

## UART Baud Divisors

UART baud rate = PS_CLK / (CD × (BDIV + 1) × 8)

| Board | PS_CLK | Target | CD | BDIV |
|---|---|---|---|---|
| Haoyue | 33.333 MHz | 115200 | 62 | 6 | 
| PYNQ-Z2 | 50 MHz | 115200 | 93 | 6 |

In `07_sw/baremetal/uart.h`, change the `UART_BAUD_*` constants when
building for PYNQ-Z2. The register addresses (UART0 = 0xE0000000) are
the same.

---

## ps7_init.tcl

This file is **board-specific** — the PLL divisors depend on PS_CLK.

| File version | PLL register 0xF8000110 | Board |
|---|---|---|
| Committed HEAD | `0x000FA220` | Haoyue (33.333 MHz) |
| Current working tree | `0x001772C0` | PYNQ-Z2 (50 MHz) |

**Workflow:**
- Haoyue build → `make pull_all` from Haoyue Vivado project → commit
- PYNQ-Z2 build → `make pull_all` from PYNQ-Z2 Vivado project → separate commit/branch

Keep both checked in, or use a `BIT_BOARD=` make variable to select.

---

## Vivado Project Differences

### PYNQ-Z2
1. Install board files: extract `pynq-z2.zip` into
   `<Vivado install>/data/boards/board_files/pynq-z2/`
2. Create project → select board "PYNQ-Z2 (TUL)"
3. Block design → Zynq PS → Re-customise:
   - PS-PL AXI GP0 enable (CGRA control @ 0x43C00000)
   - UART0 on MIO14/15
   - SD0 on MIO40-47 (for PetaLinux boot)
   - GbE on MIO16-27 (optional)
   - DDR: MT41K512M16 RE-125
4. Add CGRA top as AXI peripheral, connect S_AXI_GP0
5. Generate bitstream → Export XSA (include bitstream)
6. `make pull_all` to stage bitstream + ps7_init.tcl + .hwh

### Haoyue 7020
Same flow. DDR part: `MT41K256M16 RE-125`. No pre-made board file —
set PS clock source = Single-ended clock capable pin, frequency = 33.333 MHz.

---

## PetaLinux Build Flow

```bash
# 1. Create project (run once per board)
petalinux-create --type project --template zynq --name cgra_petalinux

# 2. Import XSA from Vivado
cd cgra_petalinux
petalinux-config --get-hw-description=<path-to-xsa>

# 3. Key settings in petalinux-config TUI
#    Subsystem AUTO Hardware Settings → Memory Settings
#      PYNQ-Z2:  Base = 0x00000000, Size = 0x20000000  (512 MB)
#      Haoyue:   Base = 0x00000000, Size = 0x40000000  (1 GB)
#    Subsystem AUTO Hardware Settings → Serial Settings
#      Primary STDIN/STDOUT = psu_uart_0 (MIO14/15 on both boards)
#    Image Packaging Configuration → Root filesystem type
#      = EXT4 (SD/eMMC)  ← for SD card boot
#      or INITRD          ← for standalone initramfs

# 4. Configure kernel (optional — enable UIO + CMA for CGRA driver)
petalinux-config -c kernel
#    Device Drivers → Userspace I/O drivers → Userspace I/O platform driver
#    Device Drivers → Generic Driver Options → DMA Contiguous Memory Allocator

# 5. Build
petalinux-build

# 6. Package SD card image
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf \
                  --fpga  ./images/linux/system.bit \
                  --u-boot

# SD card layout:
#   FAT32 partition: BOOT.BIN, image.ub (or boot.scr + uImage + system.dtb)
#   EXT4 partition:  rootfs
```

---

## Device Tree: CGRA Custom IP

Add to `project-spec/meta-user/recipes-bsp/device-tree/files/system-user.dtsi`:

```dts
/ {
    amba_pl: amba_pl {
        #address-cells = <1>;
        #size-cells = <1>;
        ranges;

        /* CGRA APB control — AXI GP0 @ 0x43C00000 */
        cgra@43c00000 {
            compatible = "generic-uio";
            reg = <0x43C00000 0x10000>;
            interrupt-parent = <&intc>;
            interrupts = <0 29 4>;   /* IRQ 61 = SPI[29], level-high */
        };
    };
};

/* CMA pool for DMA (256 MB) */
&{/} {
    reserved-memory {
        #address-cells = <1>;
        #size-cells = <1>;
        ranges;
        cma_pool: linux,cma {
            compatible = "shared-dma-pool";
            reusable;
            size = <0x10000000>;    /* 256 MB */
            alignment = <0x1000>;
            linux,cma-default;
        };
    };
};
```

This exposes the CGRA as `/dev/uio0` for the `07_sw/driver/` UIO driver,
identical on both boards since the AXI GP0 address map is the same.

---

## Boot Mode DIP/Jumper Settings

### Haoyue — DIP switch (MIO4, MIO5)
| Mode | MIO4 | MIO5 |
|---|---|---|
| JTAG | 0 | 0 |
| QSPI Flash | 0 | 1 |
| **SD Card** | **1** | **1** |

### PYNQ-Z2 — JP1 jumper
| Mode | JP1 |
|---|---|
| JTAG | open |
| QSPI | pins 1-2 |
| **SD Card** | **pins 2-3** |

---

## CGRA IRQ Mapping (same on both boards)

The CGRA `irq` output connects to `IRQ_F2P[0]` in the Zynq PS block design.

| Signal | Zynq GIC SPI | Linux interrupt | GIC register offset |
|---|---|---|---|
| IRQ_F2P[0] | SPI 61 (ID 93) | `interrupts = <0 29 4>` | SPI[29] |

`gic.c` in the baremetal regression targets distributor 0xF8F01000 and
CPU interface 0xF8F00100 — **unchanged on both boards** (hardcoded in
Zynq silicon).

---

## Makefile Variables to Add

```makefile
# Board selection — affects which ps7_init.tcl and XDC to use
BOARD ?= haoyue      # or pynq-z2

ifeq ($(BOARD),pynq-z2)
  VIVADO_PROJECT = /mnt/c/Users/thanh/Desktop/FPGA_CGRA_PYNQ/
  DDR_SIZE       = 512
else
  VIVADO_PROJECT = /mnt/c/Users/thanh/Desktop/FPGA_CGRA/
  DDR_SIZE       = 1024
endif
```
