# C ALPR Quick Start and Baseline Comparison

This guide walks you through setting up, building, and comparing C ALPR with Python baseline.

## Goal: Runtime 100% in C (No Python)

Your target workflow is valid:
- Use Python only once for migration support (export model `.pt` -> `.onnx`) if needed.
- After that, run inference with C executable only.
- No Python process is required during C runtime.

Current status in this repo:
- ✅ C inference pipeline implemented (plate detect -> char detect -> assemble text)
- ✅ C batch/single-image execution implemented
- ✅ C result dump (JSON/TXT) implemented
- ❌ C webcam backend is still stub (`capture_ffmpeg.c`)
- ❌ C overlay renderer is still stub (`draw_overlay.c`)

So right now, C-only runtime is ready for image/folder mode; webcam realtime in C still needs implementation.
So right now, C-only runtime is ready for image/folder mode and basic webcam realtime in console mode.

## Prerequisites

1. **Python 3.8+** with packages:
   - `ultralytics` (YOLOv8)
   - `opencv-python` (cv2)
   - `Pillow` (PIL)
   - `PyYAML`
   - Install: `pip install ultralytics opencv-python Pillow PyYAML`

2. **ONNX Runtime C library** (optional, enable with CMake flag)
   - Download: https://github.com/microsoft/onnxruntime/releases
   - Extract to a known path (e.g., `C:\onnxruntime-win-x64-1.16.0`)

3. **CMake 3.20+** and C Compiler
   - CMake: https://cmake.org/download/
   - Visual Studio 2019+ (MSVC) OR MinGW or GCC

## Automated E2E Workflow (Recommended)

The simplest way to run the complete build-test-compare cycle:

### Windows
```cmd
cd c_alpr
run_e2e_test.bat
```

### Linux/macOS
```bash
cd c_alpr
bash run_e2e_test.sh
```

This automatically:
1. ✅ Exports YOLO models to ONNX
2. ✅ Converts test images to BMP 24-bit
3. ✅ Builds C ALPR with CMake
4. ✅ Generates Python baseline
5. ✅ Runs C ALPR batch inference
6. ✅ Compares C vs Python results
7. ✅ Reports accuracy percentage

Expected output: Accuracy >= 95% match on plate text

## Webcam-Only Test (No CMake, No C Build)

If you only want live webcam testing, use the Python pipeline directly.

From repository root:

```cmd
run_webcam_python.bat
```

This launcher will:
1. Check YOLO model files (`runs/detect/train/weights/last.pt` and `runs/detect/train2/weights/last.pt`)
2. Check/install Python packages (`ultralytics`, `opencv-python`)
3. Start webcam ALPR (`summary/webcam/main.py`)

Controls:
- Press `q` in the webcam window to quit.

Note:
- This mode does not require `cmake`.
- This mode does not use `c_alpr` executable.

Important:
- This is Python webcam mode for quick validation only.
- It is not the final C-only webcam runtime.

## Webcam Runtime in C (No Python)

Recommended one-command launcher:

```cmd
cd c_alpr
run_webcam_c.bat C:\path\to\onnxruntime 0
```

If you use an external webcam, try index `1` first:

```cmd
run_webcam_c.bat C:\path\to\onnxruntime 1
```

Arguments:
- First argument: ONNX Runtime root folder.
- Second argument: camera index (optional, default `0`).

Manual command (after build):

After C build is complete and ONNX Runtime is linked, run:

```cmd
cd c_alpr
build\Release\c_alpr.exe configs\alpr_config.ini webcam
```

Or select camera index explicitly:

```cmd
cd c_alpr
build\Release\c_alpr.exe configs\alpr_config.ini webcam:1
```

Behavior:
- Reads webcam frames in C using `ffmpeg` rawvideo pipe.
- Runs full ALPR inference in C per frame.
- Prints plate text and FPS stats to console.
- Press `q` in terminal to stop.

Requirement:
- `ffmpeg` and `ffplay` must be installed and available in `PATH`.

Windows quick check:

```cmd
ffmpeg -version
ffplay -version
```

If both commands return version info, webcam C runtime is ready.

List webcams on Windows:

```cmd
cd c_alpr
list_webcams.bat
```

Then run with matched index: `webcam:1`, `webcam:2`, ...

---

## Manual Step-by-Step Workflow

### Step 1: Export Models to ONNX

```bash
cd c_alpr
python tools/export_onnx.py
```

Expected output:
- `c_alpr/models/license_plate.onnx`
- `c_alpr/models/character.onnx`

### Step 2: Convert Test Images to BMP 24-bit

(Optional, only if you want to test on data folder)

```bash
python tools/convert_to_bmp24.py
```

This will create:
- `c_alpr/test_images/` with all images converted to BMP 24-bit

### Step 3: Build C ALPR with ONNX Runtime

```bash
cd c_alpr
cmake -S . -B build -DENABLE_ONNXRUNTIME=ON -DONNXRUNTIME_ROOT=C:/path/to/onnxruntime-win-x64
cmake --build build --config Release
```

### Step 3.1: Run C-only (No Python) for image/folder inference

After successful build, you can run C executable directly:

```cmd
cd c_alpr
build\Release\c_alpr.exe configs\alpr_config.ini test_images
```

This command is fully C runtime (no Python invoked).

## Step 4: Run Baseline Python Pipeline

Record Python outputs for comparison:

```bash
python c_alpr/tools/generate_python_baseline.py
```

This generates:
- `output/baseline_python/*.json` with Python YOLO results

## Step 5: Run C ALPR Pipeline

Test on batch folder:

```bash
cd c_alpr
build\Release\c_alpr.exe configs\alpr_config.ini test_images
```

This will generate `test_images/*.bmp.json` with C outputs.

## Step 6: Compare Results

```bash
python c_alpr/tools/compare_baseline.py c_alpr/test_images output/baseline_python
```

Expected output:
```
✓ image1: ABC123
✓ image2: XYZ789
✗ image3: C=ABC124 PY=ABC123
...
Accuracy: 98/100 (98.0%)
Errors: 2
```

## Troubleshooting

### ONNX Runtime not found

```
cmake: Set ONNXRUNTIME_ROOT when ENABLE_ONNXRUNTIME=ON
```

Solution:
```bash
cmake -S . -B build -DENABLE_ONNXRUNTIME=ON -DONNXRUNTIME_ROOT=C:/actual/path
```

### Image load failures

Ensure images are BMP 24-bit RGB:
```bash
python tools/convert_to_bmp24.py
```

### No detections

- Check threshold values in `configs/alpr_config.ini`
- Verify ONNX models are valid: `python -c "import onnxruntime as rt; rt.InferenceSession('path/to/model.onnx')"`
- Check image quality and plate visibility

## Migration Checklist Gates

Following docs/MIGRATION_CHECKLIST.md:

- **Stage 1**: Export models - PASS if ONNX files created
- **Stage 2**: Build C foundation - PASS if cmake succeeds
- **Stage 3**: Plate detector accuracy - PASS if % diff <= 2%
- **Stage 4**: Character detector accuracy - PASS if % diff <= 2%
- **Stage 5**: Plate text assembly - PASS if string match >= 98%

Use the baseline comparison tool to verify each stage.
