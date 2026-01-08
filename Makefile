# ==============================================================================
# CGRA Project Makefile
# ==============================================================================
# Usage:
#   make sim          - Run 140-test verification
#   make wave         - Open waveform viewer
#   make gui          - Run in GUI mode (Xcelium only)
#   make clean        - Remove generated files
#   make help         - Show available commands
#
# Tool Selection:
#   Edit TOOL variable below, or override on command line:
#   make sim TOOL=xcelium
# ==============================================================================

# ==============================================================================
# TOOL SELECTION - Change this to switch simulators
# ==============================================================================
# Options: iverilog, xcelium
TOOL ?= iverilog

# ==============================================================================
# Directories
# ==============================================================================
SRC_DIR  := 00_src
BSG_DIR  := 00_src/bsg_mem
TB_DIR   := 01_bench
SIM_DIR  := 03_sim

# ==============================================================================
# Source Files
# ==============================================================================

# BSG Library files (must be compiled FIRST)
BSG_SRCS := \
	$(BSG_DIR)/bsg_defines.sv \
	$(BSG_DIR)/bsg_dff.sv \
	$(BSG_DIR)/bsg_dff_en_bypass.sv \
	$(BSG_DIR)/bsg_mem_1r1w_sync_synth.sv \
	$(BSG_DIR)/bsg_mem_1r1w_sync.sv \
	$(BSG_DIR)/cgra_config_mem_bsg.sv

# RTL Source files
RTL_SRCS := \
	$(SRC_DIR)/axi_ram.sv \
	$(SRC_DIR)/cgra_pe.sv \
	$(SRC_DIR)/cgra_router.sv \
	$(SRC_DIR)/cgra_tile.sv \
	$(SRC_DIR)/cgra_array_4x4.sv \
	$(SRC_DIR)/cgra_tile_memory.sv \
	$(SRC_DIR)/cgra_apb_csr.sv \
	$(SRC_DIR)/cgra_control_unit.sv \
	$(SRC_DIR)/cgra_dma_engine.sv \
	$(SRC_DIR)/cgra_top.sv

# Testbench files
TB_SRCS := \
	$(TB_DIR)/cgra_protocol_monitor.sv \
	$(TB_DIR)/tb_top.sv

# All sources
ALL_SRCS := $(BSG_SRCS) $(RTL_SRCS) $(TB_SRCS)

# ==============================================================================
# Tool-Specific Variables
# ==============================================================================
VVP_FILE := $(SIM_DIR)/tb_top.vvp
VCD_FILE := $(SIM_DIR)/cgra_master_sim.vcd
SHM_FILE := $(SIM_DIR)/waves.shm

# ==============================================================================
# Targets
# ==============================================================================

.PHONY: all sim compile wave gui clean clean-all help create_flist

all: sim

# ------------------------------------------------------------------------------
# Main simulation target - switches based on TOOL
# ------------------------------------------------------------------------------
sim:
ifeq ($(TOOL),iverilog)
	@$(MAKE) _sim_iverilog
else ifeq ($(TOOL),xcelium)
	@$(MAKE) _sim_xcelium
else ifeq ($(TOOL),verilator)
	@$(MAKE) _sim_verilator
else
	@echo "ERROR: Unknown TOOL=$(TOOL). Use 'iverilog', 'xcelium', or 'verilator'"
	@exit 1
endif

# ------------------------------------------------------------------------------
# Waveform viewer - switches based on TOOL
# ------------------------------------------------------------------------------
wave:
ifeq ($(TOOL),iverilog)
	@gtkwave $(VCD_FILE) &
else ifeq ($(TOOL),xcelium)
	@simvision $(SHM_FILE) &
endif

# ------------------------------------------------------------------------------
# GUI mode (Xcelium only) - uses restore.tcl for waveform setup
# ------------------------------------------------------------------------------
gui: create_flist
	@mkdir -p $(SIM_DIR)
	@cd $(SIM_DIR) && xrun -gui -access +rwc -f flist -input ../$(TB_DIR)/restore.tcl

# ------------------------------------------------------------------------------
# Icarus Verilog Implementation
# ------------------------------------------------------------------------------
_sim_iverilog: _compile_iverilog
	@echo "============================================"
	@echo "Running 140-Vector Verification (iverilog)"
	@echo "============================================"
	@cd $(SIM_DIR) && vvp ../$(VVP_FILE)
	@echo ""
	@echo "Waveform: $(VCD_FILE)"
	@echo "View with: make wave"

_compile_iverilog:
	@echo "============================================"
	@echo "Compiling with Icarus Verilog"
	@echo "============================================"
	@mkdir -p $(SIM_DIR)
	@iverilog -g2012 -I$(SRC_DIR) -I$(BSG_DIR) -I$(TB_DIR) -I$(TB_DIR)/include -o $(VVP_FILE) $(ALL_SRCS)

# ------------------------------------------------------------------------------
# Verilator 5.x Implementation (with --timing mode)
# ------------------------------------------------------------------------------
VERILATOR = verilator
# Minimal waivers: only for RTL issues outside testbench control
# - UNOPTFLAT: circular ready mesh in cgra_array_4x4.sv (RTL design pattern)
# - EOFNEWLINE: BSG library files (external code)
VERILATOR_FLAGS = --binary --timing --trace -j 0 \
	-Wall -Wno-fatal \
	-Wno-UNOPTFLAT -Wno-EOFNEWLINE \
	--top-module tb_top \
	-I$(SRC_DIR) -I$(BSG_DIR) -I$(TB_DIR) -I$(TB_DIR)/include \
	+define+VERILATOR

_sim_verilator:
	@echo "============================================"
	@echo "Compiling with Verilator 5.x (--timing)"
	@echo "============================================"
	@mkdir -p $(SIM_DIR)
	$(VERILATOR) $(VERILATOR_FLAGS) \
		$(BSG_SRCS) $(RTL_SRCS) \
		$(TB_DIR)/tb_top.sv \
		$(TB_DIR)/sim_main.cpp
	@cp obj_dir/Vtb_top $(SIM_DIR)/Vtb_top
	@echo ""
	@echo "============================================"
	@echo "Running 166-Vector Verification (Verilator)"
	@echo "============================================"
	@cd $(SIM_DIR) && ./Vtb_top +trace
	@echo ""
	@echo "Waveform: $(SIM_DIR)/cgra_sim.vcd"
	@echo "View with: gtkwave $(SIM_DIR)/cgra_sim.vcd &"

# ------------------------------------------------------------------------------
# Cadence Xcelium Implementation
# ------------------------------------------------------------------------------
_sim_xcelium: create_flist
	@echo "============================================"
	@echo "Running 140-Vector Verification (Xcelium)"
	@echo "============================================"
	@mkdir -p $(SIM_DIR)
	@cd $(SIM_DIR) && xrun -access +rwc -f flist

# Generate file list for Xcelium (paths relative to SIM_DIR)
create_flist:
	@echo "-> Creating flist"
	@rm -f flist
	@echo "-sv" >> flist
	@echo "-timescale 1ns/1ps" >> flist
	@echo "-64bit" >> flist
	@echo "" >> flist
	@echo "# BSG MEMORY LIBRARY" >> flist
	@for f in $(BSG_SRCS); do echo ../$$f >> flist; done
	@echo "" >> flist
	@echo "# RTL SOURCE FILES" >> flist
	@for f in $(RTL_SRCS); do echo ../$$f >> flist; done
	@echo "" >> flist
	@echo "# TESTBENCH FILES" >> flist
	@echo "../$(TB_DIR)/cgra_protocol_monitor.sv" >> flist
	@echo "../$(TB_DIR)/tb_top.sv" >> flist
	@echo "" >> flist
	@echo "# INCLUDE DIRECTORIES" >> flist
	@echo "-incdir ../$(SRC_DIR)" >> flist
	@echo "-incdir ../$(BSG_DIR)" >> flist
	@echo "-incdir ../$(TB_DIR)" >> flist
	@echo "-incdir ../$(TB_DIR)/include" >> flist
	@mv flist $(SIM_DIR)/flist

# ------------------------------------------------------------------------------
# Clean
# ------------------------------------------------------------------------------
clean:
	@echo "-> CLEAN"
	@rm -rf $(SIM_DIR)/*.vvp $(SIM_DIR)/*.vcd $(SIM_DIR)/*.log
	@rm -rf xcelium.d *.shm *.log *.key *.history xrun.* *.diag
	@rm -rf flist INCA_libs *.vcd $(SIM_DIR)/*.shm

clean-all: clean
	@rm -rf $(SIM_DIR)

# ------------------------------------------------------------------------------
# Help
# ------------------------------------------------------------------------------
help:
	@echo ""
	@echo "CGRA Verification Makefile"
	@echo "=========================="
	@echo ""
	@echo "Current TOOL = $(TOOL)"
	@echo ""
	@echo "Commands:"
	@echo "  make sim          - Run 140-test verification"
	@echo "  make wave         - Open waveform viewer"
	@echo "  make gui          - Run in GUI mode (Xcelium)"
	@echo "  make clean        - Remove generated files"
	@echo "  make help         - Show this help"
	@echo ""
	@echo "Switch simulator:"
	@echo "  make sim TOOL=iverilog   - Use Icarus Verilog"
	@echo "  make sim TOOL=xcelium    - Use Cadence Xcelium"
	@echo ""
	@echo "Or edit line 20:  TOOL ?= xcelium"
	@echo ""
