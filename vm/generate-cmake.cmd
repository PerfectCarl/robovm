
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
echo -----------------------------------------------------
echo.    

SET CMAKE_ARGS=
SET CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_C_COMPILER=%TOOLCHAIN_BIN%/%CMAKE_C_COMPILER%.exe 
SET CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_CXX_COMPILER=%TOOLCHAIN_BIN%/%CMAKE_CXX_COMPILER%.exe 
SET CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_MAKE_PROGRAM=%TOOLCHAIN_BIN%/%CMAKE_MAKE%.exe

REM SET CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% 
rem SET CMAKE_ARGS=%CMAKE_ARGS% -DU_WINDOWS=YES
rem SET CMAKE_ARGS=%CMAKE_ARGS% -DU_MINGW=YES
rem SET CMAKE_ARGS=%CMAKE_ARGS% -D_WINSOCK2_H=YES
rem libraries
SET CMAKE_ARGS=%CMAKE_ARGS% -DUSE_EXTERNAL_PTHREAD=%USE_EXTERNAL_PTHREAD% 
rem targets
SET CMAKE_ARGS=%CMAKE_ARGS% -DOS=%OS% 
SET CMAKE_ARGS=%CMAKE_ARGS% -DARCH=%ARCH% 
rem make type/environment
SET CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
SET CMAKE_ARGS=%CMAKE_ARGS%  -G %MAKE_TYPE% 

@mkdir %BASE%target\build\%T%-%B%
cd %BASE%target\build\%T%-%B%

cmake %CMAKE_ARGS% -Wno-dev "%BASE%"
SET PATH=%OLDPATH%
cd %BASE%