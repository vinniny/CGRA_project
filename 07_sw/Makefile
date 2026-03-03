# ===================================================================
#  Makefile – CGRA 4×4 LPR Demo Software (PYNQ-Z2 / PetaLinux)
#
#  Targets:
#    make all        – Build everything (native or cross-compile)
#    make lpr_demo   – Build demo application
#    make test_tiler – Build standalone tiler unit test
#    make clean      – Remove build artifacts
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
DRIVER_SRC = $(DRIVER_DIR)/cgra_driver.c
LIB_SRC    = $(LIB_DIR)/cgra_tiler.c
APP_SRC    = $(APP_DIR)/lpr_demo.c

DRIVER_OBJ = $(BUILD_DIR)/cgra_driver.o
LIB_OBJ    = $(BUILD_DIR)/cgra_tiler.o
APP_OBJ    = $(BUILD_DIR)/lpr_demo.o

ALL_OBJS   = $(DRIVER_OBJ) $(LIB_OBJ) $(APP_OBJ)

# ── Targets ───────────────────────────────────────────────────────
.PHONY: all clean test_tiler

all: $(BUILD_DIR) lpr_demo

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# LPR Demo application
lpr_demo: $(ALL_OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)
	@echo "[BUILD] $(BUILD_DIR)/lpr_demo ready"

# Object files
$(BUILD_DIR)/cgra_driver.o: $(DRIVER_SRC) $(DRIVER_DIR)/cgra_driver.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(DRIVER_DIR) -c $< -o $@

$(BUILD_DIR)/cgra_tiler.o: $(LIB_SRC) $(LIB_DIR)/cgra_tiler.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

$(BUILD_DIR)/lpr_demo.o: $(APP_SRC) $(DRIVER_DIR)/cgra_driver.h $(LIB_DIR)/cgra_tiler.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(DRIVER_DIR) -I$(LIB_DIR) -c $< -o $@

# Standalone tiler test (no HW dependencies)
test_tiler: $(BUILD_DIR) $(BUILD_DIR)/cgra_tiler.o $(BUILD_DIR)/test_tiler.o
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $(BUILD_DIR)/cgra_tiler.o $(BUILD_DIR)/test_tiler.o $(LDFLAGS)
	@echo "[BUILD] $(BUILD_DIR)/test_tiler ready"

$(BUILD_DIR)/test_tiler.o: $(APP_DIR)/test_tiler.c $(LIB_DIR)/cgra_tiler.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
