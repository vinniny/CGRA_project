/* =========================================================================
 * start.s — Minimal ARM Cortex-A9 startup for Zynq-7000
 *
 * Vector table at 0x00 (OCM low region) so any exception lands in our
 * abort_loop trap rather than running off into garbage memory.
 * ========================================================================= */
    .section .vectors, "ax"
    .global _vectors
_vectors:
    b   _start          /* 0x00 reset            */
    b   trap_undef      /* 0x04 undefined        */
    b   trap_swi        /* 0x08 software intr    */
    b   trap_pabt       /* 0x0C prefetch abort   */
    b   trap_dabt       /* 0x10 data abort       */
    b   trap_resv       /* 0x14 reserved         */
    b   trap_irq        /* 0x18 IRQ              */
    b   trap_fiq        /* 0x1C FIQ              */

trap_undef:
    mov r11, #0x01
    b   abort_loop
trap_swi:
    mov r11, #0x02
    b   abort_loop
trap_pabt:
    mov r11, #0x03
    b   abort_loop
trap_dabt:
    mov r11, #0x04
    b   abort_loop
trap_resv:
    mov r11, #0x05
    b   abort_loop
trap_irq:
    mov r11, #0x06
    b   abort_loop
trap_fiq:
    mov r11, #0x07
    b   abort_loop

/* abort_loop: park here. r11 holds the trap type, lr holds the faulting PC. */
abort_loop:
    b   abort_loop

    .section .init, "ax"
    .global _start
    .type   _start, %function

_start:
    /* Disable IRQ and FIQ during init */
    mrs     r0, cpsr
    orr     r0, r0, #0xC0       /* I=1, F=1 */
    msr     cpsr_c, r0

    /* Set vector base register (VBAR) to 0x4000 (start of OCM where our
     * .vectors section lives). Vectors are 32-byte aligned per ARMv7-A. */
    ldr     r0, =_vector_base
    mcr     p15, 0, r0, c12, c0, 0

    /* Enable VFP/NEON coprocessors (cp10, cp11) — required because gcc
     * with -mfpu=vfpv3 generates VFP loads for literal constants. */
    mrc     p15, 0, r0, c1, c0, 2       /* read CPACR */
    orr     r0, r0, #(0xF << 20)        /* cp10 + cp11 full access */
    mcr     p15, 0, r0, c1, c0, 2       /* write CPACR */
    isb

    /* Enable VFP via FPEXC.EN (bit 30) */
    mov     r0, #0x40000000
    vmsr    fpexc, r0

    /* Set stack pointer (grows down from STACK_TOP in OCM) */
    ldr     sp, =_stack_top

    /* Clear BSS section */
    ldr     r0, =__bss_start
    ldr     r1, =__bss_end
    mov     r2, #0
bss_loop:
    cmp     r0, r1
    bge     bss_done
    str     r2, [r0], #4
    b       bss_loop
bss_done:

    /* Jump to C main */
    bl      main

    /* If main returns, loop forever */
hang:
    wfi
    b       hang

    .size _start, . - _start
