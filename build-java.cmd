@echo off
cls 

SET M2_HOME=C:\Users\Evasion\Apps\apache-maven-3.0.5
SET JAVA_HOME=C:\Program Files\Java\jdk1.7

echo.
echo ---------------------------------
echo    VERSION
echo ---------------------------------
echo.

rem call mvn --version

echo.
echo ---------------------------------
echo    Building maven...
echo ---------------------------------
echo.

call mvn install -DskipTests 

rem pause