
@echo off
SET BASE=%~dp0

REM 
REM Robovm build type
REM 

SET OS=windows
SET ARCH=x86
SET B=release

REM 
REM Use a 32bits JDK
REM 
SET JAVA_HOME=C:\Program Files (x86)\Java\jdk1.7
SET PATH=%JAVA_HOME%\bin;%PATH%


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

SET DEPS_BASE=%BASE%\dependencies\windows

REM dlfcn
SET C_INCLUDE_PATH=%C_INCLUDE_PATH%;%DEPS_BASE%\dlfcn\include
SET CPLUS_INCLUDE_PATH=%CPLUS_INCLUDE_PATH%;%DEPS_BASE%\dlfcn\include
SET LD_LIBRARY_PATH=%LD_LIBRARY_PATH%;%DEPS_BASE%\dlfcn\lib

REM libgc
SET C_INCLUDE_PATH=%C_INCLUDE_PATH%;%DEPS_BASE%\libgc\include
SET CPLUS_INCLUDE_PATH=%CPLUS_INCLUDE_PATH%;%DEPS_BASE%\libgc\include
SET LD_LIBRARY_PATH=%LD_LIBRARY_PATH%;%DEPS_BASE%\libgc\lib

call config-make-mingw-01.cmd
REM call config-make-mingw64-10.cmd
