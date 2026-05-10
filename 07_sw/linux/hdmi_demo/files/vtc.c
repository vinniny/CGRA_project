#include "vtc.h"
#include "mmio_util.h"

static inline uint32_t pack_start_end(uint32_t start, uint32_t end)
{
    return ((end & 0x3FFFu) << 16) | (start & 0x3FFFu);
}

int vtc_configure_generator(volatile uint8_t *vtcBase, const VideoMode *mode)
{
    const uint32_t h_active = mode->width;
    const uint32_t h_sync_start = mode->hps;
    const uint32_t h_sync_end = mode->hpe;
    const uint32_t h_total = mode->hmax + 1u;

    const uint32_t v_active = mode->height;
    const uint32_t v_sync_start = mode->vps;
    const uint32_t v_sync_end = mode->vpe;
    const uint32_t v_total = mode->vmax + 1u;

    /* Active size */
    mmio_write32(vtcBase, XVTC_GASIZE_OFFSET, ((v_active & 0x1FFFu) << 16) | (h_active & 0x1FFFu));

    /* Progressive */
    mmio_write32(vtcBase, XVTC_GFENC_OFFSET, XVTC_ENC_PROG_MASK);

    /* Polarity: active video is typically active high */
    uint32_t pol = XVTC_POL_AVP_MASK;
    if (mode->hpol) {
        pol |= XVTC_POL_HSP_MASK;
    }
    if (mode->vpol) {
        pol |= XVTC_POL_VSP_MASK;
    }
    mmio_write32(vtcBase, XVTC_GPOL_OFFSET, pol);

    /* Total sizes */
    mmio_write32(vtcBase, XVTC_GHSIZE_OFFSET, h_total);
    mmio_write32(vtcBase, XVTC_GVSIZE_OFFSET, v_total);

    /* Sync positions */
    mmio_write32(vtcBase, XVTC_GHSYNC_OFFSET, pack_start_end(h_sync_start, h_sync_end));
    mmio_write32(vtcBase, XVTC_GVSYNC_OFFSET, pack_start_end(v_sync_start, v_sync_end));

    /* Blank start/end */
    mmio_write32(vtcBase, XVTC_GVBHOFF_OFFSET, pack_start_end(h_active, h_total - 1u));
    mmio_write32(vtcBase, XVTC_GVSHOFF_OFFSET, pack_start_end(h_sync_start, h_sync_end));

    /* No extra global delay */
    mmio_write32(vtcBase, XVTC_GGD_OFFSET, 0);

    /* Force generator registers as timing sources and request register update. */
    mmio_write32(vtcBase, XVTC_CTL_OFFSET,
                 XVTC_CTL_ALLGENSRC_MASK | XVTC_CTL_RU_MASK | XVTC_CTL_SW_MASK);
    return 0;
}

void vtc_enable_generator(volatile uint8_t *vtcBase)
{
    uint32_t ctl = mmio_read32(vtcBase, XVTC_CTL_OFFSET);
    ctl |= (XVTC_CTL_GE_MASK | XVTC_CTL_RU_MASK | XVTC_CTL_SW_MASK);
    mmio_write32(vtcBase, XVTC_CTL_OFFSET, ctl);
}

void vtc_disable_generator(volatile uint8_t *vtcBase)
{
    uint32_t ctl = mmio_read32(vtcBase, XVTC_CTL_OFFSET);
    ctl &= ~XVTC_CTL_GE_MASK;
    mmio_write32(vtcBase, XVTC_CTL_OFFSET, ctl | XVTC_CTL_RU_MASK | XVTC_CTL_SW_MASK);
}
