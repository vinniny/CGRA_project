SUMMARY = "HDMI demo user-space app"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://hdmi-demo.c \
           file://mmio_util.c \
           file://mmio_util.h \
           file://platform_config.h \
           file://lcd_modes.h \
           file://dynclk.c \
           file://dynclk.h \
           file://vtc.c \
           file://vtc.h \
           file://vdma.c \
           file://vdma.h \
           file://Makefile \
          "

S = "${WORKDIR}"

do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 hdmi-demo ${D}${bindir}
}
