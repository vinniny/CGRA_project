# Webcam-Only Project Cleanup Guide

## Project Structure (Optimized for FPGA/Linux Deployment)

### Keep (Essential for Webcam Detection)
```
c_alpr/
├── src/                          # Core C implementation
│   ├── app_main.c               # Webcam loop entry point
│   ├── alpr_pipeline.c          # YOLO plate+char detection
│   ├── onnx_engine.c            # ONNX Runtime wrapper
│   ├── capture_ffmpeg.c         # FFmpeg webcam capture
│   ├── display_ffplay.c         # FFplay realtime display
│   ├── draw_overlay.c           # Font rendering to frame
│   ├── config.c                 # INI config parser
│   ├── preprocess.c             # Image preprocess (letterbox, normalize)
│   ├── nms.c                    # Non-max suppression
│   ├── char_map.c               # Class ID to character mapping
│   ├── yolo_decode.c            # YOLO tensor decoding
│   └── plate_assemble.c         # Text assembly (1-line, 2-line)
├── include/                      # Header files (matching above)
├── models/                       # ONNX files (license_plate.onnx, character.onnx)
├── configs/                      # Runtime config (alpr_config.ini)
├── run_webcam_c.bat            # Main launcher (Windows)
├── list_webcams.bat            # Webcam enumerate (Windows)
├── CMakeLists.txt              # Build config
├── README.md                   # Main readme
└── docs/QUICKSTART.md          # Quick start guide
```

### Delete (Non-Webcam Related)
```
❌ src/image_io.c               # BMP file I/O (webcam-only, no files)
❌ src/batch_process.c          # Batch folder processing
❌ src/result_dump.c            # JSON/TXT result output (memory footprint)

❌ include/image_io.h           # BMP header
❌ include/batch_process.h      # Batch header
❌ include/result_dump.h        # Dump header

❌ tools/                        # Python export/convert scripts (one-time use)
❌ tests/                        # Unit tests
❌ test_images/                 # Test BMP/JPG files
❌ build/                        # Build artifacts (auto-generated)

❌ run_e2e_test.bat/sh          # End-to-end tests
❌ debug_run_webcam_c.bat       # Debug launcher (use run_webcam_c.bat instead)

❌ docs/ARCHITECTURE.md          # Design docs (not needed for deployment)
❌ docs/MIGRATION_CHECKLIST.md   # Migration guide
❌ docs/PLAN_AUDIT_TEMPLATE.md   # Planning templates
```

## Manual Cleanup Steps (Windows PowerShell)

```powershell
cd "d:\License Plate Recognition\c_alpr"

# Remove folders
Remove-Item -Recurse -Force tools, tests, test_images, build 2>$null

# Remove unused test/build scripts
Remove-Item -Force run_e2e_test.bat, run_e2e_test.sh, debug_run_webcam_c.bat 2>$null

# Remove unused docs
Remove-Item -Force docs\ARCHITECTURE.md, docs\MIGRATION_CHECKLIST.md, docs\PLAN_AUDIT_TEMPLATE.md 2>$null

# Delete unused source files from src/ folder
# (These are still in the directory but no longer compiled due to CMakeLists.txt changes)
Remove-Item -Force src\image_io.c, src\batch_process.c, src\result_dump.c 2>$null
Remove-Item -Force include\image_io.h, include\batch_process.h, include\result_dump.h 2>$null

Write-Host "✓ Cleanup complete! Project is now webcam-only."
```

## Build & Deploy (Lean Binary)

### Windows
```bash
cd c_alpr
mkdir build && cd build
cmake -DENABLE_ONNXRUNTIME=ON -DENABLE_FFMPEG=ON -DONNXRUNTIME_ROOT=<path-to-onnxruntime> ..
cmake --build . --config Release
```

### Linux (FPGA Target)
```bash
cd c_alpr
mkdir build && cd build
cmake -DENABLE_ONNXRUNTIME=ON -DENABLE_FFMPEG=ON -DONNXRUNTIME_ROOT=<path-to-onnxruntime> ..
cmake --build . --config Release
./c_alpr configs/alpr_config.ini webcam:0
```

## Footprint Reduction

| Item | Size | Removed |
|------|------|---------|
| source files | ~8 KB | Yes (image_io, batch, result_dump) |
| test files | ~2 KB | Yes |
| tools (Python) | ~15 KB | Yes |
| test_images | ~2 MB | Yes |
| docs (non-essential) | ~50 KB | Yes |
| **Total reduction** | **~2.1 MB** | ✓ |

## Current Configuration

**Webcam-Optimized Settings (c_alpr/configs/alpr_config.ini):**
```ini
# Detection thresholds
plate_conf_threshold = 0.40       # Biển số (license plate)
char_conf_threshold = 0.35        # Ký tự (characters) - reduced OCR noise

# Camera & display
camera_index = 0                  # Default webcam device
display_fps = 1                   # Show FPS bar overlay

# Model paths (relative to config dir)
plate_model_path = ../models/license_plate.onnx
char_model_path = ../models/character.onnx
```

## Remaining Deployment Files

**All necessary files fit in <20MB:**
- c_alpr executable (~5 MB)
- ONNX models (~8 MB)
- Runtime DLLs (ONNX, FFmpeg) deploy with executable
- Configs & docs (~100 KB)

Perfect for FPGA embedded deployment.
