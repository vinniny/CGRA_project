@echo off
REM List DirectShow webcam devices on Windows via ffmpeg.

setlocal

where ffmpeg >nul 2>&1
if errorlevel 1 (
    echo ERROR: ffmpeg not found in PATH.
    echo Install with: winget install Gyan.FFmpeg
    exit /B 1
)

echo ========================================
echo Available DirectShow Video Devices
echo ========================================
ffmpeg -hide_banner -list_devices true -f dshow -i dummy 2>&1
echo.
echo Note: "Error opening input file dummy" is expected in this listing mode.
echo.
echo ========================================
echo Legacy VFW Device Probe
echo ========================================
echo Trying vfw index 0...
ffmpeg -hide_banner -f vfwcap -i 0 -t 1 -f null NUL 2>&1 | findstr /I /C:"Could not" /C:"error" /C:"frame="
echo Trying vfw index 1...
ffmpeg -hide_banner -f vfwcap -i 1 -t 1 -f null NUL 2>&1 | findstr /I /C:"Could not" /C:"error" /C:"frame="
echo Trying vfw index 2...
ffmpeg -hide_banner -f vfwcap -i 2 -t 1 -f null NUL 2>&1 | findstr /I /C:"Could not" /C:"error" /C:"frame="
echo.
echo Tip:
echo - If only OBS Virtual Camera appears above, physical webcam is not exposed to ffmpeg dshow.
echo - Close OBS/Teams/Zoom, unplug-plug webcam, then run this script again.
echo - Check Windows Camera privacy settings and allow desktop apps.
echo - Run C app with: build\Release\c_alpr.exe configs\alpr_config.ini webcam:0
echo - If needed try: build\Release\c_alpr.exe configs\alpr_config.ini webcam:1
echo ========================================

endlocal
