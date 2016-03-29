#include <machine/syscall.h>
#include <sys/types.h>
#include "internal_syscall.h"

/* Write to a file.  */
__attribute__((weak))
ssize_t
_write(int file, const void *ptr, size_t len)
{
  return syscall_errno (SYS_write, 3, file, (long)ptr, len, 0, 0, 0);
}

ssize_t write(int file, const void *ptr, size_t len) {
  return _write(file, ptr, len);
}
