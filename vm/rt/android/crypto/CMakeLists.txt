project(android-crypto)

add_subdirectory(src)
set(CRYPTO_OBJECTS
  ${CRYPTO_VM_OBJECTS} 
  PARENT_SCOPE
)
