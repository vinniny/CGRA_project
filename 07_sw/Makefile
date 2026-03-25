# ===================================================================
#  Makefile – CGRA 4×4 LPR Demo Software (PYNQ-Z2 / PetaLinux)
#
#  Targets:
#    make all            – Build everything (native or cross-compile)
#    make lpr_demo       – Build demo application (requires CGRA HW)
#    make lpr_golden_test – Build golden model test (no HW needed)
#    make lpr_cgra_accel – Build CGRA-accelerated classifier (requires HW)
#    make test_tiler     – Build standalone tiler unit test
#    make clean          – Remove build artifacts
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
DRIVER_SRC  = $(DRIVER_DIR)/cgra_driver.c
TILER_SRC   = $(LIB_DIR)/cgra_tiler.c
GOLDEN_SRC  = $(LIB_DIR)/lpr_golden.c
APP_SRC     = $(APP_DIR)/lpr_demo.c

DRIVER_OBJ  = $(BUILD_DIR)/cgra_driver.o
TILER_OBJ   = $(BUILD_DIR)/cgra_tiler.o
GOLDEN_OBJ  = $(BUILD_DIR)/lpr_golden.o
APP_OBJ     = $(BUILD_DIR)/lpr_demo.o

ALL_OBJS    = $(DRIVER_OBJ) $(TILER_OBJ) $(APP_OBJ)

# ── Targets ───────────────────────────────────────────────────────
.PHONY: all clean test_tiler lpr_golden_test test dump_cgra_hex dump_hex

all: $(BUILD_DIR) lpr_demo lpr_cgra_accel lpr_golden_test dump_cgra_hex

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# LPR Demo application (requires CGRA hardware)
lpr_demo: $(ALL_OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)
	@echo "[BUILD] $(BUILD_DIR)/lpr_demo ready"

# CGRA-accelerated LPR classifier (INT8/16 quantized FC offload)
lpr_cgra_accel: $(DRIVER_OBJ) $(TILER_OBJ) $(GOLDEN_OBJ) $(BUILD_DIR)/lpr_cgra_accel.o
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)
	@echo "[BUILD] $(BUILD_DIR)/lpr_cgra_accel ready"

$(BUILD_DIR)/lpr_cgra_accel.o: $(APP_DIR)/lpr_cgra_accel.c $(DRIVER_DIR)/cgra_driver.h $(LIB_DIR)/cgra_tiler.h $(LIB_DIR)/lpr_golden.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(DRIVER_DIR) -I$(LIB_DIR) -c $< -o $@

# Golden model test (no HW dependencies — runs anywhere)
lpr_golden_test: $(BUILD_DIR)/lpr_golden_test.o $(GOLDEN_OBJ)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)
	@echo "[BUILD] $(BUILD_DIR)/lpr_golden_test ready (no HW needed)"

# Convenience alias
test: lpr_golden_test
	$(BUILD_DIR)/lpr_golden_test

# Object files
$(BUILD_DIR)/cgra_driver.o: $(DRIVER_SRC) $(DRIVER_DIR)/cgra_driver.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(DRIVER_DIR) -c $< -o $@

$(BUILD_DIR)/cgra_tiler.o: $(TILER_SRC) $(LIB_DIR)/cgra_tiler.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

$(BUILD_DIR)/lpr_golden.o: $(GOLDEN_SRC) $(LIB_DIR)/lpr_golden.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

$(BUILD_DIR)/lpr_demo.o: $(APP_SRC) $(DRIVER_DIR)/cgra_driver.h $(LIB_DIR)/cgra_tiler.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(DRIVER_DIR) -I$(LIB_DIR) -c $< -o $@

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
