/*
 * Copyright (c) 2019 BayLibre SAS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_TOOLCHAIN_STDINT_H_
#define ZEPHYR_INCLUDE_TOOLCHAIN_STDINT_H_

/*
 * Some gcc versions and/or configurations as found in the Zephyr SDK
 * (questionably) define __INT32_TYPE__ and derrivatives as a long int
 * which makes the printf format checker to complain about long vs int
 * mismatch when %u is given a u32_t argument, and u32_t pointers not
 * being compatible with int pointers. Let's redefine them to follow
 * common expectations and usage.
 */

#if __SIZEOF_INT__ != 4
#error "unexpected int width"
#endif

#undef __INT32_TYPE__
#undef __UINT32_TYPE__
#undef __INT_LEAST32_TYPE__
#undef __UINT_LEAST32_TYPE__
#define __INT32_TYPE__ int
#define __UINT32_TYPE__ unsigned int
#define __INT_LEAST32_TYPE__ __INT32_TYPE__
#define __UINT_LEAST32_TYPE__ __UINT32_TYPE__

/*
 * The confusion also exists with __INTPTR_TYPE__ which is either an int
 * (even when __INT32_TYPE__ is a long int) or a long int. Let's redefine
 * it to a long int to get some uniformity. Doing so also makes it compatible
 * with LP64 (64-bit) targets where a long is always 64-bit wide.
 */

#if __SIZEOF_POINTER__ != __SIZEOF_LONG__
#error "unexpected size difference between pointers and long ints"
#endif

#undef __INTPTR_TYPE__
#undef __UINTPTR_TYPE__
#define __INTPTR_TYPE__ long int
#define __UINTPTR_TYPE__ long unsigned int

/*
 * POSIX errno macros. These are needed by libc implementations that
 * don't support the posix extensions since Zephyr uses libc posix
 * extensions.
 *
 */

#undef EPERM
#undef ENOENT
#undef ESRCH
#undef EINTR
#undef EIO
#undef ENXIO
#undef E2BIG
#undef ENOEXEC
#undef EBADF
#undef ECHILD
#undef EAGAIN
#undef ENOMEM
#undef EACCES
#undef EFAULT
#undef ENOTEMPTY
#undef EBUSY
#undef EEXIST
#undef EXDEV
#undef ENODEV
#undef ENOTDIR
#undef EISDIR
#undef EINVAL
#undef ENFILE
#undef EMFILE
#undef ENOTTY
#undef ENAMETOOLONG
#undef EFBIG
#undef ENOSPC
#undef ESPIPE
#undef EROFS
#undef EMLINK
#undef EPIPE
#undef EDEADLK
#undef ENOLCK
#undef ENOTSUP
#undef EMSGSIZE

#define EPERM        1  /* Not owner */
#define ENOENT       2  /* No such file or directory */
#define ESRCH        3  /* No such context */
#define EINTR        4  /* Interrupted system call */
#define EIO          5  /* I/O error */
#define ENXIO        6  /* No such device or address */
#define E2BIG        7  /* Arg list too long */
#define ENOEXEC      8  /* Exec format error */
#define EBADF        9  /* Bad file number */
#define ECHILD       10 /* No children */
#define EAGAIN       11 /* No more contexts */
//#define ENOMEM       12 /* Not enough core */
#define EACCES       13 /* Permission denied */
#define EFAULT       14 /* Bad address */
#define ENOTEMPTY    15 /* Directory not empty */
#define EBUSY        16 /* Mount device busy */
#define EEXIST       17 /* File exists */
#define EXDEV        18 /* Cross-device link */
#define ENODEV       19 /* No such device */
#define ENOTDIR      20 /* Not a directory */
#define EISDIR       21 /* Is a directory */
//#define EINVAL       22 /* Invalid argument */
#define ENFILE       23 /* File table overflow */
#define EMFILE       24 /* Too many open files */
#define ENOTTY       25 /* Not a typewriter */
#define ENAMETOOLONG 26 /* File name too long */
#define EFBIG        27 /* File too large */
#define ENOSPC       28 /* No space left on device */
#define ESPIPE       29 /* Illegal seek */
#define EROFS        30 /* Read-only file system */
#define EMLINK       31 /* Too many links */
#define EPIPE        32 /* Broken pipe */
#define EDEADLK      33 /* Resource deadlock avoided */
#define ENOLCK       34 /* No locks available */
#define ENOTSUP      35 /* Unsupported value */
#define EMSGSIZE     36 /* Message size */


#undef EDOM
#undef ERANGE
#undef EDESTADDRREQ
#undef EPROTOTYPE
#undef ENOPROTOOPT
#undef EPROTONOSUPPORT
#undef ESOCKTNOSUPPORT
#undef EOPNOTSUPP
#undef EPFNOSUPPORT
#undef EAFNOSUPPORT
#undef EADDRINUSE
#undef EADDRNOTAVAIL
#undef ENOTSOCK
#undef ENETUNREACH
#undef ENETRESET
#undef ECONNABORTED
#undef ECONNRESET
#undef ENOBUFS
#undef EISCONN
#undef ENOTCONN
#undef ESHUTDOWN
#undef ETOOMANYREFS
#undef ETIMEDOUT
#undef ECONNREFUSED
#undef ENETDOWN
#undef ETXTBSY
#undef ELOOP
#undef EHOSTUNREACH
#undef ENOTBLK
#undef EHOSTDOWN
#undef EINPROGRESS
#undef EALREADY
#undef EWOULDBLOCK
#undef ENOSYS
#undef ECANCELED
#undef ERRMAX
#undef ENOSR
#undef ENOSTR
#undef EPROTO
#undef EBADMSG
#undef ENODATA
#undef ETIME
#undef ENOMSG

/* ANSI math software */
//#define EDOM 37   /* Argument too large */
/* #define ERANGE 38 /\* Result too large *\/ */

/* ipc/network software */

/* argument errors */
#define EDESTADDRREQ 40    /* Destination address required */
#define EPROTOTYPE 41      /* Protocol wrong type for socket */
#define ENOPROTOOPT 42     /* Protocol not available */
#define EPROTONOSUPPORT 43 /* Protocol not supported */
#define ESOCKTNOSUPPORT 44 /* Socket type not supported */
#define EOPNOTSUPP 45      /* Operation not supported on socket */
#define EPFNOSUPPORT 46    /* Protocol family not supported */
#define EAFNOSUPPORT 47    /* Addr family not supported */
#define EADDRINUSE 48      /* Address already in use */
#define EADDRNOTAVAIL 49   /* Can't assign requested address */
#define ENOTSOCK 50	/* Socket operation on non-socket */

/* operational errors */
#define ENETUNREACH 51  /* Network is unreachable */
#define ENETRESET 52    /* Network dropped connection on reset */
#define ECONNABORTED 53 /* Software caused connection abort */
#define ECONNRESET 54   /* Connection reset by peer */
#define ENOBUFS 55      /* No buffer space available */
#define EISCONN 56      /* Socket is already connected */
#define ENOTCONN 57     /* Socket is not connected */
#define ESHUTDOWN 58    /* Can't send after socket shutdown */
#define ETOOMANYREFS 59 /* Too many references: can't splice */
#define ETIMEDOUT 60    /* Connection timed out */
#define ECONNREFUSED 61 /* Connection refused */
#define ENETDOWN 62     /* Network is down */
#define ETXTBSY 63      /* Text file busy */
#define ELOOP 64	/* Too many levels of symbolic links */
#define EHOSTUNREACH 65 /* No route to host */
#define ENOTBLK 66      /* Block device required */
#define EHOSTDOWN 67    /* Host is down */

/* non-blocking and interrupt i/o */
#define EINPROGRESS 68 /* Operation now in progress */
#define EALREADY 69    /* Operation already in progress */
#define EWOULDBLOCK EAGAIN /* Operation would block */

#define ENOSYS 71 /* Function not implemented */

/* aio errors (should be under posix) */
#define ECANCELED 72 /* Operation canceled */

#define ERRMAX 81

/* specific STREAMS errno values */

#define ENOSR 74   /* Insufficient memory */
#define ENOSTR 75  /* STREAMS device required */
#define EPROTO 76  /* Generic STREAMS error */
#define EBADMSG 77 /* Invalid STREAMS message */
#define ENODATA 78 /* Missing expected message data */
#define ETIME 79   /* STREAMS timeout occurred */
#define ENOMSG 80  /* Unexpected message type */

/* #define EILSEQ 138 /\* Illegal byte sequence *\/ */

///////////////

// TODO: Move parts of minimal libc into posix_extensions, and then
// include it from here?

/* #if !defined(__ssize_t_defined) */
/* #define __ssize_t_defined */

/* #define unsigned signed */

// TODO: We couldn't use a typedef as other have done because this
// file is included through -imacros. Is this a problem?

// '__ssize_t_defined' acts as an header-guard in minimal libc, so
// define it to prevent others from defining 'ssize_t'.

#ifdef CONFIG_EXTERNAL_LIBC
#define __ssize_t_defined // TODO: Needed?
#define ssize_t __SIZE_TYPE__
// typedef __SIZE_TYPE__ ssize_t;
/* #undef unsigned */
#endif

/* #endif */

// TODO: Have minimal libc define ssize_t as a macro like we do here
// instead of a typedef?

#endif /* ZEPHYR_INCLUDE_TOOLCHAIN_STDINT_H_ */
