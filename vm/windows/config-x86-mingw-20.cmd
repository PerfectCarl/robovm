
REM mingw-w64 4.9
REM  - 32 bits 
REM  - win32 threads
REM  - pthread included
REM  - sljl
REM Downloaded http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/4.9.0/threads-win32/sjlj/i686-4.9.0-release-win32-sjlj-rt_v3-rev2.7z/download

SET MAKE_TYPE="MinGW Makefiles"
SET TOOL_NAME=20-mingw-32
SET TOOL_PATH=20-mingw64-32
SET ARCH=x86

REM 
REM Toolchain
REM 
SET CMAKE_C_COMPILER=gcc
SET CMAKE_CXX_COMPILER=g++
SET CMAKE_MAKE=mingw32-make

SET TOOLCHAIN_PATH=C:/Apps/local/%TOOL_PATH%
SET TOOLCHAIN_BIN=%TOOLCHAIN_PATH%/bin

SET MAKE_BIN=%TOOLCHAIN_BIN%\%CMAKE_MAKE%.exe

REM 
REM Libraries
REM Not used: included in cmakefile

REM SET C_INCLUDE_PATH=
REM SET CPLUS_INCLUDE_PATH=
REM SET LD_LIBRARY_PATH=

REM PTHREADS not included in mingw distribution
rem SET USE_EXTERNAL_PTHREAD=TRUE
REM SET LIB=pthread
REM SET C_INCLUDE_PATH=%C_INCLUDE_PATH%;%DEPS_BASE%\%LIB%\include
REM SET CPLUS_INCLUDE_PATH=%CPLUS_INCLUDE_PATH%;%DEPS_BASE%\%LIB%\include
REM SET LD_LIBRARY_PATH=%LD_LIBRARY_PATH%;%DEPS_BASE%\%LIB%\lib

REM For llvm
SET LLVM_DIR=C:\Users\cran\Dropbox\docs\projects\github\robovm\temp\llvm-dist.2
