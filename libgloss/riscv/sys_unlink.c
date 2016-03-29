#include <machine/syscall.h>
#include "internal_syscall.h"

/* Remove a file's directory entry.  */
__attribute__((weak))
int
_unlink(const char *name)
{
  return syscall_errno (SYS_unlink, 1, (long)name, 0, 0, 0, 0, 0);
}

int unlink(const char *name) {
  return _unlink(name);
}
