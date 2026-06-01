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
