bdwgc 

```
git clone git://github.com/robovm/bdwgc.git
git checkout 40ed2d5272191a169598e60697221c88de71027b .
```

libatomic 
```
git clone git://github.com/ivmai/libatomic_ops.git
git checkout f5f47f7b9c70df2e0d371dd2f303a0dec1a37223 .
```

NOTE: libatomic ships with mingw-w64

Command line from cmake 
```
CC=/usr/bin/gcc CFLAGS=' -DGC_DISABLE_INCREMENTAL -DGC_FORCE_UNMAP_ON_GCOLLECT' LDFLAGS=' ' 
./configure  --enable-shared=no --enable-munmap=1 --prefix=/home/cran/robovm/gc

```

Compilation
```
> [your.msys.path]\msys.bat
Example: C:\Apps\Mingw\msys\1.0\msys.bat
> cd robovm-windows-openssl
cd /C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src
> export PATH=/[your.mingw.path]/bin:$PATH
Example: export PATH=/C/Apps/local/20-mingw64-32/bin:$PATH
> export CFLAGS=" -DGC_DISABLE_INCREMENTAL -DGC_FORCE_UNMAP_ON_GCOLLECT -DGC_PTHREADS"
> ./configure  --enable-shared=no --enable-munmap=1 --prefix=$PWD/dist 

> make depend && make && make install
```

Output
```
checking build system type... i686-pc-mingw32
checking host system type... i686-pc-mingw32
checking target system type... i686-pc-mingw32
checking GC version numbers... major=7 minor=3 alpha=3
checking for a BSD-compatible install... /bin/install -c
checking whether build environment is sane... yes
checking for a thread-safe mkdir -p... /bin/mkdir -p
checking for gawk... gawk
checking whether make sets $(MAKE)... yes
checking whether to enable maintainer-specific portions of Makefiles... no
checking for style of include used by make... GNU
checking for gcc... gcc
checking whether the C compiler works... yes
checking for C compiler default output file name... a.exe
checking for suffix of executables... .exe
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether we are using the GNU C compiler... yes
checking whether gcc accepts -g... yes
checking for gcc option to accept ISO C89... none needed
checking dependency style of gcc... gcc3
checking whether gcc and cc understand -c and -o together... yes
checking for g++... g++
checking whether we are using the GNU C++ compiler... yes
checking whether g++ accepts -g... yes
checking dependency style of g++... gcc3
checking dependency style of gcc... gcc3
checking for thread model used by GCC... win32
checking for inline... inline
checking for gcc -Wextra... yes
checking for xlc... no
checking whether gcc supports -fno-strict-aliasing... yes
checking for dlopen in -ldl... no
checking whether to build shared libraries... no
checking which machine-dependent code should be used...
checking how to print strings... printf
checking for a sed that does not truncate output... /bin/sed
checking for grep that handles long lines and -e... /bin/grep
checking for egrep... /bin/grep -E
checking for fgrep... /bin/grep -F
checking for ld used by gcc... c:/Apps/local/20-mingw64-32/i686-w64-mingw32/bin/ld.exe
checking if the linker (c:/Apps/local/20-mingw64-32/i686-w64-mingw32/bin/ld.exe) is GNU ld... yes
checking for BSD- or MS-compatible name lister (nm)... /C/Apps/local/20-mingw64-32/bin/nm
checking the name lister (/C/Apps/local/20-mingw64-32/bin/nm) interface... BSD nm
checking whether ln -s works... no, using cp -p
checking the maximum length of command line arguments... 8192
checking whether the shell understands some XSI constructs... yes
checking whether the shell understands "+="... yes
checking how to convert i686-pc-mingw32 file names to i686-pc-mingw32 format... func_convert_file_msys_to_w32
checking how to convert i686-pc-mingw32 file names to toolchain format... func_convert_file_msys_to_w32
checking for c:/Apps/local/20-mingw64-32/i686-w64-mingw32/bin/ld.exe option to reload object files... -r
checking for objdump... objdump
checking how to recognize dependent libraries... file_magic ^x86 archive import|^x86 DLL
checking for dlltool... dlltool
checking how to associate runtime and link libraries... func_cygming_dll_for_implib
checking for ar... ar
checking for archiver @FILE support... @
checking for strip... strip
checking for ranlib... ranlib
checking command to parse /C/Apps/local/20-mingw64-32/bin/nm output from gcc object... ok
checking for sysroot... no
checking for mt... no
checking if : is a manifest tool... no
checking how to run the C preprocessor... gcc -E
checking for ANSI C header files... yes
checking for sys/types.h... yes
checking for sys/stat.h... yes
checking for stdlib.h... yes
checking for string.h... yes
checking for memory.h... yes
checking for strings.h... yes
checking for inttypes.h... yes
checking for stdint.h... yes
checking for unistd.h... yes
checking for dlfcn.h... no
checking for objdir... .libs
checking if gcc supports -fno-rtti -fno-exceptions... no
checking for gcc option to produce PIC... -DDLL_EXPORT -DPIC
checking if gcc PIC flag -DDLL_EXPORT -DPIC works... yes
checking if gcc static flag -static works... yes
checking if gcc supports -c -o file.o... yes
checking if gcc supports -c -o file.o... (cached) yes
checking whether the gcc linker (c:/Apps/local/20-mingw64-32/i686-w64-mingw32/bin/ld.exe) supports shared libra
checking dynamic linker characteristics... Win32 ld.exe
checking how to hardcode library paths into programs... immediate
checking whether stripping libraries is possible... yes
checking if libtool supports shared libraries... yes
checking whether to build shared libraries... no
checking whether to build static libraries... yes
checking how to run the C++ preprocessor... g++ -E
checking for ld used by g++... c:/Apps/local/20-mingw64-32/i686-w64-mingw32/bin/ld.exe
checking if the linker (c:/Apps/local/20-mingw64-32/i686-w64-mingw32/bin/ld.exe) is GNU ld... yes
checking whether the g++ linker (c:/Apps/local/20-mingw64-32/i686-w64-mingw32/bin/ld.exe) supports shared libra
checking for g++ option to produce PIC... -DDLL_EXPORT -DPIC
checking if g++ PIC flag -DDLL_EXPORT -DPIC works... yes
checking if g++ static flag -static works... yes
checking if g++ supports -c -o file.o... yes
checking if g++ supports -c -o file.o... (cached) yes
checking whether the g++ linker (c:/Apps/local/20-mingw64-32/i686-w64-mingw32/bin/ld.exe) supports shared libra
checking dynamic linker characteristics... Win32 ld.exe
checking how to hardcode library paths into programs... immediate
checking whether Solaris gcc optimization fix is necessary... no
checking sys/dg_sys_info.h usability... no
checking sys/dg_sys_info.h presence... no
checking for sys/dg_sys_info.h... no
checking for pkg-config... no
checking for ATOMIC_OPS... no
checking which libatomic_ops to use... internal
configure: creating ./config.status
config.status: creating Makefile
config.status: creating bdw-gc.pc
config.status: creating include/config.h
config.status: executing depfiles commands
config.status: executing libtool commands
config.status: executing default commands
=== configuring in libatomic_ops (/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/libatomi
configure: WARNING: no configuration information is in libatomic_ops

```
Compilation 
```
$ make && make install
make[1]: Entering directory `/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src'
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo allchblk.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/allchblk.Tpo .deps/allchblk.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/alloc.Tpo .deps/alloc.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo blacklst.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/blacklst.Tpo .deps/blacklst.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
ms.lo checksums.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/checksums.Tpo .deps/checksums.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
dbg_mlc.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/dbg_mlc.Tpo .deps/dbg_mlc.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo dyn_load.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/dyn_load.Tpo .deps/dyn_load.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo finalize.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/finalize.Tpo .deps/finalize.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
en.lo gc_dlopen.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/gc_dlopen.Tpo .deps/gc_dlopen.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
gcj_mlc.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/gcj_mlc.Tpo .deps/gcj_mlc.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
headers.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/headers.Tpo .deps/headers.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo mach_dep.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/mach_dep.Tpo .deps/mach_dep.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
loc.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/malloc.Tpo .deps/malloc.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
mallocx.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/mallocx.Tpo .deps/mallocx.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mark.c: In function 'GC_mark_some':
mark.c:533:25: warning: assignment from incompatible pointer type
       er.ex_reg.handler = mark_ex_handler;
                         ^
mv -f .deps/mark.Tpo .deps/mark.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo mark_rts.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/mark_rts.Tpo .deps/mark_rts.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/misc.Tpo .deps/misc.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo new_hblk.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/new_hblk.Tpo .deps/new_hblk.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
obj_map.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/obj_map.Tpo .deps/obj_map.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
dep.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/os_dep.Tpo .deps/os_dep.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
 pcr_interface.lo pcr_interface.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
e.o
mv -f .deps/pcr_interface.Tpo .deps/pcr_interface.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo ptr_chck.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/ptr_chck.Tpo .deps/ptr_chck.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
l_malloc.lo real_malloc.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/real_malloc.Tpo .deps/real_malloc.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
reclaim.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/reclaim.Tpo .deps/reclaim.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo specific.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/specific.Tpo .deps/specific.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo stubborn.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/stubborn.Tpo .deps/stubborn.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
.Tpo -c -o thread_local_alloc.lo thread_local_alloc.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
-o thread_local_alloc.o
mv -f .deps/thread_local_alloc.Tpo .deps/thread_local_alloc.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo typd_mlc.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/typd_mlc.Tpo .deps/typd_mlc.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
 win32_threads.lo win32_threads.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
s.o
mv -f .deps/win32_threads.Tpo .deps/win32_threads.Plo
/bin/sh ./libtool --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
lo fnlz_mlc.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mv -f .deps/fnlz_mlc.Tpo .deps/fnlz_mlc.Plo
/bin/sh ./libtool  --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
ic_ops.lo `test -f 'libatomic_ops/src/atomic_ops.c' || echo './'`libatomic_ops/src/atomic_ops.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
mic_ops.o
mv -f .deps/atomic_ops.Tpo .deps/atomic_ops.Plo
/bin/sh ./libtool --tag=CC   --mode=link gcc -fexceptions -Wall -Wextra  -DGC_DISABLE_INCREMENTAL -DGC_FORCE_UNM
o blacklst.lo checksums.lo dbg_mlc.lo dyn_load.lo finalize.lo gc_dlopen.lo gcj_mlc.lo headers.lo mach_dep.lo mal
.lo win32_threads.lo     fnlz_mlc.lo atomic_ops.lo
libtool: link: ar cru .libs/libgc.a  allchblk.o alloc.o blacklst.o checksums.o dbg_mlc.o dyn_load.o finalize.o g
 thread_local_alloc.o typd_mlc.o win32_threads.o fnlz_mlc.o atomic_ops.o
libtool: link: ranlib .libs/libgc.a
libtool: link: ( cd ".libs" && rm -f "libgc.la" && cp -p "../libgc.la" "libgc.la" )
/bin/sh ./libtool  --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
scs.Tpo -c -o libcord_la-cordbscs.lo `test -f 'cord/cordbscs.c' || echo './'`cord/cordbscs.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
libcord_la-cordbscs.o
mv -f .deps/libcord_la-cordbscs.Tpo .deps/libcord_la-cordbscs.Plo
/bin/sh ./libtool  --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
rnt.Tpo -c -o libcord_la-cordprnt.lo `test -f 'cord/cordprnt.c' || echo './'`cord/cordprnt.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
libcord_la-cordprnt.o
mv -f .deps/libcord_la-cordprnt.Tpo .deps/libcord_la-cordprnt.Plo
/bin/sh ./libtool  --tag=CC   --mode=compile gcc -DHAVE_CONFIG_H   -I./include -I./include -I./libatomic_ops/src
tra.Tpo -c -o libcord_la-cordxtra.lo `test -f 'cord/cordxtra.c' || echo './'`cord/cordxtra.c
libtool: compile:  gcc -DHAVE_CONFIG_H -I./include -I./include -I./libatomic_ops/src -I./libatomic_ops/src -fexc
libcord_la-cordxtra.o
mv -f .deps/libcord_la-cordxtra.Tpo .deps/libcord_la-cordxtra.Plo
/bin/sh ./libtool --tag=CC   --mode=link gcc -fexceptions -Wall -Wextra  -DGC_DISABLE_INCREMENTAL -DGC_FORCE_UNM
s.lo libcord_la-cordprnt.lo libcord_la-cordxtra.lo ./libgc.la
libtool: link: ar cru .libs/libcord.a  libcord_la-cordbscs.o libcord_la-cordprnt.o libcord_la-cordxtra.o
libtool: link: ranlib .libs/libcord.a
libtool: link: ( cd ".libs" && rm -f "libcord.la" && cp -p "../libcord.la" "libcord.la" )
make[1]: Leaving directory `/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src'
make[1]: Entering directory `/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src'
make[2]: Entering directory `/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src'
test -z "/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/lib" || /bin/mkdir -p "/C/Use
 /bin/sh ./libtool   --mode=install /bin/install -c   libgc.la libcord.la '/C/Users/cran/Dropbox/docs/projects/g
libtool: install: /bin/install -c .libs/libgc.lai /C/Users/cran/Dropbox/docs/projects/github/robovm/external/bui
libtool: install: /bin/install -c .libs/libcord.lai /C/Users/cran/Dropbox/docs/projects/github/robovm/external/b
libtool: install: /bin/install -c .libs/libgc.a /C/Users/cran/Dropbox/docs/projects/github/robovm/external/build
libtool: install: chmod 644 /C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/lib/libgc.
libtool: install: ranlib /C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/lib/libgc.a
libtool: install: /bin/install -c .libs/libcord.a /C/Users/cran/Dropbox/docs/projects/github/robovm/external/bui
libtool: install: chmod 644 /C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/lib/libcor
libtool: install: ranlib /C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/lib/libcord.a
test -z "/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/share/gc" || /bin/mkdir -p "/
 /bin/install -c -m 644 AUTHORS README doc/README.DGUX386 doc/README.Mac doc/README.OS2 doc/README.amiga doc/REA
os doc/README.rs6000 doc/README.sgi doc/README.solaris2 doc/README.symbian doc/README.uts doc/README.win32 doc/R
c/simple_example.html doc/tree.html '/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/s
test -z "/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/include" || /bin/mkdir -p "/C
 /bin/install -c -m 644 include/extra/gc.h '/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src
test -z "/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/lib/pkgconfig" || /bin/mkdir
 /bin/install -c -m 644 bdw-gc.pc '/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/lib
test -z "/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src/dist/include/gc" || /bin/mkdir -p
 /bin/install -c -m 644 include/gc.h include/gc_allocator.h include/gc_backptr.h include/gc_config_macros.h incl
de/leak_detector.h include/weakpointer.h include/cord.h '/C/Users/cran/Dropbox/docs/projects/github/robovm/exter
make[2]: Leaving directory `/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src'
make[1]: Leaving directory `/C/Users/cran/Dropbox/docs/projects/github/robovm/external/build/src'
```


checking for ATOMIC_OPS... no
checking which libatomic_ops to use... internal

