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
 // CARL dll
#ifdef WINDOWS
//#include "dlfcn.h"
#else
#include <dlfcn.h>
#endif
#include <robovm.h>

jlong Java_org_robovm_rt_bro_Dl_open(Env* env, Class* c, Object* name) {
    char* cName = NULL;
    if (name) {
        cName = rvmGetStringUTFChars(env, name);
        if (!cName) return 0;
    }
 // CARL dll
#ifdef WINDOWS
    void* handle = NULL ;
	printf("WINDOWS doesn't support dll loading. Function: Java_org_robovm_rt_bro_Dl_open. File: %s", cName ) ;
#else
	void* handle = dlopen(cName, RTLD_LOCAL | RTLD_LAZY);
#endif

if (!handle) {
        return 0;
    }
    return PTR_TO_LONG(handle);
}

jlong Java_org_robovm_rt_bro_Dl_resolve(Env* env, Class* c, jlong handle, Object* name) {
    char* cName = rvmGetStringUTFChars(env, name);
    if (!cName) return 0;
    return PTR_TO_LONG(dlsym(LONG_TO_PTR(handle), cName));
}

void Java_org_robovm_rt_bro_Dl_close(Env* env, Class* c, jlong handle) {
    dlclose((void*) LONG_TO_PTR(handle));
}

Object* Java_org_robovm_rt_bro_Dl_lastError(Env* env, Class* c) {
    char* error = dlerror();
    if (!error) return NULL;
    return rvmNewStringUTF(env, error, -1);
}

