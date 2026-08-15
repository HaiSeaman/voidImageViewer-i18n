@echo off
rem Build the decode harness for one arch and run it on one file.
rem usage: heif_run_one.bat x64|x86 <heic-file>
setlocal
set ROOT=%~dp0..
set ARCH=%~1
set FILE=%~2

if /i "%ARCH%"=="x64" (
  call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul
  set OUT=heif_dec_test_x64.exe
  set HLIBS=..\third_party\staging-heif\lib\heif.lib
  set DLIBS=..\third_party\staging-de265\lib\libde265.lib
) else (
  call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars32.bat" >nul
  set OUT=heif_dec_test_x86.exe
  set HLIBS=..\third_party\staging-heif-x86\lib\heif.lib
  set DLIBS=..\third_party\staging-de265-x86\libde265.lib
)

cd /d "%ROOT%\test_images"
cl /nologo /O2 /MT /I ..\third_party\staging-heif\include heif_dec_test.cpp %HLIBS% %DLIBS% /Fe:%OUT% /link /SUBSYSTEM:CONSOLE /MAP:heif_dec_test_%ARCH%.map
if errorlevel 1 goto fail

echo === %ARCH% run %FILE% ===
%OUT% %FILE% dec_%ARCH%.raw
echo === exit code: %ERRORLEVEL% ===
goto done

:fail
echo BUILD FAILED
:done
endlocal
