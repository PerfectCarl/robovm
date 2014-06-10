/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PORTABILITY_H_included
#define PORTABILITY_H_included

#if defined(__APPLE__)

// Mac OS.
#include <AvailabilityMacros.h> // For MAC_OS_X_VERSION_MAX_ALLOWED

#include <libkern/OSByteOrder.h>
#define bswap_16 OSSwapInt16
#define bswap_32 OSSwapInt32
#define bswap_64 OSSwapInt64

#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
extern char** environ;
#else
#  include <crt_externs.h>
#  define environ (*_NSGetEnviron())
#endif

// Mac OS has a 64-bit off_t and no 32-bit compatibility cruft.
#define flock64 flock
#define ftruncate64 ftruncate
#define isnanf __inline_isnanf
#define lseek64 lseek
#define pread64 pread
#define pwrite64 pwrite

// TODO: Darwin appears to have an fdatasync syscall.
static inline int fdatasync(int fd) { return fsync(fd); }

// For Linux-compatible sendfile(3).
#include <sys/socket.h>
#include <sys/types.h>
static inline ssize_t sendfile(int out_fd, int in_fd, off_t* offset, size_t count) {
  off_t in_out_count = count;
  int result = sendfile(in_fd, out_fd, *offset, &in_out_count, NULL, 0);
  if (result == -1) {
    return -1;
  }
  return in_out_count;
}

// For mincore(3).
#define _DARWIN_C_SOURCE
#include <sys/mman.h>
#undef _DARWIN_C_SOURCE
static inline int mincore(void* addr, size_t length, unsigned char* vec) {
  return mincore(addr, length, reinterpret_cast<char*>(vec));
}

// For statfs(3).
#include <sys/param.h>
#include <sys/mount.h>
#define f_frsize f_bsize // TODO: close enough?

#elif defined(WIN32)

#include <stdint.h>

template <class T>
inline T
bswap_16(T v)
{
  return (((v >> 8) & 0xFF) |
          ((v << 8)));
}

template <class T>
inline T
bswap_32(T v)
{
  return (((v >> 24) & 0x000000FF) |
          ((v >>  8) & 0x0000FF00) |
          ((v <<  8) & 0x00FF0000) |
          ((v << 24)));
}

template <class T>
inline T
bswap_64(T v)
{
  return (((static_cast<uint64_t>(v) >> 56) & UINT64_C(0x00000000000000FF)) |
          ((static_cast<uint64_t>(v) >> 40) & UINT64_C(0x000000000000FF00)) |
          ((static_cast<uint64_t>(v) >> 24) & UINT64_C(0x0000000000FF0000)) |
          ((static_cast<uint64_t>(v) >>  8) & UINT64_C(0x00000000FF000000)) |
          ((static_cast<uint64_t>(v) <<  8) & UINT64_C(0x000000FF00000000)) |
          ((static_cast<uint64_t>(v) << 24) & UINT64_C(0x0000FF0000000000)) |
          ((static_cast<uint64_t>(v) << 40) & UINT64_C(0x00FF000000000000)) |
          ((static_cast<uint64_t>(v) << 56)));
}
#if !defined(__MINGW32__) && !defined(__MINGW64__)
inline char*
strtok_r(char* source, const char* delimiters, char** context)
{
  if (source == 0) {
    if (*context == 0) {
      return 0;
    } else {
      source = *context;
    }
  }

  { bool next = true;
    while (next) {
      next = false;
      for (const char* p = delimiters; *p; ++p) {
        if (*source == *p) {
          next = true;
          break;
        }
      }
      ++ source;
    }
  }

  if (*source == 0) {
    *context = 0;
    return 0;
  }

  char* result = source - 1;

  while (*source) {
    for (const char* p = delimiters; *p; ++p) {
      if (*source == *p) {
        *source = 0;
        *context = source + 1;
        return result;
      }
    }
    ++ source;    
  }

  *context = 0;
  return result;
}
#else 
// CARL HACK Needed
// strtok_r defined here
// Requires mingw64
#include <pthread.h>
#endif

#else

// Bionic or glibc.

#include <byteswap.h>
#include <sys/sendfile.h>

// For statfs(3).
#include <sys/vfs.h> // Bionic doesn't have <sys/statvfs.h>

#endif

#endif  // PORTABILITY_H_included
