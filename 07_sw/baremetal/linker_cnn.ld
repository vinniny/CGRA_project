/* =========================================================================
 * linker_cnn.ld — Zynq-7000 bare-metal linker script for CNN smoke/demo ELFs
 *
 * Extends linker.ld with DDR sections for CNN weight blobs.
 * XSDB loads each ELF section to its LMA; DDR is accessible from ARM
 * immediately after ps7_init runs (no explicit DDR init required).
 *
 * Layout:
 *   OCM  0x004000 : code + data (~120KB)
 *   DDR  0x200000 : .cnn_spm  — FC SPM weights (104960 bytes, 0x19A00 B)
 * ========================================================================= */
ENTRY(_start)

MEMORY {
    OCM      (rwx) : ORIGIN = 0x00004000, LENGTH = 120K
    DDR_CNN   (r)  : ORIGIN = 0x00200000, LENGTH = 256K   /* FC SPM weights */
    DDR_DATA  (r)  : ORIGIN = 0x00240000, LENGTH = 64M    /* sweep fixture / large rodata */
}

_stack_top      = 0x0001FFC0;
_irq_stack_top  = 0x0001EFC0;
_vector_base    = 0x00004000;
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

    /* FC SPM weight blob (104960 bytes) at DDR 0x200000 */
    .cnn_spm : {
        *(.cnn_spm)
    } > DDR_CNN

    /* Large rodata (sweep fixture etc.) at DDR 0x240000+ */
    .cnn_sweep : {
        *(.cnn_sweep)
    } > DDR_DATA
}
