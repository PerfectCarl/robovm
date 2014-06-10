REM  mingw-w64 SJLJ
REM  lib: llvm3.2
REM  clang: 3.2
REM  gcc

REM clang version 3.3 (tags/RELEASE_33/final)
REM Target: i686-w64-mingw32
REM Thread model: posix

SET MAKE_TYPE="MinGW Makefiles"
SET TOOL_NAME=11-mingw64-32
SET ARCH=x86

REM 
REM Toolchain
REM 

SET LLVM_DEPS=C:\Apps\local
SET TOOLCHAIN_PATH=%LLVM_DEPS%\%TOOL_NAME%

SET PATH=%PATH%;%TOOLCHAIN_PATH%\bin
SET MAKE_BIN=%TOOLCHAIN_PATH%\bin\mingw32-make.exe

REM 
REM Libraries
REM 

REM PTHREADS using mingw32
rem SET C_INCLUDE_PATH=%C_INCLUDE_PATH%;%DEPS_BASE%\pthreads\include
rem SET CPLUS_INCLUDE_PATH=%CPLUS_INCLUDE_PATH%;%DEPS_BASE%\pthreads\include
rem SET LD_LIBRARY_PATH=%LD_LIBRARY_PATH%;%DEPS_BASE%\pthreads\lib
