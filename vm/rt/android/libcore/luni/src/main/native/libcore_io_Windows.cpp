/*
 * Copyright (C) 2014 The Android Open Source Project
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

#if defined(__MINGW32__) || defined(__MINGW64__)
// needs to be defined prior JNIHelp.h include, otherwise LOG_TAG gets redefined leading
// to compiler warning
#define LOG_TAG "Windows"
#endif

#include "JNIHelp.h"

#if defined(__MINGW32__) || defined(__MINGW64__)
#include "JniConstants.h"
#include "JniException.h"

#include "ScopedUtfChars.h"

#include "shlwapi.h"

static jboolean Windows_pathIsRelative(JNIEnv* env, jclass, jstring javaPath) {
    ScopedUtfChars path(env, javaPath);
    if (path.c_str() == NULL) {
        return false;
    }

    if (path.size() > MAX_PATH) {
    	return false;	// TODO: Possible throw an exception in this case...
    }

    return PathIsRelative(path.c_str());
}


static JNINativeMethod gMethods[] = {
    NATIVE_METHOD(Windows, pathIsRelative, "(Ljava/lang/String;)Z"),
};
#endif

void register_libcore_io_Windows(JNIEnv* env) {
#if defined(__MINGW32__) || defined(__MINGW64__)
    jniRegisterNativeMethods(env, "libcore/io/Windows", gMethods, NELEM(gMethods));
#endif
}
