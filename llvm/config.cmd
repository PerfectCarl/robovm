
@echo off
SET BASE=%~dp0

SET OS=windows
SET ARCH=x86
SET B=Release

SET PATH=%PATH%;%BASE%\dependencies\mingw32\bin

call config-make-msys.cmd
