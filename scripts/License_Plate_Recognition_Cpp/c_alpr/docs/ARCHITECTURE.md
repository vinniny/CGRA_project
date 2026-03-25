# C ALPR Architecture Overview

## Module Hierarchy

```
c_alpr/
├── include/
│   ├── alpr_types.h          # Shared types (detection, image, plate result)
│   ├── config.h              # Configuration parser
│   ├── preprocess.h          # Letterbox, normalize, coordinate mapping
│   ├── nms.h                 # IoU, NMS for detections
│   ├── onnx_engine.h         # ONNX Runtime wrapper
│   ├── yolo_decode.h         # YOLO output to detections
│   ├── char_map.h            # Character class mapping
│   ├── plate_assemble.h      # One-line/two-line text assembly
│   ├── alpr_pipeline.h       # End-to-end ALPR runtime
│   ├── image_io.h            # BMP 24-bit loader
│   ├── result_dump.h         # JSON/TXT output
│   ├── batch_process.h       # Folder batch processing
│   ├── capture_ffmpeg.h      # Camera capture (stub)
│   └── draw_overlay.h        # Rendering (stub)
├── src/
│   ├── app_main.c            # Entry point (single image / batch folder / smoke test)
│   ├── config.c              # INI parser implementation
│   ├── preprocess.c          # Image preprocessing (200+ lines)
│   ├── nms.c                 # NMS algorithm implementation
│   ├── onnx_engine.c         # ONNX Runtime integration (~250 lines)
│   ├── yolo_decode.c         # Decode flexibly for [1,N,5+nc] or [1,5+nc,N]
│   ├── char_map.c            # Hardcoded mapping from config_character.yaml
│   ├── plate_assemble.c      # Sort + assemble logic for 1-line/2-line
│   ├── alpr_pipeline.c       # Full inference pipeline (500+ lines)
│   ├── image_io.c            # Pure C BMP parser + BGR->RGB
│   ├── result_dump.c         # JSON/TXT formatter
│   ├── batch_process.c       # Windows API folder enumeration
│   ├── capture_ffmpeg.c      # Stub for FFmpeg integration
│   └── draw_overlay.c        # Stub for rendering
├── configs/
│   └── alpr_config.ini       # Runtime parameters
├── models/
│   ├── license_plate.onnx    # Exported from train/weights/last.pt
│   └── character.onnx        # Exported from train2/weights/last.pt
├── tools/
│   ├── export_onnx.py        # Export YOLO models to ONNX
│   ├── convert_to_bmp24.py   # Convert dataset to BMP for C testing
│   └── compare_baseline.py   # Compare C output with Python baseline
├── tests/
│   └── test_plate_assemble.c # Unit test assembly logic
├── docs/
│   ├── MIGRATION_CHECKLIST.md      # Stage gates and sign-off
│   ├── PLAN_AUDIT_TEMPLATE.md      # Audit per-stage drift
│   ├── QUICKSTART.md               # Step-by-step baseline comparison
│   └── ARCHITECTURE.md (this file)
├── CMakeLists.txt            # Build configuration
└── README.md                 # Feature summary

```

## Data Flow (End-to-End Pipeline)

```
RGB Image Buffer
     ↓
[alpr_runtime_run_image]
     ├─→ [run_plate_detector]
     │       ├─→ letterbox (preprocess.c)
     │       ├─→ normalize (preprocess.c)
     │       ├─→ ONNX inference (onnx_engine.c)
     │       ├─→ decode YOLO (yolo_decode.c)
     │       ├─→ NMS (nms.c)
     │       └─→ map boxes to original space (preprocess.c)
     │
     ├─→ [run_char_detector_for_plate] (for best plate)
     │       ├─→ crop biển số từ box
     │       ├─→ scale up if needed
     │       ├─→ letterbox + normalize
     │       ├─→ ONNX inference (character model)
     │       ├─→ decode YOLO detections
     │       ├─→ NMS per character
     │       ├─→ map ký tự class to label (char_map.c)
     │       └─→ collect AlprCharacterArray
     │
     └─→ [alpr_assemble_plate_text]
             ├─→ sort ký tự by x coordinate
             ├─→ distinguish 1-line vs 2-line
             ├─→ insert dashes at alpha→digit transition
             └─→ return plate text string
             
Result: AlprPlateResult {text, confidence, type}
     ↓
[alpr_dump_result_json/txt] (when input image)
```

## Key Design Decisions

1. **Pure C (C11 standard)**
   - No C++ STL, no Boost, no convenience libs
   - ONNX Runtime C API only
   - FFmpeg, OpenCV only via C APIs if needed

2. **ONNX over Direct PyTorch**
   - Model export decoupled from runtime
   - ONNX Runtime mature and widely deployed
   - Avoids PyTorch C++ dependency bloat

3. **BMP 24-bit Loader (Pure C)**
   - Portable implementation, single file
   - Better than stb_image for minimal deps
   - Conversion tools help with JPG/PNG datasets

4. **Modular Architecture**
   - Each stage can be tested independently
   - Preprocess, inference, decode, assemble = clear boundaries
   - Easy to swap backend (e.g., TensorRT instead of ONNX)

5. **Result Dump for Validation**
   - JSON for structured comparison
   - TXT for human review
   - Tools provided to compare against Python

## Integration Points for Extensions

### Camera Backend (capture_ffmpeg.c)
- Implement `alpr_capture_open_camera`
- Return frames as `AlprImageU8`
- Use either FFmpeg C API or OpenCV C bindings

### Rendering Backend (draw_overlay.c)
- Implement `alpr_draw_plate_box` to draw bbox + text
- Implement `alpr_draw_fps` for performance display
- Target: Windows display or save to output video file

### Image Loaders (image_io.c extension)
- Add `alpr_load_jpeg_rgb`
- Add `alpr_load_png_rgb`
- Keep same output type: `AlprImageU8`

### TensorRT Backend Alternative
- Replace `onnx_engine.c` with TensorRT APIs
- Keep same public interface: `alpr_onnx_run`
- May need to update output tensor marshalling

## Performance Tuning Opportunities

1. **Memory Layout**
   - Pre-allocate large buffers in `AlprRuntime`
   - Reduce malloc/free per frame

2. **Threading**
   - Capture thread (camera/video reader)
   - Inference thread (plate + char detect)
   - Render thread (display results)
   - Use condition variables for sync

3. **Quantization**
   - FP16 inference if ONNX backend supports
   - INT8 for even more speed

4. **Batching**
   - Placeholder for future multi-frame batch inference

## Standards Met

- ✅ C11 compliance (no C99-isms, standard headers only)
- ✅ Cross-platform header structure (Windows/Linux guards where needed)
- ✅ Error handling (negative return codes, null checks)
- ✅ Resource cleanup (free all allocations in destroy functions)
- ✅ Configuration externalization (INI file, not hardcoded)

## Testing Strategy

1. **Unit tests** (test/test_*.c)
   - Plate assembly edge cases
   - Coordinate mapping correctness
   - NMS determinism

2. **Integration tests**
   - Single image baseline comparison
   - Batch folder accuracy metric

3. **Regression tests**
   - Synthetic frame smoke test (no ONNX needed)
   - BMP load/save round-trip

## Next Milestones

- [ ] Full baseline accuracy match (Stage 3-5 gates passed)
- [ ] Webcam backend integrated
- [ ] Realtime overlay rendering
- [ ] Performance: 20+ FPS at 720p
- [ ] JPG/PNG loader
- [ ] Publish as standalone library
