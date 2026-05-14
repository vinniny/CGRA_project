# Makefile for the Chapter 5 LaTeX build.
# Usage:
#   make          — build main.pdf (standalone Chapter 5 PDF)
#   make watch    — continuous build (latexmk -pvc); needs a PDF viewer
#   make clean    — drop intermediate files
#   make distclean — also drop main.pdf

LATEX     := pdflatex
LATEXMK   := latexmk
DOC       := main
SOURCES   := main.tex preamble.tex chapter5.tex

# Project-relative paths used by sample_waveforms.
PROJECT_ROOT  := $(abspath ../..)
SCEN_DIR      := $(PROJECT_ROOT)/01_bench/scenarios
SCEN_SCRIPT   := $(SCEN_DIR)/run_scenarios.sh
SCEN_TB       := $(SCEN_DIR)/tb_wave_scenarios.sv
SHM_OUT_DIR   := $(PROJECT_ROOT)/03_sim/scenarios
WAVE_SHMS     := $(SHM_OUT_DIR)/wave_dma.shm \
                 $(SHM_OUT_DIR)/wave_cumac.shm \
                 $(SHM_OUT_DIR)/wave_fcgroup.shm

.PHONY: all watch clean distclean sample_waveforms wave_clean

all: $(DOC).pdf

# --- LaTeX build ---------------------------------------------------
$(DOC).pdf: $(SOURCES)
	$(LATEXMK) -pdf -interaction=nonstopmode -halt-on-error $(DOC).tex

watch: $(SOURCES)
	$(LATEXMK) -pdf -pvc -interaction=nonstopmode $(DOC).tex

# --- Sample-waveform generation -----------------------------------
# `make sample_waveforms` invokes the SystemVerilog scenario testbench
# in 01_bench/scenarios/ via Cadence Xcelium, producing three SHM
# databases in 03_sim/scenarios/ that the user opens in SimVision to
# capture the screenshots referenced from Chapter 5 §5.1.5.
#
# Prerequisite: the Cadence Xcelium environment must be sourced so
# that xmvlog / xmelab / xmsim are on PATH. The driver script bails
# with a clear error if they are missing.
sample_waveforms: $(WAVE_SHMS)

$(WAVE_SHMS) &: $(SCEN_TB) $(SCEN_SCRIPT)
	@echo "[sample_waveforms] Running Xcelium scenario testbench..."
	@bash $(SCEN_SCRIPT)
	@echo "[sample_waveforms] SHM databases ready under $(SHM_OUT_DIR)/"
	@echo "  View, e.g.: cd $(SHM_OUT_DIR) && \\"
	@echo "              simvision wave_dma.shm/wave_dma.trn \\"
	@echo "                       -input $(SCEN_DIR)/wave_restore.tcl"

wave_clean:
	rm -rf $(WAVE_SHMS) $(SHM_OUT_DIR)

# --- Cleanup ------------------------------------------------------
clean:
	$(LATEXMK) -c
	rm -f *.aux *.log *.toc *.out *.fls *.fdb_latexmk *.synctex.gz

distclean: clean
	rm -f $(DOC).pdf
