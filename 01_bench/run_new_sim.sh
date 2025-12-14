#!/bin/bash

# ==============================================================================
# Simulation Script for New CGRA Architecture
# ==============================================================================

echo "========================================"
echo "CGRA Top-Level Integration Simulation"
echo "========================================"

# Clean previous build
rm -f tb_cgra_top_new
rm -f tb_cgra_top_new.vcd
rm -f *.o

# Compile with Icarus Verilog
echo ""
echo "Compiling design files..."

iverilog -g2012 -o tb_cgra_top_new \
    ../00_src/cgra_pe.sv \
    ../00_src/cgra_router.sv \
    ../00_src/cgra_array_4x4.sv \
    ../00_src/cgra_config_loader.sv \
    ../00_src/cgra_axi_csr.sv \
    ../00_src/cgra_control_unit.sv \
    ../00_src/cgra_tile_memory.sv \
    ../00_src/cgra_dma_engine.sv \
    ../00_src/cgra_top_new.sv \
    tb_cgra_top_new.sv

if [ $? -ne 0 ]; then
    echo ""
    echo "[ERROR] Compilation failed!"
    exit 1
fi

echo "[OK] Compilation successful"

# Run simulation
echo ""
echo "Running simulation..."
echo "========================================"

vvp tb_cgra_top_new

if [ $? -ne 0 ]; then
    echo ""
    echo "[ERROR] Simulation failed!"
    exit 1
fi

echo ""
echo "========================================"
echo "[OK] Simulation completed"

# Check if VCD was generated
if [ -f tb_cgra_top_new.vcd ]; then
    echo "[OK] Waveform file generated: tb_cgra_top_new.vcd"
    echo ""
    echo "To view waveforms, run:"
    echo "  gtkwave tb_cgra_top_new.vcd"
else
    echo "[WARNING] No waveform file generated"
fi

echo ""
echo "========================================"
