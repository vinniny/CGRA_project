#include "vdma.h"
#include "mmio_util.h"

#include <unistd.h>

static inline uint32_t tx_reg(uint32_t off)
{
    return XAXIVDMA_TX_OFFSET + off;
}

int vdma_stop_mm2s(volatile uint8_t *vdmaBase)
{
    uint32_t cr = mmio_read32(vdmaBase, tx_reg(XAXIVDMA_CR_OFFSET));
    cr &= ~XAXIVDMA_CR_RUNSTOP_MASK;
    mmio_write32(vdmaBase, tx_reg(XAXIVDMA_CR_OFFSET), cr);
    usleep(1000);
    return 0;
}

uint32_t vdma_mm2s_status(volatile uint8_t *vdmaBase)
{
    return mmio_read32(vdmaBase, tx_reg(XAXIVDMA_SR_OFFSET));
}

int vdma_start_mm2s(volatile uint8_t *vdmaBase,
                    uint32_t fb_phys,
                    uint32_t width,
                    uint32_t height,
                    uint32_t bytes_per_pixel,
                    uint32_t stride_bytes)
{
    const uint32_t hsize = width * bytes_per_pixel;
    const uint32_t frame_base = XAXIVDMA_MM2S_ADDR_OFFSET;

    /* Reset channel. */
    mmio_write32(vdmaBase, tx_reg(XAXIVDMA_CR_OFFSET), XAXIVDMA_CR_RESET_MASK);
    usleep(1000);

    /* Single frame store, park mode on frame 0. */
    mmio_write32(vdmaBase, tx_reg(XAXIVDMA_FRMSTORE_OFFSET), 1u);
    mmio_write32(vdmaBase, XAXIVDMA_PARKPTR_OFFSET, (0u << XAXIVDMA_PARKPTR_READREF_SHIFT));

    /* Start the MM2S channel in direct register mode (tail enable = 0). */
    mmio_write32(vdmaBase, tx_reg(XAXIVDMA_CR_OFFSET),
                 XAXIVDMA_CR_RUNSTOP_MASK | (0u << XAXIVDMA_CR_RD_PTR_SHIFT));

    /* Program frame buffer and video params. VSIZE must be written last. */
    mmio_write32(vdmaBase, tx_reg(frame_base + XAXIVDMA_START_ADDR_OFFSET), fb_phys);
    mmio_write32(vdmaBase, tx_reg(frame_base + XAXIVDMA_STRD_FRMDLY_OFFSET), stride_bytes);
    mmio_write32(vdmaBase, tx_reg(frame_base + XAXIVDMA_HSIZE_OFFSET), hsize);
    mmio_write32(vdmaBase, tx_reg(frame_base + XAXIVDMA_VSIZE_OFFSET), height);

    usleep(1000);
    return (vdma_mm2s_status(vdmaBase) & XAXIVDMA_SR_ERR_ALL_MASK) ? -1 : 0;
}

uint32_t vdma_mm2s_control(volatile uint8_t *vdmaBase)
{
    return mmio_read32(vdmaBase, XAXIVDMA_TX_OFFSET + XAXIVDMA_CR_OFFSET);
}
