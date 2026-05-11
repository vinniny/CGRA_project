/* cgra_user.h — Linux userspace wrapper for the bare-metal CGRA FC1/FC2
 * MNIST kernels. Bridges the existing `cgra_kernels_cnn.h` API (which
 * assumes identity-mapped phys=virt) to Linux mmap-via-/dev/mem.
 *
 * The wrapper:
 *   1. Opens the CGRA APB (cgra_init) and binds the bare-metal shim
 *      (cgra_shim_attach) so cgra_wr/cgra_rd route through the mmap'd
 *      register window.
 *   2. mmap()s /dev/mem with MAP_FIXED so virtual == physical for our
 *      staging region — the bare-metal kernels do `(uint32_t *)phys`
 *      pointer casts internally; with VA=PA that works directly.
 *   3. Stages the FC1+FC2 weight blob (cnn_spm_start[]) into the
 *      reserved region and builds the FC1/FC2 SG-DMA chains there.
 *
 * All addresses live in the reserved-memory framebuffer region
 * (0x1F000000-0x1F7FFFFF). The first 921 KB (0x1F000000+) is the VDMA
 * display framebuffer (managed by fb_lib). We use 0x1F100000+ for CGRA
 * staging — 128 KB of which is mmap'd in a single MAP_FIXED region.
 */
#ifndef CGRA_USER_H
#define CGRA_USER_H

#include <stdint.h>
#include <stddef.h>

#include "../../driver/cgra_driver.h"

/* Physical layout of the CGRA staging region.
 *
 * IMPORTANT: top nibble MUST be 0 (DDR/AXI prefix). The CGRA DMA engine's
 * cgra_dma_engine.sv treats dst[31:28]==1 as TILE memory and 4'h2 as CONFIG
 * — so addresses in our reserved-memory carve-out at 0x1F100000+ get
 * silently redirected to internal CGRA memory, which is why the chain reads
 * return zeros and inference produces all-zero results.
 *
 * 0x10000000 is in System RAM (PYNQ-Z2 has 512 MB DDR at 0x00000000-0x1FFFFFFF).
 * The kernel manages this range, so MAP_FIXED here is technically corrupting
 * whatever process happens to have pages there. Safe enough for a single
 * demo run on an otherwise-idle board. For production, reserve this region
 * in the device tree (memreserve@10000000) so the kernel never allocates
 * pages there. */
/* 0x08000000 = 128 MB into 512 MB DDR. Bits[31:28] = 0 → DDR/AXI prefix.
 * Past the kernel image (~12 MB) and past most boot allocations. */
#define CGRA_STAGING_PHYS       0x08000000UL
#define CGRA_STAGING_SIZE       0x00020000UL  /* 128 KB */

#define CGRA_FC1_W_PHYS         (CGRA_STAGING_PHYS + 0x00000UL)  /* 102,400 B (25 pages) */
#define CGRA_FC2_W_PHYS         (CGRA_STAGING_PHYS + 0x19000UL)  /* 2,560 B   (1 page) */
#define CGRA_ACT400_PHYS        (CGRA_STAGING_PHYS + 0x1A000UL)  /* 1,600 B   (1 page) */
#define CGRA_ACT64_PHYS         (CGRA_STAGING_PHYS + 0x1B000UL)  /* 256 B     (1 page) */
#define CGRA_FC1_CHAINS_PHYS    (CGRA_STAGING_PHYS + 0x1C000UL)  /* 1,824 B   (1 page) */
#define CGRA_FC2_CHAINS_PHYS    (CGRA_STAGING_PHYS + 0x1D000UL)  /* 992 B     (1 page) */

typedef struct {
    cgra_dev_t  dev;
    int         mem_fd;
    void       *staging_va;   /* virtual == physical via MAP_FIXED */
    int         initialized;
} cgra_user_t;

/* Initialize: opens CGRA APB, mmaps staging region, copies weight blob,
 * builds FC1+FC2 SG-DMA chains. Call once at startup.
 * Returns 0 on success, -1 on error. */
int  cgra_user_init(cgra_user_t *u);

/* Run one full inference: FC1(act400) (output discarded) then FC2(act64)
 * → fc2_out[10]. Mirrors demo_mnist_sweep.c::run_image: the sweep feeds
 * pre-computed act64 directly so FC1 errors don't compound into FC2.
 * Returns 0 on success, -1 on CGRA timeout. */
int  cgra_user_run_inference(cgra_user_t *u,
                             const int32_t act400[400],
                             const int32_t act64[64],
                             int32_t fc2_out[10]);

void cgra_user_close(cgra_user_t *u);

/* Argmax helper. Returns the index 0..n-1 of the max element. */
int  cgra_user_argmax(const int32_t *v, int n);

#endif /* CGRA_USER_H */
