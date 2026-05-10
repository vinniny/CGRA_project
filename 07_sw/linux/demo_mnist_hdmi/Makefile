# Makefile — cross-build the MNIST live HDMI demo for PYNQ-Z2 PetaLinux.
#
# Toolchain: arm-linux-musleabihf-cross from musl.cc, installed at
# ~/toolchains/arm-linux-musleabihf-cross/. Override with MUSL_TC=...
# Static-linked → no glibc/musl dependency on the target rootfs.
#
# Targets so far:
#   make fb_test      — M1 smoke: draw 4 corners + white rect to FB
#   make clean        — remove build artifacts
#
# Future milestone targets (M2..M5) are added here as the demo grows.
#
# Deploy: scp build/<binary> petalinux@<board>:/tmp/

MUSL_TC ?= $(HOME)/toolchains/arm-linux-musleabihf-cross
CC       = $(MUSL_TC)/bin/arm-linux-musleabihf-gcc

# -fno-tree-vectorize: same defensive setting as scripts/fb_paint.c — keeps
# memcpy on the scalar path so we never hit unaligned NEON loads on the
# /dev/mem-mapped FB region.
REPO_ROOT := $(abspath $(CURDIR)/../../..)

# -DSWEEP_RODATA= : override the bare-metal section attribute in the fixture
#   so the data lands in default rodata when linked into a Linux ELF.
CFLAGS  = -O2 -Wall -Wextra -static \
          -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard \
          -fno-tree-vectorize \
          -I. \
          -I$(REPO_ROOT)/07_sw/baremetal \
          -DSWEEP_RODATA=

BUILD_DIR = build

# fb_test (M1)
FB_TEST_SRCS = fb_test.c fb_lib.c
FB_TEST_OBJS = $(addprefix $(BUILD_DIR)/, $(FB_TEST_SRCS:.c=.o))
FB_TEST_BIN  = $(BUILD_DIR)/fb_test

# fb_test2 (M2)
FB_TEST2_SRCS = fb_test2.c fb_lib.c font5x7.c
FB_TEST2_OBJS = $(addprefix $(BUILD_DIR)/, $(FB_TEST2_SRCS:.c=.o))
FB_TEST2_BIN  = $(BUILD_DIR)/fb_test2

.PHONY: all clean toolchain-check fb_test fb_test2
all: fb_test fb_test2

fb_test: toolchain-check $(FB_TEST_BIN)
	@:

fb_test2: toolchain-check $(FB_TEST2_BIN)
	@:

$(FB_TEST2_BIN): $(FB_TEST2_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Built: $@ ($$(stat -c %s $@) bytes)"
	@file $@

$(FB_TEST_BIN): $(FB_TEST_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Built: $@ ($$(stat -c %s $@) bytes)"
	@file $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

toolchain-check:
	@if [ ! -x $(CC) ]; then \
	    echo "ERROR: cross-gcc not found at $(CC)"; \
	    echo "Install once with:"; \
	    echo "  mkdir -p $$(dirname $(MUSL_TC)) && cd $$(dirname $(MUSL_TC))"; \
	    echo "  curl -fLO https://musl.cc/arm-linux-musleabihf-cross.tgz"; \
	    echo "  tar xzf arm-linux-musleabihf-cross.tgz"; \
	    exit 1; \
	fi

clean:
	rm -rf $(BUILD_DIR)
