project(android-dalvik-vm)

include_directories(
  ../libnativehelper/include/nativehelper
)

set(SRC
  main/native/org_apache_harmony_dalvik_NativeTestTarget.cpp
)

add_library(android-dalvik-vm OBJECT ${SRC})
set(DALVIK_VM_OBJECTS $<TARGET_OBJECTS:android-dalvik-vm> PARENT_SCOPE)

