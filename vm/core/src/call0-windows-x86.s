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
function_offset       = 0  # void*
stackArgsSize_offset  = 4  # jint
stackArgsIndex_offset = 8  # jint
stackArgs_offset      = 12 # void**
returnValue_offset    = 16 # FpIntValue
returnType_offset     = 24 # jint
CallInfo_size         = 28

    .text

    .globl _call0
    
    .align    16, 0x90

// CARL asm DONE

/* 
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm-xxx/vm/core/src/call0-windows-x86.s: Assembler messages:
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm-xxx/vm/core/src/call0-windows-x86.s:42: Warning: .type pseudo-op used outside of .def/.endef ignored.
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm-xxx/vm/core/src/call0-windows-x86.s:42: Error: junk at end of line, first unrecognized character is `_'
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm-xxx/vm/core/src/call0-windows-x86.s:65: Warning: .size pseudo-op used outside of .def/.endef ignored.
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm-xxx/vm/core/src/call0-windows-x86.s:65: Error: junk at end of line, first unrecognized character is `_'
make[2]: *** [core/src/CMakeFiles/robovm-core.dir/call0-windows-x86.s.obj] Error 1
make[1]: *** [core/src/CMakeFiles/robovm-core.dir/all] Error 2
make: *** [all] Error 2
*/
//.globl _call0
        .def    _call0; .scl    2;      .type   32;    
.endef 

_call0:
.Lcall0Begin:
    push  %ebp
    mov   %esp, %ebp
    mov   8(%ebp), %eax         # %eax = First arg (CallInfo*)

    mov   stackArgsSize_offset(%eax), %ecx # %ecx = stackArgsSize
.LsetStackArgsNext:
    test  %ecx, %ecx
    je    .LsetStackArgsDone
    dec   %ecx
    mov   stackArgs_offset(%eax), %edx     # %edx = stackArgs
    lea   (%edx, %ecx, 4), %edx  # %edx = stackArgs + %ecx * 4
    push  (%edx)
    jmp   .LsetStackArgsNext
.LsetStackArgsDone:

    call  *function_offset(%eax)

    leave
    ret

.Lcall0End:
