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

# Local storage used by proxy0.
proxy0_stack_size     = (4+CallInfo_size)
# Offset of CallInfo struct on the stack
CallInfo_offset       = 4

RETURN_TYPE_INT    = 0
RETURN_TYPE_LONG   = 1
RETURN_TYPE_FLOAT  = 2
RETURN_TYPE_DOUBLE = 3


/* c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/proxy0-windows-x86.s: Assembler messages:
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/proxy0-windows-x86.s:39: Warning: .type pseudo-op used
outside of .def/.endef ignored.
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/proxy0-windows-x86.s:39: Error: junk at end of line, fi
rst unrecognized character is `_'
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/proxy0-windows-x86.s:77: Warning: .size pseudo-op used
outside of .def/.endef ignored.
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/proxy0-windows-x86.s:77: Error: junk at end of line, fi
rst unrecognized character is `_'
clang: error: assembler (via gcc) command failed with exit code 1 (use -v to see invocation)
make[2]: *** [core/src/CMakeFiles/robovm-core.dir/proxy0-windows-x86.s.obj] Error 1

*/

    .text

    .globl _proxy0

    .align    16, 0x90
// CARL    .type    _proxy0, @function
proxy0:
.Lproxy0Begin:
    pushl %ebp
    mov   %esp, %ebp

    sub   $proxy0_stack_size, %esp       # Make room for local variables on the stack

    movl  $0, CallInfo_offset+stackArgsIndex_offset(%esp)      # stackArgsIndex = 0

    lea   8(%ebp), %eax                          # $rax = first stack arg
    mov   %eax, CallInfo_offset+stackArgs_offset(%esp)         # stackArgs = first stack arg

    # Call _rvmProxyHandler with the CallInfo as first argument
    lea   CallInfo_offset(%esp), %eax
    movl  %eax, (%esp)
    call  _rvmProxyHandler

    # For simplicity we always copy returnValue to eax and 
    # returnValue>>32 to edx even if float or double is returned.
    mov   CallInfo_offset+returnValue_offset(%esp), %eax
    mov   CallInfo_offset+returnValue_offset+4(%esp), %edx

    # Only touch the x87 fp stack if a float or double is returned
    mov   CallInfo_offset+returnType_offset(%esp), %ecx
    cmp   $RETURN_TYPE_FLOAT, %ecx
    jne   .LreturnTypeNotFloat
    flds  CallInfo_offset+returnValue_offset(%esp)
    jmp   .LreturnTypeNotDouble
.LreturnTypeNotFloat:
    cmp   $RETURN_TYPE_DOUBLE, %ecx
    jne   .LreturnTypeNotDouble
    fldl  CallInfo_offset+returnValue_offset(%esp)
.LreturnTypeNotDouble:

    leave
    ret

// CARL : ASM TODO  .size _proxy0, . - .Lproxy0Begin
.Lproxy0End:

