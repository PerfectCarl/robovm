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

prev_offset = 0
sel_offset  = 4
fp_offset   = 8
pc_offset   = 12
esp_offset  = 16
ebx_offset  = 20
esi_offset  = 24
edi_offset  = 28
mxcsr_offset = 32
fpucw_offset = 36

Env_trycatchContext_offset = 28

    .text

    /*  CARL ASM DONE

    c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/trycatch-windows-x86.s: Assembler messages:
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/trycatch-windows-x86.s:38: Warning: .type pseudo-op use
d outside of .def/.endef ignored.
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/trycatch-windows-x86.s:38: Error: junk at end of line,
first unrecognized character is `r'
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/trycatch-windows-x86.s:64: Warning: .size pseudo-op use
d outside of .def/.endef ignored.
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/trycatch-windows-x86.s:64: Error: junk at end of line,
first unrecognized character is `r'
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/trycatch-windows-x86.s:73: Warning: .type pseudo-op use
d outside of .def/.endef ignored.
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/trycatch-windows-x86.s:73: Error: junk at end of line,
first unrecognized character is `r'
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/trycatch-windows-x86.s:93: Warning: .size pseudo-op use
d outside of .def/.endef ignored.
c:/Users/Evasion/Dropbox/docs/projects/robovm/robovm/vm/core/src/trycatch-windows-x86.s:93: Error: junk at end of line,
first unrecognized character is `r'
clang: error: assembler (via gcc) command failed with exit code 1 (use -v to see invocation)
make[2]: *** [core/src/CMakeFiles/robovm-core.dir/trycatch-windows-x86.s.obj] Error 1
make[1]: *** [core/src/CMakeFiles/robovm-core.dir/all] Error 2

*/

/*
 * rvmTrycatchEnter(Env* env, TrycatchContext* tc) 
 */
    .globl _rvmTrycatchEnter
    .globl rvmTrycatchEnter
    
    .align    16, 0x90
// CARL : ASM DONE
        .def    _rvmTrycatchEnter; .scl    2;      .type   32;    
.endef 

rvmTrycatchEnter:
_rvmTrycatchEnter:
.LrvmTrycatchEnterBegin:
    mov   8(%esp), %eax          # %eax = tc
    mov   %ebp, fp_offset(%eax)
    mov   (%esp), %ecx           # %ecx = return address
    mov   %ecx, pc_offset(%eax)
    mov   %esp, esp_offset(%eax)
    mov   %ebx, ebx_offset(%eax)
    mov   %esi, esi_offset(%eax)
    mov   %edi, edi_offset(%eax)
    stmxcsr mxcsr_offset(%eax)
    fnstcw fpucw_offset(%eax)

    # tc->prev = env->trycatchContext;
    # env->trycatchContext = tc;
    mov   4(%esp), %ecx         # %ecx = env
    mov   Env_trycatchContext_offset(%ecx), %edx
    mov   %edx, prev_offset(%eax)
    mov   %eax, Env_trycatchContext_offset(%ecx)

    # Return 0
    mov   $0, %eax

    ret

// CARL  : ASM DONE
//    .size rvmTrycatchEnter, . - .LrvmTrycatchEnterBegin
.LrvmTrycatchEnterEnd:

/*
 * rvmTrycatchJump(TrycatchContext* tc) 
 */
    .globl _rvmTrycatchJump
    
    .align    16, 0x90
// CARL  : ASM DONE
//.type    rvmTrycatchJump, @function
        .def    _rvmTrycatchJump; .scl    2;      .type   32;    
.endef 

_rvmTrycatchJump:
.LrvmTrycatchJumpBegin:
    mov   4(%esp), %ecx        # %ecx = tc
    mov   fp_offset(%ecx), %ebp
    mov   esp_offset(%ecx), %esp
    mov   ebx_offset(%ecx), %ebx
    mov   esi_offset(%ecx), %esi
    mov   edi_offset(%ecx), %edi
    ldmxcsr mxcsr_offset(%ecx)
    fldcw fpucw_offset(%ecx)

    # Remove the return address of the caller of rvmTrycatchJump from the stack
    pop   %eax

    # Set the return value that the call to rvmTrycatchEnter will return
    mov   sel_offset(%ecx), %eax
    # Jump to the return address from the initial call to rvmTrycatchEnter
    jmp   *pc_offset(%ecx)

// CARL  : ASM DONE ? Not ret here ?  .size rvmTrycatchJump, . - .LrvmTrycatchJumpBegin
.LrvmTrycatchJumpEnd:
