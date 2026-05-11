/* test_probe.c — diagnostic for M3 all-zero FC2 issue.
 *
 * After cgra_user_init, we check whether the chain memory and weight blob
 * actually landed in the staging region (i.e. CPU writes are visible at
 * the physical address the CGRA DMA reads from). Also reads CGRA registers
 * before/after a single FC2 run_group to see what the CGRA is actually doing.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cgra_user.h"
/* Shim MUST come before any cgra.h-using kernels in this TU so CGRA_BASE
 * resolves to the runtime mmap'd pointer (not the compile-time physical). */
#include "../../lib/cgra_baremetal_shim.h"
#include "../../driver/cgra_driver.h"
#include "../../baremetal/cgra.h"
#include "../../baremetal/cgra_kernels_cnn.h"
#include "mnist_sweep_fixture.h"

static void dump_words(const char *label, volatile uint32_t *p, int n) {
    printf("%s:", label);
    for (int i = 0; i < n; ++i) printf(" 0x%08X", p[i]);
    printf("\n");
}

int main(void)
{
    cgra_user_t u;
    if (cgra_user_init(&u) < 0) return 1;

    printf("\n=== staging region content after init ===\n");
    /* FC1 weights — first 8 words should be INT16 weights packed in low 16 */
    dump_words("FC1_W[0..7]",
               (volatile uint32_t *)(uintptr_t)CGRA_FC1_W_PHYS, 8);
    dump_words("FC2_W[0..7]",
               (volatile uint32_t *)(uintptr_t)CGRA_FC2_W_PHYS, 8);

    /* FC1 chains start with 8-word opword area */
    dump_words("FC1_chains[0..7] (opwords)",
               (volatile uint32_t *)(uintptr_t)CGRA_FC1_CHAINS_PHYS, 8);
    dump_words("FC2_chains[0..7] (opwords)",
               (volatile uint32_t *)(uintptr_t)CGRA_FC2_CHAINS_PHYS, 8);

    /* SG descriptors at +0x20 (acc_clr first descriptor: 16 bytes = 4 words) */
    dump_words("FC1_chains[+0x20] (acc_clr d0)",
               (volatile uint32_t *)(uintptr_t)(CGRA_FC1_CHAINS_PHYS + 0x20), 4);

    /* SPM preload chain for group 0 at +0x320 */
    dump_words("FC1_chains[+0x320] (SPM g0 d0)",
               (volatile uint32_t *)(uintptr_t)(CGRA_FC1_CHAINS_PHYS + 0x320), 4);
    dump_words("FC2_chains[+0x320] (SPM g0 d0)",
               (volatile uint32_t *)(uintptr_t)(CGRA_FC2_CHAINS_PHYS + 0x320), 4);
    dump_words("FC2_chains[+0x320 + 0x10] (SPM g0 d1)",
               (volatile uint32_t *)(uintptr_t)(CGRA_FC2_CHAINS_PHYS + 0x330), 4);

    /* Copy act400/act64 like run_inference does */
    memcpy((void *)(uintptr_t)CGRA_ACT400_PHYS, sweep_act400[0], 1600);
    memcpy((void *)(uintptr_t)CGRA_ACT64_PHYS,  sweep_act64[0],   256);
    asm volatile("dsb" ::: "memory");

    printf("\n=== activation staging after memcpy ===\n");
    dump_words("act400[0..7]",
               (volatile uint32_t *)(uintptr_t)CGRA_ACT400_PHYS, 8);
    dump_words("act64[0..7]",
               (volatile uint32_t *)(uintptr_t)CGRA_ACT64_PHYS, 8);

    printf("\n=== CGRA registers before tile_preload ===\n");
    printf("  CU_STATUS  : 0x%08X\n", cgra_read(&u.dev, CGRA_CU_STATUS));
    printf("  DMA_STATUS : 0x%08X\n", cgra_read(&u.dev, CGRA_DMA_STATUS));
    printf("  RESULT_ROW0: 0x%08X\n", cgra_read(&u.dev, CGRA_RESULT_ROW0));
    printf("  RESULT_ROW1: 0x%08X\n", cgra_read(&u.dev, CGRA_RESULT_ROW1));

    /* Sanity: DMA the tile contents back to DDR after a preload, check
     * that the activations actually landed in the tile bank. */
    printf("\n=== tile readback sanity ===\n");
    if (cnn_fc2_tile_preload(CGRA_ACT64_PHYS) == 0) {
        printf("  tile_preload(act64) OK\n");
        /* DMA bank 0 [0..7 words] back to a known DDR slot for inspection */
        const uint32_t READBACK_PHYS = CGRA_ACT64_PHYS + 0x200;
        memset((void *)(uintptr_t)READBACK_PHYS, 0xCC, 32);
        asm volatile("dsb" ::: "memory");
        /* DMA src = tile bank 0 (CGRA_TILE_BANK(0) = 0x10000000), dst = DDR */
        if (cgra_dma(0x10000000, READBACK_PHYS, 32) == 0) {
            dump_words("  tile bank0[0..7] readback",
                       (volatile uint32_t *)(uintptr_t)READBACK_PHYS, 8);
        } else {
            printf("  tile readback DMA failed\n");
        }
    } else {
        printf("  tile_preload(act64) failed\n");
    }

    /* Run one FC2 group 0 and read results */
    printf("\n=== single FC2 group 0 run ===\n");
    if (cnn_fc2_tile_preload(CGRA_ACT64_PHYS)) {
        printf("  FAIL: tile_preload timed out\n");
        cgra_user_close(&u);
        return 2;
    }
    printf("  tile_preload OK\n");

    int32_t grp[4];
    int rc = cnn_fc_run_group(CGRA_FC2_CHAINS_PHYS, 0,
                              CNN_FC2_LOOP_COUNT,
                              CNN_FC2_N_OUTPUTS, grp);
    printf("  run_group rc=%d  result={%d, %d, %d, %d}\n",
           rc, grp[0], grp[1], grp[2], grp[3]);
    printf("  CU_STATUS  after = 0x%08X\n", cgra_read(&u.dev, CGRA_CU_STATUS));
    printf("  DMA_STATUS after = 0x%08X\n", cgra_read(&u.dev, CGRA_DMA_STATUS));
    printf("  CU_CYCLES  : 0x%08X\n", cgra_read(&u.dev, CGRA_CU_CYCLES));
    printf("  RESULT_ROW0..3: 0x%08X 0x%08X 0x%08X 0x%08X\n",
           cgra_read(&u.dev, CGRA_RESULT_ROW0),
           cgra_read(&u.dev, CGRA_RESULT_ROW1),
           cgra_read(&u.dev, CGRA_RESULT_ROW2),
           cgra_read(&u.dev, CGRA_RESULT_ROW3));

    cgra_user_close(&u);
    return 0;
}
