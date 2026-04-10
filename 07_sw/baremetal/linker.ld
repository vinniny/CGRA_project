/* =========================================================================
 * linker.ld — Zynq-7000 bare-metal linker script
 *
 * Uses OCM (On-Chip Memory) — always accessible, no DDR init needed.
 * Zynq XC7Z020 OCM: 256KB at 0x00000000-0x0002FFFF (boot-time low mapping)
 *
 * Layout:
 *   0x00000000-0x000000FF: exception vectors (simple traps, avoid by offset)
 *   0x00004000-0x0001EFFF: code + data (~76KB, more than enough for 5KB ELF)
 *   0x0001F000-0x0001FFFF: stack (4KB, grows down)
 *
 * DMA staging: DDR_STAGE in cgra.h → 0x00800000 (well into DDR — written
 * by the ARM at runtime after OCM code is running, DDR accessible from ARM
 * even if not via JTAG DAP).
 * ========================================================================= */
ENTRY(_start)

MEMORY {
    OCM  (rwx) : ORIGIN = 0x00004000, LENGTH = 120K
}

_stack_top      = 0x0001FFC0;  /* Supervisor stack top — in OCM */
_irq_stack_top  = 0x0001EFC0;  /* IRQ-mode stack top, 4 KB below SVC stack */
_vector_base    = 0x00004000;  /* Vectors live at start of OCM, VBAR points here */

/* ── Symbols the Vitis BSP cache helpers reference ──────────────────────
 * Xil_L1DCacheInvalidate temporarily swaps SP to __undef_stack to avoid
 * losing in-flight stack writes during the cache flush sweep. We point
 * the symbols at the existing IRQ/SVC stack region — they will only
 * ever be touched during cache ops, which our demo serializes with
 * normal stack use, so any reasonable in-OCM address works. */
__undef_stack   = 0x0001EFC0;
_stack_end      = 0x0001E000;

SECTIONS {
    /DISCARD/ : {
        *(.note.gnu.build-id)
        *(.ARM.attributes)
    }

    .vectors 0x00004000 : {
        KEEP(*(.vectors))
        . = ALIGN(32);
    } > OCM

    .init : {
        KEEP(*(.init))
    } > OCM

    .text : {
        *(.text*)
        *(.rodata*)
    } > OCM

    .data : {
        *(.data*)
    } > OCM

    .bss : {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    } > OCM
}
