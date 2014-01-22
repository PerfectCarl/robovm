
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

rmdir /Q /S %BASE_ROOT%target\build\%T%
echo * Deleted : target

echo.
echo -----------------------------------------------------
echo    Cmaking for %OS%, %ARCH%, %BUILD_TYPE% ...
echo -----------------------------------------------------
echo.
REM cmake -G "MinGW Makefiles"

echo.
echo -----------------------------------------------------
echo    Please, run generate-cmake.cmd and then build.com
echo -----------------------------------------------------
echo.    
SET PATH=%OLDPATH%