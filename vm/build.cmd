
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
echo    Using    %TOOL_NAME%
echo    Output   %BASE%\target\binaries\%OS%\%ARCH%
echo -----------------------------------------------------
echo.    

rem SET MSYS_PATH=%MINGW_PATH%\msys\1.0\bin
rem SET MAKE_BIN=%MSYS_PATH%\make.exe
rem SET PATH=%PATH%;%MSYS_PATH%

rem echo base dir : %BASE%\target\build\%T%-%B%
cd %BASE%target\build\%T%-%B%
rem %CMAKE_BIN% 
"%MAKE_BIN%" -j 4 install
rem make install
SET PATH=%OLDPATH%

cd %BASE%