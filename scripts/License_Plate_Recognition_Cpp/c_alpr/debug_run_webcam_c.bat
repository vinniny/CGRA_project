@echo off
setlocal EnableExtensions DisableDelayedExpansion
cd /d "%~dp0"

echo [DBG] start
set "ALPR_DIR=%CD%"
set "BUILD_DIR=%ALPR_DIR%\build"
set "EXE_PATH=%BUILD_DIR%\Release\c_alpr.exe"
set "CONFIG_PATH=%ALPR_DIR%\configs\alpr_config.ini"
set "CMAKE_EXE="
set "WEBCAM_ARG=webcam"
if not "%~2"=="" set "WEBCAM_ARG=webcam:%~2"

echo [DBG] ALPR_DIR=%ALPR_DIR%
echo [DBG] BUILD_DIR=%BUILD_DIR%
echo [DBG] EXE_PATH=%EXE_PATH%
echo [DBG] CONFIG_PATH=%CONFIG_PATH%
echo [DBG] WEBCAM_ARG=%WEBCAM_ARG%

echo [DBG] checking cmake
where cmake
where ffmpeg
where ffplay

echo [DBG] arg1=%~1
set "ORT_ROOT=%~1"
if "%ORT_ROOT%"=="" set "ORT_ROOT=%ONNXRUNTIME_ROOT%"
if "%ORT_ROOT%"=="" if exist "%ALPR_DIR%\onnxruntime\include" set "ORT_ROOT=%ALPR_DIR%\onnxruntime"
if "%ORT_ROOT%"=="" if exist "%ALPR_DIR%\..\onnxruntime\include" set "ORT_ROOT=%ALPR_DIR%\..\onnxruntime"
echo [DBG] ORT_ROOT=%ORT_ROOT%

echo [DBG] done precheck
endlocal
