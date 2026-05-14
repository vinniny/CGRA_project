/* =============================================================================
 * lpr_fc_probe.c — Compile-probe + smoke for FC-on-CGRA on Linux.
 *
 * Goal: prove that the baremetal FC kernel (cgra_kernels_lpr.h) compiles and
 * runs correctly in Linux user-space via the cgra_baremetal_shim. If this
 * passes, lpr_eval -c becomes a small integration step.
 *
 * Steps:
 *   1. Open CGRA via cgra_driver.
 *   2. cgra_shim_attach() so CGRA_BASE routes to mmap'd regs.
 *   3. Allocate uncached DDR scratch via /dev/mem at 0x3FFF0000 (proven good
 *      by cgra_dmatest).
 *   4. Run lpr_fc_init_chain() → lpr_fc_acc_clr() → one lpr_fc_program_chunk()
 *      → cgra_dma() of dummy inputs → cgra_cu_start/wait → lpr_fc_readout().
 *   5. Print the 4 result words. Anything other than 0xAAAAAAAA = FC plumbing
 *      is alive.
 * ============================================================================= */
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "cgra_baremetal_shim.h"   /* MUST come before cgra.h */
#include "cgra.h"
#include "cgra_kernels_lpr.h"

#define DDR_SCRATCH_PHYS  0x3FFF0000u
#define DDR_SCRATCH_SIZE  0x1000u    /* one page is plenty */

#define STAGING_OFF       0x000      /* lpr_fc_*: PE-config DMA staging */
#define INPUTS_OFF        0x400      /* 16 INT32 inputs for one chunk */

int main(void)
{
    cgra_dev_t dev = {0};
    if (cgra_init(&dev, NULL) < 0) { perror("cgra_init"); return 1; }
    cgra_shim_attach(&dev);
    fprintf(stderr, "[probe] CGRA mmap'd, shim base=%p\n", (void *)_cgra_shim_base);

    /* Uncached DDR scratch with VA == PA. The baremetal kernel functions
     * (cgra_config_pe etc.) treat staging_ddr as a direct CPU pointer to write
     * config words before issuing cgra_dma() — so VA must equal PA for those
     * unmodified bare-metal paths to work. MAP_FIXED at the physical address
     * forces VA = PA = 0x3FFF0000. */
    int memfd = open("/dev/mem", O_RDWR | O_SYNC);
    if (memfd < 0) { perror("/dev/mem"); return 1; }
    void *scratch = mmap((void *)(uintptr_t)DDR_SCRATCH_PHYS, DDR_SCRATCH_SIZE,
                         PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_FIXED, memfd, DDR_SCRATCH_PHYS);
    if (scratch == MAP_FAILED) { perror("mmap MAP_FIXED"); return 1; }
    if ((uintptr_t)scratch != DDR_SCRATCH_PHYS) {
        fprintf(stderr, "MAP_FIXED returned VA=%p, expected 0x%08x\n",
                scratch, DDR_SCRATCH_PHYS);
        return 1;
    }
    memset(scratch, 0, DDR_SCRATCH_SIZE);
    fprintf(stderr, "[probe] scratch va==pa=0x%08x\n", DDR_SCRATCH_PHYS);

    /* Lay 16 input words into DDR at INPUTS_OFF */
    int32_t *inputs = (int32_t *)((uint8_t *)scratch + INPUTS_OFF);
    for (int i = 0; i < 16; i++) inputs[i] = i + 1;     /* 1..16 */

    /* Build a synthetic INT16 weight array — 1 per (input, neuron) */
    static int16_t fc_w_dummy[LPR_FC_N_INPUTS * LPR_FC_N_CLASSES];
    for (int i = 0; i < LPR_FC_N_INPUTS * LPR_FC_N_CLASSES; i++)
        fc_w_dummy[i] = 1;     /* sum-of-inputs reference */

    uint32_t staging_ddr = DDR_SCRATCH_PHYS + STAGING_OFF;
    uint32_t inputs_ddr  = DDR_SCRATCH_PHYS + INPUTS_OFF;

    /* Step 0: sanity DMA via this scratch region — same pattern as cgra_dmatest
     * but using the baremetal cgra_dma() through the shim. If this hangs, the
     * shim itself is wrong; bail before touching FC kernel functions. */
    {
        uint32_t *src = (uint32_t *)((uint8_t *)scratch + 0x800);
        uint32_t *dst = (uint32_t *)((uint8_t *)scratch + 0x900);
        for (int i = 0; i < 16; i++) src[i] = 0xDEAD0000u | (uint32_t)i;
        memset(dst, 0xAA, 64);
        const uint32_t tile_b0 = CGRA_PFX_TILE;          /* 0x10000000 = bank 0 */
        fprintf(stderr, "[probe] sanity: cgra_dma DDR→TILE_BANK(0)\n");
        if (cgra_dma(DDR_SCRATCH_PHYS + 0x800, tile_b0, 64u) < 0) {
            fprintf(stderr, "  shim DMA path broken\n"); return 1;
        }
        fprintf(stderr, "[probe] sanity: cgra_dma TILE_BANK(0)→DDR\n");
        if (cgra_dma(tile_b0, DDR_SCRATCH_PHYS + 0x900, 64u) < 0) {
            fprintf(stderr, "  shim DMA write broken\n"); return 1;
        }
        int ok = 0; for (int i = 0; i < 16; i++) if (dst[i] == src[i]) ok++;
        fprintf(stderr, "[probe] sanity: %d/16 words match\n", ok);
        if (ok != 16) { fprintf(stderr, "  shim DMA data corruption\n"); return 1; }
    }

    /* Run one chunk × one group of the FC kernel — uses the baremetal kernel
     * verbatim through the shim. */
    fprintf(stderr, "[probe] lpr_fc_init_chain\n");
    if (lpr_fc_init_chain(staging_ddr) < 0) { fprintf(stderr, "init_chain failed\n"); return 1; }

    fprintf(stderr, "[probe] lpr_fc_acc_clr\n");
    if (lpr_fc_acc_clr(staging_ddr) < 0)    { fprintf(stderr, "acc_clr failed\n"); return 1; }

    fprintf(stderr, "[probe] lpr_fc_program_chunk c=0 g=0\n");
    if (lpr_fc_program_chunk(fc_w_dummy, 0, 0, staging_ddr) < 0) {
        fprintf(stderr, "program_chunk failed\n"); return 1;
    }

    fprintf(stderr, "[probe] cgra_dma inputs → tile bcast\n");
    if (cgra_dma(inputs_ddr, CGRA_TILE_BCAST, 64u) < 0) {
        fprintf(stderr, "input DMA failed\n"); return 1;
    }

    fprintf(stderr, "[probe] cgra_cu_start + wait\n");
    cgra_cu_start();
    if (cgra_cu_wait(1000000u) < 0) { fprintf(stderr, "CU timeout\n"); return 1; }

    int32_t result[4];
    fprintf(stderr, "[probe] lpr_fc_readout\n");
    if (lpr_fc_readout(staging_ddr, result) < 0) { fprintf(stderr, "readout failed\n"); return 1; }

    fprintf(stderr, "[probe] result = [%d, %d, %d, %d]\n",
            result[0], result[1], result[2], result[3]);
    /* Expected: each neuron's accumulator after one chunk of 16 inputs with
     * unit weights = sum(1..16) × LPR_POOL2_ACT_SCALE = 136 × 8 = 1088? Actually
     * this dummy doesn't apply the act-scale; just expect 136 (= 16*17/2). */
    fprintf(stderr, "[probe] expected ≈ 136 per row (sum of 1..16 with unit weights)\n");

    munmap(scratch, DDR_SCRATCH_SIZE);
    close(memfd);
    cgra_close(&dev);
    return 0;
}
