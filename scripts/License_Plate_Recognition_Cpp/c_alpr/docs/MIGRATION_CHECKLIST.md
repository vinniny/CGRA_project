# C Migration Checklist (Python -> Pure C)

This checklist is strict by design. Do not skip gate checks.

## Current Implementation Status (as of Phase 2)

**Completed:**
- ✅ Stage 1: Export tools ready (tools/export_onnx.py)
- ✅ Stage 2: C foundation built and compiles cleanly
- ✅ Stage 3: Plate detector implemented (decode + NMS ready)
- ✅ Stage 4: Character detector implemented (decode + NMS ready)
- ✅ Stage 5: Plate assembly logic implemented
- ✅ Core pipeline: End-to-end ALPR runs on image buffers
- ✅ Image I/O: BMP 24-bit loader (C pure)
- ✅ Result dump: JSON/TXT output for baseline comparison
- ✅ Batch mode: Process folder of images

**In Progress:**
- ⏳ Stage 6: Webcam capture backend (stub only)

**Not Started:**
- ⌛ JPG/PNG image support
- ⌛ Realtime overlay rendering
- ⌛ Performance tuning (FP16, threading)

---

## Stage 0: Baseline Freeze (Python)

Goal: lock reference behavior before writing C runtime.

Tasks:
- Run webcam pipeline in summary/webcam/main.py on a fixed 2-minute video capture.
- Run image pipeline on a fixed test set (at least 100 images).
- Save metrics:
  - plate_recall
  - character_detection_f1
  - full_plate_text_accuracy
  - avg_fps and p95_latency_ms
- Save reference outputs (json + rendered images) under output/baseline_python.

Gate:
- PASS only when all metrics and artifacts are saved and reproducible.

## Stage 1: Export Models to ONNX

Goal: produce stable model artifacts for C runtime.

Tasks:
- Export license plate model to models/license_plate.onnx.
- Export character model to models/character.onnx.
- Validate output tensor shape and class count.
- Verify ONNX inference in Python on 20 random samples.

Gate:
- PASS only when ONNX outputs are numerically consistent with PyTorch outputs.

## Stage 2: Build C Foundation

Goal: compile C project and run skeleton app.

Tasks:
- Build c_alpr with CMake on Windows.
- Verify config parser and module linking.
- Run executable and verify no crash on startup/shutdown.

Gate:
- PASS when build is clean and app exits gracefully.

## Stage 3: Plate Detector in C

Goal: match plate detector behavior.

Tasks:
- Implement ONNX Runtime C API in src/onnx_engine.c.
- Implement plate output decode and per-class NMS.
- Ensure preprocess matches letterbox behavior exactly.
- Compare boxes against Python baseline on fixed images.

Gate:
- PASS only when:
  - mean IoU vs baseline >= 0.90
  - plate recall drop <= 2%

## Stage 4: Character Detector in C

Goal: match character detector behavior.

Tasks:
- Add crop logic from plate boxes.
- Implement character detector decode + NMS.
- Validate class mapping exactly follows config_character.yaml.

Gate:
- PASS when character-level F1 drop <= 2% vs baseline.

## Stage 5: Plate Text Assembly

Goal: preserve one-line and two-line logic.

Tasks:
- Use sort-by-x for one-line plate.
- Insert '-' between alpha->digit transitions.
- For two-line plate, split by mean y and concatenate top-line + '-' + bottom-line.
- Add unit tests for edge cases.

Gate:
- PASS when full plate text accuracy drop <= 2%.

## Stage 6: Webcam Runtime

Goal: stable real-time processing.

Tasks:
- Implement camera capture backend.
- Implement overlay rendering.
- Run 30-minute stress test.

Gate:
- PASS when:
  - no memory leak observed
  - no crash in stress run
  - fps meets target

## Stage 7: Optimization (Optional)

Goal: improve speed without quality regression.

Tasks:
- Reduce copy operations.
- Introduce capture/inference/render pipeline threading if needed.
- Evaluate FP16 backend path if supported.

Gate:
- PASS only if quality remains within previous gate thresholds.

## Final Audit Checklist

- [ ] All stage gates passed.
- [ ] Metrics documented in one summary report.
- [ ] Runtime reproducible from clean machine instructions.
- [ ] Failure handling tested (camera disconnect, empty frame, bad model path).
- [ ] CPU fallback behavior documented.
