#!/bin/bash
# End-to-End ALPR C Implementation Build and Test Workflow
# Run this script to build the C ALPR and validate against Python baseline
# 
# Prerequisites:
#  - Python 3.8+ with: ultralytics, opencv-python, Pillow, PyYAML
#  - CMake 3.20+
#  - C compiler (MSVC, GCC, or Clang)
#  - ONNX Runtime (optional, for inference)
#  - Git (for version control)

set -e  # Exit on first error

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ALPR_DIR="$REPO_ROOT/c_alpr"
TOOLS_DIR="$ALPR_DIR/tools"
CONFIG_DIR="$ALPR_DIR/configs"

echo "========================================"
echo "ALPR C Implementation - E2E Test Workflow"
echo "========================================"
echo "Repository root: $REPO_ROOT"
echo ""

# Step 1: Export ONNX models
echo "[1/6] Exporting YOLO models to ONNX format..."
echo "    Running: python $TOOLS_DIR/export_onnx.py"
python "$TOOLS_DIR/export_onnx.py" || {
    echo "ERROR: ONNX export failed"
    exit 1
}
echo "✓ ONNX models exported successfully"
echo ""

# Step 2: Convert test images to BMP 24-bit
echo "[2/6] Converting test images to BMP 24-bit format..."
echo "    Running: python $TOOLS_DIR/convert_to_bmp24.py"
python "$TOOLS_DIR/convert_to_bmp24.py" || {
    echo "ERROR: Image conversion failed"
    exit 1
}
echo "✓ Test images converted to BMP"
echo ""

# Step 3: Build C ALPR with CMake
echo "[3/6] Building C ALPR application..."
if [ ! -d "$ALPR_DIR/build" ]; then
    mkdir "$ALPR_DIR/build"
fi

cd "$ALPR_DIR/build"
echo "    Running CMake configuration..."
cmake -S "$ALPR_DIR" -B . -DENABLE_ONNXRUNTIME=ON -DCMAKE_BUILD_TYPE=Release

echo "    Running build..."
cmake --build . --config Release -j 4 || {
    echo "ERROR: Build failed"
    echo ""
    echo "Troubleshooting tips:"
    echo "  1. Make sure CMake 3.20+ is installed"
    echo "  2. Check that ONNX Runtime is properly downloaded"
    echo "  3. Try: cmake -S $ALPR_DIR -B . -DENABLE_ONNXRUNTIME=OFF"
    exit 1
}
echo "✓ C ALPR built successfully"
echo ""

# Step 4: Generate Python baseline
echo "[4/6] Generating Python baseline results..."
echo "    Running: python $TOOLS_DIR/generate_python_baseline.py"
python "$TOOLS_DIR/generate_python_baseline.py" || {
    echo "ERROR: Python baseline generation failed"
    exit 1
}
echo "✓ Python baseline generated"
echo ""

# Step 5: Run C ALPR on test images
echo "[5/6] Running C ALPR on test images..."
if [ -f "$ALPR_DIR/build/Release/c_alpr.exe" ]; then
    C_ALPR_BIN="$ALPR_DIR/build/Release/c_alpr.exe"
elif [ -f "$ALPR_DIR/build/c_alpr" ]; then
    C_ALPR_BIN="$ALPR_DIR/build/c_alpr"
else
    echo "ERROR: C ALPR executable not found"
    exit 1
fi

echo "    Running: $C_ALPR_BIN $CONFIG_DIR/alpr_config.ini $ALPR_DIR/test_images"
"$C_ALPR_BIN" "$CONFIG_DIR/alpr_config.ini" "$ALPR_DIR/test_images" || {
    echo "ERROR: C ALPR execution failed"
    exit 1
}
echo "✓ C ALPR results generated"
echo ""

# Step 6: Compare results
echo "[6/6] Comparing C vs Python results..."
echo "    Running: python $TOOLS_DIR/compare_baseline.py"
python "$TOOLS_DIR/compare_baseline.py" "$ALPR_DIR/test_images" "$REPO_ROOT/output/baseline_python" || {
    echo "ERROR: Comparison failed"
    exit 1
}
echo "✓ Comparison complete"
echo ""

echo "========================================"
echo "SUCCESS: E2E workflow completed!"
echo "========================================"
echo ""
echo "Results:"
echo "  - Python baseline: $REPO_ROOT/output/baseline_python/"
echo "  - C ALPR output:   $ALPR_DIR/test_images/"
echo "  - Comparison logs: Check output above"
echo ""
echo "Next steps:"
echo "  1. Review accuracy percentages above"
echo "  2. Check output/baseline_python/ and c_alpr/test_images/ for JSON files"
echo "  3. Investigate any discrepancies in individual results"
echo ""
