# CGRA Architecture Analysis: Bottlenecks, Drift, and Improvements
## Cross-referenced against NotebookLM literature + actual design

---

## 1. How Far We've Drifted from State-of-the-Art

### 1.1 PE Pipeline — Significant Drift

| Aspect | Literature (CGRA4ML / OpenEdgeCGRA) | Your Design |
|---|---|---|
| Pipeline depth | 1–2 stages (shallow) | 3 stages (decode→_r→_r2) |
| RF bypassing | Data forwarding between PEs, bypasses RF | **None** — dependent read N+1 sees stale data from N |
| MAC throughput | Dedicated MAC unit, no stall | **~1/3 throughput** — only 1 in 3 back-to-back MACs contributes |
| RF readability | Multi-port or full depth | **Effectively 1 register (RF[0])** — src0_sel=0 reads RF[raddr=0]; values 1–6 → N/E/S/W/SPM/IMM |
| PE utilization | 69–100% (OpenEdgeCGRA / CGRA4ML) | Estimated **<40%** for non-trivial kernels due to hazards |

The 3-stage pipeline was intended to raise Fmax, but without forwarding it
serializes everything. The RF write-to-read latency means every dependent
operation needs a "bubble" cycle or must route through a neighbor PE, which
then wastes that PE's compute bandwidth.

The RF[0]-only readability is the single largest architectural limitation:
the 16×32b register file exists in silicon but 15/16 entries are write-only.
This is a compile-time constraint, not a runtime bug — the ISA encodes
src_sel as a type selector, not an address.

### 1.2 Routing — Matches Literature's Simple Tier (Acceptable for 4×4)

| Aspect | Literature | Your Design |
|---|---|---|
| Topology | Mesh, bus, torus, ruche | 5-port N/E/S/W/Local mesh |
| Long-distance | Single-cycle multi-hop or bypass routes | Multi-hop through intermediate PEs |
| Multicast | Yes (efficiency feature) | Yes — implemented (route_mask) |
| Broadcast | In some designs | Not directly — via multicast |

For a 4×4 array this is acceptable. The worst case is 6 hops (corner-to-corner),
meaning up to 5 intermediate PEs are consumed purely for routing. This directly
reduces effective compute PE count from 16 to ~11 for long-range data movement.

Literature recommendation: add a "ruche" or express-link every 2 hops to cut
max routing PE waste in half. On a 4×4 this would mean 2-hop bypass from PE(0,0)
to PE(0,2), etc. — a small RTL addition.

### 1.3 Control Unit — Notable Drift

| Aspect | Literature (SNAX-CGRA) | Your Design |
|---|---|---|
| Config overhead | 907 cycles (DMA-loaded) vs 2900 cycles (DRAM-direct) | Every APB write = 2–3 cycles, ~30 regs × 3 = 90 cycles from bare-metal, **5–20 µs per reg from Linux MMIO** |
| Wasted loop slots | Zero-overhead loops in hardware | **CU always runs PC 0..15** — for a 4-instruction kernel, 12 NOP slots wasted per iteration |
| Config hiding | Double-buffer Config RAM with background DMA | Context switching requires CU to be idle (TILE_BANK_SEL blocked while busy) |
| Loop nesting | 2+ levels in literature | 2 levels (LOOP / LOOP2) — adequate |

The CU "run to PC 15" behaviour means for a kernel using only slots 0–3:
- Each iteration wastes 12/16 = **75% of CU cycles** on NOPs
- LOOP_COUNT=10 → 120 wasted CU cycles per outer-loop
- This is in-silicon behaviour (not fixable without RTL change to CU_PC_END logic)

CU_PC_END register was added (0x3C) to set the last active PC — confirm this
actually gates `array_done` correctly and doesn't still run all 16 slots.

### 1.4 DMA Engine — Moderate Drift

| Aspect | Literature | Your Design |
|---|---|---|
| FIFO depth | 128 outstanding transactions recommended | **32 words** |
| Transfer modes | 2D strided + descriptor chaining | 2D strided + SG-DMA registers (partially implemented) |
| Config loading | DMA-loaded CSR (SNAX: 907 cycles) | APB-written registers only |
| Concurrency | Compute/DMA overlap | Supported (tested in bench) |
| AXI bursts | Up to 256 beats | Unclear — likely 32-beat bursts limited by FIFO |

The 32-word FIFO is the main DMA bottleneck. At 50 MHz with a 32-bit AXI
bus, throughput = 32 × 4B × 50 MHz = 6.4 GB/s theoretical, but the FIFO
fills in 32 cycles and stalls if the PS-side AXI fabric is busy. Doubling
to 64 words gives a proportionally larger tolerance window.

---

## 2. Bottlenecks by Severity

### Critical (limits correctness/throughput severely)

**B1: RF[0]-only readability**
- Root cause: src0_sel doubles as source-type and RF address
- Effect: All multi-instruction kernels must chain through neighbor ports (N/E/S/W)
  or the scratchpad instead of the RF — adds routing hops and forces serial dependency chains
- Fix: Remap ISA encoding — add a separate 4-bit rf_raddr field in the 64-bit config word
  (bits currently unused could be repurposed). This is a breaking ISA change but
  only affects the toolchain/testbench config generation.

**B2: MAC accumulator pipeline hazard (measured: 66.6% throughput)**
- Root cause: 3-stage pipeline (decode→_r→_r2), 2-cycle hazard window before accumulator
  result is visible to the next MAC. Only 10 out of 15 back-to-back MACs accumulate.
- Silicon measurement (Cat 2, 2026-04-22 Haoyue 7020): 15×MAC b2b → 10 effective = **66.6%**;
  with 2-NOP spacing → 80%; with 1-NOP spacing → 62.5% (worse — pipeline alignment effect).
- **Status: Deferred — not worth fixing at current bottleneck profile.**
  Amdahl's law: CU compute is only 7.4% of Conv2 frame time (Cat 15). Even perfect 100%
  MAC rate saves at most 2.5% of total frame time. DMA-CU overlap (B9) is the priority.
  Software workaround: 2-NOP spacing between dependent MACs restores 80% throughput.
  Revisit if a future workload pushes CU-compute share above 30%.

**B3: CU dead slots (NOP cycles at PC LOOP_END+1..15)**
- Root cause: CU FSM always advances to PC=15 before asserting `done`
- Effect: 4-instruction kernel → 75% wasted CU cycles
- **Status: FIXED** — `CU_PC_END` register (0x3C) already gates `array_done` at
  `cgra_top.sv:606-610`. The fix was software-only: `bench_setup()` now explicitly
  resets CU_PC_END to 15, and each kernel sets it via `cgra_set_pc_end()` in `cgra.h:153`.
  Cat 17a measures the per-kernel speedup (≤16 slots → up to 4× fewer CU cycles).

### High (degrades real-time performance on PetaLinux)

**B4: APB register write latency from Linux**
- Root cause: APB is 2–3 cycles per transaction; from Linux MMIO via AXI GP0 it's 5–20 µs
- Effect: Programming 30 CSRs = 150–600 µs overhead per inference call
- Fix: Use scatter-gather DMA to preload a config descriptor to a shadow register
  block and have hardware copy it atomically. Short term: batch writes using
  `memcpy` to the APB region (some Zynq AXI bridges support burst writes to APB
  via AXI-to-APB bridge in AXI mode, check if Vivado's AXI interconnect enables this).

**B5: RESULT_FIFO warmup (12-cycle skip)**
- Root cause: 3-stage pipeline + FIFO fill latency
- Effect: First 12 results discarded → for small kernels (<16 results) this dominates
- Fix: Document as fixed overhead, or expose RESULT_SKIP as a tunable in the Linux driver
  based on kernel size (not always 12).

**B6: No background context loading**
- Root cause: Context switching requires CU idle; no DMA path to Config RAM
- Effect: Reconfiguration is blocking — PS must wait for CU done, write new configs, restart
- Fix: Add an AXI slave port to Config RAM so DMA can pre-load the next context
  while CU is running the current one. TILE_BANK_SEL double-buffer is already
  doing this for data — the same pattern should apply to Config RAM.

**B9: DMA dominates frame time (91.5%) — NEW top priority**
- Root cause: current driver serialises each chunk as (4×DMA load) → (CU run) → (readback).
  The tile memory already has a double-buffer (TILE_BANK_SEL, 0x74). DMA can write to the
  INACTIVE half while CU reads from the ACTIVE half with zero hardware conflict.
- Silicon measurement (Cat 15, 2026-04-22): Config 1.0%, **DMA 91.5%**, CU 7.4%, Readback 0.0%.
- Fix: ping-pong pattern — while CU processes tile N from buffer A, DMA fetches tile N+1
  into buffer B. Toggle TILE_BANK_SEL after each chunk. Expected speedup per chunk:
  max(DMA, CU) / (DMA + CU) ≈ 9881/10672 = **1.08×** (8% per chunk).
  Buffer B addresses = buffer A addresses + 0x800 (bit 11 of AXI addr = 1).
- Silicon result (Cat 18, 2026-04-22): serial 47,409 µs → overlap 46,840 µs = **570 µs saved
  (1.2%)**. Overlap limited to CU execution window (213 ARM cycles = 2.0% of chunk). CU
  finishes before DMA_r0 completes, so only single-row-DMA overlap is achieved.
- Next step: use SG-DMA (DMA_DESC_HEAD 0x7C) to chain all 4 row-DMAs into one descriptor,
  making the full ~4× DMA transfer overlap with CU → expected ~8% gain.
- Literature cites 95% data-movement energy share for CGRAs; hiding DMA latency is the
  primary lever.

### Medium (area/energy inefficiency)

**B7: 5-port mesh without bypass links**
- Effect: Corner-to-corner transfer ties up 5 intermediate PEs per hop chain
- Fix: Add express links at 2-hop intervals (4 extra wires per row/column in a 4×4)

**B8: Shallow DMA FIFO (32 words)**
- Effect: AXI stalls when PS AXI fabric backpressure exceeds 32 cycles
- Fix: Increase FIFO_DEPTH from 32 → 64 or 128 in `cgra_dma_engine.sv`
  (already parameterized, zero-risk RTL change)

---

## 3. Improvements for Real-Time PetaLinux

### Tier 1 — Software only (no RTL change, implement now)

**S1: Threaded IRQ + bottom-half model**
```c
// In 07_sw/driver/cgra_driver.c
request_threaded_irq(irq, cgra_irq_top_half, cgra_irq_worker,
                     IRQF_SHARED, "cgra", dev);
// top_half: just wake the worker thread — stays insensitive to AXI latency
// worker: reads RESULT_ROW0-3, copies to user buffer, signals completion
```

**S2: Zero-copy mmap for result buffer**
```c
// Map tile memory and result FIFO directly to userspace
// Eliminates kernel→user copy for each inference result
cgra_mmap() → vm_insert_page() on the CMA-allocated DMA buffer
```

**S3: Pre-program config at driver open(), not per-inference**
- Parse the CGRA binary at `open()`, write all static config (PE slots, loop params)
- Per-inference: only update DMA_SRC, DMA_DST, DMA_SIZE, then set CU_CTRL[0]
- Reduces per-call latency from ~600 µs → ~60 µs (3 APB writes × 20 µs)

**S4: CPU affinity + real-time priority**
```bash
# In PetaLinux init script
echo 1 > /sys/bus/platform/devices/43c00000.cgra/driver/irq_affinity
chrt -f 80 cgra_daemon &   # SCHED_FIFO priority 80
```

**S5: Increase DMA FIFO in Vivado (trivial RTL)**
Change `parameter FIFO_DEPTH = 32` → `64` in `cgra_dma_engine.sv`, rebuild bitstream.
Zero functional risk — only affects BRAM utilization (+1 RAMB36).

### Tier 2 — RTL changes (next milestone)

**R1: CU_PC_END enforcement**
Verify `cgra_control_unit.sv` — if `done` does not already respect CU_PC_END,
add: `assign array_done = (pc == cu_pc_end_r);`
This alone recovers 75% of CU cycles for typical kernels.

**R2: MAC accumulator bypass**
In `cgra_pe.sv`, add a 1-bit `mac_acc_bypass` that routes `alu_result_r2` back
to `src1` operand mux when the instruction is MAC and the previous instruction
wrote the accumulator. Eliminates the 2-cycle dead wait.

**R3: FIFO depth → 64**
Single-line parameter change, resynthesize. Reduces AXI stall probability.

### Tier 3 — Architectural (thesis extensions)

**A1: RF address decoupling**
Split config word field: bits [63:60] = src0_type (was src0_sel[2:0]),
bits [59:56] = rf_raddr0 (new). Allows reading any RF[0..15] entry.
Requires updating tb_defs.svh, PE config generation in cgra.h.

**A2: Background Config RAM DMA**
Add AXI-Lite slave port to each PE's Config RAM. The DMA engine writes
next-context configs while CU runs current context. Context switch latency
drops from ~30 APB writes (90–600 µs) to 4 cycles.

**A3: Express routing links**
Add direct PE-to-PE wires skipping 1 hop (PE[0]→PE[2] in each row/column).
Halves routing PE waste for long-distance transfers. ~8% area increase.

---

## 4. Summary Priority Table

*(Updated 2026-04-22 with silicon measurements from Haoyue 7020 @ 50 MHz)*

| ID | Fix | Status | Measured result | Risk |
|---|---|---|---|---|
| R1 | CU_PC_END per kernel | **DONE** — RTL at `cgra_top.sv:606-610`; `cgra_set_pc_end()` in `cgra.h:153`; `bench_setup()` resets to 15 | Cat 17a: 4-slot kernel 5.0× speedup (3 CU cycles vs 15 baseline) | Zero |
| R3 | FIFO_DEPTH 32→64 | **DONE** — `cgra_top.sv:354`; bitstream rebuilt 2026-04-22 | DMA peak 86.0 MB/s; 9063/9063 sim pass (0 failures) | Zero |
| S3 | Bulk config programming | **DONE** — `cgra_config_pe_bulk()` + `cgra_program_kernel()` in `cgra.h:363+` | Cat 17b: 262,808 → 155,372 ARM cyc = **1.7× speedup** (16 PE × 4 slots) | Zero |
| R2 | MAC bypass RTL | **DEFERRED** — measured 66.6% b2b throughput; CU = 7.4% of frame → max 2.5% total gain per Amdahl; 2-NOP spacing gives 80% as SW workaround | 66.6% MAC rate on silicon (Cat 2) | Medium (timing) |
| B9 | DMA-CU overlap | **MEASURED** — Cat 18 ping-pong via TILE_BANK_SEL: 570 µs/frame saved (1.2%). CU execution = 213 ARM cycles (2.0% of 10,880 chunk); overlap limited to CU+DMA_r0 window. To reach 8% requires SG-DMA chaining all 4 row-DMAs into one descriptor. | Serial 47,409 µs → overlap 46,840 µs (Cat 18, 2026-04-22) | Zero (SW only) |
| S1 | Threaded IRQ kernel module | Deferred — no PetaLinux project yet | — | Requires `.ko` |
| S2 | Zero-copy mmap | Deferred | — | Requires `.ko` |
| A1 | RF address decoupling | Deferred — breaking ISA change | — | High |
| A2 | Background Config RAM DMA | Deferred — thesis extension | — | Medium |
| A3 | Express routing links | Deferred — thesis extension | — | Low |
