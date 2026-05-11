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
# -DBOARD_PYNQ_BASE : selects CGRA APB at 0x43C80000 (PYNQ-base + CGRA bolt-on).
CFLAGS  = -O2 -Wall -Wextra -static \
          -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard \
          -fno-tree-vectorize \
          -Wno-array-bounds \
          -I. \
          -I$(REPO_ROOT)/07_sw/baremetal \
          -I$(REPO_ROOT)/07_sw/lib \
          -I$(REPO_ROOT)/07_sw/driver \
          -DSWEEP_RODATA= \
          -DBOARD_PYNQ_BASE

# Mark stack as non-executable in the ELF. Without this, musl-cross-gcc
# leaves the PT_GNU_STACK flag at the default (RWX), and the kernel emits
# a warning "Process '...' started with executable stack" on every run.
# Cosmetic but worth fixing — also future-proofs against kernels that
# enforce SIGKILL on exec-stack binaries.
LDFLAGS = -Wl,-z,noexecstack

BUILD_DIR = build

# fb_test (M1)
FB_TEST_SRCS = fb_test.c fb_lib.c
FB_TEST_OBJS = $(addprefix $(BUILD_DIR)/, $(FB_TEST_SRCS:.c=.o))
FB_TEST_BIN  = $(BUILD_DIR)/fb_test

# fb_test2 (M2)
FB_TEST2_SRCS = fb_test2.c fb_lib.c font5x7.c
FB_TEST2_OBJS = $(addprefix $(BUILD_DIR)/, $(FB_TEST2_SRCS:.c=.o))
FB_TEST2_BIN  = $(BUILD_DIR)/fb_test2

# test_inference (M3) — CGRA inference smoke test
# Includes the bare-metal weight blob (.S) and the existing cgra_driver.c.
TEST_INF_SRCS  = test_inference.c cgra_user.c
TEST_INF_DEPS  = $(REPO_ROOT)/07_sw/driver/cgra_driver.c \
                 $(REPO_ROOT)/07_sw/baremetal/demo_mnist_weights.S
TEST_INF_OBJS  = $(addprefix $(BUILD_DIR)/, $(TEST_INF_SRCS:.c=.o)) \
                 $(BUILD_DIR)/cgra_driver.o \
                 $(BUILD_DIR)/demo_mnist_weights.o
TEST_INF_BIN   = $(BUILD_DIR)/test_inference

.PHONY: all clean toolchain-check fb_test fb_test2 test_inference test_probe
all: fb_test fb_test2 test_inference

# test_probe — diagnostic for M3 debugging
TEST_PROBE_OBJS = $(BUILD_DIR)/test_probe.o $(BUILD_DIR)/cgra_user.o \
                  $(BUILD_DIR)/cgra_driver.o $(BUILD_DIR)/demo_mnist_weights.o
TEST_PROBE_BIN  = $(BUILD_DIR)/test_probe
test_probe: toolchain-check $(TEST_PROBE_BIN)
	@:
$(TEST_PROBE_BIN): $(TEST_PROBE_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "Built: $@ ($$(stat -c %s $@) bytes)"

# test_compare (M4) — ARM vs CGRA timing + accuracy
TEST_CMP_OBJS = $(BUILD_DIR)/test_compare.o $(BUILD_DIR)/cgra_user.o \
                $(BUILD_DIR)/cgra_driver.o $(BUILD_DIR)/demo_mnist_weights.o \
                $(BUILD_DIR)/arm_fc.o
TEST_CMP_BIN  = $(BUILD_DIR)/test_compare
.PHONY: test_compare
test_compare: toolchain-check $(TEST_CMP_BIN)
	@:
$(TEST_CMP_BIN): $(TEST_CMP_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "Built: $@ ($$(stat -c %s $@) bytes)"

# demo_mnist_hdmi (M5) — the full live HDMI demo binary
DEMO_OBJS = $(BUILD_DIR)/demo_mnist_hdmi.o $(BUILD_DIR)/fb_lib.o \
            $(BUILD_DIR)/font5x7.o $(BUILD_DIR)/cgra_user.o \
            $(BUILD_DIR)/cgra_driver.o $(BUILD_DIR)/demo_mnist_weights.o \
            $(BUILD_DIR)/arm_fc.o
DEMO_BIN  = $(BUILD_DIR)/demo_mnist_hdmi
.PHONY: demo_mnist_hdmi
demo_mnist_hdmi: toolchain-check $(DEMO_BIN)
	@:
$(DEMO_BIN): $(DEMO_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "Built: $@ ($$(stat -c %s $@) bytes)"

# test_arm_cnn (P1) — full ARM CNN reference accuracy + speed
# Brings in the Conv weight blob via demo_mnist_conv_weights.S.
TEST_ARM_CNN_OBJS = $(BUILD_DIR)/test_arm_cnn.o \
                    $(BUILD_DIR)/arm_cnn.o $(BUILD_DIR)/arm_fc.o \
                    $(BUILD_DIR)/demo_mnist_weights.o \
                    $(BUILD_DIR)/demo_mnist_conv_weights.o
TEST_ARM_CNN_BIN  = $(BUILD_DIR)/test_arm_cnn
.PHONY: test_arm_cnn
test_arm_cnn: toolchain-check $(TEST_ARM_CNN_BIN)
	@:
$(TEST_ARM_CNN_BIN): $(TEST_ARM_CNN_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -lm -o $@ $^
	@echo "Built: $@ ($$(stat -c %s $@) bytes)"

# Conv-weights blob — .incbin a binary file via assembler.
$(BUILD_DIR)/demo_mnist_conv_weights.o: demo_mnist_conv_weights.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

fb_test: toolchain-check $(FB_TEST_BIN)
	@:

fb_test2: toolchain-check $(FB_TEST2_BIN)
	@:

test_inference: toolchain-check $(TEST_INF_BIN)
	@:

$(FB_TEST2_BIN): $(FB_TEST2_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "Built: $@ ($$(stat -c %s $@) bytes)"
	@file $@

$(TEST_INF_BIN): $(TEST_INF_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "Built: $@ ($$(stat -c %s $@) bytes)"
	@file $@

# Driver lives in 07_sw/driver/ — compile from there.
$(BUILD_DIR)/cgra_driver.o: $(REPO_ROOT)/07_sw/driver/cgra_driver.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Weight blob: .incbin a binary file via assembler.
$(BUILD_DIR)/demo_mnist_weights.o: $(REPO_ROOT)/07_sw/baremetal/demo_mnist_weights.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(FB_TEST_BIN): $(FB_TEST_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
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
