/* src/config.h.  Generated from config.h.in by configure.  */
/* src/config.h.in.  Generated from configure.ac by autoheader.  */

/* Define demangle type */
#define BACKTRACE_DEMANGLE_METHOD_TEXT "cxa_demangle"

/* Define symbol lookup type */
/* #undef BACKTRACE_LOOKUP_METHOD_BACKTRACE_SYMBOLS */

/* Define symbol lookup type */
#define BACKTRACE_LOOKUP_METHOD_DLADDR 1

/* Define backtrace type */
#define BACKTRACE_LOOKUP_METHOD_TEXT "dladdr"

/* Define backtrace type */
#define BACKTRACE_METHOD_TEXT "x86 custom backtrace"

/* Define backtrace type */
#define BACKTRACE_METHOD_X86_LINUX 1

/* PPC */
/* #undef CPU_PPC */

/* x86 */
#define CPU_X86 1

/* x86-64 */
/* #undef CPU_X86_64 */

/* Define if using crash handler */
#define CRASH_HANDLER 1

/* Big endian */
/* #undef ENDIAN_BIG */

/* Little endian */
#define ENDIAN_LITTLE 1

/* Force OSS Usage */
/* #undef FORCE_OSS */

/* Define presence of ALSA */
#define HAVE_ALSA 1

/* abi::__cxa_demangle available */
#define HAVE_CXA_DEMANGLE 1

/* Define to 1 if you have the declaration of `SIGPWR', and to 0 if you don't.
   */
#define HAVE_DECL_SIGPWR 1

/* Define to 1 if you have the <endian.h> header file. */
#define HAVE_ENDIAN_H 1

/* FMPEG support available */
#define HAVE_FFMPEG 1

/* Define presence of GTK */
#define HAVE_GTK 1

/* Define if you have the iconv() function. */
#define HAVE_ICONV 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `asound' library (-lasound). */
#define HAVE_LIBASOUND 1

/* Liberty available */
/* #undef HAVE_LIBIBERTY */

/* libpthread is available */
#define HAVE_LIBPTHREAD 1

/* libXtst available */
#define HAVE_LIBXTST 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* OSS support available */
#define HAVE_OSS 1

/* OSS_GETVERSION is defined */
#define HAVE_OSS_GETVERSION 1

/* pthreads has pthread_cond_timedwait() */
#define HAVE_PTHREAD_COND_TIMEDWAIT 1

/* pthreads has pthread_mutex_timedlock() */
#define HAVE_PTHREAD_MUTEX_TIMEDLOCK 1

/* SDL is available */
/* #undef HAVE_SDL */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define if the compiler supports __thread */
#define HAVE_TLS 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* X11 libraries present */
#define HAVE_X11 1

/* Define as const if the declaration of iconv() needs const. */
#define ICONV_CONST 

/* Integer Vorbis decoding */
/* #undef INTEGER_VORBIS */

/* ITG Arcade specification */
/* #undef ITG_ARCADE */

/* Linux */
#define LINUX 1

/* stdint.h is missing */
/* #undef MISSING_STDINT_H */

/* Need acosf */
/* #undef NEED_ACOSF */

/* Need tanf */
/* #undef NEED_COSF */

/* cstdlib breaks llabs */
#define NEED_CSTDLIB_WORKAROUND 1

/* Need powf */
/* #undef NEED_POWF */

/* Need roundf */
/* #undef NEED_ROUNDF */

/* Need sinf */
/* #undef NEED_SINF */

/* Need sqrtf */
/* #undef NEED_SQRTF */

/* Need cosf */
/* #undef NEED_TANF */

/* Need truncf */
/* #undef NEED_TRUNCF */

/* JPEG support not available */
/* #undef NO_JPEG_SUPPORT */

/* MP3 support not available */
/* #undef NO_MP3_SUPPORT */

/* Vorbis support not available */
/* #undef NO_VORBIS_SUPPORT */

/* Name of package */
#define PACKAGE "StepMania"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Unix */
#define UNIX 1

/* Version number of package */
#define VERSION "3.001"

/* Networking support not available */
/* #undef WITHOUT_NETWORKING */

/* Use GNU extensions */
#define _GNU_SOURCE 1

/* Define to the compiler TLS keyword */
#define thread_local __thread
