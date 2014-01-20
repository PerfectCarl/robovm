@echo off
SET BASE=%~dp0
SET COMPILER_JAR=%BASE%\lib\robovm-compiler.jar
SET ROBOVM_DEV_ROOT=%BASE%..\
echo COMPILER_JAR %COMPILER_JAR%
rem java -XX:+HeapDumpOnOutOfMemoryError -Xmx1024m -Xss1024k -jar %COMPILER_JAR% %*
java -XX:+HeapDumpOnOutOfMemoryError -jar %COMPILER_JAR% %*
 
goto success 

:failure
echo Error.

:success
echo Done