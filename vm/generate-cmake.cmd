
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
rem SET CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_C_COMPILER=%CMAKE_CC% 
rem SET CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_CXX_COMPILER=%CMAKE_CXX% 
REM SET CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% 
rem SET CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_INSTALL_PREFIX=%MINGW_PATH%/bin
rem SET CMAKE_ARGS=%CMAKE_ARGS% -DU_WINDOWS=YES
rem SET CMAKE_ARGS=%CMAKE_ARGS% -DU_MINGW=YES
rem SET CMAKE_ARGS=%CMAKE_ARGS% -D_WINSOCK2_H=YES
SET CMAKE_ARGS=%CMAKE_ARGS% -DOS=%OS% 
SET CMAKE_ARGS=%CMAKE_ARGS% -DARCH=%ARCH% 
SET CMAKE_ARGS=%CMAKE_ARGS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
SET CMAKE_ARGS=%CMAKE_ARGS%  -G %MAKE_TYPE% 

@mkdir %BASE%target\build\%T%-%B%
cd %BASE%target\build\%T%-%B%

cmake %CMAKE_ARGS% -Wno-dev "%BASE%"
SET PATH=%OLDPATH%
cd %BASE%