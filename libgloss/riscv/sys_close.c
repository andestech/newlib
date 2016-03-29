#include <machine/syscall.h>
#include "internal_syscall.h"

/* Close a file.  */
__attribute__((weak))
int
_close(int file)
{
  return syscall_errno (SYS_close, 1, file, 0, 0, 0, 0, 0);
}

int close(int file) {
  return _close(file);
}
