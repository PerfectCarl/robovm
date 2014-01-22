@echo off

call build.cmd
copy C:\Users\cran\Dropbox\docs\projects\github\robovm\vm\target\binaries\windows\x86\*.* C:\Users\cran\Dropbox\docs\projects\github\robovm\carl\robovm-0.0.8\lib\vm\windows\x86

echo Copied binaries to carl\robovm-0.0.8\lib\vm\windows\x86 
