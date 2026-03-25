# Webcam-only C ALPR - Cleanup Script
# Removes non-webcam related files to reduce project footprint

$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
Write-Host "Cleaning up $projectRoot for webcam-only deployment..." -ForegroundColor Cyan

# Folders to remove
$foldersToRemove = @(
    "$projectRoot\tools",
    "$projectRoot\tests",
    "$projectRoot\test_images",
    "$projectRoot\build"
)

foreach ($folder in $foldersToRemove) {
    if (Test-Path $folder) {
        Write-Host "Removing folder: $folder" -ForegroundColor Yellow
        Remove-Item -Recurse -Force $folder
    }
}

# Files to remove
$filesToRemove = @(
    "$projectRoot\run_e2e_test.bat",
    "$projectRoot\run_e2e_test.sh",
    "$projectRoot\debug_run_webcam_c.bat",
    "$projectRoot\src\image_io.c",
    "$projectRoot\src\batch_process.c",
    "$projectRoot\src\result_dump.c",
    "$projectRoot\include\image_io.h",
    "$projectRoot\include\batch_process.h",
    "$projectRoot\include\result_dump.h",
    "$projectRoot\docs\ARCHITECTURE.md",
    "$projectRoot\docs\MIGRATION_CHECKLIST.md",
    "$projectRoot\docs\PLAN_AUDIT_TEMPLATE.md"
)

foreach ($file in $filesToRemove) {
    if (Test-Path $file) {
        Write-Host "Removing file: $file" -ForegroundColor Yellow
        Remove-Item -Force $file
    }
}

Write-Host "`n✓ Cleanup complete!" -ForegroundColor Green
Write-Host "`nRemaining essential structure for webcam detection:" -ForegroundColor Cyan
Write-Host "  ✓ src/ - Core C implementation"
Write-Host "  ✓ include/ - Headers"
Write-Host "  ✓ models/ - ONNX models"
Write-Host "  ✓ configs/ - Runtime config"
Write-Host "  ✓ run_webcam_c.bat - Main launcher"
Write-Host "  ✓ list_webcams.bat - Enumeration tool"
Write-Host "`nNext: run 'c_alpr\run_webcam_c.bat' to build and test."
