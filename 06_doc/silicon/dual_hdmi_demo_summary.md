# Dual-HDMI CGRA MNIST Demo — Bring-up & Results (PYNQ-Z2)

Defense-ready summary of the live dual-HDMI demonstrator: HDMI-in capture →
CGRA MNIST inference → HDMI-out display, on a TUL **PYNQ-Z2 (XC7Z020-1)** via the
pure **Vivado → export `.xsa` → Vitis** flow. (2026-06; HDMI-OUT silicon-validated,
HDMI-IN build-complete & verified, hardware capture test pending.)

## 1. Architecture

```
 Laptop ──HDMI──> J10 (RX)                          J11 (TX) <──HDMI── Monitor
                   │                                    ▲
              dvi2rgb (TMDS→RGB, recovers PixelClk)     │ rgb2dvi (RGB→TMDS)
                   │ PixelClk (~148.5 MHz @1080p)        │ PixelClk 25.175 (640×480)
              v_vid_in_axi4s ─AXIS@200MHz─> axi_vdma_1   │ v_axi4s_vid_out <─ axi_vdma_0
                   (S2MM → DDR ring)                     │      (MM2S ← DDR framebuffer)
                                                         │   paced by v_tc_0 + axi_dynclk
                         DDR  ◀── ARM Cortex-A9 (650 MHz) ──▶  CGRA (50 MHz, APB+AXI-HP)
                                       └ MNIST: ARM-VFP Conv+Pool → CGRA-FC head
```

- Clocks (crystal **50 MHz**): FCLK0=50 (CGRA + AXI-lite), FCLK1=100 (dynclk ref),
  FCLK2=200 (dvi2rgb RefClk **+ HDMI-in capture AXIS**).
- DDR: REF UIPARAMs (PARTNO=Custom, BOARD_DELAY0=0.223) — NOT the pynq-z2 board
  preset (its 0.279 delays don't train DDR).
- Single reproducible build: `build_cgra_hdmi_pynqz2_clean.tcl` (OUT) +
  `add_hdmi_in_pynqz2.tcl` (IN), orchestrated by `hdmi_dual_build_p1/p2.tcl`.

## 2. Bring-up fix chain (each silicon- or build-verified)

| # | Symptom | Root cause | Fix |
|---|---------|-----------|-----|
| 1 | garbled UART, DDR fail, MMIO wedge | PS7 crystal defaulted 33.333 vs board 50 → 1.5× overclock | `PCW_CRYSTAL=50` |
| 2 | A9 AXI-hang in hdmi_init | `hdmi_bm.c` used old-BD addresses + nonexistent color_convert | dynclk→0x43C00000, drop FCLK0 override + hls_configure |
| 3 | VDMA DMADecErr | framebuffer 0x1F000000 at HP0 high-DDR edge | move FB → 0x10000000 |
| 4 | "no signal" (out) | rgb2dvi/v_axi4s_vid_out reset on 100M domain, not pixel clock | `proc_sys_reset_video` on PXL_CLK_O |
| 5 | (same) datapath gated | `aclken`/`vid_io_out_ce` floating | tie HIGH |
| 6 | **"no signal" — the key one** | VTC `clken`/`gen_clken` floating, `vtg_ce` unconnected → no genlock | `vtg_ce → v_tc/gen_clken + clken` (ILA-verified `locked` 0→1) |
| 7 | white→yellow stripes (blue lane) | rgb2dvi `kGenerateSerialClk=true` → CDC vs external PixelClk | `=false` + phase-coherent `PXL_CLK_5X_O` |
| 8 | yellow text shown purple | framebuffer G/B byte order | swap G/B in `hdmi_pixel` |
| 9 | **HDMI-in capture frozen** | capture AXIS @ FCLK0=50 MHz can't drain laptop 1080p60 (~124 Mpix/s) | reclock v_vid_in/subset/vdma s_axis → **FCLK2=200 MHz** (async FIFO from PixelClk) |
| 10 | −0.058 ns setup (200 MHz domain) | tight capture-clock timing | `Performance_ExploreWithRemap` → +0.112/+0.052 MET |

Diagnosis was done **headless on WSL** throughout: System ILA (driven via Vivado
`hw_manager` Tcl over JTAG) for the genlock `locked` bit; solid-colour DDR fills via
`xsct mwr` to isolate TMDS lanes; dvi2rgb's built-in debug ILAs to confirm RX lock.

## 3. Silicon results (HDMI-OUT demo, live)

Same `act400` (ARM-VFP Conv+Pool front end) into three FC implementations:

| FC implementation | mean cycles | speedup | accuracy (100-img sweep) |
|-------------------|-------------|---------|--------------------------|
| **CGRA-FC** (INT16 tiled) | 2,180,561 | **1.0×** | 86 / 100 |
| ARM-INT-FC (INT64)        | 17,292,252 | CGRA **7.93×** | 94 / 100 |
| ARM-VFP-FC (float)        |  8,644,381 | CGRA **3.96×** | 99 / 100 |

**Headline:** the CGRA accelerates the dense FC head **4–8× over ARM**, end-to-end
on silicon including DMA + readout overhead, at **86%** accuracy vs the 99% float
reference — a clear throughput/accuracy trade-off. (See `hdmi_demo_silicon_speedup.md`.)

## 4. Status & reproduction

- **HDMI-OUT**: fully working on silicon — clean 640×480, correct colours, MNIST UI
  + live CGRA/ARM cycle panels + speedup counter.
- **HDMI-IN**: bitstream + LIVE ELF build-complete and timing-met; the capture-clock
  reclock is in place. Hardware capture test pending a board session — steps in
  `hdmi_in_board_test_checklist.md`.
- **Reproduce on Windows GUI**: open the Vivado project, source the build scripts (or
  re-run p1/p2), `write_hw_platform -include_bit`, then Vitis platform+app from the
  `.xsa`. All fixes are baked into the scripts — no manual BD edits.
