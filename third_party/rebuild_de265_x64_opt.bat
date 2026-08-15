@echo off
rem Rebuild the x64 libde265 static library with a chosen optimization level.
rem usage: rebuild_de265_x64_opt.bat "O2"|"Od"|"O1"
setlocal
set ROOT=%~dp0
set OPT=%~1
set CMAKE=C:\Python311\Lib\site-packages\cmake\data\bin\cmake.exe

call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul

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
