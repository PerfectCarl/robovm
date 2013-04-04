# RoboVM for Windows

This is a windows build for [robovm](http://www.robovm.org) a **native java compiler** (and runtime). 

Main benefits of robovm  :
  - no java runtime (JRE) needed to execute your app
  - your application starts faster
  - using native bindings is easier
  - robovm runtime is published [under business friendly licenses] (http://www.robovm.org/license.html).  
_No_, there is **no GPLed code involved** (in the runtime).   
_Yes_, you will be able to publish your application to the **mac app store** and the **iphone app store**.

Robovm actually supports linux, macosx and [ios] (http://www.robovm.org/docs.html#ios-example).

So I thought, **why not windows** ?   

# The goal
This project is a build for windows (32 bits for now, [64 bits is planned] (https://github.com/PerfectCarl/robovm/issues/2)) using [mingw] (http://en.wikipedia.org/wiki/MinGW).
using gcc and/or clang 3.1.

# What's up ?
Well, I'm just getting started.   
Read : the code compiles on windows but doesn't work at the moment. 

The build system has been adapted but some code had to be commented out (mostly call to platform C calls : signals, threading, io etc.)

The commented code is marked with `CARL`.

Pretty much like that :
````c
static jboolean blockSigPipe() {
    sigset_t set;
    sigemptyset(&set);
    // CARL : posix ? pipe ? 
#ifndef WINDOWS  
	sigaddset(&set, SIGPIPE);
#endif
    if (sigprocmask(SIG_BLOCK, &set, NULL) != 0) {
...
````

Or like this :
````c
//CARL posix
#ifndef WINDOWS
#include <pwd.h>
#include <sys/utsname.h>
#endif 
````
The goal is to uncomment the code and get a complete user [friendly setup program] (http://www.jrsoftware.org/isinfo.php#features).

# Getting started 
How to install mingw, get the source and [build everything] (https://github.com/PerfectCarl/robovm/wiki/Getting-started).

If you're in a hurry, you can [download the binaries] (https://github.com/PerfectCarl/robovm/wiki/Download)

# Roadmap
As a rule, everything is tracked through issues : 
  1. Find [posix equivalents] (https://github.com/PerfectCarl/robovm/issues/4)
  2. Have [Networking and io] working (https://github.com/PerfectCarl/robovm/issues/6)
  3. Fix [misc C calls] (https://github.com/PerfectCarl/robovm/issues/7) 
  4. Review [assembly code] (https://github.com/PerfectCarl/robovm/issues/8)
  5. Pass [the test suites] (https://github.com/PerfectCarl/robovm/issues/9)
  6. Build a [setup program] (https://github.com/PerfectCarl/robovm/issues/10)
  7. [Support windows 64 bits] (https://github.com/PerfectCarl/robovm/issues/2)

# Contribute
For now, there is nothing to run, I'm afraid.  
But you can have a look at the [issues] (https://github.com/PerfectCarl/robovm/issues) : your feedback is welcomed.

Obviously, if you know about win32 assembly (4 short files to maintain), SEH (to handle platform errors), Posix compatability on windows (without using resorting to use cygwin) and mingw/clang compilation you can be my *new best friend*.

In any case, don't hesitate to drop by the official [robovm google group] (https://groups.google.com/forum/?fromgroups=#!forum/robovm).
