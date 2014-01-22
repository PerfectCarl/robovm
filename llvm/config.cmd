
@echo off
SET BASE=%~dp0

SET OS=windows
SET ARCH=x86
SET B=Release

REM Using mingw64: do not use for now. Robovm not 64 bits ready
REM SET PATH=%PATH%;%BASE%\dependencies\mingw64\bin
REM Using mingw32
SET TOOLCHAIN_PATH=%BASE%\dependencies\mingw32

SET PATH=%PATH%;%TOOLCHAIN_PATH%\bin

call config-make-mingw.cmd
