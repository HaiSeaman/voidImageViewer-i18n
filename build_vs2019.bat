@echo off
rem ===================================================
rem  voidImageViewer Portable Auto Build Script
rem ===================================================

set "VS_PATH="

rem Method 1: Check Developer Command Prompt Environment variable
if not "%VCINSTALLDIR%"=="" (
    if exist "%VCINSTALLDIR%\Auxiliary\Build\vcvarsall.bat" (
        set "VS_PATH=%VCINSTALLDIR%\Auxiliary\Build\vcvarsall.bat"
    )
)

rem Method 2: Use vswhere to detect Visual Studio installation path dynamically
if "%VS_PATH%"=="" (
    for /f "tokens=*" %%I in ('powershell -NoProfile -Command "try { $p = & '${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe' -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools -property installationPath; if ($p) { Join-Path $p 'VC\Auxiliary\Build\vcvarsall.bat' } } catch {}"') do (
        if exist "%%I" set "VS_PATH=%%I"
    )
)

rem Method 3: PowerShell Registry & Drive Deep Scan for vcvarsall.bat
if "%VS_PATH%"=="" (
    for /f "tokens=*" %%I in ('powershell -NoProfile -Command "Get-ChildItem 'C:\Program Files*','D:\*','E:\*','F:\*' -Filter 'vcvarsall.bat' -Recurse -ErrorAction SilentlyContinue | Select-Object -First 1 -ExpandProperty FullName"') do (
        if exist "%%I" set "VS_PATH=%%I"
    )
)

if "%VS_PATH%"=="" (
    echo [ERROR] Visual Studio C++ build environment not found.
    echo Please make sure Visual Studio C++ Workload is installed.
    echo.
    pause
    exit /b 1
)

echo [Found VS Toolchain] %VS_PATH%

echo.
echo [1/2] Building x64 Release Portable Version...
call "%VS_PATH%" x64 >nul
msbuild vs2026\voidImageViewer.sln /t:Rebuild /p:Configuration=Release /p:Platform=x64

if %ERRORLEVEL% equ 0 (
    echo [SUCCESS] x64 Portable Executable created: vs2026\x64\Release\voidImageViewer.exe
) else (
    echo [ERROR] x64 build failed.
)

echo.
echo [2/2] Building x86 (Win32) Release Portable Version...
call "%VS_PATH%" x86 >nul
msbuild vs2026\voidImageViewer.sln /t:Rebuild /p:Configuration=Release /p:Platform=Win32

if %ERRORLEVEL% equ 0 (
    echo [SUCCESS] x86 Portable Executable created: vs2026\Release\voidImageViewer.exe
) else (
    echo [ERROR] x86 build failed.
)

echo.
echo ===================================================
echo  Build finished! Check outputs in vs2026\ directory.
echo ===================================================
pause
