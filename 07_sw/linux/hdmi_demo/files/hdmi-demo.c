#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "platform_config.h"
#include "lcd_modes.h"
#include "mmio_util.h"
#include "dynclk.h"
#include "vtc.h"
#include "vdma.h"

static void fill_colorbar(volatile uint8_t *fb, const VideoMode *mode)
{
    const uint32_t width = mode->width;
    const uint32_t height = mode->height;
    const uint32_t bar0 = width / 3u;
    const uint32_t bar1 = (width * 2u) / 3u;

    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width; ++x) {
            const uint32_t idx = (y * width + x) * 3u;

            if (x < bar0) {
                /* Red bar in BGR byte order */
                fb[idx + 0] = 0x00; /* B */
                fb[idx + 1] = 0x00; /* G */
                fb[idx + 2] = 0xFF; /* R */
            } else if (x < bar1) {
                /* Green bar */
                fb[idx + 0] = 0x00;
                fb[idx + 1] = 0xFF;
                fb[idx + 2] = 0x00;
            } else {
                /* Blue bar */
                fb[idx + 0] = 0xFF;
                fb[idx + 1] = 0x00;
                fb[idx + 2] = 0x00;
            }
        }
    }
}

static void dump_regs(volatile uint8_t *dynclk,
                      volatile uint8_t *vtc,
                      volatile uint8_t *vdma)
{
    printf("dynclk ctrl   = 0x%08" PRIx32 "\n", mmio_read32(dynclk, 0x00));
    printf("dynclk status = 0x%08" PRIx32 "\n", mmio_read32(dynclk, 0x04));

    printf("vtc control   = 0x%08" PRIx32 "\n", mmio_read32(vtc, 0x00));
    printf("vtc status    = 0x%08" PRIx32 "\n", mmio_read32(vtc, 0x04));

    printf("vdma cr       = 0x%08" PRIx32 "\n", vdma_mm2s_control(vdma));
    printf("vdma sr       = 0x%08" PRIx32 "\n", vdma_mm2s_status(vdma));
    printf("vdma vsize    = 0x%08" PRIx32 "\n", mmio_read32(vdma, 0x50));
    printf("vdma hsize    = 0x%08" PRIx32 "\n", mmio_read32(vdma, 0x54));
    printf("vdma stride   = 0x%08" PRIx32 "\n", mmio_read32(vdma, 0x58));
    printf("vdma fb addr0 = 0x%08" PRIx32 "\n", mmio_read32(vdma, 0x5c));
}

int main(void)
{
    const VideoMode mode = HDMI_DEFAULT_MODE;
    volatile uint8_t *dynclk = NULL, *vtc = NULL, *vdma = NULL, *fb = NULL;
    int dynclk_fd = -1, vtc_fd = -1, vdma_fd = -1, fb_fd = -1;
    double actual_freq = 0.0;
    int ret;

    printf("hdmi-demo: start (%s %ux%u %.3f MHz)\n",
           mode.label, mode.width, mode.height, mode.freq);

    ret = mmio_map_physical(DYNCLK_BASE, DYNCLK_SIZE, &dynclk, &dynclk_fd);
    if (ret) {
        fprintf(stderr, "map dynclk failed: %s\n", strerror(-ret));
        goto out;
    }

    ret = mmio_map_physical(VTC_BASE, VTC_SIZE, &vtc, &vtc_fd);
    if (ret) {
        fprintf(stderr, "map vtc failed: %s\n", strerror(-ret));
        goto out;
    }

    ret = mmio_map_physical(VDMA_BASE, VDMA_SIZE, &vdma, &vdma_fd);
    if (ret) {
        fprintf(stderr, "map vdma failed: %s\n", strerror(-ret));
        goto out;
    }

    ret = mmio_map_physical(HDMI_FB_BASE, HDMI_FB_SIZE, &fb, &fb_fd);
    if (ret) {
        fprintf(stderr, "map framebuffer failed: %s\n", strerror(-ret));
        goto out;
    }

    printf("hdmi-demo: mapped dynclk=0x%08X vtc=0x%08X vdma=0x%08X fb=0x%08X\n",
           DYNCLK_BASE, VTC_BASE, VDMA_BASE, HDMI_FB_BASE);

    fill_colorbar(fb, &mode);
    __sync_synchronize();

    ret = dynclk_program(dynclk, &mode, &actual_freq);
    if (ret) {
        fprintf(stderr, "dynclk programming failed\n");
        dump_regs(dynclk, vtc, vdma);
        goto out;
    }

    ret = vtc_configure_generator(vtc, &mode);
    if (ret) {
        fprintf(stderr, "vtc configure failed\n");
        dump_regs(dynclk, vtc, vdma);
        goto out;
    }

    ret = vdma_start_mm2s(vdma, HDMI_FB_BASE, mode.width, mode.height, 3u, mode.width * 3u);
    if (ret) {
        fprintf(stderr, "vdma start failed, status=0x%08" PRIx32 "\n", vdma_mm2s_status(vdma));
        dump_regs(dynclk, vtc, vdma);
        goto out;
    }

    vtc_enable_generator(vtc);

    printf("hdmi-demo: running, actual pixel clock %.6f MHz\n", actual_freq);
    dump_regs(dynclk, vtc, vdma);
    printf("hdmi-demo: FB @ 0x%08X\n", HDMI_FB_BASE);

    return 0;

out:
    if (fb) {
        mmio_unmap(fb, HDMI_FB_SIZE, fb_fd);
        fb = NULL;
        fb_fd = -1;
    }
    if (vdma) {
        mmio_unmap(vdma, VDMA_SIZE, vdma_fd);
        vdma = NULL;
        vdma_fd = -1;
    }
    if (vtc) {
        mmio_unmap(vtc, VTC_SIZE, vtc_fd);
        vtc = NULL;
        vtc_fd = -1;
    }
    if (dynclk) {
        mmio_unmap(dynclk, DYNCLK_SIZE, dynclk_fd);
        dynclk = NULL;
        dynclk_fd = -1;
    }

    return 1;
}
