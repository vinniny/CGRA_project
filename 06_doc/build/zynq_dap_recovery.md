# Zynq-7000 DAP / JTAG Recovery Notes

Lessons learned debugging a "stuck DAP" situation during the v_tpg ILA bring-up
on PYNQ-Z2 (2026-05-24).

## Symptom

XSDB enumerates the JTAG chain and shows:
```
1  DAP (AHB AP transaction error, DAP status 0x30000021)
2  xc7z020
   3  Legacy Debug Hub
```

The Arm Cortex-A9 cores are MISSING from the target tree. Anything that
tries to access them (ps7_init, dow, mrd to PS registers) fails with:
```
Memory read error at 0xF8007080. AHB AP transaction error, DAP status 0xF0000021
```

The board still responds to JTAG at the TAP level (we can read IDCODE,
program the PL via `fpga -file`), but the **AHB-AP inside the DAP** is in
a sticky-error state and won't route transactions to the PS.

## Cause hierarchy

In order from most-common to rare:

1. **`program_hw_devices` in Vivado HW Manager** programs the PL but does
   NOT run `ps7_init`. FCLK_CLK0/1/2/3 stay at default/unstable values,
   the AHB-AP errors on the next access, and the cores disappear. Always
   program via XSDB (`scripts/xsdb_program.tcl` via `make program`)
   which calls `ps7_init` immediately after PL load.

2. **System ILA bitstreams** insert a Vivado debug hub on JTAG USER1/USER2
   BSCAN primitives. On Zynq-7000 the same TAP serves both the ARM DAP
   and the debug hub, so concurrent / contended access can corrupt DAP
   state. The ILA cgra_vtpg_ila bitstream exhibits this: even after
   clean PL load + ps7_init, the DAP shows the AHB-AP error and `rst
   -system` hangs with "Cannot reset APU. Timeout waiting for PLL lock".

3. **Timing violations in PS-PL clock paths** can desync the FCLK output
   so the PS PLLs drift out of lock. The cgra_vtpg_ila bitstream has
   WNS = -0.105 ns on an internal VDMA path at 142.857 MHz — could be a
   contributing factor.

## Recovery (without physical SRST)

The single biggest discovery: **`rst -dap`** clears the DAP sticky error
and brings the ARM cores back into the target list:

```tcl
connect
catch {targets -set 1}   ;# select DAP target
catch {rst -dap}         ;# clears AHB-AP sticky error
after 1500
targets                  ;# Cortex-A9 cores now visible as "Suspended"
```

But this is only a **partial** recovery: subsequent writes to PS registers
(SLCR_UNLOCK, FPGA0_CLK_CTRL, etc.) often *appear* to succeed but never
persist. Reads come back as 0. This means the PS register fabric is in
an inconsistent state that JTAG alone can't fix.

What `rst -dap` is good for:
- Making the cores visible long enough to dump CPU registers / memory
- Loading + running a small bare-metal program that re-initializes the
  PS from inside (works ~50% of the time)
- Confirming that the board is alive and the JTAG chain isn't dead

What needs physical intervention:
- Stable PS PLL recovery — requires PS_POR pulse (PWR button) or PS_SRST
  pulse (SRST button). Neither is reachable via JTAG on PYNQ-Z2 because
  the FT2232H's SRST output is not wired to the SoC SRST pin.

## Other commands tried that DID NOT help

| Command                | Result |
|------------------------|--------|
| `rst -srst`            | Accepted, no effect — SRST not wired |
| `rst -por`             | Accepted, no effect — POR not wired |
| `rst -system`          | "Cannot reset APU. Timeout waiting for PLL lock" |
| `fpga -file <bit>`     | PL reprograms, DAP still errored |
| `pkill hw_server` + restart | hw_server restart fine, DAP still errored |
| USB cable detach/reattach via `usbipd` | Only doable from Windows side; not tried this session |

## Recommended workflow to avoid DAP lockup

1. **NEVER** use Vivado HW Manager's `program_hw_devices` on Zynq-7000.
   Always use XSDB via `make program BIT=...`.

2. For ILA-based debug, split the workflow so JTAG arbitration stays
   clean:
   - Phase 1: XSDB programs PL + runs `ps7_init` + `dow` + `con`.
   - Phase 2: SUSPEND the CPU (`stop`) before any Vivado HW Manager
     ILA interaction.
   - Phase 3: Vivado HW Manager attaches to the ALREADY-PROGRAMMED
     device with `refresh_hw_device -update_hw_probes false` — no
     `program_hw_devices` call.
   - Phase 4: After ILA capture, RESUME CPU (`con`) and re-detach
     Vivado from hw_server.

3. If you must rebuild an ILA bitstream, watch timing carefully:
   - Aim for WNS > +0.1 ns
   - Avoid CONNECTING the ILA's debug-hub AXI-Lite to the same
     SmartConnect that drives PS-managed peripherals
   - Use the smallest practical DATA_DEPTH (e.g., 256, not 1024)
   - Prefer monitoring only 2-3 nets, not 5
