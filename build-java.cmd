@echo off
cls 



echo.
echo ---------------------------------
echo    Building java...
echo ---------------------------------
echo.
echo Output : compiler/target 
echo.

call mvn -q install -DskipTests

rem pause