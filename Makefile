# ==============================================================================
# CGRA Project Makefile
# ==============================================================================
# Usage:
#   make compile TB=<testbench>   - Compile a testbench
#   make sim TB=<testbench>       - Compile and run simulation
#   make wave TB=<testbench>      - Open waveform in GTKWave
#   make clean                    - Remove all generated files
#   make list                     - List available testbenches
#
# Available testbenches:
#   tb_cgra_top_golden       - Top-level integration (6 tests)
#   tb_cgra_array_4x4_golden - 4x4 mesh routing (6 tests)
#   tb_cgra_tile_memory_golden - Tile memory
#   tb_cgra_axi_csr_golden   - AXI CSR interface
#   tb_cgra_dma_engine_golden - DMA engine
#
# Example:
#   make sim TB=tb_cgra_top_golden
# ==============================================================================

# Directories
SRC_DIR  := 00_src
TB_DIR   := 01_bench
SIM_DIR  := 03_sim

# Default testbench
TB ?= tb_cgra_top_golden

# Output files
VVP_FILE := $(SIM_DIR)/$(TB).vvp
VCD_FILE := $(SIM_DIR)/$(TB).vcd

# Compiler and flags
IVERILOG := iverilog
VVP      := vvp
GTKWAVE  := gtkwave
VFLAGS   := -g2012

# RTL Source files (order matters for dependencies)
RTL_SRCS := \
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

# Testbench file
TB_SRC := $(TB_DIR)/$(TB).sv

# ==============================================================================
# Targets
# ==============================================================================

.PHONY: all compile sim wave clean list help

# Default target
all: sim

# Compile testbench
compile: $(VVP_FILE)

$(VVP_FILE): $(RTL_SRCS) $(TB_SRC)
	@echo "============================================"
	@echo "Compiling: $(TB)"
	@echo "============================================"
	@mkdir -p $(SIM_DIR)
	$(IVERILOG) $(VFLAGS) -o $(VVP_FILE) $(RTL_SRCS) $(TB_SRC)
	@echo "Output: $(VVP_FILE)"

# Run simulation
sim: compile
	@echo "============================================"
	@echo "Running: $(TB)"
	@echo "============================================"
	cd $(SIM_DIR) && $(VVP) $(TB).vvp
	@if [ -f $(VCD_FILE) ]; then \
		echo "Waveform: $(VCD_FILE)"; \
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
	@echo "Done."

# List available testbenches
list:
	@echo "Available testbenches:"
	@echo "  tb_cgra_top_golden         - Top-level integration (6 tests)"
	@echo "  tb_cgra_array_4x4_golden   - 4x4 mesh routing (6 tests)"
	@echo "  tb_cgra_tile_memory_golden - Tile memory (10 tests)"
	@echo "  tb_cgra_axi_csr_golden     - AXI CSR interface (10 tests)"
	@echo "  tb_cgra_dma_engine_golden  - DMA engine (10 tests)"
	@echo ""
	@echo "Usage: make sim TB=<testbench_name>"

# Help
help:
	@echo "CGRA Project Makefile"
	@echo "====================="
	@echo ""
	@echo "Targets:"
	@echo "  compile  - Compile testbench (TB=<name>)"
	@echo "  sim      - Compile and run simulation (TB=<name>)"
	@echo "  wave     - Open VCD waveform in GTKWave (TB=<name>)"
	@echo "  clean    - Remove generated files"
	@echo "  list     - Show available testbenches"
	@echo "  help     - Show this help"
	@echo ""
	@echo "Examples:"
	@echo "  make sim TB=tb_cgra_top_golden"
	@echo "  make wave TB=tb_cgra_array_4x4_golden"
	@echo "  make sim  (uses default: tb_cgra_top_golden)"
