# ==============================================================================
# CGRA Project Makefile - Cadence Xcelium / Genus / Conformal Flow
# ==============================================================================
# Version: 2.6.0 | March 2026
# ==============================================================================
SHELL := /bin/bash

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

# X-Propagation (set XPROP=1 to enable ternary X-propagation during elaboration)
XPROP            ?= 0
XPROP_ELAB_FLAGS :=
ifeq ($(XPROP),1)
XPROP_ELAB_FLAGS := -xprop c
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
	$(SRC_DIR)/cgra_tile.sv \
	$(SRC_DIR)/cgra_config_broadcaster.sv \
	$(SRC_DIR)/cgra_array.sv \
	$(SRC_DIR)/cgra_tile_memory.sv \
	$(SRC_DIR)/cgra_apb_csr.sv \
	$(SRC_DIR)/cgra_control_unit.sv \
	$(SRC_DIR)/cgra_dma_engine.sv \
	$(SRC_DIR)/cgra_dma_chain_ctrl.sv \
	$(SRC_DIR)/cgra_dma_subsystem.sv \
	$(SRC_DIR)/cgra_result_fifo.sv \
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
# FPGA Deployment (Xilinx XSDB / Zynq-7000)
# ==============================================================================
XILINX_VITIS    ?= /tools/Xilinx/2025.1/Vitis
XILINX_SETTINGS := $(XILINX_VITIS)/settings64.sh
XSDB            := $(XILINX_VITIS)/bin/xsdb
VIVADO          ?= /tools/Xilinx/2025.1/Vivado/bin/vivado
HW_SERVER_BIN   := $(XILINX_VITIS)/bin/hw_server
BIT             ?= bitstreams/cgra_top.bit
ELF             ?=
REG             ?=
VAL             ?=
HW_HOST         ?= localhost
HW_SERVER_PORT  ?= 3121
PS_INIT         ?= 1

# Vivado project on Windows (accessible via WSL2 /mnt/)
VIVADO_PROJECT  ?= /mnt/c/Users/thanh/Desktop/FPGA_CGRA
VIVADO_IMPL     := $(VIVADO_PROJECT)/cgra_ip.runs/impl_1
VIVADO_PS7_DIR  := $(VIVADO_PROJECT)/cgra_ip.gen/sources_1/bd/design_1/ip/design_1_processing_system7_0_0
VIVADO_HWH      := $(VIVADO_PROJECT)/cgra_ip.gen/sources_1/bd/design_1/hw_handoff/design_1.hwh

# ==============================================================================
# Phony Targets
# ==============================================================================
.PHONY: all help compile build run sim test lab_test wave clean clean-all \
        syn restore_syn lec full create_flist lint check_tools gui \
        cov cov_gui cov_report hal xprop vivado_lint lint_static lint_all \
        hw_server_start hw_server_stop hw_server_check \
        program fpga_status run_elf reg_read reg_write reg_dump \
        pull_bit pull_ps7 pull_hwh pull_all deploy vivado_reports \
        baremetal run_baremetal demo run_demo

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
	@echo "   make cov_report   - Generate IMC text report (block/expr/toggle/func)"
	@echo "   make cov_gui      - Open SimVision with coverage database"
	@echo ""
	@echo " Static Analysis & X-Prop Targets:"
	@echo "   make lint         - Xcelium compile-time lint (fast)"
	@echo "   make hal          - Genus check_design: synthesizability, latches (VM)"
	@echo "   make vivado_lint  - Vivado synth_design -rtl: latches, widths, CDC"
	@echo "   make xprop        - Simulate with X-Propagation (ternary mode)"
	@echo "   make lint_static  - lint + hal + vivado_lint (no simulation)"
	@echo "   make lint_all     - lint_static + xprop (full suite)"
	@echo "   XPROP=1           - Enable X-prop on existing build/run targets"
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
	@echo "   XPROP=1                 - Enable X-propagation for build target"
	@echo "   COV_TEST=name           - Coverage test name (default: full_sim)"
	@echo "   TOP_SYN=module          - Top module for synthesis (default cgra_top)"
	@echo "   GENUS_GUI_ENABLE=1      - Enable Genus GUI"
	@echo "   LEC_GUI_ENABLE=1        - Enable Conformal GUI"
	@echo "   LEC_EFFORT=Auto|Medium  - LEC comparison effort"
	@echo ""
	@echo " FPGA Deployment Targets (Xilinx XSDB / Zynq-7000):"
	@echo "   make program BIT=<file.bit>         - Program PL + init PS"
	@echo "   make program BIT=<file> PS_INIT=0   - Program PL only (no PS init)"
	@echo "   make fpga_status                    - Read FPGA state + CGRA registers"
	@echo "   make run_elf ELF=<file>             - Load & run bare-metal ELF"
	@echo "   make run_elf ELF=<f> BIT=<b>        - Program PL + run ELF"
	@echo "   make reg_read REG=<name>            - Read single CGRA register"
	@echo "   make reg_write REG=<name> VAL=<val> - Write CGRA register"
	@echo "   make reg_dump                       - Dump all 28 CGRA registers"
	@echo "   make hw_server_start                - Start Xilinx hw_server"
	@echo "   make hw_server_stop                 - Stop hw_server"
	@echo ""
	@echo " Vivado Integration Targets:"
	@echo "   make pull_bit             - Pull bitstream from Vivado project"
	@echo "   make pull_ps7             - Pull ps7_init.tcl from Vivado"
	@echo "   make pull_hwh             - Pull hardware handoff (.hwh)"
	@echo "   make pull_all             - Pull all Vivado artifacts"
	@echo "   make deploy               - Pull bitstream + program FPGA"
	@echo "   make vivado_reports       - Show timing/utilization/DRC reports"
	@echo ""
	@echo " FPGA Options:"
	@echo "   BIT=path/to/file.bit     - Bitstream file (default: bitstreams/cgra_top.bit)"
	@echo "   ELF=path/to/file.elf     - ELF binary for ARM"
	@echo "   PS_INIT=0|1              - PS initialization (default: 1)"
	@echo "   HW_HOST=<ip>             - Remote hw_server host (default: localhost)"
	@echo "   VIVADO_PROJECT=<path>    - Vivado project path (default: Windows Desktop)"
	@echo ""
	@echo " Bare-Metal Targets:"
	@echo "   make baremetal            - Build bare-metal CGRA test ELF"
	@echo "   make run_baremetal        - Build + program FPGA + load ELF + UART monitor"
	@echo "   make demo                 - Build ASCII Image Accelerator demo ELF (Vitis BSP)"
	@echo "   make run_demo             - Build + program FPGA + load demo + UART monitor"
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
		$(XPROP_ELAB_FLAGS) \
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
# Generate coverage summary from simulation log
# (IMC/xcrg not available in this Xcelium 20.09 installation;
#  code coverage browsing requires SimVision GUI via 'make cov_gui')
# ------------------------------------------------------------------------------
cov_report:
	@echo "=========================================================================="
	@echo " [COV_REPORT] Extracting coverage summary from simulation log"
	@echo "=========================================================================="
	@if [ ! -f "$(LOG_DIR)/cov.log" ]; then \
		echo "ERROR: $(LOG_DIR)/cov.log not found. Run 'make cov' first."; \
		exit 1; \
	fi
	@{ echo "=== CGRA Coverage Report (extracted from cov.log) ==="; \
	   echo "Date: $$(date)"; \
	   echo ""; \
	   echo "--- Test Results ---"; \
	   grep -A 6 'TEST RESULTS' $(LOG_DIR)/cov.log | tail -5; \
	   echo ""; \
	   echo "--- AXI Protocol Statistics ---"; \
	   grep -A 15 'AXI PROTOCOL STATISTICS' $(LOG_DIR)/cov.log | tail -13; \
	   echo ""; \
	   echo "--- Functional Coverage ---"; \
	   grep -A 10 'FUNCTIONAL COVERAGE' $(LOG_DIR)/cov.log | tail -8; \
	   echo ""; \
	   echo "--- Coverage Counters ---"; \
	   grep -A 10 'COVERAGE SUMMARY' $(LOG_DIR)/cov.log | tail -8; \
	   echo ""; \
	   echo "--- Coverage Database ---"; \
	   ls -lh $(COV_DIR)/scope/$(COV_TEST)/*.ucd 2>/dev/null || echo "(no .ucd files found)"; \
	   echo ""; \
	   echo "NOTE: For block/expression/toggle breakdown, use 'make cov_gui' (SimVision)."; \
	 } | tee $(LOG_DIR)/cov_report.txt
	@echo ""
	@echo "[COV_REPORT] Report: $(LOG_DIR)/cov_report.txt"
	@echo "[COV_REPORT] For detailed code coverage: make cov_gui"

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

# ------------------------------------------------------------------------------
# HAL: synthesizability + CDC + LINT static analysis
# Uses Genus check_design (not standalone HAL) — avoids Xcelium 20.09
# snapshot-path mismatch that causes NOSNAP on all xrun -hal invocations.
# Genus reads SV directly without a simulation snapshot.
# ------------------------------------------------------------------------------
hal:
	@echo "=========================================================================="
	@echo " [HAL] Genus RTL synthesizability check (check_design -unresolved)"
	@echo " Checks: inferred latches, multi-driven nets, unsynthesizable constructs"
	@echo "=========================================================================="
	@mkdir -p $(SYN_DIR)/reports $(LOG_DIR)
	cd $(SYN_DIR) && $(GENUS) -batch \
		-files ../$(SCRIPT_DIR)/genus_check.tcl \
		-log ../$(LOG_DIR)/hal.log \
		-overwrite
	@echo "[HAL] Done - see $(LOG_DIR)/hal.log"
	@echo "[HAL] check_design report: $(SYN_DIR)/reports/check_design.rpt"
	@echo "[HAL] Error/Warning summary:"
	@grep -iE "^(error|warning)" $(SYN_DIR)/reports/check_design.rpt \
		| sort | uniq -c | sort -rn | head -30 || true

# ------------------------------------------------------------------------------
# Vivado RTL lint: synth_design -rtl elaboration (no P&R)
# Catches: inferred latches, multi-driven nets, port-width mismatches,
# unresolved references, unsynthesizable constructs.
# ------------------------------------------------------------------------------
vivado_lint:
	@echo "=========================================================================="
	@echo " [VIVADO LINT] RTL elaboration lint (synth_design -rtl)"
	@echo "=========================================================================="
	@mkdir -p $(LOG_DIR)
	cd $(CURDIR) && $(VIVADO) -mode batch \
		-source $(SCRIPT_DIR)/vivado_lint.tcl \
		-log $(LOG_DIR)/vivado_lint.log \
		-nojournal
	@echo "[VIVADO LINT] Done"
	@echo "  Log      : $(LOG_DIR)/vivado_lint.log"
	@echo "  DRC      : $(LOG_DIR)/vivado_lint_drc.rpt"
	@echo "  Method   : $(LOG_DIR)/vivado_lint_methodology.rpt"
	@echo "--- Error/Warning summary (Synth 8-7129 suppressed — by-design) ---"
	@grep -E "^(ERROR|WARNING|CRITICAL)" $(LOG_DIR)/vivado_lint.log \
		| grep -v "Synth 8-7129" \
		| sort | uniq -c | sort -rn | head -40 || true

# ------------------------------------------------------------------------------
# Combined lint targets
# lint_static : fast static checks — no simulation required (lint + hal + vivado_lint)
# lint_all    : full suite including X-propagation simulation
# Note: hal requires Genus (Cadence VM); vivado_lint requires Vivado (local)
# ------------------------------------------------------------------------------
lint_static: lint hal vivado_lint
	@echo "=========================================================================="
	@echo " [LINT_STATIC] All static lint checks complete"
	@echo "   Xcelium compile  : $(LOG_DIR)/lint.log"
	@echo "   Genus HAL        : $(LOG_DIR)/hal.log  +  $(SYN_DIR)/reports/check_design.rpt"
	@echo "   Vivado RTL       : $(LOG_DIR)/vivado_lint.log  +  $(LOG_DIR)/vivado_lint_drc.rpt"
	@echo "=========================================================================="

lint_all: lint_static xprop
	@echo "=========================================================================="
	@echo " [LINT_ALL] Full lint suite complete (static + X-propagation)"
	@echo "   X-prop sim       : $(LOG_DIR)/xprop.log"
	@echo "=========================================================================="

# ------------------------------------------------------------------------------
# X-Propagation: elaborate with -xprop c and run full regression
# Uses a separate snapshot (snap_xprop) so normal make run is unaffected
# ------------------------------------------------------------------------------
xprop: compile
	@echo "=========================================================================="
	@echo " [XPROP] Elaborating with X-Propagation (ternary mode) + running sim"
	@echo "=========================================================================="
	@mkdir -p $(LOG_DIR)
	cd $(SIM_DIR) && $(XMELAB) \
		-timescale 1ns/1ps \
		-access +rwc \
		-xprop c \
		-snapshot snap_xprop \
		worklib.tb_top \
		2>&1 | tee ../$(LOG_DIR)/xprop_elab.log
	cd $(SIM_DIR) && $(XMSIM) snap_xprop \
		+SEED=$(SEED) \
		+TEST_ITERS=$(TEST_ITERS) \
		+CYCLES=$(CYCLES) \
		2>&1 | tee ../$(LOG_DIR)/xprop.log
	@echo "[XPROP] Done - see $(LOG_DIR)/xprop.log"
	@grep -E "FAIL|ERROR|X-prop" $(LOG_DIR)/xprop.log | head -20 || true

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
# FPGA DEPLOYMENT TARGETS (Xilinx XSDB / Zynq-7000)
# ==============================================================================

# ------------------------------------------------------------------------------
# hw_server management
# ------------------------------------------------------------------------------
hw_server_start:
	@if pgrep -x hw_server > /dev/null 2>&1; then \
		echo "[HW_SERVER] Already running (PID $$(pgrep -x hw_server))"; \
	else \
		echo "[HW_SERVER] Starting on port $(HW_SERVER_PORT)..."; \
		source $(XILINX_SETTINGS) && \
		$(HW_SERVER_BIN) -d -s tcp::$(HW_SERVER_PORT) > $(LOG_DIR)/hw_server.log 2>&1; \
		sleep 2; \
		if pgrep -x hw_server > /dev/null 2>&1; then \
			echo "[HW_SERVER] Running (PID $$(pgrep -x hw_server))"; \
		else \
			echo "[HW_SERVER] FAILED — check $(LOG_DIR)/hw_server.log"; \
			cat $(LOG_DIR)/hw_server.log 2>/dev/null; \
			exit 1; \
		fi; \
	fi

hw_server_stop:
	@if pgrep -x hw_server > /dev/null 2>&1; then \
		echo "[HW_SERVER] Stopping (PID $$(pgrep -x hw_server))..."; \
		pkill -x hw_server; \
		echo "[HW_SERVER] Stopped"; \
	else \
		echo "[HW_SERVER] Not running"; \
	fi

hw_server_check:
	@if pgrep -x hw_server > /dev/null 2>&1; then \
		echo "[HW_SERVER] Running (PID $$(pgrep -x hw_server))"; \
	else \
		echo "[HW_SERVER] Not running"; \
	fi

# ------------------------------------------------------------------------------
# Program FPGA bitstream
# Usage: make program BIT=bitstreams/cgra_top.bit
#        make program BIT=bitstreams/cgra_top.bit PS_INIT=0
#        HW_HOST=192.168.1.100 make program BIT=bitstreams/cgra_top.bit
# ------------------------------------------------------------------------------
program: hw_server_start
	@if [ -z "$(BIT)" ]; then \
		echo "ERROR: No bitstream specified. Usage: make program BIT=path/to/file.bit"; \
		exit 1; \
	fi
	@if [ ! -f "$(BIT)" ]; then \
		echo "ERROR: Bitstream not found: $(BIT)"; \
		exit 1; \
	fi
	@echo "=========================================================================="
	@echo " [PROGRAM] Programming FPGA: $(BIT)"
	@echo "=========================================================================="
	@mkdir -p $(LOG_DIR)
	source $(XILINX_SETTINGS) && \
	XSDB_HW_HOST=$(HW_HOST) XSDB_PS_INIT=$(PS_INIT) \
	$(XSDB) $(SCRIPT_DIR)/xsdb_program.tcl $(BIT) \
		$(if $(filter 1,$(PS_INIT)),--ps-init,) \
		--hw-host $(HW_HOST) \
		2>&1 | tee $(LOG_DIR)/program.log
	@echo "[PROGRAM] Log: $(LOG_DIR)/program.log"

# ------------------------------------------------------------------------------
# Read FPGA status + dump CGRA registers
# ------------------------------------------------------------------------------
fpga_status: hw_server_start
	@echo "=========================================================================="
	@echo " [FPGA_STATUS] Reading FPGA state + CGRA registers"
	@echo "=========================================================================="
	@mkdir -p $(LOG_DIR)
	source $(XILINX_SETTINGS) && \
	$(XSDB) $(SCRIPT_DIR)/xsdb_status.tcl \
		--hw-host $(HW_HOST) \
		2>&1 | tee $(LOG_DIR)/fpga_status.log

# ------------------------------------------------------------------------------
# Load and run bare-metal ELF on ARM Cortex-A9
# Usage: make run_elf ELF=07_sw/build/lpr_demo
#        make run_elf ELF=07_sw/build/lpr_demo BIT=bitstreams/cgra_top.bit
# ------------------------------------------------------------------------------
run_elf: hw_server_start
	@if [ -z "$(ELF)" ]; then \
		echo "ERROR: No ELF specified. Usage: make run_elf ELF=path/to/file"; \
		exit 1; \
	fi
	@if [ ! -f "$(ELF)" ]; then \
		echo "ERROR: ELF not found: $(ELF)"; \
		exit 1; \
	fi
	@echo "=========================================================================="
	@echo " [RUN_ELF] Loading: $(ELF)"
	@echo "=========================================================================="
	@mkdir -p $(LOG_DIR)
	source $(XILINX_SETTINGS) && \
	$(XSDB) $(SCRIPT_DIR)/xsdb_run_elf.tcl $(ELF) \
		$(if $(BIT),--bit $(BIT),) \
		--hw-host $(HW_HOST) \
		2>&1 | tee $(LOG_DIR)/run_elf.log

# ------------------------------------------------------------------------------
# Register access helpers
# Usage: make reg_read REG=DMA_STATUS
#        make reg_write REG=DMA_SRC VAL=0x10000000
#        make reg_dump
# ------------------------------------------------------------------------------
reg_read: hw_server_start
	@if [ -z "$(REG)" ]; then \
		echo "ERROR: No register specified. Usage: make reg_read REG=DMA_STATUS"; \
		exit 1; \
	fi
	source $(XILINX_SETTINGS) && \
	$(XSDB) $(SCRIPT_DIR)/xsdb_regmap.tcl read $(REG) --hw-host $(HW_HOST)

reg_write: hw_server_start
	@if [ -z "$(REG)" ] || [ -z "$(VAL)" ]; then \
		echo "ERROR: Usage: make reg_write REG=DMA_SRC VAL=0x10000000"; \
		exit 1; \
	fi
	source $(XILINX_SETTINGS) && \
	$(XSDB) $(SCRIPT_DIR)/xsdb_regmap.tcl write $(REG) $(VAL) --hw-host $(HW_HOST)

reg_dump: hw_server_start
	@mkdir -p $(LOG_DIR)
	source $(XILINX_SETTINGS) && \
	$(XSDB) $(SCRIPT_DIR)/xsdb_regmap.tcl dump --hw-host $(HW_HOST) \
		2>&1 | tee $(LOG_DIR)/reg_dump.log

# ==============================================================================
# VIVADO INTEGRATION TARGETS (pull from Windows project via WSL2 /mnt/)
# ==============================================================================

# ------------------------------------------------------------------------------
# Pull bitstream from Vivado impl_1 to bitstreams/
# ------------------------------------------------------------------------------
pull_bit:
	@if [ ! -f "$(VIVADO_IMPL)/design_1_wrapper.bit" ]; then \
		echo "ERROR: No bitstream at $(VIVADO_IMPL)/design_1_wrapper.bit"; \
		echo "  Run 'Generate Bitstream' in Vivado first."; \
		exit 1; \
	fi
	@mkdir -p bitstreams
	@cp "$(VIVADO_IMPL)/design_1_wrapper.bit" bitstreams/cgra_top.bit
	@echo "[PULL_BIT] Copied to bitstreams/cgra_top.bit"
	@ls -lh bitstreams/cgra_top.bit

# ------------------------------------------------------------------------------
# Pull ps7_init.tcl from Vivado generated IP
# ------------------------------------------------------------------------------
pull_ps7:
	@if [ ! -f "$(VIVADO_PS7_DIR)/ps7_init.tcl" ]; then \
		echo "ERROR: ps7_init.tcl not found at $(VIVADO_PS7_DIR)/"; \
		exit 1; \
	fi
	@cp "$(VIVADO_PS7_DIR)/ps7_init.tcl" $(SCRIPT_DIR)/ps7_init.tcl
	@echo "[PULL_PS7] Updated $(SCRIPT_DIR)/ps7_init.tcl"

# ------------------------------------------------------------------------------
# Pull hardware handoff (.hwh) for Pynq/SW integration
# ------------------------------------------------------------------------------
pull_hwh:
	@if [ ! -f "$(VIVADO_HWH)" ]; then \
		echo "ERROR: HWH not found at $(VIVADO_HWH)"; \
		exit 1; \
	fi
	@mkdir -p bitstreams
	@cp "$(VIVADO_HWH)" bitstreams/design_1.hwh
	@echo "[PULL_HWH] Copied to bitstreams/design_1.hwh"

# ------------------------------------------------------------------------------
# Pull all Vivado artifacts
# ------------------------------------------------------------------------------
pull_all: pull_bit pull_ps7 pull_hwh
	@echo "[PULL_ALL] All Vivado artifacts synced."

# ==============================================================================
# BARE-METAL TARGETS
# ==============================================================================
BAREMETAL_DIR := 07_sw/baremetal
UART_PORT     ?= /dev/ttyUSB2
UART_BAUD     ?= 115200

baremetal:
	@echo "=========================================================================="
	@echo " [BAREMETAL] Building CGRA test ELF"
	@echo "=========================================================================="
	$(MAKE) -C $(BAREMETAL_DIR) all

run_baremetal: baremetal program
	@echo "=========================================================================="
	@echo " [RUN_BAREMETAL] Starting UART monitor on $(UART_PORT) @ $(UART_BAUD)"
	@echo "=========================================================================="
	@mkdir -p $(LOG_DIR)
	@python3 scripts/uart_monitor.py $(UART_PORT) $(UART_BAUD) \
		2>&1 | tee $(LOG_DIR)/uart.log &
	@sleep 1
	source $(XILINX_SETTINGS) && \
	$(XSDB) $(SCRIPT_DIR)/xsdb_run_elf.tcl $(BAREMETAL_DIR)/cgra_test.elf \
		--hw-host $(HW_HOST) \
		2>&1 | tee $(LOG_DIR)/run_elf.log
	@echo "[RUN_BAREMETAL] ELF running. UART log: $(LOG_DIR)/uart.log"

# ------------------------------------------------------------------------------
# ASCII Image Accelerator demo (Vitis BSP, drops cleanly into Vitis Workbench)
# ------------------------------------------------------------------------------
demo:
	@echo "=========================================================================="
	@echo " [DEMO] Building ASCII Image Accelerator ELF (Vitis BSP)"
	@echo "=========================================================================="
	$(MAKE) -C $(BAREMETAL_DIR) demo

run_demo: demo program
	@echo "=========================================================================="
	@echo " [RUN_DEMO] Starting UART monitor on $(UART_PORT) @ $(UART_BAUD)"
	@echo "=========================================================================="
	@mkdir -p $(LOG_DIR)
	@python3 scripts/uart_monitor.py $(UART_PORT) $(UART_BAUD) \
		2>&1 | tee $(LOG_DIR)/demo_uart.log &
	@sleep 1
	source $(XILINX_SETTINGS) && \
	$(XSDB) $(SCRIPT_DIR)/xsdb_run_elf.tcl $(BAREMETAL_DIR)/demo_ascii.elf \
		--hw-host $(HW_HOST) \
		2>&1 | tee $(LOG_DIR)/demo_run_elf.log
	@echo "[RUN_DEMO] ELF running. UART log: $(LOG_DIR)/demo_uart.log"

# ------------------------------------------------------------------------------
# One-command deploy: pull bitstream + program FPGA
# ------------------------------------------------------------------------------
deploy: pull_bit program
	@echo "[DEPLOY] Complete."

# ------------------------------------------------------------------------------
# Show key Vivado implementation reports
# ------------------------------------------------------------------------------
vivado_reports:
	@echo "=========================================================================="
	@echo " Vivado Implementation Reports: $(VIVADO_IMPL)"
	@echo "=========================================================================="
	@echo ""
	@echo "=== Timing Summary ==="
	@cat "$(VIVADO_IMPL)/design_1_wrapper_timing_summary_routed.rpt" 2>/dev/null | head -80 || echo "  (not found)"
	@echo ""
	@echo "=== Utilization ==="
	@cat "$(VIVADO_IMPL)/design_1_wrapper_utilization_placed.rpt" 2>/dev/null | head -80 || echo "  (not found)"
	@echo ""
	@echo "=== DRC ==="
	@cat "$(VIVADO_IMPL)/design_1_wrapper_drc_routed.rpt" 2>/dev/null | head -40 || echo "  (not found)"

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
	@rm -f $(LOG_DIR)/cov.log $(LOG_DIR)/cov_report.log $(LOG_DIR)/cov_report.txt
	@rm -f $(LOG_DIR)/lint.log $(LOG_DIR)/hal.log $(LOG_DIR)/hal_compile.log
	@rm -f $(LOG_DIR)/xprop.log $(LOG_DIR)/xprop_elab.log
	@rm -f $(LOG_DIR)/program.log $(LOG_DIR)/fpga_status.log $(LOG_DIR)/hw_server.log
	@rm -f $(LOG_DIR)/run_elf.log $(LOG_DIR)/reg_dump.log
	@rm -rf $(SIM_DIR)/hal_run $(SIM_DIR)/hal_cds.lib $(SIM_DIR)/hal.f
	@rm -rf $(SIM_DIR)/hal_work $(SIM_DIR)/hal.log $(SIM_DIR)/xp_elab.log
	@rm -rf $(SIM_DIR)/cov_work
	@rm -f $(SIM_DIR)/xmvlog.log $(SIM_DIR)/xmelab.log $(SIM_DIR)/xmsim.log
	@rm -rf $(SIM_DIR)/snap_xprop
	@echo "  - Cleaning Genus HAL artifacts"
	@rm -f $(SYN_DIR)/genus.log $(SYN_DIR)/genus.cmd
	@rm -rf $(SYN_DIR)/fv $(SYN_DIR)/reports
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
