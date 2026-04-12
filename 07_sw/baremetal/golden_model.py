#!/usr/bin/env python3
"""
Golden model for CGRA benchmark verification.

Independently computes the expected result for each benchmark category
so hardware UART output can be cross-checked. Models the PE pipeline
hazard, SIMD dot-product accumulation, and LIF neuron dynamics using
the same RTL semantics documented in cgra_pe.sv.

Usage:
    python golden_model.py                  # print all expected values
    python golden_model.py --check uart.log # compare against UART capture
"""
import sys

LIF_LEAK = 10  # hardcoded in cgra_pe.sv: localparam signed [39:0] LIF_LEAK = 40'sd10


def clamp40(v):
    """40-bit signed saturation (matches cgra_pe.sv overflow logic)."""
    MAX = (1 << 39) - 1   # 549755813887
    MIN = -(1 << 39)      # -549755813888
    return max(MIN, min(MAX, v))


# ── Category 1: Per-Op expected results ──────────────────────────────
# The CU runs 16 contexts. PE[0,0] feeds IMM → east. PE[0,1] computes.
# RESULT_ROW0 captures the LAST cycle's alu_result from PE[0,3] (east edge).
# Because slot 0 writes broadcast to all 16 slots, the same op runs 16 times.
# For most ops, the result is just the op applied to the two operands.

def cat1_expected():
    """Expected RESULT_ROW0 for each op in Category 1."""
    results = {}
    results["NOP"]     = 0       # NOP doesn't write alu_result; last value undefined
    results["ADD"]     = 10 + 20
    results["SUB"]     = 50 - 20
    results["MUL"]     = 7 * 6
    results["MAC"]     = 0       # MAC accumulates but result depends on pipeline hazard
    results["AND"]     = 0xFF & 0x0F
    results["OR"]      = 0xA0 | 0x05
    results["XOR"]     = 0xFF ^ 0xFF
    results["SHL"]     = 5 << 2
    results["SHR"]     = 100 >> 3  # arithmetic, but 100 is positive so same as logical
    results["CMP_GT"]  = 1  # 10 > 5
    results["CMP_LT"]  = 1  # 3 < 10
    results["CMP_EQ"]  = 1  # 7 == 7
    results["ACC_CLR"] = 0
    results["PASS0"]   = 99
    results["PASS1"]   = 99
    results["LIF"]     = None  # depends on accumulator state, handled separately
    results["RELU"]    = 42    # relu(42) = 42
    results["MAX"]     = 20    # max(10, 20) = 20
    return results


# ── Category 2: MAC Pipeline Hazard ──────────────────────────────────
# PE[0,1] slot 0 = ACC_CLR, slots 1-15 are MAC/NOP patterns.
# Each MAC does: acc += west(1) * imm(1) = acc += 1
# Pipeline hazard: 3-stage pipeline means dependent MAC on consecutive
# slots may see stale accumulator. We model which MACs "stick".
#
# RTL behavior: the accumulator update from slot N lands in _r2 (2 cycles
# later). A MAC at slot N+1 reads the OLD accumulator, so its += 1 is
# based on stale state. Only MACs spaced ≥3 slots apart see the updated
# accumulator reliably.
#
# Empirically from the regression: back-to-back MAC gives ~1/3 effective
# utilization. But the EXACT number depends on the PE pipeline timing.
# We predict the values here and verify against hardware.

def cat2_mac_simulate(mac_slots):
    """
    Simulate MAC accumulation with 3-stage pipeline hazard.

    The accumulator update from slot N is visible to slot N+3 (after
    passing through decode → _r → _r2 → writeback). Slots N+1 and N+2
    read the old accumulator value.

    However, the actual behavior is that the accumulator register is
    written at the end of _r2 stage. So if slot N writes, slot N+1's
    decode reads the OLD value, and slot N+2's decode also reads OLD.
    Slot N+3's decode sees the NEW value.

    Model: track the "committed" accumulator and a 3-deep pipeline.
    """
    acc_committed = 0   # what the accumulator register actually holds
    # Pipeline: acc_committed is updated 2 cycles after the instruction
    # For simplicity, track pending writes
    pending = [None, None, None]  # [will_land_in_1, will_land_in_2, will_land_in_3]

    # Slot 0 is ACC_CLR
    acc_committed = 0

    for s in range(1, 16):
        # Apply pending writeback from 3 cycles ago
        if pending[0] is not None:
            acc_committed = pending[0]
        pending = [pending[1], pending[2], None]

        if mac_slots[s]:
            # MAC reads current acc_committed (which may be stale)
            new_acc = acc_committed + 1  # 1 * 1 = 1
            pending[2] = new_acc  # will be committed 3 cycles later
        # NOP: no pending write

    # Drain remaining pending writes
    for i in range(3):
        if pending[0] is not None:
            acc_committed = pending[0]
        pending = [pending[1], pending[2], None]

    return acc_committed


def cat2_expected():
    """Expected accumulated values for the three MAC patterns."""
    patterns = {
        "16x MAC b2b":  [0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
        "8x MAC+NOP":   [0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1],
        "6x MAC+2NOP":  [0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1],
    }
    results = {}
    for name, slots in patterns.items():
        results[name] = cat2_mac_simulate(slots)
    return results


# ── Category 3: SIMD expected accumulation ───────────────────────────
# MAC with self-dot: src0=src1=packed_val from tile memory
# INT32:   1 * 1 = 1 per MAC
# INT16x2: dot([1,1], [1,1]) = 2 per MAC
# INT8x4:  dot([1,1,1,1], [1,1,1,1]) = 4 per MAC
# Same pipeline hazard as cat 2 (all 15 slots are MAC after ACC_CLR).

def cat3_expected():
    """Expected accumulation for each SIMD mode."""
    # Slots: 0=ACC_CLR, 1-15=MAC (back-to-back)
    mac_slots = [0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
    eff_macs = cat2_mac_simulate(mac_slots)

    return {
        "INT32":   eff_macs * 1,  # 1 MAC per op
        "INT16x2": eff_macs * 2,  # 2 MACs per op (dot product of 2 lanes)
        "INT8x4":  eff_macs * 4,  # 4 MACs per op (dot product of 4 lanes)
    }


# ── Category 9: Activation function expected results ─────────────────

def cat9_expected():
    """Expected results for activation function tests."""
    results = {}
    results["RELU positive(5)"]    = 5
    results["RELU negative(-5)"]   = 0
    results["MAX max(10,20)"]      = 20
    results["MAX max(30,5)"]       = 30
    results["SHL 5<<2=20"]         = 20
    results["SHR 100>>3=12"]       = 12
    results["CMP_GT 10>5=1"]       = 1
    results["CMP_GT 3>10=0"]       = 0
    results["CMP_LT 3<10=1"]       = 1
    results["CMP_EQ 7==7=1"]       = 1
    return results


def cat9_lif_ramp():
    """
    LIF neuron with input=100, leak=10, threshold=80.
    Slot 0 = ACC_CLR (acc=0), then 16 slots with:
      PE[0,0] feeds 100 via PASS0 IMM
      PE[0,1] does LIF: acc = acc + input - leak; if acc >= threshold: spike, reset

    Actually the bench uses slot 0 broadcast (PASS0 IMM for PE[0,0],
    LIF for PE[0,1]). All 16 slots run the same config.

    Wait — bench_cgra.c does ACC_CLR as a separate CU run, then
    configures PE[0,1] with LIF (broadcast to all 16 slots).
    So all 16 slots do LIF with input=100, threshold=80.
    """
    acc = 0
    last_result = 0
    for s in range(16):
        v_new = clamp40(acc + 100 - LIF_LEAK)  # acc + input - leak
        threshold = 80  # from operand1 (IMM)
        if v_new >= threshold:
            last_result = 1
            acc = 0  # reset
        else:
            last_result = 0
            acc = v_new
    return last_result


def cat9_lif_subthreshold():
    """LIF with input=5, leak=10, threshold=5000. Net per slot = 5-10 = -5."""
    acc = 0
    last_result = 0
    for s in range(16):
        v_new = clamp40(acc + 5 - LIF_LEAK)
        if v_new >= 5000:
            last_result = 1
            acc = 0
        else:
            last_result = 0
            acc = v_new
    return last_result


# ── Main ─────────────────────────────────────────────────────────────

def main():
    print("=== CGRA Benchmark Golden Model ===\n")

    print("--- Cat 1: Per-Op Expected Results ---")
    for op, val in cat1_expected().items():
        if val is not None:
            print(f"  {op:<12} → {val}")
        else:
            print(f"  {op:<12} → (state-dependent)")

    print("\n--- Cat 2: MAC Pipeline Hazard ---")
    for name, val in cat2_expected().items():
        print(f"  {name:<16} → accum = {val}")

    print("\n--- Cat 3: SIMD Expected Accumulation ---")
    for name, val in cat3_expected().items():
        print(f"  {name:<12} → accum = {val}")

    print("\n--- Cat 9: Activation Functions ---")
    for name, val in cat9_expected().items():
        print(f"  {name:<20} → {val}")
    print(f"  {'LIF ramp(100,thr=80)':<20} → {cat9_lif_ramp()}")
    print(f"  {'LIF sub-thr(5,thr=5k)':<20} → {cat9_lif_subthreshold()}")

    print("\n--- Cat 5: Multicast ---")
    print("  All fan-out configs should deliver test_val=0x1234 to the")
    print("  expected RESULT_ROW registers. CU_CYCLES should be identical")
    print("  across 1/2/3/4-way configs (CU is lockstep).")

    print("\n--- Cat 6: Parallel Rows ---")
    eff = cat2_expected()["16x MAC b2b"]
    print(f"  Each row accumulates {eff} MACs (same hazard as cat 2).")
    print(f"  1 row: {eff} total MACs")
    print(f"  2 row: {eff*2} total MACs")
    print(f"  4 row: {eff*4} total MACs")
    print(f"  CU_CYCLES should be identical for all (lockstep execution).")

    print("\nNote: Cat 2 pipeline hazard model assumes 3-cycle pipeline")
    print("latency for accumulator writeback. If hardware shows different")
    print("numbers, adjust the pipeline depth in cat2_mac_simulate().")

    # Check mode
    if len(sys.argv) > 2 and sys.argv[1] == "--check":
        print(f"\n--- Checking against {sys.argv[2]} ---")
        print("(Not yet implemented — compare manually for now)")


if __name__ == "__main__":
    main()
