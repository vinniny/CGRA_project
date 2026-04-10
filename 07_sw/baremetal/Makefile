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

.PHONY: all clean dis demo

all: $(TARGET)

demo: $(DEMO_TARGET)

$(TARGET): $(SRCS) uart.h cgra.h gic.h linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $@
	@echo "[BUILD] $(TARGET) OK"
	@$(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-size $@

$(DEMO_TARGET): $(DEMO_SRCS) xparameters.h bspconfig.h linker.ld
	$(CC) $(DEMO_CFLAGS) $(DEMO_LDFLAGS) $(DEMO_SRCS) $(DEMO_LIBS) -o $@
	@echo "[BUILD] $(DEMO_TARGET) OK"
	@$(VITIS)/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-size $@

dis: $(TARGET)
	$(OBJDUMP) -d $@ | less

clean:
	rm -f $(TARGET) $(DEMO_TARGET) *.o
