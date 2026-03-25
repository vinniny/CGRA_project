cmake_minimum_required(VERSION 3.20)
project(c_alpr C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
    # Build with static runtime (/MT, /MTd) to avoid external VC++ redistributable dependency.
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Webcam-only minimal build
option(ENABLE_ONNXRUNTIME "Enable ONNX Runtime integration" ON)
option(ENABLE_FFMPEG "Enable FFmpeg camera capture" ON)

add_executable(c_alpr
    src/app_main.c
    src/alpr_pipeline.c
    src/config.c
    src/preprocess.c
    src/nms.c
    src/char_map.c
    src/yolo_decode.c
    src/plate_assemble.c
    src/onnx_engine.c
    src/capture_ffmpeg.c
    src/draw_overlay.c
    src/display_ffplay.c
    src/image_io.c
    src/result_dump.c
    src/batch_process.c
)

target_include_directories(c_alpr PRIVATE include)

if(ENABLE_ONNXRUNTIME)
    target_compile_definitions(c_alpr PRIVATE ALPR_USE_ONNXRUNTIME=1)
    set(ONNXRUNTIME_ROOT "" CACHE PATH "ONNX Runtime root directory")
    if(NOT ONNXRUNTIME_ROOT)
        message(FATAL_ERROR "Set ONNXRUNTIME_ROOT when ENABLE_ONNXRUNTIME=ON")
    endif()
    target_include_directories(c_alpr PRIVATE ${ONNXRUNTIME_ROOT}/include)
    if(WIN32)
        target_link_libraries(c_alpr PRIVATE ${ONNXRUNTIME_ROOT}/lib/onnxruntime.lib)
    else()
        target_link_libraries(c_alpr PRIVATE ${ONNXRUNTIME_ROOT}/lib/libonnxruntime.so)
    endif()
endif()

if(ENABLE_FFMPEG)
    target_compile_definitions(c_alpr PRIVATE ALPR_USE_FFMPEG=1)
endif()

if(MSVC)
    target_compile_options(c_alpr PRIVATE /W4)
else()
    target_compile_definitions(c_alpr PRIVATE _POSIX_C_SOURCE=200809L)
    target_compile_options(c_alpr PRIVATE -Wall -Wextra -Wpedantic)
    target_link_libraries(c_alpr PRIVATE m)
endif()
