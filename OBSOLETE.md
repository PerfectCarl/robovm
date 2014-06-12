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

