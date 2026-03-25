# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What This Is

Pure C11 license plate recognition pipeline. Uses ONNX Runtime for YOLO inference (plate detection + character recognition), FFmpeg/FFplay for webcam capture/display. No C++ or Python at runtime. Part of the larger CGRA project (`scripts/License_Plate_Recognition_Cpp/c_alpr/`).

## Build Commands

```bash
# Basic build (no ONNX inference — stubs only)
cmake -S . -B build
cmake --build build --config Release

# Build with ONNX Runtime (required for actual inference)
cmake -S . -B build -DENABLE_ONNXRUNTIME=ON -DONNXRUNTIME_ROOT=/path/to/onnxruntime
cmake --build build --config Release

# Linux embedded/FPGA build
cmake -S . -B build -DENABLE_ONNXRUNTIME=ON -DENABLE_FFMPEG=ON -DONNXRUNTIME_ROOT=/path/to/onnxruntime
cmake --build build --config Release
```

## Run Modes

```bash
# Smoke test (synthetic, no models needed)
build/Release/c_alpr configs/alpr_config.ini

# Single BMP image → outputs image.bmp.json + image.bmp.txt
build/Release/c_alpr configs/alpr_config.ini image.bmp

# Batch folder of BMPs
build/Release/c_alpr configs/alpr_config.ini folder_with_bmps/

# Webcam (requires ffmpeg + ffplay in PATH)
build/Release/c_alpr configs/alpr_config.ini webcam:0
```

## E2E Test (Python baseline comparison)

```bash
./run_e2e_test.sh   # Full 6-step workflow: export models → convert images → build → baseline → run → compare
```

Requires Python 3.8+ with ultralytics, opencv-python, Pillow, PyYAML.

## Architecture

The pipeline flows: **Image → Plate Detection → Character Detection → Text Assembly**

Key runtime struct is `AlprRuntime` (in `alpr_pipeline.h`) which holds config, two ONNX engines (plate + char), and pre-allocated input buffers. The main entry point is `alpr_runtime_run_image()`.

```
app_main.c          → Entry point, mode dispatch (smoke/image/batch/webcam), temporal voting for webcam
alpr_pipeline.c     → Core pipeline: plate detect → char detect → assemble (500+ lines, most logic lives here)
onnx_engine.c       → ONNX Runtime C API wrapper (session create/run/destroy)
preprocess.c        → Letterbox resize + normalize to float32 + coordinate remapping
yolo_decode.c       → YOLO output tensor → AlprDetectionArray (handles both [1,N,5+nc] and [1,5+nc,N] layouts)
nms.c               → Non-maximum suppression
char_map.c          → Class ID → character label (hardcoded from config_character.yaml)
plate_assemble.c    → Sort characters by position, detect 1-line vs 2-line, insert dashes
config.c            → INI file parser → AlprConfig struct
capture_ffmpeg.c    → FFmpeg camera capture (pipes raw frames via subprocess)
display_ffplay.c    → FFplay video output (pipes raw frames via subprocess)
draw_overlay.c      → 10x10 bitmap font rendering directly on frame buffer
image_io.c          → Pure C BMP 24-bit loader (BGR→RGB)
batch_process.c     → Folder enumeration + per-image processing
result_dump.c       → JSON/TXT output formatters
```

## Key Types (alpr_types.h)

- `AlprImageU8` — Raw image buffer (data, width, height, channels, stride)
- `AlprDetection` — Bounding box + score + class_id
- `AlprCharacterDetection` — Bounding box + score + character label
- `AlprPlateResult` — Final output: text string, plate type (1-line/2-line), confidence
- Max detections per frame: `ALPR_MAX_DETECTIONS` (512)

## CMake Options

- `ENABLE_ONNXRUNTIME` (ON/OFF) — gates `ALPR_USE_ONNXRUNTIME` compile define
- `ENABLE_FFMPEG` (ON/OFF) — gates `ALPR_USE_FFMPEG` compile define
- `ONNXRUNTIME_ROOT` — path to ONNX Runtime install (required when ONNXRUNTIME=ON)

## Conventions

- Pure C11 only. No C++ STL, no Boost. ONNX Runtime C API, not C++.
- MSVC uses static runtime (`/MT`). GCC/Clang use `-Wall -Wextra -Wpedantic`.
- Error handling via negative return codes and NULL checks.
- All allocations freed in corresponding `_destroy` functions.
- Platform guards (`#ifdef _WIN32`) where Windows/Linux APIs differ (batch_process uses Windows API for folder enumeration).
- Runtime config externalized in `configs/alpr_config.ini` — model paths, thresholds, camera index.

## Validation Tools (tools/)

Python scripts for model export and accuracy comparison against the Python YOLO reference:
- `export_onnx.py` — Export YOLO .pt weights → ONNX
- `convert_to_bmp24.py` — Convert test images to BMP format for C loader
- `generate_python_baseline.py` — Run Python inference to produce baseline JSON
- `compare_baseline.py` — Diff C output JSON vs Python baseline
