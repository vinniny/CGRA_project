#!/bin/bash
# run_demo_arm.sh
# Runs the License Plate Recognition (LPR) pipeline entirely on the ARM Cortex-A9 CPU.
# Evaluates 4500 character images to demonstrate baseline software performance.

echo "=========================================================="
echo " Running LPR Inference on ARM CPU ONLY (Baseline)"
echo "=========================================================="

# Ensure we are in the directory with the binaries and data
cd "$(dirname "$0")"

# The executable built without CGRA definitions
time ./build/lpr_eval ../lprnet_eval/golden_weights.bin ../demo_lpr_test_images.bin
