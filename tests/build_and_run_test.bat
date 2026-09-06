@echo off
rem Builds and runs the standalone unit tests (left_drag truth table,
rem playlist-delete shuffle regression).
rem Usage from the repo root: cmd /c tests\build_and_run_test.bat

set VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe
if not exist "%VSWHERE%" (
    echo vswhere.exe not found; is Visual Studio installed?
    exit /b 1
)
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set VS_PATH=%%i
if not defined VS_PATH (
    echo No Visual Studio with C++ tools found.
    exit /b 1
)
call "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b 1

cl /nologo /W4 /WX /Fe:%~dp0test_left_drag.exe "%~dp0test_left_drag.c"
if errorlevel 1 exit /b 1
"%~dp0test_left_drag.exe"
if errorlevel 1 exit /b 1

cl /nologo /W4 /WX /Fe:%~dp0test_playlist_delete.exe "%~dp0test_playlist_delete.c"
if errorlevel 1 exit /b 1
"%~dp0test_playlist_delete.exe"
if errorlevel 1 exit /b 1

rem the --show-bug run must FAIL (it reproduces the pre-fix behaviour).
"%~dp0test_playlist_delete.exe" --show-bug >nul 2>&1
if errorlevel 1 (echo pass show-bug regression fails as expected) else (echo FAIL show-bug should have failed & exit /b 1)

echo ALL TESTS PASSED
