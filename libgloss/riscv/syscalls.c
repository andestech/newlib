//========================================================================
// syscalls.c : Newlib operating system interface
//========================================================================
// This is the maven implementation of the narrow newlib operating
// system interface. It is based on the minimum stubs in the newlib
// documentation, the error stubs in libnosys, and the previous scale
// implementation. Please do not include any additional system calls or
// other functions in this file. Additional header and source files
// should be in the machine subdirectory.
//
// Here is a list of the functions which make up the operating system
// interface. The file management instructions execute syscall assembly
// instructions so that a proxy kernel (or the simulator) can marshal up
// the request to the host machine. The process management functions are
// mainly just stubs since for now maven only supports a single process.
//
//  - File management functions
//     + open   : (v) open file
//     + lseek  : (v) set position in file
//     + read   : (v) read from file
//     + write  : (v) write to file
//     + fstat  : (z) status of an open file
//     + stat   : (z) status of a file by name
//     + close  : (z) close a file
//     + link   : (z) rename a file
//     + unlink : (z) remote file's directory entry
//
//  - Process management functions
//     + execve : (z) transfer control to new proc
//     + fork   : (z) create a new process
//     + getpid : (v) get process id
//     + kill   : (z) send signal to child process
//     + wait   : (z) wait for a child process
//
//  - Misc functions
//     + isatty : (v) query whether output stream is a terminal
//     + times  : (z) timing information for current process
//     + sbrk   : (v) increase program data space
//     + _exit  : (-) exit program without cleaning up files
//
// There are two types of system calls. Those which return a value when
// everything is okay (marked with (v) in above list) and those which
// return a zero when everything is okay (marked with (z) in above
// list). On an error (ie. when the error flag is 1) the return value is
// always an errno which should correspond to the numbers in
// newlib/libc/include/sys/errno.h
//
// See the newlib documentation for more information
// http://sourceware.org/newlib/libc.html#Syscalls

#include <machine/syscall.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <utime.h>
#ifndef SBRK_USES_SYSCALL
#include "../glue.h"
#endif

//------------------------------------------------------------------------
// environment
//------------------------------------------------------------------------
// A pointer to a list of environment variables and their values. For a
// minimal environment, this empty list is adequate. We used to define
// environ here but it is already defined in
// xcc/src/newlib/libc/stdlib/environ.c so to avoid multiple definition
// errors we have commented this out for now.
//
// char* __env[1] = { 0 };
// char** environ = __env;

//------------------------------------------------------------------------
// open
//------------------------------------------------------------------------
// Open a file.

#define syscall_errno(n, a, b, c, d) \
        __internal_syscall(n, (long)(a), (long)(b), (long)(c), (long)(d))

long
__syscall_error(long a0)
{
  errno = -a0;
  return -1;
}

__attribute__((weak)) int
_open(const char *name, int flags, int mode)
{
  return syscall_errno (SYS_open, name, flags, mode, 0);
}

//------------------------------------------------------------------------
// openat
//------------------------------------------------------------------------
// Open file relative to given directory
__attribute__((weak)) int _openat(int dirfd, const char *name, int flags, int mode)
{
  return syscall_errno (SYS_openat, dirfd, name, flags, mode);
}

//------------------------------------------------------------------------
// lseek
//------------------------------------------------------------------------
// Set position in a file.

__attribute__((weak)) off_t
_lseek(int file, off_t ptr, int dir)
{
  return syscall_errno (SYS_lseek, file, ptr, dir, 0);
}

//----------------------------------------------------------------------
// read
//----------------------------------------------------------------------
// Read from a file.

__attribute__((weak)) ssize_t _read(int file, void *ptr, size_t len)
{
  return syscall_errno (SYS_read, file, ptr, len, 0);
}

//------------------------------------------------------------------------
// write
//------------------------------------------------------------------------
// Write to a file.

__attribute__((weak)) ssize_t
_write(int file, const void *ptr, size_t len)
{
  return syscall_errno (SYS_write, file, ptr, len, 0);
}

//------------------------------------------------------------------------
// fstat
//------------------------------------------------------------------------
// Status of an open file. The sys/stat.h header file required is
// distributed in the include subdirectory for this C library.

__attribute__((weak)) int
_fstat(int file, struct stat *st)
{
  return syscall_errno (SYS_fstat, file, st, 0, 0);
}

//------------------------------------------------------------------------
// stat
//------------------------------------------------------------------------
// Status of a file (by name).

__attribute__((weak)) int
_stat(const char *file, struct stat *st)
{
  return syscall_errno (SYS_stat, file, st, 0, 0);
}

//------------------------------------------------------------------------
// lstat
//------------------------------------------------------------------------
// Status of a link (by name).

__attribute__((weak)) int _lstat(const char *file, struct stat *st)
{
  return syscall_errno (SYS_lstat, file, st, 0, 0);
}

//------------------------------------------------------------------------
// fstatat
//------------------------------------------------------------------------
// Status of a file (by name) in a given directory.

__attribute__((weak)) int
_fstatat(int dirfd, const char *file, struct stat *st, int flags)
{
  return syscall_errno (SYS_fstatat, dirfd, file, st, flags);
}

//------------------------------------------------------------------------
// access
//------------------------------------------------------------------------
// Permissions of a file (by name).

__attribute__((weak)) int
_access(const char *file, int mode)
{
  return syscall_errno (SYS_access, file, mode, 0, 0);
}

//------------------------------------------------------------------------
// faccessat
//------------------------------------------------------------------------
// Permissions of a file (by name) in a given directory.

__attribute__((weak)) int _faccessat(int dirfd, const char *file, int mode, int flags)
{
  return syscall_errno (SYS_faccessat, dirfd, file, mode, flags);
}

//------------------------------------------------------------------------
// close
//------------------------------------------------------------------------
// Close a file.

__attribute__((weak)) int
_close(int file)
{
  return syscall_errno (SYS_close, file, 0, 0, 0);
}

//------------------------------------------------------------------------
// link
//------------------------------------------------------------------------
// Establish a new name for an existing file.

__attribute__((weak)) int _link(const char *old_name, const char *new_name)
{
  return syscall_errno (SYS_link, old_name, new_name, 0, 0);
}

//------------------------------------------------------------------------
// unlink
//------------------------------------------------------------------------
// Remove a file's directory entry.

__attribute__((weak)) int
_unlink(const char *name)
{
  return syscall_errno (SYS_unlink, name, 0, 0, 0);
}

//------------------------------------------------------------------------
// execve
//------------------------------------------------------------------------
// Transfer control to a new process. Minimal implementation for a
// system without processes from newlib documentation.

__attribute__((weak)) int
_execve(const char *name, char *const argv[], char *const env[])
{
  errno = ENOMEM;
  return -1;
}

//------------------------------------------------------------------------
// fork
//------------------------------------------------------------------------
// Create a new process. Minimal implementation for a system without
// processes from newlib documentation.

__attribute__((weak)) int _fork()
{
  errno = EAGAIN;
  return -1;
}

//------------------------------------------------------------------------
// getpid
//------------------------------------------------------------------------
// Get process id. This is sometimes used to generate strings unlikely
// to conflict with other processes. Minimal implementation for a
// system without processes just returns 1.

__attribute__((weak)) int
_getpid()
{
  return 1;
}

//------------------------------------------------------------------------
// kill
//------------------------------------------------------------------------
// Send a signal. Minimal implementation for a system without processes
// just causes an error.

__attribute__((weak)) int
_kill(int pid, int sig)
{
  errno = EINVAL;
  return -1;
}

//------------------------------------------------------------------------
// wait
//------------------------------------------------------------------------
// Wait for a child process. Minimal implementation for a system without
// processes just causes an error.

__attribute__((weak)) int _wait(int *status)
{
  errno = ECHILD;
  return -1;
}

//------------------------------------------------------------------------
// isatty
//------------------------------------------------------------------------
// Query whether output stream is a terminal. For consistency with the
// other minimal implementations, which only support output to stdout,
// this minimal implementation is suggested by the newlib docs.

__attribute__((weak)) int
_isatty(int file)
{
  struct stat s;
  int ret = _fstat (file, &s);
  return ret == -1 ? 0 : !!(s.st_mode & S_IFCHR);
}

//------------------------------------------------------------------------
// times
//------------------------------------------------------------------------
// Timing information for current process. From
// newlib/libc/include/sys/times.h the tms struct fields are as follows:
//
//  - clock_t tms_utime  : user clock ticks
//  - clock_t tms_stime  : system clock ticks
//  - clock_t tms_cutime : children's user clock ticks
//  - clock_t tms_cstime : children's system clock ticks
//
// Since maven does not currently support processes we set both of the
// children's times to zero. Eventually we might want to separately
// account for user vs system time, but for now we just return the total
// number of cycles since starting the program.

__attribute__((weak)) clock_t
_times(struct tms *buf)
{
  // when called for the first time, initialize t0
  static struct timeval t0;
  if(t0.tv_sec == 0)
    gettimeofday (&t0,0);

  struct timeval t;
  gettimeofday (&t, 0);

  long long utime = (t.tv_sec - t0.tv_sec) * 1000000 + (t.tv_usec - t0.tv_usec);
  buf->tms_utime = utime * CLOCKS_PER_SEC / 1000000;
  buf->tms_stime = buf->tms_cstime = buf->tms_cutime = 0;

  return -1;
}

//----------------------------------------------------------------------
// gettimeofday
//----------------------------------------------------------------------
// Get the current time.  Only relatively correct.

__attribute__((weak)) int
_gettimeofday(struct timeval *tp, void *tzp)
{
  return syscall_errno (SYS_gettimeofday, tp, 0, 0, 0);
}

//----------------------------------------------------------------------
// ftime
//----------------------------------------------------------------------
// Get the current time.  Only relatively correct.

__attribute__((weak)) int
_ftime(struct timeb *tp)
{
  tp->time = tp->millitm = 0;
  return 0;
}

//----------------------------------------------------------------------
// utime
//----------------------------------------------------------------------
// Stub.

__attribute__((weak)) int
_utime(const char *path, const struct utimbuf *times)
{
  return -1;
}

//----------------------------------------------------------------------
// chown
//----------------------------------------------------------------------
// Stub.

__attribute__((weak)) int _chown(const char *path, uid_t owner, gid_t group)
{
  return -1;
}

//----------------------------------------------------------------------
// chmod
//----------------------------------------------------------------------
// Stub.

__attribute__((weak)) int
_chmod(const char *path, mode_t mode)
{
  return -1;
}

//----------------------------------------------------------------------
// chdir
//----------------------------------------------------------------------
// Stub.

__attribute__((weak)) int
_chdir(const char *path)
{
  return -1;
}

//----------------------------------------------------------------------
// getcwd
//----------------------------------------------------------------------
// Stub.

__attribute__((weak)) char *
_getcwd(char *buf, size_t size)
{
  return NULL;
}

//----------------------------------------------------------------------
// sysconf
//----------------------------------------------------------------------
// Get configurable system variables

__attribute__((weak)) long
_sysconf(int name)
{
  switch (name)
    {
    case _SC_CLK_TCK:
      return CLOCKS_PER_SEC;
    }

  return -1;
}

//----------------------------------------------------------------------
// sbrk
//----------------------------------------------------------------------
// Increase program data space. As malloc and related functions depend
// on this, it is useful to have a working implementation. The following
// is suggested by the newlib docs and suffices for a standalone
// system.

#ifdef SBRK_USES_SYSCALL
__attribute__((weak)) void *
_sbrk(ptrdiff_t incr)
{
  static unsigned long heap_end;

  if (heap_end == 0)
    {
      long brk = syscall_errno (SYS_brk, 0, 0, 0, 0);
      if (brk == -1)
	return (void *)-1;
      heap_end = brk;
    }

  if (syscall_errno (SYS_brk, heap_end + incr, 0, 0, 0) != heap_end + incr)
    return (void *)-1;

  heap_end += incr;
  return (void *)(heap_end - incr);
}
#else
void *
_sbrk(ptrdiff_t incr)
{
  static uintptr_t heap_end;
  if (heap_end == 0) heap_end = (uintptr_t) _end;

  uintptr_t new_heap_end = heap_end + incr;

  register uintptr_t sp asm("sp");
  if (new_heap_end > sp) { // Check collision with stack pointer
    errno = ENOMEM;
    return (void*) -1;
  }

  uintptr_t old_heap_end = heap_end;
  heap_end = new_heap_end;
  return (void*) old_heap_end;
}
#endif

//------------------------------------------------------------------------
// _exit
//------------------------------------------------------------------------
// Exit a program without cleaning up files.

__attribute__((weak)) void
_exit(int exit_status)
{
  syscall_errno (SYS_exit, exit_status, 0, 0, 0);
  while (1);
}

//------------------------------------------------------------------------
// _rename
//------------------------------------------------------------------------
// Rename a file.

__attribute__((weak)) int
_rename(const char* oldpath, const char* newpath)
{
  return syscall_errno (SYS_rename, oldpath, newpath, 0, 0);
}
