
@echo off
SET BASE=%~dp0

SET OS=windows
SET ARCH=x86
SET B=debug


rem SET MAKE_TYPE="MSYS Makefiles"

REM --- 
REM Compiler : clang
REM --- 
REM SET CC=clang
rem SET CC=mingw-gcc
rem TEMP
rem SET CC=llvm-gcc
rem SET CLANG_PATH=%MINGW_PATH%\clang
rem SET CLANG_PATH=%MINGW_PATH%\clang3.1
rem SET CMAKE_CC=%MINGW_PATH%\bin\%CC%.exe
rem SET PATH=%PATH%;%CLANG_PATH%\bin
rem SET CMAKE_CXX=%CMAKE_CC%



REM SET CMAKE_OPTS=
rem SET CMAKE_OPTS="-DLLVM_TARGETS_TO_BUILD=X86"

SET CONFIGURE_OPTS="--enable-optimized --enable-assertions --enable-targets=host-only"
rem SET CXX=%CC%
rem SET CMAKE_CC=%CC%
SET PATH=%PATH%;%MINGW_PATH%\bin
rem SET MSYS_PATH=%MINGW_PATH%\msys\1.0\bin
rem SET MAKE_BIN=%MSYS_PATH%\make.exe
rem SET PATH=%PATH%;%MSYS_PATH%

SET DEPS_BASE=%BASE%\dependencies\windows

REM PTHREADS
SET C_INCLUDE_PATH=%C_INCLUDE_PATH%;%DEPS_BASE%\pthreads\include
SET CPLUS_INCLUDE_PATH=%CPLUS_INCLUDE_PATH%;%DEPS_BASE%\pthreads\include
SET LD_LIBRARY_PATH=%LD_LIBRARY_PATH%;%DEPS_BASE%\pthreads\lib

rem SET CMAKE_BIN=%CMAKE_BIN%  %CMAKE_OPTS%

call config-make-msys.cmd
