@echo off
cls 



echo.
echo ---------------------------------
echo    Building java...
echo ---------------------------------
echo.

call mvn -q  install -DskipTests  -Dmaven.javadoc.skip=true

rem pause