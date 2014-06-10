
@echo off
cls 
SET OLDPATH=%PATH%
call config.cmd

SET T=%OS%-%ARCH%
SET BUILD_TYPE=%B%
SET BASE_ROOT=%BASE%

echo.
echo -----------------------------------------------------
echo    Cleaning build for %OS%, %ARCH%, %BUILD_TYPE% ...
echo -----------------------------------------------------
echo.

del %BASE_ROOT%CMakeCache.txt
echo * Deleted cmake files: %BASE_ROOT%CMakeCache.txt
@del %BASE_ROOT%Makefile
echo * Deleted cmake files: %BASE_ROOT%Makefile
@rmdir /Q /S %BASE_ROOT%target\build\%T%-%B%
echo * Deleted : target
@rmdir /Q /S %BASE_ROOT%binaries\%OS%\%ARCH%\%B%
echo * Deleted : binaries
@rmdir /Q /S %BASE_ROOT%CMakeFiles
echo * Deleted cmake files : %BASE_ROOT%CMakeFiles

cd %BASE%
rem %MAKE_BIN% clean

echo.
echo -----------------------------------------------------
echo    Cmaking for %OS%, %ARCH%, %BUILD_TYPE% ...
echo -----------------------------------------------------
echo.
REM cmake -G "MinGW Makefiles"

SET CMAKE_BIN=cmake 
SET CMAKE_BIN=%CMAKE_BIN%  -DCMAKE_C_COMPILER=%CMAKE_CC% 
SET CMAKE_BIN=%CMAKE_BIN%  -DCMAKE_CXX_COMPILER=%CMAKE_CC% 
SET CMAKE_BIN=%CMAKE_BIN%  -DCMAKE_BUILD_TYPE=%BUILD_TYPE% 
SET CMAKE_BIN=%CMAKE_BIN%  -DOS=%OS% 
SET CMAKE_BIN=%CMAKE_BIN%  -DARCH=%ARCH% 
SET CMAKE_BIN=%CMAKE_BIN%  -DU_WINDOWS=YES
SET CMAKE_BIN=%CMAKE_BIN%  -DU_MINGW=YES
SET CMAKE_BIN=%CMAKE_BIN%  -D_WINSOCK2_H=YES
SET CMAKE_BIN=%CMAKE_BIN%  -DCMAKE_SYSTEM_NAME=%OS% 
SET CMAKE_BIN=%CMAKE_BIN%  %BASE% 
SET CMAKE_BIN=%CMAKE_BIN%  -G %MAKE_TYPE% 
REM generate files 

mkdir  %BASE%target\build\%T%-%B%
cd %BASE%target\build\%T%-%B%
REM %CMAKE_BIN% 
cd %BASE%
SET PATH=%OLDPATH%
echo.
echo -----------------------------------------------------
echo    Please, now run build.cmd
echo -----------------------------------------------------
echo.    