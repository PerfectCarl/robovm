# RoboVM for Windows

This is a windows build for [robovm](http://www.robovm.org) a **native java compiler** (and runtime). 
Thanks to robovm, you code your app in java but get a  executable :
  - your users won't need to install to the java runtime (JRE) to execute your app.
  - your application will start a lot faster.
  - using native bindings is easier.

Robovm actually supports linux, macosx and [ios] (http://www.robovm.org/docs.html#ios-example).

So I thought, **why not windows** ? 
Yeah, _why not_

# Uh ?
This project is a build for windows (32 bits for now) using [mingw] (http://en.wikipedia.org/wiki/MinGW).

# What's up ?
Well, I'm just getting started. 
Read : it compiles but doesn't work at the moment. 
The build system has been adapted but code had to be commented (mostly call to platform C calls : signals, threading, io etc.)

The goal is to uncomment the code and get it to work.

# Getting started 
How to install mingw, get the source and [build everything] (https://github.com/PerfectCarl/robovm/wiki/Getting-started).

If you're in a hurry, you can [download the binaries] (https://github.com/PerfectCarl/robovm/wiki/Download)

# Roadmap
As a rule, everything is tracked through issues and branches.
  1. Get [posix to work] (https://github.com/PerfectCarl/robovm/issues/4)
  2. Get [Networking and io] (https://github.com/PerfectCarl/robovm/issues/6)
  3. Fix [misc C calls] (https://github.com/PerfectCarl/robovm/issues/7) 
  4. Fix [assembly code] (https://github.com/PerfectCarl/robovm/issues/8)
  5. Pass [the test suite] (https://github.com/PerfectCarl/robovm/issues/9)
  6. Build a [setup program] (https://github.com/PerfectCarl/robovm/issues/10)
  7. [Support windows 64 bits] (https://github.com/PerfectCarl/robovm/issues/2)

# Contribute
For now, there is nothing to run, I'm afraid. But you have a look at the issues and weigh in.

Obviously, if you know about win32 assembly (4 short files to maintain), SEH (to handle platform errors), Posix compatibily on windows (without using resorting to cygwin) and mingw/clang compilation you can be my *new best friend*
