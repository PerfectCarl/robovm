@echo off

call build.cmd
echo.  
SET DEST=C:\Users\cran\Dropbox\docs\projects\github\robovm\carl\robovm-0.0.8

SET TAG=%OS%-%ARCH%-%B%_(%TOOL_NAME%)

copy %BASE%\target\binaries\windows\%ARCH%\*.* %DEST%\lib\vm\windows\%ARCH%
echo %TAG% > %DEST%\libversion.txt

echo -----------------------------------------------------
echo    Copied binaries to carl\robovm-0.0.8\lib\vm\windows\%ARCH% 
echo -----------------------------------------------------
echo.  

call copyshare.cmd
