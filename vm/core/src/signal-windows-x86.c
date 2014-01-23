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

#define _GNU_SOURCE
#include <robovm.h>
#include <signal.h>
#include <errno.h>
#include "private.h"

// TODO Carl posix 
#define LOG_TAG "core.signal"

#define DUMP_THREAD_STACK_TRACE_SIGNAL SIGUSR2

/*
 * The common way to implement stack overflow detection is to catch SIGSEGV and see if the
 * address that generated the fault is in the current thread's stack guard page. Since the stack
 * has been consumed at this point one usually uses an alternate signal stack for the signal
 * handler to run on using sigaltstack(). Unfortunately sigaltstack() seems to be broken on
 * iOS. Even if it completes without errors the alternate stack won't be used by the signal
 * handler. In RoboVM we work around this bug by inserting code in the prologue of
 * compiled methods which tries to read from the stack area at sp-64k. If this read hits the 
 * guard page a fault will occur but we'll still have about 64k left of stack space to run the signal 
 * handler on.
 */

static InstanceField* stackStateField = NULL;
static CallStack* dumpThreadStackTraceCallStack = NULL;

jboolean rvmInitSignals(Env* env) {
	printf("WINDOWS: rvmInitSignals") ;
    stackStateField = rvmGetInstanceField(env, java_lang_Throwable, "stackState", "J");
    if (!stackStateField) return FALSE;
	return TRUE;
}

static jboolean installSignalHandlers(Env* env) {
	printf("WINDOWS: installSignalHandlers") ;

    return TRUE;
}

void dumpThreadStackTrace(Env* env, Thread* thread, CallStack* callStack) {
	printf("WINDOWS: dumpThreadStackTrace") ;

}

jboolean rvmSetupSignals(Env* env) {
    if (!installSignalHandlers(env)) {
        return FALSE;
    }
    return TRUE;
}

void rvmRestoreSignalMask(Env* env) {
	printf("WINDOWS: rvmRestoreSignalMask") ;
}

void rvmTearDownSignals(Env* env) {
}
