rem Building executable C:\Users\cran\AppData\Local\Temp\robovm6640977305721361800.tmp\HelloWorld
rem g++ -o C:\Users\cran\AppData\Local\Temp\robovm6640977305721361800.tmp\HelloWorld 
rem -g -m32 @C:\Users\cran\AppData\Local\Temp\robovm6640977305721361800.tmp\objects 
rem -L C:\Users\cran\Dropbox\docs\projects\github\robovm\carl\robovm-0.0.9\lib\vm\windows\x86 
rem -lrobovm-bc -Wl,--whole-archive -lrobovm-rt -Wl,--no-whole-archive 
rem -lrobovm-core -lgc -lpthread -ldl -lm

@echo off
cls
SET OBJ_FILE=%1
SET OUTPUT=%2
SET LINK_BASE=%~dp0

call %LINK_BASE%\config.cmd

echo --------------------------------
Echo    Linking with %TOOL_NAME%...
echo --------------------------------
echo.

SET ARG=%TOOLCHAIN_PATH%\bin\g++
SET ARG=%ARG% -o .\%OUTPUT%.exe 
SET ARG=%ARG% -g -m32 
SET RVM_PATH=C:\Users\cran\Dropbox\docs\projects\github\robovm\robovm
SET ROBOVM_DEPS=%RVM_PATH%\..\android-windows-binaries\dependencies\windows
SET TOOL_DEPS=%TOOLS%

SET ARG=%ARG% -L %RVM_PATH%\..\carl\robovm-0.0.9\lib\vm\windows\x86
REM 
REM Common libs
REM 
SET ARG=%ARG% -L %ROBOVM_DEPS%\gc\lib
SET ARG=%ARG% -L %ROBOVM_DEPS%\dlfcn\lib
rem not using alien openssl SET ARG=%ARG% -L %ROBOVM_DEPS%\openssl\no-shared\lib

rem PTHREAD included 22
rem SET ARG=%ARG% -L %ROBOVM_DEPS%\pthread\lib\x86

SET ARG=%ARG% -Wl,-rpath=$ORIGIN -Wl,--gc-sections -lrobovm-bc -Wl,--whole-archive -lrobovm-rt 
SET ARG=%ARG% -Wl,--no-whole-archive -lrobovm-core -lgc 
rem PTHREAD included 22
rem SET ARG=%ARG% -lpthreadGC2 -ldl -lstdc++ -lssl -lcrypto -lws2_32 -lwsock32 -lgdi32 -lgcc -lgcc_s 
rem not using alien ssl SET ARG=%ARG% -lpthread -ldl -lstdc++ -lssl -lcrypto -lws2_32 -lwsock32 -lgdi32 -lgcc -lgcc_s 
SET ARG=%ARG% -lpthread -ldl -lstdc++ -lws2_32 -lwsock32 -lgdi32 -lgcc -lgcc_s 
SET ARG=%ARG%  -lshlwapi
SET ARG=%ARG% @%OBJ_FILE%
rem SET ARG=%ARG% -Wl,--entry=_mainXX

%ARG%

rem HelloWorld.exe -rvm:log=trace