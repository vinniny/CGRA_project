# xsdb_dma_smoke.tcl — direct CGRA DMA test via xsct mwr (no ELF chain).
# Per refined senior advice (06_doc/senior_dma_hang_review_2026-05-28.md
# §3 Rank 1): bypass Vitis entirely, kick a DMA via APB register writes,
# and inspect what gets stuck.
#
# Sequence:
#   1. Connect + halt A9
#   2. Source legacy scripts/ps7_init.tcl (NOT the Vivado-regen one)
#   3. ps7_init + ps7_post_config (wakes PS, enables FCLK0, enables HP0)
#   4. Pre-fill DDR scratch (0x100000) with a known pattern
#   5. Write CGRA DMA registers via mwr
#   6. Read DMA_STATUS in a polling loop with timeout
#   7. Report final state of every relevant register
#
# Run from the repo root via:
#   xsct scripts/xsdb_dma_smoke.tcl
#
# Expected (success): DMA_STATUS bit 1 (DONE) goes HIGH within < 100 polls.
# Expected (hang):    DMA_STATUS stays at BUSY forever — see DMA_ERROR
#                     (0x38) and DMA_STATUS bit pattern for clue.

# CGRA register map (per 07_sw/baremetal/cgra.h)
set CGRA_BASE       0x43C00000
set DMA_CTRL        0x00
set DMA_STATUS      0x04
set DMA_SRC         0x08
set DMA_DST         0x0C
set DMA_SIZE        0x10
set DMA_SRC_STRIDE  0x14
set DMA_ROWS        0x18
set DMA_COLS        0x1C
set CU_CTRL         0x20
set CU_STATUS       0x24
set IRQ_STATUS      0x30
set IRQ_MASK        0x34
set DMA_ERROR       0x38

# CGRA-internal address prefixes (see cgra.h)
#   0x10000000  = tile memory
#   0x10000000 | 0x80000000 = 0x90000000  = tile broadcast
set DDR_SCRATCH     0x00100000   ;# physical DDR address for staging
set TILE_BCAST      0x90000000   ;# CGRA-internal: broadcast to all banks

proc reg_addr {off} {
    global CGRA_BASE
    return [expr $CGRA_BASE + $off]
}

proc rd {off} {
    set addr [reg_addr $off]
    if {[catch {mrd -value $addr 1} v]} {
        return "ERR: $v"
    }
    return $v
}

proc wr {off val} {
    set addr [reg_addr $off]
    if {[catch {mwr $addr $val} e]} {
        puts "  WRITE 0x[format %X $addr]=0x[format %X $val] FAILED: $e"
        return -1
    }
    return 0
}

# ────────────────────────────────────────────────────────────
puts "==========================================================="
puts " xsdb_dma_smoke — direct CGRA DMA test (no ELF)"
puts "==========================================================="

# Connect and find A9
connect -url tcp:localhost:3121
configparams force-mem-accesses 1

# Defensive DAP recovery
catch {targets -set -filter {name =~ "DAP*"}}
catch {rst -dap}
after 500

# Load the (already-programmed) bitstream — only if not done by HW Manager
catch {targets -set -filter {name =~ "xc7z020"}}
puts "\n\[1\] Loading bitstreams/cgra_top.bit ..."
if {[catch {fpga -file bitstreams/cgra_top.bit} err]} {
    puts "fpga -file error (continuing — may already be loaded): $err"
}
after 1000

# Halt A9 and run legacy ps7_init
catch {targets -set -filter {name =~ "ARM*Cortex-A9*#0"}}
catch {stop} e
puts "\n\[2\] stop: '$e'"
after 200

puts "\n\[3\] Sourcing legacy scripts/ps7_init.tcl ..."
source scripts/ps7_init.tcl
if {[catch {ps7_init} e]} { puts "ps7_init err: $e"; exit 1 }
if {[catch {ps7_post_config} e]} { puts "ps7_post_config err: $e"; exit 1 }
puts "  PS init complete."

# ────────────────────────────────────────────────────────────
puts "\n\[4\] Initial CGRA register state:"
foreach {label off} {
    DMA_CTRL    0x00
    DMA_STATUS  0x04
    DMA_ERROR   0x38
    IRQ_STATUS  0x30
    CU_STATUS   0x24
} {
    puts "  $label = [rd $off]"
}

# ────────────────────────────────────────────────────────────
puts "\n\[5\] Pre-fill DDR scratch (16 words @ 0x100000) ..."
for {set i 0} {$i < 16} {incr i} {
    set val [expr 0xA5A50000 + $i]
    mwr [expr $DDR_SCRATCH + ($i*4)] $val
}
puts "  DDR\[0..3\] = [mrd -value 0x00100000 4]"

# ────────────────────────────────────────────────────────────
puts "\n\[6\] Configure CGRA DMA: SRC=0x[format %X $DDR_SCRATCH] DST=0x[format %X $TILE_BCAST] SIZE=64"
# Clear DMA state first
wr $DMA_CTRL    0x0
wr $IRQ_STATUS  0x7      ;# W1C clears all IRQ bits
after 100
wr $DMA_SRC          $DDR_SCRATCH
wr $DMA_DST          $TILE_BCAST
wr $DMA_SRC_STRIDE   0x0
wr $DMA_ROWS         0x0
wr $DMA_COLS         0x0
wr $DMA_SIZE         64
puts "  DMA_SRC    = [rd $DMA_SRC]"
puts "  DMA_DST    = [rd $DMA_DST]"
puts "  DMA_SIZE   = [rd $DMA_SIZE]"

# ────────────────────────────────────────────────────────────
puts "\n\[7\] Kick DMA (CTRL=1) ..."
wr $DMA_CTRL 0x1
after 1
puts "  Immediately after kick:"
puts "    DMA_CTRL   = [rd $DMA_CTRL]"
puts "    DMA_STATUS = [rd $DMA_STATUS]"
puts "    DMA_ERROR  = [rd $DMA_ERROR]"

# ────────────────────────────────────────────────────────────
puts "\n\[8\] Poll DMA_STATUS for up to 50 reads (~1 second total) ..."
set done 0
for {set p 0} {$p < 50} {incr p} {
    set s [rd $DMA_STATUS]
    if {$p < 5 || $p == 25 || $p == 49} {
        puts "  poll $p: DMA_STATUS=$s"
    }
    # Strip "0x" prefix; check bit 1 (DONE)
    if {[string match "*0x*" $s]} {
        if {[scan $s "%x" v] == 1 || [scan $s "0x%x" v] == 1} {
            if {($v & 0x2) != 0} {
                puts "  DONE bit set at poll $p"
                set done 1
                break
            }
        }
    }
    after 20  ;# 20 ms between polls
}

# ────────────────────────────────────────────────────────────
puts "\n\[9\] Final state:"
foreach {label off} {
    DMA_CTRL    0x00
    DMA_STATUS  0x04
    DMA_SRC     0x08
    DMA_DST     0x0C
    DMA_SIZE    0x10
    DMA_ERROR   0x38
    IRQ_STATUS  0x30
    CU_STATUS   0x24
} {
    puts "  $label = [rd $off]"
}

if {$done} {
    puts "\n*** SUCCESS *** DMA completed. The DMA path WORKS with this combo."
    puts "    bitstream  = bitstreams/cgra_top.bit (MD5 24f7ad...)"
    puts "    ps7_init   = scripts/ps7_init.tcl (legacy)"
} else {
    puts "\n*** HANG *** DMA never asserted DONE bit."
    puts "    Use Vivado HW Manager to capture System ILA trace."
    puts "    Per senior §2 smoking guns:"
    puts "      - dbg_dma_fifo_full=1 + WVALID+!WREADY → HP0 backpressure"
    puts "      - dbg_dma_read_state=WAIT_RDATA (after AR done) → RVALID gone"
    puts "      - dbg_dma_busy=1 + no AXI VALID → internal FSM stuck"
}

exit
