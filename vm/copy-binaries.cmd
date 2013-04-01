@echo off
cls 
call config.cmd
echo %BASE%target\build\%T%-%B%
echo  %BASE%\binaries
xcopy %BASE%target\binaries %BASE%\binaries /R /S