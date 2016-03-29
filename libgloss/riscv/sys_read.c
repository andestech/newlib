#include <machine/syscall.h>
#include <sys/types.h>
#include "internal_syscall.h"

/* Read from a file.  */
__attribute__((weak))
ssize_t _read(int file, void *ptr, size_t len)
{
  return syscall_errno (SYS_read, 3, file, (long)ptr, len, 0, 0, 0);
}

ssize_t read(int file, void *ptr, size_t len) {
  return _read(file, ptr, len);
}
