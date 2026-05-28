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

## Brutal verdict

> ***"Your .xsa is likely coherent, but the implementation it points to
> is garbage (likely timing or a bad route). Revert to the last git tag
> that worked and export from there."***

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
