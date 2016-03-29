#include <machine/syscall.h>
#include "internal_syscall.h"

/* Open file relative to given directory.  */
__attribute__((weak))
int _openat(int dirfd, const char *name, int flags, int mode)
{
  return syscall_errno (SYS_openat, 4, dirfd, (long)name, flags, mode, 0, 0);
}

int openat(int dirfd, const char *name, int flags, int mode) {
  return _openat(dirfd, name, flags, mode);
}