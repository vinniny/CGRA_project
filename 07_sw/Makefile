# ===================================================================
#  Makefile – CGRA 4×4 host-side test utilities
#
#  Targets:
#    make all             – Build everything (native or cross-compile)
#    make lpr_golden_test – Build golden model test (no HW needed)
#    make dump_cgra_hex   – Build CGRA hex dump utility (no HW)
#    make test_tiler      – Build standalone tiler unit test
#    make clean           – Remove build artifacts
#
#  For the live LPR demo, see 07_sw/linux/Makefile (lpr_live_demo_v2,
#  lpr_eval, lpr_hdmi_demo, lpr_fc_probe).
#
#  Cross-compilation for Zynq ARM:
#    make CROSS=arm-linux-gnueabihf-
# ===================================================================

# ── Toolchain ─────────────────────────────────────────────────────
CROSS   ?=
CC       = $(CROSS)gcc
AR       = $(CROSS)ar
CFLAGS   = -Wall -Wextra -O2 -std=c11
LDFLAGS  = -lrt -lm

# ── Directories ───────────────────────────────────────────────────
DRIVER_DIR = driver
LIB_DIR    = lib
APP_DIR    = app
BUILD_DIR  = build

# ── Sources ───────────────────────────────────────────────────────
TILER_SRC   = $(LIB_DIR)/cgra_tiler.c
GOLDEN_SRC  = $(LIB_DIR)/lpr_golden.c

TILER_OBJ   = $(BUILD_DIR)/cgra_tiler.o
GOLDEN_OBJ  = $(BUILD_DIR)/lpr_golden.o

# ── Targets ───────────────────────────────────────────────────────
.PHONY: all clean test_tiler lpr_golden_test test dump_cgra_hex dump_hex

all: $(BUILD_DIR) lpr_golden_test dump_cgra_hex test_tiler

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Golden model test (no HW dependencies — runs anywhere)
lpr_golden_test: $(BUILD_DIR)/lpr_golden_test.o $(GOLDEN_OBJ)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)
	@echo "[BUILD] $(BUILD_DIR)/lpr_golden_test ready (no HW needed)"

# Convenience alias
test: lpr_golden_test
	$(BUILD_DIR)/lpr_golden_test

# Object files
$(BUILD_DIR)/cgra_tiler.o: $(TILER_SRC) $(LIB_DIR)/cgra_tiler.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

$(BUILD_DIR)/lpr_golden.o: $(GOLDEN_SRC) $(LIB_DIR)/lpr_golden.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

$(BUILD_DIR)/lpr_golden_test.o: $(APP_DIR)/lpr_golden_test.c $(LIB_DIR)/lpr_golden.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

# CGRA hex dump utility (no HW — runs on host, outputs $readmemh files)
dump_cgra_hex: $(BUILD_DIR)/dump_cgra_hex.o $(GOLDEN_OBJ)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)
	@echo "[BUILD] $(BUILD_DIR)/dump_cgra_hex ready"

$(BUILD_DIR)/dump_cgra_hex.o: $(APP_DIR)/dump_cgra_hex.c $(LIB_DIR)/lpr_golden.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

# Convenience: build + run, writes .mem files to 01_bench/
dump_hex: dump_cgra_hex
	$(BUILD_DIR)/dump_cgra_hex ../01_bench/
	@echo "[DUMP] config.mem  image.mem  golden.mem → ../01_bench/"

# Standalone tiler test (no HW dependencies)
test_tiler: $(BUILD_DIR) $(BUILD_DIR)/cgra_tiler.o $(BUILD_DIR)/test_tiler.o
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $(BUILD_DIR)/cgra_tiler.o $(BUILD_DIR)/test_tiler.o $(LDFLAGS)
	@echo "[BUILD] $(BUILD_DIR)/test_tiler ready"

$(BUILD_DIR)/test_tiler.o: $(APP_DIR)/test_tiler.c $(LIB_DIR)/cgra_tiler.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
