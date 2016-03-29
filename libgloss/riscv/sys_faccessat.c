#include <machine/syscall.h>
#include "internal_syscall.h"

/* Permissions of a file (by name) in a given directory.  */
__attribute__((weak))
int _faccessat(int dirfd, const char *file, int mode, int flags)
{
  return syscall_errno (SYS_faccessat, 4, dirfd, (long)file, mode, flags, 0, 0);
}

int faccessat(int dirfd, const char *file, int mode, int flags) {
  return _faccessat(dirfd, file, mode, flags);
}