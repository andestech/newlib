#include <machine/syscall.h>
#include <sys/time.h>
#include <stdint.h>
#include "internal_syscall.h"

/* Get the current time.  Only relatively correct.  */
__attribute__((weak))
int
_gettimeofday(struct timeval *tp, void *tzp)
{
  return syscall_errno (SYS_gettimeofday, 1, (long)tp, 0, 0, 0, 0, 0);
}

int gettimeofday(struct timeval *tp, void *tzp) {
  return _gettimeofday(tp, tzp);
}
