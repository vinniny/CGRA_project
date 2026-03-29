/* ===================================================================
 *  cgra_driver.c – CGRA 4×4 Linux Driver implementation
 *
 *  Targets: PetaLinux 2022.2 / Zynq-7000 (XC7Z010/XC7Z020)
 *
 *  Access modes (auto-detected):
 *    UIO:    /dev/uioN — mmap registers, IRQ via read/poll
 *    devmem: /dev/mem  — direct physical access (no IRQ, polling only)
 *
 *  CMA buffers:
 *    /dev/udmabuf0 (preferred) or /dev/mem at CGRA_DMA_BUF_PHYS
 * =================================================================== */

#define _DEFAULT_SOURCE

#include "cgra_driver.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/mman.h>
#include <time.h>

/* ── Default timeouts ────────────────────────────────────────────── */
#define DMA_POLL_LIMIT   100000
#define CU_POLL_LIMIT    1000000

/* ── Internal: monotonic time in milliseconds ────────────────────── */
static inline double ms_now(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

/* ── Internal: read hex integer from sysfs ───────────────────────── */
static long sysfs_read_hex(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    char buf[64];
    if (!fgets(buf, sizeof(buf), f)) { fclose(f); return -1; }
    fclose(f);
    return strtol(buf, NULL, 16);
}

/* ================================================================= */
/* Lifecycle                                                          */
/* ================================================================= */

static int init_uio(cgra_dev_t *dev, const char *uio_path)
{
    const char *name = strrchr(uio_path, '/');
    name = name ? name + 1 : uio_path;

    /* Read map0 size from sysfs */
    char sysfs[256];
    snprintf(sysfs, sizeof(sysfs),
             "/sys/class/uio/%s/maps/map0/size", name);
    long sz = sysfs_read_hex(sysfs);
    dev->map_size = (sz > 0) ? (size_t)sz : 4096;

    dev->fd = open(uio_path, O_RDWR | O_SYNC);
    if (dev->fd < 0) return -1;

    dev->regs = (volatile uint32_t *)mmap(NULL, dev->map_size,
                    PROT_READ | PROT_WRITE, MAP_SHARED, dev->fd, 0);
    if (dev->regs == MAP_FAILED) {
        close(dev->fd);
        dev->regs = NULL;
        return -1;
    }

    dev->mode = CGRA_MODE_UIO;
    dev->phys_base = 0;
    return 0;
}

static int init_devmem(cgra_dev_t *dev, uint32_t phys_base)
{
    dev->fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (dev->fd < 0) {
        perror("cgra_init: open /dev/mem");
        return -1;
    }

    dev->map_size = CGRA_REG_SPAN;
    dev->regs = (volatile uint32_t *)mmap(NULL, dev->map_size,
                    PROT_READ | PROT_WRITE, MAP_SHARED,
                    dev->fd, phys_base);
    if (dev->regs == MAP_FAILED) {
        perror("cgra_init: mmap /dev/mem");
        close(dev->fd);
        dev->regs = NULL;
        return -1;
    }

    dev->mode = CGRA_MODE_DEVMEM;
    dev->phys_base = phys_base;
    return 0;
}

int cgra_init(cgra_dev_t *dev, const char *dev_path)
{
    if (!dev) { errno = EINVAL; return -1; }
    memset(dev, 0, sizeof(*dev));
    dev->fd = -1;

    int rc = -1;

    if (dev_path && strstr(dev_path, "uio")) {
        /* Explicit UIO path */
        rc = init_uio(dev, dev_path);
        if (rc < 0)
            fprintf(stderr, "cgra_init: UIO '%s' failed, trying /dev/mem\n",
                    dev_path);
    }

    if (rc < 0) {
        /* Try /dev/uio0 first */
        if (access("/dev/uio0", F_OK) == 0) {
            rc = init_uio(dev, "/dev/uio0");
        }
    }

    if (rc < 0) {
        /* Fallback: /dev/mem at compiled physical base */
        rc = init_devmem(dev, CGRA_PHYS_BASE);
    }

    if (rc < 0) {
        fprintf(stderr, "cgra_init: all access methods failed\n");
        return -1;
    }

    const char *mode_str = (dev->mode == CGRA_MODE_UIO) ? "UIO" : "devmem";
    fprintf(stderr, "cgra_init: %s mode, map_size=%zu",
            mode_str, dev->map_size);
    if (dev->mode == CGRA_MODE_DEVMEM)
        fprintf(stderr, ", phys=0x%08X", dev->phys_base);
    fprintf(stderr, "\n");

    /* Soft-reset to known state */
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
    if (dev->fd >= 0) {
        close(dev->fd);
        dev->fd = -1;
    }
}

/* ================================================================= */
/* DMA helpers                                                        */
/* ================================================================= */

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
    cgra_write(dev, CGRA_DMA_SRC, src_phys);
    cgra_write(dev, CGRA_DMA_DST, dst_local);
    cgra_write(dev, CGRA_DMA_SIZE, bytes);
    cgra_write(dev, CGRA_DMA_CTRL, DMA_CTRL_START);

    if (dma_wait_done(dev) < 0) return -1;
    return 0;
}

int cgra_dma_write(cgra_dev_t *dev, uint32_t src_local,
                   uint32_t dst_phys, uint32_t bytes)
{
    cgra_write(dev, CGRA_DMA_SRC, src_local);
    cgra_write(dev, CGRA_DMA_DST, dst_phys);
    cgra_write(dev, CGRA_DMA_SIZE, bytes);
    cgra_write(dev, CGRA_DMA_CTRL, DMA_CTRL_START);

    if (dma_wait_done(dev) < 0) return -1;
    return 0;
}

/* ================================================================= */
/* Compute helpers                                                    */
/* ================================================================= */

int cgra_run(cgra_dev_t *dev)
{
    /* Clear stale done flag */
    cgra_write(dev, CGRA_IRQ_STATUS, IRQ_CU_DONE);

    /* Start execution */
    cgra_write(dev, CGRA_CU_CTRL, CU_CTRL_START);

    /* Poll CU_STATUS.done */
    for (int i = 0; i < CU_POLL_LIMIT; i++) {
        uint32_t st = cgra_read(dev, CGRA_CU_STATUS);
        if (st & CU_STATUS_DONE) {
            return (int)cgra_read(dev, CGRA_CU_CYCLES);
        }
    }

    fprintf(stderr, "cgra_run: timeout waiting for CU done\n");
    cgra_soft_reset(dev);
    return -1;
}

void cgra_soft_reset(cgra_dev_t *dev)
{
    cgra_write(dev, CGRA_CU_CTRL, CU_CTRL_SOFT_RESET);
    usleep(10);
    cgra_write(dev, CGRA_CU_CTRL, 0);
    usleep(1);
}

void cgra_set_timeout(cgra_dev_t *dev, uint32_t max_cycles)
{
    cgra_write(dev, CGRA_CU_TIMEOUT, max_cycles);
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

/* ================================================================= */
/* IRQ helpers                                                        */
/* ================================================================= */

void cgra_irq_enable(cgra_dev_t *dev, uint32_t mask)
{
    cgra_write(dev, CGRA_IRQ_MASK, mask);

    if (dev->mode == CGRA_MODE_UIO) {
        uint32_t enable = 1;
        if (write(dev->fd, &enable, sizeof(enable)) < 0)
            perror("cgra_irq_enable: write UIO");
    }
}

uint32_t cgra_irq_wait(cgra_dev_t *dev, int timeout_ms)
{
    if (dev->mode == CGRA_MODE_UIO) {
        /* UIO: re-arm interrupt, then poll fd */
        uint32_t enable = 1;
        if (write(dev->fd, &enable, sizeof(enable)) < 0) {
            perror("cgra_irq_wait: write UIO");
            return 0;
        }

        struct pollfd pfd = { .fd = dev->fd, .events = POLLIN };
        int ret = poll(&pfd, 1, timeout_ms);
        if (ret <= 0) return 0;

        uint32_t irq_count;
        if (read(dev->fd, &irq_count, sizeof(irq_count)) < 0) {
            perror("cgra_irq_wait: read UIO");
            return 0;
        }
    } else {
        /* devmem: poll register with timeout */
        double deadline = ms_now() + timeout_ms;
        while (ms_now() < deadline) {
            uint32_t status = cgra_read(dev, CGRA_IRQ_STATUS);
            if (status) {
                cgra_write(dev, CGRA_IRQ_STATUS, status);
                return status;
            }
            usleep(100);
        }
        return 0;
    }

    /* Read and clear IRQ status (W1C) */
    uint32_t status = cgra_read(dev, CGRA_IRQ_STATUS);
    cgra_write(dev, CGRA_IRQ_STATUS, status);
    return status;
}

/* ================================================================= */
/* CMA / DMA buffer allocation                                       */
/* ================================================================= */

/*
 * Strategy:
 *   1. Try /dev/udmabuf0 (if driver loaded)
 *   2. Fall back to /dev/mem at a fixed physical address
 *
 * The /dev/mem fallback maps a region of physical DDR directly.
 * The caller must ensure no other software uses that region.
 * This is safe on bare PetaLinux where Linux doesn't use the
 * CGRA_DMA_BUF_PHYS region (above kernel image, below CMA).
 */

static uint32_t devmem_alloc_offset = 0;  /* Simple bump allocator */

static int cma_alloc_udmabuf(cgra_cma_buf_t *buf, size_t alloc_size)
{
    int fd = open("/dev/udmabuf0", O_RDWR | O_SYNC);
    if (fd < 0) return -1;

    void *virt = mmap(NULL, alloc_size,
                      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (virt == MAP_FAILED) {
        close(fd);
        return -1;
    }

    long phys = sysfs_read_hex("/sys/class/udmabuf/udmabuf0/phys_addr");
    if (phys < 0) {
        munmap(virt, alloc_size);
        close(fd);
        return -1;
    }

    buf->virt = virt;
    buf->phys = (uint32_t)phys;
    buf->size = alloc_size;
    buf->fd   = fd;
    buf->is_devmem = 0;
    return 0;
}

static int cma_alloc_devmem(cgra_cma_buf_t *buf, size_t alloc_size)
{
    uint32_t phys = CGRA_DMA_BUF_PHYS + devmem_alloc_offset;

    /* Bounds check */
    if (devmem_alloc_offset + alloc_size > CGRA_DMA_BUF_SIZE) {
        fprintf(stderr, "cgra_cma_alloc: /dev/mem region exhausted "
                "(used %u + %zu > %u)\n",
                devmem_alloc_offset, alloc_size, CGRA_DMA_BUF_SIZE);
        return -1;
    }

    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("cgra_cma_alloc: open /dev/mem");
        return -1;
    }

    void *virt = mmap(NULL, alloc_size,
                      PROT_READ | PROT_WRITE, MAP_SHARED, fd, phys);
    if (virt == MAP_FAILED) {
        perror("cgra_cma_alloc: mmap /dev/mem");
        close(fd);
        return -1;
    }

    buf->virt = virt;
    buf->phys = phys;
    buf->size = alloc_size;
    buf->fd   = fd;
    buf->is_devmem = 1;

    devmem_alloc_offset += alloc_size;
    return 0;
}

int cgra_cma_alloc(cgra_cma_buf_t *buf, size_t bytes)
{
    if (!buf || bytes == 0) { errno = EINVAL; return -1; }
    memset(buf, 0, sizeof(*buf));
    buf->fd = -1;

    /* Round up to page boundary */
    long page = sysconf(_SC_PAGESIZE);
    size_t alloc_size = (bytes + page - 1) & ~(page - 1);

    /* Try udmabuf first */
    if (cma_alloc_udmabuf(buf, alloc_size) == 0) {
        fprintf(stderr, "cgra_cma_alloc: udmabuf %zu bytes @ phys 0x%08X\n",
                alloc_size, buf->phys);
        return 0;
    }

    /* Fallback: /dev/mem */
    if (cma_alloc_devmem(buf, alloc_size) == 0) {
        fprintf(stderr, "cgra_cma_alloc: devmem %zu bytes @ phys 0x%08X\n",
                alloc_size, buf->phys);
        return 0;
    }

    fprintf(stderr, "cgra_cma_alloc: all methods failed\n");
    return -1;
}

void cgra_cma_free(cgra_cma_buf_t *buf)
{
    if (!buf) return;
    if (buf->virt && buf->virt != MAP_FAILED)
        munmap(buf->virt, buf->size);
    if (buf->fd >= 0)
        close(buf->fd);
    /* Note: devmem bump allocator does not reclaim — acceptable for
     * embedded use where allocations are done once at startup. */
    memset(buf, 0, sizeof(*buf));
    buf->fd = -1;
}

/* ================================================================= */
/* Config memory                                                      */
/* ================================================================= */

int cgra_load_config(cgra_dev_t *dev, uint32_t cfg_phys,
                     uint32_t pe_id, uint32_t slot, uint32_t n_words)
{
    /*
     * Config address space (RTL cgra_dma_engine.sv):
     *   [31:28] = 0x2  (config prefix)
     *   [10:7]  = PE select (0-15)
     *   [6:3]   = slot (0-15, slot 0 = broadcast)
     *   [2]     = hi/lo word select
     *
     * Base address for PE p, slot s: 0x20000000 | (p << 7) | (s << 3)
     */
    uint32_t dst = DMA_PREFIX_CONFIG | (pe_id << 7) | (slot << 3);
    return cgra_dma_read(dev, cfg_phys, dst, n_words * 4);
}
