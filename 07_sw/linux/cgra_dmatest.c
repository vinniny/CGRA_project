/* =============================================================================
 * cgra_dmatest.c — Validate CGRA M_AXI ↔ DDR path from Linux user-space.
 *
 * Strategy: allocate one MAP_ANONYMOUS|MAP_LOCKED|MAP_POPULATE page, look up
 * its physical address via /proc/self/pagemap, hand the PA to the CGRA DMA
 * engine. The kernel will not reclaim or remap a locked page, so the CGRA's
 * AXI master can safely read/write into our process's memory.
 *
 * Test: write pattern to DDR[off=0..63], DMA it into tile bank 0, DMA it back
 * to DDR[off=128..191], compare. Round-trip verifies M_AXI master path
 * through S_AXI_GP1 reaches our pinned page.
 *
 * Build: make -C 07_sw/linux dmatest
 * Run:   /home/root/cgra/cgra_dmatest
 * ============================================================================= */
#define _DEFAULT_SOURCE
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/syscall.h>

#include "cgra_driver.h"

#define PAGE_SIZE  4096

/* ARM-specific cacheflush syscall — flushes BOTH d-cache (clean to PoC)
 * and i-cache for the given VA range. There is no glibc wrapper. */
#ifndef __ARM_NR_cacheflush
#define __ARM_NR_cacheflush  (0x0f0000 + 2)
#endif
static inline int arm_cacheflush(void *start, void *end, int flags)
{
    return (int)syscall(__ARM_NR_cacheflush, start, end, flags);
}

/* Resolve virtual → physical address using /proc/self/pagemap.
 * Returns 0 on success, sets *phys_out to the physical address. */
static int virt_to_phys(void *virt, uint64_t *phys_out)
{
    int fd = open("/proc/self/pagemap", O_RDONLY);
    if (fd < 0) { perror("open pagemap"); return -1; }

    uintptr_t va  = (uintptr_t)virt;
    uintptr_t off = (va / PAGE_SIZE) * sizeof(uint64_t);
    uint64_t  ent;

    if (lseek(fd, (off_t)off, SEEK_SET) == (off_t)-1) { perror("lseek"); close(fd); return -1; }
    if (read(fd, &ent, sizeof(ent)) != sizeof(ent))   { perror("read");  close(fd); return -1; }
    close(fd);

    if (!(ent & (1ull << 63))) {
        fprintf(stderr, "page not present (entry=0x%016llx)\n", (unsigned long long)ent);
        return -1;
    }
    uint64_t pfn = ent & ((1ull << 55) - 1);
    *phys_out = (pfn * PAGE_SIZE) + (va & (PAGE_SIZE - 1));
    return 0;
}

int main(void)
{
    cgra_dev_t dev = {0};
    if (cgra_init(&dev, NULL) < 0) {
        fprintf(stderr, "cgra_init failed\n");
        return 1;
    }
    fprintf(stderr, "[dmatest] CGRA mode=%d phys=0x%08x\n", dev.mode, dev.phys_base);

    /* Map an uncached page from /dev/mem at the top of CMA-reserved DDR
     * (0x30000000-0x3FFFFFFF). O_SYNC + MAP_SHARED gives us a strongly-ordered
     * uncacheable mapping — neither L1 nor L2 holds our writes — so CGRA M_AXI
     * (which doesn't snoop) sees the same DRAM the CPU writes to. The chosen
     * 0x3FFF0000 address is at the top of CMA, very unlikely to be in active
     * use by any kernel DMA driver. */
    const uint32_t phys = 0x3FFF0000u;
    int memfd = open("/dev/mem", O_RDWR | O_SYNC);
    if (memfd < 0) { perror("open /dev/mem"); return 1; }
    void *buf = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, phys);
    if (buf == MAP_FAILED) { perror("mmap /dev/mem"); close(memfd); return 1; }
    memset(buf, 0, PAGE_SIZE);
    fprintf(stderr, "[dmatest] uncached devmem va=%p pa=0x%08x\n", buf, phys);

    /* Lay out: src @ +0x000 (64 B), dst @ +0x080 (64 B clear). */
    uint32_t *src = (uint32_t *)buf;
    uint32_t *dst = (uint32_t *)((uint8_t *)buf + 0x80);
    for (int i = 0; i < 16; i++) src[i] = 0xCAFE0000u | (uint32_t)i;
    memset(dst, 0xAA, 64);

    /* Uncached mapping — no flush needed before CGRA reads. */

    /* Round-trip via tile bank 0. */
    uint32_t tile_dst = TILE_BANK(0);             /* 0x10000000 */
    uint32_t ddr_back = phys + 0x80;

    fprintf(stderr, "[dmatest] DMA: DDR(0x%08x) → TILE_BANK(0)\n", phys);
    int rc1 = cgra_dma_read(&dev, phys, tile_dst, 64);
    fprintf(stderr, "  rc=%d  DMA_STATUS=0x%08x  DMA_ERROR=0x%08x  IRQ_STATUS=0x%08x\n",
            rc1, cgra_read(&dev, CGRA_DMA_STATUS),
            cgra_read(&dev, CGRA_DMA_ERROR),
            cgra_read(&dev, CGRA_IRQ_STATUS));
    cgra_write(&dev, CGRA_IRQ_STATUS, 0x7);  /* W1C all */

    fprintf(stderr, "[dmatest] DMA: TILE_BANK(0) → DDR(0x%08x)\n", ddr_back);
    int rc2 = cgra_dma_write(&dev, tile_dst, ddr_back, 64);
    fprintf(stderr, "  rc=%d  DMA_STATUS=0x%08x  DMA_ERROR=0x%08x  IRQ_STATUS=0x%08x\n",
            rc2, cgra_read(&dev, CGRA_DMA_STATUS),
            cgra_read(&dev, CGRA_DMA_ERROR),
            cgra_read(&dev, CGRA_IRQ_STATUS));

    /* Uncached mapping — no invalidate needed before CPU reads. */

    /* Verify. */
    int ok = 0, bad = 0;
    for (int i = 0; i < 16; i++) {
        if (dst[i] == src[i]) ok++;
        else {
            if (bad < 4)
                fprintf(stderr, "  word[%2d] expect 0x%08x got 0x%08x\n",
                        i, src[i], dst[i]);
            bad++;
        }
    }
    fprintf(stderr, "[dmatest] match=%d/16 mismatch=%d\n", ok, bad);

    munmap(buf, PAGE_SIZE);
    close(memfd);
    cgra_close(&dev);
    return (bad == 0) ? 0 : 2;
}
