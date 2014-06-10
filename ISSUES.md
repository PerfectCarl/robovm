## robovm-rt.jar
concrypt package is not where it should be

## New Android 4.4 API
- Use `Register.cpp` instead of `registerCoreLibrariesJni` and `registerJniHelp`

## Dependencies 
- Missing dependency to patched imvai libgc (using hp's instead). See [this exchange](https://groups.google.com/forum/#!topic/robovm/LiDa3z5bAcE)
- Compiling openssl with `OPENSSL_SMALL_FOOTPRINT` to . See [this exchange](https://groups.google.com/d/msg/robovm/GGTubkAT2vg/CgVHrVPQ1AsJ)
- Review Openssl compilation flags

## Luni
- Porting luni/posix code to windows

## Misc 
### Converting pthread_t to int in windows

This code doesn't compile on windows because `pthread_t` is a struct:

```java
static unsigned long id_function(void) {
    // cannot convert 'pthread_t' (aka 'ptw32_handle_t') to 'unsigned long' without a conversion operator
    return ((unsigned long)THREAD_ID);
}
```

See [this post](http://stackoverflow.com/questions/1759794/how-to-print-pthread-t)

## libnativehelper and jni

This code looks odd on Windows

```java
bool JniInvocation::Init(const char* library) {
#ifdef HAVE_ANDROID_OS
  char default_library[PROPERTY_VALUE_MAX];
  property_get("persist.sys.dalvik.vm.lib", default_library, "libdvm.so");
#else
	// CARL HACK : what is this ??
	const char* default_library = "libdvm.so";
#endif
  if (library == NULL) {
    library = default_library;
  }

  handle_ = dlopen(library, RTLD_NOW);
  if (handle_ == NULL) {
    ALOGE("Failed to dlopen %s: %s", library, dlerror());
    return false;
  }
  if (!FindSymbol(reinterpret_cast<void**>(&JNI_GetDefaultJavaVMInitArgs_),
                  "JNI_GetDefaultJavaVMInitArgs")) {
    return false;
  }
  if (!FindSymbol(reinterpret_cast<void**>(&JNI_CreateJavaVM_),
                  "JNI_CreateJavaVM")) {
    return false;
  }
  if (!FindSymbol(reinterpret_cast<void**>(&JNI_GetCreatedJavaVMs_),
                  "JNI_GetCreatedJavaVMs")) {
    return false;
  }
  return true;
}
```

How do `libdvm.so` applies on Windows? Is the whole feature? 
Will it break JNI on Windows?

## Check the exception handling system
[DWARF or SLJL?](https://groups.google.com/forum/#!topic/robovm/cE-Bj6cygkk)

## Intercept the windows system errors
In `vm\core\src\signal.c`
See [this post](http://www.codeproject.com/Articles/207464/Exception-Handling-in-Visual-Cplusplus)

## Not compiling with clang 3.3
See [this](https://github.com/dicej/android-libcore64/issues/8)
