# ==============================================================================
# CGRA Project Makefile - Cadence Xcelium / Genus / Conformal Flow
# ==============================================================================
# Version: 2.6.0 | March 2026
# ==============================================================================

# ==============================================================================
# Directory Structure
# ==============================================================================
SRC_DIR     := 00_src
BSG_DIR     := 00_src/bsg_mem
TB_DIR      := 01_bench
LOG_DIR     := 02_log
SIM_DIR     := 03_sim
SYN_DIR     := 04_syn
LEC_DIR     := 05_lec
SCRIPT_DIR  := scripts

# ==============================================================================
# Configurable Parameters
# ==============================================================================
# Synthesis
TOP_SYN         ?= cgra_top
GENUS_GUI_ENABLE ?= 0

# LEC
LEC_GUI_ENABLE  ?= 0
LEC_EFFORT      ?= Auto

# Simulation
SEED            ?= $(shell date +%s)
TEST_ITERS      ?= 500
CYCLES          ?= 100
CORE            ?= 4

# Coverage (set COV=1 to enable code+functional coverage)
COV             ?= 0
COV_DIR         := cov_work
COV_DUT         := cgra_top
COV_TEST        ?= full_sim
COV_ELAB_FLAGS  :=
COV_SIM_FLAGS   :=
ifeq ($(COV),1)
COV_ELAB_FLAGS  := -coverage all -covdut $(COV_DUT)
COV_SIM_FLAGS   := -covworkdir ../$(COV_DIR) -covoverwrite -covtest $(COV_TEST)
endif

# ==============================================================================
# Source Files
# ==============================================================================

# BSG Library files (must be compiled FIRST)
BSG_SRCS := \
	$(BSG_DIR)/bsg_defines.sv \
	$(BSG_DIR)/bsg_dff.sv \
	$(BSG_DIR)/bsg_dff_en.sv \
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

# All sources for simulation
ALL_SRCS := $(BSG_SRCS) $(RTL_SRCS) $(TB_SRCS)

# ==============================================================================
# Tool Commands
# ==============================================================================
XMVLOG  := xmvlog
XMELAB  := xmelab
XMSIM   := xmsim
GENUS   := genus
LEC     := lec

# ==============================================================================
# Phony Targets
# ==============================================================================
.PHONY: all help compile build run sim test lab_test wave clean clean-all \
        syn restore_syn lec full create_flist lint check_tools gui \
        cov cov_gui cov_report

# ==============================================================================
# Default Target
# ==============================================================================
all: test

# ==============================================================================
# Help
# ==============================================================================
help:
	@echo "=========================================================================="
	@echo " CGRA Project Makefile - Cadence Xcelium / Genus / Conformal"
	@echo "=========================================================================="
	@echo ""
	@echo " Simulation Targets:"
	@echo "   make compile      - Compile RTL sources with xmvlog"
	@echo "   make build        - Elaborate design with xmelab"
	@echo "   make run          - Run simulation with xmsim"
	@echo "   make sim          - Complete flow: compile + build + run"
	@echo "   make test         - Alias for sim"
	@echo "   make lab_test     - Run sanity + advanced + benchmark + stress"
	@echo "   make wave         - Open Simvision waveform viewer"
	@echo "   make gui          - Run Xcelium in GUI mode"
	@echo ""
	@echo " Coverage Targets:"
	@echo "   make cov          - Simulate with coverage collection (COV=1)"
	@echo "   make cov_report   - Generate text coverage summary from database"
	@echo "   make cov_gui      - Open SimVision with coverage database"
	@echo ""
	@echo " Synthesis & Formal Targets:"
	@echo "   make syn          - Run Genus synthesis"
	@echo "   make restore_syn  - Restore Genus with synthesized design"
	@echo "   make lec          - Run Conformal logical equivalence check"
	@echo "   make full         - Run complete flow (sim + syn + lec)"
	@echo ""
	@echo " Utility Targets:"
	@echo "   make lint         - Run Xcelium lint checks"
	@echo "   make clean        - Remove simulation artifacts"
	@echo "   make clean-all    - Remove all generated files"
	@echo ""
	@echo " Options:"
	@echo "   SEED=N                  - Set random seed (default: timestamp)"
	@echo "   CYCLES=N                - Cycles for stress test (default 100)"
	@echo "   TEST_ITERS=N            - Iterations per randomized testcase (default 500)"
	@echo "   CORE=N                  - Number of cores for parallel tools (default 4)"
	@echo "   COV=1                   - Enable coverage for build/run targets"
	@echo "   COV_TEST=name           - Coverage test name (default: full_sim)"
	@echo "   TOP_SYN=module          - Top module for synthesis (default cgra_top)"
	@echo "   GENUS_GUI_ENABLE=1      - Enable Genus GUI"
	@echo "   LEC_GUI_ENABLE=1        - Enable Conformal GUI"
	@echo "   LEC_EFFORT=Auto|Medium  - LEC comparison effort"
	@echo "=========================================================================="

# ==============================================================================
# SIMULATION TARGETS (Split Flow)
# ==============================================================================

# ------------------------------------------------------------------------------
# Step 1: Compile RTL with xmvlog
# ------------------------------------------------------------------------------
compile: create_flist
	@echo "=========================================================================="
	@echo " [COMPILE] Compiling RTL sources with xmvlog"
	@echo "=========================================================================="
	@mkdir -p $(SIM_DIR) $(LOG_DIR)
	cd $(SIM_DIR) && $(XMVLOG) -sv -f flist \
		-define XCELIUM \
		-define SEED=$(SEED) \
		-define TEST_ITERS=$(TEST_ITERS) \
		2>&1 | tee ../$(LOG_DIR)/compile.log
	@echo "[COMPILE] Done - see $(LOG_DIR)/compile.log"

# ------------------------------------------------------------------------------
# Step 2: Elaborate design with xmelab
# ------------------------------------------------------------------------------
build: 
	@echo "=========================================================================="
	@echo " [BUILD] Elaborating design with xmelab"
	@echo "=========================================================================="
	@mkdir -p $(LOG_DIR)
	cd $(SIM_DIR) && $(XMELAB) \
		-timescale 1ns/1ps \
		-access +rwc \
		$(COV_ELAB_FLAGS) \
		-snapshot snap \
		worklib.tb_top \
		2>&1 | tee ../$(LOG_DIR)/elaborate.log
	@echo "[BUILD] Done - see $(LOG_DIR)/elaborate.log"

# ------------------------------------------------------------------------------
# Step 3: Run simulation with xmsim
# ------------------------------------------------------------------------------
run:
	@echo "=========================================================================="
	@echo " [RUN] Running simulation with xmsim"
	@echo "=========================================================================="
	@mkdir -p $(LOG_DIR)
	cd $(SIM_DIR) && $(XMSIM) snap \
		+SEED=$(SEED) \
		+TEST_ITERS=$(TEST_ITERS) \
		+CYCLES=$(CYCLES) \
		$(COV_SIM_FLAGS) \
		2>&1 | tee ../$(LOG_DIR)/sim.log
	@echo ""
	@echo "[RUN] Done - see $(LOG_DIR)/sim.log"
	@echo "Waveform: $(SIM_DIR)/waves.shm"

# ------------------------------------------------------------------------------
# Complete sanity flow: compile + build + run
# ------------------------------------------------------------------------------
test: compile build run
	@echo ""
	@echo "=========================================================================="
	@echo " [TEST] Complete sanity flow finished"
	@echo "=========================================================================="

# ------------------------------------------------------------------------------
# Lab test: Run all test categories in sequence
# ------------------------------------------------------------------------------
lab_test:
	@echo "=========================================================================="
	@echo " [LAB_TEST] Running complete lab test suite"
	@echo "=========================================================================="
	@$(MAKE) compile
	@$(MAKE) build
	@mkdir -p $(LOG_DIR)
	@echo ""
	@echo "--- Running Sanity Tests ---"
	@cd $(SIM_DIR) && $(XMSIM) -64bit worklib.tb_top:snap +TEST_MODE=sanity -l ../$(LOG_DIR)/sanity.log
	@echo ""
	@echo "--- Running Advanced Tests ---"
	@cd $(SIM_DIR) && $(XMSIM) -64bit worklib.tb_top:snap +TEST_MODE=advanced -l ../$(LOG_DIR)/advanced.log
	@echo ""
	@echo "--- Running Benchmark Tests ---"
	@cd $(SIM_DIR) && $(XMSIM) -64bit worklib.tb_top:snap +TEST_MODE=benchmark -l ../$(LOG_DIR)/benchmark.log
	@echo ""
	@echo "--- Running Stress Tests ---"
	@cd $(SIM_DIR) && $(XMSIM) -64bit worklib.tb_top:snap +TEST_MODE=stress +CYCLES=$(CYCLES) -l ../$(LOG_DIR)/stress.log
	@echo ""
	@echo "=========================================================================="
	@echo " [LAB_TEST] All tests complete. Check logs in $(LOG_DIR)/"
	@echo "=========================================================================="

# ------------------------------------------------------------------------------
# Legacy sim target for compatibility
# ------------------------------------------------------------------------------
sim: test

# ------------------------------------------------------------------------------
# Open Simvision waveform viewer
# ------------------------------------------------------------------------------
wave:
	@echo "[WAVE] Opening Simvision..."
	@cd $(SIM_DIR) && simvision waves.shm &

# ------------------------------------------------------------------------------
# GUI mode with waveform setup
# ------------------------------------------------------------------------------
gui: compile
	@echo "[GUI] Running Xcelium in GUI mode..."
	@cd $(SIM_DIR) && xrun -gui -64bit \
		-access +rwc \
		-f flist \
		-input ../$(TB_DIR)/restore.tcl

# ==============================================================================
# COVERAGE TARGETS (Xcelium Code & Functional Coverage)
# ==============================================================================

# ------------------------------------------------------------------------------
# Generate coverage database (compile + elaborate + run with coverage enabled)
# ------------------------------------------------------------------------------
cov:
	@echo "=========================================================================="
	@echo " [COV] Running simulation with coverage collection"
	@echo " DUT scope: $(COV_DUT) | Output: $(COV_DIR)/"
	@echo "=========================================================================="
	@$(MAKE) compile
	@$(MAKE) build COV=1
	@echo "=========================================================================="
	@echo " [COV-RUN] Running simulation with coverage + report"
	@echo "=========================================================================="
	@mkdir -p $(LOG_DIR)
	cd $(SIM_DIR) && $(XMSIM) snap \
		+SEED=$(SEED) \
		+TEST_ITERS=$(TEST_ITERS) \
		+CYCLES=$(CYCLES) \
		-covworkdir ../$(COV_DIR) -covoverwrite -covtest $(COV_TEST) \
		-input ../$(SCRIPT_DIR)/cov_report.tcl \
		2>&1 | tee ../$(LOG_DIR)/cov.log
	@echo ""
	@echo "[COV] Coverage database: $(COV_DIR)/"
	@echo "[COV] Full log: $(LOG_DIR)/cov.log"
	@echo "[COV] Run 'make cov_gui' to browse in SimVision"

# ------------------------------------------------------------------------------
# Generate text coverage report from existing database
# ------------------------------------------------------------------------------
cov_report:
	@echo "=========================================================================="
	@echo " [COV_REPORT] Coverage Database Summary"
	@echo "=========================================================================="
	@if [ ! -d "$(COV_DIR)" ]; then \
		echo "ERROR: Coverage database $(COV_DIR)/ not found. Run 'make cov' first."; \
		exit 1; \
	fi
	@echo ""
	@echo "  Database location: $(COV_DIR)/"
	@echo "  DUT scope:         $(COV_DUT)"
	@echo ""
	@echo "  Files:"
	@find $(COV_DIR) -type f -exec ls -lh {} \; 2>/dev/null
	@echo ""
	@echo "  To view detailed coverage metrics, use one of:"
	@echo "    make cov_gui          - Open SimVision coverage browser"
	@echo "    imc -load $(COV_DIR)  - Open IMC (if installed)"
	@echo ""

# ------------------------------------------------------------------------------
# Open SimVision with coverage database
# ------------------------------------------------------------------------------
cov_gui:
	@echo "[COV_GUI] Opening SimVision with coverage data..."
	@if [ ! -d "$(COV_DIR)" ]; then \
		echo "ERROR: Coverage database $(COV_DIR)/ not found. Run 'make cov' first."; \
		exit 1; \
	fi
	@cd $(SIM_DIR) && simvision -covworkdir ../$(COV_DIR) &

# ------------------------------------------------------------------------------
# Lint check
# ------------------------------------------------------------------------------
lint: create_flist
	@echo "=========================================================================="
	@echo " [LINT] Running Xcelium lint checks"
	@echo "=========================================================================="
	@mkdir -p $(SIM_DIR) $(LOG_DIR)
	@cd $(SIM_DIR) && xmvlog -sv -64bit -f flist \
		-work worklib \
		2>&1 | tee ../$(LOG_DIR)/lint.log
	@echo "[LINT] Done - see $(LOG_DIR)/lint.log"

# ==============================================================================
# SYNTHESIS TARGETS (Genus)
# ==============================================================================

# ------------------------------------------------------------------------------
# Run Genus synthesis
# ------------------------------------------------------------------------------
syn:
	@echo "=========================================================================="
	@echo " [SYN] Running Genus Synthesis"
	@echo " Top Module: $(TOP_SYN)"
	@echo "=========================================================================="
	@mkdir -p $(SYN_DIR)
ifeq ($(GENUS_GUI_ENABLE),1)
	@cd $(SYN_DIR) && $(GENUS) -gui \
		-files ../$(SCRIPT_DIR)/genus_syn.tcl \
		-log genus.log \
		-overwrite
else
	@cd $(SYN_DIR) && $(GENUS) -batch \
		-files ../$(SCRIPT_DIR)/genus_syn.tcl \
		-log genus.log \
		-overwrite
endif
	@echo "[SYN] Done - see $(SYN_DIR)/genus.log"

# ------------------------------------------------------------------------------
# Restore Genus with synthesized design
# ------------------------------------------------------------------------------
restore_syn:
	@echo "=========================================================================="
	@echo " [RESTORE_SYN] Restoring Genus session"
	@echo "=========================================================================="
	@cd $(SYN_DIR) && $(GENUS) -gui \
		-files ../$(SCRIPT_DIR)/genus_restore.tcl \
		-log genus_restore.log

# ==============================================================================
# LEC TARGETS (Conformal)
# ==============================================================================

# ------------------------------------------------------------------------------
# Run Conformal LEC
# ------------------------------------------------------------------------------
lec:
	@echo "=========================================================================="
	@echo " [LEC] Running Conformal Logical Equivalence Check"
	@echo " Effort: $(LEC_EFFORT)"
	@echo "=========================================================================="
	@mkdir -p $(LEC_DIR)
ifeq ($(LEC_GUI_ENABLE),1)
	@cd $(LEC_DIR) && $(LEC) -gui \
		-dofile ../$(SCRIPT_DIR)/conformal_lec.tcl \
		-logfile lec.log
else
	@cd $(LEC_DIR) && $(LEC) -nogui \
		-dofile ../$(SCRIPT_DIR)/conformal_lec.tcl \
		-logfile lec.log
endif
	@echo "[LEC] Done - see $(LEC_DIR)/lec.log"

# ==============================================================================
# FULL FLOW
# ==============================================================================
full: test syn lec
	@echo "=========================================================================="
	@echo " [FULL] Complete flow finished: Simulation + Synthesis + LEC"
	@echo "=========================================================================="

# ==============================================================================
# FILE LIST GENERATION
# ==============================================================================
create_flist:
	@echo "[FLIST] Creating file list for Xcelium..."
	@mkdir -p $(SIM_DIR)
	@rm -f $(SIM_DIR)/flist
	@echo "# CGRA Project File List" > $(SIM_DIR)/flist
	@echo "# Generated: $$(date)" >> $(SIM_DIR)/flist
	@echo "" >> $(SIM_DIR)/flist
	@echo "# Compilation options" >> $(SIM_DIR)/flist
	@echo "-sv" >> $(SIM_DIR)/flist
	@echo "" >> $(SIM_DIR)/flist
	@echo "" >> $(SIM_DIR)/flist
	@echo "# Include directories" >> $(SIM_DIR)/flist
	@echo "-incdir ../$(SRC_DIR)" >> $(SIM_DIR)/flist
	@echo "-incdir ../$(BSG_DIR)" >> $(SIM_DIR)/flist
	@echo "-incdir ../$(TB_DIR)" >> $(SIM_DIR)/flist
	@echo "-incdir ../$(TB_DIR)/include" >> $(SIM_DIR)/flist
	@echo "" >> $(SIM_DIR)/flist
	@echo "# BSG Memory Library" >> $(SIM_DIR)/flist
	@for f in $(BSG_SRCS); do echo ../$$f >> $(SIM_DIR)/flist; done
	@echo "" >> $(SIM_DIR)/flist
	@echo "# RTL Source Files" >> $(SIM_DIR)/flist
	@for f in $(RTL_SRCS); do echo ../$$f >> $(SIM_DIR)/flist; done
	@echo "" >> $(SIM_DIR)/flist
	@echo "# Testbench Files" >> $(SIM_DIR)/flist
	@for f in $(TB_SRCS); do echo ../$$f >> $(SIM_DIR)/flist; done
	@echo "[FLIST] Done - $(SIM_DIR)/flist"

# ==============================================================================
# CLEAN TARGETS
# ==============================================================================
clean:
	@echo "[CLEAN] Removing simulation & coverage artifacts..."
	@echo "  - Cleaning $(SIM_DIR)/"
	@rm -rf $(SIM_DIR)/worklib $(SIM_DIR)/xcelium.d $(SIM_DIR)/INCA_libs
	@rm -rf $(SIM_DIR)/*.shm $(SIM_DIR)/*.key $(SIM_DIR)/*.diag $(SIM_DIR)/*.history
	@rm -rf $(SIM_DIR)/*.err $(SIM_DIR)/*.dsn $(SIM_DIR)/*.trn
	@rm -rf $(SIM_DIR)/flist
	@echo "  - Cleaning $(COV_DIR)/"
	@rm -rf $(COV_DIR)
	@echo "  - Cleaning simulation logs"
	@rm -f $(LOG_DIR)/compile.log $(LOG_DIR)/elaborate.log $(LOG_DIR)/sim.log
	@rm -f $(LOG_DIR)/cov.log $(LOG_DIR)/cov_report.log $(LOG_DIR)/lint.log
	@echo "  - Cleaning root directory artifacts"
	@rm -rf xcelium.d INCA_libs xrun.* .simvision
	@rm -f *.log *.key *.history *.diag *.err
	@echo "[CLEAN] Done"

clean-all: clean
	@echo "[CLEAN-ALL] Removing all generated directories..."
	@rm -rf $(SIM_DIR)/* $(SYN_DIR)/* $(LEC_DIR)/*
	@rm -rf obj_dir
	@rm -f $(LOG_DIR)/*.log
	@echo "[CLEAN-ALL] Done"

# ==============================================================================
# TOOL CHECK
# ==============================================================================
check_tools:
	@echo "Checking Cadence tools..."
	@which xmvlog && xmvlog -version || echo "xmvlog not found"
	@which xmelab && xmelab -version || echo "xmelab not found"
	@which xmsim && xmsim -version || echo "xmsim not found"
	@which genus && genus -version || echo "Genus not found"
	@which lec && lec -version || echo "Conformal not found"
