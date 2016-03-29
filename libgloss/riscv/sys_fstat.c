#include <machine/syscall.h>
#include "internal_syscall.h"

/* Status of an open file. The sys/stat.h header file required is
   distributed in the include subdirectory for this C library.  */
__attribute__((weak))
int
_fstat(int file, struct stat *st)
{
  return syscall_errno (SYS_fstat, 2, file, (long)st, 0, 0, 0, 0);
}

int fstat(int file, struct stat *st) {
  return _fstat(file, st);
}
