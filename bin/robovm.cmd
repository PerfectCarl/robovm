@echo off
SET BASE=%~dp0
SET COMPILER_JAR=%BASE%lib\robovm-compiler.jar
SET ROBOVM_DEV_ROOT=%BASE%..\
if exist %COMPILER_JAR% (
    echo ONE
    SET ROBOVM_HOME=%BASE%

) else (
    echo XXX
    if defined ROBOVM_DEV_ROOT (
	echo TWO %ROBOVM_DEV_ROOT%compiler\target\robovm-compiler-*.jar
	FOR %%F IN (%ROBOVM_DEV_ROOT%compiler\target\robovm-compiler-*.jar) DO (
	 set filename=%%F
	 echo ccc %%F
	 goto found
	)
	:found
	echo Found %filename%
        SET COMPILER_JAR=%filename%
    )
)
if not defined COMPILER_JAR (
  echo COMPILER_JAR empty
  goto failure
)
if not exist %COMPILER_JAR% (
  echo "robovm-compiler.jar not found"
  goto failure 
)
echo THREE : %COMPILER_JAR%

rem java -XX:+HeapDumpOnOutOfMemoryError -Xmx1024m -Xss1024k -jar %COMPILER_JAR% %*
java -XX:+HeapDumpOnOutOfMemoryError -jar %COMPILER_JAR% %*
 
goto success 

:failure
echo Error.

:success
echo Done