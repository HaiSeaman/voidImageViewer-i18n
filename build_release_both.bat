@echo off
rem Build both Release exes (x64 + Win32) without pausing.
rem Locates Visual Studio via vswhere instead of a hard-coded path.
setlocal

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

call "%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul

echo === x64 Release ===
msbuild vs2026\voidImageViewer.sln /t:Rebuild /p:Configuration=Release /p:Platform=x64 /m /v:m /nologo
if errorlevel 1 goto fail

echo === Win32 Release ===
msbuild vs2026\voidImageViewer.sln /t:Rebuild /p:Configuration=Release /p:Platform=Win32 /m /v:m /nologo
if errorlevel 1 goto fail

echo BUILD OK
dir /b vs2026\x64\Release\voidImageViewer.exe
dir /b vs2026\Release\voidImageViewer.exe
goto done

:fail
echo BUILD FAILED
exit /b 1

:done
endlocal
