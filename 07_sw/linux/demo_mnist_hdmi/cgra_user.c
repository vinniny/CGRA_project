/* cgra_user.c — see cgra_user.h. */

/* IMPORTANT: shim must be included BEFORE cgra.h so the CGRA_BASE override
 * lands before cgra.h's static inline cgra_wr/cgra_rd are emitted. */
#include "cgra_user.h"
#include "../../lib/cgra_baremetal_shim.h"
#include "../../baremetal/cgra.h"
#include "../../baremetal/cgra_kernels_cnn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

/* The shim's global is defined here (declared extern in the header). */
uintptr_t _cgra_shim_base = 0;

/* CMA stubs: cgra_driver.c references libcma's cma_alloc/cma_free/
 * cma_get_phy_addr unconditionally inside cgra_cma_alloc. We don't use
 * cgra_cma_alloc (we manage our own staging via /dev/mem) but the static
 * linker pulls in the references. Provide weak no-op stubs so the link
 * resolves. */
__attribute__((weak)) void *cma_alloc(uint32_t len, uint32_t cacheable) {
    (void)len; (void)cacheable; return NULL;
}
__attribute__((weak)) void  cma_free(void *buf) { (void)buf; }
__attribute__((weak)) unsigned long cma_get_phy_addr(void *buf) {
    (void)buf; return 0;
}

/* The FC1+FC2 INT16 weight blob, linked from demo_mnist_weights.S into
 * the .cnn_spm section. Layout (per quantize_cgra.py + demo_mnist_weights.S):
 *   bytes [0       .. 102399]  → FC1 weights (64 neurons × 400 INT32 words,
 *                                 each word = INT16 in low 16 bits)
 *   bytes [102400  .. 104959]  → FC2 weights (10 neurons × 64 words). */
extern const uint32_t cnn_spm_start[];
extern const uint32_t cnn_spm_end[];

#define FC1_BYTES       (CNN_FC1_N_OUTPUTS * CNN_FC1_SPM_BPN)   /* 102400 */
#define FC2_BYTES       (CNN_FC2_N_OUTPUTS * CNN_FC2_SPM_BPN)   /* 2560 */

int cgra_user_init(cgra_user_t *u)
{
    memset(u, 0, sizeof(*u));
    u->mem_fd = -1;
    u->dev.fd = -1;

    /* 1. CGRA APB — direct /dev/mem mmap at 0x43C80000.
     *    We deliberately avoid cgra_init() because it auto-picks /dev/uio0
     *    if present, and on this PetaLinux build the legacy DTB binds the
     *    UIO node at the wrong physical address (0x43C00000 = audio_codec
     *    in our bitstream; CGRA actually lives at 0x43C80000). Going
     *    straight to /dev/mem at CGRA_PHYS_BASE bypasses that DT mismatch. */
    int apb_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (apb_fd < 0) {
        perror("cgra_user: open /dev/mem (APB)");
        return -1;
    }
    void *regs = mmap(NULL, CGRA_REG_SPAN,
                      PROT_READ | PROT_WRITE,
                      MAP_SHARED, apb_fd, (off_t)CGRA_PHYS_BASE);
    if (regs == MAP_FAILED) {
        perror("cgra_user: mmap CGRA APB");
        close(apb_fd);
        return -1;
    }
    u->dev.regs       = (volatile uint32_t *)regs;
    u->dev.fd         = apb_fd;
    u->dev.map_size   = CGRA_REG_SPAN;
    u->dev.mode       = CGRA_MODE_DEVMEM;
    u->dev.phys_base  = CGRA_PHYS_BASE;
    cgra_shim_attach(&u->dev);
    fprintf(stderr, "cgra_user: APB mmap'd at %p (phys 0x%08X)\n",
            regs, CGRA_PHYS_BASE);

    /* CGRA may carry stale state from a previous user (e.g. another demo
     * left it mid-run). Soft-reset CU and clear any IRQ flags. */
    cgra_soft_reset(&u->dev);
    cgra_write(&u->dev, CGRA_IRQ_STATUS, 0xFFFFFFFFu);  /* W1C: clear all */

    /* 2. mmap the staging region at VA == PA so the kernels' inline
     *    `(uint32_t *)phys` pointer casts work. O_SYNC = uncached mapping
     *    (critical for DMA buffers: writes complete before DMA reads). */
    u->mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (u->mem_fd < 0) {
        perror("cgra_user: open /dev/mem");
        cgra_close(&u->dev);
        return -1;
    }

    u->staging_va = mmap((void *)(uintptr_t)CGRA_STAGING_PHYS,
                         CGRA_STAGING_SIZE,
                         PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_FIXED,
                         u->mem_fd, (off_t)CGRA_STAGING_PHYS);
    if (u->staging_va == MAP_FAILED) {
        perror("cgra_user: mmap CGRA staging");
        close(u->mem_fd); u->mem_fd = -1;
        cgra_close(&u->dev);
        return -1;
    }
    if ((uintptr_t)u->staging_va != CGRA_STAGING_PHYS) {
        fprintf(stderr, "cgra_user: mmap returned VA=%p but we asked for 0x%lX\n",
                u->staging_va, CGRA_STAGING_PHYS);
        munmap(u->staging_va, CGRA_STAGING_SIZE);
        close(u->mem_fd); u->mem_fd = -1;
        cgra_close(&u->dev);
        return -1;
    }

    /* 3. Stage the weight blob from .cnn_spm into the DMA region. */
    size_t blob_bytes = (size_t)((uintptr_t)cnn_spm_end - (uintptr_t)cnn_spm_start);
    if (blob_bytes < FC1_BYTES + FC2_BYTES) {
        fprintf(stderr, "cgra_user: weight blob too small (%zu < %u)\n",
                blob_bytes, FC1_BYTES + FC2_BYTES);
        cgra_user_close(u);
        return -1;
    }
    memcpy((void *)(uintptr_t)CGRA_FC1_W_PHYS, cnn_spm_start, FC1_BYTES);
    memcpy((void *)(uintptr_t)CGRA_FC2_W_PHYS,
           (const uint8_t *)cnn_spm_start + FC1_BYTES, FC2_BYTES);
    asm volatile("dsb" ::: "memory");

    /* 4. Build SG-DMA chains in the staging region.
     *    Note we call cnn_fc_build_chains directly (not the FC1/FC2 wrappers
     *    in cgra_kernels_cnn.h) because the wrappers hardcode the bare-metal
     *    chain addresses (0x114000 / 0x115000) which we can't access from
     *    Linux. */
    if (cnn_fc_build_chains(CGRA_FC1_CHAINS_PHYS,
                            CGRA_FC1_W_PHYS,
                            CNN_FC1_N_OUTPUTS,
                            CNN_FC1_N_GROUPS,
                            CNN_FC1_SPM_BPN)) {
        fprintf(stderr, "cgra_user: FC1 build_chains failed\n");
        cgra_user_close(u);
        return -1;
    }
    if (cnn_fc_build_chains(CGRA_FC2_CHAINS_PHYS,
                            CGRA_FC2_W_PHYS,
                            CNN_FC2_N_OUTPUTS,
                            CNN_FC2_N_GROUPS,
                            CNN_FC2_SPM_BPN)) {
        fprintf(stderr, "cgra_user: FC2 build_chains failed\n");
        cgra_user_close(u);
        return -1;
    }

    u->initialized = 1;
    return 0;
}

int cgra_user_run_inference(cgra_user_t *u,
                            const int32_t act400[400],
                            const int32_t act64[64],
                            int32_t fc2_out[10])
{
    if (!u->initialized) return -1;

    /* Stage act400, run FC1 (output discarded — matches demo_mnist_sweep). */
    memcpy((void *)(uintptr_t)CGRA_ACT400_PHYS, act400, 400 * sizeof(int32_t));
    memcpy((void *)(uintptr_t)CGRA_ACT64_PHYS,  act64,   64 * sizeof(int32_t));
    asm volatile("dsb" ::: "memory");

    /* tile_preload wrappers don't use the hardcoded chain addresses, just
     * cgra_dma + N_INPUTS — safe to call directly. */
    if (cnn_fc1_tile_preload(CGRA_ACT400_PHYS)) return -1;
    int32_t fc1_dummy[4];
    for (uint32_t g = 0; g < CNN_FC1_N_GROUPS; ++g) {
        if (cnn_fc_run_group(CGRA_FC1_CHAINS_PHYS,
                             (int)g,
                             CNN_FC1_LOOP_COUNT,
                             CNN_FC1_N_OUTPUTS,
                             fc1_dummy)) return -1;
    }

    /* FC2 from pre-computed act64 (fixture provides this). */
    if (cnn_fc2_tile_preload(CGRA_ACT64_PHYS)) return -1;
    int32_t buf[12] = {0};
    for (uint32_t g = 0; g < CNN_FC2_N_GROUPS; ++g) {
        int32_t grp[4];
        if (cnn_fc_run_group(CGRA_FC2_CHAINS_PHYS,
                             (int)g,
                             CNN_FC2_LOOP_COUNT,
                             CNN_FC2_N_OUTPUTS,
                             grp)) return -1;
        for (int r = 0; r < 4 && (int)(g * 4u + (uint32_t)r) < (int)CNN_FC2_N_OUTPUTS; ++r) {
            buf[g * 4u + r] = grp[r];
        }
    }
    for (int i = 0; i < 10; ++i) fc2_out[i] = buf[i];
    return 0;
}

void cgra_user_close(cgra_user_t *u)
{
    if (u->staging_va && u->staging_va != MAP_FAILED) {
        munmap(u->staging_va, CGRA_STAGING_SIZE);
        u->staging_va = NULL;
    }
    if (u->mem_fd >= 0) {
        close(u->mem_fd);
        u->mem_fd = -1;
    }
    cgra_close(&u->dev);
    u->initialized = 0;
}

int cgra_user_argmax(const int32_t *v, int n)
{
    int best = 0;
    for (int i = 1; i < n; ++i) if (v[i] > v[best]) best = i;
    return best;
}
