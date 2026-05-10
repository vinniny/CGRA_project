#ifndef VDMA_H
#define VDMA_H

#include <stdint.h>

/* Minimal subset from xaxivdma_hw.h */
#define XAXIVDMA_TX_OFFSET              0x00000000u
#define XAXIVDMA_CR_OFFSET              0x00000000u
#define XAXIVDMA_SR_OFFSET              0x00000004u
#define XAXIVDMA_FRMSTORE_OFFSET        0x00000018u
#define XAXIVDMA_PARKPTR_OFFSET         0x00000028u
#define XAXIVDMA_MM2S_ADDR_OFFSET       0x00000050u
#define XAXIVDMA_VSIZE_OFFSET           0x00000000u
#define XAXIVDMA_HSIZE_OFFSET           0x00000004u
#define XAXIVDMA_STRD_FRMDLY_OFFSET     0x00000008u
#define XAXIVDMA_START_ADDR_OFFSET      0x0000000Cu
#define XAXIVDMA_START_ADDR_LEN         0x00000004u

#define XAXIVDMA_CR_RUNSTOP_MASK        0x00000001u
#define XAXIVDMA_CR_TAIL_EN_MASK        0x00000002u
#define XAXIVDMA_CR_RESET_MASK          0x00000004u
#define XAXIVDMA_CR_GENLCK_RPT_MASK     0x00008000u
#define XAXIVDMA_CR_RD_PTR_SHIFT        8u
#define XAXIVDMA_PARKPTR_READREF_SHIFT  0u
#define XAXIVDMA_SR_HALTED_MASK         0x00000001u
#define XAXIVDMA_SR_IDLE_MASK           0x00000002u
#define XAXIVDMA_SR_ERR_ALL_MASK        0x00000FF0u

int vdma_start_mm2s(volatile uint8_t *vdmaBase,
                    uint32_t fb_phys,
                    uint32_t width,
                    uint32_t height,
                    uint32_t bytes_per_pixel,
                    uint32_t stride_bytes);

int vdma_stop_mm2s(volatile uint8_t *vdmaBase);
uint32_t vdma_mm2s_status(volatile uint8_t *vdmaBase);
uint32_t vdma_mm2s_control(volatile uint8_t *vdmaBase);

#endif
