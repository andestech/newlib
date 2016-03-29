#include <machine/syscall.h>
#include "internal_syscall.h"

/* Status of a file (by name).  */
__attribute__((weak))
int
_stat(const char *file, struct stat *st)
{
  return syscall_errno (SYS_stat, 2, (long)file, (long)st, 0, 0, 0, 0);
}

int stat(const char *file, struct stat *st) {
  return _stat(file, st);
}
