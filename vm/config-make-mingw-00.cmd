SET MAKE_TYPE="MinGW Makefiles"

SET TOOL_NAME=0-mingw32

REM 
REM Toolchain
REM 

SET LLVM_DEPS=C:\Users\cran\Dropbox\docs\projects\github\robovm\llvm\dependencies
SET TOOLCHAIN_PATH=%LLVM_DEPS%\%TOOL_NAME%

SET PATH=%PATH%;%TOOLCHAIN_PATH%\bin
SET MAKE_BIN=%TOOLCHAIN_PATH%\bin\make.exe

REM 
REM Libraries
REM 

REM PTHREADS using mingw32
SET C_INCLUDE_PATH=%C_INCLUDE_PATH%;%DEPS_BASE%\pthreads\include
SET CPLUS_INCLUDE_PATH=%CPLUS_INCLUDE_PATH%;%DEPS_BASE%\pthreads\include
SET LD_LIBRARY_PATH=%LD_LIBRARY_PATH%;%DEPS_BASE%\pthreads\lib
