project(android-libcore)

include_directories(
  include
)

# Carl TEmp
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpermissive")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

if( NOT WINDOWS )
	add_definitions('-DGCC_HIDDEN=__attribute__((visibility(\"hidden\")))')
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
endif() 

add_subdirectory(luni/src/main/native)
set(LIBCORE_OBJECTS ${LIBCORE_LUNI_OBJECTS} PARENT_SCOPE)

