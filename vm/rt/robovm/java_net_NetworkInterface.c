/*
 * Copyright (C) 2013 Trillian AB
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
#include <robovm.h>
#include <unistd.h>
#include <sys/types.h>
#if defined(WINDOWS)
#   include <winsock2.h>
#   include <ws2tcpip.h>
//http://msdn.microsoft.com/en-us/library/ms738545(v=vs.85).aspx
//http://msdn.microsoft.com/en-us/library/ms740096(VS.85).aspx
#else
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <ifaddrs.h>
#if defined(DARWIN)
#   include <net/if_dl.h>
#   include <sys/sockio.h>
#else
#   include <net/if_arp.h>
#endif
#endif
#include <errno.h>
#include <string.h>
#include <stdlib.h>

static Class* java_lang_String_array = NULL;

static void throwSocketExceptionErrno(Env* env, int errnum) {
    char message[512];
    Class* exCls = rvmFindClassUsingLoader(env, "java/net/SocketException", NULL);
    if (!exCls) {
        return;
    }
    if (strerror_r(errnum, message, 512) == 0) {
        rvmThrowNew(env, exCls, message);
    } else {
        rvmThrowNew(env, exCls, NULL);
    }
}

static jboolean ioctl_ifreq(Env* env, Object* interfaceName, struct ifreq* ifreq, int request) {
#if !defined(WINDOWS)
    const char* name = rvmGetStringUTFChars(env, interfaceName);
    if (!name) {
        return FALSE;
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        throwSocketExceptionErrno(env, errno);
        return FALSE;
    }

    memset(ifreq, 0, sizeof(struct ifreq));
    strcpy(ifreq->ifr_name, name);
    if (ioctl(sock, request, ifreq) < 0) {
        close(sock);
        throwSocketExceptionErrno(env, errno);
        return FALSE;
    }
    close(sock);

    return TRUE;
#else
    return FALSE;
#endif
}

static jboolean iterateAddrInfo(Env* env, const char* interfaceName, jboolean (*f)(Env*, struct ifaddrs *, void*), void* data) {
#if !defined(WINDOWS)
    struct ifaddrs *ap, *apit;
    if (getifaddrs(&ap) < 0) {
        throwSocketExceptionErrno(env, errno);
        return FALSE;
    }

    for (apit = ap; apit != NULL; apit = apit->ifa_next) {
        if (!interfaceName || !strcmp(apit->ifa_name, interfaceName)) {
            if (!f(env, apit, data)) {
                break;
            }
        }
    }

    freeifaddrs(ap);
    return TRUE;
#else
    return FALSE;
#endif
}

ObjectArray* Java_java_net_NetworkInterface_getInterfaceNames(Env* env, Class* cls) {
#if !defined(WINDOWS)
    if (!java_lang_String_array) {
        java_lang_String_array = rvmFindClassUsingLoader(env, "[Ljava/lang/String;", NULL);
        if (!java_lang_String_array) {
            return NULL;
        }
    }

    struct if_nameindex* ifs = if_nameindex();
    if (!ifs) {
        // Assume out of memory
        rvmThrowOutOfMemoryError(env);
        return NULL;
    }
    jint count = 0;
    while (ifs[count].if_index > 0) {
        count++;
    }

    ObjectArray* result = rvmNewObjectArray(env, count, NULL, java_lang_String_array, NULL);
    if (!result) {
        goto done;
    }

    jint i = 0;
    for (i = 0; i < count; i++) {
        Object* name = rvmNewStringUTF(env, ifs[i].if_name, -1);
        if (!name) {
            goto done;
        }
        result->values[i] = name;
    }

done:
    if_freenameindex(ifs);
    return result;
#else
    return NULL;
#endif
}

jint Java_java_net_NetworkInterface_getInterfaceIndex(Env* env, Class* cls, Object* interfaceName) {
#if !defined(WINDOWS)
    const char* name = rvmGetStringUTFChars(env, interfaceName);
    if (!name) {
        return 0;
    }
    return if_nametoindex(name);
#else
    return 0;
#endif
}

jint Java_java_net_NetworkInterface_getFlags(Env* env, Class* cls, Object* interfaceName) {
#if !defined(WINDOWS)
    struct ifreq ifreq;
    if (!ioctl_ifreq(env, interfaceName, &ifreq, SIOCGIFFLAGS)) {
        return 0;
    }
    return ((jint) ifreq.ifr_flags) & 0xffff;
#else
    return 0;
#endif
}

jint Java_java_net_NetworkInterface_getMTU(Env* env, Class* cls, Object* interfaceName) {
#if !defined(WINDOWS)
    struct ifreq ifreq;
    if (!ioctl_ifreq(env, interfaceName, &ifreq, SIOCGIFMTU)) {
        return 0;
    }
    return ifreq.ifr_mtu;
#else
    return 0;
#endif
}

#if defined(DARWIN)
static jboolean getHardwareAddressIterator(Env* env, struct ifaddrs *ia, void* data) {
    ByteArray** resultPtr = (ByteArray**) data;
    if (ia->ifa_addr->sa_family == AF_LINK) {
        struct sockaddr_dl* addr = (struct sockaddr_dl*) ia->ifa_addr;
        if (addr->sdl_alen == 6) {
            char* bytes = (char*) LLADDR(addr);
            *resultPtr = rvmNewByteArray(env, 6);
            if (*resultPtr) {
                memcpy((*resultPtr)->values, bytes, 6);
            }
            return FALSE; // Stop iteration
        }
    }
    return TRUE; // Continue iteration
}
#endif

ByteArray* Java_java_net_NetworkInterface_getHardwareAddress(Env* env, Class* cls, Object* interfaceName) {
    const char* name = rvmGetStringUTFChars(env, interfaceName);
    if (!name) {
        return NULL;
    }
    ByteArray* result = NULL;
#if !defined(WINDOWS)
#if defined(DARWIN)
    // Darwin doesn't have SIOCGIFHWADDR so we need to use getifaddrs() instead.
    iterateAddrInfo(env, name, getHardwareAddressIterator, &result);
#else
    struct ifreq ifreq;
    if (!ioctl_ifreq(env, interfaceName, &ifreq, SIOCGIFHWADDR)) {
        return NULL;
    }
    if (ifreq.ifr_hwaddr.sa_family == ARPHRD_ETHER) {
        result = rvmNewByteArray(env, 6);
        if (result) {
            memcpy(result->values, ifreq.ifr_hwaddr.sa_data, 6);
        }
    }
#endif
#endif
    return result;
}

#if !defined(WINDOWS)
static jboolean countIpv6AddressesIterator(Env* env, struct ifaddrs *ia, void* data) {
    jint* count = (jint*) data;
    if (ia->ifa_addr && ia->ifa_addr->sa_family == AF_INET6) {
        (*count)++;
    }
    return TRUE;
}
typedef struct {
    ByteArray* result;
    jint index;
} GetIpv6AddressesData;
static jboolean getIpv6AddressesIterator(Env* env, struct ifaddrs *ia, void* _data) {
    GetIpv6AddressesData* data = (GetIpv6AddressesData*) _data;
    if (ia->ifa_addr && ia->ifa_addr->sa_family == AF_INET6) {
        struct sockaddr_in6* addr = (struct sockaddr_in6*) ia->ifa_addr;
        struct sockaddr_in6* netmask = (struct sockaddr_in6*) ia->ifa_netmask;
        memcpy(data->result->values + (16 * 2 * data->index), addr->sin6_addr.s6_addr, 16);
        if (netmask) {
            memcpy(data->result->values + (16 * 2 * data->index) + 16, netmask->sin6_addr.s6_addr, 16);
        }
        data->index++;
    }
    return TRUE; // Continue iteration
}
ByteArray* Java_java_net_NetworkInterface_getIpv6Addresses(Env* env, Class* cls, Object* interfaceName) {
    const char* name = rvmGetStringUTFChars(env, interfaceName);
    if (!name) {
        return NULL;
    }
    jint count = 0;
    if (!iterateAddrInfo(env, name, countIpv6AddressesIterator, &count)) {
        return NULL;
    }

    if (count == 0) {
        return NULL;
    }

    ByteArray* result = rvmNewByteArray(env, 16 * 2 * count);
    if (!result) {
        return NULL;
    }

    GetIpv6AddressesData data = {result, 0};
    if (!iterateAddrInfo(env, name, getIpv6AddressesIterator, &data)) {
        return NULL;
    }
    return result;
}
#else
ByteArray* Java_java_net_NetworkInterface_getIpv6Addresses(Env* env, Class* cls, Object* interfaceName) {
    return NULL;
}
#endif
