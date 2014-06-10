
@echo off
SET BASE=%~dp0


REM 
REM Robovm build type
REM 

SET OS=windows
SET ARCH=x86
SET B=release

REM 
REM Use a 32bits JDK
REM 
rem JAVA_HOME=C:\Program Files (x86)\Java\jdk1.7
rem JAVA_HOME=C:\Program Files\Java\jdk1.7
rem SET PATH=%JAVA_HOME%\bin;%PATH%
SET JAVA_PATH="C:/Program Files/Java/jdk1.7"
SET JAVA_PATH=
REM Using mingw64: do not use for now. Robovm not 64 bits ready
REM SET PATH=%PATH%;%BASE%\dependencies\mingw64\bin
REM Using mingw32
rem SET TOOLCHAIN_PATH=%BASE%\dependencies\mingw32

rem SET PATH=%PATH%;%TOOLCHAIN_PATH%\bin

call ..\vm\windows\config-x86-mingw-20.cmd
