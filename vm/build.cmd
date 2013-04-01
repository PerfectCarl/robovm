
@echo off
cls 
call config.cmd


SET T=%OS%-%ARCH%
SET BUILD_TYPE=%B%
echo.
echo -----------------------------------------------------
echo    Building for %OS%, %ARCH%, %BUILD_TYPE% ...
echo -----------------------------------------------------
echo.    

rem echo base dir : %BASE%\target\build\%T%-%B%
cd %BASE%\target\build\%T%-%B%
rem %CMAKE_BIN% 
rem "%MAKE_BIN%" install
make install

cd %BASE%