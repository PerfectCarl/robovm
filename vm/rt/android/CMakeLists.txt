project(android)

include_directories(
  system/core/include/arch/${OS_FAMILY}-${ARCH}
  system/core/include
  libnativehelper/include/nativehelper
)

if( WINDOWS )
	include_directories(
	  libcore/luni/src/main/native
	)
  add_definitions(-DMINGW_HAS_SECURE_API=1)

endif() 

add_definitions(-DICU_DATA_DIR="/usr/share/icu")

if(IOS AND X86)
  add_definitions(-DICU_DATA_DIR_PREFIX_ENV_VAR="IPHONE_SIMULATOR_ROOT")
endif()
add_definitions(-DHAVE_ANDROID_OS=1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -include AndroidConfig.h")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include AndroidConfig.h")

add_subdirectory(crypto)
add_subdirectory(dalvik)
add_subdirectory(libcore)
add_subdirectory(libnativehelper)
add_subdirectory(external/expat)
add_subdirectory(external/fdlibm)
add_subdirectory(external/icu4c)
add_subdirectory(external/javasqlite)
#if( NOT WINDOWS )
	# Using separate distribution
	add_subdirectory(external/openssl)
#endif()

if(NOT DARWIN)
  # Mac OS X and iOS ships with sqlite so we'll just use that
  add_subdirectory(external/sqlite)
endif()

add_subdirectory(external/zlib)
if( WINDOWS ) 
	set(ANDROID_OBJECTS
	  ${CRYPTO_OBJECTS} 
	  ${DALVIK_OBJECTS} 
	  ${LIBCORE_OBJECTS} 
	  ${LIBNATIVEHELPER_OBJECTS} 
	  ${EXTERNAL_EXPAT_OBJECTS} 
	  ${EXTERNAL_FDLIBM_OBJECTS}
	  ${EXTERNAL_ICU4C_OBJECTS}
	  ${EXTERNAL_JAVASQLITE_OBJECTS}
	  ${EXTERNAL_OPENSSL_OBJECTS}
	  ${EXTERNAL_SQLITE_OBJECTS}
	  ${EXTERNAL_ZLIB_OBJECTS}
	  PARENT_SCOPE
	)
else()

	set(ANDROID_OBJECTS
	  ${CRYPTO_OBJECTS} 
	  ${DALVIK_OBJECTS} 
	  ${LIBCORE_OBJECTS} 
	  ${LIBNATIVEHELPER_OBJECTS} 
	  ${EXTERNAL_EXPAT_OBJECTS} 
	  ${EXTERNAL_FDLIBM_OBJECTS}
	  ${EXTERNAL_ICU4C_OBJECTS}
	  ${EXTERNAL_JAVASQLITE_OBJECTS}
	  ${EXTERNAL_OPENSSL_OBJECTS}
	  ${EXTERNAL_SQLITE_OBJECTS}
	  ${EXTERNAL_ZLIB_OBJECTS}
	  PARENT_SCOPE
	)
endif()
