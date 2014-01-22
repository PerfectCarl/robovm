SET MAKE_TYPE="MinGW Makefiles"

SET LLVM_DEPS=C:\Users\cran\Dropbox\docs\projects\github\robovm\llvm\dependencies
SET TOOLCHAIN_PATH=%LLVM_DEPS%\mingw32

SET PATH=%PATH%;%TOOLCHAIN_PATH%\bin
rem SET CMAKE_MAKE_PROGRAM=%TOOLCHAIN_PATH%\bin\
SET MAKE_BIN=%TOOLCHAIN_PATH%\bin\make.exe
REM Fail with error "-DGCC_HIDDEN=__attribute__: No such file or directory"