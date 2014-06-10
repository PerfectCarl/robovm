Introduction
============

This a build of libcore64 for [Robovm 0.9](https://github.com/PerfectCarl/robovm/tree/link_windows_libcore64) using [cmake](www.cmake.org).
This wouldn't be possible without [Jan's work](https://github.com/janblok/robovm/tree/link_windows)

Libcore64 is a fork of Android libcore [4.4_r07](https://github.com/dicej/android-libcore64/issues/3) that supports **64 bits** and **Windows**

[Build](BUILD.md)
=================

Todo
====
- [ ] C libaries
  - [ ] libgc.a
  - librobovm-bc.a (no libcore code)
  - librobovm-core.a (no libcore code)
  - [ ] librobovm-debug.a
    vm/debug
  - [ ] librobovm-rt.a
    vm/rt
- [x] robovm-rt.jar
- [ ] certificates: no file has been added, but the content of the files are different
   - libcore64 in `luni/src/main/files/cacerts`
   - robovm in `cacerts/full/src/main/resources/cacerts`

