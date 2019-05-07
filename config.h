/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* display only boring messages */
/* #undef BORING_MODE */

/* Define to 1 if the `closedir' function returns void instead of `int'. */
/* #undef CLOSEDIR_VOID */

/* return value of an overflowed snprintf */
#define CONF_SNPRINTF_TYPE 8

/* defaut TCP receive buffer */
#define CONF_TCP_SO_RCVBUF 87380

/* default TCP send buffer */
#define CONF_TCP_SO_SNDBUF 16384

/* with cookie */
#define COOKIE 1

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Define to 1 if using `getloadavg.c'. */
/* #undef C_GETLOADAVG */

/* Define to 1 for DGUX with <sys/dg_sys_info.h>. */
/* #undef DGUX */

/* without globbing */
/* #undef DISABLE_GLOBBING */

/* without humor */
/* #undef DISABLE_HUMOR */

/* without sendfile */
/* #undef DISABLE_SENDFILE */

/* disallow unicode control chars */
/* #undef DISABLE_UNICODE_CONTROL_CHARS */

/* without iplogging */
/* #undef DONT_LOG_IP */

/* with ftpwho */
#define FTPWHO 1

/* Define to the type of elements in the array set by `getgroups'. Usually
   this is either `int' or `gid_t'. */
#define GETGROUPS_T gid_t

/* Define if the `getloadavg' function needs to be run setuid or setgid. */
/* #undef GETLOADAVG_PRIVILEGED */

/* Define to 1 if you have the `alarm' function. */
#define HAVE_ALARM 1

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#define HAVE_ALLOCA_H 1

/* Define to 1 if you have the `arc4random' function. */
/* #undef HAVE_ARC4RANDOM */

/* Define to 1 if you have the `arc4random_addrandom' function. */
/* #undef HAVE_ARC4RANDOM_ADDRANDOM */

/* Define to 1 if you have the `arc4random_stir' function. */
/* #undef HAVE_ARC4RANDOM_STIR */

/* Define to 1 if your system has a working `chown' function. */
#define HAVE_CHOWN 1

/* Define to 1 if you have the `closefrom' function. */
/* #undef HAVE_CLOSEFROM */

/* Define to 1 if you have the <CoreFoundation/CoreFoundation.h> header file.
   */
/* #undef HAVE_COREFOUNDATION_COREFOUNDATION_H */

/* Define to 1 if you have the <crypt.h> header file. */
#define HAVE_CRYPT_H 1

/* Define to 1 if you have the declaration of `tzname', and to 0 if you don't.
   */
/* #undef HAVE_DECL_TZNAME */

/* Define if you have /dev/random */
#define HAVE_DEV_RANDOM /**/

/* Define if you have /dev/urandom */
#define HAVE_DEV_URANDOM /**/

/* Define to 1 if you have the `DH_get_2048_256' function. */
#define HAVE_DH_GET_2048_256 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Define to 1 if you have the `explicit_bzero' function. */
#define HAVE_EXPLICIT_BZERO 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `fileno' function. */
#define HAVE_FILENO 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define to 1 if you have the `getaddrinfo' function. */
#define HAVE_GETADDRINFO 1

/* Define to 1 if your system has a working `getgroups' function. */
#define HAVE_GETGROUPS 1

/* Define to 1 if you have the `gethostname' function. */
#define HAVE_GETHOSTNAME 1

/* Define to 1 if you have the `getloadavg' function. */
#define HAVE_GETLOADAVG 1

/* Define to 1 if you have the `getnameinfo' function. */
#define HAVE_GETNAMEINFO 1

/* Define to 1 if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define to 1 if you have the `getopt_long' function. */
#define HAVE_GETOPT_LONG 1

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define to 1 if you have the `getpwnam_shadow' function. */
/* #undef HAVE_GETPWNAM_SHADOW */

/* Define to 1 if you have the `inet_ntop' function. */
#define HAVE_INET_NTOP 1

/* Define to 1 if you have the `inet_pton' function. */
#define HAVE_INET_PTON 1

/* Define to 1 if you have the `initgroups' function. */
#define HAVE_INITGROUPS 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <ioctl.h> header file. */
/* #undef HAVE_IOCTL_H */

/* Define to 1 if you have the <io.h> header file. */
/* #undef HAVE_IO_H */

/* Define to 1 if you have the `cap' library (-lcap). */
#define HAVE_LIBCAP 1

/* Define to 1 if you have the `crypt' library (-lcrypt). */
#define HAVE_LIBCRYPT 1

/* Define to 1 if you have the `crypto' library (-lcrypto). */
#define HAVE_LIBCRYPTO 1

/* Define to 1 if you have the `dgc' library (-ldgc). */
/* #undef HAVE_LIBDGC */

/* Define to 1 if you have the `dl' library (-ldl). */
/* #undef HAVE_LIBDL */

/* Define to 1 if you have the `kstat' library (-lkstat). */
/* #undef HAVE_LIBKSTAT */

/* Define to 1 if you have the `lber' library (-llber). */
/* #undef HAVE_LIBLBER */

/* Define to 1 if you have the `ldap' library (-lldap). */
/* #undef HAVE_LIBLDAP */

/* Define to 1 if you have the `m' library (-lm). */
#define HAVE_LIBM 1

/* Define to 1 if you have the `mariadb' library (-lmariadb). */
/* #undef HAVE_LIBMARIADB */

/* Define to 1 if you have the `mysqlclient' library (-lmysqlclient). */
#define HAVE_LIBMYSQLCLIENT 1

/* Define to 1 if you have the `nsl' library (-lnsl). */
/* #undef HAVE_LIBNSL */

/* Define to 1 if you have the `pq' library (-lpq). */
/* #undef HAVE_LIBPQ */

/* Define to 1 if you have the `resolv' library (-lresolv). */
/* #undef HAVE_LIBRESOLV */

/* Define to 1 if you have the `sendfile' library (-lsendfile). */
/* #undef HAVE_LIBSENDFILE */

/* Define to 1 if you have the `socket' library (-lsocket). */
/* #undef HAVE_LIBSOCKET */

/* Define to 1 if you have the `sodium' library (-lsodium). */
/* #undef HAVE_LIBSODIUM */

/* Define to 1 if you have the `ssl' library (-lssl). */
#define HAVE_LIBSSL 1

/* Define to 1 if you have the `z' library (-lz). */
#define HAVE_LIBZ 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if `lstat' has the bug that it succeeds when given the
   zero-length file name argument. */
/* #undef HAVE_LSTAT_EMPTY_STRING_BUG */

/* Define to 1 if you have the <mach/mach.h> header file. */
/* #undef HAVE_MACH_MACH_H */

/* Define to 1 if you have the `madvise' function. */
#define HAVE_MADVISE 1

/* Define to 1 if you have the `mapviewoffile' function. */
/* #undef HAVE_MAPVIEWOFFILE */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mkfifo' function. */
#define HAVE_MKFIFO 1

/* Define to 1 if you have the `mknod' function. */
#define HAVE_MKNOD 1

/* Define to 1 if you have a working `mmap' system call. */
#define HAVE_MMAP 1

/* Define to 1 if you have the `munmap' function. */
#define HAVE_MUNMAP 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <netinet/in_systm.h> header file. */
#define HAVE_NETINET_IN_SYSTM_H 1

/* Define to 1 if you have the <nlist.h> header file. */
/* #undef HAVE_NLIST_H */

/* obsolete pam */
/* #undef HAVE_OLD_PAM */

/* Define to 1 if you have the <openssl/ec.h> header file. */
#define HAVE_OPENSSL_EC_H 1

/* Define to 1 if you have the <openssl/ssl.h> header file. */
#define HAVE_OPENSSL_SSL_H 1

/* Define to 1 if you have the `pam_getenvlist' function. */
/* #undef HAVE_PAM_GETENVLIST */

/* Define to 1 if you have the <pam/pam_appl.h> header file. */
/* #undef HAVE_PAM_PAM_APPL_H */

/* Define to 1 if you have the <pam/pam_filter.h> header file. */
/* #undef HAVE_PAM_PAM_FILTER_H */

/* Define to 1 if you have the <pam/pam_misc.h> header file. */
/* #undef HAVE_PAM_PAM_MISC_H */

/* Define to 1 if you have the <pam/pam_modules.h> header file. */
/* #undef HAVE_PAM_PAM_MODULES_H */

/* Define to 1 if you have the `posix_fadvise' function. */
#define HAVE_POSIX_FADVISE 1

/* Define if you have POSIX termios */
#define HAVE_POSIX_TERMIOS /**/

/* Define to 1 if you have the `pread' function. */
#define HAVE_PREAD 1

/* Define to 1 if you have the `pstat_getdynamic' function. */
/* #undef HAVE_PSTAT_GETDYNAMIC */

/* Define to 1 if you have the `ptrace' function. */
#define HAVE_PTRACE 1

/* Define to 1 if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define to 1 if you have the `random' function. */
#define HAVE_RANDOM 1

/* Define to 1 if you have the `realpath' function. */
#define HAVE_REALPATH 1

/* Define if your timezone is a scalar number */
#define HAVE_SCALAR_TIMEZONE /**/

/* Define to 1 if you have the <security/pam_appl.h> header file. */
#define HAVE_SECURITY_PAM_APPL_H 1

/* Define to 1 if you have the <security/pam_filter.h> header file. */
#define HAVE_SECURITY_PAM_FILTER_H 1

/* Define to 1 if you have the <security/pam_misc.h> header file. */
#define HAVE_SECURITY_PAM_MISC_H 1

/* Define to 1 if you have the <security/pam_modules.h> header file. */
#define HAVE_SECURITY_PAM_MODULES_H 1

/* Define to 1 if you have the `setegid' function. */
#define HAVE_SETEGID 1

/* Define to 1 if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define to 1 if you have the `seteuid' function. */
#define HAVE_SETEUID 1

/* Define to 1 if you have the `setgroups' function. */
#define HAVE_SETGROUPS 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the `setproctitle' function. */
/* #undef HAVE_SETPROCTITLE */

/* Define to 1 if you have the `setregid' function. */
#define HAVE_SETREGID 1

/* Define to 1 if you have the `setresgid' function. */
#define HAVE_SETRESGID 1

/* Define to 1 if you have the `setresuid' function. */
#define HAVE_SETRESUID 1

/* Define to 1 if you have the `setreuid' function. */
#define HAVE_SETREUID 1

/* Define to 1 if you have the `setrlimit' function. */
#define HAVE_SETRLIMIT 1

/* Define to 1 if you have the `setusershell' function. */
#define HAVE_SETUSERSHELL 1

/* Define to 1 if you have the <sgtty.h> header file. */
#define HAVE_SGTTY_H 1

/* Define to 1 if you have the <shadow.h> header file. */
#define HAVE_SHADOW_H 1

/* define if you have sin_len */
/* #undef HAVE_SIN_LEN */

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the `srandomdev' function. */
/* #undef HAVE_SRANDOMDEV */

/* define if you have ss_len */
/* #undef HAVE_SS_LEN */

/* Define to 1 if you have the `statfs' function. */
#define HAVE_STATFS 1

/* Define to 1 if you have the `statvfs' function. */
#define HAVE_STATVFS 1

/* define if you have statvfs64 */
#define HAVE_STATVFS64 /**/

/* Define to 1 if `stat' has the bug that it succeeds when given the
   zero-length file name argument. */
/* #undef HAVE_STAT_EMPTY_STRING_BUG */

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strftime' function. */
#define HAVE_STRFTIME 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlcat' function. */
/* #undef HAVE_STRLCAT */

/* Define to 1 if you have the `strlcpy' function. */
/* #undef HAVE_STRLCPY */

/* Define to 1 if you have the `strtoq' function. */
#define HAVE_STRTOQ 1

/* Define to 1 if you have the `strtoull' function. */
#define HAVE_STRTOULL 1

/* define if you have struct addrinfo */
#define HAVE_STRUCT_ADDRINFO /**/

/* Define to 1 if `n_un.n_name' is a member of `struct nlist'. */
/* #undef HAVE_STRUCT_NLIST_N_UN_N_NAME */

/* Define to 1 if `tm_zone' is a member of `struct tm'. */
#define HAVE_STRUCT_TM_TM_ZONE 1

/* define if syslog names are available */
#define HAVE_SYSLOG_NAMES /**/

/* Define to 1 if you have the <sys/capability.h> header file. */
#define HAVE_SYS_CAPABILITY_H 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/fcntl.h> header file. */
#define HAVE_SYS_FCNTL_H 1

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/loadavg.h> header file. */
/* #undef HAVE_SYS_LOADAVG_H */

/* Define to 1 if you have the <sys/mount.h> header file. */
#define HAVE_SYS_MOUNT_H 1

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/pstat.h> header file. */
/* #undef HAVE_SYS_PSTAT_H */

/* Define to 1 if you have the <sys/ptrace.h> header file. */
#define HAVE_SYS_PTRACE_H 1

/* Define to 1 if you have the <sys/resource.h> header file. */
#define HAVE_SYS_RESOURCE_H 1

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/sendfile.h> header file. */
#define HAVE_SYS_SENDFILE_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/statvfs.h> header file. */
#define HAVE_SYS_STATVFS_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/uio.h> header file. */
#define HAVE_SYS_UIO_H 1

/* Define to 1 if you have the <sys/vfs.h> header file. */
#define HAVE_SYS_VFS_H 1

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <termio.h> header file. */
#define HAVE_TERMIO_H 1

/* Define to 1 if you have the `timegm' function. */
#define HAVE_TIMEGM 1

/* Define to 1 if you have the `TLS_server_method' function. */
#define HAVE_TLS_SERVER_METHOD 1

/* Define to 1 if your `struct tm' has `tm_zone'. Deprecated, use
   `HAVE_STRUCT_TM_TM_ZONE' instead. */
#define HAVE_TM_ZONE 1

/* Define to 1 if you don't have `tm_zone' but do have the external array
   `tzname'. */
/* #undef HAVE_TZNAME */

/* Define to 1 if you have the `tzset' function. */
#define HAVE_TZSET 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `unsetenv' function. */
#define HAVE_UNSETENV 1

/* Define to 1 if you have the `utime' function. */
#define HAVE_UTIME 1

/* Define to 1 if you have the `utimes' function. */
#define HAVE_UTIMES 1

/* Define to 1 if you have the <utime.h> header file. */
#define HAVE_UTIME_H 1

/* Define to 1 if `utime(file, NULL)' sets file's timestamp to the present. */
#define HAVE_UTIME_NULL 1

/* Define to 1 if you have the <varargs.h> header file. */
/* #undef HAVE_VARARGS_H */

/* Define to 1 if you have the `vfork' function. */
#define HAVE_VFORK 1

/* Define to 1 if you have the <vfork.h> header file. */
/* #undef HAVE_VFORK_H */

/* Define to 1 if you have the `vfprintf' function. */
#define HAVE_VFPRINTF 1

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the `wait3' system call. Deprecated, you should no
   longer depend upon `wait3'. */
#define HAVE_WAIT3 1

/* Define to 1 if you have the `waitpid' function. */
#define HAVE_WAITPID 1

/* Define to 1 if you have the <windows.h> header file. */
/* #undef HAVE_WINDOWS_H */

/* Define to 1 if `fork' works. */
#define HAVE_WORKING_FORK 1

/* Define to 1 if `vfork' works. */
#define HAVE_WORKING_VFORK 1

/* define if you have __ss_family */
/* #undef HAVE___SS_FAMILY */

/* define if you have __ss_len */
/* #undef HAVE___SS_LEN */

/* with implicit TLS */
/* #undef IMPLICIT_TLS */

/* Define to 1 if `lstat' dereferences a symlink specified with a trailing
   slash. */
#define LSTAT_FOLLOWS_SLASHED_SYMLINK 1

/* catalan */
/* #undef MESSAGES_CA_ES */

/* czech */
/* #undef MESSAGES_CS_CZ */

/* danish */
/* #undef MESSAGES_DA */

/* german */
/* #undef MESSAGES_DE */

/* english */
#define MESSAGES_EN /**/

/* spanish */
/* #undef MESSAGES_ES */

/* french */
/* #undef MESSAGES_FR */

/* french-funny */
/* #undef MESSAGES_FR_FUNNY */

/* hungarian */
/* #undef MESSAGES_HU */

/* italian */
/* #undef MESSAGES_IT */

/* korean */
/* #undef MESSAGES_KR */

/* dutch */
/* #undef MESSAGES_NL */

/* norwegian */
/* #undef MESSAGES_NO */

/* polish */
/* #undef MESSAGES_PL */

/* brazilian portuguese */
/* #undef MESSAGES_PT_BR */

/* romanian */
/* #undef MESSAGES_RO */

/* russian */
/* #undef MESSAGES_RU */

/* slovak */
/* #undef MESSAGES_SK */

/* albanian */
/* #undef MESSAGES_SQ */

/* swedish */
/* #undef MESSAGES_SV */

/* turkish */
/* #undef MESSAGES_TR */

/* simplified chinese */
/* #undef MESSAGES_ZH_CN */

/* traditional chinese */
/* #undef MESSAGES_ZH_TW */

/* with minimal */
/* #undef MINIMAL */

/* Never ever ignore assertions */
#ifdef NDEBUG
#/**/undef/**/ NDEBUG
#endif

/* Define to 1 if your `struct nlist' has an `n_un' member. Obsolete, depend
   on `HAVE_STRUCT_NLIST_N_UN_N_NAME */
/* #undef NLIST_NAME_UNION */

/* with nonroot */
/* #undef NON_ROOT_FTP */

/* without usernames */
/* #undef NO_FTP_USERS */

/* without longoptions */
/* #undef NO_GETOPT_LONG */

/* without inetd */
/* #undef NO_INETD */

/* without standalone */
/* #undef NO_STANDALONE */

/* Name of package */
#define PACKAGE "pure-ftpd"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://github.com/jedisct1/pure-ftpd/issues"

/* Define to the full name of this package. */
#define PACKAGE_NAME "pure-ftpd"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "pure-ftpd 1.0.49"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "pure-ftpd"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://www.pureftpd.org"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.0.49"

/* disallow non-alphanumeric characters */
/* #undef PARANOID_FILE_NAMES */

/* with paranoidmsg */
/* #undef PARANOID_MESSAGES */

/* with per-user limits */
#define PER_USER_LIMITS 1

/* with quotas */
#define QUOTAS 1

/* with ratios */
#define RATIOS 1

/* Define if realpath() works on unreadable directories */
#define REALPATH_WORKS_WITH_UNREADABLE_DIRECTORIES /**/

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Define is getgroups(0, NULL) works on your system */
#define SAFE_GETGROUPS_0 /**/

/* Define to the type of arg 1 for `select'. */
#define SELECT_TYPE_ARG1 int

/* Define to the type of args 2, 3 and 4 for `select'. */
#define SELECT_TYPE_ARG234 (fd_set *)

/* Define to the type of arg 5 for `select'. */
#define SELECT_TYPE_ARG5 (struct timeval *)

/* define if you have a linuxish sendfile64 */
#define SENDFILE64_LINUX /**/

/* define if you have a solarisish sendfilev */
/* #undef SENDFILEV_SOLARIS */

/* define if you have a freebsdish sendfile */
/* #undef SENDFILE_FREEBSD */

/* define if you have a hpuxish sendfile */
/* #undef SENDFILE_HPUX */

/* define if you have a linuxish sendfile */
#define SENDFILE_LINUX /**/

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 8

/* The size of `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* The size of `mode_t', as computed by sizeof. */
#define SIZEOF_MODE_T 4

/* The size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if the `S_IS*' macros in <sys/stat.h> do not work properly. */
/* #undef STAT_MACROS_BROKEN */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define if you have struct tm/tm_gmtoff */
#define STRUCT_TM_TM_GMTOFF /**/

/* Define to 1 on System V Release 4. */
/* #undef SVR4 */

/* with sysquotas */
/* #undef SYSTEM_QUOTAS */

/* with throttling */
#define THROTTLING 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Define to 1 for Encore UMAX. */
/* #undef UMAX */

/* Define to 1 for Encore UMAX 4.3 that has <inq_status/cpustats.h> instead of
   <sys/cpustats.h>. */
/* #undef UMAX4_3 */

/* realpath() is broken */
/* #undef USE_BUILTIN_REALPATH */

/* use capabilities */
#define USE_CAPABILITIES /**/

/* use pam */
/* #undef USE_PAM */

/* use shadow passwords */
#define USE_SHADOW /**/

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "1.0.49"

/* Define if you are inside a Virtuozzo virtual host */
/* #undef VIRTUOZZO */

/* without ascii */
#define WITHOUT_ASCII /**/

/* disable privilege separation */
/* #undef WITHOUT_PRIVSEP */

/* with altlog */
#define WITH_ALTLOG 1

/* Enable Bonjour on MacOS X */
/* #undef WITH_BONJOUR */

/* with directory aliases */
#define WITH_DIRALIASES 1

/* Define if using the dmalloc debugging malloc package */
/* #undef WITH_DMALLOC */

/* with extauth (*BETA*) */
#define WITH_EXTAUTH 1

/* with ldap */
/* #undef WITH_LDAP */

/* with mysql */
#define WITH_MYSQL /**/

/* with pgsql */
/* #undef WITH_PGSQL */

/* with puredb */
#define WITH_PUREDB 1

/* Enable TLS */
#define WITH_TLS /**/

/* with uploadscript */
#define WITH_UPLOAD_SCRIPT 1

/* with virtual chroot */
#define WITH_VIRTUAL_CHROOT /**/

/* with virtualhosts */
#define WITH_VIRTUAL_HOSTS 1

/* with welcomemsg */
#define WITH_WELCOME_MSG /**/

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* dev_t type */
/* #undef dev_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* in_port_t type */
/* #undef in_port_t */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* ino_t type */
/* #undef ino_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* nlink_t type */
/* #undef nlink_t */

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* sig_atomic_t type */
/* #undef sig_atomic_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* socklen_t type */
/* #undef socklen_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef ssize_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */

/* Define to empty if the keyword `volatile' does not work. Warning: valid
   code using `volatile' can become incorrect without. Disable with care. */
/* #undef volatile */
