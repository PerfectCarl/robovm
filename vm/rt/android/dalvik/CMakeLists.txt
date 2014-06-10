project(android-dalvik)

add_subdirectory(src)
set(DALVIK_OBJECTS
  ${DALVIK_VM_OBJECTS} 
  PARENT_SCOPE
)
