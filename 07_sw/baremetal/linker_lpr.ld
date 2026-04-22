/* =========================================================================
 * linker_lpr.ld — Zynq-7000 bare-metal linker script for demo_lpr.elf
 *
 * OCM (120 KB):  code + rodata (test images) + BSS (GoldenContext ~47 KB)
 * DDR (at 0x800000):  .lpr_weights section — golden_weights.bin (99,192 B)
 *
 * XSDB loads each ELF section to its LMA address.  The DDR controller is
 * already initialised by ps7_init.tcl at program time, so 0x800000 is
 * accessible before the ARM begins execution.
 *
 * SVC stack: 8 KB (0x1DFC0..0x1FFC0) — needed for golden_infer's 3 KB
 * local input_f[784] plus nested-call overhead.
 * IRQ stack: 4 KB (0x1CFC0..0x1DFC0) — allocated even though demo_lpr
 * runs in polling mode; start.s uses _irq_stack_top unconditionally.
 * ========================================================================= */
ENTRY(_start)

MEMORY {
    OCM (rwx) : ORIGIN = 0x00004000, LENGTH = 120K
    DDR (r)   : ORIGIN = 0x00800000, LENGTH = 256K
}

/* Stack tops — stacks grow downward */
_stack_top      = 0x0001FFC0;  /* SVC stack top  (8 KB for golden_infer) */
_irq_stack_top  = 0x0001DFC0;  /* IRQ stack top  (4 KB) */
_vector_base    = 0x00004000;  /* VBAR points here */

/* Vitis BSP cache helper symbol — points into IRQ stack region */
__undef_stack   = 0x0001DFC0;
_stack_end      = 0x0001CC00;

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

    /* GoldenWeights binary linked into DDR via demo_lpr_weights.S .incbin.
     * LMA = VMA = 0x800000.  XSDB writes this section to DDR at load time. */
    .lpr_weights : {
        *(.lpr_weights)
    } > DDR
}
