# Chapter 5 — Silicon Results

**Thesis supporting material.** Every number in this chapter is measured
on the PYNQ-Z2 (Xilinx Zynq-7020) target on the dates noted, with
artefacts checked into the repository for traceability.

## 5.1 Bitstream-build reproducibility (Vivado 2025.1)

A central thesis claim is that *the working bitstream can be regenerated
from a single source file by anyone with the right tool tree*. We
demonstrate this with **three additive procedures**, each documented
end-to-end in `06_doc/vivado_bitstream_build_procedure.md`:

| Procedure | Source(s) | Output bitstream |
|---|---|---|
| **A** — Rebuild baseline | `base.tcl` | `bitstreams/cgra_rebuilt_from_base.bit` |
| **B** — + Test pattern | `base.tcl` + `add_v_tpg_test_pattern.tcl` | `bitstreams/cgra_vtpg_test.bit` |
| **D** — + System ILA | A + B + `add_system_ila_to_vtpg.tcl` | `bitstreams/cgra_vtpg_ila.bit` |

Each orchestrator (`scripts/rebuild_bitstream_from_base.tcl`,
`build_v_tpg_test_bitstream.tcl`, `build_vtpg_ila_bitstream.tcl`) runs
`synth_1` + `impl_1` + `write_bitstream` headless. All three use the
**`Performance_ExploreWithRemap`** impl strategy, which closes timing
on the v_tpg HLS-internal critical path that defaults at -0.014 ns slack
under Vivado's `Vivado Implementation Defaults` strategy.

### 5.1.1 Post-route results

| Metric | A (baseline) | B (+ v_tpg) | D (+ v_tpg + ILA) |
|---|---|---|---|
| Slice LUTs | 40,330 / 53,200 = **75.81 %** | 42,965 / 53,200 = 80.76 % | 45,248 / 53,200 = 85.05 % |
| Slice Registers | 31,363 (29.48 %) | 34,827 (32.73 %) | 38,145 (35.85 %) |
| BRAM tiles | 44 (31.43 %) | 48.5 (34.64 %) | 52 (37.14 %) |
| DSPs | 165 (75.00 %) | 178 (80.91 %) | 178 (80.91 %) |
| **WNS** (timing slack) | **+0.344 ns** | +0.232 ns | **+0.309 ns** |
| WHS (hold) | +0.017 ns | +0.018 ns | +0.019 ns |
| Total on-chip power | 2.393 W | 2.489 W | 2.49 W |
| Dynamic / Static (W) | 2.223 / 0.170 | 2.319 / 0.170 | 2.32 / 0.170 |
| DRC errors | 0 | 0 | 0 |
| Timing constraints met | ✅ all | ✅ all | ✅ all |

Δ cost of inserting the test-pattern generator + 2 → 1 axis_switch
(Procedure B over A): **+2 635 LUTs (+5.0 pp), +13 DSPs, +0.10 W**.
Δ cost of adding the System ILA (Procedure D over B): **+2 283 LUTs,
+3.5 BRAM tiles, +0.05 W**.

### 5.1.2 Tcl-debug timeline (each bug = one commit)

Six independent Vivado/Tcl issues were caught and fixed during the
Procedure B + D bring-up. Each is committed individually so the
"how the build procedure works" appendix can cite them by hash:

| Commit | Bug | Symptom | Fix |
|---|---|---|---|
| `b1b67b2` | `${overlay_name}` literal inside `set_property` braces | PFM_NAME contained the literal `${overlay_name}` | regsub the placeholder before sourcing `base.tcl` |
| `ba36c02` | Minimal XDC only constrains HDMI pins | `write_bitstream` UCIO-1 + NSTD-1 errors | Switch to PYNQ-Z2 master XDC |
| `a263ddf` | axis_switch `ROUTING_MODE=0` doesn't expose AXI-Lite | "No interface pins matched `S_AXI_CTRL`" | Set `ROUTING_MODE=1` (Control-Register Routing) |
| `19bac97` | PS cell is `ps7_0`, not `processing_system7_0` | Address-seg lookup returned empty | Use `assign_bd_address -offset` directly |
| `d250c95` | New MIs on `axi_interconnect` have unconnected `Mxx_ACLK` | BD 41-758 — clock pin not connected | Wire `Mxx_ACLK` to the right FCLK |
| `75ca313` | HDMI pipeline is on FCLK1 (142.857 MHz), not FCLK0 | BD 41-237 FREQ_HZ / CLK_DOMAIN mismatch | Dual-domain wiring (data on FCLK1, ctrl on FCLK0) |

## 5.2 End-to-end AXIS path silicon validation

**Procedure D bitstream + bare-metal demo + System ILA.** Pipeline:

```
v_tpg_test_0  ──►  axis_switch_in.S01 ─┐
                                       ├─► M00 ─► color_convert ─► pixel_pack ─► axi_vdma  ─► DDR @ 0x1100_0000
J10 / dvi2rgb ──►  axis_switch_in.S00 ─┘
```

`scripts/silicon_vtpg_test.sh` orchestrates the full flow (program → run
→ ILA → capture → BMP → automated 8-bar verify) in ~30 seconds.

### 5.2.1 ILA-measured signal density (256 free-running samples)

| AXIS link | Width | TVALID density | TREADY density |
|---|---|---|---|
| `v_tpg_test_0/m_axis_video` | 24-bit | **97.0 %** | 98.0 % |
| `axis_switch_in/M00_AXIS` | 24-bit | 97.0 % | 98.0 % |
| `pixel_pack/stream_out_32` (→ VDMA) | 32-bit | 71.3 % * | **99.9 %** |

(*) The 71.3 % pixel_pack output density is exactly what the 3-pixel-
per-cycle packer produces — one stall cycle every four to align the
24-bit input stream into 32-bit output words. VDMA's near-saturated
TREADY (99.9 %) shows the AXI-HP0 write side is not bottlenecking.

### 5.2.2 Captured framebuffer

`scripts/silicon_vtpg_test.sh` dumps `0x1100_0000` (FB0) via XSDB
(230 400 32-bit words = 921 600 bytes), renders to BMP with
`scripts/hdmi_in_dump_to_bmp.py --rgb-order RGB`, and verifies all
8 SMPTE bars within ±3 RGB tolerance:

| Bar | Expected RGB | Captured RGB | Match |
|---|---|---|---|
| 0 (white) | 255, 255, 255 | 255, 255, 255 | ✅ |
| 1 (yellow) | 254, 254, 0 | 254, 254, 0 | ✅ |
| 2 (cyan) | 0, 255, 252 | 0, 255, 252 | ✅ |
| 3 (green) | 0, 254, 0 | 0, 254, 0 | ✅ |
| 4 (magenta) | 254, 0, 254 | 254, 0, 254 | ✅ |
| 5 (red) | 255, 0, 0 | 255, 0, 0 | ✅ |
| 6 (blue) | 0, 0, 254 | 0, 0, 254 | ✅ |
| 7 (black) | 1, 0, 0 | 1, 0, 0 | ✅ |

Artefact: `06_doc/silicon_vtpg_smpte_bars.bmp` (640×480, 921 654 B BMP).

### 5.2.3 Colour-space discovery during bring-up

The v_tpg IP's `colorFormat` register (offset `0x40`) was set to `2`
(RGB per the v8.6 driver header), but live capture revealed v_tpg
*actually outputs YCbCr-444 BT.601 full-range* regardless:

| Probe pattern | Captured DDR bytes (Y, Cb, Cr) | Interpretation |
|---|---|---|
| `BCKGND_ID = 7` (SOLID_BLACK) | (0, 128, 128) | Y=0, Cb=Cr=128 → black in YCbCr ✓ (not 0,0,0 of RGB) |
| `BCKGND_ID = 4` (SOLID_RED) | (76, 85, 255) | BT.601: Y=76.2, Cb=84.9, Cr→sat→255 ✓ |
| `BCKGND_ID = 5` (SOLID_GREEN) | (149, 43, 21) | BT.601: Y=149.7, Cb=43.6, Cr=21.2 ✓ |
| `BCKGND_ID = 6` (SOLID_BLUE) | (29, 255, 107) | BT.601: Y=29.1, Cb→sat→255, Cr=107.3 ✓ |

The `color_convert` HLS IP supports a full 3×3 matrix with offsets via
its `bias_c1/c2/c3` registers (`0x58`, `0x60`, `0x68`). The bare-metal
helper `hdmi_in_color_convert_ycbcr2rgb()` programs the BT.601 matrix:

```
R = 1.000·Y  +  0.000·Cb  +  1.402·Cr  −  0.701
G = 1.000·Y  −  0.344·Cb  −  0.714·Cr  +  0.529
B = 1.000·Y  +  1.772·Cb  +  0.000·Cr  −  0.886
```

The `bt709()` variant covers HD HDMI sources (laptops, ≥720p), which
typically use BT.709.

## 5.3 Verification (Cadence Xcelium)

Latest regression on the development VM (2026-05-25):

| Metric | Value |
|---|---|
| Test count | **9 159** |
| Failures / Protocol errors | **0 / 0** |
| Sim cycles | 5 387 274 |
| ISA opcodes hit | **21 / 21 (100 %)** |
| DMA writes covered | 402 |
| Multi-beat DMA bursts | 40 distinct |
| Max-burst DMA | 10 |
| 4 KB-boundary crossings | 6 |
| Stress cycles | 109 |
| Reset tests | 337 |

Coverage database: `cov_work/scope/full_sim/icc_53417130_2eaa3a3d.ucd`.
Text snapshot: `06_doc/sim_cov_report_2026-05-25.txt`.

## 5.4 Bare-metal hardware regression (board)

`07_sw/baremetal/cgra_test.elf` (`make run_baremetal`) — 96 checks
across 25 groups, all PASS on `bitstreams/cgra_top.bit`. Coverage:

- **Round 1**: APB CSR, 1D/2D DMA (varied sizes, back-to-back, tile-bank
  isolation), all four `RESULT_ROW` registers + `RESULT_DATA`, PASS0
  East/South routing, loop control, `CU_CYCLES` monotonicity,
  `IRQ_STATUS` W1C, 20-iter stress, CU soft reset.
- **Round 2**: ALU smoke test (ADD/SUB/MUL/AND/OR/XOR), multi-instruction
  context programs, nested LOOP2 over LOOP, North + West routing +
  3-way multicast, MAC saturation to the 40-bit accumulator boundary,
  DMA + CU concurrency, DMA error / register protection.
- **Round 3**: End-to-end GIC interrupt delivery — DMA-done + CU-done
  via a hand-rolled ARMv7 GIC v1 driver (`gic.{h,c}`); 5 back-to-back
  delivery test; LED4 visually pulses during the IRQ stress.

System ILA in the cgra_top.bit bitstream monitors the CGRA AXI master,
APB control, and DMA debug signals (`dbg_dma_busy`, `dbg_dma_read_state`,
`dbg_dma_write_state`, `dbg_dma_fifo_full/empty`, `dbg_dma_write_words_remaining`,
`irq`) — refresh in Vivado HW Manager to capture if any future test
fails.

## 5.5 What is silicon-validated as of 2026-05-25

- ✅ All 21 ISA opcodes (sim + bare-metal)
- ✅ All 4 routing directions (N/E/S/W) + 3-way multicast
- ✅ MAC pipeline at 99.7 % steady-state slot efficiency (Suite MTP)
- ✅ Nested LOOP2 over LOOP, with zero-overhead branching
- ✅ DMA + CU concurrency (interleaved access)
- ✅ End-to-end GIC interrupt delivery (DMA-done + CU-done + multi-IRQ)
- ✅ MNIST CNN inference at 665 FPS / 97.0 % top-1 (CGRA-FC)
- ✅ Vivado bitstream rebuild reproducibility (Procedure A)
- ✅ v_tpg + axis_switch + color_convert + pixel_pack + VDMA AXIS chain
- ✅ YCbCr → RGB BT.601 conversion via color_convert matrix programming
- ✅ DAP-lockup software recovery (`rst -dap`, no physical SRST needed)

Still pending on hardware:

- ⏳ Live HDMI input through `dvi2rgb` (HDMI splitter pending)
- ⏳ MNIST inference on a *captured* HDMI frame (depends on above)
- ⏳ VTC detector lock with real PixelClk
