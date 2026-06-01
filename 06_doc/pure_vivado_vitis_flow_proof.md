# Pure Vivado→Vitis flow — end-to-end silicon proof (2026-06-01)

Goal: prove the textbook Vivado→Vitis flow works perfectly, with every
artifact produced by the official tools (no hand-rolled bitstream/ps7_init).

## The chain (all tool-generated)
1. **Vivado** → `write_hw_platform -fixed -include_bit` → `bitstreams/cgra_top.xsa`
   (v18, MD5 ca3dbd5e; DDR=PARTNO Custom + REF trace delays, FCLK0=50, WNS +2.57 ns).
2. **Vitis** `platform create -hw cgra_top.xsa` + `platform generate`
   → auto-generates BSP + `ps7_init.{c,tcl}` + extracts the bitstream.
3. **Vitis** `app create` (Empty Application C) + import sources + `app build`
   → the application `.elf`.
4. **Hardware run** via the Vitis-generated `_ide/psinit/ps7_init.tcl` +
   `_ide/bitstream/cgra_top.bit` + `Debug/<app>.elf` (xsct = what Vitis
   "Launch on Hardware" does under the hood: fpga -file + ps7_init + dow + con).

Build recipe: `scripts/vitis_build_demo.tcl` (generic) and
`scripts/vitis_build_mnist_proof.tcl` (MNIST, handles the `../cnn_eval/`
header + `.incbin` weight blobs via a sibling dir + assembler `-I`).
Launch: `scripts/vitis_launch_autohw.tcl` (bare `connect`, auto hw_server).

## Results on silicon (PYNQ-Z2)
| Vitis app | result |
|---|---|
| `ddr_stress` (37 KB) | 64 MB DDR march — T1 addr-in-addr, T2 walking-bits, T3 patterns, T4 inc — **ALL PASS, 0 errors** |
| `mnist_perstage` (463 KB, embedded weights) | full CGRA CNN inference — **CGRA 87/100, ARM-INT 94/100** |

Both produced by the official Vivado+Vitis tools end-to-end. MNIST accuracy
is identical to every prior run, confirming the canonical artifact + flow
are correct. This is the functional gate (MNIST argmax accuracy), not the
bench_mac_micro contribs readout (a result-FIFO artifact).

## Windows GUI note
The Windows recreation is the same flow via the Vitis IDE GUI
(Platform Component from .xsa → Application Component → Build → Run on
Hardware). See `06_doc/windows_gui_recreation_recipe.md`. Do NOT use the
Vivado pynq-z2 board preset for DDR; use PARTNO=Custom + the REF delays.

---

## Canonical demo numbers — Vitis Empty-App, caches-OFF, FCLK0=50 (2026-06-01)

Decision: the **Vitis Empty-Application build is the canonical reference** for
defense (matches the live board exactly). The Vitis launch resets the A9 to
caches-OFF deterministically, so every run is reproducible. (The earlier
"combo" numbers were ~6× faster only because a prior ELF had left caches ON —
not a controlled measurement.) Methodology statement for the thesis:
**"caches disabled — raw-HW + on-chip-SPM measurement; APU 650 MHz, FCLK0 50 MHz."**

`mnist_demo` (per-stage, two-pass), reproducible to <0.02 % jitter:

| stage (per inference) | cycles @650 MHz | time |
|---|---|---|
| Conv2+ReLU (VFP, ARM) | 53.1 M | 81.7 ms |
| **ROW FC total — ARM-INT** | 13.34 M | 20.53 ms |
| **ROW FC total — CGRA** | 1.73 M | **2.66 ms** |
| end-to-end (VFP conv + CGRA FC) | 106.8 M | 164.3 ms |
| **CGRA-FC speedup vs ARM-INT-FC** | — | **7.72×** |
| Accuracy | ARM-INT 94/100, **CGRA 87/100** | |

Build (identical Linux xsct / Windows xsct.bat — the GUI recipe):
```
xsct scripts/vitis_build_mnist_demo.tcl          # platform + app from cgra_top.xsa
# then run:
CGRA_XSA_DIR=<ws>/mnist_demo/_ide \
CGRA_BIT=<ws>/mnist_demo/_ide/bitstream/cgra_top.bit \
CGRA_ELF=<ws>/mnist_demo/Debug/mnist_demo.elf \
xsct scripts/vitis_launch_autohw.tcl
```
GUI equivalent: Platform Component from cgra_top.xsa → Application Component
(Empty Application C) → import 07_sw/baremetal sources + a sibling cnn_eval/
folder with the 3 weight files → set linker_cnn.ld, defines BOARD_CGRA_ONLY +
TWO_PASS_PMU=1, assembler -I<src> → Build → Run on Hardware.
