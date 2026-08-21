@echo off
rem Builds and runs the standalone unit test for src/left_drag.h.
rem Usage from the repo root: cmd /c tests\build_and_run_test.bat

call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b 1

cl /nologo /W4 /WX /Fe:%~dp0test_left_drag.exe "%~dp0test_left_drag.c"
if errorlevel 1 exit /b 1

"%~dp0test_left_drag.exe"
