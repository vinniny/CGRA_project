# Senior consult on DMA hang + bitstream regression (2026-05-28 evening)

Second senior consult of the session, focused on tactical FPGA debug.
Earlier consult (`senior_arch_review_2026-05-28.md`) was architectural;
this one is operational. Recorded verbatim because the recovery ranking
is what unblocks the next session.

---

## §1 — `write_hw_platform` and MD5 mismatch

- **Behavior**: `write_hw_platform` is a packaging tool. It does *not*
  re-run implementation unless the project is in an "Out-of-Date" state
  AND your script triggers a `launch_runs` before export.
- **MD5 change**: Bitstreams are not deterministic by default. Even
  with identical RTL/netlist, the `BITSTREAM.CONFIG.USR_ACCESS`
  (timestamp) or `USERID` fields change the MD5.
- **The trap**: If MD5 changed AND behavior broke, Vivado likely
  detected the implementation as "Out-of-Date" (possibly from a stray
  file touch) and re-ran bitgen or re-routed if the batch script forced
  a "clean" state. **A new route = new timing slack. If the CGRA DMA
  is timing-marginal, a different seed/route can break it.**

---

## §2 — System ILA workflow for DMA hang

### Trigger condition
```
dbg_dma_busy == 1  AND  dbg_dma_write_words_remaining > 0
```
Use a long Storage Qualification window to see if
`write_words_remaining` is decrementing.

### Three smoking guns

1. **PS Backpressure**:
   - `AWVALID` (or `ARVALID`) HIGH, but `AWREADY` LOW
   - **Cause**: PS Interconnect / DDR Controller refusing transactions
   - **Check**: Is FCLK actually toggling? Is PS7 in a weird reset state?

2. **Internal FSM stuck**:
   - `WVALID` and `WREADY` both HIGH (handshaking) BUT
     `dbg_dma_write_words_remaining` NOT decrementing
   - **Cause**: RTL counter/logic bug

3. **Response Starvation**:
   - `AWVALID/AWREADY` handshake completed, but `BVALID` never returns
   - **Cause**: DMA FSM waiting for write response before clearing `busy`

### HP0 PS-side probing

> *"If `AWVALID` is visible on the CGRA side but not the HP0 slave
> side, your Interconnect is misconfigured (likely a clock domain
> mismatch or reset assertion)."*

So: ALSO probe the PS side via AXI Performance Monitor or by adding
ILA taps on the HP0 inputs. Confirms whether transactions are even
arriving at PS.

---

## §3 — Recovery strategy (ranked)

### 🏆 Rank 1: revert to git checkpoint

> *"Only way to ensure the BD and PS-7 configuration are identical to
> the silicon-validated state. Exporting a new .xsa from a known-good
> commit is the safest path."*

Action plan:
1. Find the Vivado project's git history (`/mnt/c/Users/thanh/Desktop/FPGA_CGRA/`)
2. Identify the commit that produced the silicon-validated .bit
   (MD5 `24f7ad9d22e229e6cca58f5d336d04bf`)
3. `git checkout <tag>` in the Vivado project
4. Open in Vivado, `write_hw_platform -fixed -include_bit -force`
5. Verify the resulting .bit MD5 matches the backed-up silicon-validated one

### Rank 2: clean rebuild from TCL

If git is messy: `rm -rf .xpr cgra_ip.cache cgra_ip.runs`, rebuild from
the project-creation TCL script (`create_synth_project.tcl` etc.) plus
the RTL files. 60-min cost, but removes any "ghost in the machine"
stale artifacts. Produces a guaranteed-coherent .xsa.

### Rank 3: restore old .bit + legacy ps7_init (Hail Mary)

> *"High risk. If the old bitstream expects a 100MHz FCLK and your
> legacy ps7_init provides 50MHz (or vice-versa), the DMA will either
> hang or produce garbage. Only do this if you are 100% sure the
> ps7_init.tcl matches the settings of the old bitstream's BD."*

For this project, the old bitstream + legacy `scripts/ps7_init.tcl` is
the historically-used combo. So the risk is lower than the senior's
general warning — but still requires verification.

### Rank 4: debug DMA root cause

> *"Only if (b) and (c) fail. If a stable project suddenly breaks on a
> re-export, it's usually a tool/environment issue, not a new RTL bug
> you need to hunt."*

---

## Brutal verdict (initial)

> ***"Your .xsa is likely coherent, but the implementation it points to
> is garbage (likely timing or a bad route). Revert to the last git tag
> that worked and export from there."***

## REFINED Senior Response (User-sourced, takes precedence)

### §1 — refined: write_hw_platform never re-impls
> *"write_hw_platform does NOT re-run implementation or bitstream
> generation under the hood. It strictly packages the existing outputs
> from your local runs directory into the .xsa zip archive.
> If your .bit MD5 differs, it is **almost certainly due to timestamp
> metadata** — Vivado injects generation date, time, and absolute build
> path into the bitstream header. If any script, makefile, or stray GUI
> click triggered a fresh `write_bitstream` on the implemented DCP — even
> if RTL and routing are 100% identical — the resulting .bit will have
> a different MD5 hash."*

To verify whether two .bit files have identical *configuration payload*
(ignoring header timestamps):
```
write_bitstream -mask_file ...
diff <(strip headers from bit1) <(strip headers from bit2)
```

### §2 — refined: ILA workflow (skip APM)
> *"Skip the AXI Performance Monitor (APM) on the PS side. Your System
> ILA is sitting right on the HP0 boundary; if a transaction makes it
> across the AXI interface, the ILA will see the handshake. The APM
> will just tell you what the ILA already knows with less granularity."*

**Trigger setup**:
- You CAN'T trigger on "never asserts done."
- Trigger on the START of the transaction: `AWVALID == 1 && AWREADY == 1`
  (writes) or `ARVALID == 1 && ARREADY == 1` (reads).
- Set trigger position to 5-10% so the ILA buffer captures the stall
  tail.

**Refined smoking guns**:

1. `dbg_dma_fifo_full == 1 AND WVALID == 1 AND WREADY == 0`
   → Zynq-7000 PS is backpressuring. HP0 FIFO clogged, DDR controller
     deadlocked, or **HP0 not properly initialized by FSBL/ps7_init**.

2. `dbg_dma_read_state stuck in WAIT_RDATA AND ARREADY was previously 1`
   → PS accepted the address but RVALID never asserted or RLAST dropped.

3. `dbg_dma_busy == 1 but NO AXI VALID signals asserted`
   → CGRA internal FSM stuck. DMA tasked but logic failed to format
     the AXI request, or stuck waiting for internal CGRA data.

### §3 — REFINED Recovery Ranking

> *"Stop fighting the tooling. Your immediate goal is to root-cause the
> DMA hang, not to appease the Vitis workspace."*

#### 🏆 Rank 1: Option (D) — XSCT + Hardware Manager (< 5 min)

**Bypass the .xsa and Vitis entirely for this debug session.**

1. Open **Vivado Hardware Manager** and program the FPGA with existing
   `.bit` and `.ltx` (debug-probes file).
2. Open **xsct** (Xilinx Software Command-Line Tool).
3. Connect to target, source the **legacy `scripts/ps7_init.tcl`**, run
   `ps7_init` + `ps7_post_config`. This wakes the PS, enables FCLKs to
   PL, and unlocks the HP0 ports.
4. Use **`mwr` from xsct** to manually write CGRA APB control registers
   to kick off the DMA.
5. Watch the ILA trigger.

> *"The legacy ps7_init.tcl WILL work perfectly as long as you haven't
> radically altered the required FCLK frequencies or MIO configurations
> since that legacy file was generated."*

#### Rank 2: Option (C) — Full Rebuild (30-60 min)

> *"If your CGRA requires a complex, multi-megabyte software payload
> running on the ARM cores to generate the failure condition, manual
> XSCT pokes won't cut it. Take the 45-minute hit. Clean the project,
> synthesize, implement, and export a fresh .xsa. Use the time to
> review your RTL constraints."*

#### Rank 3: Option (B) — Git revert
Only if the build system perfectly caches intermediate DCPs. Otherwise
a revert triggers full rebuild → equivalent to Option C with extra
version-control friction.

---

## Final action plan (per refined senior advice)

**Rank 1 (Option D) is the right next step. We have all the artifacts:**
- `backups/silicon-debug-20260528/cgra_top_pre-vivado-regen.bit` (old .bit)
- `bitstreams/cgra_vtpg_ila.ltx` (debug probes, if matches old .bit) OR
  the `.ltx` co-located with whatever .bit Vivado was actually using
- `scripts/ps7_init.tcl` (legacy, paired with old .bit)
- `scripts/xsdb_program.tcl` (existing JTAG load script)

**Concrete next-session steps:**
1. Restore old .bit to `bitstreams/cgra_top.bit`
2. Power-cycle PYNQ-Z2
3. `make program BIT=bitstreams/cgra_top.bit` (uses legacy ps7_init)
4. Open Vivado Hardware Manager in a separate session, refresh
   hw_server, load `bitstreams/cgra_vtpg_ila.ltx` (or matching .ltx)
5. In xsct: write the CGRA registers to trigger a smoke-style DMA
   (DMA_SRC, DMA_DST, DMA_SIZE, DMA_CTRL=1)
6. Capture ILA trace, identify which smoking gun is firing
7. Fix accordingly

If smoke-style DMA WORKS via direct xsct mwr (no ELF intermediate),
then the issue was in the ELF/Vitis chain, not the bitstream. We can
then either fix the ELF flow or just use xsct mwr for the silicon
measurements (slower but possible).

If smoke-style DMA HANGS via direct xsct mwr, the bitstream's DMA is
genuinely broken — escalate to Option C (rebuild).


---

## Action items for next session

1. **Check Vivado project git status** — `cd /mnt/c/Users/thanh/Desktop/FPGA_CGRA && git log --all` if it's a git repo, or look for backup folders / dated zip files.

2. **If git tag found** → revert, re-export, retry silicon work.

3. **If no git history** → try Rank 3 (old .bit + legacy ps7_init):
   ```bash
   cp backups/silicon-debug-20260528/cgra_top_pre-vivado-regen.bit \
      bitstreams/cgra_top.bit
   md5sum bitstreams/cgra_top.bit   # should be 24f7ad9d22e229e6cca58f5d336d04bf
   # Use legacy scripts/ps7_init.tcl (NOT the .xsa bundled one)
   make program BIT=bitstreams/cgra_top.bit
   make run_elf ELF=07_sw/baremetal/demo_mnist_per_stage.elf BIT=...
   # If demo_mnist_per_stage produces 1.50 ms FC1+FC2: silicon path restored
   ```

4. **If Rank 3 fails** → Rank 2 (clean rebuild from TCL).

5. **If all else fails** → Rank 4 (System ILA debug per §2 above).

Once silicon path is restored, fire B1-B6 sequence via
`scripts/run_pillar.sh`, then `analyze_two_pass.py` → `calibrate_emulator.py`
to get the final ±10% emulator-vs-silicon validation across all
four pillars.
