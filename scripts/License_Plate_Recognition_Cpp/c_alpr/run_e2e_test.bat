@echo off
REM End-to-End ALPR C Implementation Build and Test Workflow (Windows)
REM Run this script to build the C ALPR and validate against Python baseline
REM 
REM Prerequisites:
REM  - Python 3.8+ with: ultralytics, opencv-python, Pillow, PyYAML
REM  - CMake 3.20+
REM  - C compiler (MSVC, GCC with WSL, or MinGW)
REM  - Visual Studio 2019+ (for MSVC) OR MinGW
REM  - ONNX Runtime (optional, for inference)

setlocal enabledelayedexpansion

cd /d "%~dp0.."
set REPO_ROOT=%CD%
set ALPR_DIR=%REPO_ROOT%\c_alpr
set TOOLS_DIR=%ALPR_DIR%\tools
set CONFIG_DIR=%ALPR_DIR%\configs

echo ========================================
echo ALPR C Implementation - E2E Test Workflow (Windows)
echo ========================================
echo Repository root: %REPO_ROOT%
echo.

REM Step 1: Export ONNX models
echo [1/6] Exporting YOLO models to ONNX format...
echo     Running: python %TOOLS_DIR%\export_onnx.py
python "%TOOLS_DIR%\export_onnx.py"
if errorlevel 1 (
    echo ERROR: ONNX export failed
    exit /B 1
)
echo Done. ONNX models exported successfully
echo.

REM Step 2: Convert test images to BMP 24-bit
echo [2/6] Converting test images to BMP 24-bit format...
echo     Running: python %TOOLS_DIR%\convert_to_bmp24.py
python "%TOOLS_DIR%\convert_to_bmp24.py"
if errorlevel 1 (
    echo ERROR: Image conversion failed
    exit /B 1
)
echo Done. Test images converted to BMP
echo.

REM Step 3: Build C ALPR with CMake
echo [3/6] Building C ALPR application...
if not exist "%ALPR_DIR%\build" mkdir "%ALPR_DIR%\build"

cd /d "%ALPR_DIR%\build"
echo     Running CMake configuration...
cmake -S "%ALPR_DIR%" -B . -DENABLE_ONNXRUNTIME=ON -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 16 2019" -A x64
if errorlevel 1 (
    echo     Note: Above generator failed. Trying with MSVC 2022...
    cmake -S "%ALPR_DIR%" -B . -DENABLE_ONNXRUNTIME=ON -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022" -A x64
)
if errorlevel 1 (
    echo     Note: Trying MinGW if MSVC unavailable...
    cmake -S "%ALPR_DIR%" -B . -DENABLE_ONNXRUNTIME=ON -DCMAKE_BUILD_TYPE=Release
)
if errorlevel 1 (
    echo ERROR: CMake configuration failed
    echo.
    echo Troubleshooting tips:
    echo   1. Make sure CMake 3.20+ is installed
    echo   2. Make sure Visual Studio 2019+ or MinGW is installed
    echo   3. Check that ONNX Runtime is properly downloaded
    echo   4. Try: cmake -S %ALPR_DIR% -B . -DENABLE_ONNXRUNTIME=OFF
    exit /B 1
)

echo     Running build...
cmake --build . --config Release -j 4
if errorlevel 1 (
    echo ERROR: Build failed
    exit /B 1
)
echo Done. C ALPR built successfully
echo.

REM Step 4: Generate Python baseline
echo [4/6] Generating Python baseline results...
echo     Running: python %TOOLS_DIR%\generate_python_baseline.py
python "%TOOLS_DIR%\generate_python_baseline.py"
if errorlevel 1 (
    echo ERROR: Python baseline generation failed
    exit /B 1
)
echo Done. Python baseline generated
echo.

REM Step 5: Run C ALPR on test images
echo [5/6] Running C ALPR on test images...
set C_ALPR_BIN=%ALPR_DIR%\build\Release\c_alpr.exe
if not exist "%C_ALPR_BIN%" (
    set C_ALPR_BIN=%ALPR_DIR%\build\Debug\c_alpr.exe
)
if not exist "%C_ALPR_BIN%" (
    echo ERROR: C ALPR executable not found
    echo         Expected: %ALPR_DIR%\build\Release\c_alpr.exe
    echo         Fallback: %ALPR_DIR%\build\Debug\c_alpr.exe
    exit /B 1
)

echo     Running: %C_ALPR_BIN% %CONFIG_DIR%\alpr_config.ini %ALPR_DIR%\test_images
"%C_ALPR_BIN%" "%CONFIG_DIR%\alpr_config.ini" "%ALPR_DIR%\test_images"
if errorlevel 1 (
    echo ERROR: C ALPR execution failed
    echo Make sure ONNX Runtime DLLs are in PATH or in the same directory as c_alpr.exe
    exit /B 1
)
echo Done. C ALPR results generated
echo.

REM Step 6: Compare results
echo [6/6] Comparing C vs Python results...
echo     Running: python %TOOLS_DIR%\compare_baseline.py
python "%TOOLS_DIR%\compare_baseline.py" "%ALPR_DIR%\test_images" "%REPO_ROOT%\output\baseline_python"
if errorlevel 1 (
    echo ERROR: Comparison failed
    exit /B 1
)
echo Done. Comparison complete
echo.

echo ========================================
echo SUCCESS: E2E workflow completed!
echo ========================================
echo.
echo Results:
echo   - Python baseline: %REPO_ROOT%\output\baseline_python\
echo   - C ALPR output:   %ALPR_DIR%\test_images\
echo   - Comparison logs: Check output above
echo.
echo Next steps:
echo   1. Review accuracy percentages above
echo   2. Check output\baseline_python\ and c_alpr\test_images\ for JSON files
echo   3. Investigate any discrepancies in individual results
echo.
endlocal
