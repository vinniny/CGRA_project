# Windows GUI recreation recipe — CGRA on PYNQ-Z2 (DDR-working)

Purpose: the Linux/batch work prototyped and **proved** the design + FPGA
work. This is the recipe to recreate the same working configuration in the
**Vivado/Vitis GUI on Windows**, as a clean canonical project.

Validated on silicon 2026-05-29: DDR R/W, CGRA APB, CGRA DMA-from-DDR, and
full MNIST per-stage all working. See `06_doc/silicon_pillars_2026-05-29.md`.

---

## ⚠️ The one trap that wasted a day — read this first

**DO NOT use Vivado's built-in `pynq-z2` board preset for the PS-7 DDR.**
The board file shipped in Vivado 2025.1
(`data/boards/board_files/pynq-z2/A.0/preset.xml`) has DDR trace delays that
**do not train DDR on this board** (`BOARD_DELAY0=0.279`,
`DQS_TO_CLK_DELAY_0=-0.051`, `DQS_0_LENGTH_MM=32.14`). Symptom: DDR controller
reports NORMAL + PLL locked, but reads/writes are corrupt (address aliasing).

Instead, configure the PS-7 DDR with **`PARTNO = Custom`** and the explicit
values in §2 below (these are the PYNQ `base.tcl` values that actually work).

Also: associating the board (`board_part`) re-locks the smartconnect's
internal `psr_aclk` (board-mismatch) and blocks generation. With the explicit
Custom DDR config you do **not** need the board association at all — leave the
project board unset and just set the part `xc7z020clg400-1`.

---

## 1. Project + clocks (PS-7 → Clock Configuration)

- Part: **xc7z020clg400-1** (do NOT set a board / `board_part`).
- `PCW_CRYSTAL_PERIPHERAL_FREQMHZ` = **50** (TUL PYNQ-Z2 PS_CLK is 50 MHz).
- `FCLK_CLK0` (PL clock to CGRA) = **50 MHz** (CGRA is timed at 50 MHz;
  REF used 100 but the CGRA design needs 50).
- UART1 ref ≈ 100 MHz (default), 115200 baud.

## 2. PS-7 → DDR Configuration (THE critical part)

Set **Memory Part = Custom**, then enter these exactly (PS-7 GUI "DDR
Configuration" tab → "Memory Part Configuration" + "Board / Training"):

```
Memory Type            DDR 3
Part No.               Custom
DRAM Width             16 Bits
Bus Width              16 Bit
Device Capacity        4096 MBits
Speed Bin              DDR3_1066F
DDR freq (derived)     525 MHz   (from DDR PLL FBDIV=21 × 50 MHz / 2)
ECC                    Disabled
Internal VREF          0 (off / external)
CL / CWL               7 / 6
Row / Col / Bank addr  15 / 10 / 3
AL                     0     BL  8
t_RCD 13.125  t_RP 13.125  t_RC 50.625  t_RAS_min 35.0  t_FAW 40.0
Train: WriteLevel=1  ReadGate=1  DataEye=1

Board delays (ns):     DELAY0 0.223  DELAY1 0.212  DELAY2 0.085  DELAY3 0.092
DQS-to-CLK (ns):       0.040  0.058  0.0  0.0

Trace lengths (mm):
  DQS  0..3: 15.6   18.8   0   0
  DQ   0..3: 16.5   18     0   0
  CLOCK0..3: 25.8   25.8   0   0
Package lengths:
  DQS  0..3: 105.056  66.904  89.1715  113.63
  DQ   0..3: 98.503   68.5855 90.295   103.977
  CLOCK0..3: 80.4535 (all four)
Propagation delay: 160 (all DQS/DQ/CLOCK lanes)
```

(Full machine-readable list: `scripts/vivado_diagnostics/ref_ddr_uiparams.tcl`.
 Quick check after building: the generated `ps7_init.tcl` read-DQS-gate regs
 `0xF800612C..6138` should be DISTINCT per lane, e.g. ~`0x26C05 / 0x26007 /
 0x1D800 / 0x1E000` — NOT four identical `0x28C00`.)

## 3. Block design

PS-7 (M_AXI_GP0 + S_AXI_HP0 enabled) + the CGRA wiring already in the design:
- `cgra_top` IP (xilinx.com:user:cgra_top:1.0, from the `cgra_block` repo).
- `axi_apb_bridge` on GP0 → CGRA APB control @ **0x43C00000** (64K).
- `smartconnect` / `axi_interconnect`: CGRA `m_axi` → **HP0** (DDR access).
- `system_ila` on CGRA `m_axi` + APB + DMA debug signals (optional, for debug).
- Address map: CGRA APB **0x43C00000**, HP0 covers DDR `0x00100000..0x1FFFFFFF`.

(The HDMI/video IPs were removed during prototyping — not needed for the CGRA.
 If you start from a base that has them, either wire them or delete them; if
 deleted, set DRC `NSTD-1`/`UCIO-1` to Warning for the now-floating
 `tmds_*`/`ddc_*` wrapper ports, or remove those ports from the wrapper.)

## 4. Generate → implement → export

1. Sources → `design_1.bd` → **Generate Output Products** (Global).
2. Create HDL Wrapper (let Vivado manage).
3. **Generate Bitstream** (impl strategy: default is fine; design met timing
   at WNS ≈ +2.5 ns @ 50 MHz).
4. **File → Export → Export Hardware** → **Include bitstream** → produces the
   `.xsa` (this bundles bitstream + ps7_init from the SAME BD — the single
   source of truth). See `memory/feedback_xsa_source_of_truth`.

## 5. Vitis

Platform Project ← the `.xsa`. Build the bare-metal apps from
`07_sw/baremetal/` (e.g. `demo_mnist_per_stage`, `bench_*`). "Launch on
Hardware" does PL program + ps7_init + ELF load in one step.

## 6. Quick silicon sanity (after first program)

Per `memory/feedback_mmio_ping_pong_smoke`:
1. PS health: read `0xF8000600` (DDR), `0xF800010C` (PLL lock = 0x3F).
2. DDR R/W: write `0xDEADBEEF` to `0x00100000`, read back — must match.
3. CGRA APB ping-pong: write/read `0x43C00008`.
4. Short DDR→CGRA loopback DMA.
Only then run the real workload.

---

## Proven silicon numbers (from this config)
- Compute roof: 1 MAC/cyc/PE → 1.6 GOPS
- Memory roof: 76 MB/s (DMA-engine-limited)
- CGRA FC: 1.276 ms; NEON FC: 1.011 ms; end-to-end MNIST: 27.03 ms
- Accuracy: ARM-INT 94/100, CGRA 87/100
