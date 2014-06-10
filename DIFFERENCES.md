This document provides an overview of the changes that have been made to Robovm to build on Windows.

# For the end user

Fondamentally, there is no big changes for the end user apart the fact that Robovm now relies on an updated set of components.
Which should be transparent to the end user.

The set up on Windows has the following steps:

   - download `Robovm` (that now includes Windows binaries, Windows runtime dependencies and robovm-llvm runtime dependencies)
   - install `mingw` (without msys)
   - choose a way to notify Robovm about the mingw installation path. (There is no fixed installation path on Windows). It may be by setting a environment variable or passing an argument to robovm command line
   - build their application
   - package their application including the runtime dependencies (dll)

## Updated components 
<table>
    <tr>
        <th></th>
        <th>Robovm 0.0.13</th>
        <th>New branch</th>
    </tr>
    <tr>
        <th>Android</th>
        <td>4.1.1_r3</td>
        <td>4.4_r0.7</td>
    </tr>
    <tr>
        <th>icu4c</th>
        <td>4.8.0.0</td>
        <td>51.1.0.0</td>
    </tr>
    <tr>
        <th>openssl</th>
        <td>1.0.1c</td>
        <td>1.0.1e</td>
    </tr>
    <tr>
        <th>javasqlite</th>
        <td>20100727</td>
        <td>20100727</td>
    </tr>
    <tr>
        <th>sqlite</th>
        <td>3071100</td>
        <td>3071100</td>
    </tr>
    <tr>
        <th>zlib</th>
        <td>1.2.6</td>
        <td>1.2.8</td>
    </tr>
    <tr>
        <th>expat</th>
        <td>2.0.1</td>
        <td>2.1.0</td>
    </tr>
    <tr>
        <th>fdlibm</th>
        <td>5.3</td>
        <td>5.3</td>
    </tr>
</table>


# For the robovm maintainer

This part is about building and maintaining Robovm on a Windows box (this does not cover cross compilation for Windows).

## Changes to robovm-compiler

GCC linker works differently on Windows so the `robovm compiler` must be adapted to work in [two phases](https://github.com/robovm/robovm/pull/297).

Once the java classes have been compiled to .o files, `robovm compiler` calls `gcc` to link the files and create the executable. 
Not surprisingly, the linking process requires is specific on Windows requiring different options and different libraries. 
At the moment the modifications to the linking process are implemented in the current code logic.

>In the future, it would more convenient to have a pluggable linking sytem to ease the support of many platforms (IOS, Mac, Windows and Windows cross compilation).

## Dependencies
Windows has no package manager for mingw compiled libraries.
It means that each dependency not provided by mingw has to be downloaded and compiled separately.

Sometimes, it's straightforward as the library uses cmake. 
Some other times, the library may use shell/perl scripts that would require msys (msys is a lightweight shell environment for windows).

The code for those libraries is not included in robovm repository.

>In the future it may be a good idea to add the code to those libraries in robovm repository

The following dependencies have been added :
  - dlfcn
  - gc (cmake fails to download and patch imvai gc on Windows)
  - pthead 
  - a custom version of openssl is used (not the one in the Robovm repository) 

The Windows specific dependencies can [be found here](https://github.com/PerfectCarl/robovm-windows-binaries/tree/master/dependencies).  
### Openssl
[Android's openssl](https://android.googlesource.com/platform/external/openssl/+/android-4.4_r0.7) can't be compiled on Windows (see [here](https://groups.google.com/d/msg/robovm/GGTubkAT2vg/JIc6I5CY6wQJ)).

A quick inspection showed that the failing code is very similar to the official version.
It feels like the problem is related to a make/flag issue.

A quick solution that  I found is to use the official version and re apply some of Android's patches.
The updated version is located in [robovm-windows-openssl](https://github.com/PerfectCarl/robovm-windows-openssl). The [readme](https://github.com/PerfectCarl/robovm-windows-openssl/README.md) describes the changes that has been made.

The openssl is built according to [this tutorial](https://qt-project.org/wiki/Compiling-OpenSSL-with-MinGW):
```
./Configure --prefix=$PWD/dist no-idea no-mdc2 no-rc5 no-shared mingw
make depend && make && make install
```

> This configuration looks different from Robovm openssl compilation flags.
> OPENSSL_THREADS _REENTRANT L_ENDIAN OPENSSL_NO_CAMELLIA OPENSSL_NO_CAPIENG OPENSSL_NO_CAST OPENSSL_NO_CMS OPENSSL_NO_GMP OPENSSL_NO_IDEA OPENSSL_NO_JPAKE OPENSSL_NO_MD2 OPENSSL_NO_MDC2 OPENSSL_NO_RC5 OPENSSL_NO_SHA0 OPENSSL_NO_RFC3779 OPENSSL_NO_SEED OPENSSL_NO_STORE OPENSSL_NO_WHIRLPOOL OPENSSL_NO_STATIC_ENGINE OPENSSL_NO_GOSTOPENSSL_NO_DTLS1 OPENSSL_NO_RSAX OPENSSL_NO_RDRAND 

> the new 4.4-r0.7 flags: MONOLITH OPENSSL_NO_EC_NISTP_64_GCC_128 OPENSSL_NO_HEARTBEATS OPENSSL_NO_SCTP TERMIO 

## New components  
The folder `crypto` has been added to `robovm/vm/rt/android`: the cryptographic code has changed with Android 4.4_r07.

## Libcore and luni

We used [a new version of libcore](https://github.com/PerfectCarl/avian-pack.android.libcore) which is derived from [libcore64]() a 64bits Windows compliant version of libcore.

`libcore64` is based on Android 4.4_r07 and uses Android.mk build system.
Our branch ported it to cmake.

While numerous functions have been port to Windows, there is still work left to do.
At the moment, some code is still commented. The list of the most important issues [is here](ISSUES.md). 

## Runtime dependencies

Because we are using GPL compiler and components, some components have to be shipped as dll and thus cannot be statically linked.

It means that :
   - librobovm-llvm.dll needs to find its runtime dependencies.
   - any application needs its runtime dependencies (different from the librobovm-llvm.dll dependencies)

The Windows specific dependencies [can be found here](https://github.com/PerfectCarl/robovm-windows-binaries/tree/master/runtime)
## Compilation
At the moment, robovm on windows must be built with gcc (see this [issue]()).

Also the following components must be compiled with `fpermissive` flag: 
  - crypto
  - libnativehelper
  - libcore

As the external components have been updated, so have the compilation flags in the cmake files
