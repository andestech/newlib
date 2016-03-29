#include <machine/syscall.h>
#include "internal_syscall.h"

/* Permissions of a file (by name).  */
__attribute__((weak))
int
_access(const char *file, int mode)
{
  return syscall_errno (SYS_access, 2, (long)file, mode, 0, 0, 0, 0);
}

int access(const char *file, int mode) {
  return _access(file, mode);
}