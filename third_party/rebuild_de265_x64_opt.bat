@echo off
rem Rebuild the x64 libde265 static library with a chosen optimization level.
rem usage: rebuild_de265_x64_opt.bat "O2"|"Od"|"O1"
rem cmake is taken from PATH when available, then the pip-installed copy,
rem then cmake.exe's default install location - no hard-coded user path.
setlocal
set ROOT=%~dp0
set OPT=%~1

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

set CMAKE=cmake
where cmake >nul 2>nul
if errorlevel 1 set CMAKE=C:\Python311\Lib\site-packages\cmake\data\bin\cmake.exe
if not exist "%CMAKE%" set CMAKE=%ProgramFiles%\CMake\bin\cmake.exe
if not exist "%CMAKE%" (
    echo cmake.exe not found in PATH or standard locations.
    exit /b 1
)

cd /d "%ROOT%"

"%CMAKE%" -S libde265-1.0.15 -B build-de265-fixed -G "Visual Studio 18 2026" -A x64 ^
  -DCMAKE_POLICY_VERSION_MINIMUM=3.5 ^
  -DCMAKE_POLICY_DEFAULT_CMP0091=NEW ^
  -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded ^
  -DCMAKE_C_FLAGS="/DWIN32 /D_WINDOWS /W3" ^
  -DCMAKE_CXX_FLAGS="/DWIN32 /D_WINDOWS /W3 /GR /EHsc" ^
  -DCMAKE_C_FLAGS_RELEASE="/%OPT% /DNDEBUG" ^
  -DCMAKE_CXX_FLAGS_RELEASE="/%OPT% /DNDEBUG" ^
  -DBUILD_SHARED_LIBS=OFF ^
  -DCMAKE_INSTALL_PREFIX="%ROOT%staging-de265"
if errorlevel 1 goto fail

"%CMAKE%" --build build-de265-fixed --config Release -- /m
if errorlevel 1 goto fail

"%CMAKE%" --build build-de265-fixed --config Release --target install
if errorlevel 1 goto fail

echo DONE /%OPT%
goto done

:fail
echo REBUILD FAILED
:done
endlocal
