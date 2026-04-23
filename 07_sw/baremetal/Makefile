# ==============================================================================
# Makefile — CGRA Bare-Metal Test
# Toolchain: arm-none-eabi-gcc from Vitis 2025.1
# ==============================================================================

VITIS   := /tools/Xilinx/2025.1/Vitis
CC      := $(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-gcc
OBJDUMP := $(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-objdump
OBJCOPY := $(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-objcopy

TARGET  := cgra_test.elf

CFLAGS  := -O1 -Wall -Wextra \
           -ffreestanding -nostdlib \
           -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard \
           -I.

LDFLAGS := -T linker.ld -nostdlib

SRCS    := start.s main.c gic.c

# ==============================================================================
# Vitis BSP source paths — used by the demo_ascii.elf target only.
# These are referenced (not vendored) directly from the Vitis install tree.
# ==============================================================================
VITIS_BSP    := /tools/Xilinx/2025.1/data/embeddedsw
BSP_COMMON   := $(VITIS_BSP)/lib/bsp/standalone_v9_2/src/common
BSP_ARM_COM  := $(VITIS_BSP)/lib/bsp/standalone_v9_2/src/arm/common
BSP_ARM_GCC  := $(VITIS_BSP)/lib/bsp/standalone_v9_2/src/arm/common/gcc
BSP_A9       := $(VITIS_BSP)/lib/bsp/standalone_v9_2/src/arm/cortexa9
BSP_SCUGIC   := $(VITIS_BSP)/XilinxProcessorIPLib/drivers/scugic_v5_5/src

DEMO_INC := -I. \
            -I$(BSP_COMMON) \
            -I$(BSP_ARM_COM) \
            -I$(BSP_ARM_GCC) \
            -I$(BSP_A9) \
            -I$(BSP_SCUGIC)

# PLATFORM_ZYNQ -> selects the Zynq-7000 IRQ count (95) in xscugic_hw.h.
# ARMA9 is defined by xscugic.h itself, don't redefine it from -D.
DEMO_DEFS := -DPLATFORM_ZYNQ -DUSE_AMP=0

DEMO_CFLAGS := -O1 -Wall -ffreestanding -nostdlib \
               -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard \
               -ffunction-sections -fdata-sections \
               $(DEMO_INC) $(DEMO_DEFS)

DEMO_LDFLAGS := -T linker.ld -nostdlib -Wl,--gc-sections

# libgcc gives us __aeabi_uidiv etc that the BSP cache helpers reference.
DEMO_LIBS := -lgcc

DEMO_SRCS := \
    start.s \
    demo_ascii_inverter.c \
    xscugic_g.c \
    $(BSP_COMMON)/xil_assert.c \
    $(BSP_COMMON)/xplatform_info.c \
    $(BSP_ARM_COM)/xil_exception.c \
    $(BSP_ARM_COM)/xil_spinlock.c \
    $(BSP_A9)/xil_cache.c \
    $(BSP_SCUGIC)/xscugic.c \
    $(BSP_SCUGIC)/xscugic_hw.c \
    $(BSP_SCUGIC)/xscugic_intr.c \
    $(BSP_SCUGIC)/xscugic_sinit.c

DEMO_TARGET := demo_ascii.elf

BENCH_SRCS   := start.s bench_cgra.c gic.c
BENCH_TARGET := bench_cgra.elf

BENCH_RES_SRCS   := start.s bench_resolution.c gic.c
BENCH_RES_TARGET := bench_resolution.elf

BENCH_TAI_SRCS   := start.s bench_tile_autoinc.c gic.c
BENCH_TAI_TARGET := bench_tile_autoinc.elf

# ── demo_lpr: VN plate OCR demo (ARM golden inference + CGRA DMA staging) ──
# Weights embedded via .incbin at DDR 0x800000 (linker_lpr.ld).
# Use -ffunction-sections + --gc-sections to drop lpr_golden's fopen/fread.
LPR_CFLAGS  := -O1 -Wall -ffreestanding -nostdlib \
               -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard \
               -ffunction-sections -fdata-sections \
               -I. -I../lib

LPR_LDFLAGS := -T linker_lpr.ld -nostdlib -Wl,--gc-sections

LPR_SRCS    := start.s demo_lpr.c demo_lpr_weights.S demo_lpr_images.S ../lib/lpr_golden.c

DEMO_LPR_TARGET := demo_lpr.elf

# ── demo_lpr_cgra: CGRA-accelerated FC variant (v1 — IMM weight-stationary) ─
LPR_CGRA_CFLAGS  := $(LPR_CFLAGS) -DUSE_CGRA_INFER
# Profile build: make demo_lpr_cgra LPR_CGRA_CFLAGS='$(LPR_CFLAGS) -DUSE_CGRA_INFER -DLPR_CGRA_PROFILE'
DEMO_LPR_CGRA_TARGET := demo_lpr_cgra.elf

# ── demo_lpr_cgra_v2: CGRA FC v2 — SPM weight preload (R1/R2/R3 required) ──
LPR_CGRA_V2_CFLAGS  := $(LPR_CFLAGS) -DUSE_CGRA_INFER_V2
# Profile build: make demo_lpr_cgra_v2 LPR_CGRA_V2_CFLAGS='$(LPR_CFLAGS) -DUSE_CGRA_INFER_V2 -DLPR_CGRA_PROFILE'
DEMO_LPR_CGRA_V2_TARGET := demo_lpr_cgra_v2.elf

.PHONY: all clean dis demo bench bench_res bench_tai demo_lpr demo_lpr_cgra demo_lpr_cgra_v2

all: $(TARGET)

demo: $(DEMO_TARGET)

demo_lpr: $(DEMO_LPR_TARGET)

demo_lpr_cgra: $(DEMO_LPR_CGRA_TARGET)

demo_lpr_cgra_v2: $(DEMO_LPR_CGRA_V2_TARGET)

bench: $(BENCH_TARGET)

bench_res: $(BENCH_RES_TARGET)

bench_tai: $(BENCH_TAI_TARGET)

$(BENCH_TARGET): $(BENCH_SRCS) uart.h cgra.h gic.h linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) $(BENCH_SRCS) -lgcc -o $@
	@echo "[BUILD] $(BENCH_TARGET) OK"
	@$(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-size $@

$(BENCH_RES_TARGET): $(BENCH_RES_SRCS) uart.h cgra.h gic.h linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) $(BENCH_RES_SRCS) -lgcc -o $@
	@echo "[BUILD] $(BENCH_RES_TARGET) OK"
	@$(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-size $@

$(BENCH_TAI_TARGET): $(BENCH_TAI_SRCS) uart.h cgra.h gic.h linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) $(BENCH_TAI_SRCS) -lgcc -o $@
	@echo "[BUILD] $(BENCH_TAI_TARGET) OK"
	@$(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-size $@

$(TARGET): $(SRCS) uart.h cgra.h gic.h linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $@
	@echo "[BUILD] $(TARGET) OK"
	@$(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-size $@

$(DEMO_TARGET): $(DEMO_SRCS) xparameters.h bspconfig.h linker.ld
	$(CC) $(DEMO_CFLAGS) $(DEMO_LDFLAGS) $(DEMO_SRCS) $(DEMO_LIBS) -o $@
	@echo "[BUILD] $(DEMO_TARGET) OK"
	@$(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-size $@

run_demo_lpr: $(DEMO_LPR_TARGET)
	@echo "Load $(DEMO_LPR_TARGET) with: make run_elf ELF=$(BAREMETAL_DIR)/$(DEMO_LPR_TARGET) BIT=..."

$(DEMO_LPR_TARGET): $(LPR_SRCS) uart.h cgra.h linker_lpr.ld demo_lpr_test_images.h demo_lpr_test_images.bin cgra_kernels_lpr.h
	$(CC) $(LPR_CFLAGS) $(LPR_LDFLAGS) $(LPR_SRCS) -lgcc -o $@
	@echo "[BUILD] $(DEMO_LPR_TARGET) OK"
	@$(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-size $@

$(DEMO_LPR_CGRA_TARGET): $(LPR_SRCS) uart.h cgra.h linker_lpr.ld demo_lpr_test_images.h demo_lpr_test_images.bin cgra_kernels_lpr.h ../lprnet_eval/golden_weights_int16.bin
	$(CC) $(LPR_CGRA_CFLAGS) $(LPR_LDFLAGS) $(LPR_SRCS) -lgcc -o $@
	@echo "[BUILD] $(DEMO_LPR_CGRA_TARGET) OK"
	@$(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-size $@

$(DEMO_LPR_CGRA_V2_TARGET): $(LPR_SRCS) uart.h cgra.h linker_lpr.ld demo_lpr_test_images.h demo_lpr_test_images.bin cgra_kernels_lpr.h ../lprnet_eval/golden_weights_int16.bin ../lprnet_eval/golden_weights_spm.bin
	$(CC) $(LPR_CGRA_V2_CFLAGS) $(LPR_LDFLAGS) $(LPR_SRCS) -lgcc -o $@
	@echo "[BUILD] $(DEMO_LPR_CGRA_V2_TARGET) OK"
	@$(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-size $@

dis: $(TARGET)
	$(OBJDUMP) -d $@ | less

clean:
	rm -f $(TARGET) $(DEMO_TARGET) $(BENCH_TARGET) $(BENCH_RES_TARGET) $(BENCH_TAI_TARGET) $(DEMO_LPR_TARGET) $(DEMO_LPR_CGRA_TARGET) $(DEMO_LPR_CGRA_V2_TARGET) *.o
