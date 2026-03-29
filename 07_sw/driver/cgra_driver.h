/* ===================================================================
 *  cgra_driver.h – CGRA 4×4 Linux Driver (Zynq-7000)
 *
 *  Supports two access modes (auto-detected):
 *    1. UIO mode  — /dev/uioN for register access + IRQ
 *    2. devmem mode — /dev/mem for direct physical register access
 *
 *  CMA buffer allocation via:
 *    1. /dev/udmabuf0 (if available)
 *    2. /dev/mem at fixed physical address (fallback)
 *
 *  Register map mirrors cgra_apb_csr + cgra_top APB decode:
 *    0x00  DMA_CTRL        RW  [0]=start
 *    0x04  DMA_STATUS      RO  [0]=busy, [1]=done
 *    0x08  DMA_SRC         RW  Source address (AXI / physical)
 *    0x0C  DMA_DST         RW  Destination address
 *    0x10  DMA_SIZE        RW  Transfer size (bytes)
 *    0x20  CU_CTRL         RW  [0]=start, [1]=soft_reset
 *    0x24  CU_STATUS       RO  [0]=busy, [1]=done
 *    0x28  CU_CYCLES       RO  Execution cycle count
 *    0x2C  CU_TIMEOUT      RW  Max cycles (0=no limit)
 *    0x30  IRQ_STATUS      RW  W1C: [0]=dma_done, [1]=cu_done
 *    0x34  IRQ_MASK        RW  [0]=dma_done_en, [1]=cu_done_en
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
#define CGRA_CU_TIMEOUT       0x2C

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
#define DMA_STATUS_BUSY       (1u << 0)
#define DMA_STATUS_DONE       (1u << 1)

#define CU_CTRL_START         (1u << 0)
#define CU_CTRL_SOFT_RESET    (1u << 1)
#define CU_STATUS_BUSY        (1u << 0)
#define CU_STATUS_DONE        (1u << 1)

#define IRQ_DMA_DONE          (1u << 0)
#define IRQ_CU_DONE           (1u << 1)
#define IRQ_DONE              IRQ_CU_DONE  /* Backward compat */

/* ── Physical address configuration ─────────────────────────────── */

/*
 * CGRA IP base address in the Zynq PL address map.
 * Must match the Vivado block design address assignment.
 * Default: 0x43C00000 (typical AXI GP0 range on Zynq-7000)
 * Override at compile time: -DCGRA_PHYS_BASE=0xNNNNNNNN
 */
#ifndef CGRA_PHYS_BASE
#define CGRA_PHYS_BASE        0x43C00000u
#endif
#define CGRA_REG_SPAN         0x10000u     /* 64KB register region */

/*
 * DMA buffer physical addresses.
 * Must be in low DDR (below highmem threshold) for USB DMA compat.
 * On Zynq-7000 with 1GB DDR and cma=64M@0x0-0x30000000:
 *   Safe range: 0x10000000 — 0x2FFFFFFF (256MB–768MB)
 *
 * Override at compile time if needed.
 */
#ifndef CGRA_DMA_BUF_PHYS
#define CGRA_DMA_BUF_PHYS    0x10000000u   /* DMA buffer physical base */
#endif
#define CGRA_DMA_BUF_SIZE    0x00400000u   /* 4MB reserved for DMA */

/* Convenience offsets within the DMA buffer region */
#define CGRA_IMAGE_OFFSET     0x00000000u
#define CGRA_CONFIG_OFFSET    0x00100000u
#define CGRA_RESULT_OFFSET    0x00200000u

#define CGRA_IMAGE_ADDR       (CGRA_DMA_BUF_PHYS + CGRA_IMAGE_OFFSET)
#define CGRA_CONFIG_ADDR      (CGRA_DMA_BUF_PHYS + CGRA_CONFIG_OFFSET)
#define CGRA_RESULT_ADDR      (CGRA_DMA_BUF_PHYS + CGRA_RESULT_OFFSET)

/* ── DMA address space prefixes (matches RTL cgra_dma_engine.sv) ── */
#define DMA_PREFIX_AXI        0x00000000u  /* [31:28]=0x0 → external DDR */
#define DMA_PREFIX_TILE       0x10000000u  /* [31:28]=0x1 → tile memory  */
#define DMA_PREFIX_CONFIG     0x20000000u  /* [31:28]=0x2 → PE config    */

#define TILE_BANK(b)          (DMA_PREFIX_TILE | ((uint32_t)(b) << 12))

/* ── CMA buffer descriptor ──────────────────────────────────────── */
typedef struct {
    void       *virt;        /* User-space virtual address             */
    uint32_t    phys;        /* Physical (bus) address for DMA         */
    size_t      size;        /* Allocation size in bytes               */
    int         fd;          /* Backing fd (for munmap / close)        */
    int         is_devmem;   /* 1 if allocated via /dev/mem            */
} cgra_cma_buf_t;

/* ── Access mode ────────────────────────────────────────────────── */
typedef enum {
    CGRA_MODE_UIO,           /* /dev/uioN — register + IRQ             */
    CGRA_MODE_DEVMEM         /* /dev/mem  — direct physical access     */
} cgra_mode_t;

/* ── Device handle ──────────────────────────────────────────────── */
typedef struct {
    volatile uint32_t *regs; /* mmap'd register space                  */
    int         fd;          /* UIO or /dev/mem file descriptor         */
    size_t      map_size;    /* Register region size                    */
    cgra_mode_t mode;        /* Access mode                             */
    uint32_t    phys_base;   /* Physical base (devmem mode)             */
} cgra_dev_t;

/* ── Lifecycle ──────────────────────────────────────────────────── */

/**
 * cgra_init - Open CGRA device.
 * @dev:      Pointer to device handle (caller-allocated).
 * @dev_path: "/dev/uio0" for UIO mode, or NULL for auto-detect.
 *            Auto-detect tries UIO first, falls back to /dev/mem.
 * Returns 0 on success, -1 on error (errno set).
 */
int  cgra_init(cgra_dev_t *dev, const char *dev_path);

/**
 * cgra_close - Unmap registers and close device fd.
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
 * cgra_dma_read - DMA from external DDR into CGRA tile/config memory.
 * @src_phys:  Physical source address in DDR.
 * @dst_local: CGRA-local destination (0x1XXX=tile, 0x2XXX=config).
 * @bytes:     Transfer size in bytes (must be 4-byte aligned).
 * Blocks until DMA_STATUS.done. Returns 0 or -1 on timeout.
 */
int  cgra_dma_read(cgra_dev_t *dev, uint32_t src_phys,
                   uint32_t dst_local, uint32_t bytes);

/**
 * cgra_dma_write - DMA from CGRA tile memory to external DDR.
 * @src_local: CGRA-local source (0x1XXX=tile).
 * @dst_phys:  Physical destination address in DDR.
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
 * cgra_set_timeout - Set CU execution timeout (0=no limit).
 */
void cgra_set_timeout(cgra_dev_t *dev, uint32_t max_cycles);

/**
 * cgra_set_loop - Program hardware loop parameters.
 * @start_pc: First PC of loop body.
 * @end_pc:   Last PC of loop body.
 * @count:    Iterations (0=no looping).
 */
void cgra_set_loop(cgra_dev_t *dev, uint16_t start_pc,
                   uint16_t end_pc, uint16_t count);

/**
 * cgra_get_results - Read east-edge row results.
 * @out: array of at least 4 uint32_t.
 */
void cgra_get_results(cgra_dev_t *dev, uint32_t out[4]);

/* ── IRQ helpers ─────────────────────────────────────────────────── */

/**
 * cgra_irq_enable - Unmask IRQ sources. Only works in UIO mode.
 */
void cgra_irq_enable(cgra_dev_t *dev, uint32_t mask);

/**
 * cgra_irq_wait - Block on interrupt (UIO) or poll status (devmem).
 * Clears matched bits via W1C before returning.
 * Returns IRQ_STATUS bits, or 0 on timeout.
 */
uint32_t cgra_irq_wait(cgra_dev_t *dev, int timeout_ms);

/* ── CMA / DMA buffer allocation ────────────────────────────────── */

/**
 * cgra_cma_alloc - Allocate physically contiguous DMA buffer.
 * Tries /dev/udmabuf0, falls back to /dev/mem at fixed address.
 * @buf:   Pointer to buffer descriptor (filled on success).
 * @bytes: Requested size.
 * Returns 0 on success, -1 on error.
 */
int  cgra_cma_alloc(cgra_cma_buf_t *buf, size_t bytes);

/**
 * cgra_cma_free - Release DMA buffer.
 */
void cgra_cma_free(cgra_cma_buf_t *buf);

/* ── Config memory helpers ───────────────────────────────────────── */

/**
 * cgra_load_config - DMA PE config data into CGRA config RAM.
 * @cfg_phys: Physical address of config data in DDR.
 * @pe_id:    Target PE (0-15).
 * @slot:     Config slot (0-15, slot 0 = broadcast all).
 * @n_words:  Number of 32-bit words (2 per 64-bit config entry).
 */
int  cgra_load_config(cgra_dev_t *dev, uint32_t cfg_phys,
                      uint32_t pe_id, uint32_t slot, uint32_t n_words);

#ifdef __cplusplus
}
#endif

#endif /* CGRA_DRIVER_H */
