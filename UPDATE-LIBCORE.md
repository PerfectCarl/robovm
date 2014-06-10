# Prerequesites 

 - Maven 3.1
 - cmake 

# Download the sources
### Download robovm 
```
git clone https://github.com/PerfectCarl/robovm.git -b link_windows_libcore64 --single-branch
```

### Download libcore64
```
git clone https://github.com/PerfectCarl/avian-pack.android.libcore.git
```
### Download libnativehelper 
```
git clone https://android.googlesource.com/platform/libnativehelper
cd libnativehelper
git checkout tags/android-4.4_r0.7
```
```
git clone https://android.googlesource.com/platform/external/openssl
cd openssl
git checkout tags/android-4.4_r0.7
```

```
git clone https://android.googlesource.com/platform/external/sqlite/
cd sqlite
git checkout tags/android-4.4_r0.7
```

```
git clone https://android.googlesource.com/platform/external/zlib/
cd zlib
git checkout tags/android-4.4_r0.7
```

```
git clone https://android.googlesource.com/platform/external/fdlibm/
cd fdlibm
git checkout tags/android-4.4_r0.7
```

```
git clone https://android.googlesource.com/platform/external/icu4c/
cd icu4c
git checkout tags/android-4.4_r0.7
```

```
git clone https://android.googlesource.com/platform/system/core
cd core
git checkout tags/android-4.4_r0.7
```

The two folders must be in the same parent folder 
```
 ;) > dir

29/05/2014  15:15    <REP>          .
29/05/2014  15:15    <REP>          ..
29/05/2014  18:26    <REP>          avian-pack.android.libcore
08/03/2014  23:53    <REP>          robovm
````

# Build robovm-rt.jar

````
cd avian-pack.android.libcore/robovm 
maven package
````
The jar file is located in `robovm/target`

**Note** 
bouncycastle: OpenSSLDigest.java NativeCrypto has move from `org.apache.harmony.xnet.provider.jsse.NativeCrypto` to `import com.android.org.conscrypt.NativeCrypto` 

http://platform--external--bouncycastle.android-source-browsing.googlecode.com/git/bcprov/src/main/java/org/bouncycastle/crypto/digests/OpenSSLDigest.java

# Build llvm 

# Build rt


