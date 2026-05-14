#!/bin/bash
# run_demo_cgra.sh
# Runs the License Plate Recognition (LPR) pipeline with FC layers offloaded to the CGRA.
# Evaluates 4500 character images to demonstrate hardware acceleration performance.

echo "=========================================================="
echo " Running LPR Inference on CGRA HARDWARE ACCELERATOR"
echo "=========================================================="

# Ensure we are in the directory with the binaries and data
cd "$(dirname "$0")"

# The executable built WITH CGRA definitions (-c flag enables the offload path)
time ./build/lpr_eval_cgra -c ../lprnet_eval/golden_weights.bin ../demo_lpr_test_images.bin
