# ==============================================================================
# CGRA Project Makefile
# ==============================================================================
# Usage:
#   make sim                      - Run master verification (80 tests)
#   make compile                  - Compile testbench only
#   make wave                     - Open waveform in GTKWave
#   make clean                    - Remove all generated files
#   make help                     - Show available commands
#
# Example:
#   make sim
#   make wave
# ==============================================================================

# Directories
SRC_DIR  := 00_src
BSG_DIR  := 00_src/bsg_mem
TB_DIR   := 01_bench
SIM_DIR  := 03_sim

# Output files
VVP_FILE := $(SIM_DIR)/tb_top.vvp
VCD_FILE := $(SIM_DIR)/cgra_master_sim.vcd

# Compiler and flags
IVERILOG := iverilog
VVP      := vvp
GTKWAVE  := gtkwave
VFLAGS   := -g2012 -I$(SRC_DIR) -I$(BSG_DIR) -I$(TB_DIR)

# BSG Library files (must be compiled FIRST for macro definitions)
BSG_SRCS := \
	$(BSG_DIR)/bsg_defines.sv \
	$(BSG_DIR)/bsg_dff.sv \
	$(BSG_DIR)/bsg_dff_en_bypass.sv \
	$(BSG_DIR)/bsg_mem_1r1w_sync_synth.sv \
	$(BSG_DIR)/bsg_mem_1r1w_sync.sv \
	$(BSG_DIR)/cgra_config_mem_bsg.sv

# RTL Source files (order matters for dependencies)
RTL_SRCS := \
	$(SRC_DIR)/axi_ram.sv \
	$(SRC_DIR)/cgra_pe.sv \
	$(SRC_DIR)/cgra_router.sv \
	$(SRC_DIR)/cgra_tile.sv \
	$(SRC_DIR)/cgra_array_4x4.sv \
	$(SRC_DIR)/cgra_tile_memory.sv \
	$(SRC_DIR)/cgra_axi_csr.sv \
	$(SRC_DIR)/cgra_control_unit.sv \
	$(SRC_DIR)/cgra_config_loader.sv \
	$(SRC_DIR)/cgra_dma_engine.sv \
	$(SRC_DIR)/cgra_top.sv

# Testbench files
TB_SRCS := \
	$(TB_DIR)/cgra_protocol_monitor.sv \
	$(TB_DIR)/tb_top.sv

# All sources in correct compilation order
ALL_SRCS := $(BSG_SRCS) $(RTL_SRCS) $(TB_SRCS)

# ==============================================================================
# Targets
# ==============================================================================

.PHONY: all compile sim wave clean help

# Default target
all: sim

# Compile testbench
compile: $(VVP_FILE)

$(VVP_FILE): $(ALL_SRCS) $(TB_DIR)/tb_tasks.svh $(TB_DIR)/tb_test_suites.svh
	@echo "============================================"
	@echo "Compiling CGRA Master Testbench (80 tests)"
	@echo "============================================"
	@mkdir -p $(SIM_DIR)
	$(IVERILOG) $(VFLAGS) -o $(VVP_FILE) $(ALL_SRCS)
	@echo "Output: $(VVP_FILE)"

# Run simulation
sim: compile
	@echo "============================================"
	@echo "Running 80-Vector Master Verification"
	@echo "============================================"
	cd $(SIM_DIR) && $(VVP) ../$(VVP_FILE)
	@if [ -f $(VCD_FILE) ]; then \
		echo ""; \
		echo "Waveform: $(VCD_FILE)"; \
		echo "View with: make wave"; \
	fi

# Open waveform viewer
wave: $(VCD_FILE)
	@echo "Opening waveform: $(VCD_FILE)"
	$(GTKWAVE) $(VCD_FILE) &

$(VCD_FILE): sim

# Clean generated files
clean:
	@echo "Cleaning simulation files..."
	rm -f $(SIM_DIR)/*.vvp $(SIM_DIR)/*.vcd $(SIM_DIR)/*.log
	rm -f *.vcd
	@echo "Done."

# Help
help:
	@echo ""
	@echo "CGRA Master Verification Makefile"
	@echo "=================================="
	@echo ""
	@echo "Commands:"
	@echo "  make sim     - Compile and run 80-test verification suite"
	@echo "  make compile - Compile testbench only"
	@echo "  make wave    - Open waveform in GTKWave"  
	@echo "  make clean   - Remove generated files"
	@echo "  make help    - Show this help"
	@echo ""
	@echo "Test Coverage (80 vectors):"
	@echo "  Suite A: Register Logic & Config (19 tests)"
	@echo "  Suite B: DMA Datapath (16 tests)"
	@echo "  Suite C: Protocol Compliance (15 tests)"
	@echo "  Suite D: Performance & Timing (10 tests)"
	@echo "  Suite E: Stress Testing (10 tests)"
	@echo "  Suite F: System Integration (10 tests)"
	@echo ""
