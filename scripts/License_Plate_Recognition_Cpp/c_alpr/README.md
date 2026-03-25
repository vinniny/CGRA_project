# c_alpr - Webcam License Plate Recognition (Pure C)

**Production-ready C implementation for real-time license plate detection via webcam. Zero Python runtime - pure C with ONNX inference.**

## Status

- ✅ Pure C webcam detection pipeline
- ✅ ONNX Runtime integration (plate + character detection)
- ✅ FFmpeg/FFplay realtime capture & display
- ✅ 8-frame temporal stability voting
- ✅ Bitmap font overlay rendering (10x10 chars)
- ✅ Linux-ready (no Python dependencies)
- ✅ FPGA embedded deployment (lean ~20 MB)

## Quick Start

### 1. Install Dependencies (Windows)
- Visual Studio 2019+ (C compiler)
- CMake 3.20+
- FFmpeg + FFplay (auto-detected or bundled)
- ONNX Runtime 1.17.0

### 2. Build & Run Webcam
```cmd
cd c_alpr
run_webcam_c.bat
```

**Specify ONNX Runtime location:**
```cmd
run_webcam_c.bat "C:\path\to\onnxruntime"
```

**Select different webcam device:**
```cmd
run_webcam_c.bat C:\path\to\onnxruntime 1
```

### 3. List Available Cameras
```cmd
list_webcams.bat
```

## Configuration

Edit `configs/alpr_config.ini`:
```ini
# Detection sensitivity
plate_conf_threshold = 0.40       # License plate confidence
char_conf_threshold = 0.35        # Character confidence (prevents OCR noise)

# Camera settings
camera_index = 0                  # Webcam device index (0 = default)
display_fps = 1                   # Show FPS overlay
```

## Runtime Command Line

```bash
c_alpr configs/alpr_config.ini webcam:0
```

**Output:**
- Real-time plate text overlaid on video stream
- Console logs: detection history, voting confidence, FPS stats
- Yellow text (10x10 bitmap font) on frame

## Architecture

```
c_alpr/
├── src/
│   ├── app_main.c               # Webcam loop + voting logic
│   ├── alpr_pipeline.c          # YOLO plate→char→assembly
│   ├── onnx_engine.c            # ONNX Runtime wrapper
│   ├── capture_ffmpeg.c         # FFmpeg camera input
│   ├── display_ffplay.c         # FFplay video output
│   ├── draw_overlay.c           # Bitmap font rendering
│   ├── plate_assemble.c         # 1-line/2-line plate text
│   ├── config.c                 # INI parser
│   ├── preprocess.c             # Letterbox + normalize
│   ├── yolo_decode.c            # YOLO output decoding
│   ├── nms.c                    # Non-max suppression
│   └── char_map.c               # Class ID→character mapping
├── include/                      # Headers (matching src/)
├── models/                       # ONNX files (auto-exported)
├── configs/                      # Runtime config
└── docs/                         # Quick start
```

## Performance

| Metric | Value |
|--------|-------|
| Resolution | 640x360 |
| FPS | 4-6 (inference every 2 frames) |
| Inference | ~100-200ms per plate crop |
| Latency | <500ms real-time |
| Memory | <150 MB (lean build) |
| Binary | ~5 MB |

## Cleanup (Remove Non-Webcam Files)

To reduce footprint for FPGA deployment:
```powershell
cd c_alpr
powershell -ExecutionPolicy Bypass -File cleanup.ps1
```

Removes: tools/, tests/, test_images/, build/, unused docs, unused source files.
Keeps: src/, include/, models/, configs/, launchers.

**See [CLEANUP_GUIDE.md](CLEANUP_GUIDE.md) for details.**

## Linux/FPGA Deployment

Build for embedded Linux:
```bash
cd c_alpr
mkdir build && cd build
cmake -DENABLE_ONNXRUNTIME=ON -DENABLE_FFMPEG=ON \
      -DONNXRUNTIME_ROOT=/path/to/onnxruntime ..
cmake --build . --config Release
```

Run:
```bash
./c_alpr configs/alpr_config.ini webcam:0
```

## Debug Logging

Console output includes:
- `[infer #N] raw='59-NB'` - Raw inference text
- `[voting PASS]` - Text passed temporal voting
- `[DRAW] stable_text='59-NB'` - Text rendered to frame
- `[stats]` - FPS & detection count


From repository root:

```bash
python c_alpr/tools/export_onnx.py
```

Expected output files:

- c_alpr/models/license_plate.onnx
- c_alpr/models/character.onnx

## Build

```bash
cd c_alpr
cmake -S . -B build
cmake --build build --config Release
```

Build with ONNX Runtime:

```bash
cd c_alpr
cmake -S . -B build -DENABLE_ONNXRUNTIME=ON -DONNXRUNTIME_ROOT=C:/path/to/onnxruntime-win-x64
cmake --build build --config Release
```

## Run modes

Synthetic test (smoke test):
```bash
build\Release\c_alpr.exe configs\alpr_config.ini
```

Single BMP image:
```bash
build\Release\c_alpr.exe configs\alpr_config.ini image.bmp
```

Output files: `image.bmp.json`, `image.bmp.txt`

Batch process BMP folder:
```bash
build\Release\c_alpr.exe configs\alpr_config.ini folder_with_bmp_images
```

Outputs: JSON/TXT for each image in the folder.

Webcam in C runtime (console mode):
```bash
build\Release\c_alpr.exe configs\alpr_config.ini webcam
```

Select camera index explicitly:
```bash
build\Release\c_alpr.exe configs\alpr_config.ini webcam:1
```

Requirement: `ffmpeg` and `ffplay` must be installed and available in `PATH`.

## Baseline Comparison Workflow

1. Export ONNX models: `python c_alpr/tools/export_onnx.py`
2. Convert images: `python c_alpr/tools/convert_to_bmp24.py`
3. Generate Python baseline JSON: `python c_alpr/tools/generate_python_baseline.py`
4. Run C ALPR on `c_alpr/test_images`
5. Compare: `python c_alpr/tools/compare_baseline.py c_alpr/test_images output/baseline_python`
6. Follow `docs/MIGRATION_CHECKLIST.md` gates

## Next implementation priorities

1. JPG/PNG image loader (stb_image single-header or external library)
2. Webcam backend (FFmpeg/OpenCV C API)
3. Realtime rendering overlay
4. Metric comparison tools

