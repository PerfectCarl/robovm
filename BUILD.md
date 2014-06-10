maven
jdk x86
mingw

## robovm-llvm
### Pre requesites

1. compile [llvm 3.4](BUILD-LLVM-Windows.md) or superior
2. Update the variable `LLVM_DIR` in `llvm\generate-cmake.cmd` with the path to the output directory of llvm

### Build the c library 

Let's build `librobovm-llvm`.

```
	cd llvm
	clean.md
	generate-cmake.cmd
	build.cmd
```
The output files are in `llvm/target`
  - `librobovm-llvm.dll`
  - `librobovm-llvm.dll.a`

Because, we compile `librobovm-llvm.dll` wih mingw, it has the following dependencies: 
  - libcord-1.dll
  - libgc-1.dll
  - libgcc_s_sjlj-1.dll
  - libstdc++-6.dll
  - pthreadGC2.dll


### Build the java library 
Let's build `robovm-llvm.jar`.
You must use a 32 bits JDK to execute the tests

```
	mvn package
```
The output files are in `llvm/target`: 
  - `robovm-llvm.jar`

Note : the jar file includes the c library.

## Build vm 

### Prerequisites 

  - libgc
  - libatomic
  - pthread
  - dlfcn -> included in code ???
  - [openssl](BUILD-OPENSSL.md)

Most of the compiled prerequesites [are available](https://github.com/PerfectCarl/robovm-windows-binaries/tree/master/dependencies).

## [Old notes](BUILD-OLD.md)