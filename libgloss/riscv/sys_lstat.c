#include <machine/syscall.h>
#include <sys/stat.h>
#include "internal_syscall.h"

/* Status of a link (by name).  */
__attribute__((weak))
int _lstat(const char *file, struct stat *st)
{
  return syscall_errno (SYS_lstat, 2, (long)file, (long)st, 0, 0, 0, 0);
}

int lstat(const char *file, struct stat *st) {
  return _lstat(file, st);
}