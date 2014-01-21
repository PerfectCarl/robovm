
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
SET PATH=%PATH%;%MSYS_PATH%

cd %BASE%target\build\%T%
"%MAKE_BIN%" install/strip
SET PATH=%OLDPATH%

cd %BASE%