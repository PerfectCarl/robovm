/*
 * Copyright (C) 2014 The Android Open Source Project
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

#ifndef MINGW_EXTENSIONS
#define MINGW_EXTENSIONS

#if !defined(__MINGW32__) && !defined(__MINGW64__)
    #error "mingw-extensions.h should be included only for MinGW builds"
#endif

// mingw-w64 now lacks support of these functions and structures
// If some of them are included into the new version of MinGW, they could be removed from this file

// winsock2.h has to be included before windows.h
#include <winsock2.h>

#include <windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <iphlpapi.h>

#include "Portability.h"

// errno.h

// Some constants are useless in Windows and aren't defined in
// MinGW headers, but they should be defined to build libcore_io_OsConstants.cpp

#define EAI_ADDRFAMILY			1
#define EAI_OVERFLOW			8
#define EAI_SYSTEM				11

#define AI_ADDRCONFIG			0x0001
#define AI_ALL					0x0002
#define AI_NUMERICSERV			0x0010
#define AI_V4MAPPED				0x0040
#define AI_DEFAULT				(AI_V4MAPPED | AI_ADDRCONFIG)

#define NI_NUMERICSCOPE			0x0010

#ifdef EAGAIN
#undef EAGAIN
#endif
#define EAGAIN					EWOULDBLOCK		// EAGAIN should be equal to EWOULDBLOCK

#define ETXTBSY					26
#define ENOMSG					42
#define EIDRM					43
#define ENOSTR					60
#define ENODATA					61
#define ETIME					62
#define ENOSR					63
#define ENOLINK					67


#define EMULTIHOP				72
#define EDOTDOT					73
#define EBADMSG					74
#define ENOTUNIQ				76
#define EBADFD					77
#define EREMCHG					78
#define ELIBACC					79
#define ELIBBAD					80
#define ELIBSCN					81
#define ELIBMAX					82
#define ELIBEXEC				83
#define ERESTART				85
#define ESTRPIPE				86
#define EUSERS					87
#define ESOCKTNOSUPPORT			94
#define EPFNOSUPPORT			96
#define ESHUTDOWN				108
#define ETOOMANYREFS			109
#define EHOSTDOWN				112
#define ESTALE					116
#define EUCLEAN					117
#define ENOTNAM					118
#define ENAVAIL					119
#define EISNAM					120
#define EREMOTEIO				121
#define EDQUOT					122

#define ENOMEDIUM				123
#define EMEDIUMTYPE				124
#define ENOKEY					126
#define EKEYEXPIRED				127
#define EKEYREVOKED				128
#define EKEYREJECTED			129
#define ENOTRECOVERABLE			131

#define	FD_CLOEXEC				1

#define	F_DUPFD					0
#define	F_GETFD					1
#define	F_SETFD					2
#define	F_GETFL					3
#define	F_SETFL					4
#define	F_GETOWN				5
#define F_SETOWN				6
#define	F_GETLK					7
#define	F_SETLK					8
#define	F_SETLKW				9

#define	F_RDLCK					1
#define	F_UNLCK					2
#define	F_WRLCK					3

#define IFF_DEBUG				0x0004 
#define IFF_ALLMULTI			0x0200 
#define IFF_NOARP				0x0080
#define IFF_NOTRAILERS			0x0020
#define IFF_POINTOPOINT			0x0010
#define IFF_PROMISC				0x0100
#define IFF_RUNNING				0x0040

#define MCL_CURRENT				1
#define MCL_FUTURE				2

#define MSG_CTRUNC				8
#define MSG_EOR					0x80
#define MSG_TRUNC				0x20

#define O_NOCTTY				0x00000400
#define O_NOFOLLOW				0x00400000
#define O_NONBLOCK				0x00004000
#define O_SYNC					0x04100000

#define POLLIN					0x0001
#define POLLPRI					0x0002
#define POLLOUT					0x0004
#define POLLERR					0x0008
#define POLLHUP					0x0010
#define POLLNVAL				0x0020

#define POLLRDNORM				0x0040
#define POLLRDBAND				0x0080
#define POLLWRNORM				0x0100
#define POLLWRBAND				0x0200

enum sock_shutdown_cmd {
    SHUT_RD = SD_RECEIVE,
    SHUT_WR = SD_SEND,
    SHUT_RDWR = SD_BOTH
};

#define SIGHUP					1
#define SIGQUIT					3
#define SIGTRAP					5
#define SIGBUS					7
#define SIGKILL					9
#define SIGUSR1					10
#define SIGUSR2					12
#define SIGPIPE					13
#define SIGALRM					14
#define SIGCHLD					17
#define SIGCONT					18
#define SIGSTOP					19
#define SIGTSTP					20
#define SIGTTIN					21
#define SIGTTOU					22
#define SIGURG					23
#define SIGXCPU					24
#define SIGXFSZ					25
#define SIGVTALRM				26
#define SIGPROF					27
#define SIGWINCH				28
#define SIGIO					29
#define SIGSYS					31

#define SIOCGIFADDR				0x8915
#define SIOCGIFDSTADDR			0x8917
#define SIOCGIFBRDADDR			0x8919
#define SIOCGIFNETMASK			0x891b

#define WNOHANG					0x00000001
#define WUNTRACED				0x00000002
#define WSTOPPED				WUNTRACED
#define WEXITED					0x00000004
#define WCONTINUED				0x00000008
#define WNOWAIT					0x01000000

#define NI_MAXHOST				1025
#define NI_MAXSERV				32

#define IFNAMSIZ				16

#define UNIX_PATH_LEN			108

#define MS_ASYNC				1
#define MS_SYNC					2
#define MS_INVALIDATE			4

#define _SC_ARG_MAX							0x0000
#define _SC_BC_BASE_MAX						0x0001
#define _SC_BC_DIM_MAX						0x0002
#define _SC_BC_SCALE_MAX					0x0003
#define _SC_BC_STRING_MAX					0x0004
#define _SC_CHILD_MAX						0x0005
#define _SC_CLK_TCK							0x0006
#define _SC_COLL_WEIGHTS_MAX				0x0007
#define _SC_EXPR_NEST_MAX					0x0008
#define _SC_LINE_MAX						0x0009
#define _SC_NGROUPS_MAX						0x000a
#define _SC_OPEN_MAX						0x000b
#define _SC_PASS_MAX						0x000c
#define _SC_2_C_BIND						0x000d
#define _SC_2_C_DEV							0x000e
#define _SC_2_C_VERSION						0x000f
#define _SC_2_CHAR_TERM						0x0010
#define _SC_2_FORT_DEV						0x0011
#define _SC_2_FORT_RUN						0x0012
#define _SC_2_LOCALEDEF						0x0013
#define _SC_2_SW_DEV						0x0014
#define _SC_2_UPE							0x0015
#define _SC_2_VERSION						0x0016
#define _SC_JOB_CONTROL						0x0017
#define _SC_SAVED_IDS						0x0018
#define _SC_VERSION							0x0019
#define _SC_RE_DUP_MAX						0x001a
#define _SC_STREAM_MAX						0x001b
#define _SC_TZNAME_MAX						0x001c
#define _SC_XOPEN_CRYPT						0x001d
#define _SC_XOPEN_ENH_I18N					0x001e
#define _SC_XOPEN_SHM						0x001f
#define _SC_XOPEN_VERSION					0x0020
#define _SC_XOPEN_XCU_VERSION				0x0021
#define _SC_XOPEN_REALTIME					0x0022
#define _SC_XOPEN_REALTIME_THREADS			0x0023
#define _SC_XOPEN_LEGACY					0x0024
#define _SC_ATEXIT_MAX						0x0025
#define _SC_IOV_MAX							0x0026
#define _SC_PAGESIZE						0x0027
#define _SC_PAGE_SIZE						0x0028
#define _SC_XOPEN_UNIX						0x0029
#define _SC_XBS5_ILP32_OFF32				0x002a
#define _SC_XBS5_ILP32_OFFBIG				0x002b
#define _SC_XBS5_LP64_OFF64					0x002c
#define _SC_XBS5_LPBIG_OFFBIG				0x002d
#define _SC_AIO_LISTIO_MAX					0x002e
#define _SC_AIO_MAX							0x002f
#define _SC_AIO_PRIO_DELTA_MAX				0x0030
#define _SC_DELAYTIMER_MAX					0x0031
#define _SC_MQ_OPEN_MAX						0x0032
#define _SC_MQ_PRIO_MAX						0x0033
#define _SC_RTSIG_MAX						0x0034
#define _SC_SEM_NSEMS_MAX					0x0035
#define _SC_SEM_VALUE_MAX					0x0036
#define _SC_SIGQUEUE_MAX					0x0037
#define _SC_TIMER_MAX						0x0038
#define _SC_ASYNCHRONOUS_IO					0x0039
#define _SC_FSYNC							0x003a
#define _SC_MAPPED_FILES					0x003b
#define _SC_MEMLOCK							0x003c
#define _SC_MEMLOCK_RANGE					0x003d
#define _SC_MEMORY_PROTECTION				0x003e
#define _SC_MESSAGE_PASSING					0x003f
#define _SC_PRIORITIZED_IO					0x0040
#define _SC_PRIORITY_SCHEDULING				0x0041
#define _SC_REALTIME_SIGNALS				0x0042
#define _SC_SEMAPHORES						0x0043
#define _SC_SHARED_MEMORY_OBJECTS			0x0044
#define _SC_SYNCHRONIZED_IO					0x0045
#define _SC_TIMERS							0x0046
#define _SC_GETGR_R_SIZE_MAX				0x0047
#define _SC_GETPW_R_SIZE_MAX				0x0048
#define _SC_LOGIN_NAME_MAX					0x0049
#define _SC_THREAD_DESTRUCTOR_ITERATIONS	0x004a
#define _SC_THREAD_KEYS_MAX					0x004b
#define _SC_THREAD_STACK_MIN				0x004c
#define _SC_THREAD_THREADS_MAX				0x004d
#define _SC_TTY_NAME_MAX					0x004e

#define _SC_THREADS                 	    0x004f
#define _SC_THREAD_ATTR_STACKADDR			0x0050
#define _SC_THREAD_ATTR_STACKSIZE			0x0051
#define _SC_THREAD_PRIORITY_SCHEDULING		0x0052
#define _SC_THREAD_PRIO_INHERIT				0x0053
#define _SC_THREAD_PRIO_PROTECT				0x0054
#define _SC_THREAD_SAFE_FUNCTIONS			0x0055

#define _SC_NPROCESSORS_CONF				0x0060
#define _SC_NPROCESSORS_ONLN				0x0061
#define _SC_PHYS_PAGES						0x0062
#define _SC_AVPHYS_PAGES					0x0063
#define _SC_MONOTONIC_CLOCK					0x0064

#ifndef TEMP_FAILURE_RETRY
/* Stub. On Windows EINTR makes no sense AFAIK.
 * TODO: verify that. */
#define TEMP_FAILURE_RETRY(exp) (exp)
#endif

#define IF_NAMESIZE				256

typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef long loff_t;
typedef int socklen_t;
typedef unsigned int nfds_t;

typedef struct _sockaddr_un {
    uint16_t   sun_family;
    char       sun_path[UNIX_PATH_LEN];
} sockaddr_un;

// pwd.h

struct passwd
{
  char *pw_name;
  char *pw_passwd;
  uid_t pw_uid;
  gid_t pw_gid;
  char *pw_comment;
  char *pw_gecos;
  char *pw_dir;
  char *pw_shell;
};
int getpwnam_r(const char *name, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result);
int getpwuid_r(uid_t uid, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result);

// sys/mman.h

#define PROT_NONE				0
#define PROT_READ				1
#define PROT_WRITE				2
#define PROT_EXEC				4

#define MAP_FILE				0
#define MAP_SHARED				1
#define MAP_PRIVATE				2
#define MAP_TYPE				0xf
#define MAP_FIXED				0x10
#define MAP_ANONYMOUS			0x20
#define MAP_ANON				MAP_ANONYMOUS

#define MAP_FAILED				((void *)-1)

int mincore(void *addr, size_t length, unsigned char *vec);
void* mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);
int munmap(void *addr, size_t len);
int mprotect(void *addr, size_t len, int prot);
int msync(void *addr, size_t len, int flags);
int mlock(const void *addr, size_t len);
int munlock(const void *addr, size_t len);

// unistd.h

int pipe(int pipefd[2]);
int fdatasync(int fd);
int fsync(int fd);
gid_t getgid();
gid_t getegid();
pid_t getppid();
uid_t getuid();
uid_t geteuid();
int seteuid(uid_t euid);
int setegid(gid_t egid);
int setgid(gid_t gid);
pid_t setsid();
int setuid(uid_t euid);
int chown(const char *path, uid_t owner, gid_t group);
int lchown(const char *path, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int symlink(const char *path1, const char *path2);
int sysconf(int name);
ssize_t pread64(int fd, void *buf, size_t count, off_t offset);
ssize_t pwrite64(int fd, const void *buf, size_t count, off_t offset);

// sys/fcntl.h

struct flock64 {
        short  l_type;
        short  l_whence;
        loff_t l_start;
        loff_t l_len;
        pid_t  l_pid;
};
int fcntl(int fd, int cmd, ... /* arg */ );

// sys/ioctl.h

int ioctl(int fd, int request, void *argp);

// sys/stat.h

#define S_IFSOCK				0140000
#define S_IFLNK					0120000
#define S_ISUID					0004000
#define S_ISGID					0002000
#define S_ISVTX					0001000

#define S_IRWXG					00070
#define S_IRGRP					00040
#define S_IWGRP					00020
#define S_IXGRP					00010
#define S_IRWXO					00007
#define S_IROTH					00004
#define S_IWOTH					00002
#define S_IXOTH					00001

int fchmod(int fd, mode_t mode);
int lstat(const char *path, struct stat *buf);
int mkdir(const char *pathname, mode_t mode);

// statfs.h

struct statfs {
   long			f_type;
   long			f_bsize;
   long long	f_blocks;
   long long	f_bfree;
   long long	f_bavail;
   long			f_files;
   long			f_ffree;
   long			f_fsid;
   long			f_namelen;
   long			f_spare[6];
   
   long long	f_frsize;
};

int fstatfs(int fd, struct statfs *buf);
int statfs(const char *path, struct statfs *buf);

// poll.h

struct pollfd {
    SOCKET fd;
    short  events;
    short  revents;
};
int poll(struct pollfd *fds, nfds_t nfds, int timeout);

// sys/utsname.h

struct utsname
{
	char 	machine [20];
	char 	nodename [20];
	char 	release [20];
	char 	sysname [20];
	char 	version [20];
};
int uname(struct utsname *buf);

// signal.h

int kill(pid_t pid, int sig);

// sys/socket.h

struct ucred {
	unsigned int 	pid;
	uid_t 			uid;
	gid_t 			gid;
};
int socketpair(int domain, int type, int protocol, int sv[2]);

// net/if.h

struct ifmap {
    unsigned long   mem_start;
    unsigned long   mem_end;
    unsigned short  base_addr;
    unsigned char   irq;
    unsigned char   dma;
    unsigned char   port;
};
struct ifreq {
    char    ifr_name[IFNAMSIZ];
    union {
            sockaddr ifr_addr;
            sockaddr ifr_dstaddr;
            sockaddr ifr_broadaddr;
            sockaddr ifr_netmask;
            sockaddr ifr_hwaddr;
            short   ifr_flags;
            int     ifr_ifindex;
            int     ifr_metric;
            int     ifr_mtu;
            ifmap   ifr_map;
            char    ifr_slave[IFNAMSIZ];
            char    ifr_newname[IFNAMSIZ];
            char *  ifr_data;
    };
};
char *if_indextoname(unsigned int ifindex, char *ifname);

// arpa/inet.h

int inet_pton(int af, const char *src, void *dst);

const char *inet_ntop(int af, const void *src, char *dst, size_t cnt);
// stdlib.h

#define unsetenv(pname) SetEnvironmentVariable(pname, NULL)
#define setenv(__pname,__pvalue,___overwrite) \
({ \
  int result; \
 if (___overwrite == 0 && getenv (__pname)) result = 0; \
   else \
     result = SetEnvironmentVariable (__pname,__pvalue); \
 result; \
})

// termios.h

int tcsendbreak(int fd, int duration);
int tcdrain(int fd);

// stdio.h

int vasprintf(char **strp, const char *fmt, va_list args);
int asprintf(char **strp, const char *fmt, ...);

// sendfile.h

ssize_t sendfile(int out_fd, int in_fd, off_t * offset, size_t count);

// sys/wait.h

pid_t waitpid(pid_t pid, int *status, int options);

// string.h

char *strsignal(int sig);


// ** Not POSIX, but useful functions **

// This is the emulation for POSIX close() (unfortunately, the 
// default close() function in Windows doesn't close everything)
int mingw_close(int fd);

/* This emulates POSIX socket(); Windows has native implementation that works,
 * but we want more tricky implementation than that (differs on Windows version):
 * for WinXP / WinServer2003 create sockets with AF_INET even if AF_INET6 was requested
 * for newer OSes set IPV6_V6ONLY to "false" for AF_INET6 sockets */
SOCKET mingw_socket(int af, int type, int protocol);

// An equivalent for POSIX realpath function
char *mingw_realpath(const char *path, char *resolved_path);

// Converts Windows API error code into errno code
int windowsErrorToErrno(DWORD winErr);

// Gets a description for errno code
const char* getErrnoDescription(int err);

#ifdef MINGW_HAS_SECURE_API
	extern "C" int strerror_r(int errno, char *buf, size_t len) ;
#endif

#endif
