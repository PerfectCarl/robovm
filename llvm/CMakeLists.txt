cmake_minimum_required(VERSION 2.8)
project(robovm-llvm)
include(ExternalProject)

if(OS STREQUAL "linux")
  set(LINUX YES)
elseif(OS STREQUAL "macosx")
  set(MACOSX YES)
elseif(OS STREQUAL "windows")
  set(WINDOWS YES)
  add_definitions(-DWINDOWS)
endif()

if( WINDOWS )
	if( JAVA_PATH ) 
		set( JNI_FOUND             "TRUE")
		set( JAVA_AWT_LIBRARY      "${JAVA_PATH}/lib/jawt.lib")
		set( JAVA_JVM_LIBRARY      "${JAVA_PATH}/lib/jvm.lib")
		set( JAVA_INCLUDE_PATH     "${JAVA_PATH}/include")
		set( JAVA_INCLUDE_PATH2    "${JAVA_PATH}/include/win32")
		set( JAVA_AWT_INCLUDE_PATH "${JAVA_PATH}/include")
		set( JNI_INCLUDE_DIRS      "${JAVA_INCLUDE_PATH};${JAVA_INCLUDE_PATH2};${JAVA_AWT_INCLUDE_PATH}")
		set( JNI_LIBRARIES         "${JAVA_AWT_LIBRARY};${JAVA_JVM_LIBRARY}")
	else()
		find_package(JNI REQUIRED)
	endif() 
else()
	find_package(JNI REQUIRED)
endif()

message(STATUS "JNI_INCLUDE_DIRS        : ${JNI_INCLUDE_DIRS}")
message(STATUS "JNI_LIBRARIES           : ${JNI_LIBRARIES}")
message(STATUS "JNI_FOUND               : ${JNI_FOUND}")
message(STATUS "JAVA_AWT_LIBRARY        : ${JAVA_AWT_LIBRARY}")
message(STATUS "JAVA_JVM_LIBRARY        : ${JAVA_JVM_LIBRARY}")
message(STATUS "JAVA_INCLUDE_PATH       : ${JAVA_INCLUDE_PATH}")
message(STATUS "JAVA_INCLUDE_PATH2      : ${JAVA_INCLUDE_PATH2}")
message(STATUS "JAVA_AWT_INCLUDE_PATH   : ${JAVA_AWT_INCLUDE_PATH}")

if (ARCH STREQUAL "x86")
  set(X86 YES)
elseif (ARCH STREQUAL "x86_64")
  set(X86_64 YES)
endif()

set(C_CXX_FLAGS "${C_CXX_FLAGS} -fvisibility=hidden -fdata-sections -ffunction-sections")
if(MACOSX AND X86)
  set(C_CXX_FLAGS "${C_CXX_FLAGS} -arch i386 -mmacosx-version-min=10.6")
  set(LD_FLAGS "${LD_FLAGS} -arch i386 -mmacosx-version-min=10.6")
elseif(MACOSX AND X86_64)
  set(C_CXX_FLAGS "${C_CXX_FLAGS} -arch x86_64 -mmacosx-version-min=10.6")
  set(LD_FLAGS "${LD_FLAGS} -arch x86_64 -mmacosx-version-min=10.6")
elseif(LINUX AND X86)
  set(C_CXX_FLAGS "${C_CXX_FLAGS} -m32")
  set(LD_FLAGS "${LD_FLAGS} -m64")
elseif(LINUX AND X86_64)
  set(C_CXX_FLAGS "${C_CXX_FLAGS} -m64")
  set(LD_FLAGS "${LD_FLAGS} -m64")
elseif(WINDOWS AND X86)
  set(C_CXX_FLAGS "${C_CXX_FLAGS} -m32")
  set(LD_FLAGS "${LD_FLAGS} -m64")
elseif(WINDOWS AND X86_64)
  set(C_CXX_FLAGS "${C_CXX_FLAGS} -m64")
  set(LD_FLAGS "${LD_FLAGS} -m64")
endif()

set(LLVM_ARCHS "X86^^ARM")
set(LLVM_C_FLAGS "${C_CXX_FLAGS} -fvisibility=hidden -fdata-sections -ffunction-sections")
set(LLVM_CXX_FLAGS "${C_CXX_FLAGS} -fvisibility=hidden -fdata-sections -ffunction-sections")

if( MACOSX OR LINUX )
ExternalProject_Add(extllvm
  URL http://llvm.org/releases/3.4/llvm-3.4.src.tar.gz
  LIST_SEPARATOR ^^
  CONFIGURE_COMMAND cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/llvm" "-DLLVM_TARGETS_TO_BUILD=${LLVM_ARCHS}" "-DCMAKE_C_FLAGS=${LLVM_C_FLAGS}" "-DCMAKE_CXX_FLAGS=${LLVM_CXX_FLAGS}" -G "MSYS Makefiles" ../extllvm/
)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${C_CXX_FLAGS} -fno-rtti")
set(CMAKE_INSTALL_DO_STRIP YES)

add_definitions(-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS)
if( WINDOWS ) 
include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2} ${LLVM_DIR}/include)
else()
include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2} ${CMAKE_BINARY_DIR}/llvm/include)
endif() 

if( WINDOWS )  
# C:\Users\cran\Dropbox\docs\projects\github\robovm\llvm\dependencies\mingw32\bin\llvm-config.exe --libs core bitreader bitwriter irreader ipo x86
# CARL: we added EVERYTHING to fix unrolved links
set(LLVM_LIBS
-lLLVMIRReader -lLLVMAsmParser -lLLVMInterpreter -lLLVMOption -lLLVMInstrumentation -lLLVMXCoreDisassembler 
-lLLVMXCoreCodeGen -lLLVMXCoreDesc -lLLVMXCoreInfo -lLLVMXCoreAsmPrinter -lLLVMSystemZDisassembler 
-lLLVMSystemZCodeGen -lLLVMSystemZAsmParser -lLLVMSystemZDesc -lLLVMSystemZInfo -lLLVMSystemZAsmPrinter 
-lLLVMSparcCodeGen -lLLVMSparcDesc -lLLVMSparcInfo -lLLVMR600CodeGen -lLLVMR600Desc -lLLVMR600Info
-lLLVMR600AsmPrinter -lLLVMPowerPCCodeGen -lLLVMPowerPCAsmParser -lLLVMPowerPCDesc -lLLVMPowerPCInfo
-lLLVMPowerPCAsmPrinter -lLLVMNVPTXCodeGen -lLLVMNVPTXDesc -lLLVMNVPTXInfo -lLLVMNVPTXAsmPrinter -lLLVMMSP430CodeGen
-lLLVMMSP430Desc -lLLVMMSP430Info -lLLVMMSP430AsmPrinter -lLLVMMipsDisassembler -lLLVMMipsCodeGen -lLLVMMipsAsmParser
-lLLVMMipsDesc -lLLVMMipsInfo -lLLVMMipsAsmPrinter -lLLVMHexagonCodeGen -lLLVMHexagonAsmPrinter -lLLVMHexagonDesc
-lLLVMHexagonInfo -lLLVMCppBackendCodeGen -lLLVMCppBackendInfo -lLLVMARMDisassembler -lLLVMARMCodeGen
-lLLVMARMAsmParser -lLLVMARMDesc -lLLVMARMInfo -lLLVMARMAsmPrinter -lLLVMAArch64Disassembler -lLLVMAArch64CodeGen
-lLLVMAArch64AsmParser -lLLVMAArch64Desc -lLLVMAArch64Info -lLLVMAArch64AsmPrinter -lLLVMAArch64Utils -lLLVMDebugInfo
-lLLVMLTO -lLLVMLinker -lLLVMipo -lLLVMVectorize -lLLVMBitWriter -lLLVMBitReader -lLLVMTableGen -lLLVMMCJIT
-lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMX86Desc -lLLVMX86Info
-lLLVMX86AsmPrinter -lLLVMX86Utils -lLLVMJIT -lLLVMRuntimeDyld -lLLVMExecutionEngine -lLLVMCodeGen -lLLVMObjCARCOpts
-lLLVMScalarOpts -lLLVMInstCombine -lLLVMTransformUtils -lLLVMipa -lLLVMAnalysis -lLLVMTarget -lLLVMCore
-lLLVMMCDisassembler -lLLVMMCParser -lLLVMMC -lLLVMObject -lLLVMSupport)
else()
# This was generated using 'llvm-config --libs core bitreader bitwriter irreader ipo arm x86 OUTPUT_VARIABLE LLVM_LIBS'
set(LLVM_LIBS
  -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMX86Desc -lLLVMX86Info 
  -lLLVMX86AsmPrinter -lLLVMX86Utils -lLLVMARMDisassembler -lLLVMARMCodeGen -lLLVMSelectionDAG 
  -lLLVMAsmPrinter -lLLVMCodeGen -lLLVMARMAsmParser -lLLVMMCParser -lLLVMARMDesc -lLLVMARMInfo 
  -lLLVMARMAsmPrinter -lLLVMipo -lLLVMObjCARCOpts -lLLVMVectorize -lLLVMScalarOpts -lLLVMInstCombine 
  -lLLVMTransformUtils -lLLVMipa -lLLVMAnalysis -lLLVMTarget -lLLVMMC -lLLVMObject -lLLVMIRReader 
  -lLLVMAsmParser -lLLVMBitWriter -lLLVMBitReader -lLLVMCore -lLLVMSupport 
)
endif()
# This was generated using 'llvm-config --ldflags'
if(LINUX)
  set(LLVM_LDFLAGS
    -L"${CMAKE_BINARY_DIR}/llvm/lib"
    -lrt -ldl -lpthread -lz
  )
elseif(MACOSX)
  set(LLVM_LDFLAGS
    -L"${CMAKE_BINARY_DIR}/llvm/lib"
    -lpthread -lz
  )
elseif(WINDOWS)
  set(LLVM_LDFLAGS
    -L"${LLVM_DIR}/lib"
	-lpsapi -limagehlp -lm
  )
endif()

set(SRC
  src/main/native/LLVM_wrap.c
  src/main/native/LLVMExtra.cpp
)

add_library(robovm-llvm SHARED ${SRC})
add_dependencies(robovm-llvm extllvm)
target_link_libraries(robovm-llvm ${LLVM_LIBS} ${LLVM_LDFLAGS})
set_target_properties(robovm-llvm PROPERTIES LINKER_LANGUAGE CXX)
if(WINDOWS)
  set_target_properties(robovm-llvm PROPERTIES LINK_FLAGS "-Wl,--kill-at -Wl,--gc-sections -Wl,--version-script=${CMAKE_SOURCE_DIR}/src/main/native/exports_windows.sym")
elseif(LINUX)
  set_target_properties(robovm-llvm PROPERTIES LINK_FLAGS "-Wl,--gc-sections -Wl,--version-script=${CMAKE_SOURCE_DIR}/src/main/native/exports_linux.sym")
elseif(MACOSX)
  set_target_properties(robovm-llvm PROPERTIES LINK_FLAGS "-Wl,-dead_strip -Wl,-exported_symbols_list -Wl,${CMAKE_SOURCE_DIR}/src/main/native/exports_macosx.sym")
endif()
set(INSTALL_DIR ${CMAKE_SOURCE_DIR}/src/main/resources/org/robovm/llvm/binding/${OS}/${ARCH})
install(TARGETS robovm-llvm DESTINATION ${INSTALL_DIR})
