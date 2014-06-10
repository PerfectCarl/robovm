
REM NOT WORKING

REM  mingw-w64+ mingw-w32
REM  llvm 3.4.1
REM  clang
REM  pthread included

SET MAKE_TYPE="MinGW Makefiles"
SET TOOL_NAME=21-mingw-32
SET TOOL_PATH=21-mingw64-32
SET ARCH=x86

REM 
REM Toolchain
REM 
SET CMAKE_C_COMPILER=clang
SET CMAKE_CXX_COMPILER=clang
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
SET LLVM_DIR=C:\Users\cran\Dropbox\docs\projects\github\temp\llvm-dist.2
