#include <machine/syscall.h>
#include <sys/types.h>
#include "internal_syscall.h"

/* Set position in a file.  */
__attribute__((weak))
off_t
_lseek(int file, off_t ptr, int dir)
{
  return syscall_errno (SYS_lseek, 3, file, ptr, dir, 0, 0, 0);
}

off_t lseek(int file, off_t ptr, int dir) {
  return _lseek(file, ptr, dir);
}
