
@echo off
SET BASE=C:\Users\Evasion\Dropbox\docs\projects\robovm\robovm\vm\
SET BASE=%~dp0

rem echo BASE : %BASE%

SET OS=windows
SET ARCH=x86
SET B=debug


REM --- 
REM Make platform
REM --- 

rem SET MAKE_TYPE="MinGW Makefiles"
SET MAKE_TYPE="MSYS Makefiles"

REM --- 
REM Compiler : clang
REM --- 
REM SET CC=clang
rem TEMP
rem SET CC=llvm-gcc
rem SET CLANG_PATH=%MINGW_PATH%\clang
rem SET CLANG_PATH=%MINGW_PATH%\clang3.1
rem SET CMAKE_CC=%MINGW_PATH%\bin\%CC%.exe
rem SET PATH=%PATH%;%CLANG_PATH%\bin

REM --- 
REM Compiler : gcc
REM --- 
SET CC=


REM SET CMAKE_OPTS=
rem SET CMAKE_OPTS="-DLLVM_TARGETS_TO_BUILD=X86"

SET CONFIGURE_OPTS="--enable-optimized --enable-assertions --enable-targets=host-only"
SET CXX=%CC%
SET CMAKE_CC=%CC%

SET MSYS_PATH=%MINGW_PATH%\msys\1.0\bin
SET MAKE_BIN=%MSYS_PATH%\make.exe
SET PATH=%PATH%;%MSYS_PATH%


rem SET CMAKE_BIN=%CMAKE_BIN%  %CMAKE_OPTS%
