/* ===================================================================
 *  cgra_driver.c – CGRA 4×4 UIO+CMA Linux Driver implementation
 *
 *  Targets: PetaLinux / PYNQ-Z2 (Zynq-7000)
 *  Requires: UIO kernel module loaded for CGRA, CMA reserved region
 * =================================================================== */

#define _DEFAULT_SOURCE   /* Expose usleep() on glibc ≥ 2.19 */

#include "cgra_driver.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/mman.h>

/* ── Default timeouts ────────────────────────────────────────────── */
#define DMA_POLL_LIMIT   100000   /* Polling iterations for DMA done  */
#define CU_POLL_LIMIT    1000000  /* Polling iterations for CU done   */

/* ── Sysfs helpers ───────────────────────────────────────────────── */

/* Read an integer from sysfs (e.g. UIO map size).
 * path: full sysfs path, e.g. "/sys/class/uio/uio0/maps/map0/size" */
static long sysfs_read_hex(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    char buf[64];
    if (!fgets(buf, sizeof(buf), f)) { fclose(f); return -1; }
    fclose(f);
    return strtol(buf, NULL, 16);
}

/* ── Lifecycle ──────────────────────────────────────────────────── */

int cgra_init(cgra_dev_t *dev, const char *uio_path)
{
    if (!dev || !uio_path) { errno = EINVAL; return -1; }
    memset(dev, 0, sizeof(*dev));

    /* Extract UIO number from path (e.g. "/dev/uio0" → "uio0") */
    const char *name = strrchr(uio_path, '/');
    name = name ? name + 1 : uio_path;

    /* Read map0 size from sysfs */
    char sysfs[256];
    snprintf(sysfs, sizeof(sysfs),
             "/sys/class/uio/%s/maps/map0/size", name);
    long sz = sysfs_read_hex(sysfs);
    if (sz <= 0) {
        fprintf(stderr, "cgra_init: cannot read map size from %s\n", sysfs);
        dev->map_size = 4096;  /* Fallback: one page */
    } else {
        dev->map_size = (size_t)sz;
    }

    /* Open UIO device */
    dev->uio_fd = open(uio_path, O_RDWR | O_SYNC);
    if (dev->uio_fd < 0) {
        perror("cgra_init: open UIO");
        return -1;
    }

    /* mmap register space */
    dev->regs = (volatile uint32_t *)mmap(NULL, dev->map_size,
                    PROT_READ | PROT_WRITE, MAP_SHARED, dev->uio_fd, 0);
    if (dev->regs == MAP_FAILED) {
        perror("cgra_init: mmap");
        close(dev->uio_fd);
        dev->regs = NULL;
        return -1;
    }

    /* Soft-reset the CGRA to a known state */
    cgra_soft_reset(dev);

    return 0;
}

void cgra_close(cgra_dev_t *dev)
{
    if (!dev) return;
    if (dev->regs && dev->regs != MAP_FAILED) {
        munmap((void *)dev->regs, dev->map_size);
        dev->regs = NULL;
    }
    if (dev->uio_fd >= 0) {
        close(dev->uio_fd);
        dev->uio_fd = -1;
    }
}

/* ── DMA helpers ─────────────────────────────────────────────────── */

static int dma_wait_done(cgra_dev_t *dev)
{
    for (int i = 0; i < DMA_POLL_LIMIT; i++) {
        uint32_t st = cgra_read(dev, CGRA_DMA_STATUS);
        if (st & DMA_STATUS_DONE) return 0;
    }
    fprintf(stderr, "cgra_dma: timeout waiting for DMA done\n");
    return -1;
}

int cgra_dma_read(cgra_dev_t *dev, uint32_t src_phys,
                  uint32_t dst_local, uint32_t bytes)
{
    /* Configure: read mode (wr_mode=0) */
    cgra_write(dev, CGRA_DMA_SRC, src_phys);
    cgra_write(dev, CGRA_DMA_DST, dst_local);
    cgra_write(dev, CGRA_DMA_SIZE, bytes);
    cgra_write(dev, CGRA_DMA_CTRL, DMA_CTRL_START);  /* start, rd mode */

    if (dma_wait_done(dev) < 0) return -1;

    /* Clear start bit */
    cgra_write(dev, CGRA_DMA_CTRL, 0);
    return 0;
}

int cgra_dma_write(cgra_dev_t *dev, uint32_t src_local,
                   uint32_t dst_phys, uint32_t bytes)
{
    cgra_write(dev, CGRA_DMA_SRC, src_local);
    cgra_write(dev, CGRA_DMA_DST, dst_phys);
    cgra_write(dev, CGRA_DMA_SIZE, bytes);
    cgra_write(dev, CGRA_DMA_CTRL, DMA_CTRL_START | DMA_CTRL_WR_MODE);

    if (dma_wait_done(dev) < 0) return -1;

    cgra_write(dev, CGRA_DMA_CTRL, 0);
    return 0;
}

/* ── Compute helpers ─────────────────────────────────────────────── */

int cgra_run(cgra_dev_t *dev)
{
    /* Clear any stale done flag via IRQ W1C */
    cgra_write(dev, CGRA_IRQ_STATUS, IRQ_DONE);

    /* Start execution */
    cgra_write(dev, CGRA_CU_CTRL, CU_CTRL_START);

    /* Poll CU_STATUS.done */
    for (int i = 0; i < CU_POLL_LIMIT; i++) {
        uint32_t st = cgra_read(dev, CGRA_CU_STATUS);
        if (st & CU_STATUS_DONE) {
            cgra_write(dev, CGRA_CU_CTRL, 0);  /* Deassert start */
            return (int)cgra_read(dev, CGRA_CU_CYCLES);
        }
    }

    fprintf(stderr, "cgra_run: timeout waiting for CU done\n");
    cgra_write(dev, CGRA_CU_CTRL, 0);
    return -1;
}

void cgra_soft_reset(cgra_dev_t *dev)
{
    cgra_write(dev, CGRA_CU_CTRL, CU_CTRL_SOFT_RESET);
    /* Brief delay for reset propagation (1 µs minimum) */
    usleep(10);
    cgra_write(dev, CGRA_CU_CTRL, 0);
    usleep(1);
}

void cgra_set_loop(cgra_dev_t *dev, uint16_t start_pc,
                   uint16_t end_pc, uint16_t count)
{
    cgra_write(dev, CGRA_LOOP_START, (uint32_t)start_pc);
    cgra_write(dev, CGRA_LOOP_END,   (uint32_t)end_pc);
    cgra_write(dev, CGRA_LOOP_COUNT, (uint32_t)count);
}

void cgra_get_results(cgra_dev_t *dev, uint32_t out[4])
{
    out[0] = cgra_read(dev, CGRA_RESULT_ROW0);
    out[1] = cgra_read(dev, CGRA_RESULT_ROW1);
    out[2] = cgra_read(dev, CGRA_RESULT_ROW2);
    out[3] = cgra_read(dev, CGRA_RESULT_ROW3);
}

/* ── IRQ helpers ─────────────────────────────────────────────────── */

void cgra_irq_enable(cgra_dev_t *dev, uint32_t mask)
{
    cgra_write(dev, CGRA_IRQ_MASK, mask);

    /* Re-enable UIO interrupt (kernel UIO driver requires this) */
    uint32_t enable = 1;
    if (write(dev->uio_fd, &enable, sizeof(enable)) < 0)
        perror("cgra_irq_enable: write UIO");
}

uint32_t cgra_irq_wait(cgra_dev_t *dev, int timeout_ms)
{
    /* Re-arm UIO interrupt before polling */
    uint32_t enable = 1;
    if (write(dev->uio_fd, &enable, sizeof(enable)) < 0) {
        perror("cgra_irq_wait: write UIO");
        return 0;
    }

    struct pollfd pfd = { .fd = dev->uio_fd, .events = POLLIN };
    int ret = poll(&pfd, 1, timeout_ms);
    if (ret <= 0) return 0;  /* Timeout or error */

    /* Consume the interrupt count */
    uint32_t irq_count;
    if (read(dev->uio_fd, &irq_count, sizeof(irq_count)) < 0) {
        perror("cgra_irq_wait: read UIO");
        return 0;
    }

    /* Read and clear IRQ status (W1C) */
    uint32_t status = cgra_read(dev, CGRA_IRQ_STATUS);
    cgra_write(dev, CGRA_IRQ_STATUS, status);
    return status;
}

/* ── CMA allocation ──────────────────────────────────────────────── */

/*
 * On PYNQ / PetaLinux the CMA allocator can be accessed through:
 *   1. /dev/xlnk  (Xilinx legacy)
 *   2. /dev/udmabuf0 (u-dma-buf driver)
 *   3. libcma from PYNQ runtime
 *
 * This implementation uses a generic approach via /dev/udmabuf0.
 * For PYNQ Python flow, prefer pynq.allocate() instead.
 */

#define CMA_DEV  "/dev/udmabuf0"

int cgra_cma_alloc(cgra_cma_buf_t *buf, size_t bytes)
{
    if (!buf || bytes == 0) { errno = EINVAL; return -1; }
    memset(buf, 0, sizeof(*buf));

    /* Round up to page boundary */
    long page = sysconf(_SC_PAGESIZE);
    size_t alloc_size = (bytes + page - 1) & ~(page - 1);

    /* Open CMA device */
    int fd = open(CMA_DEV, O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("cgra_cma_alloc: open " CMA_DEV);
        return -1;
    }

    /* mmap to get user-space pointer */
    void *virt = mmap(NULL, alloc_size,
                      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (virt == MAP_FAILED) {
        perror("cgra_cma_alloc: mmap");
        close(fd);
        return -1;
    }

    /* Read physical address from sysfs */
    char phys_path[256];
    snprintf(phys_path, sizeof(phys_path),
             "/sys/class/udmabuf/udmabuf0/phys_addr");
    long phys = sysfs_read_hex(phys_path);
    if (phys < 0) {
        fprintf(stderr, "cgra_cma_alloc: cannot read phys_addr\n");
        munmap(virt, alloc_size);
        close(fd);
        return -1;
    }

    buf->virt = virt;
    buf->phys = (uint32_t)phys;
    buf->size = alloc_size;
    buf->fd   = fd;
    return 0;
}

void cgra_cma_free(cgra_cma_buf_t *buf)
{
    if (!buf) return;
    if (buf->virt && buf->virt != MAP_FAILED)
        munmap(buf->virt, buf->size);
    if (buf->fd >= 0)
        close(buf->fd);
    memset(buf, 0, sizeof(*buf));
    buf->fd = -1;
}

/* ── Config memory ───────────────────────────────────────────────── */

int cgra_load_config(cgra_dev_t *dev, uint32_t cfg_phys,
                     uint32_t slot, uint32_t n_words)
{
    /*
     * Config memory base in CGRA address space: 0x2000
     * Each config slot = n_words × 4 bytes
     * DMA into config region: dst = 0x2000 + slot * n_words * 4
     */
    uint32_t dst = 0x2000 + slot * n_words * 4;
    return cgra_dma_read(dev, cfg_phys, dst, n_words * 4);
}
