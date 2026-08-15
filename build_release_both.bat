@echo off
rem Build both Release exes (x64 + Win32) without pausing.
setlocal

call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul

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
