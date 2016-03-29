#include <machine/syscall.h>
#include "internal_syscall.h"

/* Open a file.  */
__attribute__((weak))
int
_open(const char *name, int flags, int mode)
{
  return syscall_errno (SYS_open, 3, (long)name, flags, mode, 0, 0, 0);
}

int open(const char *name, int flags, int mode) {
  return _open(name, flags, mode);
}
