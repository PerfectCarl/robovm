
@echo off
cls 
SET OLDPATH=%PATH%
call config.cmd


SET T=%OS%-%ARCH%
SET BUILD_TYPE=%B%
echo.
echo -----------------------------------------------------
echo    Building for %OS%, %ARCH%, %BUILD_TYPE% ...
echo -----------------------------------------------------
echo.    
echo Output %BASE%\target\binaries\%OS%\%ARCH%

SET MSYS_PATH=%MINGW_PATH%\msys\1.0\bin
rem SET MAKE_BIN=%MSYS_PATH%\make.exe
SET PATH=%PATH%;%MSYS_PATH%

rem echo base dir : %BASE%\target\build\%T%-%B%
cd %BASE%target\build\%T%-%B%
rem %CMAKE_BIN% 
"%MAKE_BIN%" install
rem make install
SET PATH=%OLDPATH%

cd %BASE%