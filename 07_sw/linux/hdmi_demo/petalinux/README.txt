Put these files under:
  project-spec/meta-user/recipes-apps/hdmi-demo/files/

And put hdmi-demo.bb here:
  project-spec/meta-user/recipes-apps/hdmi-demo/hdmi-demo.bb

Before build, edit platform_config.h:
  - HDMI_FB_BASE / HDMI_FB_SIZE must match reserved-memory in system-user.dtsi
  - DYNCLK_UIO_NAME / VTC_UIO_NAME / VDMA_UIO_NAME must match /sys/class/uio/uioX/name

Runtime check on target:
  ls /sys/class/uio/uio*/name
  dmesg | grep -i uio
  hdmi-demo

Notes:
  - This code is a bring-up path for a single RGB888 framebuffer.
  - It assumes AXI VDMA MM2S direct register mode.
  - It assumes VTC generator is enabled from software.
  - If your HDMI TX uses a different pixel component order, swap bytes in fill_colorbar().
