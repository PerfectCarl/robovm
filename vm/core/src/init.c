/*
 * Copyright (C) 2012 Trillian AB
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <robovm.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <signal.h>
#if defined(IOS) && (defined(RVM_ARMV7) || defined(RVM_THUMBV7))
#   include <fenv.h>
#endif
#include "private.h"
#include "utlist.h"

#define LOG_TAG "core.init"

#if defined(WINDOWS)
#include <stddef.h>
#include <windows.h>

char* strsep(char** stringp, const char* delim)
{
  char* start = *stringp;
  char* p;

  p = (start != NULL) ? strpbrk(start, delim) : NULL;

  if (p == NULL)
  {
    *stringp = NULL;
  }
  else
  {
    *p = '\0';
    *stringp = p + 1;
  }

  return start;
}

char *c_realpath(const char *path, char *resolved_path)
{
    return GetFullPathName(path, MAX_PATH, resolved_path, NULL) ? resolved_path : NULL;
}
#endif

ClassLoader* systemClassLoader = NULL;
static Class* java_lang_Daemons = NULL;
static Method* java_lang_Daemons_start = NULL;

// CARL Hack : not defined in 4.4r07
// extern int registerJniHelp(JNIEnv* env);
// extern int registerCoreLibrariesJni(JNIEnv* env);

static inline jint startsWith(char* s, char* prefix) {
    return s && strncmp(s, prefix, strlen(prefix)) == 0;
}

static char* absolutize(char* basePath, char* rel, char* dest) {
    if (rel[0] == '/') {
        strcpy(dest, rel);
    } else {
        strcpy(dest, basePath);
        strcat(dest, "/");
        strcat(dest, rel);
    }
    return dest;
}

//CARL debug 

void CARL_start( char* string)
{	
	printf( "%s started\n", string ) ; 
}
void CARL_stop( char* string)
{	
	printf( "%s stopped\n", string ) ; 
}
void CARL_log( char* string)
{	
	printf( "** CARL %s\n", string ) ; 
}

static jboolean ignoreSignal(int signo) {
#if !defined(WINDOWS)
    if (signal(signo, SIG_IGN) == SIG_ERR) {
        return FALSE;
    }
#endif
	CARL_log( "Ignored signal") ;
	return TRUE;
}


static jboolean initClasspathEntries(Env* env, char* basePath, char** raw, ClasspathEntry** first) {
    jint i = 0;
    while (raw[i]) {
        ClasspathEntry* entry = rvmAllocateMemoryAtomicUncollectable(env, sizeof(ClasspathEntry));
        if (!entry) return FALSE;
        absolutize(basePath, raw[i], entry->jarPath);
        LL_APPEND(*first, entry);
        i++;
    }

    return TRUE;
}

jboolean rvmInitOptions(int argc, char* argv[], Options* options, jboolean ignoreRvmArgs) {
    CARL_start( "rvmInitOptions");
	SystemProperty** nextProperty = &options->properties; //Keep a pointer to where the next SystemProperty* will go.
    char path[PATH_MAX];
#ifdef WINDOWS
	if (!c_realpath(argv[0], path)) {
        CARL_log("Bye") ;
		return FALSE;
    }

#else
	if (!realpath(argv[0], path)) {
        return FALSE;
    }
#endif
    strcpy(options->executablePath, path);

    jint i = strlen(path);
    while (i >= 0 && path[i] != '/') {
        path[i--] = '\0';
    }
    if (i >= 0 && path[i] == '/') {
        path[i] = '\0';
    }

    strcpy(options->basePath, path);
	CARL_log("A1");
    jint firstJavaArg = 1;
    for (i = 1; i < argc; i++) {
        if (startsWith(argv[i], "-rvm:")) {
            if (!ignoreRvmArgs) {
                char* arg = &argv[i][5];
                if (startsWith(arg, "log=trace")) {
                    if (options->logLevel == 0) options->logLevel = LOG_LEVEL_TRACE;
                } else if (startsWith(arg, "log=debug")) {
                    if (options->logLevel == 0) options->logLevel = LOG_LEVEL_DEBUG;
                } else if (startsWith(arg, "log=info")) {
                    if (options->logLevel == 0) options->logLevel = LOG_LEVEL_INFO;
                } else if (startsWith(arg, "log=warn")) {
                    if (options->logLevel == 0) options->logLevel = LOG_LEVEL_WARN;
                } else if (startsWith(arg, "log=error")) {
                    if (options->logLevel == 0) options->logLevel = LOG_LEVEL_ERROR;
                } else if (startsWith(arg, "log=fatal")) {
                    if (options->logLevel == 0) options->logLevel = LOG_LEVEL_FATAL;
                } else if (startsWith(arg, "log=silent")) {
                    if (options->logLevel == 0) options->logLevel = LOG_LEVEL_SILENT;
                } else if (startsWith(arg, "mx") || startsWith(arg, "ms")) {
                    char* unit;
                    jlong n = strtol(&arg[2], &unit, 10);
                    if (n > 0) {
                        if (unit[0] != '\0') {
                            switch (unit[0]) {
                            case 'g':
                            case 'G':
                                n *= 1024 * 1024 * 1024;
                                break;
                            case 'm':
                            case 'M':
                                n *= 1024 * 1024;
                                break;
                            case 'k':
                            case 'K':
                                n *= 1024;
                                break;
                            }
                        }
                    }
                    if (startsWith(arg, "mx")) {
                        options->maxHeapSize = n;
                    } else {
                        options->initialHeapSize = n;
                    }
                } else if (startsWith(arg, "MainClass=")) {
                    if (!options->mainClass) {
                        char* s = strdup(&arg[10]);
                        jint j;
                        for (j = 0; s[j] != 0; j++) {
                            if (s[j] == '.') s[j] = '/';
                        }
                        options->mainClass = s;
                    }
                } else if (startsWith(arg, "D")) {
                    char* s = strdup(&arg[1]);
                    // Split the arg string on the '='. 'key' will have the
                    // part on the left and 's' will have the value on the right
                    char* key = strsep(&s, "=");

                    *nextProperty = malloc(sizeof(SystemProperty));

                    (*nextProperty)->key = key;
                    (*nextProperty)->value = s;
                    (*nextProperty)->next = NULL;

                    //Set the nextProperty variable to the 'next' field on the
                    //property we just created.
                    nextProperty = &((*nextProperty)->next);
                }
            }
            firstJavaArg++;
        } else {
            break;
        }
    }
	CARL_log("A2");
    options->commandLineArgs = NULL;
    options->commandLineArgsCount = argc - firstJavaArg;
    CARL_log("A3");
	if (options->commandLineArgsCount > 0) {
        options->commandLineArgs = &argv[firstJavaArg];
    }
    CARL_stop( "rvmInitOptions");

    return options->mainClass != NULL;
}

VM* rvmCreateVM(Options* options) {
    CARL_start( "rvmCreateVM");

	VM* vm = gcAllocate(sizeof(VM));
    if (!vm) return NULL;
    vm->options = options;
    rvmInitJavaVM(vm);
	CARL_stop( "rvmCreateVM");

    return vm;
}

Env* rvmCreateEnv(VM* vm) {
    Env* env = gcAllocate(sizeof(Env));
    if (!env) return NULL;
    env->vm = vm;
    rvmInitJNIEnv(env);
    return env;
}

Env* rvmStartup(Options* options) {
    // TODO: Error handling
	CARL_start( "rvmStartup");

#if defined(IOS) && (defined(RVM_ARMV7) || defined(RVM_THUMBV7))
    // Enable IEEE-754 denormal support.
    // Without this the VFP treats numbers that are close to zero as zero itself.
    // See http://developer.apple.com/library/ios/#technotes/tn2293/_index.html.
    fenv_t fenv;
    fegetenv(&fenv);
    fenv.__fpscr &= ~__fpscr_flush_to_zero;
    fesetenv(&fenv);
#endif

    TRACE("Initializing GC");
    if (!initGC(options)) return NULL;

#ifdef SIGPIPE
    // Ignore SIGPIPE signals. SIGPIPE interrupts write() calls which we don't
    // want. Dalvik does this too in dalvikvm/Main.cpp.
    if (!ignoreSignal(SIGPIPE)) return NULL;
#endif

#ifdef SIGXFSZ
    // Ignore SIGXFSZ signals. SIGXFSZ is raised when writing beyond the RLIMIT_FSIZE
    // of the current process (at least on Darwin) using pwrite().
    if (!ignoreSignal(SIGXFSZ)) return NULL;
#endif

    VM* vm = rvmCreateVM(options);
    if (!vm) return NULL;

    Env* env = rvmCreateEnv(vm);
    if (!env) return NULL;
    // TODO: What if we can't allocate Env?

    if (!initClasspathEntries(env, options->basePath, options->rawBootclasspath, &options->bootclasspath)) return NULL;
    if (!initClasspathEntries(env, options->basePath, options->rawClasspath, &options->classpath)) return NULL;

    // Call init on modules
    TRACE("Initializing logging");
    if (!rvmInitLog(env)) return NULL;
    TRACE("Initializing classes");
    if (!rvmInitClasses(env)) return NULL;
    TRACE("Initializing memory");
    if (!rvmInitMemory(env)) return NULL;
    TRACE("Initializing methods");
    if (!rvmInitMethods(env)) return NULL;
    TRACE("Initializing strings");
    if (!rvmInitStrings(env)) return NULL;
    TRACE("Initializing monitors");
    if (!rvmInitMonitors(env)) return NULL;
    TRACE("Initializing proxy");
    if (!rvmInitProxy(env)) return NULL;
    TRACE("Initializing threads");
    if (!rvmInitThreads(env)) return NULL;
    TRACE("Initializing attributes");
    if (!rvmInitAttributes(env)) return NULL;
    TRACE("Initializing primitive wrapper classes");
    if (!rvmInitPrimitiveWrapperClasses(env)) return NULL;
    TRACE("Initializing exceptions");
    if (!rvmInitExceptions(env)) return NULL;
    TRACE("Initializing signals");
    if (!rvmInitSignals(env)) return NULL;

    // Initialize the RoboVM rt JNI code
//    RT_JNI_OnLoad(&vm->javaVM, NULL);
    // Initialize dalvik's JNIHelp code in libnativehelper
    TRACE("Initializing dalvik's libnativehelper");
    // CARL Hack : not defined in 4.4r07
	// registerJniHelp((JNIEnv*) env);
    // Initialize the dalvik rt JNI code
    TRACE("Initializing dalvik's runtime JNI code");
    // CARL HACK
	//registerCoreLibrariesJni((JNIEnv*) env);

    TRACE("Creating system ClassLoader");
    systemClassLoader = rvmGetSystemClassLoader(env);
    if (rvmExceptionOccurred(env)) goto error_system_ClassLoader;
    env->currentThread->threadObj->contextClassLoader = systemClassLoader;

    TRACE("Initialization done");
    env->vm->initialized = TRUE;
    
    // Start Daemons
    TRACE("Starting Daemons");
    java_lang_Daemons = rvmFindClassUsingLoader(env, "java/lang/Daemons", NULL);
    if (!java_lang_Daemons) goto error_daemons;
    java_lang_Daemons_start = rvmGetClassMethod(env, java_lang_Daemons, "start", "()V");
    if (!java_lang_Daemons_start) goto error_daemons;
    rvmCallVoidClassMethod(env, java_lang_Daemons, java_lang_Daemons_start);
    if (rvmExceptionCheck(env)) goto error_daemons;
    TRACE("Daemons started");
	CARL_stop( "rvmStartup");
    return env;

error_daemons:
error_system_ClassLoader:
    rvmDetachCurrentThread(env->vm, TRUE, FALSE);
	CARL_stop( "rvmStartup");

    return NULL;
}

jboolean rvmRun(Env* env) {
	CARL_start( "rvmRun");
    Options* options = env->vm->options;
    Class* clazz = NULL;

    jboolean errorDuringSetup = FALSE;

    //If our options has any properties, let's set them before we call our main.
    if (options->properties) {
        //First, find java.lang.System, which has the setProperty method.
        clazz = rvmFindClassUsingLoader(env, "java/lang/System", NULL);
        if (clazz) {
            //Get the setProperty method.
            Method* method = rvmGetClassMethod(env, clazz, "setProperty", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
            if (method) {
                SystemProperty* property = options->properties;

                //Go through all of our properties and add each one in turn by calling setProperty.
                while (property != NULL) {
                    Object* key = NULL;
                    Object* value = NULL;
                    //The key is not allowed to be an empty string, so don't set it if we don't get a key.
                    if(property->key && strlen(property->key) > 0) {
                        key = rvmNewStringUTF(env, property->key, -1);
                    } else {
                        FATAL("Cannot have empty key in system property.");
                        errorDuringSetup = TRUE;
                        break;
                    }
                    if (property->value) {
                        value = rvmNewStringUTF(env, property->value, -1);
                    } else {
                        value = rvmNewStringUTF(env, "", -1);
                    }

                    if (key && value) {
                        rvmCallObjectClassMethod(env, clazz, method, key, value);
                    } else {
                        if (!key) {
                            FATALF("Error creating string from system property key: %s", property->key);
                        }
                        if (!value) {
                            FATALF("Error creating string from system property value: %s", property->value);
                        }
                        errorDuringSetup = TRUE;
                        break;
                    }
                    property = property->next; //Advance to the next property.
                }
            }
        }
    }

    if (!errorDuringSetup) {
        clazz = rvmFindClassUsingLoader(env, options->mainClass, systemClassLoader);
        if (clazz) {
            Method* method = rvmGetClassMethod(env, clazz, "main", "([Ljava/lang/String;)V");
            if (method) {
                ObjectArray* args = rvmNewObjectArray(env, options->commandLineArgsCount, java_lang_String, NULL, NULL);
                if (args) {
                    jint i = 0;
                    for (i = 0; i < args->length; i++) {
                        // TODO: Don't assume modified UTF-8
                        args->values[i] = rvmNewStringUTF(env, options->commandLineArgs[i], -1);
                        if (!args->values[i]) {
                            args = NULL;
                            break;
                        }
                    }
                    if (args) rvmCallVoidClassMethod(env, clazz, method, args);
                }
            }
        }
    }

    Object* throwable = rvmExceptionOccurred(env);
    rvmDetachCurrentThread(env->vm, TRUE, FALSE);

    rvmJoinNonDaemonThreads(env);
	CARL_stop( "rvmRun");
    return throwable == NULL ? TRUE : FALSE;
}

void rvmShutdown(Env* env, jint code) {
    // TODO: Cleanup, stop threads.
    exit(code);
}

void rvmAbort(char* format, ...) {
    va_list args;
    if (format) {
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
        fprintf(stderr, "\n");
    }
    abort();
}

DynamicLib* rvmOpenDynamicLib(Env* env, const char* file, char** errorMsg) {
    *errorMsg = NULL;
    DynamicLib* dlib = NULL;

    void* handle = dlopen(file, RTLD_LOCAL | RTLD_LAZY);
    if (!handle) {
        *errorMsg = dlerror();
        TRACEF("Failed to load dynamic library '%s': %s", file, *errorMsg);
        return NULL;
    }

    TRACEF("Opening dynamic library '%s'", file);

    dlib = rvmAllocateMemoryAtomicUncollectable(env, sizeof(DynamicLib));
    if (!dlib) {
        dlclose(handle);
        return NULL;
    }

    dlib->handle = handle;

    return dlib;
}

void rvmCloseDynamicLib(Env* env, DynamicLib* lib) {
    dlclose(lib->handle);
    rvmFreeMemoryUncollectable(env, lib);
}

jboolean rvmHasDynamicLib(Env* env, DynamicLib* lib, DynamicLib* libs) {
    DynamicLib* dlib = NULL;
    LL_FOREACH(libs, dlib) {
        if (dlib->handle == lib->handle) {
            return TRUE;
        }
    }
    return FALSE;
}

void rvmAddDynamicLib(Env* env, DynamicLib* lib, DynamicLib** libs) {
    LL_APPEND(*libs, lib);
}

void* rvmFindDynamicLibSymbol(Env* env, DynamicLib* libs, const char* symbol, jboolean searchAll) {
    TRACEF("Searching for symbol '%s'", symbol);

    DynamicLib* dlib = NULL;
    LL_FOREACH(libs, dlib) {
        void* v = dlsym(dlib->handle, symbol);
        if (v) return v;
        if (!searchAll) return NULL;
    }
    return NULL;
}

