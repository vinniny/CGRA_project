@echo off
REM Build and run C-only webcam ALPR runtime.

setlocal EnableExtensions DisableDelayedExpansion
cd /d "%~dp0"

set "ALPR_DIR=%CD%"
set "BUILD_DIR=%ALPR_DIR%\build"
set "EXE_PATH=%BUILD_DIR%\Release\c_alpr.exe"
set "CONFIG_PATH=%ALPR_DIR%\configs\alpr_config.ini"
set "MODEL_DIR=%ALPR_DIR%\models"
set "PLATE_ONNX=%MODEL_DIR%\license_plate.onnx"
set "CHAR_ONNX=%MODEL_DIR%\character.onnx"
set "CMAKE_EXE="

set "WEBCAM_ARG=webcam"
if not "%~2"=="" set "WEBCAM_ARG=webcam:%~2"

echo ========================================
echo C Webcam ALPR Launcher
if not "%~2"=="" echo Camera index: %~2
echo ========================================

where cmake >nul 2>&1
if not errorlevel 1 (
	set "CMAKE_EXE=cmake"
)
if not defined CMAKE_EXE (
	if exist "%ProgramFiles%\CMake\bin\cmake.exe" (
		set "CMAKE_EXE=%ProgramFiles%\CMake\bin\cmake.exe"
	)
)
if not defined CMAKE_EXE (
	if exist "%ProgramW6432%\CMake\bin\cmake.exe" (
		set "CMAKE_EXE=%ProgramW6432%\CMake\bin\cmake.exe"
	)
)
if not defined CMAKE_EXE (
	if exist "C:\Program Files\CMake\bin\cmake.exe" (
		set "CMAKE_EXE=C:\Program Files\CMake\bin\cmake.exe"
	)
)

where ffmpeg >nul 2>&1
if errorlevel 1 goto :no_ffmpeg

where ffplay >nul 2>&1
if errorlevel 1 goto :no_ffplay

set "ORT_ROOT=%~1"
if "%ORT_ROOT%"=="" (
	set "ORT_ROOT=%ONNXRUNTIME_ROOT%"
)
if "%ORT_ROOT%"=="" (
	if exist "%ALPR_DIR%\onnxruntime\include" (
		set "ORT_ROOT=%ALPR_DIR%\onnxruntime"
	)
)
if "%ORT_ROOT%"=="" (
	if exist "%ALPR_DIR%\..\onnxruntime\include" (
		set "ORT_ROOT=%ALPR_DIR%\..\onnxruntime"
	)
)
if "%ORT_ROOT%"=="" goto :no_ort

if not "%ORT_ROOT:~1,1%"==":" (
	set "ORT_ROOT=%ALPR_DIR%\%ORT_ROOT%"
)

if not exist "%ORT_ROOT%\include\onnxruntime_c_api.h" goto :bad_ort

echo Using ONNX Runtime: %ORT_ROOT%

call :ensure_models
if errorlevel 1 goto :models_missing

if not defined CMAKE_EXE goto :no_cmake

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

echo Rebuilding c_alpr with ONNX Runtime from: %ORT_ROOT%

"%CMAKE_EXE%" -S "%ALPR_DIR%" -B "%BUILD_DIR%" -DENABLE_ONNXRUNTIME=ON -DONNXRUNTIME_ROOT="%ORT_ROOT%" -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 goto :cmake_config_fail

"%CMAKE_EXE%" --build "%BUILD_DIR%" --config Release -j 4
if errorlevel 1 goto :build_fail

if not exist "%EXE_PATH%" goto :no_exe

:run_exe
set "ORT_DLL="
set "ORT_DLL_DIR="
if exist "%ORT_ROOT%\lib\onnxruntime.dll" (
	set "ORT_DLL=%ORT_ROOT%\lib\onnxruntime.dll"
	set "ORT_DLL_DIR=%ORT_ROOT%\lib"
)
if exist "%ORT_ROOT%\bin\onnxruntime.dll" (
	set "ORT_DLL=%ORT_ROOT%\bin\onnxruntime.dll"
	set "ORT_DLL_DIR=%ORT_ROOT%\bin"
)
if not defined ORT_DLL goto :no_ort_dll

for %%F in ("%ORT_DLL_DIR%\onnxruntime*.dll") do (
	copy /Y "%%~fF" "%BUILD_DIR%\Release\" >nul
)
set "PATH=%ORT_ROOT%\lib;%ORT_ROOT%\bin;%PATH%"

echo.
echo Starting C webcam runtime...
echo Press q in terminal to quit.
echo Using runtime DLL: %ORT_DLL%
echo.
"%EXE_PATH%" "%CONFIG_PATH%" "%WEBCAM_ARG%"
set "RET=%ERRORLEVEL%"
if not "%RET%"=="0" echo Application exited with code: %RET%
if "%RET%"=="-1073741502" goto :dll_init_fail
endlocal & exit /B %RET%

:no_ffmpeg
echo ERROR: ffmpeg not found in PATH.
echo Install with one of these commands:
echo   winget install Gyan.FFmpeg
echo   choco install ffmpeg
endlocal & exit /B 1

:no_ffplay
echo ERROR: ffplay not found in PATH.
echo Install full ffmpeg package (must include ffplay).
endlocal & exit /B 1

:no_ort
echo ERROR: ONNXRUNTIME_ROOT is not set and no local onnxruntime folder was found.
echo Usage:
echo   run_webcam_c.bat C:\path\to\onnxruntime [camera_index]
echo Or set environment variable:
echo   setx ONNXRUNTIME_ROOT "C:\path\to\onnxruntime"
endlocal & exit /B 1

:bad_ort
echo ERROR: Invalid ONNX Runtime folder: %ORT_ROOT%
echo Expected file missing: %ORT_ROOT%\include\onnxruntime_c_api.h
echo Provide the extracted root folder, e.g.:
echo   run_webcam_c.bat D:\onnxruntime-win-x64-1.24.4 0
endlocal & exit /B 1

:no_ort_dll
echo ERROR: Cannot find onnxruntime.dll in selected folder.
echo Checked:
echo   %ORT_ROOT%\lib\onnxruntime.dll
echo   %ORT_ROOT%\bin\onnxruntime.dll
endlocal & exit /B 1

:no_cmake
echo ERROR: cmake not found in PATH and no prebuilt executable was found.
echo Install with one of these commands:
echo   winget install Kitware.CMake
echo   choco install cmake
echo Then open a new terminal and run again.
endlocal & exit /B 1

:cmake_config_fail
echo ERROR: cmake configure failed.
endlocal & exit /B 1

:build_fail
echo ERROR: build failed.
endlocal & exit /B 1

:no_exe
echo ERROR: executable not found: %EXE_PATH%
endlocal & exit /B 1

:models_missing
echo ERROR: Missing ONNX model files required by runtime.
echo Expected:
echo   %PLATE_ONNX%
echo   %CHAR_ONNX%
echo Please run: python tools\export_onnx.py
endlocal & exit /B 1

:ensure_models
if not exist "%MODEL_DIR%" mkdir "%MODEL_DIR%"

if not exist "%PLATE_ONNX%" (
	if exist "%ALPR_DIR%\..\runs\detect\train\weights\last.onnx" (
		copy /Y "%ALPR_DIR%\..\runs\detect\train\weights\last.onnx" "%PLATE_ONNX%" >nul
	)
)

if not exist "%CHAR_ONNX%" (
	if exist "%ALPR_DIR%\..\runs\detect\train2\weights\last.onnx" (
		copy /Y "%ALPR_DIR%\..\runs\detect\train2\weights\last.onnx" "%CHAR_ONNX%" >nul
	)
)

if exist "%PLATE_ONNX%" if exist "%CHAR_ONNX%" exit /B 0

if exist "%ALPR_DIR%\tools\export_onnx.py" (
	echo ONNX models missing. Running export tool...
	python "%ALPR_DIR%\tools\export_onnx.py"
)

if exist "%PLATE_ONNX%" if exist "%CHAR_ONNX%" exit /B 0
exit /B 1

:dll_init_fail
echo.
echo ERROR: Process initialization failed (0xC0000142).
echo This is usually a DLL runtime issue.
echo.
echo Try these fixes in order:
echo   1) Install/repair Microsoft Visual C++ 2015-2022 Redistributable (x64):
echo      winget install Microsoft.VCRedist.2015+.x64
echo   2) Re-run this script in a new terminal.
echo   3) If still failing, try ONNX Runtime 1.17.1 package for maximum compatibility.
echo.
echo Quick check:
echo   dir "%BUILD_DIR%\Release\onnxruntime*.dll"
echo.
endlocal & exit /B -1073741502
