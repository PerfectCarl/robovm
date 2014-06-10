@echo off

call build.cmd
echo.  
SET DEST=C:\Users\cran\Dropbox\docs\projects\github\robovm\carl\robovm-0.0.9

SET TAG=%OS%-%ARCH%-%B%_(%TOOL_NAME%)

copy %BASE%\target\binaries\windows\%ARCH%\*.* %DEST%\lib\vm\windows\%ARCH%
echo %TAG% > %DEST%\libversion.txt

echo -----------------------------------------------------
echo    Copied binaries to carl\robovm-0.0.9\lib\vm\windows\%ARCH% 
echo -----------------------------------------------------
echo.  
REM clang 
REM 03, no optimization
REM start:10h45 end:11h20 
REM -> 35min 

REM gcc 
REM 03, no optimization
REM start:11h24 end: 11h45
REM: cuts sound windows media player (after massive wupdate)
REM -> 21min

REM clang 
REM 03, no optimization
REM start:12h16 end:12h48 
REM -> 33min

rem call copyshare.cmd
