@echo off

call config.cmd

SET DEST_NAME=share\%OS%-%ARCH%-%B%_(%TOOL_NAME%)
SET DEST=C:\Users\cran\Dropbox\docs\projects\github\robovm\%DEST_NAME%\

mkdir %DEST%
copy %BASE%\target\binaries\windows\%ARCH%\*.* %DEST%

echo -----------------------------------------------------
echo    Copied binaries to %DEST_NAME%
echo -----------------------------------------------------
echo.  