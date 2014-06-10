## Prerequisites
Mingw+Msys
Get the [openssl source 1.0.1e](http://www.openssl.org/source/openssl-1.0.1e.tar.gz)
Get the patches files from https://android.googlesource.com/platform/external/openssl/+/android-4.4.3_r1.1/patches/
Copy the following files to the openssl folder:
   - jsse.patch
   - channelid.patch

## Building 

Generate dlls
```
C:\Apps\Mingw\msys\1.0\msys.bat
cd /c/users/cran/Dropbox/docs/projects/github/robovm/temp/openssl-1.0.1e
export PATH=/C/Apps/Mingw/bin:$PATH

patch -p1 -i channelid.patch
patch -p1 -i alpn.patch
patch -p1 -i jsse.patch
patch -p1 -i handshake_cutthrough.patch

./Configure --prefix=$PWD/dist no-idea no-mdc2 no-rc5 shared mingw
make depend && make && make install
```

Generate static libraries
```
C:\Apps\Mingw\msys\1.0\msys.bat
cd /c/users/cran/Dropbox/docs/projects/github/robovm/temp/openssl-1.0.1e
export PATH=/C/Apps/Mingw/bin:$PATH

patch -p1 -i channelid.patch
patch -p1 -i alpn.patch
patch -p1 -i jsse.patch
patch -p1 -i handshake_cutthrough.patch

./Configure --prefix=$PWD/dist no-idea no-mdc2 no-rc5 no-shared mingw
make depend && make && make install
```

The result are in the `dist` folder