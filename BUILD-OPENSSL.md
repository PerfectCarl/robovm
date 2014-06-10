## Prerequisites
  - install Mingw in `your.mingw.path`
  - install Msys in `your.msys.path`
  - Download the openssl source
 ```
	git clone https://github.com/PerfectCarl/robovm-windows-openssl.git
 ```
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
> [your.msys.path]\msys.bat
Example: C:\Apps\Mingw\msys\1.0\msys.bat
> cd robovm-windows-openssl
> export PATH=/[your.mingw.path]/bin:$PATH
Example: export PATH=/C/Apps/local/20-mingw64-32/bin:$PATH
> ./Configure --prefix=$PWD/dist no-idea no-mdc2 no-rc5 no-shared mingw
> make depend && make && make install
```

The result are in the `dist` folder

Configuration
```
$ ./Configure --prefix=$PWD/dist no-idea no-mdc2 no-rc5 no-shared mingw
Configuring for mingwe/openssl/rsa.h
    no-ec_nistp_64_gcc_128 [default]  OPENSSL_NO_EC_NISTP_64_GCC_128 (skip dir)
    no-gmp          [default]  OPENSSL_NO_GMP (skip dir)rojects/github/robovm/te
    no-idea         [option]   OPENSSL_NO_IDEA (skip dir)
    no-jpake        [experimental] OPENSSL_NO_JPAKE (skip dir)
    no-krb5         [krb5-flavor not specified] OPENSSL_NO_KRB5s/github/robovm/t
    no-md2          [default]  OPENSSL_NO_MD2 (skip dir)
    no-mdc2         [option]   OPENSSL_NO_MDC2 (skip dir)
    no-rc5          [option]   OPENSSL_NO_RC5 (skip dir)
    no-rfc3779      [default]  OPENSSL_NO_RFC3779 (skip dir)cts/github/robovm/te
    no-sctp         [default]  OPENSSL_NO_SCTP (skip dir)
    no-shared       [option]  .
    no-store        [experimental] OPENSSL_NO_STORE (skip dir)ts/github/robovm/t
    no-zlib         [default] pto/ecdsa'
    no-zlib-dynamic [default] sl/ecdsa.h
IsMK1MF=0.c => ../../test/ecdsatest.c
CC            =gccirectory `/c/users/cran/Dropbox/docs/projects/github/robovm/te
CFLAG         =-DOPENSSL_THREADS -D_MT -DDSO_WIN32 -DL_ENDIAN -DWIN32_LEAN_AND_MEAN -fomit-
 -DWHIRLPOOL_ASM -DGHASH_ASM
EX_LIBS       =-lws2_32 -lgdi32 -lcrypt32n/Dropbox/docs/projects/github/robovm/t
CPUID_OBJ     =x86cpuid.ol/crypto/dh'
BN_ASM        =bn-586.o co-586.o x86-mont.o x86-gf2m.o
DES_ENC       =des-586.o crypt586.o
AES_ENC       =aes-586.o vpaes-x86.o aesni-x86.ox/docs/projects/github/robovm/te
BF_ENC        =bf-586.osl/crypto/dh'
CAST_ENC      =cast-586.odh...
RC4_ENC       =rc4-586.oory `/c/users/cran/Dropbox/docs/projects/github/robovm/t
RC5_ENC       =rc5-586.osl/crypto/ecdh'
MD5_OBJ_ASM   =md5-586.oopenssl/ecdh.h
SHA1_OBJ_ASM  =sha1-586.o sha256-586.o sha512-586.o
RMD160_OBJ_ASM=rmd-586.ory `/c/users/cran/Dropbox/docs/projects/github/robovm/te
CMLL_ENC      =cmll-x86.o/crypto/ecdh'
MODES_OBJ     =ghash-x86.o...
ENGINES_OBJ   =ng directory `/c/users/cran/Dropbox/docs/projects/github/robovm/t
PROCESSOR     =ows-openssl/crypto/dso'
RANLIB        =/C/Apps/local/20-mingw64-32/bin/ranlib.exe
ARFLAGS       =g directory `/c/users/cran/Dropbox/docs/projects/github/robovm/te
PERL          =/bin/perl.exeypto/dso'
THIRTY_TWO_BIT modepto/engine...
DES_PTR usedering directory `/c/users/cran/Dropbox/docs/projects/github/robovm/t
DES_RISC1 useddows-openssl/crypto/engine'
DES_UNROLL used../include/openssl/engine.h
BN_LLONG mode=> ../../test/enginetest.c
RC4_INDEX modeng directory `/c/users/cran/Dropbox/docs/projects/github/robovm/te
RC4_CHUNK is undefinedssl/crypto/engine'
```
