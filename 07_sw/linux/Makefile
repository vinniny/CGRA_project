# =============================================================================
# Makefile — Linux user-space tools for the CGRA on Haoyue
# Cross-compiled from WSL2 with Vitis 2025.1's arm-linux-gnueabihf-gcc.
# Targets: ARM Cortex-A9 hard-float (matches Wildfire's 5.15.0-xilinx kernel).
# =============================================================================

# VITIS_BIN := /tools/Xilinx/2025.1/Vitis/gnu/aarch32/lin/gcc-arm-linux-gnueabi/bin
CC        := gcc
CXX       := g++
SIZE      := size

CFLAGS  := -O2 -Wall -Wextra -mcpu=cortex-a9 -mfpu=neon-vfpv3 -mfloat-abi=hard \
           -ffunction-sections -fdata-sections \
           -I../driver -I../lib -I../baremetal
LDFLAGS := -Wl,--gc-sections -lm -lcma

BUILD := build

DRIVER_SRC := ../driver/cgra_driver.c
GOLDEN_SRC := ../lib/lpr_golden.c

# ── Targets ──────────────────────────────────────────────────────────────
SMOKE_SRC  := cgra_smoke.c $(DRIVER_SRC)
SMOKE_BIN  := $(BUILD)/cgra_smoke

DEMO_SRC   := lpr_live_demo_v2.c $(DRIVER_SRC)
DEMO_BIN   := $(BUILD)/lpr_live_demo_v2

EVAL_SRC   := lpr_eval.c $(GOLDEN_SRC)
EVAL_BIN   := $(BUILD)/lpr_eval

EVAL_CGRA_SRC := lpr_eval.c $(GOLDEN_SRC) ../lib/cgra_baremetal_shim.c $(DRIVER_SRC)
EVAL_CGRA_BIN := $(BUILD)/lpr_eval_cgra

HDMI_DEMO_SRC := lpr_hdmi_demo.c $(GOLDEN_SRC) ../lib/cgra_baremetal_shim.c $(DRIVER_SRC)
HDMI_DEMO_BIN := $(BUILD)/lpr_hdmi_demo

DMATEST_SRC := cgra_dmatest.c $(DRIVER_SRC)
DMATEST_BIN := $(BUILD)/cgra_dmatest

FCLK2_SRC := fclk2_enable.c
FCLK2_BIN := $(BUILD)/fclk2_enable

PROBE_SRC := lpr_fc_probe.c $(DRIVER_SRC) ../lib/cgra_baremetal_shim.c
PROBE_BIN := $(BUILD)/lpr_fc_probe

ALL_BINS := $(SMOKE_BIN) $(DEMO_BIN) $(EVAL_BIN) $(DMATEST_BIN) $(FCLK2_BIN) $(PROBE_BIN)

.PHONY: all clean smoke demo eval dmatest fclk2 fcprobe deploy

all: smoke

smoke: $(SMOKE_BIN)

demo: $(DEMO_BIN)

eval: $(EVAL_BIN)

eval_cgra: $(EVAL_CGRA_BIN)

hdmi_demo: $(HDMI_DEMO_BIN)

dmatest: $(DMATEST_BIN)

fclk2: $(FCLK2_BIN)

fcprobe: $(PROBE_BIN)

$(BUILD):
	mkdir -p $(BUILD)

$(SMOKE_BIN): $(SMOKE_SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SMOKE_SRC)
	@echo "[BUILD] $@"
	@$(SIZE) $@

$(DEMO_BIN): $(DEMO_SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(DEMO_SRC)
	@echo "[BUILD] $@"
	@$(SIZE) $@

$(EVAL_BIN): $(EVAL_SRC) lpr_eval.c | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $(EVAL_SRC) $(LDFLAGS)
	@echo "[BUILD] $@"
	@$(SIZE) $@

# CGRA-FC build: -DUSE_CGRA_INFER pulls golden_infer_cgra into lpr_golden.c,
# and override LPR_CGRA_*_DDR to safe Linux-side addresses (top of CMA-reserved
# region, below 0x40000000, mapped MAP_FIXED uncached at runtime).
CGRA_FC_DEFS := -DUSE_CGRA_INFER -DCGRA_LINUX_SHIM \
                -DLPR_CGRA_POOL2_Q_DDR=0x3FFE0000UL \
                -DLPR_CGRA_STAGING_DDR=0x3FFE2000UL

$(EVAL_CGRA_BIN): $(EVAL_CGRA_SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(CGRA_FC_DEFS) -o $@ $(EVAL_CGRA_SRC) $(LDFLAGS)
	@echo "[BUILD] $@"
	@$(SIZE) $@

$(HDMI_DEMO_BIN): $(HDMI_DEMO_SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(CGRA_FC_DEFS) -o $@ $(HDMI_DEMO_SRC) $(LDFLAGS)
	@echo "[BUILD] $@"
	@$(SIZE) $@

$(DMATEST_BIN): $(DMATEST_SRC) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $(DMATEST_SRC) $(LDFLAGS)
	@echo "[BUILD] $@"
	@$(SIZE) $@

$(FCLK2_BIN): $(FCLK2_SRC) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $(FCLK2_SRC) $(LDFLAGS)
	@echo "[BUILD] $@"
	@$(SIZE) $@

$(PROBE_BIN): $(PROBE_SRC) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $(PROBE_SRC) $(LDFLAGS)
	@echo "[BUILD] $@"
	@$(SIZE) $@

# Push compiled binary onto the board via SSH (uses ~/.ssh/config "haoyue" host).
deploy: smoke
	scp $(SMOKE_BIN) haoyue:/home/root/cgra/

clean:
	rm -rf $(BUILD)

# Helpful prints
info:
	@echo "Cross compiler: $(CC)"
	@echo "Targets       : $(ALL_BINS)"
