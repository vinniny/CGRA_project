#!/bin/bash
# ==============================================================================
# CGRA Simulation Script
# ==============================================================================
# Usage: ./run_sim.sh <testbench_name>
# Example: ./run_sim.sh tb_cgra_pe

if [ $# -eq 0 ]; then
    echo "Usage: $0 <testbench_name>"
    echo "Available testbenches:"
    echo "  tb_cgra_pe"
    echo "  tb_cgra_router"
    echo "  tb_cgra_config_loader"
    echo "  tb_cgra_top"
    exit 1
fi

TB_NAME=$1
SRC_DIR="../00_src"
BENCH_DIR="."
SIM_DIR="../03_sim"

# Create simulation directory if it doesn't exist
mkdir -p $SIM_DIR

echo "========================================"
echo "  CGRA Simulation Script"
echo "  Testbench: $TB_NAME"
echo "========================================"

# Compile source files
echo "[1/3] Compiling source files..."
iverilog -g2012 -o $SIM_DIR/${TB_NAME}.vvp \
    $SRC_DIR/cgra_pe.sv \
    $SRC_DIR/cgra_router.sv \
    $SRC_DIR/cgra_array_4x4.sv \
    $SRC_DIR/cgra_config_loader.sv \
    $SRC_DIR/cgra_tile_memory.sv \
    $SRC_DIR/cgra_dma_engine.sv \
    $SRC_DIR/cgra_axi_csr.sv \
    $SRC_DIR/cgra_top.sv \
    $BENCH_DIR/${TB_NAME}.sv

if [ $? -ne 0 ]; then
    echo "ERROR: Compilation failed!"
    exit 1
fi

echo "[2/3] Running simulation..."
cd $SIM_DIR
vvp ${TB_NAME}.vvp

if [ $? -ne 0 ]; then
    echo "ERROR: Simulation failed!"
    exit 1
fi

echo "[3/3] Simulation completed successfully!"

# Check if VCD file was generated
if [ -f "cgra_top.vcd" ]; then
    echo "Waveform file generated: cgra_top.vcd"
    echo "View with: gtkwave cgra_top.vcd"
fi

echo "========================================"
echo "  Simulation Complete"
echo "========================================"
