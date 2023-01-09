#include <machine/syscall.h>
#include "internal_syscall.h"

/* Status of an open file. The sys/stat.h header file required is
   distributed in the include subdirectory for this C library.  */
__attribute__((weak))
int
_fstatat(int dirfd, const char *file, struct stat *st, int flags)
{
  return syscall_errno (SYS_fstatat, 4, dirfd, (long)file, (long)st, flags, 0, 0);
}

int fstatat(int dirfd, const char *file, struct stat *st, int flags) {
  return _fstatat(dirfd, file, st, flags);
}