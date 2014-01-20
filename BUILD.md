Taken from https://github.com/robovm/robovm/wiki/Hacking-on-RoboVM


## Install mingw

http://sourceforge.net/projects/mingw/files/latest/download?source=files

It may takes a while

Pick a safe place (without space in the path. I chose `C:\Apps\Mingw`)
Add mingw to your environment variables 
MINGW_PATH=C:\Apps\Mingw
DONT PATH=%PATH%;%MINGW_PATH%\bin
DONT PATH=%PATH%;%MINGW_PATH%\msys\1.0\bin;

DONT MSYS

## Install cmake 

http://www.cmake.org/cmake/resources/software.html

http://www.cmake.org/files/v2.8/cmake-2.8.12.1-win32-x86.exe

## Install maven 3.0.5
robovm is not compatible with maven 3.1+, so be sure to install maven 3.0x
http://maven.apache.org/docs/3.0.5/release-notes.html

SET M2_HOME=%MAVEN_PATH%

SET JAVA_HOME=C:\Program Files\Java\jdk1.7

## Generate the make files 

Source code : <proj_path>/vm


## Install clang 

http://llvm.org/releases/download.html

http://llvm.org/releases/3.4/LLVM-3.4-win32.exe

CLANG_PATH=C:\Apps\llvm

## Additional files

Pthread for windows 2.9.1+

http://sourceware.org/pthreads-win32/
ftp://sourceware.org/pub/pthreads-win32/pthreads-w32-2-9-1-release.zip

In file included from C:/Users/cran/Dropbox/docs/projects/github/robovm/vm/core/src/../include/robovm.h:34:0,
                 from c:/Users/cran/Dropbox/docs/projects/github/robovm/vm/core/src/array.c:16:
C:/Users/cran/Dropbox/docs/projects/github/robovm/vm/core/src/../include/robovm/types.h:19:21: fatal error: pthread.h: N
o such file or directory
 #include <pthread.h>

 Unzip the content of the Prebuilt.2 folder of the zip into <proj_path>\vm\dependencies\windows\pthreads



## Run your first build

Fumble with config.cmd

The scripts are in the `robovm/vm` folder.
config.cmd sets environment variables.
build.cmd builds robovm
The compilation outputs are located in `XXXX`

cd `robovm\vm`
`generate_cmake.cmd`
`build.cmd`

That step will be pretty long as the initial build check your system configuration.

The subsequent builds will be faster