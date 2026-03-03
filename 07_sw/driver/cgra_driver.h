/* ===================================================================
 *  cgra_driver.h – CGRA 4×4 UIO+CMA Linux Driver (PYNQ-Z2)
 *
 *  Register map mirrors cgra_apb_csr + cgra_top APB decode:
 *    0x00  DMA_CTRL        RW  [0]=start, [1]=wr_mode
 *    0x04  DMA_STATUS      RO  [0]=busy, [1]=done
 *    0x08  DMA_SRC         RW  Source address (AXI / physical)
 *    0x0C  DMA_DST         RW  Destination address
 *    0x10  DMA_SIZE        RW  Transfer size (bytes)
 *    0x20  CU_CTRL         RW  [0]=start, [1]=soft_reset
 *    0x24  CU_STATUS       RO  [0]=busy, [1]=done
 *    0x28  CU_CYCLES       RO  Execution cycle count
 *    0x30  IRQ_STATUS      RW  W1C: [0]=done, [1]=dma_done
 *    0x34  IRQ_MASK        RW  [0]=done_en, [1]=dma_done_en
 *    0x40  RESULT_DATA     RO  PE[15] output (global_result)
 *    0x44  RESULT_STATUS   RO  [0]=result_valid
 *    0x48  LOOP_START      RW  HW-loop start PC [15:0]
 *    0x4C  LOOP_END        RW  HW-loop end PC   [15:0]
 *    0x50  LOOP_COUNT      RW  HW-loop iteration count [15:0]
 *    0x58  RESULT_ROW0     RO  East-edge row 0
 *    0x5C  RESULT_ROW1     RO  East-edge row 1
 *    0x60  RESULT_ROW2     RO  East-edge row 2
 *    0x64  RESULT_ROW3     RO  East-edge row 3
 * =================================================================== */

#ifndef CGRA_DRIVER_H
#define CGRA_DRIVER_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Register offsets ────────────────────────────────────────────── */
#define CGRA_DMA_CTRL         0x00
#define CGRA_DMA_STATUS       0x04
#define CGRA_DMA_SRC          0x08
#define CGRA_DMA_DST          0x0C
#define CGRA_DMA_SIZE         0x10

#define CGRA_CU_CTRL          0x20
#define CGRA_CU_STATUS        0x24
#define CGRA_CU_CYCLES        0x28

#define CGRA_IRQ_STATUS       0x30
#define CGRA_IRQ_MASK         0x34

#define CGRA_RESULT_DATA      0x40
#define CGRA_RESULT_STATUS    0x44

#define CGRA_LOOP_START       0x48
#define CGRA_LOOP_END         0x4C
#define CGRA_LOOP_COUNT       0x50

#define CGRA_RESULT_ROW0      0x58
#define CGRA_RESULT_ROW1      0x5C
#define CGRA_RESULT_ROW2      0x60
#define CGRA_RESULT_ROW3      0x64

/* ── Bit masks ───────────────────────────────────────────────────── */
#define DMA_CTRL_START        (1u << 0)
#define DMA_CTRL_WR_MODE      (1u << 1)
#define DMA_STATUS_BUSY       (1u << 0)
#define DMA_STATUS_DONE       (1u << 1)

#define CU_CTRL_START         (1u << 0)
#define CU_CTRL_SOFT_RESET    (1u << 1)
#define CU_STATUS_BUSY        (1u << 0)
#define CU_STATUS_DONE        (1u << 1)

#define IRQ_DONE              (1u << 0)
#define IRQ_DMA_DONE          (1u << 1)

/* ── CMA buffer descriptor ──────────────────────────────────────── */
typedef struct {
    void       *virt;        /* User-space virtual address             */
    uint32_t    phys;        /* Physical (bus) address for DMA         */
    size_t      size;        /* Allocation size in bytes               */
    int         fd;          /* CMA fd (for munmap / close)            */
} cgra_cma_buf_t;

/* ── Device handle ──────────────────────────────────────────────── */
typedef struct {
    volatile uint32_t *regs; /* mmap'd register space                  */
    int    uio_fd;           /* /dev/uioN file descriptor              */
    size_t map_size;         /* Register region size (from sysfs)      */
} cgra_dev_t;

/* ── Lifecycle ──────────────────────────────────────────────────── */

/**
 * cgra_init - Open UIO device and mmap register space.
 * @dev:        Pointer to device handle (caller-allocated).
 * @uio_path:   e.g. "/dev/uio0"
 * Returns 0 on success, -1 on error (errno set).
 */
int  cgra_init(cgra_dev_t *dev, const char *uio_path);

/**
 * cgra_close - Unmap registers and close UIO fd.
 */
void cgra_close(cgra_dev_t *dev);

/* ── Register access ─────────────────────────────────────────────── */

static inline void cgra_write(cgra_dev_t *dev, uint32_t offset, uint32_t val)
{
    dev->regs[offset >> 2] = val;
}

static inline uint32_t cgra_read(cgra_dev_t *dev, uint32_t offset)
{
    return dev->regs[offset >> 2];
}

/* ── DMA helpers ─────────────────────────────────────────────────── */

/**
 * cgra_dma_read - DMA read from external memory into CGRA tile memory.
 * @src_phys:  Physical source address (CMA buffer).
 * @dst_local: CGRA-local destination (e.g. 0x1000 for tile-mem bank 0).
 * @bytes:     Transfer size in bytes (must be 4-byte aligned).
 * Blocks until DMA_STATUS.done is set.  Returns cycle count or -1 on timeout.
 */
int  cgra_dma_read(cgra_dev_t *dev, uint32_t src_phys,
                   uint32_t dst_local, uint32_t bytes);

/**
 * cgra_dma_write - DMA write from CGRA tile memory to external memory.
 * @src_local: CGRA-local source (e.g. 0x1000).
 * @dst_phys:  Physical destination address (CMA buffer).
 * @bytes:     Transfer size.
 */
int  cgra_dma_write(cgra_dev_t *dev, uint32_t src_local,
                    uint32_t dst_phys, uint32_t bytes);

/* ── Compute helpers ─────────────────────────────────────────────── */

/**
 * cgra_run - Start CU execution and block until done.
 * Returns execution cycles or -1 on timeout.
 */
int  cgra_run(cgra_dev_t *dev);

/**
 * cgra_soft_reset - Assert and deassert CU soft reset.
 */
void cgra_soft_reset(cgra_dev_t *dev);

/**
 * cgra_set_loop - Program hardware loop parameters via APB.
 * @start_pc:  First PC of the loop body.
 * @end_pc:    Last PC of the loop body.
 * @count:     Number of iterations (0 = no looping).
 */
void cgra_set_loop(cgra_dev_t *dev, uint16_t start_pc,
                   uint16_t end_pc, uint16_t count);

/**
 * cgra_get_results - Read east-edge row results into caller buffer.
 * @out: array of at least 4 uint32_t.
 */
void cgra_get_results(cgra_dev_t *dev, uint32_t out[4]);

/* ── IRQ helpers ─────────────────────────────────────────────────── */

/**
 * cgra_irq_enable - Unmask selected IRQ sources.
 */
void cgra_irq_enable(cgra_dev_t *dev, uint32_t mask);

/**
 * cgra_irq_wait - Block on UIO interrupt, then return IRQ_STATUS bits.
 * Clears matched bits via W1C before returning.
 * Returns 0 on timeout.
 */
uint32_t cgra_irq_wait(cgra_dev_t *dev, int timeout_ms);

/* ── CMA allocation (uses /dev/cma or xlnk) ─────────────────────── */

/**
 * cgra_cma_alloc - Allocate physically contiguous DMA buffer.
 * @buf:   Pointer to CMA descriptor (filled on success).
 * @bytes: Requested size.
 * Returns 0 on success, -1 on error.
 */
int  cgra_cma_alloc(cgra_cma_buf_t *buf, size_t bytes);

/**
 * cgra_cma_free - Release CMA buffer.
 */
void cgra_cma_free(cgra_cma_buf_t *buf);

/* ── Config memory helpers ───────────────────────────────────────── */

/**
 * cgra_load_config - DMA a PE configuration bitstream into config memory.
 * @cfg_phys:  Physical address of config data (CMA buffer).
 * @slot:      Config slot index (0-15 for double-buffered contexts).
 * @n_words:   Number of 32-bit config words.
 */
int  cgra_load_config(cgra_dev_t *dev, uint32_t cfg_phys,
                      uint32_t slot, uint32_t n_words);

#ifdef __cplusplus
}
#endif

#endif /* CGRA_DRIVER_H */
