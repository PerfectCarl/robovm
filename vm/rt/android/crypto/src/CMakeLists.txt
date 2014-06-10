project(android-crypto-vm)

include_directories(
  ../libnativehelper/include/nativehelper
  ../../libcore/include
#  ../../../../../dependencies/windows/openssl/no-shared/include
  ../../external/openssl/include
)

# Carl TEmp
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpermissive")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

set(SRC
  main/native/org_conscrypt_NativeCrypto.cpp
)

add_library(android-crypto-vm OBJECT ${SRC})
set(CRYPTO_VM_OBJECTS $<TARGET_OBJECTS:android-crypto-vm> PARENT_SCOPE)

